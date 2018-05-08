//###########################################################################
//
// FILE:   lin.c
//
// TITLE:  Stellaris style wrapper driver for C28x LIN peripheral.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

//*****************************************************************************
//
//! \addtogroup lin_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_lin.h"
#include "cpu.h"
#include "debug.h"
#include "interrupt.h"
#include "lin.h"

//*****************************************************************************
//
//! Enables the LIN module.
//!
//! \param base is the LIN module base address
//!
//! This function sets the RESET bit of the SCIGCR0 register. Registers in this
//! module are not writable until this has been done.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Set reset bit.
    //
    EALLOW;

    HWREGH(base + LIN_O_SCIGCR0) |= LIN_SCIGCR0_RESET;

    EDIS;
}

//*****************************************************************************
//
//! Disable the LIN module.
//!
//! \param base is the LIN module base address
//!
//! This function clears the RESET bit of the SCIGCR0 register. Registers in
//! this module are not writable when this bit is cleared.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Clear reset bit.
    //
    EALLOW;

    HWREGH(base + LIN_O_SCIGCR0) &= ~LIN_SCIGCR0_RESET;

    EDIS;
}

//*****************************************************************************
//
//! Sets the LIN node as either a slave or a master
//!
//! \param base is the LIN module base address
//! \param mode is the desired mode--slave or master
//!
//! This function sets the mode of the LIN node to either slave or master. The
//! \e mode parameter should be passed a value of \b LIN_MODE_LIN_SLAVE or
//! \e LIN_MODE_LIN_MASTER to configure the mode of the LIN module specified by
//! \e base.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setLinMode(uint32_t base, LIN_LINMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Write the LIN mode to the appropriate register.
    //
    EALLOW;

    HWREGH(base + LIN_O_SCIGCR1) = (HWREGH(base + LIN_O_SCIGCR1) &
                                   ~LIN_SCIGCR1_CLK_MASTER) | (uint16_t)mode;

    EDIS;
}

//*****************************************************************************
//
//!  Set Baud Rate
//!
//! \param base is the LIN module base address
//! \param baudRate is the value for the baud rate
//!
//! This function is used to select baud rate for SCI/LIN module.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setBaudRate(uint32_t base, uint32_t baudRate)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Setup baud rate prescaler
    //
    HWREG(base + LIN_O_BRSR) = baudRate;
}

//*****************************************************************************
//
//!  Set Maximum Baud Rate Prescaler
//!
//! \param base is the LIN module base address
//! \param prescaler is the value for the maximum baud rate prescaler
//!
//! In LIN mode, this function is used to set the maximum baud rate prescaler.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setMaximumBaudRate(uint32_t base, uint16_t prescaler)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Setup maximum baud rate prescaler
    //
    HWREGH(base + LIN_O_MBRSR) = (HWREGH(base + LIN_O_MBRSR) &
                                  ~LIN_MBRSR_MBR_M) | (prescaler &
                                                       LIN_MBRSR_MBR_M);
}

//*****************************************************************************
//
//! Enable HGENCTRL (Mask filtering with ID-Byte)
//!
//! \param base is the LIN module base address
//!
//! This function enables mask filtering.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enableMaskFiltering(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Enable HGENCTRL (Mask filtering with ID-Byte)
    //
    HWREGH(base + LIN_O_SCIGCR1) &= ~LIN_SCIGCR1_HGENCTRL;
}

//*****************************************************************************
//
//! Enable SCI Mode
//!
//! \param base is the LIN module base address
//!
//! This function enables the LIN peripheral to function as a SCI.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enableSCIMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Enable SCI communications mode
    //
    EALLOW;

    HWREGH(base + LIN_O_SCIGCR1) &= ~LIN_SCIGCR1_LINMODE;
    HWREGH(base + LIN_O_SCIGCR1) |= LIN_SCIGCR1_CLK_MASTER |
                                    LIN_SCIGCR1_TIMINGMODE;

    EDIS;
}

//*****************************************************************************
//
//! Configures the SCI parity settings.
//!
//! \param base is the LIN module base address
//! \param enable is \b true when parity is required and \b false when not
//! required.
//! \param mode is \b true for even parity and \b false for odd parity when in
//! SCI mode.
//!
//! Configures the parity settings when the LIN peripheral is configured as
//! a SCI.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setSCIParity(uint32_t base, bool enable, bool mode)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Configure SCI parity mode
    //
    HWREGH(base + LIN_O_SCIGCR1) &= ~(LIN_SCIGCR1_PARITYENA |
                                      LIN_SCIGCR1_PARITY);

    HWREGH(base + LIN_O_SCIGCR1) |= ((enable ? LIN_SCIGCR1_PARITYENA : 0U) |
                                     (mode ? LIN_SCIGCR1_PARITY : 0U));
}

