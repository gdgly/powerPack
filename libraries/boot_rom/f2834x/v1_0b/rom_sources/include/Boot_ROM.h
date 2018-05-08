// TI File $Revision: /main/1 $
// Checkin $Date: May 30, 2008   14:11:43 $
//###########################################################################
//
// FILE:   Boot_ROM.h
//
// TITLE:  Boot ROM Definitions.
//
//###########################################################################
// $TI Release: 2834x Boot ROM V1b $
// $Release Date: June 3, 2008 $
//###########################################################################

#ifndef BOOT_ROM_H
#define BOOT_ROM_H


#include "DSP2834x_Device.h"

//---------------------------------------------------------------------------
// Fixed boot entry points:
//
#define TI_TEST_R_ENTRY_POINT 0x33F000
#define RAM_ENTRY_POINT       0x000000
#define XINTF_ENTRY_POINT     0x100000
#define PASSWORD_LOCATION     0x33FFF6

#define XTIMING_X16_VAL       0x0043FFFF
#define XTIMING_X32_VAL       0x0041FFFF
#define XINTCNF2_VAL          0x00090D14
#define DIVSEL_BY_8             0
#define DIVSEL_BY_4             1
#define DIVSEL_BY_2             2
#define DIVSEL_BY_1             3

#define TIMING1                 1
#define TIMING2                 2

#define ERROR                   1
#define NO_ERROR                0
#define EIGHT_BIT               8
#define SIXTEEN_BIT            16
#define EIGHT_BIT_HEADER   0x08AA
#define SIXTEEN_BIT_HEADER 0x10AA

#define TI_TEST_EN  ((*(unsigned int *)0x09c0) & 0x0001)

typedef Uint16 (* uint16fptr)();
extern uint16fptr GetWordData;
extern Uint16 BootMode;

extern Uint32 SCI_Boot(void);
extern Uint32 SPI_Boot(void);
extern Uint32 Parallel_Boot(void);
extern Uint32 XINTF_Parallel_Boot(void);
extern Uint32 I2C_Boot(Uint16);
extern Uint32 CAN_Boot(Uint16);
extern Uint32 MCBSP_Boot();
extern Uint32 XINTF_Boot(Uint16 size);

extern void WatchDogEnable(void);
extern void WatchDogDisable(void);
extern void WatchDogService(void);
extern void WatchDogReset(void);
extern void InitPll(Uint16 val, Uint16 divsel);

extern void   CopyData(void);
extern Uint32 GetLongData(void);
extern void   ReadReservedFn(void);
extern void   TI_Test(void);

#endif  // end of BOOT_ROM_H definition
