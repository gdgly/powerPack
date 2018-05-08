//###########################################################################
//
// FILE:    hw_fsi.h
//
// TITLE:   Definitions for the FSI registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __HW_FSI_H__
#define __HW_FSI_H__

//*****************************************************************************
//
// The following are defines for the FSI register offsets
//
//*****************************************************************************
#define FSI_O_TX_MASTER_CTRL      0x0U         // Transmit master control
                                               // register
#define FSI_O_TX_CLK_CTRL         0x2U         // Transmit clock control
                                               // register
#define FSI_O_TX_OPER_CTRL_LO     0x4U         // Transmit operation control
                                               // register low
#define FSI_O_TX_OPER_CTRL_HI     0x5U         // Transmit operation control
                                               // register high
#define FSI_O_TX_PACKET_CTRL      0x6U         // Transmit packet/frame control
                                               // register
#define FSI_O_TX_PACKET_UDATA_TAG  0x7U         // Transmit packet/frame tag and
                                               // user data register
#define FSI_O_TX_BUF_PTR_LOAD     0x8U         // Transmit Buffer pointer
                                               // control load register
#define FSI_O_TX_BUF_PTR_STATUS   0x9U         // Transmit Buffer pointer
                                               // control status register
#define FSI_O_TX_PING_CTRL        0xAU         // Transmit PING control
                                               // register
#define FSI_O_TX_PING_TAG         0xBU         // Transmit PING tag register
#define FSI_O_TX_PING_TIMEOUT_REF  0xCU         // Transmit PING timeout counter
                                               // reference
#define FSI_O_TX_PING_TIMEOUT_COUNT  0xEU         // Transmit PING timeout current
                                               // count
#define FSI_O_TX_INTR_EVENT_CTRL  0x10U        // Transmit Interrupt Event
                                               // control register
#define FSI_O_TX_DMA_EVENT_CTRL   0x11U        // Transmit  DMA Event control
                                               // register
#define FSI_O_TX_LOCK_CTRL        0x12U        // Transmit Lock control
                                               // register
#define FSI_O_TX_EVT_ERR_STATUS   0x14U        // Transmit Event and Error
                                               // status flag register
#define FSI_O_TX_EVT_ERR_CLEAR    0x16U        // Transmit Event and Error
                                               // clearing register
#define FSI_O_TX_EVT_ERR_SET      0x17U        // Transmit Event and Error flag
                                               // set register
#define FSI_O_TX_USER_DEFINED_CRC  0x18U        // Transmit User defined CRC
#define FSI_O_TX_ECC_DATA         0x20U        // Transmit ECC data register
#define FSI_O_TX_ECC_VALUE        0x22U        // Transmit ECC value register
#define FSI_O_TX_BUF_BASE         0x40U        // Base address for transmit
                                               // buffer
#define FSI_O_RX_MASTER_CTRL      0x0U         // Receive master control
                                               // register
#define FSI_O_RX_OPER_CTRL        0x4U         // Receive operation control
                                               // register
#define FSI_O_RX_PACKET_INFO      0x6U         // Receive packet/frame control
                                               // register
#define FSI_O_RX_PACKET_UDATA_TAG  0x7U         // Receive packet user data and
                                               // tag info
#define FSI_O_RX_DMA_EVENT_CTRL   0x8U         // Receive DMA Event control
                                               // register
#define FSI_O_RX_EVT_ERR_STATUS   0xAU         // Receive Event and Error
                                               // status flag register
#define FSI_O_RX_CRC_INFO         0xBU         // Receive CRC info of received
                                               // and computed CRC
#define FSI_O_RX_EVT_ERR_CLEAR    0xCU         // Receive Event and Error
                                               // clearing register
#define FSI_O_RX_EVT_ERR_SET      0xDU         // Receive Event and Error flag
                                               // set register
#define FSI_O_RX_BUF_PTR_LOAD     0xEU         // Receive Buffer pointer load
                                               // register
#define FSI_O_RX_BUF_PTR_STATUS   0xFU         // Receive Buffer pointer status
                                               // register
#define FSI_O_RX_FRAME_WD_CTRL    0x10U        // Receive FRAME watchdog
                                               // control register
#define FSI_O_RX_FRAME_WD_REF     0x12U        // Receive FRAME watchdog
                                               // counter reference
