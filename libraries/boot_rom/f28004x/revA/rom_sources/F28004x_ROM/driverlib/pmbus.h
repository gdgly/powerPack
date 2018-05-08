#ifndef __PMBUS_H__
#define __PMBUS_H__
//#############################################################################
//
// FILE:   pmbus.h
//
// TITLE:  C28x PMBUS Driver
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//#############################################################################

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
//! \addtogroup pmbus_api
//! @{
//
//
// Defines for the API.
//
//*****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_pmbus.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"
#include "interrupt.h"

//! Specifies whether to include the crc8 table in the 
//! library build
#define PMBUS_INCLUDE_CRC8_TABLE        0x1U

//*****************************************************************************
// PMBMC Commands -> used in PMBus_configMaster()
//*****************************************************************************
//! Enable Process call message
#define PMBUS_MASTER_ENABLE_PRC_CALL    0x00100000U        
//! Enable Group command message
#define PMBUS_MASTER_ENABLE_GRP_CMD     0x00080000U        
//! Enable PEC byte
#define PMBUS_MASTER_ENABLE_PEC         0x00040000U        
//! Enable Extended command
#define PMBUS_MASTER_ENABLE_EXT_CMD     0x00020000U        
//! Enable Command word
#define PMBUS_MASTER_ENABLE_CMD         0x00010000U        
//! Enable read
#define PMBUS_MASTER_ENABLE_READ        0x00000001U        

//*****************************************************************************
// PMBINTM Commands -> used in PMBus_enableInterrupt() and 
// PMBus_disableInterrupt()
//*****************************************************************************
//! Bus Free Interrupt 
#define PMBUS_INT_BUS_FREE                  0x00000001U   
//! Clock Low Timeout Interrupt 
#define PMBUS_INT_CLK_LOW_TIMEOUT           0x00000002U   
//! Data Ready Interrupt 
#define PMBUS_INT_DATA_READY                0x00000004U   
//! Data Request Interrupt 
#define PMBUS_INT_DATA_REQUEST              0x00000008U   
//! Slave Address Ready Interrupt 
#define PMBUS_INT_SLAVE_ADDR_READY          0x00000010U   
//! End of Message Interrupt 
#define PMBUS_INT_EOM                       0x00000020U   
//! Alert Detection Interrupt 
#define PMBUS_INT_ALERT                     0x00000040U   
//! Control Detection Interrupt 
#define PMBUS_INT_CONTROL                   0x00000080U   
//! Lost Arbitration Interrupt 
#define PMBUS_INT_LOST_ARB                  0x00000100U   
//! Clock High Detection Interrupt 
#define PMBUS_INT_CLK_HIGH_DETECT           0x00000200U   
//! all PMBUS interrupts
#define PMBUS_INT_ALL                       0x000003FFU   

//*****************************************************************************
// PMBSTS Commands -> returned by PMBus_getInterruptStatus()
//*****************************************************************************
//! Bus Free Interrupt 
#define PMBUS_INTSRC_BUS_FREE               0x00002000U   
//! Clock Low Timeout Interrupt 
#define PMBUS_INTSRC_CLK_LOW_TIMEOUT        0x00000100U   
//! Data Ready Interrupt 
#define PMBUS_INTSRC_DATA_READY             0x00000008U   
//! Data Request Interrupt 
#define PMBUS_INTSRC_DATA_REQUEST           0x00000010U   
//! Slave Address Ready Interrupt 
#define PMBUS_INTSRC_SLAVE_ADDR_READY       0x00000400U   
//! End of Message Interrupt 
#define PMBUS_INTSRC_EOM                    0x00000020U   
//! Alert Detection Interrupt 
#define PMBUS_INTSRC_ALERT                  0x00010000U   
//! Control Detection Interrupt 
#define PMBUS_INTSRC_CONTROL                0x00020000U   
//! Lost Arbitration Interrupt 
#define PMBUS_INTSRC_LOST_ARB               0x00004000U   
//! Clock High Detection Interrupt 
#define PMBUS_INTSRC_CLK_HIGH_DETECT        0x00000200U   

//*****************************************************************************
// PMBSC Commands -> They are used in the configWord passed to 
// PMBus_configSlave()
//*****************************************************************************
//! Enable manual slave ack modes
#define PMBUS_SLAVE_ENABLE_MANUAL_ACK        0x00000080U   
//! Enable PEC byte processing
#define PMBUS_SLAVE_ENABLE_PEC_PROCESSING    0x00008000U 
//! Transmit PEC at end of transaction
#define PMBUS_SLAVE_TRANSMIT_PEC             0x00080000U   
//! Data Request flag generated after receipt of command code, firmware 
//! required to issue ACK to continue message
#define PMBUS_SLAVE_ENABLE_MANUAL_CMD_ACK    0x00100000U   
//! any bits cleared in slave address mask make that bit a don't care
#define PMBUS_SLAVE_DISABLE_ADDRESS_MASK     0x0000007FU   
//! Slave will auto acknowledge every received byte
#define PMBUS_SLAVE_AUTO_ACK_1_BYTES         0x00000000U   
//! Slave will auto acknowledge every 2 received bytes
#define PMBUS_SLAVE_AUTO_ACK_2_BYTES         0x00200000U   
//! Slave will auto acknowledge every 3 received bytes
#define PMBUS_SLAVE_AUTO_ACK_3_BYTES         0x00400000U   
//! Slave will auto acknowledge every 4 received bytes
#define PMBUS_SLAVE_AUTO_ACK_4_BYTES         0x00600000U   
//*****************************************************************************
// PMBCTRL Commands
//*****************************************************************************
//! Reset control state machines
#define PMBUS_RESET                         0x00000001U     
//! Enable Slave Alert
#define PMBUS_ENABLE_SLAVE_ALERT            0x00000002U     
//! Set Clock Low Timeout Interrupt generation on falling edge
#define PMBUS_SET_BUS_LO_INT_FALLING_EDGE   0x00000004U     
//! Set Control Interrupt to be generated on rising edge
#define PMBUS_SET_CNTL_INT_RISING_EDGE      0x00000020U     
//! Enable PMBus Current Source A Control
#define PMBUS_ENABLE_IBIAS_A_EN             0x00040000U     
//! Enable PMBus Current Source B Control
#define PMBUS_ENABLE_IBIAS_B_EN             0x00080000U     
//! Disable Clock Low Timeout
#define PMBUS_DISABLE_CLK_LOW_TIMEOUT       0x00100000U     
//! Enable PMBus Slave Enable
#define PMBUS_ENABLE_SLAVE_MODE             0x00200000U     
//! Enable PMBus Master Enable
#define PMBUS_ENABLE_MASTER_MODE            0x00400000U     

