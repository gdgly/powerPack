//###########################################################################
//
// FILE:   sysctl.h
//
// TITLE:  C28x system control driver.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright: $
//###########################################################################

#ifndef __SYSCTL_H__
#define __SYSCTL_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup sysctl_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nmi.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
//
// Defines for system control functions. Not intended for use by application
// code.
//
//*****************************************************************************
// Shifted pattern for WDCR register's WDCHK field.
#define SYSCTL_WD_CHKBITS       0x0028U

// Keys for WDKEY field. The first enables resets and the second resets.
#define SYSCTL_WD_ENRSTKEY      0x0055U
#define SYSCTL_WD_RSTKEY        0x00AAU

// Values to help decode peripheral parameter
#define SYSCTL_PERIPH_REG_M     0x001FU
#define SYSCTL_PERIPH_REG_S     0x0000U
#define SYSCTL_PERIPH_BIT_M     0x1F00U
#define SYSCTL_PERIPH_BIT_S     0x0008U

// LPM defines for LPMCR.LPM
#define SYSCTL_LPM_IDLE         0x0000U
#define SYSCTL_LPM_STANDBY      0x0001U
#define SYSCTL_LPM_HALT         0x0002U

// Generic Peripheral Access Control bit field defines
#define SYSCTL_PERIPH_AC_CPU1_ACC_S  0U
#define SYSCTL_PERIPH_AC_CPU1_ACC_M  0x3U
#define SYSCTL_PERIPH_AC_CLA1_ACC_S  2U
#define SYSCTL_PERIPH_AC_CLA1_ACC_M  0xCU
#define SYSCTL_PERIPH_AC_DMA1_ACC_S  4U
#define SYSCTL_PERIPH_AC_DMA1_ACC_M  0x30U

// Default internal oscillator frequency, 10 MHz
#define SYSCTL_DEFAULT_OSC_FREQ      10000000U

//*****************************************************************************
//
//! Macro to call SysCtl_delay() to achieve a delay in microseconds. The macro
//! will convert the desired delay in microseconds to the count value expected
//! by the function. \b x is the number of microseconds to delay and \b f is
//! the SYSCLK rate in Hz.
//
//*****************************************************************************
#define SYSCTL_DELAY_US(x, f)                                                 \
    SysCtl_delay(((((long double)(x)) / (1000000.0L / (long double)(f))) - 9.0L) / 5.0L)

//*****************************************************************************
//
// The following are values that can be passed to the SysCtl_setClock() API as
// the config parameter.
//
//*****************************************************************************
// System clock divider (SYSDIV)
#define SYSCTL_SYSDIV_M     0x00001F80U // Mask for SYSDIV value in config
#define SYSCTL_SYSDIV_S     7U          // Shift for SYSDIV value in config
//! Macro to format system clock divider value. x must be 1 or even values up
//! to 126.
#define SYSCTL_SYSDIV(x)    ((((x) / 2U) << SYSCTL_SYSDIV_S) & SYSCTL_SYSDIV_M)

// Integer multiplier (IMULT)
#define SYSCTL_IMULT_M      0x0000007FU // Mask for IMULT value in config
#define SYSCTL_IMULT_S      0U          // Shift for IMULT value in config
//! Macro to format integer multiplier value. x is a number from 1 to 127.
#define SYSCTL_IMULT(x)     (((x) << SYSCTL_IMULT_S) & SYSCTL_IMULT_M)

// Fractional multiplier (FMULT)
#define SYSCTL_FMULT_M      0x00006000U // Mask for FMULT value in config
#define SYSCTL_FMULT_S      13U         // Shift for FMULT value in config
#define SYSCTL_FMULT_NONE   0x00000000U //!< No fractional multiplier
#define SYSCTL_FMULT_0      0x00000000U //!< No fractional multiplier
#define SYSCTL_FMULT_1_4    0x00002000U //!< Fractional multiplier of 0.25
#define SYSCTL_FMULT_1_2    0x00004000U //!< Fractional multiplier of 0.50
#define SYSCTL_FMULT_3_4    0x00006000U //!< Fractional multiplier of 0.75

// Oscillator source
// Also used with the SysCtl_selectOscSource(), SysCtl_turnOnOsc(),
// and SysCtl_turnOffOsc() functions as the oscSource parameter.
#define SYSCTL_OSCSRC_M         0x00030000U // Mask for OSCSRC value in config
#define SYSCTL_OSCSRC_S         16U         // Shift for OSCSRC value in config
//! Internal oscillator INTOSC2
#define SYSCTL_OSCSRC_OSC2      0x00000000U
//! External oscillator (XTAL) in crystal mode
#define SYSCTL_OSCSRC_XTAL      0x00010000U
//! External oscillator (XTAL) in single-ended mode
#define SYSCTL_OSCSRC_XTAL_SE   0x00030000U
//! Internal oscillator INTOSC1
#define SYSCTL_OSCSRC_OSC1      0x00020000U

// Enable/disable PLL
#define SYSCTL_PLL_ENABLE   0x80000000U //!< Enable PLL
#define SYSCTL_PLL_DISABLE  0x00000000U //!< Disable PLL

//*****************************************************************************
//
// Values that can be passed to SysCtl_clearNMIStatus(),
// SysCtl_forceNMIFlags(), SysCtl_isNMIFlagSet(), and
// SysCtl_isNMIShadowFlagSet() as the nmiFlags parameter and returned by
// SysCtl_getNMIFlagStatus() and SysCtl_getNMIShadowFlagStatus().
//
//*****************************************************************************
#define SYSCTL_NMI_NMIINT           0x0001U //!< Non-maskable interrupt
#define SYSCTL_NMI_CLOCKFAIL        0x0002U //!< Clock Failure
#define SYSCTL_NMI_RAMUNCERR        0x0004U //!< Uncorrectable RAM error
#define SYSCTL_NMI_FLUNCERR         0x0008U //!< Uncorrectable Flash error
#define SYSCTL_NMI_SWERR            0x2000U //!< SW Error Force NMI Flag

