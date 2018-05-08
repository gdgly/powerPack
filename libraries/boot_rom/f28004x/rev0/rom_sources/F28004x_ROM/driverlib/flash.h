//###########################################################################
//
// FILE:   flash.h
//
// TITLE:  C28x Flash driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __FLASH_H__
#define __FLASH_H__

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
//! \addtogroup flash_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_flash.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
//! Values that can be passed to Flash_setBankPowerMode as the bank parameter.
//
//*****************************************************************************
typedef enum
{
    FLASH_BANK0 = 0x0,
    FLASH_BANK1 = 0x1
} Flash_BankNumber;

//*****************************************************************************
//
//! Values that can be passed to Flash_setBankPowerMode as the powerMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    FLASH_BANK_PWR_SLEEP    = 0x0,
    FLASH_BANK_PWR_STANDBY  = 0x1,
    FLASH_BANK_PWR_ACTIVE   = 0x3
} Flash_BankPowerMode;

//*****************************************************************************
//
//! Values that can be passed to Flash_setPumpPowerMode as the powerMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    FLASH_PUMP_PWR_SLEEP    = 0x0,
    FLASH_PUMP_PWR_ACTIVE   = 0x1
} Flash_PumpPowerMode;

//*****************************************************************************
//
//! Type that correspond to values returned from Flash_getLowErrorStatus and
//! Flash_getHighErrorStatus determining the error status code.
//
//*****************************************************************************
typedef enum
{
    FLASH_NO_ERR       = 0x0,
    FLASH_FAIL_0       = 0x1,
    FLASH_FAIL_1       = 0x2,
    FLASH_UNC_ERR      = 0x4
} Flash_ErrorStatus;

//*****************************************************************************
//
//! Values that can be returned from Flash_getLowErrorType and
//! Flash_getHighErrorType determining the error type.
//
//*****************************************************************************
typedef enum
{
    FLASH_DATA_ERR      = 0x0,
    FLASH_ECC_ERR       = 0x1
} Flash_ErrorType;

//*****************************************************************************
//
// Values that can be passed to Flash_clearLowErrorStatus and
// Flash_clearHighErrorStatus.
//
//*****************************************************************************
#define    FLASH_FAIL_0_CLR       0x1 //!< Fail-0 clear
#define    FLASH_FAIL_1_CLR       0x2 //!< Fail-1 clear
#define    FLASH_UNC_ERR_CLR      0x4 //!< Uncorrectable error Clear

//*****************************************************************************
//
// Values that can be returned from Flash_getInterruptFlag and
// Flash_getECCTestStatus.
//
//*****************************************************************************
#define    FLASH_NO_ERROR         0x0 //!< No error
#define    FLASH_SINGLE_ERROR     0x1 //!< Single bit error
#define    FLASH_UNC_ERROR        0x2 //!< Uncorrectable error

//*****************************************************************************
//
//! Values that can be returned from Flash_getECCTestSingleBitErrorType
//
//*****************************************************************************
typedef enum
{
    FLASH_DATA_BITS          = 0x0,
    FLASH_CHECK_BITS         = 0x1
} Flash_SingleBitErrorIndicator;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Sets the random read wait state amount.
//!
//! \param waitstates is the wait-state amount.
//!
//! This function sets the number of wait states for a flash read access.  The
//! \e waitstates parameter is a number between 0 and 15.  It is \b important
//! to look at your device's datasheet for information about what the required
//! minimum flash wait-state is for your selected SYSCLK frequency.
//!
//! By default the wait state amount is configured to the maximum 15.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setReadWaitstates(uint16_t waitstates)
{
    ASSERT(waitstates <= 0xFU);
    EALLOW;
    // Write flash read wait-state amount to appropriate register.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRDCNTL) =
        (HWREG(FLASH0CTRL_BASE + FLASH_O_FRDCNTL) &
         ~(uint32_t)FLASH_FRDCNTL_RWAIT_M) |
         ((uint32_t)waitstates << FLASH_FRDCNTL_RWAIT_S);
    EDIS;
}

