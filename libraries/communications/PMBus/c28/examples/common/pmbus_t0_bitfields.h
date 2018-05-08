//###########################################################################
//
// FILE:   pmbus_t0.h
//
// TITLE:  Device PMBUS Register Definitions.
//
// BUILD:  CUSTOMER RELEASE
//
//###########################################################################
// $TI Release: C28x PMBus Communications Stack Library v1.00.00.00 $
// $Release Date: May 22, 2017 $
//###########################################################################

#ifndef _PMBUS_R0_H_
#define _PMBUS_R0_H_
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// PMBUS Individual Register Bit Definitions:
    
struct PMBMC_BITS               {            // bits   description
    uint16_t RW:1;                           // 0      RnW bit of the Message
    uint16_t SLAVE_ADDR:7;                   // 7..1   Slave Address
    uint16_t BYTE_COUNT:8;                   // 15..8  Number of Bytes Transmitted
    uint16_t CMD_ENA:1;                      // 16     Master Command Code Enable
    uint16_t EXT_CMD:1;                      // 17     Master Extended Command Code Enable
    uint16_t PEC_ENA:1;                      // 18     Master PEC Processing Enable
    uint16_t GRP_CMD:1;                      // 19     Master Group Command Message Enable
    uint16_t PRC_CALL:1;                     // 20     Master Process Call Message Enable
    uint16_t rsvd1:11;                       // 31..21 Reserved
}; 

union PMBMC_REG {
    uint32_t  all;
    struct  PMBMC_BITS  bit;
}; 

struct PMBACK_BITS              {            // bits   description
    uint16_t ACK:1;                          // 0      Allows firmware to ack/nack received data
    uint32_t rsvd1:31;                       // 31..1  Reserved
}; 

union PMBACK_REG {
    uint32_t  all;
    struct  PMBACK_BITS  bit;
}; 

struct PMBSTS_BITS              {            // bits   description
    uint16_t RD_BYTE_COUNT:3;                // 2..0   Number of Data Bytes available in Receive Data Register
    uint16_t DATA_READY:1;                   // 3      Data Ready Flag
    uint16_t DATA_REQUEST:1;                 // 4      Data Request Flag
    uint16_t EOM:1;                          // 5      End of Message Indicator
    uint16_t NACK:1;                         // 6      Not Acknowledge Flag Status
    uint16_t PEC_VALID:1;                    // 7      PEC Valid Indicator
    uint16_t CLK_LOW_TIMEOUT:1;              // 8      Clock Low Timeout Status
    uint16_t CLK_HIGH_DETECTED:1;            // 9      Clock High Detection Status
    uint16_t SLAVE_ADDR_READY:1;             // 10     Slave Address Ready
    uint16_t RPT_START:1;                    // 11     Repeated Start Flag
    uint16_t UNIT_BUSY:1;                    // 12     PMBus Busy Indicator
    uint16_t BUS_FREE:1;                     // 13     PMBus Free Indicator
    uint16_t LOST_ARB:1;                     // 14     Lost Arbitration Flag
    uint16_t MASTER:1;                       // 15     Master Indicator
    uint16_t ALERT_EDGE:1;                   // 16     Alert Edge Detection Status
    uint16_t CONTROL_EDGE:1;                 // 17     Control Edge Detection Status
    uint16_t ALERT_RAW:1;                    // 18     Alert Pin Real Time Status
    uint16_t CONTROL_RAW:1;                  // 19     Control Pin Real Time Status
    uint16_t SDA_RAW:1;                      // 20     PMBus Data Pin Real Time Status
    uint16_t SCL_RAW:1;                      // 21     PMBus Clock Pin Real Time Status
    uint16_t rsvd1:10;                       // 31..22 
}; 

union PMBSTS_REG {
    uint32_t  all;
    struct  PMBSTS_BITS  bit;
}; 

struct PMBINTM_BITS             {            // bits   description
    uint16_t BUS_FREE:1;                     // 0      Bus Free Interrupt Mask
    uint16_t BUS_LOW_TIMEOUT:1;              // 1      Clock Low Timeout Interrupt Mask
    uint16_t DATA_READY:1;                   // 2      Data Ready Interrupt Mask
    uint16_t DATA_REQUEST:1;                 // 3      Data Request Interrupt Mask
    uint16_t SLAVE_ADDR_READY:1;             // 4      Slave Address Ready Interrupt Mask
    uint16_t EOM:1;                          // 5      End of Message Interrupt Mask
    uint16_t ALERT:1;                        // 6      Alert Detection Interrupt Mask
    uint16_t CONTROL:1;                      // 7      Control Detection Interrupt Mask
    uint16_t LOST_ARB:1;                     // 8      Lost Arbitration Interrupt Mask
    uint16_t CLK_HIGH_DETECT:1;              // 9      Clock High Detection Interrupt Mask
    uint32_t rsvd1:22;                       // 31..10 
}; 

