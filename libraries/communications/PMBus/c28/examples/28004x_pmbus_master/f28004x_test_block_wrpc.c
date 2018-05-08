//#############################################################################
//
//! \file   f28004x_test_block_wrpc.c
//!
//! \brief  Block Write-Read Process Call (255 bytes)
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
// PMBUS_TEST_initBlockWriteReadProcessCall()
//=============================================================================
void PMBUS_TEST_initBlockWriteReadProcessCall(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set count to 255
    hnd->count = 255U;

    // Enable the test
#if ENABLE_TEST_9 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_9 == 1
}

//=============================================================================
// PMBUS_TEST_runBlockWriteReadProcessCall()
//=============================================================================
void PMBUS_TEST_runBlockWriteReadProcessCall(PMBUS_TEST_Handle hnd)
{
    // Locals
    uint16_t i, count = 0U, nBytes = 0U;

    // Clear the spot where the command will go
    memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));

    // command, soon to be overwritten by block read
    pmbusMasterBuffer[0]  = PMBUS_CMD_PAGE_PLUS_READ;
    for(i = 1U; i <= hnd->count; i++)
    {
        pmbusMasterBuffer[i] = pmbusMasterBuffer[0] ^ i; // Bytes #0 to #N-1
    }
    // Block-Write, Block-Read, and Process Call
    // Config the master to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // enable process call (the master does the block read, with the repeated
    // start, right after the block write finishes)
    // Write, and then read, hnd->count bytes
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, hnd->count,
            (PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_PRC_CALL |
                    PMBUS_MASTER_ENABLE_CMD));

    // Transfer the first 4 bytes, i.e., command, byte #0, #1, #2
    // NOTE: Byte count is automatically inserted after command
    PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 4U);
    // Write the remaining bytes in chunks of 4, last transaction is N+2 % 4
    for(i = 4U; i <= hnd->count; ){
        // Wait for DATA_REQUEST to assert
        while(masterDataRequested == false){}
        masterDataRequested = false;
        if((hnd->count - i - 1U) >= 4U)
        {    // Transfer 4 bytes at a time
            PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[i], 4U);
            i = i + 4U;
        }
        else // remaining bytes < 4U
        {
            PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[i],
                    (hnd->count + 1U - i));
            i += (hnd->count + 1U - i);
        }
        // NOTE: PEC is not transmitted for a Block Write-Read Process Call
    }
    // Master automatically issues a repeated start (because of the process
    // call), and waits for the slave to respond with the block data...when
    // the necessary bytes (specified in PMBMC.BYTE_COUNT) is received, master
    // NACKs last byte and generates an EOM
    // However, if the slave is transmitting more than 3 bytes, the
    // DATA_READY goes high first, the RXBUF is full and must be read
    // before the slave can send any more data

    // Wait for the EOM, the slave transmits all its data, the
    // master NACKs it, and then issues an EOM on the bus
    // -- this flag is set in the ISR
    // NOTE: Although the master issues a NACK to the slave to indicate the
    // end of transmission, the NACK bit (status) is not asserted at the master
    // end, only at the slave end.
    while(endOfMessage == false)
    {
        if(masterDataAvailable == true)
        {
            // Reset the flag
            masterDataAvailable = false;
            count = PMBus_getMasterData(PMBUSA_BASE, 
                    &pmbusMasterBuffer[nBytes], pmbusStatus);
            nBytes += count;
            // Master has received 4 bytes
        }
    }

    if((endOfMessage == true) && (masterDataAvailable == true))
    {   // EOM = 1 DATA_READY = 1, but this wasnt captured in the while loop
        // above
        count = PMBus_getMasterData(PMBUSA_BASE, &pmbusMasterBuffer[nBytes],
                pmbusStatus);
        nBytes += count;
        // No need to reset these flags, they will be reset at the start of the
        // next test
    }


    // Check that we got nBytes + 1 (byte count) bytes
    (nBytes == hnd->count + 1) ? hnd->pass++ : hnd->fail++;
    (pmbusMasterBuffer[0]  == hnd->count) ? hnd->pass++ : hnd->fail++;
    for (i = 1U; i <= hnd->count; i++)
    {
        if(pmbusMasterBuffer[i] == PMBUS_CMD_PAGE_PLUS_READ)
        {
            hnd->pass++;
        }
        else
        {
            hnd->fail++;
        }
    }
    (receivedPecValid == true)? hnd->pass++: hnd->fail++;
    return;
}

// End of File
