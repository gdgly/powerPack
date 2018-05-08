//###########################################################################
//
// FILE:   epwm.c
//
// TITLE:  C28x EPWM driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "epwm.h"

//*****************************************************************************
//
// EPWM_setEmulationMode
//
//*****************************************************************************
void EPWM_setEmulationMode(uint32_t base, EPWM_EmulationMode emulationMode)
{
    ASSERT(EPWM_isBaseValid(base));
    // write to FREE_SOFT bits
    HWREGH(base + EPWM_O_TBCTL) =
           ((HWREGH(base + EPWM_O_TBCTL) & (~EPWM_TBCTL_FREE_SOFT_M)) |
            ((uint16_t)emulationMode << EPWM_TBCTL_FREE_SOFT_S));
}

//*****************************************************************************
//
//! Gets the ePWM interrupt number.
//!
//! \param base is the base address of the EPWM module.
//!
//! Given an ePWM base address, this function returns the corresponding
//! interrupt number.
//!
//! \return Returns an ePWM interrupt number, or 0 if \e base is invalid.
//
//*****************************************************************************
static uint32_t EPWM_getIntNumber(uint32_t base)
{
    uint32_t intNumber;

    ASSERT(EPWM_isBaseValid(base));

    switch(base)
    {
        case EPWM1_BASE:
             intNumber = INT_EPWM1;
        break;

        case EPWM2_BASE:
            intNumber = INT_EPWM2;
        break;

        case EPWM3_BASE:
            intNumber = INT_EPWM3;
        break;

        case EPWM4_BASE:
            intNumber = INT_EPWM4;
        break;

        case EPWM5_BASE:
            intNumber = INT_EPWM5;
        break;

        case EPWM6_BASE:
            intNumber = INT_EPWM6;
        break;

        case EPWM7_BASE:
            intNumber = INT_EPWM7;
        break;

        case EPWM8_BASE:
            intNumber = INT_EPWM8;
        break;


        default:
            intNumber = 0U;
        break;
    }

    return(intNumber);
}

//*****************************************************************************
//
//! Gets the Trip Zone interrupt number.
//!
//! \param base is the base address of the EPWM module.
//!
//! Given an ePWM base address, this function returns the corresponding
//! Trip Zone interrupt number.
//!
//! \return Returns Trip Zone interrupt number, or 0 if \e base is invalid.
//
//*****************************************************************************
static uint32_t EPWM_getTripZoneIntNumber(uint32_t base)
{
    uint32_t intNumber;

    ASSERT(EPWM_isBaseValid(base));

    switch(base)
    {
        case EPWM1_BASE:
            intNumber = INT_EPWM1_TZ;
        break;

        case EPWM2_BASE:
            intNumber = INT_EPWM2_TZ;
        break;

        case EPWM3_BASE:
            intNumber = INT_EPWM3_TZ;
        break;

        case EPWM4_BASE:
            intNumber = INT_EPWM4_TZ;
        break;

        case EPWM5_BASE:
            intNumber = INT_EPWM5_TZ;
        break;

        case EPWM6_BASE:
            intNumber = INT_EPWM6_TZ;
        break;

        case EPWM7_BASE:
            intNumber = INT_EPWM7_TZ;
        break;

        case EPWM8_BASE:
            intNumber = INT_EPWM8_TZ;
        break;


        default:
            intNumber = 0U;
        break;
    }

    return(intNumber);
}

//*****************************************************************************
//
// EPWM_registerInterrupt
//
//*****************************************************************************
void EPWM_registerInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNumber;

    ASSERT(EPWM_isBaseValid(base));

    intNumber = EPWM_getIntNumber(base);

    ASSERT(intNumber != 0U);

    // Register the interrupt handler.
    Interrupt_register(intNumber, handler);

    // Enable the ePWM interrupt.
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// EPWM_registerTripZoneInterrupt
//
//*****************************************************************************
void EPWM_registerTripZoneInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNumber;

    ASSERT(EPWM_isBaseValid(base));

    intNumber = EPWM_getTripZoneIntNumber(base);

    ASSERT(intNumber != 0U);

    // Register the interrupt handler.
    Interrupt_register(intNumber, handler);

    // Enable the Trip Zone interrupt.
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// EPWM_unregisterInterrupt
//
//*****************************************************************************
void EPWM_unregisterInterrupt(uint32_t base)
{
    uint32_t intNumber;

    ASSERT(EPWM_isBaseValid(base));
    // Determine the interrupt number based on the ePWM port.
    intNumber = EPWM_getIntNumber(base);

    ASSERT(intNumber != 0U);
    // Disable the ePWM interrupt.
    Interrupt_disable(intNumber);

    // Register the interrupt handler.
    Interrupt_unregister(intNumber);
}

//*****************************************************************************
//
// EPWM_unregisterTripZoneInterrupt
//
//*****************************************************************************
void EPWM_unregisterTripZoneInterrupt(uint32_t base)
{
    uint32_t intNumber;

    ASSERT(EPWM_isBaseValid(base));
    // Determine the interrupt number based on the ePWM port.
    intNumber = EPWM_getTripZoneIntNumber(base);

    ASSERT(intNumber != 0U);
    // Disable the Trip Zone  interrupt.
    Interrupt_disable(intNumber);

    // Register the interrupt handler.
    Interrupt_unregister(intNumber);
}
