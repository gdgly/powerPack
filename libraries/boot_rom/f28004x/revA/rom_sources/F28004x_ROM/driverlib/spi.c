//###########################################################################
//
// FILE:   spi.c
//
// TITLE:  C28x SPI driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "spi.h"

//*****************************************************************************
//
//! Returns the transmit interrupt number of SPI module.
//!
//! \param base is the base address of the SPI module.
//!
//! This function returns the interrupt number for the SPI module with the base
//! address passed in the \e base parameter.
//!
//! \return Returns an SPI interrupt number, or 0 if the interrupt does not
//! exist.
//
//*****************************************************************************
static uint32_t
SPI_getTxIntNumber(uint32_t base)
{
    uint32_t intNumber;

    switch(base)
    {
        case SPIA_BASE:
            intNumber = INT_SPIA_TX;
            break;

        case SPIB_BASE:
            intNumber = INT_SPIB_TX;
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
//! Returns the receive interrupt number of SPI module .
//!
//! \param base is the base address of the SPI module.
//!
//! This function returns the interrupt number for the SPI module with the base
//! address passed in the \e base parameter.
//!
//! \return Returns an SPI interrupt number, or 0 if the interrupt does not
//! exist.
//
//*****************************************************************************
static uint32_t
SPI_getRxIntNumber(uint32_t base)
{
    uint32_t intNumber;

    switch(base)
    {
        case SPIA_BASE:
            intNumber = INT_SPIA_RX;
            break;

        case SPIB_BASE:
            intNumber = INT_SPIB_RX;
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
// SPI_setConfig
//
//*****************************************************************************
void
SPI_setConfig(uint32_t base, uint32_t lspclkHz, SPI_TransferProtocol protocol,
              SPI_Mode mode, uint32_t bitRate, uint16_t dataWidth)
{
    uint16_t regValue;
    uint16_t baud;

    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));
    ASSERT(bitRate <= (lspclkHz / 4U));
    ASSERT((lspclkHz / bitRate) <= 128U);
    ASSERT((dataWidth >= 1U) && (dataWidth <= 16U));
    ASSERT((HWREGH(base + SPI_O_CCR) & SPI_CCR_SPISWRESET) == 0U);

    //
    // Set polarity and data width.
    //
    regValue = (((uint16_t)protocol << 6) & SPI_CCR_CLKPOLARITY) |
               (dataWidth - 1U);

    HWREGH(base + SPI_O_CCR) = (HWREGH(base + SPI_O_CCR) &
                                ~(SPI_CCR_CLKPOLARITY | SPI_CCR_SPICHAR_M)) |
                               regValue;

    //
    // Set the mode and phase.
    //
    regValue = (uint16_t)mode | (((uint16_t)protocol << 2) & SPI_CTL_CLK_PHASE);

    HWREGH(base + SPI_O_CTL) = (HWREGH(base + SPI_O_CTL) &
                                ~(SPI_CTL_TALK | SPI_CTL_MASTER_SLAVE |
                                  SPI_CTL_CLK_PHASE)) | regValue;

    //
    // Set the clock.
    //
    baud = (lspclkHz / bitRate) - 1U;
    HWREGH(base + SPI_O_BRR) = baud;
}

//*****************************************************************************
//
// SPI_setBaudRate
//
//*****************************************************************************
void
SPI_setBaudRate(uint32_t base, uint16_t lspclkHz, uint16_t bitRate)
{
    uint16_t baud;

    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));
    ASSERT(bitRate <= (lspclkHz / 4U));
    ASSERT((lspclkHz / bitRate) <= 128U);

    //
    // Set the clock.
    //
    baud = (lspclkHz / bitRate) - 1U;
    HWREGH(base + SPI_O_BRR) = baud;
}

//*****************************************************************************
//
// SPI_registerRxInterrupt
//
//*****************************************************************************
void
SPI_registerRxInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Determine the interrupt number based on the SPI port.
    //
    intNumber = SPI_getRxIntNumber(base);

    ASSERT(intNumber != 0);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the SPI interrupt.
    //
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// SPI_unregisterRxInterrupt
//
//*****************************************************************************
void
SPI_unregisterRxInterrupt(uint32_t base)
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Determine the interrupt number based on the SPI port.
    //
    intNumber = SPI_getRxIntNumber(base);

    ASSERT(intNumber != 0);

    //
    // Disable the SPI interrupt.
    //
    Interrupt_disable(intNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(intNumber);
}