//*****************************************************************************
//
// The following are values that can be passed to the SysCtl_clearResetCause()
// API as rstCauses or returned by the SysCtl_getResetCause() API.
//
//*****************************************************************************
#define SYSCTL_CAUSE_POR            0x0001U //!< Power-on reset
#define SYSCTL_CAUSE_XRS            0x0002U //!< External reset pin
#define SYSCTL_CAUSE_WDRS           0x0004U //!< Watchdog reset
#define SYSCTL_CAUSE_NMIWDRS        0x0008U //!< NMI watchdog reset
#define SYSCTL_CAUSE_SCCRESET       0x0100U //!< SCCRESETn reset from DCSM

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_enablePeripheral()
//! and SysCtl_disablePeripheral() as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    // PCLKCR0
    SYSCTL_PERIPH_CLK_CLA1       = 0x0000,
    SYSCTL_PERIPH_CLK_DMA        = 0x0200,
    SYSCTL_PERIPH_CLK_TIMER0     = 0x0300,
    SYSCTL_PERIPH_CLK_TIMER1     = 0x0400,
    SYSCTL_PERIPH_CLK_TIMER2     = 0x0500,
    SYSCTL_PERIPH_CLK_HRPWM      = 0x1000,
    SYSCTL_PERIPH_CLK_TBCLKSYNC  = 0x1200,

    // PCLKCR1
    // Reserved

    // PCLKCR2
    SYSCTL_PERIPH_CLK_EPWM1      = 0x0002,
    SYSCTL_PERIPH_CLK_EPWM2      = 0x0102,
    SYSCTL_PERIPH_CLK_EPWM3      = 0x0202,
    SYSCTL_PERIPH_CLK_EPWM4      = 0x0302,
    SYSCTL_PERIPH_CLK_EPWM5      = 0x0402,
    SYSCTL_PERIPH_CLK_EPWM6      = 0x0502,
    SYSCTL_PERIPH_CLK_EPWM7      = 0x0602,
    SYSCTL_PERIPH_CLK_EPWM8      = 0x0702,

    // PCLKCR3
    SYSCTL_PERIPH_CLK_ECAP1      = 0x0003,
    SYSCTL_PERIPH_CLK_ECAP2      = 0x0103,
    SYSCTL_PERIPH_CLK_ECAP3      = 0x0203,
    SYSCTL_PERIPH_CLK_ECAP4      = 0x0303,
    SYSCTL_PERIPH_CLK_ECAP5      = 0x0403,
    SYSCTL_PERIPH_CLK_ECAP6      = 0x0503,
    SYSCTL_PERIPH_CLK_ECAP7      = 0x0603,

    // PCLKCR4
    SYSCTL_PERIPH_CLK_EQEP1      = 0x0004,
    SYSCTL_PERIPH_CLK_EQEP2      = 0x0104,

    // PCLKCR5
    // Reserved

    // PCLKCR6
    SYSCTL_PERIPH_CLK_SD1        = 0x0006,

    // PCLKCR7
    SYSCTL_PERIPH_CLK_SCIA       = 0x0007,
    SYSCTL_PERIPH_CLK_SCIB       = 0x0107,

    // PCLKCR8
    SYSCTL_PERIPH_CLK_SPIA       = 0x0008,
    SYSCTL_PERIPH_CLK_SPIB       = 0x0108,

    // PCLKCR9
    SYSCTL_PERIPH_CLK_I2CA       = 0x0009,

    // PCLKCR10
    SYSCTL_PERIPH_CLK_CANA       = 0x000A,
    SYSCTL_PERIPH_CLK_CANB       = 0x010A,

    // PCLKCR11
    // Reserved

    // PCLKCR12
    // Reserved

    // PCLKCR13
    SYSCTL_PERIPH_CLK_ADCA       = 0x000D,
    SYSCTL_PERIPH_CLK_ADCB       = 0x010D,
    SYSCTL_PERIPH_CLK_ADCC       = 0x020D,

    // PCLKCR14
    SYSCTL_PERIPH_CLK_CMPSS1     = 0x000E,
    SYSCTL_PERIPH_CLK_CMPSS2     = 0x010E,
    SYSCTL_PERIPH_CLK_CMPSS3     = 0x020E,
    SYSCTL_PERIPH_CLK_CMPSS4     = 0x030E,
    SYSCTL_PERIPH_CLK_CMPSS5     = 0x040E,
    SYSCTL_PERIPH_CLK_CMPSS6     = 0x050E,
    SYSCTL_PERIPH_CLK_CMPSS7     = 0x060E,
    SYSCTL_PERIPH_CLK_CMPSS8     = 0x070E,

    // PCLKCR15
    SYSCTL_PERIPH_CLK_PGA1       = 0x000F,
    SYSCTL_PERIPH_CLK_PGA2       = 0x010F,
    SYSCTL_PERIPH_CLK_PGA3       = 0x020F,
    SYSCTL_PERIPH_CLK_PGA4       = 0x030F,
    SYSCTL_PERIPH_CLK_PGA5       = 0x040F,
    SYSCTL_PERIPH_CLK_PGA6       = 0x050F,
    SYSCTL_PERIPH_CLK_PGA7       = 0x060F,

    // PCLKCR16
    SYSCTL_PERIPH_CLK_DACA       = 0x1010,
    SYSCTL_PERIPH_CLK_DACB       = 0x1110,
    SYSCTL_PERIPH_CLK_DACC       = 0x1210,

    // PCLKCR17
    SYSCTL_PERIPH_CLK_CLB1       = 0x0011,
    SYSCTL_PERIPH_CLK_CLB2       = 0x0111,
    SYSCTL_PERIPH_CLK_CLB3       = 0x0211,
    SYSCTL_PERIPH_CLK_CLB4       = 0x0311,

    // PCLKCR18
    SYSCTL_PERIPH_CLK_FSITXA     = 0x0012,
    SYSCTL_PERIPH_CLK_FSIRXA     = 0x0112,

    // PCLKCR19
    SYSCTL_PERIPH_CLK_LINA       = 0x0013,

    // PCLKCR20
    SYSCTL_PERIPH_CLK_PMBUSA     = 0x0014,

    // PCLKCR21
    SYSCTL_PERIPH_CLK_DCC0       = 0x0015
} SysCtl_PeripheralPCLOCKCR;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_resetPeripheral() as
//! the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    // SOFTPRES0
    SYSCTL_PERIPH_RES_CLA1       = 0x0000,

    // SOFTPRES1
    // Reserved

    // SOFTPRES2
    SYSCTL_PERIPH_RES_EPWM1      = 0x0002,
    SYSCTL_PERIPH_RES_EPWM2      = 0x0102,
    SYSCTL_PERIPH_RES_EPWM3      = 0x0202,
    SYSCTL_PERIPH_RES_EPWM4      = 0x0302,
    SYSCTL_PERIPH_RES_EPWM5      = 0x0402,
    SYSCTL_PERIPH_RES_EPWM6      = 0x0502,
    SYSCTL_PERIPH_RES_EPWM7      = 0x0602,
    SYSCTL_PERIPH_RES_EPWM8      = 0x0702,

    // SOFTPRES3
    SYSCTL_PERIPH_RES_ECAP1      = 0x0003,
    SYSCTL_PERIPH_RES_ECAP2      = 0x0103,
    SYSCTL_PERIPH_RES_ECAP3      = 0x0203,
    SYSCTL_PERIPH_RES_ECAP4      = 0x0303,
    SYSCTL_PERIPH_RES_ECAP5      = 0x0403,
    SYSCTL_PERIPH_RES_ECAP6      = 0x0503,
    SYSCTL_PERIPH_RES_ECAP7      = 0x0603,

    // SOFTPRES4
    SYSCTL_PERIPH_RES_EQEP1      = 0x0004,
    SYSCTL_PERIPH_RES_EQEP2      = 0x0104,

    // SOFTPRES5
    // Reserved

    // SOFTPRES6
    SYSCTL_PERIPH_RES_SD1        = 0x0006,

    // SOFTPRES7
    SYSCTL_PERIPH_RES_SCIA       = 0x0007,
    SYSCTL_PERIPH_RES_SCIB       = 0x0107,

    // SOFTPRES8
    SYSCTL_PERIPH_RES_SPIA       = 0x0008,
    SYSCTL_PERIPH_RES_SPIB       = 0x0108,

    // SOFTPRES9
    SYSCTL_PERIPH_RES_I2CA       = 0x0009,

    // SOFTPRES10
    SYSCTL_PERIPH_RES_CANA       = 0x000A,
    SYSCTL_PERIPH_RES_CANB       = 0x010A,

    // SOFTPRES11
    // Reserved

    // SOFTPRES12
    // Reserved

    // SOFTPRES13
    SYSCTL_PERIPH_RES_ADCA       = 0x000D,
    SYSCTL_PERIPH_RES_ADCB       = 0x010D,
    SYSCTL_PERIPH_RES_ADCC       = 0x020D,

    // SOFTPRES14
    SYSCTL_PERIPH_RES_CMPSS1     = 0x000E,
    SYSCTL_PERIPH_RES_CMPSS2     = 0x010E,
    SYSCTL_PERIPH_RES_CMPSS3     = 0x020E,
    SYSCTL_PERIPH_RES_CMPSS4     = 0x030E,
    SYSCTL_PERIPH_RES_CMPSS5     = 0x040E,
    SYSCTL_PERIPH_RES_CMPSS6     = 0x050E,
    SYSCTL_PERIPH_RES_CMPSS7     = 0x060E,

    // SOFTPRES15
    SYSCTL_PERIPH_RES_PGA1       = 0x000F,
    SYSCTL_PERIPH_RES_PGA2       = 0x010F,
    SYSCTL_PERIPH_RES_PGA3       = 0x020F,
    SYSCTL_PERIPH_RES_PGA4       = 0x030F,
    SYSCTL_PERIPH_RES_PGA5       = 0x040F,
    SYSCTL_PERIPH_RES_PGA6       = 0x050F,
    SYSCTL_PERIPH_RES_PGA7       = 0x060F,

    // SOFTPRES16
    SYSCTL_PERIPH_RES_DACA       = 0x1010,
    SYSCTL_PERIPH_RES_DACB       = 0x1110,

    // SOFTPRES17
    SYSCTL_PERIPH_RES_CLB1       = 0x0011,
    SYSCTL_PERIPH_RES_CLB2       = 0x0111,
    SYSCTL_PERIPH_RES_CLB3       = 0x0211,
    SYSCTL_PERIPH_RES_CLB4       = 0x0311,

    // SOFTPRES18
    SYSCTL_PERIPH_RES_FSITXA     = 0x0012,
    SYSCTL_PERIPH_RES_FSIRXA     = 0x0112,

    // SOFTPRES19
    SYSCTL_PERIPH_RES_LINA       = 0x0013,

    // SOFTPRES20
    SYSCTL_PERIPH_RES_PMBUSA     = 0x0014,

    // SOFTPRES21
    SYSCTL_PERIPH_RES_DCC0       = 0x0015
} SysCtl_PeripheralSOFTPRES;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_isPeripheralPresent()
//! as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    // DC0
    // Reserved

    // DC1
    SYSCTL_PERIPH_PRESENT_FPU_TMU = 0x0000,
    SYSCTL_PERIPH_PRESENT_VCU     = 0x0200,
    SYSCTL_PERIPH_PRESENT_CLA1    = 0x0600,

    // DC2
    // Reserved

    // DC3
    SYSCTL_PERIPH_PRESENT_EPWM1  = 0x0002,
    SYSCTL_PERIPH_PRESENT_EPWM2  = 0x0102,
    SYSCTL_PERIPH_PRESENT_EPWM3  = 0x0202,
    SYSCTL_PERIPH_PRESENT_EPWM4  = 0x0302,
    SYSCTL_PERIPH_PRESENT_EPWM5  = 0x0402,
    SYSCTL_PERIPH_PRESENT_EPWM6  = 0x0502,
    SYSCTL_PERIPH_PRESENT_EPWM7  = 0x0602,
    SYSCTL_PERIPH_PRESENT_EPWM8  = 0x0702,

    // DC4
    SYSCTL_PERIPH_PRESENT_ECAP1  = 0x0003,
    SYSCTL_PERIPH_PRESENT_ECAP2  = 0x0103,
    SYSCTL_PERIPH_PRESENT_ECAP3  = 0x0203,
    SYSCTL_PERIPH_PRESENT_ECAP4  = 0x0303,
    SYSCTL_PERIPH_PRESENT_ECAP5  = 0x0403,
    SYSCTL_PERIPH_PRESENT_ECAP6  = 0x0503,
    SYSCTL_PERIPH_PRESENT_ECAP7  = 0x0603,

    // DC5
    SYSCTL_PERIPH_PRESENT_EQEP1  = 0x0004,
    SYSCTL_PERIPH_PRESENT_EQEP2  = 0x0104,

    // DC6
    // Reserved

    // DC7
    SYSCTL_PERIPH_PRESENT_SD1    = 0x0006,

    // DC8
    SYSCTL_PERIPH_PRESENT_SCIA   = 0x0007,
    SYSCTL_PERIPH_PRESENT_SCIB   = 0x0107,

    // DC9
    SYSCTL_PERIPH_PRESENT_SPIA   = 0x0008,
    SYSCTL_PERIPH_PRESENT_SPIB   = 0x0108,

    // DC10
    SYSCTL_PERIPH_PRESENT_I2CA   = 0x0009,

    // DC11
    SYSCTL_PERIPH_PRESENT_CANA   = 0x000A,
    SYSCTL_PERIPH_PRESENT_CANB   = 0x010A,

    // DC12
    // Reserved

    // DC13
    // Reserved

    // DC14
    SYSCTL_PERIPH_PRESENT_ADCA   = 0x000D,
    SYSCTL_PERIPH_PRESENT_ADCB   = 0x010D,
    SYSCTL_PERIPH_PRESENT_ADCC   = 0x020D,

    // DC15
    SYSCTL_PERIPH_PRESENT_CMPSS1 = 0x000E,
    SYSCTL_PERIPH_PRESENT_CMPSS2 = 0x010E,
    SYSCTL_PERIPH_PRESENT_CMPSS3 = 0x020E,
    SYSCTL_PERIPH_PRESENT_CMPSS4 = 0x030E,
    SYSCTL_PERIPH_PRESENT_CMPSS5 = 0x040E,
    SYSCTL_PERIPH_PRESENT_CMPSS6 = 0x050E,
    SYSCTL_PERIPH_PRESENT_CMPSS7 = 0x060E,

    // DC16
    SYSCTL_PERIPH_PRESENT_PGA1   = 0x000F,
    SYSCTL_PERIPH_PRESENT_PGA2   = 0x010F,
    SYSCTL_PERIPH_PRESENT_PGA3   = 0x020F,
    SYSCTL_PERIPH_PRESENT_PGA4   = 0x030F,
    SYSCTL_PERIPH_PRESENT_PGA5   = 0x040F,
    SYSCTL_PERIPH_PRESENT_PGA6   = 0x050F,
    SYSCTL_PERIPH_PRESENT_PGA7   = 0x060F,

    // DC17
    SYSCTL_PERIPH_PRESENT_DACA   = 0x1010,
    SYSCTL_PERIPH_PRESENT_DACB   = 0x1110,

    // DC18
    SYSCTL_PERIPH_PRESENT_LS0_1  = 0x0011,
    SYSCTL_PERIPH_PRESENT_LS1_1  = 0x0111,
    SYSCTL_PERIPH_PRESENT_LS2_1  = 0x0211,
    SYSCTL_PERIPH_PRESENT_LS3_1  = 0x0311,
    SYSCTL_PERIPH_PRESENT_LS4_1  = 0x0411,
    SYSCTL_PERIPH_PRESENT_LS5_1  = 0x0511,
    SYSCTL_PERIPH_PRESENT_LS6_1  = 0x0611,
    SYSCTL_PERIPH_PRESENT_LS7_1  = 0x0711,

    // DC19
    SYSCTL_PERIPH_PRESENT_LS0_2  = 0x0012,
    SYSCTL_PERIPH_PRESENT_LS1_2  = 0x0112,
    SYSCTL_PERIPH_PRESENT_LS2_2  = 0x0212,
    SYSCTL_PERIPH_PRESENT_LS3_2  = 0x0312,
    SYSCTL_PERIPH_PRESENT_LS4_2  = 0x0412,
    SYSCTL_PERIPH_PRESENT_LS5_2  = 0x0512,

    // DC20
    SYSCTL_PERIPH_PRESENT_GS0    = 0x0013,
    SYSCTL_PERIPH_PRESENT_GS1    = 0x0113,
    SYSCTL_PERIPH_PRESENT_GS2    = 0x0213,
    SYSCTL_PERIPH_PRESENT_GS3    = 0x0313,

    // DC21
    SYSCTL_PERIPH_PRESENT_CLB1   = 0x0014,
    SYSCTL_PERIPH_PRESENT_CLB2   = 0x0114,
    SYSCTL_PERIPH_PRESENT_CLB3   = 0x0214,
    SYSCTL_PERIPH_PRESENT_CLB4   = 0x0314,

    // DC22
    SYSCTL_PERIPH_PRESENT_FSITXA = 0x0015,
    SYSCTL_PERIPH_PRESENT_FSIRXA = 0x0115,

    // DC23
    SYSCTL_PERIPH_PRESENT_LINA   = 0x0016,

    // DC24
    SYSCTL_PERIPH_PRESENT_PMBUSA = 0x0017,

    // DC25
    SYSCTL_PERIPH_PRESENT_DCCA   = 0x0018
} SysCtl_PeripheralDC;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogPredivider() as the \e predivider parameter.
//
//*****************************************************************************
typedef enum
{
    //! PREDIVCLK = INTOSC1 / 2
    SYSCTL_WD_PREDIV_2    = (0x8U << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 4
    SYSCTL_WD_PREDIV_4    = (0x9U << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 8
    SYSCTL_WD_PREDIV_8    = (0xAU << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 16
    SYSCTL_WD_PREDIV_16   = (0xBU << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 32
    SYSCTL_WD_PREDIV_32   = (0xCU << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 64
    SYSCTL_WD_PREDIV_64   = (0xDU << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 128
    SYSCTL_WD_PREDIV_128  = (0xEU << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 256
    SYSCTL_WD_PREDIV_256  = (0xFU << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 512
    SYSCTL_WD_PREDIV_512  = (0x0U << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 1024
    SYSCTL_WD_PREDIV_1024 = (0x1U << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 2048
    SYSCTL_WD_PREDIV_2048 = (0x2U << SYSCTL_WDCR_WDPRECLKDIV_S),
    //! PREDIVCLK = INTOSC1 / 4096
    SYSCTL_WD_PREDIV_4096 = (0x3U << SYSCTL_WDCR_WDPRECLKDIV_S)
} SysCtl_WDPredivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogPrescaler() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_WD_PRESCALE_1  = 1,      //!< WDCLK = PREDIVCLK / 1
    SYSCTL_WD_PRESCALE_2  = 2,      //!< WDCLK = PREDIVCLK / 2
    SYSCTL_WD_PRESCALE_4  = 3,      //!< WDCLK = PREDIVCLK / 4
    SYSCTL_WD_PRESCALE_8  = 4,      //!< WDCLK = PREDIVCLK / 8
    SYSCTL_WD_PRESCALE_16 = 5,      //!< WDCLK = PREDIVCLK / 16
    SYSCTL_WD_PRESCALE_32 = 6,      //!< WDCLK = PREDIVCLK / 32
    SYSCTL_WD_PRESCALE_64 = 7       //!< WDCLK = PREDIVCLK / 64
} SysCtl_WDPrescaler;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogMode() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    //! Watchdog can generate a reset signal
    SYSCTL_WD_MODE_RESET,
    //! Watchdog can generate an interrupt signal; reset signal is disabled
    SYSCTL_WD_MODE_INTERRUPT
} SysCtl_WDMode;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setLowSpeedClock() as
//! the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_LSPCLK_PRESCALE_1,       //!< LSPCLK = SYSCLK / 1
    SYSCTL_LSPCLK_PRESCALE_2,       //!< LSPCLK = SYSCLK / 2
    SYSCTL_LSPCLK_PRESCALE_4,       //!< LSPCLK = SYSCLK / 4 (default)
    SYSCTL_LSPCLK_PRESCALE_6,       //!< LSPCLK = SYSCLK / 6
    SYSCTL_LSPCLK_PRESCALE_8,       //!< LSPCLK = SYSCLK / 8
    SYSCTL_LSPCLK_PRESCALE_10,      //!< LSPCLK = SYSCLK / 10
    SYSCTL_LSPCLK_PRESCALE_12,      //!< LSPCLK = SYSCLK / 12
    SYSCTL_LSPCLK_PRESCALE_14       //!< LSPCLK = SYSCLK / 14
} SysCtl_LSPCLKPrescaler;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setPeripheralAccessControl() and SysCtl_getPeripheralAccessControl()
//! as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    // ADC
    SYSCTL_ACCESS_ADCA            = 0x0,
    SYSCTL_ACCESS_ADCB            = 0x2,
    SYSCTL_ACCESS_ADCC            = 0x4,

    // CMPSS
    SYSCTL_ACCESS_CMPSS1          = 0x10,
    SYSCTL_ACCESS_CMPSS2          = 0x12,
    SYSCTL_ACCESS_CMPSS3          = 0x14,
    SYSCTL_ACCESS_CMPSS4          = 0x16,
    SYSCTL_ACCESS_CMPSS5          = 0x18,
    SYSCTL_ACCESS_CMPSS6          = 0x1A,
    SYSCTL_ACCESS_CMPSS7          = 0x1C,

    // DAC
    SYSCTL_ACCESS_DACA            = 0x28,
    SYSCTL_ACCESS_DACB            = 0x2A,

    // PGA
    SYSCTL_ACCESS_PGAA            = 0x38,
    SYSCTL_ACCESS_PGAB            = 0x3A,
    SYSCTL_ACCESS_PGAC            = 0x3C,
    SYSCTL_ACCESS_PGAD            = 0x3E,
    SYSCTL_ACCESS_PGAE            = 0x40,
    SYSCTL_ACCESS_PGAF            = 0x42,
    SYSCTL_ACCESS_PGAG            = 0x44,

    // EPWM
    SYSCTL_ACCESS_EPWM1           = 0x48,
    SYSCTL_ACCESS_EPWM2           = 0x4A,
    SYSCTL_ACCESS_EPWM3           = 0x4C,
    SYSCTL_ACCESS_EPWM4           = 0x4E,
    SYSCTL_ACCESS_EPWM5           = 0x50,
    SYSCTL_ACCESS_EPWM6           = 0x52,
    SYSCTL_ACCESS_EPWM7           = 0x54,
    SYSCTL_ACCESS_EPWM8           = 0x56,

    // EQEP
    SYSCTL_ACCESS_EQEP1           = 0x70,
    SYSCTL_ACCESS_EQEP2           = 0x72,

    // ECAP
    SYSCTL_ACCESS_ECAP1           = 0x80,
    SYSCTL_ACCESS_ECAP2           = 0x82,
    SYSCTL_ACCESS_ECAP3           = 0x84,
    SYSCTL_ACCESS_ECAP4           = 0x86,
    SYSCTL_ACCESS_ECAP5           = 0x88,
    SYSCTL_ACCESS_ECAP6           = 0x8A,
    SYSCTL_ACCESS_ECAP7           = 0x8C,

    // SDFM
    SYSCTL_ACCESS_SDFM1           = 0xA8,

    // CLB
    SYSCTL_ACCESS_CLB1            = 0xB0,
    SYSCTL_ACCESS_CLB2            = 0xB2,
    SYSCTL_ACCESS_CLB3            = 0xB4,
    SYSCTL_ACCESS_CLB4            = 0xB6,

    // CLA1PROMCRC
    SYSCTL_ACCESS_CLA1PROMCRC     = 0xC0,

    // SPI
    SYSCTL_ACCESS_SPIA            = 0x110,
    SYSCTL_ACCESS_SPIB            = 0x112,

    // PMBUS
    SYSCTL_ACCESS_PMBUS_A         = 0x130,

    // LIN
    SYSCTL_ACCESS_LIN_A           = 0x138,

    // CAN
    SYSCTL_ACCESS_CANA            = 0x140,
    SYSCTL_ACCESS_CANB            = 0x142,

    // FSI
    SYSCTL_ACCESS_FSIATX          = 0x158,
    SYSCTL_ACCESS_FSIARX          = 0x15A,

    // HRPWM
    SYSCTL_ACCESS_HRPWM_A         = 0x1AA
} SysCtl_AccessPeripheral;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setPeripheralAccessControl() and SysCtl_getPeripheralAccessControl()
//! as the \e master parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_ACCESS_CPU1  = 0U,
    SYSCTL_ACCESS_CLA1  = 2U,
    SYSCTL_ACCESS_DMA1  = 4U
} SysCtl_AccessMaster;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setPeripheralAccessControl() as the \e permission parameter.
//
//*****************************************************************************
typedef enum
{
    //! Full Access for both read and write.
    SYSCTL_ACCESS_FULL      = 3U,
    //! Protected RD access such that FIFOs. Clear on read, registers are not
    //! changed and no write access.
    SYSCTL_ACCESS_PROTECTED = 2U,
    //! No read or write access.
    SYSCTL_ACCESS_NONE      = 0U
} SysCtl_AccessPermission;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_selectClockOutSource() as the \e source parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CLOCKOUT_PLLSYS  = 0U,   //!< PLL System Clock
    SYSCTL_CLOCKOUT_PLLRAW  = 1U,   //!< PLL Raw Clock
    SYSCTL_CLOCKOUT_SYSCLK  = 2U,   //!< CPU System Clock
    SYSCTL_CLOCKOUT_INTOSC1 = 5U,   //!< Internal Oscillator 1
    SYSCTL_CLOCKOUT_INTOSC2 = 6U,   //!< Internal Oscillator 2
    SYSCTL_CLOCKOUT_XTALOSC = 7U    //!< External Oscillator
} SysCtl_ClockOut;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setExternalOscMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_XTALMODE_CRYSTAL = 1U,   //!< XTAL Oscillator Crystal Mode
    SYSCTL_XTALMODE_SINGLE  = 2U    //!< XTAL Oscillator Single-Ended Mode
} SysCtl_ExternalOscMode;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Resets a peripheral
//!
//! \param peripheral is the peripheral to reset.
//!
//! This function uses the SOFTPRESx registers to reset a specified peripheral.
//! Module registers will be returned to their reset states.
//!
//! \note This includes registers containing trim values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_resetPeripheral(SysCtl_PeripheralSOFTPRES peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = 2U * ((uint16_t)peripheral & SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    EALLOW;

    //
    // Sets the appropriate reset bit and then clears it.
    //
    HWREG(DEVCFG_BASE + SYSCTL_O_SOFTPRES0 + regIndex) |=
        ((uint32_t)1U << bitIndex);
    HWREG(DEVCFG_BASE + SYSCTL_O_SOFTPRES0 + regIndex) &=
        ~((uint32_t)1U << bitIndex);

    EDIS;
}

//*****************************************************************************
//
//! Enables a peripheral.
//!
//! \param peripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = 2U * ((uint16_t)peripheral & SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    EALLOW;

    //
    // Turn on the module clock.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_PCLKCR0 + regIndex) |=
        ((uint32_t)1U << bitIndex);
    EDIS;
}

//*****************************************************************************
//
//! Disables a peripheral.
//!
//! \param peripheral is the peripheral to disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = 2U * ((uint16_t)peripheral & SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    EALLOW;

    //
    // Turn off the module clock.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_PCLKCR0 + regIndex) &=
        ~((uint32_t)1U << bitIndex);
    EDIS;
}

