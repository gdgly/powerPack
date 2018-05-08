//###########################################################################
//
// FILE:    hw_inputxbar.h
//
// TITLE:   Definitions for the XBAR registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef __HW_INPUTXBAR_H__
#define __HW_INPUTXBAR_H__

//*****************************************************************************
//
// The following are defines for the Input XBAR register offsets
//
//*****************************************************************************
#define XBAR_O_INPUT1SELECT       0x0U        // INPUT1 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT2SELECT       0x1U        // INPUT2 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT3SELECT       0x2U        // INPUT3 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT4SELECT       0x3U        // INPUT4 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT5SELECT       0x4U        // INPUT5 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT6SELECT       0x5U        // INPUT6 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT7SELECT       0x6U        // INPUT7 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT8SELECT       0x7U        // INPUT8 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT9SELECT       0x8U        // INPUT9 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT10SELECT      0x9U        // INPUT10 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT11SELECT      0xAU        // INPUT11 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT12SELECT      0xBU        // INPUT12 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT13SELECT      0xCU        // INPUT13 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUT14SELECT      0xDU        // INPUT14 Input Select Register
                                              // (GPIO0 to x)
#define XBAR_O_INPUTSELECTLOCK    0x1EU       // Input Select Lock Register
#define XBAR_O_TRIGLATCH1         0x20U       // X-Bar Input Latch Register 1
#define XBAR_O_TRIGLATCH2         0x22U       // X-Bar Input Latch Register 2
#define XBAR_O_TRIGLATCH3         0x24U       // X-Bar Input Latch Register 3
#define XBAR_O_TRIGLATCH4         0x26U       // X-Bar Input Latch Register 4
#define XBAR_O_TRIGLATCHCLR1      0x28U       // X-Bar Input Latch Clear
                                              // Register 1
#define XBAR_O_TRIGLATCHCLR2      0x2AU       // X-Bar Input Latch Clear
                                              // Register 2
#define XBAR_O_TRIGLATCHCLR3      0x2CU       // X-Bar Input Latch Clear
                                              // Register 3
#define XBAR_O_TRIGLATCHCLR4      0x2EU       // X-Bar Input Latch Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the INPUTSELECTLOCK register
//
//*****************************************************************************
#define XBAR_INPUTSELECTLOCK_INPUT1SELECT  0x1U        // Lock bit for INPUT1SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT2SELECT  0x2U        // Lock bit for INPUT2SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT3SELECT  0x4U        // Lock bit for INPUT3SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT4SELECT  0x8U        // Lock bit for INPUT4SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT5SELECT  0x10U       // Lock bit for INPUT5SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT6SELECT  0x20U       // Lock bit for INPUT7SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT7SELECT  0x40U       // Lock bit for INPUT8SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT8SELECT  0x80U       // Lock bit for INPUT9SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT9SELECT  0x100U      // Lock bit for INPUT10SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT10SELECT  0x200U      // Lock bit for INPUT11SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT11SELECT  0x400U      // Lock bit for INPUT11SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT12SELECT  0x800U      // Lock bit for INPUT12SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT13SELECT  0x1000U     // Lock bit for INPUT13SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT14SELECT  0x2000U     // Lock bit for INPUT14SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT15SELECT  0x4000U     // Lock bit for INPUT15SEL
                                              // Register
#define XBAR_INPUTSELECTLOCK_INPUT16SELECT  0x8000U     // Lock bit for INPUT16SEL
                                              // Register

