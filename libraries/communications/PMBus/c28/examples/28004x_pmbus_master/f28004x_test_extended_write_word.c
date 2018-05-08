//#############################################################################
//
//! \file   f28004x_test_extended_write_word.c
//!
//! \brief  Write Word (Extended)
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
// PMBUS_TEST_initExtendedWriteWord()
//=============================================================================
void PMBUS_TEST_initExtendedWriteWord(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT

    // Enable the test
#if ENABLE_TEST_19 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_19 == 1
}

//=============================================================================
// PMBUS_TEST_runExtendedWriteWord()
//=============================================================================
void PMBUS_TEST_runExtendedWriteWord(PMBUS_TEST_Handle hnd)
{
    // Locals


    pmbusMasterBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND; // Extended Command
    pmbusMasterBuffer[1] = PMBUS_CMD_VOUT_COMMAND; // Command
    pmbusMasterBuffer[2] = PMBUS_CMD_VOUT_COMMAND ^ 0xFFU; // Byte
    pmbusMasterBuffer[3] = PMBUS_CMD_VOUT_COMMAND ^ 0x55U; // Byte
    

    // Do an extended write word
    // Configure the master to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable extended command,
    // 2 bytes
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, 2U,
            (PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_EXT_CMD |
             PMBUS_MASTER_ENABLE_CMD));
    PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 4U);

    // Wait for the EOM, and slave to ack the address before
    // reading data -- done in the ISR
    while(endOfMessage == false){}

    // Once the bus is free, if the slave NACK'd its a failure
    (slaveAckReceived == true) ? hnd->pass++ : hnd->fail++;
    return;
}

// End of File
