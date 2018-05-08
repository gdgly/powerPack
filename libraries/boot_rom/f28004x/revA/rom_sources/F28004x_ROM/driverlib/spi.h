//###########################################################################
//
// FILE:   spi.h
//
// TITLE:  C28x SPI driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __SPI_H__
#define __SPI_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup spi_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_spi.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
//
// Values that can be passed to SPI_enableInterrupt(), SPI_disableInterrupt(),
// and SPI_clearInterruptStatus() as the \e intFlags parameter, and returned by
// SPI_getInterruptStatus().
//
//*****************************************************************************
#define SPI_INT_RX_OVERRUN        0x0001U //!< Receive overrun interrupt
#define SPI_INT_RX_DATA_TX_EMPTY  0x0002U //!< Data received, transmit empty
#define SPI_INT_RXFF              0x0004U //!< RX FIFO level interrupt
#define SPI_INT_TXFF              0x0008U //!< TX FIFO level interrupt

//*****************************************************************************
//
//! Values that can be passed to SPI_setConfig() as the \e protocol parameter.
//
//*****************************************************************************
typedef enum
{
    //! Mode 0. Polarity 0, phase 0. Rising edge without delay.
    SPI_PROT_POL0PHA0   = 0x0000U,
    //! Mode 1. Polarity 0, phase 1. Rising edge with delay.
    SPI_PROT_POL0PHA1   = 0x0002U,
    //! Mode 2. Polarity 1, phase 0. Falling edge without delay.
    SPI_PROT_POL1PHA0   = 0x0001U,
    //! Mode 3. Polarity 1, phase 1. Falling edge with delay.
    SPI_PROT_POL1PHA1   = 0x0003U
} SPI_TransferProtocol;

//*****************************************************************************
//
//! Values that can be passed to SPI_setConfig() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    SPI_MODE_SLAVE     = 0x0002U,   //!< SPI slave
    SPI_MODE_MASTER    = 0x0006U,   //!< SPI master
    SPI_MODE_SLAVE_OD  = 0x0000U,   //!< SPI slave w/ output (TALK) disabled
    SPI_MODE_MASTER_OD = 0x0004U    //!< SPI master w/ output (TALK) disabled
} SPI_Mode;

//*****************************************************************************
//
//! Values that can be passed to SPI_setFIFOInterruptLevel() as the \e txLevel
//! parameter and returned by SPI_getFIFOInterruptLevel() in the \e txLevel.
//
//*****************************************************************************
typedef enum
{
    SPI_FIFO_TXEMPTY    = 0x0000U,      //!< Transmit interrupt empty
    SPI_FIFO_TX0        = 0x0000U,      //!< Transmit interrupt empty
    SPI_FIFO_TX1        = 0x0001U,      //!< Transmit interrupt 1/15 full
    SPI_FIFO_TX2        = 0x0002U,      //!< Transmit interrupt 2/15 full
    SPI_FIFO_TX3        = 0x0003U,      //!< Transmit interrupt 3/15 full
    SPI_FIFO_TX4        = 0x0004U,      //!< Transmit interrupt 4/15 full
    SPI_FIFO_TX5        = 0x0005U,      //!< Transmit interrupt 5/15 full
    SPI_FIFO_TX6        = 0x0006U,      //!< Transmit interrupt 6/15 full
    SPI_FIFO_TX7        = 0x0007U,      //!< Transmit interrupt 7/15 full
    SPI_FIFO_TX8        = 0x0008U,      //!< Transmit interrupt 8/15 full
    SPI_FIFO_TX9        = 0x0009U,      //!< Transmit interrupt 9/15 full
    SPI_FIFO_TX10       = 0x000AU,      //!< Transmit interrupt 10/15 full
    SPI_FIFO_TX11       = 0x000BU,      //!< Transmit interrupt 11/15 full
    SPI_FIFO_TX12       = 0x000CU,      //!< Transmit interrupt 12/15 full
    SPI_FIFO_TX13       = 0x000DU,      //!< Transmit interrupt 13/15 full
    SPI_FIFO_TX14       = 0x000EU,      //!< Transmit interrupt 14/15 full
    SPI_FIFO_TX15       = 0x000FU,      //!< Transmit interrupt full
    SPI_FIFO_TXFULL     = 0x000FU       //!< Transmit interrupt full
} SPI_TxFIFOLevel;

