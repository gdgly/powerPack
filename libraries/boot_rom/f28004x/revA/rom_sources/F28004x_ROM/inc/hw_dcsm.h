//###########################################################################
//
// FILE:    hw_dcsm.h
//
// TITLE:   Definitions for the DCSM registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __HW_DCSM_H__
#define __HW_DCSM_H__

//*****************************************************************************
//
// The following are defines for the DCSM register offsets
//
//*****************************************************************************
#define DCSM_O_B0_Z1OTP_LINKPOINTER1  0x0U         // Zone 1 Link Pointer1 in Z1
                                               // OTP for flash BANK0
#define DCSM_O_B0_Z1OTP_LINKPOINTER2  0x4U         // Zone 1 Link Pointer2 in Z1
                                               // OTP for flash BANK0
#define DCSM_O_B0_Z1OTP_LINKPOINTER3  0x8U         // Zone 1 Link Pointer3 in Z1
                                               // OTP for flash BANK0
#define DCSM_O_B0_Z1OTP_GPREG1    0xCU         // Zone-1 General Purpose
                                               // Register-1 content
#define DCSM_O_B0_Z1OTP_GPREG2    0xEU         // Zone-1 General Purpose
                                               // Register-2 content
#define DCSM_O_Z1OTP_PSWDLOCK     0x10U        // Secure Password Lock in Z1
                                               // OTP
#define DCSM_O_Z1OTP_CRCLOCK      0x14U        // Secure CRC Lock in Z1 OTP
#define DCSM_O_Z1OTP_JTAGLOCK     0x18U        // Secure JTAG Lock in Z1 OTP
#define DCSM_O_B0_Z1OTP_GPREG3    0x1CU        // Zone-1 General Purpose
                                               // Register-3 content
#define DCSM_O_B0_Z1OTP_BOOTCTRL  0x1EU        // Boot Mode in Z1 OTP
#define DCSM_O_B0_Z2OTP_LINKPOINTER1  0x0U         // Zone 2Link Pointer1 in Z2 OTP
                                               // for flash BANK0
#define DCSM_O_B0_Z2OTP_LINKPOINTER2  0x4U         // Zone 2 Link Pointer2 in Z2
                                               // OTP for flash BANK0
#define DCSM_O_B0_Z2OTP_LINKPOINTER3  0x8U         // Zone 12Link Pointer3 in Z2
                                               // OTP for flash BANK0
#define DCSM_O_B0_Z2OTP_GPREG1    0xCU         // Zone-2 General Purpose
                                               // Register-1 content
#define DCSM_O_B0_Z2OTP_GPREG2    0xEU         // Zone-2 General Purpose
                                               // Register-2 content
#define DCSM_O_Z2OTP_PSWDLOCK     0x10U        // Secure Password Lock in Z2
                                               // OTP
#define DCSM_O_Z2OTP_CRCLOCK      0x14U        // Secure CRC Lock in Z2 OTP
#define DCSM_O_Z2OTP_JTAGLOCK     0x18U        // Secure JTAG Lock in Z2 OTP
#define DCSM_O_B0_Z2OTP_GPREG3    0x1CU        // Zone-2 General Purpose
                                               // Register-3 content
#define DCSM_O_B0_Z2OTP_BOOTCTRL  0x1EU        // Boot Mode in Z2 OTP
#define DCSM_O_B0_Z1_LINKPOINTER  0x0U         // Zone 1 Link Pointer for flash
                                               // BANK0
#define DCSM_O_Z1_OTPSECLOCK      0x2U         // Zone 1 OTP Secure JTAG lock
#define DCSM_O_B0_Z1_BOOTCTRL     0x4U         // Boot Mode Control
#define DCSM_O_B0_Z1_LINKPOINTERERR  0x6U         // Link Pointer Error for flash
                                               // BANK0
#define DCSM_O_B0_Z1_GPREG1       0x8U         // Zone1 General Purpose
                                               // Register-1
#define DCSM_O_B0_Z1_GPREG2       0xAU         // Zone1 General Purpose
                                               // Register-2
#define DCSM_O_B0_Z1_GPREG3       0xCU         // Zone1 General Purpose
                                               // Register-3
#define DCSM_O_Z1_CSMKEY0         0x10U        // Zone 1 CSM Key 0
#define DCSM_O_Z1_CSMKEY1         0x12U        // Zone 1 CSM Key 1
#define DCSM_O_Z1_CSMKEY2         0x14U        // Zone 1 CSM Key 2
#define DCSM_O_Z1_CSMKEY3         0x16U        // Zone 1 CSM Key 3
#define DCSM_O_Z1_CR              0x19U        // Zone 1 CSM Control Register
#define DCSM_O_B0_Z1_GRABSECTR    0x1AU        // Zone 1 Grab Flash BANK0
                                               // Sectors Register
#define DCSM_O_Z1_GRABRAMR        0x1CU        // Zone 1 Grab RAM Blocks
                                               // Register
#define DCSM_O_B0_Z1_EXEONLYSECTR  0x1EU        // Zone 1 Flash BANK0
                                               // Execute_Only Sector Register
#define DCSM_O_Z1_EXEONLYRAMR     0x20U        // Zone 1 RAM Execute_Only Block
                                               // Register
#define DCSM_O_B0_Z2_LINKPOINTER  0x0U         // Zone 2 Link Pointer for flash
                                               // BANK0
#define DCSM_O_Z2_OTPSECLOCK      0x2U         // Zone 2 OTP Secure JTAG lock
#define DCSM_O_B0_Z2_BOOTCTRL     0x4U         // Boot Mode Control
#define DCSM_O_B0_Z2_LINKPOINTERERR  0x6U         // Link Pointer Error for flash
                                               // BANK0
