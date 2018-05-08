//###########################################################################
//
// bl_config.h - The configurable parameters of the boot loader.
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

#ifndef __BL_CONFIG_H__
#define __BL_CONFIG_H__

//
// Included Files
//
#include "DSP28x_Project.h"

//*****************************************************************************
//
// The following defines are used to configure the operation of the boot
// loader.  For each define, its interactions with other defines are described.
// First is the dependencies (i.e. the defines that must also be defined if it
// is defined), next are the exclusives (i.e. the defines that can not be
// defined if it is defined), and finally are the requirements (i.e. the
// defines that must be defined if it is defined).
//
//*****************************************************************************

//*****************************************************************************
//
// The frequency of the crystal used to clock the microcontroller.
//
// This defines the crystal frequency used by the microcontroller running the
// boot loader.  
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define CRYSTAL_FREQ            20000000

//*****************************************************************************
//
// The starting address of the application.  
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define APP_START_ADDRESS       0x003DA000

//*****************************************************************************
//
// The ending address of the application.  
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define APP_END_ADDRESS            0x003F7F80

//*****************************************************************************
//
// The size of a single, erasable page in the flash.  This must be a power
// of 2.  The default value of 32KB (16K Words) represents the page size for 
// the internal flash on all C2000 MCUs.
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define FLASH_PAGE_SIZE         0x00004000

//*****************************************************************************
//
// The starting address of flash.  
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define FLASH_START_ADDR        0x003D8000UL

//*****************************************************************************
//
// The ending address of flash.  
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define FLASH_END_ADDR          0x003F8000UL

//*****************************************************************************
//
// Enables watchdog timer
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
//#define ENABLE_WATCHDOG

//*****************************************************************************
//
// Enables CSM Lock/Unlock mechanism based on a seed key exchange.
//
// Due to export restrictions this feature has been removed from the public
// release of the F2806x USB Bootloader.  If you are interested in this please 
// contact TI via email or the e2e forums.
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
//#define ENABLE_CSM_CONTROL
//
//#ifdef ENABLE_CSM_CONTROL
//#include "third_party/aes/aes.h"
//
//#if KEY_FORM & KEY_PRESET
//#include "enc_key.h"
//#endif
//
//#define PWL0    0xFFFF
//#define PWL1    0xFFFF
//#define PWL2    0xFFFF
//#define PWL3    0xFFFF
//#define PWL4    0xFFFF
//#define PWL5    0xFFFF
//#define PWL6    0xFFFF
//#define PWL7    0xFFFF
//
//#endif

//*****************************************************************************
//
// Enables reading of flash contents when the device is unlocked.  Commercial
// users of this bootloader may wish to comment this out to prevent code from
// being copied out of the device.
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define ENABLE_READ

//*****************************************************************************
//
// Enables checking of linker generated CRC tables within the application
// before the application is booted.
// Note: Depending on how the VCU library is built either the VCU or CPU
//       can be used to perform the CRC calculation.
//
// Depends on: None
// Exclusive of: None
// Requires: C28x_VCU_LIB
//
//*****************************************************************************
#define ENABLE_CRC_CHECK

//*****************************************************************************
//
// Enables CRC Table generation at runtime instead of statically linking the
// tables into flash.  CRC Tables are only needed if the CPU is calculating 
// the CRC.
//
// Depends on: ENABLE_CRC_CHECK
// Exclusive of: ENABLE_VCU
// Requires: C28x_VCU_LIB
//
//*****************************************************************************
//#define GEN_CRC_TABLES

//*****************************************************************************
//
// Enables the VCU for CRC checking.
//
// Depends on: ENABLE_CRC_CHECK
// Exclusive of: GEN_CRC_TABLES
// Requires: C28x_VCU_LIB
//
//*****************************************************************************
#define ENABLE_VCU

//*****************************************************************************
//
// Enables bootloader relocation.  During erasure the bootloader will 
// relocate itself in flash, to prevent bricking should power be removed.
// This does NOT make the bootloader un-brickable as the bootloader can be 
// corrupted if power is removed when the reset vector is being programmed.
// Enabling this mode also ensures code security as all of application flash 
// is erased before sector A (where CSM resides) is erased.
//
// Note: When building the bootloader with the failsafe option, the rts2800_bl
//       runtime support library should be used.  Otherwise the normal rts
//       library should be used to build the bootloader.
//
// Depends on: None
// Exclusive of: None
// Requires: rts2800_bl.lib
//
//*****************************************************************************
//#define ENABLE_FAILSAFE

