#ifndef _F28004X_PMBUS_MASTER_TEST_H_
#define _F28004X_PMBUS_MASTER_TEST_H_
//#############################################################################
//
//! \file   f28004x_pmbus_master_test.h
//!
//! \brief  Tries out different master transactions (used to test slave FSM)
//! \author Vishal Coelho
//! \date    Apr 6, 2015
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
#include <string.h>
#include "f28004x_examples_setup.h"
#include "pmbus_stack_handler.h"

//!
//! \defgroup PMBUS_MASTER_TESTS PMBus Master Mode Tests

//!
//! \ingroup PMBUS_MASTER_TESTS
//@{

#ifdef __cplusplus

extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
#define RESET_FLAGS               \
    slaveAckReceived     = false; \
    endOfMessage         = false; \
    masterDataAvailable  = false; \
    masterDataRequested  = false; \
    receivedPecValid     = false; \
    alertEdgeAsserted    = false; \
    clockLowTimeout      = false; \
    bytesReceived        = 0U;

#define RESET_TEST_OBJECT         \
    hnd->count           = 0U;    \
    hnd->pass            = 0U;    \
    hnd->fail            = 0U;    \
    hnd->enabled         = false;

#define ENABLE_TEST_1       1 // Send Byte
#define ENABLE_TEST_2       1 // Write Byte
#define ENABLE_TEST_3       1 // Write Word
#define ENABLE_TEST_4       1 // Block Write
#define ENABLE_TEST_5       1 // Receive Byte
#define ENABLE_TEST_6       1 // Read Byte
#define ENABLE_TEST_7       1 // Read Word
#define ENABLE_TEST_8       1 // Block Read
#define ENABLE_TEST_9       1 // Block Write/ Read/ Process Call
#define ENABLE_TEST_10      1 // Quick Command
#define ENABLE_TEST_11      1 // Block Write (command, byte count, 2 bytes)
                              // - this is actually a write word
#define ENABLE_TEST_12      1 // Block Write (command, byte count, 3 bytes)
#define ENABLE_TEST_13      1 // Block Read (3 bytes)
#define ENABLE_TEST_14      1 // Process call (write word then read word)
#define ENABLE_TEST_15      1 // Alert
#define ENABLE_TEST_16      0 // Alert (from non-existent slave)
#define ENABLE_TEST_17      1 // Group Command (slave 1st to be addressed)
#define ENABLE_TEST_18      1 // Extended Write Byte
#define ENABLE_TEST_19      1 // Extended Write Word
#define ENABLE_TEST_20      1 // Extended Read Byte
#define ENABLE_TEST_21      1 // Extended Read Word
//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief PMBUS_TEST structure
//!
typedef struct _PMBUS_TEST_Obj_{
    uint16_t    count;          //!< #bytes (block transactions > 4)
    int16_t     pass;           //!< pass metric
    int16_t     fail;           //!< fail metric
    bool        enabled;        //!< bool if this test is enabled or not
    void (*init)(void *);       //!< Function pointer to test init routine
    void (*run)(void *);        //!< Function pointer to test run routine
}PMBUS_TEST_Obj;

//! \brief Handle to the PMBUS_TEST structure
//!
typedef PMBUS_TEST_Obj *PMBUS_TEST_Handle;
//*****************************************************************************
//globals
//*****************************************************************************
extern PMBUS_TEST_Obj PMBUS_TESTS[NTESTS];
extern PMBUS_TEST_Handle hnd;

extern void (*runTestList[NTESTS])(PMBUS_TEST_Handle);
extern void (*initTestList[NTESTS])(PMBUS_TEST_Handle);

extern volatile int16_t pass, fail;

extern PMBus_Stack_Obj pmbusStackMaster;
extern PMBus_Stack_Handle hndPmbusStackMaster;
extern uint16_t pmbusMasterBuffer[256];

extern volatile bool slaveAckReceived;
extern volatile bool endOfMessage;
extern volatile bool masterDataAvailable;
extern volatile bool masterDataRequested;
extern volatile bool receivedPecValid;
extern volatile bool alertEdgeAsserted;
extern volatile bool clockLowTimeout;
extern volatile uint16_t  bytesReceived;
extern volatile uint32_t pmbusStatus;
//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Initialize Send Byte Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initSendByte(PMBUS_TEST_Handle hnd);

//! \brief Test Send Byte Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 1
//!
void PMBUS_TEST_runSendByte(PMBUS_TEST_Handle hnd);

//! \brief Initialize Write Byte Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initWriteByte(PMBUS_TEST_Handle hnd);

//! \brief Test Write Byte Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 1
//!
void PMBUS_TEST_runWriteByte(PMBUS_TEST_Handle hnd);

//! \brief Initialize Write Word Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initWriteWord(PMBUS_TEST_Handle hnd);

//! \brief Test Write Word Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 1
//!
void PMBUS_TEST_runWriteWord(PMBUS_TEST_Handle hnd);

