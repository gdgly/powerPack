#ifndef _PMBUS_STACK_CONFIG_H_
#define _PMBUS_STACK_CONFIG_H_
//#############################################################################
//
//! \file   PMBus_Stack_config.h
//!
//! \brief  PMBUS Communications Stack Configuration File
//! \author Vishal Coelho
//! \date    Mar 12, 2015
//
//  Group:          C2000
//  Target Device:  TMS320F28xxxx
//
// Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED
//#############################################################################
// $TI Release: C28x PMBus Communications Stack Library v1.00.00.00 $
// $Release Date: May 22, 2017 $
//#############################################################################

//*****************************************************************************
// the includes
//*****************************************************************************
#include "pmbus_stack_assert.h"
#include "pmbus.h"
//!
//! \defgroup PMBUS_STACK_CONFIG PMBus Configuration

//!
//! \ingroup PMBUS_STACK_CONFIG
//@{

#ifdef __cplusplus

extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
#define NTRANSACTIONS            11U
//*****************************************************************************
// typedefs
//*****************************************************************************

//! \brief Function pointer to the routine to handle a transaction
//!
typedef void (*transactionHandler)(void *hnd);

//! \brief PMBus Mode of Operation
//!
typedef enum
{
    PMBUS_STACK_MODE_SLAVE  = 0,      //!< PMBus operates in slave mode
    PMBUS_STACK_MODE_MASTER = 1,      //!< PMBus operates in master mode
}PMBus_Stack_mode;

//! \brief Enumeration of the states in the PMBus state machine
//!
typedef enum{
    //! PMBus in the Idle state
    PMBUS_STACK_STATE_IDLE                        = 0U,
    //! PMBus is waiting on an end-of-message signal (NACK on last data)
    PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM   = 1U,
    //! PMBus is reading a block of data
    PMBUS_STACK_STATE_READ_BLOCK                  = 2U,
    //! PMBus is waiting on an end-of-message signal (NACK on last data)
    PMBUS_STACK_STATE_READ_WAIT_FOR_EOM           = 3U,
    //! PMBus is either writing a block or issuing a process call
    PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL = 5U,
    //! PMBus is doing an extended read/write byte/word
    PMBUS_STACK_STATE_EXTENDED_COMMAND            = 6U,
}PMBus_Stack_State;

//! \brief PMBUS Slave Mode Object
//!
typedef struct _PMBus_Stack_Obj_
{
    uint32_t moduleBase;            //!< Base address of the PMBus module
    uint32_t moduleStatus;          //!< Status register of the PMBus module
    PMBus_Stack_mode mode;          //!< PMBus mode of operation
    uint16_t slaveAddress;          //!< Slave address for the PMBus module
    uint16_t slaveAddressMask;      //!< Slave address mask for PMBus module 
    PMBus_Stack_State currentState; //!< Current state of the state machine
    PMBus_Stack_State nextState;    //!< next state of the state machine
    uint16_t *ptrBuffer;            //!< pointer to a buffer of length >= 4
    uint16_t *currPtr;              //!< Current position in the buffer
    uint16_t nBytes;                //!< Number of bytes sent/received
    bool PECValid;                  //!< Valid PEC received or sent
    PMBus_Transaction transaction;  //!< Current Transaction type
    //! Handler for each transaction
    transactionHandler trnHnd[NTRANSACTIONS];   
}PMBus_Stack_Obj;

//! \brief Structure that packs 4 transaction fields into a word
//!
typedef struct _PMBus_Transaction_Obj_
{
	uint16_t transaction0:4;    //!< First Transaction field
	uint16_t transaction1:4;    //!< Second Transaction field
	uint16_t transaction2:4;    //!< Third Transaction field
	uint16_t transaction3:4;    //!< Fourth Transaction field
}PMBus_Transaction_Obj;

//! \brief  a union of the packed transactions struct and an unsigned
//!  word
//!
typedef union{
	PMBus_Transaction_Obj obj;
	uint16_t ui16;
}PMBus_Transaction_Obj_u;

