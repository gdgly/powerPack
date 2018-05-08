//###########################################################################
//
// FILE:    DCAN_Boot.c
//
// TITLE:   DCAN boot loader file
//
// Functions:
//
//
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July 2015 $
//###########################################################################

//DCAN boot loader functions for Soprano

#include "bootrom.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_can.h"
#include "inc/hw_gpio.h"

//Default bit timing settings for 100 kbps with a 20 MHz crystal
#define CAN_CALC_BITRATE   100000ul
#define CAN_CALC_CANCLK    20000000ul
#define CAN_CALC_BITTIME   25ul
#include "../include/CAN_Timing_Calc.h"

//Available GPIOs:
//
//BOOTDEFx[7:5] CANTXA CANRXA MUX-TX MUX-RX
//000           32     33     A      A
//001            4      5     3      3
//010           31     30     1      1
//011           37     35     6      5

/*
--------------------------------------------------
Opt No.|  BOOTDEF      |  CANATX    |  CANARX    |
--------------------------------------------------
  1    |  0x02(default)|  32        |  33        |
  2    |  0x22         |  04        |  05        |
  3    |  0x42         |  31        |  30        |
  4    |  0x62         |  37        |  35        |
--------------------------------------------------
*/

//BOOTDEFx[7] will be used to enable a test mode where the boot loader sends
//two frames on startup.
#define DCAN_BOOT_SENDTEST      0x80

//Function prototypes
extern void CopyData(void);
static void DCAN_Boot_GPIO(uint32_t pinSelect);
static void DCAN_Boot_Init(uint32_t btrReg, uint16_t switchToXTAL);
static uint16_t DCAN_GetWordData(void);
static void DCAN_SendWordData(uint16_t data);
static void DCAN_ParseReservedWords(void);


uint32_t DCAN_Boot(uint32_t bootMode, uint32_t bitTimingRegValue, uint16_t switchToXTAL)
{
	uint32_t EntryAddr = FLASH_ENTRY_POINT;

	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_8;
	if((EntryAddr != 0xFFFFFFFF) &&
	          (EntryAddr != 0x00000000))
	{
	       /*if OTP is programmed, then call OTP function*/
	       ((void (*)(void))EntryAddr)();
	}

	//If DCAN-A is not enabled, bypass the boot loader
    if(SysCtl_isPeripheralPresent(SYSCTL_PERIPH_PRESENT_CANA) == false)
    {
	   return 0xFFFFFFFF;
    }


	//Assign the DCAN data reader function to the global
	//function pointer for loading data.
	GetWordData = &DCAN_GetWordData;

	//Set up the GPIO mux for the chosen pinout
	DCAN_Boot_GPIO(bootMode);

	//Set up the DCAN to receive data. Pass the user-provided bit timing
	//register value if one was provided, otherwise pass the default for
	//100 kbps with a 20 MHz crystal.
	if (bitTimingRegValue == 0)
		bitTimingRegValue = CAN_CALC_BTRREG;
	DCAN_Boot_Init(bitTimingRegValue, switchToXTAL);

	//Escape point for OTP patches
	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_8;

	if((EntryAddr != 0xFFFFFFFF) &&
	          (EntryAddr != 0x00000000))
	{
	       /*if OTP is programmed, then call OTP function*/
	       ((void (*)(void))EntryAddr)();
	}

	//Send two tests frames if the boot mode says so
	if (bootMode & DCAN_BOOT_SENDTEST)
	{
		DCAN_SendWordData(0x0320);
		DCAN_SendWordData(0xf280);
	}

	//The first data word should be a valid key. If it's not,
	//bypass the bootloader.
	if (DCAN_GetWordData() != 0x08AA)
		return FLASH_ENTRY_POINT;

	//Use the shared utility functions to load the data.
	DCAN_ParseReservedWords();
	EntryAddr = GetLongData();
	CopyData();

	return EntryAddr;
}

/*
--------------------------------------------------
Opt No.|  BOOTDEF      |  CANATX    |  CANARX    |
--------------------------------------------------
  1    |  0x02(default)|  32        |  33        |
  2    |  0x22         |   4        |   5        |
  3    |  0x42         |  31        |  30        |
  4    |  0x62         |  37        |  35        |
--------------------------------------------------
*/