//*****************************************************************************
//
//! Values that can be passed to SPI_setFIFOInterruptLevel() as the \e rxLevel
//! parameter and returned by SPI_getFIFOInterruptLevel() in the \e rxLevel.
//
//*****************************************************************************
typedef enum
{
    SPI_FIFO_RXEMPTY    = 0x0000U,      //!< Receive interrupt empty
    SPI_FIFO_RX0        = 0x0000U,      //!< Receive interrupt empty
    SPI_FIFO_RX1        = 0x0001U,      //!< Receive interrupt 1/15 full
    SPI_FIFO_RX2        = 0x0002U,      //!< Receive interrupt 2/15 full
    SPI_FIFO_RX3        = 0x0003U,      //!< Receive interrupt 3/15 full
    SPI_FIFO_RX4        = 0x0004U,      //!< Receive interrupt 4/15 full
    SPI_FIFO_RX5        = 0x0005U,      //!< Receive interrupt 5/15 full
    SPI_FIFO_RX6        = 0x0006U,      //!< Receive interrupt 6/15 full
    SPI_FIFO_RX7        = 0x0007U,      //!< Receive interrupt 7/15 full
    SPI_FIFO_RX8        = 0x0008U,      //!< Receive interrupt 8/15 full
    SPI_FIFO_RX9        = 0x0009U,      //!< Receive interrupt 9/15 full
    SPI_FIFO_RX10       = 0x000AU,      //!< Receive interrupt 10/15 full
    SPI_FIFO_RX11       = 0x000BU,      //!< Receive interrupt 11/15 full
    SPI_FIFO_RX12       = 0x000CU,      //!< Receive interrupt 12/15 full
    SPI_FIFO_RX13       = 0x000DU,      //!< Receive interrupt 13/15 full
    SPI_FIFO_RX14       = 0x000EU,      //!< Receive interrupt 14/15 full
    SPI_FIFO_RX15       = 0x000FU,      //!< Receive interrupt full
    SPI_FIFO_RXFULL     = 0x000FU       //!< Receive interrupt full
} SPI_RxFIFOLevel;

//*****************************************************************************
//
//! Values that can be passed to SPI_setEmulationMode() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Transmission stops after midway in the bit stream
    SPI_EMULATION_STOP_MIDWAY         = 0x0000U,
    //! Continue SPI operation regardless
    SPI_EMULATION_FREE_RUN            = 0x0010U,
    //! Transmission will stop after a started transmission completes
    SPI_EMULATION_STOP_AFTER_TRANSMIT = 0x0020U
} SPI_EmulationMode;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an SPI base address.
//!
//! \param base specifies the SPI module base address.
//!
//! This function determines if a SPI module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
SPI_isBaseValid(uint32_t base)
{
    return((base == SPIA_BASE) || (base == SPIB_BASE));
}
#endif

//*****************************************************************************
//
//! Enables the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//!
//! This function enables operation of the serial peripheral interface.  The
//! serial peripheral interface must be configured before it is enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    HWREGH(base + SPI_O_CCR) |= SPI_CCR_SPISWRESET;
}

//*****************************************************************************
//
//! Disables the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//!
//! This function disables operation of the serial peripheral interface. Call
//! this function before doing any configuration.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    HWREGH(base + SPI_O_CCR) &= ~(SPI_CCR_SPISWRESET);
}

//*****************************************************************************
//
//! Enables the transmit and receive FIFOs.
//!
//! \param base is the base address of the SPI port.
//!
//! This functions enables the transmit and receive FIFOs in the SPI.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_enableFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Enable the FIFO.
    //
    HWREGH(base + SPI_O_FFTX) |= SPI_FFTX_SPIFFENA | SPI_FFTX_TXFIFO;
    HWREGH(base + SPI_O_FFRX) |= SPI_FFRX_RXFIFORESET;
}

//*****************************************************************************
//
//! Disables the transmit and receive FIFOs.
//!
//! \param base is the base address of the SPI port.
//!
//! This functions disables the transmit and receive FIFOs in the SPI.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_disableFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Disable the FIFO.
    //
    HWREGH(base + SPI_O_FFTX) &= ~(SPI_FFTX_SPIFFENA | SPI_FFTX_TXFIFO);
    HWREGH(base + SPI_O_FFRX) &= ~SPI_FFRX_RXFIFORESET;
}

