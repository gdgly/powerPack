//#############################################################################
//
//! \file   f28004x_handle_quick_command.c
//!
//! \brief  Quick Command
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
// PMBus_Stack_quickCommandHandler()
//=============================================================================
void PMBus_Stack_quickCommandHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    uint16_t address = PMBus_getOwnAddress(base);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);

    (nBytes == 0U)? pass++ : fail++;
    (address == SLAVE_ADDRESS)? pass++ : fail++;
    (PMBus_getCurrentAccessType(base) == PMBUS_ACCESSTYPE_WRITE)?
    		pass++: fail++;
    (trn == PMBUS_TRANSACTION_QUICKCOMMAND)? pass++: fail++;
    
    // Change the quick command handler for the next test
    PMBus_Stack_Obj_setTransactionHandler(hnd, PMBUS_TRANSACTION_QUICKCOMMAND,
    		(void (*)(void *))PMBus_Stack_alertHandler);

    // Update number of completed tests
    testsCompleted++;
}

// End of File
