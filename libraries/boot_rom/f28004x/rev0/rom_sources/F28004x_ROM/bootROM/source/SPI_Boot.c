//###########################################################################
//
// FILE:    SPI_Boot.c
//
// TITLE:   SPI Boot mode routines
//
// Functions:
//
//     uint32_t SPI_Boot(void)
//     uint16_t SPIA_SetAddress_KeyChk(void)
//     inline void SPIA_Transmit(u16 cmdData)
//     inline void SPIA_ReservedFn(void);
//     uint32_t SPIA_GetWordData(void)
//
// Notes:
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July 2015 $
//###########################################################################

#include "bootrom.h"

#define SPI_BIT_RATE		 19531U

#define SPI_CHARACTER_LENGTH 8

// Private functions
inline uint16_t SPIA_Transmit(uint16_t cmdData);
inline void SPIA_ReservedFn(void);
uint16_t SPIA_GetWordData(void);
uint16_t SPIA_SetAddress_KeyChk(void);

// External functions
extern void CopyData(void);
uint32_t GetLongData(void);
uint32_t SPI_start_Boot(void);

void SPIA_Init(void);

void SPIBOOT_configure_gpio(uint32_t BootMode);

/*
----------------------------------------------------------------------------
Opt No.|  BOOTDEF      |  SPISIMOA  |  SPISOMIA  |  SPICLKA   |  SPISTEA   |
----------------------------------------------------------------------------
  1    |  0x06(default)|  16        |  17        |  18        |  19        |
  2    |  0x26         |  8         |  10        |  9         |  11        |
  3    |  0x46         |  54        |  55        |  56        |  57        |
  4    |  0x66         |  16        |  17        |  56        |  57        |
  5    |  0x86         |  8         |  17        |  9         |  11        |
----------------------------------------------------------------------------
*/

//#################################################
// uint32_t SPI_Boot(void)
//--------------------------------------------
// This module is the main SPI boot routine.
// It will load code via the SPI-A port.
//
// It will return a entry point address back
// to the ExitBoot routine.
//--------------------------------------------

uint32_t SPI_Boot(uint32_t  BootMode)
{
   uint32_t EntryAddr;

	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_7;
	if((EntryAddr != 0xFFFFFFFF) &&
			(EntryAddr != 0x00000000))
	{
	       /*if OTP is programmed, then call OTP function*/
	       ((void (*)(void))EntryAddr)();

		/*if OTP is not programmed with an entry point-go with default*/
	}

   if(SysCtl_isPeripheralPresent(SYSCTL_PERIPH_PRESENT_SPIA) == false)
   {
	   return 0xFFFFFFFF;
   }

   // Asign GetWordData to the SPI-A version of the
   // function.  GetWordData is a pointer to a function.
   GetWordData = SPIA_GetWordData;
   // 1. Init SPI-A and set
   //    EEPROM chip enable - low

   SPIA_Init();

   SPIBOOT_configure_gpio(BootMode);

	//GPIO INIT
	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_7;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }




	return SPI_start_Boot();
}

uint32_t SPI_start_Boot()
{
   uint32_t EntryAddr;

	// 2. Enable EEPROM and send EEPROM Read Command
   SPIA_Transmit(0x0300);
   // 3. Send Starting Address for Serial EEPROM (16-bit - 0x0000,0000)
   //    or Serial Flash (24-bit - 0x0000,0000,0000)
   //    Then check for 0x08AA data header, else go to flash
   if(SPIA_SetAddress_KeyChk() != 0x08AA) return FLASH_ENTRY_POINT;
   // 4.Check for Clock speed change and reserved words
   SPIA_ReservedFn();
   // 5. Get point of entry address after load
   EntryAddr = GetLongData();
   // 6. Receive and copy one or more code sections to  destination addresses
   CopyData();
   // 7. Disable EEPROM chip enable - high
   //    Chip enable - high
   //GpioDataRegs.GPASET.bit.GPIO19 = 1;
   GPIO_writePin(19, 1);

   return EntryAddr;
}