#define DCSM_O_B0_Z2_GPREG1       0x8U         // Zone2 General Purpose
                                               // Register-1
#define DCSM_O_B0_Z2_GPREG2       0xAU         // Zone2 General Purpose
                                               // Register-2
#define DCSM_O_B0_Z2_GPREG3       0xCU         // Zone2 General Purpose
                                               // Register-3
#define DCSM_O_Z2_CSMKEY0         0x10U        // Zone 2 CSM Key 0
#define DCSM_O_Z2_CSMKEY1         0x12U        // Zone 2 CSM Key 1
#define DCSM_O_Z2_CSMKEY2         0x14U        // Zone 2 CSM Key 2
#define DCSM_O_Z2_CSMKEY3         0x16U        // Zone 2 CSM Key 3
#define DCSM_O_Z2_CR              0x19U        // Zone 2 CSM Control Register
#define DCSM_O_B0_Z2_GRABSECTR    0x1AU        // Zone 2 Grab Flash BANK0
                                               // Sectors Register
#define DCSM_O_Z2_GRABRAMR        0x1CU        // Zone 2 Grab RAM Blocks
                                               // Register
#define DCSM_O_B0_Z2_EXEONLYSECTR  0x1EU        // Zone 2 Flash BANK0
                                               // Execute_Only Sector Register
#define DCSM_O_Z2_EXEONLYRAMR     0x20U        // Zone 2 RAM Execute_Only Block
                                               // Register
#define DCSM_O_FLSEM              0x0U         // Flash Wrapper Semaphore
                                               // Register
#define DCSM_O_B0_SECTSTAT        0x2U         // Flash BANK0 Sectors Status
                                               // Register
#define DCSM_O_RAMSTAT            0x4U         // RAM Status Register
#define DCSM_O_B1_SECTSTAT        0x8U         // Flash BANK1 Sectors Status
                                               // Register
#define DCSM_O_SECERRSTAT         0xAU         // Security Error Status
                                               // Register
#define DCSM_O_SECERRCLR          0xCU         // Security Error Clear Register
#define DCSM_O_SECERRFRC          0xEU         // Security Error Force Register
#define DCSM_O_RAMOPENSTAT        0x0U         // RAM Security Open Status Bit
#define DCSM_O_RAMOPENFRC         0x2U         // RAM Security Open Force
                                               // Register
#define DCSM_O_RAMOPENCLR         0x4U         // RAM Security Open Clear
                                               // Register
#define DCSM_O_RAMOPENLOCK        0x6U         // RAMOPEN Lock Register
#define DCSM_O_B1_Z1OTP_LINKPOINTER1  0x0U         // Zone 1 Link Pointer1 in Z1
                                               // OTP for flash BANK1
#define DCSM_O_B1_Z1OTP_LINKPOINTER2  0x4U         // Zone 1 Link Pointer2 in Z1
                                               // OTP for flash BANK1
#define DCSM_O_B1_Z1OTP_LINKPOINTER3  0x8U         // Zone 1 Link Pointer3 in Z1
                                               // OTP for flash BANK1
#define DCSM_O_B1_Z2OTP_LINKPOINTER1  0x0U         // Zone 2 Link Pointer1 in Z2
                                               // OTP for flash BANK1
#define DCSM_O_B1_Z2OTP_LINKPOINTER2  0x4U         // Zone 2 Link Pointer2 in Z2
                                               // OTP for flash BANK1
#define DCSM_O_B1_Z2OTP_LINKPOINTER3  0x8U         // Zone 2 Link Pointer3 in Z2
                                               // OTP for flash BANK1
#define DCSM_O_B1_Z1_LINKPOINTER  0x0U         // Zone 1 Link Pointer for flash
                                               // BANK1
#define DCSM_O_B1_Z1_LINKPOINTERERR  0x6U         // Link Pointer Error for flash
                                               // BANK1
#define DCSM_O_B1_Z1_GRABSECTR    0x1AU        // Zone 1 Grab Flash BANK1
                                               // Sectors Register
#define DCSM_O_B1_Z1_EXEONLYSECTR  0x1EU        // Zone 1 Flash BANK1
                                               // Execute_Only Sector Register
#define DCSM_O_B1_Z2_LINKPOINTER  0x0U         // Zone 2 Link Pointer for flash
                                               // BANK1
#define DCSM_O_B1_Z2_LINKPOINTERERR  0x6U         // Link Pointer Error for flash
                                               // BANK1
#define DCSM_O_B1_Z2_GRABSECTR    0x1AU        // Zone 2 Grab Flash BANK1
                                               // Sectors Register
#define DCSM_O_B1_Z2_EXEONLYSECTR  0x1EU        // Zone 2 Flash BANK1
                                               // Execute_Only Sector Register

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z1_LINKPOINTER register
//
//*****************************************************************************
#define DCSM_B0_Z1_LINKPOINTER_LINKPOINTER_S  0U
#define DCSM_B0_Z1_LINKPOINTER_LINKPOINTER_M  0x1FFFFFFFU  // Zone1 LINK Pointer in flash
                                               // BANK0

