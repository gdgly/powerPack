//###########################################################################
//
// FILE:   dcc.h
//
// TITLE:  Stellaris style wrapper driver for C28x DCC peripheral.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __DCC_H__
#define __DCC_H__

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
//! \addtogroup dcc_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_dcc.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//
// The reset value required to start or enable specific DCC operations
//
#define DCC_ENABLE_VALUE     (0xAU)

//
// The reset value required to stop or disable specific DCC operations
//
#define DCC_DISABLE_VALUE    (0x5U)

//
// A 16-bit register mask
//
#define DCC_REG_WORD_MASK    (0xFFFFU)

//
// A 8-bit register mask
//
#define DCC_REG_BYTE_MASK    (0xFFU)

//
// A mask for the DCC counter seed registers
//
#define DCC_SEED_REG_MASK    (0xFFF0U)

//
// A mask for the DCC counter seed value
//
#define DCC_SEED_CNT_MASK    (0xF0000U)

//*****************************************************************************
//
//! The following are defines for the mode parameter of the
//! DCC_enableSingleShotMode() function.
//
//*****************************************************************************
typedef enum
{
    //!< Use to stop counting when counter0 and valid0 both reach zero
    DCC_MODE_COUNTER_ZERO = 0xA00U,
    
    //!< Use to stop counting when counter1 reaches zero
    DCC_MODE_COUNTER_ONE  = 0xB00U
} DCC_SingleShotMode;

//*****************************************************************************
//
//! The following are defines for the identifier parameter of the
//! DCC_getRevisionNumber() function.
//
//*****************************************************************************
typedef enum
{
    DCC_REVISION_MINOR       = 0x0U,  //!< The module minor revision number
    DCC_REVISION_CUSTOM      = 0x1U,  //!< The custom module revision number
    DCC_REVISION_MAJOR       = 0x2U,  //!< The module major revision number
    DCC_REVISION_DESIGN      = 0x3U,  //!< The module design release number
    DCC_REVISION_FUNCTIONAL  = 0x4U,  //!< The module functional release number
    DCC_REVISION_SCHEME      = 0x5U   //!< The scheme of the module
} DCC_RevisionNumber;

//*****************************************************************************
//
//! The following are defines for the source parameter of the
//! DCC_setCounter1ClkSource() function.
//
//*****************************************************************************
typedef enum
{
    DCC_COUNT1SRC_PLL       = 0x0U,    //!< PLL021SSP Clock Out Source
    DCC_COUNT1SRC_INTOSC1   = 0x2U,    //!< Internal Oscillator 1 Clock Source
    DCC_COUNT1SRC_INTOSC2   = 0x3U,    //!< Internal Oscillator 2 Clock Source
    DCC_COUNT1SRC_PUMOSC    = 0x4U,    //!< PUMOSC Clock Source
    DCC_COUNT1SRC_DCDC      = 0x5U,    //!< DCDC Clock Source
    DCC_COUNT1SRC_SYSCLK    = 0x6U,    //!< System Clock Source
    DCC_COUNT1SRC_FOSCLK    = 0x7U,    //!< FOS Clock Source
    DCC_COUNT1SRC_ODPOSC    = 0x8U,    //!< ODP Oscillator Clock Source
    DCC_COUNT1SRC_CROSSBAR  = 0x9U,    //!< Input Crossbar Clock Source
    DCC_COUNT1SRC_AUXCLK    = 0xAU,    //!< AUX Clock Source
    DCC_COUNT1SRC_ETPWM     = 0xBU,    //!< ETPWM Clock Source
    DCC_COUNT1SRC_LSPCLK    = 0xCU,    //!< LSP Clock Source
    DCC_COUNT1SRC_ADCCLK    = 0xDU,    //!< ADC Clock Source
    DCC_COUNT1SRC_WDCLK     = 0xEU,    //!< Watch Dog Clock Source
    DCC_COUNT1SRC_CANX      = 0xFU     //!< CANxBIT Clock Source
} DCC_Count1ClockSource;

