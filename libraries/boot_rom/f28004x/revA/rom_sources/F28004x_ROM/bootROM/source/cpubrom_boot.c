//###########################################################################
//
// FILE:    ccore_boot.c
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

uint32_t	cbrom_status;
uint32_t	cbrom_pbist_status;
extern uint32_t	iTrap_addr;
uint32_t 	brom_flash_single_bit_error_low_address;
uint32_t 	brom_flash_single_bit_error_high_address;

void WaitBoot(void);

static inline void cbrom_change_clock_dividers()
{
        EALLOW;

		//set the divider to /1
//		ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0;
        HWREG(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) = 0;

//		ClkCfgRegs.SYSPLLMULT.bit.IMULT = 34;
        // Setting integer multiplier
        HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLMULT) =  19 ;

//		ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0x1;
        // Enable SYSPLL
        HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL1) |= (SYSCTL_SYSPLLCTL1_PLLEN);

        //access OTP - read OTP revision or something to power up flash
        OTP_VERSION_FOR_BOOT;

        // read enMASK from TI OTP and load
        if((TI_OTP_REG_VREGCTL_ENMASK_KEY) == 0x5A)
        {
        	if(TI_OTP_REG_VREGCTL_ENMASK_VAL == 0x0)
        	{
        		// OTP bits programmed zero means POR/BOR generation is masked in HW
        		// this means no need to implement Blanking period in SW
        		// blanking window is implemented in HW if the ENMASK bit (bit 15 of VREGCTL) is set to '1'
        		// the default of this bit is '0'.
            	HWREGH(ANALOGSUBSYS_BASE + BROM_ANALOG_SYSCTL_O_VREGCTL) =
            			(HWREGH(ANALOGSUBSYS_BASE + BROM_ANALOG_SYSCTL_O_VREGCTL) & 0x7FFF) | (0x8000);

            	//make sure there is a delay of atleat 100ns after this
            	// device is runnning at 10MHz +/- efuse trimmed (or not) so a count of so 1 cycle is about
            	// 1/10MHz = .1uS = 100ns; so three NOPS should be good enough margin here
            	asm(" NOP ");
            	asm(" NOP ");
            	asm(" NOP ");
        	}
        }
        EDIS;

}

static inline void cbrom_pmm_trim_config()
{

	if(TI_OTP_PMM_LC_TRIM_KEY != 0x5A5A)
		return;

	EALLOW;

	HWREGH(ANALOGSUBSYS_BASE + BROM_ASYSCTL_O_PMMREFTRIM) = TI_OTP_PMM_LC_BGSLOPE_VAL_IREF_TRIM;
	HWREGH(ANALOGSUBSYS_BASE + BROM_ASYSCTL_O_PMMVMONTRIM) = TI_OTP_PMM_LC_VMON_TRIM;
	HWREGH(ANALOGSUBSYS_BASE + BROM_ASYSCTL_O_PMMVMONTRIM2) = TI_OTP_PMM_LC_VMON_TRIM_2;
	HWREGH(ANALOGSUBSYS_BASE + BROM_ASYSCTL_O_PMMVREGTRIM) = TI_OTP_PMM_LC_VREG_TRIM;

	EDIS;

    // calculate the Count for 75 uS at 10MHz +/- 5% MHz efuse trimmed clock, with buffer
    // which is 1225, This would result in 82uS blank window

	//decided to do the NOPS allways irrespetive of the ENMASK
	// it is better to have ENMASK =1 to mask unwanted trips and also better to have
	//NOPS in SW so we are not exercising any logic that might cause problems
	asm(" MOV	@T,#1225 ");
	asm(" RPT	@T \
			||NOP ");


}

void cbrom_intosc_trim_config()
{
	if(TI_OTP_OSC_TRIM_KEY != 0x5A5A)
		return;

	EALLOW;

	HWREGH(ANALOGSUBSYS_BASE + BROM_ASYSCTL_O_OSCREFTRIM) = TI_OTP_OSC_REF_TRIM;
	HWREG(ANALOGSUBSYS_BASE + BROM_ASYSCTL_O_OSC1_TRIM) = TI_OTP_OSC1_TRIM;
	HWREG(ANALOGSUBSYS_BASE + BROM_ASYSCTL_O_OSC2_TRIM) = TI_OTP_OSC2_TRIM;

//	AnalogSubsysRegs.OSCREFTRIM.all = TI_OTP_OSC_REF_TRIM;
//	AnalogSubsysRegs.INTOSC1TRIM.all = TI_OTP_OSC1_TRIM;
//	AnalogSubsysRegs.INTOSC2TRIM.all = TI_OTP_OSC2_TRIM;
	EDIS;

}