//*****************************************************************************
//
// Enables the call to decrypt the downloaded data before writing it into
// flash.  The decryption routine is empty in the reference boot loader source,
// which simply provides a placeholder for adding an actual decrypter.
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
//#define ENABLE_DECRYPTION
//
//#ifdef ENABLE_DECRYPTION
//#include "third_party/aes/aes.h"
//
//#if KEY_FORM & KEY_PRESET
//#include "dec_key.h"
//#endif
//
//#endif

//*****************************************************************************
//
// Enables the pin-based forced update check.  When enabled, the boot loader
// will go into update mode instead of calling the application if a pin is read
// at a particular polarity, forcing an update operation.  In either case, the
// application is still able to return control to the boot loader in order to
// start an update.
//
// Depends on: None
// Exclusive of: None
// Requires: FORCED_UPDATE_PERIPH, FORCED_UPDATE_PORT, FORCED_UPDATE_PIN,
//           FORCED_UPDATE_POLARITY
//
//*****************************************************************************
#define ENABLE_UPDATE_CHECK

//*****************************************************************************
//
// The GPIO direction register to use to setup the pin direction (either: 
// GpioCtrlRegs.GPADIR.all or GpioCtrlRegs.GPBDIR.all).
//
// Depends on: ENABLE_UPDATE_CHECK
// Exclusive of: None
// Requries: None
//
//*****************************************************************************
#define FORCED_UPDATE_DIR_REG    GpioCtrlRegs.GPADIR.all

//*****************************************************************************
//
// The GPIO data register to check for pin state (either: 
// GpioDataRegs.GPADAT.all or GpioDataRegs.GPBDAT.all)
//
// Depends on: ENABLE_UPDATE_CHECK
// Exclusive of: None
// Requries: None
//
//*****************************************************************************
#define FORCED_UPDATE_DATA_REG      GpioDataRegs.GPADAT.all

//*****************************************************************************
//
// This enables a weak pull up for the GPIO pin used in a forced update.  Tl
//
// Depends on: ENABLE_UPDATE_CHECK
// Exclusive of: None
// Requries: None
//
//*****************************************************************************
#define FORCED_UPDATE_WPU

//*****************************************************************************
//
// The pin to check for a forced update.  This is a value between 0 and 64.
//
// Depends on: ENABLE_UPDATE_CHECK
// Exclusive of: None
// Requries: None
//
//*****************************************************************************
#define FORCED_UPDATE_PIN       33

//*****************************************************************************
//
// The polarity of the GPIO pin that results in a forced update.  This value
// should be 0 if the pin should be low and 1 if the pin should be high.
//
// Depends on: ENABLE_UPDATE_CHECK
// Exclusive of: None
// Requries: None
//
//*****************************************************************************
#define FORCED_UPDATE_POLARITY  0

//*****************************************************************************
//
// The USB vendor ID published by the DFU device.  This value is the TI
// Stellaris vendor ID.  Change this to the vendor ID you have been assigned by
// USB-IF.
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define USB_VENDOR_ID           0x1cbe

//*****************************************************************************
//
// The USB device ID published by the DFU device.  If you are using your own
// vendor ID, chose a device ID that is different from the ID you use in
// non-update operation.  If you have sublicensed TI's vendor ID, you must
// use an assigned product ID here.
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define USB_PRODUCT_ID          0x00ff

//*****************************************************************************
//
// Selects the BCD USB device release number published in the device
// descriptor.
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define USB_DEVICE_ID           0x0001

//*****************************************************************************
//
// Sets the maximum power consumption that the DFU device will report to the
// USB host in the configuration descriptor.  Units are milliamps.
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define USB_MAX_POWER           150

//*****************************************************************************
//
// Determines whether the DFU device reports to the host that it is self
// powered (defined as 0) or bus powered (defined as 1).
//
// Depends on: None
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define USB_BUS_POWERED         0

//*****************************************************************************
//
// Specifies the GPIO peripheral associated with the USB host/device mux.
//
// Depends on: None
// Exclusive of: None
// Requires: USB_MUX_PERIPH, USB_MUX_PORT, USB_MUX_PIN, USB_MUX_DEVICE
//
//*****************************************************************************
//#define USB_HAS_MUX

//*****************************************************************************
//
// Specifies the GPIO pin number used to switch the USB host/device mux.  Valid
// values are 0 through 64.
//
// Depends on: USB_HAS_MUX
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define USB_MUX_PIN             44

//*****************************************************************************
//
// Specifies the state to set the GPIO pin to to select USB device mode via
// the USB host/device mux.  Valid values are 1 (high) or 0 (low).
//
// Depends on: USB_HAS_MUX
// Exclusive of: None
// Requires: None
//
//*****************************************************************************
#define USB_MUX_DEVICE          1

//*****************************************************************************
//
// Boot loader hook functions.
//
// The following defines allow you to add application-specific function which
// are called at various points during boot loader execution.
//
//*****************************************************************************

