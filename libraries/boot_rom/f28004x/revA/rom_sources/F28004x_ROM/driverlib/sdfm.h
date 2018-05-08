//###########################################################################
//
// FILE:   sdfm.h
//
// TITLE:   C28x SDFM Driver
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################
#ifndef __SDFM_H__
#define __SDFM_H__

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
//! \addtogroup sdfm_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_sdfm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "cpu.h"
#include "interrupt.h"
#include "debug.h"


//! Macro to convert comparator over sampling ratio to acceptable bit location
#define SDFM_SET_OSR(X) (((X) - 1) << 8U)
//! Macro to convert the data shift bit values to acceptable bit location
#define SDFM_SHIFT_VALUE(X) ((X) << 2U)

//! Macro to combine high threshold and low threshold values
#define SDFM_THRESHOLD(H,L) ((((uint32_t)(H)) << 16U) | (L))

//! Macro to set the FIFO level to acceptable bit location
#define SDFM_SET_FIFO_LEVEL(X) ((X) << 7U)

//! Macros to enable or disable filter.
#define SDFM_FILTER_DISABLE     0x0U
#define SDFM_FILTER_ENABLE      0x2U


//! \brief Enumeration to define the Manchester Decoder status
//!
typedef enum
{
    SDFM_MANCHESTER_DECODER_SUCCESS = 0, //!< Manchester Decoder is working
    SDFM_MANCHESTER_DECODER_FAIL = 1     //!< Manchester Decoder has failed
}SDFM_ManchesterDecoderStatus;

//! \brief Enumeration to define the SDFM output threshold status
//!
typedef enum
{
    SDFM_OUTPUT_WITHIN_THRESHOLD = 0,//!< SDFM output is within threshold
    SDFM_OUTPUT_ABOVE_THRESHOLD = 1, //!< SDFM output is above threshold
    SDFM_OUTPUT_BELOW_THRESHOLD = 2  //!< SDFM output is below threshold
}SDFM_OutputThresholdStatus;

//! \brief Enumeration to define the Filter numbers
//!
typedef enum
{
    SDFM_FILTER_1 = 0, //!< Digital filter 1
    SDFM_FILTER_2 = 1, //!< Digital filter 2
    SDFM_FILTER_3 = 2, //!< Digital filter 3
    SDFM_FILTER_4 = 3  //!< Digital filter 4
} SDFM_FilterNumber;

//! \brief Enumeration to define the Digital Filter types
//!
typedef enum
{
    //! Digital filter with SincFast structure.
    SDFM_FILTER_SINC_FAST = (0U << 4U),
    //! Digital filter with Sinc1 structure
    SDFM_FILTER_SINC_1    = (1U << 4U),
    //! Digital filter with Sinc3 structure.
    SDFM_FILTER_SINC_2    = (2U << 4U),
    //! Digital filter with Sinc4 structure.
    SDFM_FILTER_SINC_3    = (3U << 4U)
} SDFM_FilterType;

//! \brief Enumeration to define the Modulator clock mode
//!
typedef enum
{
   //! Modulator clock is identical to the data rate
   SDFM_MODULATOR_CLK_EQUAL_DATA_RATE  = 0,
   //! Modulator clock is half the data rate
   SDFM_MODULATOR_CLK_HALF_DATA_RATE   = 1,
   //! Modulator clock is off. Data is Manchester coded.
   SDFM_MODULATOR_CLK_OFF              = 2,
   //! Modulator clock is double the data rate.
   SDFM_MODULATOR_CLK_DOUBLE_DATA_RATE = 3
}SDFM_ModulatorClockMode;

//! \brief Enumeration to define the filter data output format
//!
typedef enum
{
   //! Filter output is in 16 bits 2's complement format.
   SDFM_DATA_FORMAT_16_BIT = 0,
   //! Filter output is in 32 bits 2's complement format.
   SDFM_DATA_FORMAT_32_BIT = 1
}SDFM_OutputDataFormat;


//! \brief Enumeration to define the Data ready interrupt source
//!
typedef enum
{
   //! Data ready interrupt source is direct (non -FIFO).
   SDFM_DATA_READY_SOURCE_DIRECT = 0,
   //! Data ready interrupt source is FIFO.
   SDFM_DATA_READY_SOURCE_FIFO = 1
}SDFM_DataReadyInterruptSource;

//! \brief Enumeration to define the PWM sync source for SDFM
//!
typedef enum
{
   SDFM_SYNC_PWM1_SOCA = 0,    //!< SDFM sync source is PWM1 SOCA
   SDFM_SYNC_PWM1_SOCB = 1,    //!< SDFM sync source is PWM1 SOCB
   SDFM_SYNC_PWM2_SOCA = 2,    //!< SDFM sync source is PWM2 SOCA
   SDFM_SYNC_PWM2_SOCB = 3,    //!< SDFM sync source is PWM2 SOCB
   SDFM_SYNC_PWM3_SOCA = 4,    //!< SDFM sync source is PWM3 SOCA
   SDFM_SYNC_PWM3_SOCB = 5,    //!< SDFM sync source is PWM3 SOCB
   SDFM_SYNC_PWM4_SOCA = 6,    //!< SDFM sync source is PWM4 SOCA
   SDFM_SYNC_PWM4_SOCB = 7,    //!< SDFM sync source is PWM4 SOCB
   SDFM_SYNC_PWM5_SOCA = 8,    //!< SDFM sync source is PWM5 SOCA
   SDFM_SYNC_PWM5_SOCB = 9,    //!< SDFM sync source is PWM5 SOCB
   SDFM_SYNC_PWM6_SOCA = 10,   //!< SDFM sync source is PWM6 SOCA
   SDFM_SYNC_PWM6_SOCB = 11,   //!< SDFM sync source is PWM6 SOCB
   SDFM_SYNC_PWM7_SOCA = 12,   //!< SDFM sync source is PWM7 SOCA
   SDFM_SYNC_PWM7_SOCB = 13,   //!< SDFM sync source is PWM7 SOCB
   SDFM_SYNC_PWM8_SOCA = 14,   //!< SDFM sync source is PWM8 SOCA
   SDFM_SYNC_PWM8_SOCB = 15    //!< SDFM sync source is PWM8 SOCB

}SDFM_PwmSyncSource;

//! \brief Enumeration to define the FIFO clear sync mode.
//!
typedef enum
{
   //! SDFM Fifo buffer is not cleared on Sync signal
   SDFM_FIFO_NOT_CLEARED_ON_SYNC = 0,
   //! SDFM Fifo buffer is cleared on Sync signal
   SDFM_FIFO_CLEARED_ON_SYNC = 1
}SDFM_FIFOClearSyncMode;

