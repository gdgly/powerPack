//#############################################################################
//
//! \file   f28004x_test_process_call.c
//!
//! \brief  Process Call (write word, then read word)
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
// PMBUS_TEST_initProcessCall()
//=============================================================================
void PMBUS_TEST_initProcessCall(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT

    // Enable the test
#if ENABLE_TEST_14 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_14 == 1
}

//=============================================================================
// PMBUS_TEST_runProcessCall()
//=============================================================================
void PMBUS_TEST_runProcessCall(PMBUS_TEST_Handle hnd)
{
    // Locals
    uint16_t nBytes = 0U;

    pmbusMasterBuffer[0] = 0x55U; // Command
    pmbusMasterBuffer[1] = 0xAAU; // Byte #0
    pmbusMasterBuffer[2] = 0x7EU; // Byte #1

    // Do a Process Call (write word then read word)
    // Configure the master to enable PEC (processing), enable Write (by
    // omitting the read option from the configWord, you enable write),
    // enable command, enable process call (the master does the read word,
    // with the repeated start, right after the write word finishes)
    // Write, and then read 2 bytes
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, 2U,
    		(PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_PRC_CALL |
    		                    PMBUS_MASTER_ENABLE_CMD));
    PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 3U);

    // Master automatically issues a repeated start (because of the process
    // call), and waits for the slave to respond with the word...when
    // the necessary bytes (specified in PMBMC.BYTE_COUNT) is received, master
    // NACKs last byte and generates an EOM

    // Wait for the EOM, the slave transmits all its data, the
    // master NACKs it, and then issues an EOM on the bus
    // -- this flag is set in the ISR
    // NOTE: Although the master issues a NACK to the slave to indicate the
    // end of transmission, the NACK bit (status) is not asserted at the master
    // end, only at the slave end.
    while(endOfMessage == false){}

    if((endOfMessage == true) && (masterDataAvailable == true))
	{   // EOM = 1 DATA_READY = 1
		nBytes = PMBus_getMasterData(PMBUSA_BASE, &pmbusMasterBuffer[nBytes],
				pmbusStatus);
		// No need to reset these flags, they will be reset at the start of the
		// next test
	}

    // Check that we got 2 bytes
    (nBytes == 2U) ? hnd->pass++ : hnd->fail++;
    (pmbusMasterBuffer[0]  == (0xAAU ^ 0x55U)) ? hnd->pass++ : hnd->fail++;
    (pmbusMasterBuffer[1]  == (0x7EU ^ 0x55U)) ? hnd->pass++ : hnd->fail++;
    (receivedPecValid == true)? hnd->pass++: hnd->fail++;
    return;
}

// End of File
