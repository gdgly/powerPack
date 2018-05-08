//###########################################################################
//
// FILE:    hw_sdfm.h
//
// TITLE:   Definitions for the SDFM registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __HW_SDFM_H__
#define __HW_SDFM_H__

//*****************************************************************************
//
// The following are defines for the SDFM register offsets
//
//*****************************************************************************
#define SDFM_O_SDIFLG             0x0U         // Interrupt Flag Register
#define SDFM_O_SDIFLGCLR          0x2U         // Interrupt Flag Clear Register
#define SDFM_O_SDCTL              0x4U         // SD Control Register
#define SDFM_O_SDMFILEN           0x6U         // SD Master Filter Enable
#define SDFM_O_SDSTATUS           0x7U         // SD Status Register
#define SDFM_O_SDCTLPARM1         0x10U        // Control Parameter Register
                                               // for Ch1
#define SDFM_O_SDDFPARM1          0x11U        // Sinc Filter Parameter
                                               // Register for Ch1
#define SDFM_O_SDDPARM1           0x12U        // Primary Filter Data Control
                                               // for Ch1
#define SDFM_O_SDCMPH1            0x13U        // High-level Threshold Register
                                               // for Ch1
#define SDFM_O_SDCMPL1            0x14U        // Low-level Threshold Register
                                               // for Ch1
#define SDFM_O_SDCPARM1           0x15U        // Comparator Parameter Register
                                               // for Ch1
#define SDFM_O_SDDATA1            0x16U        // Filter Data Register (16 or
                                               // 32bit) for Ch1
#define SDFM_O_SDDATFIFO1         0x18U        // Filter Data FIFO Output(32b)
                                               // for Ch1
#define SDFM_O_SDCDATA1           0x1AU        // Comparator Data Register
                                               // (16b) for Ch1
#define SDFM_O_SDCMPZ1            0x1CU        // Zero-Cross Threshold Register
                                               // for Ch1
#define SDFM_O_SDFIFOCTL1         0x1DU        // FIFO Control Register for Ch1
#define SDFM_O_SDSYNC1            0x1EU        // SD Filter Sync control for
                                               // Ch1
#define SDFM_O_SDCTLPARM2         0x20U        // Control Parameter Register
                                               // for Ch2
#define SDFM_O_SDDFPARM2          0x21U        // Sinc Filter Parameter
                                               // Register for Ch2
#define SDFM_O_SDDPARM2           0x22U        // Primary Filter Data Control
                                               // for Ch2
#define SDFM_O_SDCMPH2            0x23U        // High-level Threshold Register
                                               // for Ch2
#define SDFM_O_SDCMPL2            0x24U        // Low-level Threshold Register
                                               // for Ch2
#define SDFM_O_SDCPARM2           0x25U        // Comparator Parameter Register
                                               // for Ch2
#define SDFM_O_SDDATA2            0x26U        // Filter Data Register (16 or
                                               // 32bit) for Ch2
#define SDFM_O_SDDATFIFO2         0x28U        // Filter Data FIFO Output(32b)
                                               // for Ch2
#define SDFM_O_SDCDATA2           0x2AU        // Comparator Data Register
                                               // (16b) for Ch2
#define SDFM_O_SDCMPZ2            0x2CU        // Zero-Cross Threshold Register
                                               // for Ch2
#define SDFM_O_SDFIFOCTL2         0x2DU        // FIFO Control Register for Ch2
#define SDFM_O_SDSYNC2            0x2EU        // SD Filter Sync control for
                                               // Ch2
#define SDFM_O_SDCTLPARM3         0x30U        // Control Parameter Register
                                               // for Ch3
#define SDFM_O_SDDFPARM3          0x31U        // Sinc Filter Parameter
                                               // Register for Ch3
#define SDFM_O_SDDPARM3           0x32U        // Primary Filter Data Control
                                               // for Ch3
#define SDFM_O_SDCMPH3            0x33U        // High-level Threshold Register
                                               // for Ch3
#define SDFM_O_SDCMPL3            0x34U        // Low-level Threshold Register
                                               // for Ch3
#define SDFM_O_SDCPARM3           0x35U        // Comparator Parameter Register
                                               // for Ch3
#define SDFM_O_SDDATA3            0x36U        // Filter Data Register (16 or
                                               // 32bit) for Ch3
#define SDFM_O_SDDATFIFO3         0x38U        // Filter Data FIFO Output(32b)
                                               // for Ch3
#define SDFM_O_SDCDATA3           0x3AU        // Comparator Data Register
                                               // (16b) for Ch3
#define SDFM_O_SDCMPZ3            0x3CU        // Zero-Cross Threshold Register
                                               // for Ch3
