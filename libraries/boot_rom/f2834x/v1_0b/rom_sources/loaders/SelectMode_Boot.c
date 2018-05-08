// TI File $Revision: /main/1 $
// Checkin $Date: May 30, 2008   14:12:22 $
//###########################################################################
//
// FILE:    SelectMode_Boot.c
//
// TITLE:   Boot Mode selection routines
//
// Functions:
//
//      Uint32 SelectBootMode(void)
//      inline void SelectMode_GPOISelect(void)
//
// Notes:
//
//###########################################################################
// $TI Release: 2834x Boot ROM V1b $
// $Release Date: June 3, 2008 $
//###########################################################################

#include "Boot_ROM.h"


// Functions in this file
Uint32 SelectBootMode(void);

//         GPIO87   GPIO86    GPIO85   GPIO84
//          XA15     XA14      XA13     XA12
//           PU       PU        PU       PU
//        ==========================================
//Mode F     1        1          1        1    Reserved for TI test
//Mode E     1        1          1        0    SCI-A boot
//Mode D     1        1          0        1    SPI-A boot
//Mode C     1        1          0        0    I2C-A Timing 1 boot
//Mode B     1        0          1        1    eCAN-A Timing 1 boot
//Mode A     1        0          1        0    McBSP-A boot
//Mode 9     1        0          0        1    Jump to XINTF x16
//Mode 8     1        0          0        0    Reserved
//Mode 7     0        1          1        1    eCAN-A Timing 2 boot
//Mode 6     0        1          1        0    Parallel GPIO I/O boot
//Mode 5     0        1          0        1    Parallel XINTF boot
//Mode 4     0        1          0        0    Jump to SARAM
//Mode 3     0        0          1        1    Branch to check boot mode
//Mode 2     0        0          1        0    I2C-A Timing 2 boot
//Mode 1     0        0          0        1    Reserved: enables watchdog and loops
//Mode 0     0        0          0        0    Reserved for TI test


#define TI_TEST_R           0xF
#define SCI_BOOT            0xE
#define SPI_BOOT            0xD
#define I2C_TIMING1_BOOT    0xC
#define CAN_TIMING1_BOOT    0xB
#define MCBSP_BOOT          0xA
#define XINTF_16_BOOT       0x9
#define XINTF_32_BOOT       0x8   // XD is not properly configured - DO NOT USE
#define CAN_TIMING2_BOOT    0x7
#define PARALLEL_BOOT       0x6
#define XINTF_PARALLEL_BOOT 0x5
#define RAM_BOOT            0x4
#define LOOP_BOOT           0x3
#define I2C_TIMING2_BOOT    0x2
#define ENABLE_WD_LOOP      0x1
#define TI_TEST_F           0x0

Uint32 SelectBootMode()
{

  Uint32 EntryAddr;
  EALLOW;

  // At reset we are in /8 mode.  Change to /2
  SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_4;
  asm(" RPT #200 || NOP");
  asm(" RPT #200 || NOP");
  asm(" RPT #200 || NOP");
  SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_2;

  // Set MUX for BOOT Select
  GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 0;
  GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 0;
  GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 0;
  GpioCtrlRegs.GPCMUX2.bit.GPIO84 = 0;

  // Set DIR for BOOT Select
  GpioCtrlRegs.GPCDIR.bit.GPIO87 = 0;
  GpioCtrlRegs.GPCDIR.bit.GPIO86 = 0;
  GpioCtrlRegs.GPCDIR.bit.GPIO85 = 0;
  GpioCtrlRegs.GPCDIR.bit.GPIO84 = 0;
  EDIS;

  WatchDogService();

  if(TI_TEST_EN == 0)
  {
      do
      {
      // Read the BootMode from the pins. If the mode is
      // "LOOP_BOOT" then keep checking with the watchdog enabled.
      // "LOOP_BOOT" will typically only used for debug
          BootMode  = GpioDataRegs.GPCDAT.bit.GPIO87 << 3;
          BootMode |= GpioDataRegs.GPCDAT.bit.GPIO86 << 2;
          BootMode |= GpioDataRegs.GPCDAT.bit.GPIO85 << 1;
          BootMode |= GpioDataRegs.GPCDAT.bit.GPIO84;
          if (BootMode == LOOP_BOOT)
          {
             asm("    ESTOP0");
          }
      } while (BootMode == LOOP_BOOT);
  }

  WatchDogService();

  // For compatiblity with devices containing code security,
  // read these locations to enable access all memories.

  CsmPwl.PSWD0;
  CsmPwl.PSWD1;
  CsmPwl.PSWD2;
  CsmPwl.PSWD3;
  CsmPwl.PSWD4;
  CsmPwl.PSWD5;
  CsmPwl.PSWD6;
  CsmPwl.PSWD7;

  WatchDogService();

  // Check for modes which do not require a boot loader
  if(BootMode == RAM_BOOT) return RAM_ENTRY_POINT;
  else if(BootMode == XINTF_16_BOOT) return EntryAddr = XINTF_Boot(16);
  else if(BootMode == XINTF_32_BOOT) return EntryAddr = XINTF_Boot(32);
  else if(BootMode == TI_TEST_R) return TI_TEST_R_ENTRY_POINT;

  // Disable the watchdog and check for the other boot modes
  WatchDogDisable();
  if(BootMode == SCI_BOOT) EntryAddr = SCI_Boot();
  else if(BootMode == SPI_BOOT) EntryAddr = SPI_Boot();
  else if(BootMode == I2C_TIMING1_BOOT) EntryAddr = I2C_Boot(TIMING1);
  else if(BootMode == I2C_TIMING2_BOOT) EntryAddr = I2C_Boot(TIMING2);
  else if(BootMode == CAN_TIMING1_BOOT)
  {
      EALLOW;
      InitPll(0x0000, DIVSEL_BY_1);
      EDIS;
      EntryAddr = CAN_Boot(TIMING1);
  }
  else if(BootMode == CAN_TIMING2_BOOT) EntryAddr = CAN_Boot(TIMING2);
  else if(BootMode == MCBSP_BOOT) EntryAddr = MCBSP_Boot();
  else if(BootMode == PARALLEL_BOOT) EntryAddr = Parallel_Boot();
  else if(BootMode == XINTF_PARALLEL_BOOT) EntryAddr = XINTF_Parallel_Boot();
  else if(BootMode == TI_TEST_F) TI_Test();
  // Mode is reserved.  Force the watchdog to reset the device.
  else
  {
     WatchDogReset();
  }

  WatchDogEnable();
  return EntryAddr;

}

