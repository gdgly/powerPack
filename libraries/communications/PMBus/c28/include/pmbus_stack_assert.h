#ifndef _PMBUS_STACK_ASSERT_H_
#define _PMBUS_STACK_ASSERT_H_
//#############################################################################
//
//! \file   PMBus_Stack_assert.h
//!
//! \brief  Defines the PMBUS_STACK_ASSERT function macro
//! \author Vishal Coelho
//! \date    Mar 12, 2015
//
// Work in this file is based on the article:
// http://www.embedded.com/electronics-blogs/other/4023329/Assert-Yourself
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
//!
//! \defgroup PMBUS_STACK_ASSERT Code Development with Assertion

//!
//! \ingroup PMBUS_STACK_ASSERT
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
//! \brief Assign a "unique" number to each file, compiler error
//! on duplicates
//!
#define PMBUS_STACK_FILENUM(number)   \
    enum{FILE_NUM = number};    \
    void _nullFunction##number(void){}

//! \brief The assert() for the PMBus communications stack
//!
#define PMBUS_STACK_ASSERT(expr) \
    if (expr)              \
    {}                     \
    else                   \
    PMBus_Stack_assertionFailed(FILE_NUM, __LINE__)

//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Error Handler Function Pointer
//! In the \e Release Mode, the user must define an error handler, and assign
//! it to this function pointer which gets called when PMBUS_STACK_ASSERT 
//! fails in the state machine.
//! \note If the library was built in debug mode, i.e. the macro \b _DEBUG 
//! defined then it is unnecessary for the user to define this function in 
//! their project. It is only required when using the release version of the 
//! library; failure to define this will result in a linker error 
//! \return none
//!
extern void (*PMBus_Stack_errorHandler)( void );

//! \brief Handles failed assertions
//! \param[in] file File number where the assertion failed
//! \param[in] line Line number where the assertion failed
//!
static inline void PMBus_Stack_assertionFailed(int16_t file, int16_t line)
{
#if defined(_DEBUG)
    __asm("    ESTOP0");
#else
    PMBus_Stack_errorHandler();
#endif //defined(_DEBUG)
}

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _PMBUS_STACK_ASSERT_H_ definition
