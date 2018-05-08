//#############################################################################
//
//! \file   f28004x_handle_block_write_2_bytes.c
//!
//! \brief  Block Write (2 bytes)
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
// PMBus_Stack_blockWrite2BytesHandler()
//=============================================================================
void PMBus_Stack_blockWrite2BytesHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);
    uint16_t i;

    (nBytes == 4U)? pass++ : fail++;
    // Command
    (hnd->ptrBuffer[0U] ==  PMBUS_CMD_PAGE_PLUS_WRITE)? pass++ : fail++;
    // A block write attempt with 2 bytes is a write word transaction
    (trn == PMBUS_TRANSACTION_WRITEWORD)? pass++: fail++;
    for(i = 1U; i <= 2U; i++)
    {
        if(hnd->ptrBuffer[i] ==  (PMBUS_CMD_PAGE_PLUS_WRITE ^ i))
        {
        	pass++;
        }
        else
        {
        	fail++;
        }
    }
    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table,
    		           nBytes - 1, buffer[3U]))
    {
        pass++;
    }
    else
    {
        fail++;
    }
    
    // Change the write word handler for the next test
    PMBus_Stack_Obj_setTransactionHandler(hnd, PMBUS_TRANSACTION_WRITEWORD,
    		(void (*)(void *))PMBus_Stack_groupCommandHandler);

    // Update number of completed tests
    testsCompleted++;
}

// End of File