//*****************************************************************************
//
//! Sets the power mode of a flash bank.
//!
//! \param bank is the flash bank that is being configured.
//! \param powerMode is the power mode to be entered.
//!
//! This function sets the power mode of the flash bank specified by the
//! \e bank parameter. The power mode is specified by the \e powerMode
//! parameter with one of the following values:
//!
//! - \b FLASH_BANK_PWR_SLEEP - Sense amplifiers and sense reference disabled.
//! - \b FLASH_BANK_PWR_STANDBY - Sense amplifiers disabled but sense reference
//!   enabled.
//! - \b FLASH_BANK_PWR_ACTIVE - Sense amplifiers and sense reference enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setBankPowerMode(Flash_BankNumber bank,
                            Flash_BankPowerMode powerMode)
{
    EALLOW;
    // Write the power mode to the appropriate register.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FBFALLBACK) =
        (HWREG(FLASH0CTRL_BASE + FLASH_O_FBFALLBACK) &
         ~((FLASH_FBFALLBACK_BNKPWR0_M) << ((uint32_t)bank * 2U))) |
        ((uint32_t)powerMode << ((uint32_t)bank * 2U));
    EDIS;
}

//*****************************************************************************
//
//! Sets the fallback power mode of the charge pump.
//!
//! \param powerMode is the power mode to be entered.
//!
//! This function sets the fallback power mode flash charge pump.
//!
//! - \b FLASH_PUMP_PWR_SLEEP - All circuits disabled.
//! - \b FLASH_PUMP_PWR_ACTIVE - All pump circuits active.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setPumpPowerMode(Flash_PumpPowerMode powerMode)
{
    EALLOW;
    // Write the power mode to the appropriate register.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FPAC1) =
        (HWREG(FLASH0CTRL_BASE + FLASH_O_FPAC1) &
        ~(uint32_t)FLASH_FPAC1_PMPPWR) | (uint32_t)powerMode;
    EDIS;
}