//! \brief Enumeration to define the Wait-for-sync clear mode.
//!
typedef enum
{
   //! Wait for sync cleared using software.
   SDFM_MANUAL_CLEAR_WAIT_FOR_SYNC = 0,
   //! Wait for sync cleared automatically
   SDFM_AUTO_CLEAR_WAIT_FOR_SYNC = 1
}SDFM_WaitForSyncClearMode;

//! \brief Enumeration to define the Zero Cross Detection (ZCD) mode.
//!
typedef enum
{
   //! comparator data is greater than ZCD threshold data.
   SDFM_ZCD_COMP_DATA_GREATER_ZCT  = 0,
   //! High pulse on Low to High transition
   SDFM_ZCD_HIGH_PULSE_ON_LOW_TO_HIGH = 1,
   //! High pulse on High to Low transition
   SDFM_ZCD_HIGH_PULSE_ON_HIGH_TO_LOW = 2,
   //! High pulse on both Low and high transitions.
   SDFM_ZCD_HIGH_PULSE_ON_LOW_AND_HIGH = 3
}SDFM_ZeroCrossDetectMode;

//! \brief Enumeration to define SDFM interrupt types.
//!
typedef enum
{
   SDFM_INTERRUPT = 0,                     //!< SDFM interrupt
   SDFM_FILTER_1_DATA_READY_INTERRUPT = 1, //!< SDFM Filter 1 Data Ready
   SDFM_FILTER_2_DATA_READY_INTERRUPT = 2, //!< SDFM Filter 2 Data Ready
   SDFM_FILTER_3_DATA_READY_INTERRUPT = 3, //!< SDFM Filter 3 Data Ready
   SDFM_FILTER_4_DATA_READY_INTERRUPT = 4  //!< SDFM Filter 4 Data Ready
}SDFM_InterruptType;

//*****************************************************************************
//
// Values that can be passed to SDFM_enableInterrupt and SDFM_disableInterrupt
// as intFlags parameter
//
//*****************************************************************************
//! Interrupt is generated if Modulator fails.
#define SDFM_MODULATOR_FAILURE_INTERRUPT    0x200U
//! Interrupt on Comparator low-level threshold.
#define SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT  0x40U
//! Interrupt on Comparator high-level threshold.
#define SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT 0x20U
//! Interrupt on Acknowledge flag
#define SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT 0x1U
//! Interrupt on FIFO level
#define SDFM_FIFO_INTERRUPT                 0x1000U
//! Interrupt on FIFO overflow
#define SDFM_FIFO_OVERFLOW_INTERRUPT        0x8000U
//*****************************************************************************
//
// Values that can be passed to SDFM_clearInterruptFlag flags parameter
//
//*****************************************************************************
//! Master interrupt flag
#define SDFM_MASTER_INTERRUPT_FLAG         0x80000000U
//! Filter 1 high -level threshold flag
#define SDFM_FILTER_1_HIGH_THRESHOLD_FLAG  0x1U
//! Filter 1 low -level threshold flag
#define SDFM_FILTER_1_LOW_THRESHOLD_FLAG   0x2U
//! Filter 2 high -level threshold flag
#define SDFM_FILTER_2_HIGH_THRESHOLD_FLAG  0x4U
//! Filter 2 low -level threshold flag
#define SDFM_FILTER_2_LOW_THRESHOLD_FLAG   0x8U
//! Filter 3 high -level threshold flag
#define SDFM_FILTER_3_HIGH_THRESHOLD_FLAG  0x10U
//! Filter 3 low -level threshold flag
#define SDFM_FILTER_3_LOW_THRESHOLD_FLAG   0x20U
//! Filter 4 high -level threshold flag
#define SDFM_FILTER_4_HIGH_THRESHOLD_FLAG  0x40U
//! Filter 4 low -level threshold flag
#define SDFM_FILTER_4_LOW_THRESHOLD_FLAG   0x80U
//! Filter 1 modulator failed flag
#define SDFM_FILTER_1_MOD_FAILED_FLAG      0x100U
//! Filter 2 modulator failed flag
#define SDFM_FILTER_2_MOD_FAILED_FLAG      0x200U
//! Filter 3 modulator failed flag
#define SDFM_FILTER_3_MOD_FAILED_FLAG      0x400U
//! Filter 4 modulator failed flag
#define SDFM_FILTER_4_MOD_FAILED_FLAG      0x800U
//! Filter 1 new data flag
#define SDFM_FILTER_1_NEW_DATA_FLAG        0x1000U
//! Filter 2 new data flag
#define SDFM_FILTER_2_NEW_DATA_FLAG        0x2000U
//! Filter 3 new data flag
#define SDFM_FILTER_3_NEW_DATA_FLAG        0x4000U
//! Filter 4 new data flag
#define SDFM_FILTER_4_NEW_DATA_FLAG        0x8000U
//! Filter 1 FIFO overflow flag
#define SDFM_FILTER_1_FIFO_OVERFLOW_FLAG   0x10000U
//! Filter 2 FIFO overflow flag
#define SDFM_FILTER_2_FIFO_OVERFLOW_FLAG   0x20000U
//! Filter 3 FIFO overflow flag
#define SDFM_FILTER_3_FIFO_OVERFLOW_FLAG   0x40000U
//! Filter 4 FIFO overflow flag
#define SDFM_FILTER_4_FIFO_OVERFLOW_FLAG   0x80000U
//! Filter 1 FIFO overflow flag
#define SDFM_FILTER_1_FIFO_INTERRUPT_FLAG  0x100000U
//! Filter 2 FIFO overflow flag
#define SDFM_FILTER_2_FIFO_INTERRUPT_FLAG  0x200000U
//! Filter 3 FIFO overflow flag
#define SDFM_FILTER_3_FIFO_INTERRUPT_FLAG  0x400000U
//! Filter 4 FIFO overflow flag
#define SDFM_FILTER_4_FIFO_INTERRUPT_FLAG  0x800000U
//*****************************************************************************
//
//! \internal
//! Checks SDFM base address.
//!
//! \param base specifies the SDFM module base address.
//!
//! This function determines if SDFM module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool SDFM_isBaseValid(uint32_t base)
{
    return(base == SDFM1_BASE);
}
#endif

