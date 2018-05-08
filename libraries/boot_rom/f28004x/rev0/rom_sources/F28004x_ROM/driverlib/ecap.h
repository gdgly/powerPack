//###########################################################################
//
// FILE: ecap.h
//
// TITLE: C28x ECAP driver
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//#############################################################################

#ifndef __ECAP_H__
#define __ECAP_H__

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
//! \addtogroup ecap_api
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
#include "inc/hw_ecap.h"
#include "cpu.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
//
// eCAP minimum and maximum values
//
//*****************************************************************************
#define ECAP_MAX_PRESCALER_VALUE       32U  // Maximum Pre-scaler value

//*****************************************************************************
//
// Values that can be passed to intFlags parameter of
// ECAP_enableInterrupt, ECAP_disableInterrupt, ECAP_clearInterrupt and
// ECAP_forceInterrupt functions.
//
//*****************************************************************************
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_1 0x2U  // Event 1 ISR source
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_2 0x4U  // Event 2 ISR source
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_3 0x8U  // Event 3 ISR source
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_4 0x10U // Event 4 ISR source
#define ECAP_ISR_SOURCE_COUNTER_OVERFLOW 0x20U // Counter overflow ISR source
#define ECAP_ISR_SOURCE_COUNTER_PERIOD 0x40U   // Counter equals period
                                             // ISR source
#define ECAP_ISR_SOURCE_COUNTER_COMPARE 0x80U  //Counter equals compare
                                              // ISR source


//! \brief Enumeration to define the Emulation modes
//!
typedef enum
{
    //! TSCTR is stopped on emulation suspension
    ECAP_EMULATION_STOP = 0x0U ,
    //! TSCTR runs until 0 before stopping on emulation suspension
    ECAP_EMULATION_RUN_TO_ZERO = 0x1U,
    //! TSCTR is not affected by emulation suspension
    ECAP_EMULATION_FREE_RUN = 0x2U
}ECAP_EmulationMode;

//! \brief Enumeration to define the Capture modes
//!
typedef enum
{
    //! eCAP operates in continuous capture mode
    ECAP_CONTINUOUS_CAPTURE_MODE = 0U,
    //! eCAP operates in one shot capture mode
    ECAP_ONE_SHOT_CAPTURE_MODE = 1U
}ECAP_CaptureMode;

//! \brief Enumeration to define eCAP event identifiers
//!
typedef enum
{
    ECAP_EVENT_1 = 0U,   //!< eCAP event 1
    ECAP_EVENT_2 = 1U,   //!< eCAP event 2
    ECAP_EVENT_3 = 2U,   //!< eCAP event 3
    ECAP_EVENT_4 = 3U    //!< eCAP event 4
}ECAP_Events;

//! \brief Enumeration to define the Sync out mode
//!
typedef enum
{
    //! sync out on the sync in signal and software force
    ECAP_SYNC_OUT_SYNCI = (0x0U << 6U),
    //! sync out on counter equals period
    ECAP_SYNC_OUT_COUNTER_PRD = (0x1U << 6U),
    //! Disable sync out signal
    ECAP_SYNC_OUT_DISABLED = (0x2U << 6U)
}ECAP_SyncOutMode;

//! \brief Enumeration to define the APWM Polarity
//!
typedef enum
{
    ECAP_APWM_ACTIVE_HIGH = (0x0U << 10U), //!< APWM is active high
    ECAP_APWM_ACTIVE_LOW  = (0x1U << 10U)  //!< APWM is active low
}ECAP_APWMPolarity;

//! \brief Enumeration to define the Event Polarity
//!
typedef enum
{
    ECAP_EVNT_RISING_EDGE  = 0U, //!< Rising edge polarity
    ECAP_EVNT_FALLING_EDGE = 1U  //!< Falling edge polarity
}ECAP_EventPolarity;