//*****************************************************************************
//
// The following are defines for the bit fields in the Z1_OTPSECLOCK register
//
//*****************************************************************************
#define DCSM_Z1_OTPSECLOCK_JTAGLOCK_S  0U
#define DCSM_Z1_OTPSECLOCK_JTAGLOCK_M  0xFU         // Zone1 JTAG Lock.
#define DCSM_Z1_OTPSECLOCK_PSWDLOCK_S  4U
#define DCSM_Z1_OTPSECLOCK_PSWDLOCK_M  0xF0U        // Zone1 Password Lock.
#define DCSM_Z1_OTPSECLOCK_CRCLOCK_S  8U
#define DCSM_Z1_OTPSECLOCK_CRCLOCK_M  0xF00U       // Zone1 CRC Lock.

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z1_BOOTCTRL register
//
//*****************************************************************************
#define DCSM_B0_Z1_BOOTCTRL_KEY_S  0U
#define DCSM_B0_Z1_BOOTCTRL_KEY_M  0xFFU        // OTP Boot Key
#define DCSM_B0_Z1_BOOTCTRL_BMODE_S  8U
#define DCSM_B0_Z1_BOOTCTRL_BMODE_M  0xFF00U      // OTP Boot Mode
#define DCSM_B0_Z1_BOOTCTRL_BOOTPIN0_S  16U
#define DCSM_B0_Z1_BOOTCTRL_BOOTPIN0_M  0xFF0000U    // OTP Boot Pin 0 Mapping
#define DCSM_B0_Z1_BOOTCTRL_BOOTPIN1_S  24U
#define DCSM_B0_Z1_BOOTCTRL_BOOTPIN1_M  0xFF000000U  // OTP Boot Pin 1 Mapping

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z1_LINKPOINTERERR register
//
//*****************************************************************************
#define DCSM_B0_Z1_LINKPOINTERERR_Z1_LINKPOINTERERR_S  0U
#define DCSM_B0_Z1_LINKPOINTERERR_Z1_LINKPOINTERERR_M  0x1FFFFFFFU  // Error to Resolve Z1 Link
                                               // pointer from OTP loaded values

//*****************************************************************************
//
// The following are defines for the bit fields in the Z1_CR register
//
//*****************************************************************************
#define DCSM_Z1_CR_ALLZERO        0x8U         // CSMPSWD All Zeros
#define DCSM_Z1_CR_ALLONE         0x10U        // CSMPSWD All Ones
#define DCSM_Z1_CR_UNSECURE       0x20U        // CSMPSWD Match CSMKEY
#define DCSM_Z1_CR_ARMED          0x40U        // CSM Passwords Read Status
#define DCSM_Z1_CR_FORCESEC       0x8000U      // Force Secure

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z1_GRABSECTR register
//
//*****************************************************************************
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT0_S  0U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT0_M  0x3U         // Grab Flash Sector 0 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT1_S  2U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT1_M  0xCU         // Grab Flash Sector 1 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT2_S  4U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT2_M  0x30U        // Grab Flash Sector 2 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT3_S  6U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT3_M  0xC0U        // Grab Flash Sector 3 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT4_S  8U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT4_M  0x300U       // Grab Flash Sector 4 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT5_S  10U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT5_M  0xC00U       // Grab Flash Sector 5 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT6_S  12U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT6_M  0x3000U      // Grab Flash Sector 6 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT7_S  14U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT7_M  0xC000U      // Grab Flash Sector 7 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT8_S  16U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT8_M  0x30000U     // Grab Flash Sector 8 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT9_S  18U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT9_M  0xC0000U     // Grab Flash Sector 9 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT10_S  20U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT10_M  0x300000U    // Grab Flash Sector 10 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT11_S  22U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT11_M  0xC00000U    // Grab Flash Sector 11 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT12_S  24U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT12_M  0x3000000U   // Grab Flash Sector 12 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT13_S  26U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT13_M  0xC000000U   // Grab Flash Sector 13 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT14_S  28U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT14_M  0x30000000U  // Grab Flash Sector 14 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT15_S  30U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT15_M  0xC0000000U  // Grab Flash Sector 15 in BANK0

//*****************************************************************************
//
// The following are defines for the bit fields in the Z1_GRABRAMR register
//
//*****************************************************************************
#define DCSM_Z1_GRABRAMR_GRAB_RAM0_S  0U
#define DCSM_Z1_GRABRAMR_GRAB_RAM0_M  0x3U         // Grab RAM LS0
#define DCSM_Z1_GRABRAMR_GRAB_RAM1_S  2U
#define DCSM_Z1_GRABRAMR_GRAB_RAM1_M  0xCU         // Grab RAM LS1
#define DCSM_Z1_GRABRAMR_GRAB_RAM2_S  4U
#define DCSM_Z1_GRABRAMR_GRAB_RAM2_M  0x30U        // Grab RAM LS2
#define DCSM_Z1_GRABRAMR_GRAB_RAM3_S  6U
#define DCSM_Z1_GRABRAMR_GRAB_RAM3_M  0xC0U        // Grab RAM LS3
#define DCSM_Z1_GRABRAMR_GRAB_RAM4_S  8U
#define DCSM_Z1_GRABRAMR_GRAB_RAM4_M  0x300U       // Grab RAM LS4
#define DCSM_Z1_GRABRAMR_GRAB_RAM5_S  10U
#define DCSM_Z1_GRABRAMR_GRAB_RAM5_M  0xC00U       // Grab RAM LS5
#define DCSM_Z1_GRABRAMR_GRAB_RAM6_S  12U
#define DCSM_Z1_GRABRAMR_GRAB_RAM6_M  0x3000U      // Grab RAM LS6
#define DCSM_Z1_GRABRAMR_GRAB_RAM7_S  14U
#define DCSM_Z1_GRABRAMR_GRAB_RAM7_M  0xC000U      // Grab RAM LS7

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z1_EXEONLYSECTR register
//
//*****************************************************************************
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT0  0x1U         // Execute-Only Flash Sector 0
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT1  0x2U         // Execute-Only Flash Sector 1
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT2  0x4U         // Execute-Only Flash Sector 2
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT3  0x8U         // Execute-Only Flash Sector 3
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT4  0x10U        // Execute-Only Flash Sector 4
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT5  0x20U        // Execute-Only Flash Sector 5
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT6  0x40U        // Execute-Only Flash Sector 6
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT7  0x80U        // Execute-Only Flash Sector 7
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT8  0x100U       // Execute-Only Flash Sector 8
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT9  0x200U       // Execute-Only Flash Sector 9
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT10  0x400U       // Execute-Only Flash Sector 10
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT11  0x800U       // Execute-Only Flash Sector 11
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT12  0x1000U      // Execute-Only Flash Sector 12
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT13  0x2000U      // Execute-Only Flash Sector 13
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT14  0x4000U      // Execute-Only Flash Sector 14
                                               // in flash BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT15  0x8000U      // Execute-Only Flash Sector 15
                                               // in flash BANK0

