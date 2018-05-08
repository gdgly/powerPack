//###########################################################################
//
// FILE:    hw_pga.h
//
// TITLE:   Definitions for the PGA registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __HW_PGA_H__
#define __HW_PGA_H__

//*****************************************************************************
//
// The following are defines for the PGA register offsets
//
//*****************************************************************************
#define PGA_O_CTL                 0x0U        // PGA Control Register
#define PGA_O_LOCK                0x2U        // PGA Lock Register
#define PGA_O_GAIN1TRIM           0x3U        // PGA Gain Trim Register for a
                                              // gain setting of 1
#define PGA_O_GAIN3TRIM           0x4U        // PGA Gain Trim Register for a
                                              // gain setting of 3
#define PGA_O_GAIN6TRIM           0x5U        // PGA Gain Trim Register for a
                                              // gain setting of 6
#define PGA_O_GAIN12TRIM          0x6U        // PGA Gain Trim Register for a
                                              // gain setting of 12
#define PGA_O_GAIN24TRIM          0x7U        // PGA Gain Trim Register for a
                                              // gain setting of 24
#define PGA_O_TYPE                0x8U        // PGA Type Register

//*****************************************************************************
//
// The following are defines for the bit fields in the PGACTL register
//
//*****************************************************************************
#define PGA_CTL_PGAEN             0x1U        // PGA Enable
#define PGA_CTL_FILTRESSEL_S      1U
#define PGA_CTL_FILTRESSEL_M      0x1EU       // Filter Resistor Select
#define PGA_CTL_GAIN_S            5U
#define PGA_CTL_GAIN_M            0xE0U       // PGA gain setting
#define PGA_CTL_NOISECTL_S        8U
#define PGA_CTL_NOISECTL_M        0xFF00U     // TBD

//*****************************************************************************
//
// The following are defines for the bit fields in the PGALOCK register
//
//*****************************************************************************
#define PGA_LOCK_PGACTL           0x1U        // "Lock bit for "&$B49&"."
#define PGA_LOCK_PGAGAIN1TRIM     0x2U        // "Lock bit for "&$B50&"."
#define PGA_LOCK_PGAGAIN3TRIM     0x4U        // "Lock bit for "&$B51&"."
#define PGA_LOCK_PGAGAIN6TRIM     0x8U        // "Lock bit for "&$B52&"."
#define PGA_LOCK_PGAGAIN12TRIM    0x10U       // "Lock bit for "&$B53&"."
#define PGA_LOCK_PGAGAIN24TRIM    0x20U       // "Lock bit for "&$B54&"."
#define PGA_LOCK_PGADFT           0x80U       // "Lock bit for "&$B56&"."

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAGAIN1TRIM register
//
//*****************************************************************************
#define PGA_GAIN1TRIM_GAINTRIM_S  0U
#define PGA_GAIN1TRIM_GAINTRIM_M  0xFFU       // Gain TRIM value, when gain
                                              // setting is 1
#define PGA_GAIN1TRIM_OFFSETTRIM_S  8U
#define PGA_GAIN1TRIM_OFFSETTRIM_M  0xFF00U     // OFFSET TRIM value, when Gain
                                              // setting is 1

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAGAIN3TRIM register
//
//*****************************************************************************
#define PGA_GAIN3TRIM_GAINTRIM_S  0U
#define PGA_GAIN3TRIM_GAINTRIM_M  0xFFU       // Gain TRIM value, when gain
                                              // setting is 3
#define PGA_GAIN3TRIM_OFFSETTRIM_S  8U
#define PGA_GAIN3TRIM_OFFSETTRIM_M  0xFF00U     // OFFSET TRIM value, when Gain
                                              // setting is 1

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAGAIN6TRIM register
//
//*****************************************************************************
#define PGA_GAIN6TRIM_GAINTRIM_S  0U
#define PGA_GAIN6TRIM_GAINTRIM_M  0xFFU       // Gain TRIM value, when gain
                                              // setting is 6
#define PGA_GAIN6TRIM_OFFSETTRIM_S  8U
#define PGA_GAIN6TRIM_OFFSETTRIM_M  0xFF00U     // OFFSET TRIM value, when Gain
                                              // setting is 1

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAGAIN12TRIM register
//
//*****************************************************************************
#define PGA_GAIN12TRIM_GAINTRIM_S  0U
#define PGA_GAIN12TRIM_GAINTRIM_M  0xFFU       // Gain TRIM value, when gain
                                              // setting is 12
#define PGA_GAIN12TRIM_OFFSETTRIM_S  8U
#define PGA_GAIN12TRIM_OFFSETTRIM_M  0xFF00U     // OFFSET TRIM value, when Gain
                                              // setting is 1

//*****************************************************************************
//
// The following are defines for the bit fields in the PGAGAIN24TRIM register
//
//*****************************************************************************
#define PGA_GAIN24TRIM_GAINTRIM_S  0U
#define PGA_GAIN24TRIM_GAINTRIM_M  0xFFU       // Gain TRIM value, when gain
                                              // setting is 24
#define PGA_GAIN24TRIM_OFFSETTRIM_S  8U
#define PGA_GAIN24TRIM_OFFSETTRIM_M  0xFF00U     // OFFSET TRIM value, when Gain
                                              // setting is 1

//*****************************************************************************
//
// The following are defines for the bit fields in the PGATYPE register
//
//*****************************************************************************
#define PGA_TYPE_REV_S            0U
#define PGA_TYPE_REV_M            0xFFU       // PGA Revision Field
#define PGA_TYPE_TYPE_S           8U
#define PGA_TYPE_TYPE_M           0xFF00U     // PGA Type Field
#endif
