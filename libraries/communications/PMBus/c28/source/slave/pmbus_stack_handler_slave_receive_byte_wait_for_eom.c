//#############################################################################
//
//! \file   pmbus_stack_handler_slave_receive_byte_wait_for_eom.c
//!
//! \brief  PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM handler
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
#include "pmbus_stack_handler.h"
//*****************************************************************************
//defines
//*****************************************************************************
PMBUS_STACK_FILENUM(7)

//*****************************************************************************
// the function definitions
//*****************************************************************************
//=============================================================================
// PMBus_Stack_slaveReceiveByteWaitForEomHandler()
//=============================================================================
void PMBus_Stack_slaveReceiveByteWaitForEomHandler( PMBus_Stack_Handle hnd )
{
    // Locals
    uint32_t status  = PMBus_Stack_Obj_getModuleStatus(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);

    // Set the current state to RECEIVE_BYTE_WAIT_FOR_EOM
    PMBus_Stack_Obj_setCurrentState(hnd,
            PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM);

    if(((status & PMBUS_PMBSTS_EOM) != 0U) &&
            ((status & PMBUS_PMBSTS_NACK) != 0U))
    {
        // DATA_READY = 0, EOM = 1, DATA_REQUEST = 0, NACK = 1
        // After a DATA_REQUEST for a receive byte is seen by the slave,
        // it places the requested byte (and PEC) on the line and transitions
        // from the idle to the recevie byte wait-for-eom state
        //
        // The only interrupt expected after the recevied byte is that from an
        // EOM. The quick command also has EOM=1 and DATA_READY=0 at the end.
        // In order to distinguish between the two, if an EOM is received while
        // in this state it was a receive byte, if an EOM was recevied in the
        // idle state it was a quick command
        //
        // NOTE: ACK is required to allow the slave to ack its address in
        // any subsequent transaction.
        PMBus_ackTransaction(base);

        // Return to the idle state
        PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);

        return;

    }
    else
    {
        // Unhandled Exception
        PMBUS_STACK_ASSERT(0);
    }
}

// End of File
