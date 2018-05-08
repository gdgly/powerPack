//###########################################################################
//
// FILE:    hw_sysctl.h
//
// TITLE:   Definitions for the SYSCTL registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __HW_SYSCTL_H__
#define __HW_SYSCTL_H__

//*****************************************************************************
//
// The following are defines for the SYSCTL register offsets
//
//*****************************************************************************
#define SYSCTL_O_PARTIDL          0x8U         // Lower 32-bit of Device PART
                                               // Identification Number
#define SYSCTL_O_PARTIDH          0xAU         // Upper 32-bit of Device PART
                                               // Identification Number
#define SYSCTL_O_REVID            0xCU         // Device Revision Number
#define SYSCTL_O_DC1              0x12U        // Device Capability: Processing
                                               // Block Customization
#define SYSCTL_O_DC3              0x16U        // Device Capability: Peripheral
                                               // Customization
#define SYSCTL_O_DC4              0x18U        // Device Capability: Peripheral
                                               // Customization
#define SYSCTL_O_DC5              0x1AU        // Device Capability: Peripheral
                                               // Customization
#define SYSCTL_O_DC7              0x1EU        // Device Capability: Peripheral
                                               // Customization
#define SYSCTL_O_DC8              0x20U        // Device Capability: Peripheral
                                               // Customization
#define SYSCTL_O_DC9              0x22U        // Device Capability: Peripheral
                                               // Customization
#define SYSCTL_O_DC10             0x24U        // Device Capability: Peripheral
                                               // Customization
#define SYSCTL_O_DC11             0x26U        // Device Capability: Peripheral
                                               // Customization
#define SYSCTL_O_DC14             0x2CU        // Device Capability: Analog
                                               // Modules Customization
#define SYSCTL_O_DC15             0x2EU        // Device Capability: Analog
                                               // Modules Customization
#define SYSCTL_O_DC16             0x30U        // Device Capability: Analog
                                               // Modules Customization
#define SYSCTL_O_DC17             0x32U        // Device Capability: Analog
                                               // Modules Customization
#define SYSCTL_O_DC18             0x34U        // Device Capability: Lx.1 SRAM
                                               // Customization
#define SYSCTL_O_DC20             0x38U        // Device Capability: GSx SRAM
                                               // Customization
#define SYSCTL_O_DC21             0x3AU        // Device Capability: CLB
#define SYSCTL_O_DC22             0x3CU        // Device Capability: FSI
#define SYSCTL_O_DC23             0x3EU        // Device Capability: LIN
#define SYSCTL_O_DC24             0x40U        // Device Capability: PMBUS
#define SYSCTL_O_DC25             0x42U        // Device Capability: DCC
#define SYSCTL_O_FUSEERR          0x74U        // e-Fuse error Status register
#define SYSCTL_O_CJTAGNODEID      0x7EU        // cJTAG Node ID Register
#define SYSCTL_O_SOFTPRES0        0x82U        // Processing Block Software
                                               // Reset register
#define SYSCTL_O_SOFTPRES2        0x86U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES3        0x88U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES4        0x8AU        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES6        0x8EU        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES7        0x90U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES8        0x92U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES9        0x94U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES10       0x96U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES13       0x9CU        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES14       0x9EU        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES15       0xA0U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES16       0xA2U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES17       0xA4U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES18       0xA6U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES19       0xA8U        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES20       0xAAU        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_SOFTPRES21       0xACU        // Peripheral Software Reset
                                               // register
#define SYSCTL_O_TAP_STATUS       0x130U       // Status of JTAG State machine
                                               // & Debugger Connect
#define SYSCTL_O_CLKCFGLOCK1      0x2U         // Lock bit for CLKCFG registers
#define SYSCTL_O_CLKSRCCTL1       0x8U         // Clock Source Control
                                               // register-1
#define SYSCTL_O_CLKSRCCTL2       0xAU         // Clock Source Control
                                               // register-2
#define SYSCTL_O_CLKSRCCTL3       0xCU         // Clock Source Control
                                               // register-3
#define SYSCTL_O_SYSPLLCTL1       0xEU         // SYSPLL Control register-1
#define SYSCTL_O_SYSPLLMULT       0x14U        // SYSPLL Multiplier register
#define SYSCTL_O_SYSPLLSTS        0x16U        // SYSPLL Status register
#define SYSCTL_O_SYSCLKDIVSEL     0x22U        // System Clock Divider Select
                                               // register
#define SYSCTL_O_PERCLKDIVSEL     0x26U        // Peripheral Clock Divider
                                               // Selet register
#define SYSCTL_O_XCLKOUTDIVSEL    0x28U        // XCLKOUT Divider Select
                                               // register
#define SYSCTL_O_LOSPCP           0x2CU        // Low Speed Clock Source
                                               // Prescalar
#define SYSCTL_O_MCDCR            0x2EU        // Missing Clock Detect Control
                                               // Register
#define SYSCTL_O_X1CNT            0x30U        // 10-bit Counter on X1 Clock
#define SYSCTL_O_XTALCR           0x32U        // XTAL Control Register
#define SYSCTL_O_CPUSYSLOCK1      0x0U         // Lock bit for CPUSYS registers
#define SYSCTL_O_PIEVERRADDR      0xAU         // PIE Vector Fetch Error
                                               // Address register
#define SYSCTL_O_PCLKCR0          0x22U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR2          0x26U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR3          0x28U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR4          0x2AU        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR6          0x2EU        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR7          0x30U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR8          0x32U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR9          0x34U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR10         0x36U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR13         0x3CU        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR14         0x3EU        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR15         0x40U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR16         0x42U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR17         0x44U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR18         0x46U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR19         0x48U        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR20         0x4AU        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR21         0x4CU        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_PCLKCR22         0x4EU        // Peripheral Clock Gating
                                               // Registers
#define SYSCTL_O_LPMCR            0x76U        // LPM Control Register
#define SYSCTL_O_GPIOLPMSEL0      0x78U        // GPIO LPM Wakeup select
                                               // registers
#define SYSCTL_O_GPIOLPMSEL1      0x7AU        // GPIO LPM Wakeup select
                                               // registers
#define SYSCTL_O_TMR2CLKCTL       0x7CU        // Timer2 Clock Measurement
                                               // functionality control register
#define SYSCTL_O_RESCCLR          0x7EU        // Reset Cause Clear Register
#define SYSCTL_O_RESC             0x80U        // Reset Cause register
#define SYSCTL_O_SCSR             0x22U        // System Control & Status
                                               // Register
#define SYSCTL_O_WDCNTR           0x23U        // Watchdog Counter Register
#define SYSCTL_O_WDKEY            0x25U        // Watchdog Reset Key Register
#define SYSCTL_O_WDCR             0x29U        // Watchdog Control Register
#define SYSCTL_O_WDWCR            0x2AU        // Watchdog Windowed Control
                                               // Register
#define SYSCTL_O_CLA1TASKSRCSELLOCK  0x0U         // CLA1 Task Trigger Source
                                               // Select Lock Register
#define SYSCTL_O_DMACHSRCSELLOCK  0x4U         // DMA Channel Triger Source
                                               // Select Lock Register
#define SYSCTL_O_CLA1TASKSRCSEL1  0x6U         // CLA1 Task Trigger Source
                                               // Select Register-1
#define SYSCTL_O_CLA1TASKSRCSEL2  0x8U         // CLA1 Task Trigger Source
                                               // Select Register-2
#define SYSCTL_O_DMACHSRCSEL1     0x16U        // DMA Channel Trigger Source
                                               // Select Register-1
#define SYSCTL_O_DMACHSRCSEL2     0x18U        // DMA Channel Trigger Source
                                               // Select Register-2
#define SYSCTL_O_ADCA_AC          0x0U         // ADCA Master Access Control
                                               // Register
#define SYSCTL_O_ADCB_AC          0x2U         // ADCB Master Access Control
                                               // Register
#define SYSCTL_O_ADCC_AC          0x4U         // ADCC Master Access Control
                                               // Register
#define SYSCTL_O_CMPSS1_AC        0x10U        // CMPSS1 Master Access Control
                                               // Register
#define SYSCTL_O_CMPSS2_AC        0x12U        // CMPSS2 Master Access Control
                                               // Register
#define SYSCTL_O_CMPSS3_AC        0x14U        // CMPSS3 Master Access Control
                                               // Register
#define SYSCTL_O_CMPSS4_AC        0x16U        // CMPSS4 Master Access Control
                                               // Register
#define SYSCTL_O_CMPSS5_AC        0x18U        // CMPSS5 Master Access Control
                                               // Register
#define SYSCTL_O_CMPSS6_AC        0x1AU        // CMPSS6 Master Access Control
                                               // Register
#define SYSCTL_O_CMPSS7_AC        0x1CU        // CMPSS7 Master Access Control
                                               // Register
#define SYSCTL_O_DACA_AC          0x28U        // DACA Master Access Control
                                               // Register
