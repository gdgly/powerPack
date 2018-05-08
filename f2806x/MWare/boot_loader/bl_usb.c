//###########################################################################
//
// bl_usb.c - Functions to transfer data via the USB port.
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

//
// Included Files
//
#include <stdlib.h>
#include "DSP28x_Project.h"
#include "crc_tbl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_usb.h"
#include "boot_loader/bl_config.h"
#include "boot_loader/bl_sym.h"
#include "boot_loader/bl_decrypt.h"
#include "boot_loader/bl_check.h"
#include "boot_loader/bl_hooks.h"
#include "boot_loader/bl_usbfuncs.h"
#include "boot_loader/usbdfu.h"

#include "Flash2806x_API_Config.h"
#include "Flash2806x_API_Library.h"

//
// Globals
//
extern Uint32 Flash_CPUScaleFactor;

extern void (*Flash_CallbackPtr) (void);

FLASH_ST g_FlashStatus;

extern void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

//*****************************************************************************
//
// DFU Notes:
//
// 1. This implementation is manifestation-tolerant and doesn't time out
//    waiting for a reset after a download completes.  As a result, the detach
//    timeout in the DFU functional descriptor is set to the maximum possible
//    value representing a timeout of 65.536 seconds.
//
// 2. This implementation does not support the BUSY state.  By skipping this
//    and remaining in DNLOAD_SYNC when we are waiting for a programming or
//    erase operation to complete, we save the overhead of having to support a
//    timeout mechanism.  Host-side implementations don't seem to rely upon
//    the busy state so this does not appear to be a problem.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup bl_usb_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// The DFU device information structure was developed assuming flash block
// sizes in the 1KB to 32KB range but large external flash devices may have
// 64KB or larger blocks.  If the configuration options indicate a target
// device with large pages, we fake the size at 32KB to keep the client happy.
// The other option would be to redefince this field as an unsigned long but
// that would break existing applications using the interface.
//
// For normal operation, this is unlikely to cause a problem since we will not
// allow a flash operation to start anywhere other than at APP_START_ADDRESS
// (which must fall on a real flash page boundary) or the start of the
// reserved
//
//*****************************************************************************
#define DFU_REPORTED_PAGE_SIZE  FLASH_PAGE_SIZE

//*****************************************************************************
//
// This holds the total size of the firmware image being downloaded (which is
// needed if we have a progress reporting hook function provided).
//
//*****************************************************************************
#ifdef BL_PROGRESS_FN_HOOK
unsigned long g_ulImageSize;
#endif

//*****************************************************************************
//
// The structure used to define a block of memory.
//
//*****************************************************************************
typedef struct
{
    unsigned char *pcStart;
    unsigned long ulLength;
}
tMemoryBlock;

//*****************************************************************************
//
// The block of memory that is to be sent back in response to the next upload
// request.
//
//*****************************************************************************
tMemoryBlock g_sNextUpload;

//*****************************************************************************
//
// The block of memory into which the next programming operation will write.
//
//*****************************************************************************
volatile tMemoryBlock g_sNextDownload;

//*****************************************************************************
//
// The block of flash to be erased.
//
//*****************************************************************************
volatile tMemoryBlock g_sErase;

//*****************************************************************************
//
// Information on the device we are running on.  This will be returned to the
// host after a download request containing command DFU_CMD_INFO.
//
//*****************************************************************************
tDFUDeviceInfo g_sDFUDeviceInfo;

//*****************************************************************************
//
// This variable keeps track of the last TI-specific command received
// from the host via a download request.
//
//*****************************************************************************
unsigned char g_ucLastCommand;

//*****************************************************************************
//
// The current status of the DFU device as reported to the host in response to
// USBD_DFU_REQUEST_GETSTATUS.
//
//*****************************************************************************
tDFUGetStatusResponse g_sDFUStatus =
{
    0, {5, 0, 0}, (unsigned char)STATE_IDLE, 0
};

//*****************************************************************************
//
// The structure sent in response to a valid USBD_DFU_REQUEST_TI.
//
//*****************************************************************************
tDFUQueryTIProtocol g_sDFUProtocol =
{
    {TI_DFU_PROTOCOL_MARKER & 0xFF, (TI_DFU_PROTOCOL_MARKER & 0xFF00) >> 8},  
    {TI_DFU_PROTOCOL_VERSION_C2000_1 & 0xFF, (TI_DFU_PROTOCOL_VERSION_C2000_1 
                                              & 0xFF00) >> 8}
};

//*****************************************************************************
//
// The current state of the device.
//
//*****************************************************************************
volatile tDFUState g_eDFUState = STATE_IDLE;

//*****************************************************************************
//
// The current status of the device.
//
//*****************************************************************************
volatile tDFUStatus g_eDFUStatus = STATUS_OK;

//*****************************************************************************
//
// The buffer used to hold download data from the host prior to writing it to
// flash or image data in the process of being uploaded to the host.
//
//*****************************************************************************
unsigned char g_pcDFUBuffer[DFU_TRANSFER_SIZE];

#ifdef ENABLE_CSM_CONTROL
//*****************************************************************************
//
// The buffer used to hold the seed generated for CSM unlock authentication
//
//*****************************************************************************
unsigned char g_pucSeedBuffer[16];

//*****************************************************************************
//
// The buffer used to hold the key calcuated for CSM unlock authentication
//
//*****************************************************************************
unsigned char g_pucKeyBuffer[16];

//*****************************************************************************
//
// The buffer used to hold the key calcuated for CSM unlock authentication
//
//*****************************************************************************
unsigned char * g_pucReceivedKey;


#if KEY_FORM == KEY_SET
//*****************************************************************************
//
// The key to use for encryption.  Note that this key is not a good example
// since it is not random.
//
//*****************************************************************************
const unsigned char g_ucKey[16] =
{
    0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89,
    0x9A, 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0xF0, 0x00
};

//*****************************************************************************
//
// The context structure for the AES functions.  This structure contains a
// buffer so it is best to not put it on the stack unless you make the stack
// larger.
//
//*****************************************************************************
static aes_context g_aesCtx;

#endif

#endif

//*****************************************************************************
//
// The start of the image data within g_pcDFUBuffer.
//
//*****************************************************************************
unsigned char *g_pcDFUWrite;

//*****************************************************************************
//
// The number of bytes of valid data in the DFU buffer.
//
//*****************************************************************************
volatile unsigned short g_usDFUBufferUsed;

//*****************************************************************************
//
// The buffer used to hold download data from the host prior to writing it to
// flash or image data in the process of being uploaded to the host.
//
//*****************************************************************************
unsigned char g_pcCopyBuffer[0x1000];


//*****************************************************************************
//
// Flags used to indicate that the main thread is being asked to do something.
//
//*****************************************************************************
volatile unsigned long g_ulCommandFlags;

#define CMD_FLAG_ERASE          0
#define CMD_FLAG_WRITE          1
#define CMD_FLAG_RESET          2
#define CMD_FLAG_CSM            3

//*****************************************************************************
//
// This global determines whether or not we add a DFU header to any uploaded
// image data.  If true, the binary image is sent without the header.  If false
// the header is included.  This is a DFU requirement since uploaded images
// must be able to be downloaded again and hence must have the header in place
// so that the destination address is available.
//
//*****************************************************************************
tBoolean g_bUploadBinary = false;

//*****************************************************************************
//
// If the upload format includes the header, we need to be able to suppress
// this when replying to TI-specific commands such as CMD_DFU_INFO.  This
// global determines whether we need to suppress the header that would
// otherwise be send in response to the first USBD_DFU_REQUEST_UPLOAD received
// while in STATE_IDLE.
//
//*****************************************************************************
tBoolean g_bSuppressUploadHeader = false;

//*****************************************************************************
//
// A flag we use to indicate when the device has been enumerated.
//
//*****************************************************************************
tBoolean g_bAddressSet = false;

#ifdef ENABLE_FAILSAFE
//*****************************************************************************
//
// A flag we use to indicate when we are in failsafe mode.
//
//*****************************************************************************
tBoolean g_bFailsafe;
#endif

//*****************************************************************************
//
// The languages supported by this device.
//
//*****************************************************************************
const unsigned char g_pLangDescriptor[] =
{
    4,
    USB_DTYPE_STRING,
    USBShort(USB_LANG_EN_US)
};

//*****************************************************************************
//
// The jump table used to implement request handling in the DFU state machine.
//
//*****************************************************************************
typedef void (* tHandleRequests)(tUSBRequest *pUSBRequest);

extern void HandleRequestIdle(tUSBRequest *pUSBRequest);
extern void HandleRequestDnloadSync(tUSBRequest *pUSBRequest);
extern void HandleRequestDnloadIdle(tUSBRequest *pUSBRequest);
extern void HandleRequestManifestSync(tUSBRequest *pUSBRequest);
extern void HandleRequestUploadIdle(tUSBRequest *pUSBRequest);
extern void HandleRequestError(tUSBRequest *pUSBRequest);

tHandleRequests g_pfnRequestHandlers[] =
{
    0,                          // STATE_APP_IDLE
    0,                          // STATE_APP_DETACH
    HandleRequestIdle,          // STATE_IDLE
    HandleRequestDnloadSync,    // STATE_DNLOAD_SYNC
    HandleRequestDnloadSync,    // STATE_DNBUSY
    HandleRequestDnloadIdle,    // STATE_DNLOAD_IDLE
    HandleRequestManifestSync,  // STATE_MANIFEST_SYNC
    0,                          // STATE_MANIFEST
    0,                          // STATE_MANIFEST_WAIT_RESET
    HandleRequestUploadIdle,    // STATE_UPLOAD_IDLE
    HandleRequestError          // STATE_ERROR
};

//*****************************************************************************
//
// The manufacturer string.
//
//*****************************************************************************
const unsigned char g_pManufacturerString[] =
{

    2 + (17 * 2),
    USB_DTYPE_STRING,
    'T', 0, 'e', 0, 'x', 0, 'a', 0, 's', 0, ' ', 0, 'I', 0, 'n', 0,
    's', 0, 't', 0, 'r', 0, 'u', 0, 'm', 0, 'e', 0, 'n', 0, 't', 0,
    's', 0
};