//*****************************************************************************
//
//! Enables prefetch mechanism.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_enablePrefetch(void)
{
    EALLOW;
    // Set the prefetch enable bit.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) |=
            FLASH_FRD_INTF_CTRL_PREFETCH_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disables prefetch mechanism.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_disablePrefetch(void)
{
    EALLOW;
    // Clear the prefetch enable bit.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) &=
            ~(uint32_t)FLASH_FRD_INTF_CTRL_PREFETCH_EN;
    EDIS;
}

//*****************************************************************************
//
//! Enables data cache.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_enableCache(void)
{
    EALLOW;
    // Set the data cache enable bit.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) |=
            FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disables data cache.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_disableCache(void)
{
    EALLOW;
    // Clear the data cache enable bit.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) &=
            ~(uint32_t)FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;
    EDIS;
}

//*****************************************************************************
//
//! Enables flash error correction code (ECC) protection.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_enableECC(void)
{
    EALLOW;
    // Write the key value 0xA to ECC_ENABLE register.
    HWREG(FLASH0ECC_BASE + FLASH_O_ECC_ENABLE) =
        (HWREG(FLASH0ECC_BASE + FLASH_O_ECC_ENABLE) &
         ~(uint32_t)FLASH_ECC_ENABLE_ENABLE_M) | 0xAU;
    EDIS;
}

//*****************************************************************************
//
//! Disables flash error correction code (ECC) protection.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_disableECC(void)
{
    EALLOW;
    // Clear ECC enable field with the one's complement of the key.
    HWREG(FLASH0ECC_BASE + FLASH_O_ECC_ENABLE) =
        (HWREG(FLASH0ECC_BASE + FLASH_O_ECC_ENABLE) &
         ~(uint32_t)FLASH_ECC_ENABLE_ENABLE_M) | 0x5U;
    EDIS;
}

//*****************************************************************************
//
//! Initializes the flash control registers.
//!
//! \param waitstate is the wait-state amount.
//!
//! This function initializes the flash control registers. At reset bank and
//! pump are in sleep.  A flash access will power up the bank and pump
//! automatically.  After a flash access, bank and pump go to low power mode
//! (configurable in FBFALLBACK/FPAC1 registers) if there is no further access
//! to flash.  This function will power up Flash bank and pump and set the
//! fallback mode of flash and pump as active.
//!
//! This function also sets the number of wait-states for a flash read access
//! (see Flash_setReadWaitstates() for more details), and enables cache, the
//! prefetch mechanism, and ECC.
//!
//! \return None.
//
//*****************************************************************************
extern void Flash_initModule(uint16_t waitstates);

//*****************************************************************************
//
//! Enables read margin 0.
//!
//! \param bank is the flash bank that is being used.
//!
//! This function disables read margin 1 and enables read margin 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_enableReadMargin0(Flash_BankNumber bank)
{
    uint32_t cacheEnable;
    EALLOW;

    // Save the state of the cache enable bit
    cacheEnable = HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) &
                    FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;

    // Clear the data cache enable bit.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) &=
            ~(uint32_t)FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;

    __asm("  NOP");

    // Write code to disable read margin 1.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FSPRD) &= ~(uint32_t)FLASH_FSPRD_RM1;

    // Write code to enable read margin 0.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FSPRD) |= FLASH_FSPRD_RM0;

    // Set the bank select bit for the bank to work on
    if(bank == FLASH_BANK0)
    {
        HWREG(FLASH0CTRL_BASE + FLASH_O_FSPRD) |= FLASH_FSPRD_RMBSEL0;
    }
    else
    {
        HWREG(FLASH0CTRL_BASE + FLASH_O_FSPRD) |= FLASH_FSPRD_RMBSEL1;
    }

    // Restore the state of the cache enable bit
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) |= cacheEnable;

    EDIS;
}

//*****************************************************************************
//
//! Enables read margin 1.
//!
//! \param bank is the flash bank that is being used.
//!
//! This function disables read margin 0 and enables read margin 1.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_enableReadMargin1(Flash_BankNumber bank)
{
    uint32_t cacheEnable;
    EALLOW;

    // Save the state of the cache enable bit
    cacheEnable = HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) &
                    FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;

    // Clear the data cache enable bit.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) &=
            ~(uint32_t)FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;

    __asm("  NOP");

    // Disable read margin 0.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FSPRD) &= ~(uint32_t)FLASH_FSPRD_RM0;

    // Enable read margin 1.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FSPRD) |= FLASH_FSPRD_RM1;

    // Set the bank select bit for the bank to work on
    if(bank == FLASH_BANK0)
    {
        HWREG(FLASH0CTRL_BASE + FLASH_O_FSPRD) |= FLASH_FSPRD_RMBSEL0;
    }
    else
    {
        HWREG(FLASH0CTRL_BASE + FLASH_O_FSPRD) |= FLASH_FSPRD_RMBSEL1;
    }

    // Restore the state of the cache enable bit
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) |= cacheEnable;

    EDIS;
}

//*****************************************************************************
//
//! Disables read margin.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_disableReadMargin(void)
{
    EALLOW;
    // Write code to disable read margin 0 and read margin 1
    // and the RMBSEL0 and RMBSEL1 bits to disable for each bank.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FSPRD) &= ~((uint32_t)FLASH_FSPRD_RM0 |
           (uint32_t)FLASH_FSPRD_RM1 | (uint32_t)FLASH_FSPRD_RMBSEL0 |
           (uint32_t)FLASH_FSPRD_RMBSEL1);
    EDIS;
}

