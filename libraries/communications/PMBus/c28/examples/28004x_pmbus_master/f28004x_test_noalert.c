//#############################################################################
//
//! \file   f28004x_test_noalert.c
//!
//! \brief  Alert Response to a different slave
//! \author Vishal Coelho
//! \date   Jun 23, 2015
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
// PMBUS_TEST_initNoAlert()
//=============================================================================
void PMBUS_TEST_initNoAlert(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set count to 1
    hnd->count = 1;

    // Enable the test
#if ENABLE_TEST_16 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_16 == 1
}

//=============================================================================
// PMBUS_TEST_runNoAlert()
//=============================================================================
void PMBUS_TEST_runNoAlert(PMBUS_TEST_Handle hnd)
{
    // Locals

	// Increment fail, a DATA_REQUEST should set it back to 0
	hnd->fail++;


	// Clear the spot where the alerting slave's address will go
    memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));

    // Lets assume slave 0x39 asserted the alert line -- for the purposes
    // of this test let the master assert  the alert line, and pretend
    // that slave 0x39 did it

	// Check EOM is asserted at the end of failed alert response
	(endOfMessage == true) ? hnd->pass++ : hnd->fail++;
	// Did the master timeout?
	(clockLowTimeout == true) ? hnd->pass++ : hnd->fail++;
    // Check that no NACK was sent, i.e. it will be an ACK instead
    (slaveAckReceived == true) ? hnd->pass++ : hnd->fail++;

    RESET_FLAGS

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