//*****************************************************************************
//
// The product string.
//
//*****************************************************************************
const unsigned char g_pProductString[] =
{
    (23 + 1) * 2,
    USB_DTYPE_STRING,
    'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0, ' ', 0, 'F', 0, 'i', 0,
    'r', 0, 'm', 0, 'w', 0, 'a', 0, 'r', 0, 'e', 0, ' ', 0, 'U', 0, 'p', 0,
    'g', 0, 'r', 0, 'a', 0, 'd', 0, 'e', 0
};

//*****************************************************************************
//
// The serial number string.
//
//*****************************************************************************
const unsigned char g_pSerialNumberString[] =
{
    (3 + 1) * 2,
    USB_DTYPE_STRING,
    '0', 0, '.', 0, '1', 0
};

//*****************************************************************************
//
// The DFU Interface string.
//
//*****************************************************************************
const unsigned char g_pDFUInterfaceString[] =
{
    (10 + 1) * 2,
    USB_DTYPE_STRING,
    'S', 0, 'U', 0, 'P', 0, 'E', 0, 'R', 0, '-', 0, 'B', 0, 'O', 0, 'O', 0, 'T', 0
};

//*****************************************************************************
//
// The descriptor string table.
//
//*****************************************************************************
const unsigned char * const g_pStringDescriptors[] =
{
    g_pLangDescriptor,
    g_pManufacturerString,
    g_pProductString,
    g_pSerialNumberString,
    g_pDFUInterfaceString
};

//*****************************************************************************
//
// DFU Device Descriptor.
//
//*****************************************************************************
const unsigned char g_pDFUDeviceDescriptor[] =
{
    18,                         // Size of this structure.
    USB_DTYPE_DEVICE,           // Type of this structure.
    USBShort(0x110),            // USB version 1.1 (if we say 2.0, hosts assume
                                // high-speed - see USB 2.0 spec 9.2.6.6)
    USB_CLASS_VEND_SPECIFIC,    // USB Device Class
    0,                          // USB Device Sub-class
    0,                          // USB Device protocol
    64,                         // Maximum packet size for default pipe.
    USBShort(USB_VENDOR_ID),    // Vendor ID (VID).
    USBShort(USB_PRODUCT_ID),   // Product ID (PID).
    USBShort(USB_DEVICE_ID),    // Device Release Number BCD.
    1,                          // Manufacturer string identifier.
    2,                          // Product string indentifier.
    3,                          // Product serial number.
    1                           // Number of configurations.
};

//*****************************************************************************
//
// DFU device configuration descriptor.
//
//*****************************************************************************
const unsigned char g_pDFUConfigDescriptor[] =
{
    //
    // Configuration descriptor header.
    //
    9,                          // Size of the configuration descriptor.
    USB_DTYPE_CONFIGURATION,    // Type of this descriptor.
    USBShort(27),               // The total size of this full structure.
    1,                          // The number of interfaces in this
                                // configuration.
    1,                          // The unique value for this configuration.
    0,                          // The string identifier that describes this
                                // configuration.
#if USB_BUS_POWERED
    USB_CONF_ATTR_BUS_PWR,      // Bus Powered
#else
    USB_CONF_ATTR_SELF_PWR,     // Self Powered
#endif
    (USB_MAX_POWER / 2),        // The maximum power in 2mA increments.

    //
    // Interface descriptor.
    //
    9,                          // Length of this descriptor.
    USB_DTYPE_INTERFACE,        // This is an interface descriptor.
    0,                          // Interface number .
    0,                          // Alternate setting number.
    0,                          // Number of endpoints (only endpoint 0 used)
    USB_CLASS_APP_SPECIFIC,     // Application specific interface class
    USB_DFU_SUBCLASS,           // Device Firmware Upgrade subclass
    USB_DFU_PROTOCOL,           // DFU protocol
    4,                          // No interface description string present.

    //
    // Device Firmware Upgrade functional descriptor.
    //
    9,                          // Length of this descriptor.
    0x21,                       // DFU Functional descriptor type
    (DFU_ATTR_CAN_DOWNLOAD |    // DFU attributes.
     DFU_ATTR_CAN_UPLOAD |
     DFU_ATTR_MANIFEST_TOLERANT),
    USBShort(0xFFFF),           // Detach timeout (set to maximum).
    USBShort(DFU_TRANSFER_SIZE),// Transfer size 1KB.
    USBShort(0x0110)            // DFU Version 1.1
};


//*****************************************************************************
//
//! The USB device interrupt handler.
//!
//! This function is called to process USB interrupts when in device mode.
//! This handler will branch the interrupt off to the appropriate application 
//! or stack handlers depending on the current status of the USB controller.
//!
//! \return None.
//
//*****************************************************************************
__interrupt void
USB0DeviceIntHandler(void)
{
    unsigned long ulTxStatus = 0UL, ulGenStatus = 0UL;
    uint16_t usbis = 0U, txis = 0U;
    //
    // Get the current full USB interrupt status.
    //
    
    //
    // Do-While to make sure that all status registers are cleared before 
    // continuing. This eliminates the race condition which can cause the 
    // USB interrupt to stay high and never get triggered again.
    //
    do
    {
        //
    	// Get the transmit interrupt status.
        //
    	txis = HWREGH(USB0_BASE + USB_O_TXIS);
        
        //
    	// Get the general interrupt status.
        //
    	usbis = (uint16_t)HWREGB(USB0_BASE + USB_O_IS);

        ulTxStatus |= txis;
        ulGenStatus |= usbis;
    }
    while((txis != 0x0000U) || (usbis != 0x0000U));


    //
    // Received a reset from the host.
    //
    if(ulGenStatus & USB_IS_RESET)
    {
        USBDeviceEnumResetHandler();
    }

    //
    // USB device was disconnected.
    //
    if(ulGenStatus & USB_IS_DISCON)
    {
        HandleDisconnect();
    }

    //
    // Handle end point 0 interrupts.
    //
    if(ulTxStatus & USB_TXIE_EP0)
    {
        USBDeviceEnumHandler();
    }
    
    
    PieCtrlRegs.PIEACK.all |= 0x10;
}

//*****************************************************************************
//
//! Send the current state or status structure back to the host.  This function
//! also acknowledges the request which causes us to send back this data.
//
//*****************************************************************************
void
SendDFUStatus(void)
{
    //
    // Acknowledge the original request.
    //
    USBDevEndpoint0DataAck(false);

    //
    // Copy the current state into the status structure we will return.
    //
    g_sDFUStatus.bState = (unsigned char)g_eDFUState;
    g_sDFUStatus.bStatus = (unsigned char)g_eDFUStatus;

    //
    // Send the status structure back to the host.
    //
    USBBLSendDataEP0((unsigned char *)&g_sDFUStatus,
                     sizeof(tDFUGetStatusResponse));
}

//*****************************************************************************
//
//! Send the next block of upload data back to the host assuming data remains
//! to be sent.
//!
//! \param usLength is the requested amount of data.
//! \param bAppendHeader is \b true to append a tDFUDownloadProgHeader at the
//! start of the uploaded data or \b false if no header is required.
//!
//! Returns \b true if a full packet containing DFU_TRANSFER_SIZE bytes
//! was sent and data remains to be sent following this transaction, or \b
//! false if no more data remains to be sent following this transaction.
//
//*****************************************************************************
tBoolean
SendUploadData(unsigned short usLength, tBoolean bAppendHeader)
{
    unsigned short usToSend;
    unsigned long ulAvailable;
    tBoolean bInFlash;

    //
    // Acknowledge the original request.
    //
    USBDevEndpoint0DataAck(false);
   
    //
    // Check to see if we are uploading from flash
    //
    if((unsigned long)g_sNextUpload.pcStart > 0x3D8000 && 
       (unsigned long)g_sNextUpload.pcStart < 0x3F8000)
    {
        bInFlash = true;
    }
    else 
    {
        bInFlash = false;
    }
        
    //
    // How much data is available to be sent?
    //
    if(bInFlash)
    {
#ifdef ENABLE_READ
        if(!g_sDFUDeviceInfo.ucLocked)       
        {
            ulAvailable = 2 * g_sNextUpload.ulLength +
                          (bAppendHeader ? sizeof(tDFUDownloadProgHeader) : 0);
        }
        else
        {
            ulAvailable = (bAppendHeader ? sizeof(tDFUDownloadProgHeader) : 0);
        }
        
#else
        ulAvailable = (bAppendHeader ? sizeof(tDFUDownloadProgHeader) : 0);
#endif
    }
    else
    {
        ulAvailable = g_sNextUpload.ulLength +
                      (bAppendHeader ? sizeof(tDFUDownloadProgHeader) : 0);
    }

    //
    // How much data can we send? This is the smallest of the maximum transfer
    // size, the requested length or the available data.
    //
    usToSend = (usLength > DFU_TRANSFER_SIZE) ? DFU_TRANSFER_SIZE : usLength;
    usToSend = ((unsigned long)usToSend > ulAvailable) ? ulAvailable : usToSend;

    //
    // If we have been asked to send a header, we need to copy some of the
    // data into a buffer and send from there.  If we don't do this, we run the
    // risk of sending a short packet prematurely and ending the upload
    // before it is complete.
    //
    if(bAppendHeader)
    {
        tDFUDownloadProgHeader *psHdr;
        unsigned char *pcFrom;
        unsigned char *pcTo;
        unsigned long ulLoop;

        //
        // We are appending a header so write the header information into a
        // buffer then copy the first chunk of data from its original position
        // into the same buffer.
        //
        psHdr = (tDFUDownloadProgHeader *)g_pcDFUBuffer;

        //
        // Build the header.
        //
        psHdr->ucCommand = DFU_CMD_PROG;
        psHdr->ucReserved = 0;
        writeShort(&(psHdr->usStartAddr), 
                  ((unsigned long)(g_sNextUpload.pcStart) / 1024));
        writeShort(&(psHdr->ulLength), g_sNextUpload.ulLength);

        //
        // Copy the remainder of the first transfer's data from its original
        // position.
        //
        pcFrom = g_sNextUpload.pcStart;
        pcTo = (unsigned char *)(psHdr + 1);

        if(bInFlash)
        {
            for(ulLoop = (usToSend - sizeof(tDFUDownloadProgHeader)) / 2; 
                ulLoop; ulLoop--)
            {
                *pcTo++ = __byte((int*)pcFrom,1);
                *pcTo++ = __byte((int*)pcFrom++,0);
            }
        }
        else
        {    
            for(ulLoop = (usToSend - sizeof(tDFUDownloadProgHeader)); ulLoop;
                ulLoop--)
            {
                *pcTo++ = *pcFrom++;
            }
        }

        //
        // Send the data.
        //
        USBBLSendDataEP0((unsigned char *)psHdr, (unsigned long)usToSend);

        //
        // Update our upload pointer and length.
        //
        if(bInFlash)
        {
            g_sNextUpload.pcStart += (usToSend - 
                                      sizeof(tDFUDownloadProgHeader)) / 2;
            g_sNextUpload.ulLength -= (usToSend - 
                                       sizeof(tDFUDownloadProgHeader)) / 2;
        }
        else
        {
            g_sNextUpload.pcStart += (usToSend - 
                                      sizeof(tDFUDownloadProgHeader));
            g_sNextUpload.ulLength -= (usToSend - 
                                       sizeof(tDFUDownloadProgHeader));
        }
    }
    else
    {
        //
        // We are not sending a header so send the requested upload data back to
        // the host directly from its original position.
        //
        USBBLSendDataEP0((unsigned char *)g_sNextUpload.pcStart,
                         (unsigned long)usToSend);

        //
        // Update our upload pointer and length.
        //
        if(bInFlash)
        {
            g_sNextUpload.pcStart += usToSend / 2;
            g_sNextUpload.ulLength -= usToSend / 2;
        }
        else
        {
            g_sNextUpload.pcStart += usToSend;
            g_sNextUpload.ulLength -= usToSend;
        }    

    }

    //
    // We return true if we sent a full packet (containing the maximum transfer
    // size bytes) or false to indicate that a short packet was sent or no more
    // data remains.
    //
    return(((usToSend == DFU_TRANSFER_SIZE) && g_sNextUpload.ulLength) ?
           true : false);
}

