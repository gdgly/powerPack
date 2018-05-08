//###########################################################################
//
// FILE:   adc.c
//
// TITLE:  C28x ADC driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "adc.h"

//*****************************************************************************
//
// A mapping of ADC base address to interrupt number. Not intended for use by
// application code.
//
//*****************************************************************************
static const uint32_t ADC_intMap[3][ADC_NUM_INTERRUPTS + 1U] =
{
    {ADCA_BASE, INT_ADCA1, INT_ADCA2, INT_ADCA3, INT_ADCA4},
    {ADCB_BASE, INT_ADCB1, INT_ADCB2, INT_ADCB3, INT_ADCB4},
    {ADCC_BASE, INT_ADCC1, INT_ADCC2, INT_ADCC3, INT_ADCC4}
};

//*****************************************************************************
//
//! \internal
//! Returns the analog-to-digital converter interrupt number.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function returns the interrupt number for the ADC interrupt that
//! corresponds to the base address passed in \e base and the number passed in
//! \e adcIntNum.  \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3, \b or ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module should be used.
//!
//! \return Returns an ADC interrupt number or 0 if the interrupt does not
//! exist.
//
//*****************************************************************************
static uint32_t
ADC_getIntNumber(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint16_t index;
    uint16_t intMapRows = sizeof(ADC_intMap) / sizeof(ADC_intMap[0]);

    //
    // Loop through the table that maps ADC base addresses to interrupt
    // numbers.
    //
    for(index = 0U; index < intMapRows; index++)
    {
        //
        // See if this base address matches.
        //
        if(ADC_intMap[index][0U] == base)
        {
            //
            // Return the corresponding interrupt number.
            //
            return(ADC_intMap[index][(uint16_t)adcIntNum + 1U]);
        }
    }

    //
    // The base address could not be found, so return an error.
    //
    return(0U);
}