//! \brief Enumeration to define the ECAP input signals
//!
typedef enum
{
    //! GPIO Input Crossbar output signal-1
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT1 = 0,
    //! GPIO Input Crossbar output signal-2
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT2 = 1,
    //! GPIO Input Crossbar output signal-3
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT3 = 2,
    //! GPIO Input Crossbar output signal-4
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT4 = 3,
    //! GPIO Input Crossbar output signal-5
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT5 = 4,
    //! GPIO Input Crossbar output signal-6
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT6 = 5,
    //! GPIO Input Crossbar output signal-7
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT7 = 6,
    //! GPIO Input Crossbar output signal-8
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT8 = 7,
    //! GPIO Input Crossbar output signal-9
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT9 = 8,
    //! GPIO Input Crossbar output signal-10
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT10 = 9,
    //! GPIO Input Crossbar output signal-11
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT11 = 10,
    //! GPIO Input Crossbar output signal-12
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT12 = 11,
    //! GPIO Input Crossbar output signal-13
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT13 = 12,
    //! GPIO Input Crossbar output signal-14
    ECAP_INPUT_GPIOTRIP_XBAR_INPUT14 = 13,
    //! Delay clock for measurement
    ECAP_INPUT_ECAP_DELAY_CLOCK = 23,
    //! Output Xbar Output-1
    ECAP_INPUT_XBAR_OUTPUT1 = 24,
    //! Output Xbar Output-2
    ECAP_INPUT_XBAR_OUTPUT2 = 25,
    //! Output Xbar Output-3
    ECAP_INPUT_XBAR_OUTPUT3 = 26,
    //! Output Xbar Output-4
    ECAP_INPUT_XBAR_OUTPUT4 = 27,
    //! Output Xbar Output-5
    ECAP_INPUT_XBAR_OUTPUT5 = 28,
    //! Output Xbar Output-6
    ECAP_INPUT_XBAR_OUTPUT6 = 29,
    //! Output Xbar Output-7
    ECAP_INPUT_XBAR_OUTPUT7 = 30,
    //! Output Xbar Output-8
    ECAP_INPUT_XBAR_OUTPUT8 = 31,
    //! ADCC Event4
    ECAP_INPUT_ADC_C_EVENTT4 = 36,
    //! ADCC Event3
    ECAP_INPUT_ADC_C_EVENTT3 = 37,
    //! ADCC Event2
    ECAP_INPUT_ADC_C_EVENTT2 = 38,
    //! ADCC Event1
    ECAP_INPUT_ADC_C_EVENTT1 = 39,
    //! ADCB Event4
    ECAP_INPUT_ADC_B_EVENTT4 = 40,
    //! ADCB Event3
    ECAP_INPUT_ADC_B_EVENTT3 = 41,
    //! ADCB Event2
    ECAP_INPUT_ADC_B_EVENTT2 = 42,
    //! ADCB Event1
    ECAP_INPUT_ADC_B_EVENTT1 = 43,
    //! ADCA Event4
    ECAP_INPUT_ADC_A_EVENTT4 = 44,
    //! ADCA Event3
    ECAP_INPUT_ADC_A_EVENTT3 = 45,
    //! ADCA Event2
    ECAP_INPUT_ADC_A_EVENTT2 = 46,
    //! ADCA Event1
    ECAP_INPUT_ADC_A_EVENTT1 = 47,
    //! SDFM-1 Filter-1 Compare Low Trip
    ECAP_INPUT_SDFM_FLT1_COMPARE_LOW = 64,
    //! SDFM-1 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM_FLT2_COMPARE_LOW = 65,
    //! SDFM-1 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM_FLT3_COMPARE_LOW = 66,
    //! SDFM-1 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM_FLT4_COMPARE_LOW = 67,
    //! SDFM-1 Filter-1 Compare High Trip
    ECAP_INPUT_SDFM_FLT1_COMPARE_HIGH = 80,
    //! SDFM-1 Filter-2 Compare High Trip
    ECAP_INPUT_SDFM_FLT2_COMPARE_HIGH = 81,
    //! SDFM-1 Filter-3 Compare High Trip
    ECAP_INPUT_SDFM_FLT3_COMPARE_HIGH = 82,
    //! SDFM-1 Filter-4 Compare High Trip
    ECAP_INPUT_SDFM_FLT4_COMPARE_HIGH = 83,
    //! SDFM-1 Filter-1 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM_FLT1_COMPARE_HIGH_OR_LOW = 88,
    //! SDFM-1 Filter-2 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM_FLT2_COMPARE_HIGH_OR_LOW = 89,
    //! SDFM-1 Filter-3 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM_FLT3_COMPARE_HIGH_OR_LOW = 90,
    //! SDFM-1 Filter-4 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM_FLT4_COMPARE_HIGH_OR_LOW = 91,
    //! Compare Subsystem-1 Low Trip
    ECAP_INPUT_CMPSS1_CTRIP_LOW = 96,
    //! Compare Subsystem-2 Low Trip
    ECAP_INPUT_CMPSS2_CTRIP_LOW = 97,
    //! Compare Subsystem-3 Low Trip
    ECAP_INPUT_CMPSS3_CTRIP_LOW = 98,
    //! Compare Subsystem-4 Low Trip
    ECAP_INPUT_CMPSS4_CTRIP_LOW = 99,
    //! Compare Subsystem-5 Low Trip
    ECAP_INPUT_CMPSS5_CTRIP_LOW = 100,
    //! Compare Subsystem-6 Low Trip
    ECAP_INPUT_CMPSS6_CTRIP_LOW = 101,
    //! Compare Subsystem-7 Low Trip
    ECAP_INPUT_CMPSS7_CTRIP_LOW = 102,
    //! Compare Subsystem-1 High Trip
    ECAP_INPUT_CMPSS1_CTRIP_HIGH = 108,
    //! Compare Subsystem-2 High Trip
    ECAP_INPUT_CMPSS2_CTRIP_HIGH = 109,
    //! Compare Subsystem-3 High Trip
    ECAP_INPUT_CMPSS3_CTRIP_HIGH = 110,
    //! Compare Subsystem-4 High Trip
    ECAP_INPUT_CMPSS4_CTRIP_HIGH = 111,
    //! Compare Subsystem-5 High Trip
    ECAP_INPUT_CMPSS5_CTRIP_HIGH = 112,
    //! Compare Subsystem-6 High Trip
    ECAP_INPUT_CMPSS6_CTRIP_HIGH = 113,
    //! Compare Subsystem-7 High Trip
    ECAP_INPUT_CMPSS7_CTRIP_HIGH = 114,
    //! Compare Subsystem-1 High Trip or Low Trip
    ECAP_INPUT_CMPSS1_CTRIP_HIGH_OR_LOW = 120,
    //! Compare Subsystem-2 High Trip or Low Trip
    ECAP_INPUT_CMPSS2_CTRIP_HIGH_OR_LOW = 121,
    //! Compare Subsystem-3 High Trip or Low Trip
    ECAP_INPUT_CMPSS3_CTRIP_HIGH_OR_LOW = 122,
    //! Compare Subsystem-4 High Trip or Low Trip
    ECAP_INPUT_CMPSS4_CTRIP_HIGH_OR_LOW = 123,
    //! Compare Subsystem-5 High Trip or Low Trip
    ECAP_INPUT_CMPSS5_CTRIP_HIGH_OR_LOW = 124,
    //! Compare Subsystem-6 High Trip or Low Trip
    ECAP_INPUT_CMPSS6_CTRIP_HIGH_OR_LOW = 125,
    //! Compare Subsystem-7 High Trip or Low Trip
    ECAP_INPUT_CMPSS7_CTRIP_HIGH_OR_LOW = 126
}ECAP_InputCaptureSignals;

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
static inline bool ECAP_isBaseValid(uint32_t base)
{

    return((base == ECAP1_BASE) || (base == ECAP2_BASE)||
           (base == ECAP3_BASE) || (base == ECAP4_BASE)||
           (base == ECAP5_BASE) || (base == ECAP6_BASE)||
           (base == ECAP7_BASE));
}
#endif