union PMBINTM_REG {
    uint32_t  all;
    struct  PMBINTM_BITS  bit;
}; 

struct PMBSC_BITS               {            // bits   description
    uint16_t SLAVE_ADDR:7;                   // 6..0   Configures the current device address of the slave.
    uint16_t MAN_SLAVE_ACK:1;                // 7      Manual Slave Address Acknowledgement Mode
    uint16_t SLAVE_MASK:7;                   // 14..8  Slave address mask
    uint16_t PEC_ENA:1;                      // 15     PEC Processing Enable
    uint16_t TX_COUNT:3;                     // 18..16 Number of valid bytes in Transmit Data Register
    uint16_t TX_PEC:1;                       // 19     send a PEC byte at end of message
    uint16_t MAN_CMD:1;                      // 20     Manual Command Acknowledgement Mode
    uint16_t RX_BYTE_ACK_CNT:2;              // 22..21 Number of data bytes to automatically acknowledge
    uint16_t rsvd1:9;                        // 31..23 Reserved
}; 

union PMBSC_REG {
    uint32_t  all;
    struct  PMBSC_BITS  bit;
}; 

struct PMBHSA_BITS              {            // bits   description
    uint16_t SLAVE_RW:1;                     // 0      Stored R/W bit
    uint16_t SLAVE_ADDR:7;                   // 7..1   Stored device address
    uint32_t rsvd1:24;                       // 31..8  
}; 

union PMBHSA_REG {
    uint32_t  all;
    struct  PMBHSA_BITS  bit;
}; 

struct PMBCTRL_BITS             {            // bits   description
    uint16_t RESET:1;                        // 0      PMBus Interface Synchronous Reset
    uint16_t ALERT_EN:1;                     // 1      Slave Alert Enable
    uint16_t BUS_LO_INT_EDGE:1;              // 2      Clock Low Timeout Interrupt Edge Select
    uint16_t FAST_MODE:1;                    // 3      Fast Mode Enable
    uint16_t FAST_MODE_PLUS:1;               // 4      Fast Mode Plus Enable
    uint16_t CNTL_INT_EDGE:1;                // 5      Control Interrupt Edge Select
    uint16_t ALERT_MODE:1;                   // 6      Configures mode of Alert pin
    uint16_t ALERT_VALUE:1;                  // 7      Configures output value of Alert pin in GPIO Mode
    uint16_t ALERT_DIR:1;                    // 8      Configures direction of Alert pin in GPIO mode
    uint16_t CNTL_MODE:1;                    // 9      Configures mode of Control pin
    uint16_t CNTL_VALUE:1;                   // 10     Configures output value of Control pin in GPIO Mode
    uint16_t CNTL_DIR:1;                     // 11     Configures direction of Control pin in GPIO mode
    uint16_t SDA_MODE:1;                     // 12     Configures mode of PMBus Data pin
    uint16_t SDA_VALUE:1;                    // 13     Configures output value of PMBus data pin in GPIO Mode
    uint16_t SDA_DIR:1;                      // 14     Configures direction of PMBus data pin in GPIO mode
    uint16_t SCL_MODE:1;                     // 15     Configures mode of PMBus Clock pin
    uint16_t SCL_VALUE:1;                    // 16     Configures output value of PMBus clock pin in GPIO Mode
    uint16_t SCL_DIR:1;                      // 17     Configures direction of PMBus clock pin in GPIO mode
    uint16_t IBIAS_A_EN:1;                   // 18     PMBus Current Source A Control
    uint16_t IBIAS_B_EN:1;                   // 19     PMBus Current Source B Control
    uint16_t CLK_LO_DIS:1;                   // 20     Clock Low Timeout Disable
    uint16_t SLAVE_EN:1;                     // 21     PMBus Slave Enable
    uint16_t MASTER_EN:1;                    // 22     PMBus Master Enable
    uint16_t CLKDIV:5;                       // 27..23 PMBUS IP Clock Divide Value
    uint16_t rsvd1:3;                        // 30..28 Reserved
    uint16_t I2CMODE:1;                      // 31     Bit to enable I2C mode
}; 

union PMBCTRL_REG {
    uint32_t  all;
    struct  PMBCTRL_BITS  bit;
}; 