//*****************************************************************************
//
// The following are defines for the bit fields in the TRIGLATCH1 register
//
//*****************************************************************************
#define XBAR_TRIGLATCH1_CMPSS1_CTRIPL  0x1U        // Input Latch for CMPSS1.CTRIPL
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS1_CTRIPH  0x2U        // Input Latch for CMPSS1.CTRIPH
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS2_CTRIPL  0x4U        // Input Latch for CMPSS2.CTRIPL
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS2_CTRIPH  0x8U        // Input Latch for CMPSS2.CTRIPH
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS3_CTRIPL  0x10U       // Input Latch for CMPSS3.CTRIPL
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS3_CTRIPH  0x20U       // Input Latch for CMPSS3.CTRIPH
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS4_CTRIPL  0x40U       // Input Latch for CMPSS4.CTRIPL
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS4_CTRIPH  0x80U       // Input Latch for CMPSS4.CTRIPH
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS5_CTRIPL  0x100U      // Input Latch for CMPSS5.CTRIPL
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS5_CTRIPH  0x200U      // Input Latch for CMPSS5.CTRIPH
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS6_CTRIPL  0x400U      // Input Latch for CMPSS6.CTRIPL
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS6_CTRIPH  0x800U      // Input Latch for CMPSS6.CTRIPH
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS7_CTRIPL  0x1000U     // Input Latch for CMPSS7.CTRIPL
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS7_CTRIPH  0x2000U     // Input Latch for CMPSS7.CTRIPH
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS8_CTRIPL  0x4000U     // Input Latch for CMPSS8.CTRIPL
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS8_CTRIPH  0x8000U     // Input Latch for CMPSS8.CTRIPH
                                              // Signal
#define XBAR_TRIGLATCH1_CMPSS1_CTRIPOUTL  0x10000U    // Input Latch for
                                              // CMPSS1.CTRIPOUTL Signal
#define XBAR_TRIGLATCH1_CMPSS1_CTRIPOUTH  0x20000U    // Input Latch for
                                              // CMPSS1.CTRIPOUTH Signal
#define XBAR_TRIGLATCH1_CMPSS2_CTRIPOUTL  0x40000U    // Input Latch for
                                              // CMPSS2.CTRIPOUTL Signal
#define XBAR_TRIGLATCH1_CMPSS2_CTRIPOUTH  0x80000U    // Input Latch for
                                              // CMPSS2.CTRIPOUTH Signal
#define XBAR_TRIGLATCH1_CMPSS3_CTRIPOUTL  0x100000U   // Input Latch for
                                              // CMPSS3.CTRIPOUTL Signal
#define XBAR_TRIGLATCH1_CMPSS3_CTRIPOUTH  0x200000U   // Input Latch for
                                              // CMPSS3.CTRIPOUTH Signal
#define XBAR_TRIGLATCH1_CMPSS4_CTRIPOUTL  0x400000U   // Input Latch for
                                              // CMPSS4.CTRIPOUTL Signal
#define XBAR_TRIGLATCH1_CMPSS4_CTRIPOUTH  0x800000U   // Input Latch for
                                              // CMPSS4.CTRIPOUTH Signal
#define XBAR_TRIGLATCH1_CMPSS5_CTRIPOUTL  0x1000000U  // Input Latch for
                                              // CMPSS5.CTRIPOUTL Signal
#define XBAR_TRIGLATCH1_CMPSS5_CTRIPOUTH  0x2000000U  // Input Latch for
                                              // CMPSS5.CTRIPOUTH Signal
#define XBAR_TRIGLATCH1_CMPSS6_CTRIPOUTL  0x4000000U  // Input Latch for
                                              // CMPSS6.CTRIPOUTL Signal
#define XBAR_TRIGLATCH1_CMPSS6_CTRIPOUTH  0x8000000U  // Input Latch for
                                              // CMPSS6.CTRIPOUTH Signal
#define XBAR_TRIGLATCH1_CMPSS7_CTRIPOUTL  0x10000000U // Input Latch for
                                              // CMPSS7.CTRIPOUTL Signal
#define XBAR_TRIGLATCH1_CMPSS7_CTRIPOUTH  0x20000000U // Input Latch for
                                              // CMPSS7.CTRIPOUTH Signal
#define XBAR_TRIGLATCH1_CMPSS8_CTRIPOUTL  0x40000000U // Input Latch for
                                              // CMPSS8.CTRIPOUTL Signal
