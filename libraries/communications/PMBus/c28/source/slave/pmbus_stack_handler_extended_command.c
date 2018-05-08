//#############################################################################
//
//! \file   pmbus_stack_handler_extended_command.c
//!
//! \brief  PMBUS_STACK_STATE_EXTENDED_COMMAND handler
//! \author Vishal Coelho
//! \date   Jul 9, 2015
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
PMBUS_STACK_FILENUM(8)

//*****************************************************************************
// the function definitions
//*****************************************************************************
//=============================================================================
// PMBUS_STACK_extendedCommandHandler()
//=============================================================================
void PMBUS_STACK_extendedCommandHandler( PMBus_Stack_Handle hnd )
{
    // Locals
    uint32_t status  = PMBus_Stack_Obj_getModuleStatus(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t command = buffer[1U];
    uint16_t nBytes  = 0U;

    // Set the current state to PMBUS_STACK_STATE_EXTENDED_COMMAND
    PMBus_Stack_Obj_setCurrentState(hnd,
            PMBUS_STACK_STATE_EXTENDED_COMMAND);

    if((status & PMBUS_PMBSTS_DATA_REQUEST) != 0U)
    {
        // DATA_REQUEST = 1 (an extended read)
        if(PMBus_Stack_doesCommandMatchTransaction(command,
            PMBUS_TRANSACTION_READBYTE))
        {
            // Set the object transaction type
            PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_READBYTE);
            // Call the handler for the READBYTE transaction
            (void)hnd->trnHnd[PMBUS_TRANSACTION_READBYTE](hnd);
            // Get the number of bytes to transfer, buffer pointer
            nBytes = PMBus_Stack_Obj_getNBytes(hnd);
            // Put the data to the PMBUS Transmit buffer, with PEC
            PMBus_putSlaveData(base, buffer, nBytes, true);
        }
        else if(PMBus_Stack_doesCommandMatchTransaction(command,
            PMBUS_TRANSACTION_READWORD))
        {
            // Set the object transaction type
            PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_READWORD);
            // Call the handler for the READWORD transaction
            (void)hnd->trnHnd[PMBUS_TRANSACTION_READWORD](hnd);
            // Get the number of bytes to transfer, buffer pointer
            nBytes = PMBus_Stack_Obj_getNBytes(hnd);
            // Put the data to the PMBUS Transmit buffer, with PEC
            PMBus_putSlaveData(base, buffer, nBytes, true);
        }
        else
        {
            // Unhandled exception
            PMBUS_STACK_ASSERT(0);
        }    
    }
    else if((status & PMBUS_PMBSTS_EOM) != 0U)
    {
        // EOM = 1, DATA_REQUEST = 0
        if(((status & PMBUS_PMBSTS_NACK) != 0U) &&
           ((status & PMBUS_PMBSTS_DATA_READY) == 0U))
        {
            // EOM = 1, NACK = 1, DATA_REQUEST = 0, DATA_READY = 0
            // Master NACKs the extended read, ack and
            // change state to IDLE
            PMBus_ackTransaction(base);
            PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);
        }
        else if(((status & PMBUS_PMBSTS_NACK) == 0U) &&
                ((status & PMBUS_PMBSTS_DATA_READY) != 0U))
        {
            // EOM = 1, DATA_READY = 1, NACK = 0, DATA_REQUEST = 0
            // Master completes either an ext write byte/word

        	// set buffer pointer to the current pointer
        	buffer = PMBus_Stack_Obj_getCurrPtr(hnd);

            if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                            PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 2U)
            {
                // RD_BYTE_COUNT = 2, EOM = 1, DATA_READY = 1
                // extended write Byte (Receive buffer has Byte & PEC)

                // Read the data
                nBytes = PMBus_getSlaveData(base, buffer, status);
                // Set the object's nBytes field
                // Set the pointer in the buffer to point to the next
                // available spot
                PMBus_Stack_Obj_setCurrPtr(hnd, &buffer[nBytes]);
                // Set the object's nBytes field
                PMBus_Stack_Obj_setNBytes(hnd,
                        (nBytes + PMBus_Stack_Obj_getNBytes(hnd)));
                // Set the object transaction type
                PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_WRITEBYTE);
                // Call the handler for the WRITEBYTE transaction
                (void)hnd->trnHnd[PMBUS_TRANSACTION_WRITEBYTE](hnd);
                //ACK the entire transaction
                PMBus_ackTransaction(base);
            }
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                                 PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 3U)
            {
                // RD_BYTE_COUNT = 3, EOM = 1, DATA_READY = 1
                // Write word (Receive buffer has Byte #1, Byte #2, PEC)

                // Read the data
                nBytes = PMBus_getSlaveData(base, buffer, status);
                // Set the object's nBytes field
                // Set the pointer in the buffer to point to the next
                // available spot
                PMBus_Stack_Obj_setCurrPtr(hnd, &buffer[nBytes]);
                // Set the object's nBytes field
                PMBus_Stack_Obj_setNBytes(hnd,
                        (nBytes + PMBus_Stack_Obj_getNBytes(hnd)));
                // Set the object transaction type
                PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_WRITEWORD);
                // Call the handler for the WRITEWORD transaction
                (void)hnd->trnHnd[PMBUS_TRANSACTION_WRITEWORD](hnd);
                //ACK the entire transaction
                PMBus_ackTransaction(base);
            }
            else
            {
                // Unhandled exception
                PMBUS_STACK_ASSERT(0);
            }
            // Set next state to IDLE
            PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);
        }
        else
        {
            // Unhandled exception
            // TODO
            PMBUS_STACK_ASSERT(0);
        }
    }
    else
    {
        // EOM = 0, DATA_REQUEST = 0, DATA_READY = X, NACK = X
        // Unhandled exception
        PMBUS_STACK_ASSERT(0); 
    }
}

// End of File
