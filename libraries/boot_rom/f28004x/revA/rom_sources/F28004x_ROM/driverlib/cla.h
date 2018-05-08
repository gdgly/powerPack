//###########################################################################
//
// FILE:   cla.h
//
// TITLE:  CLA Driver Implementation File
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright: $
//###########################################################################

#ifndef __CLA_H__
#define __CLA_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup cla_t2_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "cpu.h"
#include "debug.h"
#include "interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_cla.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"

//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
#define CLA_NUM_EOT_INTERRUPTS          8U

//*****************************************************************************
//
// Values that can be passed to CLA_getBackgroundTaskStatus() as the stsFlag
// parameter.
//
//*****************************************************************************
typedef enum
{
    //! Run status
    CLA_BGSTS_RUNNING          = CLA_MSTSBGRND_RUN,    
    //! Can BG task be interrupted?
    CLA_BGSTS_CANNOT_INTERRUPT = CLA_MSTSBGRND_BGINTM, 
    //! BG task hardware trigger overflow - if a second trigger occurs
    //! while the BG is already running, the overflow is set
    CLA_BGSTS_OVERFLOW         = CLA_MSTSBGRND_BGOVF   
} CLA_BGTaskStatus;

//*****************************************************************************
//
// Values that can be passed to CLA_clearTaskFlags(), CLA_forceTasks(),
// and CLA_enableTasks(), CLA_disableTasks(), and CLA_enableSoftwareInterrupt()
// as the taskFlags parameter.
//
//*****************************************************************************
#define CLA_TASKFLAG_1          0x01U
#define CLA_TASKFLAG_2          0x02U
#define CLA_TASKFLAG_3          0x04U
#define CLA_TASKFLAG_4          0x08U
#define CLA_TASKFLAG_5          0x10U
#define CLA_TASKFLAG_6          0x20U
#define CLA_TASKFLAG_7          0x40U
#define CLA_TASKFLAG_8          0x80U
#define CLA_TASKFLAG_ALL        0xFFU

//*****************************************************************************
//
// Values that can be passed to CLA_getPendingTaskFlag(), 
// CLA_getTaskOverflowFlag(), CLA_getTaskRunStatus(), CLA_setTriggerSource(),
// CLA_registerEndOfTaskInterrupt(), and CLA_unregisterEndOfTaskInterrupt()
// as the taskNumber parameter.
//
//*****************************************************************************
typedef enum
{
    CLA_TASK_1,
    CLA_TASK_2,
    CLA_TASK_3,
    CLA_TASK_4,
    CLA_TASK_5,
    CLA_TASK_6,
    CLA_TASK_7,
    CLA_TASK_8
} CLA_TaskNumber;

//*****************************************************************************
//
// Values that can be passed to CLA_mapTaskVector() as the claIntVect
// parameter.
//
//*****************************************************************************
typedef enum
{
    CLA_MVECT_1 = CLA_O_MVECT1,     // Task Interrupt Vector 1
    CLA_MVECT_2 = CLA_O_MVECT2,     // Task Interrupt Vector 2
    CLA_MVECT_3 = CLA_O_MVECT3,     // Task Interrupt Vector 3
    CLA_MVECT_4 = CLA_O_MVECT4,     // Task Interrupt Vector 4
    CLA_MVECT_5 = CLA_O_MVECT5,     // Task Interrupt Vector 5
    CLA_MVECT_6 = CLA_O_MVECT6,     // Task Interrupt Vector 6
    CLA_MVECT_7 = CLA_O_MVECT7,     // Task Interrupt Vector 7
    CLA_MVECT_8 = CLA_O_MVECT8      // Task Interrupt Vector 8
} CLA_MVECTNumber;