#define XBAR_TRIGLATCH1_CMPSS8_CTRIPOUTH  0x80000000U // Input Latch for
                                              // CMPSS8.CTRIPOUTH Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the TRIGLATCH2 register
//
//*****************************************************************************
#define XBAR_TRIGLATCH2_INPUT1    0x1U        // Input Latch for INPUT1 Signal
#define XBAR_TRIGLATCH2_INPUT2    0x2U        // Input Latch for INPUT2 Signal
#define XBAR_TRIGLATCH2_INPUT3    0x4U        // Input Latch for INPUT3 Signal
#define XBAR_TRIGLATCH2_INPUT4    0x8U        // Input Latch for INPUT4 Signal
#define XBAR_TRIGLATCH2_INPUT5    0x10U       // Input Latch for INPUT5 Signal
#define XBAR_TRIGLATCH2_INPUT6    0x20U       // Input Latch for INPUT6 Signal
#define XBAR_TRIGLATCH2_ADCSOCA   0x40U       // Input Latch for ADCSOCA
                                              // Signal
#define XBAR_TRIGLATCH2_ADCSOCB   0x80U       // Input Latch for ADCSOCB
                                              // Signal
#define XBAR_TRIGLATCH2_ECAP1_OUT  0x10000U    // Input Latch for ECAP1.OUT
                                              // Signal
#define XBAR_TRIGLATCH2_ECAP2_OUT  0x20000U    // Input Latch for ECAP2.OUT
                                              // Signal
#define XBAR_TRIGLATCH2_ECAP3_OUT  0x40000U    // Input Latch for ECAP3.OUT
                                              // Signal
#define XBAR_TRIGLATCH2_ECAP4_OUT  0x80000U    // Input Latch for ECAP4.OUT
                                              // Signal
#define XBAR_TRIGLATCH2_ECAP5_OUT  0x100000U   // Input Latch for ECAP5.OUT
                                              // Signal
#define XBAR_TRIGLATCH2_ECAP6_OUT  0x200000U   // Input Latch for ECAP6.OUT
                                              // Signal
#define XBAR_TRIGLATCH2_EXTSYNCOUT  0x400000U   // Input Latch for EXTSYNCOUT
                                              // Signal
#define XBAR_TRIGLATCH2_ADCAEVT1  0x800000U   // Input Latch for ADCAEVT1
                                              // Signal
#define XBAR_TRIGLATCH2_ADCAEVT2  0x1000000U  // Input Latch for ADCAEVT2
                                              // Signal
#define XBAR_TRIGLATCH2_ADCAEVT3  0x2000000U  // Input Latch for ADCAEVT3
                                              // Signal
#define XBAR_TRIGLATCH2_ADCAEVT4  0x4000000U  // Input Latch for ADCAEVT4
                                              // Signal
#define XBAR_TRIGLATCH2_ADCBEVT1  0x8000000U  // Input Latch for ADCBEVT1
                                              // Signal
#define XBAR_TRIGLATCH2_ADCBEVT2  0x10000000U // Input Latch for ADCBEVT2
                                              // Signal
#define XBAR_TRIGLATCH2_ADCBEVT3  0x20000000U // Input Latch for ADCBEVT3
                                              // Signal
#define XBAR_TRIGLATCH2_ADCBEVT4  0x40000000U // Input Latch for ADCBEVT4
                                              // Signal
#define XBAR_TRIGLATCH2_ADCCEVT1  0x80000000U // Input Latch for ADCCEVT1
                                              // Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the TRIGLATCH3 register
//
//*****************************************************************************
#define XBAR_TRIGLATCH3_ADCCEVT2  0x1U        // Input Latch for ADCCEVT2
                                              // Signal
#define XBAR_TRIGLATCH3_ADCCEVT3  0x2U        // Input Latch for ADCCEVT3
                                              // Signal
#define XBAR_TRIGLATCH3_ADCCEVT4  0x4U        // Input Latch for ADCCEVT4
                                              // Signal
#define XBAR_TRIGLATCH3_ADCDEVT1  0x8U        // Input Latch for ADCDEVT1
                                              // Signal
