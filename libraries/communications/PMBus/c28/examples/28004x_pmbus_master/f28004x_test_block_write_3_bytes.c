//#############################################################################
//
//! \file   f28004x_test_block_write_3_bytes.c
//!
//! \brief  Block Write (3 bytes)
//! \author Vishal Coelho
//! \date   May 20, 2015
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
// PMBUS_TEST_initBlockWrite3Bytes()
//=============================================================================
void PMBUS_TEST_initBlockWrite3Bytes(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set the block length to 3
    hnd->count = 3U;

    // Enable the test
#if ENABLE_TEST_12 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_12 == 1
}

//=============================================================================
// PMBUS_TEST_runBlockWrite3Bytes()
//=============================================================================
void PMBUS_TEST_runBlockWrite3Bytes(PMBUS_TEST_Handle hnd)
{
    // Locals
    uint16_t i = 0U;

    pmbusMasterBuffer[0] = PMBUS_CMD_PAGE_PLUS_WRITE;       // Command
    for(i = 1U; i <= hnd->count; i++)
    {
    	// Bytes #0 to #N-1 (2)
        pmbusMasterBuffer[i] = pmbusMasterBuffer[0] ^ i;
    }

    // Block writes must be done in chunks of 4 bytes starting with the
    // command byte

    // Config the master to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // >3 bytes to transfer
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, hnd->count,
            (PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_CMD));

    // Transfer the first 3 bytes, i.e., command, byte #0, #1, #2
    // NOTE: Byte count is automatically inserted after command
    PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 4U);
    // NOTE: PEC is automatically inserted at the end of block write
    // transmission

    // Wait for the EOM, and slave to ack the address before
    // reading data -- done in the ISR
    while(endOfMessage == false){}

    // Once the bus is free, if the slave NACK'd its a failure
    (slaveAckReceived == true) ? hnd->pass++ : hnd->fail++;
    return;
}

// End of File
