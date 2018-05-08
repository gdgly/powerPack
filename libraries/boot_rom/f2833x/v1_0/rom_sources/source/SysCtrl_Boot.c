// TI File $Revision: /main/5 $
// Checkin $Date: May 30, 2007   13:36:47 $
//###########################################################################
//
// FILE:    SysCtrl_Boot.c
//
// TITLE:   F2810/12 Boot Rom System Control Routines
//
// Functions:
//
//     void WatchDogDisable(void)
//     void WatchDogEnable(void)
//
// Notes:
//
//###########################################################################
// $TI Release: 2833x Boot ROM Version 1 $
// $Release Date: June 25, 2007 $
//###########################################################################


#include "DSP2833x_Device.h"
#include "TMS320x2833x_Boot.h"

//---------------------------------------------------------------
// This module disables the watchdog timer.
//---------------------------------------------------------------

void  WatchDogDisable()
{
   EALLOW;
   SysCtrlRegs.WDCR = 0x0068;               // Disable watchdog module
   EDIS;
}

//---------------------------------------------------------------
// This module enables the watchdog timer.
//---------------------------------------------------------------

void  WatchDogEnable()
{
   EALLOW;
   SysCtrlRegs.WDCR = 0x0028;               // Enable watchdog module
   SysCtrlRegs.WDKEY = 0x55;                // Clear the WD counter
   SysCtrlRegs.WDKEY = 0xAA;
   EDIS;
}

//---------------------------------------------------------------
// This module services the watchdog timer.
//---------------------------------------------------------------
void WatchDogService(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}


//---------------------------------------------------------------
// This module sets up the PLL.
//---------------------------------------------------------------
void InitPll(Uint16 val, Uint16 divsel)
{
   // Make sure the PLL is not running in limp mode
   // If it is, there is nothing we can do here.
   // The user must check for this condition in the main application
   if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0) return;

   EALLOW;

   // Change the PLLCR
   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {
      // CLKINDIV MUST be 0 before PLLCR can be changed
      SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_4;

      // Before setting PLLCR turn off missing clock detect logic
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;

      SysCtrlRegs.PLLCR.bit.DIV = val;
      while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1) {}

      // Turn missing clock detect back on
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
   }

   if (SysCtrlRegs.PLLSTS.bit.DIVSEL != divsel)
   {
      if((divsel == DIVSEL_BY_4) || (divsel == DIVSEL_BY_2))
      {
         SysCtrlRegs.PLLSTS.bit.DIVSEL = divsel;
      }
      else
      {
         if(SysCtrlRegs.PLLSTS.bit.DIVSEL == DIVSEL_BY_4)
         {
            // If switching to 1/1 from 1/4
            // * First go to 1/2 and let the power settle some
            // * Then switch to 1/1
            SysCtrlRegs.PLLSTS.bit.DIVSEL != DIVSEL_BY_2;
            asm(" RPT #200 || NOP");
            asm(" RPT #200 || NOP");
         }
         SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_1;
      }
   }

   EDIS;
}



// EOF --------