//*****************************************************************************
//
//! \internal
//! Returns the analog-to-digital converter event interrupt number.
//!
//! \param base base is the base address of the ADC module.
//!
//! This function returns the event interrupt number for the ADC with the base
//! address passed in the \e base parameter.
//!
//! \return Returns an ADC event interrupt number or 0 if the interrupt does not
//! exist.
//
//*****************************************************************************
static uint32_t
ADC_getPPBEventIntNumber(uint32_t base)
{
    uint32_t intNumber;

    //
    // Find the valid interrupt number for this ADC.
    //
    switch (base)
    {
        case ADCA_BASE:
            intNumber = INT_ADCA_EVT;
            break;

        case ADCB_BASE:
            intNumber = INT_ADCB_EVT;
            break;

        case ADCC_BASE:
            intNumber = INT_ADCC_EVT;
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
// ADC_registerInterrupt
//
//*****************************************************************************
void
ADC_registerInterrupt(uint32_t base, ADC_IntNumber adcIntNum,
                      void (*handler)(void))
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Determine the interrupt number based on the ADC port.
    //
    intNumber = ADC_getIntNumber(base, adcIntNum);

    ASSERT(intNumber != 0);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the ADC interrupt.
    //
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// ADC_unregisterInterrupt
//
//*****************************************************************************
void
ADC_unregisterInterrupt(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Determine the interrupt number based on the ADC port.
    //
    intNumber = ADC_getIntNumber(base, adcIntNum);

    ASSERT(intNumber != 0);

    //
    // Disable the ADC interrupt.
    //
    Interrupt_disable(intNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(intNumber);
}

//*****************************************************************************
//
// ADC_enableInterrupt
//
//*****************************************************************************
void
ADC_enableInterrupt(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Enable the specified ADC interrupt.
    //
    EALLOW;

    HWREGH(intRegAddr) |= ADC_INTSEL1N2_INT1E << shiftVal;

    EDIS;
}

//*****************************************************************************
//
// ADC_disableInterrupt
//
//*****************************************************************************
void
ADC_disableInterrupt(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Disable the specified ADC interrupt.
    //
    EALLOW;

    HWREGH(intRegAddr) &= ~(ADC_INTSEL1N2_INT1E << shiftVal);

    EDIS;
}

//*****************************************************************************
//
// ADC_setInterruptSource
//
//*****************************************************************************
void
ADC_setInterruptSource(uint32_t base, ADC_IntNumber adcIntNum,
                       ADC_SOCNumber socNumber)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Set the specified ADC interrupt source.
    //
    EALLOW;

    HWREGH(intRegAddr) =
        (HWREGH(intRegAddr) & ~(ADC_INTSEL1N2_INT1SEL_M << shiftVal)) |
        ((uint16_t)socNumber << shiftVal);

    EDIS;
}

//*****************************************************************************
//
// ADC_enableContinuousMode
//
//*****************************************************************************
void
ADC_enableContinuousMode(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Enable continuous mode for the specified ADC interrupt.
    //
    EALLOW;

    HWREGH(intRegAddr) |= ADC_INTSEL1N2_INT1CONT << shiftVal;

    EDIS;
}

//*****************************************************************************
//
// ADC_disableContinuousMode
//
//*****************************************************************************
void
ADC_disableContinuousMode(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Disable continuous mode for the specified ADC interrupt.
    //
    EALLOW;

    HWREGH(intRegAddr) &= ~(ADC_INTSEL1N2_INT1CONT << shiftVal);

    EDIS;
}

//*****************************************************************************
//
// ADC_registerPPBEventInterrupt
//
//*****************************************************************************
void
ADC_registerPPBEventInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Determine the interrupt number based on the ADC port.
    //
    intNumber = ADC_getPPBEventIntNumber(base);

    ASSERT(intNumber != 0);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the ADC interrupt.
    //
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// ADC_unregisterPPBEventInterrupt
//
//*****************************************************************************
void
ADC_unregisterPPBEventInterrupt(uint32_t base)
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Determine the interrupt number based on the ADC port.
    //
    intNumber = ADC_getPPBEventIntNumber(base);

    ASSERT(intNumber != 0);

    //
    // Disable the ADC interrupt.
    //
    Interrupt_disable(intNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(intNumber);
}

//*****************************************************************************
//
// ADC_setPPBTripLimits
//
//*****************************************************************************
void
ADC_setPPBTripLimits(uint32_t base, ADC_PPBNumber ppbNumber,
                     int32_t tripHiLimit, int32_t tripLoLimit)
{
    uint32_t ppbHiOffset;
    uint32_t ppbLoOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((tripHiLimit <= 65535) && (tripHiLimit >= -65536));
    ASSERT((tripLoLimit <= 65535) && (tripLoLimit >= -65536));

    //
    // Get the offset to the appropriate trip limit registers.
    //
    ppbHiOffset = (ADC_PPBxTRIPHI_STEP * (uint32_t)ppbNumber) +
                  ADC_O_PPB1TRIPHI;
    ppbLoOffset = (ADC_PPBxTRIPLO_STEP * (uint32_t)ppbNumber) +
                  ADC_O_PPB1TRIPLO;

    EALLOW;

    //
    // Set the trip high limit.
    //
    HWREG(base + ppbHiOffset) &= ~((uint32_t)ADC_PPB1TRIPHI_LIMITHI_M |
                                   ADC_PPB1TRIPHI_HSIGN);
    HWREG(base + ppbHiOffset) |= (uint32_t)tripHiLimit &
                                 (ADC_PPB1TRIPHI_LIMITHI_M |
                                  ADC_PPB1TRIPHI_HSIGN);

    //
    // Set the trip low limit.
    //
    HWREG(base + ppbLoOffset) &= ~((uint32_t)ADC_PPB1TRIPLO_LIMITLO_M |
                                   ADC_PPB1TRIPLO_LSIGN);
    HWREG(base + ppbLoOffset) |= (uint32_t)tripLoLimit &
                                 (ADC_PPB1TRIPLO_LIMITLO_M |
                                  ADC_PPB1TRIPLO_LSIGN);

    EDIS;
}
