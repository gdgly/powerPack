//#############################################################################
//
//! \file   f28004x_test_quick_command.c
//!
//! \brief  Quick Command
//! \author Vishal Coelho
//! \date   Apr 6, 2015
//
//  Group:          C2000
//  Target Device:  TMS320F28xxxx
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
#include "f28004x_pmbus_master_test.h"

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// PMBUS_TEST_initQuickCommand()
//=============================================================================
void PMBUS_TEST_initQuickCommand(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT

    // Enable the test
#if ENABLE_TEST_10 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_10 == 1
}

//=============================================================================
// PMBUS_TEST_runQuickCommand()
//=============================================================================
void PMBUS_TEST_runQuickCommand(PMBUS_TEST_Handle hnd)
{
    // Locals

    // Increment fail, a DATA_REQUEST should set it back to 0
    hnd->fail++;

    // Do a Quick command
    // Config the master enable Write (by omitting the read
    // option from the configWord, you enable write), 0 byte
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, 0U, 0U);

    // Wait for the EOM, and slave to ack the address before
    // reading data -- done in the ISR
    while(endOfMessage == false)
    {
        if(masterDataRequested == true)
        {
            // decrement fail if DATA_REQUEST was asserted
            hnd->fail--;
            // Reset the flag
            masterDataRequested = false;
            // NACK the transaction to complete the quick command
            PMBus_nackTransaction(PMBUSA_BASE);
        }
    }

    // Once the bus is free, if the slave NACK'd its a failure
    (slaveAckReceived == true) ? hnd->pass++ : hnd->fail++;
    return;
}

// End of File
