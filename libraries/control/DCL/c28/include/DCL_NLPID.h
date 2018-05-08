/* DCL_NLPID.h - non-linear PID controller
 *
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 *
*/

#ifndef _C_DCL_NLPID_H
#define _C_DCL_NPLID_H

//! \file   		DCL_NLPID.h
//! \brief  		Contains the public interface to the
//!         		non-linear PID controller functions
//!

#include <math.h>

//--- Non-linear PID controller -----------------------------------------------

//! \brief 			Defines the non-linear PID controller structure
//!
typedef volatile struct {
	float Kp;		//!< Linear proportional gain
	float Ki;		//!< Linear integral gain
	float Kd;		//!< Linear derivative gain
	float alpha_p;	//!< P path non-linear exponent
	float alpha_i;	//!< I path non-linear exponent
	float alpha_d;	//!< D path non-linear exponent
	float delta_p;	//!< P path linearized range
	float delta_i;	//!< I path linearized range
	float delta_d;	//!< D path linearized range
	float gamma_p;	//!< P path gain limit
	float gamma_i;	//!< I path gain limit
	float gamma_d;	//!< D path gain limit
	float c1;		//!< D path filter coefficient 1
	float c2;		//!< D path filter coefficient 2
	float d2;		//!< D path filter intermediate storage 1
	float d3;		//!< D path filter intermediate storage 2
	float i7;		//!< I path intermediate storage
	float i16;		//!< Intermediate saturation storage
	float Umax;		//!< Upper saturation limit
	float Umin;		//!< Lower saturation limit
} NLPID;

//! \brief 			Defines default values to initialise the NLPID structure
//!
#define	NLPID_DEFAULTS {  	1.0f, 0.0f, 0.0f, \
							1.0f, 1.0f, 1.0f, \
							0.1f, 0.1f, 0.1f, \
							1.0f, 1.0f, 1.0f, \
							0.0f, 0.0f, \
							0.0f, 0.0f, \
							0.0f, 0.0f, \
							1.0f, -1.0f  }

//! \brief     		Executes a non-linear PID controller on the FPU32
//! \param[in] p	Pointer to the NLPID structure
//! \param[in] rk	The controller set-point reference
//! \param[in] yk	The measured feedback value
//! \param[in] lk	External output clamp flag
//! \return    		The control effort
//!
static inline float DCL_runNLPID_C1(NLPID *p, float rk, float yk, float lk)
{
	float v1, v2, v3, v4, v5, v8, v9, v10, v12, v13, v14, v15;

	// pre-conditioning block
	v1 = rk - yk;
	v2 = (v1 < 0.0f) ? -1.0f : 1.0f;
	v3 = abs(v1);

	// proportional path
	v4 = ((v3 > p->delta_p) ? (v2 * (float) pow(v3, p->alpha_p)) : (v1 * p->gamma_p));

	// integral path
	v5 = ((v3 > p->delta_i) ? (v2 * (float) pow(v3, p->alpha_i)) : (v1 * p->gamma_i));
	v8 = (v5 * p->Kp * p->Ki * p->i16) + p->i7;
	p->i7 = v8;

	// derivative path
	v9 = ((v3 > p->delta_d) ? (v2 * (float) pow(v3, p->alpha_d)) : (v1 * p->gamma_d));
	v10 = v9 * p->Kd * p->c1;
	v12 = v10 - p->d2 - p->d3;
	p->d2 = v10;
	p->d3 = v12 * p->c2;

	// output sum & clamp
	v13 = (p->Kp * (v4 + v12)) + v8;
	v14 = (v13 > p->Umax) ? p->Umax : v13;
	v14 = (v14 < p->Umin) ? p->Umin : v14;
	v15 = (v14 == v13) ? 1.0f : 0.0f;
	p->i16 = v15 * lk;

	return v14;
}

//! \brief     		Computes the linearised gains for each path
//! \param[in] p	Pointer to the NLPID structure
//!
static inline void DCL_setGamma(NLPID *p)
{
	p->gamma_p = (float) pow(p->delta_p, (p->alpha_p - 1.0f));
	p->gamma_i = (float) pow(p->delta_i, (p->alpha_i - 1.0f));
	p->gamma_d = (float) pow(p->delta_d, (p->alpha_d - 1.0f));
}


#endif // _C_DCL_NLPID_H

/* end of file */
