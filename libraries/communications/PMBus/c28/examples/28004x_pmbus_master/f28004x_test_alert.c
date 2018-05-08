//#############################################################################
//
//! \file   f28004x_test_alert.c
//!
//! \brief  Alert
//! \author Vishal Coelho
//! \date   Jun 16, 2015
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
// PMBUS_TEST_initAlert()
//=============================================================================
void PMBUS_TEST_initAlert(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set count to 1
    hnd->count = 1;

    // Enable the test
#if ENABLE_TEST_15 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_15 == 1
}

//=============================================================================
// PMBUS_TEST_runAlert()
//=============================================================================
void PMBUS_TEST_runAlert(PMBUS_TEST_Handle hnd)
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

	// Reset the EOM flag
	endOfMessage = false;

	// Once the bus is free, if the slave NACK'd its a failure
	(slaveAckReceived == true) ? hnd->pass++ : hnd->fail++;

	// Loop till the alert signal is asserted
	while(alertEdgeAsserted == false){}

    // Clear the spot where the alerting slave's address will go
    memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));

    // An alert was recevied
    // Configure the master to set the address to the alert address,
    // enable Read and expect the alerting slave's address (no PEC)
    PMBus_configMaster(PMBUSA_BASE, ALERT_RESPONSE_ADDRESS, 1U,
            PMBUS_MASTER_ENABLE_READ);
    // Wait for the EOM, and slave to ack the address before
    // reading data -- done in the ISR
    while(endOfMessage == false){}
    PMBus_getMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0],
            pmbusStatus);

    // NOTE:  the alert line needs to be asserted for the slave to respond
    // to the alert response address, if you de-assert early the slave
    // ignores the alert response address line. The slave state machine will
    // de-assert when it detects an EOM, NACK and ALERT_EDGE

	// Check DATA_READY is asserted at the end of alert response
	(masterDataAvailable == true) ? hnd->pass++ : hnd->fail++;
    // Check that the alerting slave sent its address
    (bytesReceived == 1U) ? hnd->pass++ : hnd->fail++;
    // Slave sends its address in the 7 most significant bits with a
    // 0 or 1 in the LSb, which we dont care about
    ((pmbusMasterBuffer[0] & 0xFEU) == (SLAVE_ADDRESS << 1U)) ?
    		hnd->pass++ : hnd->fail++;
    return;
}

// End of File