//*****************************************************************************
//
// SPI_registerTxInterrupt
//
//*****************************************************************************
void
SPI_registerTxInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Determine the interrupt number based on the SPI port.
    //
    intNumber = SPI_getTxIntNumber(base);

    ASSERT(intNumber != 0);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the SPI interrupt.
    //
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//
// SPI_unregisterTxInterrupt
//
//*****************************************************************************
void
SPI_unregisterTxInterrupt(uint32_t base)
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Determine the interrupt number based on the SPI port.
    //
    intNumber = SPI_getTxIntNumber(base);

    ASSERT(intNumber != 0);

    //
    // Disable the SPI interrupt.
    //
    Interrupt_disable(intNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(intNumber);
}

//*****************************************************************************
//
// SPI_enableInterrupt
//
//*****************************************************************************
void
SPI_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Enable the specified non-FIFO interrupts.
    //
    if((intFlags & SPI_INT_RX_DATA_TX_EMPTY) != 0U)
    {
        HWREGH(base + SPI_O_CTL) |= SPI_CTL_SPIINTENA;
    }

    if((intFlags & SPI_INT_RX_OVERRUN) != 0U)
    {
        HWREGH(base + SPI_O_CTL) |= SPI_CTL_OVERRUNINTENA;
    }

    //
    // Enable the specified FIFO-mode interrupts.
    //
    if((intFlags & SPI_INT_TXFF) != 0U)
    {
        HWREGH(base + SPI_O_FFTX) |= SPI_FFTX_TXFFIENA;
    }

    if((intFlags & SPI_INT_RXFF) != 0U)
    {
        HWREGH(base + SPI_O_FFRX) |= SPI_FFRX_RXFFIENA;
    }
}

//*****************************************************************************
//
// SPI_disableInterrupt
//
//*****************************************************************************
void
SPI_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Disable the specified non-FIFO interrupts.
    //
    if((intFlags & SPI_INT_RX_DATA_TX_EMPTY) != 0U)
    {
        HWREGH(base + SPI_O_CTL) &= ~(SPI_CTL_SPIINTENA);
    }

    if((intFlags & SPI_INT_RX_OVERRUN) != 0U)
    {
        HWREGH(base + SPI_O_CTL) &= ~(SPI_CTL_OVERRUNINTENA);
    }

    //
    // Disable the specified FIFO-mode interrupts.
    //
    if((intFlags & SPI_INT_TXFF) != 0U)
    {
        HWREGH(base + SPI_O_FFTX) &= ~(SPI_FFTX_TXFFIENA);
    }

    if((intFlags & SPI_INT_RXFF) != 0U)
    {
        HWREGH(base + SPI_O_FFRX) &= ~(SPI_FFRX_RXFFIENA);
    }
}

//*****************************************************************************
//
// SPI_getInterruptStatus
//
//*****************************************************************************
uint32_t
SPI_getInterruptStatus(uint32_t base)
{
    uint32_t temp = 0;

    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    if((HWREGH(base + SPI_O_STS) & SPI_STS_INT_FLAG) != 0U)
    {
        temp |= SPI_INT_RX_DATA_TX_EMPTY;
    }

    if((HWREGH(base + SPI_O_STS) & SPI_STS_OVERRUN_FLAG) != 0U)
    {
        temp |= SPI_INT_RX_OVERRUN;
    }

    if((HWREGH(base + SPI_O_FFTX) & SPI_FFTX_TXFFINT) != 0U)
    {
        temp |= SPI_INT_TXFF;
    }

    if((HWREGH(base + SPI_O_FFRX) & SPI_FFRX_RXFFINT) != 0U)
    {
        temp |= SPI_INT_RXFF;
    }

    return(temp);
}

//*****************************************************************************
//
// SPI_clearInterruptStatus
//
//*****************************************************************************
void
SPI_clearInterruptStatus(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Clear the specified non-FIFO interrupt sources.
    //
    if(((intFlags & SPI_INT_RX_DATA_TX_EMPTY) != 0U) ||
       ((intFlags & SPI_INT_RX_OVERRUN) != 0U))
    {
        HWREGH(base + SPI_O_CCR) &= ~(SPI_CCR_SPISWRESET);
        HWREGH(base + SPI_O_CCR) |= SPI_CCR_SPISWRESET;
    }

    //
    // Clear the specified FIFO-mode interrupt sources.
    //
    if((intFlags & SPI_INT_TXFF) != 0U)
    {
        HWREGH(base + SPI_O_FFTX) |= SPI_FFTX_TXFFINTCLR;
    }

    if((intFlags & SPI_INT_RXFF) != 0U)
    {
        HWREGH(base + SPI_O_FFRX) |= SPI_FFRX_RXFFINTCLR;
    }
}
