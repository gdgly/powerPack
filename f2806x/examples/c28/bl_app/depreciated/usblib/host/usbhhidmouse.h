//###########################################################################
//
// FILE:   usbhhidmouse.h
//
// TITLE:  This file holds the application interfaces for USB
//         mouse devices.
//
//###########################################################################
// $TI Release: F2806x Support Library v2.02.00.00 $
// $Release Date: Mon May 22 15:42:15 CDT 2017 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __USBHHIDMOUSE_H__
#define __USBHHIDMOUSE_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! @{
//
//*****************************************************************************

    extern unsigned long USBHMouseOpen(tUSBCallback pfnCallback,
                                       unsigned char *pucBuffer,
                                       unsigned long ulBufferSize);
    extern unsigned long USBHMouseClose(unsigned long ulInstance);
    extern unsigned long USBHMouseInit(unsigned long ulInstance);

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif


