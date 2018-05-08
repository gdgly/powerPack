//###########################################################################
//
// FILE:    hw_pie.h
//
// TITLE:   Definitions for the PIE registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef __HW_PIE_H__
#define __HW_PIE_H__

//*****************************************************************************
//
// The following are defines for the PIECTRL register offsets
//
//*****************************************************************************
#define PIE_O_CTRL                0x0U        // Control Register
#define PIE_O_ACK                 0x1U        // Acknowledge Register
#define PIE_O_IER1                0x2U        // INT1 Group Enable Register
#define PIE_O_IFR1                0x3U        // INT1 Group Flag Register
#define PIE_O_IER2                0x4U        // INT2 Group Enable Register
#define PIE_O_IFR2                0x5U        // INT2 Group Flag Register
#define PIE_O_IER3                0x6U        // INT3 Group Enable Register
#define PIE_O_IFR3                0x7U        // INT3 Group Flag Register
#define PIE_O_IER4                0x8U        // INT4 Group Enable Register
#define PIE_O_IFR4                0x9U        // INT4 Group Flag Register
#define PIE_O_IER5                0xAU        // INT5 Group Enable Register
#define PIE_O_IFR5                0xBU        // INT5 Group Flag Register
#define PIE_O_IER6                0xCU        // INT6 Group Enable Register
#define PIE_O_IFR6                0xDU        // INT6 Group Flag Register
#define PIE_O_IER7                0xEU        // INT7 Group Enable Register
#define PIE_O_IFR7                0xFU        // INT7 Group Flag Register
#define PIE_O_IER8                0x10U       // INT8 Group Enable Register
#define PIE_O_IFR8                0x11U       // INT8 Group Flag Register
#define PIE_O_IER9                0x12U       // INT9 Group Enable Register
#define PIE_O_IFR9                0x13U       // INT9 Group Flag Register
#define PIE_O_IER10               0x14U       // INT10 Group Enable Register
#define PIE_O_IFR10               0x15U       // INT10 Group Flag Register
#define PIE_O_IER11               0x16U       // INT11 Group Enable Register
#define PIE_O_IFR11               0x17U       // INT11 Group Flag Register
#define PIE_O_IER12               0x18U       // INT12 Group Enable Register
#define PIE_O_IFR12               0x19U       // INT12 Group Flag Register

//*****************************************************************************
//
// The following are defines for the bit fields in the PIECTRL register
//
//*****************************************************************************
#define PIE_CTRL_ENPIE            0x1U        // PIE Enable
#define PIE_CTRL_PIEVECT_S        1U
#define PIE_CTRL_PIEVECT_M        0xFFFEU     // PIE Vector Address

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEACK register
//
//*****************************************************************************
#define PIE_ACK_ACK1              0x1U        // Acknowledge PIE Interrupt
                                              // Group 1
#define PIE_ACK_ACK2              0x2U        // Acknowledge PIE Interrupt
                                              // Group 2
#define PIE_ACK_ACK3              0x4U        // Acknowledge PIE Interrupt
                                              // Group 3
#define PIE_ACK_ACK4              0x8U        // Acknowledge PIE Interrupt
                                              // Group 4
#define PIE_ACK_ACK5              0x10U       // Acknowledge PIE Interrupt
                                              // Group 5
#define PIE_ACK_ACK6              0x20U       // Acknowledge PIE Interrupt
                                              // Group 6
#define PIE_ACK_ACK7              0x40U       // Acknowledge PIE Interrupt
                                              // Group 7
#define PIE_ACK_ACK8              0x80U       // Acknowledge PIE Interrupt
                                              // Group 8
#define PIE_ACK_ACK9              0x100U      // Acknowledge PIE Interrupt
                                              // Group 9
#define PIE_ACK_ACK10             0x200U      // Acknowledge PIE Interrupt
                                              // Group 10
#define PIE_ACK_ACK11             0x400U      // Acknowledge PIE Interrupt
                                              // Group 11
#define PIE_ACK_ACK12             0x800U      // Acknowledge PIE Interrupt
                                              // Group 12

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER1 register
//
//*****************************************************************************
#define PIE_IER1_INTX1            0x1U        // Interrupt Enable for INT1.1
#define PIE_IER1_INTX2            0x2U        // Interrupt Enable for INT1.2
#define PIE_IER1_INTX3            0x4U        // Interrupt Enable for INT1.3
#define PIE_IER1_INTX4            0x8U        // Interrupt Enable for INT1.4
#define PIE_IER1_INTX5            0x10U       // Interrupt Enable for INT1.5
#define PIE_IER1_INTX6            0x20U       // Interrupt Enable for INT1.6
#define PIE_IER1_INTX7            0x40U       // Interrupt Enable for INT1.7
#define PIE_IER1_INTX8            0x80U       // Interrupt Enable for INT1.8
#define PIE_IER1_INTX9            0x100U      // Interrupt Enable for INT1.9
#define PIE_IER1_INTX10           0x200U      // Interrupt Enable for INT1.10
#define PIE_IER1_INTX11           0x400U      // Interrupt Enable for INT1.11
#define PIE_IER1_INTX12           0x800U      // Interrupt Enable for INT1.12
#define PIE_IER1_INTX13           0x1000U     // Interrupt Enable for INT1.13
#define PIE_IER1_INTX14           0x2000U     // Interrupt Enable for INT1.14
#define PIE_IER1_INTX15           0x4000U     // Interrupt Enable for INT1.15
#define PIE_IER1_INTX16           0x8000U     // Interrupt Enable for INT1.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR1 register
//
//*****************************************************************************
#define PIE_IFR1_INTX1            0x1U        // Interrupt Flag for INT1.1
#define PIE_IFR1_INTX2            0x2U        // Interrupt Flag for INT1.2
#define PIE_IFR1_INTX3            0x4U        // Interrupt Flag for INT1.3
#define PIE_IFR1_INTX4            0x8U        // Interrupt Flag for INT1.4
#define PIE_IFR1_INTX5            0x10U       // Interrupt Flag for INT1.5
#define PIE_IFR1_INTX6            0x20U       // Interrupt Flag for INT1.6
#define PIE_IFR1_INTX7            0x40U       // Interrupt Flag for INT1.7
#define PIE_IFR1_INTX8            0x80U       // Interrupt Flag for INT1.8
#define PIE_IFR1_INTX9            0x100U      // Interrupt Flag for INT1.9
#define PIE_IFR1_INTX10           0x200U      // Interrupt Flag for INT1.10
#define PIE_IFR1_INTX11           0x400U      // Interrupt Flag for INT1.11
#define PIE_IFR1_INTX12           0x800U      // Interrupt Flag for INT1.12
#define PIE_IFR1_INTX13           0x1000U     // Interrupt Flag for INT1.13
#define PIE_IFR1_INTX14           0x2000U     // Interrupt Flag for INT1.14
#define PIE_IFR1_INTX15           0x4000U     // Interrupt Flag for INT1.15
#define PIE_IFR1_INTX16           0x8000U     // Interrupt Flag for INT1.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER2 register
//
//*****************************************************************************
#define PIE_IER2_INTX1            0x1U        // Interrupt Enable for INT2.1
#define PIE_IER2_INTX2            0x2U        // Interrupt Enable for INT2.2
#define PIE_IER2_INTX3            0x4U        // Interrupt Enable for INT2.3
#define PIE_IER2_INTX4            0x8U        // Interrupt Enable for INT2.4
#define PIE_IER2_INTX5            0x10U       // Interrupt Enable for INT2.5
#define PIE_IER2_INTX6            0x20U       // Interrupt Enable for INT2.6
#define PIE_IER2_INTX7            0x40U       // Interrupt Enable for INT2.7
#define PIE_IER2_INTX8            0x80U       // Interrupt Enable for INT2.8
#define PIE_IER2_INTX9            0x100U      // Interrupt Enable for INT2.9
#define PIE_IER2_INTX10           0x200U      // Interrupt Enable for INT2.10
#define PIE_IER2_INTX11           0x400U      // Interrupt Enable for INT2.11
#define PIE_IER2_INTX12           0x800U      // Interrupt Enable for INT2.12
#define PIE_IER2_INTX13           0x1000U     // Interrupt Enable for INT2.13
#define PIE_IER2_INTX14           0x2000U     // Interrupt Enable for INT2.14
#define PIE_IER2_INTX15           0x4000U     // Interrupt Enable for INT2.15
#define PIE_IER2_INTX16           0x8000U     // Interrupt Enable for INT2.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR2 register
//
//*****************************************************************************
#define PIE_IFR2_INTX1            0x1U        // Interrupt Flag for INT2.1
#define PIE_IFR2_INTX2            0x2U        // Interrupt Flag for INT2.2
#define PIE_IFR2_INTX3            0x4U        // Interrupt Flag for INT2.3
#define PIE_IFR2_INTX4            0x8U        // Interrupt Flag for INT2.4
#define PIE_IFR2_INTX5            0x10U       // Interrupt Flag for INT2.5
#define PIE_IFR2_INTX6            0x20U       // Interrupt Flag for INT2.6
#define PIE_IFR2_INTX7            0x40U       // Interrupt Flag for INT2.7
#define PIE_IFR2_INTX8            0x80U       // Interrupt Flag for INT2.8
#define PIE_IFR2_INTX9            0x100U      // Interrupt Flag for INT2.9
#define PIE_IFR2_INTX10           0x200U      // Interrupt Flag for INT2.10
#define PIE_IFR2_INTX11           0x400U      // Interrupt Flag for INT2.11
#define PIE_IFR2_INTX12           0x800U      // Interrupt Flag for INT2.12
#define PIE_IFR2_INTX13           0x1000U     // Interrupt Flag for INT2.13
#define PIE_IFR2_INTX14           0x2000U     // Interrupt Flag for INT2.14
#define PIE_IFR2_INTX15           0x4000U     // Interrupt Flag for INT2.15
#define PIE_IFR2_INTX16           0x8000U     // Interrupt Flag for INT2.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER3 register
//
//*****************************************************************************
#define PIE_IER3_INTX1            0x1U        // Interrupt Enable for INT3.1
#define PIE_IER3_INTX2            0x2U        // Interrupt Enable for INT3.2
#define PIE_IER3_INTX3            0x4U        // Interrupt Enable for INT3.3
#define PIE_IER3_INTX4            0x8U        // Interrupt Enable for INT3.4
#define PIE_IER3_INTX5            0x10U       // Interrupt Enable for INT3.5
#define PIE_IER3_INTX6            0x20U       // Interrupt Enable for INT3.6
#define PIE_IER3_INTX7            0x40U       // Interrupt Enable for INT3.7
#define PIE_IER3_INTX8            0x80U       // Interrupt Enable for INT3.8
#define PIE_IER3_INTX9            0x100U      // Interrupt Enable for INT3.9
#define PIE_IER3_INTX10           0x200U      // Interrupt Enable for INT3.10
#define PIE_IER3_INTX11           0x400U      // Interrupt Enable for INT3.11
#define PIE_IER3_INTX12           0x800U      // Interrupt Enable for INT3.12
#define PIE_IER3_INTX13           0x1000U     // Interrupt Enable for INT3.13
#define PIE_IER3_INTX14           0x2000U     // Interrupt Enable for INT3.14
#define PIE_IER3_INTX15           0x4000U     // Interrupt Enable for INT3.15
#define PIE_IER3_INTX16           0x8000U     // Interrupt Enable for INT3.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR3 register
//
//*****************************************************************************
#define PIE_IFR3_INTX1            0x1U        // Interrupt Flag for INT3.1
#define PIE_IFR3_INTX2            0x2U        // Interrupt Flag for INT3.2
#define PIE_IFR3_INTX3            0x4U        // Interrupt Flag for INT3.3
#define PIE_IFR3_INTX4            0x8U        // Interrupt Flag for INT3.4
#define PIE_IFR3_INTX5            0x10U       // Interrupt Flag for INT3.5
#define PIE_IFR3_INTX6            0x20U       // Interrupt Flag for INT3.6
#define PIE_IFR3_INTX7            0x40U       // Interrupt Flag for INT3.7
#define PIE_IFR3_INTX8            0x80U       // Interrupt Flag for INT3.8
#define PIE_IFR3_INTX9            0x100U      // Interrupt Flag for INT3.9
#define PIE_IFR3_INTX10           0x200U      // Interrupt Flag for INT3.10
#define PIE_IFR3_INTX11           0x400U      // Interrupt Flag for INT3.11
#define PIE_IFR3_INTX12           0x800U      // Interrupt Flag for INT3.12
#define PIE_IFR3_INTX13           0x1000U     // Interrupt Flag for INT3.13
#define PIE_IFR3_INTX14           0x2000U     // Interrupt Flag for INT3.14
#define PIE_IFR3_INTX15           0x4000U     // Interrupt Flag for INT3.15
#define PIE_IFR3_INTX16           0x8000U     // Interrupt Flag for INT3.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER4 register
//
//*****************************************************************************
#define PIE_IER4_INTX1            0x1U        // Interrupt Enable for INT4.1
#define PIE_IER4_INTX2            0x2U        // Interrupt Enable for INT4.2
#define PIE_IER4_INTX3            0x4U        // Interrupt Enable for INT4.3
#define PIE_IER4_INTX4            0x8U        // Interrupt Enable for INT4.4
#define PIE_IER4_INTX5            0x10U       // Interrupt Enable for INT4.5
#define PIE_IER4_INTX6            0x20U       // Interrupt Enable for INT4.6
#define PIE_IER4_INTX7            0x40U       // Interrupt Enable for INT4.7
#define PIE_IER4_INTX8            0x80U       // Interrupt Enable for INT4.8
#define PIE_IER4_INTX9            0x100U      // Interrupt Enable for INT4.9
#define PIE_IER4_INTX10           0x200U      // Interrupt Enable for INT4.10
#define PIE_IER4_INTX11           0x400U      // Interrupt Enable for INT4.11
#define PIE_IER4_INTX12           0x800U      // Interrupt Enable for INT4.12
#define PIE_IER4_INTX13           0x1000U     // Interrupt Enable for INT4.13
#define PIE_IER4_INTX14           0x2000U     // Interrupt Enable for INT4.14
#define PIE_IER4_INTX15           0x4000U     // Interrupt Enable for INT4.15
#define PIE_IER4_INTX16           0x8000U     // Interrupt Enable for INT4.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR4 register
//
//*****************************************************************************
#define PIE_IFR4_INTX1            0x1U        // Interrupt Flag for INT4.1
#define PIE_IFR4_INTX2            0x2U        // Interrupt Flag for INT4.2
#define PIE_IFR4_INTX3            0x4U        // Interrupt Flag for INT4.3
#define PIE_IFR4_INTX4            0x8U        // Interrupt Flag for INT4.4
#define PIE_IFR4_INTX5            0x10U       // Interrupt Flag for INT4.5
#define PIE_IFR4_INTX6            0x20U       // Interrupt Flag for INT4.6
#define PIE_IFR4_INTX7            0x40U       // Interrupt Flag for INT4.7
#define PIE_IFR4_INTX8            0x80U       // Interrupt Flag for INT4.8
#define PIE_IFR4_INTX9            0x100U      // Interrupt Flag for INT4.9
#define PIE_IFR4_INTX10           0x200U      // Interrupt Flag for INT4.10
#define PIE_IFR4_INTX11           0x400U      // Interrupt Flag for INT4.11
#define PIE_IFR4_INTX12           0x800U      // Interrupt Flag for INT4.12
#define PIE_IFR4_INTX13           0x1000U     // Interrupt Flag for INT4.13
#define PIE_IFR4_INTX14           0x2000U     // Interrupt Flag for INT4.14
#define PIE_IFR4_INTX15           0x4000U     // Interrupt Flag for INT4.15
#define PIE_IFR4_INTX16           0x8000U     // Interrupt Flag for INT4.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER5 register
//
//*****************************************************************************
#define PIE_IER5_INTX1            0x1U        // Interrupt Enable for INT5.1
#define PIE_IER5_INTX2            0x2U        // Interrupt Enable for INT5.2
#define PIE_IER5_INTX3            0x4U        // Interrupt Enable for INT5.3
#define PIE_IER5_INTX4            0x8U        // Interrupt Enable for INT5.4
#define PIE_IER5_INTX5            0x10U       // Interrupt Enable for INT5.5
#define PIE_IER5_INTX6            0x20U       // Interrupt Enable for INT5.6
#define PIE_IER5_INTX7            0x40U       // Interrupt Enable for INT5.7
#define PIE_IER5_INTX8            0x80U       // Interrupt Enable for INT5.8
#define PIE_IER5_INTX9            0x100U      // Interrupt Enable for INT5.9
#define PIE_IER5_INTX10           0x200U      // Interrupt Enable for INT5.10
#define PIE_IER5_INTX11           0x400U      // Interrupt Enable for INT5.11
#define PIE_IER5_INTX12           0x800U      // Interrupt Enable for INT5.12
#define PIE_IER5_INTX13           0x1000U     // Interrupt Enable for INT5.13
#define PIE_IER5_INTX14           0x2000U     // Interrupt Enable for INT5.14
#define PIE_IER5_INTX15           0x4000U     // Interrupt Enable for INT5.15
#define PIE_IER5_INTX16           0x8000U     // Interrupt Enable for INT5.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR5 register
//
//*****************************************************************************
#define PIE_IFR5_INTX1            0x1U        // Interrupt Flag for INT5.1
#define PIE_IFR5_INTX2            0x2U        // Interrupt Flag for INT5.2
#define PIE_IFR5_INTX3            0x4U        // Interrupt Flag for INT5.3
#define PIE_IFR5_INTX4            0x8U        // Interrupt Flag for INT5.4
#define PIE_IFR5_INTX5            0x10U       // Interrupt Flag for INT5.5
#define PIE_IFR5_INTX6            0x20U       // Interrupt Flag for INT5.6
#define PIE_IFR5_INTX7            0x40U       // Interrupt Flag for INT5.7
#define PIE_IFR5_INTX8            0x80U       // Interrupt Flag for INT5.8
#define PIE_IFR5_INTX9            0x100U      // Interrupt Flag for INT5.9
#define PIE_IFR5_INTX10           0x200U      // Interrupt Flag for INT5.10
#define PIE_IFR5_INTX11           0x400U      // Interrupt Flag for INT5.11
#define PIE_IFR5_INTX12           0x800U      // Interrupt Flag for INT5.12
#define PIE_IFR5_INTX13           0x1000U     // Interrupt Flag for INT5.13
#define PIE_IFR5_INTX14           0x2000U     // Interrupt Flag for INT5.14
#define PIE_IFR5_INTX15           0x4000U     // Interrupt Flag for INT5.15
#define PIE_IFR5_INTX16           0x8000U     // Interrupt Flag for INT5.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER6 register
//
//*****************************************************************************
#define PIE_IER6_INTX1            0x1U        // Interrupt Enable for INT6.1
#define PIE_IER6_INTX2            0x2U        // Interrupt Enable for INT6.2
#define PIE_IER6_INTX3            0x4U        // Interrupt Enable for INT6.3
#define PIE_IER6_INTX4            0x8U        // Interrupt Enable for INT6.4
#define PIE_IER6_INTX5            0x10U       // Interrupt Enable for INT6.5
#define PIE_IER6_INTX6            0x20U       // Interrupt Enable for INT6.6
#define PIE_IER6_INTX7            0x40U       // Interrupt Enable for INT6.7
#define PIE_IER6_INTX8            0x80U       // Interrupt Enable for INT6.8
#define PIE_IER6_INTX9            0x100U      // Interrupt Enable for INT6.9
#define PIE_IER6_INTX10           0x200U      // Interrupt Enable for INT6.10
#define PIE_IER6_INTX11           0x400U      // Interrupt Enable for INT6.11
#define PIE_IER6_INTX12           0x800U      // Interrupt Enable for INT6.12
#define PIE_IER6_INTX13           0x1000U     // Interrupt Enable for INT6.13
#define PIE_IER6_INTX14           0x2000U     // Interrupt Enable for INT6.14
#define PIE_IER6_INTX15           0x4000U     // Interrupt Enable for INT6.15
#define PIE_IER6_INTX16           0x8000U     // Interrupt Enable for INT6.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR6 register
//
//*****************************************************************************
#define PIE_IFR6_INTX1            0x1U        // Interrupt Flag for INT6.1
#define PIE_IFR6_INTX2            0x2U        // Interrupt Flag for INT6.2
#define PIE_IFR6_INTX3            0x4U        // Interrupt Flag for INT6.3
#define PIE_IFR6_INTX4            0x8U        // Interrupt Flag for INT6.4
#define PIE_IFR6_INTX5            0x10U       // Interrupt Flag for INT6.5
#define PIE_IFR6_INTX6            0x20U       // Interrupt Flag for INT6.6
#define PIE_IFR6_INTX7            0x40U       // Interrupt Flag for INT6.7
#define PIE_IFR6_INTX8            0x80U       // Interrupt Flag for INT6.8
#define PIE_IFR6_INTX9            0x100U      // Interrupt Flag for INT6.9
#define PIE_IFR6_INTX10           0x200U      // Interrupt Flag for INT6.10
#define PIE_IFR6_INTX11           0x400U      // Interrupt Flag for INT6.11
#define PIE_IFR6_INTX12           0x800U      // Interrupt Flag for INT6.12
#define PIE_IFR6_INTX13           0x1000U     // Interrupt Flag for INT6.13
#define PIE_IFR6_INTX14           0x2000U     // Interrupt Flag for INT6.14
#define PIE_IFR6_INTX15           0x4000U     // Interrupt Flag for INT6.15
#define PIE_IFR6_INTX16           0x8000U     // Interrupt Flag for INT6.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER7 register
//
//*****************************************************************************
#define PIE_IER7_INTX1            0x1U        // Interrupt Enable for INT7.1
#define PIE_IER7_INTX2            0x2U        // Interrupt Enable for INT7.2
#define PIE_IER7_INTX3            0x4U        // Interrupt Enable for INT7.3
#define PIE_IER7_INTX4            0x8U        // Interrupt Enable for INT7.4
#define PIE_IER7_INTX5            0x10U       // Interrupt Enable for INT7.5
#define PIE_IER7_INTX6            0x20U       // Interrupt Enable for INT7.6
#define PIE_IER7_INTX7            0x40U       // Interrupt Enable for INT7.7
#define PIE_IER7_INTX8            0x80U       // Interrupt Enable for INT7.8
#define PIE_IER7_INTX9            0x100U      // Interrupt Enable for INT7.9
#define PIE_IER7_INTX10           0x200U      // Interrupt Enable for INT7.10
#define PIE_IER7_INTX11           0x400U      // Interrupt Enable for INT7.11
#define PIE_IER7_INTX12           0x800U      // Interrupt Enable for INT7.12
#define PIE_IER7_INTX13           0x1000U     // Interrupt Enable for INT7.13
#define PIE_IER7_INTX14           0x2000U     // Interrupt Enable for INT7.14
#define PIE_IER7_INTX15           0x4000U     // Interrupt Enable for INT7.15
#define PIE_IER7_INTX16           0x8000U     // Interrupt Enable for INT7.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR7 register
//
//*****************************************************************************
#define PIE_IFR7_INTX1            0x1U        // Interrupt Flag for INT7.1
#define PIE_IFR7_INTX2            0x2U        // Interrupt Flag for INT7.2
#define PIE_IFR7_INTX3            0x4U        // Interrupt Flag for INT7.3
#define PIE_IFR7_INTX4            0x8U        // Interrupt Flag for INT7.4
#define PIE_IFR7_INTX5            0x10U       // Interrupt Flag for INT7.5
#define PIE_IFR7_INTX6            0x20U       // Interrupt Flag for INT7.6
#define PIE_IFR7_INTX7            0x40U       // Interrupt Flag for INT7.7
#define PIE_IFR7_INTX8            0x80U       // Interrupt Flag for INT7.8
#define PIE_IFR7_INTX9            0x100U      // Interrupt Flag for INT7.9
#define PIE_IFR7_INTX10           0x200U      // Interrupt Flag for INT7.10
#define PIE_IFR7_INTX11           0x400U      // Interrupt Flag for INT7.11
#define PIE_IFR7_INTX12           0x800U      // Interrupt Flag for INT7.12
#define PIE_IFR7_INTX13           0x1000U     // Interrupt Flag for INT7.13
#define PIE_IFR7_INTX14           0x2000U     // Interrupt Flag for INT7.14
#define PIE_IFR7_INTX15           0x4000U     // Interrupt Flag for INT7.15
#define PIE_IFR7_INTX16           0x8000U     // Interrupt Flag for INT7.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER8 register
//
//*****************************************************************************
#define PIE_IER8_INTX1            0x1U        // Interrupt Enable for INT8.1
#define PIE_IER8_INTX2            0x2U        // Interrupt Enable for INT8.2
#define PIE_IER8_INTX3            0x4U        // Interrupt Enable for INT8.3
#define PIE_IER8_INTX4            0x8U        // Interrupt Enable for INT8.4
#define PIE_IER8_INTX5            0x10U       // Interrupt Enable for INT8.5
#define PIE_IER8_INTX6            0x20U       // Interrupt Enable for INT8.6
#define PIE_IER8_INTX7            0x40U       // Interrupt Enable for INT8.7
#define PIE_IER8_INTX8            0x80U       // Interrupt Enable for INT8.8
#define PIE_IER8_INTX9            0x100U      // Interrupt Enable for INT8.9
#define PIE_IER8_INTX10           0x200U      // Interrupt Enable for INT8.10
#define PIE_IER8_INTX11           0x400U      // Interrupt Enable for INT8.11
#define PIE_IER8_INTX12           0x800U      // Interrupt Enable for INT8.12
#define PIE_IER8_INTX13           0x1000U     // Interrupt Enable for INT8.13
#define PIE_IER8_INTX14           0x2000U     // Interrupt Enable for INT8.14
#define PIE_IER8_INTX15           0x4000U     // Interrupt Enable for INT8.15
#define PIE_IER8_INTX16           0x8000U     // Interrupt Enable for INT8.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR8 register
//
//*****************************************************************************
#define PIE_IFR8_INTX1            0x1U        // Interrupt Flag for INT8.1
#define PIE_IFR8_INTX2            0x2U        // Interrupt Flag for INT8.2
#define PIE_IFR8_INTX3            0x4U        // Interrupt Flag for INT8.3
#define PIE_IFR8_INTX4            0x8U        // Interrupt Flag for INT8.4
#define PIE_IFR8_INTX5            0x10U       // Interrupt Flag for INT8.5
#define PIE_IFR8_INTX6            0x20U       // Interrupt Flag for INT8.6
#define PIE_IFR8_INTX7            0x40U       // Interrupt Flag for INT8.7
#define PIE_IFR8_INTX8            0x80U       // Interrupt Flag for INT8.8
#define PIE_IFR8_INTX9            0x100U      // Interrupt Flag for INT8.9
#define PIE_IFR8_INTX10           0x200U      // Interrupt Flag for INT8.10
#define PIE_IFR8_INTX11           0x400U      // Interrupt Flag for INT8.11
#define PIE_IFR8_INTX12           0x800U      // Interrupt Flag for INT8.12
#define PIE_IFR8_INTX13           0x1000U     // Interrupt Flag for INT8.13
#define PIE_IFR8_INTX14           0x2000U     // Interrupt Flag for INT8.14
#define PIE_IFR8_INTX15           0x4000U     // Interrupt Flag for INT8.15
#define PIE_IFR8_INTX16           0x8000U     // Interrupt Flag for INT8.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER9 register
//
//*****************************************************************************
#define PIE_IER9_INTX1            0x1U        // Interrupt Enable for INT9.1
#define PIE_IER9_INTX2            0x2U        // Interrupt Enable for INT9.2
#define PIE_IER9_INTX3            0x4U        // Interrupt Enable for INT9.3
#define PIE_IER9_INTX4            0x8U        // Interrupt Enable for INT9.4
#define PIE_IER9_INTX5            0x10U       // Interrupt Enable for INT9.5
#define PIE_IER9_INTX6            0x20U       // Interrupt Enable for INT9.6
#define PIE_IER9_INTX7            0x40U       // Interrupt Enable for INT9.7
#define PIE_IER9_INTX8            0x80U       // Interrupt Enable for INT9.8
#define PIE_IER9_INTX9            0x100U      // Interrupt Enable for INT9.9
#define PIE_IER9_INTX10           0x200U      // Interrupt Enable for INT9.10
#define PIE_IER9_INTX11           0x400U      // Interrupt Enable for INT9.11
#define PIE_IER9_INTX12           0x800U      // Interrupt Enable for INT9.12
#define PIE_IER9_INTX13           0x1000U     // Interrupt Enable for INT9.13
#define PIE_IER9_INTX14           0x2000U     // Interrupt Enable for INT9.14
#define PIE_IER9_INTX15           0x4000U     // Interrupt Enable for INT9.15
#define PIE_IER9_INTX16           0x8000U     // Interrupt Enable for INT9.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR9 register
//
//*****************************************************************************
#define PIE_IFR9_INTX1            0x1U        // Interrupt Flag for INT9.1
#define PIE_IFR9_INTX2            0x2U        // Interrupt Flag for INT9.2
#define PIE_IFR9_INTX3            0x4U        // Interrupt Flag for INT9.3
#define PIE_IFR9_INTX4            0x8U        // Interrupt Flag for INT9.4
#define PIE_IFR9_INTX5            0x10U       // Interrupt Flag for INT9.5
#define PIE_IFR9_INTX6            0x20U       // Interrupt Flag for INT9.6
#define PIE_IFR9_INTX7            0x40U       // Interrupt Flag for INT9.7
#define PIE_IFR9_INTX8            0x80U       // Interrupt Flag for INT9.8
#define PIE_IFR9_INTX9            0x100U      // Interrupt Flag for INT9.9
#define PIE_IFR9_INTX10           0x200U      // Interrupt Flag for INT9.10
#define PIE_IFR9_INTX11           0x400U      // Interrupt Flag for INT9.11
#define PIE_IFR9_INTX12           0x800U      // Interrupt Flag for INT9.12
#define PIE_IFR9_INTX13           0x1000U     // Interrupt Flag for INT9.13
#define PIE_IFR9_INTX14           0x2000U     // Interrupt Flag for INT9.14
#define PIE_IFR9_INTX15           0x4000U     // Interrupt Flag for INT9.15
#define PIE_IFR9_INTX16           0x8000U     // Interrupt Flag for INT9.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER10 register
//
//*****************************************************************************
#define PIE_IER10_INTX1           0x1U        // Interrupt Enable for INT10.1
#define PIE_IER10_INTX2           0x2U        // Interrupt Enable for INT10.2
#define PIE_IER10_INTX3           0x4U        // Interrupt Enable for INT10.3
#define PIE_IER10_INTX4           0x8U        // Interrupt Enable for INT10.4
#define PIE_IER10_INTX5           0x10U       // Interrupt Enable for INT10.5
#define PIE_IER10_INTX6           0x20U       // Interrupt Enable for INT10.6
#define PIE_IER10_INTX7           0x40U       // Interrupt Enable for INT10.7
#define PIE_IER10_INTX8           0x80U       // Interrupt Enable for INT10.8
#define PIE_IER10_INTX9           0x100U      // Interrupt Enable for INT10.9
#define PIE_IER10_INTX10          0x200U      // Interrupt Enable for INT10.10
#define PIE_IER10_INTX11          0x400U      // Interrupt Enable for INT10.11
#define PIE_IER10_INTX12          0x800U      // Interrupt Enable for INT10.12
#define PIE_IER10_INTX13          0x1000U     // Interrupt Enable for INT10.13
#define PIE_IER10_INTX14          0x2000U     // Interrupt Enable for INT10.14
#define PIE_IER10_INTX15          0x4000U     // Interrupt Enable for INT10.15
#define PIE_IER10_INTX16          0x8000U     // Interrupt Enable for INT10.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR10 register
//
//*****************************************************************************
#define PIE_IFR10_INTX1           0x1U        // Interrupt Flag for INT10.1
#define PIE_IFR10_INTX2           0x2U        // Interrupt Flag for INT10.2
#define PIE_IFR10_INTX3           0x4U        // Interrupt Flag for INT10.3
#define PIE_IFR10_INTX4           0x8U        // Interrupt Flag for INT10.4
#define PIE_IFR10_INTX5           0x10U       // Interrupt Flag for INT10.5
#define PIE_IFR10_INTX6           0x20U       // Interrupt Flag for INT10.6
#define PIE_IFR10_INTX7           0x40U       // Interrupt Flag for INT10.7
#define PIE_IFR10_INTX8           0x80U       // Interrupt Flag for INT10.8
#define PIE_IFR10_INTX9           0x100U      // Interrupt Flag for INT10.9
#define PIE_IFR10_INTX10          0x200U      // Interrupt Flag for INT10.10
#define PIE_IFR10_INTX11          0x400U      // Interrupt Flag for INT10.11
#define PIE_IFR10_INTX12          0x800U      // Interrupt Flag for INT10.12
#define PIE_IFR10_INTX13          0x1000U     // Interrupt Flag for INT10.13
#define PIE_IFR10_INTX14          0x2000U     // Interrupt Flag for INT10.14
#define PIE_IFR10_INTX15          0x4000U     // Interrupt Flag for INT10.15
#define PIE_IFR10_INTX16          0x8000U     // Interrupt Flag for INT10.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER11 register
//
//*****************************************************************************
#define PIE_IER11_INTX1           0x1U        // Interrupt Enable for INT11.1
#define PIE_IER11_INTX2           0x2U        // Interrupt Enable for INT11.2
#define PIE_IER11_INTX3           0x4U        // Interrupt Enable for INT11.3
#define PIE_IER11_INTX4           0x8U        // Interrupt Enable for INT11.4
#define PIE_IER11_INTX5           0x10U       // Interrupt Enable for INT11.5
#define PIE_IER11_INTX6           0x20U       // Interrupt Enable for INT11.6
#define PIE_IER11_INTX7           0x40U       // Interrupt Enable for INT11.7
#define PIE_IER11_INTX8           0x80U       // Interrupt Enable for INT11.8
#define PIE_IER11_INTX9           0x100U      // Interrupt Enable for INT11.9
#define PIE_IER11_INTX10          0x200U      // Interrupt Enable for INT11.10
#define PIE_IER11_INTX11          0x400U      // Interrupt Enable for INT11.11
#define PIE_IER11_INTX12          0x800U      // Interrupt Enable for INT11.12
#define PIE_IER11_INTX13          0x1000U     // Interrupt Enable for INT11.13
#define PIE_IER11_INTX14          0x2000U     // Interrupt Enable for INT11.14
#define PIE_IER11_INTX15          0x4000U     // Interrupt Enable for INT11.15
#define PIE_IER11_INTX16          0x8000U     // Interrupt Enable for INT11.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR11 register
//
//*****************************************************************************
#define PIE_IFR11_INTX1           0x1U        // Interrupt Flag for INT11.1
#define PIE_IFR11_INTX2           0x2U        // Interrupt Flag for INT11.2
#define PIE_IFR11_INTX3           0x4U        // Interrupt Flag for INT11.3
#define PIE_IFR11_INTX4           0x8U        // Interrupt Flag for INT11.4
#define PIE_IFR11_INTX5           0x10U       // Interrupt Flag for INT11.5
#define PIE_IFR11_INTX6           0x20U       // Interrupt Flag for INT11.6
#define PIE_IFR11_INTX7           0x40U       // Interrupt Flag for INT11.7
#define PIE_IFR11_INTX8           0x80U       // Interrupt Flag for INT11.8
#define PIE_IFR11_INTX9           0x100U      // Interrupt Flag for INT11.9
#define PIE_IFR11_INTX10          0x200U      // Interrupt Flag for INT11.10
#define PIE_IFR11_INTX11          0x400U      // Interrupt Flag for INT11.11
#define PIE_IFR11_INTX12          0x800U      // Interrupt Flag for INT11.12
#define PIE_IFR11_INTX13          0x1000U     // Interrupt Flag for INT11.13
#define PIE_IFR11_INTX14          0x2000U     // Interrupt Flag for INT11.14
#define PIE_IFR11_INTX15          0x4000U     // Interrupt Flag for INT11.15
#define PIE_IFR11_INTX16          0x8000U     // Interrupt Flag for INT11.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIER12 register
//
//*****************************************************************************
#define PIE_IER12_INTX1           0x1U        // Interrupt Enable for INT12.1
#define PIE_IER12_INTX2           0x2U        // Interrupt Enable for INT12.2
#define PIE_IER12_INTX3           0x4U        // Interrupt Enable for INT12.3
#define PIE_IER12_INTX4           0x8U        // Interrupt Enable for INT12.4
#define PIE_IER12_INTX5           0x10U       // Interrupt Enable for INT12.5
#define PIE_IER12_INTX6           0x20U       // Interrupt Enable for INT12.6
#define PIE_IER12_INTX7           0x40U       // Interrupt Enable for INT12.7
#define PIE_IER12_INTX8           0x80U       // Interrupt Enable for INT12.8
#define PIE_IER12_INTX9           0x100U      // Interrupt Enable for INT12.9
#define PIE_IER12_INTX10          0x200U      // Interrupt Enable for INT12.10
#define PIE_IER12_INTX11          0x400U      // Interrupt Enable for INT12.11
#define PIE_IER12_INTX12          0x800U      // Interrupt Enable for INT12.12
#define PIE_IER12_INTX13          0x1000U     // Interrupt Enable for INT12.13
#define PIE_IER12_INTX14          0x2000U     // Interrupt Enable for INT12.14
#define PIE_IER12_INTX15          0x4000U     // Interrupt Enable for INT12.15
#define PIE_IER12_INTX16          0x8000U     // Interrupt Enable for INT12.16

