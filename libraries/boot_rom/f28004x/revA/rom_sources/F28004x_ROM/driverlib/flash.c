//###########################################################################
//
// FILE:   flash.c
//
// TITLE:  C28x Flash driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "flash.h"

//*****************************************************************************
//
// Flash_initModule
//
//*****************************************************************************
void Flash_initModule(uint16_t waitstates)
{
    ASSERT(waitstates <= 0xFU);

    // Power up flash bank and pump and this also sets the fall back mode of
    // flash and pump as active.
    Flash_setPumpPowerMode(FLASH_PUMP_PWR_ACTIVE);
    Flash_setBankPowerMode(FLASH_BANK0, FLASH_BANK_PWR_ACTIVE);
    Flash_setBankPowerMode(FLASH_BANK1, FLASH_BANK_PWR_ACTIVE);

    // Disable cache and prefetch mechanism before changing wait states
    Flash_disableCache();
    Flash_disablePrefetch();

    // Set waitstates according to frequency
    Flash_setReadWaitstates(waitstates);

    // Enable cache and prefetch mechanism to improve performance of code
    // executed from flash.
    Flash_enableCache();
    Flash_enablePrefetch();

    // At reset, ECC is enabled.  If it is disabled by application software and
    // if application again wants to enable ECC.
    Flash_enableECC();

    // Force a pipeline flush to ensure that the write to the last register
    // configured occurs before returning.
    __asm(" RPT #7 || NOP");
}


