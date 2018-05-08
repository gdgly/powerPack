//#############################################################################
//
//! \file   f28004x_handle_noalert.c
//!
//! \brief  Alert (different slave on the line, this slave does not respond)
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
// PMBus_Stack_noAlertHandler()
//=============================================================================
void PMBus_Stack_noAlertHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);
    uint16_t addressedAs = PMBus_getOwnAddress(base);
    PMBus_accessType aType = PMBus_getCurrentAccessType(base);

    if(trn == PMBUS_TRANSACTION_QUICKCOMMAND)
    {
        // Got the quick command
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