#define SYSCTL_O_DACB_AC          0x2AU        // DACB Master Access Control
                                               // Register
#define SYSCTL_O_PGAA_AC          0x38U        // PGAA Master Access Control
                                               // Register
#define SYSCTL_O_PGAB_AC          0x3AU        // PGAB Master Access Control
                                               // Register
#define SYSCTL_O_PGAC_AC          0x3CU        // PGAC Master Access Control
                                               // Register
#define SYSCTL_O_PGAD_AC          0x3EU        // PGAD Master Access Control
                                               // Register
#define SYSCTL_O_PGAE_AC          0x40U        // PGAE Master Access Control
                                               // Register
#define SYSCTL_O_PGAF_AC          0x42U        // PGAF Master Access Control
                                               // Register
#define SYSCTL_O_PGAG_AC          0x44U        // PGAG Master Access Control
                                               // Register
#define SYSCTL_O_EPWM1_AC         0x48U        // EPWM1 Master Access Control
                                               // Register
#define SYSCTL_O_EPWM2_AC         0x4AU        // EPWM2 Master Access Control
                                               // Register
#define SYSCTL_O_EPWM3_AC         0x4CU        // EPWM3 Master Access Control
                                               // Register
#define SYSCTL_O_EPWM4_AC         0x4EU        // EPWM4 Master Access Control
                                               // Register
#define SYSCTL_O_EPWM5_AC         0x50U        // EPWM5 Master Access Control
                                               // Register
#define SYSCTL_O_EPWM6_AC         0x52U        // EPWM6 Master Access Control
                                               // Register
#define SYSCTL_O_EPWM7_AC         0x54U        // EPWM7 Master Access Control
                                               // Register
#define SYSCTL_O_EPWM8_AC         0x56U        // EPWM8 Master Access Control
                                               // Register
#define SYSCTL_O_EQEP1_AC         0x70U        // EQEP1 Master Access Control
                                               // Register
#define SYSCTL_O_EQEP2_AC         0x72U        // EQEP2 Master Access Control
                                               // Register
#define SYSCTL_O_ECAP1_AC         0x80U        // ECAP1 Master Access Control
                                               // Register
#define SYSCTL_O_ECAP2_AC         0x82U        // ECAP2 Master Access Control
                                               // Register
#define SYSCTL_O_ECAP3_AC         0x84U        // ECAP3 Master Access Control
                                               // Register
#define SYSCTL_O_ECAP4_AC         0x86U        // ECAP4 Master Access Control
                                               // Register
#define SYSCTL_O_ECAP5_AC         0x88U        // ECAP5 Master Access Control
                                               // Register
#define SYSCTL_O_ECAP6_AC         0x8AU        // ECAP6 Master Access Control
                                               // Register
#define SYSCTL_O_ECAP7_AC         0x8CU        // ECAP7 Master Access Control
                                               // Register
#define SYSCTL_O_SDFM1_AC         0xA8U        // SDFM1 Master Access Control
                                               // Register
#define SYSCTL_O_CLB1_AC          0xB0U        // CLB1 Master Access Control
                                               // Register
#define SYSCTL_O_CLB2_AC          0xB2U        // CLB2 Master Access Control
                                               // Register
#define SYSCTL_O_CLB3_AC          0xB4U        // CLB3 Master Access Control
                                               // Register
#define SYSCTL_O_CLB4_AC          0xB6U        // CLB4 Master Access Control
                                               // Register
#define SYSCTL_O_CLA1PROMCRC_AC   0xC0U        // CLA1PROMCRC Master Access
                                               // Control Register
#define SYSCTL_O_SPIA_AC          0x110U       // SPIA Master Access Control
                                               // Register
#define SYSCTL_O_SPIB_AC          0x112U       // SPIB Master Access Control
                                               // Register
#define SYSCTL_O_PMBUS_A_AC       0x130U       // PMBUSA Master Access Control
                                               // Register
#define SYSCTL_O_LIN_A_AC         0x138U       // LINA Master Access Control
                                               // Register
#define SYSCTL_O_DCANA_AC         0x140U       // DCANA Master Access Control
                                               // Register
#define SYSCTL_O_DCANB_AC         0x142U       // DCANB Master Access Control
                                               // Register
#define SYSCTL_O_FSIATX_AC        0x158U       // FSIA Master Access Control
                                               // Register
#define SYSCTL_O_FSIARX_AC        0x15AU       // FSIB Master Access Control
                                               // Register
#define SYSCTL_O_HRPWM_A_AC       0x1AAU       // HRPWM Master Access Control
                                               // Register
#define SYSCTL_O_PERIPH_AC_LOCK   0x1FEU       // Lock Register to stop Write
                                               // access to peripheral Access
                                               // register.

//*****************************************************************************
//
// The following are defines for the bit fields in the PARTIDL register
//
//*****************************************************************************
#define SYSCTL_PARTIDL_TEMPERATURE_S  0U
#define SYSCTL_PARTIDL_TEMPERATURE_M  0x7U         // Temperature Rating
#define SYSCTL_PARTIDL_PACKAGE_S  3U
#define SYSCTL_PARTIDL_PACKAGE_M  0x18U        // Device Package
#define SYSCTL_PARTIDL_QUAL_S     6U
#define SYSCTL_PARTIDL_QUAL_M     0xC0U        // Qualification Status
#define SYSCTL_PARTIDL_PIN_COUNT_S  8U
#define SYSCTL_PARTIDL_PIN_COUNT_M  0x700U       // Device Pin Count
#define SYSCTL_PARTIDL_INSTASPIN_S  13U
#define SYSCTL_PARTIDL_INSTASPIN_M  0x6000U      // Motorware feature set
#define SYSCTL_PARTIDL_FLASH_SIZE_S  16U
#define SYSCTL_PARTIDL_FLASH_SIZE_M  0xFF0000U    // Flash size in KB

//*****************************************************************************
//
// The following are defines for the bit fields in the PARTIDH register
//
//*****************************************************************************
#define SYSCTL_PARTIDH_PARTID_FORMAT_REVISION_S  0U
#define SYSCTL_PARTIDH_PARTID_FORMAT_REVISION_M  0xFU         // Revision of the PARTID format
#define SYSCTL_PARTIDH_FAMILY_S   8U
#define SYSCTL_PARTIDH_FAMILY_M   0xFF00U      // Device family
#define SYSCTL_PARTIDH_PARTNO_S   16U
#define SYSCTL_PARTIDH_PARTNO_M   0xFF0000U    // Device part number
#define SYSCTL_PARTIDH_DEVICE_CLASS_ID_S  24U
#define SYSCTL_PARTIDH_DEVICE_CLASS_ID_M  0xFF000000U  // Device class ID

//*****************************************************************************
//
// The following are defines for the bit fields in the REVID register
//
//*****************************************************************************
#define SYSCTL_REVID_REVID_S      0U
#define SYSCTL_REVID_REVID_M      0xFFFFU      // Device Revision ID. This is
                                               // specific to the Device

//*****************************************************************************
//
// The following are defines for the bit fields in the DC1 register
//
//*****************************************************************************
#define SYSCTL_DC1_CPU1_FPU_TMU   0x1U         // CPU1's FPU1+TMU1
#define SYSCTL_DC1_CPU1_VCU       0x4U         // CPU1's VCU
#define SYSCTL_DC1_CPU1_CLA1      0x40U        // CPU1.CLA1

//*****************************************************************************
//
// The following are defines for the bit fields in the DC3 register
//
//*****************************************************************************
#define SYSCTL_DC3_EPWM1          0x1U         // EPWM1 Present
#define SYSCTL_DC3_EPWM2          0x2U         // EPWM2 Present
#define SYSCTL_DC3_EPWM3          0x4U         // EPWM3 Present
#define SYSCTL_DC3_EPWM4          0x8U         // EPWM4 Present
#define SYSCTL_DC3_EPWM5          0x10U        // EPWM5 Present
#define SYSCTL_DC3_EPWM6          0x20U        // EPWM6 Present
#define SYSCTL_DC3_EPWM7          0x40U        // EPWM7 Present
#define SYSCTL_DC3_EPWM8          0x80U        // EPWM8 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the DC4 register
//
//*****************************************************************************
#define SYSCTL_DC4_ECAP1          0x1U         // ECAP1
#define SYSCTL_DC4_ECAP2          0x2U         // ECAP2
#define SYSCTL_DC4_ECAP3          0x4U         // ECAP3
#define SYSCTL_DC4_ECAP4          0x8U         // ECAP4
#define SYSCTL_DC4_ECAP5          0x10U        // ECAP5
#define SYSCTL_DC4_ECAP6          0x20U        // ECAP6
#define SYSCTL_DC4_ECAP7          0x40U        // ECAP7

//*****************************************************************************
//
// The following are defines for the bit fields in the DC5 register
//
//*****************************************************************************
#define SYSCTL_DC5_EQEP1          0x1U         // EQEP1
#define SYSCTL_DC5_EQEP2          0x2U         // EQEP2