#define SDFM_O_SDFIFOCTL3         0x3DU        // FIFO Control Register for Ch3
#define SDFM_O_SDSYNC3            0x3EU        // SD Filter Sync control for
                                               // Ch3
#define SDFM_O_SDCTLPARM4         0x40U        // Control Parameter Register
                                               // for Ch4
#define SDFM_O_SDDFPARM4          0x41U        // Sinc Filter Parameter
                                               // Register for Ch4
#define SDFM_O_SDDPARM4           0x42U        // Primary Filter Data Control
                                               // for Ch4
#define SDFM_O_SDCMPH4            0x43U        // High-level Threshold Register
                                               // for Ch4
#define SDFM_O_SDCMPL4            0x44U        // Low-level Threshold Register
                                               // for Ch4
#define SDFM_O_SDCPARM4           0x45U        // Comparator Parameter Register
                                               // for Ch4
#define SDFM_O_SDDATA4            0x46U        // Filter Data Register (16 or
                                               // 32bit) for Ch4
#define SDFM_O_SDDATFIFO4         0x48U        // Filter Data FIFO Output(32b)
                                               // for Ch4
#define SDFM_O_SDCDATA4           0x4AU        // Comparator Data Register
                                               // (16b) for Ch4
#define SDFM_O_SDCMPZ4            0x4CU        // Zero-Cross Threshold Register
                                               // for Ch4
#define SDFM_O_SDFIFOCTL4         0x4DU        // FIFO Control Register for Ch4
#define SDFM_O_SDSYNC4            0x4EU        // SD Filter Sync control for
                                               // Ch4

//*****************************************************************************
//
// The following are defines for the bit fields in the SDIFLG register
//
//*****************************************************************************
#define SDFM_SDIFLG_IFH1          0x1U         // High-level Interrupt flag
                                               // Filter 1
#define SDFM_SDIFLG_IFL1          0x2U         // Low-Level Interrupt flag
                                               // Filter 1
#define SDFM_SDIFLG_IFH2          0x4U         // High-level Interrupt flag
                                               // Filter 2
#define SDFM_SDIFLG_IFL2          0x8U         // Low-Level Interrupt flag
                                               // Filter 2
#define SDFM_SDIFLG_IFH3          0x10U        // High-level Interrupt flag
                                               // Filter 3
#define SDFM_SDIFLG_IFL3          0x20U        // Low-Level Interrupt flag
                                               // Filter 3
#define SDFM_SDIFLG_IFH4          0x40U        // High-level Interrupt flag
                                               // Filter 4
#define SDFM_SDIFLG_IFL4          0x80U        // Low-Level Interrupt flag
                                               // Filter 4
#define SDFM_SDIFLG_MF1           0x100U       // Modulator Failure for Filter
                                               // 1
#define SDFM_SDIFLG_MF2           0x200U       // Modulator Failure for Filter
                                               // 2
#define SDFM_SDIFLG_MF3           0x400U       // Modulator Failure for Filter
                                               // 3
#define SDFM_SDIFLG_MF4           0x800U       // Modulator Failure for Filter
                                               // 4
#define SDFM_SDIFLG_AF1           0x1000U      // Acknowledge flag for Filter 1
#define SDFM_SDIFLG_AF2           0x2000U      // Acknowledge flag for Filter 2
#define SDFM_SDIFLG_AF3           0x4000U      // Acknowledge flag for Filter 3
#define SDFM_SDIFLG_AF4           0x8000U      // Acknowledge flag for Filter 4
#define SDFM_SDIFLG_SDFFOVF1      0x10000U     // FIFO Overflow Flag for Ch 1.
#define SDFM_SDIFLG_SDFFOVF2      0x20000U     // FIFO Overflow Flag for Ch 2
#define SDFM_SDIFLG_SDFFOVF3      0x40000U     // FIFO Overflow Flag for Ch 3
#define SDFM_SDIFLG_SDFFOVF4      0x80000U     // FIFO Overflow Flag for Ch 4
#define SDFM_SDIFLG_FFINT1        0x100000U    // SD FIFO interrupt for Ch 1
#define SDFM_SDIFLG_FFINT2        0x200000U    // SD FIFO interrupt for Ch 2
#define SDFM_SDIFLG_FFINT3        0x400000U    // SD FIFO interrupt for Ch 3
#define SDFM_SDIFLG_FFINT4        0x800000U    // SD FIFO interrupt for Ch 4
#define SDFM_SDIFLG_MIF           0x80000000U  // Master Interrupt Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the SDIFLGCLR register
//
//*****************************************************************************
#define SDFM_SDIFLGCLR_IFH1       0x1U         // High-level Interrupt flag
                                               // Filter 1