//*****************************************************************************
//
//! Disable HGENCTRL (Mask filtering with ID-Byte)
//!
//! \param base is the LIN module base address
//!
//! This function disables mask filtering.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_disableMaskFiltering(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Disable HGENCTRL (Mask filtering with ID-Byte)
    //
    HWREGH(base + LIN_O_SCIGCR1) |= LIN_SCIGCR1_HGENCTRL;
}

//*****************************************************************************
//
//! Disable SCI Mode
//!
//! \param base is the LIN module base address
//!
//! This function disables the SCI mode of the LIN peripheral.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_disableSCIMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Disable SCI communications mode
    //
    EALLOW;

    HWREGH(base + LIN_O_SCIGCR1) &= ~(LIN_SCIGCR1_CLK_MASTER |
                                      LIN_SCIGCR1_TIMINGMODE);
    HWREGH(base + LIN_O_SCIGCR1) |= LIN_SCIGCR1_LINMODE;

    EDIS;
}

//*****************************************************************************
//
//! Initializes the LIN Driver
//!
//! \param base is the LIN module base address
//!
//! This function initializes the LIN module.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_initModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    EALLOW;

    //
    // initialize LIN
    // Release from reset
    //
    HWREG(base + LIN_O_SCIGCR0) = LIN_SCIGCR0_RESET;

    //
    // Start LIN configuration
    // Keep state machine in software reset
    // Enable LIN Mode
    //
    HWREG(base + LIN_O_SCIGCR1) = LIN_SCIGCR1_LINMODE;

    //
    // Setup control register 1
    // - Enable transmitter
    // - Enable receiver
    // - Stop when debug mode is entered
    // - Disable Loopback mode
    // - Enable HGENCTRL (Mask filtering with ID-Byte)
    // - Use enhance checksum
    // - Enable multi buffer mode
    // - Disable automatic baudrate adjustment
    // - Disable sleep mode
    // - Set LIN module as master
    // - Disable parity
    // - Disable data length control in ID4 and ID5
    //
    HWREGH(base + LIN_O_SCIGCR1) |=
            LIN_SCIGCR1_CLK_MASTER | LIN_SCIGCR1_HGENCTRL |
            LIN_SCIGCR1_MBUFMODE | LIN_SCIGCR1_CTYPE;

    HWREGH(base + LIN_O_SCIGCR1 + 2) |=
            (LIN_SCIGCR1_TXENA | LIN_SCIGCR1_RXENA) >> 16;

    //
    // Setup maximum baud rate prescaler
    //
    HWREG(base + LIN_O_MBRSR) = 4046U;

    //
    // Setup baud rate prescaler
    //
    HWREG(base + LIN_O_BRSR) = 280U;

    //
    //Setup RX and TX reception masks
    //
    HWREG(base + LIN_O_MASK) = ((uint32_t)0xFFU << 16U) | (uint32_t)0xFFU;

    //
    // Setup compare
    // Sync delimiter
    // Sync break extension
    //
    HWREG(base + LIN_O_COMP) = 0U;

    //
    //  Setup response length to maximum
    //
    HWREGH(base + LIN_O_SCIFORMAT) = (HWREGH(base + LIN_O_SCIFORMAT) &
                                     ~LIN_SCIFORMAT_CHAR_M) | 7U;

    HWREGH(base + LIN_O_SCIFORMAT + 2) = (HWREGH(base + LIN_O_SCIFORMAT) &
                                          ~LIN_SCIFORMAT_LENGTH_M >> 16) | 7U;

    //
    // Set LIN pins functional mode
    // - TX
    // - RXlinREG->FORMAT
    // - CLK
    //
    HWREGH(base + LIN_O_SCIPIO0) = LIN_SCIPIO0_RXFUNC | LIN_SCIPIO0_TXFUNC;

    //
    // Set LIN pins default output value
    // - TX
    // - RX
    // - CLK
    //
    HWREGH(base + LIN_O_SCIPIO3) = 0U;

    // Set LIN pins output direction
    // - TX
    // - RX
    // - CLK
    //
    HWREGH(base + LIN_O_SCIPIO1) = 0U;

    //
    // Set LIN pins open drain enable
    // - TX
    // - RX
    // - CLK
    //
    HWREGH(base + LIN_O_SCIPIO6) = 0U;

    //
    // Set LIN pins pullup/pulldown enable
    // - TX
    // - RX
    // - CLK
    //
    HWREGH(base + LIN_O_SCIPIO7) = 0U;

    //
    // Set LIN pins pullup/pulldown select
    // - TX
    // - RX
    // - CLK
    //
    HWREGH(base + LIN_O_SCIPIO8) = LIN_SCIPIO8_TXPSL | LIN_SCIPIO8_RXPSL | 1U;

    //
    // Set interrupt level
    // - Bit error level
    // - Physical bus error level
    // - Checksum error level
    // - Inconsistent sync field error level
    // - No response error level
    // - Framing error level
    // - Overrun error level
    // - Parity error level
    // - Identifier level
    // - RX level
    // - TX level
    // - Timeout after 3 wakeup signals level
    // - Timeout after wakeup signal level
    // - Timeout level
    // - Wakeup level
    // - Break detect level
    //
    HWREG(base + LIN_O_SCISETINTLVL) = 0U;

    //
    // Set interrupt enable
    // - Disable bit error
    // - Disable physical bus error level
    // - Disable checksum error level
    // - Disable inconsistent sync field error level
    // - Disable no response error level
    // - Disable framing error level
    // - Disable overrun error level
    // - Disable parity error level
    // - Disable identifier level
    // - Disable RX level
    // - Disable TX level
    // - Disable timeout after 3 wakeup signals level
    // - Disable timeout after wakeup signal level
    // - Disable timeout level
    // - Disable wakeup level
    // - Disable break detect level
    //
    HWREG(base + LIN_O_SCISETINT) = 0U;

    //
    // Finally start LIN
    //
    HWREG(base + LIN_O_SCIGCR1) |= LIN_SCIGCR1_SWNRST;

    EDIS;
}

