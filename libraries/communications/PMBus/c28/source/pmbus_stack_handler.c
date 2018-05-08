//#############################################################################
//
//! \file   PMBus_Stack_Handler.c
//!
//! \brief  PMBUS Communications State Machine
//! \author Vishal Coelho
//! \date   Mar 10, 2015
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
#include "pmbus_stack_handler.h"

//*****************************************************************************
//defines
//*****************************************************************************
PMBUS_STACK_FILENUM(2)

//*****************************************************************************
// the function definitions
//*****************************************************************************
//=============================================================================
// PMBus_Stack_slaveHandler()
//=============================================================================
void PMBus_Stack_slaveHandler( PMBus_Stack_Handle hnd )
{
    // Read the status bits once at the start of each state handler
    // The status bits are cleared on a read, therefore, they should be
    // read once at the start of each ISR; any subsequent flags will cause
    // another interrupt
    PMBus_Stack_Obj_setModuleStatus(hnd, PMBus_getStatus(hnd->moduleBase));

    switch(PMBus_Stack_Obj_getNextState(hnd))
    {
        case PMBUS_STACK_STATE_IDLE:
            PMBus_Stack_slaveIdleHandler(hnd);
            break;
        case PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM:
            PMBus_Stack_slaveReceiveByteWaitForEomHandler(hnd);
            break;
        case PMBUS_STACK_STATE_READ_BLOCK:
            PMBus_Stack_slaveReadBlockHandler(hnd);
            break;
        case PMBUS_STACK_STATE_READ_WAIT_FOR_EOM:
            PMBus_Stack_slaveReadWaitForEOMHandler(hnd);
            break;
        case PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL:
            PMBus_Stack_slaveBlockWriteOrProcessCallHandler(hnd);
            break;
        case PMBUS_STACK_STATE_EXTENDED_COMMAND:
            PMBUS_STACK_extendedCommandHandler(hnd);
            break;
        default:
            PMBus_Stack_Obj_setCurrentState(hnd, PMBUS_STACK_STATE_IDLE);
            PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);
            PMBus_Stack_slaveIdleHandler(hnd);
            break;
    }
}

// End of File