static inline void cbrom_enable_pll_ouput_to_clock()
{
	if(((OTP_BOOT_CONFIGURE_WORD & 0xFF000000) >> 24) != 0x5A) //simply return if key match fails
	{
		return;
	}

	if(((OTP_BOOT_CONFIGURE_WORD & 0x3) == 0x1) && (HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLSTS) &
            SYSCTL_SYSPLLSTS_LOCKS))
	{
			EALLOW;
//			ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = ((OTP_BOOT_CONFIGURE_WORD & 0x00FC) >> 2); //0x1; //set it to /2 before enabling PLL
			 HWREG(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) = ((OTP_BOOT_CONFIGURE_WORD & 0x00FC) >> 2);
			//if bits 1:0 of OTP_BOOT_CONFIGURE_WORD are equal to 01b then enable PLL else NO
			HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL1 ) |= SYSCTL_SYSPLLCTL1_PLLCLKEN;
//			 ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;
			EDIS;
	}
}


void cbrom_configure_device_for_fast_boot()
{

	uint32_t EntryAddr = 0xFFFFFFFF;

	//Adjust the PSLEEP as per the FLash wrapper Spec
	//write 0x64 for device would now be working at 10Mhz
	if(HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & (SYSCTL_RESC_POR|SYSCTL_RESC_XRSN))
	{
        EALLOW;
		//set the divider to /1 before we try to wake up flash
        HWREG(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) = 0;

        EDIS;
        Flash_setPumpWakeupTime(0xAA * 2);
    	//RWAIT is set to 0x01 for optimal power up
    	Flash_setReadWaitstates(0x1);
	}
	else
	{
		//Adjust the PSLEEP as per the FLash wrapper Spec
		//write 0x3E8 for device
		Flash_setPumpWakeupTime(0x3E8 *2);
    	//RWAIT is set to 0x04 for optimal power up
    	Flash_setReadWaitstates(0x4);
	}

	Flash_setPumpPowerMode (FLASH_PUMP_PWR_ACTIVE);
	Flash_setBankPowerMode (FLASH_BANK0, FLASH_BANK_PWR_ACTIVE);
	Flash_setBankPowerMode (FLASH_BANK1, FLASH_BANK_PWR_ACTIVE);

/*****************************************************************************
	WARNING: Delete this code. Was meant for debug purposes only
*/
//	EALLOW;
//	HWREG(0x0005FB00)  = 0x0;	//Disable Flash ECC to facilitate BOOTROM bootloader automation
//	EDIS;

/*****************************************************************************/

	//do the below for XRSn or POR resets only
	if(HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & (SYSCTL_RESC_POR|SYSCTL_RESC_XRSN))
	{

		//change dividers, power up PLL
		cbrom_change_clock_dividers();
		cbrom_pmm_trim_config();
		cbrom_enable_pll_ouput_to_clock();

		//Adjust the PSLEEP as per the FLash wrapper Spec
		//write 0x3E8 for device would now be working at 100Mhz
		Flash_setPumpWakeupTime(0x3E8 *2);
	}
	//set back the Flash wait states
	Flash_setReadWaitstates(0xF);


	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_11;
	if((EntryAddr != 0xFFFFFFFF) &&
			(EntryAddr != 0x00000000))
	{
		/*if OTP is programmed, then call OTP function*/
		((void (*)(void))EntryAddr)();
	}

}


void cbrom_device_config()
{
    uint32_t	EntryAddr = 0xFFFFFFFF;

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_15;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }


	EALLOW;
	//PARTIDL
	HWREG(DEVCFG_BASE + SYSCTL_O_PARTIDL) = TI_OTP_PARTID_L;
	HWREG(DEVCFG_BASE + SYSCTL_O_PARTIDH) = TI_OTP_PARTID_H;

	//DC0 to DC25
