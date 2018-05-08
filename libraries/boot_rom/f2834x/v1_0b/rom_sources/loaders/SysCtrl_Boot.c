// TI File $Revision: /main/1 $
// Checkin $Date: May 30, 2008   14:12:28 $
//###########################################################################
//
// FILE:    SysCtrl_Boot.c
//
// TITLE:   Boot Rom System Control Routines
//
// Functions:
//
//     void WatchDogDisable(void)
//     void WatchDogEnable(void)
//
// Notes:
//
//###########################################################################
// $TI Release: 2834x Boot ROM V1b $
// $Release Date: June 3, 2008 $
//###########################################################################


#include "Boot_ROM.h"

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
// This module forces a reset by the watchdog timer.
//---------------------------------------------------------------
void WatchDogReset(void)
{
    EALLOW;
    SysCtrlRegs.WDCR = 0x0028;                   
    SysCtrlRegs.WDCR = 0x0000;
    EDIS;
    for(;;);
}


//---------------------------------------------------------------
// This module sets up the PLL.
//---------------------------------------------------------------
void InitPll(Uint16 val, Uint16 divsel)
{

   EALLOW;

   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {    
      SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_8;
      SysCtrlRegs.PLLCR.bit.DIV = val;
      while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1) {}
   }

   if (SysCtrlRegs.PLLSTS.bit.DIVSEL != divsel)
   {
      SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_8;
        
      if(   divsel == DIVSEL_BY_4 
         || divsel == DIVSEL_BY_2
         || divsel == DIVSEL_BY_1)
      {
          asm(" RPT #200 || NOP");
          asm(" RPT #200 || NOP");
          asm(" RPT #200 || NOP");
          SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_4;
      }
      if(   divsel == DIVSEL_BY_2
         || divsel == DIVSEL_BY_1)
      {
          asm(" RPT #200 || NOP");
          asm(" RPT #200 || NOP");
          asm(" RPT #200 || NOP");
          SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_2;      
      }
      if(divsel == DIVSEL_BY_1)
      {
          // Note: Only use DIVSEL == /1 when the PLL is in 
          //       bypass mode
          asm(" RPT #200 || NOP");
          asm(" RPT #200 || NOP");
          asm(" RPT #200 || NOP");
          SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_1;      
      }
      
   }

   EDIS;
}



// EOF --------