//*****************************************************************************
//
// The following are defines for the bit fields in the DC7 register
//
//*****************************************************************************
#define SYSCTL_DC7_SD1            0x1U         // SD1

//*****************************************************************************
//
// The following are defines for the bit fields in the DC8 register
//
//*****************************************************************************
#define SYSCTL_DC8_SCI_A          0x1U         // SCI_A
#define SYSCTL_DC8_SCI_B          0x2U         // SCI_B

//*****************************************************************************
//
// The following are defines for the bit fields in the DC9 register
//
//*****************************************************************************
#define SYSCTL_DC9_SPI_A          0x1U         // SPI_A
#define SYSCTL_DC9_SPI_B          0x2U         // SPI_B

//*****************************************************************************
//
// The following are defines for the bit fields in the DC10 register
//
//*****************************************************************************
#define SYSCTL_DC10_I2C_A         0x1U         // I2C_A

//*****************************************************************************
//
// The following are defines for the bit fields in the DC11 register
//
//*****************************************************************************
#define SYSCTL_DC11_CAN_A         0x1U         // CAN_A
#define SYSCTL_DC11_CAN_B         0x2U         // CAN_B

//*****************************************************************************
//
// The following are defines for the bit fields in the DC14 register
//
//*****************************************************************************
#define SYSCTL_DC14_ADC_A         0x1U         // ADC_A
#define SYSCTL_DC14_ADC_B         0x2U         // ADC_B
#define SYSCTL_DC14_ADC_C         0x4U         // ADC_C

//*****************************************************************************
//
// The following are defines for the bit fields in the DC15 register
//
//*****************************************************************************
#define SYSCTL_DC15_CMPSS1        0x1U         // CMPSS1
#define SYSCTL_DC15_CMPSS2        0x2U         // CMPSS2
#define SYSCTL_DC15_CMPSS3        0x4U         // CMPSS3
#define SYSCTL_DC15_CMPSS4        0x8U         // CMPSS4
#define SYSCTL_DC15_CMPSS5        0x10U        // CMPSS5
#define SYSCTL_DC15_CMPSS6        0x20U        // CMPSS6
#define SYSCTL_DC15_CMPSS7        0x40U        // CMPSS7

//*****************************************************************************
//
// The following are defines for the bit fields in the DC16 register
//
//*****************************************************************************
#define SYSCTL_DC16_PGA1          0x1U         // PGA1
#define SYSCTL_DC16_PGA2          0x2U         // PGA2
#define SYSCTL_DC16_PGA3          0x4U         // PGA3
#define SYSCTL_DC16_PGA4          0x8U         // PGA4
#define SYSCTL_DC16_PGA5          0x10U        // PGA5
#define SYSCTL_DC16_PGA6          0x20U        // PGA6
#define SYSCTL_DC16_PGA7          0x40U        // PGA7

//*****************************************************************************
//
// The following are defines for the bit fields in the DC17 register
//
//*****************************************************************************
#define SYSCTL_DC17_DAC_A         0x10000U     // Buffered-DAC_A
#define SYSCTL_DC17_DAC_B         0x20000U     // Buffered-DAC_B

//*****************************************************************************
//
// The following are defines for the bit fields in the DC18 register
//
//*****************************************************************************
#define SYSCTL_DC18_LS0_1         0x1U         // LS0_1
#define SYSCTL_DC18_LS1_1         0x2U         // LS1_1
#define SYSCTL_DC18_LS2_1         0x4U         // LS2_1
#define SYSCTL_DC18_LS3_1         0x8U         // LS3_1
#define SYSCTL_DC18_LS4_1         0x10U        // LS4_1
#define SYSCTL_DC18_LS5_1         0x20U        // LS5_1
#define SYSCTL_DC18_LS6_1         0x40U        // LS6_1
#define SYSCTL_DC18_LS7_1         0x80U        // LS7_1

//*****************************************************************************
//
// The following are defines for the bit fields in the DC20 register
//
//*****************************************************************************
#define SYSCTL_DC20_GS0           0x1U         // GS0
#define SYSCTL_DC20_GS1           0x2U         // GS1
#define SYSCTL_DC20_GS2           0x4U         // GS2
#define SYSCTL_DC20_GS3           0x8U         // GS3

//*****************************************************************************
//
// The following are defines for the bit fields in the DC21 register
//
//*****************************************************************************
#define SYSCTL_DC21_CLB1          0x1U         // CLB1
#define SYSCTL_DC21_CLB2          0x2U         // CLB2
#define SYSCTL_DC21_CLB3          0x4U         // CLB3
#define SYSCTL_DC21_CLB4          0x8U         // CLB4

//*****************************************************************************
//
// The following are defines for the bit fields in the DC22 register
//
//*****************************************************************************
#define SYSCTL_DC22_FSITX_A       0x1U         // FSITX_A
#define SYSCTL_DC22_FSIRX_A       0x2U         // FSIRX_A

//*****************************************************************************
//
// The following are defines for the bit fields in the DC23 register
//
//*****************************************************************************
#define SYSCTL_DC23_LIN_A         0x1U         // LIN_A

//*****************************************************************************
//
// The following are defines for the bit fields in the DC24 register
//
//*****************************************************************************
#define SYSCTL_DC24_PMBUS_A       0x1U         // PMBUS_A

//*****************************************************************************
//
// The following are defines for the bit fields in the DC25 register
//
//*****************************************************************************
#define SYSCTL_DC25_DCC_A         0x1U         // DCC_A

//*****************************************************************************
//
// The following are defines for the bit fields in the FUSEERR register
//
//*****************************************************************************
#define SYSCTL_FUSEERR_ALERR_S    0U
#define SYSCTL_FUSEERR_ALERR_M    0x1FU        // Efuse Autoload Error Status
#define SYSCTL_FUSEERR_ERR        0x20U        // Efuse Self Test Error Status

//*****************************************************************************
//
// The following are defines for the bit fields in the CJTAGNODEID register
//
//*****************************************************************************
#define SYSCTL_CJTAGNODEID_ID_S   0U
#define SYSCTL_CJTAGNODEID_ID_M   0xFFU        // cJTAG Node ID

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES0 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES0_CPU1_CLA1  0x1U         // CPU1_CLA1 software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES2 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES2_EPWM1    0x1U         // EPWM1 software reset bit
#define SYSCTL_SOFTPRES2_EPWM2    0x2U         // EPWM2 software reset bit
#define SYSCTL_SOFTPRES2_EPWM3    0x4U         // EPWM3 software reset bit
#define SYSCTL_SOFTPRES2_EPWM4    0x8U         // EPWM4 software reset bit
#define SYSCTL_SOFTPRES2_EPWM5    0x10U        // EPWM5 software reset bit
#define SYSCTL_SOFTPRES2_EPWM6    0x20U        // EPWM6 software reset bit
#define SYSCTL_SOFTPRES2_EPWM7    0x40U        // EPWM7 software reset bit
#define SYSCTL_SOFTPRES2_EPWM8    0x80U        // EPWM8 software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES3 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES3_ECAP1    0x1U         // ECAP1 software reset bit
#define SYSCTL_SOFTPRES3_ECAP2    0x2U         // ECAP2 software reset bit
#define SYSCTL_SOFTPRES3_ECAP3    0x4U         // ECAP3 software reset bit
#define SYSCTL_SOFTPRES3_ECAP4    0x8U         // ECAP4 software reset bit
#define SYSCTL_SOFTPRES3_ECAP5    0x10U        // ECAP5 software reset bit
#define SYSCTL_SOFTPRES3_ECAP6    0x20U        // ECAP6 software reset bit
#define SYSCTL_SOFTPRES3_ECAP7    0x40U        // ECAP7 software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES4 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES4_EQEP1    0x1U         // EQEP1 software reset bit
#define SYSCTL_SOFTPRES4_EQEP2    0x2U         // EQEP2 software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES6 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES6_SD1      0x1U         // SD1 software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES7 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES7_SCI_A    0x1U         // SCI_A software reset bit
#define SYSCTL_SOFTPRES7_SCI_B    0x2U         // SCI_B software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES8 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES8_SPI_A    0x1U         // SPI_A software reset bit
#define SYSCTL_SOFTPRES8_SPI_B    0x2U         // SPI_B software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES9 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES9_I2C_A    0x1U         // I2C_A software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES10 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES10_CAN_A   0x1U         // CAN_A software reset bit
#define SYSCTL_SOFTPRES10_CAN_B   0x2U         // CAN_B software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES13 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES13_ADC_A   0x1U         // ADC_A software reset bit
#define SYSCTL_SOFTPRES13_ADC_B   0x2U         // ADC_B software reset bit
#define SYSCTL_SOFTPRES13_ADC_C   0x4U         // ADC_C software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES14 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES14_CMPSS1  0x1U         // CMPSS1 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS2  0x2U         // CMPSS2 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS3  0x4U         // CMPSS3 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS4  0x8U         // CMPSS4 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS5  0x10U        // CMPSS5 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS6  0x20U        // CMPSS6 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS7  0x40U        // CMPSS7 software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES15 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES15_PGA1    0x1U         // PGA1 software reset bit
#define SYSCTL_SOFTPRES15_PGA2    0x2U         // PGA2 software reset bit
#define SYSCTL_SOFTPRES15_PGA3    0x4U         // PGA3 software reset bit
#define SYSCTL_SOFTPRES15_PGA4    0x8U         // PGA4 software reset bit
#define SYSCTL_SOFTPRES15_PGA5    0x10U        // PGA5 software reset bit
#define SYSCTL_SOFTPRES15_PGA6    0x20U        // PGA6 software reset bit
#define SYSCTL_SOFTPRES15_PGA7    0x40U        // PGA7 software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES16 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES16_DAC_A   0x10000U     // Buffered_DAC_A software reset
                                               // bit
