//###########################################################################
//
// FILE:   interrupt.h
//
// TITLE:  C28x Interrupt (PIE) driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

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
//! \addtogroup interrupt_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_pie.h"
#include "inc/hw_types.h"
#include "cpu.h"

//*****************************************************************************
//
// The following are values that can be passed to the Interrupt_enableInCPU()
// and Interrupt_disableInCPU() functions as the cpuInterrupt parameter.
//
//*****************************************************************************
#define INTERRUPT_CPU_INT1    0x1U      //!< CPU Interrupt Number 1
#define INTERRUPT_CPU_INT2    0x2U      //!< CPU Interrupt Number 2
#define INTERRUPT_CPU_INT3    0x4U      //!< CPU Interrupt Number 3
#define INTERRUPT_CPU_INT4    0x8U      //!< CPU Interrupt Number 4
#define INTERRUPT_CPU_INT5    0x10U     //!< CPU Interrupt Number 5
#define INTERRUPT_CPU_INT6    0x20U     //!< CPU Interrupt Number 6
#define INTERRUPT_CPU_INT7    0x40U     //!< CPU Interrupt Number 7
#define INTERRUPT_CPU_INT8    0x80U     //!< CPU Interrupt Number 8
#define INTERRUPT_CPU_INT9    0x100U    //!< CPU Interrupt Number 9
#define INTERRUPT_CPU_INT10   0x200U    //!< CPU Interrupt Number 10
#define INTERRUPT_CPU_INT11   0x400U    //!< CPU Interrupt Number 11
#define INTERRUPT_CPU_INT12   0x800U    //!< CPU Interrupt Number 12
#define INTERRUPT_CPU_INT13   0x1000U   //!< CPU Interrupt Number 13
#define INTERRUPT_CPU_INT14   0x2000U   //!< CPU Interrupt Number 14
#define INTERRUPT_CPU_DLOGINT 0x4000U   //!< CPU Data Log Interrupt
#define INTERRUPT_CPU_RTOSINT 0x8000U   //!< CPU RTOS Interrupt

//*****************************************************************************
//
// The following are values that can be passed to the Interrupt_clearACKGroup()
// function as the group parameter.
//
//*****************************************************************************
#define INTERRUPT_ACK_GROUP1    0x1U    //!< Acknowledge PIE Interrupt Group 1
#define INTERRUPT_ACK_GROUP2    0x2U    //!< Acknowledge PIE Interrupt Group 2
#define INTERRUPT_ACK_GROUP3    0x4U    //!< Acknowledge PIE Interrupt Group 3
#define INTERRUPT_ACK_GROUP4    0x8U    //!< Acknowledge PIE Interrupt Group 4
#define INTERRUPT_ACK_GROUP5    0x10U   //!< Acknowledge PIE Interrupt Group 5
#define INTERRUPT_ACK_GROUP6    0x20U   //!< Acknowledge PIE Interrupt Group 6
#define INTERRUPT_ACK_GROUP7    0x40U   //!< Acknowledge PIE Interrupt Group 7
#define INTERRUPT_ACK_GROUP8    0x80U   //!< Acknowledge PIE Interrupt Group 8
#define INTERRUPT_ACK_GROUP9    0x100U  //!< Acknowledge PIE Interrupt Group 9
#define INTERRUPT_ACK_GROUP10   0x200U  //!< Acknowledge PIE Interrupt Group 10
#define INTERRUPT_ACK_GROUP11   0x400U  //!< Acknowledge PIE Interrupt Group 11
#define INTERRUPT_ACK_GROUP12   0x800U  //!< Acknowledge PIE Interrupt Group 12

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! The default interrupt handler.
//!
//! This is the default interrupt handler.  The Interrupt_initVectorTable()
//! function sets all vectors to this function.  Also, when an interrupt is
//! unregistered using the Interrupt_unregister() function, this handler takes
//! its place.  This should never be called during normal operation.
//!
//! The ESTOP0 statement is for debug purposes only. Remove and replace with an
//! appropriate error handling routine for your program.
//!
//! \return None.
//
//*****************************************************************************
static void Interrupt_defaultHandler(void)
{
    uint16_t vectID;

    // Calculate vector ID. It's the offset of the vector that was fetched
    // (bits 7:1 of PIECTRL.PIEVECT) divided by two.
    vectID = (HWREGH(PIECTRL_BASE + PIE_O_CTRL) & 0xFEU) >> 1U;

    // This line just suppresses the "variable set but never used" warning.
    if(vectID == 0U);

    // Something has gone wrong. An interrupt without a proper registered
    // handler function has occurred. To help you debug the issue, local
    // variable vectID contains the vector ID of the interrupt that occurred.
    ESTOP0;
    for(;;);
}