//*****************************************************************************
//
// The following are defines for the bit fields in the Z1_EXEONLYRAMR register
//
//*****************************************************************************
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM0  0x1U         // Execute-Only RAM LS0
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM1  0x2U         // Execute-Only RAM LS1
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM2  0x4U         // Execute-Only RAM LS2
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM3  0x8U         // Execute-Only RAM LS3
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM4  0x10U        // Execute-Only RAM LS4
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM5  0x20U        // Execute-Only RAM LS5
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM6  0x40U        // Execute-Only RAM LS6
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM7  0x80U        // Execute-Only RAM LS7

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z2_LINKPOINTER register
//
//*****************************************************************************
#define DCSM_B0_Z2_LINKPOINTER_LINKPOINTER_S  0U
#define DCSM_B0_Z2_LINKPOINTER_LINKPOINTER_M  0x1FFFFFFFU  // Zone2 LINK Pointer in flash
                                               // BANK0

//*****************************************************************************
//
// The following are defines for the bit fields in the Z2_OTPSECLOCK register
//
//*****************************************************************************
#define DCSM_Z2_OTPSECLOCK_JTAGLOCK_S  0U
#define DCSM_Z2_OTPSECLOCK_JTAGLOCK_M  0xFU         // Zone2 JTAG Lock.
#define DCSM_Z2_OTPSECLOCK_PSWDLOCK_S  4U
#define DCSM_Z2_OTPSECLOCK_PSWDLOCK_M  0xF0U        // Zone2 Password Lock.
#define DCSM_Z2_OTPSECLOCK_CRCLOCK_S  8U
#define DCSM_Z2_OTPSECLOCK_CRCLOCK_M  0xF00U       // Zone2 CRC Lock.

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z2_BOOTCTRL register
//
//*****************************************************************************
#define DCSM_B0_Z2_BOOTCTRL_KEY_S  0U
#define DCSM_B0_Z2_BOOTCTRL_KEY_M  0xFFU        // OTP Boot Key
#define DCSM_B0_Z2_BOOTCTRL_BMODE_S  8U
#define DCSM_B0_Z2_BOOTCTRL_BMODE_M  0xFF00U      // OTP Boot Mode
#define DCSM_B0_Z2_BOOTCTRL_BOOTPIN0_S  16U
#define DCSM_B0_Z2_BOOTCTRL_BOOTPIN0_M  0xFF0000U    // OTP Boot Pin 0 Mapping
#define DCSM_B0_Z2_BOOTCTRL_BOOTPIN1_S  24U
#define DCSM_B0_Z2_BOOTCTRL_BOOTPIN1_M  0xFF000000U  // OTP Boot Pin 1 Mapping

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z2_LINKPOINTERERR register
//
//*****************************************************************************
#define DCSM_B0_Z2_LINKPOINTERERR_Z2_LINKPOINTERERR_S  0U
#define DCSM_B0_Z2_LINKPOINTERERR_Z2_LINKPOINTERERR_M  0x1FFFFFFFU  // Error to Resolve Z2 Link
                                               // pointer from OTP loaded values

//*****************************************************************************
//
// The following are defines for the bit fields in the Z2_CR register
//
//*****************************************************************************
#define DCSM_Z2_CR_ALLZERO        0x8U         // CSMPSWD All Zeros
#define DCSM_Z2_CR_ALLONE         0x10U        // CSMPSWD All Ones
#define DCSM_Z2_CR_UNSECURE       0x20U        // CSMPSWD Match CSMKEY
#define DCSM_Z2_CR_ARMED          0x40U        // CSM Passwords Read Status
#define DCSM_Z2_CR_FORCESEC       0x8000U      // Force Secure

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z2_GRABSECTR register
//
//*****************************************************************************
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT0_S  0U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT0_M  0x3U         // Grab Flash Sector 0 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT1_S  2U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT1_M  0xCU         // Grab Flash Sector 1 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT2_S  4U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT2_M  0x30U        // Grab Flash Sector 2 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT3_S  6U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT3_M  0xC0U        // Grab Flash Sector 3 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT4_S  8U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT4_M  0x300U       // Grab Flash Sector 4 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT5_S  10U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT5_M  0xC00U       // Grab Flash Sector 5 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT6_S  12U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT6_M  0x3000U      // Grab Flash Sector 6 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT7_S  14U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT7_M  0xC000U      // Grab Flash Sector 7 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT8_S  16U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT8_M  0x30000U     // Grab Flash Sector 8 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT9_S  18U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT9_M  0xC0000U     // Grab Flash Sector 9 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT10_S  20U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT10_M  0x300000U    // Grab Flash Sector 10 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT11_S  22U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT11_M  0xC00000U    // Grab Flash Sector 11 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT12_S  24U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT12_M  0x3000000U   // Grab Flash Sector 12 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT13_S  26U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT13_M  0xC000000U   // Grab Flash Sector 13 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT14_S  28U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT14_M  0x30000000U  // Grab Flash Sector 14 in flash
                                               // BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT15_S  30U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT15_M  0xC0000000U  // Grab Flash Sector 15 in flash
                                               // BANK0

