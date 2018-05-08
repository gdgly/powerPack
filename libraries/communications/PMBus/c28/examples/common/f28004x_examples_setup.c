//#############################################################################
//
//! \file   f28004x_examples_setup.c
//!
//! \brief  f28004x Examples Common Code
//! \author Vishal Coelho
//! \date   Apr 1, 2015
//
//  Group:          C2000
//  Target Device:  TMS320F28004x
//
// Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED
//#############################################################################
// $TI Release: C28x PMBus Communications Stack Library v1.00.00.00 $
// $Release Date: May 22, 2017 $
//#############################################################################

//*****************************************************************************
// the includes
//*****************************************************************************
#include "f28004x_examples_setup.h"

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// PMBUS_Example_setupGPIO()
//=============================================================================
void PMBUS_Example_setupGPIO( void )
{
    // PMBus module is accessible over other GPIO pin mux configurations 
    // as well. Refer to the device TRM for the different pin configurations
    GPIO_setPinConfig(GPIO_12_PMBACTL);
    GPIO_setPinConfig(GPIO_13_PMBAALRT);
    GPIO_setPinConfig(GPIO_2_PMBASDA);
    GPIO_setPinConfig(GPIO_3_PMBASCL);
}

//=============================================================================
// PMBUS_Example_setupSysCtrl()
//=============================================================================
void PMBUS_Example_setupSysCtrl( void )
{

    // 1. Set the primary oscillator as the system clock source
    // 2. Enable the PLL
    // 3. Set the Integer multiplier to 20, fractional to 0- a 10x increase
    // 4. Divide the final sysclk by 2 to get 100MHz
    // 5. Disable watchdog
    SysCtl_setClock(SYSCTL_PLL_ENABLE | SYSCTL_OSCSRC_OSC1 |
                    SYSCTL_IMULT(20)  | SYSCTL_FMULT_0     |
                    SYSCTL_SYSDIV(2));

    // Enable the PMBUS-A peripheral at the system level
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PMBUSA);
    // Disable the watchdog
    SysCtl_disableWatchdog();
}

//=============================================================================
// PMBUS_Example_setupInterrupts()
//=============================================================================
void PMBUS_Example_setupInterrupts( void (*pmbusISR)(void))
{
	// Initialize PIE and clear PIE registers. Disables CPU interrupts
	Interrupt_initModule();
    // Initialize the interrupt vector table
    Interrupt_initVectorTable();
    // Register user defined PMBUS ISR
    Interrupt_register(INT_PMBUSA, pmbusISR);
    // Enable the PMBUS interrupt
    Interrupt_enable(INT_PMBUSA);
    // ACK any pending group 8 interrupts (if any got set)
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
    // Globally enable all interrupts
    Interrupt_enableMaster();
}

//=============================================================================
// PMBUS_Example_setupFlash()
//=============================================================================
void PMBUS_Example_setupFlash( void )
{
#if defined(_FLASH)
    //
    // Copy time critical code and flash setup code to RAM. This includes the
    // following functions: InitFlash();
    //
    // The RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart symbols
    // are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (uint32_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
#endif //defined(_FLASH)
}

//=============================================================================
// done()
//=============================================================================
void done( void )
{
    for(;;);
}

//=============================================================================
// __error__()
//=============================================================================
void __error__(char *filename, uint32_t line)
{
	__asm(" ESTOP0");
}

// End of File