//*****************************************************************************
//
//! Send the current state back to the host.
//
//*****************************************************************************
void
SendDFUState(void)
{
    //
    // Acknowledge the original request.
    //
    USBDevEndpoint0DataAck(false);

    //
    // Update the status structure with the current state.
    //
    g_sDFUStatus.bState = (unsigned char)g_eDFUState;

    //
    // Send the state from the status structure back to the host.
    //
    USBBLSendDataEP0((unsigned char *)&g_sDFUStatus.bState, 1);
}

//*****************************************************************************
//
//! Handle USB requests sent to the DFU device.
//!
//! \param pUSBRequest is a pointer to the USB request that the device has
//! been sent.
//!
//! This function is called to handle all non-standard requests received
//! by the device.  This will include all the DFU endpoint 0 commands along
//! with the TI-specific request we use to query whether the device
//! supports our flavor of the DFU binary format.  Incoming DFU requests are
//! processed by request handlers specific to the particular state of the DFU
//! connection.  This state machine implementation is chosen to keep the
//! software as close as possible to the USB DFU class documentation.
//!
//! \return None.
//
//*****************************************************************************
void
HandleRequests(tUSBRequest *pUSBRequest)
{
    //
    // This request is used by the host to determine whether the connected
    // device supports the TI protocol extensions to DFU (our
    // DFU_CMD_xxxx command headers passed alongside DNLOAD requests).  We
    // check the parameters and, if they are as expected, we respond with
    // a 4 byte structure providing a marker and the protocol version
    // number.
    //
    if(pUSBRequest->bRequest == USBD_DFU_REQUEST_TI)
    {
        //
        // Check that the request parameters are all as expected.  We are
        // using the wValue value merely as a way of making it less likely
        // that we respond to another vendor's device-specific request.
        //
        if((readShort(&(pUSBRequest->wLength)) == sizeof(tDFUQueryTIProtocol)) 
           && (readShort(&(pUSBRequest->wValue)) == REQUEST_TI_VALUE))
        {
            //
            // Acknowledge the original request.
            //
            USBDevEndpoint0DataAck(false);

            //
            // Send the status structure back to the host.
            //
            USBBLSendDataEP0((unsigned char *)&g_sDFUProtocol,
                             sizeof(tDFUQueryTIProtocol));
        }
        else
        {
            //
            // The request parameters were not as expected so we assume
            // that this is not our request and stall the endpoint to
            // indicate an error.
            //
            USBBLStallEP0();
        }

        return;
    }

    //
    // Pass the request to the relevant handler depending upon our current
    // state.  If no handler is configured, we stall the endpoint since this
    // implies that requests can't be handled in this state.
    //
    if(g_pfnRequestHandlers[g_eDFUState])
    {
        //
        // Dispatch the request to the relevant handler depending upon the
        // current state.
        //
        (g_pfnRequestHandlers[g_eDFUState])(pUSBRequest);
    }
    else
    {
        USBBLStallEP0();
    }
}

//*****************************************************************************
//
//! Idle request handler
//!
//! \param pUSBRequest USB request to handle.
//!
//! Handle all incoming DFU requests while in state STATE_IDLE.
//
//*****************************************************************************
void
HandleRequestIdle(tUSBRequest *pUSBRequest)
{
    switch(pUSBRequest->bRequest)
    {
        //
        // This is a download request.  We need to request the transaction
        // payload unless this is a zero length request in which case we mark
        // the error by stalling the endpoint.
        //
        case USBD_DFU_REQUEST_DNLOAD:
        {
            if(readShort(&(pUSBRequest->wLength)))
            {
                USBBLRequestDataEP0(g_pcDFUBuffer, 
                                    readShort(&(pUSBRequest->wLength)));
            }
            else
            {
                USBBLStallEP0();
                return;
            }
            break;
        }

        //
        // This is an upload request.  We send back a block of data
        // corresponding to the current upload pointer as held in
        // g_sNextUpload.
        //
        case USBD_DFU_REQUEST_UPLOAD:
        {
            //
            // If we have any upload data to send, send it.  Make sure we append
            // a header if required.
            //
            if(SendUploadData(readShort(&(pUSBRequest->wLength)),
                           g_bSuppressUploadHeader ? false : !g_bUploadBinary))
            {
                //
                // We sent a full (max packet size) frame to the host so
                // transition to UPLOAD_IDLE state since we expect another
                // upload request to continue the process.
                //
                g_eDFUState = STATE_UPLOAD_IDLE;
            }

            //
            // Clear the flag we use to suppress sending the DFU header.
            //
            g_bSuppressUploadHeader = false;

            return;
        }

        //
        // Return the current device status structure.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            SendDFUStatus();
            return;
        }

        //
        // Return the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            return;
        }

        //
        // Ignore the ABORT request.  This returns us to IDLE state but we're
        // there already.
        //
        case USBD_DFU_REQUEST_ABORT:
            break;

        //
        // All other requests are illegal in this state so signal the error
        // by stalling the endpoint.
        //
        case USBD_DFU_REQUEST_CLRSTATUS:
        case USBD_DFU_REQUEST_DETACH:
        default:
        {
            USBBLStallEP0();
            return;
        }
    }

    //
    // If we drop out of the switch, we need to ACK the received request.
    //
    USBDevEndpoint0DataAck(false);
}

//*****************************************************************************
//
//! Download Sync request handler
//!
//! \param pUSBRequest USB request to handle.
//!
//! Handle all incoming DFU requests while in state STATE_DNLOAD_SYNC or
//! STATE_DNBUSY.
//
//*****************************************************************************
void
HandleRequestDnloadSync(tUSBRequest *pUSBRequest)
{
    //
    // In this state, we have received a block of the download and are waiting
    // for a USBD_DFU_REQUEST_GETSTATUS which will trigger a return
    // to STATE_DNLOAD_IDLE assuming we have finished programming the block.
    // If the last command we received was not DFU_CMD_PROG, we transition
    // directly from this state back to STATE_IDLE once the last operation has
    // completed since we need to be able to accept a new command.
    //
    switch(pUSBRequest->bRequest)
    {
        //
        // The host is requesting the current device status.  Return this and
        // revert to STATE_IDLE.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            //
            // Are we finished processing whatever the last flash-operation
            // was?  Note that we don't support DNLOAD_BUSY state in this
            // implementation, we merely continue to report DNLOAD_SYNC state
            // until we are finished with the command.
            //
            if(!g_ulCommandFlags)
            {
                //
                // If we are in the middle of a programming operation,
                // transition back to DNLOAD_IDLE state to wait for the
                // next block.  If not, go back to idle since we expect a
                // new command.
                //
                g_eDFUState = (g_ucLastCommand == DFU_CMD_PROG) ?
                              STATE_DNLOAD_IDLE : STATE_IDLE;
            }

            //
            // Send the latest status back to the host.
            //
            SendDFUStatus();

            //
            // Return here since we've already ACKed the request.
            //
            return;
        }

        //
        // The host is requesting the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            //
            // Are we currently in DNLOAD_SYNC state?
            //
            if(g_eDFUState == STATE_DNLOAD_SYNC)
            {
                //
                // Yes - send back the state.
                //
                SendDFUState();
            }
            else
            {
                //
                // In STATE_BUSY, we can't respond to any requests so stall
                // the endpoint.
                //
                USBBLStallEP0();
            }

            //
            // Return here since the incoming request has already been either
            // ACKed or stalled by the processing above.
            //
            return;
        }

        //
        // Any other request is ignored and causes us to stall the control
        // endpoint and remain in STATE_ERROR.
        //
        default:
        {
            USBBLStallEP0();
            return;
        }
    }
}