#define XBAR_TRIGLATCH3_ADCDEVT2  0x10U       // Input Latch for ADCDEVT2
                                              // Signal
#define XBAR_TRIGLATCH3_ADCDEVT3  0x20U       // Input Latch for ADCDEVT3
                                              // Signal
#define XBAR_TRIGLATCH3_ADCDEVT4  0x40U       // Input Latch for ADCDEVT4
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT1_COMPL  0x80U       // Input Latch for SD1FLT1.COMPL
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT1_COMPH  0x100U      // Input Latch for SD1FLT1.COMPH
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT2_COMPL  0x200U      // Input Latch for SD1FLT2.COMPL
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT2_COMPH  0x400U      // Input Latch for SD1FLT2.COMPH
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT3_COMPL  0x800U      // Input Latch for SD1FLT3.COMPL
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT3_COMPH  0x1000U     // Input Latch for SD1FLT3.COMPH
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT4_COMPL  0x2000U     // Input Latch for SD1FLT4.COMPL
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT4_COMPH  0x4000U     // Input Latch for SD1FLT4.COMPH
                                              // Signal
#define XBAR_TRIGLATCH3_ECAP7_OUT  0x800000U   // Input Latch for ECAP7.OUT
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT1_COMPZ  0x1000000U  // Input Latch for SD1FLT1.COMPZ
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT1_DRINT  0x2000000U  // Input Latch for SD1FLT1.DRINT
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT2_COMPZ  0x4000000U  // Input Latch for SD1FLT2.COMPZ
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT2_DRINT  0x8000000U  // Input Latch for SD1FLT2.DRINT
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT3_COMPZ  0x10000000U // Input Latch for SD1FLT3.COMPZ
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT3_DRINT  0x20000000U // Input Latch for SD1FLT3.DRINT
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT4_COMPZ  0x40000000U // Input Latch for SD1FLT4.COMPZ
                                              // Signal
#define XBAR_TRIGLATCH3_SD1FLT4_DRINT  0x80000000U // Input Latch for SD1FLT4.DRINT
                                              // Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the TRIGLATCH4 register
//
//*****************************************************************************
#define XBAR_TRIGLATCH4_SD2FLT1_COMPZ  0x1U        // Input Latch for SD2FLT1.COMPZ
                                              // Signal
#define XBAR_TRIGLATCH4_SD2FLT1_DRINT  0x2U        // Input Latch for SD2FLT1.DRINT
                                              // Signal
#define XBAR_TRIGLATCH4_SD2FLT2_COMPZ  0x4U        // Input Latch for SD2FLT2.COMPZ
                                              // Signal
#define XBAR_TRIGLATCH4_SD2FLT2_DRINT  0x8U        // Input Latch for SD2FLT2.DRINT
                                              // Signal
#define XBAR_TRIGLATCH4_SD2FLT3_COMPZ  0x10U       // Input Latch for SD2FLT3.COMPZ
                                              // Signal
#define XBAR_TRIGLATCH4_SD2FLT3_DRINT  0x20U       // Input Latch for SD2FLT3.DRINT
                                              // Signal
#define XBAR_TRIGLATCH4_SD2FLT4_COMPZ  0x40U       // Input Latch for SD2FLT4.COMPZ
                                              // Signal
#define XBAR_TRIGLATCH4_SD2FLT4_DRINT  0x80U       // Input Latch for SD2FLT4.DRINT
                                              // Signal
#define XBAR_TRIGLATCH4_CLB1_4_1  0x10000U    // Input Latch for CLB1_4.1
                                              // Signal
#define XBAR_TRIGLATCH4_CLB1_5_1  0x20000U    // Input Latch for CLB1_5.1
                                              // Signal
#define XBAR_TRIGLATCH4_CLB2_4_1  0x40000U    // Input Latch for CLB2_4.1
                                              // Signal
#define XBAR_TRIGLATCH4_CLB2_5_1  0x80000U    // Input Latch for CLB2_5.1
                                              // Signal