//Configure the peripheral mux to connect DCAN-A to the chosen GPIOs
static void DCAN_Boot_GPIO(uint32_t BootMode)
{
	//Unlock the GPIO configuration registers
	EALLOW;
	HWREG(GPIOCTRL_BASE + GPIO_O_GPALOCK) = 0x00000000;
	HWREG(GPIOCTRL_BASE + GPIO_O_GPBLOCK) = 0x00000000;

	//Decode the GPIO selection, then set up the mux and configure the inputs
	//for asynchronous qualification.
	switch (BootMode)
	{
		case CAN_BOOT:
		case CAN_BOOT_SENDTEST:
		default:
			 //Enable pull up on GPIOs 32, 33 pins
			 GPIO_setPadConfig(32,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(33,GPIO_PIN_TYPE_PULLUP);

			 //GPIO32 = CANATX
			 //GPIO33 = CANARX
			 GPIO_setPinConfig(GPIO_32_CANTXA);
			 GPIO_setPinConfig(GPIO_33_CANRXA);

			 //Configure GPIOs 32, 33 pins as async pins
			 GPIO_setQualificationMode(32,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(33,GPIO_QUAL_ASYNC);

			 break;

		case CAN_BOOT_ALT1:
		case CAN_BOOT_ALT1_SENDTEST:
			 //Enable pull up on GPIOs 4, 5 pins
			 GPIO_setPadConfig(4,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(5,GPIO_PIN_TYPE_PULLUP);

			 //GPIO4 = CANATX
			 //GPIO5 = CANARX
			 GPIO_setPinConfig(GPIO_4_CANTXA);
			 GPIO_setPinConfig(GPIO_5_CANRXA);

			 //Configure GPIOs 4, 5 pins as async pins
			 GPIO_setQualificationMode(4,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(5,GPIO_QUAL_ASYNC);

			 break;

		case CAN_BOOT_ALT2:
		case CAN_BOOT_ALT2_SENDTEST:
			 //Enable pull up on GPIOs 31, 30 pins
			 GPIO_setPadConfig(31,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(30,GPIO_PIN_TYPE_PULLUP);

			 //GPIO31 = CANATX
			 //GPIO30 = CANARX
			 GPIO_setPinConfig(GPIO_31_CANTXA);
			 GPIO_setPinConfig(GPIO_30_CANRXA);

			 //Configure GPIOs 31, 30 pins as async pins
			 GPIO_setQualificationMode(31,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(30,GPIO_QUAL_ASYNC);

			 break;

		case CAN_BOOT_ALT3:
		case CAN_BOOT_ALT3_SENDTEST:
			 //Enable pull up on GPIOs 37, 35 pins
			 GPIO_setPadConfig(37,GPIO_PIN_TYPE_PULLUP);
			 GPIO_setPadConfig(35,GPIO_PIN_TYPE_PULLUP);

			 //GPIO37 = CANATX
			 //GPIO35 = CANARX
			 GPIO_setPinConfig(GPIO_37_CANTXA);
			 GPIO_setPinConfig(GPIO_35_CANRXA);

			 //Configure GPIOs 37, 35 pins as async pins
			 GPIO_setQualificationMode(37,GPIO_QUAL_ASYNC);
			 GPIO_setQualificationMode(35,GPIO_QUAL_ASYNC);

			 break;

	}

	EDIS;
}

//Initialize the DCAN-A module and configure its bit clock and message objects
static void DCAN_Boot_Init(uint32_t btrReg, uint16_t switchToXTAL)
{
	//Select XTAL for OSCCLK and the CAN bit clock and set the SYSCLK divider to /1
	EALLOW;
	if (switchToXTAL)
	{
	    //Turn on XTAL and select crystal mode
	    HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_OSCOFF;
	    HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_SE;

	    //Wait for the X1 clock to saturate
	    HWREG(CLKCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
	    while(HWREGH(CLKCFG_BASE + SYSCTL_O_X1CNT) != 0x3FFU) {;}

		HWREG(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &= ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M;
		HWREG(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |= 0x1ul;
		asm(" RPT #16 || NOP");
		HWREG(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL2) &= ~SYSCTL_CLKSRCCTL2_CANABCLKSEL_M;
		HWREG(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL2) |= 0x1ul << SYSCTL_CLKSRCCTL2_CANABCLKSEL_S;
		HWREG(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) = 0x0;
	}

	//Turn on the clock to the DCAN-A module
	HWREG(CPUSYS_BASE + SYSCTL_O_PCLKCR10) |= SYSCTL_PCLKCR10_CAN_A;
	EDIS;

	//Put the CAN module into initialization mode, then issue a software reset
	//via the self-clearing SWR bit.
	HWREG(CANA_BASE + CAN_O_CTL) = (0x5ul << CAN_CTL_PMD_S) | CAN_CTL_INIT;
	asm(" RPT #16 || NOP");
	EALLOW;
	HWREG(CANA_BASE + CAN_O_CTL) |= CAN_CTL_SWR;
	EDIS;
	asm(" RPT #16 || NOP");

	//Initialize the CAN message RAM
	HWREG(CANA_BASE + CAN_O_RAM_INIT) = CAN_RAM_INIT_CAN_RAM_INIT | 0xa;
	while ((HWREG(CANA_BASE + CAN_O_RAM_INIT) & CAN_RAM_INIT_RAM_INIT_DONE) != CAN_RAM_INIT_RAM_INIT_DONE) {;}

	//Enable config register access, set up the bit timing, and make sure
	//parity stays enabled.
	HWREG(CANA_BASE + CAN_O_CTL) = (0xAul << CAN_CTL_PMD_S) | CAN_CTL_CCE | CAN_CTL_INIT;
	HWREG(CANA_BASE + CAN_O_BTR) = btrReg;

	//Set up a receive message object via interface 1, then transfer it to the
	//message RAM.
	HWREG(CANA_BASE + CAN_O_IF1ARB) = CAN_IF1ARB_MSGVAL | (0x1ul << 18ul);
	HWREG(CANA_BASE + CAN_O_IF1MCTL) = CAN_IF1MCTL_EOB | (2ul << CAN_IF1MCTL_DLC_S);
	HWREG(CANA_BASE + CAN_O_IF1MSK) = 0xffffffff;
	HWREG(CANA_BASE + CAN_O_IF1CMD) = CAN_IF1CMD_DIR | CAN_IF1CMD_MASK | CAN_IF1CMD_ARB | CAN_IF1CMD_CONTROL | CAN_IF1CMD_CLRINTPND | 1ul;
	while (HWREG(CANA_BASE + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) {;}

	//Set up a transmit object via interface 2 for debug, then transfer it to
	//the message RAM.
	HWREG(CANA_BASE + CAN_O_IF2ARB) = CAN_IF2ARB_MSGVAL | CAN_IF2ARB_DIR | (0x2ul << 18ul);
	HWREG(CANA_BASE + CAN_O_IF2MCTL) = CAN_IF2MCTL_EOB | (2ul << CAN_IF2MCTL_DLC_S);
	HWREG(CANA_BASE + CAN_O_IF2MSK) = 0xffffffff;
	HWREG(CANA_BASE + CAN_O_IF2CMD) = CAN_IF2CMD_DIR | CAN_IF2CMD_MASK | CAN_IF2CMD_ARB | CAN_IF2CMD_CONTROL | CAN_IF2CMD_CLRINTPND | 2ul;
	while (HWREG(CANA_BASE + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY) {;}

	//Leave inititalization mode and disable timing register access and
	//automatic retransmission.
	HWREGH(CANA_BASE + CAN_O_CTL) &= ~(CAN_CTL_CCE | CAN_CTL_INIT);
}

//Read 16 bits from an incoming DCAN message sent to ID #1. If no message has
//been received, wait for one to arrive.
static uint16_t DCAN_GetWordData(void)
{
	//Wait for a new CAN message to be received in mailbox 1
	while ((HWREG(CANA_BASE + CAN_O_NDAT_21) & 0x1ul) != 0x1ul) {;}

	//Read the message object via IF1 and return the data
	HWREG(CANA_BASE + CAN_O_IF1CMD) = CAN_IF1CMD_TXRQST | CAN_IF1CMD_DATA_A | CAN_IF1CMD_DATA_B | 1ul;
	asm(" RPT #2 || NOP");
	while (HWREG(CANA_BASE + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) {;}
	return HWREGH(CANA_BASE + CAN_O_IF1DATA);
}

//Send a CAN message to ID #2 for external testing and data rate measurement.
//Wait for the transmission to complete.
static void DCAN_SendWordData(uint16_t data)
{
	HWREG(CANA_BASE + CAN_O_IF2DATA) = data;
	HWREG(CANA_BASE + CAN_O_IF2CMD) = CAN_IF2CMD_DIR | CAN_IF2CMD_TXRQST | CAN_IF2CMD_DATA_A | CAN_IF2CMD_DATA_B | 2ul;
	asm(" RPT #255 || NOP");
	while (HWREGH(CANA_BASE + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY) {;}
	while (HWREGH(CANA_BASE + CAN_O_TXRQ_21) & 0x2ul) {;}
}

//Parse the eight reserved words and check whether there's a new bit timing
//register value in the first pair.
static void DCAN_ParseReservedWords(void)
{
	uint32_t newBtrReg;
	uint16_t word;

	//Read the new bit timing value, LSW first
	newBtrReg = DCAN_GetWordData();
	newBtrReg |= (uint32_t)DCAN_GetWordData() << 16ul;

	//Skip the rest of the reserved words
	for (word = 3; word <= 8; word++)
	{
		DCAN_GetWordData();
	}

	//If a new bit timing value was received, switch to the new settings
	if (newBtrReg != 0x00000000)
	{
		DCAN_Boot_Init(newBtrReg, 0);
	}
}