//*****************************************************************************
//
// Values that can be passed to CLA_setTriggerSource() as the trigger
// parameter.
//
//*****************************************************************************
typedef enum
{
    CLA_TRIGGER_SOFTWARE    = 0U,
    CLA_TRIGGER_ADCA1       = 1U,
    CLA_TRIGGER_ADCA2       = 2U,
    CLA_TRIGGER_ADCA3       = 3U,
    CLA_TRIGGER_ADCA4       = 4U,
    CLA_TRIGGER_ADCAEVT     = 5U,
    CLA_TRIGGER_ADCB1       = 6U,
    CLA_TRIGGER_ADCB2       = 7U,
    CLA_TRIGGER_ADCB3       = 8U,
    CLA_TRIGGER_ADCB4       = 9U,
    CLA_TRIGGER_ADCBEVT     = 10U,
    CLA_TRIGGER_ADCC1       = 11U,
    CLA_TRIGGER_ADCC2       = 12U,
    CLA_TRIGGER_ADCC3       = 13U,
    CLA_TRIGGER_ADCC4       = 14U,
    CLA_TRIGGER_ADCCEVT     = 15U,

    CLA_TRIGGER_XINT1       = 29U,
    CLA_TRIGGER_XINT2       = 30U,
    CLA_TRIGGER_XINT3       = 31U,
    CLA_TRIGGER_XINT4       = 32U,
    CLA_TRIGGER_XINT5       = 33U,

    CLA_TRIGGER_EPWM1INT    = 36U,
    CLA_TRIGGER_EPWM2INT    = 37U,
    CLA_TRIGGER_EPWM3INT    = 38U,
    CLA_TRIGGER_EPWM4INT    = 39U,
    CLA_TRIGGER_EPWM5INT    = 40U,
    CLA_TRIGGER_EPWM6INT    = 41U,
    CLA_TRIGGER_EPWM7INT    = 42U,
    CLA_TRIGGER_EPWM8INT    = 43U,

    CLA_TRIGGER_TINT0       = 68U,
    CLA_TRIGGER_TINT1       = 69U,
    CLA_TRIGGER_TINT2       = 70U,

    CLA_TRIGGER_ECAP1INT    = 75U,
    CLA_TRIGGER_ECAP2INT    = 76U,
    CLA_TRIGGER_ECAP3INT    = 77U,
    CLA_TRIGGER_ECAP4INT    = 78U,
    CLA_TRIGGER_ECAP5INT    = 79U,
    CLA_TRIGGER_ECAP6INT    = 80U,
    CLA_TRIGGER_ECAP7INT    = 81U,

    CLA_TRIGGER_EQEP1INT    = 83U,
    CLA_TRIGGER_EQEP2INT    = 84U,

    CLA_TRIGGER_ECAP6INT2   = 92U,
    CLA_TRIGGER_ECAP7INT2   = 93U,

    CLA_TRIGGER_SDFM1INT    = 95U,
    CLA_TRIGGER_SDFM1DRINT1 = 96U,
    CLA_TRIGGER_SDFM1DRINT2 = 97U,
    CLA_TRIGGER_SDFM1DRINT3 = 98U,
    CLA_TRIGGER_SDFM1DRINT4 = 99U,

    CLA_TRIGGER_PMBUSAINT   = 105U,

    CLA_TRIGGER_SPITXINTA   = 109U,
    CLA_TRIGGER_SPIRXINTA   = 110U,
    CLA_TRIGGER_SPITXINTB   = 111U,
    CLA_TRIGGER_SPIRXINTB   = 112U,

    CLA_TRIGGER_LINA_INT1   = 117U,
    CLA_TRIGGER_LINA_INT0   = 118U,

    CLA_TRIGGER_CLA1PROMCRC = 121U,

    CLA_TRIGGER_FSITX_INT1  = 123U,
    CLA_TRIGGER_FSITX_INT2  = 124U,
    CLA_TRIGGER_FSIRX_INT1  = 125U,
    CLA_TRIGGER_FSIRX_INT2  = 126U,

    CLA_TRIGGER_CLB1INT     = 127U,
    CLA_TRIGGER_CLB2INT     = 128U,
    CLA_TRIGGER_CLB3INT     = 129U,
    CLA_TRIGGER_CLB4INT     = 130U
} CLA_Trigger;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks a CLA base address.
//!
//! \param base is the base address of the CLA controller.
//!
//! This function determines if a CLA controller base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
CLA_isBaseValid(uint32_t base)
{
    return(base == CLA1_BASE);
}
#endif

