//###########################################################################
//
// FILE:  hrcap.h
//
// TITLE: C28x HRCAP Driver.
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//#############################################################################

#ifndef __HRCAP_H__
#define __HRCAP_H__

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
//! \addtogroup hrcap_api
//! @{
//
//*****************************************************************************

// ****************************************************************************
// the includes
// ****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_hrcap.h"
#include "cpu.h"
#include "debug.h"
#include "interrupt.h"
#include "ecap.h"

//*****************************************************************************
//
// Values that can be passed as intFlags variable to the
// HRCAP_enableCalibrationInterrupt, HRCAP_disableCalibrationInterrupt,
// HRCAP_clearCalibrationInterrupt functions.
//
//*****************************************************************************

//! Global Calibration interrupt
#define HRCAP_GLOBAL_CALIBRATION_INTERRUPT 0x1U
//! Calibration done interrupt
#define HRCAP_CALIBRATION_DONE_INTERRUPT  0x2U
//! Calibration period check interrupt
#define HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT 0x4U


//! \brief Enumeration to define clock source for Period match
//!
typedef enum
{
    HRCAP_CALIBRATION_CLOCK_SYSCLK = 0 << 2, //!< Use SYSCLK for period match.
    HRCAP_CALIBRATION_CLOCK_HRCLK  = 1 << 2  //!< Use HRCLK for period match.
}HRCAP_CalibrationClockSource;

//! \brief Enumeration to define continuous calibration mode.
//!
typedef enum
{
    //! Continuous calibration disabled.
    HRCAP_CONTINUOUS_CALIBRATION_DISABLED = 0 << 5,
    //! Continuous calibration enabled.
    HRCAP_CONTINUOUS_CALIBRATION_ENABLED =  1 << 5
}HRCAP_ContinuousCalibrationMode;

// API functions that are defined in ECAP module
#define HRCAP_setEventPrescaler           ECAP_setEventPrescaler
#define HRCAP_setEventPolarity            ECAP_setEventPolarity
#define HRCAP_setCaptureMode              ECAP_setCaptureMode
#define HRCAP_reArm                       ECAP_reArm
#define HRCAP_enableInterrupt             ECAP_enableInterrupt
#define HRCAP_disableInterrupt            ECAP_disableInterrupt
#define HRCAP_getInterruptSource          ECAP_getInterruptSource
#define HRCAP_getGlobalInterruptStatus    ECAP_getGlobalInterruptStatus
#define HRCAP_clearInterrupt              ECAP_clearInterrupt
#define HRCAP_clearGlobalInterrupt        ECAP_clearGlobalInterrupt
#define HRCAP_forceInterrupt              ECAP_forceInterrupt
#define HRCAP_setOperatingMode            ECAP_setOperatingMode
#define HRCAP_enableCounterResetOnEvent   ECAP_enableCounterResetOnEvent
#define HRCAP_disableCounterResetOnEvent  ECAP_disableCounterResetOnEvent
#define HRCAP_setCaptureRegisterLoadMode  ECAP_setCaptureRegisterLoadMode
#define HRCAP_setEmulationMode            ECAP_setEmulationMode
#define HRCAP_setPhaseShiftCount          ECAP_setPhaseShiftCount
#define HRCAP_setCounterLoadOnSyncMode    ECAP_setCounterLoadOnSyncMode
#define HRCAP_loadCounter                 ECAP_loadCounter
#define HRCAP_setSyncOutMode              ECAP_setSyncOutMode
#define HRCAP_stopCounter                 ECAP_stopCounter
#define HRCAP_startCounter                ECAP_startCounter
#define HRCAP_setAPWMPolarity             ECAP_setAPWMPolarity
#define HRCAP_setAPWMPeriod               ECAP_setAPWMPeriod
#define HRCAP_setAPWMCompare              ECAP_setAPWMCompare
#define HRCAP_setAPWMShadowPeriod         ECAP_setAPWMShadowPeriod
#define HRCAP_setAPWMShadowCompare        ECAP_setAPWMShadowCompare
#define HRCAP_getEventTimeStamp           ECAP_getEventTimeStamp
#define HRCAP_selectECAPInput             ECAP_selectECAPInput
#define HRCAP_resetCounters               ECAP_resetCounters
#define HRCAP_setDMASource                ECAP_setDMASource
#define HRCAP_getModuloCounterStatus      ECAP_getModuloCounterStatus
#define HRCAP_registerInterrupt           ECAP_registerInterrupt
#define HRCAP_unregisterInterrupt         ECAP_unregisterInterrupt

