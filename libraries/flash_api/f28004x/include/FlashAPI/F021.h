/*--------------------------------------------------------*/
/* F021\F021.h                                            */
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

/*!
    \file F021\F021.h
    \brief Main include file for F021 devices.
*/
#ifndef F021_H_
#define F021_H_

#include "Registers.h"
#include "Init.h"
#include "Constants/Constants.h"

#if !defined(F021)
   #define F021
#endif

/* Flash C API functions*/

/* Flash State Machine commands */
extern Fapi_FlashStatusType Fapi_getFsmStatus(void);

extern Fapi_StatusType Fapi_checkFsmForReady(void);

extern Fapi_StatusType Fapi_setActiveFlashBank(Fapi_FlashBankType oFlashBank);

extern Fapi_StatusType Fapi_connectFlashPumpToCpu(Fapi_CpuSelectorType oFlashCpu);

extern Fapi_StatusType Fapi_enableBanksForOtpWrite(uint8 u8Banks);

extern Fapi_StatusType Fapi_disableBanksForOtpWrite(void);

extern Fapi_StatusType Fapi_issueFsmSuspendCommand(void);

extern Fapi_StatusType Fapi_writeEwaitValue(uint32 u32Ewait);

extern void Fapi_flushPipeline(void);

/* Device Family Dependent FSM commands */
extern uint32 * Fapi_remapEccAddress(uint32 u32EccAddress);

extern boolean Fapi_isAddressEcc(uint32 u32Address);

/* Async Commands */
extern Fapi_StatusType Fapi_issueAsyncCommandWithAddress(
                                                        Fapi_FlashStateCommandsType oCommand,
                                                        uint32 *pu32StartAddress
                                                        );

extern Fapi_StatusType Fapi_issueAsyncCommand(Fapi_FlashStateCommandsType oCommand);

/* Info Commands */
extern Fapi_LibraryInfoType Fapi_getLibraryInfo(void);
extern Fapi_DeviceInfoType Fapi_getDeviceInfo(void);
extern Fapi_StatusType Fapi_getBankSectors(Fapi_FlashBankType oBank, Fapi_FlashBankSectorsType *poFlashBankSectors );

/* Init */
extern Fapi_InitStruct Fapi_GlobalInit;
extern Fapi_StatusType Fapi_initializeAPI(
                                         Fapi_FmcRegistersType *poFlashControlRegister,
                                         uint32 u32HclkFrequency
                                         );

/* Read commands */
extern Fapi_StatusType Fapi_doBlankCheck(
                                        uint32 *pu32StartAddress,
                                        uint32 u32Length,
                                        Fapi_FlashStatusWordType *poFlashStatusWord
                                        );

extern Fapi_StatusType Fapi_doMarginRead(
                                        uint32 *pu32StartAddress,
                                        uint32 *pu32ReadBuffer,
                                        uint32 u32Length,
                                        Fapi_FlashReadMarginModeType oReadMode
                                        );

extern Fapi_StatusType Fapi_doVerify(
                                    uint32 *pu32StartAddress,
                                    uint32 u32Length,
                                    uint32 *pu32CheckValueBuffer,
                                    Fapi_FlashStatusWordType *poFlashStatusWord
                                    );

extern Fapi_StatusType Fapi_doVerifyBy16bits(
                             uint16 *pu16StartAddress,
                             uint32 u16Length,
                             uint16 *pu16CheckValueBuffer,
                             Fapi_FlashStatusWordType *poFlashStatusWord
                             );

extern uint32 Fapi_calculatePsa(
                                uint32 *pu32StartAddress,
                                uint32 u32Length,
                                uint32 u32PsaSeed,
                                Fapi_FlashReadMarginModeType oReadMode
                               );

extern Fapi_StatusType Fapi_doPsaVerify(
                                       uint32 *pu32StartAddress,
                                       uint32 u32Length,
                                       uint32 u32PsaValue,
                                       Fapi_FlashStatusWordType *poFlashStatusWord
                                       );

extern Fapi_StatusType Fapi_doBlankCheckByByte(
                                              uint8 *pu8StartAddress,
                                              uint32 u32Length,
                                              Fapi_FlashStatusWordType *poFlashStatusWord
                                              );

extern Fapi_StatusType Fapi_doMarginReadByByte(
                                              uint8 *pu8StartAddress,
                                              uint8 *pu8ReadBuffer,
                                              uint32 u32Length,
                                              Fapi_FlashReadMarginModeType oReadMode
                                              );

extern Fapi_StatusType Fapi_doVerifyByByte(
                                          uint8 *pu8StartAddress,
                                          uint32 u32Length,
                                          uint8 *pu8CheckValueBuffer,
                                          Fapi_FlashStatusWordType *poFlashStatusWord
                                          );

/* Programming Commands */
#if defined(_C28X)
extern Fapi_StatusType Fapi_issueProgrammingCommand(
                                            uint32 *pu32StartAddress,
                                            uint16 *pu16DataBuffer,
                                            uint16  u16DataBufferSizeInWords,
                                            uint16 *pu16EccBuffer,
                                            uint16  u16EccBufferSizeInBytes,
                                            Fapi_FlashProgrammingCommandsType oMode
                                            );

extern Fapi_StatusType Fapi_issueProgrammingCommandForEccAddresses(
                                                           uint32 *pu32StartAddress,
                                                           uint16 *pu16EccBuffer,
                                                           uint16 u16EccBufferSizeInBytes
                                                           );
#else
extern Fapi_StatusType Fapi_issueProgrammingCommand(
                                                   uint32 *pu32StartAddress,
                                                   uint8  *pu8DataBuffer,
                                                   uint8  u8DataBufferSizeInBytes,
                                                   uint8  *pu8EccBuffer,
                                                   uint8  u8EccBufferSizeInBytes,
                                                   Fapi_FlashProgrammingCommandsType oMode
                                                   );

extern Fapi_StatusType Fapi_issueProgrammingCommandForEccAddresses(
                                                                  uint32 *pu32StartAddress,
                                                                  uint8 *pu8EccBuffer,
                                                                  uint8 u8EccBufferSizeInBytes
                                                                  );
#endif

/* Utility Commands */
extern uint32 Fapi_calculateFletcherChecksum(
                                            uint16 const * pu16Data,
                                            uint16 u16Length
                                            );

extern uint8 Fapi_calculateEcc(
                               uint32 u32Address,
                               uint64 u64Data
                               );

/* User Defined Functions */
extern Fapi_StatusType Fapi_serviceWatchdogTimer(void);
extern Fapi_StatusType Fapi_setupEepromSectorEnable(void);
extern Fapi_StatusType Fapi_setupBankSectorEnable(void);

#endif /*F021_H_*/
