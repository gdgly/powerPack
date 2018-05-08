// TI File $Revision: /main/6 $
// Checkin $Date: May 9, 2007   15:09:19 $
//###########################################################################
//
// FILE:    Parallel_Boot.c    
//
// TITLE:   2833x XINTF Parallel Port I/O boot routines
//
// Functions:
//
//       Uint32 XINTF_Parallel_Boot(void)        
//       inline void XINTF_Parallel_GPIOSelect(void)
//       inline Uint16 XINTF_Parallel_CheckKeyVal(void)
//       Uint16 XINTF_Parallel_GetWordData_8bit()
//       Uint16 XINTF_Parallel_GetWordData_16bit()
//       void XINTF_Parallel_WaitHostRdy(void)
//       void XINTF_Parallel_HostHandshake(void)
// Notes:
//
//###########################################################################
// $TI Release: 2833x Boot ROM Version 1 $
// $Release Date: June 25, 2007 $
//###########################################################################


#include "DSP2833x_Device.h"
#include "TMS320x2833x_Boot.h"

// Private function definitions
inline void XINTF_Parallel_GPIOSelect(void);
inline Uint16 XINTF_Parallel_CheckKeyVal(void);
Uint16 XINTF_Parallel_GetWordData_8bit(void);
Uint16 XINTF_Parallel_GetWordData_16bit(void);
void XINTF_Parallel_WaitHostRdy(void);
void XINTF_Parallel_HostHandshake(void);
void XINTF_Parallel_ReservedFn(void);

// External function definitions
extern void CopyData(void);
extern Uint32 GetLongData(void);
extern void InitPll(Uint16 val, Uint16 divsel);

#define HOST_CTRL          GPIO13  // GPIO13 is the host control signal
#define DSP_CTRL           GPIO12  // GPIO12 is the DSP's control signal

#define HOST_DATA_NOT_RDY  GpioDataRegs.GPADAT.bit.HOST_CTRL!=0
#define WAIT_HOST_ACK      GpioDataRegs.GPADAT.bit.HOST_CTRL!=1

// Set (DSP_ACK) or Clear (DSP_RDY) GPIO 12
#define DSP_ACK            GpioDataRegs.GPASET.bit.DSP_CTRL = 1;
#define DSP_RDY            GpioDataRegs.GPACLEAR.bit.DSP_CTRL = 1;
#define DATA               (Uint16 *)0x100000

//#################################################
// Uint32 XINTF_Parallel_Boot(void)
//--------------------------------------------
// This module is the main XINTF Parallel boot routine. 
// It will load code via XD[15:0].  
//
// This boot mode accepts 8-bit or 16-bit data. 
// 8-bit data is expected to be the order LSB
// followed by MSB.
//
// This function returns a entry point address back
// to the InitBoot routine which in turn calls
// the ExitBoot routine. 
//--------------------------------------------

Uint32 XINTF_Parallel_Boot()
{

   Uint32 EntryAddr;
   // Setup for Parallel boot
   XINTF_Parallel_GPIOSelect();
   // Check for the key value.  Based on this the data will
   // be read as 8-bit or 16-bit values. 
   if (XINTF_Parallel_CheckKeyVal() == ERROR) return FLASH_ENTRY_POINT;
   // Read and discard the reserved words
   XINTF_Parallel_ReservedFn();
   // Get the entry point address
   EntryAddr = GetLongData(); 
   // Load the data
   CopyData();
    
   return EntryAddr;

}

//#################################################
// void Parallel_GPIOSelect(void)
//------------------------------------------
// Enable I/O pins for input GPIO 15:0.  Also 
// enable the control pins for HOST_CTRL and 
// DSP_CTRL.
//------------------------------------------

inline void XINTF_Parallel_GPIOSelect()
{
    EALLOW;

    // enable clock to XINTF module
    SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;
    
    // GPIO64-GPIO79 (XD0-XD15)
    GpioCtrlRegs.GPCMUX1.all = 0xAAAAAAAA;   
  
    // GPIO80-GPIO87 (XA8-XA15)
    // (top half of this register is reserved)
    GpioCtrlRegs.GPCMUX2.all = 0x0000AAAA;
  
    // XZCS6n, XA17-XA19   
    GpioCtrlRegs.GPAMUX2.all |= 0xF0000000;
  
    // XREADYn, XRNW, XWE0n, XA16, XA0-XA7
    GpioCtrlRegs.GPBMUX1.all |= 0xFFFF00F0;
    
    // Use the default XINTF timing
    XintfRegs.XTIMING6.all = XTIMING_X16_VAL;
    XintfRegs.XINTCNF2.all = XINTCNF2_VAL; 

    GpioCtrlRegs.GPAMUX1.bit.DSP_CTRL = 0;  // GPIO
	GpioCtrlRegs.GPAPUD.bit.DSP_CTRL = 0;   // Pullup enabled
	GpioDataRegs.GPASET.bit.DSP_CTRL = 1;   // Set the pin high to start
    GpioCtrlRegs.GPADIR.bit.DSP_CTRL = 1;   // Output

    GpioCtrlRegs.GPAMUX1.bit.HOST_CTRL = 0; // GPIO
	GpioCtrlRegs.GPAPUD.bit.HOST_CTRL = 0;  // Pullup enabled
    GpioCtrlRegs.GPADIR.bit.HOST_CTRL = 0;  // Input

    EDIS;
}

