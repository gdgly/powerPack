// TI File $Revision: /main/6 $
// Checkin $Date: May 10, 2007   09:21:40 $
//###########################################################################
//
// FILE:   F2833x_Boot.h
//
// TITLE:  F2833x Boot ROM Definitions.
//
//###########################################################################
// $TI Release: 2833x Boot ROM Version 1 $
// $Release Date: June 25, 2007 $
//###########################################################################

#ifndef TMS320X2833X_BOOT_H
#define TMS320X2833X_BOOT_H

//---------------------------------------------------------------------------
// Fixed boot entry points:
//
#define FLASH_ENTRY_POINT 0x33FFF6
#define OTP_ENTRY_POINT   0x380400
#define RAM_ENTRY_POINT   0x000000
#define XINTF_ENTRY_POINT 0x100000
#define PASSWORD_LOCATION 0x33FFF6

#define XTIMING_X16_VAL   0x0043FFFF
#define XTIMING_X32_VAL   0x0041FFFF
#define XINTCNF2_VAL      0x00010D14
#define DIVSEL_BY_4             0
#define DIVSEL_BY_2             2
#define DIVSEL_BY_1             3


#define ERROR                   1
#define NO_ERROR                0
#define EIGHT_BIT               8
#define SIXTEEN_BIT            16
#define EIGHT_BIT_HEADER   0x08AA
#define SIXTEEN_BIT_HEADER 0x10AA

typedef Uint16 (* uint16fptr)();
extern uint16fptr GetWordData;

#endif  // end of TMS320x2833x_BOOT_H definition