//#################################################
// uint16_t SPIA_SetAddress_KeyChk(void)
//-----------------------------------------------
// This routine sends either a 16-bit address to
// Serial EEPROM or a 24-bit address to Serial
// FLASH. It then fetches the 2 bytes that make
// up the key value  from the SPI-A port and
// puts them together to form a single
// 16-bit value.  It is assumed that the host is
// sending the data in the form MSB:LSB.
//-----------------------------------------------

uint16_t SPIA_SetAddress_KeyChk()
{
   uint16_t keyValue;
   // Transmit first byte of Serial Memory address
   SPIA_Transmit(0x0000);
   // Transmit second byte of  Serial Memory address
   SPIA_Transmit(0x0000);
  // Transmit third byte of  Serial Memory address (0x00) if using Serial Flash
  // or receive first byte of key value if using Serial EEPROM.
   keyValue = SPIA_Transmit(0x0000);
  // If previously received LSB of key value (Serial EEPROM), then fetch MSB of key value
   if (keyValue == 0x00AA)
   {
       keyValue |= (SPIA_Transmit(0x0000)<<8);
   }
   else
   {
   // Serial Flash is being used - keyValue will be received after 24-bit address in the next 2 bytes
   // Fetch Key Value LSB (after 24-bit addressing)
       keyValue = SPIA_Transmit(0x0000);
   // Fetch Key Value MSB (after 24-bit addressing)
       keyValue |= (SPIA_Transmit(0x0000)<<8);
   }
   return keyValue;
}


//#################################################
// uint16_t SPIA_Transmit(uint16_t cmdData)
//------------------------------------------------
// Send a byte/words through SPI transmit channel
//------------------------------------------------

inline uint16_t SPIA_Transmit(uint16_t cmdData)
{
    uint16_t recvData;

    //SpiaRegs.SPITXBUF = cmdData;
    SPI_writeDataNonBlocking(SPIA_BASE,cmdData);
    //while( (SpiaRegs.SPISTS.bit.INT_FLAG) !=1);
    while(SPI_getInterruptStatus(SPIA_BASE) != SPI_INT_RX_DATA_TX_EMPTY);
    //recvData = SpiaRegs.SPIRXBUF;
    recvData = SPI_readDataNonBlocking(SPIA_BASE);
    return recvData;
}

//#################################################
// void SPIA_ReservedFn(void)
//-------------------------------------------------
// This function reads 8 reserved words in the header.
// The first word has parameters for LOSPCP
// and SPIBRR register 0xMSB:LSB, LSB = is a three
// bit field for LOSPCP change MSB = is a 6bit field
// for SPIBRR register update
//
// If either byte is the default value of the register
// then no speed change occurs.  The default values
// are LOSPCP = 0x02 and SPIBRR = 0x7F
// The remaining reserved words are read and discarded
// and then returns to the main routine.
//-------------------------------------------------

inline void SPIA_ReservedFn()
{
    uint16_t speedData;
    uint16_t i;

    // update LOSPCP register
    speedData = SPIA_Transmit((uint16_t)0x0000);
    EALLOW;
    //ClkCfgRegs.LOSPCP.all = speedData;
    HWREG(CLKCFG_BASE + SYSCTL_O_LOSPCP) = speedData;
    EDIS;
    asm("   RPT #0x0F ||NOP");

    // update SPIBRR register
    speedData = SPIA_Transmit((uint16_t)0x0000);
    //SpiaRegs.SPIBRR  = speedData;
	HWREGH(SPIA_BASE + SPI_O_BRR) = speedData;

    asm("   RPT #0x0F ||NOP");

    // Read and discard the next 7 reserved words.
    for(i = 1; i <= 7; i++)
    {
       SPIA_GetWordData();
    }
    return;
}

//#################################################
// uint16_t SPIA_GetWordData(void)
//-----------------------------------------------
// This routine fetches two bytes from the SPI-A
// port and puts them together to form a single
// 16-bit value.  It is assumed that the host is
// sending the data in the form MSB:LSB.
//-----------------------------------------------

uint16_t SPIA_GetWordData()
{
   uint16_t wordData;
   // Fetch the LSB
   wordData =  SPIA_Transmit(0x0000);
   // Fetch the MSB
   wordData |= (SPIA_Transmit(0x0000) << 8);
   return wordData;
}


