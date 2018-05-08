//###########################################################################
//
// FILE:    cpubrom_dcsm.c
//
// TITLE:   main boot loader file for C-Core
//
// Functions:
//
//
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July 2015 $
//###########################################################################
#include "bootrom.h"

const uint32_t dcsm_default_keys_z1[] = {
		0x47ffffff,			//Z1-ZSB0-CSMPSWD1
		0xdb7fffff,			//Z1-ZSB1-CSMPSWD1
		0x4bffffff,			//Z1-ZSB2-CSMPSWD1
		0x3f7fffff,			//Z1-ZSB3-CSMPSWD1
		0xcfbfffff,			//Z1-ZSB4-CSMPSWD1
		0x8bffffff,			//Z1-ZSB5-CSMPSWD1
		0x53ffffff,			//Z1-ZSB6-CSMPSWD1
		0xcf7fffff,			//Z1-ZSB7-CSMPSWD1
		0xe77fffff,			//Z1-ZSB8-CSMPSWD1
		0x93ffffff,			//Z1-ZSB9-CSMPSWD1
		0xeb7fffff,			//Z1-ZSB10-CSMPSWD1
		0x69ffffff,			//Z1-ZSB11-CSMPSWD1
		0xa9ffffff,			//Z1-ZSB12-CSMPSWD1
		0xdd7fffff,			//Z1-ZSB13-CSMPSWD1
		0x8bffffff,			//Z1-ZSB14-CSMPSWD1
		0xcfbfffff,			//Z1-ZSB15-CSMPSWD1
		0x3f7fffff,			//Z1-ZSB16-CSMPSWD1
		0x4bffffff,			//Z1-ZSB17-CSMPSWD1
		0xdb7fffff,			//Z1-ZSB18-CSMPSWD1
		0x47ffffff,			//Z1-ZSB19-CSMPSWD1
		0x87ffffff,			//Z1-ZSB20-CSMPSWD1
		0xf37fffff,			//Z1-ZSB21-CSMPSWD1
		0xdd7fffff,			//Z1-ZSB22-CSMPSWD1
		0xa9ffffff,			//Z1-ZSB23-CSMPSWD1
		0x69ffffff,			//Z1-ZSB24-CSMPSWD1
		0xeb7fffff,			//Z1-ZSB25-CSMPSWD1
		0x93ffffff,			//Z1-ZSB26-CSMPSWD1
		0xe77fffff,			//Z1-ZSB27-CSMPSWD1
		0xcf7fffff,			//Z1-ZSB28-CSMPSWD1
		0x53ffffff			//Z1-ZSB29-CSMPSWD1
};

const uint32_t dcsm_default_keys_z2[] = {
		0xe3ffffff, 		//Z2-ZSB0-CSMPSWD1
		0x977fffff, 		//Z2-ZSB1-CSMPSWD1
		0xf1ffffff, 		//Z2-ZSB2-CSMPSWD1
		0x9b7fffff, 		//Z2-ZSB3-CSMPSWD1
		0x5b7fffff, 		//Z2-ZSB4-CSMPSWD1
		0x2fffffff, 		//Z2-ZSB5-CSMPSWD1
		0x1fffffff, 		//Z2-ZSB6-CSMPSWD1
		0x6b7fffff, 		//Z2-ZSB7-CSMPSWD1
		0xab7fffff, 		//Z2-ZSB8-CSMPSWD1
		0x37ffffff, 		//Z2-ZSB9-CSMPSWD1
		0x4f7fffff, 		//Z2-ZSB10-CSMPSWD1
		0x3bffffff, 		//Z2-ZSB11-CSMPSWD1
		0xe5ffffff, 		//Z2-ZSB12-CSMPSWD1
		0x8f7fffff, 		//Z2-ZSB13-CSMPSWD1
		0x2fffffff, 		//Z2-ZSB14-CSMPSWD1
		0x5b7fffff, 		//Z2-ZSB15-CSMPSWD1
		0x9b7fffff, 		//Z2-ZSB16-CSMPSWD1
		0xf1ffffff, 		//Z2-ZSB17-CSMPSWD1
		0x977fffff, 		//Z2-ZSB18-CSMPSWD1
		0xe3ffffff, 		//Z2-ZSB19-CSMPSWD1
		0xcbffffff, 		//Z2-ZSB20-CSMPSWD1
		0x577fffff, 		//Z2-ZSB21-CSMPSWD1
		0x8f7fffff, 		//Z2-ZSB22-CSMPSWD1
		0xe5ffffff, 		//Z2-ZSB23-CSMPSWD1
		0x3bffffff, 		//Z2-ZSB24-CSMPSWD1
		0x4f7fffff, 		//Z2-ZSB25-CSMPSWD1
		0x37ffffff, 		//Z2-ZSB26-CSMPSWD1
		0xab7fffff, 		//Z2-ZSB27-CSMPSWD1
		0x6b7fffff, 		//Z2-ZSB28-CSMPSWD1
		0x1fffffff	 		//Z2-ZSB29-CSMPSWD1
};