//*****************************************************************************
//
//! Sets the FIFO level at which interrupts are generated.
//!
//! \param base is the base address of the SPI port.
//! \param txLevel is the transmit FIFO interrupt level, specified as
//! \b SPI_FIFO_TX0, \b SPI_FIFO_TX1, \b SPI_FIFO_TX2, . . . or
//! \b SPI_FIFO_TX15.
//! \param rxLevel is the receive FIFO interrupt level, specified as
//! \b SPI_FIFO_RX0, \b SPI_FIFO_RX1, \b SPI_FIFO_RX2, . . . or
//! \b SPI_FIFO_RX15.
//!
//! This function sets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_setFIFOInterruptLevel(uint32_t base, SPI_TxFIFOLevel txLevel,
                          SPI_RxFIFOLevel rxLevel)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Set the FIFO interrupt levels.
    //
    HWREGH(base + SPI_O_FFTX) = (HWREGH(base + SPI_O_FFTX) &
                                 (~SPI_FFTX_TXFFIL_M)) | (uint16_t)txLevel;
    HWREGH(base + SPI_O_FFRX) = (HWREGH(base + SPI_O_FFRX) &
                                 (~SPI_FFRX_RXFFIL_M)) | (uint16_t)rxLevel;
}

//*****************************************************************************
//
//! Gets the FIFO level at which interrupts are generated.
//!
//! \param base is the base address of the SPI port.
//! \param txLevel is a pointer to storage for the transmit FIFO level,
//! returned as one of \b SPI_FIFO_TX0, \b SPI_FIFO_TX1,
//! \b SPI_FIFO_TX2, . . . or \b SPI_FIFO_TX15.
//! \param rxLevel is a pointer to storage for the receive FIFO level,
//! returned as one of \b SPI_FIFO_RX0, \b SPI_FIFO_RX1,
//! \b SPI_FIFO_RX2, . . . or \b SPI_FIFO_RX15.
//!
//! This function gets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_getFIFOInterruptLevel(uint32_t base, SPI_TxFIFOLevel *txLevel,
                          SPI_RxFIFOLevel *rxLevel)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Extract the transmit and receive FIFO levels.
    //
    *txLevel = (SPI_TxFIFOLevel)(HWREGH(base + SPI_O_FFTX) &
                                 SPI_FFTX_TXFFIL_M);
    *rxLevel = (SPI_RxFIFOLevel)(HWREGH(base + SPI_O_FFRX) &
                                 SPI_FFRX_RXFFIL_M);
}

//*****************************************************************************
//
//! Get the transmit FIFO status
//!
//! \param base is the base address of the SPI port.
//!
//! This function gets the current number of words in the transmit FIFO.
//!
//! \return Returns the current number of words in the transmit FIFO specified
//! as one of the following:
//! \b SPI_FIFO_TX0, \b SPI_FIFO_TX1, \b SPI_FIFO_TX2, \b SPI_FIFO_TX3,
//! ..., or \b SPI_FIFO_TX15
//
//*****************************************************************************
static inline SPI_TxFIFOLevel
SPI_getTxFIFOStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Get the current FIFO status
    //
    return((SPI_TxFIFOLevel)((HWREGH(base + SPI_O_FFTX) & SPI_FFTX_TXFFST_M) >>
                             SPI_FFTX_TXFFST_S));
}

//*****************************************************************************
//
//! Get the receive FIFO status
//!
//! \param base is the base address of the SPI port.
//!
//! This function gets the current number of words in the receive FIFO.
//!
//! \return Returns the current number of words in the receive FIFO specified
//! as one of the following:
//! \b SPI_FIFO_RX0, \b SPI_FIFO_RX1, \b SPI_FIFO_RX2, \b SPI_FIFO_RX3,
//! ..., or \b SPI_FIFO_RX15
//
//*****************************************************************************
static inline SPI_RxFIFOLevel
SPI_getRxFIFOStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Get the current FIFO status
    //
    return((SPI_RxFIFOLevel)((HWREGH(base + SPI_O_FFRX) & SPI_FFRX_RXFFST_M) >>
                             SPI_FFRX_RXFFST_S));
}

//*****************************************************************************
//
//! Determines whether the SPI transmitter is busy or not.
//!
//! \param base is the base address of the SPI port.
//!
//! This function allows the caller to determine whether all transmitted bytes
//! have cleared the transmitter hardware.  If \b false is returned, then the
//! transmit FIFO is empty and all bits of the last transmitted word have left
//! the hardware shift register. This function is only valid when operating in
//! FIFO mode.
//!
//! \return Returns \b true if the SPI is transmitting or \b false if all
//! transmissions are complete.
//
//*****************************************************************************
static inline bool
SPI_isBusy(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Determine if the SPI is busy.
    //
    return((HWREGH(base + SPI_O_FFTX) & SPI_FFTX_TXFFST_M) != 0U);
}

