//#############################################################################
//
//! \file   f28004x_handle_send_byte.c
//!
//! \brief  Send Byte
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
// PMBus_Stack_sendByteHandler()
//=============================================================================
void PMBus_Stack_sendByteHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);

    (nBytes == 2U)? pass++ : fail++;
    (hnd->ptrBuffer[0U] ==  0x55U)? pass++ : fail++;
    (trn == PMBUS_TRANSACTION_SENDBYTE)? pass++: fail++;
    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table,
    		           nBytes - 1, buffer[1]))
    {
        pass++;
    }
    else
    {
        fail++;
    }
    // Update number of completed tests
    testsCompleted++;
}


// End of File