//*****************************************************************************
//
// The following are defines for the bit fields in the PIEIFR12 register
//
//*****************************************************************************
#define PIE_IFR12_INTX1           0x1U        // Interrupt Flag for INT12.1
#define PIE_IFR12_INTX2           0x2U        // Interrupt Flag for INT12.2
#define PIE_IFR12_INTX3           0x4U        // Interrupt Flag for INT12.3
#define PIE_IFR12_INTX4           0x8U        // Interrupt Flag for INT12.4
#define PIE_IFR12_INTX5           0x10U       // Interrupt Flag for INT12.5
#define PIE_IFR12_INTX6           0x20U       // Interrupt Flag for INT12.6
#define PIE_IFR12_INTX7           0x40U       // Interrupt Flag for INT12.7
#define PIE_IFR12_INTX8           0x80U       // Interrupt Flag for INT12.8
#define PIE_IFR12_INTX9           0x100U      // Interrupt Flag for INT12.9
#define PIE_IFR12_INTX10          0x200U      // Interrupt Flag for INT12.10
#define PIE_IFR12_INTX11          0x400U      // Interrupt Flag for INT12.11
#define PIE_IFR12_INTX12          0x800U      // Interrupt Flag for INT12.12
#define PIE_IFR12_INTX13          0x1000U     // Interrupt Flag for INT12.13
#define PIE_IFR12_INTX14          0x2000U     // Interrupt Flag for INT12.14
#define PIE_IFR12_INTX15          0x4000U     // Interrupt Flag for INT12.15
#define PIE_IFR12_INTX16          0x8000U     // Interrupt Flag for INT12.16
#endif