//*****************************************************************************
//
//! Sets the input prescaler.
//!
//! \param base is the base address of the ECAP module.
//! \param preScalerValue is the pre scaler value for ECAP input
//!
//! This function divides the ECAP input scaler. The pre scale value is
//! doubled inside the module. For example a preScalerValue of 5 will divide
//! the scaler by 10. Use a value of 1 to divide the pre scaler by 1.
//! The value of preScalerValue should be less than ECAP_MAX_PRESCALER_VALUE.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setEventPrescaler(uint32_t base,
                                          uint16_t preScalerValue)
{
    ASSERT(ECAP_isBaseValid( base));

    ASSERT(preScalerValue < ECAP_MAX_PRESCALER_VALUE);

    EALLOW;
    // write to PRESCALE bit
    HWREGH(base + ECAP_O_ECCTL1) =
                 ((HWREGH(base + ECAP_O_ECCTL1) & (~ECAP_ECCTL1_PRESCALE_M)) |
                    (preScalerValue << ECAP_ECCTL1_PRESCALE_S));
    EDIS;
}

//*****************************************************************************
//
//! Sets the Capture event polarity.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number.
//! \param polarity is the polarity of the event.
//!
//! This function sets the polarity of a given event. The value of event
//! is between ECAP_EVENT_1 and ECAP_EVENT_4 inclusive corresponding to the
//! four available events.For each event the polarity value determines the edge
//! on which the capture is activated. For a rising edge use a polarity value
//! of \b ECAP_EVNT_RISING_EDGE and for a falling edge use a polarity of
//! \b ECAP_EVNT_FALLING_EDGE.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setEventPolarity(uint32_t base,
                                         ECAP_Events event,
                                         ECAP_EventPolarity polarity)
{

    uint16_t shift;

    ASSERT(ECAP_isBaseValid( base));

    shift = ((uint16_t)event) << 1U;

    EALLOW;
    // write to CAP1POL, CAP2POL, CAP3POL or CAP4POL
    HWREGH(base + ECAP_O_ECCTL1) =
                         (HWREGH(base + ECAP_O_ECCTL1) & ~(1U << shift)) |
                          ((uint16_t)polarity << shift);
    EDIS;
}
//*****************************************************************************
//
//! Sets the capture mode.
//!
//! \param base is the base address of the ECAP module.
//! \param mode is the capture mode.
//! \param event is the event number at which the counter stops or wraps.
//!
//! This function sets the eCAP module to a continuous or one-shot mode.
//! The value of mode should be either ECAP_CONTINUOUS_CAPTURE_MODE or
//! ECAP_ONE_SHOT_CAPTURE_MODE corresponding to continuous or one-shot mode
//! respectively.
//!
//! The value of event determines the event number at which the counter stops
//! (in one-shot mode) or the counter wraps (in continuous mode). The value of
//! event should be between ECAP_EVENT_1 and ECAP_EVENT_4 corresponding to the
//! valid event numbers.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setCaptureMode(uint32_t base,
                                       ECAP_CaptureMode mode,
                                       ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // write to CONT/ONESHT
    HWREGH(base + ECAP_O_ECCTL2) =
               ((HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_CONT_ONESHT)) |
                (uint16_t)mode);
    // write to STOP_WRAP
    HWREGH(base + ECAP_O_ECCTL2) =
               ((HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_STOP_WRAP_M)) |
                (((uint16_t)event) << ECAP_ECCTL2_STOP_WRAP_S ));
    EDIS;
}
//*****************************************************************************
//
//! Re Arms the eCAP module.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function re-arms the eCAP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_reArm(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // write to RE-ARM bit
    HWREGH(base + ECAP_O_ECCTL2) = (HWREGH(base + ECAP_O_ECCTL2) |
                                    ECAP_ECCTL2_REARM);
    EDIS;
}
//*****************************************************************************
//
//! Enables interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source to be enabled.
//!
//! This function sets and enables eCAP interrupt source. The following are
//! valid interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableInterrupt(uint32_t base,
                                        uint16_t intFlags)
{
    ASSERT(ECAP_isBaseValid( base));
    ASSERT((intFlags > 1U) && (intFlags < 0xFFU));

    EALLOW;
    // set bits in ECEINT register
    HWREGH(base + ECAP_O_ECEINT) |= intFlags;
    EDIS;
}
//*****************************************************************************
//
//! Disables interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source to be disabled.
//!
//! This function clears and disables eCAP interrupt source. The following are
//! valid interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1   - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2   - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3   - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4   - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW  - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD    - Counter equal period generates
//!                                        interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE   - Counter equal compare generates
//!                                        interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableInterrupt(uint32_t base,
                                         uint16_t intFlags)
{

    ASSERT(ECAP_isBaseValid( base));
    ASSERT((intFlags > 1U) && (intFlags < 0xFFU));

    EALLOW;
    // clear bits in ECEINT register
    HWREGH(base + ECAP_O_ECEINT) &= ~intFlags;
    EDIS;
}
//*****************************************************************************
//
//! Returns the interrupt flag.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the eCAP interrupt flag. The following are valid
//! interrupt sources corresponding to the eCAP interrupt flag.
//!
//! \return Returns the eCAP interrupt that has occurred. The following are
//!  valid return values.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1   - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2   - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3   - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4   - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW  - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD    - Counter equal period generates
//!                                        interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE   - Counter equal compare generates
//!                                        interrupt
//!
//! \note - User can check if a combination of various interrupts have occurred
//!         by ORing the above return values.
//
//*****************************************************************************
static inline uint16_t ECAP_getInterruptSource(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    // return contents of ECFLG register
    return(HWREGH(base + ECAP_O_ECFLG) & 0xFEU);
}