//*****************************************************************************
//
//! Change functional behavior of pins at runtime.
//!
//! \param base is the LIN module base address
//! \param port is the value to write to PIO0 register
//!
//! This function change the value of the PCFUN register at runtime, this
//! allows to dynamically change the functionality of the LIN pins between
//! functional and GIO mode.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setFunctional(uint32_t base, uint32_t port)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREG(base + LIN_O_SCIPIO0) = port;
}

//*****************************************************************************
//
//!  Send LIN header.
//!
//! \param base is the LIN module base address
//! \param identifier is the LIN header id
//!
//! Send LIN header including sync break field, sync field and identifier.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_sendHeader(uint32_t base, uint16_t identifier)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_ID) = (HWREGH(base + LIN_O_ID) & ~(LIN_ID_IDBYTE_M)) |
                              identifier;
}

//*****************************************************************************
//
//!  Set ID-SlaveTask
//!
//! \param base is the LIN module base address
//! \param identifier is the Received ID comparison ID
//!
//! Set the identifier to which the received ID of an incoming Header will be
//! compared in order to decide whether a RX response.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setIDSlaveTask(uint32_t base, uint16_t identifier)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_ID) = (HWREGH(base + LIN_O_ID) &
                               ~(LIN_ID_IDSLAVETASKBYTE_M)) |
                              (identifier << LIN_ID_IDSLAVETASKBYTE_S);
}

//*****************************************************************************
//
//!  Send LIN wakeup signal
//!
//! \param base is the LIN module base address
//!
//! Send LIN wakeup signal to terminate the sleep mode of any LIN node
//! connected to the BUS.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_sendWakeupSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGB(base + LIN_O_TD0 + 3) = 0xF0U;
    HWREGH(base + LIN_O_SCIGCR2) |= LIN_SCIGCR2_GENWU;
}

//*****************************************************************************
//
//!  Take Module to Sleep.
//!
//! \param base is the LIN module base address
//!
//! Application must call this function to take Module to Sleep when Sleep
//! command is received.
//! This function can also be called to forcefully enter Sleep when no activity
//! on BUS.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enterSleep(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIGCR2) |= LIN_SCIGCR2_POWERDOWN;
}

//*****************************************************************************
//
//!  Perform software reset.
//!
//! \param base is the LIN module base address
//!
//! This function will reset the LIN state machine and clear all pending flags.
//! It is required to call this function after a wakeup signal has been sent.
//!
//! To enter the reset state separately, use LIN_enterResetState(). To come
//! out of reset, use LIN_enterReadyState().
//!
//! \return None.
//
//*****************************************************************************
void
LIN_softwareReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIGCR1) &= ~(LIN_SCIGCR1_SWNRST);
    HWREGH(base + LIN_O_SCIGCR1) |= LIN_SCIGCR1_SWNRST;
}

//*****************************************************************************
//
//!  Put LIN into its reset state.
//!
//! \param base is the LIN module base address
//!
//! This function will reset the LIN state machine and clear all pending flags.
//! It is required to call this function after a wakeup signal has been sent.
//! When in this state, changes to the configuration of this module may be
//! made.
//!
//! To take LIN out of the reset state and back into the ready state, use
//! LIN_enterReadyState().
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enterResetState(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIGCR1) &= ~(LIN_SCIGCR1_SWNRST);
}

//*****************************************************************************
//
//!  Put LIN into its ready state.
//!
//! \param base is the LIN module base address
//!
//! This function will put LIN into its ready state. Transmission and reception
//! can be done in this state. While in the ready state, configuration of the
//! module should not be changed.
//!
//! To put the module into its reset state, use LIN_enterResetState().
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enterReadyState(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIGCR1) |= LIN_SCIGCR1_SWNRST;
}