//*****************************************************************************
//
//! Enable external reset
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables data filter to be reset by an external source (PWM
//! compare output).
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableExternalReset(uint32_t base,
                                            SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));
    // Set the FILRESEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 +
          (uint16_t)((uint16_t)filterNumber*16U)) |= SDFM_SDDFPARM1_SDSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable external reset
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables data filter from being reset by an external source
//! (PWM compare output).
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_disableExternalReset(uint32_t base,
                                             SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));
    // Clear the FILRESEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 +
          (uint16_t)((uint16_t)filterNumber*16U)) &= ~SDFM_SDDFPARM1_SDSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Enable filter
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables the filter specified by the filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableFilter(uint32_t base,
                                     SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));
    // Set the FEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 +
          (uint16_t)((uint16_t)filterNumber*16U)) |= SDFM_SDDFPARM1_FEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable filter
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables the filter specified by the filterNumber variable.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_disableFilter(uint32_t base,
                                      SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));
    // Clear the FEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 +
          (uint16_t)((uint16_t)filterNumber*16U)) &= ~SDFM_SDDFPARM1_FEN;
    EDIS;
}
//*****************************************************************************
//
//! Enable FIFO buffer
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables the filter FIFO buffer specified by the filterNumber
//! variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableFIFOBuffer(uint32_t base,
                                         SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));
    // Set the FFEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDFIFOCTL1 +
          (uint16_t)((uint16_t)filterNumber*16U)) |= SDFM_SDFIFOCTL1_FFEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable FIFO buffer
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables the filter FIFO buffer specified by the filterNumber
//! variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableFIFOBuffer(uint32_t base,
                                          SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));
    // Clear the FFEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDFIFOCTL1 +
          (uint16_t)((uint16_t)filterNumber*16U)) &= ~SDFM_SDFIFOCTL1_FFEN;
    EDIS;
}

//*****************************************************************************
//
//! Return the Manchester lock status
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//!  This function returns the Manchester code lock status.
//!
//! \return Returns true if the Manchester decoder module is locked (success).
//!         Returns false if the Manchester decoder module isn't locked
//!         (failure).
//
//*****************************************************************************
static inline bool SDFM_getManchesterDecoderLockedStatus(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{
   uint16_t shift;

   ASSERT(SDFM_isBaseValid(base));

   shift = (uint16_t)filterNumber + 12U;
   // Read bits MAL1,MAL2, MAL3 and MAL4 bits
   return((((HWREGH(base + SDFM_O_SDSTATUS) & (1U << shift)) >> shift) ==
             0x1U) ? false :true);
}

//*****************************************************************************
//
//! Return the Manchester fail status
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//!  This function returns the Manchester failed lock status for the filter
//!  type specified by filterNumber variable.
//!
//! \return Returns SDFM_MANCHESTER_DECODER_SUCCESS if the Manchester decoder
//!         is working properly.
//!         Returns SDFM_MANCHESTER_DECODER_FAIL if the Manchester decoder has
//!         encountered issues.
//
//*****************************************************************************
static inline SDFM_ManchesterDecoderStatus
         SDFM_getManchesterDecoderFailedStatus(uint32_t base,
                                              SDFM_FilterNumber filterNumber)
{
   uint16_t shift;

   ASSERT(SDFM_isBaseValid(base));

   shift = (uint16_t)filterNumber + 8U;
   // Read bits MAF1,MAF2, MAF3 and MAF4 bits
   return((SDFM_ManchesterDecoderStatus)((HWREGH(base + SDFM_O_SDSTATUS) &
           (1U << shift)) >> shift));
}

//*****************************************************************************
//
//! Return the Zero Cross Trip status
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Zero Cross Trip status for the filter type
//! specified by filterNumber variable.
//!
//! \return \b 1
//!         \b 0
//
//*****************************************************************************
static inline uint16_t SDFM_getZeroCrossTripStatus(uint32_t base,
                                                SDFM_FilterNumber filterNumber)
{
   ASSERT(SDFM_isBaseValid(base));

   return((HWREGH(base + SDFM_O_SDSTATUS) >> (uint16_t)filterNumber) & 0x1U);
}

//*****************************************************************************
//
//! Clear the Zero Cross Trip status
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//!  This function clears the Zero Cross Trip status for the filter type
//!  specified by filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_clearZeroCrossTripStatus(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{

    ASSERT(SDFM_isBaseValid(base));

    // Set SDCTL MIE bit
    EALLOW;
    HWREGH(base + SDFM_O_SDCTL) |= (1U << filterNumber);
    EDIS;
}

//*****************************************************************************
//
//! Enable Comparator.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//!  This function enables the Comparator for the selected filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableComparator(uint32_t base,
                                         SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Set CEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDCPARM1 +
          (uint16_t)((uint16_t)filterNumber*16U)) |= SDFM_SDCPARM1_CEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable Comparator.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//!  This function disables the Comparator for the selected filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableComparator(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Clear CEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDCPARM1 +
          (uint16_t)((uint16_t)filterNumber*16U)) &= ~SDFM_SDCPARM1_CEN;
    EDIS;
}

//*****************************************************************************
//
//! Set filter type.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param filterType is the filter type or structure.
//!
//! This function sets the filter type or structure to be used as specified by
//! filterType for the selected filter number as specified by filterNumber.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setFilterType(uint32_t base,
                                      SDFM_FilterNumber filterNumber,
                                      SDFM_FilterType filterType)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDDFPARM1 + (uint16_t)((uint16_t)filterNumber*16U);
    // write to SST bits
    EALLOW;
    HWREGH(base + offset) =
          ((HWREGH(base + offset) & (~SDFM_SDDFPARM1_SST_M)) |
          ((uint16_t)filterType << 6U));
    EDIS;
}

//*****************************************************************************
//
//! Set data filter over sampling ratio.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param overSamplingRatio is the data filter over sampling ratio.
//!
//! This function sets the filter oversampling ratio for the filter specified
//! by the filterNumber variable.Valid values for the variable
//! overSamplingRatio are 0 to 255 inclusive. The actual oversampling ratio
//! will be this value plus one.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setFilterOverSamplingRatio(uint32_t base,
                                              SDFM_FilterNumber filterNumber,
                                              uint16_t overSamplingRatio)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDDFPARM1 + (uint16_t)((uint16_t)filterNumber*16U);

    ASSERT(overSamplingRatio < 256U);
    // write to DOSR bits
    EALLOW;
    HWREGH(base + offset) =
          ((HWREGH(base + offset) & (~SDFM_SDDFPARM1_DOSR_M)) |
           overSamplingRatio);
    EDIS;
}

//*****************************************************************************
//
//! Set modulator clock mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param clockMode is the modulator clock mode.
//!
//! This function sets the modulator clock mode specified by clockMode
//! for the filter specified by filterNumber.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setupModulatorClock(uint32_t base,
                                            SDFM_FilterNumber filterNumber,
                                            SDFM_ModulatorClockMode clockMode)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDCTLPARM1 + (uint16_t)((uint16_t)filterNumber*16U);

    // write to MOD bits
    EALLOW;
    HWREGH(base + offset) =
          ((HWREGH(base + offset) & (~SDFM_SDCTLPARM1_MOD_M)) |
          (uint16_t)clockMode);
    EDIS;
}