#define FSI_O_RX_FRAME_WD_COUNT   0x14U        // Receive FRAME watchdog
                                               // current count
#define FSI_O_RX_PING_WD_CTRL     0x16U        // Receive PING watchdog control
                                               // register
#define FSI_O_RX_PING_TAG         0x17U        // Receive PING tag register
#define FSI_O_RX_PING_WD_REF      0x18U        // Receive PING watchdog counter
                                               // reference
#define FSI_O_RX_PING_WD_COUNT    0x1AU        // Receive PING watchdog current
                                               // count
#define FSI_O_RX_INTR_EVENT_CTRL_1  0x1CU        // Receive Interrupt control
                                               // register for RX_INT1N
#define FSI_O_RX_INTR_EVENT_CTRL_2  0x1DU        // Receive Interrupt control
                                               // register for RX_INT2N
#define FSI_O_RX_LOCK_CTRL        0x1EU        // Receive Lock control register
#define FSI_O_RX_ECC_DATA         0x20U        // Receive ECC data register
#define FSI_O_RX_ECC_VALUE        0x22U        // Receive ECC value register
#define FSI_O_RX_ECC_CORRECTED_DATA  0x24U        // Receive ECC corrected data
                                               // register
#define FSI_O_RX_ECC_LOG          0x26U        // Receive ECC log and status
                                               // register
#define FSI_O_RX_DLYLINE_CTRL     0x30U        // Receive Delay Line control
                                               // register
#define FSI_O_RX_VIS_1            0x38U        // Receive Debug visibility
                                               // register 1
#define FSI_O_RX_BUF_BASE         0x40U        // Base Address for receive data
                                               // buffer

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_MASTER_CTRL register
//
//*****************************************************************************
#define FSI_TX_MASTER_CTRL_SOFT_RESET  0x1U         // Soft Reset bit
#define FSI_TX_MASTER_CTRL_FLUSH  0x2U         // Flush operation initiation
                                               // bit
#define FSI_TX_MASTER_CTRL_WRITE_KEY_S  8U
#define FSI_TX_MASTER_CTRL_WRITE_KEY_M  0xFF00U      // Write Key bit positions

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_CLK_CTRL register
//
//*****************************************************************************
#define FSI_TX_CLK_CTRL_SOFT_RESET  0x1U         // Soft reset for the divider
#define FSI_TX_CLK_CTRL_ENABLE    0x2U         // Enable for the divider
#define FSI_TX_CLK_CTRL_PRESCALE_VALUE_S  2U
#define FSI_TX_CLK_CTRL_PRESCALE_VALUE_M  0x3FCU       // Prescale value

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_OPER_CTRL_LO register
//
//*****************************************************************************
#define FSI_TX_OPER_CTRL_LO_XMIT_DATA_WIDTH_S  0U
#define FSI_TX_OPER_CTRL_LO_XMIT_DATA_WIDTH_M  0x3U         // Transmit Data width
#define FSI_TX_OPER_CTRL_LO_SPI_MODE  0x4U         // Enable SPI mode
#define FSI_TX_OPER_CTRL_LO_START_MODE_S  3U
#define FSI_TX_OPER_CTRL_LO_START_MODE_M  0x38U        // Transmission start mode
#define FSI_TX_OPER_CTRL_LO_SW_CRC  0x40U        // CRC provided by Software
#define FSI_TX_OPER_CTRL_LO_PING_TIMEOUT_MODE  0x80U        // Timeout mode for PING
                                               // operation
#define FSI_TX_OPER_CTRL_LO_SEL_PLLCLK  0x100U       // Select PLL Clock instead of
                                               // SYSCLK

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_OPER_CTRL_HI register
//
//*****************************************************************************
#define FSI_TX_OPER_CTRL_HI_EXT_TRIG_SEL_S  0U
#define FSI_TX_OPER_CTRL_HI_EXT_TRIG_SEL_M  0x1FU        // Selection for external
                                               // trigger
#define FSI_TX_OPER_CTRL_HI_FORCE_ERROR  0x20U        // Control bit for forcing error
                                               // packet
