#ifndef _PMBUS_STACK_HANDLER_H_
#define _PMBUS_STACK_HANDLER_H_
//#############################################################################
//
//! \file   pmbus_stack_Handler.h
//!
//! \brief  PMBUS Communications State Machine
//! \author Vishal Coelho
//! \date    Mar 11, 2015
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
#include "pmbus_stack_assert.h"
#include "pmbus_stack_config.h"

//!
//! \defgroup PMBUS_STACK_HANDLER PMBus State Machine Handler

//!
//! \ingroup PMBUS_STACK_HANDLER
//@{

#ifdef __cplusplus

extern "C" {
#endif

//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief The PMBus State Machine handler (Slave Mode)
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//! This function implements the state machine of the PMBus in slave mode, it
//! is designed to operate in the interrupt service routine (ISR) triggered by
//! the following interrupts
//! - DATA_READY (Read buffer is full)
//! - DATA_REQEUST (Master has requested data)
//! - EOM (Master signals an end of a block message)
//! \note The handler must be called in the PMBus ISR only
extern void PMBus_Stack_slaveHandler( PMBus_Stack_Handle hnd );

//! \brief Idle State Handler (Slave Mode)
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//!
extern void PMBus_Stack_slaveIdleHandler( PMBus_Stack_Handle hnd );

//! \brief Receive Byte Wait-for-EOM State Handler (Slave Mode)
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//!
extern void
PMBus_Stack_slaveReceiveByteWaitForEomHandler( PMBus_Stack_Handle hnd );

//! \brief Read Block State Handler (Slave Mode)
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//!
extern void PMBus_Stack_slaveReadBlockHandler( PMBus_Stack_Handle hnd );

//! \brief Read/Wait-for-EOM State Handler (Slave Mode)
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//!
extern void PMBus_Stack_slaveReadWaitForEOMHandler( PMBus_Stack_Handle hnd );

//! \brief Block Write or Process Call State Handler (Slave Mode)
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//!
extern void 
PMBus_Stack_slaveBlockWriteOrProcessCallHandler( PMBus_Stack_Handle hnd );

//! \brief Extended Read/Write Byte/Word Handler (Slave Mode)
//! \param[in] hnd Handle to the PMBus_Stack_Obj object
//!
extern void 
PMBUS_STACK_extendedCommandHandler( PMBus_Stack_Handle hnd );

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of _PMBUS_STACK_HANDLER_H_ definition