//*****************************************************************************
//
//! Sets the bank active grace period.
//!
//! \param period is the starting count value for the BAGP down counter.
//!
//! This function sets the bank active grace period specified by the
//! \e period parameter. The \e period is a value between 0 and 255.  This
//! value must be greater than 1 when the fallback mode is not Active.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setBankActiveGracePeriod(uint32_t period)
{
    ASSERT( period <= 255U );
    EALLOW;
    // Write period to the BAGP of the FBAC register.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FBAC) =
          (HWREG(FLASH0CTRL_BASE + FLASH_O_FBAC) &
             ~(uint32_t)FLASH_FBAC_BAGP_M) | (period << FLASH_FBAC_BAGP_S);
    EDIS;
}

//*****************************************************************************
//
//! Sets the pump wake up time.
//!
//! \param sysclkCycles is the number of SYSCLK cycles it takes for the pump
//! to wakeup.
//!
//! This function sets the wakeup time with \e sysclkCycles parameter.
//! The \e sysclkCycles is a value between 0 and 4095.  When the charge pump
//! exits sleep power mode, it will take sysclkCycles to wakeup.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setPumpWakeupTime(uint16_t sysclkCycles)
{
    ASSERT( sysclkCycles <= 4095U );
    EALLOW;
    // Write sysclkCycles/2 to PSLEEP of the FPAC1 register.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FPAC1) =
          (HWREG(FLASH0CTRL_BASE + FLASH_O_FPAC1) &
          ~(uint32_t)FLASH_FPAC1_PSLEEP_M) |
          (((uint32_t)sysclkCycles/(uint32_t)2) << 
          (uint32_t)FLASH_FPAC1_PSLEEP_S);
    EDIS;
}

//*****************************************************************************
//
//! Sets the pump active grace period.
//!
//! \param period is the starting count value for the PAGP down counter.
//!
//! This function sets the pump active grace period specified by the
//! \e period parameter. The \e period is a value between 0 and 65535.  The
//! counter is reloaded after any flash access.  After the counter expires, the
//! charge pump falls back to the power mode determined by FPAC1, bit PMPPWR.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setPumpActiveGracePeriod(uint16_t period)
{
    EALLOW;
    // Write period to the PAGP of the FPAC2 register.
    HWREG(FLASH0CTRL_BASE + FLASH_O_FPAC2) =
          (HWREG(FLASH0CTRL_BASE + FLASH_O_FPAC2) &
          ~(uint32_t)FLASH_FPAC2_PAGP_M) |
          ((uint32_t)period << FLASH_FPAC2_PAGP_S);
    EDIS;
}

//*****************************************************************************
//
//! Reads the bank active power state.
//!
//! \return Returns \b true if the Bank is in Active power state and \b false
//! otherwise.
//
//*****************************************************************************
static inline bool Flash_isBankReady(void)
{
    bool ready;

    // returns the BANKRDY bit in FBPRDY.
    if((HWREG(FLASH0CTRL_BASE + FLASH_O_FBPRDY) &
        (uint32_t)FLASH_FBPRDY_BANKRDY) == FLASH_FBPRDY_BANKRDY)
    {
        ready = true;
    }
    else
    {
        ready = false;
    }
    return(ready);
}

//*****************************************************************************
//
//! Reads the pump active power state.
//!
//! \return Returns \b true if the Pump is in Active power state and \b false
//! otherwise.
//
//*****************************************************************************
static inline bool Flash_isPumpReady(void)
{
    bool ready;

    // returns the PUMPRDY bit in FBPRDY.
    if((HWREG(FLASH0CTRL_BASE + FLASH_O_FBPRDY) &
        (uint32_t)FLASH_FBPRDY_PUMPRDY) == FLASH_FBPRDY_PUMPRDY)
    {
        ready = true;
    }
    else
    {
        ready = false;
    }
    return(ready);
}