//*****************************************************************************
//
// The following are defines for the bit fields in the Z2_GRABRAMR register
//
//*****************************************************************************
#define DCSM_Z2_GRABRAMR_GRAB_RAM0_S  0U
#define DCSM_Z2_GRABRAMR_GRAB_RAM0_M  0x3U         // Grab RAM LS0
#define DCSM_Z2_GRABRAMR_GRAB_RAM1_S  2U
#define DCSM_Z2_GRABRAMR_GRAB_RAM1_M  0xCU         // Grab RAM LS1
#define DCSM_Z2_GRABRAMR_GRAB_RAM2_S  4U
#define DCSM_Z2_GRABRAMR_GRAB_RAM2_M  0x30U        // Grab RAM LS2
#define DCSM_Z2_GRABRAMR_GRAB_RAM3_S  6U
#define DCSM_Z2_GRABRAMR_GRAB_RAM3_M  0xC0U        // Grab RAM LS3
#define DCSM_Z2_GRABRAMR_GRAB_RAM4_S  8U
#define DCSM_Z2_GRABRAMR_GRAB_RAM4_M  0x300U       // Grab RAM LS4
#define DCSM_Z2_GRABRAMR_GRAB_RAM5_S  10U
#define DCSM_Z2_GRABRAMR_GRAB_RAM5_M  0xC00U       // Grab RAM LS5
#define DCSM_Z2_GRABRAMR_GRAB_RAM6_S  12U
#define DCSM_Z2_GRABRAMR_GRAB_RAM6_M  0x3000U      // Grab RAM LS6
#define DCSM_Z2_GRABRAMR_GRAB_RAM7_S  14U
#define DCSM_Z2_GRABRAMR_GRAB_RAM7_M  0xC000U      // Grab RAM LS7

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_Z2_EXEONLYSECTR register
//
//*****************************************************************************
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT0  0x1U         // Execute-Only Flash Sector 0
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT1  0x2U         // Execute-Only Flash Sector 1
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT2  0x4U         // Execute-Only Flash Sector 2
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT3  0x8U         // Execute-Only Flash Sector 3
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT4  0x10U        // Execute-Only Flash Sector 4
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT5  0x20U        // Execute-Only Flash Sector 5
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT6  0x40U        // Execute-Only Flash Sector 6
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT7  0x80U        // Execute-Only Flash Sector 7
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT8  0x100U       // Execute-Only Flash Sector 8
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT9  0x200U       // Execute-Only Flash Sector 9
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT10  0x400U       // Execute-Only Flash Sector 10
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT11  0x800U       // Execute-Only Flash Sector 11
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT12  0x1000U      // Execute-Only Flash Sector 12
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT13  0x2000U      // Execute-Only Flash Sector 13
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT14  0x4000U      // Execute-Only Flash Sector 14
                                               // in flash BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT15  0x8000U      // Execute-Only Flash Sector 15
                                               // in flash BANK0

//*****************************************************************************
//
// The following are defines for the bit fields in the Z2_EXEONLYRAMR register
//
//*****************************************************************************
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM0  0x1U         // Execute-Only RAM LS0
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM1  0x2U         // Execute-Only RAM LS1
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM2  0x4U         // Execute-Only RAM LS2
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM3  0x8U         // Execute-Only RAM LS3
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM4  0x10U        // Execute-Only RAM LS4
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM5  0x20U        // Execute-Only RAM LS5
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM6  0x40U        // Execute-Only RAM LS6
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM7  0x80U        // Execute-Only RAM LS7

//*****************************************************************************
//
// The following are defines for the bit fields in the FLSEM register
//
//*****************************************************************************
#define DCSM_FLSEM_SEM_S          0U
#define DCSM_FLSEM_SEM_M          0x3U         // Flash Semaphore Bit
#define DCSM_FLSEM_KEY_S          8U
#define DCSM_FLSEM_KEY_M          0xFF00U      // Semaphore Key

//*****************************************************************************
//
// The following are defines for the bit fields in the B0_SECTSTAT register
//
//*****************************************************************************
#define DCSM_B0_SECTSTAT_STATUS_SECT0_S  0U
#define DCSM_B0_SECTSTAT_STATUS_SECT0_M  0x3U         // Zone Status flash BANK0
                                               // Sector 0
#define DCSM_B0_SECTSTAT_STATUS_SECT1_S  2U
#define DCSM_B0_SECTSTAT_STATUS_SECT1_M  0xCU         // Zone Status flash BANK0
                                               // sector 1
#define DCSM_B0_SECTSTAT_STATUS_SECT2_S  4U
#define DCSM_B0_SECTSTAT_STATUS_SECT2_M  0x30U        // Zone Status flash BANK0
                                               // Sector 2
#define DCSM_B0_SECTSTAT_STATUS_SECT3_S  6U
#define DCSM_B0_SECTSTAT_STATUS_SECT3_M  0xC0U        // Zone Status flash BANK0
                                               // Sector 3
#define DCSM_B0_SECTSTAT_STATUS_SECT4_S  8U
#define DCSM_B0_SECTSTAT_STATUS_SECT4_M  0x300U       // Zone Status flash BANK0
                                               // Sector 4