#define SYSCTL_SOFTPRES16_DAC_B   0x20000U     // Buffered_DAC_B software reset
                                               // bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES17 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES17_CLB1    0x1U         // CLB1 software reset bit
#define SYSCTL_SOFTPRES17_CLB2    0x2U         // CLB2 software reset bit
#define SYSCTL_SOFTPRES17_CLB3    0x4U         // CLB3 software reset bit
#define SYSCTL_SOFTPRES17_CLB4    0x8U         // CLB4 software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES18 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES18_FSITX_A  0x1U         // FSITX_A software reset bit
#define SYSCTL_SOFTPRES18_FSIRX_A  0x2U         // FSIRX_A software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES19 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES19_LIN_A   0x1U         // LIN_A software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES20 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES20_PMBUS_A  0x1U         // PMBUS_A software reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES21 register
//
//*****************************************************************************
#define SYSCTL_SOFTPRES21_DCC_0   0x1U         // DCC Module reset bit

//*****************************************************************************
//
// The following are defines for the bit fields in the TAP_STATUS register
//
//*****************************************************************************
#define SYSCTL_TAP_STATUS_TAP_STATE_S  0U
#define SYSCTL_TAP_STATUS_TAP_STATE_M  0xFFFFU      // Present TAP State
#define SYSCTL_TAP_STATUS_DCON    0x80000000U  // Debugger Connect Indication

//*****************************************************************************
//
// The following are defines for the bit fields in the CLKCFGLOCK1 register
//
//*****************************************************************************
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL1  0x1U         // Lock bit for CLKSRCCTL1
                                               // register
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL2  0x2U         // Lock bit for CLKSRCCTL2
                                               // register
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL3  0x4U         // Lock bit for CLKSRCCTL3
                                               // register
#define SYSCTL_CLKCFGLOCK1_SYSPLLCTL1  0x8U         // Lock bit for SYSPLLCTL1
                                               // register
#define SYSCTL_CLKCFGLOCK1_SYSPLLMULT  0x40U        // Lock bit for SYSPLLMULT
                                               // register
#define SYSCTL_CLKCFGLOCK1_SYSCLKDIVSEL  0x800U       // Lock bit for SYSCLKDIVSEL
                                               // register
#define SYSCTL_CLKCFGLOCK1_PERCLKDIVSEL  0x2000U      // Lock bit for PERCLKDIVSEL
                                               // register
#define SYSCTL_CLKCFGLOCK1_LOSPCP  0x8000U      // Lock bit for LOSPCP register
#define SYSCTL_CLKCFGLOCK1_XTALCR  0x10000U     // Lock bit for XTALCR register

//*****************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL1 register
//
//*****************************************************************************
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_S  0U
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M  0x3U         // OSCCLK Source Select Bit
#define SYSCTL_CLKSRCCTL1_INTOSC2OFF  0x8U         // Internal Oscillator 2 Off Bit
#define SYSCTL_CLKSRCCTL1_WDHALTI  0x20U        // Watchdog HALT Mode Ignore Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL2 register
//
//*****************************************************************************
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_S  2U
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_M  0xCU         // CANA Bit Clock Source Select
                                               // Bit
#define SYSCTL_CLKSRCCTL2_CANBBCLKSEL_S  4U
#define SYSCTL_CLKSRCCTL2_CANBBCLKSEL_M  0x30U        // CANB Bit Clock Source Select
                                               // Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL3 register
//
//*****************************************************************************
#define SYSCTL_CLKSRCCTL3_XCLKOUTSEL_S  0U
#define SYSCTL_CLKSRCCTL3_XCLKOUTSEL_M  0x7U         // XCLKOUT Source Select Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSPLLCTL1 register
//
//*****************************************************************************
#define SYSCTL_SYSPLLCTL1_PLLEN   0x1U         // SYSPLL enable/disable bit
#define SYSCTL_SYSPLLCTL1_PLLCLKEN  0x2U         // SYSPLL bypassed or included
                                               // in the PLLSYSCLK path

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSPLLMULT register
//
//*****************************************************************************
#define SYSCTL_SYSPLLMULT_IMULT_S  0U
#define SYSCTL_SYSPLLMULT_IMULT_M  0x7FU        // SYSPLL Integer Multiplier
#define SYSCTL_SYSPLLMULT_FMULT_S  8U
#define SYSCTL_SYSPLLMULT_FMULT_M  0x300U       // SYSPLL Fractional Multiplier
#define SYSCTL_SYSPLLMULT_ODIV_S  16U
#define SYSCTL_SYSPLLMULT_ODIV_M  0x70000U     // Output Clock Divider

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSPLLSTS register
//
//*****************************************************************************
#define SYSCTL_SYSPLLSTS_LOCKS    0x1U         // SYSPLL Lock Status Bit
#define SYSCTL_SYSPLLSTS_SLIPS    0x2U         // SYSPLL Slip Status Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCLKDIVSEL register
//
//*****************************************************************************
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_S  0U
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M  0x3FU        // PLLSYSCLK Divide Select

//*****************************************************************************
//
// The following are defines for the bit fields in the PERCLKDIVSEL register
//
//*****************************************************************************
#define SYSCTL_PERCLKDIVSEL_EPWMCLKDIV_S  0U
#define SYSCTL_PERCLKDIVSEL_EPWMCLKDIV_M  0x3U         // EPWM Clock Divide Select

//*****************************************************************************
//
// The following are defines for the bit fields in the XCLKOUTDIVSEL register
//
//*****************************************************************************
#define SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_S  0U
#define SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_M  0x3U         // XCLKOUT Divide Select

//*****************************************************************************
//
// The following are defines for the bit fields in the LOSPCP register
//
//*****************************************************************************
#define SYSCTL_LOSPCP_LSPCLKDIV_S  0U
#define SYSCTL_LOSPCP_LSPCLKDIV_M  0x7U         // LSPCLK Divide Select

//*****************************************************************************
//
// The following are defines for the bit fields in the MCDCR register
//
//*****************************************************************************
#define SYSCTL_MCDCR_MCLKSTS      0x1U         // Missing Clock Status Bit
#define SYSCTL_MCDCR_MCLKCLR      0x2U         // Missing Clock Clear Bit
#define SYSCTL_MCDCR_MCLKOFF      0x4U         // Missing Clock Detect Off Bit
#define SYSCTL_MCDCR_OSCOFF       0x8U         // Oscillator Clock Off Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the X1CNT register
//
//*****************************************************************************
#define SYSCTL_X1CNT_X1CNT_S      0U
#define SYSCTL_X1CNT_X1CNT_M      0x3FFU       // X1 Counter
#define SYSCTL_X1CNT_CLR          0x10000U     // X1 Counter Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the XTALCR register
//
//*****************************************************************************
#define SYSCTL_XTALCR_OSCOFF      0x1U         // XTAL Oscillator powered-down
#define SYSCTL_XTALCR_SE          0x2U         // XTAL Oscilator in
                                               // Single-Ended mode
#define SYSCTL_XTALCR_SWH         0x4U         // XTAL Oscilator Operation
                                               // range

//*****************************************************************************
//
// The following are defines for the bit fields in the CPUSYSLOCK1 register
//
//*****************************************************************************
#define SYSCTL_CPUSYSLOCK1_PIEVERRADDR  0x4U         // Lock bit for PIEVERRADDR
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR0  0x8U         // Lock bit for PCLKCR0 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR2  0x20U        // Lock bit for PCLKCR2 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR3  0x40U        // Lock bit for PCLKCR3 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR4  0x80U        // Lock bit for PCLKCR4 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR6  0x200U       // Lock bit for PCLKCR6 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR7  0x400U       // Lock bit for PCLKCR7 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR8  0x800U       // Lock bit for PCLKCR8 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR9  0x1000U      // Lock bit for PCLKCR9 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR10  0x2000U      // Lock bit for PCLKCR10
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR13  0x10000U     // Lock bit for PCLKCR13
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR14  0x20000U     // Lock bit for PCLKCR14
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR15  0x40000U     // Lock bit for PCLKCR15
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR16  0x80000U     // Lock bit for PCLKCR16
                                               // Register
