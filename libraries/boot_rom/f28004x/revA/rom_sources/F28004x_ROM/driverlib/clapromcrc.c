//###########################################################################
//
// FILE:   clapromcrc.c
//
// TITLE:  C28x CLAPROMCRC driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "clapromcrc.h"

//*****************************************************************************
//
// CLAPROMCRC_registerInterrupt
//
//*****************************************************************************
void
CLAPROMCRC_registerInterrupt(uint32_t base, void (*handler)(void))
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // Register the interrupt handler.
    //
    Interrupt_register(INT_CLA1PROMCRC, handler);

    //
    // Enable the CLAPROMCRC interrupt.
    //
    Interrupt_enable(INT_CLA1PROMCRC);
}

//*****************************************************************************
//
// CLAPROMCRC_unregisterInterrupt
//
//*****************************************************************************
void
CLAPROMCRC_unregisterInterrupt(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // Disable the CLAPROMCRC interrupt.
    //
    Interrupt_disable(INT_CLA1PROMCRC);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(INT_CLA1PROMCRC);
}
