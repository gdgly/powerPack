// TI File $Revision: /main/1 $
// Checkin $Date: May 30, 2008   14:12:32 $
//###########################################################################
//
// FILE:    XINTF_Boot.c
//
// TITLE:   XINTF boot routine
//
// Functions:
//
//       Uint32 XINTF_Boot(Uint16 size)
//
// Notes:
//
//###########################################################################
// $TI Release: 2834x Boot ROM V1b $
// $Release Date: June 3, 2008 $
//###########################################################################


#include "Boot_ROM.h"

// Private function definitions


// External function definitions


//#################################################
// Uint32 XINTF_Boot(Uint16 size)
//--------------------------------------------
// This module is the main Parallel boot routine.
// It will load code via GP I/O port B.
//
// This function configures XINTF zone 6 and returns
// the first address in XINTF zone 6 to the InitBoot
// routine. InitBoot then calls ExitBoot
//--------------------------------------------

Uint32 XINTF_Boot(Uint16 size)
{
   EALLOW;

   SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;

   // GPIO64-GPIO79 (XD0-XD15)
   GpioCtrlRegs.GPCMUX1.all = 0xAAAAAAAA;

   // GPIO80-GPIO87 (XA8-XA15)
   // (top half of this register is reserved)
   GpioCtrlRegs.GPCMUX2.all = 0x0000AAAA;

   // XZCS6n, XA17-XA19
   GpioCtrlRegs.GPAMUX2.all |= 0xFF000000;

   // XREADYn, XRNW, XWE0n, XA16, XA0-XA7
   GpioCtrlRegs.GPBMUX1.all |= 0xFFFFF0F0;


   if (size == 16)
   {
     XintfRegs.XTIMING6.all = XTIMING_X16_VAL;
   }
   else if (size == 32)
   {
     // GPIO48-GPIO63 (XD16-XD31)
     GpioCtrlRegs.GPBMUX2.all  = 0xFFFFFFFF; // XINTF functionality
     GpioCtrlRegs.GPBQSEL2.all = 0xFFFFFFFF; // Asynchronous inputs
     XintfRegs.XTIMING6.all = XTIMING_X32_VAL;
   }
   XintfRegs.XINTCNF2.all = XINTCNF2_VAL;

   EDIS;
   return XINTF_ENTRY_POINT;

}

// EOF --------