#define SYSCTL_CPUSYSLOCK1_LPMCR  0x200000U    // Lock bit for LPMCR Register
#define SYSCTL_CPUSYSLOCK1_GPIOLPMSEL0  0x400000U    // Lock bit for GPIOLPMSEL0
                                               // Register
#define SYSCTL_CPUSYSLOCK1_GPIOLPMSEL1  0x800000U    // Lock bit for GPIOLPMSEL1
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR17  0x1000000U   // Lock bit for PCLKCR17
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR18  0x2000000U   // Lock bit for PCLKCR18
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR19  0x4000000U   // Lock bit for PCLKCR19
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR20  0x8000000U   // Lock bit for PCLKCR20
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR21  0x10000000U  // Lock bit for PCLKCR21
                                               // Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR22  0x20000000U  // Lock bit for PCLKCR22
                                               // Register

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEVERRADDR register
//
//*****************************************************************************
#define SYSCTL_PIEVERRADDR_ADDR_S  0U
#define SYSCTL_PIEVERRADDR_ADDR_M  0x3FFFFFU    // PIE Vector Fetch Error
                                               // Handler Routine Address

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR0 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR0_CLA1       0x1U         // CLA1 Clock Enable Bit
#define SYSCTL_PCLKCR0_DMA        0x4U         // DMA Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER0  0x8U         // CPUTIMER0 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER1  0x10U        // CPUTIMER1 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER2  0x20U        // CPUTIMER2 Clock Enable bit
#define SYSCTL_PCLKCR0_HRPWM      0x10000U     // HRPWM Clock Enable Bit
#define SYSCTL_PCLKCR0_TBCLKSYNC  0x40000U     // EPWM Time Base Clock sync

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR2 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR2_EPWM1      0x1U         // EPWM1 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM2      0x2U         // EPWM2 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM3      0x4U         // EPWM3 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM4      0x8U         // EPWM4 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM5      0x10U        // EPWM5 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM6      0x20U        // EPWM6 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM7      0x40U        // EPWM7 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM8      0x80U        // EPWM8 Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR3 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR3_ECAP1      0x1U         // ECAP1 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP2      0x2U         // ECAP2 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP3      0x4U         // ECAP3 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP4      0x8U         // ECAP4 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP5      0x10U        // ECAP5 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP6      0x20U        // ECAP6 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP7      0x40U        // ECAP7 Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR4 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR4_EQEP1      0x1U         // EQEP1 Clock Enable bit
#define SYSCTL_PCLKCR4_EQEP2      0x2U         // EQEP2 Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR6 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR6_SD1        0x1U         // SD1 Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR7 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR7_SCI_A      0x1U         // SCI_A Clock Enable bit
#define SYSCTL_PCLKCR7_SCI_B      0x2U         // SCI_B Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR8 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR8_SPI_A      0x1U         // SPI_A Clock Enable bit
#define SYSCTL_PCLKCR8_SPI_B      0x2U         // SPI_B Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR9 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR9_I2C_A      0x1U         // I2C_A Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR10 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR10_CAN_A     0x1U         // CAN_A Clock Enable bit
#define SYSCTL_PCLKCR10_CAN_B     0x2U         // CAN_B Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR13 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR13_ADC_A     0x1U         // ADC_A Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_B     0x2U         // ADC_B Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_C     0x4U         // ADC_C Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR14 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR14_CMPSS1    0x1U         // CMPSS1 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS2    0x2U         // CMPSS2 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS3    0x4U         // CMPSS3 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS4    0x8U         // CMPSS4 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS5    0x10U        // CMPSS5 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS6    0x20U        // CMPSS6 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS7    0x40U        // CMPSS7 Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR15 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR15_PGA1      0x1U         // PGA1 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA2      0x2U         // PGA2 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA3      0x4U         // PGA3 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA4      0x8U         // PGA4 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA5      0x10U        // PGA5 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA6      0x20U        // PGA6 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA7      0x40U        // PGA7 Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR16 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR16_DAC_A     0x10000U     // Buffered_DAC_A Clock Enable
                                               // Bit
#define SYSCTL_PCLKCR16_DAC_B     0x20000U     // Buffered_DAC_B Clock Enable
                                               // Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR17 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR17_CLB1      0x1U         // CLB1 Clock Enable bit
#define SYSCTL_PCLKCR17_CLB2      0x2U         // CLB2 Clock Enable bit
#define SYSCTL_PCLKCR17_CLB3      0x4U         // CLB3 Clock Enable bit
#define SYSCTL_PCLKCR17_CLB4      0x8U         // CLB4 Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR18 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR18_FSITX_A   0x1U         // FSITX_A Clock Enable bit
#define SYSCTL_PCLKCR18_FSIRX_A   0x2U         // FSIRX_A Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR19 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR19_LIN_A     0x1U         // LIN_A Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR20 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR20_PMBUS_A   0x1U         // PMBUS_A Clock Enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR21 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR21_DCC_0     0x1U         // DCC_0 Clock Enable Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the PCLKCR22 register
//
//*****************************************************************************
#define SYSCTL_PCLKCR22_PBISTCLK_0  0x1U         // PBISTCLK_0 Clock Enable Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the LPMCR register
//
//*****************************************************************************
#define SYSCTL_LPMCR_LPM_S        0U
#define SYSCTL_LPMCR_LPM_M        0x3U         // Low Power Mode setting
#define SYSCTL_LPMCR_QUALSTDBY_S  2U
#define SYSCTL_LPMCR_QUALSTDBY_M  0xFCU        // STANDBY Wakeup Pin
                                               // Qualification Setting
#define SYSCTL_LPMCR_WDINTE       0x8000U      // Enable for WDINT wakeup from
                                               // STANDBY

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIOLPMSEL0 register
//
//*****************************************************************************
#define SYSCTL_GPIOLPMSEL0_GPIO0  0x1U         // GPIO0 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO1  0x2U         // GPIO1 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO2  0x4U         // GPIO2 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO3  0x8U         // GPIO3 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO4  0x10U        // GPIO4 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO5  0x20U        // GPIO5 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO6  0x40U        // GPIO6 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO7  0x80U        // GPIO7 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO8  0x100U       // GPIO8 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO9  0x200U       // GPIO9 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO10  0x400U       // GPIO10 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO11  0x800U       // GPIO11 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO12  0x1000U      // GPIO12 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO13  0x2000U      // GPIO13 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO14  0x4000U      // GPIO14 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO15  0x8000U      // GPIO15 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO16  0x10000U     // GPIO16 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO17  0x20000U     // GPIO17 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO18  0x40000U     // GPIO18 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO19  0x80000U     // GPIO19 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO20  0x100000U    // GPIO20 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO21  0x200000U    // GPIO21 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO22  0x400000U    // GPIO22 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO23  0x800000U    // GPIO23 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO24  0x1000000U   // GPIO24 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO25  0x2000000U   // GPIO25 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO26  0x4000000U   // GPIO26 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO27  0x8000000U   // GPIO27 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO28  0x10000000U  // GPIO28 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO29  0x20000000U  // GPIO29 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO30  0x40000000U  // GPIO30 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO31  0x80000000U  // GPIO31 Enable for LPM Wakeup

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIOLPMSEL1 register
//
//*****************************************************************************
#define SYSCTL_GPIOLPMSEL1_GPIO32  0x1U         // GPIO32 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO33  0x2U         // GPIO33 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO34  0x4U         // GPIO34 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO35  0x8U         // GPIO35 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO36  0x10U        // GPIO36 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO37  0x20U        // GPIO37 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO38  0x40U        // GPIO38 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO39  0x80U        // GPIO39 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO40  0x100U       // GPIO40 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO41  0x200U       // GPIO41 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO42  0x400U       // GPIO42 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO43  0x800U       // GPIO43 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO44  0x1000U      // GPIO44 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO45  0x2000U      // GPIO45 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO46  0x4000U      // GPIO46 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO47  0x8000U      // GPIO47 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO48  0x10000U     // GPIO48 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO49  0x20000U     // GPIO49 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO50  0x40000U     // GPIO50 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO51  0x80000U     // GPIO51 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO52  0x100000U    // GPIO52 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO53  0x200000U    // GPIO53 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO54  0x400000U    // GPIO54 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO55  0x800000U    // GPIO55 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO56  0x1000000U   // GPIO56 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO57  0x2000000U   // GPIO57 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO58  0x4000000U   // GPIO58 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO59  0x8000000U   // GPIO59 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO60  0x10000000U  // GPIO60 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO61  0x20000000U  // GPIO61 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO62  0x40000000U  // GPIO62 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO63  0x80000000U  // GPIO63 Enable for LPM Wakeup

//*****************************************************************************
//
// The following are defines for the bit fields in the TMR2CLKCTL register
//
//*****************************************************************************
#define SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_S  0U
#define SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_M  0x7U         // CPU Timer 2 Clock Source
                                               // Select Bit
#define SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_S  3U
#define SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_M  0x38U        // CPU Timer 2 Clock Pre-Scale
                                               // Value

