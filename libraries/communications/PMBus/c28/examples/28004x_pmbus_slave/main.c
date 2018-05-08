//#############################################################################
//
//! \file   main.c
//!
//! \brief  PMBUS Slave Demo Code
//! \author Vishal Coelho
//! \date   Apr 1, 2015
//
//  Group:          C2000
//  Target Device:  TMS320F28004x
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
#include "pmbus_t0_bitfields.h"

#include <string.h>
//*****************************************************************************
//defines
//*****************************************************************************

//*****************************************************************************
//globals
//*****************************************************************************
PMBus_Stack_Obj pmbusStackSlave;
PMBus_Stack_Handle hndPmbusStackSlave = &pmbusStackSlave;
uint16_t pmbusSlaveBuffer[300U];

volatile uint16_t testsCompleted = 0U;
volatile uint16_t pass = 0U, fail = 0U;

#ifdef __cplusplus
#pragma DATA_SECTION("PMBUSRegsFile")
#else
#pragma DATA_SECTION(PMBUSRegs, "PMBUSRegsFile")
#endif // __cplusplus
volatile struct PMBUS_REGS PMBUSRegs;
//*****************************************************************************
//prototypes
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc")
#else
#pragma CODE_SECTION(pmbusIntHandler, ".TI.ramfunc")
#endif // __cplusplus
__interrupt void pmbusIntHandler( void );

//*****************************************************************************
// the function definitions
//*****************************************************************************
int main(void)
{
    // Locals
    uint16_t i;
    uint32_t moduleFreq = 0U;

#if defined(_FLASH)
    // Setup the Flash banks
    PMBUS_Example_setupFlash();
#endif //defined(_FLASH)

    // Setup the system clocking
    PMBUS_Example_setupSysCtrl();

    // Enable the PMBUS GPIOs
    PMBUS_Example_setupGPIO();

    // Setup the interrupt tables, register PMBUS interrupt handler
    PMBUS_Example_setupInterrupts(pmbusIntHandler);

    //************************************************************************
    // Transaction Handlers
    //************************************************************************
    // Set the default handlers, user must overwrite
    for(i = 0U; i < NTRANSACTIONS; i++){
        PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
         (PMBus_Transaction)i, (void (*)(void *))
         PMBus_Stack_defaultTransactionHandler);
    }

    // Overwrite the send byte transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
            PMBUS_TRANSACTION_SENDBYTE,
            (void (*)(void *))PMBus_Stack_sendByteHandler);
    // Overwrite the write byte transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
            PMBUS_TRANSACTION_WRITEBYTE,
            (void (*)(void *))PMBus_Stack_writeByteHandler);
    // Overwrite the write word transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
            PMBUS_TRANSACTION_WRITEWORD,
            (void (*)(void *))PMBus_Stack_writeWordHandler);
    // Overwrite the block write transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
            PMBUS_TRANSACTION_BLOCKWRITE,
            (void (*)(void *))PMBus_Stack_blockWriteHandler);
    // Overwrite the Recevie Byte transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
            PMBUS_TRANSACTION_RECEIVEBYTE,
               (void (*)(void *))PMBus_Stack_receiveByteHandler);
    // Overwrite the Read Byte transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
           PMBUS_TRANSACTION_READBYTE,
           (void (*)(void *))PMBus_Stack_readByteHandler);
    // Overwrite the Read Word transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
           PMBUS_TRANSACTION_READWORD,
           (void (*)(void *))PMBus_Stack_readWordHandler);
    // Overwrite the Block Read transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
           PMBUS_TRANSACTION_BLOCKREAD,
           (void (*)(void *))PMBus_Stack_blockReadHandler);
    // Overwrite the Block Write Read Process Call transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
           PMBUS_TRANSACTION_BLOCKWRPC, (void (*)(void *))
           PMBus_Stack_blockWriteReadProcessCallHandler);
    // Overwrite the Quick Command transaction handler
    PMBus_Stack_Obj_setTransactionHandler(hndPmbusStackSlave,
           PMBUS_TRANSACTION_QUICKCOMMAND,
           (void (*)(void *))PMBus_Stack_quickCommandHandler);

    //************************************************************************

    // Set the buffer to some default non-zero value
    memset(pmbusSlaveBuffer, 0xBAADU, sizeof(pmbusSlaveBuffer));

    // Setup the PMBUS Stack Object
    PMBus_Stack_Obj_setMode(hndPmbusStackSlave, PMBUS_STACK_MODE_SLAVE);
    // Set the slave address and mask
    PMBus_Stack_Obj_setAddress(hndPmbusStackSlave, SLAVE_ADDRESS);
    PMBus_Stack_Obj_setAddressMask(hndPmbusStackSlave, SLAVE_ADDRESSMASK);
    // Initialize the state machine handler
    PMBus_Stack_initModule(hndPmbusStackSlave, PMBUSA_BASE,
            &pmbusSlaveBuffer[0]);
// TODO
    // Configure the PMBUS module clock to be PMBUS_MODULE_FREQ_MAX
    moduleFreq = PMBus_configModuleClock(PMBUSA_BASE, PMBUS_MODULE_FREQ_MAX,
            PMBUS_SYS_FREQ_MAX);
    // Configure the PMBUS bus clock
    PMBus_configBusClock(PMBUSA_BASE, PMBUS_CLOCKMODE_STANDARD,
            moduleFreq);

    while(testsCompleted != NENABLEDTESTS){
        // Loop forever
        if(fail > 0U)
        {
            __asm(" ESTOP0");
        }
    };


    done(); // End of test

    // code does not reach this point
    return 1;
}   // end of main


//=============================================================================
// pmbusIntHandler()
//=============================================================================
__interrupt void pmbusIntHandler( void )
{
    // Call the library State Machine handler
    PMBus_Stack_slaveHandler(hndPmbusStackSlave);
    // ACK any pending group 8 interrupts (if any got set)
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

// End of File