//#################################################
// void InitDCSM(void)
//--------------------------------------------
// This function initializes code security module, until this function is executed
// all access to RAM and JTAG is blocked.
//--------------------------------------------
uint32_t Gather_Bx_Zx_ZSB(uint16_t bank, uint16_t zone, uint32_t *csmkey)
{
    uint32_t linkPointer;
    uint32_t ZSBBase, OtpBase; // base address of the ZSB
    int32_t bitPos = 28;
    uint32_t zeroFound = 0;
    const uint32_t *dcsm_keys = &dcsm_default_keys_z1[0];

    if(bank == FLASH_BANK0)
    {
    	linkPointer = DCSMBANK0_Z1_BASE;
    	OtpBase  = DCSMBANK0_Z1OTP_BASE;
    }
    else if (bank == FLASH_BANK1)
    {
    	linkPointer = DCSMBANK1_Z1_BASE;
    	OtpBase  = DCSMBANK1_Z1OTP_BASE;
    }

    if(zone == 2)
    {
    	linkPointer += 0x40;
    	OtpBase += 0x200;
    	dcsm_keys = &dcsm_default_keys_z2[0];
    }

	linkPointer = HWREG(linkPointer);
	linkPointer = linkPointer << 3; // Bits 29, 30 and 31 as most-sigificant 0 are
                        			//invalid LinkPointer options

	while((zeroFound == 0) && (bitPos > -1))
	{
		if( (linkPointer & 0x80000000U) == 0U)
		{
			zeroFound = 1;
			ZSBBase = (OtpBase + (((uint32_t)bitPos + 3U) * 0x10));
		}
		else
		{
			bitPos--;
			linkPointer = linkPointer << 1;
		}
	}
	if(zeroFound == 0)
	{
		ZSBBase = (OtpBase + 0X20);
	}
	if(csmkey != (uint32_t *)0) //check NULL Pointer, for BANK2 this will be NULL
	{
		*csmkey = dcsm_keys[bitPos+1];
	}

	return ZSBBase;
}