//*****************************************************************************
//
//!  Check if Tx buffer empty
//!
//! \param base is the LIN module base address
//!
//! Checks to see if the Tx buffer ready flag is set, returns
//! 0 if the flags are not set otherwise will return the Tx flag itself.
//!
//! \return Returns the TX ready flag
//
//*****************************************************************************
uint32_t
LIN_isTxReady(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    return(HWREGH(base + LIN_O_SCIFLR) & LIN_SCIFLR_TXRDY);
}

//*****************************************************************************
//
//!  Set frame length
//!
//! \param base is the LIN module base address
//! \param length is the number of data words in bytes. Range: 1-8.
//!
//! Send data response length in bytes.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setLength(uint32_t base, uint32_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIFORMAT + 2) = (HWREGH(base + LIN_O_SCIFORMAT) &
                                          ~LIN_SCIFORMAT_LENGTH_M >> 16) |
                                         (length - 1U);

}

//*****************************************************************************
//
//!  Set character length
//!
//! \param base is the LIN module base address
//! \param numBits is the number of bits per character. Range: 1-8.
//!
//! Set the number of bits per character in SCI mode.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setCharLength(uint32_t base, uint32_t numBits)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIFORMAT) = (HWREGH(base + LIN_O_SCIFORMAT) &
                                     ~LIN_SCIFORMAT_CHAR_M) | (numBits - 1U);
}

//*****************************************************************************
//
//!  Set communication mode
//!
//! \param base is the LIN module base address
//! \param mode is the selected communication mode
//!
//! This function sets the communication mode of the module.
//!
//! In LIN mode, this function is used to choose how the length of data is
//! conveyed. This choice relates to the version of LIN being used. The \e mode
//! parameter can have one of two values:
//! - \b LIN_COMM_LIN_USELENGTHVAL will use the length set with the
//!   LIN_setLength() function.
//! - \b LIN_COMM_LIN_ID4ID5LENCTL will use ID4 and ID5 for length control.
//!
//! In SCI mode, this function is used to choice between idle-line mode and
//! address-bit mode. The \e mode parameter can have one of the following
//! values:
//! - \b LIN_COMM_SCI_IDLELINE for idle-line mode.
//! - \b LIN_COMM_SCI_ADDRBIT for address-bit mode.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setCommMode(uint32_t base, LIN_CommMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Write communication mode selection to the appropriate bit.
    //
    HWREGH(base + LIN_O_SCIGCR1) = (HWREGH(base + LIN_O_SCIGCR1) &
                                    ~LIN_SCIGCR1_COMMMODE) | mode;
}

//*****************************************************************************
//
//!  Sets the transmit and receive ID masks
//!
//! \param base is the LIN module base address
//! \param txMask is the 8-bit mask to be used as the transmit ID mask
//! \param rxMask is the 8-bit mask to be used as the receive ID mask
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setMasks(uint32_t base, uint16_t txMask, uint16_t rxMask)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREG(base + LIN_O_MASK) = ((uint32_t)txMask |
                                ((uint32_t)rxMask <<
                                 LIN_MASK_RXIDMASK_S));
}

//*****************************************************************************
//
//!  Send Data
//!
//! \param base is the LIN module base address
//! \param data is the pointer to data to send
//!
//! Send a block of data pointed to by 'data'.
//! The number of data to transmit must be set with LIN_setLength() before.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_sendData(uint32_t base, uint16_t *data)
{
    int16_t i;
    uint16_t length;
    uint16_t *pData;

    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Get the length from the SCIFORMAT register.
    //
    length = HWREGH(base + LIN_O_SCIFORMAT + 2);

    pData = data + length;

    //
    // Shift each 8-bit piece of data into the correct register.
    //
    for(i = (int32_t)length; i >= 0; i--)
    {
        HWREGB(base + LIN_O_TD0 + (i ^ 3)) = *pData;

        pData--;
    }
}

//*****************************************************************************
//
//!  Check if Rx buffer full
//!
//! \param base is the LIN module base address
//!
//! Checks to see if the Rx buffer full flag is set, returns
//! 0 is flags not set otherwise will return the Rx flag itself.
//!
//! \return Returns the Rx Ready Flag
//
//*****************************************************************************
uint32_t
LIN_isRxReady(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    return(HWREGH(base + LIN_O_SCIFLR) & LIN_SCIFLR_RXRDY);
}