//*****************************************************************************
//
//! Return Manchester decoder calibration status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Manchester decoder calibration status of the
//! filter specified by filterNumber. The calibration status is 11 bits wide.
//!
//! \return \b returns the Manchester decoder calibration status.
//
//*****************************************************************************
static inline uint16_t SDFM_getManchesterCalStatus(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // return bits MS[10:0]
    return(HWREGH(base + SDFM_O_SDCTLPARM1 +
                  (uint16_t)((uint16_t)filterNumber*16U)) >>
                  SDFM_SDCTLPARM1_MS_S);
}

//*****************************************************************************
//
//! Set the output data format
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param dataFormat is the output data format.
//!
//! This function sets the output data format for the filter specified by
//! filterNumber.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setOutputDataFormat(uint32_t base,
                                            SDFM_FilterNumber filterNumber,
                                            SDFM_OutputDataFormat dataFormat)
{

    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));
    offset = SDFM_O_SDDPARM1 + (uint16_t)((uint16_t)filterNumber*16U);

    // write to DR bit
    EALLOW;
    HWREGH(base + offset) = ((HWREGH(base + offset) & (~SDFM_SDDPARM1_DR)) |
                             ((uint16_t)dataFormat << 10U));
    EDIS;
}

//*****************************************************************************
//
//! Set data shift value.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param shiftValue is the data shift value.
//!
//! This function sets the shift value for the 16 bit 2's complement data
//! format. The valid maximum value for shiftValue is 31.
//!
//! \b Note: Use this function with 16 bit 2's complement data format only.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setDataShiftValue(uint32_t base,
                                          SDFM_FilterNumber filterNumber,
                                          uint16_t shiftValue)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(shiftValue < 32U);
    offset = SDFM_O_SDDPARM1 + (uint16_t)((uint16_t)filterNumber*16U);

    // write to SH bit
    EALLOW;
    HWREGH(base + offset) = ((HWREGH(base + offset) & (~SDFM_SDDPARM1_SH_M)) |
                             (shiftValue << SDFM_SDDPARM1_SH_S));
    EDIS;
}

//*****************************************************************************
//
//! Set Filter output high-level threshold.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param highThreshold is the high-level threshold.
//!
//! This function sets the unsigned high-level threshold value for the
//! Comparator filter output. If the output value of the filter exceeds
//! highThreshold and interrupt generation is enabled, an interrupt will be
//! issued.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setCompFilterHighThreshold(uint32_t base,
                                     SDFM_FilterNumber filterNumber,
                                     uint16_t highThreshold)
{

    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(highThreshold < 0x7FFFU);

    offset = SDFM_O_SDCMPH1 + (uint16_t)((uint16_t)filterNumber*16U);

    // write to HLT bit
    EALLOW;
    HWREGH(base + offset) =
           ((HWREGH(base + offset) & (~SDFM_SDCMPH1_HLT_M)) | highThreshold );
    EDIS;

}

//*****************************************************************************
//
//! Set Filter output low-level threshold.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param lowThreshold is the low-level threshold.
//!
//! This function sets the unsigned low-level threshold value for the
//! Comparator filter output. If the output value of the filter gets below
//! lowThreshold and interrupt generation is enabled, an interrupt will be
//! issued.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setCompFilterLowThreshold(uint32_t base,
                                              SDFM_FilterNumber filterNumber,
                                              uint16_t lowThreshold)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDCMPL1 + (uint16_t)((uint16_t)filterNumber*16U);

    ASSERT(lowThreshold < 0x7FFFU);
    // write to LLT bit
    EALLOW;
    HWREGH(base + offset) =
           ((HWREGH(base + offset) & (~SDFM_SDCMPL1_LLT_M)) | lowThreshold );
    EDIS;
}

//*****************************************************************************
//
//! Set Filter output zero-cross threshold.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param zeroCrossThreshold is the zero-cross threshold.
//!
//! This function sets the unsigned zero-cross threshold value for the
//! Comparator filter output.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setCompFilterZeroCrossThreshold(uint32_t base,
                                              SDFM_FilterNumber filterNumber,
                                              uint16_t zeroCrossThreshold)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDCMPZ1 + (uint16_t)((uint16_t)filterNumber*16U);

    ASSERT(zeroCrossThreshold < 0x7FFFU);
    // write to ZCT bit
    EALLOW;
    HWREGH(base + offset) =
           ((HWREGH(base + offset) & (~SDFM_SDCMPZ1_ZCT_M)) |
            zeroCrossThreshold );
    EDIS;
}