//*****************************************************************************                                                
//PMBus Version 1.2 command number constants:
//*****************************************************************************
#define PMBUS_CMD_PAGE                          0x00U
#define PMBUS_CMD_OPERATION                     0x01U
#define PMBUS_CMD_ON_OFF_CONFIG                 0x02U
#define PMBUS_CMD_CLEAR_FAULTS                  0x03U
#define PMBUS_CMD_PHASE                         0x04U
#define PMBUS_CMD_PAGE_PLUS_WRITE               0x05U
#define PMBUS_CMD_PAGE_PLUS_READ                0x06U
                                             // 0x07-0x0F Reserved
#define PMBUS_CMD_WRITE_PROTECT                 0x10U
#define PMBUS_CMD_STORE_DEFAULT_ALL             0x11U
#define PMBUS_CMD_RESTORE_DEFAULT_ALL           0x12U
#define PMBUS_CMD_STORE_DEFAULT_CODE            0x13U
#define PMBUS_CMD_RESTORE_DEFAULT_CODE          0x14U
#define PMBUS_CMD_STORE_USER_ALL                0x15U
#define PMBUS_CMD_RESTORE_USER_ALL              0x16U
#define PMBUS_CMD_STORE_USER_CODE               0x17U
#define PMBUS_CMD_RESTORE_USER_CODE             0x18U
#define PMBUS_CMD_CAPABILITY                    0x19U
#define PMBUS_CMD_QUERY                         0x1AU
#define PMBUS_CMD_SMBALERT_MASK                 0x1BU
                                             // 0x1C - 0x1F Reserved
#define PMBUS_CMD_VOUT_MODE                     0x20U
#define PMBUS_CMD_VOUT_COMMAND                  0x21U
#define PMBUS_CMD_VOUT_TRIM                     0x22U
#define PMBUS_CMD_VOUT_CAL_OFFSET               0x23U
#define PMBUS_CMD_VOUT_MAX                      0x24U
#define PMBUS_CMD_VOUT_MARGIN_HIGH              0x25U
#define PMBUS_CMD_VOUT_MARGIN_LOW               0x26U
#define PMBUS_CMD_VOUT_TRANSITION_RATE          0x27U
#define PMBUS_CMD_VOUT_DROOP                    0x28U
#define PMBUS_CMD_VOUT_SCALE_LOOP               0x29U
#define PMBUS_CMD_VOUT_SCALE_MONITOR            0x2AU
                                             // 0x2B - 0x2F Reserved
#define PMBUS_CMD_COEFFICIENTS                  0x30U
#define PMBUS_CMD_POUT_MAX                      0x31U
#define PMBUS_CMD_MAX_DUTY                      0x32U
#define PMBUS_CMD_FREQUENCY_SWITCH              0x33U
                                             // 0x34 Reserved
#define PMBUS_CMD_VIN_ON                        0x35U
#define PMBUS_CMD_VIN_OFF                       0x36U
#define PMBUS_CMD_INTERLEAVE                    0x37U
#define PMBUS_CMD_IOUT_CAL_GAIN                 0x38U
#define PMBUS_CMD_IOUT_CAL_OFFSET               0x39U
#define PMBUS_CMD_FAN_CONFIG_1_2                0x3AU
#define PMBUS_CMD_FAN_COMMAND_1                 0x3BU
#define PMBUS_CMD_FAN_COMMAND_2                 0x3CU
#define PMBUS_CMD_FAN_CONFIG_3_4                0x3DU
#define PMBUS_CMD_FAN_COMMAND_3                 0x3EU
#define PMBUS_CMD_FAN_COMMAND_4                 0x3FU
#define PMBUS_CMD_VOUT_OV_FAULT_LIMIT           0x40U
#define PMBUS_CMD_VOUT_OV_FAULT_RESPONSE        0x41U
#define PMBUS_CMD_VOUT_OV_WARN_LIMIT            0x42U
#define PMBUS_CMD_VOUT_UV_WARN_LIMIT            0x43U
#define PMBUS_CMD_VOUT_UV_FAULT_LIMIT           0x44U
#define PMBUS_CMD_VOUT_UV_FAULT_RESPONSE        0x45U
#define PMBUS_CMD_IOUT_OC_FAULT_LIMIT           0x46U
#define PMBUS_CMD_IOUT_OC_FAULT_RESPONSE        0x47U
#define PMBUS_CMD_IOUT_OC_LV_FAULT_LIMIT        0x48U
#define PMBUS_CMD_IOUT_OC_LV_FAULT_RESPONSE     0x49U
#define PMBUS_CMD_IOUT_OC_WARN_LIMIT            0x4AU
#define PMBUS_CMD_IOUT_UC_FAULT_LIMIT           0x4BU
#define PMBUS_CMD_IOUT_UC_FAULT_RESPONSE        0x4CU
                                             // 0x4D – 0x4E Reserved
#define PMBUS_CMD_OT_FAULT_LIMIT                0x4FU
#define PMBUS_CMD_OT_FAULT_RESPONSE             0x50U
#define PMBUS_CMD_OT_WARN_LIMIT                 0x51U
#define PMBUS_CMD_UT_WARN_LIMIT                 0x52U
#define PMBUS_CMD_UT_FAULT_LIMIT                0x53U
#define PMBUS_CMD_UT_FAULT_RESPONSE             0x54U
#define PMBUS_CMD_VIN_OV_FAULT_LIMIT            0x55U
#define PMBUS_CMD_VIN_OV_FAULT_RESPONSE         0x56U
#define PMBUS_CMD_VIN_OV_WARN_LIMIT             0x57U
#define PMBUS_CMD_VIN_UV_WARN_LIMIT             0x58U
#define PMBUS_CMD_VIN_UV_FAULT_LIMIT            0x59U
#define PMBUS_CMD_VIN_UV_FAULT_RESPONSE         0x5AU
#define PMBUS_CMD_IIN_OC_FAULT_LIMIT            0x5BU // (For CBC current limit)
#define PMBUS_CMD_IIN_OC_FAULT_RESPONSE         0x5CU
#define PMBUS_CMD_IIN_OC_WARN_LIMIT             0x5DU
#define PMBUS_CMD_POWER_GOOD_ON                 0x5EU
#define PMBUS_CMD_POWER_GOOD_OFF                0x5FU
#define PMBUS_CMD_TON_DELAY                     0x60U
#define PMBUS_CMD_TON_RISE                      0x61U
#define PMBUS_CMD_TON_MAX_FAULT_LIMIT           0x62U
#define PMBUS_CMD_TON_MAX_FAULT_RESPONSE        0x63U
#define PMBUS_CMD_TOFF_DELAY                    0x64U
#define PMBUS_CMD_TOFF_FALL                     0x65U
#define PMBUS_CMD_TOFF_MAX_WARN_LIMIT           0x66U
                                             // 0x67 Rsvd Deleted PMBus v1.1
