//#############################################################################
//
//! \file   f28004x_handle_block_wrpc.c
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
#include "f28004x_pmbus_slave_test.h"

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// PMBus_Stack_blockWriteReadProcessCallHandler()
//=============================================================================
void PMBus_Stack_blockWriteReadProcessCallHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    // The Block Write portion
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);
    uint16_t i;

    // Should have received command, byte count, 255 bytes but no PEC
    (nBytes == 257U)? pass++ : fail++;
    // Command
    (buffer[0U] ==  PMBUS_CMD_PAGE_PLUS_READ)? pass++ : fail++;
    // Byte Count
    (buffer[1U] ==  0xFFU)? pass++ : fail++;
    for(i = 1U; i <= 255U; i++)
    {
        if(buffer[i + 1U] ==  PMBUS_CMD_PAGE_PLUS_READ ^ i)
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }

    // The Block Read portion
    // Set the number of bytes to send (inlcuding the byte count)
    PMBus_Stack_Obj_setNBytes(hnd, 256U);

    // Set the byte cont as the first byte to be trasnmitted
    buffer[0] = 255U;

    for(i = 1U; i <= 255U; i++)
    {
        buffer[i] = buffer[i+1] ^ i;  // Send this message to the master
    }

    (trn == PMBUS_TRANSACTION_BLOCKWRPC)? pass++: fail++;
    
    // Change the Block Write/Read/Process Call handler for the next test
    PMBus_Stack_Obj_setTransactionHandler(hnd, PMBUS_TRANSACTION_BLOCKWRPC,
    		(void (*)(void *))PMBus_Stack_processCallHandler);

    // Update number of completed tests
    testsCompleted++;
}

// End of File
