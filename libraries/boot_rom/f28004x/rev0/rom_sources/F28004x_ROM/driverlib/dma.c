//###########################################################################
//
// FILE:   dma.c
//
// TITLE:  C28x DMA driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "dma.h"

//*****************************************************************************
//
//! \internal
//! Returns the transmit interrupt number of DMA channel.
//!
//! \param base is the base address of the DMA channel.
//!
//! This function returns the interrupt number for the DMA channel with the
//! base address passed in the \e base parameter.
//!
//! \return Returns an DMA interrupt number, or 0 if the interrupt does not
//! exist.
//
//*****************************************************************************
static uint32_t
DMA_getIntNumber(uint32_t base)
{
    uint32_t intNumber;

    switch(base)
    {
        case DMA_CH1_BASE:
            intNumber = INT_DMA_CH1;
            break;

        case DMA_CH2_BASE:
            intNumber = INT_DMA_CH2;
            break;

        case DMA_CH3_BASE:
            intNumber = INT_DMA_CH3;
            break;

        case DMA_CH4_BASE:
            intNumber = INT_DMA_CH4;
            break;

        case DMA_CH5_BASE:
            intNumber = INT_DMA_CH5;
            break;

        case DMA_CH6_BASE:
            intNumber = INT_DMA_CH6;
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
// DMA_configAddresses
//
//*****************************************************************************
void DMA_configAddresses(uint32_t base, uint16_t *destAddr, uint16_t *srcAddr)
{
    // Check the arguments.
    ASSERT(DMA_isBaseValid(base));

    EALLOW;

    // Set up SOURCE address.
    HWREG(base + DMA_O_SRC_BEG_ADDR_SHADOW) = (uint32_t)srcAddr;
    HWREG(base + DMA_O_SRC_ADDR_SHADOW)     = (uint32_t)srcAddr;

    // Set up DESTINATION address.
    HWREG(base + DMA_O_DST_BEG_ADDR_SHADOW) = (uint32_t)destAddr;
    HWREG(base + DMA_O_DST_ADDR_SHADOW)     = (uint32_t)destAddr;

    EDIS;
}

//*****************************************************************************
//
// DMA_configBurst
//
//*****************************************************************************
void DMA_configBurst(uint32_t base, uint16_t size, int16_t srcStep,
                     int16_t destStep)
{
    // Check the arguments.
    ASSERT(DMA_isBaseValid(base));
    ASSERT((size >= 1U) || (size <= 32U));

    EALLOW;

    // Set up BURST registers.
    HWREGH(base + DMA_O_BURST_SIZE)     = size - 1U;
    HWREGH(base + DMA_O_SRC_BURST_STEP) = srcStep;
    HWREGH(base + DMA_O_DST_BURST_STEP) = destStep;

    EDIS;
}

//*****************************************************************************
//
// DMA_configTransfer
//
//*****************************************************************************
void DMA_configTransfer(uint32_t base, uint16_t transferSize, int16_t srcStep,
                        int16_t destStep)
{
    // Check the arguments.
    ASSERT(DMA_isBaseValid(base));

    EALLOW;

    // Set up TRANSFER registers.
    HWREGH(base + DMA_O_TRANSFER_SIZE)     = transferSize - 1U;
    HWREGH(base + DMA_O_SRC_TRANSFER_STEP) = srcStep;
    HWREGH(base + DMA_O_DST_TRANSFER_STEP) = destStep;

    EDIS;
}

//*****************************************************************************
//
// DMA_configWrap
//
//*****************************************************************************
void DMA_configWrap(uint32_t base, uint16_t srcWrapSize, int16_t srcStep,
                    uint16_t destWrapSize, int16_t destStep)
{
    // Check the arguments.
    ASSERT(DMA_isBaseValid(base));

    EALLOW;

    // Set up WRAP registers.
    HWREGH(base + DMA_O_SRC_WRAP_SIZE) = srcWrapSize - 1U;
    HWREGH(base + DMA_O_SRC_WRAP_STEP) = srcStep;

    HWREGH(base + DMA_O_DST_WRAP_SIZE) = destWrapSize - 1U;
    HWREGH(base + DMA_O_DST_WRAP_STEP) = destStep;

    EDIS;
}

//*****************************************************************************
//
// DMA_configMode
//
//*****************************************************************************
void DMA_configMode(uint32_t base, DMA_Trigger trigger, uint32_t config)
{
    // Check the arguments.
    ASSERT(DMA_isBaseValid(base));

    EALLOW;

    // Set up trigger selection in the CMA/CLA trigger source selection
    // registers. These are considered part of system control.
    switch(base)
    {
        case DMA_CH1_BASE:
            // Channel 1
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL1_CH1_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL1_CH1_S);

            // Set peripheral interrupt select bits to the channel number.
            HWREGH(DMA_CH1_BASE + DMA_O_MODE) =
                (HWREGH(DMA_CH1_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 1U;
            break;

        case DMA_CH2_BASE:
            // Channel 2
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL1_CH2_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL1_CH2_S);

            // Set peripheral interrupt select bits to the channel number.
            HWREGH(DMA_CH2_BASE + DMA_O_MODE) =
                (HWREGH(DMA_CH2_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 2U;
            break;

        case DMA_CH3_BASE:
            // Channel 3
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL1_CH3_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL1_CH3_S);

            // Set peripheral interrupt select bits to the channel number.
            HWREGH(DMA_CH3_BASE + DMA_O_MODE) =
                (HWREGH(DMA_CH3_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 3U;
            break;

        case DMA_CH4_BASE:
            // Channel 4
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL1) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL1_CH4_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL1_CH4_S);

            // Set peripheral interrupt select bits to the channel number.
            HWREGH(DMA_CH4_BASE + DMA_O_MODE) =
                (HWREGH(DMA_CH4_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 4U;
            break;

        case DMA_CH5_BASE:
            // Channel 5
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL2) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL2) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL2_CH5_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL2_CH5_S);

            // Set peripheral interrupt select bits to the channel number.
            HWREGH(DMA_CH5_BASE + DMA_O_MODE) =
                (HWREGH(DMA_CH5_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 5U;
            break;

        case DMA_CH6_BASE:
            // Channel 6
            HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL2) =
                (HWREG(DMACLASRCSEL_BASE + SYSCTL_O_DMACHSRCSEL2) &
                 ~((uint32_t)SYSCTL_DMACHSRCSEL2_CH6_M)) |
                ((uint32_t)trigger << SYSCTL_DMACHSRCSEL2_CH6_S);

            // Set peripheral interrupt select bits to the channel number.
            HWREGH(DMA_CH6_BASE + DMA_O_MODE) =
                (HWREGH(DMA_CH6_BASE + DMA_O_MODE) & ~DMA_MODE_PERINTSEL_M) | 6U;
            break;

        default:
            // Invalid base.
            break;
    }

    // Write the configuration to the mode register.
    HWREGH(base + DMA_O_MODE) |= config;

    EDIS;
}

//*****************************************************************************
//
// DMA_registerInterrupt
//
//*****************************************************************************
void
DMA_registerInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNumber;

    // Check the arguments.
    ASSERT(DMA_isBaseValid(base));

    // Determine the interrupt number based on the DMA channel.
    intNumber = DMA_getIntNumber(base);

    ASSERT(intNumber != 0U);

    // Register the interrupt handler.
    Interrupt_register(intNumber, handler);

    // Enable the DMA interrupt.
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// DMA_unregisterInterrupt
//
//*****************************************************************************
void
DMA_unregisterInterrupt(uint32_t base)
{
    uint32_t intNumber;

    // Check the arguments.
    ASSERT(DMA_isBaseValid(base));

    // Determine the interrupt number based on the DMA channel.
    intNumber = DMA_getIntNumber(base);

    ASSERT(intNumber != 0U);

    // Disable the DMA interrupt.
    Interrupt_disable(intNumber);

    // Register the interrupt handler.
    Interrupt_unregister(intNumber);
}
