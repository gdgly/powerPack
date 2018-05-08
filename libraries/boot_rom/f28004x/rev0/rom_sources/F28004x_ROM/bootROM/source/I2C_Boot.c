//###########################################################################
//
// FILE:    I2C_Boot.c
//
// TITLE:   I2C Boot mode routines
//
// Functions:
//
//     uint32_t I2C_Boot(void)
//     inline uint16_t I2C_CheckKeyVal(void)
//     inline void I2C_ReservedFn(void)
//     uint16_t I2C_GetWord(void)
//
// Notes:
//     The I2C code contained here is specifically steamlined for the
//     bootloader. It can be used to load code via the I2C port into the
//     RAM and jump to an entry point within that code.
//
//     Features/Limitations:
//     - The I2C boot loader code is written to communicate with an EEPROM
//       device at address 0x50. The EEPROM must adhere to conventional I2C
//       EEPROM protocol (see the boot rom documentation) with a 16-bit
//       base address architecture (as opposed to 8-bits). The base address
//       of the code should be contained at address 0x0000 in the EEPROM.
//     - At boot, the internal osciallator will run at 10Mhz.  The boot ROM
//       will configure the DIVSEL to be /1 for a 10Mhz system clock.
//       This is due to a requirement that the I2C clock be between 7Mhz
//       and 12Mhz to meet all of the I2C specification timing requirements.
//       The I2CPSC default value is hardcoded to 0 so that the I2C
//       clock will not be divided down from the system clock.
//       The I2CPSC value can be modified after receiving
//       the first few bytes from the EEPROM (see the boot rom documentation),
//       but it is advisable not to, as this can cause the I2C to operate out
//       of specification with a system clock between 7Mhz and 12Mhz.
//     - The bit period prescalers (I2CCLKH and I2CCLKL) are configured to
//       run the I2C at 50% duty cycle at 100kHz bit rate (standard I2C mode)
//       when the system clock is 12Mhz. These registers can be modified after
//       receiving the first few bytes from the EEPROM (see the boot rom
//       documentation). This allows the communication to be increased up to
//       a 400kHz bit rate (fast I2C mode) during the remaining data reads.
//     - Arbitration, bus busy, and slave signals are not checked. Therefore,
//       no other master is allowed to control the bus during this
//       initialization phase. If the application requires another master
//       during I2C boot mode, that master must be configured to hold off
//       sending any I2C messages until the F280x application software
//       signals that it is past the bootloader portion of initialization.
//     - The non-acknowledgement bit is only checked during the first message
//       sent to initialize the EEPROM base address. This ensures that an
//       EEPROM is present at address 0x50 before continuing on. If an EEPROM
//       is not present, code will jump to the Flash entry point. The
//       non-acknowledgement bit is not checked during the address phase of
//       the data read messages (I2C_GetWord). If a non-acknowledge is
//       received during the data read messages, the I2C bus will hang.
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July 2015 $
//###########################################################################


#include "bootrom.h"


// Private functions
inline uint16_t I2C_CheckKeyVal(void);
inline void   I2C_ReservedFn(void);
uint16_t I2C_GetWord(void);

// External functions
extern void   CopyData(void);
extern uint32_t GetLongData(void);

void I2CBOOT_configure_gpio(uint32_t BootMode);

#define MODULE_CLOCK	BOOTROM_SYSCLK	//Frequency of I2C module operation
#define SCLA_CLOCK		100000U			//I2C bit rate frequency


/*
--------------------------------------------------
Opt No.|  BOOTDEF      |  SDAA      |  SCLA      |
--------------------------------------------------
  1    |  0x07(default)|  32        |  33        |
  2    |  0x27         |  19        |  18        |
  3    |  0x47         |  26        |  27        |
  4    |  0x67         |  42        |  43        |
--------------------------------------------------
*/

//#################################################
// uint32_t I2C_Boot(void)
//--------------------------------------------
// This module is the main I2C boot routine.
// It will load code via the I2C-A port.
//
// It will return an entry point address back
// to the ExitBoot routine.
//--------------------------------------------

uint32_t I2C_Boot(uint32_t  BootMode)
{
   uint32_t EntryAddr;

	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_5;
	if((EntryAddr != 0xFFFFFFFF) &&
			(EntryAddr != 0x00000000))
	{
	       /*if OTP is programmed, then call OTP function*/
	       ((void (*)(void))EntryAddr)();

		/*if OTP is not programmed with an entry point-go with default*/
	}

   if(SysCtl_isPeripheralPresent(SYSCTL_PERIPH_PRESENT_I2CA) == false)
   {
	   return 0xFFFFFFFF;
   }


   // Assign GetWordData to the I2C-A version of the
   // function.  GetWordData is a pointer to a function.
   GetWordData = I2C_GetWord;

   // Init I2C pins, clock, and registers
   // I2C_Init();
   //----------------------------------------------
   // Initialize the I2C-A port for communications
   // with the host.
   //----------------------------------------------
   // Configure I2C pins and turn on I2C clock
   EALLOW;
  // CpuSysRegs.PCLKCR9.bit.I2C_A = 1;	// Turn I2C module clock on
   SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);

   EDIS;


   //   I2caRegs.I2CSAR  = 0x0050;		// Slave address - EEPROM control code
   I2C_setSlaveAddress(I2CA_BASE, 0x0050);

   // Initialize I2C in master transmitter mode

   //   I2caRegs.I2CPSC.all = 0;		// I2C clock should be between 7Mhz-12Mhz
   //   I2caRegs.I2CCLKL = 43;			// Prescalers set for 100kHz bit rate
   //   I2caRegs.I2CCLKH = 43;			//   at a 10Mhz I2C clock

   //I2C input frequency (SYSCLKOUT)		 = 10 MHz (Device running out of INTOSC2)
   //I2C module frequency(Module clock) 	 = 10 MHz
   //I2C bit rate (in freq) (Output clock)	 = 100 KHz

   I2C_initMaster(I2CA_BASE,BOOTROM_SYSCLK,SCLA_CLOCK,I2C_DUTYCYCLE_50);


