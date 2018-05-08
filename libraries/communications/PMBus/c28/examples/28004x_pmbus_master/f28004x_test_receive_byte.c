//#############################################################################
//
//! \file   f28004x_test_receive_byte.c
//!
//! \brief  Receive Byte
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
// PMBUS_TEST_initReceiveByte()
//=============================================================================
void PMBUS_TEST_initReceiveByte(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set count to 1
    hnd->count = 1;

    // Enable the test
#if ENABLE_TEST_5 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_5 == 1
}

//=============================================================================
// PMBUS_TEST_runReceiveByte()
//=============================================================================
void PMBUS_TEST_runReceiveByte(PMBUS_TEST_Handle hnd)
{
    // Locals

    // Clear the spot where the command will go
    memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));

    // Do a receive byte
    // Configure the master to enable PEC, enable Read
    // Expect 1 byte
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, 1U,
            (PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_READ));
    // Wait for the EOM, and slave to ack the address before
    // reading data -- done in the ISR
    while(endOfMessage == false){}
    PMBus_getMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0],
            pmbusStatus);

    // Check the received byte
    (bytesReceived == 1U) ? hnd->pass++ : hnd->fail++;
    (pmbusMasterBuffer[0] == 0x55U) ? hnd->pass++ : hnd->fail++;
    return;
}

// End of File