#define PMBUS_CMD_POUT_OP_FAULT_LIMIT           0x68U
#define PMBUS_CMD_POUT_OP_FAULT_RESPONSE        0x69U
#define PMBUS_CMD_POUT_OP_WARN_LIMIT            0x6AU
#define PMBUS_CMD_PIN_OP_WARN_LIMIT             0x6BU
                                             // 0x6C - 0x77 Reserved
#define PMBUS_CMD_STATUS_BYTE                   0x78U
#define PMBUS_CMD_STATUS_WORD                   0x79U
#define PMBUS_CMD_STATUS_VOUT                   0x7AU
#define PMBUS_CMD_STATUS_IOUT                   0x7BU
#define PMBUS_CMD_STATUS_INPUT                  0x7CU
#define PMBUS_CMD_STATUS_TEMPERATURE            0x7DU
#define PMBUS_CMD_STATUS_CML                    0x7EU
#define PMBUS_CMD_STATUS_OTHER                  0x7FU
#define PMBUS_CMD_STATUS_MFR_SPECIFIC           0x80U
#define PMBUS_CMD_STATUS_FANS_1_2               0x81U
#define PMBUS_CMD_STATUS_FANS_3_4               0x82U
                                             // 0x83 - 0x85 Reserved
#define PMBUS_CMD_READ_EIN                      0x86U
#define PMBUS_CMD_READ_EOUT                     0x87U
#define PMBUS_CMD_READ_VIN                      0x88U
#define PMBUS_CMD_READ_IIN                      0x89U
#define PMBUS_CMD_READ_VCAP                     0x8AU
#define PMBUS_CMD_READ_VOUT                     0x8BU
#define PMBUS_CMD_READ_IOUT                     0x8CU
#define PMBUS_CMD_READ_TEMPERATURE_1            0x8DU
#define PMBUS_CMD_READ_TEMPERATURE_2            0x8EU
#define PMBUS_CMD_READ_TEMPERATURE_3            0x8FU
#define PMBUS_CMD_READ_FAN_SPEED_1              0x90U
#define PMBUS_CMD_READ_FAN_SPEED_2              0x91U
#define PMBUS_CMD_READ_FAN_SPEED_3              0x92U
#define PMBUS_CMD_READ_FAN_SPEED_4              0x93U
#define PMBUS_CMD_READ_DUTY_CYCLE               0x94U
#define PMBUS_CMD_READ_FREQUENCY                0x95U
#define PMBUS_CMD_READ_POUT                     0x96U
#define PMBUS_CMD_READ_PIN                      0x97U
#define PMBUS_CMD_PMBUS_REVISION                0x98U
#define PMBUS_CMD_MFR_ID                        0x99U
#define PMBUS_CMD_MFR_MODEL                     0x9AU
#define PMBUS_CMD_MFR_REVISION                  0x9BU
#define PMBUS_CMD_MFR_LOCATION                  0x9CU
#define PMBUS_CMD_MFR_DATE                      0x9DU
#define PMBUS_CMD_MFR_SERIAL                    0x9EU
#define PMBUS_CMD APP_PROFILE_SUPPORT           0x9FU 
#define PMBUS_CMD_MFR_VIN_MIN                   0xA0U
#define PMBUS_CMD_MFR_VIN_MAX                   0xA1U
#define PMBUS_CMD_MFR_IIN_MAX                   0xA2U
#define PMBUS_CMD_MFR_PIN_MAX                   0xA3U
#define PMBUS_CMD_MFR_VOUT_MIN                  0xA4U
#define PMBUS_CMD_MFR_VOUT_MAX                  0xA5U
#define PMBUS_CMD_MFR_IOUT_MAX                  0xA6U
#define PMBUS_CMD_MFR_POUT_MAX                  0xA7U
#define PMBUS_CMD_MFR_TAMBIENT_MAX              0xA8U
#define PMBUS_CMD_MFR_TAMBIENT_MIN              0xA9U
#define PMBUS_CMD_MFR_EFFICIENCY_LL             0xAAU
#define PMBUS_CMD_MFR_EFFICIENCY_HL             0xABU
#define PMBUS_CMD_MFR_PIN_ACURRACY              0xACU
#define PMBUS_CMD_MFR_IC_DEVICE                 0xADU
#define PMBUS_CMD_MFR_IC_DEVICE_REV             0xAEU
                                             // 0xAF Reserved                                                                                               
#define PMBUS_CMD_USER_DATA_00                  0xB0U     
#define PMBUS_CMD_USER_DATA_01                  0xB1U     
#define PMBUS_CMD_USER_DATA_02                  0xB2U     
#define PMBUS_CMD_USER_DATA_03                  0xB3U     
#define PMBUS_CMD_USER_DATA_04                  0xB4U
#define PMBUS_CMD_USER_DATA_05                  0xB5U
#define PMBUS_CMD_USER_DATA_06                  0xB6U
#define PMBUS_CMD_USER_DATA_07                  0xB7U
#define PMBUS_CMD_USER_DATA_08                  0xB8U
#define PMBUS_CMD_USER_DATA_09                  0xB9U
#define PMBUS_CMD_USER_DATA_10                  0xBAU
#define PMBUS_CMD_USER_DATA_11                  0xBBU
#define PMBUS_CMD_USER_DATA_12                  0xBCU
#define PMBUS_CMD_USER_DATA_13                  0xBDU
#define PMBUS_CMD_USER_DATA_14                  0xBEU
#define PMBUS_CMD_USER_DATA_15                  0xBFU
#define PMBUS_CMD_MFR_MAX_TEMP_1                0xC0U
#define PMBUS_CMD_MFR_MAX_TEMP_2                0xC1U 
#define PMBUS_CMD_MFR_MAX_TEMP_3                0xC2U 
                                             // 0xC3-0xCF Reserved                                                                                       
