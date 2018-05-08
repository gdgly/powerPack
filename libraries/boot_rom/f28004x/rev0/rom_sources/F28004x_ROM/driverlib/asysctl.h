//###########################################################################
//
// FILE:   asysctl.h
//
// TITLE:  C28x driver for Analog System Control.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:  $
//###########################################################################

#ifndef __ASYSCTL_H__
#define __ASYSCTL_H__

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
//! \addtogroup asysctl_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_asysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "debug.h"
#include "cpu.h"

//*****************************************************************************
//
// Defines used for setting AnalogReference functions.
// ASysCtl_setAnalogReferenceInternal()
// ASysCtl_setAnalogReferenceExternal()
// ASysCtl_setAnalogReference2P5()
// ASysCtl_setAnalogReference1P65()
//
//*****************************************************************************
#define ASYSCTL_VREFHIA     0x1U //!< VREFHIA
#define ASYSCTL_VREFHIB     0x2U //!< VREFHIB
#define ASYSCTL_VREFHIC     0x4U //!< VREFHIC

//*****************************************************************************
//
// Values used for function ASysCtl_selectPGAADCINMux().  These values can be
// OR-ed together and passed to ASysCtl_selectPGAADCINMux().
//
//*****************************************************************************
#define     ASYSCTL_PGA_1_ADCIN_MUX     0x1U
#define     ASYSCTL_PGA_2_ADCIN_MUX     0x2U
#define     ASYSCTL_PGA_3_ADCIN_MUX     0x4U
#define     ASYSCTL_PGA_4_ADCIN_MUX     0x8U
#define     ASYSCTL_PGA_5_ADCIN_MUX     0x10U
#define     ASYSCTL_PGA_6_ADCIN_MUX     0x20U
#define     ASYSCTL_PGA_7_ADCIN_MUX     0x40U

//*****************************************************************************
//
// Values used for function ASysCtl_selectCMPHNMux().  These values can be
// OR-ed together and passed to ASysCtl_selectCMPHNMux().
//
//*****************************************************************************
#define     ASYSCTL_CMPHNMUX_SELECT_1   0X1U
#define     ASYSCTL_CMPHNMUX_SELECT_2   0X2U
#define     ASYSCTL_CMPHNMUX_SELECT_3   0X4U
#define     ASYSCTL_CMPHNMUX_SELECT_4   0X8U
#define     ASYSCTL_CMPHNMUX_SELECT_5   0X10U
#define     ASYSCTL_CMPHNMUX_SELECT_6   0X20U
#define     ASYSCTL_CMPHNMUX_SELECT_7   0X40U

//*****************************************************************************
//
// Values used for function ASysCtl_selectCMPLNMux().  These values can be
// OR-ed together and passed to ASysCtl_selectCMPLNMux().
//
//*****************************************************************************
#define     ASYSCTL_CMPLNMUX_SELECT_1   0X1U
#define     ASYSCTL_CMPLNMUX_SELECT_2   0X2U
#define     ASYSCTL_CMPLNMUX_SELECT_3   0X4U
#define     ASYSCTL_CMPLNMUX_SELECT_4   0X8U
#define     ASYSCTL_CMPLNMUX_SELECT_5   0X10U
#define     ASYSCTL_CMPLNMUX_SELECT_6   0X20U
#define     ASYSCTL_CMPLNMUX_SELECT_7   0X40U

//*****************************************************************************
//
//! ASysCtl_CMPHPMuxSelect used for function ASysCtl_selectCMPHPMux().
//
//*****************************************************************************
typedef enum
{
    ASYSCTL_CMPHPMUX_SELECT_1 = 0x0U,
    ASYSCTL_CMPHPMUX_SELECT_2 = 0x3U,
    ASYSCTL_CMPHPMUX_SELECT_3 = 0x6U,
    ASYSCTL_CMPHPMUX_SELECT_4 = 0x9U,
    ASYSCTL_CMPHPMUX_SELECT_5 = 0xCU,
    ASYSCTL_CMPHPMUX_SELECT_6 = 0x10U,
    ASYSCTL_CMPHPMUX_SELECT_7 = 0x13U
} ASysCtl_CMPHPMuxSelect;