//*****************************************************************************
//
// The following are defines for the bit fields in the RESCCLR register
//
//*****************************************************************************
#define SYSCTL_RESCCLR_POR        0x1U         // POR Reset Cause Indication
                                               // Bit
#define SYSCTL_RESCCLR_XRSN       0x2U         // XRSn Reset Cause Indication
                                               // Bit
#define SYSCTL_RESCCLR_WDRSN      0x4U         // WDRSn Reset Cause Indication
                                               // Bit
#define SYSCTL_RESCCLR_NMIWDRSN   0x8U         // NMIWDRSn Reset Cause
                                               // Indication Bit
#define SYSCTL_RESCCLR_SCCRESETN  0x100U       // SCCRESETn Reset Cause
                                               // Indication Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the RESC register
//
//*****************************************************************************
#define SYSCTL_RESC_POR           0x1U         // POR Reset Cause Indication
                                               // Bit
#define SYSCTL_RESC_XRSN          0x2U         // XRSn Reset Cause Indication
                                               // Bit
#define SYSCTL_RESC_WDRSN         0x4U         // WDRSn Reset Cause Indication
                                               // Bit
#define SYSCTL_RESC_NMIWDRSN      0x8U         // NMIWDRSn Reset Cause
                                               // Indication Bit
#define SYSCTL_RESC_SCCRESETN     0x100U       // SCCRESETn Reset Cause
                                               // Indication Bit
#define SYSCTL_RESC_XRSN_PIN_STATUS  0x40000000U  // XRSN Pin Status
#define SYSCTL_RESC_DCON          0x80000000U  // Debugger conntion status to
                                               // C28x

//*****************************************************************************
//
// The following are defines for the bit fields in the SCSR register
//
//*****************************************************************************
#define SYSCTL_SCSR_WDOVERRIDE    0x1U         // WD Override for WDDIS bit
#define SYSCTL_SCSR_WDENINT       0x2U         // WD Interrupt Enable
#define SYSCTL_SCSR_WDINTS        0x4U         // WD Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the WDCNTR register
//
//*****************************************************************************
#define SYSCTL_WDCNTR_WDCNTR_S    0U
#define SYSCTL_WDCNTR_WDCNTR_M    0xFFU        // WD Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the WDKEY register
//
//*****************************************************************************
#define SYSCTL_WDKEY_WDKEY_S      0U
#define SYSCTL_WDKEY_WDKEY_M      0xFFU        // WD KEY

//*****************************************************************************
//
// The following are defines for the bit fields in the WDCR register
//
//*****************************************************************************
#define SYSCTL_WDCR_WDPS_S        0U
#define SYSCTL_WDCR_WDPS_M        0x7U         // WD Clock Prescalar
#define SYSCTL_WDCR_WDCHK_S       3U
#define SYSCTL_WDCR_WDCHK_M       0x38U        // WD Check Bits
#define SYSCTL_WDCR_WDDIS         0x40U        // WD Disable
#define SYSCTL_WDCR_WDFLG         0x80U        // WD Reset Status Flag
#define SYSCTL_WDCR_WDPRECLKDIV_S  8U
#define SYSCTL_WDCR_WDPRECLKDIV_M  0xF00U       // WD Pre Clock Divider

//*****************************************************************************
//
// The following are defines for the bit fields in the WDWCR register
//
//*****************************************************************************
#define SYSCTL_WDWCR_MIN_S        0U
#define SYSCTL_WDWCR_MIN_M        0xFFU        // WD Min Threshold setting for
                                               // Windowed Watchdog
                                               // functionality
#define SYSCTL_WDWCR_FIRSTKEY     0x100U       // First Key Detect Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the CLA1TASKSRCSELLOCK register
//
//*****************************************************************************
#define SYSCTL_CLA1TASKSRCSELLOCK_CLA1TASKSRCSEL1  0x1U         // CLA1TASKSRCSEL1 Register Lock
                                               // bit
#define SYSCTL_CLA1TASKSRCSELLOCK_CLA1TASKSRCSEL2  0x2U         // CLA1TASKSRCSEL2 Register Lock
                                               // bit

//*****************************************************************************
//
// The following are defines for the bit fields in the DMACHSRCSELLOCK register
//
//*****************************************************************************
#define SYSCTL_DMACHSRCSELLOCK_DMACHSRCSEL1  0x1U         // DMACHSRCSEL1 Register Lock
                                               // bit
#define SYSCTL_DMACHSRCSELLOCK_DMACHSRCSEL2  0x2U         // DMACHSRCSEL2 Register Lock
                                               // bit

//*****************************************************************************
//
// The following are defines for the bit fields in the CLA1TASKSRCSEL1 register
//
//*****************************************************************************
#define SYSCTL_CLA1TASKSRCSEL1_TASK1_S  0U
#define SYSCTL_CLA1TASKSRCSEL1_TASK1_M  0xFFU        // Selects the Trigger Source
                                               // for TASK1 of CLA1
#define SYSCTL_CLA1TASKSRCSEL1_TASK2_S  8U
#define SYSCTL_CLA1TASKSRCSEL1_TASK2_M  0xFF00U      // Selects the Trigger Source
                                               // for TASK2 of CLA1
#define SYSCTL_CLA1TASKSRCSEL1_TASK3_S  16U
#define SYSCTL_CLA1TASKSRCSEL1_TASK3_M  0xFF0000U    // Selects the Trigger Source
                                               // for TASK3 of CLA1
#define SYSCTL_CLA1TASKSRCSEL1_TASK4_S  24U
#define SYSCTL_CLA1TASKSRCSEL1_TASK4_M  0xFF000000U  // Selects the Trigger Source
                                               // for TASK4 of CLA1

//*****************************************************************************
//
// The following are defines for the bit fields in the CLA1TASKSRCSEL2 register
//
//*****************************************************************************
#define SYSCTL_CLA1TASKSRCSEL2_TASK5_S  0U
#define SYSCTL_CLA1TASKSRCSEL2_TASK5_M  0xFFU        // Selects the Trigger Source
                                               // for TASK5 of CLA1
#define SYSCTL_CLA1TASKSRCSEL2_TASK6_S  8U
#define SYSCTL_CLA1TASKSRCSEL2_TASK6_M  0xFF00U      // Selects the Trigger Source
                                               // for TASK6 of CLA1
#define SYSCTL_CLA1TASKSRCSEL2_TASK7_S  16U
#define SYSCTL_CLA1TASKSRCSEL2_TASK7_M  0xFF0000U    // Selects the Trigger Source
                                               // for TASK7 of CLA1
#define SYSCTL_CLA1TASKSRCSEL2_TASK8_S  24U
#define SYSCTL_CLA1TASKSRCSEL2_TASK8_M  0xFF000000U  // Selects the Trigger Source
                                               // for TASK8 of CLA1

//*****************************************************************************
//
// The following are defines for the bit fields in the DMACHSRCSEL1 register
//
//*****************************************************************************
#define SYSCTL_DMACHSRCSEL1_CH1_S  0U
#define SYSCTL_DMACHSRCSEL1_CH1_M  0xFFU        // Selects the Trigger and Sync
                                               // Source CH1 of DMA
#define SYSCTL_DMACHSRCSEL1_CH2_S  8U
#define SYSCTL_DMACHSRCSEL1_CH2_M  0xFF00U      // Selects the Trigger and Sync
                                               // Source CH2 of DMA
#define SYSCTL_DMACHSRCSEL1_CH3_S  16U
#define SYSCTL_DMACHSRCSEL1_CH3_M  0xFF0000U    // Selects the Trigger and Sync
                                               // Source CH3 of DMA
#define SYSCTL_DMACHSRCSEL1_CH4_S  24U
#define SYSCTL_DMACHSRCSEL1_CH4_M  0xFF000000U  // Selects the Trigger and Sync
                                               // Source CH4 of DMA

//*****************************************************************************
//
// The following are defines for the bit fields in the DMACHSRCSEL2 register
//
//*****************************************************************************
#define SYSCTL_DMACHSRCSEL2_CH5_S  0U
#define SYSCTL_DMACHSRCSEL2_CH5_M  0xFFU        // Selects the Trigger and Sync
                                               // Source CH5 of DMA
