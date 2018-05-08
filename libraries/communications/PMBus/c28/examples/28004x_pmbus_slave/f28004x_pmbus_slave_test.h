#ifndef _F28004X_PMBUS_SLAVE_TEST_H_
#define _F28004X_PMBUS_SLAVE_TEST_H_
//#############################################################################
//
//! \file   f28004x_pmbus_slave_test.h
//!
//! \brief  Prototypes for the different command handlers
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
#include "pmbus_stack_config.h"
#include "pmbus_stack_handler.h"

//!
//! \defgroup PMBUS_SLAVE_TESTS PMBus Slave Mode Tests

//!
//! \ingroup PMBUS_SLAVE_TESTS
//@{

#ifdef __cplusplus

extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
//globals
//*****************************************************************************
extern PMBus_Stack_Obj pmbusStackSlave;
extern PMBus_Stack_Handle hndPmbusStackSlave;
extern uint16_t pmbusSlaveBuffer[300U];

extern volatile uint16_t testsCompleted;
extern volatile uint16_t pass, fail;
//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Send Byte Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 4
//!
void PMBus_Stack_sendByteHandler(PMBus_Stack_Handle hnd);

//! \brief Write Byte Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 5
//!
void PMBus_Stack_writeByteHandler(PMBus_Stack_Handle hnd);

//! \brief Write Word Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 6
//!
void PMBus_Stack_writeWordHandler(PMBus_Stack_Handle hnd);

//! \brief Block Write (255 bytes) Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 260
//!
void PMBus_Stack_blockWriteHandler(PMBus_Stack_Handle hnd);

//! \brief Receive Byte Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 1
//!
void PMBus_Stack_receiveByteHandler(PMBus_Stack_Handle hnd);

//! \brief Read Byte Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 1
//!
void PMBus_Stack_readByteHandler(PMBus_Stack_Handle hnd);

//! \brief Read Word Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 1
//!
void PMBus_Stack_readWordHandler(PMBus_Stack_Handle hnd);

//! \brief Block Read (255 bytes) Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 1
//!
void PMBus_Stack_blockReadHandler(PMBus_Stack_Handle hnd);

//! \brief Block Read (3 bytes) Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 1
//!
void PMBus_Stack_blockRead3BytesHandler(PMBus_Stack_Handle hnd);

//! \brief Block Write/Read/Process Call (255 bytes) Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 259
//!
void PMBus_Stack_blockWriteReadProcessCallHandler(PMBus_Stack_Handle hnd);

//! \brief Quick Command Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 4
//!
void PMBus_Stack_quickCommandHandler(PMBus_Stack_Handle hnd);

//! \brief Block Write (2 bytes) Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note an attempted block write with 1 byte is a write byte, 2 bytes
//! a write word - the master does not put the byte count on the line
//! \note make sure to run the write word test before this, as the original
//! write word handler overwrites the handler to point to this function
//! \note expected pass: 6
//!
void PMBus_Stack_blockWrite2BytesHandler(PMBus_Stack_Handle hnd);

//! \brief Block Write (3 bytes) Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note an attempted block write with 1 byte is a write byte, 2 bytes
//! a write word - the master does not put the byte count on the line
//! \note make sure to run the block write test before this, as the original
//!  block write handler overwrites the handler to point to this function
//! \note expected pass: 8
//!
void PMBus_Stack_blockWrite3BytesHandler(PMBus_Stack_Handle hnd);

//! \brief Process Call Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 5
//!
void PMBus_Stack_processCallHandler(PMBus_Stack_Handle hnd);

//! \brief Alert Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 1
//!
void PMBus_Stack_alertHandler(PMBus_Stack_Handle hnd);

//! \brief Alert (from non-existenst slave) Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 1
//!
void PMBus_Stack_noAlertHandler(PMBus_Stack_Handle hnd);

//! \brief Group Command (slave 1st addressed) Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 6
//!
void PMBus_Stack_groupCommandHandler(PMBus_Stack_Handle hnd);

//! \brief Extended Write Byte Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 6
//!
void PMBus_Stack_extWriteByteHandler(PMBus_Stack_Handle hnd);

//! \brief Extended Write Word Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 7
//!
void PMBus_Stack_extWriteWordHandler(PMBus_Stack_Handle hnd);

//! \brief Extended Read Byte Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 1
//!
void PMBus_Stack_extReadByteHandler(PMBus_Stack_Handle hnd);

//! \brief ExtendedRead Word Handler
//! \param hnd Pointer to a PMBUS_STACK object
//! \note expected pass: 1
//!
void PMBus_Stack_extReadWordHandler(PMBus_Stack_Handle hnd);

#ifdef __cplusplus
{
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _F28004X_PMBUS_SLAVE_TEST_H_ definition