//*****************************************************************************
//
//!  Return Tx and Rx Error flags
//!
//! \param base is the LIN module base address
//!
//!  Returns the bit, physical bus, checksum, inconsistent sync field,
//!  no response, framing, overrun, parity and timeout error flags.
//!  It also clears the error flags before returning.
//!
//! \return Returns the bit, physical bus, checksum, inconsistent sync field,
//!  no response, framing, overrun, parity and timeout error flags.
//
//*****************************************************************************
uint32_t
LIN_getTxRxErrorStatus(uint32_t base)
{
    uint32_t status;

    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    status = HWREG(base + LIN_O_SCIFLR) & (LIN_BE_INT | LIN_PBE_INT |
                                           LIN_CE_INT | LIN_ISFE_INT |
                                           LIN_NRE_INT | LIN_FE_INT |
                                           LIN_OE_INT | LIN_PE_INT |
                                           LIN_TOA3WUS_INT | LIN_TOAWUS_INT |
                                           LIN_TO_INT);

    HWREG(base + LIN_O_SCIFLR) = (LIN_BE_INT | LIN_PBE_INT | LIN_CE_INT |
                                  LIN_ISFE_INT | LIN_NRE_INT | LIN_FE_INT |
                                  LIN_OE_INT | LIN_PE_INT | LIN_TOA3WUS_INT |
                                  LIN_TOAWUS_INT | LIN_TO_INT);

    return(status);
}

//*****************************************************************************
//
//!  Get last received identifier
//!
//! \param base is the LIN module base address
//!
//! Read last received identifier.
//!
//! \return Identifier
//
//*****************************************************************************
uint32_t
LIN_getIdentifier(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    return(HWREGH(base + LIN_O_ID + 2) & (LIN_ID_RECEIVEDID_M >> 16));
}

//*****************************************************************************
//
//!  Read received data
//!
//! \param base is the LIN module base address
//! \param data is the pointer to the data buffer
//!
//! Read a block of bytes and place it into the data buffer pointed to by
//! 'data'.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_getData(uint32_t base, uint16_t * const data)
{
    uint16_t i;
    uint16_t length;
    uint16_t *pData = data;

    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Get the length from the SCIFORMAT register.
    //
    length = HWREGH(base + LIN_O_SCIFORMAT + 2);

    //
    // Read each 8-bit piece of data.
    //
    for(i = 0U; i <= length; i++)
    {
        *pData = HWREGB(base + LIN_O_RD0 + (i ^ 3));

        pData++;
    }
}

//*****************************************************************************
//
//!  Enable Loopback mode for self test
//!
//! \param base is the LIN module base address
//! \param loopbackType is either \b LIN_LOOPBACK_DIGITAL or
//! \b LIN_LOOPBACK_ANALOG
//!
//! This function enables the Loopback mode for self test.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enableLoopback(uint32_t base, LIN_LoopbackType loopbackType)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Clear Loopback in case enabled already
    //
    EALLOW;

    HWREGH(base + LIN_O_IODFTCTRL) &= ~(LIN_IODFTCTRL_IODFTENA_M |
                                        LIN_IODFTCTRL_LPBENA);

    //
    // Enable Loopback either in Analog or Digital Mode
    //
    HWREGH(base + LIN_O_IODFTCTRL) |= (0xAU << LIN_IODFTCTRL_IODFTENA_S) |
                                      (uint16_t)loopbackType;

    EDIS;
}

//*****************************************************************************
//
//!  Disable Loopback mode for self test
//!
//! \param base is the LIN module base address
//!
//! This function disables the Loopback mode.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_disableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    //Disable Loopback Mode
    //
    EALLOW;

    HWREGH(base + LIN_O_IODFTCTRL) &= ~(LIN_IODFTCTRL_IODFTENA_M |
                                        LIN_IODFTCTRL_LPBENA);

    EDIS;
}

//*****************************************************************************
//
//!  Enable interrupts
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b LIN_BE_INT       - bit error
//! - \b LIN_PBE_INT      - physical bus error
//! - \b LIN_CE_INT       - checksum error
//! - \b LIN_ISFE_INT     - inconsistent sync field error
//! - \b LIN_NRE_INT      - no response error
//! - \b LIN_FE_INT       - framing error
//! - \b LIN_OE_INT       - overrun error
//! - \b LIN_PE_INT       - parity error
//! - \b LIN_RXDMAALL_INT - all receiver DMA request
//! - \b LIN_RXDMA_INT    - receiver DMA request
//! - \b LIN_TXDMA_INT    - transmit DMA request
//! - \b LIN_ID_INT       - received matching identifier
//! - \b LIN_RX_INT       - receive buffer ready
//! - \b LIN_TOA3WUS_INT  - time out after 3 wakeup signals
//! - \b LIN_TOAWUS_INT   - time out after wakeup signal
//! - \b LIN_TO_INT       - time out signal
//! - \b LIN_WAKEUP_INT   - wakeup
//! - \b LIN_BREAK_INT    - break detect
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREG(base + LIN_O_SCISETINT) = intFlags;
}