#ifdef __TMS320C28XX__ // These functions are only accessible from the C28x
//*****************************************************************************
//
//! Map CLA Task Interrupt Vector
//!
//! \param base is the base address of the CLA controller.
//! \param claIntVect is CLA interrupt vector (MVECT1 to MVECT8)
//! the value of claIntVect can be any of the following:
//! - CLA_MVECT_1 - Task Interrupt Vector 1
//! - CLA_MVECT_2 - Task Interrupt Vector 2
//! - CLA_MVECT_3 - Task Interrupt Vector 3
//! - CLA_MVECT_4 - Task Interrupt Vector 4
//! - CLA_MVECT_5 - Task Interrupt Vector 5
//! - CLA_MVECT_6 - Task Interrupt Vector 6
//! - CLA_MVECT_7 - Task Interrupt Vector 7
//! - CLA_MVECT_8 - Task Interrupt Vector 8
//! \param claTaskAddr is the start address of the code for task
//!
//! Each CLA Task (1 to 8) has its own MVECTx register. When a task is 
//! triggered, the CLA loads the MVECTx register of the task in question
//! to the MPC (CLA program counter) and begins execution from that point.
//! The CLA has a 16-bit address bus, and can therefore, access the lower
//! 64 KW space. The MVECTx registers take an address anywhere in this space.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_mapTaskVector(uint32_t base, CLA_MVECTNumber claIntVect,
                  uint16_t claTaskAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    HWREGH(base + claIntVect) = claTaskAddr;

    EDIS;
}
                            
//*****************************************************************************
//
//! Hard Reset
//!
//! \param base is the base address of the CLA controller.
//!
//! This function will cause a hard reset of the CLA and set all CLA registers
//! to their default state.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_performHardReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Hard reset of the CLA
    //
    HWREGH(base + CLA_O_MCTL) |= CLA_MCTL_HARDRESET;

    EDIS;
}

//*****************************************************************************
//
//! Soft Reset
//!
//! \param base is the base address of the CLA controller.
//!
//! This function will cause a soft reset of the CLA. This will stop the
//! current task, clear the MIRUN flag and clear all bits in the MIER register.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_performSoftReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Soft reset of the CLA
    //
    HWREGH(base + CLA_O_MCTL) |= CLA_MCTL_SOFTRESET;

    EDIS;
}

//*****************************************************************************
//
//! IACK enable
//!
//! \param base is the base address of the CLA controller.
//!
//! This function enables the main CPU to use the IACK #16bit instruction to
//! set MIFR bits in the same manner as writing to the MIFRC register.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_enableIACK(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Enable the main CPU to use the IACK #16bit instruction
    //
    HWREGH(base + CLA_O_MCTL) |= CLA_MCTL_IACKE;

    EDIS;
}

//*****************************************************************************
//
//! IACK disable
//!
//! \param base is the base address of the CLA controller.
//!
//! This function disables the main CPU to use the IACK #16bit instruction to
//! set MIFR bits in the same manner as writing to the MIFRC register.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_disableIACK(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Enable the main CPU to use the IACK #16bit instruction
    //
    HWREGH(base + CLA_O_MCTL) &= ~CLA_MCTL_IACKE;

    EDIS;
}