//*****************************************************************************
//
//! Download Idle request handler
//!
//! \param pUSBRequest USB request to handle.
//!
//! Handle all incoming DFU requests while in state STATE_DNLOAD_IDLE.
//
//*****************************************************************************
void
HandleRequestDnloadIdle(tUSBRequest *pUSBRequest)
{
    switch(pUSBRequest->bRequest)
    {
        //
        // This is a download request.  We need to request the transaction
        // payload unless this is a zero length request in which case we mark
        // the error by stalling the endpoint.
        //
        case USBD_DFU_REQUEST_DNLOAD:
        {
            //
            // Are we being passed data to program?
            //
            if(readShort(&(pUSBRequest->wLength)))
            {
                //
                // Yes - request the data.
                //
                USBBLRequestDataEP0(g_pcDFUBuffer, 
                                    readShort(&(pUSBRequest->wLength)));
            }
            else
            {
                //
                // No - this is the signal that a download operation is
                // complete.  Do we agree?
                //
                if(g_sNextDownload.ulLength)
                {
                    //
                    // We think there should still be some data to be received
                    // so mark this as an error.
                    //
                    g_eDFUState = STATE_ERROR;
                    g_eDFUStatus = STATUS_ERR_NOTDONE;
                }
                else
                {
                    //
                    // We agree that the download has completed.  Enter state
                    // STATE_MANIFEST_SYNC.
                    //
                    g_eDFUState = STATE_MANIFEST_SYNC;
                }
             }
            break;
        }

        //
        // Return the current device status structure.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            SendDFUStatus();
            return;
        }

        //
        // Return the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            return;
        }

        //
        // An ABORT request causes us to abort the current transfer and
        // return the the idle state regardless of the state of the previous
        // programming operation.
        //
        case USBD_DFU_REQUEST_ABORT:
        {
            //
            // Default to downloading the main code image.
            //
            g_sNextDownload.pcStart =
                (unsigned char *)readLong(&(g_sDFUDeviceInfo.ulAppStartAddr));
            g_sNextDownload.ulLength = 
                (readLong(&(g_sDFUDeviceInfo.ulFlashTop)) -
                 readLong(&(g_sDFUDeviceInfo.ulAppStartAddr)));
            g_eDFUState = STATE_IDLE;
            break;
        }

        //
        // All other requests are illegal in this state so signal the error
        // by stalling the endpoint.
        //
        case USBD_DFU_REQUEST_CLRSTATUS:
        case USBD_DFU_REQUEST_DETACH:
        case USBD_DFU_REQUEST_UPLOAD:
        default:
        {
            USBBLStallEP0();
            return;
        }
    }

    //
    // If we drop out of the switch, we need to ACK the received request.
    //
    USBDevEndpoint0DataAck(false);

}
//*****************************************************************************
//
//! Manifest Sync request handler
//!
//! \param pUSBRequest USB request to handle.
//!
//! Handle all incoming DFU requests while in state STATE_MANIFEST_SYNC.
//
//*****************************************************************************
void
HandleRequestManifestSync(tUSBRequest *pUSBRequest)
{
    //
    // In this state, we have received the last block of a download and are
    // waiting for a USBD_DFU_REQUEST_GETSTATUS which will trigger a return
    // to STATE_IDLE.
    //
    switch(pUSBRequest->bRequest)
    {
        //
        // The host is requesting the current device status.  Return this and
        // revert to STATE_IDLE.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            g_eDFUState = STATE_IDLE;
            SendDFUStatus();
            break;
        }

        //
        // The host is requesting the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            break;
        }

        //
        // Any other request is ignored and causes us to stall the control
        // endpoint and remain in STATE_MANIFEST_SYNC.
        //
        default:
        {
            USBBLStallEP0();
            break;
        }
    }
}

//*****************************************************************************
//
//! Upload Idle request handler
//!
//! \param pUSBRequest USB request to handle.
//!
//! Handle all incoming DFU requests while in state STATE_UPLOAD_IDLE.
//
//*****************************************************************************
void
HandleRequestUploadIdle(tUSBRequest *pUSBRequest)
{
    //
    // In this state, we have already received the first upload request. 
    // What are we being asked to do now?
    //
    switch(pUSBRequest->bRequest)
    {
        //
        // The host is requesting more upload data.
        //
        case USBD_DFU_REQUEST_UPLOAD:
        {
            //
            // See if there is any more data to transfer and, if there is,
            // send it back to the host.
            //
            if(!SendUploadData(readShort(&(pUSBRequest->wLength)), false))
            {
                //
                // We sent less than a full packet of data so the transfer is
                // complete.  Revert to idle state and ensure that we reset
                // our upload pointer and size to the default flash region.
                //
                g_eDFUState = STATE_IDLE;
                g_sNextUpload.pcStart =
                    (unsigned char *)readLong(&(g_sDFUDeviceInfo.ulAppStartAddr));
                g_sNextUpload.ulLength =
                    (readLong(&(g_sDFUDeviceInfo.ulFlashTop)) -
                     readLong(&(g_sDFUDeviceInfo.ulAppStartAddr)));
            }
            break;
        }

        //
        // The host is requesting the current device status.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            SendDFUStatus();
            break;
        }

        //
        // The host is requesting the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            break;
        }

        //
        // The host is requesting that we abort the current upload.
        //
        case USBD_DFU_REQUEST_ABORT:
        {
            //
            // Default to sending the main application image for the next
            // upload.
            //
            g_sNextUpload.pcStart =
                (unsigned char *)readLong(&(g_sDFUDeviceInfo.ulAppStartAddr));
            g_sNextUpload.ulLength = 
                (readLong(&(g_sDFUDeviceInfo.ulFlashTop)) -
                 readLong(&(g_sDFUDeviceInfo.ulAppStartAddr)));
            g_eDFUState = STATE_IDLE;
            break;
        }

        //
        // Any other request is ignored and causes us to stall the control
        // endpoint and remain in STATE_ERROR.
        //
        default:
        {
            USBBLStallEP0();
            break;
        }
    }

}

//*****************************************************************************
//
//! Error request handler
//!
//! \param pUSBRequest USB request to handle.
//!
//! Handle all incoming DFU requests while in state STATE_ERROR.
//
//*****************************************************************************
void
HandleRequestError(tUSBRequest *pUSBRequest)
{
    //
    // In this state, we respond to state and status requests and also to
    // USBD_DFU_REQUEST_CLRSTATUS which clears the previous error condition.
    //
    switch(pUSBRequest->bRequest)
    {
        //
        // The host is requesting the current device status.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            SendDFUStatus();
            break;
        }

        //
        // The host is requesting the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            break;
        }

        //
        // The host is asking us to clear our previous error condition and
        // revert to idle state in preparation to receive new commands.
        //
        case USBD_DFU_REQUEST_CLRSTATUS:
        {
            g_eDFUState = STATE_IDLE;
            g_eDFUStatus = STATUS_OK;
            g_ulCommandFlags = 0;
            USBDevEndpoint0DataAck(false);
            break;
        }

        //
        // Any other request is ignored and causes us to stall the control
        // endpoint and remain in STATE_ERROR.
        //
        default:
        {
            USBBLStallEP0();
            break;
        }
    }
}

//*****************************************************************************
//
//! Handle cases where the host sets a new USB configuration.
//!
//! \param ulInfo Is not used in this implementation.
//
//*****************************************************************************
void
HandleConfigChange(unsigned long ulInfo)
{
    //
    // Revert to idle state.
    //
    g_eDFUState = STATE_IDLE;
    g_eDFUStatus = STATUS_OK;
}

//*****************************************************************************
//
//! Setting the device address indicates that we are now connected to the host
//! and can expect some DFU communication so we use this opportunity to clean
//! out our state just in case we were not idle last time the host disconnected.
//
//*****************************************************************************
void
HandleSetAddress(void)
{
    g_eDFUState = STATE_IDLE;
    g_eDFUStatus = STATUS_OK;
    g_bAddressSet = true;

    //
    // Default the download address to the app start address and valid length
    // to the whole of the programmable flash area.
    //
    g_sNextDownload.pcStart =
                (unsigned char *)readLong(&(g_sDFUDeviceInfo.ulAppStartAddr));
    g_sNextDownload.ulLength = (readLong(&(g_sDFUDeviceInfo.ulFlashTop)) -
                                readLong(&(g_sDFUDeviceInfo.ulAppStartAddr)));

    //
    // Default the upload address to the app start address and valid length
    // to the whole of the programmable flash area.
    //
    g_sNextUpload.pcStart =
                (unsigned char *)readLong(&(g_sDFUDeviceInfo.ulAppStartAddr));
    g_sNextUpload.ulLength = (readLong(&(g_sDFUDeviceInfo.ulFlashTop)) -
                              readLong(&(g_sDFUDeviceInfo.ulAppStartAddr)));
}

//*****************************************************************************
//
//! Check that a range of addresses passed is within the region of flash that
//! the boot loader is allowed to access.
//!
//! \param ulStart Starting address of flash range to be checked
//! \param ulLength Length of flash range to be checked
//!
//! \return True if the address range is accessible or false otherwise.
//
//*****************************************************************************
tBoolean
FlashRangeCheck(unsigned long ulStart, unsigned long ulLength)
{        


    if((ulStart >= readLong(&(g_sDFUDeviceInfo.ulAppStartAddr))) && 
       (ulLength <= (readLong(&(g_sDFUDeviceInfo.ulFlashTop)) - 
       readLong(&(g_sDFUDeviceInfo.ulAppStartAddr)))) &&
       ((ulStart + ulLength) <= readLong(&(g_sDFUDeviceInfo.ulFlashTop))))   
    {
        //
        // The block passed lies wholly within the flash address range of
        // this device.
        //
        return(true);
    }
    else
    {
        //
        // We were passed an address that is out of range so set the
        // appropriate status code.
        //
        g_eDFUStatus = STATUS_ERR_ADDRESS;
        return(false);
    }
}

//*****************************************************************************
//
//! Flash API callback (used to kick the watchdog)
//
//*****************************************************************************
#ifdef ENABLE_WATCHDOG
void 
FlashAPICallback(void)
{
    //
    // Kick the watchdog
    //
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;        
}
#endif

//*****************************************************************************
//
//! Initialize variables needed by the flash api
//
//*****************************************************************************
void 
FlashAPIInit(void)
{
    EALLOW;
    Flash_CPUScaleFactor = SCALE_FACTOR;
#ifdef ENABLE_WATCHDOG    
    Flash_CallbackPtr = FlashAPICallback;
#else
    Flash_CallbackPtr = 0;
#endif    
    EDIS;    
    
}

//*****************************************************************************
//
//! Get the sector index given a start address and size
//!
//! \param ulAddress is the address of the block of flash to erase.
//! \param ulSize is the size of the block of memory to return the index for
//!
//! This function converts and address and size into the index format used
//! by the flash erase function.
//!
//! \return Index for use with flash erase function
//
//*****************************************************************************
unsigned long
FlashAPIIndex(unsigned long ulAddress, unsigned long ulSize)
{
    volatile unsigned long ulIdx;
    volatile unsigned long ulTemp;
    
    //
    // Runtime check
    //
    if((ulAddress < FLASH_START_ADDR) || 
       ((ulAddress + ulSize) > FLASH_END_ADDR))
        return 0;
        
    ulTemp = 0;

    for(ulIdx = FLASH_START_ADDR ; ulIdx <= FLASH_END_ADDR ; 
        ulIdx += FLASH_PAGE_SIZE)
    {
        if((ulIdx >= (unsigned long)ulAddress) && 
           (ulIdx <= ((unsigned long)ulAddress + ulSize)))
        {
            ulTemp = (ulTemp << 1) | 1;
        }        
    }
    return ulTemp;
}