//*****************************************************************************
//
//! Returns the Global interrupt flag.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the eCAP Global interrupt flag.
//!
//! \return Returns true if there is a global eCAP interrupt, false otherwise.
//
//*****************************************************************************
static inline bool ECAP_getGlobalInterruptStatus(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    // return contents of Global interrupt bit
    if((HWREGH(base + ECAP_O_ECFLG) & 0x1U) == 0x1U)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}
//*****************************************************************************
//
//! Clears interrupt flag.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source.
//!
//! This function clears eCAP interrupt flags. The following are valid
//! interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_clearInterrupt(uint32_t base,
                                       uint16_t intFlags)
{
    ASSERT(ECAP_isBaseValid( base));
    ASSERT((intFlags > 1U) && (intFlags < 0xFFU));

    // write to ECCLR register
    HWREGH(base + ECAP_O_ECCLR) |= intFlags;
}
//*****************************************************************************
//
//! Clears global interrupt flag
//!
//! \param base is the base address of the ECAP module.
//!
//! This function clears the global interrupt bit.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_clearGlobalInterrupt(uint32_t base)
{

    ASSERT(ECAP_isBaseValid( base));

    // write to INT bit
    HWREGH(base + ECAP_O_ECCLR) |= 0x1U;
}
//*****************************************************************************
//
//! Forces interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source.
//!
//! This function forces and enables eCAP interrupt source. The following are
//! valid interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_forceInterrupt(uint32_t base,
                                       uint16_t intFlags)
{
    ASSERT(ECAP_isBaseValid( base));
    ASSERT((intFlags > 1U) && (intFlags < 0xFFU));

    EALLOW;
    // write to ECFRC register
    HWREGH(base + ECAP_O_ECFRC) =
                      (HWREGH(base + ECAP_O_ECFRC) | intFlags);
    EDIS;
}
//*****************************************************************************
//
//! Sets eCAP in Capture mode.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function sets the eCAP module to operate in Capture mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableCaptureMode(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // clear CAP/APWM bit
    HWREGH(base + ECAP_O_ECCTL2) =
                      (HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_CAP_APWM));
    EDIS;
}
//*****************************************************************************
//
//! Sets eCAP in APWM mode.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function sets the eCAP module to operate in APWM mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableAPWMMode(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // set CAP/APWM bit
    HWREGH(base + ECAP_O_ECCTL2) =
                        (HWREGH(base + ECAP_O_ECCTL2) | ECAP_ECCTL2_CAP_APWM);
    EDIS;
}