#define SYSCTL_DMACHSRCSEL2_CH6_S  8U
#define SYSCTL_DMACHSRCSEL2_CH6_M  0xFF00U      // Selects the Trigger and Sync
                                               // Source CH6 of DMA

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCA_AC register
//
//*****************************************************************************
#define SYSCTL_ADCA_AC_CPU1_ACC_S  0U
#define SYSCTL_ADCA_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ADCA_AC_CLA1_ACC_S  2U
#define SYSCTL_ADCA_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ADCA_AC_DMA1_ACC_S  4U
#define SYSCTL_ADCA_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCB_AC register
//
//*****************************************************************************
#define SYSCTL_ADCB_AC_CPU1_ACC_S  0U
#define SYSCTL_ADCB_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ADCB_AC_CLA1_ACC_S  2U
#define SYSCTL_ADCB_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ADCB_AC_DMA1_ACC_S  4U
#define SYSCTL_ADCB_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCC_AC register
//
//*****************************************************************************
#define SYSCTL_ADCC_AC_CPU1_ACC_S  0U
#define SYSCTL_ADCC_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ADCC_AC_CLA1_ACC_S  2U
#define SYSCTL_ADCC_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ADCC_AC_DMA1_ACC_S  4U
#define SYSCTL_ADCC_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPSS1_AC register
//
//*****************************************************************************
#define SYSCTL_CMPSS1_AC_CPU1_ACC_S  0U
#define SYSCTL_CMPSS1_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CMPSS1_AC_CLA1_ACC_S  2U
#define SYSCTL_CMPSS1_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_CMPSS1_AC_DMA1_ACC_S  4U
#define SYSCTL_CMPSS1_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPSS2_AC register
//
//*****************************************************************************
#define SYSCTL_CMPSS2_AC_CPU1_ACC_S  0U
#define SYSCTL_CMPSS2_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CMPSS2_AC_CLA1_ACC_S  2U
#define SYSCTL_CMPSS2_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_CMPSS2_AC_DMA1_ACC_S  4U
#define SYSCTL_CMPSS2_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPSS3_AC register
//
//*****************************************************************************
#define SYSCTL_CMPSS3_AC_CPU1_ACC_S  0U
#define SYSCTL_CMPSS3_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CMPSS3_AC_CLA1_ACC_S  2U
#define SYSCTL_CMPSS3_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_CMPSS3_AC_DMA1_ACC_S  4U
#define SYSCTL_CMPSS3_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPSS4_AC register
//
//*****************************************************************************
#define SYSCTL_CMPSS4_AC_CPU1_ACC_S  0U
#define SYSCTL_CMPSS4_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CMPSS4_AC_CLA1_ACC_S  2U
#define SYSCTL_CMPSS4_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_CMPSS4_AC_DMA1_ACC_S  4U
#define SYSCTL_CMPSS4_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPSS5_AC register
//
//*****************************************************************************
#define SYSCTL_CMPSS5_AC_CPU1_ACC_S  0U
#define SYSCTL_CMPSS5_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CMPSS5_AC_CLA1_ACC_S  2U
#define SYSCTL_CMPSS5_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_CMPSS5_AC_DMA1_ACC_S  4U
#define SYSCTL_CMPSS5_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPSS6_AC register
//
//*****************************************************************************
#define SYSCTL_CMPSS6_AC_CPU1_ACC_S  0U
#define SYSCTL_CMPSS6_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CMPSS6_AC_CLA1_ACC_S  2U
#define SYSCTL_CMPSS6_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_CMPSS6_AC_DMA1_ACC_S  4U
#define SYSCTL_CMPSS6_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPSS7_AC register
//
//*****************************************************************************
#define SYSCTL_CMPSS7_AC_CPU1_ACC_S  0U
#define SYSCTL_CMPSS7_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CMPSS7_AC_CLA1_ACC_S  2U
#define SYSCTL_CMPSS7_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_CMPSS7_AC_DMA1_ACC_S  4U
#define SYSCTL_CMPSS7_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the DACA_AC register
//
//*****************************************************************************
#define SYSCTL_DACA_AC_CPU1_ACC_S  0U
#define SYSCTL_DACA_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_DACA_AC_CLA1_ACC_S  2U
#define SYSCTL_DACA_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_DACA_AC_DMA1_ACC_S  4U
#define SYSCTL_DACA_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the DACB_AC register
//
//*****************************************************************************
#define SYSCTL_DACB_AC_CPU1_ACC_S  0U
#define SYSCTL_DACB_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_DACB_AC_CLA1_ACC_S  2U
#define SYSCTL_DACB_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_DACB_AC_DMA1_ACC_S  4U
#define SYSCTL_DACB_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAA_AC register
//
//*****************************************************************************
#define SYSCTL_PGAA_AC_CPU1_ACC_S  0U
#define SYSCTL_PGAA_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_PGAA_AC_CLA1_ACC_S  2U
#define SYSCTL_PGAA_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_PGAA_AC_DMA1_ACC_S  4U
#define SYSCTL_PGAA_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAB_AC register
//
//*****************************************************************************
#define SYSCTL_PGAB_AC_CPU1_ACC_S  0U
#define SYSCTL_PGAB_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_PGAB_AC_CLA1_ACC_S  2U
#define SYSCTL_PGAB_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_PGAB_AC_DMA1_ACC_S  4U
#define SYSCTL_PGAB_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAC_AC register
//
//*****************************************************************************
#define SYSCTL_PGAC_AC_CPU1_ACC_S  0U
#define SYSCTL_PGAC_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_PGAC_AC_CLA1_ACC_S  2U
#define SYSCTL_PGAC_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_PGAC_AC_DMA1_ACC_S  4U
#define SYSCTL_PGAC_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAD_AC register
//
//*****************************************************************************
#define SYSCTL_PGAD_AC_CPU1_ACC_S  0U
#define SYSCTL_PGAD_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_PGAD_AC_CLA1_ACC_S  2U
#define SYSCTL_PGAD_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_PGAD_AC_DMA1_ACC_S  4U
#define SYSCTL_PGAD_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAE_AC register
//
//*****************************************************************************
#define SYSCTL_PGAE_AC_CPU1_ACC_S  0U
#define SYSCTL_PGAE_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_PGAE_AC_CLA1_ACC_S  2U
#define SYSCTL_PGAE_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_PGAE_AC_DMA1_ACC_S  4U
#define SYSCTL_PGAE_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAF_AC register
//
//*****************************************************************************
#define SYSCTL_PGAF_AC_CPU1_ACC_S  0U
#define SYSCTL_PGAF_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_PGAF_AC_CLA1_ACC_S  2U
#define SYSCTL_PGAF_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_PGAF_AC_DMA1_ACC_S  4U
#define SYSCTL_PGAF_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAG_AC register
//
//*****************************************************************************
#define SYSCTL_PGAG_AC_CPU1_ACC_S  0U
#define SYSCTL_PGAG_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_PGAG_AC_CLA1_ACC_S  2U
#define SYSCTL_PGAG_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_PGAG_AC_DMA1_ACC_S  4U
#define SYSCTL_PGAG_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EPWM1_AC register
//
//*****************************************************************************
#define SYSCTL_EPWM1_AC_CPU1_ACC_S  0U
#define SYSCTL_EPWM1_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EPWM1_AC_CLA1_ACC_S  2U
#define SYSCTL_EPWM1_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EPWM1_AC_DMA1_ACC_S  4U
#define SYSCTL_EPWM1_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EPWM2_AC register
//
//*****************************************************************************
#define SYSCTL_EPWM2_AC_CPU1_ACC_S  0U
#define SYSCTL_EPWM2_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EPWM2_AC_CLA1_ACC_S  2U
#define SYSCTL_EPWM2_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EPWM2_AC_DMA1_ACC_S  4U
#define SYSCTL_EPWM2_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EPWM3_AC register
//
//*****************************************************************************
#define SYSCTL_EPWM3_AC_CPU1_ACC_S  0U
#define SYSCTL_EPWM3_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EPWM3_AC_CLA1_ACC_S  2U
#define SYSCTL_EPWM3_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EPWM3_AC_DMA1_ACC_S  4U
#define SYSCTL_EPWM3_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EPWM4_AC register
//
//*****************************************************************************
#define SYSCTL_EPWM4_AC_CPU1_ACC_S  0U
#define SYSCTL_EPWM4_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EPWM4_AC_CLA1_ACC_S  2U
#define SYSCTL_EPWM4_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EPWM4_AC_DMA1_ACC_S  4U
#define SYSCTL_EPWM4_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EPWM5_AC register
//
//*****************************************************************************
#define SYSCTL_EPWM5_AC_CPU1_ACC_S  0U
#define SYSCTL_EPWM5_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EPWM5_AC_CLA1_ACC_S  2U
#define SYSCTL_EPWM5_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EPWM5_AC_DMA1_ACC_S  4U
#define SYSCTL_EPWM5_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EPWM6_AC register
//
//*****************************************************************************
#define SYSCTL_EPWM6_AC_CPU1_ACC_S  0U
#define SYSCTL_EPWM6_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EPWM6_AC_CLA1_ACC_S  2U
#define SYSCTL_EPWM6_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EPWM6_AC_DMA1_ACC_S  4U
#define SYSCTL_EPWM6_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EPWM7_AC register
//
//*****************************************************************************
#define SYSCTL_EPWM7_AC_CPU1_ACC_S  0U
#define SYSCTL_EPWM7_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EPWM7_AC_CLA1_ACC_S  2U
#define SYSCTL_EPWM7_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EPWM7_AC_DMA1_ACC_S  4U
#define SYSCTL_EPWM7_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EPWM8_AC register
//
//*****************************************************************************
#define SYSCTL_EPWM8_AC_CPU1_ACC_S  0U
#define SYSCTL_EPWM8_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EPWM8_AC_CLA1_ACC_S  2U
#define SYSCTL_EPWM8_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EPWM8_AC_DMA1_ACC_S  4U
#define SYSCTL_EPWM8_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EQEP1_AC register
//
//*****************************************************************************
#define SYSCTL_EQEP1_AC_CPU1_ACC_S  0U
#define SYSCTL_EQEP1_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EQEP1_AC_CLA1_ACC_S  2U
#define SYSCTL_EQEP1_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EQEP1_AC_DMA1_ACC_S  4U
#define SYSCTL_EQEP1_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the EQEP2_AC register
//
//*****************************************************************************
#define SYSCTL_EQEP2_AC_CPU1_ACC_S  0U
#define SYSCTL_EQEP2_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_EQEP2_AC_CLA1_ACC_S  2U
#define SYSCTL_EQEP2_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_EQEP2_AC_DMA1_ACC_S  4U
#define SYSCTL_EQEP2_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the ECAP1_AC register
//
//*****************************************************************************
#define SYSCTL_ECAP1_AC_CPU1_ACC_S  0U
#define SYSCTL_ECAP1_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ECAP1_AC_CLA1_ACC_S  2U
#define SYSCTL_ECAP1_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ECAP1_AC_DMA1_ACC_S  4U
#define SYSCTL_ECAP1_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the ECAP2_AC register
//
//*****************************************************************************
#define SYSCTL_ECAP2_AC_CPU1_ACC_S  0U
#define SYSCTL_ECAP2_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ECAP2_AC_CLA1_ACC_S  2U
#define SYSCTL_ECAP2_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ECAP2_AC_DMA1_ACC_S  4U
#define SYSCTL_ECAP2_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the ECAP3_AC register
//
//*****************************************************************************
#define SYSCTL_ECAP3_AC_CPU1_ACC_S  0U
#define SYSCTL_ECAP3_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ECAP3_AC_CLA1_ACC_S  2U
#define SYSCTL_ECAP3_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ECAP3_AC_DMA1_ACC_S  4U
#define SYSCTL_ECAP3_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the ECAP4_AC register
//
//*****************************************************************************
#define SYSCTL_ECAP4_AC_CPU1_ACC_S  0U
#define SYSCTL_ECAP4_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ECAP4_AC_CLA1_ACC_S  2U
#define SYSCTL_ECAP4_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ECAP4_AC_DMA1_ACC_S  4U
#define SYSCTL_ECAP4_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the ECAP5_AC register
//
//*****************************************************************************
#define SYSCTL_ECAP5_AC_CPU1_ACC_S  0U
#define SYSCTL_ECAP5_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ECAP5_AC_CLA1_ACC_S  2U
#define SYSCTL_ECAP5_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ECAP5_AC_DMA1_ACC_S  4U
#define SYSCTL_ECAP5_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the ECAP6_AC register
//
//*****************************************************************************
#define SYSCTL_ECAP6_AC_CPU1_ACC_S  0U
#define SYSCTL_ECAP6_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ECAP6_AC_CLA1_ACC_S  2U
#define SYSCTL_ECAP6_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ECAP6_AC_DMA1_ACC_S  4U
#define SYSCTL_ECAP6_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the ECAP7_AC register
//
//*****************************************************************************
#define SYSCTL_ECAP7_AC_CPU1_ACC_S  0U
#define SYSCTL_ECAP7_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_ECAP7_AC_CLA1_ACC_S  2U
#define SYSCTL_ECAP7_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_ECAP7_AC_DMA1_ACC_S  4U
#define SYSCTL_ECAP7_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the SDFM1_AC register
//
//*****************************************************************************
#define SYSCTL_SDFM1_AC_CPU1_ACC_S  0U
#define SYSCTL_SDFM1_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_SDFM1_AC_CLA1_ACC_S  2U
#define SYSCTL_SDFM1_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_SDFM1_AC_DMA1_ACC_S  4U
#define SYSCTL_SDFM1_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CLB1_AC register
//
//*****************************************************************************
#define SYSCTL_CLB1_AC_CPU1_ACC_S  0U
#define SYSCTL_CLB1_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CLB1_AC_CLA1_ACC_S  2U
#define SYSCTL_CLB1_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CLB2_AC register
//
//*****************************************************************************
#define SYSCTL_CLB2_AC_CPU1_ACC_S  0U
#define SYSCTL_CLB2_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CLB2_AC_CLA1_ACC_S  2U
#define SYSCTL_CLB2_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CLB3_AC register
//
//*****************************************************************************
#define SYSCTL_CLB3_AC_CPU1_ACC_S  0U
#define SYSCTL_CLB3_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CLB3_AC_CLA1_ACC_S  2U
#define SYSCTL_CLB3_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CLB4_AC register
//
//*****************************************************************************
#define SYSCTL_CLB4_AC_CPU1_ACC_S  0U
#define SYSCTL_CLB4_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CLB4_AC_CLA1_ACC_S  2U
#define SYSCTL_CLB4_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the CLA1PROMCRC_AC register
//
//*****************************************************************************
#define SYSCTL_CLA1PROMCRC_AC_CPU1_ACC_S  0U
#define SYSCTL_CLA1PROMCRC_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_CLA1PROMCRC_AC_CLA1_ACC_S  2U
#define SYSCTL_CLA1PROMCRC_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the SPIA_AC register
//
//*****************************************************************************
#define SYSCTL_SPIA_AC_CPU1_ACC_S  0U
#define SYSCTL_SPIA_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_SPIA_AC_CLA1_ACC_S  2U
#define SYSCTL_SPIA_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_SPIA_AC_DMA1_ACC_S  4U
#define SYSCTL_SPIA_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the SPIB_AC register
//
//*****************************************************************************
#define SYSCTL_SPIB_AC_CPU1_ACC_S  0U
#define SYSCTL_SPIB_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_SPIB_AC_CLA1_ACC_S  2U
#define SYSCTL_SPIB_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_SPIB_AC_DMA1_ACC_S  4U
#define SYSCTL_SPIB_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the PMBUS_A_AC register
//
//*****************************************************************************
#define SYSCTL_PMBUS_A_AC_CPU1_ACC_S  0U
#define SYSCTL_PMBUS_A_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_PMBUS_A_AC_CLA1_ACC_S  2U
#define SYSCTL_PMBUS_A_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_PMBUS_A_AC_DMA1_ACC_S  4U
#define SYSCTL_PMBUS_A_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the LIN_A_AC register
//
//*****************************************************************************
#define SYSCTL_LIN_A_AC_CPU1_ACC_S  0U
#define SYSCTL_LIN_A_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_LIN_A_AC_CLA1_ACC_S  2U
#define SYSCTL_LIN_A_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_LIN_A_AC_DMA1_ACC_S  4U
#define SYSCTL_LIN_A_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the DCANA_AC register
//
//*****************************************************************************
#define SYSCTL_DCANA_AC_CPU1_ACC_S  0U
#define SYSCTL_DCANA_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_DCANA_AC_DMA1_ACC_S  4U
#define SYSCTL_DCANA_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the DCANB_AC register
//
//*****************************************************************************
#define SYSCTL_DCANB_AC_CPU1_ACC_S  0U
#define SYSCTL_DCANB_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_DCANB_AC_DMA1_ACC_S  4U
#define SYSCTL_DCANB_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the FSIATX_AC register
//
//*****************************************************************************
#define SYSCTL_FSIATX_AC_CPU1_ACC_S  0U
#define SYSCTL_FSIATX_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_FSIATX_AC_CLA1_ACC_S  2U
#define SYSCTL_FSIATX_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_FSIATX_AC_DMA1_ACC_S  4U
#define SYSCTL_FSIATX_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the FSIARX_AC register
//
//*****************************************************************************
#define SYSCTL_FSIARX_AC_CPU1_ACC_S  0U
#define SYSCTL_FSIARX_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_FSIARX_AC_CLA1_ACC_S  2U
#define SYSCTL_FSIARX_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_FSIARX_AC_DMA1_ACC_S  4U
#define SYSCTL_FSIARX_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the HRPWM_A_AC register
//
//*****************************************************************************
#define SYSCTL_HRPWM_A_AC_CPU1_ACC_S  0U
#define SYSCTL_HRPWM_A_AC_CPU1_ACC_M  0x3U         // CPU1 Access conditions to
                                               // peripheral
#define SYSCTL_HRPWM_A_AC_CLA1_ACC_S  2U
#define SYSCTL_HRPWM_A_AC_CLA1_ACC_M  0xCU         // CLA1 Access Conditions to
                                               // Peripheral
#define SYSCTL_HRPWM_A_AC_DMA1_ACC_S  4U
#define SYSCTL_HRPWM_A_AC_DMA1_ACC_M  0x30U        // DMA1 Access Conditions to
                                               // Peripheral

//*****************************************************************************
//
// The following are defines for the bit fields in the PERIPH_AC_LOCK register
//
//*****************************************************************************
#define SYSCTL_PERIPH_AC_LOCK_LOCK_AC_WR  0x1U         // Lock control for Access
                                               // control registers write.
#endif
