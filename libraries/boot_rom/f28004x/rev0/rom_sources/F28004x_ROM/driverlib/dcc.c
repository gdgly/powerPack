//###########################################################################
//
// FILE:   dcc.c
//
// TITLE:  Stellaris style wrapper driver for C28x DCC peripheral.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "dcc.h"

//*****************************************************************************
//
// DCC_getRevisionNumber
//
//*****************************************************************************
uint16_t
DCC_getRevisionNumber(uint32_t base, DCC_RevisionNumber identifier)
{
    uint16_t number;

    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));

    //
    //  Get specified revision number or scheme
    //
    if (identifier == DCC_REVISION_MINOR)
    {
        number = (HWREGH(base + DCC_O_REV) & DCC_REV_MINOR_M);
    }
    else if (identifier == DCC_REVISION_CUSTOM)
    {
        number = (HWREGH(base + DCC_O_REV) & DCC_REV_CUSTOM_M) >>
                 DCC_REV_CUSTOM_S;
    }
    else if (identifier == DCC_REVISION_MAJOR)
    {
        number = (HWREGH(base + DCC_O_REV) & DCC_REV_MAJOR_M) >>
                 DCC_REV_MAJOR_S;
    }
    else if (identifier == DCC_REVISION_DESIGN)
    {
        number = (HWREGH(base + DCC_O_REV) & DCC_REV_RTL_M) >>
                 DCC_REV_RTL_S;
    }
    else if (identifier == DCC_REVISION_FUNCTIONAL)
    {
        number = (HWREGH(base + DCC_O_REV + 2U) & (DCC_REG_WORD_MASK >> 4U));
    }
    else
    {
        // Module Scheme
        number = (HWREGH(base + DCC_O_REV + 2U) &
                  (uint16_t)(DCC_REV_SCHEME_M >> 16U)) >> 14U;
    }

    return number;
}

//*****************************************************************************
//
// DCC_setCounterSeeds
//
//*****************************************************************************
void
DCC_setCounterSeeds(uint32_t base, uint32_t counter0, uint32_t validcounter0,
                    uint32_t counter1)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));
    ASSERT(validcounter0 >= 4U);
    ASSERT(counter0 > 0U);
    ASSERT(counter1 > 0U);

    EALLOW;

    //
    // Set Counter 0 Seed
    //
    HWREGH(base + DCC_O_CNTSEED0) = counter0 & DCC_REG_WORD_MASK;
    HWREGH(base + DCC_O_CNTSEED0 + 2U) = (HWREGH(base + DCC_O_CNTSEED0 + 2U) &
                                          DCC_SEED_REG_MASK) |
                                         ((uint32_t)(counter0 &
                                          DCC_SEED_CNT_MASK) >> 16U);

    //
    // Set Valid Duration Counter 0 Seed
    //
    HWREGH(base + DCC_O_VALIDSEED0) = validcounter0;

    //
    // Set Counter 1 Seed
    //
    HWREGH(base + DCC_O_CNTSEED1) = counter1 & DCC_REG_WORD_MASK;
    HWREGH(base + DCC_O_CNTSEED1 + 2U) = (HWREGH(base + DCC_O_CNTSEED1 + 2U) &
                                          DCC_SEED_REG_MASK) |
                                         ((uint32_t)(counter1 &
                                          DCC_SEED_CNT_MASK) >> 16U);

    EDIS;
}