//*****************************************************************************
//
//! The following are defines for the source parameter of the
//! DCC_setCounter0ClkSource() function.
//
//*****************************************************************************
typedef enum
{
    DCC_COUNT0SRC_XTAL     = 0x0U,    //!< Accurate Clock Source
    DCC_COUNT0SRC_INTOSC1  = 0x1U,    //!< Internal Oscillator 1 Clock Source
    DCC_COUNT0SRC_INTOSC2  = 0x2U,    //!< Internal Oscillator 2 Clock Source
    DCC_COUNT0SRC_TCK      = 0x4U,    //!< Preliminary Clock Source
    DCC_COUNT0SRC_AUXCLK   = 0x8U,    //!< AUX Clock Source
    DCC_COUNT0SRC_XBAR     = 0xDU     //!< Input XBAR Clock Source
} DCC_Count0ClockSource;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks DCC base address.
//!
//! \param base specifies the DCC module base address.
//!
//! This function determines if an DCC module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static bool
DCC_isBaseValid(uint32_t base)
{
    return(base == DCC0_BASE);
}
#endif

//*****************************************************************************
//
//! Enables the DCC module.
//!
//! \param base is the DCC module base address
//!
//! This function starts the DCC counter operation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Set DCC enable bit field.
    //
    EALLOW;

    HWREGH(base + DCC_O_GCTRL) = (HWREGH(base + DCC_O_GCTRL) &
                                  ~(DCC_GCTRL_DCCENA_M)) | DCC_ENABLE_VALUE;

    EDIS;
}

//*****************************************************************************
//
//! Disable the DCC module.
//!
//! \param base is the DCC module base address
//!
//! This function stops the DCC counter operation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Reset DCC enable bit field.
    //
    EALLOW;

    HWREGH(base + DCC_O_GCTRL) = (HWREGH(base + DCC_O_GCTRL) &
                                  ~(DCC_GCTRL_DCCENA_M)) | DCC_DISABLE_VALUE;

    EDIS;
}

//*****************************************************************************
//
//! Enable DCC Error Signal
//!
//! \param base is the DCC module base address
//!
//! This function enables the error signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_enableErrorSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Enable the error signal
    //
    EALLOW;

    HWREGH(base + DCC_O_GCTRL) = (HWREGH(base + DCC_O_GCTRL) &
                                  ~(DCC_GCTRL_ERRENA_M)) |
                                  (DCC_ENABLE_VALUE << 4U);

    EDIS;
}

//*****************************************************************************
//
//! Enable DCC Done Signal
//!
//! \param base is the DCC module base address
//!
//! This function enables the done signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_enableDoneSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Enable the done interrupt signal
    //
    EALLOW;

    HWREGH(base + DCC_O_GCTRL) = (HWREGH(base + DCC_O_GCTRL) &
                                  ~(DCC_GCTRL_DONEENA_M)) |
                                  (DCC_ENABLE_VALUE << 12U);

    EDIS;
}

//*****************************************************************************
//
//! Disable DCC Error Signal
//!
//! \param base is the DCC module base address
//!
//! This function disables the error signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_disableErrorSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Disable the error signal
    //
    EALLOW;

    HWREGH(base + DCC_O_GCTRL) = (HWREGH(base + DCC_O_GCTRL) &
                                  ~(DCC_GCTRL_ERRENA_M)) |
                                 (DCC_DISABLE_VALUE << 4U);

    EDIS;
}

//*****************************************************************************
//
//! Disable DCC Done Signal
//!
//! \param base is the DCC module base address
//!
//! This function disables the done signal interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_disableDoneSignal(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Disable the done interrupt signal
    //
    EALLOW;

    HWREGH(base + DCC_O_GCTRL) = (HWREGH(base + DCC_O_GCTRL) &
                                  ~(DCC_GCTRL_DONEENA_M)) |
                                 (DCC_DISABLE_VALUE << 12U);

    EDIS;
}

//*****************************************************************************
//
//! Enable DCC Single-Shot Mode
//!
//! \param base is the DCC module base address
//! \param mode is the selected Single-Shot operation mode
//!
//! This function enables the single-shot mode and sets the operation mode.
//!
//! The \e mode parameter can have one of two values:
//! - \b DCC_MODE_COUNTER_ZERO - Stops counting when counter0 and valid0 both
//!   reach zero
//! - \b DCC_MODE_COUNTER_ONE  - Stops counting when counter1 reaches zero
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_enableSingleShotMode(uint32_t base, DCC_SingleShotMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Set Single-Shot mode value to the appropriate register
    //
    if (mode == DCC_MODE_COUNTER_ZERO)
    {
        EALLOW;

        HWREGH(base + DCC_O_GCTRL) = (HWREGH(base + DCC_O_GCTRL) &
                                      ~(DCC_GCTRL_SINGLESHOT_M)) |
                                     (uint16_t)DCC_MODE_COUNTER_ZERO;

        EDIS;
    }
    else
    {
        EALLOW;

        HWREGH(base + DCC_O_GCTRL) = (HWREGH(base + DCC_O_GCTRL) &
                                      ~(DCC_GCTRL_SINGLESHOT_M)) |
                                     (uint16_t)DCC_MODE_COUNTER_ONE;

        EDIS;
    }
}

