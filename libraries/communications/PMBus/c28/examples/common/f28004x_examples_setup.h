#ifndef _F28004X_EXAMPLES_SETUP_H_
#define _F28004X_EXAMPLES_SETUP_H_
//#############################################################################
//
//! \file   f28004x_examples_setup.h
//!
//! \brief  f28004x Examples Common Code
//! \author Vishal Coelho
//! \date    Apr 1, 2015
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
#include <stdint.h>
#include "sysctl.h"
#include "interrupt.h"
#include "pmbus.h"
#include "gpio.h"
#include "pin_map.h"

#if defined(_FLASH)
#include "flash.h"
#endif //defined(_FLASH)

//!
//! \defgroup PMBUS_EXAMPLES_SETUP PMBus Examples Setup Code

//!
//! \ingroup PMBUS_EXAMPLES_SETUP
//@{

#ifdef __cplusplus

extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
#define NTESTS              21U
#define NENABLEDTESTS		20U

#define SLAVE_ADDRESS            0x6AU
#define SLAVE_ADDRESSMASK        0x7FU
#define ALERT_RESPONSE_ADDRESS	 0x0CU
//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
//globals
//*****************************************************************************
#if defined(_FLASH)
extern uint32_t RamfuncsRunStart, RamfuncsLoadStart, RamfuncsLoadSize;
#endif //defined(_FLASH)

//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Setup GPIO pins for PMBUS mode of operation
//! 
extern void PMBUS_Example_setupGPIO( void );

//! \brief Setup system controls
//! 
extern void PMBUS_Example_setupSysCtrl( void );

//! \brief Setup system interrupts
//! \param[in] pmbusISR pointer to the ISR that handles PMBUS interrupts
//!
extern void PMBUS_Example_setupInterrupts( void (*pmbusISR)(void));

//! \brief Setup flash
//! 
extern void PMBUS_Example_setupFlash( void );

//! \brief Function indicating end of test (Autobot regression)
//! 
extern void done( void );

#ifdef __cplusplus
{
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _F28004X_EXAMPLES_SETUP_H_ definition

// End of File