//   	I2caRegs.I2CMDR.all = 0x0620;	// Master transmitter
//   									// Take I2C out of reset
//   									// Stop when suspended

   I2C_setConfig(I2CA_BASE,(I2C_MASTER_SEND_MODE|I2C_MDR_IRS|I2C_BITCOUNT_8));


   //I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
   //I2caRegs.I2CFFRX.all = 0x2000;	// Enable RXFIFO
   I2C_enableFIFO(I2CA_BASE);

	//GPIO INIT
   I2CBOOT_configure_gpio(BootMode);

	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_5;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }


   // Check for 0x08AA data header, else go to flash
   if (I2C_CheckKeyVal() == ERROR) { return FLASH_ENTRY_POINT; }

   // Check for clock and prescaler speed changes and reserved words
   I2C_ReservedFn();
   EDIS;
   // Get point of entry address after load
   EntryAddr = GetLongData();

   // Receive and copy one or more code sections to  destination addresses
   CopyData();

   return EntryAddr;
}

//#################################################
// uint16_t I2C_CheckKeyVal(void)
//-----------------------------------------------
// This routine sets up the starting address in the
// EEPROM by writing two bytes (0x0000) via the
// I2C-A port to slave address 0x50. Without
// sending a stop bit, the communication is then
// restarted and two bytes are read from the EEPROM.
// If these two bytes read do not equal 0x08AA
// (little endian), an error is returned.
//-----------------------------------------------

inline uint16_t I2C_CheckKeyVal(void)
{
   // To read a word from the EEPROM, an address must be given first in
   // master transmitter mode. Then a restart is performed and data can
   // be read back in master receiver mode.
   //I2caRegs.I2CCNT = 0x02;				// Setup how many bytes to send
	I2C_setDataCount(I2CA_BASE, 0x02);

//   I2caRegs.I2CDXR = 0x00;				// Configure fifo data for byte
//   I2caRegs.I2CDXR = 0x00;				//   address of 0x0000
	I2C_putData(I2CA_BASE, 0x0);
    I2C_putData(I2CA_BASE, 0x0);

    //I2caRegs.I2CMDR.all = 0x2620;		// Send data to setup EEPROM address
    I2C_sendStartCondition(I2CA_BASE);


//   while (I2caRegs.I2CSTR.bit.ARDY == 0)
   while((I2C_getStatus(I2CA_BASE) & I2C_STR_ARDY) == 0)  // Wait until communication
   {									 				  // complete and registers ready
	   //I2caRegs.I2CMDR.all = 0x2620;					  // Send data to setup EEPROM address
   }

//   if (I2caRegs.I2CSTR.bit.NACK == 1)	// Set stop bit & return error if NACK received
   if(I2C_getStatus(I2CA_BASE) & I2C_STR_NACK)
   {
      //I2caRegs.I2CMDR.bit.STP = 1;
	   I2C_sendStopCondition(I2CA_BASE);
       return ERROR;
   }

   // Check to make sure key value received is correct
   if (I2C_GetWord() != 0x08AA) {return ERROR;}

   return NO_ERROR;
}


//#################################################
// void I2C_ReservedFn(void)
//-------------------------------------------------
// This function reads 8 reserved words in the header.
//   1st word - parameters for I2CPSC register
//   2nd word - parameters for I2CCLKH register
//   3rd word - parameters for I2CCLKL register
//
// The remaining reserved words are read and discarded
// and then program execution returns to the main routine.
//-------------------------------------------------

