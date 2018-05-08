//###########################################################################
//
// FILE:    Parallel_Boot.c    
//
// TITLE:   Parallel Port I/O boot routines
//
// Functions:
//
//       uint32_t Parallel_Boot(void)
//       inline void Parallel_GPIOSelect(void)
//       inline uint16_t Parallel_CheckKeyVal(void)
//       uint16_t Parallel_GetWordData_8bit()
//       uint16_t Parallel_GetWordData_16bit()
//       void Parallel_WaitHostRdy(void)
//       void Parallel_HostHandshake(void)
// Notes:
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July 2015 $
//###########################################################################


#include "bootrom.h"


// Private function definitions
uint16_t Parallel_GetWordData_8bit(void);

// External function definitions
extern void CopyData(void);
extern uint32_t GetLongData(void);
extern void ReadReservedFn(void);

//D0-D7	GPIO [7:0]
//DSP Control	GPIO 16
//HOST Control	GPIO 12

/*
BOOTDEF = 0x0 (Only option available)

------------------
Bit0	 |	GPIO0	(Configured as Input pin)
Bit1	 |	GPIO1	(Configured as Input pin)
Bit2	 |	GPIO2	(Configured as Input pin)
Bit3	 |	GPIO3	(Configured as Input pin)
Bit4	 |	GPIO4	(Configured as Input pin)
Bit5	 |	GPIO5	(Configured as Input pin)
Bit6	 |	GPIO6	(Configured as Input pin)
Bit7	 |	GPIO7	(Configured as Input pin)

HOST_CTRL|	GPIO12	(Configured as Input pin)
DSP_CTRL |	GPIO16	(Configured as Output pin)
------------------
*/


#define HOST_CTRL          12  // GPIO12 is the host control signal (will be configured as input pin)
#define DSP_CTRL           16  // GPIO16 is the DSP's control signal (will be configured as output pin)

#define HOST_DATA_NOT_RDY  (GPIO_readPin(12) != 0)
#define WAIT_HOST_ACK      (GPIO_readPin(12) != 1)

// Set (DSP_ACK) or Clear (DSP_RDY) GPIO69
#define DSP_ACK            GPIO_writePin(16, 1) //GpioDataRegs.GPCSET.bit.DSP_CTRL = 1;
#define DSP_RDY            GPIO_writePin(16, 0) //GpioDataRegs.GPCCLEAR.bit.DSP_CTRL = 1;
#define DATA               (GPIO_readPortData(GPIO_PORT_A) & 0xFF) //(HWREG(GPIODATA_BASE + GPIO_O_GPADAT) & 0xFF)

void Parallel_GPIOSelect(void);

//#################################################
// uint32_t Parallel_Boot(void)
//--------------------------------------------
// This module is the main Parallel boot routine. 
// It will load code via GP I/Os.  
//
// This boot mode accepts 8-bit data. 
// 8-bit data is expected to be the order LSB
// followed by MSB.
//
// This function returns a entry point address back
// to the InitBoot routine which in turn calls
// the ExitBoot routine. 
//--------------------------------------------

uint32_t Parallel_Boot()
{

   uint32_t EntryAddr;
   uint16_t wordData;
   
   // Setup for Parallel boot
    Parallel_GPIOSelect();

   // Check for the key value. This version only 
   // supports 8-bit data.
   GetWordData = Parallel_GetWordData_8bit;   
   wordData = GetWordData(); 
   if(wordData != BROM_EIGHT_BIT_HEADER) return FLASH_ENTRY_POINT;
   // Read and discard the reserved words
   ReadReservedFn();
   // Get the entry point address
   EntryAddr = GetLongData(); 
   // Load the data
   CopyData();
    
   return EntryAddr;

}