#define SDFM_SDIFLGCLR_IFL1       0x2U         // Low-Level Interrupt flag
                                               // Filter 1
#define SDFM_SDIFLGCLR_IFH2       0x4U         // High-level Interrupt flag
                                               // Filter 2
#define SDFM_SDIFLGCLR_IFL2       0x8U         // Low-Level Interrupt flag
                                               // Filter 2
#define SDFM_SDIFLGCLR_IFH3       0x10U        // High-level Interrupt flag
                                               // Filter 3
#define SDFM_SDIFLGCLR_IFL3       0x20U        // Low-Level Interrupt flag
                                               // Filter 3
#define SDFM_SDIFLGCLR_IFH4       0x40U        // High-level Interrupt flag
                                               // Filter 4
#define SDFM_SDIFLGCLR_IFL4       0x80U        // Low-Level Interrupt flag
                                               // Filter 4
#define SDFM_SDIFLGCLR_MF1        0x100U       // Modulator Failure for Filter
                                               // 1
#define SDFM_SDIFLGCLR_MF2        0x200U       // Modulator Failure for Filter
                                               // 2
#define SDFM_SDIFLGCLR_MF3        0x400U       // Modulator Failure for Filter
                                               // 3
#define SDFM_SDIFLGCLR_MF4        0x800U       // Modulator Failure for Filter
                                               // 4
#define SDFM_SDIFLGCLR_AF1        0x1000U      // Acknowledge flag for Filter 1
#define SDFM_SDIFLGCLR_AF2        0x2000U      // Acknowledge flag for Filter 2
#define SDFM_SDIFLGCLR_AF3        0x4000U      // Acknowledge flag for Filter 3
#define SDFM_SDIFLGCLR_AF4        0x8000U      // Acknowledge flag for Filter 4
#define SDFM_SDIFLGCLR_SDFFOVF1   0x10000U     // SD FIFO overflow clear Ch 1
#define SDFM_SDIFLGCLR_SDFFOVF2   0x20000U     // SD FIFO overflow clear Ch 2
#define SDFM_SDIFLGCLR_SDFFOVF3   0x40000U     // SD FIFO overflow clear Ch 3
#define SDFM_SDIFLGCLR_SDFFOVF4   0x80000U     // SD FIFO overflow clear Ch 4
#define SDFM_SDIFLGCLR_SDFFINT1   0x100000U    // SDFIFO Interrupt flag-clear
                                               // bit for Ch 1
#define SDFM_SDIFLGCLR_SDFFINT2   0x200000U    // SDFIFO Interrupt flag-clear
                                               // bit for Ch 2
#define SDFM_SDIFLGCLR_SDFFINT3   0x400000U    // SDFIFO Interrupt flag-clear
                                               // bit for Ch 3
#define SDFM_SDIFLGCLR_SDFFINT4   0x800000U    // SDFIFO Interrupt flag-clear
                                               // bit for Ch 4
#define SDFM_SDIFLGCLR_MIF        0x80000000U  // Master Interrupt Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCTL register
//
//*****************************************************************************
#define SDFM_SDCTL_ZC1            0x1U         // Zero Cross Trip status Clear
                                               // for Ch1
#define SDFM_SDCTL_ZC2            0x2U         // Zero Cross Trip status Clear
                                               // for Ch2
#define SDFM_SDCTL_ZC3            0x4U         // Zero Cross Trip status Clear
                                               // for Ch3
#define SDFM_SDCTL_ZC4            0x8U         // Zero Cross Trip status Clear
                                               // for Ch4
#define SDFM_SDCTL_MIE            0x2000U      // Master SDINT Interrupt enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDMFILEN register
//
//*****************************************************************************
#define SDFM_SDMFILEN_MFE         0x800U       // Master Filter Enable.

//*****************************************************************************
//
// The following are defines for the bit fields in the SDSTATUS register
//
//*****************************************************************************
#define SDFM_SDSTATUS_ZC1         0x1U         // Zero Cross Trip status for
                                               // Ch1
#define SDFM_SDSTATUS_ZC2         0x2U         // Zero Cross Trip status for
                                               // Ch2
#define SDFM_SDSTATUS_ZC3         0x4U         // Zero Cross Trip status for
                                               // Ch3
#define SDFM_SDSTATUS_ZC4         0x8U         // Zero Cross Trip status for
                                               // Ch4
#define SDFM_SDSTATUS_MAF1        0x100U       // Manchester failure status for
                                               // filter module 1.
#define SDFM_SDSTATUS_MAF2        0x200U       // Manchester failure status for
                                               // filter module 2.
#define SDFM_SDSTATUS_MAF3        0x400U       // Manchester failure status for
                                               // filter module 3.
