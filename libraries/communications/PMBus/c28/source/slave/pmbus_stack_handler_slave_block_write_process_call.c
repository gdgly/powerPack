//#############################################################################
//
//! \file   pmbus_stack_handler_slave_block_write_process_call.c
//!
//! \brief  PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL handler
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
PMBUS_STACK_FILENUM(5)

//*****************************************************************************
// the function definitions
//*****************************************************************************
//=============================================================================
// PMBus_Stack_slaveBlockWriteOrProcessCallHandler()
//=============================================================================
void PMBus_Stack_slaveBlockWriteOrProcessCallHandler( PMBus_Stack_Handle hnd )
{
    // Locals
    uint32_t status  = PMBus_Stack_Obj_getModuleStatus(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getCurrPtr(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t nBytes  = 0U;

    // Set the current state to block write/Process Call
    PMBus_Stack_Obj_setCurrentState(hnd,
            PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL);

    if((status & PMBUS_PMBSTS_EOM) != 0U)
    {
        // EOM = 1
        if((status & PMBUS_PMBSTS_DATA_READY) != 0U)
        {
            // RD_BYTE_COUNT != 0, EOM = 1, DATA_READY = 1, DATA_REQUEST = 0
            // This must be the last few bytes of the block write command
        	// or an extended write byte/word command

            // Start saving data in the buffer from the currPtr position
            // Read the data
            nBytes = PMBus_getSlaveData(base, buffer, status);
            // Set the pointer in the buffer to point to the next
            // available spot
            PMBus_Stack_Obj_setCurrPtr(hnd, &buffer[nBytes]);
            // Set the object's nBytes field
            PMBus_Stack_Obj_setNBytes(hnd,
                    (nBytes + PMBus_Stack_Obj_getNBytes(hnd)));
			// Set the object transaction type
			PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_BLOCKWRITE);
			// Call the handler for the BLOCKWRITE transaction
			hnd->trnHnd[PMBUS_TRANSACTION_BLOCKWRITE](hnd);
            //ACK the entire transaction
            PMBus_ackTransaction(base);
            // Set the next state to PMBUS_STACK_STATE_IDLE
            PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);
        }
        else
        {
            // RD_BYTE_COUNT = 0, EOM = 1, DATA_READY = 0, DATA_REQUEST = 0
            // End-of-message, no data ready, no data requested, no bytes
            // received. This must be a write word command
            //ACK the entire transaction
            PMBus_ackTransaction(base);
            // Set the object transaction type
            PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_WRITEWORD);
            // Call the handler for the WRITEWORD transaction
            hnd->trnHnd[PMBUS_TRANSACTION_WRITEWORD](hnd);
            // Set the next state to PMBUS_STACK_STATE_IDLE
            PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);
        }
    }
    else
    {
        // EOM = 0
        if((status & PMBUS_PMBSTS_DATA_READY) != 0U)
        {
            // EOM = 0, DATA_READY = 1 RD_BYTE_COUNT = ?
            // Start saving data in the buffer from the currPtr position
            // Read the data
            nBytes = PMBus_getSlaveData(base, buffer, status);
            // Set the pointer in the buffer to point to the next
            // available spot
            PMBus_Stack_Obj_setCurrPtr(hnd, &buffer[nBytes]);
            // Set the object's nBytes field
            PMBus_Stack_Obj_setNBytes(hnd,
                    (nBytes + PMBus_Stack_Obj_getNBytes(hnd)));
            //ACK the entire transaction
            PMBus_ackTransaction(base);
            // Stay in the same state, i.e.
            // PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL
        }
        else if ((status & PMBUS_PMBSTS_DATA_REQUEST) != 0U)
        {
            // EOM = 0, DATA_READY = 0 RD_BYTE_COUNT  = 0, DATA_REQUEST = 1
            // This is a Block Write, Read, Process Call
        	// Set the object transaction type
        	PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_BLOCKWRPC);
            // Call the handler for the BLOCKWRPC transaction
            (void)hnd->trnHnd[PMBUS_TRANSACTION_BLOCKWRPC](hnd);
            // Get the number of bytes to transfer, buffer pointer
            nBytes = PMBus_Stack_Obj_getNBytes(hnd);
            // Rewind the buffer pointer
            buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);

            if(nBytes <= 4U)
            {
                // Put the data to the PMBUS Transmit buffer, with PEC
                PMBus_putSlaveData(base, buffer, nBytes, true);
            }
            else // nBytes > 4
            {
                // Put the data to the PMBUS Transmit buffer, without PEC
                PMBus_putSlaveData(base, buffer, 4U, false);
                // Update the current index into the buffer
                PMBus_Stack_Obj_setCurrPtr(hnd, &buffer[4U]);
            }
            // Proceed to the READ_BLOCK state
            PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_READ_BLOCK);
        }
        else
        {
            // EOM = 0, DATA_READY = ? RD_BYTE_COUNT = ?, DATA_REQUEST = 0
            // A Fault condition
            PMBUS_STACK_ASSERT(0);
        }
    }

}

// End of File
