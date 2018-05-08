//#############################################################################
//
//! \file   f28004x_test_extended_read_word.c
//!
//! \brief  Read Word (Extended)
//! \author Vishal Coelho
//! \date   Jul 8, 2015
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
// PMBUS_TEST_initExtendedReadWord()
//=============================================================================
void PMBUS_TEST_initExtendedReadWord(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set count to 2
    hnd->count = 2;

    // Enable the test
#if ENABLE_TEST_21 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_21 == 1
}

//=============================================================================
// PMBUS_TEST_runExtendedReadWord()
//=============================================================================
void PMBUS_TEST_runExtendedReadWord(PMBUS_TEST_Handle hnd)
{
    // Locals
    uint16_t nBytes = 0U;

    // Clear the spot where the command will go
    memset(&pmbusMasterBuffer[0], 0U, hnd->count*sizeof(uint16_t));

    // Do a extended read byte
    // Configure the master to send a read-word command (by asserting the 
    // command and extended command bits) and then to issue a repeated start 
    // followed by a read (i.e. enable read) and get two data bytes and a 
    // PEC from the slave. Also enable PEC processing on the master side to 
    // verify the PEC
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, 2U,
            (PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_READ |
            PMBUS_MASTER_ENABLE_CMD | PMBUS_MASTER_ENABLE_EXT_CMD));

    // Load the extended command and command bytes into the transmit register,
    // in this case the PMBUS_CMD_VOUT_COMMAND command
    pmbusMasterBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND;
    pmbusMasterBuffer[1] = PMBUS_CMD_VOUT_COMMAND;
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
    (nBytes == 2U) ? hnd->pass++ : hnd->fail++;
    (pmbusMasterBuffer[0] == (PMBUS_CMD_VOUT_COMMAND ^ 0xFF)) ? hnd->pass++ :
            hnd->fail++;
    (pmbusMasterBuffer[1] == (PMBUS_CMD_VOUT_COMMAND ^ 0x55)) ? hnd->pass++ :
                hnd->fail++;
    (receivedPecValid == true)? hnd->pass++: hnd->fail++;
    return;
}

// End of File
