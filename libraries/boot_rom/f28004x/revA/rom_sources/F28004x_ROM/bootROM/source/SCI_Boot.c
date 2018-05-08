//###########################################################################
//
// FILE:    SCI_Boot.c
//
// TITLE:   SCI Boot mode routines
//
// Functions:
//
//     uint32_t SCI_Boot(void)
//     inline void SCIA_Init(void)
//     inline void SCIA_AutobaudLock(void)
//     uint32_t SCIA_GetWordData(void)
//
// Notes:
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July 2015 $
//###########################################################################

#include "bootrom.h"


// Private functions
uint16_t SCIA_GetWordData(void);

// External functions
extern void CopyData(void);
uint32_t GetLongData(void);
extern void ReadReservedFn(void);

static void SCIBOOT_configure_gpio(uint32_t BootMode);

/*
--------------------------------------------------
Opt No.|  BOOTDEF      |  SCITXA    |  SCIRXA    |
--------------------------------------------------
  1    |  0x01(default)|  29        |  28        |
  2    |  0x21         |  16        |  17        |
  3    |  0x41         |  8         |  9         |
  4    |  0x61         |  48        |  49        |
  5    |  0x81         |  24        |  25        |
--------------------------------------------------
*/

//#################################################
// uint32_t SCI_Boot(void)
//--------------------------------------------
// This module is the main SCI boot routine.
// It will load code via the SCI-A port.
//
// It will return a entry point address back
// to the InitBoot routine which in turn calls
// the ExitBoot routine.
//--------------------------------------------

uint32_t SCI_Boot(uint32_t  BootMode)
{
   uint32_t EntryAddr;
   uint16_t byteData;

   EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_6;   //re-using the entry point
   if((EntryAddr != 0xFFFFFFFF) &&
           (EntryAddr != 0x00000000))
   {
       /*if OTP is programmed, then call OTP function*/
       ((void (*)(void))EntryAddr)();
   }

	/*read CCNF0 register to check if SCI is enabled or not*/
   if(SysCtl_isPeripheralPresent(SYSCTL_PERIPH_PRESENT_SCIA) == false)
//	if((DevCfgRegs.DC8.bit.SCI_A != 0x01))
	{
		return 0xFFFFFFFF;
	}

   
   // Asign GetWordData to the SCI-A version of the
   // function.  GetWordData is a pointer to a function.
   GetWordData = SCIA_GetWordData;

	//----------------------------------------------
    // Initialize the SCI-A port for communications
    // with the host.
    //----------------------------------------------

    // Enable the SCI-A clocks
    EALLOW;
//  CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);

//    ClkCfgRegs.LOSPCP.all = 0x0002;
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);

//	 SciaRegs.SCIFFTX.all=0x8000;
     HWREGH(SCIA_BASE + SCI_O_FFTX) = SCI_FFTX_SCIRST;
// 	 SCI_resetChannels(SCIA_BASE);

    // 1 stop bit, No parity, 8-bit character
    // No loopback
    //SciaRegs.SCICCR.all = 0x0007;
	HWREGB(SCIA_BASE + SCI_O_CCR) = (SCI_CONFIG_WLEN_8|SCI_CONFIG_PAR_NONE|SCI_CONFIG_STOP_ONE);

    // Enable TX, RX, Use internal SCICLK
    //SciaRegs.SCICTL1.all = 0x0003;
	HWREGB(SCIA_BASE + SCI_O_CTL1) = (SCI_CTL1_TXENA | SCI_CTL1_RXENA);

    // Disable RxErr, Sleep, TX Wake,
    // Diable Rx Interrupt, Tx Interrupt
    //SciaRegs.SCICTL2.all = 0x0000;
	HWREGB(SCIA_BASE + SCI_O_CTL2) = 0x0;

    // Relinquish SCI-A from reset
    //SciaRegs.SCICTL1.all = 0x0023;
	SCI_enableModule(SCIA_BASE);

    EDIS;

	//GPIO INIT
    SCIBOOT_configure_gpio(BootMode);

	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_6;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }


    //------------------------------------------------
    // Perform autobaud lock with the host.
    // Note that if autobaud never occurs
    // the program will hang in this routine as there
    // is no timeout mechanism included.
    //------------------------------------------------

    // Must prime baud register with >= 1
    //SciaRegs.SCILBAUD = 1;
	HWREGB (SCIA_BASE + SCI_O_LBAUD) = 1;
    // Prepare for autobaud detection
    // Set the CDC bit to enable autobaud detection
    // and clear the ABD bit
	//SciaRegs.SCIFFCT.bit.CDC = 1;
	HWREGH(SCIA_BASE + SCI_O_FFCT) = SCI_FFCT_CDC;

	//SciaRegs.SCIFFCT.bit.ABDCLR = 1;
	HWREGH(SCIA_BASE + SCI_O_FFCT) |= SCI_FFCT_ABDCLR;

    // Wait until we correctly read an
    // 'A' or 'a' and lock
    //while(SciaRegs.SCIFFCT.bit.ABD != 1) {}
	while (!(HWREGH(SCIA_BASE + SCI_O_FFCT) & SCI_FFCT_ABD)) {}
    // After autobaud lock, clear the ABD and CDC bits
    //SciaRegs.SCIFFCT.bit.ABDCLR = 1;
	HWREGH(SCIA_BASE + SCI_O_FFCT) = SCI_FFCT_ABDCLR;

	//SciaRegs.SCIFFCT.bit.CDC = 0;
	HWREGH(SCIA_BASE + SCI_O_FFCT) &= ~SCI_FFCT_CDC;

    //while(SciaRegs.SCIRXST.bit.RXRDY != 1) { }
    //byteData = SciaRegs.SCIRXBUF.bit.RXDT;
	byteData = SCI_readCharBlockingNonFIFO(SCIA_BASE);

    //SciaRegs.SCITXBUF = byteData;
	SCI_writeCharNonBlocking(SCIA_BASE,byteData);

   // If the KeyValue was invalid, abort the load
   // and return the flash entry point.
   if (SCIA_GetWordData() != 0x08AA) return FLASH_ENTRY_POINT;

   ReadReservedFn();

   EntryAddr = GetLongData();

   CopyData();

   return EntryAddr;
}

