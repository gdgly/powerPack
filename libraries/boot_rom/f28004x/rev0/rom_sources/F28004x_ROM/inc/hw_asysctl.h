//###########################################################################
//
// FILE:    hw_asysctl.h
//
// TITLE:   Definitions for the ASYSCTL registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef __HW_ASYSCTL_H__
#define __HW_ASYSCTL_H__

//*****************************************************************************
//
// The following are defines for the ASYS register offsets
//
//*****************************************************************************
#define ASYSCTL_O_DCDCTRIM0       0x16U       // DCDC trim0 register.
#define ASYSCTL_O_DCDCTRIM1       0x18U       // DCDC trim1 register.
#define ASYSCTL_O_TSNSCTL         0x60U       // Temperature Sensor Control
                                              // Register
#define ASYSCTL_O_ANAREFCTL       0x68U       // Analog Reference Control
                                              // Register
#define ASYSCTL_O_DCDCCTL         0x78U       // DC-DC control register.
#define ASYSCTL_O_DCDCSTS         0x7AU       // DC-DC status register.
#define ASYSCTL_O_DCDCSTSCLR      0x7BU       // DC-DC status Clear register.
#define ASYSCTL_O_DCDCSSCTL       0x7CU       // DC-DC Spread Spectrum Control
                                              // Register
#define ASYSCTL_O_ADCINMXSEL      0x80U       // Bits to select one of the 2
                                              // sources on ADC channels which
                                              // have multiple sources. Refer
                                              // to Pimux diagram for details.
#define ASYSCTL_O_CMPHPMXSEL      0x82U       // Bits to select one of the
                                              // many sources on CopmHP inputs.
                                              // Refer to Pimux diagram for
                                              // details.
#define ASYSCTL_O_CMPLPMXSEL      0x84U       // Bits to select one of the
                                              // many sources on CopmLP inputs.
                                              // Refer to Pimux diagram for
                                              // details.
#define ASYSCTL_O_CMPHNMXSEL      0x86U       // Bits to select one of the
                                              // many sources on CopmHN inputs.
                                              // Refer to Pimux diagram for
                                              // details.
#define ASYSCTL_O_CMPLNMXSEL      0x87U       // Bits to select one of the
                                              // many sources on CopmLN inputs.
                                              // Refer to Pimux diagram for
                                              // details.
#define ASYSCTL_O_LOCK            0x8EU       // Lock Register

//*****************************************************************************
//
// The following are defines for the bit fields in the DCDCTRIM0 register
//
//*****************************************************************************
#define ASYSCTL_DCDCTRIM0_TRIM_S  0U
#define ASYSCTL_DCDCTRIM0_TRIM_M  0xFFU       // Output voltage trim:
#define ASYSCTL_DCDCTRIM0_SPARE_TRIM_S  8U
#define ASYSCTL_DCDCTRIM0_SPARE_TRIM_M  0xFF00U     // Spare Trim registers

//*****************************************************************************
//
// The following are defines for the bit fields in the TSNSCTL register
//
//*****************************************************************************
#define ASYSCTL_TSNSCTL_ENABLE    0x1U        // Temperature Sensor Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ANAREFCTL register
//
//*****************************************************************************
#define ASYSCTL_ANAREFCTL_ANAREFASEL  0x1U        // Analog Reference A Select
#define ASYSCTL_ANAREFCTL_ANAREFBSEL  0x2U        // Analog Reference B Select
#define ASYSCTL_ANAREFCTL_ANAREFCSEL  0x4U        // Analog Reference C Select
#define ASYSCTL_ANAREFCTL_ANAREFA2P5SEL  0x100U      // Analog Reference A Select
#define ASYSCTL_ANAREFCTL_ANAREFB2P5SEL  0x200U      // Analog Reference B Select
#define ASYSCTL_ANAREFCTL_ANAREFC2P5SEL  0x400U      // Analog Reference B Select

//*****************************************************************************
//
// The following are defines for the bit fields in the DCDCCTL register
//
//*****************************************************************************
#define ASYSCTL_DCDCCTL_DCDCEN    0x1U        // DCDC Enable
#define ASYSCTL_DCDCCTL_OLFNMIEN  0x80000000U // OLF NMI enable bit

//*****************************************************************************
//
// The following are defines for the bit fields in the DCDCSTS register
//
//*****************************************************************************
#define ASYSCTL_DCDCSTS_INDFAULT  0x1U        // Inductor fault
#define ASYSCTL_DCDCSTS_SWSEQDONE  0x2U        // Switch sequence to DC-DC
                                              // done.
#define ASYSCTL_DCDCSTS_OLF       0x4U        // DC-DC overload fault

//*****************************************************************************
//
// The following are defines for the bit fields in the DCDCSTSCLR register
//
//*****************************************************************************
#define ASYSCTL_DCDCSTSCLR_INDFAULT  0x1U        // Clear Inductor fault bit of
                                              // DCDCSTS register.
#define ASYSCTL_DCDCSTSCLR_SWSEQDONE  0x2U        // Clear SWESEQDONE bit of
                                              // DCDCSTS register.