//*****************************************************************************
//
//! Disable DCC Single-Shot Mode
//!
//! \param base is the DCC module base address
//!
//! This function disables the DCC Single-Shot operation mode
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_disableSingleShotMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Reset Single-Shot enable bit field.
    //
    EALLOW;

    HWREGH(base + DCC_O_GCTRL) = (HWREGH(base + DCC_O_GCTRL) &
                                  ~(DCC_GCTRL_SINGLESHOT_M)) |
                                 (DCC_DISABLE_VALUE << 8U);

    EDIS;
}

//*****************************************************************************
//
//! Get Error Flag Status
//!
//! \param base is the DCC module base address
//!
//! This function gets the error flag status.
//!
//! \return Returns \b true if an error has occurred, \b false if no errors
//! have occurred.
//
//*****************************************************************************
static inline bool
DCC_getErrorStatus(uint32_t base)
{
    bool status = false;

    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Get the error flag
    //
    if ((HWREGH(base + DCC_O_STATUS) & DCC_STATUS_ERR) == DCC_STATUS_ERR)
    {
        status = true;
    }

    return status;
}

//*****************************************************************************
//
//! Get Single-Shot Done Flag Status
//!
//! \param base is the DCC module base address
//!
//! This function gets the single-shot done flag status.
//!
//! \return Returns \b true if single-shot mode has completed, \b false if
//! single-shot mode has not completed.
//
//*****************************************************************************
static inline bool
DCC_getSingleShotStatus(uint32_t base)
{
    bool status = false;

    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Get the done flag
    //
    if ((HWREGH(base + DCC_O_STATUS) & DCC_STATUS_DONE) == DCC_STATUS_DONE)
    {
        status = true;
    }

    return status;
}

//*****************************************************************************
//
//! Clear Error Status Flag
//!
//! \param base is the DCC module base address
//!
//! This function clears the DCC error status flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_clearErrorFlag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Clear error status flag
    //
    EALLOW;

    HWREGH(base + DCC_O_STATUS) |= DCC_STATUS_ERR;

    EDIS;
}

//*****************************************************************************
//
//! Clear Single-Shot Done Status Flag
//!
//! \param base is the DCC module base address
//!
//! This function clears the DCC single-shot done status flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_clearDoneFlag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Clear done status flag
    //
    EALLOW;

    HWREGH(base + DCC_O_STATUS) |= DCC_STATUS_DONE;

    EDIS;
}

//*****************************************************************************
//
//! Get Current Value of Counter 0
//!
//! \param base is the DCC module base address
//!
//! This function gets current value of counter 0.
//!
//! \note Reads of the counter value may not be exact since the read operation
//! is synchronized to the vbus clock.
//!
//! \return Returns the current value of counter 0.
//
//*****************************************************************************
static inline uint32_t
DCC_getCounter0Value(uint32_t base)
{
    uint32_t value;

    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Get the current counter 0 value
    //
    value = HWREGH(base + DCC_O_CNT0) & DCC_REG_WORD_MASK;
    value |= ((uint32_t)(HWREGH(base + DCC_O_CNT0 + 2U) &
              (DCC_CNT0_COUNT0_M >> 16U)) << 16U);

    return value;
}

//*****************************************************************************
//
//! Get Current Value of the Valid Duration Counter for Counter 0
//!
//! \param base is the DCC module base address
//!
//! This function gets current value of the valid duration counter for
//! counter 0.
//!
//! \note Reads of the counter value may not be exact since the read operation
//! is synchronized to the vbus clock.
//!
//! \return Returns the current value of the valid duration counter.
//
//*****************************************************************************
static inline uint16_t
DCC_getValidCounter0Value(uint32_t base)
{
    uint16_t value;

    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Get the current valid duration counter value
    //
    value = HWREGH(base + DCC_O_VALID0);

    return value;
}

