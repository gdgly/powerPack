// TI File $Revision: /main/7 $
// Checkin $Date: June 6, 2007   17:04:59 $
//###########################################################################
//
// FILE:    SelectMode_Boot.c
//
// TITLE:   2833x Boot Mode selection routines
//
// Functions:
//
//      Uint32 SelectBootMode(void)
//      inline void SelectMode_GPOISelect(void)
//
// Notes:
//
//###########################################################################
// $TI Release: 2833x Boot ROM Version 1 $
// $Release Date: June 25, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"
#include "TMS320x2833x_Boot.h"

//  External functions referenced by this file
extern Uint32 SCI_Boot(void);
extern Uint32 SPI_Boot(void);
extern Uint32 Parallel_Boot(void);
extern Uint32 XINTF_Parallel_Boot(void);
extern Uint32 I2C_Boot(void);
extern Uint32 CAN_Boot();
extern Uint32 MCBSP_Boot();
extern Uint32 XINTF_Boot(Uint16 size);
extern void WatchDogEnable(void);
extern void WatchDogDisable(void);
extern void WatchDogService(void);
extern void ADC_cal(void);

// Functions in this file
Uint32 SelectBootMode(void);

//         GPIO87   GPIO86    GPIO85   GPIO84
//          XA15     XA14      XA13     XA12
//           PU       PU        PU       PU
//        ==========================================
//Mode F     1        1          1        1    Jump to Flash
//Mode E     1        1          1        0    SCI-A boot
//Mode D     1        1          0        1    SPI-A boot
//Mode C     1        1          0        0    I2C-A boot
//Mode B     1        0          1        1    eCAN-A boot
//Mode A     1        0          1        0    McBSP-A boot
//Mode 9     1        0          0        1    Jump to XINTF x16
//Mode 8     1        0          0        0    Jump to XINTF x32
//Mode 7     0        1          1        1    Jump to OTP
//Mode 6     0        1          1        0    Parallel GPIO I/O boot
//Mode 5     0        1          0        1    Parallel XINTF boot
//Mode 4     0        1          0        0    Jump to SARAM
//Mode 3     0        0          1        1    Branch to check boot mode
//Mode 2     0        0          1        0    Boot to flash, bypass ADC cal
//Mode 1     0        0          0        1    Boot to SARAM, bypass ADC cal
//Mode 0     0        0          0        0    Boot to SCI-A, bypass ADC cal


#define FLASH_BOOT          0xF
#define SCI_BOOT            0xE
#define SPI_BOOT            0xD
#define I2C_BOOT            0xC
#define CAN_BOOT            0xB
#define MCBSP_BOOT          0xA
#define XINTF_16_BOOT       0x9
#define XINTF_32_BOOT       0x8
#define OTP_BOOT            0x7
#define PARALLEL_BOOT       0x6
#define XINTF_PARALLEL_BOOT 0x5
#define RAM_BOOT            0x4
#define LOOP_BOOT           0x3
#define FLASH_BOOT_NOCAL    0x2
#define RAM_BOOT_NOCAL      0x1
#define SCI_BOOT_NOCAL      0x0

Uint32 SelectBootMode()
{

  Uint32 EntryAddr;
  Uint16 BootMode;

#ifdef _DEBUGSELECT
// To debug without having to select
// the boot mode via jumpers, define
// _DEBUGSELECT and comment out the
// appropriate boot mode to test

   EALLOW;
   SysCtrlRegs.WDCR = 0x0068;   // Disable watchdog module
   EDIS;

// EntryAddr = SCI_Boot();
// EntryAddr = SPI_Boot();
// EntryAddr = Parallel_Boot();
// EntryAddr = XINTF_Parallel_Boot();
   EntryAddr = XINTF_Boot(16);
// EntryAddr = XINTF_Boot(32);
// EntryAddr = MCBSP_Boot();
// EntryAddr = I2C_Boot();
// EntryAddr = CAN_Boot();

   EALLOW;
   SysCtrlRegs.WDCR = 0x0028; // Enable watchdog module
   SysCtrlRegs.WDKEY = 0x55;  // Clear the WD counter
   SysCtrlRegs.WDKEY = 0xAA;
   EDIS;
#endif


#ifndef _DEBUGSELECT
  EALLOW;

  // At reset we are in /4 mode.  Change to /2
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

  do
  {
  // Read the BootMode from the pins. If the mode is 
  // "LOOP_BOOT" then keep checking with the watchdog enabled.
  // "LOOP_BOOT" will typically only used for debug
      BootMode  = GpioDataRegs.GPCDAT.bit.GPIO87 << 3;
      BootMode |= GpioDataRegs.GPCDAT.bit.GPIO86 << 2;
      BootMode |= GpioDataRegs.GPCDAT.bit.GPIO85 << 1;
      BootMode |= GpioDataRegs.GPCDAT.bit.GPIO84;
  } while (BootMode == LOOP_BOOT);

  WatchDogService();
  // Read the password locations - this will unlock the
  // CSM only if the passwords are erased.  Otherwise it
  // will not have an effect.
  CsmPwl.PSWD0;
  CsmPwl.PSWD1;
  CsmPwl.PSWD2;
  CsmPwl.PSWD3;
  CsmPwl.PSWD4;
  CsmPwl.PSWD5;
  CsmPwl.PSWD6;
  CsmPwl.PSWD7;

  WatchDogService();  
  
  // First check for modes which bypass ADC calibration
  if(BootMode == FLASH_BOOT_NOCAL) return FLASH_ENTRY_POINT;
  if(BootMode == RAM_BOOT_NOCAL)   return RAM_ENTRY_POINT;
  if(BootMode == SCI_BOOT_NOCAL)
  {
      WatchDogDisable();
      EntryAddr = SCI_Boot();
      goto DONE;
  }

  WatchDogService();

  // Call ADC Cal.  
  // This function is programmed into the OTP by the factory
  EALLOW;
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; 
  ADC_cal();
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0; 
  EDIS;

  // Check for modes which do not require a boot loader (Flash/RAM/OTP)
  if(BootMode == FLASH_BOOT) return FLASH_ENTRY_POINT;
  else if(BootMode == RAM_BOOT) return RAM_ENTRY_POINT;
  else if(BootMode == OTP_BOOT) return OTP_ENTRY_POINT;
  else if(BootMode == XINTF_16_BOOT) return EntryAddr = XINTF_Boot(16);
  else if(BootMode == XINTF_32_BOOT) return EntryAddr = XINTF_Boot(32);

  // Disable the watchdog and check for the other boot modes

  WatchDogDisable();

  if(BootMode == SCI_BOOT) EntryAddr = SCI_Boot();
  else if(BootMode == SPI_BOOT) EntryAddr = SPI_Boot();
  else if(BootMode == I2C_BOOT) EntryAddr = I2C_Boot();
  else if(BootMode == CAN_BOOT) EntryAddr = CAN_Boot();
  else if(BootMode == MCBSP_BOOT) EntryAddr = MCBSP_Boot();
  else if(BootMode == PARALLEL_BOOT) EntryAddr = Parallel_Boot();
  else if(BootMode == XINTF_PARALLEL_BOOT) EntryAddr = XINTF_Parallel_Boot();
  else return FLASH_ENTRY_POINT;

DONE:
  WatchDogEnable();

#endif // end of not _DEBUGSELECT

   return EntryAddr;

}