//#################################################
// uint16_t Parallel_GetWordData_8bit()/
// The _8bit function is used if the input stream is 
// an 8-bit input stream and the upper 8-bits of the 
// GP I/O port are ignored.  In the 8-bit case the 
// first fetches the LSB and then the MSB from the 
// GPIO port.  These two bytes are then put together to
// form a single 16-bit word that is then passed back
// to the host. Note that in this case, the input stream
// from the host is in the order LSB followed by MSB
//-----------------------------------------------
uint16_t Parallel_GetWordData_8bit()
{
   uint16_t wordData;
     
   // Get LSB.  
   // Parallel_WaitHostRdy();
   // This routine tells the host that the DSP is ready to 
   // recieve data.  The DSP then waits for the host to 
   // signal that data is ready on the GP I/O port. 
   DSP_RDY;
   while(HOST_DATA_NOT_RDY) { }

   wordData = DATA;
  
  // Parallel_HostHandshake();
  // This routine tells the host that the DSP has recieved
  // the data.  The DSP then waits for the host to acknowledge
  // the reciept before continuing.  
   DSP_ACK;
   while(WAIT_HOST_ACK) { }

   // Fetch the MSB.
   wordData = wordData & 0x00FF;
  
   // Parallel_WaitHostRdy();
   // This routine tells the host that the DSP is ready to 
   // recieve data.  The DSP then waits for the host to 
   // signal that data is ready on the GP I/O port. 
   DSP_RDY;
   while(HOST_DATA_NOT_RDY) { }
   
   wordData |= (DATA << 8);
      
  // Parallel_HostHandshake();
  // This routine tells the host that the DSP has recieved
  // the data.  The DSP then waits for the host to acknowledge
  // the reciept before continuing.  
   DSP_ACK;
   while(WAIT_HOST_ACK) {} 
      
   return wordData;
}

void Parallel_GPIOSelect(void)
{

//    GPIO0         Bit 0 (will be configured as input pin)
//    GPIO1         Bit 1 (will be configured as input pin)
//    GPIO2         Bit 2 (will be configured as input pin)
//    GPIO3         Bit 3 (will be configured as input pin)
//    GPIO4         Bit 4 (will be configured as input pin)
//    GPIO5         Bit 5 (will be configured as input pin)
//    GPIO6         Bit 6 (will be configured as input pin)
//    GPIO7         Bit 7 (will be configured as input pin)

//    GPIO12		 HOST_CTRL (will be configured as input pin)
// 	  GPIO16 		 DSP_CTRL  (will be configured as output pin)

 EALLOW;

 HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD)   &= (uint32_t) 0xFFFFFF00; 	// Enable pullups on GPIO0-7

 /* Configure GPIO0-GPIO7, GPIO12 and GPIO 16 as GPIO*/

 HWREG(GPIOCTRL_BASE + GPIO_O_GPAMUX1)  &= (uint32_t) 0xFCFF0000; 	// gpio0-7, gpio12
 HWREG(GPIOCTRL_BASE + GPIO_O_GPAGMUX1) &= (uint32_t) 0xFCFF0000;	// gpio0-7, gpio12
 HWREG(GPIOCTRL_BASE + GPIO_O_GPAMUX2)  &= (uint32_t) 0xFFFFFFFC;	// gpio16
 HWREG(GPIOCTRL_BASE + GPIO_O_GPAGMUX2) &= (uint32_t) 0xFFFFFFFC;	// gpio16

 // HOST_CTRL is an input control from the Host
	// to the DSP Ack/Rdy
 // - may require an external pull-up
 // DSP_CTRL is an output from the DSP Ack/Rdy
	// - may require an external pull-up for host to
	// correctly read "1" initially.
	// DSP_CTRL set to 1 initially
 // 0 = input   1 = output

 /* Configure GPIO0-GPIO7, GPIO12 as input*/
 HWREG(GPIOCTRL_BASE + GPIO_O_GPADIR)	&= (uint32_t) 0xFFFFEF00;
 /*configure GPIO16 as output)*/
 HWREG(GPIOCTRL_BASE + GPIO_O_GPADIR)   |= (uint32_t) 0x00010000;

 EDIS;

}

// EOF --------