#define FSI_TX_OPER_CTRL_HI_ECC_16  0x40U        // ECC data width selected to be
                                               // 16 bits

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_PACKET_CTRL register
//
//*****************************************************************************
#define FSI_TX_PACKET_CTRL_PKT_TYPE_S  0U
#define FSI_TX_PACKET_CTRL_PKT_TYPE_M  0xFU         // Transmission packet type
#define FSI_TX_PACKET_CTRL_NWORDS_S  4U
#define FSI_TX_PACKET_CTRL_NWORDS_M  0xF0U        // Number of words to transmit
#define FSI_TX_PACKET_CTRL_START  0x8000U      // Start bit to initiate
                                               // transmission

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_PACKET_UDATA_TAG register
//
//*****************************************************************************
#define FSI_TX_PACKET_UDATA_TAG_PKT_TAG_S  0U
#define FSI_TX_PACKET_UDATA_TAG_PKT_TAG_M  0xFU         // Packet Tag
#define FSI_TX_PACKET_UDATA_TAG_USER_DATA_S  8U
#define FSI_TX_PACKET_UDATA_TAG_USER_DATA_M  0xFF00U      // User data field

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_BUF_PTR_LOAD register
//
//*****************************************************************************
#define FSI_TX_BUF_PTR_LOAD_BUF_PTR_LOAD_S  0U
#define FSI_TX_BUF_PTR_LOAD_BUF_PTR_LOAD_M  0xFU         // Pointer value to be loaded

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_BUF_PTR_STATUS register
//
//*****************************************************************************
#define FSI_TX_BUF_PTR_STATUS_CURR_BUF_PTR_S  0U
#define FSI_TX_BUF_PTR_STATUS_CURR_BUF_PTR_M  0xFU         // Current value of buffer
                                               // pointer
#define FSI_TX_BUF_PTR_STATUS_CURR_WORD_COUNT_S  8U
#define FSI_TX_BUF_PTR_STATUS_CURR_WORD_COUNT_M  0x1F00U      // Number of words in the buffer

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_PING_CTRL register
//
//*****************************************************************************
#define FSI_TX_PING_CTRL_SOFT_RESET  0x1U         // Soft Reset
#define FSI_TX_PING_CTRL_TIMER_ENABLE  0x2U         // Enable the PING timer
#define FSI_TX_PING_CTRL_EXT_TRIG_ENABLE  0x4U         // Enable the external trigger
#define FSI_TX_PING_CTRL_EXT_TRIG_SELECT_S  3U
#define FSI_TX_PING_CTRL_EXT_TRIG_SELECT_M  0xF8U        // Select value for the external
                                               // trigger

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_PING_TAG register
//
//*****************************************************************************
#define FSI_TX_PING_TAG_TAG_S     0U
#define FSI_TX_PING_TAG_TAG_M     0xFU         // Tag to be used for PING
                                               // packets

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_INTR_EVENT_CTRL register
//
//*****************************************************************************
#define FSI_TX_INTR_EVENT_CTRL_INT1_EN_FRAME_DONE  0x1U         // Enable INT1N for Frame-Done
#define FSI_TX_INTR_EVENT_CTRL_INT1_EN_BUFFER_UNDERRUN  0x2U         // Enable INT1N for Buffer
                                               // underrun
#define FSI_TX_INTR_EVENT_CTRL_INT1_EN_BUFFER_OVERRUN  0x4U         // Enable INT1N for Buffer
                                               // overrun
#define FSI_TX_INTR_EVENT_CTRL_INT1_EN_PING_TIMEOUT  0x8U         // Enable INT1N for PING timeout
#define FSI_TX_INTR_EVENT_CTRL_INT2_EN_FRAME_DONE  0x100U       // Enable INT2N for Frame-Done
#define FSI_TX_INTR_EVENT_CTRL_INT2_EN_BUFFER_UNDERRUN  0x200U       // Enable INT2N for Buffer
                                               // underrun
#define FSI_TX_INTR_EVENT_CTRL_INT2_EN_BUFFER_OVERRUN  0x400U       // Enable INT2N for Buffer
                                               // overrun
#define FSI_TX_INTR_EVENT_CTRL_INT2_EN_PING_TIMEOUT  0x800U       // Enable INT2N for PING timeout

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_DMA_EVENT_CTRL register
//
//*****************************************************************************
#define FSI_TX_DMA_EVENT_CTRL_DMA_EVT_EN  0x1U         // Enable for DMA events

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_LOCK_CTRL register
//
//*****************************************************************************
#define FSI_TX_LOCK_CTRL_LOCK_ENABLE  0x1U         // This bit enables the LOCK
                                               // mechanism for registers
