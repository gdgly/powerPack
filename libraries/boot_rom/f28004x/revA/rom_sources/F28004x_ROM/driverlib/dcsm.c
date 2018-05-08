//###########################################################################
//
// FILE:   dcsm.c
//
// TITLE:  C28x Driver for the DCSM security module.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//##########################################################################

#include "dcsm.h"

//*****************************************************************************
//
// DCSM_unlockZone1CSM
//
//*****************************************************************************
void 
DCSM_unlockZone1CSM(DCSM_CSMPasswordKey *psCMDKey)
{
    uint32_t linkPointer;
    uint32_t zsbBase; // base address of the ZSB
    int32_t bitPos = 28;
    int32_t zeroFound = 0;

    linkPointer = HWREG(DCSMBANK0_Z1_BASE + DCSM_O_B0_Z1_LINKPOINTER);
    linkPointer = linkPointer << 3; // Bits 31 and 30 as most-significant 0 are
                                    //invalid LinkPointer options
    while((zeroFound == 0) && (bitPos > -1))
    {
        if( (linkPointer & 0x80000000U) == 0U)
        {
            zeroFound = 1;
            zsbBase =(DCSMBANK0_Z1OTP_BASE + (((uint32_t)bitPos + 3U) * 0x10));
        }
        else
        {
            bitPos--;
            linkPointer = linkPointer << 1;
        }
    }
    if(zeroFound == 0)
    {
        zsbBase = (DCSMBANK0_Z1OTP_BASE + 0X20);
    }
    // Perform dummy reads on the 128-bit password
    // Using linkPointer because it is no longer needed
    linkPointer = HWREG(zsbBase + DCSM_O_Z1_CSMPSWD0);
    linkPointer = HWREG(zsbBase + DCSM_O_Z1_CSMPSWD1);
    linkPointer = HWREG(zsbBase + DCSM_O_Z1_CSMPSWD2);
    linkPointer = HWREG(zsbBase + DCSM_O_Z1_CSMPSWD3);

    HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY0) = psCMDKey->csmKey0;
    HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY1) = psCMDKey->csmKey1;
    HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY2) = psCMDKey->csmKey2;
    HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY3) = psCMDKey->csmKey3;
}

//*****************************************************************************
//
// DCSM_unlockZone2CSM
//
//*****************************************************************************
void 
DCSM_unlockZone2CSM(DCSM_CSMPasswordKey *psCMDKey)
{
    uint32_t linkPointer;
    uint32_t zsbBase; // base address of the ZSB
    int32_t bitPos = 28;
    int32_t zeroFound = 0;

    linkPointer = HWREG(DCSMBANK0_Z2_BASE + DCSM_O_B0_Z2_LINKPOINTER);
    linkPointer = linkPointer << 3; // Bits 31 and 30 as most-sigificant 0 are
                                    //invalid LinkPointer options
    while((zeroFound == 0) && (bitPos > -1))
    {
        if( (linkPointer & 0x80000000U) == 0U)
        {
            zeroFound = 1;
            zsbBase =(DCSMBANK0_Z2OTP_BASE + (((uint32_t)bitPos + 3U) * 0x10));
        }
        else
        {
            bitPos--;
            linkPointer = linkPointer << 1;
        }
    }
    if(zeroFound == 0)
    {
        zsbBase = (DCSMBANK0_Z2OTP_BASE + 0x20);
    }
    // Perform dummy reads on the 128-bit password
    // Using linkPointer because it is no longer needed
    linkPointer = HWREG(zsbBase + DCSM_O_Z2_CSMPSWD0);
    linkPointer = HWREG(zsbBase + DCSM_O_Z2_CSMPSWD1);
    linkPointer = HWREG(zsbBase + DCSM_O_Z2_CSMPSWD2);
    linkPointer = HWREG(zsbBase + DCSM_O_Z2_CSMPSWD3);

    HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY0) = psCMDKey->csmKey0;
    HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY1) = psCMDKey->csmKey1;
    HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY2) = psCMDKey->csmKey2;
    HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY3) = psCMDKey->csmKey3;
}

//*****************************************************************************
//
// DCSM_getZone1FlashEXEStatus
//
//*****************************************************************************
DCSM_EXEOnlyStatus
DCSM_getZone1FlashEXEStatus(DCSM_Sector sector)
{
    uint16_t regValue;
    //
    // Check if sector belongs to this zone
    //
    if(DCSM_getFlashSectorZone(sector) != DCSM_MEMORY_ZONE1)
    {
        return(DCSM_INCORRECT_ZONE);
    }

    //
    // Get the EXE status register for the specific bank
    //
    if(sector <= DCSM_BANK0_SECTOR15)
    {
        regValue = HWREGH(DCSMBANK0_Z1_BASE + DCSM_O_B0_Z1_EXEONLYSECTR);
    }
    else
    {
        regValue = HWREGH(DCSMBANK1_Z1_BASE + DCSM_O_B1_Z1_EXEONLYSECTR);
        sector = (DCSM_Sector)((uint16_t)sector & 0xFU);
    }

    //
    // Get the EXE status of the Flash Sector
    //
    return((DCSM_EXEOnlyStatus)((regValue >> (uint16_t)sector) &
                                (uint16_t)0x01U));
}