/*
----------------------------------------------------------------------------
Opt No.|  BOOTDEF      |  SPISIMOA  |  SPISOMIA  |  SPICLKA   |  SPISTEA   |
----------------------------------------------------------------------------
  1    |  0x06(default)|  16        |  17        |  18        |  19        |
  2    |  0x26         |  8         |  10        |  9         |  11        |
  3    |  0x46         |  54        |  55        |  56        |  57        |
  4    |  0x66         |  16        |  17        |  56        |  57        |
  5    |  0x86         |  8         |  17        |  9         |  11        |
----------------------------------------------------------------------------
*/

void SPIBOOT_configure_gpio(uint32_t BootMode)
{
	//Unlock the GPIO configuration registers
	EALLOW;
	GPIO_unlockPortConfig(GPIO_PORT_A,0x00000000);
	GPIO_unlockPortConfig(GPIO_PORT_B,0x00000000);

	switch (BootMode)
	{
		case SPI_MASTER_BOOT:
		default:

			 //Enable pull up on GPIOs 16,17,18,19  pins
			 GPIO_setPadConfig(16,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(17,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(18,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(19,GPIO_PIN_TYPE_PULLUP);

			 //GPIO16 = SPISIMOA
			 //GPIO17 = SPISOMIA
			 //GPIO18 = SPICLKA
			 GPIO_setPinConfig(GPIO_16_SPISIMOA);
			 GPIO_setPinConfig(GPIO_17_SPISOMIA);
			 GPIO_setPinConfig(GPIO_18_SPICLKA);

			 //GPIO19 = SPISTEA (configured as GPIO output pin)
			 GPIO_setDirectionMode(19,GPIO_DIR_MODE_OUT);

			 //Configure GPIOs 16, 17, 18 pins as async pins
			 GPIO_setQualificationMode(16,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(17,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(18,GPIO_QUAL_ASYNC);

			 //pull GPIO19 low(SPISTEA) to enable Chip Select
			 GPIO_writePin(19,0);
			 break;

		case SPI_MASTER_BOOT_ALT1:

			//Enable pull up on GPIOs 8,10,9,11  pins
			 GPIO_setPadConfig(8,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(10,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(9,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(11,GPIO_PIN_TYPE_PULLUP);

			 //GPIO08 = SPISIMOA
			 //GPIO10 = SPISOMIA
			 //GPIO09 = SPICLKA
			 GPIO_setPinConfig(GPIO_8_SPISIMOA);
			 GPIO_setPinConfig(GPIO_10_SPISOMIA);
			 GPIO_setPinConfig(GPIO_9_SPICLKA);

			 //GPIO11 = SPISTEA (configured as GPIO output pin)
			 GPIO_setDirectionMode(11,GPIO_DIR_MODE_OUT);

			 //Configure GPIOs 8, 10, 9 pins as async pins
			 GPIO_setQualificationMode(8,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(10,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(9,GPIO_QUAL_ASYNC);

			 //pull GPIO11 low(SPISTEA) to enable Chip Select
			 GPIO_writePin(11,0);
			 break;

		case SPI_MASTER_BOOT_ALT2:

			 //Enable pull up on GPIOs 54,55,56,57  pins
			 GPIO_setPadConfig(54,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(55,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(56,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(57,GPIO_PIN_TYPE_PULLUP);

			 //GPIO54 = SPISIMOA
			 //GPIO55 = SPISOMIA
			 //GPIO56 = SPICLKA
			 GPIO_setPinConfig(GPIO_54_SPISIMOA);
			 GPIO_setPinConfig(GPIO_55_SPISOMIA);
			 GPIO_setPinConfig(GPIO_56_SPICLKA);

			 //GPIO57 = SPISTEA (configured as GPIO output pin)
			 GPIO_setDirectionMode(57,GPIO_DIR_MODE_OUT);

			 //Configure GPIOs 54, 55, 56 pins as async pins
			 GPIO_setQualificationMode(54,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(55,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(56,GPIO_QUAL_ASYNC);

			 //pull GPIO57 low(SPISTEA) to enable Chip Select
			 GPIO_writePin(57,0);
			 break;

		case SPI_MASTER_BOOT_ALT3:

			 //Enable pull up on GPIOs 16,17,56,57  pins
			 GPIO_setPadConfig(16,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(17,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(56,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(57,GPIO_PIN_TYPE_PULLUP);

			 //GPIO16 = SPISIMOA
			 //GPIO17 = SPISOMIA
			 //GPIO56 = SPICLKA
			 GPIO_setPinConfig(GPIO_16_SPISIMOA);
			 GPIO_setPinConfig(GPIO_17_SPISOMIA);
			 GPIO_setPinConfig(GPIO_56_SPICLKA);

			 //GPIO57 = SPISTEA (configured as GPIO output pin)
			 GPIO_setDirectionMode(57,GPIO_DIR_MODE_OUT);

			 //Configure GPIOs 16, 17, 56 pins as async pins
			 GPIO_setQualificationMode(16,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(17,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(56,GPIO_QUAL_ASYNC);

			 //pull GPIO57 low(SPISTEA) to enable Chip Select
			 GPIO_writePin(57,0);
			 break;

		case SPI_MASTER_BOOT_ALT4:

			 //Enable pull up on GPIOs 8,17,9,11  pins
			 GPIO_setPadConfig(8,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(17,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(9,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(11,GPIO_PIN_TYPE_PULLUP);

			 //GPIO08 = SPISIMOA
			 //GPIO17 = SPISOMIA
			 //GPIO09 = SPICLKA
			 GPIO_setPinConfig(GPIO_8_SPISIMOA);
			 GPIO_setPinConfig(GPIO_17_SPISOMIA);
			 GPIO_setPinConfig(GPIO_9_SPICLKA);

			 //GPIO11 = SPISTEA (configured as GPIO output pin)
			 GPIO_setDirectionMode(11,GPIO_DIR_MODE_OUT);

			 //Configure GPIOs 8, 17, 9 pins as async pins
			 GPIO_setQualificationMode(8,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(17,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(9,GPIO_QUAL_ASYNC);

			 //pull GPIO11 low(SPISTEA) to enable Chip Select
			 GPIO_writePin(11,0);
			 break;
	}

}


void SPIA_Init(void)
{
	//----------------------------------------------
	// Initialize the SPI-A port for communications
	// with the host.
	//----------------------------------------------

	// Enable SPI-A clocks
	 EALLOW;
	 //CpuSysRegs.PCLKCR8.bit.SPI_A = 1;
	   SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);

	 //ClkCfgRegs.LOSPCP.all = 0x0002;
	  SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);

	 // Enable FIFO reset bit only (FIFO can resume transmit/receive operation)
	 //SpiaRegs.SPIFFTX.all=0x8000;
	  HWREGH(SPIA_BASE + SPI_O_FFTX) = SPI_FFTX_SPIRST;

      SPI_disableModule(SPIA_BASE);
	  SPI_setConfig(SPIA_BASE,(BOOTROM_SYSCLK/4),SPI_PROT_POL0PHA1,SPI_MODE_MASTER,SPI_BIT_RATE,SPI_CHARACTER_LENGTH);
      SPI_enableModule(SPIA_BASE);


/*
	 // 8-bit character
	 //SpiaRegs.SPICCR.all = 0x0007;
	  HWREGH(SPIA_BASE + SPI_O_CCR) = 0x0007;


	 // Use internal SPICLK master mode and Talk mode
	 //SpiaRegs.SPICTL.all = 0x000E;
	  HWREGH(SPIA_BASE + SPI_O_CTL) = 0x000E;

	 // Use the slowest baud rate
	 //SpiaRegs.SPIBRR     = 0x007f;
	  HWREGH(SPIA_BASE + SPI_O_BRR) = 0x007F;

	 // Relinquish SPI-A from reset
	 //SpiaRegs.SPICCR.all = 0x0087;
	  HWREGH(SPIA_BASE + SPI_O_CCR) = 0x0087;
*/
	 EDIS;
}