#ifdef ENABLE_WATCHDOG
//*****************************************************************************
//
//! Enable the watchdog timer
//
//*****************************************************************************
void
WatchdogEnable(void)
{
    EALLOW;
    
    //
    // Enable the watchdog
    //
    SysCtrlRegs.WDCR = 0x4E;
    EDIS;
}
#endif


#ifdef ENABLE_CSM_CONTROL
//*****************************************************************************
//
//! Generate a seed for CSM authentication
//
//*****************************************************************************
void
GenerateSeed(void)
{
    volatile unsigned char i;
    
    //
    // Stir up the random number generator
    //
    srand(i);
    srand(rand() % 0xFFFF);
    
    //
    // Create seed
    //
    for(i=0; i<16; i++)
    {
        g_pucSeedBuffer[i] = rand() % 0xFF;    
    }
}

//*****************************************************************************
//
//! Calculate the key for a given seed
//
//*****************************************************************************
void
GenerateKey(void)
{
#if KEY_FORM == KEY_SET
    //
    // Set the key to use for encryption
    //
    aes_setkey_enc(&g_aesCtx, g_ucKey, 128);
    
    //
    // Encrypt the seed
    //
    aes_crypt_ecb(&g_aesCtx, AES_ENCRYPT, g_pucSeedBuffer,
                  g_pucKeyBuffer);
    
#else
    const unsigned long * puKey;
    //
    // Get the expanded key to use for encryption
    //
    puKey = AESExpandedEncryptKeyData();
    
    //
    // Encrypt the seed
    //
    aes_crypt_ecb(puKey, AES_ENCRYPT, g_pucSeedBuffer,
                  g_pucKeyBuffer);

#endif    
    
}

//*****************************************************************************
//
//! Unlock the device's code security module
//
//*****************************************************************************
void
UnlockDevice(void)
{
    volatile unsigned long ulTemp;
    EALLOW;
    
    //
    // Write the key locations
    //
    CsmRegs.KEY0 = PWL0;
    CsmRegs.KEY1 = PWL1;
    CsmRegs.KEY2 = PWL2;
    CsmRegs.KEY3 = PWL3;
    CsmRegs.KEY4 = PWL4;
    CsmRegs.KEY5 = PWL5;
    CsmRegs.KEY6 = PWL6;
    CsmRegs.KEY7 = PWL7;
    
    //
    // Read password locations
    //
    ulTemp = CsmPwl.PSWD0;
    ulTemp = CsmPwl.PSWD1;
    ulTemp = CsmPwl.PSWD2;
    ulTemp = CsmPwl.PSWD3;
    ulTemp = CsmPwl.PSWD4;
    ulTemp = CsmPwl.PSWD5;
    ulTemp = CsmPwl.PSWD6;
    ulTemp = CsmPwl.PSWD7;
    EDIS;
    
    //
    // Wait while device unlocks
    //
    while(CsmRegs.CSMSCR.bit.SECURE);
    
    //
    // Report unlock status in device structure
    //
    g_sDFUDeviceInfo.ucLocked = 0;
    
}
#endif

//*****************************************************************************
//
//! Process TI-specific commands passed via DFU download requests.
//!
//! \param pcCmd is a pointer to the first byte of the \b DFU_DNLOAD payload
//! that is expected to hold a command.
//! \param ulSize is the number of bytes of data pointed to by \e pcCmd.
//! This function is called when a DFU download command is received while in
//! \b STATE_IDLE.  New downloads are assumed to contain a prefix structure
//! containing one of several TI-specific commands and this function
//! is responsible for parsing the download data and processing whichever
//! command is contained within it.
//!
//! \return Returns \b true on success or \b false on failure.
//
//*****************************************************************************
tBoolean
ProcessDFUDnloadCommand(tDFUDownloadHeader *pcCmd, unsigned long ulSize)
{
    //
    // Make sure we got enough data to contain a valid command header.
    //
    if(ulSize < sizeof(tDFUDownloadHeader))
    {
        return(false);
    }

    //
    // Remember the command that we have been passed since we will need thi
    // to determine which state to transition to on exit from STATE_DNLOAD_SYNC.
    //
    g_ucLastCommand = pcCmd->ucCommand;

    //
    // Which command have we been passed?
    //
    switch(pcCmd->ucCommand)
    {
        //
        // We are being asked to start a programming operation.
        //
        case DFU_CMD_PROG:
        {
            tDFUDownloadProgHeader *psHdr;

            //
            // Extract the address and size from the command header.
            //
            psHdr = (tDFUDownloadProgHeader *)pcCmd;

            //
            // Is the passed address range valid?
            //
            if(FlashRangeCheck((unsigned long)readShort(&(psHdr->usStartAddr)) * 1024,
                                readLong(&(psHdr->ulLength))))
            {
                //
                // Yes - remember the range passed so that we will write the
                // passed data to the correct place.
                //
                g_sNextDownload.pcStart =
                    (unsigned char *)((unsigned long)readShort(&(psHdr->usStartAddr)) * 1024);
                g_sNextDownload.ulLength = readLong(&(psHdr->ulLength));

                //
                // If we have been provided with a progress reporting hook
                // function, remember the total length of the image so that
                // we can report this later.
                //
#ifdef BL_PROGRESS_FN_HOOK
                g_ulImageSize = psHdr->ulLength;
#endif

                //
                // Also set the upload address and size to match this download
                // so that, by default, the host will get back what it just
                // wrote if it performs an upload without an intermediate
                // DFU_CMD_READ to set the address and size.
                //
                g_sNextUpload.pcStart =
                    (unsigned char *)((unsigned long)readShort(&(psHdr->usStartAddr)) * 1024);
                g_sNextUpload.ulLength = readLong(&(psHdr->ulLength));

                //
                // Also remember that we have data in this packet to write.
                //
                g_pcDFUWrite = (unsigned char *)(psHdr + 1);
                g_usDFUBufferUsed = ulSize - sizeof(tDFUDownloadHeader);

                //
                // If a start signal hook function has been provided, call it
                // here since we are about to start a new download.
                //
#ifdef BL_START_FN_HOOK
                BL_START_FN_HOOK();
#endif

                //
                // Tell the main thread to write the data we just received it.
                //
                HWREGBITW(&g_ulCommandFlags, CMD_FLAG_WRITE, 1);
            }
            else
            {
                //
                // The flash range was invalid so switch to error state.
                //
                return(false);
            }
            break;
        }
        
#ifdef ENABLE_READ
        //
        // We are being passed the position and size of a block of flash to
        // return in a following upload operation.
        //
        case DFU_CMD_READ:
        {
            tDFUDownloadReadCheckHeader *psHdr;

            //
            // Extract the address and size from the command header.
            //
            psHdr = (tDFUDownloadReadCheckHeader *)pcCmd;

            //
            // Is the passed address range valid and the flash unlocked
            //
            if(FlashRangeCheck((unsigned long)readShort(&(psHdr->usStartAddr)) * 1024,
               readLong(&(psHdr->ulLength))))
            {
                //
                // Yes - remember the range passed so that we will return
                // this block of flash on the next upload request.
                //
                g_sNextUpload.pcStart =
                    (unsigned char *)((unsigned long)readShort(&(psHdr->usStartAddr)) * 1024);
                g_sNextUpload.ulLength = readLong(&(psHdr->ulLength));
            }
            else
            {
                //
                // The flash range was invalid so switch to error state.
                //
                return(false);
            }
            break;
        }
#endif

        //
        // We are being passed the position and size of a block of flash which
        // we will check to ensure that it is erased.
        //
        case DFU_CMD_CHECK:
        {
            tDFUDownloadReadCheckHeader *psHdr;
            unsigned short *pusCheck;
            unsigned long ulLoop;

            //
            // Extract the address and size from the command header.
            //
            psHdr = (tDFUDownloadReadCheckHeader *)pcCmd;

            //
            // Make sure the range we have been passed is within the area of
            // flash that we are allowed to look at.
            //
            if(FlashRangeCheck((unsigned long)readShort(&(psHdr->usStartAddr)) * 1024,
               readLong(&(psHdr->ulLength))))
            {
                //
                // The range is valid so perform the check here.
                //
                pusCheck = (unsigned short *)((unsigned long)readShort(&(psHdr->usStartAddr)) * 1024);

                //
                // Check each word in the range to ensure that it is erased.  
                // If not, set the error status and return.
                //
                for(ulLoop = 0; (ulLoop < readLong(&(psHdr->ulLength))) && 
                    ((unsigned long) pusCheck < 0x3F7F80); ulLoop++)
                {
                    if(*pusCheck != 0xFFFF)
                    {
                        g_eDFUStatus = STATUS_ERR_CHECK_ERASED;
                        return(false);
                    }
                    pusCheck++;
                }

                //
                // If we get here, the check passed so set the status to
                // indicate this.
                //
                g_eDFUStatus = STATUS_OK;
            }
            else
            {
                //
                // The flash range was invalid so switch to error state.
                //
                return(false);
            }
            break;
        }

        //
        // We are being asked to erase a block of flash.
        //
        case DFU_CMD_ERASE:
        {
            tDFUDownloadEraseHeader *psHdr;
            volatile unsigned short usTemp;
            //
            // Extract the address and size from the command header.
            //
            psHdr = (tDFUDownloadEraseHeader *)pcCmd;

            usTemp = readShort(&(psHdr->usNumBlocks));
            //
            // Make sure the range we have been passed is within the area of
            // flash that we are allowed to look at.
            //
            if(FlashRangeCheck((unsigned long)readShort(&(psHdr->usStartAddr)) * 1024,
                               ((unsigned long)readShort(&(psHdr->usNumBlocks)) *
                                1024 )))
            {
                //
                // The range is valid so tell the main loop to erase the
                // block.
                //
                g_sErase.pcStart =(unsigned char *)
                                   ((unsigned long)readShort(&(psHdr->usStartAddr)) * 1024);
                g_sErase.ulLength = ((unsigned long)readShort(&(psHdr->usNumBlocks)) *
                                     1024);
                HWREGBITW(&g_ulCommandFlags, CMD_FLAG_ERASE, 1);
            }
            else
            {
                //
                // The flash range was invalid so switch to error state.
                //
                return(false);
            }
            break;
        }

        //
        // We are being asked to send back device information on the next
        // upload request.
        //
        case DFU_CMD_INFO:
        {
            //
            // Update lock status
            //
            g_sDFUDeviceInfo.ucLocked = CsmRegs.CSMSCR.bit.SECURE;
    
            //
            // Register that we need to send the device info structure on the
            // next upload request.
            //
            g_sNextUpload.pcStart = (unsigned char *)&g_sDFUDeviceInfo;
            g_sNextUpload.ulLength = sizeof(tDFUDeviceInfo);

            //
            // Make sure we don't append the DFU_CMD_PROG header when we send
            // back the data.
            //
            g_bSuppressUploadHeader = true;
            break;
        }

        //
        // We are being asked to set the format of uploaded images.
        //
        case DFU_CMD_BIN:
        {
            tDFUDownloadBinHeader *psHdr;

            //
            // Extract the requried format the command header.
            //
            psHdr = (tDFUDownloadBinHeader *)pcCmd;

            //
            // Set the global format appropriately.
            //
            g_bUploadBinary = psHdr->bBinary ? true : false;
            break;
        }

#ifdef ENABLE_CSM_CONTROL        
        //
        // We are being asked to lock or unlock flash
        //
        case DFU_CMD_CSM:
        {
            tDFUDownloadCSMHeader *psHdr;

            //
            // Extract the requried format the command header.
            //
            psHdr = (tDFUDownloadCSMHeader *)pcCmd;
            
            //
            // Are we locking the device
            //
            if(psHdr->ucLock)
            {
                //
                // If so lock it
                //
                CsmRegs.CSMSCR.bit.FORCESEC = 1;
            }
            else
            {
                if(psHdr->ucSize == 16)
                {
                    //
                    // Copy pointer to received key
                    //
                    g_pucReceivedKey = (unsigned char *)(psHdr + 1);
                    
                    //
                    // Tell the main thread to check the key    
                    //
                    HWREGBITW(&g_ulCommandFlags, CMD_FLAG_CSM, 1);
                    
                }
                else
                {
                    //
                    // Generate and send seed
                    //
                    GenerateSeed();
                    g_bUploadBinary = true;
                    g_sNextUpload.pcStart =  g_pucSeedBuffer;
                    g_sNextUpload.ulLength = 16;
                    
                }
                
            }
            break;
        }        
#endif

        //
        // We are being asked to prepare to reset the board and, as a result,
        // run the main application image.
        //
        case DFU_CMD_RESET:
        {
            //
            // Tell the main thread that it's time to go bye-bye...
            //
            HWREGBITW(&g_ulCommandFlags, CMD_FLAG_RESET, 1);

            break;
        }

        //
        // We have been passed an unrecognized command identifier so report an
        // error.
        //
        default:
        {
            g_eDFUStatus = STATUS_ERR_VENDOR;
            return(false);
        }
    }

    return(true);
}