//*****************************************************************************
//
//! Query task N to see if it is flagged and pending execution
//!
//! \param base is the base address of the CLA controller.
//! \param taskNumber is the number of the task CLA_TASK_N where N is a number
//! from 1 to 8. Do not use CLA_TASKFLAG_ALL.
//!
//! This function gets the status of each bit in the interrupt flag register
//! corresponds to a CLA task.  The corresponding bit is automatically set
//! when the task is triggered (either from a peripheral, through software, or
//! through the MIFRC register). The bit gets cleared when the CLA starts to 
//! execute the flagged task.
//!
//! \return \b True if the queried task has been triggered but pending
//! execution.
//
//*****************************************************************************
static inline bool 
CLA_getPendingTaskFlag(uint32_t base, CLA_TaskNumber taskNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Read the run status register and return the appropriate value.
    //
    if((HWREGH(base + CLA_O_MIFR) >> taskNumber & 1U) != 0U)
    {
        return(true);
    }
    else
    {
        return(false);
    };
}

//*****************************************************************************
//
//! Get status of All Task Interrupt Flag
//!
//! \param base is the base address of the CLA controller.
//!
//! This function gets the value of the interrupt flag register (MIFR)
//!
//! \return the value of Interrupt Flag Register (MIFR)
//
//*****************************************************************************
static inline uint16_t 
CLA_getAllPendingTaskFlags(uint32_t base)
{
    uint16_t status;

    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Just return the Interrupt Flag Register (MIFR) since that is what was
    // requested.
    //
    status = HWREGH(base + CLA_O_MIFR);

    //
    // Return the Interrupt Flag Register value
    //
    return(status);
}

//*****************************************************************************
//
//! Get status of Task n Interrupt Overflow Flag
//!
//! \param base is the base address of the CLA controller.
//! \param taskNumber is the number of the task CLA_TASK_N where N is a number
//! from 1 to 8. Do not use CLA_TASKFLAG_ALL.
//!
//! This function gets the status of each bit in the overflow flag register
//! corresponds to a CLA task, This bit is set when an interrupt overflow event
//! has occurred for the specific task.
//!
//! \return True if any of task interrupt overflow has occurred.
//
//*****************************************************************************
static inline bool 
CLA_getTaskOverflowFlag(uint32_t base, CLA_TaskNumber taskNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Read the run status register and return the appropriate value.
    //
    if((HWREGH(base + CLA_O_MIOVF) >> taskNumber & 1U) != 0U)
    {
        return(true);
    }
    else
    {
        return(false);
    };
}

//*****************************************************************************
//
//! Get status of All Task Interrupt Overflow Flag
//!
//! \param base is the base address of the CLA controller.
//!
//! This function gets the value of the Interrupt Overflow Flag Register
//!
//! \return the value of Interrupt Overflow Flag Register(MIOVF)
//
//*****************************************************************************
static inline uint16_t 
CLA_getAllTaskOverflowFlags(uint32_t base)
{
    uint16_t status;

    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Just return Interrupt Overflow Flag Register(MIOVF) since that is what 
    // was requested.
    //
    status = HWREGH(base + CLA_O_MIOVF);

    //
    // Return the Interrupt Overflow Flag Register
    //
    return(status);
}

//*****************************************************************************
//
//! Clear the task interrupt flag
//!
//! \param base is the base address of the CLA controller.
//! \param taskFlags is the logical OR of the tasks' flags to be cleared
//! CLA_TASKFLAG_N where N is the task number from 1 to 8, or CLA_TASKFLAG_ALL
//! to clear all flags.
//!
//! This function is used to instead manually clear bits in the interrupt
//! flag (MIFR) register
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_clearTaskFlags(uint32_t base, uint16_t taskFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    //Modify protected register
    //
    EALLOW;

    //
    // Clear the task interrupt flag
    //
    HWREGH(base + CLA_O_MICLR) |= taskFlags;

    EDIS;
}

