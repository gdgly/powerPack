//#############################################################################
//
//! \file   pmbus_stack_handler_slave_idle.c
//!
//! \brief  PMBUS_STACK_STATE_IDLE handler
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
PMBUS_STACK_FILENUM(3)

//*****************************************************************************
// the function definitions
//*****************************************************************************
//=============================================================================
// PMBus_Stack_slaveIdleHandler()
//=============================================================================
void PMBus_Stack_slaveIdleHandler( PMBus_Stack_Handle hnd )
{
    // Locals
    uint32_t status  = PMBus_Stack_Obj_getModuleStatus(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t nBytes  = 0U;
    uint16_t *currPtr;

    // Set the current state to idle
    PMBus_Stack_Obj_setCurrentState(hnd, PMBUS_STACK_STATE_IDLE);

    // Rewind the current pointer
    PMBus_Stack_Obj_setCurrPtr(hnd, buffer);

    // Set the object transaction type
    PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_NONE);

    // Check if the unit is busy
    if((status & PMBUS_PMBSTS_UNIT_BUSY) == 0U)
    {
        // Neither PMBUS hardware nor firmware are stuck,
        //
        // The user must use the clock low timeout feature to
    	// fire an interrupt off to the CPU, query the comms
    	// stack object, take remedial measures and reset
    	// the state machine prior to returning from the interrupt
    }

    if((status & PMBUS_PMBSTS_DATA_READY) != 0U)
    {
        if((status & PMBUS_PMBSTS_EOM) != 0U)
        {
            // EOM = 1, DATA_READY = 1
            if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                            PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 2U)
            {
                // RD_BYTE_COUNT = 2, EOM = 1, DATA_READY = 1
                // Send Byte (Receive buffer has Byte #0, PEC)

                // Read the data
                nBytes = PMBus_getSlaveData(base, buffer, status);
                // Set the object's nBytes field
                PMBus_Stack_Obj_setNBytes(hnd, nBytes);
                // Set the object transaction type
                PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_SENDBYTE);
                // Call the handler for the SENDBYTE transaction
                (void)hnd->trnHnd[PMBUS_TRANSACTION_SENDBYTE](hnd);
                //ACK the entire transaction
                PMBus_ackTransaction(base);
            }
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                                 PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 3U)
            {
                // RD_BYTE_COUNT = 3, EOM = 1, DATA_READY = 1
                // Write Byte (Receive buffer has Command, Byte #0, PEC)

                // Read the data
                nBytes = PMBus_getSlaveData(base, buffer, status);
                // Set the object's nBytes field
                PMBus_Stack_Obj_setNBytes(hnd, nBytes);
                // Set the object transaction type
                PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_WRITEBYTE);
                // Call the handler for the WRITEBYTE transaction
                (void)hnd->trnHnd[PMBUS_TRANSACTION_WRITEBYTE](hnd);
                //ACK the entire transaction
                PMBus_ackTransaction(base);
            }

            else
            {
                // RD_BYTE_COUNT = 1, EOM = 1, DATA_READY = 1
                // Unhandled exception
                PMBUS_STACK_ASSERT(0);
            }
        }
        else
        {
            // EOM = 0, DATA_READY = 1
            if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                           PMBUS_PMBSTS_RD_BYTE_COUNT_S) >= 3U)
            {
                // RD_BYTE_COUNT = 3/4, EOM = 0, DATA_READY = 1
                // Read buffer is full, this must either be a write word,
                // block write or process call
                //
                // Read the RXBUF, ack the transaction and then proceed
                // to the BLOCK_WRITE_OR_PROCESS_CALL state
                //
                // Read the data
                nBytes = PMBus_getSlaveData(base, buffer, status);
                // Set the pointer in the buffer to point to the next
                // available spot
                currPtr = PMBus_Stack_Obj_getCurrPtr(hnd);
                PMBus_Stack_Obj_setCurrPtr(hnd,
                                           &currPtr[nBytes]);

                // Set the object's nBytes field
                PMBus_Stack_Obj_setNBytes(hnd, nBytes);
                //ACK the entire transaction
                PMBus_ackTransaction(base);
                // Set the next state to
                // PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL
                PMBus_Stack_Obj_setNextState(hnd,
                        PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL);
            }
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                                   PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 2U)
            {
            	// RD_BYTE_COUNT = 2, EOM = 0, DATA_READY = 1
            	// This must be either an extended
            	// - Read Byte
            	// - Read Word
                // - Write Byte
                // - Write Word

            	// Read the command
            	nBytes = PMBus_getSlaveData(base, buffer, status);
            	// Check the first byte for the extended command byte
            	PMBUS_STACK_ASSERT((buffer[0] == PMBUS_CMD_MFR_SPECIFIC_COMMAND) ||
            			(buffer[0] == PMBUS_CMD_PMBUS_COMMAND_EXT));
                // Set the pointer in the buffer to point to the next
                // available spot
                PMBus_Stack_Obj_setCurrPtr(hnd,
                                           &buffer[nBytes]);

                // Set the object's nBytes field
                PMBus_Stack_Obj_setNBytes(hnd, nBytes);
            	// ACK the command for the slave to be able to proceed
            	PMBus_ackTransaction(base);

            	// Transition to the state PMBUS_STACK_STATE_EXTENDED_COMMAND
            	PMBus_Stack_Obj_setNextState(hnd,
            			PMBUS_STACK_STATE_EXTENDED_COMMAND);
            }
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                       PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 1U)
            {
                // RD_BYTE_COUNT = 1, EOM = 0, DATA_READY = 1
                // This could be either a
                // - Read Byte
                // - Read Word
                // - Block Read
                // The command determines which read transaction is being
                // requested by the master. We need to wait for DATA_REQUEST
                // to come in

                // Read the command
                nBytes = PMBus_getSlaveData(base, buffer, status);

                // ACK the command, for the master to be able to issue
                // the repeated start, and therby the DATA_REQUEST interrupt
                PMBus_ackTransaction(base);

                // Transition to the state PMBUS_STATE_READ_WAIT_FOR_EOM
                PMBus_Stack_Obj_setNextState(hnd,
                        PMBUS_STACK_STATE_READ_WAIT_FOR_EOM);
            }
            else
            {
                // Unhandled exception
                PMBUS_STACK_ASSERT(0);
            }

        }

    }else{
        // DATA_READY = 0
        if((status & PMBUS_PMBSTS_EOM) == 0U)
        {
            // DATA_READY = 0, EOM = 0
            if((status & PMBUS_PMBSTS_DATA_REQUEST) != 0U)
            {
                // DATA_READY = 0, EOM = 0, DATA_REQUEST = 1
                // This is a receive byte request
            	// Set the object transaction type
            	PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_RECEIVEBYTE);
                // Call the handler for the RECEIVEBYTE transaction
                (void)hnd->trnHnd[PMBUS_TRANSACTION_RECEIVEBYTE](hnd);
                // Get the number of bytes to transfer, buffer pointer
                nBytes = PMBus_Stack_Obj_getNBytes(hnd);

                // Put the data to the PMBUS Transmit buffer, with PEC
                PMBus_putSlaveData(base, buffer, nBytes, true);
                // Transition to the RECEIVE_BYTE_WAIT_FOR_EOM
                PMBus_Stack_Obj_setNextState(hnd,
                            PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM);
            }
            else
            {
                // DATA_READY = 0, EOM = 0, DATA_REQUEST = 0
                // Unhandled Exception
                PMBUS_STACK_ASSERT(0);
            }
        }
        else
        {
            // DATA_READY = 0 EOM = 1
            if((status & PMBUS_PMBSTS_DATA_REQUEST) != 0U)
            {
                // DATA_READY = 0, EOM = 1, DATA_REQUEST = 1
                // Unhandled Exception
                PMBUS_STACK_ASSERT(0);

            }
            else if (((status & PMBUS_PMBSTS_NACK) != 0U) &&
            		 ((status & PMBUS_PMBSTS_ALERT_EDGE) != 0U))
            {
            	// DATA_READY = 0, EOM = 1, NACK = 1, ALERT_EDGE = 1
            	// This is an alert response
            	// ACK the transaction
            	PMBus_ackTransaction(base);
            }
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                       PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 0U)
            {
                // RD_BYTE_COUNT = 0, EOM = 1, DATA_READY = 0, NACK = 0
                // Quick Command

                // Set the object's nBytes field
                PMBus_Stack_Obj_setNBytes(hnd, 0U);
                // Set the object transaction type
                PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_QUICKCOMMAND);
                // Call the handler for the QUCIKCOMMAND transaction
                (void)hnd->trnHnd[PMBUS_TRANSACTION_QUICKCOMMAND](hnd);
                //ACK the entire transaction
                PMBus_ackTransaction(base);
            }
            else
            {
                // DATA_READY = 0, EOM = 1, DATA_REQUEST = 0,
                // RD_BYTE_COUNT != 0
                // Unhandled Exception
                PMBUS_STACK_ASSERT(0);
            }
        }
    }
}
// End of File