#define XBAR_TRIGLATCH4_CLB3_4_1  0x100000U   // Input Latch for CLB3_4.1
                                              // Signal
#define XBAR_TRIGLATCH4_CLB3_5_1  0x200000U   // Input Latch for CLB3_5.1
                                              // Signal
#define XBAR_TRIGLATCH4_CLB4_4_1  0x400000U   // Input Latch for CLB4_4.1
                                              // Signal
#define XBAR_TRIGLATCH4_CLB4_5_1  0x800000U   // Input Latch for CLB4_5.1
                                              // Signal
#define XBAR_TRIGLATCH4_CLAHALT   0x80000000U // Input Latch for CLAHALT
                                              // Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the TRIGLATCHCLR1 register
//
//*****************************************************************************
#define XBAR_TRIGLATCHCLR1_CMPSS0_CTRIPL  0x1U        // Input Latch Clear for
                                              // CMPSS0.CTRIPL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS0_CTRIPH  0x2U        // Input Latch Clear for
                                              // CMPSS0.CTRIPH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS1_CTRIPL  0x4U        // Input Latch Clear for
                                              // CMPSS1.CTRIPL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS1_CTRIPH  0x8U        // Input Latch Clear for
                                              // CMPSS1.CTRIPH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS2_CTRIPL  0x10U       // Input Latch Clear for
                                              // CMPSS2.CTRIPL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS2_CTRIPH  0x20U       // Input Latch Clear for
                                              // CMPSS2.CTRIPH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS3_CTRIPL  0x40U       // Input Latch Clear for
                                              // CMPSS3.CTRIPL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS3_CTRIPH  0x80U       // Input Latch Clear for
                                              // CMPSS3.CTRIPH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS4_CTRIPL  0x100U      // Input Latch Clear for
                                              // CMPSS4.CTRIPL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS4_CTRIPH  0x200U      // Input Latch Clear for
                                              // CMPSS4.CTRIPH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS5_CTRIPL  0x400U      // Input Latch Clear for
                                              // CMPSS5.CTRIPL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS5_CTRIPH  0x800U      // Input Latch Clear for
                                              // CMPSS5.CTRIPH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS6_CTRIPL  0x1000U     // Input Latch Clear for
                                              // CMPSS6.CTRIPL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS6_CTRIPH  0x2000U     // Input Latch Clear for
                                              // CMPSS6.CTRIPH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS7_CTRIPL  0x4000U     // Input Latch Clear for
                                              // CMPSS7.CTRIPL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS7_CTRIPH  0x8000U     // Input Latch Clear for
                                              // CMPSS7.CTRIPH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS0_CTRIPOUTL  0x10000U    // Input Latch Clear for
                                              // CMPSS0.CTRIPOUTL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS0_CTRIPOUTH  0x20000U    // Input Latch Clear for
                                              // CMPSS0.CTRIPOUTH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS1_CTRIPOUTL  0x40000U    // Input Latch Clear for
                                              // CMPSS1.CTRIPOUTL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS1_CTRIPOUTH  0x80000U    // Input Latch Clear for
                                              // CMPSS1.CTRIPOUTH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS2_CTRIPOUTL  0x100000U   // Input Latch Clear for
                                              // CMPSS2.CTRIPOUTL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS2_CTRIPOUTH  0x200000U   // Input Latch Clear for
                                              // CMPSS2.CTRIPOUTH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS3_CTRIPOUTL  0x400000U   // Input Latch Clear for
                                              // CMPSS3.CTRIPOUTL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS3_CTRIPOUTH  0x800000U   // Input Latch Clear for
                                              // CMPSS3.CTRIPOUTH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS4_CTRIPOUTL  0x1000000U  // Input Latch Clear for
                                              // CMPSS4.CTRIPOUTL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS4_CTRIPOUTH  0x2000000U  // Input Latch Clear for
                                              // CMPSS4.CTRIPOUTH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS5_CTRIPOUTL  0x4000000U  // Input Latch Clear for
                                              // CMPSS5.CTRIPOUTL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS5_CTRIPOUTH  0x8000000U  // Input Latch Clear for
                                              // CMPSS5.CTRIPOUTH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS6_CTRIPOUTL  0x10000000U // Input Latch Clear for
                                              // CMPSS6.CTRIPOUTL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS6_CTRIPOUTH  0x20000000U // Input Latch Clear for
                                              // CMPSS6.CTRIPOUTH Signal