#define FSI_TX_LOCK_CTRL_KEY_S    8U
#define FSI_TX_LOCK_CTRL_KEY_M    0xFF00U      // This is the key value field.

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_EVT_ERR_STATUS register
//
//*****************************************************************************
#define FSI_TX_EVT_ERR_STATUS_FRAME_DONE  0x1U         // Status indicating Frame
                                               // completion
#define FSI_TX_EVT_ERR_STATUS_UNDER_RUN  0x2U         // Status indicating buffer
                                               // underrun
#define FSI_TX_EVT_ERR_STATUS_OVER_RUN  0x4U         // Status indicating buffer
                                               // overrun
#define FSI_TX_EVT_ERR_STATUS_PING_HW_TRIGGERED  0x8U         // Status indicating PING
                                               // hardware triggered.

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_EVT_ERR_CLEAR register
//
//*****************************************************************************
#define FSI_TX_EVT_ERR_CLEAR_FRAME_DONE  0x1U         // Clear control for Frame_done
                                               // bit
#define FSI_TX_EVT_ERR_CLEAR_UNDER_RUN  0x2U         // Clear control for Under_run
                                               // bit
#define FSI_TX_EVT_ERR_CLEAR_OVER_RUN  0x4U         // Clear control for Over_run
                                               // bit
#define FSI_TX_EVT_ERR_CLEAR_PING_HW_TRIGGERED  0x8U         // Clear control for PING
                                               // triggered bit.

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_EVT_ERR_SET register
//
//*****************************************************************************
#define FSI_TX_EVT_ERR_SET_FRAME_DONE  0x1U         // Set control for Frame_done
                                               // bit
#define FSI_TX_EVT_ERR_SET_UNDER_RUN  0x2U         // Set control for Under_run bit
#define FSI_TX_EVT_ERR_SET_OVER_RUN  0x4U         // Set control for Over_run bit
#define FSI_TX_EVT_ERR_SET_PING_HW_TRIGGERED  0x8U         // Set control for PING
                                               // triggered bit.

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_USER_DEFINED_CRC register
//
//*****************************************************************************
#define FSI_TX_USER_DEFINED_CRC_USER_CRC_S  0U
#define FSI_TX_USER_DEFINED_CRC_USER_CRC_M  0xFFU        // User Defined CRC value for
                                               // transmission

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_ECC_DATA register
//
//*****************************************************************************
#define FSI_TX_ECC_DATA_DATA_LOW_S  0U
#define FSI_TX_ECC_DATA_DATA_LOW_M  0xFFFFU      // ECC Data registers lower 16
                                               // bits
#define FSI_TX_ECC_DATA_DATA_HIGH_S  16U
#define FSI_TX_ECC_DATA_DATA_HIGH_M  0xFFFF0000U  // ECC Data registers upper 16
                                               // bits

//*****************************************************************************
//
// The following are defines for the bit fields in the TX_ECC_VALUE register
//
//*****************************************************************************
#define FSI_TX_ECC_VALUE_ECC_VAL_S  0U
#define FSI_TX_ECC_VALUE_ECC_VAL_M  0xFFU        // ECC Value generated in
                                               // hardware

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_MASTER_CTRL register
//
//*****************************************************************************
#define FSI_RX_MASTER_CTRL_SOFT_RESET  0x1U         // Soft Reset
#define FSI_RX_MASTER_CTRL_INT_LOOP_BK  0x2U         // Internal Loop Back
#define FSI_RX_MASTER_CTRL_SPI_PAIRING  0x4U         // Pair for SPI like behaviour
#define FSI_RX_MASTER_CTRL_WRITE_KEY_S  8U
#define FSI_RX_MASTER_CTRL_WRITE_KEY_M  0xFF00U      // Key value for enabling writes

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_OPER_CTRL register
//
//*****************************************************************************
#define FSI_RX_OPER_CTRL_RCV_DATA_WIDTH_S  0U
#define FSI_RX_OPER_CTRL_RCV_DATA_WIDTH_M  0x3U         // Number of receive data lines
#define FSI_RX_OPER_CTRL_SPI_MODE  0x4U         // SPI mode enable
#define FSI_RX_OPER_CTRL_NWORDS_S  3U
#define FSI_RX_OPER_CTRL_NWORDS_M  0x78U        // Number of words for NWORD
                                               // data type packet