#define SDFM_SDSTATUS_MAF4        0x800U       // Manchester failure status for
                                               // filter module 4.
#define SDFM_SDSTATUS_MAL1        0x1000U      // Manchester locked status for
                                               // filter module 1.
#define SDFM_SDSTATUS_MAL2        0x2000U      // Manchester locked status for
                                               // filter module 2.
#define SDFM_SDSTATUS_MAL3        0x4000U      // Manchester locked status for
                                               // filter module 3.
#define SDFM_SDSTATUS_MAL4        0x8000U      // Manchester locked status for
                                               // filter module 4.

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCTLPARM1 register
//
//*****************************************************************************
#define SDFM_SDCTLPARM1_MOD_S     0U
#define SDFM_SDCTLPARM1_MOD_M     0x3U         // Modulator clocking modes
#define SDFM_SDCTLPARM1_MS_S      5U
#define SDFM_SDCTLPARM1_MS_M      0xFFE0U      // Manchester Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDFPARM1 register
//
//*****************************************************************************
#define SDFM_SDDFPARM1_DOSR_S     0U
#define SDFM_SDDFPARM1_DOSR_M     0xFFU        // Primary SINC Filter
                                               // Oversample Ratio= DOSR+1
#define SDFM_SDDFPARM1_FEN        0x100U       // Filter Enable
#define SDFM_SDDFPARM1_AE         0x200U       // Ack Enable
#define SDFM_SDDFPARM1_SST_S      10U
#define SDFM_SDDFPARM1_SST_M      0xC00U       // SINC Filter Structure
                                               // (SincFast/1/2/3)
#define SDFM_SDDFPARM1_SDSYNCEN   0x1000U      // SINC FILTER Reset Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDPARM1 register
//
//*****************************************************************************
#define SDFM_SDDPARM1_DR          0x400U       // Data Representation (0/1 =
                                               // 16/32b 2's complement)
#define SDFM_SDDPARM1_SH_S        11U
#define SDFM_SDDPARM1_SH_M        0xF800U      // Shift Control (# bits to
                                               // shift in 16b mode)

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPH1 register
//
//*****************************************************************************
#define SDFM_SDCMPH1_HLT_S        0U
#define SDFM_SDCMPH1_HLT_M        0x7FFFU      // High-level threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPL1 register
//
//*****************************************************************************
#define SDFM_SDCMPL1_LLT_S        0U
#define SDFM_SDCMPL1_LLT_M        0x7FFFU      // Low-level threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCPARM1 register
//
//*****************************************************************************
#define SDFM_SDCPARM1_COSR_S      0U
#define SDFM_SDCPARM1_COSR_M      0x1FU        // Comparator Oversample Ratio.
                                               // Actual rate COSR+1
#define SDFM_SDCPARM1_IEH         0x20U        // High-level Interrupt enable.
#define SDFM_SDCPARM1_IEL         0x40U        // Low-level interrupt enable
#define SDFM_SDCPARM1_CS1_CS0_S   7U
#define SDFM_SDCPARM1_CS1_CS0_M   0x180U       // Comparator Filter Structure
#define SDFM_SDCPARM1_MFIE        0x200U       // Modulator Failure Interrupt
                                               // enable
#define SDFM_SDCPARM1_ZCEN        0x400U       // ZeroCross Trip output enable
#define SDFM_SDCPARM1_CEN         0x2000U      // Comparator Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDATA1 register
//
//*****************************************************************************
#define SDFM_SDDATA1_DATA16_S     0U
#define SDFM_SDDATA1_DATA16_M     0xFFFFU      // 16-bit Data in 16b mode,
                                               // Lo-order 16b in 32b mode
#define SDFM_SDDATA1_DATA32HI_S   16U
#define SDFM_SDDATA1_DATA32HI_M   0xFFFF0000U  // Hi-order 16b in 32b mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDATFIFO1 register
//
//*****************************************************************************
#define SDFM_SDDATFIFO1_DATA16_S  0U
#define SDFM_SDDATFIFO1_DATA16_M  0xFFFFU      // 16-bit data
#define SDFM_SDDATFIFO1_DATA32HI_S  16U
#define SDFM_SDDATFIFO1_DATA32HI_M  0xFFFF0000U  // Hi-order 16b in 32b mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPZ1 register
//
//*****************************************************************************
#define SDFM_SDCMPZ1_ZCT_S        0U
#define SDFM_SDCMPZ1_ZCT_M        0x7FFFU      // Zero-Cross Threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDFIFOCTL1 register
//
//*****************************************************************************
#define SDFM_SDFIFOCTL1_SDFFIL_S  0U
#define SDFM_SDFIFOCTL1_SDFFIL_M  0x1FU        // SD FIFO Interrupt Level
#define SDFM_SDFIFOCTL1_SDFFST_S  6U
#define SDFM_SDFIFOCTL1_SDFFST_M  0x7C0U       // SD FIFO Status
#define SDFM_SDFIFOCTL1_FFIEN     0x1000U      // FIFO Interrupt Enable
#define SDFM_SDFIFOCTL1_FFEN      0x2000U      // SD FIFO Enable
#define SDFM_SDFIFOCTL1_DRINTSEL  0x4000U      // Data-Ready Interrupt Source
                                               // Select
