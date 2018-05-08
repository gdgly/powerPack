//#############################################################################
//
//! \file   f28004x_test_extended_read_byte.c
//!
//! \brief  Read Byte (Extended)
//! \author Vishal Coelho
//! \date   Jul 08, 2015
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
// PMBUS_TEST_initExtendedReadByte()
//=============================================================================
void PMBUS_TEST_initExtendedReadByte(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set count to 1
    hnd->count = 1;

    // Enable the test
#if ENABLE_TEST_20 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_20 == 1
}

//=============================================================================
// PMBUS_TEST_runExtendedReadByte()
//=============================================================================
void PMBUS_TEST_runExtendedReadByte(PMBUS_TEST_Handle hnd)
{
    // Locals
    uint16_t nBytes = 0U;

    // Clear the spot where the command will go
    memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));

    // Do an extended read byte
    // Config the master to send an extended read-byte command 
    // (by asserting the command and extended command bits) and then to issue 
    // a repeated start followed by a read (i.e. enable
    // read) and get a data byte and a PEC from the slave. Also enable PEC
    // processing on the master side to verify the PEC
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, 1U,
            (PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_READ |
            PMBUS_MASTER_ENABLE_CMD | PMBUS_MASTER_ENABLE_EXT_CMD));

    // Load the extended command and command bytes into the transmit register,
    // in this case the PMBUS_CMD_OPERATION command
    pmbusMasterBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND;
    pmbusMasterBuffer[1] = PMBUS_CMD_OPERATION;
    PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 2U);

    // Wait for the EOM, the slave transmits all its data, the
    // master NACKs it, and then issues an EOM on the bus
    // -- this flag is set in the ISR
    // NOTE: Although the master issues a NACK to the slave to indicate the
    // end of transmission, the NACK bit (status) is not asserted at the master
    // end, only at the slave end.
    while(endOfMessage == false){}

    nBytes = PMBus_getMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0],
            pmbusStatus);

    // Check the received byte
    (nBytes == 1U) ? hnd->pass++ : hnd->fail++;
    (pmbusMasterBuffer[0] == (PMBUS_CMD_OPERATION ^ 0xFF)) ? hnd->pass++ :
            hnd->fail++;
    (receivedPecValid == true)? hnd->pass++: hnd->fail++;
    return;
}

// End of File