//*****************************************************************************
//
//! EP0 Data callback
//!
//! \param ulSize The size of data available in EP0.
//! 
//! This callback function is called when data is received for the DATA phase
//! of an EP0 OUT transaction.  This data will either be a block of download
//! data (if we are in STATE_DNLOAD_IDLE) or a new command (if we are in
//! STATE_IDLE).
//
//*****************************************************************************
void
HandleEP0Data(unsigned long ulSize)
{
    tBoolean bRetcode;

    if(g_eDFUState == STATE_IDLE)
    {
        //
        // This must be a new DFU download command header so parse it and
        // determine what to do next.
        //
        bRetcode = ProcessDFUDnloadCommand((tDFUDownloadHeader *)g_pcDFUBuffer,
                                           ulSize);

        //
        // Did we receive a recognized and valid command?
        //
        if(!bRetcode)
        {
            //
            // No - set the error state.  The status is set within the
            // ProcessDFUDnloadCommand() function.
            //
            g_eDFUState = STATE_ERROR;
            return;
        }
    }
    else
    {
        //
        // If we are not in STATE_IDLE, this must be a block of data for an
        // ongoing download so signal the main thread to write it to flash.
        //
        g_usDFUBufferUsed = (unsigned short)ulSize;
        g_pcDFUWrite = g_pcDFUBuffer;

        //
        // Tell the main thread to write the new data.
        //
        HWREGBITW(&g_ulCommandFlags, CMD_FLAG_WRITE, 1);
    }

    //
    // Move to STATE_DNLOAD_SYNC since we now expect USBD_DFU_REQUEST_GETSTATUS
    // before the next USBD_DFU_REQUEST_DNLOAD.
    //
    g_eDFUState = STATE_DNLOAD_SYNC;
}

//*****************************************************************************
//
//! Handle bus resets
//!
//! This function is called if the USB controller detects a reset condition on
//! the bus.  If we are not in the process of downloading a new image, we use
//! this as a signal to reboot and run the main application image.
//
//*****************************************************************************
void
HandleReset(void)
{
    //
    // Are we currently in the middle of a download operation?
    //
    if((g_eDFUState != STATE_DNLOAD_IDLE) && (g_eDFUState != STATE_DNLOAD_SYNC) &&
       (g_eDFUState != STATE_IDLE))
    {
        //
        // No - tell the main thread that it should reboot the system assuming
        // that we are already configured.  If we don't check that we are
        // already configured, this will cause a reset during initial
        // enumeration and that wouldn't be very helpful.
        //
        if(g_bAddressSet)
        {
            HWREGBITW(&g_ulCommandFlags, CMD_FLAG_RESET, 1);
        }
    }
    else
    {
        g_eDFUState = STATE_IDLE;
    }
}

//*****************************************************************************
//
//! Handle cases where the USB host disconnects.
//
//*****************************************************************************
void
HandleDisconnect(void)
{
    //
    // For error resilience, it may be desireable to note if the host
    // disconnects and, if partway through a main image download, clear the
    // first block of the flash to ensure that the image is not considered
    // valid on the next boot.  For now, however, we merely wait for the host
    // to connect again, remaining in DFU mode.
    //

    //
    // Remember that we are waiting for enumeration.
    //
    g_bAddressSet = false;
}

//*****************************************************************************
//
//! Compact a byte array (0x00XX, 0x00YY) into a word array (0xXXYY)
//! 
//! \param pucBuffer Buffer to compact
//! \param ulBufferSize Buffer size before compaction
//
//*****************************************************************************
void
CompactBuffer(unsigned char *pucBuffer, unsigned long ulBufferSize)
{
    unsigned char *pucCurrentByte, *pucDestWord;
    
    pucDestWord = pucBuffer;
    pucCurrentByte = pucBuffer;
    
    for(;pucDestWord < pucBuffer + (ulBufferSize/2);)
    {
        *pucDestWord++ = ((*pucCurrentByte & 0xFF) << 8) | 
                         (*(pucCurrentByte + 1) & 0xFF);
        pucCurrentByte += 2;
    }
}

#ifdef ENABLE_FAILSAFE
//*****************************************************************************
//
//! Copy the bootloader from flash sector H to flash sector G
//
//*****************************************************************************
void
CopyBLHtoG(void)
{
    //
    // Copy Bootloader entry table
    //
    MemCopy((Uint16 *)&BLTableStart, (Uint16 *)&BLTableEnd,
            (Uint16 *)g_pcCopyBuffer);
    Flash2806x_Program((Uint16 *)&BLTableStart+0x4000, 
                       (Uint16 *) g_pcCopyBuffer, 
                       (unsigned long)&BLTableEnd - 
                       (unsigned long)&BLTableStart, 
                       &g_FlashStatus);
    
    //
    // Copy Init Section
    //
    MemCopy((Uint16 *)&InitLoadStart, (Uint16 *)&InitLoadEnd, 
            (Uint16 *)g_pcCopyBuffer);
    Flash2806x_Program((Uint16 *)&InitLoadStart+0x4000, 
                       (Uint16 *) g_pcCopyBuffer, 
                       (unsigned long)&InitLoadEnd - 
                       (unsigned long)&InitLoadStart, 
                       &g_FlashStatus);
    //
    // Copy BL Kernel
    //
    MemCopy((Uint16 *)&RamfuncsLoadStart, (Uint16 *)&RamfuncsLoadEnd, 
            (Uint16 *)g_pcCopyBuffer);
    Flash2806x_Program((Uint16 *)&RamfuncsLoadStart+0x4000, 
                       (Uint16 *) g_pcCopyBuffer, 
                       (unsigned long)&RamfuncsLoadEnd - 
                       (unsigned long)&RamfuncsLoadStart, 
                       &g_FlashStatus);
    //                        
    // Copy Failsafe Entry
    //
    MemCopy((Uint16 *)&FailsafeLoadStart, (Uint16 *)&FailsafeLoadEnd,
            (Uint16 *)g_pcCopyBuffer);
    Flash2806x_Program((Uint16 *)&FailsafeRunStart, 
                       (Uint16 *) g_pcCopyBuffer, 
                       (unsigned long)&FailsafeLoadEnd - 
                       (unsigned long)&FailsafeLoadStart, 
                       &g_FlashStatus);                             
}

//*****************************************************************************
//
//! Copy the bootloader from flash sector G to flash sector H
//
//*****************************************************************************
void CopyBLGtoH(void)
{
    //
    // Copy Bootloader entry table
    //
    FailSafeMemCopy((Uint16 *)&BLTableStart+0x4000, (Uint16 *)&BLTableEnd+0x4000, 
                    (Uint16 *)g_pcCopyBuffer);
    Flash2806x_Program((Uint16 *)&BLTableStart, 
                       (Uint16 *) g_pcCopyBuffer, 
                       (unsigned long)&BLTableEnd - (unsigned long)&BLTableStart, 
                       &g_FlashStatus);
    
    //
    // Copy Init Section
    //
    FailSafeMemCopy((Uint16 *)&InitLoadStart+0x4000, (Uint16 *)&InitLoadEnd+0x4000, 
                    (Uint16 *)g_pcCopyBuffer);
    Flash2806x_Program((Uint16 *)&InitLoadStart, 
                       (Uint16 *) g_pcCopyBuffer, 
                       (unsigned long)&InitLoadEnd - (unsigned long)&InitLoadStart, 
                       &g_FlashStatus);

    // Copy BL Kernel
    FailSafeMemCopy((Uint16 *)&RamfuncsLoadStart+0x4000, (Uint16 *)&RamfuncsLoadEnd+0x4000, 
                    (Uint16 *)g_pcCopyBuffer);
    Flash2806x_Program((Uint16 *)&RamfuncsLoadStart, 
                       (Uint16 *) g_pcCopyBuffer, 
                       (unsigned long)&RamfuncsLoadEnd - (unsigned long)&RamfuncsLoadStart, 
                       &g_FlashStatus);

    // Copy Failsafe Entry
    FailSafeMemCopy((Uint16 *)&FailsafeRunStart, (Uint16 *)&FailsafeRunStart+
                    (unsigned long)&FailsafeLoadEnd - (unsigned long)&FailsafeLoadStart, 
                    (Uint16 *)g_pcCopyBuffer);
    Flash2806x_Program((Uint16 *)&FailsafeLoadStart, 
                       (Uint16 *) g_pcCopyBuffer, 
                       (unsigned long)&FailsafeLoadEnd - (unsigned long)&FailsafeLoadStart, 
                       &g_FlashStatus);                   
}

