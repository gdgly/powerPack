//#############################################################################
//
//! \file   main.c
//!
//! \brief  PMBUS Master Demo Code
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
#include "f28004x_pmbus_master_test.h"
#include "pmbus_t0_bitfields.h"

//*****************************************************************************
//defines
//*****************************************************************************

//*****************************************************************************
//globals
//*****************************************************************************
PMBus_Stack_Obj pmbusStackMaster;
PMBus_Stack_Handle hndPmbusStackMaster = &pmbusStackMaster;
uint16_t pmbusMasterBuffer[256];

volatile bool slaveAckReceived = false;
volatile bool masterDataAvailable = false;
volatile bool masterDataRequested = false;
volatile bool receivedPecValid = false;
volatile bool endOfMessage = false;
volatile bool alertEdgeAsserted = false;
volatile bool clockLowTimeout = false;
volatile uint16_t  bytesReceived = 0U;
volatile uint32_t pmbusStatus = 0UL;

#ifdef __cplusplus
#pragma DATA_SECTION("PMBUSRegsFile")
#else
#pragma DATA_SECTION(PMBUSRegs, "PMBUSRegsFile")
#endif // __cplusplus
volatile struct PMBUS_REGS PMBUSRegs;

volatile int16_t pass =0U, fail = 0U;

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
    uint16_t i, j;
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

    // Setup the PMBUS Stack Object
    PMBus_Stack_Obj_setMode(hndPmbusStackMaster, PMBUS_STACK_MODE_MASTER);
    PMBus_Stack_initModule(hndPmbusStackMaster, PMBUSA_BASE,
                &pmbusMasterBuffer[0]);

    // Configure the PMBUS module clock to be less than PMBUS_MODULE_FREQ_MAX
    moduleFreq = PMBus_configModuleClock(PMBUSA_BASE, PMBUS_MODULE_FREQ_MAX,
    		PMBUS_SYS_FREQ_MAX);
    // Configure the PMBUS bus clock
    PMBus_configBusClock(PMBUSA_BASE, PMBUS_CLOCKMODE_STANDARD,
            moduleFreq);

    // Call each test sequentially and check the outputs
    for(i = 0; i < NTESTS; i++){
        // Clear the buffer
        // Set the buffer to some default non-zero value
        memset(pmbusMasterBuffer, 0xBAADU, sizeof(pmbusMasterBuffer));

        hnd = &PMBUS_TESTS[i];
        hnd->init = (void (*)(void *))initTestList[i];
        hnd->run  = (void (*)(void *))runTestList[i];
        if(hnd->init != NULL){
            hnd->init(hnd);
        }
        hnd->pass = hnd->fail = 0;
        if(hnd->enabled == true){ //Test has been enabled
            hnd->run(hnd);
            // Wait some time to allow the slave to complete processing the
            // transaction before proceeding
            for(j = 0U; j < 1000U; j++){};

            //Tally the pass/fail metrics
            pass += hnd->pass;
            fail += hnd->fail;

            if(hnd->fail > 0U )
            {
                __asm(" ESTOP0");
            }
        }else{ //Test has been disabled
            hnd->pass = -1;
            hnd->fail = -1;
        }
    }

    done(); // End of test

    // code does not reach this point
    return 1;
}   // end of main


//*****************************************************************************
// pmbusIntHandler()
//*****************************************************************************
__interrupt void pmbusIntHandler( void )
{
    // Read the status registers
    pmbusStatus = PMBus_getStatus(PMBUSA_BASE);

    //Write to the PMBUS_STACK object
    PMBus_Stack_Obj_setModuleStatus(hndPmbusStackMaster, pmbusStatus);

    bytesReceived = (pmbusStatus & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                                      PMBUS_PMBSTS_RD_BYTE_COUNT_S;
    endOfMessage        = (bool)((pmbusStatus & PMBUS_PMBSTS_EOM) >> 5U);
    slaveAckReceived    = (bool)((~pmbusStatus & PMBUS_PMBSTS_NACK) >> 6U);
    masterDataRequested = (bool)((pmbusStatus & PMBUS_PMBSTS_DATA_REQUEST) >>
                                  4U);
    receivedPecValid    = (bool)((pmbusStatus & PMBUS_PMBSTS_PEC_VALID) >>
                                  7U);
    alertEdgeAsserted   = (bool)((pmbusStatus & PMBUS_PMBSTS_ALERT_EDGE) >>
    		                      16U);
    clockLowTimeout     = (bool)((pmbusStatus & PMBUS_PMBSTS_CLK_LOW_TIMEOUT) >>
                                  8U);
    if((bytesReceived != 0U) || // EOM + data
        ((bytesReceived == 4U) && //!EOM+DATA_READY+4 bytes
          ((pmbusStatus & PMBUS_PMBSTS_DATA_READY) != 0U)))
    {
        masterDataAvailable = true;
    }

    // ACK any pending group 8 interrupts (if any got set)
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

// End of File