//*****************************************************************************
//
//! \internal
//! The default illegal instruction trap interrupt handler.
//!
//! This is the default interrupt handler for an illegal instruction trap
//! (ITRAP).  The Interrupt_initVectorTable() function sets the appropriate
//! vector to this function.  This should never be called during normal
//! operation.
//!
//! The ESTOP0 statement is for debug purposes only.  Remove and replace with
//! an appropriate error handling routine for your program.
//!
//! \return None.
//
//*****************************************************************************
static void Interrupt_illegalOperationHandler(void)
{
    // Something has gone wrong.  The CPU has tried to execute an illegal
    // instruction, generating an illegal instruction trap (ITRAP).
    ESTOP0;
    for(;;);
}

//*****************************************************************************
//
//! \internal
//! The default non-maskable interrupt handler.
//!
//! This is the default interrupt handler for a non-maskable interrupt (NMI).
//! The Interrupt_initVectorTable() function sets the appropriate vector to
//! this function.  This should never be called during normal operation.
//!
//! The ESTOP0 statement is for debug purposes only. Remove and replace with an
//! appropriate error handling routine for your program.
//!
//! \return None.
//
//*****************************************************************************
static void Interrupt_nmiHandler(void)
{
    // A non-maskable interrupt has occurred, indicating that a hardware error
    // has occurred in the system.  You can use SysCtl_getNMIFlagStatus() to
    // to read the NMIFLG register and determine what caused the NMI.
    ESTOP0;
    for(;;);
}

//*****************************************************************************
//
//! Enables the processor interrupt.
//!
//! This function clears the global interrupt mask bit (INTM) in the CPU,
//! allowing the processor to respond to interrupts.
//!
//! \return Returns \b true if interrupts were disabled when the function was
//! called or \b false if they were initially enabled.
//
//*****************************************************************************
static inline bool
Interrupt_enableMaster(void)
{
    // Enable processor interrupts.
    return(((__enable_interrupts() & 0x1U) != 0U) ? true : false);
}

//*****************************************************************************
//
//! Disables the processor interrupt.
//!
//! This function sets the global interrupt mask bit (INTM) in the CPU,
//! preventing the processor from receiving maskable interrupts.
//!
//! \return Returns \b true if interrupts were already disabled when the
//! function was called or \b false if they were initially enabled.
//
//*****************************************************************************
static inline bool
Interrupt_disableMaster(void)
{
    // Disable processor interrupts.
    return(((__disable_interrupts() & 0x1U) != 0U) ? true : false);
}

//*****************************************************************************
//
//! Registers a function to be called when an interrupt occurs.
//!
//! Assumes PIE is enabled
//!
//! \param interruptNumber specifies the interrupt in question.
//! \param handler is a pointer to the function to be called.
//!
//! This function is used to specify the handler function to be called when the
//! given interrupt is asserted to the processor.  When the interrupt occurs,
//! if it is enabled (via Interrupt_enable()), the handler function will be
//! called in interrupt context.  Since the handler function can pre-empt other
//! code, care must be taken to protect memory or peripherals that are accessed
//! by the handler and other non-handler code.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_register(uint32_t interruptNumber, void (*handler)(void))
{
    EALLOW;
    // Copy ISR address into PIE table
    HWREG(PIEVECTTABLE_BASE + (((interruptNumber & 0xFFFF0000U) >> 16) * 2U)) =
        (uint32_t)handler;
    EDIS;
}