inline void I2C_ReservedFn(void)
{
   uint16_t I2CPrescaler;
   uint16_t I2cClkHData;
   uint16_t I2cClkLData;
   uint16_t i;

   // Get I2CPSC, I2CCLKH, and I2CCLKL values
   I2CPrescaler = I2C_GetWord();
   I2cClkHData  = I2C_GetWord();
   I2cClkLData  = I2C_GetWord();

   // Store I2C clock prescalers
   //I2caRegs.I2CMDR.bit.IRS = 0;
   I2C_disableModule(I2CA_BASE);

//   I2caRegs.I2CCLKL = I2cClkLData;
//   I2caRegs.I2CCLKH = I2cClkHData;
//   I2caRegs.I2CPSC.all = I2CPrescaler;
   HWREGH(I2CA_BASE + I2C_O_CLKL) = I2cClkLData;
   HWREGH(I2CA_BASE + I2C_O_CLKH) = I2cClkHData;
   HWREGH(I2CA_BASE + I2C_O_PSC)  = I2CPrescaler;

   //I2caRegs.I2CMDR.bit.IRS = 1;
   I2C_enableModule(I2CA_BASE);

   // Read and discard the next 5 reserved words
   for (i=1; i<=5; i++)
   {
      I2cClkHData = I2C_GetWord();
   }

   return;
}


//#################################################
// uint16_t I2C_GetWord(void)
//-----------------------------------------------
// This routine fetches two bytes from the I2C-A
// port and puts them together little endian style
// to form a single 16-bit value.
//-----------------------------------------------

uint16_t I2C_GetWord(void)
{
   uint16_t LowByte;

//   I2caRegs.I2CCNT = 2;					// Setup how many bytes to expect
   I2C_setDataCount(I2CA_BASE, 0x02);

   //I2caRegs.I2CMDR.all = 0x2C20;		// Send start as master receiver
   I2C_setConfig(I2CA_BASE,I2C_MASTER_RECEIVE_MODE);
   I2C_sendStartCondition(I2CA_BASE);
   I2C_sendStopCondition(I2CA_BASE);

   // Wait until communication done
   //while (I2caRegs.I2CMDR.bit.STP == 1) {}
   while(I2C_getStopConditionStatus(I2CA_BASE)){}

   // Combine two bytes to one word & return
   //LowByte = I2caRegs.I2CDRR;
   LowByte = I2C_getData(I2CA_BASE);
   //return (LowByte | (I2caRegs.I2CDRR<<8));
   return (LowByte | (I2C_getData(I2CA_BASE)<<8));
}


/*
--------------------------------------------------
Opt No.|  BOOTDEF      |  SDAA      |  SCLA      |
--------------------------------------------------
  1    |  0x07(default)|  32        |  33        |
  2    |  0x27         |  19        |  18        |
  3    |  0x47         |  26        |  27        |
  4    |  0x67         |  42        |  43        |
--------------------------------------------------
*/

void I2CBOOT_configure_gpio(uint32_t BootMode)
{
	//Unlock the GPIO configuration registers
	EALLOW;
	GPIO_unlockPortConfig(GPIO_PORT_A,0x00000000);
	GPIO_unlockPortConfig(GPIO_PORT_B,0x00000000);

	switch (BootMode)
	{
		case I2C_MASTER_BOOT:
		default:

			 //Enable pull up on GPIOs 32, 33 pins
			 GPIO_setPadConfig(32,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(33,GPIO_PIN_TYPE_PULLUP);

			 //GPIO32 = SDAA
			 //GPIO33 = SCLA
			 GPIO_setPinConfig(GPIO_32_SDAA);
			 GPIO_setPinConfig(GPIO_33_SCLA);

			 //Configure GPIOs 32, 33 pins as async pins
			 GPIO_setQualificationMode(32,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(33,GPIO_QUAL_ASYNC);
			 break;

		case I2C_MASTER_BOOT_ALT1:

			 //Enable pull up on GPIOs 19, 18 pins
			 GPIO_setPadConfig(19,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(18,GPIO_PIN_TYPE_PULLUP);

			 //GPIO19 = SDAA
			 //GPIO18 = SCLA
			 GPIO_setPinConfig(GPIO_19_SDAA);
			 GPIO_setPinConfig(GPIO_18_SCLA);

			 //Configure GPIOs 19, 18 pins as async pins
			 GPIO_setQualificationMode(19,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(18,GPIO_QUAL_ASYNC);
			 break;

		case I2C_MASTER_BOOT_ALT2:

			 //Enable pull up on GPIOs 26, 27 pins
			 GPIO_setPadConfig(26,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(27,GPIO_PIN_TYPE_PULLUP);

			 //GPIO26 = SDAA
			 //GPIO27 = SCLA
			 GPIO_setPinConfig(GPIO_26_SDAA);
			 GPIO_setPinConfig(GPIO_27_SCLA);

			 //Configure GPIOs 26, 27 pins as async pins
			 GPIO_setQualificationMode(26,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(27,GPIO_QUAL_ASYNC);
			 break;

		case I2C_MASTER_BOOT_ALT3:

			 //Enable pull up on GPIOs 42, 43 pins
			 GPIO_setPadConfig(42,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(43,GPIO_PIN_TYPE_PULLUP);

			 //GPIO42 = SDAA
			 //GPIO43 = SCLA
			 GPIO_setPinConfig(GPIO_42_SDAA);
			 GPIO_setPinConfig(GPIO_43_SCLA);

			 //Configure GPIOs 42, 43 pins as async pins
			 GPIO_setQualificationMode(42,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(43,GPIO_QUAL_ASYNC);
			 break;
	}
}

//===========================================================================
// No more.
//===========================================================================