void InitDCSM()
{

	uint32_t ZsbBase01 = 0, ZsbBase02 = 0, ZsbBase11 = 0, ZsbBase12 = 0;
	uint32_t csmKey01 = 0, csmKey02 = 0;
	EALLOW;

	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_B0_Z1OTP_LINKPOINTER1);	//Bank 0 Zone 1 Contents
	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_B0_Z1OTP_LINKPOINTER2);
	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_B0_Z1OTP_LINKPOINTER3);

	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_B0_Z2OTP_LINKPOINTER1);	//Bank 0 Zone 2 Contents
	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_B0_Z2OTP_LINKPOINTER2);
	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_B0_Z2OTP_LINKPOINTER3);

	HWREG(DCSMBANK1_Z1OTP_BASE + DCSM_O_B1_Z1OTP_LINKPOINTER1);	//Bank 1 Zone 1 Contents
	HWREG(DCSMBANK1_Z1OTP_BASE + DCSM_O_B1_Z1OTP_LINKPOINTER2);
	HWREG(DCSMBANK1_Z1OTP_BASE + DCSM_O_B1_Z1OTP_LINKPOINTER3);

	HWREG(DCSMBANK1_Z2OTP_BASE + DCSM_O_B1_Z2OTP_LINKPOINTER1);	//Bank 1 Zone 2 Contents
	HWREG(DCSMBANK1_Z2OTP_BASE + DCSM_O_B1_Z2OTP_LINKPOINTER2);
	HWREG(DCSMBANK1_Z2OTP_BASE + DCSM_O_B1_Z2OTP_LINKPOINTER3);

	HWREG(TI_OTP_SECDC);	// TI OTP SECDC register read

	// OTPSECLOCK and other boot related register reads from Zone 1 and Zone 2 of USER OTP1
	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_Z1OTP_PSWDLOCK);
	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_Z1OTP_JTAGLOCK);
	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_Z1OTP_CRCLOCK);
	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_B0_Z1OTP_GPREG1);
	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_B0_Z1OTP_GPREG2);
	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_B0_Z1OTP_GPREG3);
	HWREG(DCSMBANK0_Z1OTP_BASE + DCSM_O_B0_Z1OTP_BOOTCTRL);

	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_Z2OTP_PSWDLOCK);
	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_Z2OTP_JTAGLOCK);
	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_Z2OTP_CRCLOCK);
	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_B0_Z2OTP_GPREG1);
	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_B0_Z2OTP_GPREG2);
	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_B0_Z2OTP_GPREG3);
	HWREG(DCSMBANK0_Z2OTP_BASE + DCSM_O_B0_Z2OTP_BOOTCTRL);

	ZsbBase01 = Gather_Bx_Zx_ZSB(FLASH_BANK0, 1, &csmKey01);	//Gather ZSB of ZONE1 from BANK1
	ZsbBase02 = Gather_Bx_Zx_ZSB(FLASH_BANK0, 2, &csmKey02);	//Gather ZSB of ZONE2 from BANK1
	ZsbBase11 = Gather_Bx_Zx_ZSB(FLASH_BANK1, 1, 0);	//Gather ZSB of ZONE1 from BANK2
	ZsbBase12 = Gather_Bx_Zx_ZSB(FLASH_BANK1, 2, 0);	//Gather ZSB of ZONE2 from BANK2

	//Bank 0 Zone 1
	HWREG(ZsbBase01 + BROM_DCSM_O_Zx_EXEONLYRAM);	// Zone Select Block contents
	HWREG(ZsbBase01 + BROM_DCSM_O_Zx_EXEONLYSECT);
	HWREG(ZsbBase01 + BROM_DCSM_O_Zx_GRABRAM);
	HWREG(ZsbBase01 + BROM_DCSM_O_Zx_GRABSECT);

	//Bank 0 Zone 2
	HWREG(ZsbBase02 + BROM_DCSM_O_Zx_EXEONLYRAM);	// Zone Select Block contents
	HWREG(ZsbBase02 + BROM_DCSM_O_Zx_EXEONLYSECT);
	HWREG(ZsbBase02 + BROM_DCSM_O_Zx_GRABRAM);
	HWREG(ZsbBase02 + BROM_DCSM_O_Zx_GRABSECT);

	//Bank 1 Zone 1
	HWREG(ZsbBase11 + BROM_DCSM_O_Zx_EXEONLYSECT);	// Zone Select Block contents
	HWREG(ZsbBase11 + BROM_DCSM_O_Zx_GRABSECT);

	//Bank 1 Zone 2
	HWREG(ZsbBase12 + BROM_DCSM_O_Zx_EXEONLYSECT);	// Zone Select Block contents
	HWREG(ZsbBase12 + BROM_DCSM_O_Zx_GRABSECT);

    HWREG(ZsbBase01 + DCSM_O_Z1_CSMPSWD0);	// CSMPSWD reads for zone 1
	HWREG(ZsbBase01 + DCSM_O_Z1_CSMPSWD1);
	HWREG(ZsbBase01 + DCSM_O_Z1_CSMPSWD2);
	HWREG(ZsbBase01 + DCSM_O_Z1_CSMPSWD3);

	HWREG(ZsbBase02 + DCSM_O_Z2_CSMPSWD0);  // CSMPSWD reads for zone 2
	HWREG(ZsbBase02 + DCSM_O_Z2_CSMPSWD1);
	HWREG(ZsbBase02 + DCSM_O_Z2_CSMPSWD2);
	HWREG(ZsbBase02 + DCSM_O_Z2_CSMPSWD3);

	HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY0) = 0xFFFFFFFF;//Zone 1 CSMKEY Loads
	HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY1) = (uint32_t) csmKey01;
	HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY2) = 0xFFFFFFFF;
	HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY3) = 0xFFFFFFFF;

	HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY0) = 0xFFFFFFFF;//Zone 2 CSMKEY Loads
	HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY1) = (uint32_t) csmKey02;
	HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY2) = 0xFFFFFFFF;
	HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY3) = 0xFFFFFFFF;



}


//===========================================================================
// End of file.
//===========================================================================