#define PMBUS_CMD_MFR_LIGHT_LOAD_ENB            0xD0U      
#define PMBUS_CMD_MFR_SPECIFIC_01               0xD1U
#define PMBUS_CMD_MFR_SPECIFIC_02               0xD2U                                          
#define PMBUS_CMD_MFR_SPECIFIC_03               0xD3U      
#define PMBUS_CMD_MFR_SPECIFIC_04               0xD4U      
#define PMBUS_CMD_MFR_SPECIFIC_05               0xD5U      
#define PMBUS_CMD_MFR_SPECIFIC_06               0xD6U                              
#define PMBUS_CMD_MFR_SPECIFIC_07               0xD7U      
#define PMBUS_CMD_MFR_SPECIFIC_08               0xD8U      
#define PMBUS_CMD_ROM_MODE                      0xD9U      
#define PMBUS_CMD_USER_RAM_00                   0xDAU                             
#define PMBUS_CMD_MFR_PHASE_CONTROL             0xDBU                             
#define PMBUS_CMD_MFR_IOUT_OC_FAULT_LIMIT_LOW   0xDCU                                                                                                    
#define PMBUS_CMD_MFR_VIN_SCALE                 0xDDU    
#define PMBUS_CMD_MFR_VIN_OFFSET                0xDEU    
#define PMBUS_CMD_MFR_READ_TEMPERATURE_4        0xDFU    
#define PMBUS_CMD_MFR_OT_LIMIT_1                0xE0U     
#define PMBUS_CMD_MFR_OT_LIMIT_2                0xE1U     
#define PMBUS_CMD_MFR_PARM_INFO                 0xE2U     
#define PMBUS_CMD_MFR_PARM_VALUE                0xE3U     
#define PMBUS_CMD_MFR_CMDS_DCDC_PAGED           0xE4U     
#define PMBUS_CMD_MFR_CMDS_DCDC_NONPAGED        0xE5U     
#define PMBUS_CMD_MFR_CMDS_PFC                  0xE6U     
#define PMBUS_CMD_MFR_SETUP_ID                  0xE7U     
#define PMBUS_CMD_MFR_OT_LIMIT_3                0xE8U     
#define PMBUS_CMD_MFR_OT_LIMIT_4                0xE9U     
#define PMBUS_CMD_MFR_DEADBAND_CONFIG           0xEAU    
#define PMBUS_CMD_MFR_PIN_CAL_A                 0xEBU    
#define PMBUS_CMD_MFR_PIN_CAL_B                 0xECU                
#define PMBUS_CMD_MFR_PIN_CAL_C                 0xEDU    
#define PMBUS_CMD_MFR_PIN_CAL_D                 0xEEU                                                                            
#define PMBUS_CMD_MFR_TEMP_CAL_OFFSET           0xEFU    
#define PMBUS_CMD_MFR_DEBUG_BUFFER              0xF0U     
#define PMBUS_CMD_MFR_TEMP_CAL_GAIN             0xF1U     
#define PMBUS_CMD_MFR_STATUS_BIT_MASK           0xF2U     
#define PMBUS_CMD_MFR_SPECIFIC_35               0xF3U                                                                                         
#define PMBUS_CMD_MFR_SPECIFIC_36               0xF4U     
#define PMBUS_CMD_MFR_SPECIFIC_37               0xF5U                                                                             
#define PMBUS_CMD_MFR_SPECIFIC_38               0xF6U                                                                                         
#define PMBUS_CMD_MFR_SPECIFIC_39               0xF7U                                                                             
#define PMBUS_CMD_MFR_VOUT_CAL_MONITOR          0xF8U                                                                             
#define PMBUS_CMD_ROM_MODE_WITH_PASSWORD        0xF9U                                                                             
#define PMBUS_CMD_MFR_SPECIFIC_42               0xFAU                                                                            
#define PMBUS_CMD_MFR_SPECIFIC_43               0xFBU                                                                            
#define PMBUS_CMD_MFR_SPECIFIC_44               0xFCU                                                                            
#define PMBUS_CMD_MFR_DEVICE_ID                 0xFDU                                       
#define PMBUS_CMD_MFR_SPECIFIC_COMMAND          0xFEU    
#define PMBUS_CMD_PMBUS_COMMAND_EXT             0xFFU

//*****************************************************************************
//
//! Transaction Descriptor
//! Defines the transaction type, used in the command object
//! and passed to PMBus_configTransfer()
//
//*****************************************************************************
typedef enum{
  PMBUS_TRANSACTION_NONE          = 0U,  //!< No Transaction
  PMBUS_TRANSACTION_QUICKCOMMAND  = 1U,  //!< Quick Command
  PMBUS_TRANSACTION_WRITEBYTE     = 2U,  //!< Write single byte
  PMBUS_TRANSACTION_READBYTE      = 3U,  //!< Read single byte
  PMBUS_TRANSACTION_SENDBYTE      = 4U,  //!< Send Byte
  PMBUS_TRANSACTION_RECEIVEBYTE   = 5U,  //!< Receive Byte
  PMBUS_TRANSACTION_BLOCKWRITE    = 6U,  //!< Block Write (up to 255 bytes)
  PMBUS_TRANSACTION_BLOCKREAD     = 7U,  //!< Block Read (up to 255 bytes)
  PMBUS_TRANSACTION_WRITEWORD     = 8U,  //!< Write word
  PMBUS_TRANSACTION_READWORD      = 9U,  //!< Read word
  PMBUS_TRANSACTION_BLOCKWRPC     = 10U  //!< Block write, then process call
}PMBus_Transaction;

//*****************************************************************************
// PMBUS Module Clock defines
//*****************************************************************************
//! Min SYSCLK input to PMBUS module
#define PMBUS_SYS_FREQ_MIN      10000000UL              
//! Max SYSCLK input to PMBUS module
#define PMBUS_SYS_FREQ_MAX      100000000UL             
//! Max module frequency of 10 MHz
#define PMBUS_MODULE_FREQ_MAX   10000000UL              
//! Min module frequency = min_sys_freq/32
#define PMBUS_MODULE_FREQ_MIN   (PMBUS_SYS_FREQ_MIN/32) 

//*****************************************************************************
//
//! Clock Mode Descriptor
//! Used in setting up the bus speed. There are three possible modes of 
//! operation:
//! -# Standard Mode 100 KHz
//! -# Fast Mode 400 KHz
//! -# Fast Mode Plus 1 MHz
//! Used in PMBus_configBusClock()
//
//*****************************************************************************
typedef enum{
  PMBUS_CLOCKMODE_STANDARD  = 0U,   //!< Standard mode 100 KHz
  PMBUS_CLOCKMODE_FAST      = 1U,   //!< Fast Mode 400 KHz
  PMBUS_CLOCKMODE_FASTPLUS  = 2U    //!< Fast Mode plus 1 MHz
}PMBus_ClockMode;


//*****************************************************************************
//
//! Access Type Descriptor
//! Used in PMBus_getCurrentAccessType() to determine if the device, in slave
//! mode, was accessed with read or write enabled.
//
//*****************************************************************************
typedef enum{
    PMBUS_ACCESSTYPE_WRITE  = 0U, //!< Slave last address for write transaction
    PMBUS_ACCESSTYPE_READ   = 1U  //!< Slave last address for read transaction
}PMBus_accessType;

//*****************************************************************************
//
//! Interrupt Edge Descriptor
//! Used in PMBus_setCtrlIntEdge() and PMBus_setClkLowTimeoutIntEdge() to set 
//! the edge, falling or rising, that triggers an interrupt
//
//*****************************************************************************
typedef enum{
    PMBUS_INTEDGE_FALLING   = 0U, //! Interrupt generated on falling edge
    PMBUS_INTEDGE_RISING    = 1U  //! Interrupt generated on rising edge
}PMBus_intEdge;