#define SDFM_SDFIFOCTL1_OVFIEN    0x8000U      // SD FIFO Overflow interrupt
                                               // enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDSYNC1 register
//
//*****************************************************************************
#define SDFM_SDSYNC1_SYNCSEL_S    0U
#define SDFM_SDSYNC1_SYNCSEL_M    0x3FU        // SDSYNC Source Select
#define SDFM_SDSYNC1_WTSYNCEN     0x40U        // Wait-for-Sync Enable
#define SDFM_SDSYNC1_WTSYNFLG     0x80U        // Wait-for-Sync Flag
#define SDFM_SDSYNC1_WTSYNCLR     0x100U       // Wait-for-Sync Flag Clear
#define SDFM_SDSYNC1_FFSYNCCLREN  0x200U       // FIFO Clear-on-SDSYNC Enable
#define SDFM_SDSYNC1_WTSCLREN     0x400U       // WTSYNFLG Clear-on-FIFOINT
                                               // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCTLPARM2 register
//
//*****************************************************************************
#define SDFM_SDCTLPARM2_MOD_S     0U
#define SDFM_SDCTLPARM2_MOD_M     0x3U         // Modulator clocking modes
#define SDFM_SDCTLPARM2_MS_S      5U
#define SDFM_SDCTLPARM2_MS_M      0xFFE0U      // Manchester Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDFPARM2 register
//
//*****************************************************************************
#define SDFM_SDDFPARM2_DOSR_S     0U
#define SDFM_SDDFPARM2_DOSR_M     0xFFU        // Primary SINC Filter
                                               // Oversample Ratio= DOSR+1
#define SDFM_SDDFPARM2_FEN        0x100U       // Filter Enable
#define SDFM_SDDFPARM2_AE         0x200U       // Ack Enable
#define SDFM_SDDFPARM2_SST_S      10U
#define SDFM_SDDFPARM2_SST_M      0xC00U       // SINC Filter Structure
                                               // (SincFast/1/2/3)
#define SDFM_SDDFPARM2_SDSYNCEN   0x1000U      // SINC FILTER Reset Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDPARM2 register
//
//*****************************************************************************
#define SDFM_SDDPARM2_DR          0x400U       // Data Representation (0/1 =
                                               // 16/32b 2's complement)
#define SDFM_SDDPARM2_SH_S        11U
#define SDFM_SDDPARM2_SH_M        0xF800U      // Shift Control (# bits to
                                               // shift in 16b mode)

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPH2 register
//
//*****************************************************************************
#define SDFM_SDCMPH2_HLT_S        0U
#define SDFM_SDCMPH2_HLT_M        0x7FFFU      // High-level threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPL2 register
//
//*****************************************************************************
#define SDFM_SDCMPL2_LLT_S        0U
#define SDFM_SDCMPL2_LLT_M        0x7FFFU      // Low-level threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCPARM2 register
//
//*****************************************************************************
#define SDFM_SDCPARM2_COSR_S      0U
#define SDFM_SDCPARM2_COSR_M      0x1FU        // Comparator Oversample Ratio.
                                               // Actual rate COSR+1
#define SDFM_SDCPARM2_IEH         0x20U        // High-level Interrupt enable.
#define SDFM_SDCPARM2_IEL         0x40U        // Low-level interrupt enable
#define SDFM_SDCPARM2_CS1_CS0_S   7U
#define SDFM_SDCPARM2_CS1_CS0_M   0x180U       // Comparator Filter Structure
#define SDFM_SDCPARM2_MFIE        0x200U       // Modulator Failure Interrupt
                                               // enable
#define SDFM_SDCPARM2_ZCEN        0x400U       // ZeroCross Trip output enable
#define SDFM_SDCPARM2_CEN         0x2000U      // Comparator Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDATA2 register
//
//*****************************************************************************
#define SDFM_SDDATA2_DATA16_S     0U
#define SDFM_SDDATA2_DATA16_M     0xFFFFU      // 16-bit Data in 16b mode,
                                               // Lo-order 16b in 32b mode