#define ASYSCTL_DCDCSTSCLR_OLF    0x4U        // Clear OLF bit of DCDCSTS
                                              // register.

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCINMXSEL register
//
//*****************************************************************************
#define ASYSCTL_ADCINMXSEL_ADCIN1MXSEL  0x1U        // Mux select of ADCIN1MXSEL
#define ASYSCTL_ADCINMXSEL_ADCIN2MXSEL  0x2U        // Mux select of ADCIN2MXSEL
#define ASYSCTL_ADCINMXSEL_ADCIN3MXSEL  0x4U        // Mux select of ADCIN3MXSEL
#define ASYSCTL_ADCINMXSEL_ADCIN4MXSEL  0x8U        // Mux select of ADCIN4MXSEL
#define ASYSCTL_ADCINMXSEL_ADCIN5MXSEL  0x10U       // Mux select of ADCIN5MXSEL
#define ASYSCTL_ADCINMXSEL_ADCIN6MXSEL  0x20U       // Mux select of ADCIN6MXSEL
#define ASYSCTL_ADCINMXSEL_ADCIN7MXSEL  0x40U       // Mux select of ADCIN7MXSEL

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPHPMXSEL register
//
//*****************************************************************************
#define ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_S  0U
#define ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_M  0x7U        // CMP1HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP2HPMXSEL_S  3U
#define ASYSCTL_CMPHPMXSEL_CMP2HPMXSEL_M  0x38U       // CMP2HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP3HPMXSEL_S  6U
#define ASYSCTL_CMPHPMXSEL_CMP3HPMXSEL_M  0x1C0U      // CMP3HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP4HPMXSEL_S  9U
#define ASYSCTL_CMPHPMXSEL_CMP4HPMXSEL_M  0xE00U      // CMP4HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP5HPMXSEL_S  12U
#define ASYSCTL_CMPHPMXSEL_CMP5HPMXSEL_M  0x7000U     // CMP5HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP6HPMXSEL_S  16U
#define ASYSCTL_CMPHPMXSEL_CMP6HPMXSEL_M  0x70000U    // CMP6HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP7HPMXSEL_S  19U
#define ASYSCTL_CMPHPMXSEL_CMP7HPMXSEL_M  0x380000U   // CMP7HPMXSEL bits

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPLPMXSEL register
//
//*****************************************************************************
#define ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_S  0U
#define ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M  0x7U        // CMP1LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP2LPMXSEL_S  3U
#define ASYSCTL_CMPLPMXSEL_CMP2LPMXSEL_M  0x38U       // CMP2LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP3LPMXSEL_S  6U
#define ASYSCTL_CMPLPMXSEL_CMP3LPMXSEL_M  0x1C0U      // CMP3LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP4LPMXSEL_S  9U
#define ASYSCTL_CMPLPMXSEL_CMP4LPMXSEL_M  0xE00U      // CMP4LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP5LPMXSEL_S  12U
#define ASYSCTL_CMPLPMXSEL_CMP5LPMXSEL_M  0x7000U     // CMP5LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP6LPMXSEL_S  16U
#define ASYSCTL_CMPLPMXSEL_CMP6LPMXSEL_M  0x70000U    // CMP6LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP7LPMXSEL_S  19U
#define ASYSCTL_CMPLPMXSEL_CMP7LPMXSEL_M  0x380000U   // CMP7LPMXSEL bits

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPHNMXSEL register
//
//*****************************************************************************
#define ASYSCTL_CMPHNMXSEL_CMP1HNMXSEL  0x1U        // CMP1HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP2HNMXSEL  0x2U        // CMP2HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP3HNMXSEL  0x4U        // CMP3HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP4HNMXSEL  0x8U        // CMP4HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP5HNMXSEL  0x10U       // CMP5HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP6HNMXSEL  0x20U       // CMP6HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP7HNMXSEL  0x40U       // CMP7HNMXSEL bits

//*****************************************************************************
//
// The following are defines for the bit fields in the CMPLNMXSEL register
//
//*****************************************************************************
#define ASYSCTL_CMPLNMXSEL_CMP1LNMXSEL  0x1U        // CMP1LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP2LNMXSEL  0x2U        // CMP2LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP3LNMXSEL  0x4U        // CMP3LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP4LNMXSEL  0x8U        // CMP4LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP5LNMXSEL  0x10U       // CMP5LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP6LNMXSEL  0x20U       // CMP6LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP7LNMXSEL  0x40U       // CMP7LNMXSEL bits

//*****************************************************************************
//
// The following are defines for the bit fields in the LOCK register
//
//*****************************************************************************
#define ASYSCTL_LOCK_TSNSCTL      0x1U        // TSNSCTL Register lock bit
#define ASYSCTL_LOCK_ANAREFCTL    0x2U        // ANAREFCTL Register lock bit
#define ASYSCTL_LOCK_VMONCTL      0x4U        // VMONCTL Register lock bit
#define ASYSCTL_LOCK_DCDCCTL      0x8U        // DCDCCTL Register lock bit
#define ASYSCTL_LOCK_ADCINMXSEL   0x10U       // ADCINMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPHPMXSEL   0x20U       // CMPHPMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPLPMXSEL   0x40U       // CMPLPMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPHNMXSEL   0x80U       // CMPHNMXSEL Register lock bit
#define ASYSCTL_LOCK_CMPLNMXSEL   0x100U      // CMPLNMXSEL Register lock bit
#define ASYSCTL_LOCK_VREGCTL      0x200U      // VREGCTL Register lock bit
#endif