//*****************************************************************************
//
//!  Disable interrupts
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b LIN_BE_INT       - bit error
//! - \b LIN_PBE_INT      - physical bus error
//! - \b LIN_CE_INT       - checksum error
//! - \b LIN_ISFE_INT     - inconsistent sync field error
//! - \b LIN_NRE_INT      - no response error
//! - \b LIN_FE_INT       - framing error
//! - \b LIN_OE_INT       - overrun error
//! - \b LIN_PE_INT       - parity error
//! - \b LIN_RXDMAALL_INT - all receiver DMA request
//! - \b LIN_RXDMA_INT    - receiver DMA request
//! - \b LIN_TXDMA_INT    - transmit DMA request
//! - \b LIN_ID_INT       - received matching identifier
//! - \b LIN_RX_INT       - receive buffer ready
//! - \b LIN_TOA3WUS_INT  - time out after 3 wakeup signals
//! - \b LIN_TOAWUS_INT   - time out after wakeup signal
//! - \b LIN_TO_INT       - time out signal
//! - \b LIN_WAKEUP_INT   - wakeup
//! - \b LIN_BREAK_INT    - break detect
//!
//! \return None.
//
//*****************************************************************************
void
LIN_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREG(base + LIN_O_SCICLEARINT) = intFlags;
}

//*****************************************************************************
//
//!  Clear interrupt status
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of the interrupt sources to be cleared.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b LIN_BE_INT      - bit error
//! - \b LIN_PBE_INT     - physical bus error
//! - \b LIN_CE_INT      - checksum error
//! - \b LIN_ISFE_INT    - inconsistent sync field error
//! - \b LIN_NRE_INT     - no response error
//! - \b LIN_FE_INT      - framing error
//! - \b LIN_OE_INT      - overrun error
//! - \b LIN_PE_INT      - parity error
//! - \b LIN_ID_INT      - received matching identifier
//! - \b LIN_RX_INT      - receive buffer ready
//! - \b LIN_TOA3WUS_INT - time out after 3 wakeup signals
//! - \b LIN_TOAWUS_INT  - time out after wakeup signal
//! - \b LIN_TO_INT      - time out signal
//! - \b LIN_WAKEUP_INT  - wakeup
//! - \b LIN_BREAK_INT   - break detect
//!
//! \return None.
//
//*****************************************************************************
void
LIN_clearInterruptStatus(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREG(base + LIN_O_SCIFLR) = intFlags;
}

//*****************************************************************************
//
//!  Get interrupt status
//!
//! \param base is the LIN module base address
//!
//! This returns the interrupt status for the specified LIN module.
//!
//! \return Returns a bitwise OR of the following flags if they've been set:
//! - \b LIN_BE_INT      - bit error
//! - \b LIN_PBE_INT     - physical bus error
//! - \b LIN_CE_INT      - checksum error
//! - \b LIN_ISFE_INT    - inconsistent sync field error
//! - \b LIN_NRE_INT     - no response error
//! - \b LIN_FE_INT      - framing error
//! - \b LIN_OE_INT      - overrun error
//! - \b LIN_PE_INT      - parity error
//! - \b LIN_ID_INT      - received matching identifier
//! - \b LIN_RX_INT      - receive buffer ready
//! - \b LIN_TOA3WUS_INT - time out after 3 wakeup signals
//! - \b LIN_TOAWUS_INT  - time out after wakeup signal
//! - \b LIN_TO_INT      - time out signal
//! - \b LIN_WAKEUP_INT  - wakeup
//! - \b LIN_BREAK_INT   - break detect
//
//*****************************************************************************
uint32_t
LIN_getInterruptStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    return(HWREG(base + LIN_O_SCIFLR));
}

//*****************************************************************************
//
//!  Set interrupt level
//!
//! \param base is the LIN module base address
//! \param intFlags is the bit mask of interrupt sources to be configured
//! \param setToLvl1 is the flag to indicate to which level the specified
//! interrupts will be set. If \b true, level 1; if \b false, level 0.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//! - \b LIN_BE_INT       - bit error
//! - \b LIN_PBE_INT      - physical bus error
//! - \b LIN_CE_INT       - checksum error
//! - \b LIN_ISFE_INT     - inconsistent sync field error
//! - \b LIN_NRE_INT      - no response error
//! - \b LIN_FE_INT       - framing error
//! - \b LIN_OE_INT       - overrun error
//! - \b LIN_PE_INT       - parity error
//! - \b LIN_RXDMAALL_INT - all receiver DMA request
//! - \b LIN_ID_INT       - received matching identifier
//! - \b LIN_RX_INT       - receive buffer ready
//! - \b LIN_TOA3WUS_INT  - time out after 3 wakeup signals
//! - \b LIN_TOAWUS_INT   - time out after wakeup signal
//! - \b LIN_TO_INT       - time out signal
//! - \b LIN_WAKEUP_INT   - wakeup
//! - \b LIN_BREAK_INT    - break detect
//!
//! \return None.
//
//*****************************************************************************
void
LIN_setInterruptLevel(uint32_t base, uint32_t intFlags, bool setToLvl1)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    if(setToLvl1)
    {
        HWREG(base + LIN_O_SCISETINTLVL) = intFlags;
    }
    else
    {
        HWREG(base + LIN_O_SCICLEARINTLVL) = intFlags;
    }
}