//*****************************************************************************
//
//! Enables counter reset on an event.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number the time base gets reset.
//!
//! This function enables the base timer , TSCTR , to be reset on capture
//! event provided by the variable event. Valid inputs for event are
//! ECAP_EVENT_1 to ECAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableCounterResetOnEvent(uint32_t base,
                                                  ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // set CTRRST1,CTRRST2,CTRRST3 or CTRRST4 bits
    HWREGH(base + ECAP_O_ECCTL1) =
         (HWREGH(base + ECAP_O_ECCTL1) |(1U << ((2U * (uint16_t)event) + 1U)));
    EDIS;
}
//*****************************************************************************
//
//! Disables counter reset on events.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number the time base gets reset.
//!
//! This function disables the base timer ,TSCTR , from being reset on capture
//! event provided by the variable event. Valid inputs for event are 1 to 4.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableCounterResetOnEvent(uint32_t base,
                                                   ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid( base));

    ASSERT((event >= 1U) || (event <= 4U));

    EALLOW;
    // clear CTRRST1,CTRRST2,CTRRST3 or CTRRST4 bits
    HWREGH(base + ECAP_O_ECCTL1) =
       (HWREGH(base + ECAP_O_ECCTL1) & ~(1U << ((2U * (uint16_t)event) + 1U)));
    EDIS;
}
//*****************************************************************************
//
//! Enables time stamp capture.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function enables time stamp count to be captured
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableTimeStampCapture(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // set CAPLDEN bit
    HWREGH(base + ECAP_O_ECCTL1) =
                         (HWREGH(base + ECAP_O_ECCTL1) | ECAP_ECCTL1_CAPLDEN);
    EDIS;
}
//*****************************************************************************
//
//! Disables time stamp capture.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function disables time stamp count to be captured
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableTimeStampCapture(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // clear CAPLDEN bit
    HWREGH(base + ECAP_O_ECCTL1) =
                      (HWREGH(base + ECAP_O_ECCTL1) & (~ECAP_ECCTL1_CAPLDEN));
    EDIS;
}