//*****************************************************************************
//
//! Erase and program sector A of flash with the entry point for the failsafe
//! bootloader.
//
//*****************************************************************************
void
ProgramBLFailsafeVector(void)
{                                              
    //
    // Copy Failsafe Codestart
    //
    MemCopy((Uint16 *)&code_start_f, (Uint16 *)(&code_start_f + 1), 
            (Uint16 *)g_pcCopyBuffer); 
    
    //
    // Erase Sector A
    //
    Flash2806x_Erase(0x01, &g_FlashStatus);
    
    //
    // Program Boot to Flash Vector with Failsafe codestart
    //
    Flash2806x_Program((Uint16 *)0x3F7FF6, 
                       (Uint16 *) g_pcCopyBuffer, 
                        2, 
                       &g_FlashStatus);
}
#endif

//*****************************************************************************
//
//! Erase and program sector A of flash with the entry point for the normal
//! bootloader.
//
//*****************************************************************************
void
ProgramBLNormalVector(void)
{
    //
    // Copy Failsafe Codestart                                             
    //
    MemCopy((Uint16 *)&code_start_n, (Uint16 *)(&code_start_n + 1), 
            (Uint16 *)g_pcCopyBuffer); 
    
    //
    // Erase Sector A
    //
    Flash2806x_Erase(0x01, &g_FlashStatus);
    
    //
    // Program Boot to Flash Vector with Normal codestart
    //
    Flash2806x_Program((Uint16 *)0x3F7FF6, 
                       (Uint16 *) g_pcCopyBuffer, 
                        2, 
                       &g_FlashStatus);
}

//*****************************************************************************
//
//! This is the main routine for handling updating over USB.
//!
//! This function forms the main loop of the USB DFU updater.  It polls for
//! commands sent from the USB request handlers and is responsible for
//! erasing flash blocks, programming data into erased blocks and resetting
//! the device.
//!
//! \return None.
//
//*****************************************************************************
void
UpdaterUSB(void)
{
    unsigned long  ulStart, ulTemp;
    unsigned short usUsed;

    usUsed = 0;

    //
    // Initialize Flash functions
    //
    FlashAPIInit();

    //
    // Loop forever waiting for the USB interrupt handlers to tell us to do
    // something.
    //
    while(1)
    {
        while((g_ulCommandFlags & 0xFFFF) == 0)
        {
            //
            // Wait for something to do.
            //
#ifdef ENABLE_WATCHDOG
            EALLOW;
            SysCtrlRegs.WDKEY = 0x0055;
            SysCtrlRegs.WDKEY = 0x00AA;
            EDIS;        
#endif                        
        }

        //
        // Are we being asked to perform a system reset?
        //
        if(HWREGBITR(&g_ulCommandFlags, CMD_FLAG_RESET))
        {
            //
            // Time to go bye-bye...  This will cause the microcontroller
            // to reset; no further code will be executed.
            //
            
            //
            // Enable watchdog reset
            //
            SysCtrlRegs.SCSR &= ~0x02;
            
            //
            // Enable the Watchdog
            //
            SysCtrlRegs.WDCR = 0x28;
            
            //
            // Force a reset
            //
            SysCtrlRegs.WDCR = 0x00;

            //
            // The microcontroller should have reset, so this should never be
            // reached.  Just in case, loop forever.
            //
            while(1)
            {
                
            }
        }

#ifdef ENABLE_CSM_CONTROL        
        //
        // Are we being asked to unlock CSM
        //
        if(HWREGBITR(&g_ulCommandFlags, CMD_FLAG_CSM))
        {
            GenerateKey();
            for(ulTemp = 0; ulTemp<16; ulTemp++)
            {
                if(g_pucKeyBuffer[ulTemp]!= g_pucReceivedKey[ulTemp])
                {
                    break;
                }
            }
            
            if(ulTemp == 16)
            {
                UnlockDevice();
            }
            
            //
            // Clear the command flag to indicate that we are done.
            //
            HWREGBITW(&g_ulCommandFlags, CMD_FLAG_CSM, 0);            
        }
#endif        

        //
        // Are we being asked to erase a range of blocks in flash?
        //
        if(HWREGBITR(&g_ulCommandFlags, CMD_FLAG_ERASE))
        {
#ifdef ENABLE_FAILSAFE
            //
            // Are we NOT in failsafe mode?
            //
            if(!g_bFailsafe)
            {
                //
                // If so, erase sectors B through G
                //
                Flash2806x_Erase(0x7E, &g_FlashStatus);

                CopyBLHtoG();
                
                ProgramBLFailsafeVector();

                //                
                // Set failsafe flag
                //
                g_bFailsafe = true;
            }
            
            //
            // Erase normal bootloader sector (H)
            //
            Flash2806x_Erase(0x80, &g_FlashStatus);
            
            CopyBLGtoH();
            ProgramBLNormalVector();
            
            //
            // Erase the failsafe copy of the bootloader
            //
            Flash2806x_Erase(0x40, &g_FlashStatus);
            g_bFailsafe = false;
#else                
            //
            // Figure out what to erase
            //
            ulTemp = FlashAPIIndex((unsigned long)g_sErase.pcStart, g_sErase.ulLength);
            
            //
            // Are we erasing sector A
            //
            if(ulTemp & 0x01)
            {
                // 
                // Erase sector A and reprogram reset vector
                //
                ProgramBLNormalVector();
            }
            ulTemp &= 0x7E;
            
            //
            // erase the rest of flash
            //
            Flash2806x_Erase(ulTemp, &g_FlashStatus);

#endif                
            //
            // Clear the command flag to indicate that we are done.
            //
            HWREGBITW(&g_ulCommandFlags, CMD_FLAG_ERASE, 0);
        }

        //
        // Are we being asked to program a block of flash?
        //
        if(HWREGBITR(&g_ulCommandFlags, CMD_FLAG_WRITE))
        {
            //
            // Decrypt the data if required.
            //
#ifdef BL_DECRYPT_FN_HOOK
            BL_DECRYPT_FN_HOOK(g_pcDFUWrite, g_usDFUBufferUsed);
#endif
            //
            // Where will the new block be written?
            //
            ulStart = (unsigned long)(g_sNextDownload.pcStart);

            usUsed = g_usDFUBufferUsed/2;

            // 
            // Compact buffer from bytes into words
            //
            CompactBuffer(g_pcDFUWrite, g_usDFUBufferUsed);

            //
            // Check for programming of the boot to flash location
            //
            if((ulStart < 0x3F7FF6) && ((ulStart + usUsed) > 0x3F7FF6))
            {
                //
            	// adjust programming to program around boot to flash location
                //

				//
				// Write the new block of data to the flash before the begin 
                // location
				//
				if(Flash2806x_Program((Uint16 *)ulStart, (Uint16 *) g_pcDFUWrite,
                  (0x3F7FF6 - ulStart), &g_FlashStatus))
				{
                    //
					// Programming Failed for some reason, enter error state
                    //
					g_eDFUState = STATE_ERROR;
					g_eDFUStatus = STATUS_ERR_PROG;

				}
                else
                {
					//
					// Write the new block of data to the flash after the begin
                    // location (CSM)
					//
					if(Flash2806x_Program((Uint16 *)ulStart + 
                       (0x3F7FF6 - ulStart) + 0x02, 
                       (Uint16 *) ((unsigned long)g_pcDFUWrite + 
                       (0x3F7FF6 - ulStart) + 0x02), 
                       (usUsed - ((0x3F7FF6 - ulStart) + 0x02)), 
                       &g_FlashStatus))
					{
                        //
						// Programming Failed for some reason, enter error
                        // state
                        // 
						g_eDFUState = STATE_ERROR;
						g_eDFUStatus = STATUS_ERR_PROG;
					}
				}

            }
            else
            {
	            //
	            // Write the new block of data to the flash
	            //
	            if(Flash2806x_Program((Uint16 *)ulStart, 
                   (Uint16 *) g_pcDFUWrite, usUsed, &g_FlashStatus))
	            {
                    //
	                // Programming Failed for some reason, enter error state
                    //
	                g_eDFUState = STATE_ERROR;
	                g_eDFUStatus = STATUS_ERR_PROG;
	            }
            }
    
            //
            // Update our position and remaining size.
            //
            g_sNextDownload.pcStart += usUsed;
            g_sNextDownload.ulLength -= usUsed;

            //
            // Clear the command flag to indicate that we are done.
            //
            HWREGBITW(&g_ulCommandFlags, CMD_FLAG_WRITE, 0);

            //
            // If a progress hook function has been provided, call
            // it here.
            //
#ifdef BL_PROGRESS_FN_HOOK
            BL_PROGRESS_FN_HOOK(g_ulImageSize - g_sNextDownload.ulLength,
                                g_ulImageSize);
#endif

            //
            // If we just finished the download and an end signal hook function
            // has been provided, call it too.
            //
#ifdef BL_END_FN_HOOK
            if(g_sNextDownload.ulLength == 0)
            {
                BL_END_FN_HOOK();
            }
#endif
        }
    }
}

