//#############################################################################
//
//! \file   f28004x_test_group_command.c
//!
//! \brief  Group Command
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
// PMBUS_TEST_initGroupCommand()
//=============================================================================
void PMBUS_TEST_initGroupCommand(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set count to 3
    hnd->count = 3;

    // Enable the test
#if ENABLE_TEST_17 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_17 == 1
}

//=============================================================================
// PMBUS_TEST_runGroupCommand()
//=============================================================================
void PMBUS_TEST_runGroupCommand(PMBUS_TEST_Handle hnd)
{
    // Locals

    // Do a Group Command

	// Clear the spot where the alerting slave's address will go
	memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));
    pmbusMasterBuffer[0] = PMBUS_CMD_MFR_VOUT_MIN; // Command
    pmbusMasterBuffer[1] = pmbusMasterBuffer[0] ^ 1U; // Byte #0
    pmbusMasterBuffer[2] = pmbusMasterBuffer[0] ^ 2U; // Byte #1
    // Configure the master to enable PEC, enable Write (by omitting the read
	// option from the configWord, you enable write), enable group command,
    // enable command, 2 bytes
	PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, 2U,
			(PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_GRP_CMD |
			 PMBUS_MASTER_ENABLE_CMD));
	PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 3U);

	// Wait on DATA_REQUEST
	while(masterDataRequested == false)
	{
		// Fail if EOM & NACK after the 1st message
		if(endOfMessage == true && slaveAckReceived == false)
		{
			hnd->fail++;
			break;
		}
	}
	masterDataRequested = false;
	(slaveAckReceived == true)? hnd->pass++ : hnd->fail++;


	// Clear the spot where the alerting slave's address will go
	memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));
    pmbusMasterBuffer[0] = PMBUS_CMD_MFR_VOUT_MAX; // Command
    pmbusMasterBuffer[1] = pmbusMasterBuffer[0] ^ 1U; // Byte #0
    pmbusMasterBuffer[2] = pmbusMasterBuffer[0] ^ 2U; // Byte #1
    // Configure the master to enable PEC, enable Write (by omitting the read
	// option from the configWord, you enable write), enable group command,
    // enable command, 2 bytes
	PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS + 1U, 2U,
			(PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_GRP_CMD |
					 PMBUS_MASTER_ENABLE_CMD));
	PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 3U);

	// Wait on DATA_REQUEST
	while(masterDataRequested == false)
	{
		// exit if EOM & NACK after the 2nd message
		// This slave doesnt exist on the bus and master will see
		// a NACK for this address, which generateds the EOM.
		if(endOfMessage == true && slaveAckReceived == false)
		{
			hnd->pass++;
			break;
		}
	}
	RESET_FLAGS

	// Clear the spot where the alerting slave's address will go
	memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));
    pmbusMasterBuffer[0] = PMBUS_CMD_MFR_IOUT_MAX; // Command
    pmbusMasterBuffer[1] = pmbusMasterBuffer[0] ^ 1U; // Byte #0
    pmbusMasterBuffer[2] = pmbusMasterBuffer[0] ^ 2U; // Byte #1
    // Configure the master to enable PEC, enable Write (by omitting the read
	// option from the configWord, you enable write), enable group command,
    // enable command, 2 bytes
	PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS + 2U, 2U,
			(PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_GRP_CMD |
					 PMBUS_MASTER_ENABLE_CMD));
	PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 3U);

	// Wait on DATA_REQUEST
	while(masterDataRequested == false)
	{
		// exit if EOM & NACK after the 3rd message
		// This slave doesnt exist on the bus and master will see
		// a NACK for this address, which generateds the EOM.
		if(endOfMessage == true && slaveAckReceived == false)
		{
			hnd->pass++;
			break;
		}
	}
	RESET_FLAGS

	// Clear the spot where the alerting slave's address will go
	memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));
    pmbusMasterBuffer[0] = PMBUS_CMD_MFR_POUT_MAX; // Command
    pmbusMasterBuffer[1] = pmbusMasterBuffer[0] ^ 1U; // Byte #0
    pmbusMasterBuffer[2] = pmbusMasterBuffer[0] ^ 2U; // Byte #1
    // Configure the master to enable PEC, enable Write (by omitting the read
	// option from the configWord, you enable write), disable group command
    // (by ommitting it), enable command, 2 bytes
	PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS + 3U, 2U,
			(PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_CMD));
	PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 3U);

    // Wait for the EOM, and slave to ack the address before
    // reading data -- done in the ISR
    while(endOfMessage == false){}

	// if EOM & NACK after the 4th message
	// This slave doesnt exist on the bus and master will see
	// a NACK for this address, which generateds the EOM.
	if(endOfMessage == true && slaveAckReceived == false)
	{
		hnd->pass++;
	}
    return;
}

// End of File
