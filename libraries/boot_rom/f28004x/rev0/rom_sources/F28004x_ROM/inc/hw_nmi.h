//###########################################################################
//
// FILE:    hw_nmi.h
//
// TITLE:   Definitions for the NMI registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef __HW_NMI_H__
#define __HW_NMI_H__

//*****************************************************************************
//
// The following are defines for the NMIINTRUPT register offsets
//
//*****************************************************************************
#define NMI_O_CFG                 0x0U        // NMI Configuration Register
#define NMI_O_FLG                 0x1U        // NMI Flag Register (SYSRsn
                                              // Clear)
#define NMI_O_FLGCLR              0x2U        // NMI Flag Clear Register
#define NMI_O_FLGFRC              0x3U        // NMI Flag Force Register
#define NMI_O_WDCNT               0x4U        // NMI Watchdog Counter Register
#define NMI_O_WDPRD               0x5U        // NMI Watchdog Period Register
#define NMI_O_SHDFLG              0x6U        // NMI Shadow Flag Register

//*****************************************************************************
//
// The following are defines for the bit fields in the NMICFG register
//
//*****************************************************************************
#define NMI_CFG_NMIE              0x1U        // Global NMI Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NMIFLG register
//
//*****************************************************************************
#define NMI_FLG_NMIINT            0x1U        // NMI Interrupt Flag
#define NMI_FLG_CLOCKFAIL         0x2U        // Clock Fail Interrupt Flag
#define NMI_FLG_RAMUNCERR         0x4U        // RAM Uncorrectable Error NMI
                                              // Flag
#define NMI_FLG_FLUNCERR          0x8U        // Flash Uncorrectable Error NMI
                                              // Flag
#define NMI_FLG_RLNMI             0x100U      // Reconfigurable Logic NMI Flag
#define NMI_FLG_SWERR             0x2000U     // SW Error Force NMI Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the NMIFLGCLR register
//
//*****************************************************************************
#define NMI_FLGCLR_NMIINT         0x1U        // NMIINT Flag Clear
#define NMI_FLGCLR_CLOCKFAIL      0x2U        // CLOCKFAIL Flag Clear
#define NMI_FLGCLR_RAMUNCERR      0x4U        // RAMUNCERR Flag Clear
#define NMI_FLGCLR_FLUNCERR       0x8U        // FLUNCERR Flag Clear
#define NMI_FLGCLR_RLNMI          0x100U      // RLNMI Flag Clear
#define NMI_FLGCLR_SWERR          0x2000U     // SW Error Force NMI Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the NMIFLGFRC register
//
//*****************************************************************************
#define NMI_FLGFRC_CLOCKFAIL      0x2U        // CLOCKFAIL Flag Force
#define NMI_FLGFRC_RAMUNCERR      0x4U        // RAMUNCERR Flag Force
#define NMI_FLGFRC_FLUNCERR       0x8U        // FLUNCERR Flag Force
#define NMI_FLGFRC_RLNMI          0x100U      // RLNMI Flag Force
#define NMI_FLGFRC_SWERR          0x2000U     // SW Error Force NMI Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the NMISHDFLG register
//
//*****************************************************************************
#define NMI_SHDFLG_CLOCKFAIL      0x2U        // Shadow CLOCKFAIL Flag
#define NMI_SHDFLG_RAMUNCERR      0x4U        // Shadow RAMUNCERR Flag
#define NMI_SHDFLG_FLUNCERR       0x8U        // Shadow FLUNCERR Flag
#define NMI_SHDFLG_RLNMI          0x100U      // Shadow RLNMI Flag
#define NMI_SHDFLG_SWERR          0x2000U     // SW Error Force NMI Flag
#endif