//*****************************************************************************
//
//! Determines if a peripheral is present.
//!
//! \param peripheral is the peripheral in question.
//!
//! This function determines if a particular peripheral is present in the
//! device.  Each member of the family has a different peripheral
//! set; this function determines which peripherals are present on this device.
//!
//! \note This function may return \b true for a peripheral that is present on
//! the device but is not usable in any practical way because of the
//! availability of GPIO pins on the package.
//!
//! \return Returns \b true if the specified peripheral is present and \b false
//! if it is not.
//
//*****************************************************************************
static inline bool
SysCtl_isPeripheralPresent(SysCtl_PeripheralDC peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;
    bool status = false;

    //
    // Decode the peripheral variable.
    //
    regIndex = 2U * ((uint16_t)peripheral & SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    //
    // Read the appropriate DC register and peripheral bit and return.
    //
    if((HWREG(DEVCFG_BASE + SYSCTL_O_DC1 + regIndex) &
       ((uint32_t)1U << bitIndex)) != 0U)
    {
        status = true;
    }

    return(status);
}

//*****************************************************************************
//
//! Resets the device.
//!
//! This function performs a watchdog reset of the device.
//!
//! \return This function does not return.
//
//*****************************************************************************
static inline void
SysCtl_resetDevice(void)
{
    //
    // Write an incorrect check value to the watchdog control register
    // This will cause a device reset
    //
    EALLOW;

    // Enable the watchdog
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = SYSCTL_WD_CHKBITS;

    // Write a bad check value
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = 0U;

    EDIS;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
//! Gets the reason for a reset.
//!
//! This function will return the reason(s) for a reset.  Since the reset
//! reasons are sticky until either cleared by software or an external reset,
//! multiple reset reasons may be returned if multiple resets have occurred.
//! The reset reason will be a logical OR of \b SYSCTL_CAUSE_POR,
//! \b SYSCTL_CAUSE_XRS, \b SYSCTL_CAUSE_WDRS, \b SYSCTL_CAUSE_NMIWDRS,
//! and/or \b SYSCTL_CAUSE_SCCRESET.
//!
//! \return Returns the reason(s) for a reset.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getResetCause(void)
{
    //
    // Return the reset reasons.
    //
    return(HWREG(CPUSYS_BASE + SYSCTL_O_RESC) &
           (uint32_t)(SYSCTL_RESC_POR | SYSCTL_RESC_XRSN | SYSCTL_RESC_WDRSN |
                      SYSCTL_RESC_NMIWDRSN | SYSCTL_RESC_SCCRESETN));
}

//*****************************************************************************
//
//! Clears reset reasons.
//!
//! \param rstCauses are the reset causes to be cleared; must be a logical
//! OR of \b SYSCTL_CAUSE_POR, \b SYSCTL_CAUSE_XRS, \b SYSCTL_CAUSE_WDRS,
//! \b SYSCTL_CAUSE_NMIWDRS, and/or \b SYSCTL_CAUSE_SCCRESET.
//!
//! This function clears the specified sticky reset reasons.  Once cleared,
//! another reset for the same reason can be detected, and a reset for a
//! different reason can be distinguished (instead of having two reset causes
//! set).  If the reset reason is used by an application, all reset causes
//! should be cleared after they are retrieved with SysCtl_getResetCause().
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearResetCause(uint32_t rstCauses)
{
    //
    // Clear the given reset reasons.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_RESCCLR) |= rstCauses;
}

//*****************************************************************************
//
//! Sets the low speed peripheral clock rate prescaler.
//!
//! \param prescaler is the LSPCLK rate relative to SYSCLK
//!
//! This function configures the clock rate of the low speed peripherals. The
//! \e prescaler parameter is the value by which the SYSCLK rate is divided to
//! get the LSPCLK rate. For example, a \e prescaler of
//! \b SYSCTL_LSPCLK_PRESCALE_4 will result in a LSPCLK rate that is a quarter
//! of the SYSCLK rate.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setLowSpeedClock(SysCtl_LSPCLKPrescaler prescaler)
{
    //
    // Write the divider selection to the appropriate register.
    //
    EALLOW;
    HWREG(CLKCFG_BASE + SYSCTL_O_LOSPCP) =
        (HWREG(CLKCFG_BASE + SYSCTL_O_LOSPCP) & ~SYSCTL_LOSPCP_LSPCLKDIV_M) |
        (uint32_t)prescaler;
    EDIS;
}

//*****************************************************************************
//
//! Selects a clock source to mux to an external GPIO pin (XCLKOUT).
//!
//! \param source is the internal clock source to be configured.
//!
//! This function configures the specified clock source to be muxed to an
//! external clock out (XCLKOUT) GPIO pin. The \e source parameter may take a
//! value of \b SYSCTL_CLOCKOUT_PLLSYS, \b SYSCTL_CLOCKOUT_PLLRAW,
//! \b SYSCTL_CLOCKOUT_SYSCLK, \b SYSCTL_CLOCKOUT_INTOSC1,
//! \b SYSCTL_CLOCKOUT_INTOSC2, or \b SYSCTL_CLOCKOUT_XTALOSC.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_selectClockOutSource(SysCtl_ClockOut source)
{
    EALLOW;

    //
    // Clear clock out source
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL3) &=
        ~SYSCTL_CLKSRCCTL3_XCLKOUTSEL_M;

    //
    // Set clock out source
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL3) |= (uint16_t)source;

    EDIS;
}

