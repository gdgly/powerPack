//###########################################################################
//
// FILE:    hw_sci_t0.h
//
// TITLE:   Definitions for the SCI registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef __HW_SCI_T0_H__
#define __HW_SCI_T0_H__

//*****************************************************************************
//
// The following are defines for the SCI register offsets
//
//*****************************************************************************
#define SCI_O_CCR                 0x0U        // Communications control
                                              // register
#define SCI_O_CTL1                0x1U        // Control register 1
#define SCI_O_HBAUD               0x2U        // Baud rate (high) register
#define SCI_O_LBAUD               0x3U        // Baud rate (low) register
#define SCI_O_CTL2                0x4U        // Control register 2
#define SCI_O_RXST                0x5U        // Recieve status register
#define SCI_O_RXEMU               0x6U        // Recieve emulation buffer
                                              // register
#define SCI_O_RXBUF               0x7U        // Recieve data buffer
#define SCI_O_TXBUF               0x9U        // Transmit data buffer
#define SCI_O_FFTX                0xAU        // FIFO transmit register
#define SCI_O_FFRX                0xBU        // FIFO recieve register
#define SCI_O_FFCT                0xCU        // FIFO control register
#define SCI_O_PRI                 0xFU        // FIFO Priority control

//*****************************************************************************
//
// The following are defines for the bit fields in the SCICCR register
//
//*****************************************************************************
#define SCI_CCR_SCICHAR_S         0U
#define SCI_CCR_SCICHAR_M         0x7U        // Character length control
#define SCI_CCR_ADDRIDLE_MODE     0x8U        // ADDR/IDLE Mode control
#define SCI_CCR_LOOPBKENA         0x10U       // Loop Back enable
#define SCI_CCR_PARITYENA         0x20U       // Parity enable
#define SCI_CCR_PARITY            0x40U       // Even or Odd Parity
#define SCI_CCR_STOPBITS          0x80U       // Number of Stop Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the SCICTL1 register
//
//*****************************************************************************
#define SCI_CTL1_RXENA            0x1U        // SCI receiver enable
#define SCI_CTL1_TXENA            0x2U        // SCI transmitter enable
#define SCI_CTL1_SLEEP            0x4U        // SCI sleep
#define SCI_CTL1_TXWAKE           0x8U        // Transmitter wakeup method
#define SCI_CTL1_SWRESET          0x20U       // Software reset
#define SCI_CTL1_RXERRINTENA      0x40U       // Recieve __interrupt enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SCIHBAUD register
//
//*****************************************************************************
#define SCI_HBAUD_BAUD_S          0U
#define SCI_HBAUD_BAUD_M          0xFFU       // SCI 16-bit baud selection
                                              // Registers SCIHBAUD

//*****************************************************************************
//
// The following are defines for the bit fields in the SCILBAUD register
//
//*****************************************************************************
#define SCI_LBAUD_BAUD_S          0U
#define SCI_LBAUD_BAUD_M          0xFFU       // SCI 16-bit baud selection
                                              // Registers SCILBAUD

//*****************************************************************************
//
// The following are defines for the bit fields in the SCICTL2 register
//
//*****************************************************************************
#define SCI_CTL2_TXINTENA         0x1U        // Transmit __interrupt enable
#define SCI_CTL2_RXBKINTENA       0x2U        // Receiver-buffer break enable
#define SCI_CTL2_TXEMPTY          0x40U       // Transmitter empty flag
#define SCI_CTL2_TXRDY            0x80U       // Transmitter ready flag

//*****************************************************************************
//
// The following are defines for the bit fields in the SCIRXST register
//
//*****************************************************************************
#define SCI_RXST_RXWAKE           0x2U        // Receiver wakeup detect flag
#define SCI_RXST_PE               0x4U        // Parity error flag
#define SCI_RXST_OE               0x8U        // Overrun error flag
#define SCI_RXST_FE               0x10U       // Framing error flag
#define SCI_RXST_BRKDT            0x20U       // Break-detect flag
#define SCI_RXST_RXRDY            0x40U       // Receiver ready flag
#define SCI_RXST_RXERROR          0x80U       // Receiver error flag

//*****************************************************************************
//
// The following are defines for the bit fields in the SCIRXEMU register
//
//*****************************************************************************
#define SCI_RXEMU_ERXDT_S         0U
#define SCI_RXEMU_ERXDT_M         0xFFU       // Receive emulation buffer data

//*****************************************************************************
//
// The following are defines for the bit fields in the SCIRXBUF register
//
//*****************************************************************************
#define SCI_RXBUF_SAR_S           0U
#define SCI_RXBUF_SAR_M           0xFFU       // Receive Character bits
#define SCI_RXBUF_SCIFFPE         0x4000U     // Receiver error flag
#define SCI_RXBUF_SCIFFFE         0x8000U     // Receiver error flag

//*****************************************************************************
//
// The following are defines for the bit fields in the SCITXBUF register
//
//*****************************************************************************
#define SCI_TXBUF_TXDT_S          0U
#define SCI_TXBUF_TXDT_M          0xFFU       // Transmit data buffer

//*****************************************************************************
//
// The following are defines for the bit fields in the SCIFFTX register
//
//*****************************************************************************
#define SCI_FFTX_TXFFIL_S         0U
#define SCI_FFTX_TXFFIL_M         0x1FU       // Interrupt level
#define SCI_FFTX_TXFFIENA         0x20U       // Interrupt enable
#define SCI_FFTX_TXFFINTCLR       0x40U       // Clear INT flag
#define SCI_FFTX_TXFFINT          0x80U       // INT flag
#define SCI_FFTX_TXFFST_S         8U
#define SCI_FFTX_TXFFST_M         0x1F00U     // FIFO status
#define SCI_FFTX_TXFIFOXRESET     0x2000U     // FIFO reset
#define SCI_FFTX_SCIFFENA         0x4000U     // Enhancement enable
#define SCI_FFTX_SCIRST           0x8000U     // SCI reset rx/tx channels

//*****************************************************************************
//
// The following are defines for the bit fields in the SCIFFRX register
//
//*****************************************************************************
#define SCI_FFRX_RXFFIL_S         0U
#define SCI_FFRX_RXFFIL_M         0x1FU       // Interrupt level
#define SCI_FFRX_RXFFIENA         0x20U       // Interrupt enable
#define SCI_FFRX_RXFFINTCLR       0x40U       // Clear INT flag
#define SCI_FFRX_RXFFINT          0x80U       // INT flag
#define SCI_FFRX_RXFFST_S         8U
#define SCI_FFRX_RXFFST_M         0x1F00U     // FIFO status
#define SCI_FFRX_RXFIFORESET      0x2000U     // FIFO reset
#define SCI_FFRX_RXFFOVRCLR       0x4000U     // Clear overflow
#define SCI_FFRX_RXFFOVF          0x8000U     // FIFO overflow

//*****************************************************************************
//
// The following are defines for the bit fields in the SCIFFCT register
//
//*****************************************************************************
#define SCI_FFCT_FFTXDLY_S        0U
#define SCI_FFCT_FFTXDLY_M        0xFFU       // FIFO transmit delay
#define SCI_FFCT_CDC              0x2000U     // Auto baud mode enable
#define SCI_FFCT_ABDCLR           0x4000U     // Auto baud clear
#define SCI_FFCT_ABD              0x8000U     // Auto baud detect

//*****************************************************************************
//
// The following are defines for the bit fields in the SCIPRI register
//
//*****************************************************************************
#define SCI_PRI_FREESOFT_S        3U
#define SCI_PRI_FREESOFT_M        0x18U       // Emulation modes
#endif