//*****************************************************************************
//
//! Puts a data element into the SPI transmit buffer.
//!
//! \param base specifies the SPI module base address.
//! \param data is the left-justified data to be transmitted over SPI.
//!
//! This function places the supplied data into the transmit buffer of the
//! specified SPI module.
//!
//! \note The data being sent must be left-justified in \e data. The lower
//! 16 - N bits will be discarded where N is the data width selected in
//! SPI_setConfig(). For example, if configured for a 6-bit data width, the
//! lower 10 bits of data will be discarded.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_writeDataNonBlocking(uint32_t base, uint16_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Write data to the transmit buffer.
    //
    HWREGH(base + SPI_O_TXBUF) = data;
}

//*****************************************************************************
//
//! Gets a data element from the SPI receive buffer.
//!
//! \param base specifies the SPI module base address.
//!
//! This function gets received data from the receive buffer of the specified
//! SPI module and returns it.
//!
//! \note Only the lower N bits of the value written to \e data contain valid
//! data, where N is the data width as configured by SPI_setConfig(). For
//! example, if the interface is configured for 8-bit data width, only the
//! lower 8 bits of the value written to \e data contain valid data.
//!
//! \return Returns the word of data read from the SPI receive buffer.
//
//*****************************************************************************
static inline uint16_t
SPI_readDataNonBlocking(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Check for data to read.
    //
    return(HWREGH(base + SPI_O_RXBUF));
}

//*****************************************************************************
//
//! Waits for space in the FIFO and then puts data into the transmit buffer.
//!
//! \param base specifies the SPI module base address.
//! \param data is the left-justified data to be transmitted over SPI.
//!
//! This function places the supplied data into the transmit buffer of the
//! specified SPI module once space is available in the transmit FIFO. This
//! function should only be used when the FIFO is enabled.
//!
//! \note The data being sent must be left-justified in \e data. The lower
//! 16 - N bits will be discarded where N is the data width selected in
//! SPI_setConfig(). For example, if configured for a 6-bit data width, the
//! lower 10 bits of data will be discarded.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_writeDataBlockingFIFO(uint32_t base, uint16_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Wait until space is available in the receive FIFO.
    //
    while(SPI_getTxFIFOStatus(base) == SPI_FIFO_TXFULL)
    {
    }

    //
    // Write data to the transmit buffer.
    //
    HWREGH(base + SPI_O_TXBUF) = data;
}

//*****************************************************************************
//
//! Waits for data in the FIFO and then reads it from the receive buffer.
//!
//! \param base specifies the SPI module base address.
//!
//! This function waits until there is data in the receive FIFO and then reads
//! received data from the receive buffer.  This function should only be used
//! when FIFO mode is enabled.
//!
//! \note Only the lower N bits of the value written to \e data contain valid
//! data, where N is the data width as configured by SPI_setConfig(). For
//! example, if the interface is configured for 8-bit data width, only the
//! lower 8 bits of the value written to \e data contain valid data.
//!
//! \return Returns the word of data read from the SPI receive buffer.
//
//*****************************************************************************
static inline uint16_t
SPI_readDataBlockingFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Wait until data is available in the receive FIFO.
    //
    while(SPI_getRxFIFOStatus(base) == SPI_FIFO_RXEMPTY)
    {
    }

    //
    // Check for data to read.
    //
    return(HWREGH(base + SPI_O_RXBUF));
}

//*****************************************************************************
//
//! Waits for the transmit buffer to empty and then writes data to it.
//!
//! \param base specifies the SPI module base address.
//! \param data is the left-justified data to be transmitted over SPI.
//!
//! This function places the supplied data into the transmit buffer of the
//! specified SPI module once it is empty. This function should not be used
//! when FIFO mode is enabled.
//!
//! \note The data being sent must be left-justified in \e data. The lower
//! 16 - N bits will be discarded where N is the data width selected in
//! SPI_setConfig(). For example, if configured for a 6-bit data width, the
//! lower 10 bits of data will be discarded.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_writeDataBlockingNonFIFO(uint32_t base, uint16_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Wait until the transmit buffer is not full.
    //
    while((HWREGH(base + SPI_O_STS) & SPI_STS_BUFFULL_FLAG) != 0U)
    {
    }

    //
    // Write data to the transmit buffer.
    //
    HWREGH(base + SPI_O_TXBUF) = data;
}