//*****************************************************************************
//
//! \internal
//! Checks eCAP base address.
//!
//! \param base specifies the eCAP module base address.
//!
//! This function determines if an eCAP module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool HRCAP_isBaseValid(uint32_t base)
{
    return((base == ECAP6_BASE)|| (base == ECAP7_BASE));
}
#endif

//*****************************************************************************
//
//! enables HRCAP.
//!
//! \param base is the base address of the eCAP instance used.
//!
//! This function enables High Resolution Capture module.
//!
//! \note High resolution clock must be enabled before High Resolution Module
//!       is enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_enableHighResolution(uint32_t base)
{
     ASSERT(HRCAP_isBaseValid(base));

     EALLOW;
     // Set HRE bit
     HWREG(base + HRCAP_O_HRCTL) |= (uint32_t)HRCAP_HRCTL_HRE;
     EDIS;
}

//*****************************************************************************
//
//! Disables HRCAP.
//!
//! \param base is the base address of the eCAP instance used.
//!
//! This function disable High Resolution Capture module.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_disableHighResolution(uint32_t base)
{
     ASSERT(HRCAP_isBaseValid(base));

     EALLOW;
     // Set HRE bit
     HWREG(base + HRCAP_O_HRCTL) &= ~(uint32_t)HRCAP_HRCTL_HRE;
     EDIS;
}

//*****************************************************************************
//
//! Enables High resolution clock.
//!
//! \param base is the base address of the eCAP instance used.
//!
//! This function enables High Resolution clock.
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_enableHighResolutionClock(uint32_t base)
{
     ASSERT(HRCAP_isBaseValid(base));

     EALLOW;
     // Set HRCLKE bit
     HWREG(base + HRCAP_O_HRCTL) |= (uint32_t)HRCAP_HRCTL_HRCLKE;
     EDIS;
}

//*****************************************************************************
//
//! Disables High resolution clock.
//!
//! \param base is the base address of the eCAP instance used.
//!
//! This function disables High Resolution clock.
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_disbleHighResolutionClock(uint32_t base)
{
     ASSERT(HRCAP_isBaseValid(base));

     EALLOW;
     // Clear HRCLKE bit
     HWREG(base + HRCAP_O_HRCTL) &= ~(uint32_t)HRCAP_HRCTL_HRCLKE;
     EDIS;
}

//*****************************************************************************
//
//! Starts Calibration.
//!
//! \param base is the base address of the eCAP instance used.
//!
//! This function starts Calibration.
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_startCalibration(uint32_t base)
{
     ASSERT(HRCAP_isBaseValid(base));

     EALLOW;
     // Set CALIBSTART bit
     HWREG(base + HRCAP_O_HRCTL) |= (uint32_t)HRCAP_HRCTL_CALIBSTART;
     EDIS;
}

//*****************************************************************************
//
//! Sets the Calibration mode.
//!
//! \param base is the base address of the eCAP instance used.
//! \param clockSource is calibration period match selection.
//! \param continuousMode is the continuous calibration mode selection.
//!
//! This function sets the the Calibration mode by setting the Calibration
//! period match select bit and the continuous calibration selection bit.
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_setCalibrationMode(uint32_t base,
                            HRCAP_CalibrationClockSource clockSource,
                            HRCAP_ContinuousCalibrationMode continuousMode)
{
     ASSERT(HRCAP_isBaseValid(base));

     EALLOW;
     // write to CALIBSTS and CALIBCONT bits
     HWREG(base + HRCAP_O_HRCTL) =
       ((HWREG(base + HRCAP_O_HRCTL) &
        ~(uint32_t)(HRCAP_HRCTL_PRDSEL | HRCAP_HRCTL_CALIBCONT)) |
        ((uint32_t)clockSource | (uint32_t)continuousMode));
     EDIS;
}

//*****************************************************************************
//
//! Enables Calibration interrupt.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the Calibration interrupt source to be enabled.
//!
//! This function enables HRCAP Calibration interrupt source.
//! Valid values for intFlags are:
//!     - HRCAP_CALIBRATION_DONE_INTERRUPT   - Calibration done interrupt.
//!     - HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT - Calibration period check
//!                                                   interrupt.
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_enableCalibrationInterrupt(uint32_t base,
                                                    uint16_t intFlags)
{
     ASSERT(HRCAP_isBaseValid(base));
     ASSERT((intFlags == HRCAP_CALIBRATION_DONE_INTERRUPT) ||
           (intFlags == HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT));

     EALLOW;
     // Set CALIBDONE or CALPRDCHKSTS
     HWREG(base + HRCAP_O_HRINTEN) |= (uint32_t)intFlags;
     EDIS;
}