//*****************************************************************************
//
//! Configure the USB controller and place the DFU device on the bus.
//!
//! This function configures the USB controller for DFU device operation,
//! initializes the state machines required to control the firmware update and
//! places the device on the bus in preparation for requests from the host.  It
//! is assumed that the main system clock has been configured at this point.
//!
//! \return None.
//
//*****************************************************************************
void
ConfigureUSBInterface(void)
{
    unsigned long ulTemp = 0;
    
    //
    // Initialize our device information structure.
    //
    writeShort(&(g_sDFUDeviceInfo.usFlashBlockSize), DFU_REPORTED_PAGE_SIZE);
    writeShort(&(g_sDFUDeviceInfo.usNumFlashBlocks), 
                (FLASH_END_ADDR - FLASH_START_ADDR) / DFU_REPORTED_PAGE_SIZE);
    writeLong(&(g_sDFUDeviceInfo.ulClassInfo), DevEmuRegs.CLASSID.all);
    writeLong(&(g_sDFUDeviceInfo.ulPartInfo),  PartIdRegs.PARTID.all);
    writeLong(&(g_sDFUDeviceInfo.ulAppStartAddr), APP_START_ADDRESS);
    writeLong(&(g_sDFUDeviceInfo.ulFlashTop), FLASH_END_ADDR);

    g_sDFUDeviceInfo.ucLocked = CsmRegs.CSMSCR.bit.SECURE;
    
#ifdef ENABLE_FAILSAFE    
    ulTemp |= TI_FEATURE_FAILSAFE;
#endif
#ifdef ENABLE_CSM_CONTROL
    ulTemp |= TI_FEATURE_CSM_CONTROL;
#endif
#ifdef ENABLE_READ
    ulTemp |= TI_FEATURE_READ;
#endif
#ifdef ENABLE_DECRYPTION
    ulTemp |= TI_FEATURE_DECRYPTION;
#endif

    writeLong(&(g_sDFUDeviceInfo.ulFeatures), ulTemp);
    
    //
    // Publish our DFU device descriptors and place the device on the bus.
    //
    USBBLInit();
}

#if (defined USB_HAS_MUX) || (defined DOXYGEN)
//*****************************************************************************
//
//! Configures and set the mux selecting USB device-mode operation.
//!
//! On target boards which use a multiplexer to switch between USB host and
//! device operation, this function is used to configure the relevant GPIO
//! pin and drive it such that the mux selects USB device-mode operation.
//! If \b USB_HAS_MUX is not defined in bl_config.h, this function is compiled
//! out.
//!
//! \return None.
//
//*****************************************************************************
static void
SetUSBMux(void)
{

    //
    // Make the pin be an output.
    //
#if USB_MUX_PIN > 31
    GpioCtrlRegs.GPBDIR.all |= (1 << (USB_MUX_PIN - 32));
#else
    GpioCtrlRegs.GPADIR.all |= (1 << USB_MUX_PIN);
#endif

#if USB_MUX_PIN < 16
    GpioCtrlRegs.GPAMUX1.all &= ~(3 << (2 * USB_MUX_PIN));
#elif USB_MUX_PIN < 32
    GpioCtrlRegs.GPAMUX2.all &= ~(3 << (2 * (USB_MUX_PIN - 16)));
#elif USB_MUX_PIN < 48
    GpioCtrlRegs.GPBMUX1.all &= ~(3 << (2 * (USB_MUX_PIN - 32)));
#else
    GpioCtrlRegs.GPBMUX2.all &= ~(3 << (2 * (USB_MUX_PIN - 48)));
#endif

    //
    // Write the pin to the appropriate level to select USB device mode.
    //
    
    //
    // Clear out previous state
    // Assert new state   
    //
#if USB_MUX_PIN > 31
    GpioDataRegs.GPBDAT.all &= ~(1 << (USB_MUX_PIN - 32));
    GpioDataRegs.GPBDAT.all |= (USB_MUX_DEVICE << (USB_MUX_PIN - 32));
#else
    GpioDataRegs.GPADAT.all &= ~(1 << USB_MUX_PIN);
    GpioDataRegs.GPADAT.all |= (USB_MUX_DEVICE << USB_MUX_PIN);
#endif
                       
}
#endif

//*****************************************************************************
//
//! Generic configuration is handled in this function.
//!
//! This function is called by the start up code to perform any configuration
//! necessary before calling the update routine.  It is responsible for setting
//! the system clock to the expected rate and setting flash programming
//! parameters prior to calling ConfigureUSBInterface() to set up the USB
//! hardware and place the DFU device on the bus.
//!
//! \b IMPORTANT: If using a F28069M Launchpad, the Launchpad doesn't have an
//! external oscillator populated. Running this will result in a missing clock
//! NMI. Although for USB an external oscillator is recommended, for Launchpad
//! use, switch the following code to use the internal oscillator or XCLKINs.
//!
//! \return None.
//
//*****************************************************************************
void
ConfigureUSB(void)
{
    //
    // Enable the main oscillator.
    //
    EALLOW;
    SysCtrlRegs.CLKCTL.bit.XCLKINOFF = 1;
    SysCtrlRegs.CLKCTL.bit.XTALOSCOFF = 0;
    SysCtrlRegs.CLKCTL.bit.OSCCLKSRC2SEL = 0;
    SysCtrlRegs.CLKCTL.bit.OSCCLKSRCSEL = 1;
    
    //
    // DELAY_US while the main oscillator starts up.
    //
    DELAY_US(10);

    //
    // Set the crystal frequency, switch to the main oscillator, and enable the
    // PLL.
    //
    // Setup PLL for 80Mhz
    // Calculate the appropriate multiplier with the given crystal frequency
    //
    while(SysCtrlRegs.PLLSTS.bit.MCLKSTS);
    SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
    SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
    SysCtrlRegs.PLLCR.bit.DIV = 80000000UL/CRYSTAL_FREQ;
    while(!SysCtrlRegs.PLLSTS.bit.PLLLOCKS);
    SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
    SysCtrlRegs.PLLSTS.bit.DIVSEL = 3;

    //
    // DELAY_US while the PLL locks.
    //
    DELAY_US(10);

    //
    // Setup PLL2 for 60Mhz operation
    // Calculate the appropriate multiplier with the given crystal frequency
    //
    SysCtrlRegs.PLL2CTL.bit.PLL2CLKSRCSEL = 2;
    SysCtrlRegs.PLL2CTL.bit.PLL2EN = 1;
    SysCtrlRegs.PLL2MULT.bit.PLL2MULT = 120000000/CRYSTAL_FREQ;
    while(!SysCtrlRegs.PLL2STS.bit.PLL2LOCKS);

    InitPieCtrl();
    InitPieVectTable();
    EDIS;
    //
    // If the target device has a mux to allow selection of USB host or
    // device mode, make sure this is set to device mode.
    //
#ifdef USB_HAS_MUX
    SetUSBMux();
#endif

    //
    // Configure the USB interface and put the device on the bus.
    //
    ConfigureUSBInterface();
}

//*****************************************************************************
//
//! Application Check function
//!
//! This funciton checks the application entry table and if requested the 
//! associated CRC table to ensure that a valid application is programmed 
//! before jumping to it.  If any of the checks fail, the bootloader is entered
//! so that an application image may be programmed.
//
//*****************************************************************************
#pragma CODE_SECTION(AppCheck, "normal")
void AppCheck(void)
{
    if(CheckForceUpdate())
    {
        return;
    }

#ifdef CHECK_CRC    
    if(CheckCRCTable((CRC_TABLE *) pAppSig))
    {
        return;    
    }
#endif
    if(((unsigned long)pAppEntry != 0xFFFFFFFF) && 
       ((unsigned long)pAppEntry    != 0x00000000))
    {
        ((void (*)(void))pAppEntry)();
    }
}

//*****************************************************************************
//
//! This is the application entry point to the USB updater.
//!
//! This function should only be entered from a running application and not
//! when running the boot loader with no application present.  If the
//! calling application supports any USB device function, it must remove
//! itself from the USB bus prior to calling this function.  This function
//! assumes that the calling application has already configured the system
//! clock to run from the PLL.
//!
//! \return None.
//
//*****************************************************************************
#pragma CODE_SECTION(AppUpdaterUSB, "normal")
void
AppUpdaterUSB(void)
{
    g_ulCommandFlags = 0;
    
    MemCopy((Uint16 *)&RamfuncsLoadStart, (Uint16 *)&RamfuncsLoadEnd,
            (Uint16 *)&RamfuncsRunStart);

#ifdef BL_REINIT_FN_HOOK
    BL_REINIT_FN_HOOK(void);
#endif

    //
    // If the target device has a mux to allow selection of USB host or
    // device mode, make sure this is set to device mode.
    //
#ifdef USB_HAS_MUX
    SetUSBMux();
#endif

    //
    // Configure the USB interface and put the device on the bus.
    //
    ConfigureUSBInterface();
    
#ifdef ENABLE_WATCHDOG
    WatchdogEnable();
#endif    

    //
    // Call the main update routine.
    //
    UpdaterUSB();
}

//*****************************************************************************
//
//! This is the normal bootloader entry point
//!
//! \return None.
//
//*****************************************************************************
#pragma CODE_SECTION(main, "normal")
void main(void)
{
    MemCopy((Uint16 *)&RamfuncsLoadStart, (Uint16 *)&RamfuncsLoadEnd, 
            (Uint16 *)&RamfuncsRunStart);

    //
    // Application check and branch
    //
    AppCheck();
    
    g_ulCommandFlags = 0;
    
#ifdef ENABLE_FAILSAFE
    g_bFailsafe = false;
#endif    
    
#ifdef BL_HW_INIT_FN_HOOK
    BL_HW_INIT_FN_HOOK(void);
#endif    

    ConfigureUSB();    
    
#ifdef BL_INIT_FN_HOOK
    BL_INIT_FN_HOOK(void);
#endif    

#ifdef ENABLE_WATCHDOG
    WatchdogEnable();
#endif    
    
    UpdaterUSB();
    
    while(1);
}

#ifdef ENABLE_FAILSAFE
//*****************************************************************************
//
//! This is the failsafe bootloader entry point
//!
//! \return None.
//
//*****************************************************************************
#pragma CODE_SECTION(FailsafeEntry, "failsafe")
void FailsafeEntry(void)
{
    g_ulCommandFlags = 0;
    
    //
    // Set failsafe flag because we are in failsafe mode
    //
    g_bFailsafe = true;
    
    //
    // Copy BL to RAM
    //
    FailSafeMemCopy(&RamfuncsLoadStart + 0x4000, &RamfuncsLoadEnd + 0x4000, 
                    &RamfuncsRunStart);
    
    ConfigureUSB();
    
#ifdef ENABLE_WATCHDOG
    WatchdogEnable();
#endif        

    UpdaterUSB();
    while(1);
}
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//
// End of File
//

