/*--------------------------------------------------------*/
/* F021\Init.h                                            */
/* F021 Flash API v1.56                                   */
/*--------------------------------------------------------*/

// $TI Release: F28004x Support Library v1.01.00.00 $
// $Release Date: Mon May 22 15:39:38 CDT 2017 $
// $Copyright:
// Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
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

#pragma once

/*!
    \file F021\Init.h
    \brief 
*/
#ifndef FAPI_INIT_H_
#define FAPI_INIT_H_

typedef struct 
{
   Fapi_TiOtpBytesType   *m_poTiOtpBaseAddress;
   Fapi_FmcRegistersType *m_poFlashControlRegisters;
   uint8 m_u8MainBankWidth;
   uint8 m_u8EeBankWidth;
   uint8 m_u8MainEccWidth;
   uint8 m_u8EeEccWidth;
   uint8 m_u8CurrentRwait;
   uint8 m_u8CurrentEwait;
   uint16 m_u16HclkFrequency;
} Fapi_InitStruct;

#endif /* FAPI_FLASH_STATE_MACHINE_H_ */
