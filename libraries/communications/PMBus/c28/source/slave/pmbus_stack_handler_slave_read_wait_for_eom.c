//#############################################################################
//
//! \file   pmbus_stack_handler_slave_read_wait_for_eom.c
//!
//! \brief  PMBUS_STACK_STATE_READ_WAIT_FOR_EOM handler
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
PMBUS_STACK_FILENUM(6)

//*****************************************************************************
// the function definitions
//*****************************************************************************
//=============================================================================
// PMBus_Stack_slaveReadWaitForEOMHandler()
//=============================================================================
void PMBus_Stack_slaveReadWaitForEOMHandler( PMBus_Stack_Handle hnd )
{
    // Locals
    uint32_t status  = PMBus_Stack_Obj_getModuleStatus(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t nBytes  = 0U;
    uint16_t command = buffer[0U];

    // Set the current state to Read/Wait for EOM
    PMBus_Stack_Obj_setCurrentState(hnd,
            PMBUS_STACK_STATE_READ_WAIT_FOR_EOM);
    if(((status & PMBUS_PMBSTS_EOM) != 0U) &&
       ((status & PMBUS_PMBSTS_NACK) != 0U))
    {
        // EOM = 1, NACK = 1
        // NOTE: ACK is required to allow the slave to ack its address in
        // any subsequent transaction.
    	PMBus_ackTransaction(base);

        // Read byte/word/block was successful, return to the
        // Idle state
        PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);
    }
    // At this point the command is already in the buffer
    else if(PMBus_Stack_doesCommandMatchTransaction(command,
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
    else if(PMBus_Stack_doesCommandMatchTransaction(command,
            PMBUS_TRANSACTION_BLOCKREAD))
    {
    	// Set the object transaction type
    	PMBus_Stack_Obj_setTransaction(hnd, PMBUS_TRANSACTION_BLOCKREAD);
        // Call the handler for the READBLOCK transaction
        (void)hnd->trnHnd[PMBUS_TRANSACTION_BLOCKREAD](hnd);
        // Get the number of bytes to transfer, buffer pointer
        nBytes = PMBus_Stack_Obj_getNBytes(hnd);
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
        // Unhandled exception
        PMBUS_STACK_ASSERT(0);
    }
}
// End of File