//	HWREG(DEVCFG_BASE + SYSCTL_O_DC0) 	= TI_OTP_REG_DC00;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC1) 	= TI_OTP_REG_DC01;
//	HWREG(DEVCFG_BASE + SYSCTL_O_DC2) 	= TI_OTP_REG_DC02;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC3) 	= TI_OTP_REG_DC03;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC4) 	= TI_OTP_REG_DC04;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC5) 	= TI_OTP_REG_DC05;
//	HWREG(DEVCFG_BASE + SYSCTL_O_DC6) 	= TI_OTP_REG_DC06;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC7) 	= TI_OTP_REG_DC07;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC8) 	= TI_OTP_REG_DC08;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC9) 	= TI_OTP_REG_DC09;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC10) 	= TI_OTP_REG_DC10;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC11) 	= TI_OTP_REG_DC11;
//	HWREG(DEVCFG_BASE + SYSCTL_O_DC12) 	= TI_OTP_REG_DC12;
//	HWREG(DEVCFG_BASE + SYSCTL_O_DC13) 	= TI_OTP_REG_DC13;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC14) 	= TI_OTP_REG_DC14;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC15) = TI_OTP_REG_DC15;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC16) = TI_OTP_REG_DC16;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC17) = TI_OTP_REG_DC17;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC18) = TI_OTP_REG_DC18;
//	HWREG(DEVCFG_BASE + SYSCTL_O_DC19) = TI_OTP_REG_DC19;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC20) = TI_OTP_REG_DC20;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC21) = TI_OTP_REG_DC21;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC22) = TI_OTP_REG_DC22;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC23) = TI_OTP_REG_DC23;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC24) = TI_OTP_REG_DC24;
	HWREG(DEVCFG_BASE + SYSCTL_O_DC25) = TI_OTP_REG_DC25;

    //PERCNF1
//    DevCfgRegs.PERCNF1.all = TI_OTP_REG_PERCNF1;
//	HWREG(DEVCFG_BASE + SYSCTL_O_PERCNF1) = TI_OTP_REG_PERCNF1;

// load CPUROM_DCx
	HWREG(DEVCFG_BASE + BROM_SYSCTL_O_CPUROM_DC1) = TI_OTP_CPUROM_DC1;
	HWREG(DEVCFG_BASE + BROM_SYSCTL_O_CPUROM_DC2) = TI_OTP_CPUROM_DC2;
	HWREG(DEVCFG_BASE + BROM_SYSCTL_O_CPUROM_DC3) = TI_OTP_CPUROM_DC3;
	HWREG(DEVCFG_BASE + BROM_SYSCTL_O_CPUROM_DC4) = TI_OTP_CPUROM_DC4;
// load CLAROM_DCx
	HWREG(DEVCFG_BASE + BROM_SYSCTL_O_CLAROM_DC1) = TI_OTP_CLAROM_DC1;
	HWREG(DEVCFG_BASE + BROM_SYSCTL_O_CLAROM_DC2) = TI_OTP_CLAROM_DC2;
	HWREG(DEVCFG_BASE + BROM_SYSCTL_O_CLAROM_DC3) = TI_OTP_CLAROM_DC3;
	HWREG(DEVCFG_BASE + BROM_SYSCTL_O_CLAROM_DC4) = TI_OTP_CLAROM_DC4;

//load PKGTYPE - only if KEY is programmed in TI_OTP_PKG_TYPE[31:24] == 0x5A
	if((((uint32_t)TI_OTP_PKG_TYPE & 0xFF000000U) >> 24) == 0x5A)
	{
		//write only LSB 3:0
		HWREG(DEVCFG_BASE + BROM_SYSCTL_O_PKG_TYPE) = (TI_OTP_PKG_TYPE & (uint32_t)0x00000000F);
	}
}

//
//Enable pullups for the unbonded GPIOs on the 144PZ package.
//
//These below GPIOs are available on the package.
//GPIOs     Grp Bits
//0-19      A   19:0
//22-31     A   31:22
//32-59     B   27:0
void enable_unbonded_pullups_144_pin()
{
	//Write 0 to unbonded pin in order to pull-up.
	//if an available pin is already pulled-up, then the pin stays pulled-up.
	//Logical AND with 0 does both of these.
    EALLOW;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD) &= 0xFFCFFFFFUL;  //GPIOs 0-19, 22-31
    HWREG(GPIOCTRL_BASE + GPIO_O_GPBPUD) &= 0x0FFFFFFFUL;  //GPIOs 32-59
    EDIS;
}

