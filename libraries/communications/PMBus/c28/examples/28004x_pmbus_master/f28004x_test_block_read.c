//#############################################################################
//
//! \file   f28004x_test_block_read.c
//!
//! \brief  Block Read (255 bytes)
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
// PMBUS_TEST_initBlockRead()
//=============================================================================
void PMBUS_TEST_initBlockRead(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set count to 255
    hnd->count = 255U;

    // Enable the test
#if ENABLE_TEST_8 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_8 == 1
}

//=============================================================================
// PMBUS_TEST_runBlockRead()
//=============================================================================
void PMBUS_TEST_runBlockRead(PMBUS_TEST_Handle hnd)
{
    // Locals
    uint16_t count = 0U, nBytes = 0U, i = 0U;

    // Clear the spot where the command will go
    memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));

    // Do a read byte
    // Config the master to send a read-block command (by asserting the command
    // bit) and then to issue a repeated start followed by a read (i.e. enable
    // read) and get hnd->count data bytes and a PEC from the slave. Also
    // enable PEC proecessing on the master side to verify the PEC
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, hnd->count,
            (PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_READ |
            PMBUS_MASTER_ENABLE_CMD));

    // Load the command byte into the transmit register,
    // in this case the PMBUS_CMD_READ_EIN command
    pmbusMasterBuffer[0] = PMBUS_CMD_READ_EIN;
    PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 1U);

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


    // Check tat we got nBytes + 1 (byte count) bytes
    (nBytes == hnd->count + 1) ? hnd->pass++ : hnd->fail++;
    (pmbusMasterBuffer[0]  == hnd->count) ? hnd->pass++ : hnd->fail++;
    for (i = 1U; i <= hnd->count; i++)
    {
        if(pmbusMasterBuffer[i] == (PMBUS_CMD_READ_EIN ^ i))
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
