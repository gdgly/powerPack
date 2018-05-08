//#############################################################################
//
//! \file   f28004x_handle_block_read_3_bytes.c
//!
//! \brief  Block Read (3 bytes)
//! \author Vishal Coelho
//! \date   Jun 11, 2015
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
// PMBus_Stack_blockRead3BytesHandler()
//=============================================================================
void PMBus_Stack_blockRead3BytesHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    uint16_t command = buffer[0];
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);
    uint16_t i;

    // Set the number of bytes to send (including the byte count)
    PMBus_Stack_Obj_setNBytes(hnd, 4U);

    // Set the byte cont as the first byte to be transmitted
    buffer[0] = 3U;

    for(i = 1U; i <= 3U; i++)
    {
        buffer[i] = command ^ i;  // Send this message to the master
    }

    (trn == PMBUS_TRANSACTION_BLOCKREAD)? pass++: fail++;
    
    // Update number of completed tests
    testsCompleted++;
}

// End of File