//*****************************************************************************
//
//! Sets a phase shift value count.
//!
//! \param base is the base address of the ECAP module.
//! \param shiftCount is the Phase shift value.
//!
//! This function writes a Phase shift value to be loaded into the main time
//! stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setPhaseShiftCount(uint32_t base, uint32_t shiftCount)
{
   ASSERT(ECAP_isBaseValid( base));

    // write to CTRPHS
    HWREG(base + ECAP_O_CTRPHS) = shiftCount;
}

//*****************************************************************************
//
//! Enable counter loading with phase shift value.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function enables loading of the counter with the value present in the
//! Phase shift counter as defined by the ECAP_setPhaseShiftCount() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableLoadCounter(uint32_t base)
{

    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // write to SYNCI_EN
    HWREGH(base + ECAP_O_ECCTL2) =
                         (HWREGH(base + ECAP_O_ECCTL2) | ECAP_ECCTL2_SYNCI_EN);
    EDIS;
}
//*****************************************************************************
//
//! Disable counter loading with phase shift value.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function disables loading of the counter with the value present in the
//! Phase shift counter as defined by the ECAP_setPhaseShiftCount() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableLoadCounter(uint32_t base)
{

    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // write to SYNCI_EN
    HWREGH(base + ECAP_O_ECCTL2) =
                     (HWREGH(base + ECAP_O_ECCTL2) & ~(ECAP_ECCTL2_SYNCI_EN));
    EDIS;
}
//*****************************************************************************
//
//! Load time stamp counter
//!
//! \param base is the base address of the ECAP module.
//!
//! This function forces the value in the phase shift counter register to be
//! loaded into Time stamp counter register.
//! Make sure to enable loading of Time stamp counter by calling
//! ECAP_enableLoadCounter() function before calling this function.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_loadCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // write to SWSYNC
    HWREGH(base + ECAP_O_ECCTL2) =
                          (HWREGH(base + ECAP_O_ECCTL2) | ECAP_ECCTL2_SWSYNC);
    EDIS;
}