//*****************************************************************************
//
//! Enable zero-cross Edge detect mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables Zero Cross Edge detection.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableZeroCrossEdgeDetect(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{

    ASSERT(SDFM_isBaseValid(base));

    // Set ZCEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDCPARM1 + (uint16_t)((uint16_t)filterNumber*16U)) |=
           SDFM_SDCPARM1_ZCEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable zero-cross Edge detect mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables Zero Cross Edge detection.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableZeroCrossEdgeDetect(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{

    ASSERT(SDFM_isBaseValid(base));

    // Clear ZCEN bit
    EALLOW;
    HWREGH(base + SDFM_O_SDCPARM1 + (uint16_t)((uint16_t)filterNumber*16U)) &=
           ~SDFM_SDCPARM1_ZCEN;
    EDIS;
}

//*****************************************************************************
//
//! Enable SDFM interrupts.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param intFlags is the interrupt source.
//!
//! This function enables the low threshold , high threshold or modulator
//! failure interrupt as determined by intFlags for the filter specified
//! by filterNumber.
//! Valid values for intFlags are:
//!  SDFM_MODULATOR_FAILURE_INTERRUPT , SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT,
//!  SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT,
//!  SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT
//!  SDFM_FIFO_INTERRUPT,SDFM_FIFO_OVERFLOW_INTERRUPT
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableInterrupt(uint32_t base,
                                        SDFM_FilterNumber filterNumber,
                                        uint16_t intFlags)
{

    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = (uint16_t)filterNumber*16U;

    EALLOW;
    // Low, high threshold, Modulator failure
    if((intFlags & (SDFM_MODULATOR_FAILURE_INTERRUPT |
                     SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT |
                     SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT)) != 0U)
    {
        // Set IEL or IEH or MFIE bit of SDFM_O_SDCPARMx
         HWREGH(base + SDFM_O_SDCPARM1 + offset) |=
                (intFlags & (SDFM_MODULATOR_FAILURE_INTERRUPT |
                             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT |
                             SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT));
    }
    // Data filter acknowledge interrupt
    if((intFlags & SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT) != 0U)
    {
        HWREGH(base + SDFM_O_SDDFPARM1 + offset) |= SDFM_SDDFPARM1_AE;
    }
    // FIFO , FIFO overflow interrupt
    if((intFlags & (SDFM_FIFO_INTERRUPT | SDFM_FIFO_OVERFLOW_INTERRUPT)) != 0U)
    {
         // Set OVFIEN or FFIEN bits of SDFM_O_SDFIFOCTLx
         HWREGH(base + SDFM_O_SDFIFOCTL1 + offset) |=
                (intFlags & (SDFM_FIFO_INTERRUPT |
                             SDFM_FIFO_OVERFLOW_INTERRUPT));
    }
    EDIS;
}

//*****************************************************************************
//
//! Disable SDFM interrupts.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param intFlags is the interrupt source.
//!
//! This function disables the low threshold , high threshold or modulator
//! failure interrupt as determined by intFlags for the filter
//! specified by filterNumber.
//! Valid values for intFlags are:
//!  SDFM_MODULATOR_FAILURE_INTERRUPT , SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT,
//!  SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT, SDFM_FIFO_INTERRUPT,
//!  SDFM_FIFO_OVERFLOW_INTERRUPT
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableInterrupt(uint32_t base,
                                         SDFM_FilterNumber filterNumber,
                                         uint16_t intFlags)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = (uint16_t)filterNumber*16U;

    EALLOW;
    // Low, high threshold, Modulator failure interrupts
    if((intFlags & (SDFM_MODULATOR_FAILURE_INTERRUPT |
                     SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT |
                     SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT)) != 0U)
    {
        // Set IEL or IEH or MFIE bit of SDFM_O_SDCPARMx
         HWREGH(base + SDFM_O_SDCPARM1 + offset) &=
              ~(intFlags & (SDFM_MODULATOR_FAILURE_INTERRUPT |
                            SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT |
                            SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT));
    }
    // Data filter acknowledge interrupt
    if((intFlags & SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT) != 0U)
    {
        HWREGH(base + SDFM_O_SDDFPARM1 + offset) &= ~SDFM_SDDFPARM1_AE;
    }
    // FIFO , FIFO overflow interrupt
    if((intFlags & (SDFM_FIFO_INTERRUPT | SDFM_FIFO_OVERFLOW_INTERRUPT)) != 0U)
    {
         // Set OVFIEN or FFIEN bits of SDFM_O_SDFIFOCTLx
         HWREGH(base + SDFM_O_SDFIFOCTL1 + offset) &=
                ~(intFlags & (SDFM_FIFO_INTERRUPT |
                              SDFM_FIFO_OVERFLOW_INTERRUPT));
    }
    EDIS;
}

//*****************************************************************************
//
//! Set the comparator filter type.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param filterType is the comparator filter type or structure.
//!
//! This function sets the Comparator filter type or structure to be used as
//! specified by filterType for the selected filter number as specified by
//! filterNumber.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setComparatorFilterType(uint32_t base,
                                                SDFM_FilterNumber filterNumber,
                                                SDFM_FilterType filterType)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDCPARM1 + (uint16_t)((uint16_t)filterNumber*16U);
    // write to CS1_CS0 bits
    EALLOW;
    HWREGH(base + offset) =
                ((HWREGH(base + offset) & (~SDFM_SDCPARM1_CS1_CS0_M)) |
                 ((uint16_t)filterType << 3U));
    EDIS;
}

//*****************************************************************************
//
//! Set Comparator filter over sampling ratio.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param overSamplingRatio is the comparator filter over sampling ration.
//!
//! This function sets the comparator filter oversampling ratio for the filter
//! specified by the filterNumber.Valid values for the variable
//! overSamplingRatio are 0 to 31 inclusive.
//! The actual oversampling ratio will be this value plus one.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setCompFilterOverSamplingRatio(uint32_t base,
                                               SDFM_FilterNumber filterNumber,
                                               uint16_t overSamplingRatio)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDCPARM1 + (uint16_t)((uint16_t)filterNumber*16U);

    ASSERT(overSamplingRatio < 32U);

    // write to COSR bits
    EALLOW;
    HWREGH(base + offset) =
      ((HWREGH(base + offset) & (~SDFM_SDCPARM1_COSR_M)) | overSamplingRatio);
    EDIS;
}

//*****************************************************************************
//
//! Get the filter data output.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the latest data filter output. Depending on the filter
//! data output format selected, the valid value will be the lower 16 bits or
//! the whole 32 bits of the returned value.
//!
//! \return Returns the latest data filter output.
//*****************************************************************************
static inline uint32_t SDFM_getFilterData(uint32_t base,
                                          SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDDATA bits
    return(HWREG(base + SDFM_O_SDDATA1 +
                           (uint16_t)((uint16_t)filterNumber*16U)));
}

//*****************************************************************************
//
//! Get the Comparator threshold status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Comparator output threshold status for the given
//! filterNumber.
//!
//! \return Returns the following status flags.
//!         - SDFM_OUTPUT_WITHIN_THRESHOLD  if the output is within the
//!                                         specified threshold.
//!         - SDFM_OUTPUT_ABOVE_THRESHOLD  if the output is above the high
//!                                        threshold
//!         - SDFM_OUTPUT_BELOW_THRESHOLD  if the output is below the low
//!                                        threshold.
//!
//*****************************************************************************
static inline SDFM_OutputThresholdStatus SDFM_getThresholdStatus(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDIFLG IFH1,IFL1,IFH2,IFL2, etc ... bits
    return((SDFM_OutputThresholdStatus)((HWREG(base + SDFM_O_SDIFLG) >>
                                (2U*(uint16_t)filterNumber)) & 0x3U));
}

//*****************************************************************************
//
//! Get the Modulator status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Modulator status.
//!
//! \return Returns true if the Modulator is operating normal
//!         Returns false if the Modulator has failed
//!
//*****************************************************************************
static inline bool SDFM_getModulatorStatus(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDIFLG MF1,MF2,MF3 OR MF4 bits
    return((((uint16_t)(HWREG(base + SDFM_O_SDIFLG) >>
           ((uint16_t)filterNumber + 8U)) & 0x1U) == 0x1U) ? true : false);
}