//*****************************************************************************
//
//! Get Current Value of Counter 1
//!
//! \param base is the DCC module base address
//!
//! This function gets current value of counter 1.
//!
//! \note Reads of the counter value may not be exact since the read operation
//! is synchronized to the vbus clock.
//!
//! \return Returns the current value of counter 1.
//
//*****************************************************************************
static inline uint32_t
DCC_getCounter1Value(uint32_t base)
{
    uint32_t value;

    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    // Get the current counter 1 value
    //
    value = HWREGH(base + DCC_O_CNT1) & DCC_REG_WORD_MASK;
    value = HWREGH(base + DCC_O_CNT1) & DCC_REG_WORD_MASK;
    value |= ((uint32_t)(HWREGH(base + DCC_O_CNT1 + 2U) &
              (DCC_CNT1_COUNT1_M >> 16U)) << 16U);

    return value;
}

//*****************************************************************************
//
//! Set Counter 1 Clock Source
//!
//! \param base is the DCC module base address
//! \param source is the selected clock source for counter 1
//!
//! This function sets the counter 1 clock source.
//!
//! The \e source parameter can have one of fifteen values:
//! - \b DCC_COUNT1SRC_PLL       -  PLL021SSP Clock Out Source
//! - \b DCC_COUNT1SRC_INTOSC1   -  Internal Oscillator 1 Clock Source
//! - \b DCC_COUNT1SRC_INTOSC2   -  Internal Oscillator 2 Clock Source
//! - \b DCC_COUNT1SRC_PUMOSC    -  PUMOSC Clock Source
//! - \b DCC_COUNT1SRC_DCDC      -  DCDC Clock Source
//! - \b DCC_COUNT1SRC_SYSCLK    -  System Clock Source
//! - \b DCC_COUNT1SRC_FOSCLK    -  FOS Clock Source
//! - \b DCC_COUNT1SRC_ODPOSC    -  ODP Oscillator Clock Source
//! - \b DCC_COUNT1SRC_CROSSBAR  -  Input Crossbar Clock Source
//! - \b DCC_COUNT1SRC_AUXCLK    -  AUX Clock Source
//! - \b DCC_COUNT1SRC_ETPWM     -  ETPWM Clock Source
//! - \b DCC_COUNT1SRC_LSPCLK    -  LSP Clock Source
//! - \b DCC_COUNT1SRC_ADCCLK    -  ADC Clock Source
//! - \b DCC_COUNT1SRC_WDCLK     -  Watch Dog Clock Source
//! - \b DCC_COUNT1SRC_CANX      -  CANxBIT Clock Source
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_setCounter1ClkSource(uint32_t base, DCC_Count1ClockSource source)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    //  Set the specified clock source
    //
    EALLOW;

    HWREGH(base + DCC_O_CLKSRC1) = (HWREGH(base + DCC_O_CLKSRC1) &
                                    (DCC_REG_BYTE_MASK << 4U)) |
                                   ((DCC_ENABLE_VALUE << 12U) |
                                    (uint16_t)source);

    EDIS;
}

//*****************************************************************************
//
//! Set Counter 0 Clock Source
//!
//! \param base is the DCC module base address
//! \param source is the selected clock source for counter 0
//!
//! This function sets the counter 0 clock source.
//!
//! The \e source parameter can have one of six values:
//! - \b DCC_COUNT0SRC_XTAL      -  Accurate Clock Source
//! - \b DCC_COUNT0SRC_INTOSC1   -  Internal Oscillator 1 Clock Source
//! - \b DCC_COUNT0SRC_INTOSC2   -  Internal Oscillator 2 Clock Source
//! - \b DCC_COUNT0SRC_TCK       -  Preliminary Clock Source
//! - \b DCC_COUNT0SRC_AUXCLK    -  AUX Clock Source
//! - \b DCC_COUNT0SRC_XBAR      -  Input XBAR Clock Source
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCC_setCounter0ClkSource(uint32_t base, DCC_Count0ClockSource source)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    //  Set the specified clock source
    //
    EALLOW;

    HWREGH(base + DCC_O_CLKSRC0) = (HWREGH(base + DCC_O_CLKSRC0) &
                                    ~(DCC_CLKSRC0_CLKSRC0_M)) |
                                    (uint16_t)source;

    EDIS;
}