//*****************************************************************************
//
//! Configures Sync out signal mode.
//!
//! \param base is the base address of the ECAP module.
//! \param mode is the sync out mode.
//!
//! This function sets the sync out mode. Valid parameters for mode are:
//! - ECAP_SYNC_OUT_SYNCI - Trigger sync out on sync-in event.
//! - ECAP_SYNC_OUT_COUNTER_PRD - Trigger sync out when counter equals period.
//! - ECAP_SYNC_OUT_DISABLED - Disable sync out.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setSyncOutMode(uint32_t base,
                                       ECAP_SyncOutMode mode)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
     // write to SYNCO_SEL
     HWREGH(base + ECAP_O_ECCTL2) =
                ((HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_SYNCO_SEL_M)) |
                 (uint16_t)mode);
    EDIS;
}
//*****************************************************************************
//
//! Stops Time stamp counter.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function stops the time stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_stopCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
     // clear TSCTR
     HWREGH(base + ECAP_O_ECCTL2) =
                    (HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_TSCTRSTOP));
    EDIS;
}
//*****************************************************************************
//
//! Starts Time stamp counter.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function starts the time stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_startCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // set TSCTR
    HWREGH(base + ECAP_O_ECCTL2) =
                      (HWREGH(base + ECAP_O_ECCTL2) | ECAP_ECCTL2_TSCTRSTOP);
    EDIS;
}
//*****************************************************************************
//
//! Set eCAP APWM polarity.
//!
//! \param base is the base address of the ECAP module.
//! \param polarity is the polarity of APWM
//!
//! This function sets the polarity of the eCAP in APWM mode. Valid inputs for
//! polarity are:
//!  - ECAP_APWM_ACTIVE_HIGH - For active high.
//!  - ECAP_APWM_ACTIVE_LOW - For active low.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMPolarity(uint32_t base,
                                        ECAP_APWMPolarity polarity)
{

    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    HWREGH(base + ECAP_O_ECCTL2) =
               ((HWREGH(base + ECAP_O_ECCTL2) & ~ECAP_ECCTL2_APWMPOL) |
                (uint16_t)polarity);
    EDIS;
}
//*****************************************************************************
//
//! Set eCAP APWM period.
//!
//! \param base is the base address of the ECAP module.
//! \param periodCount is the period count for APWM.
//!
//! This function sets the period count of the APWM waveform.
//! periodCount takes the actual count which is written to the register. The
//! user is responsible for converting the desired frequency or time into
//! the period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMPeriod(uint32_t base, uint32_t periodCount)
{
    ASSERT(ECAP_isBaseValid( base));

    // write to CAP1
    HWREG(base + ECAP_O_CAP1) = periodCount;
}
//*****************************************************************************
//
//! Set eCAP APWM on or off time count.
//!
//! \param base is the base address of the ECAP module.
//! \param compareCount is the on or off count for APWM.
//!
//! This function sets the on or off time count of the APWM waveform depending
//! on the polarity of the output. If the output , as set by
//! ECAP_setAPWMPolarity(), is active high then compareCount determines the on
//! time. If the output is active low then compareCount determines the off
//! time.compareCount takes the actual count which is written to the register.
//! The user is responsible for converting the desired frequency or time into
//! appropriate count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMCompare(uint32_t base, uint32_t compareCount)
{
    ASSERT(ECAP_isBaseValid( base));

    // write to CAP2
    HWREG(base + ECAP_O_CAP2) = compareCount;
}
//*****************************************************************************
//
//! Load eCAP APWM shadow period.
//!
//! \param base is the base address of the ECAP module.
//! \param periodCount is the shadow period count for APWM.
//!
//! This function sets the shadow period count of the APWM waveform.
//! periodCount takes the actual count which is written to the register. The
//! user is responsible for converting the desired frequency or time into
//! the period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMShadowPeriod(uint32_t base,
                                            uint32_t periodCount)
{
    ASSERT(ECAP_isBaseValid( base));

    // write to CAP3
    HWREG(base + ECAP_O_CAP3) = periodCount;
}

//*****************************************************************************
//
//! Set eCAP APWM shadow on or off time count.
//!
//! \param base is the base address of the ECAP module.
//! \param compareCount is the on or off count for APWM.
//!
//! This function sets the shadow on or off time count of the APWM waveform
//! depending on the polarity of the output. If the output , as set by
//! ECAP_setAPWMPolarity() , is active high then compareCount determines the
//! on time. If the output is active low then compareCount determines the off
//! time. compareCount takes the actual count which is written to the register.
//! The user is responsible for converting the desired frequency or time into
//! appropriate count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMShadowCompare(uint32_t base,
                                             uint32_t compareCount)
{
    ASSERT(ECAP_isBaseValid( base));

    // write to CAP4
    HWREG(base + ECAP_O_CAP4) = compareCount;
}
//*****************************************************************************
//
//! Returns event Time stamp.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number.
//!
//! This function returns the current Time stamp count of the given event.
//! Valid values for event are ECAP_EVENT_1 to ECAP_EVENT_4.
//!
//! \return Event time stamp value. or 0 if \e event is invalid.
//
//*****************************************************************************
static inline uint32_t ECAP_getEventTimeStamp(uint32_t base, ECAP_Events event)
{
    uint32_t count;

    ASSERT(ECAP_isBaseValid( base));


    switch(event)
    {
        case ECAP_EVENT_1:
            // read CAP1 register
            count = HWREG(base + ECAP_O_CAP1);
        break;

        case ECAP_EVENT_2:
            // read CAP2 register
            count = HWREG(base + ECAP_O_CAP2);
        break;

        case ECAP_EVENT_3:
            // read CAP3 register
            count = HWREG(base + ECAP_O_CAP3);
        break;

        case ECAP_EVENT_4:
            // read CAP4 register
            count = HWREG(base + ECAP_O_CAP4);
        break;

        default:
            count = 0U;
        break;
    }

    return(count);
}
//*****************************************************************************
//
//! Select eCAP input.
//!
//! \param base is the base address of the ECAP module.
//! \param input is the eCAP input signal.
//!
//! This function selects the eCAP input signal.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_selectECAPInput(uint32_t base,
                                        ECAP_InputCaptureSignals input)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // write to ECCTL0
    HWREG(base + ECAP_O_ECCTL0) =
                    ((HWREG(base + ECAP_O_ECCTL0) & ~ECAP_ECCTL0_INPUTSEL_M) |
                      input);
    EDIS;
}

