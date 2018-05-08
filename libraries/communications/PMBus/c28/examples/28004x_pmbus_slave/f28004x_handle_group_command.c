//#############################################################################
//
//! \file   f28004x_handle_group_command.c
//!
//! \brief  Group Command (Slave is 2nd addressed)
//! \author Vishal Coelho
//! \date   Jun 23, 2015
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
// PMBus_Stack_groupCommandHandler()
//=============================================================================
void PMBus_Stack_groupCommandHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);

    (nBytes == 4U)? pass++ : fail++;
    (hnd->ptrBuffer[0U] ==  PMBUS_CMD_MFR_VOUT_MIN)? pass++ : fail++;
    (hnd->ptrBuffer[1U] ==  PMBUS_CMD_MFR_VOUT_MIN ^ 1U)? pass++ : fail++;
    (hnd->ptrBuffer[2U] ==  PMBUS_CMD_MFR_VOUT_MIN ^ 2U)? pass++ : fail++;
    (trn == PMBUS_TRANSACTION_WRITEWORD)? pass++: fail++;
    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table,
    		           nBytes - 1, buffer[3]))
    {
        pass++;
    }
    else
    {
        fail++;
    }
     
    // Change the write word handler for the next test
    PMBus_Stack_Obj_setTransactionHandler(hnd, PMBUS_TRANSACTION_WRITEWORD,
    		(void (*)(void *))PMBus_Stack_extWriteWordHandler);
            
    // Update number of completed tests
    testsCompleted++;
}

// End of File