//*****************************************************************************
//
//! Disables Calibration interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the Calibration interrupt source to be disabled.
//!
//! This function disables HRCAP Calibration interrupt source.
//! Valid values for intFlags are:
//!     - HRCAP_CALIBRATION_DONE_INTERRUPT   - Calibration done interrupt.
//!     - HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT - Calibration period check
//!                                                   interrupt.
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_disableCalibrationInterrupt(uint32_t base,
                                                     uint16_t intFlags)
{
     ASSERT(HRCAP_isBaseValid(base));
     ASSERT((intFlags == HRCAP_CALIBRATION_DONE_INTERRUPT) ||
           (intFlags == HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT));
     EALLOW;
     // Clear CALIBDONE or CALPRDCHKSTS
     HWREG(base + HRCAP_O_HRINTEN) &= ~(uint32_t)intFlags;
     EDIS;
}

//*****************************************************************************
//
//! Returns the Calibration interrupt source.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the HRCAP Calibration interrupt flag.
//!
//! \return Returns the HRCAP interrupt that has occurred. The following are
//!  valid return values.
//!     - HRCAP_GLOBAL_CALIBRATION_INTERRUPT - Global Calibration interrupt.
//!     - HRCAP_CALIBRATION_DONE_INTERRUPT   - Calibration done interrupt.
//!     - HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT - Calibration period check
//!                                                   interrupt.
//!
//! \note - User can check if a combination of the interrupts have occurred
//!         by ORing the above return values.
//
//*****************************************************************************
static inline uint16_t HRCAP_getCalibrationInterruptSource(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    // return contents of HRFLG register
    return((uint16_t)(HWREG(base + HRCAP_O_HRFLG) & 0x7U));
}

//*****************************************************************************
//
//! Clears Calibration interrupt flag.
//!
//! \param base is the base address of the HRCAP module.
//! \param intFlags is the Calibration interrupt source.
//!
//! This function clears HRCAP Calibration interrupt flags.
//! The following are valid values for intFlags.
//!     - HRCAP_GLOBAL_CALIBRATION_INTERRUPT - Global Calibration interrupt.
//!     - HRCAP_CALIBRATION_DONE_INTERRUPT   - Calibration done interrupt.
//!     - HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT - Calibration period check
//!                                                   interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_clearCalibrationInterrupt(uint32_t base,
                                                   uint16_t intFlags)
{
    ASSERT(HRCAP_isBaseValid(base));
    ASSERT((intFlags == HRCAP_CALIBRATION_DONE_INTERRUPT) ||
           (intFlags == HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT) ||
           (intFlags == HRCAP_GLOBAL_CALIBRATION_INTERRUPT));

    // write to HRCLR register
    HWREG(base + HRCAP_O_HRCLR) |= (uint32_t)intFlags;
}

//*****************************************************************************
//
//! Return the Calibration status
//!
//! \param base is the base address of the eCAP instance used.
//!
//! This function returns the Calibration status.
//!
//! \return This functions returns 1 if the Calibration is in process,0 if
//!         there is no active calibration.
//
//*****************************************************************************
static inline uint16_t HRCAP_getCalibrationStatus(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));
    // Read CALIBSTS bit
    return((uint16_t)((HWREG(base + HRCAP_O_HRCTL) &
                      (uint32_t)HRCAP_HRCTL_CALIBSTS) >> 4U));
}

//*****************************************************************************
//
//! Force a software based Calibration interrupt
//!
//! \param base is the base address of the eCAP instance used.
//! \param intFlags is the Calibration interrupt source.
//!
//! This function forces a software based Calibration done interrupt.
//! The following are valid values for intFlags.
//!     - HRCAP_CALIBRATION_DONE_INTERRUPT   - Calibration done interrupt.
//!     - HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT - Calibration period check
//!                                                   interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_swForceCalibrationInterrupt(uint32_t base,
                                                     uint16_t intFlags)
{
    ASSERT(HRCAP_isBaseValid( base));
    ASSERT((intFlags == HRCAP_CALIBRATION_DONE_INTERRUPT) ||
           (intFlags == HRCAP_CALIBRATION_PERIOD_CHECK_INTERRUPT));

    EALLOW;
    // write to CALIBDONE or CALPRDCHKSTS bit
    HWREG(base + HRCAP_O_HRFRC) |= (uint32_t)intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Sets the Calibration period count
//!
//! \param base is the base address of the eCAP instance used.
//! \param period is the Calibration period count.
//!
//! This function sets the Calibration period count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_setCalibrationPeriod(uint32_t base, uint32_t period)
{
    ASSERT(HRCAP_isBaseValid( base));

    EALLOW;
    HWREG(base + HRCAP_O_HRCALPRD) = period;
    EDIS;
}

//*****************************************************************************
//
//! Return the Calibration clock period
//!
//! \param base is the base address of the eCAP instance used.
//! \param clockSource is the Calibration clock source.
//!
//! This function returns the period match value of the Calibration clock. The
//! return value has a valid count when a period match occurs.
//!
//! \return This function returns the captured value of the clock counter
//!         specified by clockSource.
//
//*****************************************************************************
static inline uint32_t HRCAP_getCalibrationClockPeriod(uint32_t base,
                                     HRCAP_CalibrationClockSource clockSource)
{
    ASSERT(HRCAP_isBaseValid( base));
    //return HRCAP_O_HRSYSCLKCAP or HRCAP_O_HRCLKCAP
    return(HWREG(base + HRCAP_O_HRSYSCLKCAP + (2U *(uint16_t)clockSource)));
}

//*****************************************************************************
//
//! Set the Calibration clock counter
//!
//! \param base is the base address of the eCAP instance used.
//! \param clockSource is the Calibration clock source.
//! \param count is the count value to set the
//!
//! This function sets the Calibration clock counter to a value specified by
//! count.
//!
//! \return None.
//
//*****************************************************************************
static inline void HRCAP_setCalibrationClockCounter(uint32_t base,
                      HRCAP_CalibrationClockSource clockSource, uint32_t count)
{
    ASSERT(HRCAP_isBaseValid( base));
    //write to HRCAP_O_HRSYSCLKCAP or HRCAP_O_HRCLKCAP
    HWREG(base + HRCAP_O_HRSYSCLKCAP + (2U*(uint16_t)clockSource)) = count;
}

//*****************************************************************************
//
//! Set the Calibration clock counter
//!
//! \param base is the base address of the eCAP instance used.
//! \param clockSource is the Calibration clock source.
//!
//! This function returns the current counter value of the Calibration clock
//! specified by clockSource
//!
//! \return This function returns the current clock counter value specified
//!          by clockSource.
//
//*****************************************************************************
static inline uint32_t HRCAP_getCalibrationClockCounter(uint32_t base,
                                     HRCAP_CalibrationClockSource clockSource)
{
    ASSERT(HRCAP_isBaseValid( base));
    //write to HRCAP_O_HRSYSCLKCTR or HRCAP_O_HRCLKCTR
    return(HWREG(base + HRCAP_O_HRSYSCLKCTR + (2U*(uint16_t)clockSource)));
}

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Registers HRCAP Calibration interrupt handler
//!
//! \param base is the base address of the eCAP instance used.
//! \param handler is a pointer to the function to be called when the
//! serial peripheral interface interrupt occurs.
//!
//! This function registers the handler to be called when an HRCAP Calibration
//! interrupt occurs.  This function enables the global interrupt in the
//! interrupt controller.
//! Specific HRCAP interrupts must be enabled via
//! HRCAP_enableCalibrationInterrupt(). If necessary, it is the interrupt
//! handler's responsibility to clear the interrupt source via
//! HRCAP_clearCalibrationInterrupt() and
//! HRCAP_clearGlobalCalibrationInterrupt() function.
//!
//! \sa Interrupt_register() for important information about registering
//!     interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void HRCAP_registerCalibrationInterrupt(uint32_t base,
                                               void (*handler)(void));

//*****************************************************************************
//
//! Unregisters HRCAP interrupt handler.
//!
//! \param base is the base address of the HRCAP instance used.
//!
//! This function clears the handler to be called when an HRCAP Calibration
//! interrupt occurs.  This function also masks off the interrupt in the
//! interrupt controller so that the interrupt handler no longer is called.
//!
//! \sa Interrupt_register() for important information about registering
//!     interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void HRCAP_unregisterCalibrationInterrupt(uint32_t base);

//*****************************************************************************
// Close the Doxygen group.
//! @}
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __HRCAP_H__