//*****************************************************************************
//
//! Unregisters the function to be called when an interrupt occurs.
//!
//! \param interruptNumber specifies the interrupt in question.
//!
//! This function is used to indicate that a default handler
//! Interrupt_defaultHandler() should be called when the given interrupt is
//! asserted to the processor.  Call Interrupt_disable() to disable
//! the interrupt before calling this function.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_unregister(uint32_t interruptNumber)
{
    EALLOW;
    // Copy default ISR address into PIE table
    HWREG(PIEVECTTABLE_BASE + (((interruptNumber & 0xFFFF0000U) >> 16) * 2U)) =
        (uint32_t)Interrupt_defaultHandler;
    EDIS;
}

//*****************************************************************************
//
//! Enable CPU interrupts
//!
//! \param cpuInterrupt specifies the CPU interrupts to be enabled.
//!
//! This function enables the specified interrupts in the CPU. The
//! \e cpuInterrupt parameter is a logical OR of the values
//! \b INTERRUPT_CPU_INTx where x is the interrupt number between 1 and 14,
//! \b INTERRUPT_CPU_DLOGINT, and \b INTERRUPT_CPU_RTOSINT.
//!
//! Note that interrupts 1-12 correspond to the PIE groups with those same
//! numbers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_enableInCPU(uint16_t cpuInterrupt)
{
    // Set the interrupt bits in the CPU.
    IER |= cpuInterrupt;
}

//*****************************************************************************
//
//! Disable CPU interrupts
//!
//! \param cpuInterrupt specifies the CPU interrupts to be disabled.
//!
//! This function disables the specified interrupts in the CPU. The
//! \e cpuInterrupt parameter is a logical OR of the values
//! \b INTERRUPT_CPU_INTx where x is the interrupt number between 1 and 14,
//! \b INTERRUPT_CPU_DLOGINT, and \b INTERRUPT_CPU_RTOSINT.
//!
//! Note that interrupts 1-12 correspond to the PIE groups with those same
//! numbers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_disableInCPU(uint16_t cpuInterrupt)
{
    // Clear the interrupt bits in the CPU.
    IER &= ~cpuInterrupt;
}

//*****************************************************************************
//
//! Acknowledges PIE Interrupt Group
//!
//! \param group specifies the interrupt group to be acknowledged.
//!
//! The specified interrupt group is acknowledged and clears any interrupt
//! flag within that respective group.
//!
//! The \e group parameter must be a logical OR of the following:
//! \b INTERRUPT_ACK_GROUP1, \b INTERRUPT_ACK_GROUP2, \b INTERRUPT_ACK_GROUP3
//! \b INTERRUPT_ACK_GROUP4, \b INTERRUPT_ACK_GROUP5, \b INTERRUPT_ACK_GROUP6
//! \b INTERRUPT_ACK_GROUP7, \b INTERRUPT_ACK_GROUP8, \b INTERRUPT_ACK_GROUP9
//! \b INTERRUPT_ACK_GROUP10, \b INTERRUPT_ACK_GROUP11,
//! \b INTERRUPT_ACK_GROUP12.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_clearACKGroup(uint16_t group)
{
    EALLOW;
    // Set interrupt group acknowledge bits
    HWREGH(PIECTRL_BASE + PIE_O_ACK) = group;
    EDIS;
}

//*****************************************************************************
//
//! Initializes the PIE vector table by setting all vectors to a default
//! handler function.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_initVectorTable(void);

//*****************************************************************************
//
//! Enables an interrupt.
//!
//! \param interruptNumber specifies the interrupt to be enabled.
//!
//! The specified interrupt is enabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_enable(uint32_t interruptNumber);

//*****************************************************************************
//
//! Disables an interrupt.
//!
//! \param interruptNumber specifies the interrupt to be disabled.
//!
//! The specified interrupt is disabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_disable(uint32_t interruptNumber);

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

#endif // __INTERRUPT_H__