#define SDFM_SDDATA2_DATA32HI_S   16U
#define SDFM_SDDATA2_DATA32HI_M   0xFFFF0000U  // Hi-order 16b in 32b mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDATFIFO2 register
//
//*****************************************************************************
#define SDFM_SDDATFIFO2_DATA16_S  0U
#define SDFM_SDDATFIFO2_DATA16_M  0xFFFFU      // 16-bit data
#define SDFM_SDDATFIFO2_DATA32HI_S  16U
#define SDFM_SDDATFIFO2_DATA32HI_M  0xFFFF0000U  // Hi-order 16b in 32b mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPZ2 register
//
//*****************************************************************************
#define SDFM_SDCMPZ2_ZCT_S        0U
#define SDFM_SDCMPZ2_ZCT_M        0x7FFFU      // Zero-Cross Threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDFIFOCTL2 register
//
//*****************************************************************************
#define SDFM_SDFIFOCTL2_SDFFIL_S  0U
#define SDFM_SDFIFOCTL2_SDFFIL_M  0x1FU        // SD FIFO Interrupt Level
#define SDFM_SDFIFOCTL2_SDFFST_S  6U
#define SDFM_SDFIFOCTL2_SDFFST_M  0x7C0U       // SD FIFO Status
#define SDFM_SDFIFOCTL2_FFIEN     0x1000U      // FIFO Interrupt Enable
#define SDFM_SDFIFOCTL2_FFEN      0x2000U      // SD FIFO Enable
#define SDFM_SDFIFOCTL2_DRINTSEL  0x4000U      // Data-Ready Interrupt Source
                                               // Select
#define SDFM_SDFIFOCTL2_OVFIEN    0x8000U      // SD FIFO Overflow interrupt
                                               // enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDSYNC2 register
//
//*****************************************************************************
#define SDFM_SDSYNC2_SYNCSEL_S    0U
#define SDFM_SDSYNC2_SYNCSEL_M    0x3FU        // SDSYNC Source Select
#define SDFM_SDSYNC2_WTSYNCEN     0x40U        // Wait-fo-Sync Enable
#define SDFM_SDSYNC2_WTSYNFLG     0x80U        // Wait-for-Sync Flag
#define SDFM_SDSYNC2_WTSYNCLR     0x100U       // Wait-for-Sync Flag Clear
#define SDFM_SDSYNC2_FFSYNCCLREN  0x200U       // FIFO Clear-on-SDSYNC Enable
#define SDFM_SDSYNC2_WTSCLREN     0x400U       // WTSYNFLG Clear-on-FIFOINT
                                               // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCTLPARM3 register
//
//*****************************************************************************
#define SDFM_SDCTLPARM3_MOD_S     0U
#define SDFM_SDCTLPARM3_MOD_M     0x3U         // Modulator clocking modes
#define SDFM_SDCTLPARM3_MS_S      5U
#define SDFM_SDCTLPARM3_MS_M      0xFFE0U      // Manchester Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDFPARM3 register
//
//*****************************************************************************
#define SDFM_SDDFPARM3_DOSR_S     0U
#define SDFM_SDDFPARM3_DOSR_M     0xFFU        // Primary SINC Filter
                                               // Oversample Ratio= DOSR+1
#define SDFM_SDDFPARM3_FEN        0x100U       // Filter Enable
#define SDFM_SDDFPARM3_AE         0x200U       // Ack Enable
#define SDFM_SDDFPARM3_SST_S      10U
#define SDFM_SDDFPARM3_SST_M      0xC00U       // SINC Filter Structure
                                               // (SincFast/1/2/3)
#define SDFM_SDDFPARM3_SDSYNCEN   0x1000U      // SINC FILTER Reset Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDPARM3 register
//
//*****************************************************************************
#define SDFM_SDDPARM3_DR          0x400U       // Data Representation (0/1 =
                                               // 16/32b 2's complement)
#define SDFM_SDDPARM3_SH_S        11U
#define SDFM_SDDPARM3_SH_M        0xF800U      // Shift Control (# bits to
                                               // shift in 16b mode)

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPH3 register
//
//*****************************************************************************
#define SDFM_SDCMPH3_HLT_S        0U
#define SDFM_SDCMPH3_HLT_M        0x7FFFU      // High-level threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPL3 register
//
//*****************************************************************************
#define SDFM_SDCMPL3_LLT_S        0U
#define SDFM_SDCMPL3_LLT_M        0x7FFFU      // Low-level threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCPARM3 register
//
//*****************************************************************************
#define SDFM_SDCPARM3_COSR_S      0U
#define SDFM_SDCPARM3_COSR_M      0x1FU        // Comparator Oversample Ratio.
                                               // Actual rate COSR+1