//#################################################
// uint16_t SCIA_GetWordData(void)
//-----------------------------------------------
// This routine fetches two bytes from the SCI-A
// port and puts them together to form a single
// 16-bit value.  It is assumed that the host is
// sending the data in the order LSB followed by MSB.
//-----------------------------------------------


uint16_t SCIA_GetWordData()
{
   uint16_t wordData;
   uint16_t byteData;

   wordData = 0x0000;
   byteData = 0x0000;

// Fetch the LSB and verify back to the host
// while(SciaRegs.SCIRXST.bit.RXRDY != 1) { }
// wordData =  (uint16_t)SciaRegs.SCIRXBUF.bit.RXDT;
	wordData = SCI_readCharBlockingNonFIFO(SCIA_BASE);

//   SciaRegs.SCITXBUF = wordData;
	SCI_writeCharNonBlocking(SCIA_BASE,wordData);


//byteData =  (uint16_t)SciaRegs.SCIRXBUF.bit.RXDT;
	byteData = SCI_readCharBlockingNonFIFO(SCIA_BASE);
   //SciaRegs.SCITXBUF = byteData;
	SCI_writeCharNonBlocking(SCIA_BASE,byteData);

   // form the wordData from the MSB:LSB
   wordData |= (byteData << 8);

   return wordData;
}


/*
--------------------------------------------------
Opt No.|  BOOTDEF      |  SCITXA    |  SCIRXA    |
--------------------------------------------------
  1    |  0x01(default)|  29        |  28        |
  2    |  0x21         |  16        |  17        |
  3    |  0x41         |  8         |  9         |
  4    |  0x61         |  48        |  49        |
  5    |  0x81         |  24        |  25        |
--------------------------------------------------
*/

static void SCIBOOT_configure_gpio(uint32_t BootMode)
{
	//Unlock the GPIO configuration registers
	EALLOW;
	GPIO_unlockPortConfig(GPIO_PORT_A,0x00000000);
	GPIO_unlockPortConfig(GPIO_PORT_B,0x00000000);

	switch (BootMode)
	{
		case SCI_BOOT:
		default:
			 //Enable pull up on GPIOs 29, 28 pins
			 GPIO_setPadConfig(29,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(28,GPIO_PIN_TYPE_PULLUP);

			 //GPIO29 = SCIATX
			 //GPIO28 = SCIARX
			 GPIO_setPinConfig(GPIO_29_SCITXDA);
			 GPIO_setPinConfig(GPIO_28_SCIRXDA);

			 //Configure GPIO28 as async pin
			 GPIO_setQualificationMode(28,GPIO_QUAL_ASYNC);
			 break;

		case SCI_BOOT_ALT1:
			 //Enable pull up on GPIOs 16, 17 pins
			 GPIO_setPadConfig(16,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(17,GPIO_PIN_TYPE_PULLUP);

			 //GPIO16 = SCIATX
			 //GPIO17 = SCIARX
			 GPIO_setPinConfig(GPIO_16_SCITXDA);
			 GPIO_setPinConfig(GPIO_17_SCIRXDA);

			 //Configure GPIO17 as async pin
			 GPIO_setQualificationMode(17,GPIO_QUAL_ASYNC);
			 break;

		case SCI_BOOT_ALT2:
			 //Enable pull up on GPIOs 8, 9 pins
			 GPIO_setPadConfig(8,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(9,GPIO_PIN_TYPE_PULLUP);

			 //GPIO8 = SCIATX
			 //GPIO9 = SCIARX
			 GPIO_setPinConfig(GPIO_8_SCITXDA);
			 GPIO_setPinConfig(GPIO_9_SCIRXDA);

			 //Configure GPIO9 as async pin
			 GPIO_setQualificationMode(9,GPIO_QUAL_ASYNC);
			 break;

		case SCI_BOOT_ALT3:
			 //Enable pull up on GPIOs 48, 49 pins
			 GPIO_setPadConfig(48,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(49,GPIO_PIN_TYPE_PULLUP);

			 //GPIO48 = SCIATX
			 //GPIO49 = SCIARX
			 GPIO_setPinConfig(GPIO_48_SCITXDA);
			 GPIO_setPinConfig(GPIO_49_SCIRXDA);

			 //Configure GPIO49 as async pin
			 GPIO_setQualificationMode(49,GPIO_QUAL_ASYNC);
			 break;

		case SCI_BOOT_ALT4:
			 //Enable pull up on GPIOs 24, 25 pins
			 GPIO_setPadConfig(24,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(25,GPIO_PIN_TYPE_PULLUP);

			 //GPIO24 = SCIATX
			 //GPIO25 = SCIARX
			 GPIO_setPinConfig(GPIO_24_SCITXDA);
			 GPIO_setPinConfig(GPIO_25_SCIRXDA);

			 //Configure GPIO25 as async pin
			 GPIO_setQualificationMode(25,GPIO_QUAL_ASYNC);
			 break;

	}

}


// EOF-------

