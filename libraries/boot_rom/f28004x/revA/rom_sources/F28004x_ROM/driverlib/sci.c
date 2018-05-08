//###########################################################################
//
// FILE:   sci.c
//
// TITLE:  C28x SCI driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date: $
// $Copyright: $
//###########################################################################

#include "sci.h"

//*****************************************************************************
//
// SCI_setConfig
//
//*****************************************************************************
void
SCI_setConfig(uint32_t base, uint32_t lspclkHz, uint32_t baud, uint32_t config)
{
    uint32_t divider;

    //
    // Check the arguments.
    // Is the required baud rate greater than the maximum rate supported?
    //
    ASSERT(SCI_isBaseValid(base));
    ASSERT(baud != 0U);
    ASSERT((baud * 16U) <= lspclkHz);

    //
    // Stop the SCI.
    //
    SCI_disableModule(base);

    //
    // Compute the baud rate divider.
    //
    divider = ((lspclkHz  / (baud * 8U)) - 1U);

    //
    // Set the baud rate.
    //
    HWREGH(base + SCI_O_HBAUD) = (divider & 0xFF00) >> 8U;
    HWREGH(base + SCI_O_LBAUD) = divider & 0x00FF;

    //
    // Set parity, data length, and number of stop bits.
    //
    HWREGH(base + SCI_O_CCR) = ((HWREGH(base + SCI_O_CCR) &
                                 ~(SCI_CONFIG_PAR_MASK |
                                   SCI_CONFIG_STOP_MASK |
                                   SCI_CONFIG_WLEN_MASK)) | config);

    //
    // Start the SCI.
    //
    SCI_enableModule(base);
}

//*****************************************************************************
//
// SCI_writeCharArray
//
//*****************************************************************************
void
SCI_writeCharArray(uint32_t base, uint16_t *array, uint16_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    uint16_t i;
    //
    // Check if FIFO enhancement is enabled.
    //
    if(SCI_isFIFOEnabled(base))
    {
        //
        // FIFO is enabled.
        // For loop to write (Blocking) 'length' number of characters
        //
        for(i = 0U; i < length; i++)
        {
            //
            // Wait until space is available in the transmit FIFO.
            //
            while(SCI_getTxFIFOStatus(base) == SCI_FIFO_TX15)
            {
            }

            //
            // Send a char.
            //
            HWREGH(base + SCI_O_TXBUF) = array[i];
        }
    }
    else
    {
        //
        // FIFO is not enabled.
        // For loop to write (Blocking) 'length' number of characters
        //
        for(i = 0U; i < length; i++)
        {
            //
            // Wait until space is available in the transmit buffer.
            //
            while(!SCI_isSpaceAvailableNonFIFO(base))
            {
            }

            //
            // Send a char.
            //
            HWREGH(base + SCI_O_TXBUF) = array[i];
        }
    }
}

//*****************************************************************************
//
// SCI_readCharArray
//
//*****************************************************************************
void
SCI_readCharArray(uint32_t base, uint16_t *array, uint16_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    uint16_t i;
    //
    // Check if FIFO enhancement is enabled.
    //
    if(SCI_isFIFOEnabled(base))
    {
        //
        // FIFO is enabled.
        // For loop to read (Blocking) 'length' number of characters
        //
        for(i = 0U; i < length; i++)
        {
            //
            // Wait until a character is available in the receive FIFO.
            //
            while(SCI_getRxFIFOStatus(base) == SCI_FIFO_RX0)
            {
            }

            //
            // Return the character from the receive buffer.
            //
            array[i] = (uint16_t)
                       (HWREGH(base + SCI_O_RXBUF) & SCI_RXBUF_SAR_M);
        }
    }
    else
    {
        //
        // FIFO is not enabled.
        // For loop to read (Blocking) 'length' number of characters
        //
        for(i = 0U; i < length; i++)
        {
            //
            // Wait until a character is available in the receive buffer.
            //
            while(!SCI_isDataAvailableNonFIFO(base))
            {
            }

            //
            // Return the character from the receive buffer.
            //
            array[i] = (uint16_t)
                       (HWREGH(base + SCI_O_RXBUF) & SCI_RXBUF_SAR_M);
        }
    }
}

