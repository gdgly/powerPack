//###########################################################################
//
// FILE:    hw_ecap_t1.h
//
// TITLE:   Definitions for the ECAP registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef __HW_ECAP_T1_H__
#define __HW_ECAP_T1_H__

//*****************************************************************************
//
// The following are defines for the EHRCAP register offsets
//
//*****************************************************************************
#define ECAP_O_TSCTR              0x0U        // Time-Stamp Counter
#define ECAP_O_CTRPHS             0x2U        // Counter Phase Offset Value
                                              // Register
#define ECAP_O_CAP1               0x4U        // Capture 1 Register
#define ECAP_O_CAP2               0x6U        // Capture 2 Register
#define ECAP_O_CAP3               0x8U        // Capture 3 Register
#define ECAP_O_CAP4               0xAU        // Capture 4 Register
#define ECAP_O_ECCTL0             0x12U       // Capture Control Register 0
#define ECAP_O_ECCTL1             0x14U       // Capture Control Register 1
#define ECAP_O_ECCTL2             0x15U       // Capture Control Register 2
#define ECAP_O_ECEINT             0x16U       // Capture Interrupt Enable
                                              // Register
#define ECAP_O_ECFLG              0x17U       // Capture Interrupt Flag
                                              // Register
#define ECAP_O_ECCLR              0x18U       // Capture Interrupt Clear
                                              // Register
#define ECAP_O_ECFRC              0x19U       // Capture Interrupt Force
                                              // Register
#define ECAP_O_HRCTL              0x20U       // High-Res Control Register
#define ECAP_O_HRINTEN            0x24U       // High-Res Calibration
                                              // Interrupt Enable Register
#define ECAP_O_HRFLG              0x26U       // High-Res Calibration
                                              // Interrupt Flag Register
#define ECAP_O_HRCLR              0x28U       // High-Res Calibration
                                              // Interrupt Clear Register
#define ECAP_O_HRFRC              0x2AU       // High-Res Calibration
                                              // Interrupt Force Register
#define ECAP_O_HRCALPRD           0x2CU       // High-Res Calibration Period
                                              // Register
#define ECAP_O_HRSYSCLKCTR        0x2EU       // High-Res Calibration SYSCLK
                                              // Counter Register
#define ECAP_O_HRSYSCLKCAP        0x30U       // High-Res Calibration SYSCLK
                                              // Capture Register
#define ECAP_O_HRCLKCTR           0x32U       // High-Res Calibration HRCLK
                                              // Counter Register
#define ECAP_O_HRCLKCAP           0x34U       // High-Res Calibration HRCLK
                                              // Capture Register

//*****************************************************************************
//
// The following are defines for the bit fields in the ECCTL0 register
//
//*****************************************************************************
#define ECAP_ECCTL0_INPUTSEL_S    0U
#define ECAP_ECCTL0_INPUTSEL_M    0x7FU       // INPUT source select

//*****************************************************************************
//
// The following are defines for the bit fields in the ECCTL1 register
//
//*****************************************************************************
#define ECAP_ECCTL1_CAP1POL       0x1U        // Capture Event 1 Polarity
                                              // select
#define ECAP_ECCTL1_CTRRST1       0x2U        // Counter Reset on Capture
                                              // Event 1
#define ECAP_ECCTL1_CAP2POL       0x4U        // Capture Event 2 Polarity
                                              // select
#define ECAP_ECCTL1_CTRRST2       0x8U        // Counter Reset on Capture
                                              // Event 2
#define ECAP_ECCTL1_CAP3POL       0x10U       // Capture Event 3 Polarity
                                              // select
#define ECAP_ECCTL1_CTRRST3       0x20U       // Counter Reset on Capture
                                              // Event 3
#define ECAP_ECCTL1_CAP4POL       0x40U       // Capture Event 4 Polarity
                                              // select
#define ECAP_ECCTL1_CTRRST4       0x80U       // Counter Reset on Capture
                                              // Event 4
#define ECAP_ECCTL1_CAPLDEN       0x100U      // Enable Loading CAP1-4 regs on
                                              // a Cap Event
#define ECAP_ECCTL1_PRESCALE_S    9U
#define ECAP_ECCTL1_PRESCALE_M    0x3E00U     // Event Filter prescale select
#define ECAP_ECCTL1_FREE_SOFT_S   14U
#define ECAP_ECCTL1_FREE_SOFT_M   0xC000U     // Emulation mode

//*****************************************************************************
//
// The following are defines for the bit fields in the ECCTL2 register
//
//*****************************************************************************
#define ECAP_ECCTL2_CONT_ONESHT   0x1U        // Continuous or one-shot
#define ECAP_ECCTL2_STOP_WRAP_S   1U
#define ECAP_ECCTL2_STOP_WRAP_M   0x6U        // Stop value for one-shot, Wrap
                                              // for continuous
