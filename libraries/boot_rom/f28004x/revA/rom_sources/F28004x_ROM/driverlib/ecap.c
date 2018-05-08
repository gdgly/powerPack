//###########################################################################
//
// FILE:   ecap_t1.c
//
// TITLE: C28x ECAP driver
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "ecap.h"

//*****************************************************************************
//
// ECAP_setEmulationMode
//
//*****************************************************************************
void ECAP_setEmulationMode(uint32_t base, ECAP_EmulationMode mode)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // write to FREE/SOFT bit
    HWREGH(base + ECAP_O_ECCTL1) =
            ((HWREGH(base + ECAP_O_ECCTL1) & (~ECAP_ECCTL1_FREE_SOFT_M)) |
             ((uint16_t)mode << ECAP_ECCTL1_FREE_SOFT_S));
    EDIS;
}

//*****************************************************************************
//
//! \internal
//! Gets the eCAP interrupt number.
//!
//! \param base is the base address of the eCAP instance used.
//!
//! Given an eCAP base address, this function returns the corresponding
//! interrupt number.
//!
//! \return Returns an eCAP interrupt number, or 0 if \e base is invalid.
//
//*****************************************************************************
static uint32_t ECAP_getIntNumber(uint32_t base)
{
    uint32_t intNumber;

    ASSERT(ECAP_isBaseValid( base));


    switch(base)
    {
        case ECAP1_BASE:
            intNumber = INT_ECAP1;
        break;

        case ECAP2_BASE:
            intNumber = INT_ECAP2;
        break;

        case ECAP3_BASE:
            intNumber = INT_ECAP3;
        break;

        case ECAP4_BASE:
            intNumber = INT_ECAP4;
        break;

        case ECAP5_BASE:
            intNumber = INT_ECAP5;
        break;

        case ECAP6_BASE:
            intNumber = INT_ECAP6;
        break;

        case ECAP7_BASE:
            intNumber = INT_ECAP7;
        break;

        default:
            intNumber = 0U;
        break;
    }

    return(intNumber);
}

//*****************************************************************************
//
// ECAP_registerInterrupt
//
//*****************************************************************************
void ECAP_registerInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNumber;

    ASSERT(ECAP_isBaseValid( base));


    intNumber = ECAP_getIntNumber(base);

    ASSERT(intNumber != 0U);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the eCAP interrupt.
    //
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// ECAP_unregisterInterrupt
//
//*****************************************************************************
void ECAP_unregisterInterrupt(uint32_t base)
{
    uint32_t intNumber;

    ASSERT(ECAP_isBaseValid( base));


    //
    // Determine the interrupt number based on the eCAP port.
    //
    intNumber = ECAP_getIntNumber(base);

    ASSERT(intNumber != 0U);

    //
    // Disable the eCAP interrupt.
    //
    Interrupt_disable(intNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(intNumber);
}