//*****************************************************************************
//
//! Resets eCAP counters and flags.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function resets the main Counter (TSCTR register) , event filter,
//! modulo counter, capture events and counter overflow flags
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_resetCounters(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // write to ECCTL2
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_CTRFILTRESET;
    EDIS;
}

//*****************************************************************************
//
//! Sets the eCAP DMA source.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the eCAP event for the DMA
//!
//! This function sets the eCAP event source for the DMA.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setDMASource(uint32_t base,  ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid( base));

    EALLOW;
    // write to ECCTL2
    HWREGH(base + ECAP_O_ECCTL2) =
               ((HWREGH(base + ECAP_O_ECCTL2) & ~ECAP_ECCTL2_DMAEVTSEL_M) |
                ((uint16_t)event << ECAP_ECCTL2_DMAEVTSEL_S));
    EDIS;
}

//*****************************************************************************
//
//! Return the Modulo counter status.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the Modulo counter status.
//!
//! \return .
//
//*****************************************************************************
static inline uint16_t ECAP_getModuloCounterStatus(uint32_t base)
{
    ASSERT(ECAP_isBaseValid( base));

    // Read MODCNTRSTS bit
    return((HWREGH(base + ECAP_O_ECCTL2) & ECAP_ECCTL2_MODCNTRSTS_M)
                >> ECAP_ECCTL2_MODCNTRSTS_S);
}

// API Function prototypes

//*****************************************************************************
//
//! Configures emulation mode.
//!
//! \param base is the base address of the ECAP module.
//! \param mode is the emulation mode.
//!
//! This function configures the eCAP counter, TSCTR,  to the desired emulation
//! mode when emulation suspension occurs. Valid input for mode are:
//! - ECAP_EMULATION_STOP  - Counter is stopped immediately.
//! - ECAP_EMULATION_RUN_TO_ZERO - Counter runs till it reaches 0.
//! - ECAP_EMULATION_FREE_RUN - Counter is not affected.
//!
//! \return None.
//
//*****************************************************************************
extern void ECAP_setEmulationMode(uint32_t base,
                                   ECAP_EmulationMode mode);

//*****************************************************************************
//
//! Registers eCAP interrupt handler
//!
//! \param base is the base address of the eCAP instance used.
//! \param handler is a pointer to the function to be called when the
//! serial peripheral interface interrupt occurs.
//!
//! This function registers the handler to be called when an eCAP interrupt
//! occurs.  This function enables the global interrupt in the interrupt
//! controller.
//! Specific eCAP interrupts must be enabled via ECAP_enableInterrupt().
//! If necessary, it is the interrupt handler's responsibility
//! to clear the interrupt source via ECAP_clearInterrupt().
//!
//! \sa Interrupt_register() for important information about registering
//!     interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void ECAP_registerInterrupt(uint32_t base, void (*handler)(void));

//*****************************************************************************
//
//! Unregisters eCAP interrupt handler.
//!
//! \param base is the base address of the eCAP instance used.
//!
//! This function clears the handler to be called when an eCAP interrupt
//! occurs.  This function also masks off the interrupt in the interrupt
//! controller so that the interrupt handler no longer is called.
//!
//! \sa Interrupt_register() for important information about registering
//!     interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void ECAP_unregisterInterrupt(uint32_t base);

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

#endif // __ECAP_H__