//*****************************************************************************
//
//!  Get the initial or current values of the LIN configuration registers
//!
//! \param base is the LIN module base address
//! \param *configReg is a pointer to the struct to which the initial or
//! current value of the configuration registers need to be stored.
//! \param type sets whether initial or current value of the configuration
//! registers are stored.
//! - \b LIN_CONFIG_INITIAL_VALUE - initial value of the configuration
//! registers will be stored in the struct pointed by configReg
//! - \b LIN_CONFIG_CURRENT_VALUE - current value of the configuration
//! registers will be stored in the struct pointed by configReg
//!
//! This function will copy the initial or current value (depending on the
//! parameter 'type') of the configuration registers to the struct pointed by
//! \e configReg.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_getConfigValue(uint32_t base, LIN_ConfigReg *configReg,
                   LIN_ConfigValue type)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    if (type == LIN_CONFIG_INITIAL_VALUE)
    {
        configReg->CONFIG_GCR0      = LIN_GCR0_CONFIGVALUE;
        configReg->CONFIG_GCR1      = LIN_GCR1_CONFIGVALUE;
        configReg->CONFIG_GCR2      = LIN_GCR2_CONFIGVALUE;
        configReg->CONFIG_SETINT    = LIN_SETINT_CONFIGVALUE;
        configReg->CONFIG_SETINTLVL = LIN_SETINTLVL_CONFIGVALUE;
        configReg->CONFIG_FORMAT    = LIN_FORMAT_CONFIGVALUE;
        configReg->CONFIG_BRSR      = LIN_BRSR_CONFIGVALUE;
        configReg->CONFIG_FUN       = LIN_FUN_CONFIGVALUE;
        configReg->CONFIG_DIR       = LIN_DIR_CONFIGVALUE;
        configReg->CONFIG_ODR       = LIN_ODR_CONFIGVALUE;
        configReg->CONFIG_PD        = LIN_PD_CONFIGVALUE;
        configReg->CONFIG_PSL       = LIN_PSL_CONFIGVALUE;
        configReg->CONFIG_COMP      = LIN_COMP_CONFIGVALUE;
        configReg->CONFIG_MASK      = LIN_MASK_CONFIGVALUE;
        configReg->CONFIG_MBRSR     = LIN_MBRSR_CONFIGVALUE;
    }
    else
    {
        configReg->CONFIG_GCR0      = HWREG(base + LIN_O_SCIGCR0);
        configReg->CONFIG_GCR1      = HWREG(base + LIN_O_SCIGCR1);
        configReg->CONFIG_GCR2      = HWREG(base + LIN_O_SCIGCR2);
        configReg->CONFIG_SETINT    = HWREG(base + LIN_O_SCISETINT);
        configReg->CONFIG_SETINTLVL = HWREG(base + LIN_O_SCISETINTLVL);
        configReg->CONFIG_FORMAT    = HWREG(base + LIN_O_SCIFORMAT);
        configReg->CONFIG_BRSR      = HWREG(base + LIN_O_BRSR);
        configReg->CONFIG_FUN       = HWREG(base + LIN_O_SCIPIO0);
        configReg->CONFIG_DIR       = HWREG(base + LIN_O_SCIPIO1);
        configReg->CONFIG_ODR       = HWREG(base + LIN_O_SCIPIO6);
        configReg->CONFIG_PD        = HWREG(base + LIN_O_SCIPIO7);
        configReg->CONFIG_PSL       = HWREG(base + LIN_O_SCIPIO8);
        configReg->CONFIG_COMP      = HWREG(base + LIN_O_COMP);
        configReg->CONFIG_MASK      = HWREG(base + LIN_O_MASK);
        configReg->CONFIG_MBRSR     = HWREG(base + LIN_O_MBRSR);
    }
}

//*****************************************************************************
//
//!  Gets the Interrupt Vector Offset
//!
//! \param base is the LIN module base address
//! \param line is specified interrupt vector line
//!
//! This function gets the offset for interrupt line specified. A read to the
//! specified line register updates its value to the next highest priority
//! pending interrupt in the flag register and clears the flag corresponding to
//! the offset that was read.
//!
//! The \e line parameter can be one of the following enumerated values:
//! - \b LIN_INTERRUPT_LINE0      - Interrupt Vector Line 0
//! - \b LIN_INTERRUPT_LINE1      - Interrupt Vector Line 1
//!
//! \note The flags for the receive and the transmit interrupts cannot be
//! cleared by reading the corresponding offset vector in this function.
//!
//! \return Returns the interrupt vector offset for the specified interrupt
//! line.
//
//*****************************************************************************
uint32_t
LIN_getInterruptOffset(uint32_t base, LIN_InterruptLine line)
{
    uint32_t offset;

    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Get interrupt vector line offset
    //
    if (line == LIN_INTERRUPT_LINE0)
    {
        offset = HWREGH(base + LIN_O_SCIINTVECT0) & LIN_SCIINTVECT0_INTVECT0_M;
    }
    else
    {
        offset = HWREGH(base + LIN_O_SCIINTVECT1) & LIN_SCIINTVECT1_INTVECT1_M;
    }

    return offset;
}