#define XBAR_TRIGLATCHCLR1_CMPSS7_CTRIPOUTL  0x40000000U // Input Latch Clear for
                                              // CMPSS7.CTRIPOUTL Signal
#define XBAR_TRIGLATCHCLR1_CMPSS7_CTRIPOUTH  0x80000000U // Input Latch Clear for
                                              // CMPSS7.CTRIPOUTH Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the TRIGLATCHCLR2 register
//
//*****************************************************************************
#define XBAR_TRIGLATCHCLR2_INPUT1  0x1U        // Input Latch Clear for INPUT1
                                              // Signal
#define XBAR_TRIGLATCHCLR2_INPUT2  0x2U        // Input Latch Clear for INPUT2
                                              // Signal
#define XBAR_TRIGLATCHCLR2_INPUT3  0x4U        // Input Latch Clear for INPUT3
                                              // Signal
#define XBAR_TRIGLATCHCLR2_INPUT4  0x8U        // Input Latch Clear for INPUT4
                                              // Signal
#define XBAR_TRIGLATCHCLR2_INPUT5  0x10U       // Input Latch Clear for INPUT5
                                              // Signal
#define XBAR_TRIGLATCHCLR2_INPUT6  0x20U       // Input Latch Clear for INPUT6
                                              // Signal
#define XBAR_TRIGLATCHCLR2_ADCSOCA  0x40U       // Input Latch Clear for ADCSOCA
                                              // Signal
#define XBAR_TRIGLATCHCLR2_ADCSOCB  0x80U       // Input Latch Clear for ADCSOCB
                                              // Signal
#define XBAR_TRIGLATCHCLR2_ECAP1_OUT  0x10000U    // Input Latch Clear for
                                              // ECAP1.OUT Signal
#define XBAR_TRIGLATCHCLR2_ECAP2_OUT  0x20000U    // Input Latch Clear for
                                              // ECAP2.OUT Signal
#define XBAR_TRIGLATCHCLR2_ECAP3_OUT  0x40000U    // Input Latch Clear for
                                              // ECAP3.OUT Signal
#define XBAR_TRIGLATCHCLR2_ECAP4_OUT  0x80000U    // Input Latch Clear for
                                              // ECAP4.OUT Signal
#define XBAR_TRIGLATCHCLR2_ECAP5_OUT  0x100000U   // Input Latch Clear for
                                              // ECAP5.OUT Signal
#define XBAR_TRIGLATCHCLR2_ECAP6_OUT  0x200000U   // Input Latch Clear for
                                              // ECAP6.OUT Signal
#define XBAR_TRIGLATCHCLR2_EXTSYNCOUT  0x400000U   // Input Latch Clear for
                                              // EXTSYNCOUT Signal
#define XBAR_TRIGLATCHCLR2_ADCAEVT1  0x800000U   // Input Latch Clear for
                                              // ADCAEVT1 Signal
#define XBAR_TRIGLATCHCLR2_ADCAEVT2  0x1000000U  // Input Latch Clear for
                                              // ADCAEVT2 Signal
#define XBAR_TRIGLATCHCLR2_ADCAEVT3  0x2000000U  // Input Latch Clear for
                                              // ADCAEVT3 Signal
#define XBAR_TRIGLATCHCLR2_ADCAEVT4  0x4000000U  // Input Latch Clear for
                                              // ADCAEVT4 Signal
#define XBAR_TRIGLATCHCLR2_ADCBEVT1  0x8000000U  // Input Latch Clear for
                                              // ADCBEVT1 Signal