#define DCSM_B0_SECTSTAT_STATUS_SECT5_S  10U
#define DCSM_B0_SECTSTAT_STATUS_SECT5_M  0xC00U       // Zone Status flash BANK0
                                               // Sector 5
#define DCSM_B0_SECTSTAT_STATUS_SECT6_S  12U
#define DCSM_B0_SECTSTAT_STATUS_SECT6_M  0x3000U      // Zone Status flash BANK0
                                               // Sector 6
#define DCSM_B0_SECTSTAT_STATUS_SECT7_S  14U
#define DCSM_B0_SECTSTAT_STATUS_SECT7_M  0xC000U      // Zone Status flash BANK0
                                               // Sector 7
#define DCSM_B0_SECTSTAT_STATUS_SECT8_S  16U
#define DCSM_B0_SECTSTAT_STATUS_SECT8_M  0x30000U     // Zone Status flash BANK0
                                               // sector 8
#define DCSM_B0_SECTSTAT_STATUS_SECT9_S  18U
#define DCSM_B0_SECTSTAT_STATUS_SECT9_M  0xC0000U     // Zone Status flash BANK0
                                               // Sector 9
#define DCSM_B0_SECTSTAT_STATUS_SECT10_S  20U
#define DCSM_B0_SECTSTAT_STATUS_SECT10_M  0x300000U    // Zone Status flash BANK0
                                               // Sector 10
#define DCSM_B0_SECTSTAT_STATUS_SECT11_S  22U
#define DCSM_B0_SECTSTAT_STATUS_SECT11_M  0xC00000U    // Zone Status flash BANK0
                                               // Sector 11
#define DCSM_B0_SECTSTAT_STATUS_SECT12_S  24U
#define DCSM_B0_SECTSTAT_STATUS_SECT12_M  0x3000000U   // Zone Status flash BANK0
                                               // Sector 12
#define DCSM_B0_SECTSTAT_STATUS_SECT13_S  26U
#define DCSM_B0_SECTSTAT_STATUS_SECT13_M  0xC000000U   // Zone Status flash BANK0
                                               // Sector 13
#define DCSM_B0_SECTSTAT_STATUS_SECT14_S  28U
#define DCSM_B0_SECTSTAT_STATUS_SECT14_M  0x30000000U  // Zone Status flash BANK0
                                               // Sector 14
#define DCSM_B0_SECTSTAT_STATUS_SECT15_S  30U
#define DCSM_B0_SECTSTAT_STATUS_SECT15_M  0xC0000000U  // Zone Status flash BANK0
                                               // Sector 15

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMSTAT register
//
//*****************************************************************************
#define DCSM_RAMSTAT_STATUS_RAM0_S  0U
#define DCSM_RAMSTAT_STATUS_RAM0_M  0x3U         // Zone Status RAM LS0
#define DCSM_RAMSTAT_STATUS_RAM1_S  2U
#define DCSM_RAMSTAT_STATUS_RAM1_M  0xCU         // Zone Status RAM LS1
#define DCSM_RAMSTAT_STATUS_RAM2_S  4U
#define DCSM_RAMSTAT_STATUS_RAM2_M  0x30U        // Zone Status RAM LS2
#define DCSM_RAMSTAT_STATUS_RAM3_S  6U
#define DCSM_RAMSTAT_STATUS_RAM3_M  0xC0U        // Zone Status RAM LS3
#define DCSM_RAMSTAT_STATUS_RAM4_S  8U
#define DCSM_RAMSTAT_STATUS_RAM4_M  0x300U       // Zone Status RAM LS4
#define DCSM_RAMSTAT_STATUS_RAM5_S  10U
#define DCSM_RAMSTAT_STATUS_RAM5_M  0xC00U       // Zone Status RAM LS5
#define DCSM_RAMSTAT_STATUS_RAM6_S  12U
#define DCSM_RAMSTAT_STATUS_RAM6_M  0x3000U      // Zone Status RAM LS6
#define DCSM_RAMSTAT_STATUS_RAM7_S  14U
#define DCSM_RAMSTAT_STATUS_RAM7_M  0xC000U      // Zone Status RAM LS7

//*****************************************************************************
//
// The following are defines for the bit fields in the B1_SECTSTAT register
//
//*****************************************************************************
#define DCSM_B1_SECTSTAT_STATUS_SECT0_S  0U
#define DCSM_B1_SECTSTAT_STATUS_SECT0_M  0x3U         // Zone Status flash BANK1
                                               // Sector 0
#define DCSM_B1_SECTSTAT_STATUS_SECT1_S  2U
#define DCSM_B1_SECTSTAT_STATUS_SECT1_M  0xCU         // Zone Status flash BANK1
                                               // sector 1
#define DCSM_B1_SECTSTAT_STATUS_SECT2_S  4U
#define DCSM_B1_SECTSTAT_STATUS_SECT2_M  0x30U        // Zone Status flash BANK1
                                               // Sector 2
#define DCSM_B1_SECTSTAT_STATUS_SECT3_S  6U
#define DCSM_B1_SECTSTAT_STATUS_SECT3_M  0xC0U        // Zone Status flash BANK1
                                               // Sector 3
#define DCSM_B1_SECTSTAT_STATUS_SECT4_S  8U
#define DCSM_B1_SECTSTAT_STATUS_SECT4_M  0x300U       // Zone Status flash BANK1
                                               // Sector 4
#define DCSM_B1_SECTSTAT_STATUS_SECT5_S  10U
#define DCSM_B1_SECTSTAT_STATUS_SECT5_M  0xC00U       // Zone Status flash BANK1
                                               // Sector 5
