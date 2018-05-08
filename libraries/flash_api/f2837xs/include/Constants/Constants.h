/*--------------------------------------------------------*/
/* F021\Constants\Constants.h                             */
/*                                                        */
/* $Release Date: Mon May 22 15:44:59 CDT 2017 $                                      */
/* $Copyright:
// Copyright (C) 2014-2017 Texas Instruments Incorporated - http://www.ti.com/
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
// $                                         */  
/*                                                        */
/* F021 Flash API v1.55                                   */
/*--------------------------------------------------------*/

/*!
    \file F021\Constants\Constants.h
    \brief A set of Constant Values.
*/
#ifndef F021_CONSTANTS_H_
#define F021_CONSTANTS_H_

#if defined(_CONCERTO)
    #include "Concerto.h"
#elif defined(_F2837xD)
    #include "F2837xD.h"
#elif defined(_F2837xS)
    #include "F2837xS.h"	
#elif defined(_F28004x)
    #include "F28004x.h"	
#else
    #include "FMC.h"
#endif


#if defined (_F2837xS)
	/*!
		\brief Define to map the direct access to the TI OTP memory.
	*/
	#define F021_TIOTP1_BASE_ADDRESS ((Fapi_TiOtpBytesType *)(F021_PROGRAM_TIOTP1_OFFSET + F021_TIOTP_SETTINGS_BASE))
	#define F021_TIOTP2_BASE_ADDRESS ((Fapi_TiOtpBytesType *)(F021_PROGRAM_TIOTP2_OFFSET + F021_TIOTP_SETTINGS_BASE))
	#define F021_TIOTP_BASE_ADDRESS ((Fapi_TiOtpBytesType *)(F021_PROGRAM_TIOTP_OFFSET + F021_TIOTP_SETTINGS_BASE))
	
	/*!
		\brief Define to map the direct access to the FMC registers.
	*/
	#define F021_CPU0_W0_BASE_ADDRESS ((Fapi_FmcRegistersType *)F021_CPU0_W0_REGISTER_ADDRESS)
	#define F021_CPU0_W1_BASE_ADDRESS ((Fapi_FmcRegistersType *)F021_CPU0_W1_REGISTER_ADDRESS)

#else
/*!
		\brief Define to map the direct access to the TI OTP memory.
	*/
	#define F021_TIOTP_BASE_ADDRESS ((Fapi_TiOtpBytesType *)(F021_PROGRAM_TIOTP_OFFSET + F021_TIOTP_SETTINGS_BASE))

	/*!
		\brief Define to map the direct access to the FMC registers.
	*/
	#define F021_CPU0_BASE_ADDRESS ((Fapi_FmcRegistersType *)F021_CPU0_REGISTER_ADDRESS)
	
#endif

#endif /* F021_CONSTANTS_H_ */