//
//Enable pullups for the unbonded GPIOs on the 100PZ package.
//
//These below GPIOs are available on the package.
//GPIOs     Grp Bits
//0-19      A   19:0
//22-31     A   31:22
//32-40     B   8:0
//56-59     B   27:24
void enable_unbonded_pullups_100_pin()
{
	//Write 0 to unbonded pin in order to pull-up.
	//if an available pin is already pulled-up, then the pin stays pulled-up.
	//Logical AND with 0 does both of these.
    EALLOW;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD) &= 0xFFCFFFFFUL;  //GPIOs 0-19, 22-31
    HWREG(GPIOCTRL_BASE + GPIO_O_GPBPUD) &= 0x0F0001FFUL;  //GPIOs 32-40, 56-59
    EDIS;
}

//
//Enable pullups for the unbonded GPIOs on the 80PZ package.
//
//These below GPIOs are available on the package.
//GPIOs     Grp Bits
//0-19      A   19:0
//22-31     A   31:22
//32-38     B   6:0
void enable_unbonded_pullups_80_pin()
{
	//Write 0 to unbonded pin in order to pull-up.
	//if an available pin is already pulled-up, then the pin stays pulled-up.
	//Logical AND with 0 does both of these.
    EALLOW;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD) &= 0xFFCFFFFFUL;  //GPIOs 0-19, 22-31
    HWREG(GPIOCTRL_BASE + GPIO_O_GPBPUD) &= 0x0000007FUL;  //GPIOs 32-38
    EDIS;
}

//
//Enable pullups for the unbonded GPIOs on the 64PZ package.
//Non-automotive.
//
//These below GPIOs are available on the package.
//GPIOs     Grp Bits
//0-13      A   13:0
//16-19     A   19:16
//22-24     A   24:22
//28-29     A   29:28
//32-33     B   1:0
//35-38     B   6:3
void enable_unbonded_pullups_64_pin()
{
	//Write 0 to unbonded pin in order to pull-up.
	//if an available pin is already pulled-up, then the pin stays pulled-up.
	//Logical AND with 0 does both of these.
    EALLOW;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD) &= 0x31CF3FFFUL;  //GPIOs 0-13, 16-19, 22-24,28-29
    HWREG(GPIOCTRL_BASE + GPIO_O_GPBPUD) &= 0x0000007BUL;  //GPIOs 32-33,35-38
    EDIS;
}

//
//Enable pullups for the unbonded GPIOs on the Q 64PZ package.
//Automotive.
//
//These below GPIOs are available on the package.
//GPIOs     Grp Bits
//0-11      A   11:0
//16-19     A   19:16
//22-24     A   24:22
//28-29     A   29:28
//32-33     B   1:0
//35-38     B   6:3
void enable_unbonded_pullups_64_Q_pin()
{
	//Write 0 to unbonded pin in order to pull-up.
	//if an available pin is already pulled-up, then the pin stays pulled-up.
	//Logical AND with 0 does both of these.
    EALLOW;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD) &= 0x31CF0FFFUL;  //GPIOs 0-11, 16-19, 22-24,28-29
    HWREG(GPIOCTRL_BASE + GPIO_O_GPBPUD) &= 0x0000007BUL;  //GPIOs 32-33,35-38
    EDIS;
}

//
//Enable pullups for the unbonded GPIOs on the 56PZ package.
//
//These below GPIOs are available on the package.
//GPIOs     Grp Bits
//0-9       A   9:0
//11-13     A   13:11
//16-19     A   19:16
//22-24     A   24:22
//28-29     A   29:28
//32-33     B   1:0
//35-38     B   6:3
void enable_unbonded_pullups_56_pin()
{
	//Write 0 to unbonded pin in order to pull-up.
	//if an available pin is already pulled-up, then the pin stays pulled-up.
	//Logical AND with 0 does both of these.
    EALLOW;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD) &= 0x31CF3BFFUL;  //GPIOs 0-9, 11-13, 16-19, 22-24,28-29
    HWREG(GPIOCTRL_BASE + GPIO_O_GPBPUD) &= 0x0000007BUL;  //GPIOs 32-33,35-38
    EDIS;
}