#define DCSM_B1_SECTSTAT_STATUS_SECT6_S  12U
#define DCSM_B1_SECTSTAT_STATUS_SECT6_M  0x3000U      // Zone Status flash BANK1
                                               // Sector 6
#define DCSM_B1_SECTSTAT_STATUS_SECT7_S  14U
#define DCSM_B1_SECTSTAT_STATUS_SECT7_M  0xC000U      // Zone Status flash BANK1
                                               // Sector 7
#define DCSM_B1_SECTSTAT_STATUS_SECT8_S  16U
#define DCSM_B1_SECTSTAT_STATUS_SECT8_M  0x30000U     // Zone Status flash BANK1
                                               // sector 8
#define DCSM_B1_SECTSTAT_STATUS_SECT9_S  18U
#define DCSM_B1_SECTSTAT_STATUS_SECT9_M  0xC0000U     // Zone Status flash BANK1
                                               // Sector 9
#define DCSM_B1_SECTSTAT_STATUS_SECT10_S  20U
#define DCSM_B1_SECTSTAT_STATUS_SECT10_M  0x300000U    // Zone Status flash BANK1
                                               // Sector 10
#define DCSM_B1_SECTSTAT_STATUS_SECT11_S  22U
#define DCSM_B1_SECTSTAT_STATUS_SECT11_M  0xC00000U    // Zone Status flash BANK1
                                               // Sector 11
#define DCSM_B1_SECTSTAT_STATUS_SECT12_S  24U
#define DCSM_B1_SECTSTAT_STATUS_SECT12_M  0x3000000U   // Zone Status flash BANK1
                                               // Sector 12
#define DCSM_B1_SECTSTAT_STATUS_SECT13_S  26U
#define DCSM_B1_SECTSTAT_STATUS_SECT13_M  0xC000000U   // Zone Status flash BANK1
                                               // Sector 13
#define DCSM_B1_SECTSTAT_STATUS_SECT14_S  28U
#define DCSM_B1_SECTSTAT_STATUS_SECT14_M  0x30000000U  // Zone Status flash BANK1
                                               // Sector 14
#define DCSM_B1_SECTSTAT_STATUS_SECT15_S  30U
#define DCSM_B1_SECTSTAT_STATUS_SECT15_M  0xC0000000U  // Zone Status flash BANK1
                                               // Sector 15

//*****************************************************************************
//
// The following are defines for the bit fields in the SECERRSTAT register
//
//*****************************************************************************
#define DCSM_SECERRSTAT_ERR       0x1U         // Security Configuration load
                                               // Error Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SECERRCLR register
//
//*****************************************************************************
#define DCSM_SECERRCLR_ERR        0x1U         // Clear Security Configuration
                                               // Load Error Status Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the SECERRFRC register
//
//*****************************************************************************
#define DCSM_SECERRFRC_ERR        0x1U         // Set Security Configuration
                                               // Load Error Status Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMOPENSTAT register
//
//*****************************************************************************
#define DCSM_RAMOPENSTAT_RAMOPEN  0x1U         // RAM Security Open

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMOPENFRC register
//
//*****************************************************************************
#define DCSM_RAMOPENFRC_SET       0x1U         // Set RAM Open request
#define DCSM_RAMOPENFRC_KEY_S     16U
#define DCSM_RAMOPENFRC_KEY_M     0xFFFF0000U  // Valid Write KEY

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMOPENCLR register
//
//*****************************************************************************
#define DCSM_RAMOPENCLR_CLEAR     0x1U         // Clear RAM Open request
#define DCSM_RAMOPENCLR_KEY_S     16U
#define DCSM_RAMOPENCLR_KEY_M     0xFFFF0000U  // Valid Write KEY

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMOPENLOCK register
//
//*****************************************************************************
#define DCSM_RAMOPENLOCK_LOCK     0x1U         // RAMOPEN Lock

//*****************************************************************************
//
// The following are defines for the bit fields in the B1_Z1_LINKPOINTER register
//
//*****************************************************************************
#define DCSM_B1_Z1_LINKPOINTER_LINKPOINTER_S  0U
#define DCSM_B1_Z1_LINKPOINTER_LINKPOINTER_M  0x1FFFFFFFU  // Zone1 LINK Pointer in flash
                                               // BANK1

//*****************************************************************************
//
// The following are defines for the bit fields in the B1_Z1_LINKPOINTERERR register
//
//*****************************************************************************
#define DCSM_B1_Z1_LINKPOINTERERR_Z1_LINKPOINTERERR_S  0U
#define DCSM_B1_Z1_LINKPOINTERERR_Z1_LINKPOINTERERR_M  0x1FFFFFFFU  // Error to Resolve Z1 Link
                                               // pointer from OTP loaded values

//*****************************************************************************
//
// The following are defines for the bit fields in the B1_Z1_GRABSECTR register
//
//*****************************************************************************
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT0_S  0U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT0_M  0x3U         // Grab Flash Sector 0 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT1_S  2U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT1_M  0xCU         // Grab Flash Sector 1 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT2_S  4U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT2_M  0x30U        // Grab Flash Sector 2 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT3_S  6U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT3_M  0xC0U        // Grab Flash Sector 3 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT4_S  8U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT4_M  0x300U       // Grab Flash Sector 4 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT5_S  10U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT5_M  0xC00U       // Grab Flash Sector 5 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT6_S  12U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT6_M  0x3000U      // Grab Flash Sector 6 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT7_S  14U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT7_M  0xC000U      // Grab Flash Sector 7 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT8_S  16U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT8_M  0x30000U     // Grab Flash Sector 8 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT9_S  18U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT9_M  0xC0000U     // Grab Flash Sector 9 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT10_S  20U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT10_M  0x300000U    // Grab Flash Sector 10 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT11_S  22U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT11_M  0xC00000U    // Grab Flash Sector 11 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT12_S  24U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT12_M  0x3000000U   // Grab Flash Sector 12 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT13_S  26U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT13_M  0xC000000U   // Grab Flash Sector 13 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT14_S  28U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT14_M  0x30000000U  // Grab Flash Sector 14 in BANK1
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT15_S  30U
#define DCSM_B1_Z1_GRABSECTR_GRAB_SECT15_M  0xC0000000U  // Grab Flash Sector 15 in BANK1