//*****************************************************************************
//
//! Sets the flash state machine operations to a specific bank.
//!
//! \param bank is the flash bank that is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_selectBank(Flash_BankNumber bank)
{
    EALLOW;
    // Write the Flash_BankNumber bank to the BANK field of FMAC
    HWREG(FLASH0CTRL_BASE + FLASH_O_FMAC) = 
           ((HWREG(FLASH0CTRL_BASE + FLASH_O_FMAC) & ~FLASH_FMAC_BANK)
           | (uint32_t)bank);

    EDIS;
}

//*****************************************************************************
//
//! Gets state machine status codes.
//!
//! \return Returns the state machine status codes from the flash module
//! status register which contains the bits for individual status codes
//! for the flash module.
//
//*****************************************************************************
static inline uint32_t Flash_getStateMachineStatus(void)
{
    // Return the flash module status register contents.
    return(HWREG(FLASH0CTRL_BASE + FLASH_O_FMSTAT));
}

//*****************************************************************************
//
//! Gets the single error address low.
//!
//! This function returns the 32-bit address of the single bit error that
//! occurred in the lower 64-bits of a 128-bit memory-aligned data.  The
//! returned address is to that 64-bit aligned data.
//!
//! \return Returns the 32 bits of a 64-bit aligned address where a single bit
//! error occurred.
//
//*****************************************************************************
static inline uint32_t Flash_getSingleBitErrorAddressLow(void)
{
    return(HWREG(FLASH0ECC_BASE + FLASH_O_SINGLE_ERR_ADDR_LOW));
}

//*****************************************************************************
//
//! Gets the single error address high.
//!
//! This function returns the 32-bit address of the single bit error that
//! occurred in the upper 64-bits of a 128-bit memory-aligned data.  The
//! returned address is to that 64-bit aligned data.
//!
//! \return Returns the 32 bits of a 64-bit aligned address where a single bit
//! error occurred.
//
//*****************************************************************************
static inline uint32_t Flash_getSingleBitErrorAddressHigh(void)
{
    return(HWREG(FLASH0ECC_BASE + FLASH_O_SINGLE_ERR_ADDR_HIGH));
}

//*****************************************************************************
//
//! Gets the uncorrectable error address low.
//!
//! This function returns the 32-bit address of the uncorrectable error that
//! occurred in the lower 64-bits of a 128-bit memory-aligned data.  The
//! returned address is to that 64-bit aligned data.
//!
//! \return Returns the 32 bits of a 64-bit aligned address where an
//! uncorrectable error occurred.
//
//*****************************************************************************
static inline uint32_t Flash_getUncorrectableErrorAddressLow(void)
{
    return(HWREG(FLASH0ECC_BASE + FLASH_O_UNC_ERR_ADDR_LOW));
}

//*****************************************************************************
//
//! Gets the uncorrectable error address high.
//!
//! This function returns the 32-bit address of the uncorrectable error that
//! occurred in the upper 64-bits of a 128-bit memory-aligned data.  The
//! returned address is to that 64-bit aligned data.
//!
//! \return Returns the 32 bits of a 64-bit aligned address where an
//! uncorrectable error occurred.
//
//*****************************************************************************
static inline uint32_t Flash_getUncorrectableErrorAddressHigh(void)
{
    return(HWREG(FLASH0ECC_BASE + FLASH_O_UNC_ERR_ADDR_HIGH));
}

//*****************************************************************************
//
//! Gets the error status of the Lower 64-bits.
//!
//! This function returns the error status of the lower 64-bits of a 128-bit
//! aligned address.
//!
//! \return Returns value of the low error status bits which can be used with
//! Flash_ErrorStatus type.
//
//*****************************************************************************
static inline uint32_t Flash_getLowErrorStatus(void)
{
    // Get the Low Error Status bits
    return((HWREG(FLASH0ECC_BASE + FLASH_O_ERR_STATUS) & (uint32_t)0x7U));
}