//*****************************************************************************
//
//! Check if new Filter data is available.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns new filter data status.
//!
//! \return Returns true if new filter data is available
//!         Returns false if no new filter data is available
//!
//*****************************************************************************
static inline bool SDFM_getNewFilterDataStatus(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDIFLG AF1,AF2,AF3 OR AF4 bits
    return((((uint16_t)(HWREG(base + SDFM_O_SDIFLG) >>
           ((uint16_t)filterNumber + 12U)) & 0x1U) == 0x1U) ? true : false);
}

//*****************************************************************************
//
//! Check if FIFO buffer is overflowed.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the status of the FIFO buffer overflow for the given
//! filter value.
//!
//! \return Returns true if FIFO buffer is overflowed
//!         Returns false if FIFO buffer is not overflowed
//!
//*****************************************************************************
static inline bool SDFM_getFIFOOverflowStatus(uint32_t base,
                                              SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDIFLG SDFFOVF1,SDFFOVF2,SDFFOVF3 OR SDFFOVF4 bits
    return((((uint16_t)(HWREG(base + SDFM_O_SDIFLG) >>
            ((uint16_t)filterNumber + 16U)) & 0x1U) == 0x1U) ? true : false);
}

//*****************************************************************************
//
//! Check FIFO buffer interrupt status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the status of the FIFO buffer interrupt for the given
//! filter.
//!
//! \return Returns true if FIFO buffer interrupt has occurred.
//!         Returns false if FIFO buffer interrupt has not occurred.
//!
//*****************************************************************************
static inline bool SDFM_getFIFOIsrStatus(uint32_t base,
                                             SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDIFLG SDFFINT1,SDFFINT2,SDFFINT3 OR SDFFINT4 bits
    return((((uint16_t)(HWREG(base + SDFM_O_SDIFLG) >>
           ((uint16_t)filterNumber + 20U)) & 0x1U) == 0x1U) ? true : false);
}

//*****************************************************************************
//
//! Get pending interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function returns any pending interrupt status.
//!
//! \return Returns true if there is a pending interrupt.
//!         Returns false if no interrupt is pending.
//!
//*****************************************************************************
static inline bool SDFM_getIsrStatus(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDIFLG MIF
    return((((uint16_t)(HWREG(base + SDFM_O_SDIFLG) >> 31U)) == 0x1U) ?
                                                            true : false);
}

//*****************************************************************************
//
//! Clear pending flags.
//!
//! \param base is the base address of the SDFM module
//! \param flag is the SDFM status
//!
//! This function clears the specified pending interrupt flag.
//! Valid values are
//! SDFM_MASTER_INTERRUPT_FLAG,SDFM_FILTER_1_NEW_DATA_FLAG,
//! SDFM_FILTER_2_NEW_DATA_FLAG,SDFM_FILTER_3_NEW_DATA_FLAG,
//! SDFM_FILTER_4_NEW_DATA_FLAG,SDFM_FILTER_1_MOD_FAILED_FLAG,
//! SDFM_FILTER_2_MOD_FAILED_FLAG,SDFM_FILTER_3_MOD_FAILED_FLAG,
//! SDFM_FILTER_4_MOD_FAILED_FLAG,SDFM_FILTER_1_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_1_LOW_THRESHOLD_FLAG,SDFM_FILTER_2_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_2_LOW_THRESHOLD_FLAG,SDFM_FILTER_3_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_3_LOW_THRESHOLD_FLAG,SDFM_FILTER_4_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_4_LOW_THRESHOLD_FLAG,SDFM_FILTER_1_FIFO_OVERFLOW_FLAG,
//! SDFM_FILTER_2_FIFO_OVERFLOW_FLAG,SDFM_FILTER_3_FIFO_OVERFLOW_FLAG
//! SDFM_FILTER_4_FIFO_OVERFLOW_FLAG,SDFM_FILTER_1_FIFO_INTERRUPT_FLAG,
//! SDFM_FILTER_2_FIFO_INTERRUPT_FLAG,SDFM_FILTER_3_FIFO_INTERRUPT_FLAG
//! SDFM_FILTER_4_FIFO_INTERRUPT_FLAG or any combination of the above flags.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_clearInterruptFlag(uint32_t base, uint32_t flag)
{
    ASSERT(SDFM_isBaseValid(base));
    ASSERT((flag & 0x80FFFFFFU) != 0U);
    // Write to  SDIFLGCLR register
    HWREG(base + SDFM_O_SDIFLGCLR) |= flag;
}

//*****************************************************************************
//
//! Enable master interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function enables the master SDFM interrupt.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_enableMasterInterrupt(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    // Set SDCTL MIE bit
    EALLOW;
    HWREGH(base + SDFM_O_SDCTL) |= SDFM_SDCTL_MIE;
    EDIS;
}

//*****************************************************************************
//
//! Disable master interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function disables the master SDFM interrupt.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_disableMasterInterrupt(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    // Clear SDCTL MIE bit
    EALLOW;
    HWREGH(base + SDFM_O_SDCTL) &= ~SDFM_SDCTL_MIE;
    EDIS;
}

//*****************************************************************************
//
//! Enable master interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function enables Master filter.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_enableMasterFilter(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    // Set SDMFILEN MFE bit
    EALLOW;
    HWREGH(base + SDFM_O_SDMFILEN) |= SDFM_SDMFILEN_MFE;
    EDIS;
}

//*****************************************************************************
//
//! Disable master filter.
//!
//! \param base is the base address of the SDFM module
//!
//! This function disables Master filter.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_disableMasterFilter(uint32_t base)
{

    ASSERT(SDFM_isBaseValid(base));

    // clear SDMFILEN MFE bit
    EALLOW;
    HWREGH(base + SDFM_O_SDMFILEN) &= ~SDFM_SDMFILEN_MFE;
    EDIS;
}

//*****************************************************************************
//
//! Return the FIFO data count
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the FIFO data count.
//!
//! \return Returns the number of data words available in FIFO buffer.
//
//*****************************************************************************
static inline uint16_t SDFM_getFIFODataCount(uint32_t base,
                                             SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDFFST
    return((HWREGH(base + SDFM_O_SDFIFOCTL1 +
        (uint16_t)((uint16_t)filterNumber*16U)) & SDFM_SDFIFOCTL1_SDFFST_M) >>
         SDFM_SDFIFOCTL1_SDFFST_S);
}

//*****************************************************************************
//
//! Return the Comparator sinc filter data
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Comparator sinc filter data output.
//!
//! \return Returns the Comparator sinc filter data output.
//!
//! \note Discard the upper 16 bits if the output data format is 16bits.
//
//*****************************************************************************
static inline uint32_t SDFM_getComparatorSincData(uint32_t base,
                                              SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDCDATA
    return(HWREG(base + SDFM_O_SDCDATA1 +
                               (uint16_t)((uint16_t)filterNumber*16U)));
}

