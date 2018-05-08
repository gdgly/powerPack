//###########################################################################
//
// FILE:   can.h
//
// TITLE:  Stellaris style wrapper driver for C28x CAN peripheral.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef __CAN_H__
#define __CAN_H__

//*****************************************************************************
//! \addtogroup can_api
//! @{
//*****************************************************************************

//*****************************************************************************
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#define CAN_INDEX_TO_BASE(idx)     ((idx == 0) ? CAN_A_BASE : CAN_B_BASE)

#define CAN_INDEX_TO_MSG_RAM_BASE(idx)                                        \
                                   ((idx == 0) ? CAN_A_MSG_RAM : CAN_B_MSG_RAM)

//*****************************************************************************
// Miscellaneous defines for Message ID Types
//*****************************************************************************

//*****************************************************************************
// These are the flags used by the CAN_MsgObject.flags value when calling
// the CAN_setMessage() and CAN_getMessage() functions.
//*****************************************************************************

//! This definition is used with the CAN_MsgObject flags value and indicates
//! that transmit interrupts should be enabled, or are enabled.
#define MSG_OBJ_TX_INT_ENABLE           0x00000001U

//! This indicates that receive interrupts should be enabled, or are
//! enabled.
#define MSG_OBJ_RX_INT_ENABLE           0x00000002U

//! This indicates that a message object will use or is using an extended
//! identifier.
#define MSG_OBJ_EXTENDED_ID             0x00000004U

//! This indicates that a message object will use or is using filtering
//! based on the object's message identifier.
#define MSG_OBJ_USE_ID_FILTER           0x00000008U

//! This indicates that new data was available in the message object.
#define MSG_OBJ_NEW_DATA                0x00000080U

//! This indicates that data was lost since this message object was last
//! read.
#define MSG_OBJ_DATA_LOST               0x00000100U

//! This indicates that a message object will use or is using filtering
//! based on the direction of the transfer.  If the direction filtering is
//! used, then ID filtering must also be enabled.
#define MSG_OBJ_USE_DIR_FILTER                                                \
                      ((uint32_t)0x00000010U | (uint32_t)MSG_OBJ_USE_ID_FILTER)

//! This indicates that a message object will use or is using message
//! identifier filtering based on the extended identifier.  If the extended
//! identifier filtering is used, then ID filtering must also be enabled.
#define MSG_OBJ_USE_EXT_FILTER                                                \
                      ((uint32_t)0x00000020U | (uint32_t)MSG_OBJ_USE_ID_FILTER)

//! This indicates that a message object is a remote frame.
#define MSG_OBJ_REMOTE_FRAME            0x00000040U

//! This indicates that this message object is part of a FIFO structure and
//! not the final message object in a FIFO.
#define MSG_OBJ_FIFO                    0x00000200U

//! This indicates that a message object has no flags set.
#define MSG_OBJ_NO_FLAGS                0x00000000U

//*****************************************************************************
//! This define is used with the flag values to allow checking only status
//! flags and not configuration flags.
//*****************************************************************************
#define MSG_OBJ_STATUS_MASK             (MSG_OBJ_NEW_DATA | MSG_OBJ_DATA_LOST)

//*****************************************************************************
//! The structure used for encapsulating all the items associated with a CAN
//! message object in the CAN controller.
//*****************************************************************************
typedef struct
{
    //! The CAN message identifier used for 11 or 29 bit identifiers.
    uint32_t msgID;

    //! The message identifier mask used when identifier filtering is enabled.
    uint32_t msgIDMask;

    //! This value holds various status flags and settings specified by
    //! tCANObjFlags.
    uint32_t flags;

    //! This value is the number of bytes of data in the message object.
    uint32_t msgLen;

    //! This is a pointer to the message object's data.
    uint16_t *msgData;
} CAN_MsgObject;

//*****************************************************************************
//! This structure is used for encapsulating the values associated with setting
//! up the bit timing for a CAN controller.  The structure is used when calling
//! the CAN_getBitTiming and CAN_setBitTiming functions.
//*****************************************************************************
typedef struct
{
    //! This value holds the sum of the Synchronization, Propagation, and Phase
    //! Buffer 1 segments, measured in time quanta.  The valid values for this
    //! setting range from 2 to 16.
    uint32_t syncPropPhase1Seg;

    //! This value holds the Phase Buffer 2 segment in time quanta. The valid
    //! values for this setting range from 1 to 8.
    uint32_t phase2Seg;

    //! This value holds the Resynchronization Jump Width in time quanta. The
    //! valid values for this setting range from 1 to 4.
    uint32_t sjw;

    //! This value holds the CAN_CLK divider used to determine time quanta.
    //! The valid values for this setting range from 1 to 1023.
    uint32_t quantumPrescaler;
} CAN_BitClkParms;