//*****************************************************************************
//
// globals
//
//*****************************************************************************
#if PMBUS_INCLUDE_CRC8_TABLE == 0x1U
// CRC table for the polynomial x^8+x^2+x^1+1 (0x7). File scope only
extern const uint16_t PMBus_crc8Table[256U];
#endif //PMBUS_INCLUDE_CRC8_TABLE == 0x1U

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an PMBUS base address.
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! This function determines if a PMBUS module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static bool
PMBus_isBaseValid(uint32_t base)
{
    return(base == PMBUSA_BASE);
}
#endif

//*****************************************************************************
//
//! Disables the PMBUS module.
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! This function resets the internal state machine of the PMBUS module and 
//! holds it in that state
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    HWREG(base + PMBUS_O_PMBCTRL) |= PMBUS_RESET;
    EDIS;
}

//*****************************************************************************
//
//! Enables the PMBUS module.
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! This function enables operation of the PMBUS module by removing it from the
//! reset state
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    HWREG(base + PMBUS_O_PMBCTRL) &= ~PMBUS_RESET;
    EDIS;
}


//*****************************************************************************
//
//! Enables PMBUS interrupt sources.
//!
//! \param base is the base address of the PMBUS instance used.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated PMBUS interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt;
//! disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b PMBUS_INT_BUS_FREE          - Bus Free Interrupt         
//! - \b PMBUS_INT_CLK_LOW_TIMEOUT   - Clock Low Timeout Interrupt         
//! - \b PMBUS_INT_DATA_READY        - Data Ready Interrupt         
//! - \b PMBUS_INT_DATA_REQUEST      - Data Request Interrupt         
//! - \b PMBUS_INT_SLAVE_ADDR_READY  - Slave Address Ready Interrupt         
//! - \b PMBUS_INT_EOM               - End of Message Interrupt         
//! - \b PMBUS_INT_ALERT             - Alert Detection Interrupt         
//! - \b PMBUS_INT_CONTROL           - Control Detection Interrupt         
//! - \b PMBUS_INT_LOST_ARB          - Lost Arbitration Interrupt         
//! - \b PMBUS_INT_CLK_HIGH_DETECT   - Clock High Detection Interrupt         
//! - \b PMBUS_INT_ALL               - all PMBUS interrupts        
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    //
    // Enable the desired basic interrupts i.e. clear their mask bits
    // in PMBINTM
    //
    HWREG(base + PMBUS_O_PMBINTM) &= ~(intFlags & 0x03FFU);
    EDIS;
}

//*****************************************************************************
//
//! Disables PMBUS interrupt sources.
//!
//! \param base is the base address of the PMBUS instance used.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//!
//! This function disables the indicated PMBUS interrupt sources.  Only
//! the sources that are enabled can be reflected to the processor interrupt;
//! disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter has the same definition as the \e intFlags
//! parameter to PMBus_enableInterrupt().
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    //
    // Disable the desired interrupts
    //
    HWREG(base + PMBUS_O_PMBINTM) |= (intFlags & 0x03FFU);
    EDIS;
}

//*****************************************************************************
//
//! Indicates whether or not the PMBUS bus is busy.
//!
//! \param status  the value of the status register (PMBUS_O_PMBSTS)
//!
//! This function returns an indication of whether or not the PMBUS bus is busy
//! 
//! \note The status register is cleared each time it is read, therefore, it 
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getInterruptStatus() and saved to a temporary variable for further 
//! processing
//!
//! \return Returns \b true if the PMBUS bus is busy; otherwise, returns
//! \b false.
//
//*****************************************************************************
static inline bool PMBus_isBusBusy(uint32_t status)
{
    return((bool)(status & PMBUS_PMBSTS_UNIT_BUSY));
}

//*****************************************************************************
//
//! Indicates whether or not the PEC is valid
//!
//! \param status  the value of the status register (PMBUS_O_PMBSTS)
//!
//! This function returns an indication of whether or not the received PEC
//! was valid
//! 
//! \note The status register is cleared each time it is read, therefore, it 
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getStatus() and saved to a temporary variable for further 
//! processing
//!
//! \return Returns \b true if the PEC is valid; otherwise, returns
//! \b false.
//
//*****************************************************************************
static inline bool PMBus_isPECValid(uint32_t status)
{
    return((bool)(status & PMBUS_PMBSTS_PEC_VALID));
}

//*****************************************************************************
//
//! Enable I2C mode
//!
//! \param base is the base address of the PMBUS instance used.
//!        
//! Set the PMBUS module to work in I2C mode
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_enableI2CMode(uint32_t base)
{
    // Locals
    uint32_t interruptState;
    
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;
    // Save off the interrupt state and disable them
    interruptState = HWREG(base + PMBUS_O_PMBINTM);
    HWREG(base + PMBUS_O_PMBINTM) = PMBUS_INT_ALL;
                                 
    // Set module to I2C mode
    HWREG(base + PMBUS_O_PMBCTRL) |= PMBUS_PMBCTRL_I2CMODE;
    
    // Restore the interrupt status
    HWREG(base + PMBUS_O_PMBINTM) = interruptState;
    EDIS;
}

//*****************************************************************************
//
//! Disable I2C mode
//!
//! \param base is the base address of the PMBUS instance used.
//!        
//! Set the PMBUS module to work in PMBUS mode
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_disableI2CMode(uint32_t base)
{
    // Locals
    uint32_t interruptState;
    
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;
    // Save off the interrupt state and disable them
    interruptState = HWREG(base + PMBUS_O_PMBINTM);
    HWREG(base + PMBUS_O_PMBINTM) = PMBUS_INT_ALL;
                                 
    // Set module to PMBUS mode
    HWREG(base + PMBUS_O_PMBCTRL) &= ~PMBUS_PMBCTRL_I2CMODE;
    
    // Restore the interrupt status
    HWREG(base + PMBUS_O_PMBINTM) = interruptState;
    EDIS;
}

//*****************************************************************************
//
//! Read the status register
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! \return Contents of the status register      
//
//*****************************************************************************
static inline uint32_t PMBus_getStatus(uint32_t base)
{
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    return(HWREG(base + PMBUS_O_PMBSTS));
}

//*****************************************************************************
//
//! Acknowledge the transaction by writing to the PMBACK register
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_ackTransaction(uint32_t base)
{
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    //acknowledge
    HWREG(base + PMBUS_O_PMBACK) |= PMBUS_PMBACK_ACK;
}

//*****************************************************************************
//
//! Nack the transaction by writing to the PMBACK register
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_nackTransaction(uint32_t base)
{
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    //NACK
    HWREG(base + PMBUS_O_PMBACK) &= ~PMBUS_PMBACK_ACK;
}

//*****************************************************************************
//
//! Alert the master by asserting the ALERT line
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! A slave PMBus can alert the master by pulling the alert line low. 
//! This triggers an Alert Response from the master, where the master issues
//! the \b Alert \b Response \b Address on the bus with a read bit and the 
//! alerting slave is required to reply with its address.
//!
//! \note The alerting device should be in slave mode
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_assertAlertLine(uint32_t base)
{
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    //Pull the alert line low
    HWREG(base + PMBUS_O_PMBCTRL) |= PMBUS_PMBCTRL_ALERT_EN;
    EDIS;
}