//*****************************************************************************
//
//! Set the external oscillator mode.
//!
//! \param mode is the external oscillator mode to be configured.
//!
//! This function sets the external oscillator mode specified by the \e mode
//! parameter which may take one of two values:
//! - \b SYSCTL_XTALMODE_CRYSTAL - Crystal Mode
//! - \b SYSCTL_XTALMODE_SINGLE  - Single-Ended Mode
//!
//! \note The external oscillator must be powered off before this configuration
//! can be performed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setExternalOscMode(SysCtl_ExternalOscMode mode)
{
    EALLOW;

    switch(mode)
    {
        case SYSCTL_XTALMODE_CRYSTAL:
            // Set mode to Crystal
            HWREG(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_SE;
            break;

        case SYSCTL_XTALMODE_SINGLE:
            // Set mode to Single-Ended
            HWREG(CLKCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_SE;
            break;

        default:
            // Do nothing. Not a valid mode value.
            break;
    }

    EDIS;
}

//*****************************************************************************
//
//! Gets the external oscillator counter value.
//!
//! This function returns the X1 clock counter value. When the return value
//! reaches 0x3FF, it freezes. Before switching from INTOSC2 to an external
//! oscillator (XTAL), an application should call this function to make sure the
//! counter is saturated.
//!
//! \return Returns the value of the 10-bit X1 clock counter.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getExternalOscCounterValue(void)
{
    return(HWREGH(CLKCFG_BASE + SYSCTL_O_X1CNT) & SYSCTL_X1CNT_X1CNT_M);
}

//*****************************************************************************
//
//! Clears the external oscillator counter value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearExternalOscCounterValue(void)
{
    HWREG(CLKCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
}

//*****************************************************************************
//
//! Turns on the specified oscillator sources.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function turns on the oscillator specified by the \e oscSource
//! parameter which may take a value of  \b SYSCTL_OSCSRC_OSC2 or
//! \b SYSCTL_OSCSRC_XTAL.
//!
//! \note \b SYSCTL_OSCSRC_OSC1 is not a valid value for \e oscSource.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_turnOnOsc(uint32_t oscSource)
{
    ASSERT((oscSource == SYSCTL_OSCSRC_OSC2) |
           (oscSource == SYSCTL_OSCSRC_XTAL));

    EALLOW;

    switch(oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            // Turn on INTOSC2
            HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &=
                ~SYSCTL_CLKSRCCTL1_INTOSC2OFF;
            break;

        case SYSCTL_OSCSRC_XTAL:
            // Turn on XTALOSC
            HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_OSCOFF;
            break;

        default:
            // Do nothing. Not a valid oscSource value.
            break;
    }

    EDIS;
}

//*****************************************************************************
//
//! Turns off the specified oscillator sources.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function turns off the oscillator specified by the \e oscSource
//! parameter which may take a value of  \b SYSCTL_OSCSRC_OSC2 or
//! \b SYSCTL_OSCSRC_XTAL.
//!
//! \note \b SYSCTL_OSCSRC_OSC1 is not a valid value for \e oscSource.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_turnOffOsc(uint32_t oscSource)
{
    ASSERT((oscSource == SYSCTL_OSCSRC_OSC2) |
           (oscSource == SYSCTL_OSCSRC_XTAL));

    EALLOW;

    switch(oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            // Turn off INTOSC2
            HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |=
                SYSCTL_CLKSRCCTL1_INTOSC2OFF;
            break;

        case SYSCTL_OSCSRC_XTAL:
            // Turn off XTALOSC
            HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_OSCOFF;
            break;

        default:
            // Do nothing. Not a valid oscSource value.
            break;
    }

    EDIS;
}

//*****************************************************************************
//
//! Enters IDLE mode.
//!
//! This function puts the device into IDLE mode. The CPU clock is gated while
//! all peripheral clocks are left running. Any enabled interrupt will wake the
//! CPU up from IDLE mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enterIdleMode(void)
{
    EALLOW;

    //
    // Configure the device to go into IDLE mode when IDLE is executed.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) =
        (HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) & ~SYSCTL_LPMCR_LPM_M) |
        SYSCTL_LPM_IDLE;

    EDIS;

    __asm(" IDLE");
}

//*****************************************************************************
//
//! Enters STANDBY mode.
//!
//! This function puts the device into STANDBY mode. This will gate both the
//! CPU clock and any peripheral clocks derived from SYSCLK. The watchdog is
//! left active, and an NMI or an optional watchdog interrupt will wake the
//! CPU subsystem from STANDBY mode.
//!
//! GPIOs may be configured to wake the CPU subsystem. See
//! SysCtl_enableLPMWakeupPin().
//!
//! The CPU will receive an interrupt (WAKEINT) on wakeup.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enterStandbyMode(void)
{
    EALLOW;

    //
    // Configure the device to go into STANDBY mode when IDLE is executed.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) =
        (HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) & ~SYSCTL_LPMCR_LPM_M) |
        SYSCTL_LPM_STANDBY;

    EDIS;

    __asm(" IDLE");
}

//*****************************************************************************
//
//! Enters HALT mode.
//!
//! This function puts the device into HALT mode. This will gate almost all
//! systems and clocks and allows for the power-down of oscillators and analog
//! blocks. The watchdog may be left clocked to produce a reset. See
//! SysCtl_enableWatchdogInHalt() to enable this. GPIOs should be
//! configured to wake the CPU subsystem. See SysCtl_enableLPMWakeupPin().
//!
//! The CPU will receive an interrupt (WAKEINT) on wakeup.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enterHaltMode(void)
{
    EALLOW;

    //
    // Configure the device to go into HALT mode when IDLE is executed.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) =
        (HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) & ~SYSCTL_LPMCR_LPM_M) |
        SYSCTL_LPM_HALT;

    EDIS;

    __asm(" IDLE");
}