//*****************************************************************************
//
//! ASysCtl_CMPLPMuxSelect used for function ASysCtl_selectCMPLPMux().
//
//*****************************************************************************
typedef enum
{
    ASYSCTL_CMPLPMUX_SELECT_1 = 0x0U,
    ASYSCTL_CMPLPMUX_SELECT_2 = 0x3U,
    ASYSCTL_CMPLPMUX_SELECT_3 = 0x6U,
    ASYSCTL_CMPLPMUX_SELECT_4 = 0x9U,
    ASYSCTL_CMPLPMUX_SELECT_5 = 0xCU,
    ASYSCTL_CMPLPMUX_SELECT_6 = 0x10U,
    ASYSCTL_CMPLPMUX_SELECT_7 = 0x13U
} ASysCtl_CMPLPMuxSelect;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Enable temperature sensor.
//!
//! This function enables the temperature sensor output to the ADC.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_enableTemperatureSensor(void)
{
    EALLOW;
    
    //
    // Set the temperature sensor enable bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_TSNSCTL) |= ASYSCTL_TSNSCTL_ENABLE;

    EDIS;
}

//*****************************************************************************
//
//! Disable temperature sensor.
//!
//! This function disables the temperature sensor output to the ADC.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_disableTemperatureSensor(void)
{
    EALLOW;
    
    //
    // Clear the temperature sensor enable bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_TSNSCTL) &= ~(ASYSCTL_TSNSCTL_ENABLE);

    EDIS;
}

//*****************************************************************************
//
//! Set the analog reference selection to internal.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB
//! - \b ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_setAnalogReferenceInternal(uint16_t reference)
{
    ASSERT( reference <= 0x7U );

    EALLOW;
    
    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) &= ~reference;

    EDIS;
}

//*****************************************************************************
//
//! Set the analog reference selection to external.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB
//! - \b ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_setAnalogReferenceExternal(uint16_t reference)
{
    ASSERT( reference <= 0x7U );

    EALLOW;
    
    //
    // Write selection to the Analog External Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) |= reference;

    EDIS;
}

//*****************************************************************************
//
//! Set the external analog reference selection to 2.5V.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB
//! - \b ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReference2P5(uint16_t reference)
{
    ASSERT( reference <= 0x7U );

    EALLOW;
    
    //
    // Write selection to the Analog Voltage Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) |= (reference << 8U);

    EDIS;
}

//*****************************************************************************
//
//! Set the external analog reference selection to 1.65V.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB
//! - \b ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReference1P65(uint16_t reference)
{
    ASSERT( reference <= 0x7U );

    EALLOW;
    
    //
    // Write selection to the Analog Voltage Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) &= ~(reference << 8U);

    EDIS;
}

//#####BEGIN_INTERNAL#####
//DC-DC is internal for now until it is tested and documented in the datasheet
//*****************************************************************************
//
//! Set the VDD DC-DC trim value for the core voltage regulator.
//!
//! \param trim is the trim value.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setDCDCTrim(uint16_t trim)
{
    ASSERT(trim <= 255U);

    EALLOW;
    
    //
    // Write the VDD DC-DC trim value.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCTRIM0) |= trim &
                                ASYSCTL_DCDCTRIM0_TRIM_M;

    EDIS;
}

//*****************************************************************************
//
//! Set the VDD DC-DC spare trim value for the core voltage regulator.
//!
//! \param trim is the spare trim value.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setDCDCSpareTrim(uint16_t trim)
{
    ASSERT(trim <= 255U);

    EALLOW;
    
    //
    // Write the spare trim value.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCTRIM0) |=
        (trim << ASYSCTL_DCDCTRIM0_SPARE_TRIM_S) & ASYSCTL_DCDCTRIM0_TRIM_M;

    EDIS;
}

//#####BEGIN_INTERNAL#####
//OTPTrim is truly internal.
//*****************************************************************************
//
//! Set the DC-DC OTP trim.
//!
//! \param trim is the trim value.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setOTPTrim(uint32_t trim)
{
    EALLOW;
    
    //
    // Write the OTP Trim value over what was loaded from OTP.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCTRIM1) = trim;

    EDIS;
}
//OTPTrim is truly internal.
//#####END_INTERNAL#####

//*****************************************************************************
//
//! Enable DC-DC.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_enableDCDC(void)
{
    EALLOW;
    
    //
    // Write 1 to enable bit.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCCTL) |= ASYSCTL_DCDCCTL_DCDCEN;

    EDIS;
}

//*****************************************************************************
//
//! Disable DC-DC.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_disableDCDC(void)
{
    EALLOW;
    
    //
    // Write 0 to enable bit.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCCTL) &= ~ASYSCTL_DCDCCTL_DCDCEN;

    EDIS;
}

//*****************************************************************************
//
//! Enable NMI generation on a overload fault condition.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_enableOverloadFaultNMI(void)
{
    EALLOW;
    
    //
    // Write 1 to enable bit.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCCTL) |= ASYSCTL_DCDCCTL_OLFNMIEN;

    EDIS;
}

