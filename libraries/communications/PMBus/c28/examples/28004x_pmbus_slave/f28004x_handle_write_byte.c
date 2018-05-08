//#############################################################################
//
//! \file   f28004x_handle_write_byte.c
//!
//! \brief  Write Byte
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
// PMBus_Stack_writeByteHandler()
//=============================================================================
void PMBus_Stack_writeByteHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);

    (nBytes == 3U)? pass++ : fail++;
    (hnd->ptrBuffer[0U] ==  0x55U)? pass++ : fail++;
    (hnd->ptrBuffer[1U] ==  0xAAU)? pass++ : fail++;
    (trn == PMBUS_TRANSACTION_WRITEBYTE)? pass++: fail++;
    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table,
    		           nBytes - 1, buffer[2]))
    {
        pass++;
    }
    else
    {
        fail++;
    }

    
    // Change the write byte handler for the next test
    PMBus_Stack_Obj_setTransactionHandler(hnd, PMBUS_TRANSACTION_WRITEBYTE,
    		(void (*)(void *))PMBus_Stack_extWriteByteHandler);

    // Update number of completed tests
    testsCompleted++;
}


// End of File
