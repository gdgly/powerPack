//#############################################################################
//
//! \file   f28004x_handle_extended_read_byte.c
//!
//! \brief  Read Byte (Extended)
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
#include "f28004x_pmbus_slave_test.h"

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// PMBus_Stack_extReadByteHandler()
//=============================================================================
void PMBus_Stack_extReadByteHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);
    uint16_t command = buffer[1];
    
    // Set the number of bytes to send
    PMBus_Stack_Obj_setNBytes(hnd, 1U);

    buffer[0] = command ^ 0xFF; // Send this message to the master

    (trn == PMBUS_TRANSACTION_READBYTE)? pass++: fail++;
            
    // Update number of completed tests
    testsCompleted++;
}

// End of File