//*****************************************************************************
//
//! Gets the error status of the Upper 64-bits.
//!
//! This function returns the error status of the upper 64-bits of a 128-bit
//! aligned address.
//!
//! \return Returns value of the high error status bits which can be used with
//! Flash_ErrorStatus type.
//
//*****************************************************************************
static inline uint32_t Flash_getHighErrorStatus(void)
{
    // Get the Low Error Status bits
    return((HWREG(FLASH0ECC_BASE + FLASH_O_ERR_STATUS) >> 16U) &
                (uint32_t)0x7U);
}

//*****************************************************************************
//
//! Gets the error position of the lower 64-bits for a single bit error.
//!
//! This function returns the error position of the lower 64-bits.  If the
//! error type is FLASH_ECC_ERR, the position ranges from 0-7 else it ranges
//! from 0-63 for FLASH_DATA_ERR.
//!
//! \return Returns the position of the lower error bit.
//
//*****************************************************************************
static inline uint32_t Flash_getLowErrorPosition(void)
{
    return((HWREG(FLASH0ECC_BASE + FLASH_O_ERR_POS) &
            (uint32_t)FLASH_ERR_POS_ERR_POS_L_M) >>
            FLASH_ERR_POS_ERR_POS_L_S);
}

//*****************************************************************************
//
//! Gets the error position of the upper 64-bits for a single bit error.
//!
//! This function returns the error position of the upper 64-bits.  If the
//! error type is FLASH_ECC_ERR, the position ranges from 0-7 else it ranges
//! from 0-63 for FLASH_DATA_ERR.
//!
//! \return Returns the position of the upper error bit.
//
//*****************************************************************************
static inline uint32_t Flash_getHighErrorPosition(void)
{
    return((HWREG(FLASH0ECC_BASE + FLASH_O_ERR_POS) &
            (uint32_t)FLASH_ERR_POS_ERR_POS_H_M) >>
            FLASH_ERR_POS_ERR_POS_H_S);
}

//*****************************************************************************
//
//! Gets the error type of the lower 64-bits.
//!
//! This function returns the error type of the lower 64-bits.  The error type
//! can be FLASH_ECC_ERR or FLASH_DATA_ERR.
//!
//! \return Returns the type of the lower 64-bit error.
//
//*****************************************************************************
static inline Flash_ErrorType Flash_getLowErrorType(void)
{
    // check which error type
    // if bit is 1 then ECC error, else it is a Data error
    return((Flash_ErrorType)((HWREG(FLASH0ECC_BASE + FLASH_O_ERR_POS) &
          (uint32_t)FLASH_ERR_POS_ERR_TYPE_L) >> 8U));
}

//*****************************************************************************
//
//! Gets the error type of the upper 64-bits.
//!
//! This function returns the error type of the upper 64-bits.  The error type
//! can be FLASH_ECC_ERR or FLASH_DATA_ERR.
//!
//! \return Returns the type of the upper 64-bit error.
//
//*****************************************************************************
static inline Flash_ErrorType Flash_getHighErrorType(void)
{
    // check which error type
    // if bit is 1 then ECC error, else it is a Data error
    return((Flash_ErrorType)((HWREG(FLASH0ECC_BASE + FLASH_O_ERR_POS) &
            (uint32_t)FLASH_ERR_POS_ERR_TYPE_H) >> 24U));
}

//*****************************************************************************
//
//! Clears the errors status of the lower 64-bits.
//!
//! \param error is the error status to clear.  error is a uint16_t.  error
//! is a logical OR of the following value:
//!
//! - \b FLASH_FAIL_0_CLR
//! - \b FLASH_FAIL_1_CLR
//! - \b FLASH_UNC_ERR_CLR
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_clearLowErrorStatus(uint16_t error)
{
    ASSERT( error <= 7U );
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_ERR_STATUS_CLR) |= ((uint32_t)error);
    EDIS;
}

//*****************************************************************************
//
//! Clears the errors status of the upper 64-bits.
//!
//! \param error is the error status to clear.  error is a uint16_t.  error
//! is a logical OR of the following value:
//!
//! - \b FLASH_FAIL_0_CLR
//! - \b FLASH_FAIL_1_CLR
//! - \b FLASH_UNC_ERR_CLR
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_clearHighErrorStatus(uint16_t error)
{
    ASSERT( error <= 7U );
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_ERR_STATUS_CLR) |= ((uint32_t)error << 16U);
    EDIS;
}