//*****************************************************************************
//
//! Force a CLA Task
//!
//! \param base is the base address of the CLA controller.
//! \param taskFlags is the logical OR of the tasks' flags to be forced
//! CLA_TASKFLAG_N where N is the task number from 1 to 8, or CLA_TASKFLAG_ALL
//! to force all tasks.
//!
//! This function forces a task through software.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_forceTasks(uint32_t base, uint16_t taskFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Force the task interrupt.
    //
    HWREGH(base + CLA_O_MIFRC) |= taskFlags;

    EDIS;
}

//*****************************************************************************
//
//! Enable CLA task(s)
//!
//! \param base is the base address of the CLA controller.
//! \param taskFlags is the logical OR of the tasks' flags to be enabled
//! CLA_TASKFLAG_N where N is the task number from 1 to 8, or CLA_TASKFLAG_ALL
//! to enable all tasks
//!
//! This function allows an incoming interrupt or main CPU software to
//! start the corresponding CLA task.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_enableTasks(uint32_t base, uint16_t taskFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Enable CLA task
    //
    HWREGH(base + CLA_O_MIER) |= taskFlags;

    EDIS;
}

//*****************************************************************************
//
//! Disable CLA task interrupt
//!
//! \param base is the base address of the CLA controller.
//! \param taskFlags is the logical OR of the tasks' flags to be disabled
//! CLA_TASKFLAG_N where N is the task number from 1 to 8, or CLA_TASKFLAG_ALL
//! to disable all tasks
//!
//! This function disables CLA task interrupt by setting the MIER register bit
//! to 0, while the corresponding task is executing this will have no effect 
//! on the task. The task will continue to run until it hits the MSTOP 
//! instruction.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_disableTasks(uint32_t base, uint16_t taskFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Disable CLA task interrupt
    //
    HWREGH(base + CLA_O_MIER) &= ~taskFlags;

    EDIS;
}

//*****************************************************************************
//
//! Get the value of task n run status
//!
//! \param base is the base address of the CLA controller.
//! \param taskNumber is the number of the task CLA_TASK_N where N is a number
//! from 1 to 8. Do not use CLA_TASKFLAG_ALL.
//!
//! This function gets the status of each bit in the Interrupt Run Status 
//! Register which indicates whether the task is currently executing
//!
//! \return True if any of task is executing.
//
//*****************************************************************************
static inline bool 
CLA_getTaskRunStatus(uint32_t base, CLA_TaskNumber taskNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Read the run status register and return the appropriate value.
    //
    if((HWREGH(base + CLA_O_MIRUN) >> taskNumber & 1U) != 0U)
    {
        return(true);
    }
    else
    {
        return(false);
    };
}

//*****************************************************************************
//
//! Get the value of all task run status
//!
//! \param base is the base address of the CLA controller.
//!
//! This function indicates which task is currently executing.
//!
//! \return the value of Interrupt Run Status Register (MIRUN)
//
//*****************************************************************************
static inline uint16_t 
CLA_getAllTaskRunStatus(uint32_t base)
{
    uint16_t status;

    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Just return the Interrupt Run Status Register since that is what was
    // requested.
    //
    status = HWREGH(base + CLA_O_MIRUN);

    //
    // Return the Interrupt Run Status Register (MIRUN)
    //
    return(status);
}

//*****************************************************************************
//
//! Get the value of Active register for MVECTBGRNDACTIVE
//!
//! \param base is the base address of the CLA controller.
//!
//! This function gives the current interrupted MPC value of the background 
//! task.
//!
//! \return the value of Active register for the Background Task Vector
//
//*****************************************************************************
static inline uint16_t 
CLA_getBackgroundActiveVector(uint32_t base)
{
    uint16_t status;

    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Just return the Active register for the Background Task Vector since
    // that is what was requested.
    //
    status = HWREGH(base + CLA_O_MVECTBGRNDACTIVE);

    //
    // Return the value of Active register for the Background Task Vector
    //
    return(status);
}

//*****************************************************************************
//
//! Enable the background task
//!
//! \param base is the base address of the CLA controller.
//!
//! This function enables the background task
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_enableBackgroundTask(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Enable background task
    //
    HWREG(base + CLA_O_MCTLBGRND) |= CLA_MCTLBGRND_BGEN;

    EDIS;
}