//*****************************************************************************
//
//! Waits for data to be received and then reads it from the buffer.
//!
//! \param base specifies the SPI module base address.
//!
//! This function waits for data to be received and then reads it from the
//! receive buffer of the specified SPI module. This function should not be
//! used when FIFO mode is enabled.
//!
//! \note Only the lower N bits of the value written to \e data contain valid
//! data, where N is the data width as configured by SPI_setConfig(). For
//! example, if the interface is configured for 8-bit data width, only the
//! lower 8 bits of the value written to \e data contain valid data.
//!
//! \return Returns the word of data read from the SPI receive buffer.
//
//*****************************************************************************
static inline uint16_t
SPI_readDataBlockingNonFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Wait until data has been received.
    //
    while((HWREGH(base + SPI_O_STS) & SPI_STS_INT_FLAG) == 0U)
    {
    }

    //
    // Check for data to read.
    //
    return(HWREGH(base + SPI_O_RXBUF));
}

//*****************************************************************************
//
//! Enables SPI 3-wire mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function enables 3-wire mode. When in master mode, this allows SPISIMO
//! to become SPIMOMI and SPISOMI to become free for non-SPI use. When in slave
//! mode, SPISOMI because the SPISISO pin and SPISIMO is free for non-SPI use.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_enableTriWire(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Set the tri-wire bit to enable 3-wire mode.
    //
    HWREGH(base + SPI_O_PRI) |= SPI_PRI_TRIWIRE;
}

//*****************************************************************************
//
//! Disables SPI 3-wire mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function disables 3-wire mode. SPI will operate in normal 4-wire mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_disableTriWire(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Clear the tri-wire bit to disable 3-wire mode.
    //
    HWREGH(base + SPI_O_PRI) &= ~SPI_PRI_TRIWIRE;
}

//*****************************************************************************
//
//! Enables SPI loopback mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function enables loopback mode. This mode is only valid during master
//! mode and is helpful during device testing as it internally connects SIMO
//! and SOMI.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_enableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Set the bit that enables loopback mode.
    //
    HWREGH(base + SPI_O_CCR) |= SPI_CCR_SPILBK;
}

//*****************************************************************************
//
//! Disables SPI loopback mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function disables loopback mode. Loopback mode is disabled by default
//! after reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_disableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Clear the bit that enables loopback mode.
    //
    HWREGH(base + SPI_O_CCR) &= ~SPI_CCR_SPILBK;
}

//*****************************************************************************
//
//! Enables SPI high speed mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function enables high speed mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_enableHighSpeedMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Set the bit that enables high speed mode.
    //
    HWREGH(base + SPI_O_CCR) |= SPI_CCR_HS_MODE;
}

//*****************************************************************************
//
//! Disables SPI high speed mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function disables high speed mode. High speed mode is disabled by
//! default after reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_disableHighSpeedMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Clear the bit that enables high speed mode.
    //
    HWREGH(base + SPI_O_CCR) &= ~SPI_CCR_HS_MODE;
}

//*****************************************************************************
//
//! Sets SPI emulation mode.
//!
//! \param base is the base address of the SPI port.
//! \param mode is the emulation mode.
//!
//! This function sets the behavior of the SPI operation when an emulation
//! suspend occurs. The \e mode parameter can be one of the following:
//!
//! - \b SPI_EMULATION_STOP_MIDWAY - Transmission stops midway through the bit
//!   stream. The rest of the bits will be transmitting after the suspend is
//!   deasserted.
//! - \b SPI_EMULATION_STOP_AFTER_TRANSMIT - If the suspend occurs before the
//!   first SPICLK pulse, the transmission will not start. If it occurs later,
//!   the transmission will be completed.
//! - \b SPI_EMULATION_FREE_RUN - SPI operation continues regardless of a
//!   the suspend.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SPI_setEmulationMode(uint32_t base, SPI_EmulationMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Write the desired emulation mode to the register.
    //
    HWREGH(base + SPI_O_PRI) = (HWREGH(base + SPI_O_PRI) &
                                ~(SPI_PRI_FREE | SPI_PRI_SOFT)) |
                               (uint16_t)mode;
}