//*****************************************************************************
//
//!  Enable Multi-buffer Mode
//!
//! \param base is the LIN module base address
//!
//! In LIN and SCI modes only, this function enables the multi-buffer mode.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enableMultibufferMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIGCR1) |= LIN_SCIGCR1_MBUFMODE;
}

//*****************************************************************************
//
//!  Disable Multi-buffer Mode
//!
//! \param base is the LIN module base address
//!
//! This function disables the multi-buffer mode.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_disableMultibufferMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIGCR1) &= ~LIN_SCIGCR1_MBUFMODE;
}

//*****************************************************************************
//
//!  Enable Checksum Type
//!
//! \param base is the LIN module base address
//!
//! In LIN mode only, this function enables the checksum type.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enableChecksum(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIGCR1) |= LIN_SCIGCR1_CTYPE;
}

//*****************************************************************************
//
//!  Disable Checksum Type
//!
//! \param base is the LIN module base address
//!
//! This function disables the checksum type.
//!
//! \return None.
//
//*****************************************************************************
void
LIN_disableChecksum(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_SCIGCR1) &= ~LIN_SCIGCR1_CTYPE;
}

//*****************************************************************************
//
//! Enables a LIN global interrupt.
//!
//! \param base is the LIN module base address
//! \param line is specified interrupt vector line
//!
//! This function globally enables an interrupt corresponding to a specified
//! interrupt line. The \e line parameter can be one of the following
//! enumerated values:
//!
//! - \b LIN_INTERRUPT_LINE0      - Interrupt Vector Line 0
//! - \b LIN_INTERRUPT_LINE1      - Interrupt Vector Line 1
//!
//! \return None.
//
//*****************************************************************************
void
LIN_enableGlobalInterrupt(uint32_t base, LIN_InterruptLine line)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_GLB_INT_EN) |= 0x1U << (uint16_t)line;
}

//*****************************************************************************
//
//! Disables a LIN global interrupt.
//!
//! \param base is the LIN module base address
//! \param line is specified interrupt vector line
//!
//! This function globally disables an interrupt corresponding to a specified
//! interrupt line. The \e line parameter can be one of the following
//! enumerated values:
//!
//! - \b LIN_INTERRUPT_LINE0      - Interrupt Vector Line 0
//! - \b LIN_INTERRUPT_LINE1      - Interrupt Vector Line 1
//!
//! \return None.
//
//*****************************************************************************
void
LIN_disableGlobalInterrupt(uint32_t base, LIN_InterruptLine line)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_GLB_INT_EN) &= ~(0x1U << (uint16_t)line);
}

//*****************************************************************************
//
//! Clears a LIN global interrupt flag.
//!
//! \param base is the LIN module base address
//! \param line is specified interrupt vector line
//!
//! This function clears the global interrupt flag that corresponds to a
//! specified interrupt line. The \e line parameter can be one of the following
//! enumerated values:
//!
//! - \b LIN_INTERRUPT_LINE0      - Interrupt Vector Line 0
//! - \b LIN_INTERRUPT_LINE1      - Interrupt Vector Line 1
//!
//! \return None.
//
//*****************************************************************************
void
LIN_clearGlobalInterruptStatus(uint32_t base, LIN_InterruptLine line)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    HWREGH(base + LIN_O_GLB_INT_CLR) |= 0x1U << (uint16_t)line;
}

//*****************************************************************************
//
//! Returns a LIN global interrupt flag status.
//!
//! \param base is the LIN module base address
//! \param line is specified interrupt vector line
//!
//! This function returns the status of a global interrupt flag that
//! corresponds to a specified interrupt line. The \e line parameter can be one
//! of the following enumerated values:
//!
//! - \b LIN_INTERRUPT_LINE0      - Interrupt Vector Line 0
//! - \b LIN_INTERRUPT_LINE1      - Interrupt Vector Line 1
//!
//! \return Returns \b true if the interrupt flag is set. Return \b false if
//!  not.
//
//*****************************************************************************
bool
LIN_getGlobalInterruptStatus(uint32_t base, LIN_InterruptLine line)
{
    //
    // Check the arguments.
    //
    ASSERT(base == LINA_BASE);

    //
    // Read the flag register and return true if the specified flag is set.
    //
    if(HWREGH(base + LIN_O_GLB_INT_FLG) == (0x1U << (uint16_t)line))
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