struct PMBTIMCTL_BITS           {            // bits   description
    uint16_t TIM_OVERRIDE:1;                 // 0      Overide the default settings of the timing parameters.
    uint32_t rsvd1:31;                       // 31..1  
}; 

union PMBTIMCTL_REG {
    uint32_t  all;
    struct  PMBTIMCTL_BITS  bit;
}; 

struct PMBTIMCLK_BITS           {            // bits   description
    uint16_t CLK_HIGH_LIMIT:8;               // 7..0   Determines the PMBUS master clock high pulse width.
    uint16_t rsvd1:8;                        // 15..8  
    uint16_t CLK_FREQ:8;                     // 23..16 Determines the PMBUS master clock frequency.
    uint16_t rsvd2:8;                        // 31..24 
}; 

union PMBTIMCLK_REG {
    uint32_t  all;
    struct  PMBTIMCLK_BITS  bit;
}; 

struct PMBTIMSTSETUP_BITS       {            // bits   description
    uint16_t TSU_STA:8;                      // 7..0   Setup time, rise edge of PMBUS master clock to start edge.
    uint32_t rsvd1:24;                       // 31..8  
}; 

union PMBTIMSTSETUP_REG {
    uint32_t  all;
    struct  PMBTIMSTSETUP_BITS  bit;
}; 

struct PMBTIMBIDLE_BITS         {            // bits   description
    uint16_t BUSIDLE:10;                     // 9..0   Determines the Bus Idle Limit
    uint32_t rsvd1:22;                       // 31..10 
}; 

union PMBTIMBIDLE_REG {
    uint32_t  all;
    struct  PMBTIMBIDLE_BITS  bit;
}; 

struct PMBTIMLOWTIMOUT_BITS     {            // bits   description
    uint32_t CLKLOWTIMOUT:20;                // 19..0  Determines the clock low timeout value
    uint16_t rsvd1:12;                       // 31..20 
}; 

union PMBTIMLOWTIMOUT_REG {
    uint32_t  all;
    struct  PMBTIMLOWTIMOUT_BITS  bit;
}; 

struct PMBTIMHIGHTIMOUT_BITS    {            // bits   description
    uint16_t CLKHIGHTIMOUT:10;               // 9..0   Determines the clock high timeout value
    uint32_t rsvd1:22;                       // 31..10 
}; 

union PMBTIMHIGHTIMOUT_REG {
    uint32_t  all;
    struct  PMBTIMHIGHTIMOUT_BITS  bit;
}; 

struct PMBUS_REGS {
    union     PMBMC_REG                PMBMC;                   // PMBUS Master Mode Control Register
    uint32_t                           PMBTXBUF;                // PMBUS Transmit Buffer
    uint32_t                           PMBRXBUF;                // PMBUS Receive buffer
    union     PMBACK_REG               PMBACK;                  // PMBUS Acknowledge Register
    union     PMBSTS_REG               PMBSTS;                  // PMBUS Status Register
    union     PMBINTM_REG              PMBINTM;                 // PMBUS Interrupt Mask Register
    union     PMBSC_REG                PMBSC;                   // PMBUS Slave Mode Configuration Register
    union     PMBHSA_REG               PMBHSA;                  // PMBUS Hold Slave Address Register
    union     PMBCTRL_REG              PMBCTRL;                 // PMBUS Control Register
    union     PMBTIMCTL_REG            PMBTIMCTL;               // PMBUS Timing Control Register
    union     PMBTIMCLK_REG            PMBTIMCLK;               // PMBUS Clock Timing Register
    union     PMBTIMSTSETUP_REG        PMBTIMSTSETUP;           // PMBUS Start Setup Time Register
    union     PMBTIMBIDLE_REG          PMBTIMBIDLE;             // PMBUS Bus Idle Time Register
    union     PMBTIMLOWTIMOUT_REG      PMBTIMLOWTIMOUT;         // PMBUS Clock Low Timeout Value Register
    union     PMBTIMHIGHTIMOUT_REG     PMBTIMHIGHTIMOUT;        // PMBUS Clock High Timeout Value Register
    uint16_t                           rsvd1[2];                // Reserved
};
//---------------------------------------------------------------------------
// PMBUS External References & Function Declarations:
//
extern volatile struct PMBUS_REGS PMBUSRegs;

#ifdef __cplusplus
}
#endif                                   /* extern "C" */


#endif                                   // end of _PMBUS_R0_H_ definition
//===========================================================================
// End of file.
//===========================================================================
    
