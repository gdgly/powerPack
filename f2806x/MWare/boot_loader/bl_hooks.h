//###########################################################################
//
// bl_hooks.h - Definitions for the application-specific hook function.
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

#ifndef __BL_HOOKS_H__
#define __BL_HOOKS_H__

//*****************************************************************************
//
// Prototypes for any application-specific hook functions that are defined in
// bl_config.h.  
//
//*****************************************************************************
#ifdef BL_HW_INIT_FN_HOOK
extern void BL_HW_INIT_FN_HOOK(void);
#endif
#ifdef BL_INIT_FN_HOOK
extern void BL_INIT_FN_HOOK(void);
#endif
#ifdef BL_REINIT_FN_HOOK
extern void BL_REINIT_FN_HOOK(void);
#endif
#ifdef BL_START_FN_HOOK
extern void BL_START_FN_HOOK(void);
#endif
#ifdef BL_PROGRESS_FN_HOOK
extern void BL_PROGRESS_FN_HOOK(unsigned long ulCompleted,
                                unsigned long ulTotal);
#endif
#ifdef BL_END_FN_HOOK
extern void BL_END_FN_HOOK(void);
#endif
#ifdef BL_DECRYPT_FN_HOOK
extern void BL_DECRYPT_FN_HOOK(unsigned char *pucBuffer, unsigned long ulSize);
#endif
#ifdef BL_CHECK_UPDATE_FN_HOOK
extern unsigned long BL_CHECK_UPDATE_FN_HOOK(void);
#endif

//*****************************************************************************
//
// If ENABLE_DECRYPTION is defined but we don't have a hook function set for
// decryption, default to the previous behavior which calls the stub function
// DecryptData.
//
//*****************************************************************************
#if (defined ENABLE_DECRYPTION) && !(defined BL_DECRYPT_FN_HOOK)
#define BL_DECRYPT_FN_HOOK      DecryptData
#endif

#endif // __BL_HOOKS_H__

//
// End of File
//