//*****************************************************************************
//
//! De-assert the alert line
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_deassertAlertLine(uint32_t base)
{
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    //Pull the alert line low
    HWREG(base + PMBUS_O_PMBCTRL) &= ~PMBUS_PMBCTRL_ALERT_EN;
    EDIS;
}

//*****************************************************************************
//
//! Configure the PMBUS operation in Master Mode.
//!
//! \param base is the base address of the PMBUS instance used.
//! \param slaveAddress address of the Slave device
//! \param byteCount number of bytes transmitted(or read) in the message 
//! (up to 255)
//! \param configWord can be a combination of the following
//! -# PMBUS_MASTER_ENABLE_PRC_CALL          
//! -# PMBUS_MASTER_ENABLE_GRP_CMD           
//! -# PMBUS_MASTER_ENABLE_PEC               
//! -# PMBUS_MASTER_ENABLE_EXT_CMD           
//! -# PMBUS_MASTER_ENABLE_CMD               
//! -# PMBUS_MASTER_ENABLE_READ              
//! Assuming the PMBUS module is set to Master mode, this function will 
//! configure the PMBMC register. It overwrites the contents of the PMBMC 
//! register. 
//! \note Writing to the PMBMC register initiates a message on the bus, once
//! the bus is free. In the event of a write, the TXBUF must be loaded prior
//! to configuration, or very quickly after configuration, before the module
//! starts the bus clock.
//! \note If the user does not specify an option, for example, 
//! PMBUS_MASTER_ENABLE_READ, the code will write a 0 (a write) in its 
//! bit field
//! \note setting byteCount to 0U (on a write) triggers a quick command; there
//! is no need to precede this command with the PMBus_putMasterData()
//! \note If transmitting with a non-zero byteCount, the user must precede this 
//! with the PMBus_putMasterData(), supplying it with the location of the data,
//! and the number of bytes (<= 4). For block transmissions, the user will have 
//! to call PMBus_putMasterData(), PMBus_configMaster(), and then continue 
//! calling PMBus_putMasterData() transmitting 4 (or less for the final 
//! transmit), till all the data bytes are transmitted.
//! \note If receiving, the user must follow up with the PMBus_getData(),
//!  supplying it with the location of an empty buffer, and the status byte
//! \note In cases where the master must transmit, for example, process call,
//! the user must call PMBus_putMasterData(), then configure the master to 
//! transmit the command and two bytes, then call PMBus_getData() to
//! read two bytes from the slave. The master module need not be reconfigured
//! between write and read whenever a repeated start is involved in the 
//! transaction
//! \return None.
//
//*****************************************************************************
static inline void PMBus_configMaster(uint32_t base, uint16_t slaveAddress, 
                               uint16_t byteCount, uint32_t configWord)
{
    // Locals
    // form a bit mask of the bit fields configWord changes
    const uint32_t bitmask = (PMBUS_PMBMC_RW | PMBUS_PMBMC_CMD_ENA | 
               PMBUS_PMBMC_EXT_CMD | PMBUS_PMBMC_PEC_ENA | 
               PMBUS_PMBMC_GRP_CMD | PMBUS_PMBMC_PRC_CALL);
  
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    ASSERT(slaveAddress <= 0x7FU);
    ASSERT(byteCount <= 0xFFU);

    
    EALLOW;
    // write the user configured bit fields (passed in configWord) as well 
    // as slave address and message byte counts. Writing to PMBMC triggers
    // activity on the bus, once the bus is free (PMBSTS.BUS_FREE = 1)
    HWREG(base + PMBUS_O_PMBMC) = ((configWord & bitmask) |
                              ((slaveAddress << PMBUS_PMBMC_SLAVE_ADDR_S) & 
                                                PMBUS_PMBMC_SLAVE_ADDR_M) |
                              ((byteCount    << PMBUS_PMBMC_BYTE_COUNT_S) & 
                                                PMBUS_PMBMC_BYTE_COUNT_M));
    EDIS;
}

//*****************************************************************************
//
//! Get the address that the PMBUS module will respond to (in slave mode)
//!
//! \param base is the base address of the PMBUS instance used.
//! \param ownAddress address that the module will respond to.
//! This function will query the PMBUS_O_PMBHSA register, this
//! will be the address of the module when used in Slave Mode. 
//! \return Address of the PMBus device (in slave mode).
//
//*****************************************************************************
static inline uint16_t PMBus_getOwnAddress(uint32_t base)
{
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    
    return((HWREG(base + PMBUS_O_PMBHSA) & 0xFEU) >> 1U);
}

//*****************************************************************************
//
//! Determine the current access (read/write) type 
//!
//! \param base is the base address of the PMBUS instance used.
//! This function will query the PMBUS_O_PMBHSA register, to determine if
//! the current access type was a read or write access. This bit is relevant
//! only when the PMBUS module is addressed as a slave. 
//! \return an enum of the type PMBus_accessType which specifies if the device,
//! in slave mode, was addressed for a read or write operation
//
//*****************************************************************************
static inline PMBus_accessType PMBus_getCurrentAccessType(uint32_t base)
{
        // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    
    return((PMBus_accessType)(HWREG(base + PMBUS_O_PMBHSA) & 0x01U));
}

//*****************************************************************************
//
//! Sets the triggering edge of the Control Interrupt
//!
//! \param base is the base address of the PMBUS instance used.
//! \param intEdge interrupt to trigger on rising or falling edge
//!
//! \return None
//
//*****************************************************************************
static inline void PMBus_setCtrlIntEdge(uint32_t base, PMBus_intEdge intEdge)
{
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    
    if(intEdge == PMBUS_INTEDGE_FALLING)
    {
        // Clear bit
        HWREG(base + PMBUS_O_PMBCTRL) &=  ~PMBUS_PMBCTRL_CNTL_INT_EDGE;
    }
    else // PMBUS_INTEDGE_RISING
    {
        // Set bit
        HWREG(base + PMBUS_O_PMBCTRL) |=  PMBUS_PMBCTRL_CNTL_INT_EDGE;
    }
}

//*****************************************************************************
//
//! Sets the triggering edge of the Clock Low Timeout Interrupt
//!
//! \param base is the base address of the PMBUS instance used.
//! \param intEdge interrupt to trigger on rising or falling edge
//!
//! \return None
//
//*****************************************************************************
static inline 
void PMBus_setClkLowTimeoutIntEdge(uint32_t base, PMBus_intEdge intEdge)
{
    // Check the arguments.
    ASSERT(PMBus_isBaseValid(base));
    
    if(intEdge == PMBUS_INTEDGE_FALLING)
    {
        // Clear bit
        HWREG(base + PMBUS_O_PMBCTRL) &=  ~PMBUS_PMBCTRL_BUS_LO_INT_EDGE;
    }
    else // PMBUS_INTEDGE_RISING
    {
        // Set bit
        HWREG(base + PMBUS_O_PMBCTRL) |=  PMBUS_PMBCTRL_BUS_LO_INT_EDGE;
    }
}

