//###########################################################################
//
// FILE:   interrupt.c
//
// TITLE:  C28x Interrupt (PIE) driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "interrupt.h"

//*****************************************************************************
//
//! \internal
//! Clears the IFR flag in the CPU.
//!
//! \param group specifies the interrupt group to be cleared.
//!
//! This function clears the IFR flag.  This switch is needed because the
//! clearing of the IFR can only be done with a constant.
//
//*****************************************************************************
static void Interrupt_clearIFR(uint16_t group)
{
    switch(group)
    {
        case 0x0001U:
            IFR &= ~0x0001U;
            break;
        case 0x0002U:
            IFR &= ~0x0002U;
            break;
        case 0x0004U:
            IFR &= ~0x0004U;
            break;
        case 0x0008U:
            IFR &= ~0x0008U;
            break;
        case 0x0010U:
            IFR &= ~0x0010U;
            break;
        case 0x0020U:
            IFR &= ~0x0020U;
            break;
        case 0x0040U:
            IFR &= ~0x0040U;
            break;
        case 0x0080U:
            IFR &= ~0x0080U;
            break;
        case 0x0100U:
            IFR &= ~0x0100U;
            break;
        case 0x0200U:
            IFR &= ~0x0200U;
            break;
        case 0x0400U:
            IFR &= ~0x0400U;
            break;
        case 0x0800U:
            IFR &= ~0x0800U;
            break;
        case 0x1000U:
            IFR &= ~0x1000U;
            break;
        case 0x2000U:
            IFR &= ~0x2000U;
            break;
        case 0x4000U:
            IFR &= ~0x4000U;
            break;
        case 0x8000U:
            IFR &= ~0x8000U;
            break;
        default:
            // Invalid group mask.
            break;
    }
}

//*****************************************************************************
//
// Interrupt_initVectorTable
//
//*****************************************************************************
void
Interrupt_initVectorTable(void)
{
    uint32_t i;

    EALLOW;
    // We skip the first three locations because they are initialized by Boot
    // ROM with boot variables.
    for(i = 3U; i < 224U; i++)
    {
        HWREG(PIEVECTTABLE_BASE + (2U * i)) =
            (uint32_t)Interrupt_defaultHandler;
    }
    
    // NMI and ITRAP get their own handlers.
    HWREG(PIEVECTTABLE_BASE + ((INT_NMI >> 16) * 2)) =
            (uint32_t)Interrupt_nmiHandler;
    HWREG(PIEVECTTABLE_BASE + ((INT_ILLEGAL >> 16) * 2)) =
            (uint32_t)Interrupt_illegalOperationHandler;
    
    EDIS;
}

//*****************************************************************************
//
//Interrupt_enable
//
//*****************************************************************************
void
Interrupt_enable(uint32_t interruptNumber)
{
    bool intsEnabled;
    uint16_t intGroup;
    uint16_t groupMask;
    uint16_t vectID;

    vectID = (uint16_t)(interruptNumber >> 16);

    EALLOW;

    // Ensure that PIE is enabled
    HWREGH(PIECTRL_BASE + PIE_O_CTRL) |= PIE_CTRL_ENPIE;

    intsEnabled = Interrupt_disableMaster();

    // PIE Interrupts
    if(vectID >= 0x20U)
    {
        intGroup = ((uint16_t)(interruptNumber & 0xFF00U) >> 8) - 1U;
        groupMask = 1U << intGroup;

        HWREGH(PIECTRL_BASE + PIE_O_IER1 + (intGroup * 2U)) |=
            1U << ((uint16_t)(interruptNumber & 0xFFU) - 1U);

        // Enable PIE Group Interrupt
        IER |= groupMask;
    }
    // INT13, INT14, DLOGINT, & RTOSINT
    else if((vectID >= 0x0DU) && (vectID <= 0x10U))
    {
        IER |= 1U << (vectID - 1U);
    }
    else
    {
        // Other interrupts
    }

    EDIS;

    // Re-enable interrupts if they were enabled
    if(!intsEnabled)
    {
        (void)Interrupt_enableMaster();
    }
}

//*****************************************************************************
//
// Interrupt_disable
//
//*****************************************************************************
void
Interrupt_disable(uint32_t interruptNumber)
{
    bool intsEnabled;
    uint16_t intGroup;
    uint16_t groupMask;
    uint16_t vectID;

    vectID = (uint16_t)(interruptNumber >> 16);

    EALLOW;

    intsEnabled = Interrupt_disableMaster();

    // PIE Interrupts
    if(vectID >= 0x20U)
    {
        intGroup = ((uint16_t)(interruptNumber & 0xFF00U) >> 8) - 1U;
        groupMask = 1U << intGroup;

        // Disable individual PIE interrupt
        HWREGH(PIECTRL_BASE + PIE_O_IER1 + (intGroup * 2U)) &=
            ~(1U << ((uint16_t)(interruptNumber & 0xFFU) - 1U));

        // Wait for any pending interrupts to get to the CPU
        __asm(" nop");
        __asm(" nop");
        __asm(" nop");
        __asm(" nop");
        __asm(" nop");

        Interrupt_clearIFR(groupMask);

        // Acknowledge any interrupts
        HWREGH(PIECTRL_BASE + PIE_O_ACK) = groupMask;
    }
    // INT13, INT14, DLOGINT, & RTOSINT
    else if((vectID >= 0x0DU) && (vectID <= 0x10U))
    {
        IER &= ~(1U << (vectID - 1U));
    }
    else
    {
        // Other interrupts
    }

    EDIS;

    // Re-enable interrupts if they were enabled
    if(!intsEnabled)
    {
        (void)Interrupt_enableMaster();
    }
}
