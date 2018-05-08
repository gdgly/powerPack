// TI File $Revision: /main/1 $
// Checkin $Date: May 30, 2008   14:12:30 $
//###########################################################################
//
// FILE:    TI_Test_F.c
//
// TITLE:   TI test routines
//
// Functions:
//
//     void TI_Test(void)
//
//###########################################################################
// $TI Release: 2834x Boot ROM V1b $
// $Release Date: June 3, 2008 $
//###########################################################################

#include "Boot_ROM.h"

void WatchDogDisable(void);

void TI_Test(void)
{
     Uint16 i;
     WatchDogDisable();
     if( ((*(Uint16*)0x09F0) & 0x1F00) == 0)
     {
         for(;;)
         {
            asm("      ESTOP0");
         }
     }
     else
     {
          EALLOW;
          GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 0;
          GpioCtrlRegs.GPCDIR.bit.GPIO87 = 1;
          EDIS;
          for(;;)
          {
             for(i=0;i<1000;i++)
             {
                 GpioDataRegs.GPCTOGGLE.bit.GPIO87 = 1;
             }

          }

     }
}