//*****************************************************************************
//
//! Initializes the PMBUS to Slave Mode.
//!
//! \param base is the base address of the PMBUS instance used.
//! \param address Slave address
//! \param mask Slave address mask - Used in address detection, the slave 
//!  mask enables acknowledgment of multiple device addresses by the slave. 
//!  Writing a ‘0’ to a bit within the slave mask enables the corresponding bit 
//!  in the slave address to be either ‘1’ or ‘0’ and still allow for a match. 
//!  Writing a ‘0’ to all bits in the mask enables the PMBus Interface to 
//!  acknowledge any device address. Upon power-up, the slave mask defaults to 
//!  7Fh, indicating the slave will only acknowledge the address programmed 
//!  into the Slave Address (Bits 6-0).
//!  Set to PMBUS_DISABLE_SLAVE_ADDRESS_MASK if you do not wish to have a mask
//! This function sets up the PMBUS in slave mode and also configures the slave
//! address for the PMBUS module
//!
//! \return None.
//
//*****************************************************************************
extern
void PMBus_initSlaveMode(uint32_t base, uint16_t address, uint16_t mask);

//*****************************************************************************
//
//! Configure the PMBUS operation in Slave Mode.
//!
//! \param base is the base address of the PMBUS instance used.
//! \param configWord can be a combination of the following
//! -# PMBUS_SLAVE_ENABLE_MANUAL_ACK      
//! -# PMBUS_SLAVE_ENABLE_PEC_PROCESSING
//! -# PMBUS_SLAVE_ENABLE_MANUAL_CMD_ACK  
//! -# PMBUS_SLAVE_DISABLE_ADDRESS_MASK   
//! -# PMBUS_SLAVE_AUTO_ACK_1_BYTES       
//! -# PMBUS_SLAVE_AUTO_ACK_2_BYTES       
//! -# PMBUS_SLAVE_AUTO_ACK_3_BYTES       
//! -# PMBUS_SLAVE_AUTO_ACK_4_BYTES            
//! Assuming the PMBUS module is set to slave mode, this function will 
//! configure the PMBSC register. It overwrites the contents of the PMBSC 
//! register, with the exception of the address, slave mask, TXPEC and byte
//! count bit fields 
//! \note If the user does not specify an option, for example, 
//! PMBUS_SLAVE_ENABLE_PEC_PROCESSING, the code will write a 0 (a write) in 
//! its  bit field
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_configSlave(uint32_t base, uint32_t configWord);

//*****************************************************************************
//
//! Registers a basic interrupt handler for the PMBUS module.
//!
//! \param base is the base address of the PMBUS instance used.
//! \param handler is a pointer to the function to be called when the PMBUS
//! interrupt occurs.
//!
//! This function sets the handler to be called when an PMBUS interrupt occurs.
//! This function enables the global interrupt in the interrupt controller;
//! specific PMBUS interrupts must be enabled via PMBus_enableInterrupt(). If
//! necessary, it is the interrupt handler's responsibility to clear the
//! interrupt source via PMBus_clearInterruptStatus().
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void 
PMBus_registerBasicInterrupt(uint32_t base, void (*handler)(void));

//*****************************************************************************
//
//! Unregisters a basic interrupt handler for the PMBUS module.
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! This function clears the handler to be called when an PMBUS interrupt 
//! occurs. This function also masks off the interrupt in the interrupt 
//! controller so that the interrupt handler no longer is called.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_unregisterBasicInterrupt(uint32_t base);

//*****************************************************************************
//
//! Gets the current PMBUS interrupt status.
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! This function returns the interrupt status for the I2C module.
//!
//! \return The current interrupt status, as a bit field of
//! - \b PMBUS_INTSRC_BUS_FREE          
//! - \b PMBUS_INTSRC_CLK_LOW_TIMEOUT   
//! - \b PMBUS_INTSRC_DATA_READY        
//! - \b PMBUS_INTSRC_DATA_REQUEST      
//! - \b PMBUS_INTSRC_SLAVE_ADDR_READY  
//! - \b PMBUS_INTSRC_EOM               
//! - \b PMBUS_INTSRC_ALERT             
//! - \b PMBUS_INTSRC_CONTROL           
//! - \b PMBUS_INTSRC_LOST_ARB          
//! - \b PMBUS_INTSRC_CLK_HIGH_DETECT   
//
//*****************************************************************************
extern uint32_t PMBus_getInterruptStatus(uint32_t base);

//*****************************************************************************
//
//! Read the receive buffer (Slave or Master mode)
//!
//! \param base is the base address of the I2C instance used.
//! \param buffer pointer to the message buffer where the received bytes
//!         will be written to
//! \param status  the value of the status register (PMBUS_O_PMBSTS)
//!
//! This function can read up to 4 bytes in the receive buffer.
//! \note The status register is cleared each time it is read, therefore, it 
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getStatus() and saved to a temporary variable for further 
//! processing
//! \note buffer should be at least 4 words long; anything smaller will lead
//! to the possibility of memory overrun when a transaction of 4 bytes happens
//!
//! \return Returns the number of byte(s) received by the PMBUS in the 
//! array pointed to by buffer
//
//*****************************************************************************
extern uint16_t 
PMBus_getData(uint32_t base, uint16_t *buffer, uint32_t status);

#define PMBus_getMasterData PMBus_getData
#define PMBus_getSlaveData  PMBus_getData
//*****************************************************************************
//
//! write to the transmit buffer (Slave mode)
//!
//! \param base is the base address of the I2C instance used.
//! \param buffer pointer to the message buffer where the transmit bytes
//!   are stored
//! \param nBytes number of transmit bytes, up to 4
//! \param txPEC 1 transmit PEC at end of message, 0 no PEC
//! This function can write up to 4 bytes in the transmit buffer. 
//! \note the user must check the UNIT_BUSY bit before attempting a
//!       transmission
//! \note buffer should be at least 4 words long; anything smaller will lead
//! to the possibility of memory overrun when a transaction of 4 bytes happens
//! \return None
//
//*****************************************************************************
extern void 
PMBus_putSlaveData(uint32_t base, uint16_t *buffer, uint16_t nBytes, 
                   bool txPEC);

