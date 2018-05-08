//###########################################################################
//
// FILE:   cla.c
//
// TITLE:  CLA Driver Implementation File
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright: $
//###########################################################################

#include "cla.h"
//*****************************************************************************
//
// A mapping of ADC base address to interrupt number. Not intended for use by
// application code.
//
//*****************************************************************************
static const uint32_t CLA_intMap[CLA_NUM_EOT_INTERRUPTS] =
{
    INT_CLA1_1,
    INT_CLA1_2,
    INT_CLA1_3,
    INT_CLA1_4,
    INT_CLA1_5,
    INT_CLA1_6,
    INT_CLA1_7,
    INT_CLA1_8
};

//*****************************************************************************
//
// CLA_registerEndOfTaskInterrupt()
//
//*****************************************************************************
void
CLA_registerEndOfTaskInterrupt(uint32_t base, CLA_TaskNumber taskNumber, 
                               void (*handler)(void))
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Determine the interrupt number based on the CLA Task.
    //
    intNumber = CLA_intMap[taskNumber];

    ASSERT(intNumber != 0);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the CLA End-of-Task interrupt.
    //
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// CLA_unregisterEndOfTaskInterrupt()
//
//*****************************************************************************
void
CLA_unregisterEndOfTaskInterrupt(uint32_t base, CLA_TaskNumber taskNumber)
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Determine the interrupt number based on the CLA Task.
    //
    intNumber = CLA_intMap[taskNumber];

    ASSERT(intNumber != 0);

    //
    // Disable the CLA End-of-Task  interrupt.
    //
    Interrupt_disable(intNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(intNumber); 
}

//*****************************************************************************
//
// CLA_registerLUFInterrupt()
//
//*****************************************************************************
void
CLA_registerLUFInterrupt(uint32_t base, void (*handler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Register the interrupt handler.
    //
    Interrupt_register(INT_CLA_OVERFLOW, handler);

    //
    // Enable the CLA LUF interrupt.
    //
    Interrupt_enable(INT_CLA_OVERFLOW);
}

//*****************************************************************************
//
// CLA_unregisterLUFInterrupt()
//
//*****************************************************************************
void
CLA_unregisterLUFInterrupt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Disable the CLA LUF  interrupt.
    //
    Interrupt_disable(INT_CLA_OVERFLOW);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(INT_CLA_OVERFLOW); 
}

//*****************************************************************************
//
// CLA_registerLVFInterrupt()
//
//*****************************************************************************
void
CLA_registerLVFInterrupt(uint32_t base, void (*handler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Register the interrupt handler.
    //
    Interrupt_register(INT_CLA_UNDERFLOW, handler);

    //
    // Enable the CLA LVF interrupt.
    //
    Interrupt_enable(INT_CLA_UNDERFLOW);
}

//*****************************************************************************
//
// CLA_unregisterLVFInterrupt()
//
//*****************************************************************************
void
CLA_unregisterLVFInterrupt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // Disable the CLA LVF  interrupt.
    //
    Interrupt_disable(INT_CLA_UNDERFLOW);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(INT_CLA_UNDERFLOW); 
}

//*****************************************************************************
//
// CLA_getBackgroundTaskStatus()
//
//*****************************************************************************
bool
CLA_getBackgroundTaskStatus(uint32_t base, CLA_BGTaskStatus stsFlag)
{
    bool status;

    //
    // Check the arguments.
    //
    ASSERT(CLA_isBaseValid(base));

    //
    // See which status the caller is looking for.
    //
    switch(stsFlag)
    {
        case CLA_BGSTS_RUNNING:
        {
            status = HWREGH(base + CLA_O_MSTSBGRND) & 0x1U;
            break;
        }
        case CLA_BGSTS_CANNOT_INTERRUPT:
        {
            status = ((HWREGH(base + CLA_O_MSTSBGRND) &
                       CLA_MSTSBGRND_BGINTM) >> 1U) & 0x1U;
            break;
        }
        case CLA_BGSTS_OVERFLOW:
        {
            status = ((HWREGH(base + CLA_O_MSTSBGRND) &
                       CLA_MSTSBGRND_BGOVF) >> 2U) & 0x1U;
            break;
        }
        default:
        {
            //
            // Request was for unknown status
            //
            break;
        }
    }

    //
    // Return the background task status value
    //
    return(status);
}

//*****************************************************************************
//
// CLA_setTriggerSource()
//
//*****************************************************************************
void
CLA_setTriggerSource(CLA_TaskNumber taskNumber, CLA_Trigger trigger)
{
    uint32_t srcSelReg;
    uint32_t shiftVal;

    //
    // Calculate the shift value for the specified task.
    //
    shiftVal = ((uint32_t)taskNumber * SYSCTL_CLA1TASKSRCSEL1_TASK2_S) % 32U;

    //
    // Calculate the register address for the specified task.
    //
    if(taskNumber <= CLA_TASK_4)
    {
        //
        // Tasks 1-4
        //
        srcSelReg = DMACLASRCSEL_BASE + SYSCTL_O_CLA1TASKSRCSEL1;
    }
    else
    {
        //
        // Tasks 5-8
        //
        srcSelReg = DMACLASRCSEL_BASE + SYSCTL_O_CLA1TASKSRCSEL2;
    }

    EALLOW;

    //
    // Write trigger selection to the appropriate register.
    //
    HWREG(srcSelReg) &= ~((uint32_t)SYSCTL_CLA1TASKSRCSEL1_TASK1_M << shiftVal);
    HWREG(srcSelReg) |= (uint32_t)trigger << shiftVal;

    EDIS;
}