//*****************************************************************************
//! This data type is used to identify the interrupt status register.  This is
//! used when calling the CAN_getInterruptStatus() function.
//*****************************************************************************
typedef enum
{
    //! Read the CAN interrupt status information.
    CAN_INT_STS_CAUSE,

    //! Read a message object's interrupt status.
    CAN_INT_STS_OBJECT
} CAN_IntStatusReg;

//*****************************************************************************
//! This data type is used to identify which of several status registers to
//! read when calling the CAN_getStatus() function.
//*****************************************************************************
typedef enum
{
    //! Read the full CAN controller status.
    CAN_STS_CONTROL,

    //! Read the full 32-bit mask of message objects with a transmit request
    //! set.
    CAN_STS_TXREQUEST,

    //! Read the full 32-bit mask of message objects with new data available.
    CAN_STS_NEWDAT,

    //! Read the full 32-bit mask of message objects that are enabled.
    CAN_STS_MSGVAL
} CAN_StatusReg;

//*****************************************************************************
// These definitions are used to specify interrupt sources to
// CAN_enableInterrupt() and CAN_disableInterrupt().
//*****************************************************************************
//! This flag is used to allow a CAN controller to generate error
//! interrupts.
#define CAN_INT_ERROR              0x00000008

//! This flag is used to allow a CAN controller to generate status
//! interrupts.
#define CAN_INT_STATUS             0x00000004

//! This flag is used to allow a CAN controller to generate interrupts
//! on interrupt line 0
#define CAN_INT_IE0                0x00000002

//! This flag is used to allow a CAN controller to generate interrupts
//! on interrupt line 1
#define CAN_INT_IE1                0x00020000

// Defined to maintain compatibility with Stellaris Examples
#define CAN_INT_MASTER             CAN_INT_IE0

//*****************************************************************************
// This enumeration is used to specify the clock source to
// CAN_setClockSource()
//*****************************************************************************
typedef enum
{
    //! This flag is used to clock the CAN controller Selected CPU SYSCLKOUT.
    CAN_CLK_CPU_SYSCLKOUT  = 0, // PERx.SYSCLK (default on reset)

    //! This flag is used to clock the CAN controller with the X1/X2 oscillator
    //! clock.
    CAN_CLK_EXT_OSC        = 1, // External Oscillator (XTAL)

    //! This flag is used to clock the CAN controller with the clock from
    //! AUXCLKIN (from GPIO)
    CAN_CLK_AUXCLKIN       = 2  // AUXCLKIN (from GPIO)
} CAN_ClkSource;

//*****************************************************************************
//! This definition is used to determine the type of message object that will
//! be set up via a call to the CAN_setMessage() API.
//*****************************************************************************
typedef enum
{
    //! Transmit message object.
    MSG_OBJ_TYPE_TX,

    //! Transmit remote request message object
    MSG_OBJ_TYPE_TX_REMOTE,

    //! Receive message object.
    MSG_OBJ_TYPE_RX,

    //! Receive remote request message object.
    MSG_OBJ_TYPE_RX_REMOTE,

    //! Remote frame receive remote, with auto-transmit message object.
    MSG_OBJ_TYPE_RXTX_REMOTE
} CAN_MsgObjType;

//*****************************************************************************
// The following definitions contain all error or status indicators that can
// be returned when calling the CAN_getStatus() function.
//*****************************************************************************
//! CAN controller is in local power down mode.
#define CAN_STATUS_PDA                   0x00000400

//! CAN controller has initiated a system wakeup.
#define CAN_STATUS_WAKE_UP               0x00000200

//! CAN controller has detected a parity error.
#define CAN_STATUS_PERR                  0x00000100

//! CAN controller has entered a Bus Off state.
#define CAN_STATUS_BUS_OFF               0x00000080

//! CAN controller error level has reached warning level.
#define CAN_STATUS_EWARN                 0x00000040

//! CAN controller error level has reached error passive level.
#define CAN_STATUS_EPASS                 0x00000020

//! A message was received successfully since the last read of this status.
#define CAN_STATUS_RXOK                  0x00000010

//! A message was transmitted successfully since the last read of this
//! status.
#define CAN_STATUS_TXOK                  0x00000008

//! This is the mask for the last error code field.
#define CAN_STATUS_LEC_MSK               0x00000007

//! There was no error.
#define CAN_STATUS_LEC_NONE              0x00000000

//! A bit stuffing error has occurred.
#define CAN_STATUS_LEC_STUFF             0x00000001

//! A formatting error has occurred.
#define CAN_STATUS_LEC_FORM              0x00000002