//*****************************************************************************
//
//! Return the FIFO data
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the latest FIFO data.
//!
//! \return Returns the latest FIFO data.
//!
//! \note Discard the upper 16 bits if the output data format is 16bits.
//
//*****************************************************************************
static inline uint32_t SDFM_getFIFOData(uint32_t base,
                                        SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read SDDATFIFO
    return(HWREG(base + SDFM_O_SDDATFIFO1 +
                                  (uint16_t)((uint16_t)filterNumber*16U)));
}

//*****************************************************************************
//
//! Set the FIFO interrupt level.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param fifoLevel is the FIFO interrupt level.
//!
//! This function sets the FIFO interrupt level. Interrupt is generated when
//! the FIFO buffer word count gets to or exceeds the value of fifoLevel.
//! Maximum value for fifoLevel is 16.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setFIFOInterruptLevel(uint32_t base,
                                              SDFM_FilterNumber filterNumber,
                                              uint16_t fifoLevel)
{

    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(SDFM_isBaseValid(fifoLevel <= 16U));

    offset = SDFM_O_SDFIFOCTL1 + (uint16_t)((uint16_t)filterNumber*16U);

    // Write to SDFFIL bit
    EALLOW;
    HWREGH(base + offset) =
       ((HWREGH(base + offset) & (~SDFM_SDFIFOCTL1_SDFFIL_M)) | fifoLevel);
    EDIS;
}

//*****************************************************************************
//
//! Set data ready interrupt source.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param dataReadySource is the data ready interrupt source.
//!
//! This function sets the data ready interrupt source.
//! Valid values for dataReadySource:
//!   - SDFM_DATA_READY_SOURCE_DIRECT - Direct data ready
//!   - SDFM_DATA_READY_SOURCE_FIFO  - FIFO data ready.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setDataReadyInterruptSource(uint32_t base,
                               SDFM_FilterNumber filterNumber,
                               SDFM_DataReadyInterruptSource dataReadySource)
{

    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDFIFOCTL1 + (uint16_t)((uint16_t)filterNumber*16U);
    // write to DRINTSEL
    EALLOW;
    HWREGH(base + offset) =
                 ((HWREGH(base + offset) & ~SDFM_SDFIFOCTL1_DRINTSEL) |
                  ((uint16_t)dataReadySource << 14U));
    EDIS;
}

//*****************************************************************************
//
//! Get the wait-for-sync event status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Wait-for-Sync event status.
//!
//! \return Returns true if sync event has occurred.
//!         Returns false if sync event has not occurred.
//
//*****************************************************************************
static inline bool SDFM_getWaitForSyncStatus(uint32_t base,
                                               SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    // Read WTSYNFLG bit
    return((((HWREGH(base + SDFM_O_SDSYNC1 +
           (uint16_t)((uint16_t)filterNumber*16U)) &
            SDFM_SDSYNC1_WTSYNFLG) >> 7U) == 0x1U) ? true : false);
}

//*****************************************************************************
//
//! Clear the Wait-for-sync event status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function clears the Wait-for-sync event status.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_clearWaitForSyncFlag(uint32_t base,
                                             SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    EALLOW;
    // Clear WTSYNCLR bit
    HWREGH(base + SDFM_O_SDSYNC1 + (uint16_t)((uint16_t)filterNumber*16U)) |=
           SDFM_SDSYNC1_WTSYNCLR;
    EDIS;
}

//*****************************************************************************
//
//! Enable wait for sync mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables the wait for sync mode. Data to FIFO will be written
//! only after PWM sync event.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableWaitForSync(uint32_t base,
                                          SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    EALLOW;
    // Set WTSYNCEN bit
    HWREGH(base + SDFM_O_SDSYNC1 + (uint16_t)((uint16_t)filterNumber*16U)) |=
           SDFM_SDSYNC1_WTSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable wait for sync mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables the wait for sync mode. Data to FIFO will be written
//! every Data ready event.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableWaitForSync(uint32_t base,
                                           SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    EALLOW;
    // Clear WTSYNCEN bit
    HWREGH(base + SDFM_O_SDSYNC1 + (uint16_t)((uint16_t)filterNumber*16U)) &=
           ~SDFM_SDSYNC1_WTSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Set the PWM sync mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param syncSource is the PWM sync source.
//!
//! This function sets the PWM sync source for the specific SDFM filter. Valid
//! values for syncSource are SDFM_SYNC_PWMx_CMPy. Where x ranges from 1 to 12
//! Representing PWM1 to PWM12 respectively and y ranges from A to D
//! representing PWM comparators A to D.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setPwmSyncSource(uint32_t base,
                                         SDFM_FilterNumber filterNumber,
                                         SDFM_PwmSyncSource syncSource)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDSYNC1 + (uint16_t)((uint16_t)filterNumber*16U);

    EALLOW;
    // write to SYNCSEL bits
    HWREGH(base + offset) =
    ((HWREGH(base + offset) & ~SDFM_SDSYNC1_SYNCSEL_M) | (uint16_t)syncSource);
    EDIS;
}

//*****************************************************************************
//
//! Set FIFO clear on sync mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param fifoClearSyncMode is the FIFO clear on sync mode.
//!
//! This function sets the FIFO clear mode for the specified filter when a sync
//! happens depending on the value of fifoClearSyncMode.
//! Valid values for fifoClearSyncMode are:
//!  - SDFM_FIFO_NOT_CLEARED_ON_SYNC - FIFO is not cleared on sync.
//!  - SDFM_FIFO_CLEARED_ON_SYNC - FIFO is cleared on sync.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setFIFOClearOnSyncMode(uint32_t base,
                                         SDFM_FilterNumber filterNumber,
                                SDFM_FIFOClearSyncMode fifoClearSyncMode)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDSYNC1 + (uint16_t)((uint16_t)filterNumber*16U);

    EALLOW;
    // write to FFSYNCCLREN bit
    HWREGH(base + offset) =
          ((HWREGH(base + offset) & ~SDFM_SDSYNC1_FFSYNCCLREN) |
          ((uint16_t)fifoClearSyncMode << 9U));
    EDIS;
}