//*****************************************************************************
//
//! Disable NMI generation on a overload fault condition.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_disableOverloadFaultNMI(void)
{
    EALLOW;
    
    //
    // Write 0 to enable bit.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCCTL) &= ~ASYSCTL_DCDCCTL_OLFNMIEN;

    EDIS;
}

//*****************************************************************************
//
//! Sets the spread spectrum control.
//!
//! \param control is the DCDC Spread Spectrum Control.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setSpreadSpectrumControl(uint32_t control)
{
    EALLOW;
    
    //
    // Write the 32 bit value to DCDCSSCTL.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSSCTL) = control;

    EDIS;
}

//*****************************************************************************
//
//! Gets the Inductor Fault Status.
//!
//! This function returns the Inductor Fault Status.
//!
//! \return Return value false indicates that the external inductor connected
//! to DC-DC is functional.  Return value of true indicates it is faulty.
//
//*****************************************************************************
static inline bool ASysCtl_getInductorFaultStatus(void)
{
    bool status = false;
    
    //
    // Return the status the INDFAULT bit.
    //
    if( (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTS) &
          ASYSCTL_DCDCSTS_INDFAULT) == ASYSCTL_DCDCSTS_INDFAULT )
    {
        status = true;
    }
    return(status);
}

//*****************************************************************************
//
//! Gets the Switch Sequence Status.
//!
//! This function returns the Switch Sequence Status.
//!
//! \return Return value false indicates that the switch to DC-DC is not
//! complete. Return value of true indicates it is complete.
//
//*****************************************************************************
static inline bool ASysCtl_getSwitchSequenceStatus(void)
{
    bool status = false;
    
    //
    // Return the status the SWSEQDONE bit.
    //
    if( (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTS) &
          ASYSCTL_DCDCSTS_SWSEQDONE) == ASYSCTL_DCDCSTS_SWSEQDONE )
    {
        status = true;
    }
    return(status);
}

//*****************************************************************************
//
//! Gets the Overload Fault Status.
//!
//! This function returns the Overload Fault Status.
//!
//! \return Return value false indicates that the load current is within the
//! spec for DC-DC. Return value of true indicates it is above the spec limit.
//
//*****************************************************************************
static inline bool ASysCtl_getOverloadFaultStatus(void)
{
    bool status = false;
    
    //
    // Return the status the OLF bit.
    //
    if( (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTS) &
          ASYSCTL_DCDCSTS_OLF) == ASYSCTL_DCDCSTS_OLF )
    {
        status = true;
    }
    return(status);
}

//*****************************************************************************
//
//! Clears the Inductor Fault status flag.
//!
//! This function clears the Inductor Fault status flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_clearInductorFaultStatus(void)
{
    EALLOW;
    
    //
    // Clear the INDFAULT bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTSCLR) |=
            ASYSCTL_DCDCSTSCLR_INDFAULT;

    EDIS;
}

//*****************************************************************************
//
//! Clears the Switch Sequence status flag.
//!
//! This function clears the Switch Sequence status flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_clearSwitchSequenceStatus(void)
{
    EALLOW;
    
    //
    // Clear the SWSEQDONE bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTSCLR) |=
            ASYSCTL_DCDCSTSCLR_SWSEQDONE;

    EDIS;
}

//*****************************************************************************
//
//! Clears the Overload Fault status flag.
//!
//! This function clears the Overload Fault status flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_clearOverloadFaultStatus(void)
{
    EALLOW;
    
    //
    // Clear the OLF bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTSCLR) |=
            ASYSCTL_DCDCSTSCLR_OLF;

    EDIS;
}
//DCDC is internal until it is validated and documented in the datasheet
//#####END_INTERNAL#####

//*****************************************************************************
//
//! Select ADC Mux.
//!
//! \param adc is a combination of PGA ADCIN Mux values.
//!
//! The parameter \e adc can be a logical OR of the below values:
//!
//! - \b ASYSCTL_PGA_1_ADCIN_MUX
//! - \b ASYSCTL_PGA_2_ADCIN_MUX
//! - \b ASYSCTL_PGA_3_ADCIN_MUX
//! - \b ASYSCTL_PGA_4_ADCIN_MUX
//! - \b ASYSCTL_PGA_5_ADCIN_MUX
//! - \b ASYSCTL_PGA_6_ADCIN_MUX
//! - \b ASYSCTL_PGA_7_ADCIN_MUX
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectPGAADCINMux(uint16_t adc)
{
    ASSERT(adc <= 0x7FU);

    EALLOW;
    
    //
    // Write to the ADCINMXEL bits for the selected ADC(s).
    //    
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ADCINMXSEL) = adc;

    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPHNMXSEL.
