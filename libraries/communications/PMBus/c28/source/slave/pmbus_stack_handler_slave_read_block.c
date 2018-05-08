//#############################################################################
//
//! \file   pmbus_stack_handler_slave_read_block.c
//!
//! \brief  PMBUS_STACK_STATE_READ_BLOCK handler
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
PMBUS_STACK_FILENUM(4)

//*****************************************************************************
// the function definitions
//*****************************************************************************
//=============================================================================
// PMBus_Stack_slaveReadBlockHandler()
//=============================================================================
void PMBus_Stack_slaveReadBlockHandler( PMBus_Stack_Handle hnd )
{
    // Locals
    uint32_t status  = PMBus_Stack_Obj_getModuleStatus(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint16_t *currPtr;
    uint16_t bytesTransmitted = 0U;
    uint16_t bytesToTransmit  = 0U;

    // Set the current state to READ_BLOCK
    PMBus_Stack_Obj_setCurrentState(hnd, PMBUS_STACK_STATE_READ_BLOCK);

    if(((status & PMBUS_PMBSTS_EOM) != 0U) &&
       ((status & PMBUS_PMBSTS_NACK) != 0U))
    {
        // EOM = 1, NACK = 1
        // Master has prematurely terminated the block read,
        // or in the READ/WAIT_FOR_EOM state, only 4 bytes
        // were required to be sent, and the transaction was complete
        // NOTE: ACK is required to allow the slave to ack its address in
        // any subsequent transaction.
    	PMBus_ackTransaction(base);

        // Return to the idle state
        PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);
    }
    else if((status & PMBUS_PMBSTS_DATA_REQUEST) != 0U)
    {
        // DATA_REQUEST = 1, EOM = 0, NACK = 0
        currPtr = PMBus_Stack_Obj_getCurrPtr(hnd);
        bytesTransmitted = (uint16_t)(currPtr - buffer);
        bytesToTransmit = nBytes - bytesTransmitted;
        if(bytesToTransmit > 4U)
        {
            // Put the data to the PMBUS Transmit buffer, without PEC
            PMBus_putSlaveData(base, currPtr, 4U, false);
            // Update the current index into the buffer
            PMBus_Stack_Obj_setCurrPtr(hnd, &currPtr[4U]);
        }
        else //bytesToTransmit <= 4U (the last transmission)
        {
            // Put the last few bytes (<=4) to the PMBUS Transmit buffer,
            // with PEC
            PMBus_putSlaveData(base, currPtr, bytesToTransmit, true);
            // Return to the EOM State
            PMBus_Stack_Obj_setNextState(hnd,
                    PMBUS_STACK_STATE_READ_WAIT_FOR_EOM);
        }
    }
    else
    {
        // Unhandled exception
        PMBUS_STACK_ASSERT(0);
    }
}

// End of File