//*****************************************************************************
//
//! Enables a pin to wake up the device from STANDBY or HALT.
//!
//! \param pin is the identifying number of the pin.
//!
//! This function connects a pin to the LPM circuit, allowing an event on the
//! pin to wake up the device when when it is in STANDBY or HALT mode.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin. Only GPIOs 0 through 63 are capable of
//! being connected to the LPM circuit.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableLPMWakeupPin(uint32_t pin)
{
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(pin <= 63U);

    pinMask = (uint32_t)1U << (uint32_t)(pin % 32U);

    EALLOW;

    if(pin < 32U)
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL0) |= pinMask;
    }
    else
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL1) |= pinMask;
    }

    EDIS;
}

//*****************************************************************************
//
//! Disables a pin to wake up the device from STANDBY or HALT.
//!
//! \param pin is the identifying number of the pin.
//!
//! This function disconnects a pin to the LPM circuit, disallowing an event on
//! the pin to wake up the device when when it is in STANDBY or HALT mode.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin. Only GPIOs 0 through 63 are valid.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableLPMWakeupPin(uint32_t pin)
{
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(pin <= 63U);

    pinMask = (uint32_t)1U << (uint32_t)(pin % 32U);

    EALLOW;

    if(pin < 32U)
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL0) &= ~pinMask;
    }
    else
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL1) &= ~pinMask;
    }

    EDIS;
}

//*****************************************************************************
//
//! Sets the number of cycles to qualify an input on waking from STANDBY mode.
//!
//! \param cycles is the number of OSCCLK cycles.
//!
//! This function sets the number of OSCCLK clock cycles used to qualify the
//! selected inputs when waking from STANDBY mode. The \e cycles parameter
//! should be passed a cycle count between 2 and 65 cycles inclusive.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setStandbyQualificationPeriod(uint16_t cycles)
{
    //
    // Check the arguments.
    //
    ASSERT((cycles >= 2U) && (cycles <= 65U));

    EALLOW;

    HWREGH(CPUSYS_BASE + SYSCTL_O_LPMCR) =
        (HWREGH(CPUSYS_BASE + SYSCTL_O_LPMCR) & ~SYSCTL_LPMCR_QUALSTDBY_M) |
        ((cycles - 2U) << SYSCTL_LPMCR_QUALSTDBY_S);

    EDIS;
}

//*****************************************************************************
//
//! Enable the device to wake from STANDBY mode upon a watchdog interrupt.
//!
//! \note In order to use this option, you must configure the watchdog to
//! generate an interrupt using SysCtl_setWatchdogMode().
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdogStandbyWakeup(void)
{
    EALLOW;

    //
    // Set the bit enables the watchdog to wake up the device from STANDBY.
    //
    HWREGH(CPUSYS_BASE + SYSCTL_O_LPMCR) |= SYSCTL_LPMCR_WDINTE;

    EDIS;
}

//*****************************************************************************
//
//! Disable the device from waking from STANDBY mode upon a watchdog interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableWatchdogStandbyWakeup(void)
{
    EALLOW;

    //
    // Clear the bit enables the watchdog to wake up the device from STANDBY.
    //
    HWREGH(CPUSYS_BASE + SYSCTL_O_LPMCR) &= ~SYSCTL_LPMCR_WDINTE;

    EDIS;
}

//*****************************************************************************
//
//! Enable the watchdog to run while in HALT mode.
//!
//! This function configures the watchdog to continue to run while in HALT
//! mode. Additionally, INTOSC1 and INTOSC2 are not powered down when the
//! system enters HALT mode. By default the watchdog is gated when the system
//! enters HALT.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdogInHalt(void)
{
    EALLOW;

    //
    // Set the watchdog HALT mode ignore bit.
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |= SYSCTL_CLKSRCCTL1_WDHALTI;

    EDIS;
}

//*****************************************************************************
//
//! Disable the watchdog from running while in HALT mode.
//!
//! This function gates the watchdog when the system enters HALT mode. INTOSC1
//! and INTOSC2 will be powered down. This is the default behavior of the
//! device.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableWatchdogInHalt(void)
{
    EALLOW;

    //
    // Clear the watchdog HALT mode ignore bit.
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &= ~SYSCTL_CLKSRCCTL1_WDHALTI;

    EDIS;
}

//*****************************************************************************
//
//! Configures whether the watchdog generates a reset or an interrupt signal.
//!
//! \param mode is a flag to select the watchdog mode.
//!
//! This function configures the action taken when the watchdog counter reaches
//! its maximum value. When the \e mode parameter is
//! \b SYSCTL_WD_MODE_INTERRUPT, the watchdog is enabled to generate a watchdog
//! interrupt signal and disables the generation of a reset signal. This will
//! allow the watchdog module to wake up the device from IDLE or STANDBY if
//! desired (see SysCtl_enableWatchdogStandbyWakeup()).
//!
//! When the \e mode parameter is \b SYSCTL_WD_MODE_RESET, the watchdog will
//! be put into reset mode and generation of a watchdog interrupt signal will
//! be disabled. This is how the watchdog is configured by default.
//!
//! \note Check the status of the watchdog interrupt using
//! SysCtl_isWatchdogInterruptActive() before calling this function. If the
//! interrupt is still active, switching from interrupt mode to reset mode will
//! immediately reset the device.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogMode(SysCtl_WDMode mode)
{
    EALLOW;

    //
    // Either set or clear the WDENINT bit to that will determine whether the
    // watchdog will generate a reset signal or an interrupt signal. Note that
    // we take care not to write a 1 to WDOVERRIDE.
    //
    if(mode)
    {
        HWREGH(WD_BASE + SYSCTL_O_SCSR) = (HWREGH(WD_BASE + SYSCTL_O_SCSR) &
                                           ~SYSCTL_SCSR_WDOVERRIDE) |
                                          SYSCTL_SCSR_WDENINT;
    }
    else
    {
        HWREGH(WD_BASE + SYSCTL_O_SCSR) &= ~(SYSCTL_SCSR_WDENINT |
                                             SYSCTL_SCSR_WDOVERRIDE);
    }

    EDIS;
}