//! \brief Initialize block write Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initBlockWrite(PMBUS_TEST_Handle hnd);

//! \brief Test block write Command 
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 1
//!
void PMBUS_TEST_runBlockWrite(PMBUS_TEST_Handle hnd);

//! \brief Initialize Receive Byte Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initReceiveByte(PMBUS_TEST_Handle hnd);

//! \brief Test Receive Byte Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 2
//!
void PMBUS_TEST_runReceiveByte(PMBUS_TEST_Handle hnd);

//! \brief Initialize Read Byte Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initReadByte(PMBUS_TEST_Handle hnd);

//! \brief Test Read Byte Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 3
//!
void PMBUS_TEST_runReadByte(PMBUS_TEST_Handle hnd);

//! \brief Initialize Read Word Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initReadWord(PMBUS_TEST_Handle hnd);

//! \brief Test Read Word Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 4
//!
void PMBUS_TEST_runReadWord(PMBUS_TEST_Handle hnd);

//! \brief Initialize Block Read Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initBlockRead(PMBUS_TEST_Handle hnd);

//! \brief Test Block Read Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 258
//!
void PMBUS_TEST_runBlockRead(PMBUS_TEST_Handle hnd);

//! \brief Initialize Block Read (3 bytes) Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initBlockRead3Bytes(PMBUS_TEST_Handle hnd);

//! \brief Test Block Read (3 bytes) Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 6
//!
void PMBUS_TEST_runBlockRead3Bytes(PMBUS_TEST_Handle hnd);

//! \brief Initialize Block Write/ Block Read/ Process Call Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initBlockWriteReadProcessCall(PMBUS_TEST_Handle hnd);

//! \brief Test Block Write/ Block Read/ Process Call
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 258
//!
void PMBUS_TEST_runBlockWriteReadProcessCall(PMBUS_TEST_Handle hnd);

//! \brief Initialize Quick Command Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initQuickCommand(PMBUS_TEST_Handle hnd);

//! \brief Test Quick Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 1
//!
void PMBUS_TEST_runQuickCommand(PMBUS_TEST_Handle hnd);

//! \brief Initialize Block Write Test with 2 bytes
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initBlockWrite2Bytes(PMBUS_TEST_Handle hnd);

//! \brief Test Block Write with 2 bytes
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 1
//!
void PMBUS_TEST_runBlockWrite2Bytes(PMBUS_TEST_Handle hnd);

//! \brief Initialize Block Write Test with 3 bytes
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initBlockWrite3Bytes(PMBUS_TEST_Handle hnd);

//! \brief Test Block Write with 3 bytes
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 1
//!
void PMBUS_TEST_runBlockWrite3Bytes(PMBUS_TEST_Handle hnd);

//! \brief Initialize Process Call Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initProcessCall(PMBUS_TEST_Handle hnd);

//! \brief Test Process Call
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 4
//!
void PMBUS_TEST_runProcessCall(PMBUS_TEST_Handle hnd);

//! \brief Initialize Alert Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initAlert(PMBUS_TEST_Handle hnd);

//! \brief Test Alert Response
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 4
//!
void PMBUS_TEST_runAlert(PMBUS_TEST_Handle hnd);

//! \brief Initialize Alert (from non-existent slave) Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initNoAlert(PMBUS_TEST_Handle hnd);

//! \brief Test Alert Response (from non-existent slave)
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 4
//!
void PMBUS_TEST_runNoAlert(PMBUS_TEST_Handle hnd);

//! \brief Initialize Group Command Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initGroupCommand(PMBUS_TEST_Handle hnd);

//! \brief Test Group Command Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 4
//!
void PMBUS_TEST_runGroupCommand(PMBUS_TEST_Handle hnd);

//! \brief Initialize Extended Write Byte Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initExtendedWriteByte(PMBUS_TEST_Handle hnd);

//! \brief Test Extended Write Byte Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 1
//!
void PMBUS_TEST_runExtendedWriteByte(PMBUS_TEST_Handle hnd);

//! \brief Initialize Extended Write Word Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initExtendedWriteWord(PMBUS_TEST_Handle hnd);

//! \brief Test Extended Write Word Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 1
//!
void PMBUS_TEST_runExtendedWriteWord(PMBUS_TEST_Handle hnd);

//! \brief Initialize Extended Read Byte Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initExtendedReadByte(PMBUS_TEST_Handle hnd);

//! \brief Test Extended Read Byte Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 3
//!
void PMBUS_TEST_runExtendedReadByte(PMBUS_TEST_Handle hnd);

//! \brief Initialize Extended Read Word Test
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//!
void PMBUS_TEST_initExtendedReadWord(PMBUS_TEST_Handle hnd);

//! \brief Test Extended Read Word Command
//! \param[in] hnd Handle to the PMBUS_TEST_Obj object
//! \note expected pass: 4
//!
void PMBUS_TEST_runExtendedReadWord(PMBUS_TEST_Handle hnd);

#ifdef __cplusplus
{
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _F28004X_PMBUS_MASTER_TEST_H_ definition