//*****************************************************************************
//
//! Gets the single bit error count.
//!
//! \return Returns the single bit error count.
//
//*****************************************************************************
static inline uint32_t Flash_getErrorCount(void)
{
    return(HWREG(FLASH0ECC_BASE + FLASH_O_ERR_CNT) &
            (uint32_t)FLASH_ERR_CNT_ERR_CNT_M);
}

//*****************************************************************************
//
//! Sets the single bit error threshold.
//!
//! \param threshold is the single bit error threshold.  Valid ranges are from
//! 0-65535.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setErrorThreshold(uint16_t threshold)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_ERR_THRESHOLD) = ((uint32_t)threshold &
        (uint32_t)FLASH_ERR_THRESHOLD_ERR_THRESHOLD_M);
    EDIS;
}

//*****************************************************************************
//
//! Gets the error interrupt.
//!
//! This function returns the type of error interrupt that occurred.  The
//! values can be used with
//! - \b FLASH_NO_ERROR
//! - \b FLASH_SINGLE_ERROR
//! - \b FLASH_UNC_ERROR
//!
//! \return Returns the interrupt flag.
//
//*****************************************************************************
static inline uint32_t Flash_getInterruptFlag(void)
{
    // Read which type of error occurred.
    return((HWREG(FLASH0ECC_BASE + FLASH_O_ERR_INTFLG) & (uint32_t)0x3U));
}

//*****************************************************************************
//
//! Clears the single error interrupt flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_clearSingleErrorInterruptFlag(void)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_ERR_INTCLR) |=
        FLASH_ERR_INTCLR_SINGLE_ERR_INTCLR;
    EDIS;
}

//*****************************************************************************
//
//! Clears the uncorrectable error interrupt flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_clearUncorrectableInterruptFlag(void)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_ERR_INTCLR) |=
        FLASH_ERR_INTCLR_UNC_ERR_INTCLR;
    EDIS;
}

//*****************************************************************************
//
//! Sets the Data Low Test register for ECC testing.
//!
//! \param data is a 32-bit value that is the low double word of selected
//! 64-bit data
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setDataLowECCTest(uint32_t data)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_FDATAL_TEST) = data;
    EDIS;
}

//*****************************************************************************
//
//! Sets the Data High Test register for ECC testing.
//!
//! \param data is a 32-bit value that is the high double word of selected
//! 64-bit data
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setDataHighECCTest(uint32_t data)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_FDATAH_TEST) = data;
    EDIS;
}

//*****************************************************************************
//
//! Sets the test address register for ECC testing.
//!
//! \param address is a 32-bit value containing an address.  Bits 21-3 will be
//! used as the flash word (128-bit) address.
//!
//! This function left shifts the address 1 bit to convert it to a byte address.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setECCTestAddress(uint32_t address)
{
    // Left shift the address 1 bit to make it byte-addressable
    address = address << 1;

    EALLOW;
    // Write bits 21-3 to the register.
    HWREG(FLASH0ECC_BASE + FLASH_O_FADDR_TEST) = address;
    EDIS;
}

//*****************************************************************************
//
//! Sets the ECC test bits for ECC testing.
//!
//! \param ecc is a 32-bit value.  The least significant 8 bits are used as
//! the ECC Control Bits in the ECC Test.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setECCTestECCBits(uint16_t ecc)
{
    ASSERT( ecc <= 255U );
    EALLOW;
    // Write the 8 ECC Control Bits.
    HWREG(FLASH0ECC_BASE + FLASH_O_FECC_TEST) =
        ((uint32_t)ecc & (uint32_t)FLASH_FECC_TEST_ECC_M);
    EDIS;
}