//*****************************************************************************
//
//! Gets the status of the watchdog interrupt signal.
//!
//! This function returns the status of the watchdog interrupt signal. If the
//! interrupt is active, this function will return \b true. If \b false, the
//! interrupt is NOT active.
//!
//! \note Make sure to call this function to ensure that the interrupt is not
//! active before making any changes to the configuration of the watchdog to
//! prevent any unexpected behavior. For instance, switching from interrupt
//! mode to reset mode while the interrupt is active will immediately reset the
//! device.
//!
//! \return \b true if the interrupt is active and \b false if it is not.
//
//*****************************************************************************
static inline bool
SysCtl_isWatchdogInterruptActive(void)
{
    bool status = false;

    //
    // If the status bit is cleared, the WDINTn signal is active.
    //
    if((HWREGH(WD_BASE + SYSCTL_O_SCSR) & SYSCTL_SCSR_WDINTS) == 0U)
    {
        status = true;
    }

    return(status);
}

//*****************************************************************************
//
//! Disables the watchdog.
//!
//! This function disables the watchdog timer. Note that the watchdog timer is
//! enabled on reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableWatchdog(void)
{
    EALLOW;

    //
    // Set the disable bit.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) |= SYSCTL_WD_CHKBITS | SYSCTL_WDCR_WDDIS;

    EDIS;
}

//*****************************************************************************
//
//! Enables the watchdog.
//!
//! This function enables the watchdog timer. Note that the watchdog timer is
//! enabled on reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdog(void)
{
    EALLOW;

    //
    // Clear the disable bit.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = (HWREGH(WD_BASE + SYSCTL_O_WDCR) &
                                       ~SYSCTL_WDCR_WDDIS) | SYSCTL_WD_CHKBITS;

    EDIS;
}

//*****************************************************************************
//
//! Services the watchdog.
//!
//! This function resets the watchdog.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_serviceWatchdog(void)
{
    EALLOW;

    //
    // Enable the counter to be reset and then reset it.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDKEY) = SYSCTL_WD_ENRSTKEY;
    HWREGH(WD_BASE + SYSCTL_O_WDKEY) = SYSCTL_WD_RSTKEY;

    EDIS;
}

//*****************************************************************************
//
//! Sets up watchdog clock (WDCLK) pre-divider.
//!
//! \param predivider is the value that configures the pre-divider.
//!
//! This function sets up the watchdog clock (WDCLK) pre-divider. There are two
//! dividers that scale INTOSC1 to WDCLK. The \e predivider parameter divides
//! INTOSC1 down to PREDIVCLK and the prescaler (set by the
//! SysCtl_setWatchdogPrescaler() function) divides PREDIVCLK down to WDCLK.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogPredivider(SysCtl_WDPredivider predivider)
{
    uint16_t regVal;

    regVal = (uint16_t)predivider | (uint16_t)SYSCTL_WD_CHKBITS;

    EALLOW;

    //
    // Write the predivider to the appropriate register.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = (HWREGH(WD_BASE + SYSCTL_O_WDCR) &
                                       ~(SYSCTL_WDCR_WDPRECLKDIV_M)) | regVal;

    EDIS;
}

//*****************************************************************************
//
//! Sets up watchdog clock (WDCLK) prescaler.
//!
//! \param prescaler is the value that configures the watchdog clock relative
//! to the value from the pre-divider.
//!
//! This function sets up the watchdog clock (WDCLK) prescaler. There are two
//! dividers that scale INTOSC1 to WDCLK. The predivider (set with the
//! SysCtl_setWatchdogPredivider function) divides INTOSC1 down to PREDIVCLK
//! and the \e prescaler parameter divides PREDIVCLK down to WDCLK.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogPrescaler(SysCtl_WDPrescaler prescaler)
{
    uint16_t regVal;

    regVal = (uint16_t)prescaler | (uint16_t)SYSCTL_WD_CHKBITS;

    EALLOW;

    //
    // Write the prescaler to the appropriate register.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = (HWREGH(WD_BASE + SYSCTL_O_WDCR) &
                                       ~(SYSCTL_WDCR_WDPS_M)) | regVal;

    EDIS;
}

//*****************************************************************************
//
//! Gets the watchdog counter value.
//!
//! \return Returns the current value of the 8-bit watchdog counter. If this
//! count value overflows, a watchdog output pulse is generated.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getWatchdogCounterValue(void)
{
    //
    // Read and return the value of the watchdog counter.
    //
    return(HWREGH(WD_BASE + SYSCTL_O_WDCNTR));
}

//*****************************************************************************
//
//! Gets the watchdog reset status.
//!
//! This function returns the watchdog reset status. If this function returns
//! \b true, that indicates that a watchdog reset generated the last reset
//! condition. Otherwise, it was an external device or power-up reset
//! condition.
//!
//! \return Returns \b true if the watchdog generated the last reset condition.
//
//*****************************************************************************
static inline bool
SysCtl_getWatchdogResetStatus(void)
{
    //
    // Read and return the status of the watchdog reset status flag.
    //
    return((HWREGH(WD_BASE + SYSCTL_O_RESC) & SYSCTL_RESC_WDRSN) != 0U);
}

//*****************************************************************************
//
//! Clears the watchdog reset status.
//!
//! This function clears the watchdog reset status. To check if it was set
//! first, see SysCtl_getWatchdogResetStatus().
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearWatchdogResetStatus(void)
{
    EALLOW;

    //
    // Read and return the status of the watchdog reset status flag.
    //
    HWREGH(WD_BASE + SYSCTL_O_RESCCLR) = SYSCTL_RESCCLR_WDRSN;

    EDIS;
}

//*****************************************************************************
//
//! Set the minimum threshold value for windowed watchdog
//!
//! \param value is the value to set the window threshold
//!
//! This function sets the minimum threshold value used to define the lower
//! limit of the windowed watchdog functionality.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogWindowValue(uint16_t value)
{
    EALLOW;

    //
    // Clear the windowed value
    //
    HWREGH(WD_BASE + SYSCTL_O_WDWCR) &= ~SYSCTL_WDWCR_MIN_M;

    //
    // Set the windowed value
    //
    HWREGH(WD_BASE + SYSCTL_O_WDWCR) |= (value & SYSCTL_WDWCR_MIN_M);

    EDIS;
}

//*****************************************************************************
//
//! Gets the status of the watchdog first key detect flag
//!
//! This function gets the status of the watchdog first key detect flag.
//!
//! \return Returns \b true if the watchdog first key detect flag is set,
//! else \b false is returned if not set.
//
//*****************************************************************************
static inline bool
SysCtl_isWatchdogKeyDetected(void)
{
    bool status = false;

    //
    // Check the first key detect flag
    //
    if((HWREGH(WD_BASE + SYSCTL_O_WDWCR) & SYSCTL_WDWCR_FIRSTKEY) != 0U)
    {
        status = true;
    }

    return(status);
}

//*****************************************************************************
//
//! Registers an interrupt handler for the WAKEINT interrupt.
//!
//! \param handler is a pointer to the wakeup interrupt handling function.
//!
//! This function ensures that the interrupt handler specified by
//! \e handler is called when an interrupt is detected from the selected
//! external interrupt.  This function also enables the corresponding
//! interrupt in the interrupt controller.
//!
//! The interrupt source must be enabled using SysCtl_setWatchdogMode(). Note
//! that this interrupt is for both low-power-mode wakeup and watchdog
//! interrupts.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_registerWakeupInterrupt(void (*handler)(void))
{
    //
    // Register the interrupt handler.
    //
    Interrupt_register(INT_WAKE, handler);

    //
    // Enable the wakeup interrupt.
    //
    Interrupt_enable(INT_WAKE);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the WAKEINT interrupt.
//!
//! This function unregisters the handler to be called when the wakeup
//! interrupt occurs.  This function also masks off the interrupt in
//! the interrupt controller so that the interrupt handler no longer is called.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_unregisterWakeupInterrupt(void)
{
    //
    // Disable the interrupt.
    //
    Interrupt_disable(INT_WAKE);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregister(INT_WAKE);
}

//*****************************************************************************
//
//! Read NMI interrupts.
//!
//! Read the current state of NMI interrupt.
//!
//! \return \b true if NMI interrupt is triggered, \b false if not.
//
//*****************************************************************************
static inline bool
SysCtl_getNMIStatus(void)
{
    //
    // Read and return the current value of the NMI flag register, masking out
    // all but the NMI bit.
    //
    return((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_NMIINT) != 0U);
}

//*****************************************************************************
//
//! Read NMI Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of NMIFLG register. These defines are provided to decode
//! the value: \b SYSCTL_NMI_NMIINT, \b SYSCTL_NMI_CLOCKFAIL,
//! \b SYSCTL_NMI_RAMUNCERR, \b SYSCTL_NMI_FLUNCERR, and
//! \b SYSCTL_NMI_SWERR.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getNMIFlagStatus(void)
{
    //
    // Read and return the current value of the NMI flag register.
    //
    return(HWREGH(NMI_BASE + NMI_O_FLG));
}

//*****************************************************************************
//
//! Check if the individual NMI interrupts are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided: \b SYSCTL_NMI_NMIINT, \b SYSCTL_NMI_CLOCKFAIL,
//! \b SYSCTL_NMI_RAMUNCERR, \b SYSCTL_NMI_FLUNCERR, and
//! \b SYSCTL_NMI_SWERR.
//!
//! Check if interrupt flags corresponding to the passed in bit mask are
//! asserted.
//!
//! \return \b true if any of the NMI asked for in the parameter bit mask
//! is set. \b false if none of the NMI requested in the parameter bit mask are
//! set.
//
//*****************************************************************************
static inline bool
SysCtl_isNMIFlagSet(uint32_t nmiFlags)
{
    bool status = false;

    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(SYSCTL_NMI_NMIINT | SYSCTL_NMI_CLOCKFAIL |
                         SYSCTL_NMI_RAMUNCERR | SYSCTL_NMI_FLUNCERR |
                         SYSCTL_NMI_SWERR)) == 0);

    //
    // Read the flag register and return true if any of them are set.
    //
    if((HWREGH(NMI_BASE + NMI_O_FLG) & nmiFlags) != 0U)
    {
        status = true;
    }

    return(status);
}