//*****************************************************************************
//
// DCSM_getZone1RAMEXEStatus
//
//*****************************************************************************
DCSM_EXEOnlyStatus
DCSM_getZone1RAMEXEStatus(DCSM_RAMModule module)
{
    //
    // Check if module belongs to this zone
    //
    if(DCSM_getRAMZone(module) != DCSM_MEMORY_ZONE1)
    {
        return(DCSM_INCORRECT_ZONE);
    }
    
    //
    // Get the EXE status of the RAM Module
    //
    return((DCSM_EXEOnlyStatus)((HWREGH(DCSMBANK0_Z1_BASE + 
           DCSM_O_Z1_EXEONLYRAMR) >> (uint16_t)module) & (uint16_t)0x01U));
}

//*****************************************************************************
//
// DCSM_getZone2FlashEXEStatus
//
//*****************************************************************************
DCSM_EXEOnlyStatus
DCSM_getZone2FlashEXEStatus(DCSM_Sector sector)
{
    uint16_t regValue;
    // Check if sector belongs to this zone
    if(DCSM_getFlashSectorZone(sector) != DCSM_MEMORY_ZONE2)
    {
        return(DCSM_INCORRECT_ZONE);
    }

    //
    // Get the EXE status register for the specific bank
    //
    if(sector <= DCSM_BANK0_SECTOR15)
    {
        regValue = HWREGH(DCSMBANK0_Z2_BASE + DCSM_O_B0_Z2_EXEONLYSECTR);
    }
    else
    {
        regValue = HWREGH(DCSMBANK1_Z2_BASE + DCSM_O_B1_Z2_EXEONLYSECTR);
        sector = (DCSM_Sector)((uint16_t)sector & 0xFU);
    }

    //
    // Get the EXE status of the Flash Sector
    //
    return((DCSM_EXEOnlyStatus)((regValue >> (uint16_t)sector) & 
                                (uint16_t)0x01U));
}

//*****************************************************************************
//
// DCSM_getZone2RAMEXEStatus
//
//*****************************************************************************
DCSM_EXEOnlyStatus
DCSM_getZone2RAMEXEStatus(DCSM_RAMModule module)
{
    //
    // Check if module belongs to this zone
    //
    if(DCSM_getRAMZone(module) != DCSM_MEMORY_ZONE2)
    {
        return(DCSM_INCORRECT_ZONE);
    }

    //
    // Get the EXE status of the RAM Module
    //
    return((DCSM_EXEOnlyStatus)((HWREGH(DCSMBANK0_Z2_BASE + 
            DCSM_O_Z2_EXEONLYRAMR) >> (uint16_t)module) & (uint16_t)0x01U));
}

//*****************************************************************************
//
// DCSM_claimZoneSemaphore
//
//*****************************************************************************
bool 
DCSM_claimZoneSemaphore(DCSM_SemaphoreZone zone)
{
    //
    // FLSEM register address.
    //
    uint32_t regAddress = DCSMCOMMON_BASE + DCSM_O_FLSEM;

    EALLOW;

    //
    // Write 0xA5 to the key and write the zone that is attempting to claim the
    // Flash Pump Semaphore to the semaphore bits.
    //
    HWREGH(regAddress) = ((uint16_t)FLSEM_KEY << DCSM_FLSEM_KEY_S) |
                         (uint16_t)zone;
    EDIS;

    //
    // If the calling function was unable to claim the zone semaphore, then 
    // return false
    //
    if((HWREGH(regAddress) & DCSM_FLSEM_SEM_M) != (uint16_t)zone ){
        return(false);
    }

    return(true);
}

//*****************************************************************************
//
// DCSM_releaseZoneSemaphore
//
//*****************************************************************************
bool 
DCSM_releaseZoneSemaphore(void)
{
    //
    // FLSEM register address.
    //
    uint32_t regAddress = DCSMCOMMON_BASE + DCSM_O_FLSEM;

    EALLOW;

    //
    // Write 0xA5 to the key and write the zone that is attempting to claim the
    // Flash Pump Semaphore to the semaphore bits.
    //
    HWREGH(regAddress) = ((uint16_t)FLSEM_KEY << DCSM_FLSEM_KEY_S);
    EDIS;

    //
    // If the calling function was unable to claim the zone semaphore, then 
    // return false
    //
    if((HWREGH(regAddress) & DCSM_FLSEM_SEM_M) != 0x0U ){
        return(false);
    }

    return(true);
}