#define FSI_RX_OPER_CTRL_ECC_16   0x80U        // Select ECC computation on
                                               // 16-bit data.
#define FSI_RX_OPER_CTRL_PING_TIMEOUT_MODE  0x100U       // PING timeout mode

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_PACKET_INFO register
//
//*****************************************************************************
#define FSI_RX_PACKET_INFO_PKT_TYPE_S  0U
#define FSI_RX_PACKET_INFO_PKT_TYPE_M  0xFU         // Packet type of received 
                                               // packet.

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_PACKET_UDATA_TAG register
//
//*****************************************************************************
#define FSI_RX_PACKET_UDATA_TAG_ZERO  0x1U         // This bit is always 0
#define FSI_RX_PACKET_UDATA_TAG_PACKET_TAG_S  1U
#define FSI_RX_PACKET_UDATA_TAG_PACKET_TAG_M  0x1EU        // 4 bit tag of received 
                                               // packet.
#define FSI_RX_PACKET_UDATA_TAG_USER_DATA_S  8U
#define FSI_RX_PACKET_UDATA_TAG_USER_DATA_M  0xFF00U      // 8 bit user data of received
                                               // data packet.

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_DMA_EVENT_CTRL register
//
//*****************************************************************************
#define FSI_RX_DMA_EVENT_CTRL_DMA_EVT_EN  0x1U         // Enable DMA event generation

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_EVT_ERR_STATUS register
//
//*****************************************************************************
#define FSI_RX_EVT_ERR_STATUS_PING_WD_TIMEOUT  0x1U         // Status indicating PING Watch
                                               // dog timeout
#define FSI_RX_EVT_ERR_STATUS_FRAME_WD_TIMEOUT  0x2U         // Status indicating FRAME Watch
                                               // dog timeout
#define FSI_RX_EVT_ERR_STATUS_CRC_ERROR  0x4U         // Status indicating CRC error
#define FSI_RX_EVT_ERR_STATUS_TYPE_ERROR  0x8U         // Status indicating TYPE Error
                                               // in received Frame.
#define FSI_RX_EVT_ERR_STATUS_EOF_ERROR  0x10U        // Status indicating
                                               // End-of-frame Error
#define FSI_RX_EVT_ERR_STATUS_OVER_RUN  0x20U        // Receive buffer overrun
#define FSI_RX_EVT_ERR_STATUS_FRAME_DONE  0x40U        // Frame successfully received
#define FSI_RX_EVT_ERR_STATUS_UNDER_RUN  0x80U        // Receive buffer underrun
#define FSI_RX_EVT_ERR_STATUS_ERROR_FRAME_RCVD  0x100U       // ERROR type Frame received
#define FSI_RX_EVT_ERR_STATUS_PING_FRAME_RCVD  0x200U       // PING type Frame received.
#define FSI_RX_EVT_ERR_STATUS_FRAME_OVERRUN  0x400U       // Frame overrun
#define FSI_RX_EVT_ERR_STATUS_DATA_FRAME_RCVD  0x800U       // DATA type frame received.

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_CRC_INFO register
//
//*****************************************************************************
#define FSI_RX_CRC_INFO_RECEIVED_CRC_S  0U
#define FSI_RX_CRC_INFO_RECEIVED_CRC_M  0xFFU        // CRC value received in the
                                               // frame
#define FSI_RX_CRC_INFO_COMPUTED_CRC_S  8U
#define FSI_RX_CRC_INFO_COMPUTED_CRC_M  0xFF00U      // CRC computed in hardware

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_EVT_ERR_CLEAR register
//
//*****************************************************************************
#define FSI_RX_EVT_ERR_CLEAR_PING_WD_TIMEOUT  0x1U         // Clear for PING WD bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_FRAME_WD_TIMEOUT  0x2U         // Clear for FRAME_WD bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_CRC_ERROR  0x4U         // Clear for CRC_ERROR bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_TYPE_ERROR  0x8U         // Clear for TYPE_ERROR bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_EOF_ERROR  0x10U        // Clear for EOF_ERROR bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_OVER_RUN  0x20U        // Clear for OVER_RUN bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_FRAME_DONE  0x40U        // Clear for FRAME_DONE bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_UNDER_RUN  0x80U        // Clear for UNDER_RUN bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_ERROR_FRAME_RCVD  0x100U       // Clear for ERROR_FRAME bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_PING_FRAME_RCVD  0x200U       // Clear for PING FRAME bit in
                                               // status register