//*****************************************************************************
//
//! Set Wait-for-sync clear mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param syncClearMode is the wait-for-sync clear mode.
//!
//! This function sets the Wait-For-sync clear mode depending on the value of
//! syncClearMode.
//! Valid values for syncClearMode are:
//!   - SDFM_MANUAL_CLEAR_WAIT_FOR_SYNC - Wait-for-sync flag is cleared by
//!                                       invoking SDFM_clearWaitForSyncFlag();
//!   - SDFM_AUTO_CLEAR_WAIT_FOR_SYNC   - Wait-for-sync flag is cleared
//!                                       automatically on FIFO interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setWaitForSyncClearMode(uint32_t base,
                                             SDFM_FilterNumber filterNumber,
                                    SDFM_WaitForSyncClearMode syncClearMode)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = SDFM_O_SDSYNC1 + (uint16_t)((uint16_t)filterNumber*16U);

    EALLOW;
    // write to WTSCLREN  bit
    HWREGH(base + offset) =
          ((HWREGH(base + offset) & ~SDFM_SDSYNC1_WTSCLREN) |
          ((uint16_t)syncClearMode << 10U));
    EDIS;
}

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Configure SDFM comparator high and low thresholds
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio.
//! \param config2 is high-level and low-level threshold values.
//!
//! This function configures the comparator filter threshold values based on
//! configurations config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio ,which ranges [1,32] inclusive, in the appropriate bit location.
//! For example the value
//! (SDFM_FILTER_1 | SDFM_FILTER_SINC_2 | SDFM_SET_OSR(16))
//! will select Filter 1 , SINC 2 type with an oversampling ratio of 16.
//!
//! The config2 parameter is the logical OR of the filter high and low
//! threshold values.
//! The bit definitions for config2 are as follow:
//!   - config2.[15:0]  low threshold
//!   - config2.[31:16] high threshold
//! The upper 16 bits define the high threshold and the lower
//! 16 bits define the low threshold.
//! SDFM_TRESHOLD(H,L) can be used to combine the high and low thresholds.
//!
//!
//! \return None
//!
//*****************************************************************************
extern void SDFM_configComparator(uint32_t base, uint16_t config1,
                                     uint32_t config2);

//*****************************************************************************
//
//! Configure SDFM data filter
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio
//!                configuration.
//! \param config2 is filter switch, data representation and data shift values
//!                configuration.
//!
//! This function configures the data filter based on configurations
//! config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio , which ranges [1,256] inclusive , in the appropriate bit location
//! for config1. For example the value
//! (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(64))
//! will select Filter 2 , SINC 3 type with an oversampling ratio of 64.
//!
//! The config2 parameter is the logical OR of data representation, filter
//! switch, and data shift values
//! The bit definitions for config2 are as follow:
//!   - config2.[0]  Data representation
//!   - config2.[1]  filter switch.
//!   - config2.[15:2]  shift values
//! Valid values for data representation are given in SDFM_OutputDataFormat
//! enumeration. SDFM_FILTER_DISABLE or SDFM_FILTER_ENABLE will define the
//! filter switch values.SDFM_SHIFT_VALUE(X) macro can be used to set the value
//! of the data shift value,which ranges [0,31] inclusive, in the appropriate
//! bit location for config2.
//! The shift value is valid only in SDFM_DATA_FORMAT_16_BIT data
//! representation format.
//!
//! \return None
//!
//*****************************************************************************
extern void SDFM_configDataFilter(uint32_t base, uint16_t config1,
                                     uint16_t config2);

//*****************************************************************************
//
//! Configure SDFM comparator Zero Cross threshold
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio.
//! \param config2 is the zero cross threshold value.
//!
//! This function configures the comparator filter zero cross threshold values
//! based on configurations config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio ,which ranges [1,32] inclusive, in the appropriate bit location.
//! For example the value
//! (SDFM_FILTER_1 | SDFM_FILTER_SINC_2 | SDFM_SET_OSR(16))
//! will select Filter 1 , SINC 2 type with an oversampling ratio of 16.
//!
//! The config2 parameter is the value of the zero cross threshold. The maximum
//! acceptable value is 32767.
//!
//! \return None
//!
//*****************************************************************************
extern void SDFM_configZeroCrossComparator(uint32_t base, uint16_t config1,
                                              uint16_t config2);

//*****************************************************************************
//
//! Configure SDFM data filter FIFO
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio
//!                configuration.
//! \param config2 is filter switch, data representation and data shift values
//!                and FIFO level configuration.
//!
//! This function enables and configures the data filter FIFO based on
//! configurations config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio , which ranges [1,256] inclusive , in the appropriate bit location
//! for config1. For example the value
//! (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(64))
//! will select Filter 2 , SINC 3 type with an oversampling ratio of 64.
//!
//! The config2 parameter is the logical OR of data representation, filter
//! switch, data shift value, and FIFO level
//! The bit definitions for config2 are as follow:
//!   - config2.[0]  Data representation
//!   - config2.[1]  filter switch.
//!   - config2.[6:2]  shift values.
//!   - config2.[15:7] FIFO level
//! Valid values for data representation are given in SDFM_OutputDataFormat
//! enumeration. SDFM_FILTER_DISABLE or SDFM_FILTER_ENABLE will define the
//! filter switch values.SDFM_SHIFT_VALUE(X) macro can be used to set the value
//! of the data shift value,which ranges [0,31] inclusive, in the appropriate
//! bit location for config2.
//! The value of FIFO level ranges [1,16] inclusive. The macro
//! SDFM_SET_FIFO_LEVEL(X) can be used to set the value of the FIFO level.
//!
//! \return None
//!
//*****************************************************************************
extern void SDFM_configDataFilterFIFO(uint32_t base, uint16_t config1,
                                         uint16_t config2);

//*****************************************************************************
//
//! Registers SDFM interrupt handler
//!
//! \param base is the base address of the SDFM module.
//! \param interruptType is the interrupt type.
//! \param handler is a pointer to the function to be called when the
//! serial peripheral interface interrupt occurs.
//!
//! This function registers the handler to be called when an SDFM interrupt
//! occurs.  This function enables the global interrupt in the interrupt
//! controller.
//! Specific SDFM interrupts must be enabled via SDFM_enableInterrupt().
//! If necessary, it is the interrupt handler's responsibility
//! to clear the interrupt source via SDFM_clearInterruptFlag().
//!
//! \sa Interrupt_register() for important information about registering
//!     interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void SDFM_registerInterrupt(uint32_t base,
                                   SDFM_InterruptType interruptType,
                                   void (*handler)(void));

//*****************************************************************************
//
//! Unregisters SDFM interrupt handler.
//!
//! \param base is the base address of the SDFM module.
//! \param interruptType is the interrupt type.
//!
//! This function clears the handler to be called when an SDFM interrupt
//! occurs.  This function also masks off the interrupt in the interrupt
//! controller so that the interrupt handler no longer is called.
//!
//! \sa Interrupt_register() for important information about registering
//!     interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
extern void SDFM_unregisterInterrupt(uint32_t base,
                                     SDFM_InterruptType interruptType);
//*****************************************************************************
//
// Close the Doxygen group.
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
#endif // __SDFM_H__