//*****************************************************************************
//
// The following are defines for the bit fields in the B1_Z1_EXEONLYSECTR register
//
//*****************************************************************************
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT0  0x1U         // Execute-Only Flash Sector 0
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT1  0x2U         // Execute-Only Flash Sector 1
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT2  0x4U         // Execute-Only Flash Sector 2
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT3  0x8U         // Execute-Only Flash Sector 3
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT4  0x10U        // Execute-Only Flash Sector 4
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT5  0x20U        // Execute-Only Flash Sector 5
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT6  0x40U        // Execute-Only Flash Sector 6
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT7  0x80U        // Execute-Only Flash Sector 7
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT8  0x100U       // Execute-Only Flash Sector 8
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT9  0x200U       // Execute-Only Flash Sector 9
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT10  0x400U       // Execute-Only Flash Sector 10
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT11  0x800U       // Execute-Only Flash Sector 11
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT12  0x1000U      // Execute-Only Flash Sector 12
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT13  0x2000U      // Execute-Only Flash Sector 13
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT14  0x4000U      // Execute-Only Flash Sector 14
                                               // in flash BANK1
#define DCSM_B1_Z1_EXEONLYSECTR_EXEONLY_SECT15  0x8000U      // Execute-Only Flash Sector 15
                                               // in flash BANK1

//*****************************************************************************
//
// The following are defines for the bit fields in the B1_Z2_LINKPOINTER register
//
//*****************************************************************************
#define DCSM_B1_Z2_LINKPOINTER_LINKPOINTER_S  0U
#define DCSM_B1_Z2_LINKPOINTER_LINKPOINTER_M  0x1FFFFFFFU  // Zone2 LINK Pointer in flash
                                               // BANK1

//*****************************************************************************
//
// The following are defines for the bit fields in the B1_Z2_LINKPOINTERERR register
//
//*****************************************************************************
#define DCSM_B1_Z2_LINKPOINTERERR_Z2_LINKPOINTERERR_S  0U
#define DCSM_B1_Z2_LINKPOINTERERR_Z2_LINKPOINTERERR_M  0x1FFFFFFFU  // Error to Resolve Z2 Link
                                               // pointer from OTP loaded values

//*****************************************************************************
//
// The following are defines for the bit fields in the B1_Z2_GRABSECTR register
//
//*****************************************************************************
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT0_S  0U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT0_M  0x3U         // Grab Flash Sector 0 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT1_S  2U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT1_M  0xCU         // Grab Flash Sector 1 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT2_S  4U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT2_M  0x30U        // Grab Flash Sector 2 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT3_S  6U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT3_M  0xC0U        // Grab Flash Sector 3 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT4_S  8U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT4_M  0x300U       // Grab Flash Sector 4 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT5_S  10U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT5_M  0xC00U       // Grab Flash Sector 5 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT6_S  12U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT6_M  0x3000U      // Grab Flash Sector 6 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT7_S  14U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT7_M  0xC000U      // Grab Flash Sector 7 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT8_S  16U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT8_M  0x30000U     // Grab Flash Sector 8 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT9_S  18U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT9_M  0xC0000U     // Grab Flash Sector 9 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT10_S  20U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT10_M  0x300000U    // Grab Flash Sector 10 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT11_S  22U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT11_M  0xC00000U    // Grab Flash Sector 11 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT12_S  24U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT12_M  0x3000000U   // Grab Flash Sector 12 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT13_S  26U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT13_M  0xC000000U   // Grab Flash Sector 13 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT14_S  28U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT14_M  0x30000000U  // Grab Flash Sector 14 in flash
                                               // BANK1
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT15_S  30U
#define DCSM_B1_Z2_GRABSECTR_GRAB_SECT15_M  0xC0000000U  // Grab Flash Sector 15 in flash
                                               // BANK1

//*****************************************************************************
//
// The following are defines for the bit fields in the B1_Z2_EXEONLYSECTR register
//
//*****************************************************************************
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT0  0x1U         // Execute-Only Flash Sector 0
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT1  0x2U         // Execute-Only Flash Sector 1
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT2  0x4U         // Execute-Only Flash Sector 2
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT3  0x8U         // Execute-Only Flash Sector 3
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT4  0x10U        // Execute-Only Flash Sector 4
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT5  0x20U        // Execute-Only Flash Sector 5
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT6  0x40U        // Execute-Only Flash Sector 6
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT7  0x80U        // Execute-Only Flash Sector 7
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT8  0x100U       // Execute-Only Flash Sector 8
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT9  0x200U       // Execute-Only Flash Sector 9
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT10  0x400U       // Execute-Only Flash Sector 10
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT11  0x800U       // Execute-Only Flash Sector 11
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT12  0x1000U      // Execute-Only Flash Sector 12
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT13  0x2000U      // Execute-Only Flash Sector 13
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT14  0x4000U      // Execute-Only Flash Sector 14
                                               // in flash BANK1
#define DCSM_B1_Z2_EXEONLYSECTR_EXEONLY_SECT15  0x8000U      // Execute-Only Flash Sector 15
                                               // in flash BANK1
#endif
