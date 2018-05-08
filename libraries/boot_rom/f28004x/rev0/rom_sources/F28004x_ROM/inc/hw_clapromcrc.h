//###########################################################################
//
// FILE:    hw_clapromcrc.h
//
// TITLE:   Definitions for the CLAPROMCRC registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __HW_CLAPROMCRC_H__
#define __HW_CLAPROMCRC_H__

//*****************************************************************************
//
// The following are defines for the CLAPROMCRC register offsets
//
//*****************************************************************************
#define CLAPROMCRC_O_CRC32_CONTROLREG  0x0U         // CRC32-Control Register
#define CLAPROMCRC_O_CRC32_STARTADDRESS  0x2U         // CRC32-Start address register
#define CLAPROMCRC_O_CRC32_SEED   0x4U         // CRC32-Seed Register
#define CLAPROMCRC_O_CRC32_STATUSREG  0x6U         // CRC32-Status Register
#define CLAPROMCRC_O_CRC32_CRCRESULT  0x8U         // CRC32-CRC result Register
#define CLAPROMCRC_O_CRC32_GOLDENCRC  0xAU         // CRC32-Golden CRC register
#define CLAPROMCRC_O_CRC32_INTEN  0x18U        // CRC32-Interrupt enable
                                               // register
#define CLAPROMCRC_O_CRC32_FLG    0x1AU        // CRC32-Interrupt Flag Register
#define CLAPROMCRC_O_CRC32_CLR    0x1CU        // CRC32-Interrupt Clear
                                               // Register
#define CLAPROMCRC_O_CRC32_FRC    0x1EU        // CRC32-Interrupt Force
                                               // Register

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC32_CONTROLREG register
//
//*****************************************************************************
#define CLAPROMCRC_CRC32_CONTROLREG_START  0x1U         // Start Bit
#define CLAPROMCRC_CRC32_CONTROLREG_FREE_SOFT  0x10U        // emulation control bit
#define CLAPROMCRC_CRC32_CONTROLREG_HALT  0x100U       // Halt Bit
#define CLAPROMCRC_CRC32_CONTROLREG_BLOCKSIZE_S  16U
#define CLAPROMCRC_CRC32_CONTROLREG_BLOCKSIZE_M  0x7F0000U    // Block size of ROM for which
                                               // CRC is to be calculated

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC32_STATUSREG register
//
//*****************************************************************************
#define CLAPROMCRC_CRC32_STATUSREG_CURRENTADDR_S  0U
#define CLAPROMCRC_CRC32_STATUSREG_CURRENTADDR_M  0xFFFFU      // Point to the data fetch unit
                                               // current address
#define CLAPROMCRC_CRC32_STATUSREG_CRCCHECKSTATUS  0x800000U    // CRC active status
#define CLAPROMCRC_CRC32_STATUSREG_RUNSTATUS  0x80000000U  // CRC active status

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC32_INTEN register
//
//*****************************************************************************
#define CLAPROMCRC_CRC32_INTEN_CRCDONE  0x2U         // CRCDONE interrupt enable
                                               // register

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC32_FLG register
//
//*****************************************************************************
#define CLAPROMCRC_CRC32_FLG_INT  0x1U         // Global Interrupt status flag
#define CLAPROMCRC_CRC32_FLG_CRCDONE  0x2U         // CRCDONE Interrupt status flag

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC32_CLR register
//
//*****************************************************************************
#define CLAPROMCRC_CRC32_CLR_INT  0x1U         // Global Interrupt clear
#define CLAPROMCRC_CRC32_CLR_CRCDONE  0x2U         // CRCDONE Interrupt clear

//*****************************************************************************
//
// The following are defines for the bit fields in the CRC32_FRC register
//
//*****************************************************************************
#define CLAPROMCRC_CRC32_FRC_CRCDONE  0x2U         // CRCDONE Interrupt force
#endif
