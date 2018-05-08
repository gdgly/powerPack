//#############################################################################
//
//! \file   f28004x_test_extended_write_byte.c
//!
//! \brief  Write Byte (Extended)
//! \author Vishal Coelho
//! \date   Jul 7, 2015
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
// PMBUS_TEST_initExtendedWriteByte()
//=============================================================================
void PMBUS_TEST_initExtendedWriteByte(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT

    // Enable the test
#if ENABLE_TEST_18 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_18 == 1
}

//=============================================================================
// PMBUS_TEST_runExtendedWriteByte()
//=============================================================================
void PMBUS_TEST_runExtendedWriteByte(PMBUS_TEST_Handle hnd)
{
    // Locals


    pmbusMasterBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND; // Extended Command
    pmbusMasterBuffer[1] = PMBUS_CMD_STORE_DEFAULT_CODE; // Command
    pmbusMasterBuffer[2] = PMBUS_CMD_STORE_DEFAULT_CODE ^ 0xFFU; // Byte
    

    // Do an extended write byte
    // Configure the master to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable extended command,
    // 1 byte
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, 1U,
            (PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_EXT_CMD |
             PMBUS_MASTER_ENABLE_CMD));
    PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 3U);

    // Wait for the EOM, and slave to ack the address before
    // reading data -- done in the ISR
    while(endOfMessage == false){}

    // Once the bus is free, if the slave NACK'd its a failure
    (slaveAckReceived == true) ? hnd->pass++ : hnd->fail++;
    return;
}

// End of File