//*****************************************************************************
//
//! Enables ECC Test mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_enableECCTestMode(void)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_FECC_CTRL) |= FLASH_FECC_CTRL_ECC_TEST_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disables ECC Test mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_disableECCTestMode(void)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_FECC_CTRL) &=
        ~(uint32_t)FLASH_FECC_CTRL_ECC_TEST_EN;
    EDIS;
}

//*****************************************************************************
//
//! Selects the ECC block on bits [63:0] of bank data.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_selectLowECCBlock(void)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_FECC_CTRL) &=
        ~(uint32_t)FLASH_FECC_CTRL_ECC_SELECT;
    EDIS;
}

//*****************************************************************************
//
//! Selects the ECC block on bits [127:64] of bank data.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_selectHighECCBlock(void)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_FECC_CTRL) |= FLASH_FECC_CTRL_ECC_SELECT;
    EDIS;
}

//*****************************************************************************
//
//! Do ECC calculation.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_doECCCalculation(void)
{
    EALLOW;
    HWREG(FLASH0ECC_BASE + FLASH_O_FECC_CTRL) |= FLASH_FECC_CTRL_DO_ECC_CALC;
    EDIS;
}

//*****************************************************************************
//
//! Gets the ECC Test data out high 63:32 bits.
//!
//! \return Returns the ECC TEst data out High.
//
//*****************************************************************************
static inline uint32_t Flash_getTestDataOutHigh(void)
{
    return(HWREG(FLASH0ECC_BASE + FLASH_O_FOUTH_TEST));
}

//*****************************************************************************
//
//! Gets the ECC Test data out low 31:0 bits.
//!
//! \return Returns the ECC Test data out Low.
//
//*****************************************************************************
static inline uint32_t Flash_getTestDataOutLow(void)
{
    return(HWREG(FLASH0ECC_BASE + FLASH_O_FOUTL_TEST));
}

//*****************************************************************************
//
//! Gets the ECC Test status.
//!
//! This function returns the ECC test status.  The values can be used with
//! - \b FLASH_NO_ERROR
//! - \b FLASH_SINGLE_ERROR
//! - \b FLASH_UNC_ERROR
//!
//! \return Returns the ECC test status.
//
//*****************************************************************************
static inline uint32_t Flash_getECCTestStatus(void)
{
    // Read which type of error occurred.
    return((HWREG(FLASH0ECC_BASE + FLASH_O_FECC_STATUS) &
                   (uint32_t)0x3U));
}

//*****************************************************************************
//
//! Gets the ECC Test single bit error position.
//!
//! \return Returns the ECC Test single bit error position.  If the error type
//! is check bits than the position can range from 0 to 7.  If the error type
//! is data bits than the position can range from 0 to 63.
//
//*****************************************************************************
static inline uint32_t Flash_getECCTestErrorPosition(void)
{
    // Read the position bits and shift it to the right.
    return((HWREG(FLASH0ECC_BASE + FLASH_O_FECC_STATUS) &
        (uint32_t)FLASH_FECC_STATUS_DATA_ERR_POS_M) >>
        FLASH_FECC_STATUS_DATA_ERR_POS_S);
}

//*****************************************************************************
//
//! Gets the single bit error type.
//!
//! \return Returns the single bit error type as a
//!  Flash_SingleBitErrorIndicator. FLASH_DATA_BITS and FLASH_CHECK_BITS
//! indicate where the single bit error occurred.
//
//*****************************************************************************
static inline Flash_SingleBitErrorIndicator
Flash_getECCTestSingleBitErrorType(void)
{
    // Read the ERR_TYPE bit to see where the single bit error was.
    return((Flash_SingleBitErrorIndicator)
                ((HWREG(FLASH0ECC_BASE + FLASH_O_FECC_STATUS) &
                (uint32_t)FLASH_FECC_STATUS_ERR_TYPE) >> 8U));
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

#endif // __FLASH_H__
