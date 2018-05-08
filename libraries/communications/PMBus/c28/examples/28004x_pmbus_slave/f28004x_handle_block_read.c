//#############################################################################
//
//! \file   f28004x_handle_block_read.c
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
#include "f28004x_pmbus_slave_test.h"

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// PMBus_Stack_blockReadHandler()
//=============================================================================
void PMBus_Stack_blockReadHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    uint16_t command = buffer[0];
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);
    uint16_t i;

    // Set the number of bytes to send (including the byte count)
    PMBus_Stack_Obj_setNBytes(hnd, 256U);

    // Set the byte cont as the first byte to be transmitted
    buffer[0] = 255U;

    for(i = 1U; i <= 255U; i++)
    {
        buffer[i] = command ^ i;  // Send this message to the master
    }

    (trn == PMBUS_TRANSACTION_BLOCKREAD)? pass++: fail++;
    
    // Change the handler for the next test
    PMBus_Stack_Obj_setTransactionHandler(hnd, PMBUS_TRANSACTION_BLOCKREAD,
    		(void (*)(void *))PMBus_Stack_blockRead3BytesHandler);


    // Update number of completed tests
    testsCompleted++;
}

// End of File