//#################################################
// void XINTF_Parallel_CheckKeyVal(void)
//-----------------------------------------
// Determine if the data we are loading is in 
// 8-bit or 16-bit format. 
// If neither, return an error. 
//
// Note that if the host never responds then
// the code will be stuck here.  That is there
// is no timeout mechanism.
//------------------------------------------
inline Uint16 XINTF_Parallel_CheckKeyVal()
{

   Uint16 wordData;
   
   // Fetch a word from the parallel port and compare
   // it to the defined 16-bit header format, if not check
   // for a 8-bit header format.
      
   wordData = XINTF_Parallel_GetWordData_16bit();

   if(wordData == SIXTEEN_BIT_HEADER) 
   {
   // Asign GetWordData to the parallel 16bit version of the
   // function.  GetWordData is a pointer to a function.
      GetWordData = XINTF_Parallel_GetWordData_16bit;
      return SIXTEEN_BIT;
   }
   // If not 16-bit mode, check for 8-bit mode
   // Call Parallel_GetWordData with 16-bit mode 
   // so we only fetch the MSB of the KeyValue and not
   // two bytes.  We will ignore the upper 8-bits and combine
   // the result with the previous byte to form the
   // header KeyValue.
   
   wordData = wordData & 0x00FF;
   wordData |= XINTF_Parallel_GetWordData_16bit() << 8;
   if(wordData == EIGHT_BIT_HEADER) 
   {
   // Asign GetWordData to the parallel 8bit version of the
   // function.  GetWordData is a pointer to a function.
      GetWordData = XINTF_Parallel_GetWordData_8bit;
      return EIGHT_BIT;
   }
   // Didn't find a 16-bit or an 8-bit KeyVal header so return an error.
   else return ERROR;
}

//#################################################
// Uint16 XINTF_Parallel_GetWordData_16bit()
// Uint16 XINTF_Parallel_GetWordData_8bit()
//-----------------------------------------------
// This routine fetches a 16-bit word from the 
// first address in XINTF zone 6.  The 16bit 
// function is used if the input 16-bits and the
// function fetches a signle word and returns it to the host.
//  
// The _8bit function is used if the input stream is 
// an 8-bit input stream and the upper 8-bits of the 
// XD lines are ignored.  In the 8-bit case the 
// first fetches the LSB and then the MSB from the 
// XINTF address. These two bytes are then put together to
// form a single 16-bit word that is then passed back
// to the host. Note that in this case, the input stream
// from the host is in the order LSB followed by MSB
//-----------------------------------------------
Uint16 XINTF_Parallel_GetWordData_8bit()
{
   Uint16 wordData;
     
   // Get LSB.  
   
   XINTF_Parallel_WaitHostRdy();
   wordData = *DATA;
   XINTF_Parallel_HostHandshake();
   
   // Fetch the MSB.
   
   wordData = wordData & 0x00FF;
   XINTF_Parallel_WaitHostRdy();
   wordData |= (*DATA << 8);
   XINTF_Parallel_HostHandshake();
   return wordData;
}


Uint16 XINTF_Parallel_GetWordData_16bit()
{
   Uint16 wordData;
     
   // Get a word of data.  If we are in
   // 16-bit mode then we are done.
   
   XINTF_Parallel_WaitHostRdy();
   wordData = *DATA;
   XINTF_Parallel_HostHandshake();
   return wordData;
}

//#################################################
// void XINTF_Parallel_WaitHostRdy(void)
//-----------------------------------------------------
// This routine tells the host that the DSP is ready to 
// recieve data.  The DSP then waits for the host to 
// signal that data is ready on the GP I/O port.e 
//-----------------------------------------------------
void XINTF_Parallel_WaitHostRdy()
{
   DSP_RDY;
   while(HOST_DATA_NOT_RDY) { }
}

//#################################################
// void XINTF_Parallel_HostHandshake(void)
//-----------------------------------------------------
// This routine tells the host that the DSP has recieved
// the data.  The DSP then waits for the host to acknowledge
// the reciept before continuing.  
//-----------------------------------------------------
void XINTF_Parallel_HostHandshake()
{
   DSP_ACK;
   while(WAIT_HOST_ACK) { }
}

//#################################################
// void XINTF_Parallel_ReservedFn(void)
//-------------------------------------------------
// This function reads 8 reserved words in the header.
// The first 6 words are as follows:
//
// PLLCR
// PLLSTS
// XTIMING6[31:16]
// XTIMING6[15:0]
// XINTCNF2[31:16]
// XINTCNF2[15:0]
//
// The remaining reserved words are read and discarded
// and then returns to the main routine.
//-------------------------------------------------

void XINTF_Parallel_ReservedFn(void)
{
    Uint16 pllcr, divsel;
	Uint32 xtiming6, xintcnf2;
    Uint16 i;

    pllcr    = GetWordData();   // word 1
    divsel   = GetWordData();   // word 2
    xtiming6 = GetLongData();   // word 3 & 4
    xintcnf2 = GetLongData();   // word 5 & 6

    InitPll(pllcr,divsel);
    
    EALLOW;
    if (xtiming6 != 0) XintfRegs.XTIMING6.all = xtiming6;
	if (xintcnf2 != 0) XintfRegs.XINTCNF2.all = xintcnf2;  
    EDIS;

    // Read and discard the next 2 reserved words.
    for(i = 1; i <= 2; i++)
    {
       GetWordData();
    }
    return;
}

// EOF --------