#define FSI_RX_EVT_ERR_CLEAR_FRAME_OVERRUN  0x400U       // Clear for FRAME_OVERRUN bit
                                               // in status register
#define FSI_RX_EVT_ERR_CLEAR_DATA_FRAME_RCVD  0x800U       // Clear for DATA_FRAME bit in
                                               // status register

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_EVT_ERR_SET register
//
//*****************************************************************************
#define FSI_RX_EVT_ERR_SET_PING_WD_TIMEOUT  0x1U         // Set for PING WD bit in status
                                               // register
#define FSI_RX_EVT_ERR_SET_FRAME_WD_TIMEOUT  0x2U         // Set for FRAME_WD bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_CRC_ERROR  0x4U         // Set for CRC_ERROR bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_TYPE_ERROR  0x8U         // Set for TYPE_ERROR bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_EOF_ERROR  0x10U        // Set for EOF_ERROR bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_OVER_RUN  0x20U        // Set for OVER_RUN bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_FRAME_DONE  0x40U        // Set for FRAME_DONE bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_UNDER_RUN  0x80U        // Set for UNDER_RUN bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_ERROR_FRAME_RCVD  0x100U       // Set for ERROR_FRAME bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_PING_FRAME_RCVD  0x200U       // Set for PING FRAME bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_FRAME_OVERRUN  0x400U       // Set for FRAME_OVERRUN bit in
                                               // status register
#define FSI_RX_EVT_ERR_SET_DATA_FRAME_RCVD  0x800U       // Set for DATA_FRAME bit in
                                               // status register

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_BUF_PTR_LOAD register
//
//*****************************************************************************
#define FSI_RX_BUF_PTR_LOAD_BUF_PTR_WR_S  0U
#define FSI_RX_BUF_PTR_LOAD_BUF_PTR_WR_M  0xFU         // Load value for receive buffer
                                               // pointer

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_BUF_PTR_STATUS register
//
//*****************************************************************************
#define FSI_RX_BUF_PTR_STATUS_CURR_BUF_PTR_S  0U
#define FSI_RX_BUF_PTR_STATUS_CURR_BUF_PTR_M  0xFU         // Current Buffer pointer
#define FSI_RX_BUF_PTR_STATUS_CURR_WORD_COUNT_S  8U
#define FSI_RX_BUF_PTR_STATUS_CURR_WORD_COUNT_M  0x1F00U      // Current word count in buffer

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_FRAME_WD_CTRL register
//
//*****************************************************************************
#define FSI_RX_FRAME_WD_CTRL_SOFT_RESET  0x1U         // Soft reset for the Frame
                                               // Watchdog counter
#define FSI_RX_FRAME_WD_CTRL_ENABLE  0x2U         // Enable for the Frame Watchdog
                                               // counter

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_PING_WD_CTRL register
//
//*****************************************************************************
#define FSI_RX_PING_WD_CTRL_SOFT_RESET  0x1U         // Soft reset for the PING
                                               // Watchdog counter
#define FSI_RX_PING_WD_CTRL_ENABLE  0x2U         // Enable for the PING Watchdog
                                               // counter

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_PING_TAG register
//
//*****************************************************************************
#define FSI_RX_PING_TAG_ZERO      0x1U         // This bit is intentionally 0
#define FSI_RX_PING_TAG_PING_TAG_S  1U
#define FSI_RX_PING_TAG_PING_TAG_M  0x1EU        // PING packet tag

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_INTR_EVENT_CTRL_1 register
//
//*****************************************************************************
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_PING_WD_TIMEOUT  0x1U         // Enable Interrupt 1 for PING
                                               // Watchdog time out
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_FRAME_WD_TIMEOUT  0x2U         // Enable Interrupt 1 for Frame
                                               // watchdog timeout
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_CRC_ERROR  0x4U         // Enable Interrupt 1 for CRC
                                               // errror
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_TYPE_ERROR  0x8U         // Enable Interrupt 1 for TYPE
                                               // error
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_EOF_ERROR  0x10U        // Enable Interrupt 1 for
                                               // End-of-frame error
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_OVER_RUN  0x20U        // Enable Interrupt 1 for buffer
                                               // overrun
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_FRAME_DONE  0x40U        // Enable Interrupt 1 when a
                                               // frame received.
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_UNDER_RUN  0x80U        // Enable Interrupt 1 for a
                                               // buffer underrun
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_ERROR_FRAME_RCVD  0x100U       // Enable Interrupt 1 when an
                                               // ERROR frame is received.
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_PING_FRAME_RCVD  0x200U       // Enable Interrupt 1 a PING
                                               // frame is received.
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_FRAME_OVERRUN  0x400U       // Enable Interrupt 1 for Frame
                                               // overrun condition