//!
//! \param select is a combination of CMPHNMXSEL values.
//!
//! The parameter \e select can be a logical OR of the below values:
//!
//! - \b ASYSCTL_CMPHNMUX_SELECT_1
//! - \b ASYSCTL_CMPHNMUX_SELECT_2
//! - \b ASYSCTL_CMPHNMUX_SELECT_3
//! - \b ASYSCTL_CMPHNMUX_SELECT_4
//! - \b ASYSCTL_CMPHNMUX_SELECT_5
//! - \b ASYSCTL_CMPHNMUX_SELECT_6
//! - \b ASYSCTL_CMPHNMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPHNMux(uint16_t select)
{
    ASSERT(select <= 0x7FU);
    
    EALLOW;
    
    //
    // Write a select to the mux select bit.
    //    
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHNMXSEL) = select;

    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPLNMXSEL.
//!
//! \param select is a combination of CMPLNMXSEL values.
//!
//! The parameter \e select can be the logical OR of the below values:
//!
//! - \b ASYSCTL_CMPLNMUX_SELECT_1
//! - \b ASYSCTL_CMPLNMUX_SELECT_2
//! - \b ASYSCTL_CMPLNMUX_SELECT_3
//! - \b ASYSCTL_CMPLNMUX_SELECT_4
//! - \b ASYSCTL_CMPLNMUX_SELECT_5
//! - \b ASYSCTL_CMPLNMUX_SELECT_6
//! - \b ASYSCTL_CMPLNMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPLNMux(uint16_t select)
{
    ASSERT(select <= 0x7FU);

    EALLOW;
    
    //
    // Write a select to the mux select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLNMXSEL) = select;

    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPHPMXSEL.
//!
//! \param select is of type ASysCtl_CMPHPMuxSelect.
//! \param value is 0, 1, 2, 3, or 4.
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b ASYSCTL_CMPHPMUX_SELECT_1
//! - \b ASYSCTL_CMPHPMUX_SELECT_2
//! - \b ASYSCTL_CMPHPMUX_SELECT_3
//! - \b ASYSCTL_CMPHPMUX_SELECT_4
//! - \b ASYSCTL_CMPHPMUX_SELECT_5
//! - \b ASYSCTL_CMPHPMUX_SELECT_6
//! - \b ASYSCTL_CMPHPMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_selectCMPHPMux(ASysCtl_CMPHPMuxSelect select, uint32_t value)
{
    ASSERT( value <= 4);

    EALLOW;

    //
    // Set the value for the appropriate Mux Select.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL) =
            (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL) & 
            ~(ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_M << (uint32_t)select)) | 
            (value << (uint32_t)select);

    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPLPMXSEL.
//!
//! \param select is of type ASysCtl_CMPLPMuxSelect.
//! \param value is 0, 1, 2, 3, or 4.
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b ASYSCTL_CMPLPMUX_SELECT_1
//! - \b ASYSCTL_CMPLPMUX_SELECT_2
//! - \b ASYSCTL_CMPLPMUX_SELECT_3
//! - \b ASYSCTL_CMPLPMUX_SELECT_4
//! - \b ASYSCTL_CMPLPMUX_SELECT_5
//! - \b ASYSCTL_CMPLPMUX_SELECT_6
//! - \b ASYSCTL_CMPLPMUX_SELECT_7
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_selectCMPLPMux(ASysCtl_CMPLPMuxSelect select, uint32_t value)
{
    ASSERT( value <= 4);

    EALLOW;
    
    //
    // Set the value for the appropriate Mux Select.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL) =
            (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL) &
            ~(ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M << (uint32_t)select)) |
            (value << (uint32_t)select);

    EDIS;
}

//*****************************************************************************
//
//! Locks the temperature sensor control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockTSNS(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_TSNSCTL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the analog reference control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockANAREF(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_ANAREFCTL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the voltage monitor control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockVMON(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_VMONCTL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the DCDC control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockDCDC(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_DCDCCTL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the ADCIN control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockPGAADCINMux(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_ADCINMXSEL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPHPMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPHPMux(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPHPMXSEL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPLPMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPLPMux(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPLPMXSEL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPHNMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPHNMux(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPHNMXSEL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPLNMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPLNMux(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPLNMXSEL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the VREG control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockVREG(void)
{
    EALLOW;
    
    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_VREGCTL;

    EDIS;
}
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __ASYSCTL_H__