#define SDFM_SDCPARM3_IEH         0x20U        // High-level Interrupt enable.
#define SDFM_SDCPARM3_IEL         0x40U        // Low-level interrupt enable
#define SDFM_SDCPARM3_CS1_CS0_S   7U
#define SDFM_SDCPARM3_CS1_CS0_M   0x180U       // Comparator Filter Structure
#define SDFM_SDCPARM3_MFIE        0x200U       // Modulator Failure Interrupt
                                               // enable
#define SDFM_SDCPARM3_ZCEN        0x400U       // ZeroCross Trip output enable
#define SDFM_SDCPARM3_CEN         0x2000U      // Comparator Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDATA3 register
//
//*****************************************************************************
#define SDFM_SDDATA3_DATA16_S     0U
#define SDFM_SDDATA3_DATA16_M     0xFFFFU      // 16-bit Data in 16b mode,
                                               // Lo-order 16b in 32b mode
#define SDFM_SDDATA3_DATA32HI_S   16U
#define SDFM_SDDATA3_DATA32HI_M   0xFFFF0000U  // Hi-order 16b in 32b mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDATFIFO3 register
//
//*****************************************************************************
#define SDFM_SDDATFIFO3_DATA16_S  0U
#define SDFM_SDDATFIFO3_DATA16_M  0xFFFFU      // 16-bit data
#define SDFM_SDDATFIFO3_DATA32HI_S  16U
#define SDFM_SDDATFIFO3_DATA32HI_M  0xFFFF0000U  // Hi-order 16b in 32b mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPZ3 register
//
//*****************************************************************************
#define SDFM_SDCMPZ3_ZCT_S        0U
#define SDFM_SDCMPZ3_ZCT_M        0x7FFFU      // Zero-Cross Threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDFIFOCTL3 register
//
//*****************************************************************************
#define SDFM_SDFIFOCTL3_SDFFIL_S  0U
#define SDFM_SDFIFOCTL3_SDFFIL_M  0x1FU        // SD FIFO Interrupt Level
#define SDFM_SDFIFOCTL3_SDFFST_S  6U
#define SDFM_SDFIFOCTL3_SDFFST_M  0x7C0U       // SD FIFO Status
#define SDFM_SDFIFOCTL3_FFIEN     0x1000U      // FIFO Interrupt Enable
#define SDFM_SDFIFOCTL3_FFEN      0x2000U      // SD FIFO Enable
#define SDFM_SDFIFOCTL3_DRINTSEL  0x4000U      // Data-Ready Interrupt Source
                                               // Select
#define SDFM_SDFIFOCTL3_OVFIEN    0x8000U      // SD FIFO Overflow interrupt
                                               // enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDSYNC3 register
//
//*****************************************************************************
#define SDFM_SDSYNC3_SYNCSEL_S    0U
#define SDFM_SDSYNC3_SYNCSEL_M    0x3FU        // SDSYNC Source Select
#define SDFM_SDSYNC3_WTSYNCEN     0x40U        // Wait-fo-Sync Enable
#define SDFM_SDSYNC3_WTSYNFLG     0x80U        // Wait-for-Sync Flag
#define SDFM_SDSYNC3_WTSYNCLR     0x100U       // Wait-for-Sync Flag Clear
#define SDFM_SDSYNC3_FFSYNCCLREN  0x200U       // FIFO Clear-on-SDSYNC Enable
#define SDFM_SDSYNC3_WTSCLREN     0x400U       // WTSYNFLG Clear-on-FIFOINT
                                               // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCTLPARM4 register
//
//*****************************************************************************
#define SDFM_SDCTLPARM4_MOD_S     0U
#define SDFM_SDCTLPARM4_MOD_M     0x3U         // Modulator clocking modes
#define SDFM_SDCTLPARM4_MS_S      5U
#define SDFM_SDCTLPARM4_MS_M      0xFFE0U      // Manchester Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDFPARM4 register
//
//*****************************************************************************
#define SDFM_SDDFPARM4_DOSR_S     0U
#define SDFM_SDDFPARM4_DOSR_M     0xFFU        // Primary SINC Filter
                                               // Oversample Ratio= DOSR+1
#define SDFM_SDDFPARM4_FEN        0x100U       // Filter Enable
#define SDFM_SDDFPARM4_AE         0x200U       // Ack Enable
#define SDFM_SDDFPARM4_SST_S      10U
#define SDFM_SDDFPARM4_SST_M      0xC00U       // SINC Filter Structure
                                               // (SincFast/1/2/3)
