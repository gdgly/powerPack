/* DCL_TCM.h - Transient Capture Module header file
 *
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 *
*/

#ifndef _C_DCL_TCM_H
#define _C_DCL_TCM_H

//! \file   		DCL_TCM.h
//! \brief  		Contains the public interface to the Transient Capture Module (TCM)
//!

#include <stdint.h>
#include "DCL_fdlog.h"


//! \brief 			Defines the Transient Capture Module (TCM) structure
//!
//! \details		The TCM can be used to capture a transient response
//!
typedef volatile struct {
	FDLOG moniFrame;	//!< Monitor data frame
	FDLOG leadFrame;	//!< Lead data frame
	FDLOG captFrame;	//!< Capture data frame
	float trigMax;		//!< Upper trigger threshold
	float trigMin;		//!< Lower trigger threshold
	uint16_t mode;		//!< Operating mode
	uint16_t lead;		//!< Lead frame size in 32-bit words = trigger crossing index
} TCM;


//! \brief 			Defines default values to initialise the TCM structure
//!
#define TCM_DEFAULTS { 	FDLOG_DEFAULTS,	FDLOG_DEFAULTS,	FDLOG_DEFAULTS, 0.1, -0.1, 0, 10  }


//! \brief 			Enumerated TCM operating modes
//!
typedef enum
{
	TCM_invalid = 0,	//!< Buffer pointers not initialised
	TCM_idle,           //!< Memory initialised but module not armed
	TCM_armed,			//!< Armed: capturing monitor frame data and waiting for trigger
	TCM_capture,		//!< Triggered: logging data into capture frame and un-winding monitor frame
	TCM_complete,		//!< Full data frame captured and available for read-out
	TCM_numStates		//!< Number of TCM states
} TCM_states;


//! \brief     		Resets the TCM module: clears buffers and sets idle mode
//! \param[in] q	The TCM structure
//! \param[in] addr	The start address of the memory block
//! \param[in] size	The size of the memory block in 32-bit words
//! \param[in] lead	The length of the lead frame in samples
//! \param[in] tmin	The upper trigger threshold
//! \param[in] tmax	The lower trigger threshold
//!
static inline void DCL_initTCM(TCM *q, float *addr, uint16_t size, uint16_t lead, float tmin, float tmax)
{
	// assign and clear capture frame, and initialize index to end of lead frame
	DCL_initLog(&(q->captFrame), addr, size);
	DCL_clearLog(&(q->captFrame));
	q->captFrame.dptr = q->captFrame.fptr + lead;

	// assign lead & monitor frame pointers
	DCL_initLog(&(q->leadFrame), addr, lead);
	DCL_initLog(&(q->moniFrame), q->captFrame.lptr - lead + 1, lead);

	// load remaining TCM vars
	q->lead = lead;
	q->trigMax = tmax;
	q->trigMin = tmin;
	q->mode = TCM_idle;
}


//! \brief     		Resets the TCM module: clears all frame buffers and sets idle mode
//! \param[in] q	The TCM structure
//! \return    		The operating mode
//!
static inline void DCL_resetTCM(TCM *q)
{
	DCL_clearLog(&(q->captFrame));
	q->captFrame.dptr = q->captFrame.fptr + q->lead - 1;
	DCL_resetLog(&(q->leadFrame));
	DCL_resetLog(&(q->moniFrame));
	q->mode = TCM_idle;
}


//! \brief     		Changes the TCM mode to "TCM_armed".  Only valid if current operating mode is "TCM_idle"
//! \param[in] q	The TCM structure
//! \return    		The operating mode
//!
static inline uint16_t DCL_armTCM(TCM *q)
{
	q->mode = (q->mode == TCM_idle) ? TCM_armed : TCM_idle;
	return q->mode;
}