void enable_unbonded_io_pullups()
{

	uint32_t pin_count = ((TI_OTP_PARTID_L & 0x00000700) >> 8); //bits 8-10 have pin count
///*
// * 0 = 56  pin
// * 1 = 64  Auto-pin
// * 2 = 64  Non Auto-pin
// * 3 = 80  pin
// * 4 = 144 pin
// * 5 = 100 pin
// * 6 = 176 pin (invalid on F28004x)
// * 7 = 337 pin (invalid on F28004x)
// */
	if(pin_count == 0U)
	{
		enable_unbonded_pullups_56_pin();
	}
	else if(pin_count == 1U)
	{
		enable_unbonded_pullups_64_Q_pin();
	}
	else if(pin_count == 2U)
	{
		enable_unbonded_pullups_64_pin();
	}
	else if(pin_count == 3U)
	{
		; //reserved
	}
	else if(pin_count == 4U)
	{
		enable_unbonded_pullups_144_pin();
	}
	else if (pin_count == 5U) //100 pin package
	{
		enable_unbonded_pullups_100_pin();
	}
	else
	{
		; // do nothing
	}
}


//Read the GPyDAT register bit for the specified pin.
uint32_t cbrom_GPIO_ReadPin(uint32_t pin)
{
	if((224 <= pin) && (pin <= 247))
	{
		GPIO_setAnalogMode(pin,GPIO_ANALOG_DISABLED);
	}

	return GPIO_readPin(pin);
}

uint16_t cbrom_decode_bootpins(uint32_t pinconfig)
{
    uint32_t bootpin0 = 0;
    uint32_t bootpin1 = 0;
    uint32_t bootpin2 = 0;
    uint16_t bmode = 0;
    //default boot pins - mode0 is GPIO32, mode1 is GPIO24

    if((uint32_t)(pinconfig & (uint32_t)0x00FFFFFF) == (uint32_t)0x00FFFFFF)
    {
//        bootpin0 = 32;
//        bootpin1 = 24;
//        bootpin2 = 0xFF;
    	return 0; //KEY Programmed and all BMPSx bits are all_1s
    }
    else
    {
    	bootpin0 = (pinconfig & 0xFF);
    	bootpin1 = ((pinconfig >> 8) & 0xFF);
    	bootpin2 = ((((uint32_t)pinconfig) >> 16) & 0xFF);
    }

    //1.>	GPIO36, GPIO38 – these are unavailable
    //2.>	GPIO22, GPIO23 – these are muxed with PMM signals
    //3.>	GPIO60 – GPIO223 – these are unavailable
    //4.>	GPIO20 - GPIO21 - these are unavailable
    //if chosen boot ROM selects the factory default

    if((bootpin0 == 36) || (bootpin0 == 38)
    		|| ((19 < bootpin0) && (bootpin0 < 24))
    		|| ((59 < bootpin0) && (bootpin0 < 224)))
    {
        bootpin0 = 32;
    }

    if((bootpin1 == 36) || (bootpin1 == 38)
    		|| ((19 < bootpin1) && (bootpin1 < 24))
			|| ((59 < bootpin1) && (bootpin1 < 224)))
    {
        bootpin1 = 24;
    }

    if((bootpin2 == 36) || (bootpin2 == 38)
    		|| ((19 < bootpin2) && (bootpin2 < 24))
			|| ((59 < bootpin2) && (bootpin2 < 224)))
    {
        bootpin2 = 0xFF;
    }

    if(bootpin2 == 0xFF)
    {
    	bmode = 0x0;
    }
    else
    {
    	bmode = (uint16_t)cbrom_GPIO_ReadPin(bootpin2) << 2 ;
    }

    if(bootpin1 == 0xFF)
    {
    	bmode &= 0xFD; // zero out bit 1
    }
    else
    {
    	bmode &= 0xFD;
    	bmode |= (uint16_t)cbrom_GPIO_ReadPin(bootpin1) << 1 ;
    }

    if(bootpin0 == 0xFF)
    {
    	bmode &= 0xFE; // zero out bit 0
    }
    else
    {
    	bmode &= 0xFE;
    	bmode |= (uint16_t)cbrom_GPIO_ReadPin(bootpin0);
    }



    return (bmode & 0x7);
}


