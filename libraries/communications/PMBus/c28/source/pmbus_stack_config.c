//#############################################################################
//
//! \file   PMBus_Stack_config.c
//!
//! \brief  PMBUS Communications Stack Configuration
//! \author Vishal Coelho
//! \date   Mar 11, 2015
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
#include <stdint.h>
#include <stdbool.h>
#include "pmbus_stack_config.h"

//*****************************************************************************
//defines
//*****************************************************************************
PMBUS_STACK_FILENUM(1)
//*****************************************************************************
//globals
//*****************************************************************************
PMBus_Stack_Obj PMBUS_STACK_Slave;
PMBus_Stack_Handle hnd_PMBUS_STACK_Slave = &PMBUS_STACK_Slave;

//*****************************************************************************
// the function definitions
//*****************************************************************************
//=============================================================================
// PMBus_Stack_initModule()
//=============================================================================
bool PMBus_Stack_initModule( PMBus_Stack_Handle hnd,
        const uint32_t moduleBase, uint16_t *buffer )
{
    // Locals
    bool status = false;

    // Set the module base address - by default this is PMBUS-A
    PMBus_Stack_Obj_setModuleBase(hnd, moduleBase);

    // Assign the buffer pointer to the object, set currPtr to the head of the
    // buffer
    PMBus_Stack_Obj_setPtrBuffer(hnd, buffer);
    PMBus_Stack_Obj_setCurrPtr(hnd, buffer);

    // Reset the PMBUS Module
    PMBus_disableModule(PMBus_Stack_Obj_getModuleBase(hnd));

    // Take the PMBUS out of reset
    PMBus_enableModule(PMBus_Stack_Obj_getModuleBase(hnd));

    if(PMBus_Stack_Obj_getMode(hnd) == PMBUS_STACK_MODE_SLAVE)
    {
        // Initialize the slave module
        PMBus_initSlaveMode(PMBus_Stack_Obj_getModuleBase(hnd),
                PMBus_Stack_Obj_getAddress(hnd),
                PMBus_Stack_Obj_getAddressMask(hnd));
        // Configure the slave module (writes to the PMBSC register)
        PMBus_configSlave(PMBUSA_BASE, (PMBUS_SLAVE_ENABLE_PEC_PROCESSING |
                PMBUS_SLAVE_AUTO_ACK_4_BYTES));

        // Enable interrupts
        PMBus_enableInterrupt(PMBus_Stack_Obj_getModuleBase(hnd),
                (PMBUS_INT_DATA_READY | PMBUS_INT_DATA_REQUEST |
                 PMBUS_INT_EOM));
                 
        // Reset the state machine
        PMBus_Stack_Obj_setCurrentState(hnd, PMBUS_STACK_STATE_IDLE);
        PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);

        status = true;
    }
    else // (PMBus_Stack_Obj_getMode(hnd) == PMBUS_STACK_MODE_MASTER)
    {
        // Zero out the slave address and set the mask to 0x7F
        // (the mask is N/A in master mode)
        PMBus_Stack_Obj_setAddress(hnd, 0U);
        PMBus_Stack_Obj_setAddressMask(hnd, 0x7FU);

        // Initialize the master module
        PMBus_initMasterMode(PMBus_Stack_Obj_getModuleBase(hnd));

        // Enable interrupts
        PMBus_enableInterrupt(PMBus_Stack_Obj_getModuleBase(hnd),
                (PMBUS_INT_DATA_READY | PMBUS_INT_DATA_REQUEST |
                 PMBUS_INT_EOM | PMBUS_INT_ALERT));

        // Reset the state machine
        PMBus_Stack_Obj_setCurrentState(hnd, PMBUS_STACK_STATE_IDLE);
        PMBus_Stack_Obj_setNextState(hnd, PMBUS_STACK_STATE_IDLE);

        status = true;
    }

    return(status);
}

//=============================================================================
// PMBus_Stack_defaultTransactionHandler()
//=============================================================================
int32_t PMBus_Stack_defaultTransactionHandler(PMBus_Stack_Handle hnd)
{
    // Replace with an actual handler. This will stop emulation
    PMBUS_STACK_ASSERT(0);
    return( -1);
}

// End of File