//*****************************************************************************
//
//! Configures the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//! \param lspclkHz is the rate of the clock supplied to the SPI module
//! (LSPCLK) in Hz.
//! \param protocol specifies the data transfer protocol.
//! \param mode specifies the mode of operation.
//! \param bitRate specifies the clock rate in Hz.
//! \param dataWidth specifies number of bits transferred per frame.
//!
//! This function configures the serial peripheral interface.  It sets the SPI
//! protocol, mode of operation, bit rate, and data width.
//!
//! The \e protocol parameter defines the data frame format.  The \e protocol
//! parameter can be one of the following values: \b SPI_PROT_POL0PHA0,
//! \b SPI_PROT_POL0PHA1, \b SPI_PROT_POL1PHA0, or
//! \b SPI_PROT_POL1PHA1. These frame formats encode the following polarity
//! and phase configurations:
//!
//! <pre>
//! Polarity Phase       Mode
//!   0       0   SPI_PROT_POL0PHA0
//!   0       1   SPI_PROT_POL0PHA1
//!   1       0   SPI_PROT_POL1PHA0
//!   1       1   SPI_PROT_POL1PHA1
//! </pre>
//!
//! The \e mode parameter defines the operating mode of the SPI module.  The
//! SPI module can operate as a master or slave; the SPI can also be be
//! configured to disable output on its serial output line.  The \e mode
//! parameter can be one of the following values: \b SPI_MODE_MASTER,
//! \b SPI_MODE_SLAVE, \b SPI_MODE_MASTER_OD or \b SPI_MODE_SLAVE_OD ("OD"
//! indicates "output disabled").
//!
//! The \e bitRate parameter defines the bit rate for the SPI.  This bit rate
//! must satisfy the following clock ratio criteria:
//!
//! - \e bitRate can be no greater than lspclkHz divided by 4.
//! - \e lspclkHz / \e bitRate cannot be greater than 128.
//!
//! The \e dataWidth parameter defines the width of the data transfers and
//! can be a value between 1 and 16, inclusive.
//!
//! The peripheral clock is the low speed peripheral clock.  This value is
//! returned by SysCtl_getLowSpeedClock(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtl_getLowSpeedClock()).
//!
//! \note SPI operation should be disabled via SPI_disableModule() before any
//! changes to its configuration.
//!
//! \return None.
//
//*****************************************************************************
extern void
SPI_setConfig(uint32_t base, uint32_t lspclkHz, SPI_TransferProtocol protocol,
              SPI_Mode mode, uint32_t bitRate, uint16_t dataWidth);

//*****************************************************************************
//
//! Configures the baud rate of the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//! \param lspclkHz is the rate of the clock supplied to the SPI module
//! (LSPCLK) in Hz.
//! \param bitRate specifies the clock rate in Hz.
//!
//! This function configures the SPI baud rate. The \e bitRate parameter
//! defines the bit rate for the SPI.  This bit rate must satisfy the following
//! clock ratio criteria:
//!
//! - \e bitRate can be no greater than \e lspclkHz divided by 4.
//! - \e lspclkHz / \e bitRate cannot be greater than 128.
//!
//! The peripheral clock is the low speed peripheral clock.  This value is
//! returned by SysCtl_getLowSpeedClock(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtl_getLowSpeedClock()).
//!
//! \note SPI_setConfig() also sets the baud rate. Use SPI_setBaudRate()
//! if you wish to configure it separately from protocol and mode.
//!
//! \return None.
//
//*****************************************************************************
extern void
SPI_setBaudRate(uint32_t base, uint16_t lspclkHz, uint16_t bitRate);

//*****************************************************************************
//
//! Registers a receive interrupt handler for the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//! \param handler is a pointer to the function to be called when the serial
//! peripheral interface interrupt occurs.
//!
//! This function registers the handler to be called when an SPI receive
//! interrupt occurs.  This function enables the global interrupt in the
//! interrupt controller; specific SPI interrupts must be enabled via
//! SPI_enableInterrupt().  If necessary, it is the interrupt handler's
//! responsibility to clear the interrupt source via SPI_clearInterruptStatus().
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
SPI_registerRxInterrupt(uint32_t base, void (*handler)(void));

//*****************************************************************************
//
//! Unregisters a receive interrupt handler for the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//!
//! This function clears the handler to be called when an SPI receive interrupt
//! occurs.  This function also masks off the interrupt in the interrupt
//! controller so that the interrupt handler no longer is called.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
SPI_unregisterRxInterrupt(uint32_t base);

