//###########################################################################
//
// bl_sym.h - Miscellaneous externs and symbol definitions needed by the 
//            bootloader
//
//###########################################################################
// $TI Release: F2806x Support Library v2.02.00.00 $
// $Release Date: Mon May 22 15:42:15 CDT 2017 $
// $Copyright:
// Copyright (C) 2009-2017 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef __BL_APP_H__
#define __BL_APP_H__

//*****************************************************************************
//
// Basic functions for erasing and programming internal flash.
//
//*****************************************************************************

extern void * pAppSig;
extern void * pAppEntry;

extern Uint16 BLTableStart;
extern Uint16 BLTableEnd;
extern Uint16 BLTableSize;
extern Uint16 InitLoadStart;
extern Uint16 InitLoadEnd;
extern Uint16 InitLoadSize;
extern void * code_start_n;
extern Uint16 CodeStart_n_Start;
extern Uint16 CodeStart_n_End;

#ifdef ENABLE_FAILSAFE
extern Uint16 FailsafeLoadStart;
extern Uint16 FailsafeLoadEnd;
extern Uint16 FailsafeLoadSize;
extern Uint16 FailsafeRunStart;
extern void * code_start_f;
extern Uint16 CodeStart_f_Start;
extern Uint16 CodeStart_f_End;
extern void FailSafeMemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr,
                            Uint16* DestAddr);
#endif

#endif // __BL_APP_H__

//
// End of File
//

