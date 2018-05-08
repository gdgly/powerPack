//#############################################################################
//
//! \file   f28004x_pmbus_master_test.c
//!
//! \brief  Tries out different master transactions (used to test slave FSM)
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
#include "f28004x_pmbus_master_test.h"

//*****************************************************************************
//globals
//*****************************************************************************
PMBUS_TEST_Obj PMBUS_TESTS[NTESTS];
PMBUS_TEST_Handle hnd;

void (*initTestList[NTESTS])(PMBUS_TEST_Handle) = {
        PMBUS_TEST_initSendByte,
        PMBUS_TEST_initWriteByte,
        PMBUS_TEST_initWriteWord,
        PMBUS_TEST_initBlockWrite,
        PMBUS_TEST_initReceiveByte,
        PMBUS_TEST_initReadByte,
        PMBUS_TEST_initReadWord,
        PMBUS_TEST_initBlockRead,
        PMBUS_TEST_initBlockWriteReadProcessCall,
        PMBUS_TEST_initQuickCommand,
        PMBUS_TEST_initBlockWrite2Bytes,
        PMBUS_TEST_initBlockWrite3Bytes,
        PMBUS_TEST_initBlockRead3Bytes,
        PMBUS_TEST_initProcessCall,
        PMBUS_TEST_initAlert,
        PMBUS_TEST_initNoAlert,
        PMBUS_TEST_initGroupCommand,
        PMBUS_TEST_initExtendedWriteByte,
        PMBUS_TEST_initExtendedWriteWord,
        PMBUS_TEST_initExtendedReadByte,
        PMBUS_TEST_initExtendedReadWord,
};

void (*runTestList[NTESTS])(PMBUS_TEST_Handle)  = {
        PMBUS_TEST_runSendByte,
        PMBUS_TEST_runWriteByte,
        PMBUS_TEST_runWriteWord,
        PMBUS_TEST_runBlockWrite,
        PMBUS_TEST_runReceiveByte,
        PMBUS_TEST_runReadByte,
        PMBUS_TEST_runReadWord,
        PMBUS_TEST_runBlockRead,
        PMBUS_TEST_runBlockWriteReadProcessCall,
        PMBUS_TEST_runQuickCommand,
        PMBUS_TEST_runBlockWrite2Bytes,
        PMBUS_TEST_runBlockWrite3Bytes,
        PMBUS_TEST_runBlockRead3Bytes,
        PMBUS_TEST_runProcessCall,
        PMBUS_TEST_runAlert,
        PMBUS_TEST_runNoAlert,
        PMBUS_TEST_runGroupCommand,
        PMBUS_TEST_runExtendedWriteByte,
        PMBUS_TEST_runExtendedWriteWord,
        PMBUS_TEST_runExtendedReadByte,
        PMBUS_TEST_runExtendedReadWord,
};

// End of File