//! \brief     		Runs the TCM module
//! \param[in] q	The TCM structure
//! \param[in] data	The input data
//! \return    		The operating mode
//!
static inline uint16_t DCL_runTCM(TCM *q, float data)
{
	switch(q->mode)
	{
	// TCM not initialised
	case TCM_invalid:
		break;

	// idle: do nothing
	case TCM_idle:
		break;

	// armed: ready to begin capturing when either trigger threshold is crossed
	case TCM_armed:
		// check for trigger condition
		if ((data > q->trigMax) || (data < q->trigMin))
		{
			// capture first data point & switch to capture mode
			DCL_writeLog(&(q->captFrame), data);
			DCL_writeLog(&(q->leadFrame), DCL_readLog(&(q->moniFrame)));
			q->mode = TCM_capture;
		}
		else
		{
			// log data into monitor frame
			DCL_writeLog(&(q->moniFrame), data);
		}
		break;

	// capture mode: acquiring data
	case TCM_capture:
		// check for full capture frame
		if (q->captFrame.dptr > q->captFrame.fptr)
		{
			// write data into main frame
			DCL_writeLog(&(q->captFrame), data);

			// check for full lead frame
			if (q->leadFrame.dptr > q->leadFrame.fptr)
			{
				// un-wind monitor data into lead frame
				DCL_writeLog(&(q->leadFrame), DCL_readLog(&(q->moniFrame)));
			}
		}
		else
		{
			// TCM complete, capture frame spans full buffer
			q->captFrame.fptr = q->leadFrame.fptr;
			q->captFrame.dptr = q->captFrame.fptr;
			q->mode = TCM_complete;
		}
		break;

	// complete: do nothing - results available in capture buffer
	case TCM_complete:
		break;

	default:
		;
	}

	return q->mode;
}


//! \brief     		Computes ITAE performance index from a log of servo error.
//!					Assembly function.
//! \param[in] elog	The servo error log
//! \param[in] prd	The sampling period in seconds
//! \return    		The ITAE index
//!
extern float DCL_runITAE_C1(FDLOG *elog, float prd);


//! \brief     		Computes ITAE performance index from a log of servo error.
//! \param[in] elog	The servo error log
//! \param[in] prd	The sampling period in seconds
//! \return    		The ITAE index
//!
static inline float DCL_runITAE_C2(FDLOG *elog, float prd)
{
	float tim = 0.0f;
	float rlt = 0.0f;

	// set index pointer to buffer start
	DCL_resetLog(elog);

	// accumulate ITAE data
	while (elog->dptr <= elog->lptr)
	{
		rlt += fabs(*(elog->dptr++)) * tim;
		tim += prd;
	}
	DCL_resetLog(elog);

	return rlt;
}


//! \brief     		Computes IAE performance index from a log of servo error.
//!					Assembly function.
//! \param[in] elog	The servo error log
//! \return    		The IAE index
//!
extern float DCL_runIAE_C1(FDLOG *elog);


//! \brief     		Computes IAE performance index from a log of servo error.
//! \param[in] elog	The servo error log
//! \return    		The IAE index
//!
static inline float DCL_runIAE_C2(FDLOG *elog)
{
	float rlt = 0.0f;

	// set index pointer to buffer start
	DCL_resetLog(elog);

	// accumulate IAE data
	while (elog->dptr <= elog->lptr)
	{
		rlt += fabs(*(elog->dptr++));
	}
	DCL_resetLog(elog);

	return rlt;
}


//! \brief     		Computes IES performance index from a log of servo error.
//!					Assembly function.
//! \param[in] elog	The servo error log
//! \return    		The IES index
//!
extern float DCL_runIES_C1(FDLOG *elog);


//! \brief     		Computes IES performance index from a log of servo error.
//! \param[in] elog	The servo error log
//! \return    		The IES index
//!
static inline float DCL_runIES_C2(FDLOG *elog)
{
	float err;
	float rlt = 0.0f;

	// set index pointers to buffer start
	DCL_resetLog(elog);

	// accumulate IES data
	while (elog->dptr <= elog->lptr)
	{
		err = *(elog->dptr++);
		rlt += (err * err);
	}

	// restore index pointer
	DCL_resetLog(elog);

	return rlt;
}


#endif // _C_DCL_TCM_H

/* end of file */
