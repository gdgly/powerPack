//#############################################################################
//
//! \file   f28004x_handle_process_call.c
//!
//! \brief  Process Call (write word then read word)
//! \author Vishal Coelho
//! \date   Jun 16, 2015
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
// PMBus_Stack_processCallHandler()
//=============================================================================
void PMBus_Stack_processCallHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    // The Write Word portion
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);
    uint16_t command;

    // Should have received command, 2 bytes but no PEC
    (nBytes == 3U)? pass++ : fail++;
    // Command
    (buffer[0U] ==  0x55U)? pass++ : fail++;
    // Byte #1
    (buffer[1U] ==  0xAAU)? pass++ : fail++;
    // Byte #2
    (buffer[2U] ==  0x7EU)? pass++ : fail++;

    command = buffer[0U];

    // The Read Word portion
    // Set the number of bytes to send
    PMBus_Stack_Obj_setNBytes(hnd, 2U);
    // Byte #1
    buffer[0U] =  buffer[1U] ^ command;
    // Byte #2
    buffer[1U] =  buffer[2U] ^ command;

    (trn == PMBUS_TRANSACTION_BLOCKWRPC)? pass++: fail++;

    // Update number of completed tests
    testsCompleted++;
}

// End of File