//*****************************************************************************
//
//! Disable background task
//!
//! \param base is the base address of the CLA controller.
//!
//! This function disables background task
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_disableBackgroundTask(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Disables background task
    //
    HWREG(base + CLA_O_MCTLBGRND) &= ~CLA_MCTLBGRND_BGEN;

    EDIS;
}

//*****************************************************************************
//
//! Start background task
//!
//! \param base is the base address of the CLA controller.
//!
//! This function will start the background task, provided there are no other
//! pending tasks.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_startBackgroundTask(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Start background task
    //
    HWREG(base + CLA_O_MCTLBGRND) |= CLA_MCTLBGRND_BGSTART;

    EDIS;
}

//*****************************************************************************
//
//! Enable background task hardware trigger
//!
//! \param base is the base address of the CLA controller.
//!
//! This function enables hardware trigger for background task
//! \note Trigger source for the background task will be MPERINT8.1.
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_enableHardwareTrigger(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Enable background task hardware trigger
    //
    HWREG(base + CLA_O_MCTLBGRND) |= CLA_MCTLBGRND_TRIGEN;

    EDIS;
}

//*****************************************************************************
//
//! Disable background task hardware trigger
//!
//! \param base is the base address of the CLA controller.
//!
//! This function disables hardware trigger for background task
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_disableHardwareTrigger(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    //
    // Disables hardware trigger for background task
    //
    HWREG(base + CLA_O_MCTLBGRND) &= ~CLA_MCTLBGRND_TRIGEN;

    EDIS;
}

//*****************************************************************************
//
//! Map background task vector
//!
//! \param base is the base address of the CLA controller.
//! \param claTaskAddr is the start address of the code for task
//!
//! This function specifies the start address for the background task
//!
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_mapBackgroundTaskVector(uint32_t base, uint16_t claTaskAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    EALLOW;

    HWREGH(base + CLA_O_MVECTBGRND) = (uint16_t)claTaskAddr;

    EDIS;
}
#endif // #ifdef __TMS320C28XX__

 // These functions are accessible only from the CLA (Type - 1/2)
#if defined(__TMS320C28XX_CLA1__) || defined(__TMS320C28XX_CLA2__)
//*****************************************************************************
//
//! Enable the Software Interrupt for a given CLA Task
//!
//! \param base is the base address of the CLA controller.
//! \param taskFlags is the logical OR of the task's for which software
//! interrupts are to be enabled, CLA_TASKFLAG_N where N is the task number 
//! from 1 to 8, or CLA_TASKFLAG_ALL to enable software interrupts of all tasks
//!
//! This function enables the  Software Interrupt for a single, or set of, CLA 
//! task(s). It does this by writing a 1 to the task's bit in the 
//! CLA1SOFTINTEN register. By setting a task's SOFTINT bit, you disable its
//! ability to generate an end-of-task interrupt
//! For example, if we enable Task 2's SOFTINT bit, we disable its ability to
//! generate an end-of-task interrupt, but now any running CLA task has the 
//! ability to force task 2's interrupt (through the CLA1INTFRC register) to 
//! the main CPU. This interrupt will be handled by the End-of-Task 2 interrupt
//! handler even though the interrupt was not caused by Task 2 running to 
//! completion. This allows programmers to generate interrupts while a control 
//! task is running.
//! 
//! \note The CLA1SOFTINTEN and CLA1INTFRC are only writable from the CLA
//! \note Enabling a given task's software interrupt enable bit disables that 
//! task's ability to generate an End-of-Task interrupt to the main CPU, 
//! however, should another task force its interrupt (through the CLA1INTFRC
//! register), it will be handled by that task's End-of-Task Interrupt Handler
//! 
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_enableSoftwareInterrupt(uint32_t base, uint16_t taskFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    __meallow();

    //
    // Enable Software Interrupt
    //
    HWREGH(base + CLA_O_SOFTINTEN) |= taskFlags;

    __medis();
}

