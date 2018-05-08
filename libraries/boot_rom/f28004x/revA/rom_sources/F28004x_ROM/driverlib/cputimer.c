//#############################################################################
//
// FILE:   cputimer.c
//
// TITLE:  C28x CPU timer Driver
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//#############################################################################

#include "cputimer.h"

//*****************************************************************************
//
// CPUTimer_setEmulationMode
//
//*****************************************************************************
void CPUTimer_setEmulationMode(uint32_t base, CPUTimer_EmulationMode mode)
{
    ASSERT(CPUTimer_isBaseValid(base));
    // Write to FREE_SOFT bits of register TCR
    HWREGH(base + CPUTIMER_O_TCR) =
            (HWREGH(base + CPUTIMER_O_TCR) & 
 			~(CPUTIMER_TCR_FREE | CPUTIMER_TCR_SOFT)) | 
			(uint16_t)mode;
}

//*****************************************************************************
//
//! Gets the CPU timer interrupt number.
//!
//! \param base is the base address of the timer module.
//!
//! Given a CPU timer base address, this function returns the corresponding
//! interrupt number.
//!
//! \return Returns a CPU timer interrupt number, or 0 if \e base is invalid.
//
//*****************************************************************************
static uint32_t CPUTimer_getIntNumber(uint32_t base)
{
    uint32_t intNumber;

    ASSERT(CPUTimer_isBaseValid(base));

    switch(base)
    {
        case CPUTIMER0_BASE:
            intNumber = INT_TIMER0;
        break;

        case CPUTIMER1_BASE:
            intNumber = INT_TIMER1;
        break;

        case CPUTIMER2_BASE:
            intNumber = INT_TIMER2;
        break;

        default:
            intNumber = 0U;
        break;
    }

    return(intNumber);
}

//*****************************************************************************
//
// CPUTimer_registerInterrupt
//
//*****************************************************************************
void CPUTimer_registerInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(CPUTimer_isBaseValid(base));

    //
    // Determine the interrupt number based on the CPU Timer port.
    //
    intNumber = CPUTimer_getIntNumber(base);

    ASSERT(intNumber != 0U);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the CPU timer interrupt.
    //
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// CPUTimer_unregisterInterrupt
//
//*****************************************************************************
void CPUTimer_unregisterInterrupt(uint32_t base)
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(CPUTimer_isBaseValid(base));

    //
    // Determine the interrupt number based on the CPU timer port
    //
    intNumber = CPUTimer_getIntNumber(base);

    ASSERT(intNumber != 0U);

    //
    // Disable the CPU timer interrupt.
    //
    Interrupt_disable(intNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(intNumber);
}