//*****************************************************************************
//
//! Registers a transmit interrupt handler for the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//! \param handler is a pointer to the function to be called when the serial
//! peripheral interface interrupt occurs.
//!
//! This function registers the handler to be called when an SPI transmit
//! interrupt occurs.  This function enables the global interrupt in the
//! interrupt controller; specific SPI interrupts must be enabled via
//! SPI_enableInterrupt().  If necessary, it is the interrupt handler's
//! responsibility to clear the interrupt source via SPI_clearInterruptStatus().
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
SPI_registerTxInterrupt(uint32_t base, void (*handler)(void));

//*****************************************************************************
//
//! Unregisters transmit interrupt handler for the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//!
//! This function clears the handler to be called when an SPI transmit interrupt
//! occurs.  This function also masks off the interrupt in the interrupt
//! controller so that the interrupt handler no longer is called.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void
SPI_unregisterTxInterrupt(uint32_t base);

//*****************************************************************************
//
//! Enables individual SPI interrupt sources.
//!
//! \param base specifies the SPI module base address.
//! \param intFlags is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated SPI interrupt sources.  Only the sources
//! that are enabled can be reflected to the processor interrupt; disabled
//! sources have no effect on the processor.  The \e intFlags parameter can be
//! any of the \b SPI_INT_RX_OVERRUN, \b SPI_INT_RX_DATA_TX_EMPTY,
//! \b SPI_INT_RXFF, or \b SPI_INT_TXFF values.
//!
//! \note \b SPI_INT_RX_OVERRUN, \b SPI_INT_RX_DATA_TX_EMPTY, and
//! \b SPI_INT_RXFF are associated \b SPIRXINT; \b SPI_INT_TXFF is
//! associated with \b SPITXINT.
//!
//! \return None.
//
//*****************************************************************************
extern void
SPI_enableInterrupt(uint32_t base, uint32_t intFlags);

//*****************************************************************************
//
//! Disables individual SPI interrupt sources.
//!
//! \param base specifies the SPI module base address.
//! \param intFlags is a bit mask of the interrupt sources to be disabled.
//!
//! This function disables the indicated SPI interrupt sources.  The
//! \e intFlags parameter can be any of the \b SPI_INT_RX_OVERRUN,
//! \b SPI_INT_RX_DATA_TX_EMPTY, \b SPI_INT_RXFF, or \b SPI_INT_TXFF
//! values.
//!
//! \note \b SPI_INT_RX_OVERRUN, \b SPI_INT_RX_DATA_TX_EMPTY, and
//! \b SPI_INT_RXFF are associated \b SPIRXINT; \b SPI_INT_TXFF is
//! associated with \b SPITXINT.
//!
//! \return None.
//
//*****************************************************************************
extern void
SPI_disableInterrupt(uint32_t base, uint32_t intFlags);

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param base specifies the SPI module base address.
//!
//! This function returns the interrupt status for the SPI module.
//!
//! \return The current interrupt status, enumerated as a bit field of
//! \b SPI_INT_RX_OVERRUN, \b SPI_INT_RX_DATA_TX_EMPTY, \b SPI_INT_RXFF,
//! \b SPI_INT_TXFF values.
//
//*****************************************************************************
extern uint32_t
SPI_getInterruptStatus(uint32_t base);

//*****************************************************************************
//
//! Clears SPI interrupt sources.
//!
//! \param base specifies the SPI module base address.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//!
//! This function clears the specified SPI interrupt sources so that they no
//! longer assert.  This function must be called in the interrupt handler to
//! keep the interrupts from being triggered again immediately upon exit.  The
//! \e intFlags parameter can consist of either or both the
//! \b SPI_INT_RX_OVERRUN, \b SPI_INT_RX_DATA_TX_EMPTY, \b SPI_INT_RXFF,
//! \b SPI_INT_TXFF values
//!
//! \note \b SPI_INT_RX_OVERRUN, \b SPI_INT_RX_DATA_TX_EMPTY, and
//! \b SPI_INT_RXFF are associated \b SPIRXINT; \b SPI_INT_TXFF is
//! associated with \b SPITXINT.
//!
//! \return None.
//
//*****************************************************************************
extern void
SPI_clearInterruptStatus(uint32_t base, uint32_t intFlags);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SPI_H__