#pragma DATA_SECTION(BootMode, "USER_BOOTMODEVAR");
uint32_t    BootMode ; //making this global for debug
uint32_t cbrom_system_init()
{
    uint32_t	EntryAddr = 0xFFFFFFFF;


    if(HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & (SYSCTL_RESC_POR | SYSCTL_RESC_XRSN))
    {
    	cbrom_status = 0; // init the status only on POR/XRSn, rest of the times it is allways non-volatile
    }
	cbrom_pbist_status = 0;
    BootMode = 0xFFFFFFFF;
	/*set BootROM health status to indicate that boot started*/
	cbrom_status |= BOOTROM_START_BOOT;
	/* initialize iTrap address, and branch address variables to cbromt values*/
	iTrap_addr = 0xFFFFFFFF;


	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_1;
	if((EntryAddr != 0xFFFFFFFF) &&
			(EntryAddr != 0x00000000))
	{
		/*if OTP is programmed, then call OTP function*/
		((void (*)(void))EntryAddr)();
	}

    /* enable C1 NMI*/
    EALLOW;
//    NmiIntruptRegs.NMICFG.bit.NMIE = 1;
    //SysCtl_enableNMIGlobalInterrupt();
    HWREGH(NMI_BASE + NMI_O_CFG) = NMI_CFG_NMIE;

    InitDCSM();

    //capture any single bit errors after DCSM init
    //if the below addresses are valid then user has to
    //debug these further
    brom_flash_single_bit_error_low_address =
    		Flash_getSingleBitErrorAddressLow();
    brom_flash_single_bit_error_high_address =
    		Flash_getSingleBitErrorAddressHigh();


    /*set C-BootROM health status to indicate that boot started*/
    cbrom_status |= BOOTROM_DCSM_INIT_DONE;

    // Add an escape Point here. if there is porblem with power, bypass PLL or increment SYSDIVSEL in TI-OTP and
    //then renable PLL (re-init SYSDIVSEL to /2) at the PBIST_end_escape point).
	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_3;
	if((EntryAddr != 0xFFFFFFFF) &&
			(EntryAddr != 0x00000000))
	{
		/*if OTP is programmed, then call OTP function*/
		((void (*)(void))EntryAddr)();
	}

	if(Z1_OTP_BOOT_GPREG2_KEY == 0x5A)
	{
	    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_13;
	    if((EntryAddr != 0xFFFFFFFF) &&
	            (EntryAddr != 0x00000000))
	    {
	        /*if OTP is programmed, then call OTP function*/
	        ((void (*)(void))EntryAddr)();
	    }

		//set ERROR_STS pin if enabled by user
		if(Z1_OTP_BOOT_GPREG2_ERRSTS_CONFIG == 0x0)
		{
			GPIO_setPinConfig(GPIO_24_ERROR_STS);
			GPIO_lockPortConfig(GPIO_PORT_A, 0x01000000U); //lock pin 24
		}
		else if(Z1_OTP_BOOT_GPREG2_ERRSTS_CONFIG == 0x1)
		{
			GPIO_setPinConfig(GPIO_28_ERROR_STS);
			GPIO_lockPortConfig(GPIO_PORT_A, 0x10000000U); //lock pin 28
		}
		else if (Z1_OTP_BOOT_GPREG2_ERRSTS_CONFIG == 0x2)
		{
			GPIO_setPinConfig(GPIO_29_ERROR_STS);	//
			GPIO_lockPortConfig(GPIO_PORT_A, 0x20000000U); //lock pin 29

		}

		if(HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & ((uint32_t)SYSCTL_RESC_POR | (uint32_t)SYSCTL_RESC_XRSN ))
		{
			//set CJTAGNODEID[3:0]
			HWREG(DEVCFG_BASE + SYSCTL_O_CJTAGNODEID) = ((HWREG(DEVCFG_BASE + SYSCTL_O_CJTAGNODEID) & 0xF0) |
														(Z1_OTP_BOOT_GPREG2_CJTAGNODEID));
		}

		if(HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & ((uint32_t)SYSCTL_RESC_POR))
		{

		    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_14;
		    if((EntryAddr != 0xFFFFFFFF) &&
		            (EntryAddr != 0x00000000))
		    {
		        /*if OTP is programmed, then call OTP function*/
		        ((void (*)(void))EntryAddr)();
		    }

  		    // DO PBIST here

		//call Boot ROM checksum routine to check CRC on bootROM (unsecure ROM only)
			// if checksum fails - skip PBIST and continue to boot.
			// inlcude status bits in BootROM STATUS word
		//call PBIST here (we have PLL locked at 90MHz and only if it is a POR reset and only if there is no NMI)
		//call PBIST only if user has asked for it to RUN.
			if((Z1_OTP_BOOT_GPREG2_PBIST_CONFIG & 0x3) == 0x00)
			{
				 //$$$$$TBD$$$$$$$$$////
				//do ROM checksum here, if fail - skip below
				if(verify_pbist_checksum_onROM() == 0)
				{
					cbrom_pbist_status = PBIST_PORMemoryTest();
					//PBIST function return here using RPC
					asm(" .ref _ExitPBISTLoc");
					asm(" PUSH XAR7");
					asm(" MOVL XAR7, #_ExitPBISTLoc");
					asm(" PUSH XAR7");
					asm(" POP RPC");
					asm(" POP XAR7");
					//ExitBoot location is supposed to be loaded to RPC, but its gone because of RAM-INIT in PBIST function
					//ROM code needs to initialize RPC
					// PUSH _exitBoot_location
					// POP RPC
					// continue
					// re-initialize the variables as needed.
					/*set BootROM health status to indicate MEM test is done*/
				    BootMode = 0xFFFFFFFF;
					/* initialize iTrap address, and branch address variables to cbromt values*/
					iTrap_addr = 0xFFFFFFFF;
					cbrom_status |= BOOTROM_START_BOOT;
				    cbrom_status |= BOOTROM_DCSM_INIT_DONE;
					cbrom_status |= BOOTROM_POR_MEM_TEST_DONE;
					//re-init the single bit error address status.
					brom_flash_single_bit_error_low_address =
				    		Flash_getSingleBitErrorAddressLow();
				    brom_flash_single_bit_error_high_address =
				    		Flash_getSingleBitErrorAddressHigh();


				}
			}
		}
	}


    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_9;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

    enable_unbonded_io_pullups();

//    if(CpuSysRegs.RESC.all & (SYSCTL_RESC_POR | SYSCTL_RESC_XRSN))
    if(HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & ((uint32_t)SYSCTL_RESC_POR | (uint32_t)SYSCTL_RESC_XRSN ))
    {
        //do the below only in this order, don;t dare to change
        EALLOW;
        // bypass PLL here

        if((HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL1) & SYSCTL_SYSPLLCTL1_PLLCLKEN) != 0)
        {
        	HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL1) &= ~SYSCTL_SYSPLLCTL1_PLLCLKEN;
        }

        //set PLL multiplier to 0x0

        if((HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLMULT)) != 0)
        {
        	HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLMULT) = 0;
        }
        //set the divider to /1

        if((HWREG(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL)) != 0)
        {
        	HWREG(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) = 0;
        }

        EDIS;
        cbrom_intosc_trim_config();

		// calculate the Count for 12 uS at 10MHz +/- 7% MHz efuse trimmed clock, with buffer
		// This would result in 16uS blank window

		asm(" MOV	@T,#178 ");
		asm(" RPT	@T \
			  || NOP ");

    }
    if(((*(uint32_t *)DEVICE_CAL_LOCATION) != 0xFFFFFFFF) &&
    		((*(uint32_t *)DEVICE_CAL_LOCATION) != 0x00000000))
     {
        (*CBROM_DEVCAL)();
     }

    //clear RESC bits so that bootROM would not go into
    //a unwanted reset handling if it got reset for some reason
    if(HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & ((uint32_t)SYSCTL_RESC_POR))
    {
    	//clear POR and XRSn

    	SysCtl_clearResetCause(SYSCTL_RESC_POR | SYSCTL_RESC_XRSN);
    	cbrom_status |= (BOOTROM_HANDLED_XRSN | BOOTROM_HANDLED_POR);


    }

    if(HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & ((uint32_t)SYSCTL_RESC_XRSN))
    {
    	SysCtl_clearResetCause(SYSCTL_RESC_XRSN);
    	cbrom_status |= (BOOTROM_HANDLED_XRSN);
    }

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_4;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

    cbrom_status |= BOOTROM_RESC_HANDLED;
   	BootMode = SelectBootMode();

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_2;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

    switch(BootMode)
    {
    case FLASH_BOOT:
    	EntryAddr = FLASH_ENTRY_POINT;
        cbrom_status |= BOOTROM_IN_FLASH_BOOT;
        break;

    case FLASH_BOOT_ALT1:
    	EntryAddr = FLASH_ENTRY_POINT_ALT1;
        cbrom_status |= BOOTROM_IN_FLASH_BOOT;
        break;

    case FLASH_BOOT_ALT2:
    	EntryAddr = FLASH_ENTRY_POINT_ALT2;
        cbrom_status |= BOOTROM_IN_FLASH_BOOT;
        break;

    case FLASH_BOOT_ALT3:
    	EntryAddr = FLASH_ENTRY_POINT_ALT3;
        cbrom_status |= BOOTROM_IN_FLASH_BOOT;
        break;


    case RAM_BOOT:
    	EntryAddr = RAM_ENTRY_POINT;
        cbrom_status |= BOOTROM_IN_RAM_BOOT;
        break;

    case WAIT_BOOT:
    case WAIT_BOOT_ALT1:
        break;

    case PARALLEL_BOOT:
        cbrom_status |= BOOTROM_IN_PARALLEL_BOOT;
    	EntryAddr = Parallel_Boot();
        break;

    case SCI_BOOT:
    case SCI_BOOT_ALT1:
    case SCI_BOOT_ALT2:
    case SCI_BOOT_ALT3:
    case SCI_BOOT_ALT4:
        cbrom_status |= BOOTROM_IN_SCI_BOOT;
    	EntryAddr = SCI_Boot(BootMode);
    	break;
    case CAN_BOOT:
    case CAN_BOOT_ALT1:
    case CAN_BOOT_ALT2:
    case CAN_BOOT_ALT3:
    case CAN_BOOT_SENDTEST:
    case CAN_BOOT_ALT1_SENDTEST:
    case CAN_BOOT_ALT2_SENDTEST:
    case CAN_BOOT_ALT3_SENDTEST:
        cbrom_status |= BOOTROM_IN_CAN_BOOT;
    	EntryAddr = DCAN_Boot(BootMode, 0, 1 );
        break;
    case SPI_MASTER_BOOT:
    case SPI_MASTER_BOOT_ALT1:
    case SPI_MASTER_BOOT_ALT2:
    case SPI_MASTER_BOOT_ALT3:
    case SPI_MASTER_BOOT_ALT4:
        cbrom_status |= BOOTROM_IN_SPI_BOOT;
    	EntryAddr = SPI_Boot(BootMode);
    	break;
    case I2C_MASTER_BOOT:
    case I2C_MASTER_BOOT_ALT1:
    case I2C_MASTER_BOOT_ALT2:
    case I2C_MASTER_BOOT_ALT3:
        cbrom_status |= BOOTROM_IN_I2C_BOOT;
    	EntryAddr = I2C_Boot(BootMode);
    	break;
    case PLC_BOOT:
    	cbrom_status |= BOOTROM_IN_PLC_BOOT;
    	EntryAddr = PLC_ENTRY_POINT_IN_ROM;
    	break;
    default:
    	  if((uint32_t)HWREG(CPUSYS_BASE + SYSCTL_O_RESC) & (uint32_t)SYSCTL_RESC_DCON)
    	    {
    	        EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_12;
    	        if((EntryAddr != 0xFFFFFFFF) &&
    	                (EntryAddr != 0x00000000))
    	        {
    	            /*if OTP is programmed, then call OTP function*/
    	            ((void (*)(void))EntryAddr)();
    	        }
    	        BootMode = WAIT_BOOT;
    	    }
    	    else
    	    {
    	        EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_12;
    	        if((EntryAddr != 0xFFFFFFFF) &&
    	                (EntryAddr != 0x00000000))
    	        {
    	            /*if OTP is programmed, then call OTP function*/
    	            ((void (*)(void))EntryAddr)();
    	        }
    	        //BootMode = WAIT_BOOT;	//should we do flash boot?
    	        BootMode = FLASH_BOOT;
    	        EntryAddr = FLASH_ENTRY_POINT;
    	        cbrom_status |= BOOTROM_IN_FLASH_BOOT;
    	    }

    }
    cbrom_status |= BOOTROM_BOOT_COMPLETE;

    if(BootMode == WAIT_BOOT)
    {
    	SysCtl_enableWatchdog();
        asm("   ESTOP0");
    	for(;;)
    	{
    	}
    }
    else if (BootMode == WAIT_BOOT_ALT1)
    {
        asm("   ESTOP0");
    	for(;;)
    	{
    	}
    }
    else
    {
        //to make sure wathDOG is enabled
    	SysCtl_enableWatchdog();
        return EntryAddr;
    }
}