#define SDFM_SDDFPARM4_SDSYNCEN   0x1000U      // SINC FILTER Reset Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDPARM4 register
//
//*****************************************************************************
#define SDFM_SDDPARM4_DR          0x400U       // Data Representation (0/1 =
                                               // 16/32b 2's complement)
#define SDFM_SDDPARM4_SH_S        11U
#define SDFM_SDDPARM4_SH_M        0xF800U      // Shift Control (# bits to
                                               // shift in 16b mode)

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPH4 register
//
//*****************************************************************************
#define SDFM_SDCMPH4_HLT_S        0U
#define SDFM_SDCMPH4_HLT_M        0x7FFFU      // High-level threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPL4 register
//
//*****************************************************************************
#define SDFM_SDCMPL4_LLT_S        0U
#define SDFM_SDCMPL4_LLT_M        0x7FFFU      // Low-level threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCPARM4 register
//
//*****************************************************************************
#define SDFM_SDCPARM4_COSR_S      0U
#define SDFM_SDCPARM4_COSR_M      0x1FU        // Comparator Oversample Ratio.
                                               // Actual rate COSR+1
#define SDFM_SDCPARM4_IEH         0x20U        // High-level Interrupt enable.
#define SDFM_SDCPARM4_IEL         0x40U        // Low-level interrupt enable
#define SDFM_SDCPARM4_CS1_CS0_S   7U
#define SDFM_SDCPARM4_CS1_CS0_M   0x180U       // Comparator Filter Structure
#define SDFM_SDCPARM4_MFIE        0x200U       // Modulator Failure Interrupt
                                               // enable
#define SDFM_SDCPARM4_ZCEN        0x400U       // ZeroCross Trip output enable
#define SDFM_SDCPARM4_CEN         0x2000U      // Comparator Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDATA4 register
//
//*****************************************************************************
#define SDFM_SDDATA4_DATA16_S     0U
#define SDFM_SDDATA4_DATA16_M     0xFFFFU      // 16-bit Data in 16b mode,
                                               // Lo-order 16b in 32b mode
#define SDFM_SDDATA4_DATA32HI_S   16U
#define SDFM_SDDATA4_DATA32HI_M   0xFFFF0000U  // Hi-order 16b in 32b mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SDDATFIFO4 register
//
//*****************************************************************************
#define SDFM_SDDATFIFO4_DATA16_S  0U
#define SDFM_SDDATFIFO4_DATA16_M  0xFFFFU      // 16-bit data
#define SDFM_SDDATFIFO4_DATA32HI_S  16U
#define SDFM_SDDATFIFO4_DATA32HI_M  0xFFFF0000U  // Hi-order 16b in 32b mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SDCMPZ4 register
//
//*****************************************************************************
#define SDFM_SDCMPZ4_ZCT_S        0U
#define SDFM_SDCMPZ4_ZCT_M        0x7FFFU      // Zero-Cross Threshold

//*****************************************************************************
//
// The following are defines for the bit fields in the SDFIFOCTL4 register
//
//*****************************************************************************
#define SDFM_SDFIFOCTL4_SDFFIL_S  0U
#define SDFM_SDFIFOCTL4_SDFFIL_M  0x1FU        // SD FIFO Interrupt Level
#define SDFM_SDFIFOCTL4_SDFFST_S  6U
#define SDFM_SDFIFOCTL4_SDFFST_M  0x7C0U       // SD FIFO Status
#define SDFM_SDFIFOCTL4_FFIEN     0x1000U      // FIFO Interrupt Enable
#define SDFM_SDFIFOCTL4_FFEN      0x2000U      // SD FIFO Enable
#define SDFM_SDFIFOCTL4_DRINTSEL  0x4000U      // Data-Ready Interrupt Source
                                               // Select
#define SDFM_SDFIFOCTL4_OVFIEN    0x8000U      // SD FIFO Overflow interrupt
                                               // enable

//*****************************************************************************
//
// The following are defines for the bit fields in the SDSYNC4 register
//
//*****************************************************************************
#define SDFM_SDSYNC4_SYNCSEL_S    0U
#define SDFM_SDSYNC4_SYNCSEL_M    0x3FU        // SDSYNC Source Select
#define SDFM_SDSYNC4_WTSYNCEN     0x40U        // Wait-fo-Sync Enable
#define SDFM_SDSYNC4_WTSYNFLG     0x80U        // Wait-for-Sync Flag
#define SDFM_SDSYNC4_WTSYNCLR     0x100U       // Wait-for-Sync Flag Clear
#define SDFM_SDSYNC4_FFSYNCCLREN  0x200U       // FIFO Clear-on-SDSYNC Enable
#define SDFM_SDSYNC4_WTSCLREN     0x400U       // WTSYNFLG Clear-on-FIFOINT
                                               // Enable
#endif
