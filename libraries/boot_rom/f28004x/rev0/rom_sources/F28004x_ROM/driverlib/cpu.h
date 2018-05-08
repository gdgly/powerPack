//###########################################################################
//
// FILE:   cpu.h
//
// TITLE:  Useful C28x CPU defines.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __CPU_H__
#define __CPU_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// External reference to the interrupt flag register (IFR) register
//
extern __cregister volatile unsigned int IFR;

//
// External reference to the interrupt enable register (IER) register
//
extern __cregister volatile unsigned int IER;

//
// Define to enable interrupts
//
#ifndef EINT
#define EINT   __asm(" clrc INTM")
#endif

//
// Define to disable interrupts
//
#ifndef DINT
#define DINT   __asm(" setc INTM")
#endif

//
// Define to enable debug events
//
#ifndef ERTM
#define ERTM   __asm(" clrc DBGM")
#endif

//
// Define to disable debug events
//
#ifndef DRTM
#define DRTM   __asm(" setc DBGM")
#endif

//
// Define to allow writes to protected registers
//
#ifndef EALLOW
#define EALLOW __asm(" EALLOW")
#endif

//
// Define to disable writes to protected registers
//
#ifndef EDIS
#define EDIS   __asm(" EDIS")
#endif

//
// Define for emulation stop
//
#ifndef ESTOP0
#define ESTOP0 __asm(" ESTOP0")
#endif

//
// Define for emulation stop
//
#ifndef ESTOP1
#define ESTOP1 __asm(" ESTOP1")
#endif

//
// Define for no operation
//
#ifndef NOP
#define NOP __asm(" NOP")
#endif

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __CPU_H__