//*****************************************************************************
//
//! Manual acknowledgment of the slave address
//!
//! \param base is the base address of the I2C instance used.
//! \param address address of the slave 
//! \param status  the value of the status register (PMBUS_O_PMBSTS)
//! \param buffer pointer to a buffer to store the received data
//!
//! This function will read the address that was put on the bus, compare it 
//! with address passed to this function and then acknowledge on a match (or 
//! nack on mismatch). For this function to work, SLAVE_ADDR_READY bit in 
//! PBINTM must be enabled. This function checks the SLAVE_ADDR_READY bit in 
//! the status register before acknowledging so it would be preferable to use 
//! this function in an interrupt handler that responds to the SLAVE_ADDR_READY 
//! interrupt.
//!
//! \note The status register is cleared each time it is read, therefore, it 
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getStatus() and saved to a temporary variable for further 
//! processing
//! \note buffer should be at least 4 words long; anything smaller will lead
//! to the possibility of memory overrun when a transaction of 4 bytes happens
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_ackAddress(uint32_t base, uint32_t address, uint32_t status,
                             uint16_t *buffer);

//*****************************************************************************
//
//! Manual acknowledgment of a command
//!
//! \param base is the base address of the I2C instance used.
//! \param command command to manually acknowledge - it can be any of the 
//!  commands listed in this header file. All commands have the common
//!  prefix \b PMBUS_CMD.
//! \param status contents of the status register PMBUS_O_PMBSTS
//! \param buffer pointer to a buffer to store the received data
//!
//! This function will read the command that was put on the bus, compare it 
//! with command passed to this function and then acknowledge on a match (or 
//! nack on mismatch). For this function to work, DATA_READY bit in PBINTM 
//! must be enabled. This function checks the DATA_READY bit in the status 
//! register before acknowledging so it would be preferable to use this 
//! function in an interrupt handler that responds to the DATA_READY interrupt.
//!
//! \note The status register is cleared each time it is read, therefore, it 
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getStatus() and saved to a temporary variable for further 
//! processing
//! \note buffer should be at least 4 words long; anything smaller will lead
//! to the possibility of memory overrun when a transaction of 4 bytes happens
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_ackCommand(uint32_t base, uint32_t command, uint32_t status,
                             uint16_t *buffer);

//*****************************************************************************
//
//! Generate a CRC table at run time
//!
//! \param base is the base address of the PMBUS instance used.
//! \param crcTable points to the CRC8 Table (must be size 256)
//!
//! This function generates a CRC lookup table to run a CRC on the
//! received data. The table is generated from the polynomial
//! x^8 + x^2 + x^1 + 1 (0x7 - leading 1 is implicit)
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_generateCRCTable(uint32_t base, uint16_t *crcTable);

//*****************************************************************************
//
//! Run a CRC on the received data and check against the 
//! received PEC to validate the integrity of the data 
//!
//! \param base is the base address of the PMBUS instance used.
//! \param buffer points to the recevied message
//! \buffer crcTable points to the CRC8 Table
//! \param byteCount size of the message, does not include the PEC byte
//! \param PEC is the received PEC to check against
//!
//! This function uses a CRC lookup table to run a CRC on the
//! received data. The table was generated from the polynomial
//! x^8 + x^2 + x^1 + 1 (0x7 - leading 1 is implicit)
//!
//! \note buffer should be at least 4 words long; anything smaller will lead
//! to the possibility of memory overrun when a transaction of 4 bytes happens
//!
//! \return \b true if the calculated CRC is equal to the PEC, \b false 
//! otherwise.
//
//*****************************************************************************
extern bool PMBus_verifyPEC(uint32_t base, uint16_t *buffer, 
                  uint16_t *crcTable, uint16_t byteCount, uint16_t PEC);

//*****************************************************************************
//
//! Initializes the PMBUS to Master Mode.
//!
//! \param base is the base address of the PMBUS instance used.
//!
//! This function sets up the PMBUS in master mode.
//!
//! \return None.
//
//*****************************************************************************
extern void PMBus_initMasterMode(uint32_t base);

//*****************************************************************************
//
//! write to the transmit buffer (Master mode)
//!
//! \param base is the base address of the I2C instance used.
//! \param buffer pointer to the message buffer where the transmit bytes
//!   are stored
//! \param nBytes number of transmit bytes, up to 255
//! This function can write up to 255 bytes in the transmit buffer. 
//! 
//! \note the user must check the UNIT_BUSY bit before attempting the 
//!   first transmission
//! \note buffer should be at least 4 words long; anything smaller will lead
//! to the possibility of memory overrun when a transaction of 4 bytes happens
//!
//! \return None
//
//*****************************************************************************
extern void 
PMBus_putMasterData(uint32_t base, uint16_t *buffer, uint16_t nBytes);

//*****************************************************************************
//
//! Configure the PMBUS module clock
//!
//! \param base is the base address of the PMBUS instance used.
//! \param moduleFrequency desired module frequency; can range from 
//! PMBUS_MODULE_FREQ_MIN Hz to PMBUS_MODULE_FREQ_MAX Hz. Please input the 
//! frequency in Hz, e.g. 312500 for 312.4 KHz etc.
//! \param sysFrequency Frequency of the system clock (input to PMBUS). The 
//! values may range anywhere from PMBUS_SYS_FREQ_MIN Hz to PMBUS_SYS_FREQ_MAX 
//! Hz. Please input the frequency in Hz, e.g. 100000000 for 100 MHz etc.
//!        
//! The frequency to the PMBUS module may not exceed PMBUS_MODULE_FREQ_MAX Hz,
//! the appropriate clock divider is chosen to bring the module clock to the
//! desired frequency - this value is then returned by the function.
//! In the event that the desired bus frequency is unattainable, the clock
//! divider is set to the max possible value 
//!
//! \return module frequency calculated from the system frequency and clock 
//! divider
//
//*****************************************************************************
extern uint32_t 
PMBus_configModuleClock(uint32_t base, uint32_t moduleFrequency, 
                        uint32_t sysFrequency);

//*****************************************************************************
//
//! Configure the bus clock by overriding the default settings
//!
//! \param base is the base address of the PMBUS instance used.
//! \param mode is the operating mode for the PMBUS, can be 
//!  - Standard Mode
//!  - Fast Mode
//!  - Fast Mode Plus
//! \param moduleFrequency desired module frequency; can range from 
//! PMBUS_MODULE_FREQ_MIN Hz to PMBUS_MODULE_FREQ_MAX Hz. Please input the 
//! frequency in Hz, e.g. 312500 for 312.4 KHz etc.  
//! 
//! The frequency to the PMBUS module may not exceed PMBUS_MODULE_FREQ_MAX Hz.
//!
//! \note The module comes out of reset with preprogrammed values that allow
//! it to work in standard mode with a module clock of 10MHz. The module clock
//! is set to 10MHz at power cycle, therefore, the user does not have to call
//! this function unless they wish to change the operating frequency of the
//! module clock from the default 10MHz
//! 
//! \return \b true for successful override, \b false on failure
//
//*****************************************************************************
extern bool 
PMBus_configBusClock(uint32_t base, PMBus_ClockMode mode, 
                     uint32_t moduleFrequency);

//*****************************************************************************
// Close the Doxygen group.
//! @}
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __PMBUS_H__
