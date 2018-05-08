//###########################################################################
//
// FILE:   sdfm.c
//
// TITLE:  C28x SDFM Driver
//
//###########################################################################
// $TI Release:
// $Release Date:
// $Copyright:  $
//###########################################################################

#include "sdfm.h"


// Get filter oversampling ratio
#define SDFM_GET_OSR(C) (((C) - 1) >> 8U)
// Maximum acceptable comparator filter oversampling ratio
#define SDFM_MAX_COMP_FILTER_OSR 31U
// Maximum acceptable data filter oversampling ratio
#define SDFM_MAX_DATA_FILTER_OSR 255U
// Get the filter type
#define SDFM_GET_FILTER_TYPE(C) ((C) & 0x30U)
// Get the filter number
#define SDFM_GET_FILTER_NUMBER(C)  ((C) & 0x3U)

// Get the low threshold
#define SDFM_GET_LOW_TRESHOLD(C) ((uint16_t)(C))
// Get the high threshold
#define SDFM_GET_HIGH_TRESHOLD(C) ((uint16_t)((uint32_t)(C) >> 16U))

// Get data shift value
#define SDFM_GET_SHIFT_VALUE(C) (((C) >> 2U) & 0x1FU)

//*****************************************************************************
//
// SDFM_configComparator
//
//*****************************************************************************
void SDFM_configComparator(uint32_t base, uint16_t config1,uint32_t config2)
{

    uint16_t oversamplingRatio;

    oversamplingRatio = SDFM_GET_OSR(config1);

    // Limit the oversampling ratio
    if(oversamplingRatio > SDFM_MAX_COMP_FILTER_OSR)
    {
        oversamplingRatio = SDFM_MAX_COMP_FILTER_OSR;
    }
    // Set the comparator filter type
    SDFM_setComparatorFilterType(base,
                          (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                            (SDFM_FilterType)SDFM_GET_FILTER_TYPE(config1));

    // Set the comparator filter over sampling ratio
    SDFM_setCompFilterOverSamplingRatio(base,
                           (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                             oversamplingRatio);

    // Set the comparator high threshold value
    SDFM_setCompFilterHighThreshold(base,
                          (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                                    SDFM_GET_HIGH_TRESHOLD(config2));

    // Set the comparator low threshold value
    SDFM_setCompFilterLowThreshold(base,
                            (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                                   SDFM_GET_LOW_TRESHOLD(config2));

}

//*****************************************************************************
//
// SDFM_configDataFilter
//
//*****************************************************************************
void SDFM_configDataFilter(uint32_t base, uint16_t config1,uint16_t config2)
{

    uint16_t oversamplingRatio;

    oversamplingRatio = SDFM_GET_OSR(config1);

    // Limit the oversampling ratio
    if(oversamplingRatio > SDFM_MAX_DATA_FILTER_OSR)
    {
        oversamplingRatio = SDFM_MAX_DATA_FILTER_OSR;
    }
    // Set the comparator filter type
    SDFM_setFilterType(base,(SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                       (SDFM_FilterType)SDFM_GET_FILTER_TYPE(config1));
    // Set the comparator filter over sampling ratio
    SDFM_setFilterOverSamplingRatio(base,
                           (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                             oversamplingRatio);

    // If filter switch on
    if((config2 & SDFM_FILTER_ENABLE) == SDFM_FILTER_ENABLE)
    {
        SDFM_enableFilter(base,
                         (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1));
    }
    else
    {
        SDFM_disableFilter(base,
                         (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1));
    }

    // Set output data format
    SDFM_setOutputDataFormat(base,
                            (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                            (SDFM_OutputDataFormat)(config2 & 0x1U));

    // Set the shift value if data is in 16bit 2's complement format
    if((config2 & 0x1U) == (uint16_t)(SDFM_DATA_FORMAT_16_BIT))
    {
            SDFM_setDataShiftValue(base,
                           (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                            SDFM_GET_SHIFT_VALUE(config2));
    }
}

//*****************************************************************************
//
// SDFM_configZeroCrossComparator
//
//*****************************************************************************
void SDFM_configZeroCrossComparator(uint32_t base, uint16_t config1,
                                        uint16_t config2)
{
    uint16_t oversamplingRatio;

    oversamplingRatio = SDFM_GET_OSR(config1);

    // Limit the oversampling ratio
    if(oversamplingRatio > SDFM_MAX_COMP_FILTER_OSR)
    {
        oversamplingRatio = SDFM_MAX_COMP_FILTER_OSR;
    }
    // Set the comparator filter type
    SDFM_setComparatorFilterType(base,
                          (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                            (SDFM_FilterType)SDFM_GET_FILTER_TYPE(config1));
    // Set the comparator filter over sampling ratio
    SDFM_setCompFilterOverSamplingRatio(base,
                           (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                             oversamplingRatio);
    // Set the zero cross threshold value
    SDFM_setCompFilterZeroCrossThreshold(base,
                          (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                                    config2);
}

//*****************************************************************************
//
// SDFM_configDataFilterFIFO
//
//*****************************************************************************
void SDFM_configDataFilterFIFO(uint32_t base, uint16_t config1,
                                         uint16_t config2)
{

    uint16_t oversamplingRatio;
    uint16_t fifoLevel;

    fifoLevel = ((config2 >> 7U) & 0x10U);
    oversamplingRatio = SDFM_GET_OSR(config1);

    // Limit the oversampling ratio
    if(oversamplingRatio > SDFM_MAX_DATA_FILTER_OSR)
    {
        oversamplingRatio = SDFM_MAX_DATA_FILTER_OSR;
    }
    // Set the comparator filter type
    SDFM_setFilterType(base,(SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                       (SDFM_FilterType)SDFM_GET_FILTER_TYPE(config1));
    // Set the comparator filter over sampling ratio
    SDFM_setFilterOverSamplingRatio(base,
                           (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                             oversamplingRatio);
    // If filter switch on
    if((config2 & SDFM_FILTER_ENABLE) == SDFM_FILTER_ENABLE)
    {
        SDFM_enableFilter(base,
                         (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1));
    }
    else
    {
        SDFM_disableFilter(base,
                         (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1));
    }

    // Set output data format
    SDFM_setOutputDataFormat(base,
                            (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                            (SDFM_OutputDataFormat)(config2 & 0x1U));

    // Set the shift value if data is in 16bit 2's complement format
    if((config2 & 0x1U) == (uint16_t)(SDFM_DATA_FORMAT_16_BIT))
    {
            SDFM_setDataShiftValue(base,
                           (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                            SDFM_GET_SHIFT_VALUE(config2));
    }
    // Set the FIFO level if level is > 0 and enable FIFO
    if(fifoLevel > 0U)
    {
        SDFM_setFIFOInterruptLevel(base,
        (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1),
                                              fifoLevel);
        SDFM_enableFIFOBuffer(base,
                          (SDFM_FilterNumber)SDFM_GET_FILTER_NUMBER(config1));
    }
}

//*****************************************************************************
//
//! \internal
//! Gets the SDFM interrupt number.
//!
//! \param base is the base address of the SDFM module.
//! \param interruptType is the interrupt type.
//!
//! Given an SDFM base address, this function returns the corresponding
//! interrupt number.
//!
//! \return Returns an SDFM interrupt number, or 0 if \e base is invalid.
//
//*****************************************************************************
static uint32_t SDFM_getIntNumber(uint32_t base,
                                  SDFM_InterruptType interruptType)
{
    uint32_t intNumber;

    ASSERT(SDFM_isBaseValid(base));

    switch(interruptType)
    {
        case SDFM_INTERRUPT:
            intNumber = INT_SDFM1;
        break;

        case SDFM_FILTER_1_DATA_READY_INTERRUPT:
            intNumber = INT_SDFM1DR1;
        break;

        case SDFM_FILTER_2_DATA_READY_INTERRUPT:
            intNumber = INT_SDFM1DR2;
        break;

        case SDFM_FILTER_3_DATA_READY_INTERRUPT:
            intNumber = INT_SDFM1DR3;
        break;

        case SDFM_FILTER_4_DATA_READY_INTERRUPT:
            intNumber = INT_SDFM1DR4;
        break;

        default:
            intNumber = 0U;
        break;
    }

    return(intNumber);
}

//*****************************************************************************
//
// SDFM_registerInterrupt
//
//*****************************************************************************
void SDFM_registerInterrupt(uint32_t base,
                            SDFM_InterruptType interruptType,
                            void (*handler)(void))
{
    uint32_t intNumber;

    ASSERT(SDFM_isBaseValid(base));

    intNumber = SDFM_getIntNumber(base,interruptType);

    ASSERT(intNumber != 0U);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the SDFM interrupt.
    //
    Interrupt_enable(intNumber);

}

//*****************************************************************************
//
// SDFM_unregisterInterrupt
//
//*****************************************************************************
void SDFM_unregisterInterrupt(uint32_t base, SDFM_InterruptType interruptType)
{
    uint32_t intNumber;

    ASSERT(SDFM_isBaseValid(base));

    //
    // Determine the interrupt number based on the SDFM port.
    //
    intNumber = SDFM_getIntNumber(base,interruptType);

    ASSERT(intNumber != 0U);

    //
    // Disable the SDFM interrupt.
    //
    Interrupt_disable(intNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(intNumber);
}

