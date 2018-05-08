//###########################################################################
//
// FILE:   eqep.c
//
// TITLE:  C28x eQEP driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "eqep.h"

//*****************************************************************************
//
//! \internal
//! Returns the eQEP module interrupt number.
//!
//! \param base is the base address of the selected quadrature encoder.
//!
//! This function returns the interrupt number for the quadrature encoder with
//! the base address passed in the \e base parameter.
//!
//! \return Returns a quadrature encoder interrupt number or 0 if the interrupt
//! does not exist.
//
//*****************************************************************************
static uint32_t
EQEP_getIntNumber(uint32_t base)
{
    uint32_t intNumber;

    //
    // Find the valid interrupt number for this quadrature encoder.
    //
    switch (base)
    {
        case EQEP1_BASE:
            intNumber = INT_EQEP1;
            break;

        case EQEP2_BASE:
            intNumber = INT_EQEP2;
            break;

        default:
            // Return an error.
            intNumber = 0U;
            break;
    }

    return(intNumber);
}

//*****************************************************************************
//
// EQEP_registerInterrupt
//
//*****************************************************************************
void
EQEP_registerInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Determine the interrupt number based on the eQEP module.
    //
    intNumber = EQEP_getIntNumber(base);

    ASSERT(intNumber != 0U);

    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the eQEP module interrupt.
    //
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// EQEP_unregisterInterrupt
//
//*****************************************************************************
void
EQEP_unregisterInterrupt(uint32_t base)
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Determine the interrupt number based on the eQEP module.
    //
    intNumber = EQEP_getIntNumber(base);

    ASSERT(intNumber != 0U);

    //
    // Disable the interrupt.
    //
    Interrupt_disable(intNumber);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregister(intNumber);
}

//*****************************************************************************
//
// EQEP_setCompareConfig
//
//*****************************************************************************
void
EQEP_setCompareConfig(uint32_t base, uint16_t config, uint32_t compareValue,
                      uint16_t cycles)
{
    uint16_t regValue;

    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));
    ASSERT(cycles <= (EQEP_QPOSCTL_PCSPW_M + 1U));

    //
    // Set the compare match value
    //
    HWREG(base + EQEP_O_QPOSCMP) |= compareValue;

    //
    // Set the shadow register settings and pulse width.
    //
    regValue = (config & (EQEP_QPOSCTL_PCSHDW | EQEP_QPOSCTL_PCLOAD)) |
               (cycles - 1U);

    HWREGH(base + EQEP_O_QPOSCTL) = (HWREGH(base + EQEP_O_QPOSCTL) &
                                     ~(EQEP_QPOSCTL_PCSPW_M |
                                       EQEP_QPOSCTL_PCLOAD |
                                       EQEP_QPOSCTL_PCSHDW)) | regValue;

    //
    // Set position compare sync-output mode.
    //
    regValue = config & (EQEP_QDECCTL_SOEN | EQEP_QDECCTL_SPSEL);

    HWREGH(base + EQEP_O_QDECCTL) = (HWREGH(base + EQEP_O_QDECCTL) &
                                     ~(EQEP_QDECCTL_SOEN |
                                       EQEP_QDECCTL_SPSEL)) | regValue;
}

//*****************************************************************************
//
// EQEP_setInputPolarity
//
//*****************************************************************************
void
EQEP_setInputPolarity(uint32_t base, bool invertQEPA, bool invertQEPB,
                      bool invertIndex, bool invertStrobe)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Configure QEPA signal
    //
    if(invertQEPA)
    {
        HWREGH(base + EQEP_O_QDECCTL) |= EQEP_QDECCTL_QAP;
    }
    else
    {
        HWREGH(base + EQEP_O_QDECCTL) &= ~EQEP_QDECCTL_QAP;
    }

    //
    // Configure QEPB signal
    //
    if(invertQEPB)
    {
        HWREGH(base + EQEP_O_QDECCTL) |= EQEP_QDECCTL_QBP;
    }
    else
    {
        HWREGH(base + EQEP_O_QDECCTL) &= ~EQEP_QDECCTL_QBP;
    }

    //
    // Configure index signal
    //
    if(invertIndex)
    {
        HWREGH(base + EQEP_O_QDECCTL) |= EQEP_QDECCTL_QIP;
    }
    else
    {
        HWREGH(base + EQEP_O_QDECCTL) &= ~EQEP_QDECCTL_QIP;
    }

    //
    // Configure strobe signal
    //
    if(invertStrobe)
    {
        HWREGH(base + EQEP_O_QDECCTL) |= EQEP_QDECCTL_QSP;
    }
    else
    {
        HWREGH(base + EQEP_O_QDECCTL) &= ~EQEP_QDECCTL_QSP;
    }
}