//*****************************************************************************
//
// SCI_getRXInterruptNumber
//
//*****************************************************************************
uint32_t
SCI_getRxInterruptNumber(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    if(base == SCIA_BASE)
    {
        return(INT_SCIA_RX);
    }
//#####BEGIN_F2837XD_F2837XS_F2807X#####
//    else if(base == SCIC_BASE)
//    {
//        return(INT_SCIC_RX);
//    }
//    else if(base == SCID_BASE)
//    {
//        return(INT_SCID_RX);
//    }
//#####END_F2837XD_F2837XS_F2807X#####
    else
    {
        return(INT_SCIB_RX);
    }
}

//*****************************************************************************
//
// SCI_getTXInterruptNumber
//
//*****************************************************************************
uint32_t
SCI_getTxInterruptNumber(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    if(base == SCIA_BASE)
    {
        return(INT_SCIA_TX);
    }
//#####BEGIN_F2837XD_F2837XS_F2807X#####
//    else if(base == SCIC_BASE)
//    {
//        return(INT_SCIC_TX);
//    }
//    else if(base == SCID_BASE)
//    {
//        return(INT_SCID_TX);
//    }
//#####END_F2837XD_F2837XS_F2807X#####
    else
    {
        return(INT_SCIB_TX);
    }
}

//*****************************************************************************
//
// SCI_registerRxInterrupt
//
//*****************************************************************************
void
SCI_registerRxInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNum;

    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    //
    // Determine the interrupt number based on the SCI port.
    //
    intNum = SCI_getRxInterruptNumber(base);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNum, handler);

    //
    // Enable the SCI interrupt.
    //
    Interrupt_enable(intNum);
}

//*****************************************************************************
//
// SCI_registerTxInterrupt
//
//*****************************************************************************
void
SCI_registerTxInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNum;

    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    //
    // Determine the interrupt number based on the SCI port.
    //
    intNum = SCI_getTxInterruptNumber(base);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNum, handler);

    //
    // Enable the SCI interrupt.
    //
    Interrupt_enable(intNum);
}

//*****************************************************************************
//
// SCI_unregisterRxInterrupt
//
//*****************************************************************************
void
SCI_unregisterRxInterrupt(uint32_t base)
{
    uint32_t intNum;

    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    //
    // Determine the interrupt number based on the SCI port.
    //
    intNum = SCI_getRxInterruptNumber(base);

    //
    // Disable the interrupt.
    //
    Interrupt_disable(intNum);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregister(intNum);
}

//*****************************************************************************
//
// SCI_unregisterTxInterrupt
//
//*****************************************************************************
void
SCI_unregisterTXInterrupt(uint32_t base)
{
    uint32_t intNum;

    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    //
    // Determine the interrupt number based on the SCI port.
    //
    intNum = SCI_getTxInterruptNumber(base);

    //
    // Disable the interrupt.
    //
    Interrupt_disable(intNum);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregister(intNum);
}

//*****************************************************************************
//
// SCI_enableInterrupt
//
//*****************************************************************************
void
SCI_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    //
    // Enable the specified interrupts.
    //
    if((intFlags & SCI_INT_RXERR) == SCI_INT_RXERR)
    {
        HWREGH(base + SCI_O_CTL1) |= SCI_CTL1_RXERRINTENA;
    }
    if((intFlags & SCI_INT_RXRDY_BRKDT) == SCI_INT_RXRDY_BRKDT)
    {
        HWREGH(base + SCI_O_CTL2) |= SCI_CTL2_RXBKINTENA;
    }
    if((intFlags & SCI_INT_TXRDY) == SCI_INT_TXRDY)
    {
        HWREGH(base + SCI_O_CTL2) |= SCI_CTL2_TXINTENA;
    }
    if((intFlags & SCI_INT_TXFF) == SCI_INT_TXFF)
    {
        HWREGH(base + SCI_O_FFTX) |= SCI_FFTX_TXFFIENA;
    }
    if((intFlags & SCI_INT_RXFF) == SCI_INT_RXFF)
    {
        HWREGH(base + SCI_O_FFRX) |= SCI_FFRX_RXFFIENA;
    }
}