//! An acknowledge error has occurred.
#define CAN_STATUS_LEC_ACK               0x00000003

//! The bus remained a bit level of 1 for longer than is allowed.
#define CAN_STATUS_LEC_BIT1              0x00000004

//! The bus remained a bit level of 0 for longer than is allowed.
#define CAN_STATUS_LEC_BIT0              0x00000005

//! A CRC error has occurred.
#define CAN_STATUS_LEC_CRC               0x00000006

//*****************************************************************************
// The following macros are added for the Global Interrupt EN/FLG/CLR
// register
//*****************************************************************************
//CANINT0 global interrupt bit
#define CAN_GLOBAL_INT_CANINT0          0x00000001

//CANINT1 global interrupt bit
#define CAN_GLOBAL_INT_CANINT1          0x00000002

//*****************************************************************************
// The following macros are missing in hw_can.h because of scripting
// but driverlib can.c needs them
//*****************************************************************************
#define CAN_INT_INT0ID_STATUS           0x8000

#define CAN_IF1ARB_STD_ID_S             18

// Standard Message Identifier
#define CAN_IF1ARB_STD_ID_M             0x1FFC0000

#define CAN_IF2ARB_STD_ID_S             18

// Standard Message Identifier
#define CAN_IF2ARB_STD_ID_M             0x1FFC0000

//*****************************************************************************
// API Function prototypes
//*****************************************************************************
extern void CAN_setClockSource(uint32_t base, CAN_ClkSource source);
extern void CAN_getBitTiming(uint32_t base, CAN_BitClkParms *clkParms);
extern void CAN_setBitTiming(uint32_t base, CAN_BitClkParms *clkParms);
extern uint32_t CAN_setBitRate(uint32_t base, uint32_t sourceClock,
                               uint32_t bitRate);
extern void CAN_disableAutoBusOn(uint32_t base);
extern void CAN_enableAutoBusOn(uint32_t base);
extern void CAN_setAutoBusOnTime(uint32_t base, uint32_t time);
extern void CAN_disableController(uint32_t base);
extern void CAN_enableController(uint32_t base);
extern void CAN_enableTestMode(uint32_t base, uint16_t mode);
extern void CAN_setInterruptionDebugMode(uint32_t base, bool enable);
extern void CAN_disableTestMode(uint32_t base, uint16_t mode);
extern void CAN_enableDMARequests(uint32_t base);
extern void CAN_disableDMARequests(uint32_t base);
extern bool CAN_getErrorCount(uint32_t base, uint32_t *rxCount,
                              uint32_t *txCount);
extern void CAN_initModule(uint32_t base);
extern void CAN_initRam(uint32_t base);
extern void CAN_clearInterruptStatus(uint32_t base, uint32_t intClr);
extern void CAN_disableInterrupt(uint32_t base, uint32_t intFlags);
extern void CAN_enableInterrupt(uint32_t base, uint32_t intFlags);
extern void CAN_registerInterrupt(uint32_t base, uint16_t intNumber,
                                  void (*handler)(void));
extern uint32_t CAN_getInterruptStatus(uint32_t base,
                                       CAN_IntStatusReg intStsReg);
extern void CAN_unregisterInterrupt(uint32_t base, uint16_t intNumber);
extern uint32_t CAN_getInterruptMux(uint32_t base);
extern void CAN_setInterruptMux(uint32_t base, uint32_t mux);
extern void CAN_clearMessage(uint32_t base, uint32_t objID);
extern void CAN_getMessage(uint32_t base, uint32_t objID,
                           CAN_MsgObject *msgObject, bool clrPendingInt);
extern void CAN_setMessage(uint32_t base, uint32_t objID,
                           CAN_MsgObject *msgObject, CAN_MsgObjType msgType);
extern void CAN_transferMessage(uint32_t base, uint_least8_t interface,
                                uint32_t objID, bool direction,
                                bool dmaRequest);
extern bool CAN_getRetry(uint32_t base);
extern void CAN_setRetry(uint32_t base, bool autoRetry);
extern uint32_t CAN_getStatus(uint32_t base, CAN_StatusReg statusReg);
extern void CAN_enableGlobalInterrupt(uint32_t base, uint32_t intFlags);
extern void CAN_disableGlobalInterrupt(uint32_t base, uint32_t intFlags);
extern void CAN_clearGlobalInterruptStatus(uint32_t base, uint32_t intFlags);
extern bool CAN_getGlobalInterruptStatus(uint32_t base, uint32_t intFlags);

//*****************************************************************************
// Mark the end of the C bindings section for C++ compilers.
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
// Close the Doxygen group.
//! @}
//*****************************************************************************

#endif //  __CAN_H__