#define FSI_RX_INTR_EVENT_CTRL_1_INTR1_EN_DATA_FRAME_RCVD  0x800U       // Enable Interrupt 1 when a
                                               // DATA frame is received.

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_INTR_EVENT_CTRL_2 register
//
//*****************************************************************************
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_PING_WD_TIMEOUT  0x1U         // Enable Interrupt 2 for PING
                                               // Watchdog time out
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_FRAME_WD_TIMEOUT  0x2U         // Enable Interrupt 2 for Frame
                                               // watchdog timeout
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_CRC_ERROR  0x4U         // Enable Interrupt 2 for CRC
                                               // errror
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_TYPE_ERROR  0x8U         // Enable Interrupt 2 for TYPE
                                               // error
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_EOF_ERROR  0x10U        // Enable Interrupt 2 for
                                               // End-of-frame error
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_OVER_RUN  0x20U        // Enable Interrupt 2 for buffer
                                               // overrun
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_FRAME_DONE  0x40U        // Enable Interrupt 2 when frame
                                               // received.
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_UNDER_RUN  0x80U        // Enable Interrupt 2 for a
                                               // buffer underrun
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_ERROR_FRAME_RCVD  0x100U       // Enable Interrupt 2 when an
                                               // ERROR frame is received.
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_PING_FRAME_RCVD  0x200U       // Enable Interrupt 2 a PING
                                               // frame is received.
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_FRAME_OVERRUN  0x400U       // Enable Interrupt 2 for Frame
                                               // overrun condition
#define FSI_RX_INTR_EVENT_CTRL_2_INTR2_EN_DATA_FRAME_RCVD  0x800U       // Enable Interrupt 2 when a
                                               // DATA frame is received.

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_LOCK_CTRL register
//
//*****************************************************************************
#define FSI_RX_LOCK_CTRL_LOCK_ENABLE  0x1U         // Lock Enable bit
#define FSI_RX_LOCK_CTRL_KEY_S    8U
#define FSI_RX_LOCK_CTRL_KEY_M    0xFF00U      // Bit positions for Write Key

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_ECC_DATA register
//
//*****************************************************************************
#define FSI_RX_ECC_DATA_DATA_LOW_S  0U
#define FSI_RX_ECC_DATA_DATA_LOW_M  0xFFFFU      // Lower 16 bits of data for ECC
                                               // computation
#define FSI_RX_ECC_DATA_DATA_HIGH_S  16U
#define FSI_RX_ECC_DATA_DATA_HIGH_M  0xFFFF0000U  // Upper 16 bits of data for ECC
                                               // computation

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_ECC_VALUE register
//
//*****************************************************************************
#define FSI_RX_ECC_VALUE_ECC_VAL_S  0U
#define FSI_RX_ECC_VALUE_ECC_VAL_M  0xFFU        // Data value for ECC
                                               // computation

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_ECC_LOG register
//
//*****************************************************************************
#define FSI_RX_ECC_LOG_ECC_LOG_S  0U
#define FSI_RX_ECC_LOG_ECC_LOG_M  0xFFU        // Log value from ECC block

//*****************************************************************************
//
// The following are defines for the bit fields in the RX_DLYLINE_CTRL register
//
//*****************************************************************************
#define FSI_RX_DLYLINE_CTRL_CLK_TAP_S  0U
#define FSI_RX_DLYLINE_CTRL_CLK_TAP_M  0x1FU        // Delay tap for RX CLK
#define FSI_RX_DLYLINE_CTRL_CLK_RX0_S  5U
#define FSI_RX_DLYLINE_CTRL_CLK_RX0_M  0x3E0U       // Delay tap for RXD0
#define FSI_RX_DLYLINE_CTRL_CLK_RX1_S  10U
#define FSI_RX_DLYLINE_CTRL_CLK_RX1_M  0x7C00U      // Delay tap for RXD1
#endif
