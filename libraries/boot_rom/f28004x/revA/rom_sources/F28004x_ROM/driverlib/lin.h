//###########################################################################
//
// FILE:   lin.h
//
// TITLE:  LIN Driver Definition File
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __LIN_H__
#define __LIN_H__

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
// Definitions for the intFlags parameter of LIN_enableInterrupt(),
// LIN_disableInterrupt(), LIN_clearInterruptStatus(),
// LIN_getInterruptStatus(), and LIN_setInterruptLevel().
//
//*****************************************************************************
#define LIN_BREAK_INT           0x00000001U // Break detect
#define LIN_WAKEUP_INT          0x00000002U // Wakeup
#define LIN_TO_INT              0x00000010U // Time out
#define LIN_TOAWUS_INT          0x00000040U // Time out after wakeup signal
#define LIN_TOA3WUS_INT         0x00000080U // Time out after 3 wakeup signals
#define LIN_TX_INT              0x00000100U // Transmit buffer ready
#define LIN_RX_INT              0x00000200U // Receive buffer ready
#define LIN_ID_INT              0x00002000U // Received matching identifier
#define LIN_TXDMA_INT           0x00010000U // Transmit DMA requests
#define LIN_RXDMA_INT           0x00020000U // Receiver DMA requests
#define LIN_RXDMAALL_INT        0x00040000U // Receiver DMA requests for
                                            // address and data frames
#define LIN_PE_INT              0x01000000U // Parity error
#define LIN_OE_INT              0x02000000U // Overrun error
#define LIN_FE_INT              0x04000000U // Framing error
#define LIN_NRE_INT             0x08000000U // No response error
#define LIN_ISFE_INT            0x10000000U // Inconsistent sync field error
#define LIN_CE_INT              0x20000000U // Checksum error
#define LIN_PBE_INT             0x40000000U // Physical bus error
#define LIN_BE_INT              0x80000000U // Bit error

//*****************************************************************************
//
// LIN Register Definition
// This structure is used to access the LIN module registers.
//
//*****************************************************************************

//
// Configuration registers for LIN_getConfigValue()
//
typedef struct
{
    uint32_t CONFIG_GCR0;
    uint32_t CONFIG_GCR1;
    uint32_t CONFIG_GCR2;
    uint32_t CONFIG_SETINT;
    uint32_t CONFIG_SETINTLVL;
    uint32_t CONFIG_FORMAT;
    uint32_t CONFIG_BRSR;
    uint32_t CONFIG_FUN;
    uint32_t CONFIG_DIR;
    uint32_t CONFIG_ODR;
    uint32_t CONFIG_PD;
    uint32_t CONFIG_PSL;
    uint32_t CONFIG_COMP;
    uint32_t CONFIG_MASK;
    uint32_t CONFIG_MBRSR;
} LIN_ConfigReg;

//*****************************************************************************
//
// config type Type Definition
//
// This type is used to specify the Initial and Current value for the function
// LIN_getConfigValue().
//
//*****************************************************************************
typedef enum
{
    LIN_CONFIG_INITIAL_VALUE,
    LIN_CONFIG_CURRENT_VALUE
} LIN_ConfigValue;

//*****************************************************************************
//
// Loopback type definition
//
// This type is used to select the module Loopback type Digital or Analog
// loopback for the function LIN_enableLoopback().
//
//*****************************************************************************
typedef enum
{
    LIN_LOOPBACK_DIGITAL = 0U,
    LIN_LOOPBACK_ANALOG  = 2U
} LIN_LoopbackType;

//
// Configuration registers initial value for LIN
//
#define LIN_GCR0_CONFIGVALUE          0x00000001U
#define LIN_GCR1_CONFIGVALUE         (0x03000CE0U | \
                                      (1U << 12U) | \
                                      (0U << 2U))
#define LIN_GCR2_CONFIGVALUE          0x00000000U
#define LIN_SETINTLVL_CONFIGVALUE ((uint32_t)   0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U)

#define LIN_SETINT_CONFIGVALUE    ((uint32_t)   0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U | \
                                   (uint32_t)0x00000000U)

#define LIN_FORMAT_CONFIGVALUE     ((8UL - 1UL) << 16U)
#define LIN_BRSR_CONFIGVALUE       (280U)
#define LIN_COMP_CONFIGVALUE       (((uint32_t)0U << 8U) | (uint32_t)0U)
#define LIN_MASK_CONFIGVALUE       (((uint32_t)   0xFFU << 16U) | \
                                    (uint32_t)0xFFU)
#define LIN_MBRSR_CONFIGVALUE      (4046U)
#define LIN_FUN_CONFIGVALUE        ((uint32_t)4U | \
                                    (uint32_t)2U | \
                                    (uint32_t)0U)
#define LIN_DIR_CONFIGVALUE        ((uint32_t)0U | \
                                    (uint32_t)0U | \
                                    (uint32_t)0U)
#define LIN_ODR_CONFIGVALUE        ((uint32_t)0U | \
                                    (uint32_t)0U | \
                                    (uint32_t)0U)