//*****************************************************************************
//
// SCI_disableInterrupt
//
//*****************************************************************************
void
SCI_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    //
    // Disable the specified interrupts.
    //
    if((intFlags & SCI_INT_RXERR) == SCI_INT_RXERR)
    {
        HWREGH(base + SCI_O_CTL1) &= ~SCI_CTL1_RXERRINTENA;
    }
    if((intFlags & SCI_INT_RXRDY_BRKDT) == SCI_INT_RXRDY_BRKDT)
    {
        HWREGH(base + SCI_O_CTL2) &= ~SCI_CTL2_RXBKINTENA;
    }
    if((intFlags & SCI_INT_TXRDY) == SCI_INT_TXRDY)
    {
        HWREGH(base + SCI_O_CTL2) &= ~SCI_CTL2_TXINTENA;
    }
    if((intFlags & SCI_INT_TXFF) == SCI_INT_TXFF)
    {
        HWREGH(base + SCI_O_FFTX) &= ~SCI_FFTX_TXFFIENA;
    }
    if((intFlags & SCI_INT_RXFF) == SCI_INT_RXFF)
    {
        HWREGH(base + SCI_O_FFRX) &= ~SCI_FFRX_RXFFIENA;
    }
}

//*****************************************************************************
//
// SCI_getInterruptStatus
//
//*****************************************************************************
uint32_t
SCI_getInterruptStatus(uint32_t base)
{
    uint32_t interruptStatus = 0;

    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    //
    // Return the interrupt status.
    //
    if((HWREGH(base + SCI_O_CTL2) & SCI_CTL2_TXRDY) == SCI_CTL2_TXRDY)
    {
        interruptStatus |= SCI_INT_TXRDY;
    }
    if((HWREGH(base + SCI_O_RXST) & SCI_RXST_RXERROR) == SCI_RXST_RXERROR)
    {
        interruptStatus |= SCI_INT_RXERR;
    }
    if((HWREGH(base + SCI_O_RXST) & (SCI_RXST_RXRDY | SCI_RXST_BRKDT)) ==
        (SCI_RXST_RXRDY | SCI_RXST_BRKDT))
    {
        interruptStatus |= SCI_INT_RXRDY_BRKDT;
    }
    if((HWREGH(base + SCI_O_FFTX) & SCI_FFTX_TXFFINT) == SCI_FFTX_TXFFINT)
    {
        interruptStatus |= SCI_INT_TXFF;
    }
    if((HWREGH(base + SCI_O_FFRX) & SCI_FFRX_RXFFINT) == SCI_FFRX_RXFFINT)
    {
        interruptStatus |= SCI_INT_RXFF;
    }

    return(interruptStatus);
}

//*****************************************************************************
//
// SCI_clearInterruptStatus
//
//*****************************************************************************
void
SCI_clearInterruptStatus(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(SCI_isBaseValid(base));

    //
    // Clear the requested interrupt sources.
    //
    if((intFlags & (SCI_INT_RXERR | SCI_INT_RXRDY_BRKDT)) ==
        (SCI_INT_RXERR | SCI_INT_RXRDY_BRKDT))
    {
        SCI_performSoftwareReset(base);
    }

    if((intFlags & SCI_INT_TXFF) == SCI_INT_TXFF)
    {
        HWREGH(base + SCI_O_FFTX) |= SCI_FFTX_TXFFINTCLR;
    }

    if((intFlags & SCI_INT_RXFF) == SCI_INT_RXFF)
    {
         HWREGH(base + SCI_O_FFRX) |= SCI_FFRX_RXFFINTCLR;
    }
}
