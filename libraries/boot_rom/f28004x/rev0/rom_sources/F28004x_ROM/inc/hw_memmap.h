//###########################################################################
//
// FILE:    hw_memmap.h
//
// TITLE:   Macros defining the memory map of the C28x.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __HW_MEMMAP_H__
#define __HW_MEMMAP_H__

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals.
//
//*****************************************************************************
#define ADCARESULT_BASE             0x00000B00U // ADC1 Result Registers
#define ADCBRESULT_BASE             0x00000B20U // ADC2 Result Registers
#define ADCCRESULT_BASE             0x00000B40U // ADC3 Result Registers
#define ADCDRESULT_BASE             0x00000B60U // ADC4 Result Registers
#define CPUTIMER0_BASE              0x00000C00U // CPU Timer 0 Registers
#define CPUTIMER1_BASE              0x00000C08U // CPU Timer 1 Registers
#define CPUTIMER2_BASE              0x00000C10U // CPU Timer 2 Registers
#define PIECTRL_BASE                0x00000CE0U // PIE Registers
#define PIEVECTTABLE_BASE           0x00000D00U // PIE Vector Table
#define DMA_BASE                    0x00001000U // DMA Control Registers
#define DMA_CH1_BASE                0x00001020U // DMA Channel Registers
#define DMA_CH2_BASE                0x00001040U // DMA Channel Registers
#define DMA_CH3_BASE                0x00001060U // DMA Channel Registers
#define DMA_CH4_BASE                0x00001080U // DMA Channel Registers
#define DMA_CH5_BASE                0x000010A0U // DMA Channel Registers
#define DMA_CH6_BASE                0x000010C0U // DMA Channel Registers
#define CLA1DEBUG_BASE              0x00001380U // CPU1.CLA1 Debug Registers
#define CLA1_BASE                   0x00001400U // CPU1.CLA1 Registers
#define EPWM1_BASE                  0x00004000U // EPWM1
#define EPWM2_BASE                  0x00004100U // EPWM2
#define EPWM3_BASE                  0x00004200U // EPWM3
#define EPWM4_BASE                  0x00004300U // EPWM4
#define EPWM5_BASE                  0x00004400U // EPWM5
#define EPWM6_BASE                  0x00004500U // EPWM6
#define EPWM7_BASE                  0x00004600U // EPWM7
#define EPWM8_BASE                  0x00004700U // EPWM8
#define EQEP1_BASE                  0x00005100U // EQEP1
#define EQEP2_BASE                  0x00005140U // EQEP2
#define ECAP1_BASE                  0x00005200U // ECAP1
#define ECAP2_BASE                  0x00005240U // ECAP2
#define ECAP3_BASE                  0x00005280U // ECAP3
#define ECAP4_BASE                  0x000052C0U // ECAP4
#define ECAP5_BASE                  0x00005300U // ECAP5
#define ECAP6_BASE                  0x00005340U // ECAP6
#define ECAP7_BASE                  0x00005380U // ECAP7
#define PGAA_BASE                   0x00005B00U // PGAA
#define PGAB_BASE                   0x00005B10U // PGAB
#define PGAC_BASE                   0x00005B20U // PGAC
#define PGAD_BASE                   0x00005B30U // PGAD
#define PGAE_BASE                   0x00005B40U // PGAE
#define PGAF_BASE                   0x00005B50U // PGAF
#define PGAG_BASE                   0x00005B60U // PGAG
#define DACA_BASE                   0x00005C00U // BUFDACA
#define DACB_BASE                   0x00005C10U // BUFDACB
#define CMPSS1_BASE                 0x00005C80U // CMPSS1
#define CMPSS2_BASE                 0x00005CA0U // CMPSS2
#define CMPSS3_BASE                 0x00005CC0U // CMPSS3
#define CMPSS4_BASE                 0x00005CE0U // CMPSS4
#define CMPSS5_BASE                 0x00005D00U // CMPSS5
#define CMPSS6_BASE                 0x00005D20U // CMPSS6
#define CMPSS7_BASE                 0x00005D40U // CMPSS7
#define SDFM1_BASE                  0x00005E00U // SDFM Configuration Registers
#define SPIA_BASE                   0x00006100U // SPI A Registers
#define SPIB_BASE                   0x00006110U // SPI B Registers
#define CLA1PROMCRC_BASE            0x000061C0U // CLA1PROMCRC Registers
#define PMBUSA_BASE                 0x00006400U // PMBUS A Registers
#define FSITXA_BASE                 0x00006600U // FSITX Configuration Registers
#define FSIRXA_BASE                 0x00006680U // FSIRX Configuration Registers
#define FSITXB_BASE                 0x00006700U // FSITX Configuration Registers
#define FSIRXB_BASE                 0x00006780U // FSIRX Configuration Registers
#define LINA_BASE                   0x00006A00U // LIN A Registers
#define LINB_BASE                   0x00006B00U // LIN B Registers
#define WD_BASE                     0x00007000U // Watchdog Registers
#define NMI_BASE                    0x00007060U // NMI Registers
#define XINT_BASE                   0x00007070U // Interrupt Control Counter Registers
#define SCIA_BASE                   0x00007200U // SCI A Registers
#define SCIB_BASE                   0x00007210U // SCI B Registers
#define I2CA_BASE                   0x00007300U // I2C A Registers
#define ADCA_BASE                   0x00007400U // ADC1 Configuration Registers
#define ADCB_BASE                   0x00007480U // ADC2 Configuration Registers
#define ADCC_BASE                   0x00007500U // ADC3 Configuration Registers
#define INPUTXBAR_BASE              0x00007900U // GPIO Mux GPTRIP Input Select Registers
#define XBAR_BASE                   0x00007920U // X-Bar Registers
#define TRIGXBAR_BASE               0x00007940U // Trig X-Bar Registers
#define DMACLASRCSEL_BASE           0x00007980U // DMA CLA Triggers Source Select Registers
#define EPWMXBAR_BASE               0x00007A00U // EPWM XBAR Configuration Registers
#define CLBXBAR_BASE                0x00007A40U // CLB XBAR Configuration Registers
#define OUTPUTXBAR_BASE             0x00007A80U // Output X-BAR Configuration Registers
#define GPIOCTRL_BASE               0x00007C00U // GPIO 0 to 31 Mux A Configuration Registers
#define GPIODATA_BASE               0x00007F00U // GPIO 0 to 31 Mux A Data Registers
#define CPU2_TO_CPU1_MSG_RAM_BASE   0x0003F800U // CPU2 to CPU1 Message RAM
#define CPU1_TO_CPU2_MSG_RAM_BASE   0x0003FC00U // CPU1 to CPU2 Message RAM
#define CANA_BASE                   0x00048000U // CAN-A Registers
#define CANA_MSG_RAM_BASE           0x00048800U // CAN-A Message RAM
#define CANA_SEDEC_BASE             0x00049800U // CAN-A SEDEC
#define CANB_BASE                   0x0004A000U // CAN-B Registers
#define CANB_MSG_RAM_BASE           0x0004A800U // CAN-B Message RAM
#define CANB_SEDEC_BASE             0x0004B800U // CAN-B SEDEC
#define DEVCFG_BASE                 0x0005D000U // Device Configuration Registers
#define CLKCFG_BASE                 0x0005D200U // Clock Configuration Registers
#define CPUSYS_BASE                 0x0005D300U // CPU System Configuration Registers
#define PERIPHAC_BASE               0x0005D500U // Peripheral Master Access Registers
#define ANALOGSUBSYS_BASE           0x0005D700U // Analog System Control Registers
#define DCC0_BASE                   0x0005E700U // Enhanced Debug Registers
#define ENHANCED_DEBUG_BASE         0x0005E800U // Enhanced Debug Registers
#define DCSMBANK0_Z1_BASE            0x0005F000U // Zone 1 DCSM Registers
#define DCSMBANK0_Z2_BASE            0x0005F040U // Zone 2 DCSM Registers
#define DCSMCOMMON_BASE             0x0005F070U // Security Registers
#define DCSMCOMMON2_BASE            0x0005F080U // Security Registers
#define DCSMBANK1_Z1_BASE            0x0005F100U // Zone 1 DCSM Registers
#define DCSMBANK1_Z2_BASE            0x0005F140U // Zone 2 DCSM Registers
#define MEMCFG_BASE                 0x0005F400U // Memory config registers
#define ACCESSPROTECTION_BASE       0x0005F4C0U // Access protection registers
#define MEMORYERROR_BASE            0x0005F500U // Memory error registers
#define FLASH0CTRL_BASE             0x0005F800U // Flash control registers
#define FLASH0ECC_BASE              0x0005FB00U // Flash ECC error log registers
#define DCSMBANK0_Z1OTP_BASE        0x00078000U // Zone 1 DCSM OTP
#define DCSMBANK0_Z2OTP_BASE        0x00078200U // Zone 2 DCSM OTP
#define DCSMBANK1_Z1OTP_BASE        0x00078400U // Zone 1 DCSM OTP
#define DCSMBANK1_Z2OTP_BASE        0x00078600U // Zone 2 DCSM OTP

#endif // __HW_MEMMAP_H__