#define LIN_PD_CONFIGVALUE         ((uint32_t)0U | \
                                    (uint32_t)0U | \
                                    (uint32_t)0U)
#define LIN_PSL_CONFIGVALUE        ((uint32_t)4U | \
                                    (uint32_t)2U | \
                                    (uint32_t)1U)

//*****************************************************************************
//
// The following are defines for the mode parameter of the LIN_setCommMode()
// function.
//
//*****************************************************************************
typedef enum
{
    LIN_COMM_LIN_USELENGTHVAL = 0x0000U,    // Use the length indicated
                                            // in the LENGTH field of
                                            // the SCIFORMAT register
    LIN_COMM_LIN_ID4ID5LENCTL = 0x0001U,    // Use ID4 and ID5 to
                                            // convey the length
    LIN_COMM_SCI_IDLELINE     = 0x0000U,    // Idle-line mode is used
    LIN_COMM_SCI_ADDRBIT      = 0x0001U     // Address bit mode is used
} LIN_CommMode;

//*****************************************************************************
//
// The following are defines for the mode parameter of the LIN_setLinMode()
// function.
//
//*****************************************************************************
typedef enum
{
    LIN_MODE_LIN_SLAVE        = 0x0000U,    // The node is in slave mode
    LIN_MODE_LIN_MASTER       = 0x0020U     // The node is in master mode
} LIN_LINMode;

//*****************************************************************************
//
// The following are defines for the line parameter of the
// LIN_getInterruptOffset() function.
//
//*****************************************************************************
typedef enum
{
    LIN_INTERRUPT_LINE0       = 0x0U,    // Interrupt line 0
    LIN_INTERRUPT_LINE1       = 0x1U     // Interrupt line 1
} LIN_InterruptLine;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void LIN_enableModule(uint32_t base);
extern void LIN_disableModule(uint32_t base);
extern void LIN_setLinMode(uint32_t base, LIN_LINMode mode);
extern void LIN_setBaudRate (uint32_t base, uint32_t baudRate);
extern void LIN_setMaximumBaudRate(uint32_t base, uint16_t prescaler);
extern void LIN_enableMaskFiltering(uint32_t base);
extern void LIN_disableMaskFiltering(uint32_t base);
extern void LIN_enableSCIMode(uint32_t base);
extern void LIN_disableSCIMode(uint32_t base);
extern void LIN_setSCIParity(uint32_t base, bool enable, bool mode);
extern void LIN_initModule(uint32_t base);
extern void LIN_setFunctional(uint32_t base, uint32_t port);
extern void LIN_sendHeader(uint32_t base, uint16_t identifier);
extern void LIN_setIDSlaveTask(uint32_t base, uint16_t identifier);
extern void LIN_sendWakeupSignal(uint32_t base);
extern void LIN_enterSleep(uint32_t base);
extern void LIN_softwareReset(uint32_t base);
extern void LIN_enterResetState(uint32_t base);
extern void LIN_enterReadyState(uint32_t base);
extern uint32_t LIN_isTxReady(uint32_t base);
extern void LIN_setLength(uint32_t base, uint32_t length);
extern void LIN_setCharLength(uint32_t base, uint32_t numBits);
extern void LIN_setCommMode(uint32_t base, LIN_CommMode mode);
extern void LIN_sendData(uint32_t base, uint16_t *data);
extern void LIN_setMasks(uint32_t base, uint16_t txMask, uint16_t rxMask);
extern uint32_t LIN_isRxReady(uint32_t base);
extern uint32_t LIN_getTxRxErrorStatus(uint32_t base);
extern uint32_t LIN_getIdentifier(uint32_t base);
extern void LIN_getData(uint32_t base, uint16_t * const data);
extern void LIN_enableInterrupt(uint32_t base, uint32_t intFlags);
extern void LIN_disableInterrupt(uint32_t base, uint32_t intFlags);
extern void LIN_clearInterruptStatus(uint32_t base, uint32_t intFlags);
extern uint32_t LIN_getInterruptStatus(uint32_t base);
extern void LIN_setInterruptLevel(uint32_t base, uint32_t intFlags,
                                  bool setToLvl1);
extern void LIN_enableLoopback(uint32_t base,
                               LIN_LoopbackType loopbackType);
extern void LIN_disableLoopback(uint32_t base);
extern void LIN_getConfigValue(uint32_t base, LIN_ConfigReg *configReg,
                               LIN_ConfigValue type);
extern uint32_t LIN_getInterruptOffset(uint32_t base, LIN_InterruptLine line);
extern void LIN_enableMultibufferMode(uint32_t base);
extern void LIN_disableMultibufferMode(uint32_t base);
extern void LIN_enableChecksum(uint32_t base);
extern void LIN_disableChecksum(uint32_t base);
extern void LIN_enableGlobalInterrupt(uint32_t base, LIN_InterruptLine line);
extern void LIN_disableGlobalInterrupt(uint32_t base, LIN_InterruptLine line);
extern void LIN_clearGlobalInterruptStatus(uint32_t base, LIN_InterruptLine line);
extern bool LIN_getGlobalInterruptStatus(uint32_t base, LIN_InterruptLine line);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __LIN_H__