#define XBAR_TRIGLATCHCLR2_ADCBEVT2  0x10000000U // Input Latch Clear for
                                              // ADCBEVT2 Signal
#define XBAR_TRIGLATCHCLR2_ADCBEVT3  0x20000000U // Input Latch Clear for
                                              // ADCBEVT3 Signal
#define XBAR_TRIGLATCHCLR2_ADCBEVT4  0x40000000U // Input Latch Clear for
                                              // ADCBEVT4 Signal
#define XBAR_TRIGLATCHCLR2_ADCCEVT1  0x80000000U // Input Latch Clear for
                                              // ADCCEVT1 Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the TRIGLATCHCLR3 register
//
//*****************************************************************************
#define XBAR_TRIGLATCHCLR3_ADCCEVT2  0x1U        // Input Latch Clear for
                                              // ADCCEVT2 Signal
#define XBAR_TRIGLATCHCLR3_ADCCEVT3  0x2U        // Input Latch Clear for
                                              // ADCCEVT3 Signal
#define XBAR_TRIGLATCHCLR3_ADCCEVT4  0x4U        // Input Latch Clear for
                                              // ADCCEVT4 Signal
#define XBAR_TRIGLATCHCLR3_ADCDEVT1  0x8U        // Input Latch Clear for
                                              // ADCDEVT1 Signal
#define XBAR_TRIGLATCHCLR3_ADCDEVT2  0x10U       // Input Latch Clear for
                                              // ADCDEVT2 Signal
#define XBAR_TRIGLATCHCLR3_ADCDEVT3  0x20U       // Input Latch Clear for
                                              // ADCDEVT3 Signal
#define XBAR_TRIGLATCHCLR3_ADCDEVT4  0x40U       // Input Latch Clear for
                                              // ADCDEVT4 Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT1_COMPL  0x80U       // Input Latch Clear for
                                              // SD1FLT1.COMPL Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT1_COMPH  0x100U      // Input Latch Clear for
                                              // SD1FLT1.COMPH Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT2_COMPL  0x200U      // Input Latch Clear for
                                              // SD1FLT2.COMPL Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT2_COMPH  0x400U      // Input Latch Clear for
                                              // SD1FLT2.COMPH Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT3_COMPL  0x800U      // Input Latch Clear for
                                              // SD1FLT3.COMPL Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT3_COMPH  0x1000U     // Input Latch Clear for
                                              // SD1FLT3.COMPH Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT4_COMPL  0x2000U     // Input Latch Clear for
                                              // SD1FLT4.COMPL Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT4_COMPH  0x4000U     // Input Latch Clear for
                                              // SD1FLT4.COMPH Signal
#define XBAR_TRIGLATCHCLR3_SD2FLT1_COMPL  0x8000U     // Input Latch Clear for
                                              // SD2FLT1.COMPL Signal
#define XBAR_TRIGLATCHCLR3_SD2FLT1_COMPH  0x10000U    // Input Latch Clear for
                                              // SD2FLT1.COMPH Signal
#define XBAR_TRIGLATCHCLR3_SD2FLT2_COMPL  0x20000U    // Input Latch Clear for
                                              // SD2FLT2.COMPL Signal
#define XBAR_TRIGLATCHCLR3_SD2FLT2_COMPH  0x40000U    // Input Latch Clear for
                                              // SD2FLT2.COMPH Signal
#define XBAR_TRIGLATCHCLR3_SD2FLT3_COMPL  0x80000U    // Input Latch Clear for
                                              // SD2FLT3.COMPL Signal
#define XBAR_TRIGLATCHCLR3_SD2FLT3_COMPH  0x100000U   // Input Latch Clear for
                                              // SD2FLT3.COMPH Signal
#define XBAR_TRIGLATCHCLR3_SD2FLT4_COMPL  0x200000U   // Input Latch Clear for
                                              // SD2FLT4.COMPL Signal
#define XBAR_TRIGLATCHCLR3_SD2FLT4_COMPH  0x400000U   // Input Latch Clear for
                                              // SD2FLT4.COMPH Signal
