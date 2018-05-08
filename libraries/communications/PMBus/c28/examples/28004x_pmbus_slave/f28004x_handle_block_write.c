//#############################################################################
//
//! \file   f28004x_handle_block_write.c
//!
//! \brief  Block Write (255 bytes)
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
// PMBus_Stack_blockWriteHandler()
//=============================================================================
void PMBus_Stack_blockWriteHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);
    uint16_t i;
    (nBytes == 258U)? pass++ : fail++;
    (hnd->ptrBuffer[0U] ==  0x55U)? pass++ : fail++; // Command
    (hnd->ptrBuffer[1U] ==  0xFFU)? pass++ : fail++; // Byte Count
    (trn == PMBUS_TRANSACTION_BLOCKWRITE)? pass++: fail++;
    for(i = 0U; i < 255U; i++)
    {
        (hnd->ptrBuffer[i + 2U] ==  i)? pass++ : fail++;
    }
    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table, nBytes - 1,
    		           buffer[257U]))
    {
        pass++;
    }
    else
    {
        fail++;
    }
    // Change the block write handler for the next test
    PMBus_Stack_Obj_setTransactionHandler(hnd, PMBUS_TRANSACTION_BLOCKWRITE,
    		(void (*)(void *))PMBus_Stack_blockWrite3BytesHandler);
            
    // Update number of completed tests
    testsCompleted++;
}

// End of File