//! \brief Handle to the PMBus_Stack_Obj object
//!
typedef PMBus_Stack_Obj *PMBus_Stack_Handle;

//*****************************************************************************
//globals
//*****************************************************************************

//! \brief PMBus Slave Object
//!
extern PMBus_Stack_Obj pmbusStackSlave;

//! \brief Handle to the slave object
//!
extern PMBus_Stack_Handle hndPmbusStackSlave;

//! PMBus Command Transaction Type Map
//! Each position in the map corresponds to a particular command, its
//! entry lists the type of read transaction that is involved. It will
//! used to distinguish between read byte, read word, and block read
//! commands in the state machine
//! Any command that has both a write and read command will have the
//! read transaction type as its entry. A command without a read command
//! will have its write transaction type as its entry
//!
static const PMBus_Transaction_Obj_u PMBus_Stack_commandTransactionMap[64] = {
 {
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_PAGE                       (0x00U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_OPERATION                  (0x01U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_ON_OFF_CONFIG              (0x02U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_CLEAR_FAULTS               (0x03U)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_PHASE                      (0x04U)
  PMBUS_TRANSACTION_BLOCKWRITE ,// PMBUS_CMD_PAGE_PLUS_WRITE            (0x05U)
  PMBUS_TRANSACTION_BLOCKWRPC  ,// PMBUS_CMD_PAGE_PLUS_READ             (0x06U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x07U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x08U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x09U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0AU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0BU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0EU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0FU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_WRITE_PROTECT              (0x10U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_STORE_DEFAULT_ALL          (0x11U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_RESTORE_DEFAULT_ALL        (0x12U)
  PMBUS_TRANSACTION_WRITEBYTE  ,// PMBUS_CMD_STORE_DEFAULT_CODE         (0x13U)
 },{
  PMBUS_TRANSACTION_WRITEBYTE  ,// PMBUS_CMD_RESTORE_DEFAULT_CODE       (0x14U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_STORE_USER_ALL             (0x15U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_RESTORE_USER_ALL           (0x16U)
  PMBUS_TRANSACTION_WRITEBYTE  ,// PMBUS_CMD_STORE_USER_CODE            (0x17U)
 },{
  PMBUS_TRANSACTION_WRITEBYTE  ,// PMBUS_CMD_RESTORE_USER_CODE          (0x18U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_CAPABILITY                 (0x19U)
  PMBUS_TRANSACTION_BLOCKWRPC  ,// PMBUS_CMD_QUERY                      (0x1AU)
  PMBUS_TRANSACTION_BLOCKWRPC  ,// PMBUS_CMD_SMBALERT_MASK              (0x1BU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x1CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x1DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x1EU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x1FU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VOUT_MODE                  (0x20U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_COMMAND               (0x21U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_TRIM                  (0x22U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_CAL_OFFSET            (0x23U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_MAX                   (0x24U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_MARGIN_HIGH           (0x25U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_MARGIN_LOW            (0x26U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_TRANSITION_RATE       (0x27U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_DROOP                 (0x28U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_SCALE_LOOP            (0x29U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_SCALE_MONITOR         (0x2AU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2BU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2EU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2FU)
 },{
  PMBUS_TRANSACTION_BLOCKWRPC  ,// PMBUS_CMD_COEFFICIENTS               (0x30U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POUT_MAX                   (0x31U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MAX_DUTY                   (0x32U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FREQUENCY_SWITCH           (0x33U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x34U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_ON                     (0x35U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_OFF                    (0x36U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_INTERLEAVE                 (0x37U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_CAL_GAIN              (0x38U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_CAL_OFFSET            (0x39U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_FAN_CONFIG_1_2             (0x3AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FAN_COMMAND_1              (0x3BU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FAN_COMMAND_2              (0x3CU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_FAN_CONFIG_3_4             (0x3DU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FAN_COMMAND_3              (0x3EU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FAN_COMMAND_4              (0x3FU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_OV_FAULT_LIMIT        (0x40U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VOUT_OV_FAULT_RESPONSE     (0x41U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_OV_WARN_LIMIT         (0x42U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_UV_WARN_LIMIT         (0x43U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_UV_FAULT_LIMIT        (0x44U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VOUT_UV_FAULT_RESPONSE     (0x45U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_OC_FAULT_LIMIT        (0x46U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_IOUT_OC_FAULT_RESPONSE     (0x47U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_OC_LV_FAULT_LIMIT     (0x48U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_IOUT_OC_LV_FAULT_RESPONSE  (0x49U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_OC_WARN_LIMIT         (0x4AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_UC_FAULT_LIMIT        (0x4BU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_IOUT_UC_FAULT_RESPONSE     (0x4CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x4DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x4EU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_OT_FAULT_LIMIT             (0x4FU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_OT_FAULT_RESPONSE          (0x50U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_OT_WARN_LIMIT              (0x51U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_UT_WARN_LIMIT              (0x52U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_UT_FAULT_LIMIT             (0x53U)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_UT_FAULT_RESPONSE          (0x54U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_OV_FAULT_LIMIT         (0x55U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VIN_OV_FAULT_RESPONSE      (0x56U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_OV_WARN_LIMIT          (0x57U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_UV_WARN_LIMIT          (0x58U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_UV_FAULT_LIMIT         (0x59U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VIN_UV_FAULT_RESPONSE      (0x5AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IIN_OC_FAULT_LIMIT         (0x5BU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_IIN_OC_FAULT_RESPONSE      (0x5CU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IIN_OC_WARN_LIMIT          (0x5DU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POWER_GOOD_ON              (0x5EU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POWER_GOOD_OFF             (0x5FU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TON_DELAY                  (0x60U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TON_RISE                   (0x61U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TON_MAX_FAULT_LIMIT        (0x62U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_TON_MAX_FAULT_RESPONSE     (0x63U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TOFF_DELAY                 (0x64U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TOFF_FALL                  (0x65U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TOFF_MAX_WARN_LIMIT        (0x66U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x67U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POUT_OP_FAULT_LIMIT        (0x68U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_POUT_OP_FAULT_RESPONSE     (0x69U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POUT_OP_WARN_LIMIT         (0x6AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_PIN_OP_WARN_LIMIT          (0x6BU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x6CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x6DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x6EU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x6FU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x70U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x71U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x72U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x73U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x74U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x75U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x76U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x77U)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_BYTE                (0x78U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_STATUS_WORD                (0x79U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_VOUT                (0x7AU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_IOUT                (0x7BU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_INPUT               (0x7CU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_TEMPERATURE         (0x7DU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_CML                 (0x7EU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_OTHER               (0x7FU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_MFR_SPECIFIC        (0x80U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_FANS_1_2            (0x81U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_FANS_3_4            (0x82U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x83U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x84U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x85U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_READ_EIN                   (0x86U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_READ_EOUT                  (0x87U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_VIN                   (0x88U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_IIN                   (0x89U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_VCAP                  (0x8AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_VOUT                  (0x8BU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_IOUT                  (0x8CU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_TEMPERATURE_1         (0x8DU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_TEMPERATURE_2         (0x8EU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_TEMPERATURE_3         (0x8FU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FAN_SPEED_1           (0x90U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FAN_SPEED_2           (0x91U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FAN_SPEED_3           (0x92U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FAN_SPEED_4           (0x93U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_DUTY_CYCLE            (0x94U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FREQUENCY             (0x95U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_POUT                  (0x96U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_PIN                   (0x97U)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_PMBUS_REVISION             (0x98U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_ID                     (0x99U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_MODEL                  (0x9AU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_REVISION               (0x9BU)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_LOCATION               (0x9CU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_DATE                   (0x9DU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_SERIAL                 (0x9EU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD APP_PROFILE_SUPPORT        (0x9FU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_VIN_MIN                (0xA0U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_VIN_MAX                (0xA1U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_IIN_MAX                (0xA2U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_PIN_MAX                (0xA3U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_VOUT_MIN               (0xA4U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_VOUT_MAX               (0xA5U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_IOUT_MAX               (0xA6U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_POUT_MAX               (0xA7U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_TAMBIENT_MAX           (0xA8U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_TAMBIENT_MIN           (0xA9U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_EFFICIENCY_LL          (0xAAU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_EFFICIENCY_HL          (0xABU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_MFR_PIN_ACURRACY           (0xACU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_IC_DEVICE              (0xADU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_IC_DEVICE_REV          (0xAEU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xAFU)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_00               (0xB0U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_01               (0xB1U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_02               (0xB2U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_03               (0xB3U)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_04               (0xB4U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_05               (0xB5U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_06               (0xB6U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_07               (0xB7U)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_08               (0xB8U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_09               (0xB9U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_10               (0xBAU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_11               (0xBBU)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_12               (0xBCU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_13               (0xBDU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_14               (0xBEU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_15               (0xBFU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_MAX_TEMP_1             (0xC0U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_MAX_TEMP_2             (0xC1U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_MAX_TEMP_3             (0xC2U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC3U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC4U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC5U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC6U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC7U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC8U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC9U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCAU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCBU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCCU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCDU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCEU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCFU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_LIGHT_LOAD_ENB         (0xD0U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_01            (0xD1U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_02            (0xD2U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_03            (0xD3U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_04            (0xD4U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_05            (0xD5U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_06            (0xD6U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_07            (0xD7U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_08            (0xD8U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_ROM_MODE                   (0xD9U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_USER_RAM_00                (0xDAU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PHASE_CONTROL          (0xDBU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_IOUT_OC_FAULT_LIMIT_LOW(0xDCU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_VIN_SCALE              (0xDDU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_VIN_OFFSET             (0xDEU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_READ_TEMPERATURE_4     (0xDFU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_OT_LIMIT_1             (0xE0U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_OT_LIMIT_2             (0xE1U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PARM_INFO              (0xE2U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PARM_VALUE             (0xE3U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_CMDS_DCDC_PAGED        (0xE4U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_CMDS_DCDC_NONPAGED     (0xE5U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_CMDS_PFC               (0xE6U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SETUP_ID               (0xE7U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_OT_LIMIT_3             (0xE8U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_OT_LIMIT_4             (0xE9U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_DEADBAND_CONFIG        (0xEAU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PIN_CAL_A              (0xEBU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PIN_CAL_B              (0xECU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PIN_CAL_C              (0xEDU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PIN_CAL_D              (0xEEU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_TEMP_CAL_OFFSET        (0xEFU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_DEBUG_BUFFER           (0xF0U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_TEMP_CAL_GAIN          (0xF1U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_STATUS_BIT_MASK        (0xF2U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_35            (0xF3U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_36            (0xF4U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_37            (0xF5U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_38            (0xF6U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_39            (0xF7U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_VOUT_CAL_MONITOR       (0xF8U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_ROM_MODE_WITH_PASSWORD     (0xF9U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_42            (0xFAU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_43            (0xFBU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_44            (0xFCU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_DEVICE_ID              (0xFDU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_COMMAND       (0xFEU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_PMBUS_COMMAND_EXT          (0xFFU)
 }
};

//*****************************************************************************
// the function prototypes
//*****************************************************************************

//! \brief Initialize PMBus module
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] address Address of the PMBus module in slave mode
//! \param[in] buffer Address of a buffer for the PMBus_Stack_Obj object
//! \return true if PMBus initialization was successful, else false
//! \note while this function does enable PMBus interrupts, the user must
//! register the interrupt service routine to handle all interrupts, and call
//! the appropriate handler within that ISR
//! \note buffer must point to an array of at least 4 words
//!
extern bool
PMBus_Stack_initModule( PMBus_Stack_Handle hnd , const uint32_t moduleBase,
        uint16_t *buffer);

//! \brief Default Transaction Handler
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//!
extern int32_t PMBus_Stack_defaultTransactionHandler(PMBus_Stack_Handle hnd);

//! \brief Set Module Base Address member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] address Address of the PMBus module in slave mode
//!
static inline void PMBus_Stack_Obj_setModuleBase(PMBus_Stack_Handle hnd,
        const uint32_t address)
{
    hnd->moduleBase  = address;
}

//! \brief Get Module Base Address member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return Module Base Address of the PMBus module
//!
static inline uint32_t PMBus_Stack_Obj_getModuleBase(PMBus_Stack_Handle hnd)
{
    return(hnd->moduleBase);
}

//! \brief Set Module Status member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] status Status of the PMBus module
//!
static inline void PMBus_Stack_Obj_setModuleStatus(PMBus_Stack_Handle hnd,
        const uint32_t status)
{
    hnd->moduleStatus  = status;
}

//! \brief Get Module Status member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return Status of the PMBus module
//!
static inline uint32_t
PMBus_Stack_Obj_getModuleStatus(PMBus_Stack_Handle hnd)
{
    return(hnd->moduleStatus);
}

//! \brief Set Mode member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] mode mode of the PMBus module
//!
static inline void PMBus_Stack_Obj_setMode(PMBus_Stack_Handle hnd,
        const PMBus_Stack_mode mode)
{
    hnd->mode  = mode;
}

//! \brief Get Mode member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return mode mode of the PMBus module
//!
static inline PMBus_Stack_mode
PMBus_Stack_Obj_getMode(PMBus_Stack_Handle hnd)
{
    return(hnd->mode);
}

//! \brief Set Address member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] address Address of the PMBus module in slave mode
//!
static inline void PMBus_Stack_Obj_setAddress(PMBus_Stack_Handle hnd,
        const uint16_t address)
{
    hnd->slaveAddress  = address;
}

//! \brief Get Address member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return address Address of the PMBus module in slave mode
//!
static inline uint16_t PMBus_Stack_Obj_getAddress(PMBus_Stack_Handle hnd)
{
    return(hnd->slaveAddress);
}

//! \brief Set Address member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] addressMask Address Mask of the PMBus module in slave mode
//!
static inline void PMBus_Stack_Obj_setAddressMask(PMBus_Stack_Handle hnd,
        const uint16_t addressMask)
{
    hnd->slaveAddressMask  = addressMask;
}

//! \brief Get Address member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return addressMask Address Mask of the PMBus module in slave mode
//!
static inline uint16_t PMBus_Stack_Obj_getAddressMask(PMBus_Stack_Handle hnd)
{
    return(hnd->slaveAddressMask);
}

//! \brief Set Current State of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] state current state of the PMBus state machine
//!
static inline void PMBus_Stack_Obj_setCurrentState(PMBus_Stack_Handle hnd,
        const PMBus_Stack_State state)
{
    hnd->currentState  = state;
}

//! \brief Get Current State of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return current state of the PMBus state machine
//!
static inline PMBus_Stack_State
PMBus_Stack_Obj_getCurrentState(PMBus_Stack_Handle hnd)
{
    return(hnd->currentState);
}

//! \brief Set Next State of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] state next state of the PMBus state machine
//!
static inline void 
PMBus_Stack_Obj_setNextState(PMBus_Stack_Handle hnd,
        const PMBus_Stack_State state)
{
    hnd->nextState  = state;
}

//! \brief Get Next State of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return next state of the PMBus state machine
//!
static inline PMBus_Stack_State
PMBus_Stack_Obj_getNextState(PMBus_Stack_Handle hnd)
{
    return(hnd->nextState);
}

//! \brief Set buffer pointer member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] Buffer Pointer to a buffer of size >= 4
//!
static inline void PMBus_Stack_Obj_setPtrBuffer(PMBus_Stack_Handle hnd,
        uint16_t *buffer)
{
    hnd->ptrBuffer  = buffer;
}

//! \brief Get buffer pointer member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return Buffer Pointer to a buffer of size >= 4
//!
static inline uint16_t* PMBus_Stack_Obj_getPtrBuffer(PMBus_Stack_Handle hnd)
{
    return(hnd->ptrBuffer);
}

//! \brief Set Current pointer member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] currPtr Current position in the buffer
//!
static inline void PMBus_Stack_Obj_setCurrPtr(PMBus_Stack_Handle hnd,
        uint16_t *currPtr)
{
    hnd->currPtr  = currPtr;
}

//! \brief Get Current pointer member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return currPtr Current position in the buffer
//!
static inline uint16_t* PMBus_Stack_Obj_getCurrPtr(PMBus_Stack_Handle hnd)
{
    return(hnd->currPtr);
}

//! \brief Set nBytes member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] nBytes Number of bytes sent/received
//!
static inline void PMBus_Stack_Obj_setNBytes(PMBus_Stack_Handle hnd,
        const uint16_t nBytes)
{
    hnd->nBytes  = nBytes;
}

//! \brief Get nBytes member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return Number of bytes sent/received
//!
static inline uint16_t PMBus_Stack_Obj_getNBytes(PMBus_Stack_Handle hnd)
{
    return(hnd->nBytes);
}

//! \brief Set PECValid member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] PECValid boolean, 1 - PEC is valid, 0 - PEC is invalid
//!
static inline void PMBus_Stack_Obj_setPECValid(PMBus_Stack_Handle hnd,
        const bool PECValid)
{
    hnd->PECValid  = PECValid;
}

//! \brief Get PECValid member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return boolean, 1 - PEC is valid, 0 - PEC is invalid
//!
static inline bool PMBus_Stack_Obj_getPECValid(PMBus_Stack_Handle hnd)
{
    return(hnd->PECValid);
}

//! \brief Set current transaction member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] transaction one of the PMBus_Transaction enumerations
//!
static inline void PMBus_Stack_Obj_setTransaction(PMBus_Stack_Handle hnd,
        const PMBus_Transaction transaction)
{
    hnd->transaction  = transaction;
}

//! \brief Get current transaction member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \return transaction one of the PMBus_Transaction enumerations
//!
static inline PMBus_Transaction
PMBus_Stack_Obj_getTransaction(PMBus_Stack_Handle hnd)
{
    return(hnd->transaction);
}

//! \brief Set transaction handler member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] transaction one of the PMBus_Transaction enumerations
//! \param[in] trnHandler pointer to the function to handle the transaction
//!
static inline void
PMBus_Stack_Obj_setTransactionHandler(PMBus_Stack_Handle hnd,
        const PMBus_Transaction transaction, transactionHandler tH)
{
    hnd->trnHnd[transaction]  = tH;
}

//! \brief Get transaction handler member of the PMBus_Stack_Obj object
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! \param[in] transaction one of the PMBus_Transaction enumerations
//! \return  trnHandler pointer to the function to handle the transaction
//!
static inline transactionHandler
PMBus_Stack_Obj_getTransactionHandler(PMBus_Stack_Handle hnd,
        const PMBus_Transaction transaction)
{
    return(hnd->trnHnd[transaction]);
}

//! \brief Checks if the command matches a given transaction type
//! \param[in] command command to be checked against a transaction
//! \param[in] transaction one of the PMBus_Transaction enumerations
//!
//! This function will query PMBus_Stack_commandTransactionMap for
//! the given command to see if it can find a match for the given
//! transaction.
//!
//! \return \b true if the command does match the given transaction type,
//! \b false otherwise
//!
static bool
PMBus_Stack_doesCommandMatchTransaction(const uint16_t command,
		                     const PMBus_Transaction transaction)
{
	uint16_t base, downshift;
	PMBus_Transaction trn;
	bool status = false;
	// The base address in the commandMap is command/4
	base   =  (command >> 2U) & 0x7FU;
	// The transaction is either field0, 1, 2, or 3, we are
	// going to determine how much right shift we need to have
	// our reference transaction in the lowest nibble. Since
	// each field if 4 bits, we multiply by 4
	downshift =  (command & 0x3U) << 2U;
	// Find the transaction nibble in the commandMap
	trn = (PMBus_Transaction)
			((PMBus_Stack_commandTransactionMap[base].ui16 >>
					    downshift) & 0x0FU);

	if(trn == transaction )
	{
		status = true;
	}

	return(status);
}


#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _PMBUS_STACK_CONFIG_H_ definition