#define ECAP_ECCTL2_REARM         0x8U        // One-shot re-arm
#define ECAP_ECCTL2_TSCTRSTOP     0x10U       // TSCNT counter stop
#define ECAP_ECCTL2_SYNCI_EN      0x20U       // Counter sync-in select
#define ECAP_ECCTL2_SYNCO_SEL_S   6U
#define ECAP_ECCTL2_SYNCO_SEL_M   0xC0U       // Sync-out mode
#define ECAP_ECCTL2_SWSYNC        0x100U      // SW forced counter sync
#define ECAP_ECCTL2_CAP_APWM      0x200U      // CAP/APWM operating mode
                                              // select
#define ECAP_ECCTL2_APWMPOL       0x400U      // APWM output polarity select
#define ECAP_ECCTL2_CTRFILTRESET  0x800U      // Reset event filter, counter.
                                              // Module copunter and flags
#define ECAP_ECCTL2_DMAEVTSEL_S   12U
#define ECAP_ECCTL2_DMAEVTSEL_M   0x3000U     // DMA event select
#define ECAP_ECCTL2_MODCNTRSTS_S  14U
#define ECAP_ECCTL2_MODCNTRSTS_M  0xC000U     // modulo counter status

//*****************************************************************************
//
// The following are defines for the bit fields in the ECEINT register
//
//*****************************************************************************
#define ECAP_ECEINT_CEVT1         0x2U        // Capture Event 1 Interrupt
                                              // Enable
#define ECAP_ECEINT_CEVT2         0x4U        // Capture Event 2 Interrupt
                                              // Enable
#define ECAP_ECEINT_CEVT3         0x8U        // Capture Event 3 Interrupt
                                              // Enable
#define ECAP_ECEINT_CEVT4         0x10U       // Capture Event 4 Interrupt
                                              // Enable
#define ECAP_ECEINT_CTROVF        0x20U       // Counter Overflow Interrupt
                                              // Enable
#define ECAP_ECEINT_CTR_EQ_PRD    0x40U       // Period Equal Interrupt Enable
#define ECAP_ECEINT_CTR_EQ_CMP    0x80U       // Compare Equal Interrupt
                                              // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ECFLG register
//
//*****************************************************************************
#define ECAP_ECFLG_INT            0x1U        // Global Flag
#define ECAP_ECFLG_CEVT1          0x2U        // Capture Event 1 Interrupt
                                              // Flag
#define ECAP_ECFLG_CEVT2          0x4U        // Capture Event 2 Interrupt
                                              // Flag
#define ECAP_ECFLG_CEVT3          0x8U        // Capture Event 3 Interrupt
                                              // Flag
#define ECAP_ECFLG_CEVT4          0x10U       // Capture Event 4 Interrupt
                                              // Flag
#define ECAP_ECFLG_CTROVF         0x20U       // Counter Overflow Interrupt
                                              // Flag
#define ECAP_ECFLG_CTR_PRD        0x40U       // Period Equal Interrupt Flag
#define ECAP_ECFLG_CTR_CMP        0x80U       // Compare Equal Interrupt Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the ECCLR register
//
//*****************************************************************************
#define ECAP_ECCLR_INT            0x1U        // Global Flag
#define ECAP_ECCLR_CEVT1          0x2U        // Capture Event 1 Interrupt
                                              // Flag
#define ECAP_ECCLR_CEVT2          0x4U        // Capture Event 2 Interrupt
                                              // Flag
#define ECAP_ECCLR_CEVT3          0x8U        // Capture Event 3 Interrupt
                                              // Flag
#define ECAP_ECCLR_CEVT4          0x10U       // Capture Event 4 Interrupt
                                              // Flag
#define ECAP_ECCLR_CTROVF         0x20U       // Counter Overflow Interrupt
                                              // Flag
#define ECAP_ECCLR_CTR_PRD        0x40U       // Period Equal Interrupt Flag
#define ECAP_ECCLR_CTR_CMP        0x80U       // Compare Equal Interrupt Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the ECFRC register
//
//*****************************************************************************
#define ECAP_ECFRC_CEVT1          0x2U        // Capture Event 1 Interrupt
                                              // Flag
#define ECAP_ECFRC_CEVT2          0x4U        // Capture Event 2 Interrupt
                                              // Flag
#define ECAP_ECFRC_CEVT3          0x8U        // Capture Event 3 Interrupt
                                              // Flag
#define ECAP_ECFRC_CEVT4          0x10U       // Capture Event 4 Interrupt
                                              // Flag
#define ECAP_ECFRC_CTROVF         0x20U       // Counter Overflow Interrupt
                                              // Flag
#define ECAP_ECFRC_CTR_PRD        0x40U       // Period Equal Interrupt Flag
#define ECAP_ECFRC_CTR_CMP        0x80U       // Compare Equal Interrupt Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the HRCTL register
//
//*****************************************************************************

//*****************************************************************************
//
// The following are defines for the bit fields in the HRINTEN register
//
//*****************************************************************************

//*****************************************************************************
//
// The following are defines for the bit fields in the HRFLG register
//
//*****************************************************************************

//*****************************************************************************
//
// The following are defines for the bit fields in the HRCLR register
//
//*****************************************************************************

//*****************************************************************************
//
// The following are defines for the bit fields in the HRFRC register
//
//*****************************************************************************
#endif