//*****************************************************************************
//
//! Function to clear individual NMI interrupts.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided: \b SYSCTL_NMI_CLOCKFAIL, \b SYSCTL_NMI_RAMUNCERR,
//! \b SYSCTL_NMI_FLUNCERR, and \b SYSCTL_NMI_SWERR.
//!
//! Clear NMI interrupt flags that correspond with the passed in bit mask.
//!
//! \b Note: The NMI Interrupt flag is always cleared by default and
//! therefore doesn't have to be included in the bit mask.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearNMIStatus(uint32_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(SYSCTL_NMI_NMIINT | SYSCTL_NMI_CLOCKFAIL |
                         SYSCTL_NMI_RAMUNCERR | SYSCTL_NMI_FLUNCERR |
                         SYSCTL_NMI_SWERR)) == 0);

    EALLOW;

    //
    // Clear the individual flags as well as NMI Interrupt flag
    //
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = nmiFlags;
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;

    EDIS;
}

//*****************************************************************************
//
//! Clear all the NMI Flags that are currently set.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearAllNMIFlags(void)
{
    uint32_t nmiFlags;

    //
    // Read the flag status register and then write to the clear register,
    // clearing all the flags that were returned plus the NMI flag.
    //
    EALLOW;

    nmiFlags = SysCtl_getNMIFlagStatus();
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = nmiFlags;
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;

    EDIS;
}

//*****************************************************************************
//
//! Function to force individual NMI interrupt fail flags
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided: \b SYSCTL_NMI_CLOCKFAIL, \b SYSCTL_NMI_RAMUNCERR,
//! \b SYSCTL_NMI_FLUNCERR, and \b SYSCTL_NMI_SWERR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_forceNMIFlags(uint32_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(SYSCTL_NMI_NMIINT | SYSCTL_NMI_CLOCKFAIL |
                         SYSCTL_NMI_RAMUNCERR | SYSCTL_NMI_FLUNCERR |
                         SYSCTL_NMI_SWERR)) == 0);

    EALLOW;

    //
    // Set the Flags for the individual interrupts in the NMI flag
    // force register
    //
    HWREGH(NMI_BASE + NMI_O_FLGFRC) |= nmiFlags;

    EDIS;
}

//*****************************************************************************
//
//! Gets the NMI watchdog counter value.
//!
//! \b Note: The counter is clocked at the SYSCLKOUT rate.
//!
//! \return Returns the NMI watchdog counter register's current value.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIWatchdogCounter(void)
{
    //
    // Read and return the NMI watchdog counter register's value.
    //
    return(HWREGH(NMI_BASE + NMI_O_WDCNT));
}

//*****************************************************************************
//
//! Sets the NMI watchdog period value.
//!
//! \param wdPeriod is the 16-bit value at which a reset is generated.
//!
//! This function writes to the NMI watchdog period register that holds the
//! value to which the NMI watchdog counter is compared. When the two registers
//! match, a reset is generated. By default, the period is 0xFFFF.
//!
//! \note If a value smaller than the current counter value is passed into the
//! \e wdPeriod parameter, a NMIRSn will be forced.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setNMIWatchdogPeriod(uint16_t wdPeriod)
{
    EALLOW;

    //
    // Write to the period register.
    //
    HWREGH(NMI_BASE + NMI_O_WDPRD) = wdPeriod;

    EDIS;
}

//*****************************************************************************
//
//! Gets the NMI watchdog period value.
//!
//! \return Returns the NMI watchdog period register's current value.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIWatchdogPeriod(void)
{
    //
    // Read and return the NMI watchdog period register's value.
    //
    return(HWREGH(NMI_BASE + NMI_O_WDPRD));
}

//*****************************************************************************
//
//! Read NMI Shadow Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of NMISHDFLG register. These defines are provided to decode
//! the value: \b SYSCTL_NMI_CLOCKFAIL, \b SYSCTL_NMI_RAMUNCERR,
//! \b SYSCTL_NMI_FLUNCERR, and \b SYSCTL_NMI_SWERR.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getNMIShadowFlagStatus(void)
{
    //
    // Read and return the current value of the NMI shadow flag register.
    //
    return(HWREGH(NMI_BASE + NMI_O_SHDFLG));
}

//*****************************************************************************
//
//! Check if the individual NMI shadow flags are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants  to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided: \b SYSCTL_NMI_CLOCKFAIL, \b SYSCTL_NMI_RAMUNCERR,
//! \b SYSCTL_NMI_FLUNCERR, and \b SYSCTL_NMI_SWERR.
//!
//! Check if interrupt flags corresponding to the passed in bit mask are
//! asserted.
//!
//! \return \b true if any of the NMI asked for in the parameter bit mask
//! is set. \b false if none of the NMI requested in the parameter bit mask are
//! set.
//
//*****************************************************************************
static inline bool
SysCtl_isNMIShadowFlagSet(uint32_t nmiFlags)
{
    bool status = false;

    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(SYSCTL_NMI_NMIINT | SYSCTL_NMI_CLOCKFAIL |
                         SYSCTL_NMI_RAMUNCERR | SYSCTL_NMI_FLUNCERR |
                         SYSCTL_NMI_SWERR)) == 0);

    //
    // Read the flag register and return true if any of them are set.
    //
    if((HWREGH(NMI_BASE + NMI_O_SHDFLG) & nmiFlags) != 0U)
    {
        status = true;
    }

    return(status);
}

//*****************************************************************************
//
//! Enable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableMCD(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) &= ~(SYSCTL_MCDCR_MCLKOFF);

    EDIS;
}

//*****************************************************************************
//
//! Disable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableMCD(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_MCLKOFF;

    EDIS;
}

//*****************************************************************************
//
//! Get the missing clock detection Failure Status
//!
//! \note A failure means the oscillator clock is missing
//!
//! \return Returns \b true if a failure is detected or \b false if a
//! failure isn't detected
//
//*****************************************************************************
static inline bool
SysCtl_isMCDClockFailureDetected(void)
{
    bool status = false;

    //
    //  Check the status bit to determine failure
    //
    if((HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) & SYSCTL_MCDCR_MCLKSTS) != 0U)
    {
        status = true;
    }

    return(status);
}

//*****************************************************************************
//
//! Reset the missing clock detection logic after clock failure
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_resetMCD(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_MCLKCLR;

    EDIS;
}

//*****************************************************************************
//
//! Re-connect missing clock detection clock source to stop simulating clock
//! failure
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_connectMCDClockSource(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) &= ~(SYSCTL_MCDCR_OSCOFF);

    EDIS;
}

//*****************************************************************************
//
//! Disconnect missing clock detection clock source to simulate clock failure.
//! This is for testing the MCD functionality.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disconnectMCDClockSource(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_OSCOFF;

    EDIS;
}

//*****************************************************************************
//
//! Lock the Access Control Registers
//!
//! This function locks the access control registers and puts them in a
//! read-only state.
//!
//! \note Only a reset can unlock the access control registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_lockAccessControlRegs(void)
{
    EALLOW;

    HWREGH(PERIPHAC_BASE + SYSCTL_O_PERIPH_AC_LOCK) |=
        SYSCTL_PERIPH_AC_LOCK_LOCK_AC_WR;

    EDIS;
}

//*****************************************************************************
//
//! Set the peripheral access control permissions
//!
//! \param peripheral is the selected peripheral
//! \param master is the selected master (CPU1, CLA1, or DMA1)
//! \param permission is the selected access permissions
//!
//! This function sets the specified peripheral access control permissions for
//! the the specified master (CPU1, CLA1, or DMA1)
//!
//! The \e peripheral parameter can have one the following enumerated values:
//! \b SYSCTL_ACCESS_ADCA, \b SYSCTL_ACCESS_ADCB, \b SYSCTL_ACCESS_ADCC,
//! \b SYSCTL_ACCESS_CMPSS1, \b SYSCTL_ACCESS_CMPSS2, \b SYSCTL_ACCESS_CMPSS3,
//! \b SYSCTL_ACCESS_CMPSS4, \b SYSCTL_ACCESS_CMPSS5, \b SYSCTL_ACCESS_CMPSS6,
//! \b SYSCTL_ACCESS_CMPSS7, \b SYSCTL_ACCESS_DACA, \b SYSCTL_ACCESS_DACB,
//! \b SYSCTL_ACCESS_PGAA, \b SYSCTL_ACCESS_PGAB, \b SYSCTL_ACCESS_PGAC,
//! \b SYSCTL_ACCESS_PGAD, \b SYSCTL_ACCESS_PGAE, \b SYSCTL_ACCESS_PGAF,
//! \b SYSCTL_ACCESS_PGAG, \b SYSCTL_ACCESS_EPWM1, \b SYSCTL_ACCESS_EPWM2,
//! \b SYSCTL_ACCESS_EPWM3, \b SYSCTL_ACCESS_EPWM4, \b SYSCTL_ACCESS_EPWM5,
//! \b SYSCTL_ACCESS_EPWM6, \b SYSCTL_ACCESS_EPWM7, \b SYSCTL_ACCESS_EPWM8,
//! \b SYSCTL_ACCESS_EQEP1, \b SYSCTL_ACCESS_EQEP2, \b SYSCTL_ACCESS_ECAP1,
//! \b SYSCTL_ACCESS_ECAP2, \b SYSCTL_ACCESS_ECAP3, \b SYSCTL_ACCESS_ECAP4,
//! \b SYSCTL_ACCESS_ECAP5, \b SYSCTL_ACCESS_ECAP6, \b SYSCTL_ACCESS_ECAP7,
//! \b SYSCTL_ACCESS_SDFM1, \b SYSCTL_ACCESS_CLB1, \b SYSCTL_ACCESS_CLB2,
//! \b SYSCTL_ACCESS_CLB3, \b SYSCTL_ACCESS_CLB4, \b SYSCTL_ACCESS_CLA1PROMCRC,
//! \b SYSCTL_ACCESS_SCIA, \b SYSCTL_ACCESS_SCIB, \b SYSCTL_ACCESS_SPIA,
//! \b SYSCTL_ACCESS_SPIB, \b SYSCTL_ACCESS_I2CA, \b SYSCTL_ACCESS_PMBUSA,
//! \b SYSCTL_ACCESS_LINA, \b SYSCTL_ACCESS_CANA, \b SYSCTL_ACCESS_CANB,
//! \b SYSCTL_ACCESS_FSIATX, \b SYSCTL_ACCESS_FSIARX, \b SYSCTL_ACCESS_HRPWMA
//!
//! The \e master parameter can have one the following enumerated values:
//! - \b SYSCTL_ACCESS_CPU1 - CPU1 Master
//! - \b SYSCTL_ACCESS_CLA1 - CLA1 Master
//! - \b SYSCTL_ACCESS_DMA1 - DMA1 Master
//!
//! The \e permission parameter can have one the following enumerated values:
//! - \b SYSCTL_ACCESS_FULL      - Full Access for both read and write
//! - \b SYSCTL_ACCESS_PROTECTED - Protected read access such that FIFOs, clear
//!                                on read registers are not changed, and no
//!                                write access
//! - \b SYSCTL_ACCESS_NONE      - No read or write access
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setPeripheralAccessControl(SysCtl_AccessPeripheral peripheral,
                                  SysCtl_AccessMaster master,
                                  SysCtl_AccessPermission permission)
{
    //
    // Set master permissions for specified peripheral. Each master has
    // two bits dedicated to its permission setting.
    //
    EALLOW;

    HWREGH(PERIPHAC_BASE + (uint16_t)peripheral) =
        (HWREGH(PERIPHAC_BASE + (uint16_t)peripheral) &
         ~(0x3U << (uint16_t)master)) |
        ((uint32_t)permission << (uint16_t)master);

    EDIS;
}

