//###########################################################################
//
// FILE:   pga.h
//
// TITLE:  C28x PGA driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __PGA_H__
#define __PGA_H__

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
//! \addtogroup pga_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_pga.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"
#include "interrupt.h"


//! \brief Enumeration to define the PGA gain values
//!
typedef enum
{
    PGA_GAIN_3 = (0U << 5U),  //!< PGA gain value of 3
    PGA_GAIN_6 = (1U << 5U),  //!< PGA gain value of 6
    PGA_GAIN_12 = (2U << 5U), //!< PGA gain value of 12
    PGA_GAIN_24 = (3U << 5U)  //!< PGA gain value of 24
}PGA_GainValue;

//! \brief Enumeration to define the PGA output low pass filter resistor values
//!
typedef enum
{
    //! Resistor value of 0 Ohms
    PGA_LOW_PASS_FILTER_RESISTOR_0 = (0U << 1U),
    //! Resistor value of TBD_1 Ohms
    PGA_LOW_PASS_FILTER_RESISTOR_TBD_1 = (1U << 1U),
    //! Resistor value of TBD_2 Ohms
    PGA_LOW_PASS_FILTER_RESISTOR_TBD_2 = (2U << 1U),
    //! Resistor value of TBD_3 Ohms
    PGA_LOW_PASS_FILTER_RESISTOR_TBD_3 = (3U << 1U),
    //! Resistor value of TBD_4 Ohms
    PGA_LOW_PASS_FILTER_RESISTOR_TBD_4 = (4U << 1U)
}PGA_LowPassResistorValue;

//! \brief Enumeration to define the PGA Trim sets
//!
typedef enum
{
    PGA_TRIM_SET_GAIN_1 = PGA_O_GAIN1TRIM,  //!< PGA Trim set for gain value 1
    PGA_TRIM_SET_GAIN_3 = PGA_O_GAIN3TRIM,  //!< PGA Trim set for gain value 3
    PGA_TRIM_SET_GAIN_6 = PGA_O_GAIN6TRIM,  //!< PGA Trim set for gain value 6
    PGA_TRIM_SET_GAIN_12 = PGA_O_GAIN12TRIM,//!< PGA Trim set for gain value 12
    PGA_TRIM_SET_GAIN_24 = PGA_O_GAIN24TRIM //!< PGA Trim set for gain value 24
}PGA_TrimGainSelect;

//*****************************************************************************
//
// Values that can be passed to PGA_lockRegisters as registerType parameters.
//
//*****************************************************************************
//! PGA Register PGACTL
#define PGA_REGISTER_PGACTL                   PGA_LOCK_PGACTL
//! PGA Register GAIN1TRIM
#define PGA_REGISTER_GAIN1TRIM                PGA_LOCK_PGAGAIN1TRIM
//! PGA Register GAIN3TRIM
#define PGA_REGISTER_GAIN3TRIM                PGA_LOCK_PGAGAIN3TRIM
//! PGA Register GAIN6TRIM
#define PGA_REGISTER_GAIN6TRIM                PGA_LOCK_PGAGAIN6TRIM
//! PGA Register GAIN12TRIM
#define PGA_REGISTER_GAIN12TRIM               PGA_LOCK_PGAGAIN12TRIM
//! PGA Register GAIN24TRIM
#define PGA_REGISTER_GAIN24TRIM               PGA_LOCK_PGAGAIN24TRIM

//*****************************************************************************
//
//! \internal
//! Checks PGA wrapper base address.
//!
//! \param base specifies the PGA wrapper base address.
//!
//! This function determines if a PGA wrapper base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool PGA_isBaseValid(uint32_t base)
{
    return((base == PGAA_BASE) || (base == PGAB_BASE)||
           (base == PGAC_BASE) || (base == PGAD_BASE)||
           (base == PGAE_BASE) || (base == PGAF_BASE)||
           (base == PGAG_BASE));
}
#endif

//*****************************************************************************
//
//! Enables PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function enables the PGA module.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_enable(uint32_t base)
{
   ASSERT(PGA_isBaseValid(base));

   EALLOW;
   // Set PGAEN bit
   HWREG(base + PGA_O_CTL) |= (uint32_t)PGA_CTL_PGAEN;
   EDIS;
}

//*****************************************************************************
//
//! Disables PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function disables the PGA module.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_disable(uint32_t base)
{
   ASSERT(PGA_isBaseValid(base));

   EALLOW;
   // Set PGAEN bit
   HWREG(base + PGA_O_CTL) &= (uint32_t)~PGA_CTL_PGAEN;
   EDIS;
}

//*****************************************************************************
//
//! Sets PGA gain value
//!
//! \param base is the base address of the PGA module.
//! \param gainValue is the PGA gain value.
//!
//! This function sets the PGA gain value.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_setGain(uint32_t base, PGA_GainValue gainValue)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    // Write to the GAIN bits
    HWREG(base + PGA_O_CTL) = ((HWREG(base + PGA_O_CTL) & ~PGA_CTL_GAIN_M) |
                               (uint16_t)gainValue);
    EDIS;
}

//*****************************************************************************
//
//! Sets PGA output filter resistor value
//!
//! \param base is the base address of the PGA module.
//! \param resistorValue is the PGA output resistor value.
//!
//! This function sets the resistor value for the PGA output low pass RC
//! filter. The resistance for the RC low pass filter is provided within the
//! microprocessor and is determined by the value of resistorValue. The
//! capacitor, however,has to be connected outside the microprocessor.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_setFilterResistor(uint32_t base,
                                       PGA_LowPassResistorValue resistorValue)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    // Write to the FILTRESSEL bits
    HWREG(base + PGA_O_CTL) =
                          ((HWREG(base + PGA_O_CTL) & ~PGA_CTL_FILTRESSEL_M) |
                           (uint16_t)resistorValue);
    EDIS;
}

//*****************************************************************************
//
//! Returns the PGA revision number.
//!
//! \param base is the base address of the PGA module.
//!
//! This function returns the PGA revision number.
//!
//! \return Returns PGA revision.
//
//*****************************************************************************
static inline uint16_t PGA_getPGARevision(uint32_t base)
{

    ASSERT(PGA_isBaseValid(base));

    // return PGA revision number
    return((uint16_t)(HWREGH(base + PGA_O_TYPE) & 0xFFU));
}

//*****************************************************************************
//
//! Returns the PGA Type.
//!
//! \param base is the base address of the PGA module.
//!
//! This function returns the PGA Type number.
//!
//! \return Returns PGA type.
//
//*****************************************************************************
static inline uint16_t PGA_getPGAType(uint32_t base)
{

    ASSERT(PGA_isBaseValid(base));

    // return PGA Type number
    return((uint16_t)(HWREGH(base + PGA_O_TYPE) >> 8U));
}

//*****************************************************************************
//
//! Locks PGA registers.
//!
//! \param base is the base address of the PGA module.
//! \param registerType is the PGA register to be locked.
//!
//! This function locks the PGA registers specified by registerType. Valid
//! values for registerType are: PGA_REGISTER_PGACTL,PGA_REGISTER_GAINxTRIM,
//! where x is 1,3,6,12 or 24.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_lockRegisters(uint32_t base, uint16_t registerType)
{

    ASSERT(PGA_isBaseValid(base));
    ASSERT(registerType < 0xFFU);

    EALLOW;
    // Write to the appropriate bits of PGALOCK register bits
    HWREGH(base + PGA_O_LOCK) |= registerType;
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

#endif // __PGA_H__