//*****************************************************************************
//
//! Get Counter 1 Clock Source
//!
//! \param base is the DCC module base address
//!
//! This function gets the counter 1 clock source.
//!
//! \return Returns one of the following enumerated source values:
//! - \b DCC_COUNT1SRC_PLL       -  PLL021SSP Clock Out Source
//! - \b DCC_COUNT1SRC_INTOSC1   -  Internal Oscillator 1 Clock Source
//! - \b DCC_COUNT1SRC_INTOSC2   -  Internal Oscillator 2 Clock Source
//! - \b DCC_COUNT1SRC_PUMOSC    -  PUMOSC Clock Source
//! - \b DCC_COUNT1SRC_DCDC      -  DCDC Clock Source
//! - \b DCC_COUNT1SRC_SYSCLK    -  System Clock Source
//! - \b DCC_COUNT1SRC_FOSCLK    -  FOS Clock Source
//! - \b DCC_COUNT1SRC_ODPOSC    -  ODP Oscillator Clock Source
//! - \b DCC_COUNT1SRC_CROSSBAR  -  Input Crossbar Clock Source
//! - \b DCC_COUNT1SRC_AUXCLK    -  AUX Clock Source
//! - \b DCC_COUNT1SRC_ETPWM     -  ETPWM Clock Source
//! - \b DCC_COUNT1SRC_LSPCLK    -  LSP Clock Source
//! - \b DCC_COUNT1SRC_ADCCLK    -  ADC Clock Source
//! - \b DCC_COUNT1SRC_WDCLK     -  Watch Dog Clock Source
//! - \b DCC_COUNT1SRC_CANX      -  CANxBIT Clock Source
//
//*****************************************************************************
static inline uint16_t
DCC_getCounter1ClkSource(uint32_t base)
{
    uint16_t source;
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    //  Get the specified clock source
    //
    source = HWREGH(base + DCC_O_CLKSRC1) & DCC_CLKSRC1_CLKSRC1_M;

    return source;
}

//*****************************************************************************
//
//! Get Counter 0 Clock Source
//!
//! \param base is the DCC module base address
//!
//! This function gets the counter 0 clock source.
//!
//! \return Returns one of the following enumerated source values:
//! - \b DCC_COUNT0SRC_XTAL      -  Accurate Clock Source
//! - \b DCC_COUNT0SRC_INTOSC1   -  Internal Oscillator 1 Clock Source
//! - \b DCC_COUNT0SRC_INTOSC2   -  Internal Oscillator 2 Clock Source
//! - \b DCC_COUNT0SRC_TCK       -  Preliminary Clock Source
//! - \b DCC_COUNT0SRC_AUXCLK    -  AUX Clock Source
//! - \b DCC_COUNT0SRC_XBAR      -  Input XBAR Clock Source
//
//*****************************************************************************
static inline uint16_t
DCC_getCounter0ClkSource(uint32_t base)
{
    uint16_t source;
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    //  Get the specified clock source
    //
    source = HWREGH(base + DCC_O_CLKSRC0) & DCC_CLKSRC0_CLKSRC0_M;

    return source;
}

//*****************************************************************************
//
//! Get DCC Version Number
//!
//! \param base is the DCC module base address
//! \param identifier is the selected revision number identifier
//!
//! This function gets the specific version number
//!
//! The \e identifier parameter can have one of six values:
//! - \b DCC_REVISION_MINOR      - The minor revision number
//! - \b DCC_REVISION_CUSTOM     - The custom module number
//! - \b DCC_REVISION_MAJOR      - The major revision number
//! - \b DCC_REVISION_DESIGN     - The design release number
//! - \b DCC_REVISION_FUNCTIONAL - The functional release number
//! - \b DCC_REVISION_SCHEME     - The scheme of the module
//!
//! \return Specified revision number
//
//*****************************************************************************
extern uint16_t
DCC_getRevisionNumber(uint32_t base, DCC_RevisionNumber identifier);

//*****************************************************************************
//
//! Set the seed values
//!
//! \param base is the DCC module base address
//! \param counter0 sets the seed value that gets loaded into Counter 0
//! \param validcounter0 sets the seed value that gets loaded into the valid
//!  duration counter for Counter 0
//! \param counter1 sets the seed value that gets loaded into Counter 1
//!
//! This function sets the seed values for Counter 0, Valid Duration Counter 0,
//! and Counter 1.
//!
//! \note Operating DCC with '0' set as the seed value for Counter 0, Valid
//! Duration Counter 0, and/or Counter 1 will result in undefined operation.
//!
//! \note The Valid Duration Counter 0 is designed to be at least four cycles
//! wide and shouldn't be programmed with a value less than '4'.
//!
//! \return None.
//
//*****************************************************************************
extern void
DCC_setCounterSeeds(uint32_t base, uint32_t counter0, uint32_t validcounter0,
                    uint32_t counter1);

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

#endif // __DCC_H__