#define XBAR_TRIGLATCHCLR3_ECAP7_OUT  0x800000U   // Input Latch clear for
                                              // ECAP7.OUT Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT1_COMPZ  0x1000000U  // Input Latch clear for
                                              // SD1FLT1.COMPZ Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT1_DRINT  0x2000000U  // Input Latch clear for
                                              // SD1FLT1.DRINT Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT2_COMPZ  0x4000000U  // Input Latch clear for
                                              // SD1FLT2.COMPZ Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT2_DRINT  0x8000000U  // Input Latch clear for
                                              // SD1FLT2.DRINT Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT3_COMPZ  0x10000000U // Input Latch clear for
                                              // SD1FLT3.COMPZ Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT3_DRINT  0x20000000U // Input Latch clear for
                                              // SD1FLT3.DRINT Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT4_COMPZ  0x40000000U // Input Latch clear for
                                              // SD1FLT4.COMPZ Signal
#define XBAR_TRIGLATCHCLR3_SD1FLT4_DRINT  0x80000000U // Input Latch clear for
                                              // SD1FLT4.DRINT Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the TRIGLATCHCLR4 register
//
//*****************************************************************************
#define XBAR_TRIGLATCHCLR4_SD2FLT1_COMPZ  0x1U        // Input Latch clear for
                                              // SD2FLT1.COMPZ Signal
#define XBAR_TRIGLATCHCLR4_SD2FLT1_DRINT  0x2U        // Input Latch clear for
                                              // SD2FLT1.DRINT Signal
#define XBAR_TRIGLATCHCLR4_SD2FLT2_COMPZ  0x4U        // Input Latch clear for
                                              // SD2FLT2.COMPZ Signal
#define XBAR_TRIGLATCHCLR4_SD2FLT2_DRINT  0x8U        // Input Latch clear for
                                              // SD2FLT2.DRINT Signal
#define XBAR_TRIGLATCHCLR4_SD2FLT3_COMPZ  0x10U       // Input Latch clear for
                                              // SD2FLT3.COMPZ Signal
#define XBAR_TRIGLATCHCLR4_SD2FLT3_DRINT  0x20U       // Input Latch clear for
                                              // SD2FLT3.DRINT Signal
#define XBAR_TRIGLATCHCLR4_SD2FLT4_COMPZ  0x40U       // Input Latch clear for
                                              // SD2FLT4.COMPZ Signal
#define XBAR_TRIGLATCHCLR4_SD2FLT4_DRINT  0x80U       // Input Latch clear for
                                              // SD2FLT4.DRINT Signal
#define XBAR_TRIGLATCHCLR4_CLB1_4_1  0x10000U    // Input Latch clear for
                                              // CLB1_4.1 Signal
#define XBAR_TRIGLATCHCLR4_CLB1_5_1  0x20000U    // Input Latch clear for
                                              // CLB1_5.1 Signal
#define XBAR_TRIGLATCHCLR4_CLB2_4_1  0x40000U    // Input Latch clear for
                                              // CLB2_4.1 Signal
#define XBAR_TRIGLATCHCLR4_CLB2_5_1  0x80000U    // Input Latch clear for
                                              // CLB2_5.1 Signal
#define XBAR_TRIGLATCHCLR4_CLB3_4_1  0x100000U   // Input Latch clear for
                                              // CLB3_4.1 Signal
#define XBAR_TRIGLATCHCLR4_CLB3_5_1  0x200000U   // Input Latch clear for
                                              // CLB3_5.1 Signal
#define XBAR_TRIGLATCHCLR4_CLB4_4_1  0x400000U   // Input Latch clear for
                                              // CLB4_4.1 Signal
#define XBAR_TRIGLATCHCLR4_CLB4_5_1  0x800000U   // Input Latch clear for
                                              // CLB4_5.1 Signal
#define XBAR_TRIGLATCHCLR4_CLAHALT  0x80000000U // Input Latch clear for CLAHALT
                                              // Signal
#endif
