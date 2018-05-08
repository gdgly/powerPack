//###########################################################################
//
// FILE:    hw_dac_t1.h
//
// TITLE:   Definitions for the DAC registers.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef __HW_DAC_T1_H__
#define __HW_DAC_T1_H__

//*****************************************************************************
//
// The following are defines for the DAC register offsets
//
//*****************************************************************************
#define DAC_O_REV                 0x0U        // DAC Revision Register
#define DAC_O_CTL                 0x1U        // DAC Control Register
#define DAC_O_VALA                0x2U        // DAC Value Register - Active
#define DAC_O_VALS                0x3U        // DAC Value Register - Shadow
#define DAC_O_OUTEN               0x4U        // DAC Output Enable Register
#define DAC_O_LOCK                0x5U        // DAC Lock Register
#define DAC_O_TRIM                0x6U        // DAC Trim Register

//*****************************************************************************
//
// The following are defines for the bit fields in the DACREV register
//
//*****************************************************************************
#define DAC_REV_REV_S             0U
#define DAC_REV_REV_M             0xFFU       // DAC Revision Register

//*****************************************************************************
//
// The following are defines for the bit fields in the DACCTL register
//
//*****************************************************************************
#define DAC_CTL_DACREFSEL         0x1U        // DAC Reference Select
#define DAC_CTL_LOADMODE          0x4U        // DACVALA Load Mode
#define DAC_CTL_SYNCSEL_S         4U
#define DAC_CTL_SYNCSEL_M         0xF0U       // DAC PWMSYNC Select

//*****************************************************************************
//
// The following are defines for the bit fields in the DACVALA register
//
//*****************************************************************************
#define DAC_VALA_DACVALA_S        0U
#define DAC_VALA_DACVALA_M        0xFFFU      // DAC Active Output Code

//*****************************************************************************
//
// The following are defines for the bit fields in the DACVALS register
//
//*****************************************************************************
#define DAC_VALS_DACVALS_S        0U
#define DAC_VALS_DACVALS_M        0xFFFU      // DAC Shadow Output Code

//*****************************************************************************
//
// The following are defines for the bit fields in the DACOUTEN register
//
//*****************************************************************************
#define DAC_OUTEN_DACOUTEN        0x1U        // DAC Output Code

//*****************************************************************************
//
// The following are defines for the bit fields in the DACLOCK register
//
//*****************************************************************************
#define DAC_LOCK_DACCTL           0x1U        // DAC Control Register Lock
#define DAC_LOCK_DACVAL           0x2U        // DAC Value Register Lock
#define DAC_LOCK_DACOUTEN         0x4U        // DAC Output Enable Register
                                              // Lock

//*****************************************************************************
//
// The following are defines for the bit fields in the DACTRIM register
//
//*****************************************************************************
#define DAC_TRIM_OFFSET_TRIM_S    0U
#define DAC_TRIM_OFFSET_TRIM_M    0xFFU       // DAC Offset Trim
#endif
