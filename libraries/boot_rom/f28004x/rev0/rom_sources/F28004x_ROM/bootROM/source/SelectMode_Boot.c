//###########################################################################
//
// FILE:    SelectMode_Boot.c
//
// TITLE:   Boot Mode selection routines
//
// Functions:
//
//      uint32_t SelectBootMode(void)
//
// Notes:
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July 2015 $
//###########################################################################

#include "bootrom.h"

uint16_t SelectBootMode(void);
uint16_t cbrom_standalone_boot(void);
uint16_t cbrom_emu_boot(void);

uint16_t cbrom_standalone_boot(void)
{
	uint16_t BootModeLocal = 0;
	 if(Z1_OTP_BOOTPIN_CONFIG_KEY != 0x5A)
    {
       //bad key //decode default
     //  BootModeLocal = cbrom_decode_bootpins((uint32_t)0x00FFFFFF); // this should be pin 72 and 84
		 BootModeLocal |= (uint16_t)cbrom_GPIO_ReadPin(24) << 1 ;
		 BootModeLocal |= (uint16_t)cbrom_GPIO_ReadPin(32);

		 return (BootModeLocal & 0x3);
    }
    else
    {
       BootModeLocal = cbrom_decode_bootpins((uint32_t)(HWREG(Z1_OTP_BOOTPIN_CONFIG)));
       if(BootModeLocal < 4) 	//boot mode 0,1,2,3
       {
       	BootModeLocal = Z1_OTP_BOOTDEF_L(BootModeLocal);
       }
       else if ((3 < BootModeLocal) && (BootModeLocal < 8)) //bootmodes 4,5,6,7
       {
       	BootModeLocal = Z1_OTP_BOOTDEF_H(BootModeLocal);
       }
       else
       {
       	//error
           asm("   ESTOP0");
       	BootModeLocal = FLASH_BOOT; //should we do flash boot?
       }
    }
	return BootModeLocal;
}

uint16_t cbrom_emu_boot(void)
{
	uint16_t BootModeLocal;
    //BOOTPIN_CONFIG.bits7:0 = BMSP0 - Boot mode select Pin0
    //BOOTPIN_CONFIG.bits15:0 = BMSP1 - Boot mode select Pin1
    //BOOTPIN_CONFIG.bits23:16 = BMSP2 - Boot mode select Pin2
    //BOOTPIN_CONFIG.bits31:24 = KEY valid if equal to 0x5A
	if(EMU_BOOTPIN_CONFIG_KEY == 0xA5)
	{
		//emulate TRUE BOOT sequence - read OTPs.
		BootModeLocal = cbrom_standalone_boot();
	}
    else if(EMU_BOOTPIN_CONFIG_KEY != 0x5A)
    {
      //bad key //decode default ??
      //BootModeLocal = cbrom_decode_bootpins((uint32_t)0x00FFFFFF);
    	BootModeLocal = WAIT_BOOT;
    }
    else
    {
      BootModeLocal = cbrom_decode_bootpins((uint32_t)(HWREG(EMU_BOOTPIN_CONFIG)));
      if(BootModeLocal < 4) 	//boot mode 0,1,2,3
      {
      	BootModeLocal = EMUBOOTDEF_L(BootModeLocal);
      }
      else if ((3 < BootModeLocal) && (BootModeLocal < 8)) //bootmodes 4,5,6,7
      {
      	BootModeLocal = EMUBOOTDEF_H(BootModeLocal);
      }
      else
      {
      	//error
          asm("   ESTOP0");
      	BootModeLocal = WAIT_BOOT;
      }
    }
	return BootModeLocal;
}

uint16_t SelectBootMode(void)
{
	  uint16_t BootModeLocal;

	//  EALLOW;
	//
	//  // Watchdog Service
	//  SysCtrlRegs.WDKEY = 0x0055;
	//  SysCtrlRegs.WDKEY = 0x00AA;

	  EALLOW;

	//  if(CpuSysRegs.RESC.bit.TRSTn_pin_status == 1)
	  if((uint32_t)HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & (uint32_t)SYSCTL_RESC_DCON)
	  {
		  BootModeLocal = cbrom_emu_boot();
	  }
	  else
	  {
		  BootModeLocal = cbrom_standalone_boot();
	  }
	  EDIS;
	  return BootModeLocal;
}