//*****************************************************************************
//
//! Disable the Software Interrupt for a given CLA Task
//!
//! \param base is the base address of the CLA controller.
//! \param taskFlags is the logical OR of the task's for which software
//! interrupts are to be disabled, CLA_TASKFLAG_N where N is the task number 
//! from 1 to 8, or CLA_TASKFLAG_ALL to disable software interrupts of all 
//! tasks
//!
//! \note The CLA1SOFTINTEN and CLA1INTFRC are only writable from the CLA
//! \note Disabling a given task's software interrupt ability allows that 
//! task to generate an End-of-Task interrupt to the main CPU
//! 
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_disableSoftwareInterrupt(uint32_t base, uint16_t taskFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    __meallow();

    //
    // Enable Software Interrupt
    //
    HWREGH(base + CLA_O_SOFTINTEN) &=  ~taskFlags;

    __medis();
}
//*****************************************************************************
//
//! Force a particular Task's Software Interrupt
//!
//! \param base is the base address of the CLA controller.
//! \param taskFlags is the logical OR of the task's whose software
//! interrupts are to be forced, CLA_TASKFLAG_N where N is the task number 
//! from 1 to 8, or CLA_TASKFLAG_ALL to force software interrupts for all tasks
//!
//! This function forces the  Software Interrupt for a single, or set of, CLA 
//! task(s). It does this by writing a 1 to the task's bit in the 
//! CLA1INTFRC register. 
//! For example, if we enable Task 2's SOFTINT bit, we disable its ability to
//! generate an end-of-task interrupt, but now any running CLA task has the 
//! ability to force task 2's interrupt (through the CLA1INTFRC register) to 
//! the main CPU. This interrupt will be handled by the End-of-Task 2 interrupt
//! handler even though the interrupt was not caused by Task 2 running to 
//! completion. This allows programmers to generate interrupts while a control 
//! task is running.
//! 
//! \note The CLA1SOFTINTEN and CLA1INTFRC are only writable from the CLA
//! \note Enabling a given task's software interrupt enable bit disables that 
//! task's ability to generate an End-of-Task interrupt to the main CPU, 
//! however, should another task force its interrupt (through the CLA1INTFRC
//! register), it will be handled by that task's End-of-Task Interrupt Handler
//! \note This function will set the INTFRC bit for a task, but does not check
//! that its SOFTINT bit is set. It falls to the user to ensure that software
//! interrupt for a given task is enabled before it can be forced
//! 
//! \return None.
//
//*****************************************************************************
static inline void 
CLA_forceSoftwareInterrupt(uint32_t base, uint16_t taskFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Modify protected register
    //
    __meallow();

    //
    // Force Software Interrupt
    //
    HWREGH(base + CLA_O_SOFTINTFRC) |= taskFlags;

    __medis();
}

#endif // #if defined(__TMS320C28XX_CLA1__) || defined(__TMS320C28XX_CLA2__)

// These functions can only be called from the C28x
#ifdef __TMS320C28XX__
//*****************************************************************************
//
//! Registers an End-of-Task interrupt handler
//!
//! \param base is the base address of the CLA controller.
//! \param taskNumber is the the logical OR of the task CLA_TASK_N where N is 
//! a number from 1 to 8.
//! \param handler is a pointer to the function to be called when the
//! CLA End-of-Taskn (n = 1 to 8) interrupt occurs.
//!
//! Each CLA Task can trigger an interrupt to the ePIE when it completes 
//! execution. This function registers the handler to be called when an 
//! CLA End-of-Task interrupt occurs.  This function enables the global 
//! interrupt in the interrupt controller for a particular task, 
//! CLA_TASK_N (N = 1 to 8)
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
CLA_registerEndOfTaskInterrupt(uint32_t base, CLA_TaskNumber taskNumber, 
                               void (*handler)(void));