//*****************************************************************************
//
// Performs application-specific low level hardware initialization on system
// reset.
//
// If hooked, this function will be called immediately after the boot loader
// code relocation completes.  An application may perform any required low
// hardware initialization during this function.  Note that the system clock
// has not been set when this function is called.  Initialization that assumes
// the system clock is set may be performed in the BL_INIT_FN_HOOK function
// instead.
//
// void MyHwInitFunc(void);
//
//*****************************************************************************
//#define BL_HW_INIT_FN_HOOK      MyHwInitFunc

//*****************************************************************************
//
// Performs application-specific initialization on system reset.
//
// If hooked, this function will be called immediately after the boot loader
// sets the system clock.  An application may perform any additional
// initialization during this function.
//
// void MyInitFunc(void);
//
//*****************************************************************************
//#define BL_INIT_FN_HOOK         MyInitFunc

//*****************************************************************************
//
// Performs application-specific reinitialization on boot loader entry via 
// the target application.
//
// If hooked, this function will be called immediately before the boot loader
// reinitializes the system clock when it is entered from an application
// rather than as a result of a system reset.  An application may perform
// any additional reinitialization in this function.
//
// void MyReinitFunc(void);
//
//*****************************************************************************
//#define BL_REINIT_FN_HOOK       MyReinitFunc

//*****************************************************************************
//
// Informs an application that a download is starting.
//
// If hooked, this function will be called when a new firmware download is
// about to start.  The application may use this signal to initialize any
// progress display.
//
// void MyStartFunc(void);
//
//*****************************************************************************
//#define BL_START_FN_HOOK        MyStartFunc

//*****************************************************************************
//
// Informs an application of download progress.
//
// If hooked, this function will be called periodically during firmware
// download.  The application may use this to update its user interface.
//
// void MyProgressFunc(unsigned long ulCompleted, unsigned long ulTotal);
//
// where:
//
// - ulCompleted indicates the number of bytes already downloaded.
// - ulTotal indicates the number of bytes expected.
//
//*****************************************************************************
//#define BL_PROGRESS_FN_HOOK     MyProgressFunc

//*****************************************************************************
//
// Informs an application that a download has completed.
//
// If hooked, this function will be called when a firmware download ends.
// The application may use this signal to update its user interface.  Typically
// a system reset will occur shortly after this function returns as the boot
// loader attempts to boot the new image.
//
// void MyEndFunc(void);
//
//*****************************************************************************
//#define BL_END_FN_HOOK          MyEndFunc

//*****************************************************************************
//
// Allows an application to perform in-place data decryption during download.
//
// If hooked, this function will be called on receipt of any new block of
// downloaded firmware image data.  The application must decrypt this data
// in place then return at which point the boot loader will write the data to
// flash.
//
// void MyDecryptionFunc(unsigned char *pucBuffer, unsigned long ulSize);
//
// where:
//
// - pucBuffer points to the first byte of data to be decrypted.
// - ulSize indicates the number of bytes of data at pucBuffer.
//
//*****************************************************************************
//#define BL_DECRYPT_FN_HOOK      MyDecryptionFunc

//*****************************************************************************
//
// Allows an application to force a new firmware download.
//
// If hooked, this function will be called after a system reset (following 
// basic initialization and the initialization hook function) to give the
// application an opportunity to force a new firmware download.  Depending upon
// the return code, the boot loader will either boot the existing firmware
// image or wait for a new download to be started.
//
// Note that this hook takes precedence over ENABLE_UPDATE_CHECK settings.  If
// the hook function is defined, the basic GPIO check offered by
// ENABLE_UPDATE_CHECK does not take place.
//
// unsigned long MyCheckUpdateFunc(void);
//
// where the return code is 0 if the boot loader should boot the existing
// image (if found) or non-zero to indicate that the boot loader should retain
// control and wait for a new firmware image to be downloaded.
//
//*****************************************************************************
//#define BL_CHECK_UPDATE_FN_HOOK MyCheckUpdateFunc

//*****************************************************************************
//
// VCU <-> CPU Function mapping
// DO NOT MODIFY
//
//*****************************************************************************
#ifdef ENABLE_VCU
#define getCRC8       getCRC8_vcu
#define getCRC16P1    getCRC16P1_vcu
#define getCRC16P2    getCRC16P2_vcu
#define getCRC32      getCRC32_vcu
#else
#define getCRC8       getCRC8_cpu
#define getCRC16P1    getCRC16P1_cpu
#define getCRC16P2    getCRC16P2_cpu
#define getCRC32      getCRC32_cpu
#endif

#endif // __BL_CONFIG_H__

//
// End of File
//


