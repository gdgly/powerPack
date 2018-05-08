//###########################################################################
//
// FILE:    hw_trigxbar.h
//
// TITLE:   Definitions for the XBAR registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef __HW_TRIGXBAR_H__
#define __HW_TRIGXBAR_H__

//*****************************************************************************
//
// The following are defines for the Trig XBAR register offsets
//
//*****************************************************************************
#define XBAR_O_SYNCSELECT         0x0U        // Sync Input and Output Select
                                              // Register
#define XBAR_O_EXTADCSOCSELECT    0x2U        // External ADCSOC Select
                                              // Register
#define XBAR_O_SYNCSOCLOCK        0x4U        // SYNCSEL and EXTADCSOC Select
                                              // Lock register

//*****************************************************************************
//
// The following are defines for the bit fields in the SYNCSELECT register
//
//*****************************************************************************
#define XBAR_SYNCSELECT_EPWM4SYNCIN_S  0U
#define XBAR_SYNCSELECT_EPWM4SYNCIN_M  0x7U        // Selects Sync Input Source for
                                              // EPWM4
#define XBAR_SYNCSELECT_EPWM7SYNCIN_S  3U
#define XBAR_SYNCSELECT_EPWM7SYNCIN_M  0x38U       // Selects Sync Input Source for
                                              // EPWM7
#define XBAR_SYNCSELECT_EPWM10SYNCIN_S  6U
#define XBAR_SYNCSELECT_EPWM10SYNCIN_M  0x1C0U      // Selects Sync Input Source for
                                              // EPWM10
#define XBAR_SYNCSELECT_ECAP1SYNCIN_S  9U
#define XBAR_SYNCSELECT_ECAP1SYNCIN_M  0xE00U      // Selects Sync Input Source for
                                              // ECAP1
#define XBAR_SYNCSELECT_ECAP4SYNCIN_S  12U
#define XBAR_SYNCSELECT_ECAP4SYNCIN_M  0x7000U     // Selects Sync Input Source for
                                              // ECAP4
#define XBAR_SYNCSELECT_ECAP6SYNCIN_S  15U
#define XBAR_SYNCSELECT_ECAP6SYNCIN_M  0x38000U    // Selects Sync Input Source for
                                              // ECAP6
#define XBAR_SYNCSELECT_SYNCOUT_S  27U
#define XBAR_SYNCSELECT_SYNCOUT_M  0x18000000U // Select Syncout Source

//*****************************************************************************
//
// The following are defines for the bit fields in the EXTADCSOCSELECT register
//
//*****************************************************************************
#define XBAR_EXTADCSOCSELECT_PWM1SOCAEN  0x1U        // PWM1SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM2SOCAEN  0x2U        // PWM2SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM3SOCAEN  0x4U        // PWM3SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM4SOCAEN  0x8U        // PWM4SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM5SOCAEN  0x10U       // PWM5SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM6SOCAEN  0x20U       // PWM6SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM7SOCAEN  0x40U       // PWM7SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM8SOCAEN  0x80U       // PWM8SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM9SOCAEN  0x100U      // PWM9SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM10SOCAEN  0x200U      // PWM10SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM11SOCAEN  0x400U      // PWM11SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM12SOCAEN  0x800U      // PWM12SOCAEN Enable for
                                              // ADCSOCAOn
#define XBAR_EXTADCSOCSELECT_PWM1SOCBEN  0x10000U    // PWM1SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM2SOCBEN  0x20000U    // PWM2SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM3SOCBEN  0x40000U    // PWM3SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM4SOCBEN  0x80000U    // PWM4SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM5SOCBEN  0x100000U   // PWM5SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM6SOCBEN  0x200000U   // PWM6SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM7SOCBEN  0x400000U   // PWM7SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM8SOCBEN  0x800000U   // PWM8SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM9SOCBEN  0x1000000U  // PWM9SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM10SOCBEN  0x2000000U  // PWM10SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM11SOCBEN  0x4000000U  // PWM11SOCBEN Enable for
                                              // ADCSOCBOn
#define XBAR_EXTADCSOCSELECT_PWM12SOCBEN  0x8000000U  // PWM12SOCBEN Enable for
                                              // ADCSOCBOn

//*****************************************************************************
//
// The following are defines for the bit fields in the SYNCSOCLOCK register
//
//*****************************************************************************
#define XBAR_SYNCSOCLOCK_SYNCSELECT  0x1U        // SYNCSEL Register Lock bit
#define XBAR_SYNCSOCLOCK_EXTADCSOCSELECT  0x2U        // EXTADCSOCSEL Register Lock
                                              // bit
#endif