//*****************************************************************************
//
//! Unregisters an End-of-Task interrupt handler
//!
//! \param base is the base address of the CLA controller.
//! \param taskNumber is the the logical OR of the task CLA_TASK_N where N is 
//! a number from 1 to 8.
//!
//! This function clears the handler of the CLA End-of-Taskn (n = 1 to 8) 
//! interrupt.  This function also masks off the interrupt in the interrupt
//! controller so that the interrupt handler is no longer called.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
CLA_unregisterEndOfTaskInterrupt(uint32_t base, CLA_TaskNumber taskNumber);

//*****************************************************************************
//
//! Registers an Overflow (Math) interrupt handler
//!
//! \param base is the base address of the CLA controller.
//! \param handler is a pointer to the function to be called when the
//! CLA LUF (Overflow from a Math Operation) interrupt occurs.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
CLA_registerLUFInterrupt(uint32_t base, void (*handler)(void));

//*****************************************************************************
//
//! Unregisters an Overflow (Math) interrupt handler
//!
//! \param base is the base address of the CLA controller.
//!
//! This function clears the handler of the CLA LUF interrupt. This function 
//! also masks off the interrupt in the interrupt controller so that the 
//! interrupt handler is no longer called.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
CLA_unregisterLUFInterrupt(uint32_t base);

//*****************************************************************************
//
//! Registers an Underflow (Math) interrupt handler
//!
//! \param base is the base address of the CLA controller.
//! \param handler is a pointer to the function to be called when the
//! CLA LVF (Underflow from a Math Operation) interrupt occurs.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
CLA_registerLVFInterrupt(uint32_t base, void (*handler)(void));

//*****************************************************************************
//
//! Unregisters an Underflow (Math) interrupt handler
//!
//! \param base is the base address of the CLA controller.
//!
//! This function clears the handler of the CLA LVF interrupt. This function 
//! also masks off the interrupt in the interrupt controller so that the 
//! interrupt handler is no longer called.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
CLA_unregisterLVFInterrupt(uint32_t base);

//*****************************************************************************
//
//! Get Status register for the back ground task.
//!
//! \param base is the base address of the CLA controller.
//! \param stsFlag is status item to be returned.
//!
//! The value of \e stsFlag can be any of the following:
//! - \b CLA_BGSTS_RUNNING
//! - \b CLA_BGSTS_CANNOT_INTERRUPT
//! - \b CLA_BGSTS_OVERFLOW
//!
//! This function gets the status of background task
//!
//! \return Based on the value of \e stsFlag, the function will return:
//! - \b CLA_BGSTS_RUNNING - The function will return \b true if the background
//!   task is running.
//! - \b CLA_BGSTS_CANNOT_INTERRUPT - The function will return \b true if the
//!   background task will not be interrupted (when MSETC BGINTM is executed).
//! - \b CLA_BGSTS_OVERFLOW - This function will return \b true if an enabled
//!   hardware trigger occurred while _MCTLBGRND.BGSTART is set.
//
//*****************************************************************************
extern bool 
CLA_getBackgroundTaskStatus(uint32_t base, CLA_BGTaskStatus stsFlag);

//*****************************************************************************
//
//! Configures CLA task triggers.
//!
//! \param taskNumber is the number of the task CLA_TASK_N where N is a number
//! from 1 to 8.
//! \param trigger is the trigger source to be assigned to the selected task.
//!
//! This function configures the trigger source of a CLA task. The
//! \e taskNumber parameter indicates which task is being configured, and the
//! \e trigger parameter is the interrupt source from a specific peripheral
//! interrupt (or software) that will trigger the task.
//!
//! \return None.
//
//*****************************************************************************
extern void 
CLA_setTriggerSource(CLA_TaskNumber taskNumber, CLA_Trigger trigger);

#endif //#ifdef __TMS320C28XX__
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************                                 
                                 
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __CLA_H__
