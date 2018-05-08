//###########################################################################
//
// FILE:   debug.h
//
// TITLE:  Assert definition macro for debug.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __DEBUG_H__
#define __DEBUG_H__

//*****************************************************************************
//
// Prototype for the function that is called when an invalid argument is passed
// to an API.  This is only used when doing a DEBUG build. It is the
// application's responsibility to define the __error__ function.
//
//*****************************************************************************
extern void __error__(char *filename, uint32_t line);

//*****************************************************************************
//
// The ASSERT macro, which does the actual assertion checking.  Typically, this
// will be for procedure arguments.
//
//*****************************************************************************
#ifdef DEBUG
#define ASSERT(expr) do                                                       \
                     {                                                        \
                         if(!(expr))                                          \
                         {                                                    \
                             __error__(__FILE__, __LINE__);                   \
                         }                                                    \
                     }                                                        \
                     while(0)
#else
#define ASSERT(expr)
#endif

#endif // __DEBUG_H__