//*****************************************************************************
//
//! Get the peripheral access control permissions
//!
//! \param peripheral is the selected peripheral
//! \param master is the selected master (CPU1, CLA1, or DMA1)
//!
//! This function gets the specified peripheral access control permissions for
//! the the specified master (CPU1, CLA1, or DMA1)
//!
//! The \e peripheral parameter can have one the following enumerated values:
//! \b SYSCTL_ACCESS_ADCA, \b SYSCTL_ACCESS_ADCB, \b SYSCTL_ACCESS_ADCC,
//! \b SYSCTL_ACCESS_CMPSS1, \b SYSCTL_ACCESS_CMPSS2, \b SYSCTL_ACCESS_CMPSS3,
//! \b SYSCTL_ACCESS_CMPSS4, \b SYSCTL_ACCESS_CMPSS5, \b SYSCTL_ACCESS_CMPSS6,
//! \b SYSCTL_ACCESS_CMPSS7, \b SYSCTL_ACCESS_DACA, \b SYSCTL_ACCESS_DACB,
//! \b SYSCTL_ACCESS_PGAA, \b SYSCTL_ACCESS_PGAB, \b SYSCTL_ACCESS_PGAC,
//! \b SYSCTL_ACCESS_PGAD, \b SYSCTL_ACCESS_PGAE, \b SYSCTL_ACCESS_PGAF,
//! \b SYSCTL_ACCESS_PGAG, \b SYSCTL_ACCESS_EPWM1, \b SYSCTL_ACCESS_EPWM2,
//! \b SYSCTL_ACCESS_EPWM3, \b SYSCTL_ACCESS_EPWM4, \b SYSCTL_ACCESS_EPWM5,
//! \b SYSCTL_ACCESS_EPWM6, \b SYSCTL_ACCESS_EPWM7, \b SYSCTL_ACCESS_EPWM8,
//! \b SYSCTL_ACCESS_EQEP1, \b SYSCTL_ACCESS_EQEP2, \b SYSCTL_ACCESS_ECAP1,
//! \b SYSCTL_ACCESS_ECAP2, \b SYSCTL_ACCESS_ECAP3, \b SYSCTL_ACCESS_ECAP4,
//! \b SYSCTL_ACCESS_ECAP5, \b SYSCTL_ACCESS_ECAP6, \b SYSCTL_ACCESS_ECAP7,
//! \b SYSCTL_ACCESS_SDFM1, \b SYSCTL_ACCESS_CLB1, \b SYSCTL_ACCESS_CLB2,
//! \b SYSCTL_ACCESS_CLB3, \b SYSCTL_ACCESS_CLB4, \b SYSCTL_ACCESS_CLA1PROMCRC,
//! \b SYSCTL_ACCESS_SCIA, \b SYSCTL_ACCESS_SCIB, \b SYSCTL_ACCESS_SPIA,
//! \b SYSCTL_ACCESS_SPIB, \b SYSCTL_ACCESS_I2CA, \b SYSCTL_ACCESS_PMBUSA,
//! \b SYSCTL_ACCESS_LINA, \b SYSCTL_ACCESS_CANA, \b SYSCTL_ACCESS_CANB,
//! \b SYSCTL_ACCESS_FSIATX, \b SYSCTL_ACCESS_FSIARX, \b SYSCTL_ACCESS_HRPWMA
//!
//! The \e master parameter can have one the following enumerated values:
//! - \b SYSCTL_ACCESS_CPU1 - CPU1 Master
//! - \b SYSCTL_ACCESS_CLA1 - CLA1 Master
//! - \b SYSCTL_ACCESS_DMA1 - DMA1 Master
//!
//! \return Returns one of the following enumerated permission values:
//! - \b SYSCTL_ACCESS_FULL      - Full Access for both read and write
//! - \b SYSCTL_ACCESS_PROTECTED - Protected read access such that FIFOs, clear
//!                                on read registers are not changed, and no
//!                                write access
//! - \b SYSCTL_ACCESS_NONE      - No read or write access
//
//*****************************************************************************
static inline uint32_t
SysCtl_getPeripheralAccessControl(SysCtl_AccessPeripheral peripheral,
                                  SysCtl_AccessMaster master)
{
    //
    // Read master permissions for specified peripheral. Each master has
    // two bits dedicated to its permission setting.
    //
    return((HWREGH(PERIPHAC_BASE + (uint16_t)peripheral) >> (uint16_t)master) &
           0x3U);
}

//*****************************************************************************
//
//! Delays for a fixed number of cycles.
//!
//! \param count is the number of delay loop iterations to perform.
//!
//! This function generates a constant length delay using assembly code. The
//! loop takes 5 cycles per iteration plus 9 cycles of overhead.
//!
//! \note If count is equal to zero, the loop will underflow and run for a
//! very long time.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_delay(uint32_t count);

//*****************************************************************************
//
//! Calculates the system clock frequency (SYSCLK).
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the system clock based on the
//! frequency of the oscillator clock source (from \e clockInHz) and the PLL
//! and clock divider configuration registers.
//!
//! \return Returns the system clock frequency. If a missing clock is detected,
//! the function will return the INTOSC1 frequency. This needs to be
//! corrected and cleared (see SysCtl_resetMCD()) before trying to call this
//! function again.
//
//*****************************************************************************
extern uint32_t
SysCtl_getClock(uint32_t clockInHz);

//*****************************************************************************
//
//! Configures the clocking of the device.
//!
//! \param config is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \e config parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! - The system clock divider is chosen with the macro \b SYSCTL_SYSDIV(x)
//!   where x is either 1 or an even value up to 126.
//!
//! - The use of the PLL is chosen with either \b SYSCTL_PLL_ENABLE or
//!   \b SYSCTL_PLL_DISABLE.
//!
//! - The integer multiplier is chosen \b SYSCTL_IMULT(x) where x is a value
//!   from 1 to 127.
//!
//! - The fractional multiplier is chosen with either \b SYSCTL_FMULT_0,
//!   \b SYSCTL_FMULT_1_4, \b SYSCTL_FMULT_1_2, or \b SYSCTL_FMULT_3_4.
//!
//! - The oscillator source chosen with \b SYSCTL_OSCSRC_OSC2,
//!   \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_XTAL_SE or \b SYSCTL_OSCSRC_OSC1.
//!
//! \return Returns \b false if a missing clock error is detected. This needs
//! to be cleared (see SysCtl_resetMCD()) before trying to call this function
//! again. Otherwise, returns \b true.
//
//*****************************************************************************
extern bool
SysCtl_setClock(uint32_t config);

//*****************************************************************************
//
//! Configures the external oscillator for the clocking of the device.
//!
//! This function configures the external oscillator (XTAL) to be used for the
//! clocking of the device in crystal mode. It follows the procedure to turn on
//! the oscillator, wait for it to power up, and select it as the source of the
//! system clock.
//!
//! Please note that this function blocks while it waits for the XTAL to power
//! up. If the XTAL does not manage to power up properly, the function will
//! loop for a long time. It is recommended that you modify this function to
//! add an appropriate timeout and error-handling procedure.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectXTAL(void);

//*****************************************************************************
//
//! Configures the external oscillator for the clocking of the device in
//! single-ended mode.
//!
//! This function configures the external oscillator (XTAL) to be used for the
//! clocking of the device in single-ended mode. It follows the procedure to
//! turn on the oscillator, wait for it to power up, and select it as the
//! source of the system clock.
//!
//! Please note that this function blocks while it waits for the XTAL to power
//! up. If the XTAL does not manage to power up properly, the function will
//! loop for a long time. It is recommended that you modify this function to
//! add an appropriate timeout and error-handling procedure.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectXTALSingleEnded(void);

//*****************************************************************************
//
//! Selects the oscillator to be used for the clocking of the device.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function configures the oscillator to be used in the clocking of the
//! device. The \e oscSource parameter may take a value of
//! \b SYSCTL_OSCSRC_OSC2, \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_XTAL_SE, or
//! \b SYSCTL_OSCSRC_OSC1.
//!
//! \sa SysCtl_turnOnOsc()
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectOscSource(uint32_t oscSource);

//*****************************************************************************
//
//! Calculates the low-speed peripheral clock frequency (LSPCLK).
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the low-speed peripheral clock
//! based on the frequency of the oscillator clock source (from \e clockInHz)
//! and the PLL and clock divider configuration registers.
//!
//! \return Returns the low-speed peripheral clock frequency.
//
//*****************************************************************************
extern uint32_t
SysCtl_getLowSpeedClock(uint32_t clockInHz);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SYSCTL_H__
