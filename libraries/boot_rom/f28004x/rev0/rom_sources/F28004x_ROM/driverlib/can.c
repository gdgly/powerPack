//###########################################################################
//
// FILE:   can.c
//
// TITLE:  Stellaris style wrapper driver for C28x CAN peripheral.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

//*****************************************************************************
//! \addtogroup can_api
//! @{
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "can.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
// This is the maximum number that can be stored as an 11bit Message
// identifier.
//*****************************************************************************
#define CAN_MAX_11BIT_MSG_ID    (0x7FFU)

//*****************************************************************************
// This is used as the loop delay for accessing the CAN controller registers.
//*****************************************************************************

//
// The maximum CAN bit timing divisor is 13.
//
#define CAN_MAX_BIT_DIVISOR     (13U)

//
// The minimum CAN bit timing divisor is 5.
//
#define CAN_MIN_BIT_DIVISOR     (5U)

//
// The maximum CAN pre-divisor is 1024.
//
#define CAN_MAX_PRE_DIVISOR     (1024U)

//
// The minimum CAN pre-divisor is 1.
//
#define CAN_MIN_PRE_DIVISOR     (1U)

//*****************************************************************************
// This table is used by the CAN_setBitRate() API as the register defaults for
// the bit timing values.
//*****************************************************************************
static const uint16_t CAN_bitValues[] =
{
    0x1100U, // TSEG2 2, TSEG1 2, SJW 1, Divide 5
    0x1200U, // TSEG2 2, TSEG1 3, SJW 1, Divide 6
    0x2240U, // TSEG2 3, TSEG1 3, SJW 2, Divide 7
    0x2340U, // TSEG2 3, TSEG1 4, SJW 2, Divide 8
    0x3340U, // TSEG2 4, TSEG1 4, SJW 2, Divide 9
    0x3440U, // TSEG2 4, TSEG1 5, SJW 2, Divide 10
    0x3540U, // TSEG2 4, TSEG1 6, SJW 2, Divide 11
    0x3640U, // TSEG2 4, TSEG1 7, SJW 2, Divide 12
    0x3740U  // TSEG2 4, TSEG1 8, SJW 2, Divide 13
};

//*****************************************************************************
//! \internal
//! Checks a CAN base address.
//!
//! \param base is the base address of the CAN controller.
//!
//! This function determines if a CAN controller base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static bool
CAN_isBaseValid(uint32_t base)
{
    return((base == CANA_BASE));
}
#endif

//*****************************************************************************
//! \internal
//!
//! Returns the CAN controller interrupt number.
//!
//! \param base is the base address of the selected CAN controller
//! \param number is the interrupt line number requested, valid values are 0
//! or 1
//!
//! Given a CAN controller base address and interrupt line number, returns the
//! corresponding interrupt number.
//!
//! \return Returns a CAN interrupt number, or -1 if \e ulPort is invalid.
//
//*****************************************************************************
static int32_t
CAN_getIntNumber(uint32_t base, uint16_t number)
{
    int32_t intNumber;

    //
    // Return the interrupt number for the given CAN controller.
    //
    switch(base)
    {
        //
        // Return the interrupt number for CAN 0
        //
        case CANA_BASE:
        {
            switch(number)
            {
                case 0U:
                {
                    intNumber = (int32_t)INT_CANA_1;
                    break;
                }
                case 1U:
                {
                    intNumber = (int32_t)INT_CANA_2;
                    break;

                }
                default:
                {
                    intNumber = -1;
                    break;
                }
            }
            break;
        }

        //
        // Return -1 to indicate a bad address was passed in.
        //
        default:
        {
            intNumber = -1;
            break;
        }
    }

    return(intNumber);
}

//*****************************************************************************
//! \internal
//!
//! Copies data from a buffer to the CAN Data registers.
//!
//! \param data is a pointer to the data to be written out to the CAN
//! controller's data registers.
//! \param address is an uint32_t pointer to the first register of the
//! CAN controller's data registers.  For example, in order to use the IF1
//! register set on CAN controller 0, the value would be: \b CANA_BASE \b +
//! \b CAN_O_IF1DATA.
//! \param size is the number of bytes to copy into the CAN controller.
//!
//! This function takes the steps necessary to copy data from a contiguous
//! buffer in memory into the non-contiguous data registers used by the CAN
//! controller.  This function is rarely used outside of the CAN_setMessage()
//! function.
//!
//! This function replaces the original CANWriteDataReg() API and performs the
//! same actions.  A macro is provided in <tt>can.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
static void
CAN_writeDataReg(uint16_t *data, uint32_t *address, uint32_t size)
{
    uint32_t idx;
    uint16_t *dataReg = (uint16_t *)address;

    //
    // Loop always copies 1 byte per iteration.
    //
    for(idx = 0U; idx < size; idx++)
    {
        //
        // Write out the data 8 bits at a time.
        //
        HWREGB(dataReg) = data[idx];

        dataReg++;
    }
}

//*****************************************************************************
//! \internal
//!
//! Copies data from a buffer to the CAN Data registers.
//!
//! \param data is a pointer to the location to store the data read from the
//! CAN controller's data registers.
//! \param address is an uint32_t pointer to the first register of the
//! CAN controller's data registers.  For example, in order to use the IF1
//! register set on CAN controller 1, the value would be: \b CANA_BASE \b +
//! \b CAN_O_IF1DATA.
//! \param size is the number of bytes to copy from the CAN controller.
//!
//! This function takes the steps necessary to copy data to a contiguous buffer
//! in memory from the non-contiguous data registers used by the CAN
//! controller.  This function is rarely used outside of the CAN_getMessage()
//! function.
//!
//! This function replaces the original CANReadDataReg() API and performs the
//! same actions.  A macro is provided in <tt>can.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
static void
CAN_readDataReg(uint16_t *data, uint32_t *address, uint32_t size)
{
    uint32_t idx;
    uint16_t *dataReg = (uint16_t *)address;

    //
    // Loop always copies 1 byte per iteration.
    //
    for(idx = 0U; idx < size; idx++)
    {
        //
        // Read out the data
        //
        data[idx] = HWREGB(dataReg);

        dataReg++;
    }
}

//*****************************************************************************
//! Initializes the CAN controller after reset.
//!
//! \param base is the base address of the CAN controller.
//!
//! After reset, the CAN controller is left in the disabled state.  However,
//! the memory used for message objects contains undefined values and must be
//! cleared prior to enabling the CAN controller the first time.  This prevents
//! unwanted transmission or reception of data before the message objects are
//! configured.  This function must be called before enabling the controller
//! the first time.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_initModule(uint32_t base)
{
    int32_t msg;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Initialize the message RAM before using it.
    //
    CAN_initRam(base);

    //
    // Place CAN controller in init state, regardless of previous state.  This
    // will put controller in idle, and allow the message object RAM to be
    // programmed.
    //
    HWREG(base + CAN_O_CTL) = CAN_CTL_INIT | (0x5U << CAN_CTL_PMD_S);
    HWREG(base + CAN_O_CTL) |=  CAN_CTL_SWR;

    //
    // Wait for busy bit to clear
    //
    while((HWREG(base + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) == CAN_IF1CMD_BUSY)
    {
    }

    //
    // Clear the message value bit in the arbitration register.  This indicates
    // the message is not valid and is a "safe" condition to leave the message
    // object.  The same arb reg is used to program all the message objects.
    //
    HWREGH(base + CAN_O_IF1CMD + 2U) = (CAN_IF1CMD_DIR | CAN_IF1CMD_ARB |
                                       CAN_IF1CMD_CONTROL) >> 16U;
    HWREG(base + CAN_O_IF1ARB) = 0U;
    HWREG(base + CAN_O_IF1MCTL) = 0U;

    HWREGH(base + CAN_O_IF2CMD + 2U) = (CAN_IF2CMD_DIR | CAN_IF2CMD_ARB |
                                       CAN_IF2CMD_CONTROL) >> 16U;
    HWREG(base + CAN_O_IF2ARB) = 0U;
    HWREG(base + CAN_O_IF2MCTL) = 0U;

    //
    // Loop through to program all 32 message objects
    //
    for(msg = 1; msg <= 32; msg ++)
    {
        msg++;

        //
        // Wait for busy bit to clear
        //
        while((HWREG(base + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) ==
              CAN_IF1CMD_BUSY)
        {
        }

        //
        // Initiate programming the message object
        //
        HWREGH(base + CAN_O_IF1CMD) = msg;

        //
        // Wait for busy bit to clear
        //
        while((HWREG(base + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY) ==
              CAN_IF2CMD_BUSY)
        {
        }

        //
        // Initiate programming the message object
        //
        HWREGH(base + CAN_O_IF2CMD) = msg + 1;
    }

    //
    // Make sure that the interrupt and new data flags are updated for the
    // message objects.
    //
    HWREGH(base + CAN_O_IF1CMD + 2U) = (CAN_IF1CMD_TXRQST |
                                        CAN_IF1CMD_CLRINTPND) >> 16U;
    HWREGH(base + CAN_O_IF2CMD + 2U) = (CAN_IF2CMD_TXRQST |
                                        CAN_IF2CMD_CLRINTPND) >> 16U;

    //
    // Loop through to program all 32 message objects
    //
    for(msg = 1; msg <= 32; msg ++)
    {
        msg++;

        //
        // Wait for busy bit to clear.
        //
        while((HWREG(base + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) ==
              CAN_IF1CMD_BUSY)
        {
        }

        //
        // Initiate programming the message object
        //
        HWREGH(base + CAN_O_IF1CMD) = msg;

        //
        // Wait for busy bit to clear.
        //
        while((HWREG(base + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY) ==
              CAN_IF2CMD_BUSY)
        {
        }

        //
        // Initiate programming the message object
        //
        HWREGH(base + CAN_O_IF2CMD) = msg + 1;
    }

    //
    // Acknowledge any pending status interrupts.
    //
    HWREG(base + CAN_O_ES);
}

//*****************************************************************************
//! Initializes the CAN controller's RAM.
//!
//! \param base is the base address of the CAN controller.
//!
//! Performs and initialization of the RAM used for the CAN message objects.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_initRam(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    HWREG(base + CAN_O_RAM_INIT) = CAN_RAM_INIT_CAN_RAM_INIT | 0x0A;

    while(!((HWREG(base + CAN_O_RAM_INIT) & CAN_RAM_INIT_RAM_INIT_DONE) ==
            CAN_RAM_INIT_RAM_INIT_DONE))
    {
        //
        // Wait until RAM Init is complete
        //
    }
}

//*****************************************************************************
//! Enables the CAN controller.
//!
//! \param base is the base address of the CAN controller to enable.
//!
//! Enables the CAN controller for message processing.  Once enabled, the
//! controller will automatically transmit any pending frames, and process any
//! received frames.  The controller can be stopped by calling
//! CAN_disableController().  Prior to calling CAN_enableController(),
//! CAN_initModule() should have been called to initialize the controller and
//! the CAN bus clock should be configured by calling CAN_setBitTiming().
//!
//! \return None.
//
//*****************************************************************************
void
CAN_enableController(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Clear the init bit in the control register.
    //
    HWREGH(base + CAN_O_CTL) = HWREGH(base + CAN_O_CTL) & ~CAN_CTL_INIT;
}

//*****************************************************************************
//! Disables the CAN controller.
//!
//! \param base is the base address of the CAN controller to disable.
//!
//! Disables the CAN controller for message processing.  When disabled, the
//! controller will no longer automatically process data on the CAN bus.  The
//! controller can be restarted by calling CAN_enableController().  The state
//! of the CAN controller and the message objects in the controller are left as
//! they were before this call was made.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_disableController(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Set the init bit in the control register.
    //
    HWREGH(base + CAN_O_CTL) = HWREGH(base + CAN_O_CTL) | CAN_CTL_INIT;
}

//*****************************************************************************
//! Enables the test modes of the CAN controller.
//!
//! \param base is the base address of the CAN controller.
//! \param mode are the the test modes to enable.
//!
//! Enables test modes within the controller.  Valid options for mode are as
//! follows:
//! - \b CAN_TEST_SILENT
//! - \b CAN_TEST_LBACK
//! - \b CAN_TEST_RX
//! - \b CAN_TEST_EXL
//! - \b CAN_TEST_RDA
//! Multiple options may also be OR'ed together.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_enableTestMode(uint32_t base, uint16_t mode)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Enable test mode and set the bits in the test register.
    //
    HWREGH(base + CAN_O_CTL) |= CAN_CTL_TEST;
    HWREGH(base + CAN_O_TEST) |= mode;
}

//*****************************************************************************
//! Sets the interruption debug mode of the CAN controller.
//!
//! \param base is the base address of the CAN controller.
//! \param enable is a flag to enable or disable the interruption debug mode.
//!
//! This function sets the interruption debug mode of the CAN controller. When
//! the \e enable parameter is \b true, CAN will be configured to interrupt any
//! transmission or reception and enter debug mode immediately after it is
//! requested. When \b false, CAN will wait for a started transmission or
//! reception to be completed before entering debug mode.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_setInterruptionDebugMode(uint32_t base, bool enable)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    if(enable)
    {
        //
        // Enable interrupt debug support
        //
        HWREGH(base + CAN_O_CTL) |= CAN_CTL_IDS;
    }
    else
    {
        //
        // Disable interrupt debug support
        //
        HWREGH(base + CAN_O_CTL) &= ~CAN_CTL_IDS;
    }
}

//*****************************************************************************
//! Disables the test modes of the CAN controller.
//!
//! \param base is the base address of the CAN controller.
//! \param mode are the the test modes to disable.
//!
//! Disables test modes within the controller.  Valid options for mode are as
//! follows:
//! - \b CAN_TEST_SILENT
//! - \b CAN_TEST_LBACK
//! - \b CAN_TEST_RX
//! - \b CAN_TEST_EXL
//! - \b CAN_TEST_RDA
//! Multiple options may also be OR'ed together.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_disableTestMode(uint32_t base, uint16_t mode)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Clear the bits in the test register.
    //
    HWREGH(base + CAN_O_TEST) &= ~mode;
}

//*****************************************************************************
//! Enables DMA Requests from the CAN controller.
//!
//! \param base is the base address of the CAN controller to enable.
//!
//! Enables the CAN controller DMA request lines for each of the 3 interface
//! register sets.  To actually assert the request line the DMA Active bit
//! must be set in the corresponding interface CMD register.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_enableDMARequests(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Set the DMA enable bits in the control register.
    //
    HWREGH(base + CAN_O_CTL + 2U) |= (CAN_CTL_DE1 | CAN_CTL_DE2 |
                                      CAN_CTL_DE3) >> 16U;
}

//*****************************************************************************
//! Disables DMA Requests from the CAN controller.
//!
//! \param base is the base address of the CAN controller to enable.
//!
//! Disables the CAN controller DMA request lines for each of the 3 interface
//! register sets.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_disableDMARequests(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Clear the DMA enable bits in the control register.
    //
    HWREGH(base + CAN_O_CTL + 2U) &= ~(CAN_CTL_DE1 | CAN_CTL_DE2 |
                                       CAN_CTL_DE3) >> 16U;
}

//*****************************************************************************
//! Reads the current settings for the CAN controller bit timing.
//!
//! \param base is the base address of the CAN controller.
//! \param clkParms is a pointer to a structure to hold the timing parameters.
//!
//! This function reads the current configuration of the CAN controller bit
//! clock timing, and stores the resulting information in the structure
//! supplied by the caller.  Refer to CAN_setBitTiming() for the meaning of
//! the values that are returned in the structure pointed to by \e clkParms.
//!
//! This function replaces the original CANGetBitTiming() API and performs the
//! same actions.  A macro is provided in <tt>can.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_getBitTiming(uint32_t base, CAN_BitClkParms *clkParms)
{
    uint32_t bitReg;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT(clkParms != 0U);

    bitReg = HWREG(base + CAN_O_BTR);

    //
    // Set the phase 2 segment.
    //
    clkParms->phase2Seg = ((bitReg & CAN_BTR_TSEG2_M) >> 12U) + 1U;

    //
    // Set the phase 1 segment.
    //
    clkParms->syncPropPhase1Seg = ((bitReg & CAN_BTR_TSEG1_M) >> 8U) + 1U;

    //
    // Set the synchronous jump width.
    //
    clkParms->sjw = ((bitReg & CAN_BTR_SJW_M) >> 6U) + 1U;

    //
    // Set the pre-divider for the CAN bus bit clock.
    //
    clkParms->quantumPrescaler = ((bitReg & CAN_BTR_BPR_M) |
                                 ((bitReg & CAN_BTR_BRPE_M) >> 10U)) + 1U;
}

//*****************************************************************************
//! This function is used to set the CAN bit timing values to a nominal setting
//! based on a desired bit rate.
//!
//! \param base is the base address of the CAN controller.
//! \param sourceClock is the clock frequency for the CAN peripheral in Hz.
//! \param bitRate is the desired bit rate.
//!
//! This function will set the CAN bit timing for the bit rate passed in the
//! \e bitRate parameter based on the \e sourceClock parameter.  The CAN
//! bit clock is calculated to be an average timing value that should work for
//! most systems.  If tighter timing requirements are needed, then the
//! CAN_setBitTiming() function is available for full customization of all of
//! the CAN bit timing values.  Since not all bit rates can be matched
//! exactly, the bit rate is set to the value closest to the desired bit rate
//! without being higher than the \e bitRate value.
//!
//! \return This function returns the bit rate that the CAN controller was
//! configured to use or it returns 0 to indicate that the bit rate was not
//! changed because the requested bit rate was not valid.
//
//*****************************************************************************
uint32_t
CAN_setBitRate(uint32_t base, uint32_t sourceClock, uint32_t bitRate)
{
    uint32_t desiredRatio;
    uint32_t canBits;
    uint32_t preDivide;
    uint32_t regValue;
    uint16_t canCtl;

    ASSERT(bitRate != 0);

    //
    // Calculate the desired clock rate.
    //
    desiredRatio = sourceClock / bitRate;

    //
    // If the ratio of CAN bit rate to processor clock is too small or too
    // large then return 0 indicating that no bit rate was set.
    //
    ASSERT(desiredRatio <= (CAN_MAX_PRE_DIVISOR * CAN_MAX_BIT_DIVISOR));
    ASSERT(desiredRatio >= (CAN_MIN_PRE_DIVISOR * CAN_MIN_BIT_DIVISOR));

    //
    // Make sure that the Desired Ratio is not too large.  This enforces the
    // requirement that the bit rate is larger than requested.
    //
    if((sourceClock / desiredRatio) > bitRate)
    {
        desiredRatio += 1U;
    }

    //
    // Check all possible values to find a matching value.
    //
    while(desiredRatio <= (CAN_MAX_PRE_DIVISOR * CAN_MAX_BIT_DIVISOR))
    {
        //
        // Loop through all possible CAN bit divisors.
        //
        for(canBits = CAN_MAX_BIT_DIVISOR; canBits >= CAN_MIN_BIT_DIVISOR;
            canBits--)
        {
            //
            // For a given CAN bit divisor save the pre divisor.
            //
            preDivide = desiredRatio / canBits;

            //
            // If the calculated divisors match the desired clock ratio then
            // return these bit rate and set the CAN bit timing.
            //
            if((preDivide * canBits) == desiredRatio)
            {
                //
                // Start building the bit timing value by adding the bit timing
                // in time quanta.
                //
                regValue = CAN_bitValues[canBits - CAN_MIN_BIT_DIVISOR];

                //
                // To set the bit timing register, the controller must be
                // placed in init mode (if not already), and also configuration
                // change bit enabled.  The state of the register should be
                // saved so it can be restored.
                //
                canCtl = HWREG(base + CAN_O_CTL);
                HWREG(base + CAN_O_CTL) = canCtl | CAN_CTL_INIT | CAN_CTL_CCE;

                //
                // Now add in the pre-scalar on the bit rate.
                //
                regValue |= ((preDivide - 1) & CAN_BTR_BPR_M) |
                            (((preDivide - 1) << 10) & CAN_BTR_BRPE_M);

                //
                // Set the clock bits in the and the bits of the pre-scalar.
                //
                HWREG(base + CAN_O_BTR) = regValue;

                //
                // Restore the saved CAN Control register.
                //
                HWREG(base + CAN_O_CTL) = canCtl;

                //
                // Return the computed bit rate.
                //
                return(sourceClock / ( preDivide * canBits));
            }
        }

        //
        // Move the divisor up one and look again.  Only in rare cases are
        // more than 2 loops required to find the value.
        //
        desiredRatio++;
    }
    return(0);
}

//*****************************************************************************
//! Configures the CAN controller bit timing.
//!
//! \param base is the base address of the CAN controller.
//! \param clkParms points to the structure with the clock parameters.
//!
//! Configures the various timing parameters for the CAN bus bit timing:
//! Propagation segment, Phase Buffer 1 segment, Phase Buffer 2 segment, and
//! the Synchronization Jump Width.  The values for Propagation and Phase
//! Buffer 1 segments are derived from the combination
//! \e clkParms->syncPropPhase1Seg parameter.  Phase Buffer 2 is determined
//! from the \e clkParms->phase2Seg parameter.  These two parameters, along
//! with \e clkParms->sjw are based in units of bit time quanta.  The actual
//! quantum time is determined by the \e clkParms->quantumPrescaler value,
//! which specifies the divisor for the CAN module clock.
//!
//! The total bit time, in quanta, will be the sum of the two Seg parameters,
//! as follows:
//!
//! bit_time_q = syncPropPhase1Seg + phase2Seg + 1
//!
//! Note that the Sync_Seg is always one quantum in duration, and will be added
//! to derive the correct duration of Prop_Seg and Phase1_Seg.
//!
//! The equation to determine the actual bit rate is as follows:
//!
//! CAN Clock /
//! ((\e syncPropPhase1Seg + \e phase2Seg + 1) * (\e quantumPrescaler))
//!
//! This means that with \e syncPropPhase1Seg = 4, \e phase2Seg = 1,
//! \e quantumPrescaler = 2 and an 8 MHz CAN clock, that the bit rate will be
//! (8 MHz) / ((5 + 2 + 1) * 2) or 500 Kbit/sec.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_setBitTiming(uint32_t base, CAN_BitClkParms *clkParms)
{
    uint32_t bitReg;
    uint32_t savedInit;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT(clkParms != 0);

    //
    // The phase 1 segment must be in the range from 2 to 16.
    //
    ASSERT((clkParms->syncPropPhase1Seg >= 2) &&
           (clkParms->syncPropPhase1Seg <= 16));

    //
    // The phase 2 segment must be in the range from 1 to 8.
    //
    ASSERT((clkParms->phase2Seg >= 1) && (clkParms->phase2Seg <= 8));

    //
    // The synchronous jump windows must be in the range from 1 to 4.
    //
    ASSERT((clkParms->sjw >= 1) && (clkParms->sjw <= 4));

    //
    // The CAN clock pre-divider must be in the range from 1 to 1024.
    //
    ASSERT((clkParms->quantumPrescaler <= 1024) &&
           (clkParms->quantumPrescaler >= 1));

    //
    // To set the bit timing register, the controller must be placed in init
    // mode (if not already), and also configuration change bit enabled.
    // State of the init bit should be saved so it can be restored at the end.
    //
    savedInit = HWREG(base + CAN_O_CTL);
    HWREG(base + CAN_O_CTL) = savedInit | CAN_CTL_INIT | CAN_CTL_CCE;

    //
    // Set the bit fields of the bit timing register according to the params.
    //
    bitReg = ((clkParms->phase2Seg - 1) << 12) & CAN_BTR_TSEG2_M;
    bitReg |= ((clkParms->syncPropPhase1Seg - 1) << 8) & CAN_BTR_TSEG1_M;
    bitReg |= ((clkParms->sjw - 1) << 6) & CAN_BTR_SJW_M;
    bitReg |= (clkParms->quantumPrescaler - 1) & CAN_BTR_BPR_M;
    bitReg |= ((clkParms->quantumPrescaler - 1) << 10)& CAN_BTR_BRPE_M;
    HWREG(base + CAN_O_BTR) = bitReg;

    //
    // Clear the config change bit, and restore the init bit.
    //
    savedInit &= ~CAN_CTL_CCE;

    //
    // If Init was not set before, then clear it.
    //
    if((savedInit & CAN_CTL_INIT) == CAN_CTL_INIT)
    {
        savedInit &= ~CAN_CTL_INIT;
    }
    HWREG(base + CAN_O_CTL) = savedInit;
}

//*****************************************************************************
//! Disables Auto-Bus-On.
//!
//! \param base is the base address of the CAN controller.
//!
//! Disables the Auto-Bus-On feature of the CAN controller.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_disableAutoBusOn(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Clear the ABO bit in the control register.
    //
    HWREG(base + CAN_O_CTL) &= ~CAN_CTL_ABO;
}

//*****************************************************************************
//! Enables Auto-Bus-On.
//!
//! \param base is the base address of the CAN controller.
//!
//! Enables the Auto-Bus-On feature of the CAN controller.  Be sure to also
//! configure the Auto-Bus-On time using the CAN_setAutoBusOnTime function.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_enableAutoBusOn(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Set the ABO bit in the control register.
    //
    HWREG(base + CAN_O_CTL) |= CAN_CTL_ABO;
}

//*****************************************************************************
//! Sets the time before a Bus-Off recovery sequence is started.
//!
//! \param base is the base address of the CAN controller.
//! \param time is number of clock cycles before a Bus-Off recovery sequence
//!        is started.
//!
//! Number of clock cycles before a Bus-Off recovery sequence is started
//! by clearing the Init bit. This function has to be enabled by setting bit
//! ABO in CAN Control Register.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_setAutoBusOnTime(uint32_t base, uint32_t time)
{
    HWREG(base + CAN_O_ABOTR) = time;
}

//*****************************************************************************
//! Registers an interrupt handler for the CAN controller.
//!
//! \param base is the base address of the CAN controller.
//! \param canIntNumber is the interrupt line to register (0 or 1).
//! \param handler is a pointer to the function to be called when the
//! enabled CAN interrupts occur.
//!
//! This function registers the interrupt handler in the interrupt vector
//! table, and enables CAN interrupts on the interrupt controller; specific CAN
//! interrupt sources must be enabled using CAN_enableInterrupt().  The
//! interrupt handler being registered must clear the source of the interrupt
//! using CAN_clearInterruptStatus().
//!
//! If the application is using a static interrupt vector table stored in
//! flash, then it is not necessary to register the interrupt handler this way.
//! Instead, Interrupt_enable() should be used to enable CAN interrupts on the
//! interrupt controller.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_registerInterrupt(uint32_t base, uint16_t canIntNumber,
                      void (*handler)(void))
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Get the actual interrupt number for this CAN controller.
    //
    intNumber = (uint32_t)CAN_getIntNumber(base, canIntNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_register(intNumber, handler);

    //
    // Enable the CAN interrupt.
    //
    Interrupt_enable(intNumber);
}

//*****************************************************************************
//! Unregisters an interrupt handler for the CAN controller.
//!
//! \param base is the base address of the controller.
//! \param canIntNumber is the interrupt line to un-register (0 or 1).
//!
//! This function unregisters the previously registered interrupt handler and
//! disables the interrupt on the interrupt controller.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_unregisterInterrupt(uint32_t base, uint16_t canIntNumber)
{
    uint32_t intNumber;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Get the actual interrupt number for this CAN controller.
    //
    intNumber = (uint32_t)CAN_getIntNumber(base, canIntNumber);

    //
    // Register the interrupt handler.
    //
    Interrupt_unregister(intNumber);

    //
    // Disable the CAN interrupt.
    //
    Interrupt_disable(intNumber);
}

//*****************************************************************************
//! Enables individual CAN controller interrupt sources.
//!
//! \param base is the base address of the CAN controller.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables specific interrupt sources of the CAN controller.  Only enabled
//! sources will cause a processor interrupt.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b CAN_INT_ERROR - a controller error condition has occurred
//! - \b CAN_INT_STATUS - a message transfer has completed, or a bus error has
//! been detected
//! - \b CAN_INT_IE0 - allow CAN controller to generate interrupts on interrupt
//! line 0
//! - \b CAN_INT_IE1 - allow CAN controller to generate interrupts on interrupt
//! line 1
//!
//! In order to generate status or error interrupts, \b CAN_INT_IE0 must be
//! enabled.
//! Further, for any particular transaction from a message object to generate
//! an interrupt, that message object must have interrupts enabled (see
//! CAN_setMessage()).  \b CAN_INT_ERROR will generate an interrupt if the
//! controller enters the ``bus off'' condition, or if the error counters reach
//! a limit.  \b CAN_INT_STATUS will generate an interrupt under quite a few
//! status conditions and may provide more interrupts than the application
//! needs to handle.  When an interrupt occurs, use CAN_getInterruptStatus() to
//! determine the cause.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((intFlags & ~(CAN_INT_ERROR | CAN_INT_STATUS | CAN_INT_IE0 |
                         CAN_INT_IE1)) == 0);

    //
    // Enable the specified interrupts.
    //
    HWREG(base + CAN_O_CTL) = HWREG(base + CAN_O_CTL) | intFlags;
}

//*****************************************************************************
//! Disables individual CAN controller interrupt sources.
//!
//! \param base is the base address of the CAN controller.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the specified CAN controller interrupt sources.  Only enabled
//! interrupt sources can cause a processor interrupt.
//!
//! The \e intFlags parameter has the same definition as in the
//! CAN_enableInterrupt() function.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((intFlags & ~(CAN_INT_ERROR | CAN_INT_STATUS | CAN_INT_IE0 |
                         CAN_INT_IE1)) == 0);

    //
    // Disable the specified interrupts.
    //
    HWREG(base + CAN_O_CTL) = HWREG(base + CAN_O_CTL) & ~(intFlags);
}

//*****************************************************************************
//! Returns the current CAN controller interrupt status.
//!
//! \param base is the base address of the CAN controller.
//! \param intStsReg indicates which interrupt status register to read
//!
//! Returns the value of one of two interrupt status registers.  The interrupt
//! status register read is determined by the \e intStsReg parameter, which
//! can have one of the following values:
//!
//! - \b CAN_INT_STS_CAUSE - indicates the cause of the interrupt
//! - \b CAN_INT_STS_OBJECT - indicates pending interrupts of all message
//! objects
//!
//! \b CAN_INT_STS_CAUSE returns the value of the controller interrupt register
//! and indicates the cause of the interrupt.  It will be a value of
//! \b CAN_INT_INT0ID_STATUS if the cause is a status interrupt.  In this case,
//! the status register should be read with the CAN_getStatus() function.
//! Calling this function to read the status will also clear the status
//! interrupt.  If the value of the interrupt register is in the range 1-32,
//! then this indicates the number of the highest priority message object that
//! has an interrupt pending.  The message object interrupt can be cleared by
//! using the CAN_clearInterruptStatus() function, or by reading the message
//! using CAN_getMessage() in the case of a received message.  The interrupt
//! handler can read the interrupt status again to make sure all pending
//! interrupts are cleared before returning from the interrupt.
//!
//! \b CAN_INT_STS_OBJECT returns a bit mask indicating which message objects
//! have pending interrupts.  This can be used to discover all of the pending
//! interrupts at once, as opposed to repeatedly reading the interrupt register
//! by using \b CAN_INT_STS_CAUSE.
//!
//! \return Returns the value of one of the interrupt status registers.
//
//*****************************************************************************
uint32_t
CAN_getInterruptStatus(uint32_t base, CAN_IntStatusReg intStsReg)
{
    uint32_t status;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // See which status the caller is looking for.
    //
    switch(intStsReg)
    {
        //
        // The caller wants the global interrupt status for the CAN controller
        // specified by base.
        //
        case CAN_INT_STS_CAUSE:
        {
            status = HWREG(base + CAN_O_INT);
            break;
        }

        //
        // The caller wants the current message status interrupt for all
        // messages.
        //
        case CAN_INT_STS_OBJECT:
        {
            //
            // Read message object interrupt status
            //
            status = HWREG(base + CAN_O_IPEN_21);
            break;
        }

        //
        // Request was for unknown status so just return 0.
        //
        default:
        {
            status = 0U;
            break;
        }
    }
    //
    // Return the interrupt status value
    //
    return(status);
}

//*****************************************************************************
//! Clears a CAN interrupt source.
//!
//! \param base is the base address of the CAN controller.
//! \param intClr is a value indicating which interrupt source to clear.
//!
//! This function can be used to clear a specific interrupt source.  The
//! \e intClr parameter should be one of the following values:
//!
//! - \b CAN_INT_INTID_STATUS - Clears a status interrupt.
//! - 1-32 - Clears the specified message object interrupt
//!
//! It is not necessary to use this function to clear an interrupt.  This
//! should only be used if the application wants to clear an interrupt source
//! without taking the normal interrupt action.
//!
//! Normally, the status interrupt is cleared by reading the controller status
//! using CAN_getStatus().  A specific message object interrupt is normally
//! cleared by reading the message object using CAN_getMessage().
//!
//! \note Since there is a write buffer in the Cortex-M3 processor, it may take
//! several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately re-entered (since NVIC still sees the interrupt source
//! asserted).
//!
//! \return None.
//
//*****************************************************************************
void
CAN_clearInterruptStatus(uint32_t base, uint32_t intClr)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((intClr == CAN_INT_INT0ID_STATUS) ||
           ((intClr>=1) && (intClr <=32)));

    if(intClr == (uint32_t)CAN_INT_INT0ID_STATUS)
    {
        //
        // Simply read and discard the status to clear the interrupt.
        //
        HWREG(base + CAN_O_ES);
    }
    else
    {
        //
        // Wait to be sure that this interface is not busy.
        //
        while((HWREG(base + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) ==
              CAN_IF1CMD_BUSY)
        {
        }

        //
        // Only change the interrupt pending state by setting only the
        // CAN_IF1CMD_CLRINTPND bit.
        //
        HWREGH(base + CAN_O_IF1CMD + 2U) = ((uint32_t)CAN_IF1CMD_CLRINTPND >>
                                            16U);

        //
        // Send the clear pending interrupt command to the CAN controller.
        //
        HWREGH(base + CAN_O_IF1CMD) = intClr & CAN_IF1CMD_MSG_NUM_M;

        //
        // Wait to be sure that this interface is not busy.
        //
        while((HWREG(base + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) ==
              CAN_IF1CMD_BUSY)
        {
        }
    }
}

//*****************************************************************************
//! Get the CAN controller automatic retransmission behavior.
//!
//! \param base is the base address of the CAN controller.
//!
//! Gets which interrupt line each message object should assert when an
//! interrupt occurs. Bit 0 corresponds to message object 32 and then bits
//! 1-31 correspond to message object 1 through 31 respectively.  Bits that
//! are asserted indicate the message object should generate an interrupt on
//! interrupt line 1, while bits that are not asserted indicate the message
//! object should generate an interrupt on line 0.
//!
//! \return Returns the value of the interrupt muxing register.
//
//*****************************************************************************
uint32_t
CAN_getInterruptMux(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Get the interrupt muxing for the CAN peripheral
    //
    return(HWREG(base + CAN_O_IP_MUX21));
}

//*****************************************************************************
//! Sets the CAN controller automatic retransmission behavior.
//!
//! \param base is the base address of the CAN controller.
//! \param mux bit packed representation of which message objects should
//!        generate an interrupt on a given interrupt line.
//!
//! Selects which interrupt line each message object should assert when an
//! interrupt occurs. Bit 0 corresponds to message object 32 and then bits
//! 1-31 correspond to message object 1 through 31 respectively.  Bits that
//! are asserted indicate the message object should generate an interrupt on
//! interrupt line 1, while bits that are not asserted indicate the message
//! object should generate an interrupt on line 0.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_setInterruptMux(uint32_t base, uint32_t mux)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Set the interrupt muxing for the CAN peripheral
    //
    HWREG(base + CAN_O_IP_MUX21) = mux;
}

//*****************************************************************************
//! Sets the CAN controller automatic retransmission behavior.
//!
//! \param base is the base address of the CAN controller.
//! \param autoRetry enables automatic retransmission.
//!
//! Enables or disables automatic retransmission of messages with detected
//! errors.  If \e autoRetry is \b true, then automatic retransmission is
//! enabled, otherwise it is disabled.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_setRetry(uint32_t base, bool autoRetry)
{
    uint32_t ctlReg;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    ctlReg = HWREG(base + CAN_O_CTL);

    //
    // Conditionally set the DAR bit to enable/disable auto-retry.
    //
    if(autoRetry)
    {
        //
        // Clearing the DAR bit tells the controller to not disable the
        // auto-retry of messages which were not transmitted or received
        // correctly.
        //
        ctlReg &= ~CAN_CTL_DAR;
    }
    else
    {
        //
        // Setting the DAR bit tells the controller to disable the auto-retry
        // of messages which were not transmitted or received correctly.
        //
        ctlReg |= CAN_CTL_DAR;
    }

    HWREG(base + CAN_O_CTL) = ctlReg;
}

//*****************************************************************************
//! Returns the current setting for automatic retransmission.
//!
//! \param base is the base address of the CAN controller.
//!
//! Reads the current setting for the automatic retransmission in the CAN
//! controller and returns it to the caller.
//!
//! \return Returns \b true if automatic retransmission is enabled, \b false
//! otherwise.
//
//*****************************************************************************
bool
CAN_getRetry(uint32_t base)
{
    bool status = true;
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Read the disable automatic retry setting from the CAN controller.
    //
    if((HWREG(base + CAN_O_CTL) & CAN_CTL_DAR) == CAN_CTL_DAR)
    {
        //
        // Automatic data retransmission is not enabled.
        //
        status = false;
    }

    //
    // Automatic data retransmission is enabled.
    //
    return status;
}

//*****************************************************************************
//! Reads one of the controller status registers.
//!
//! \param base is the base address of the CAN controller.
//! \param statusReg is the status register to read.
//!
//! Reads a status register of the CAN controller and returns it to the caller.
//! The different status registers are:
//!
//! - \b CAN_STS_CONTROL - the main controller status
//! - \b CAN_STS_TXREQUEST - bit mask of objects pending transmission
//! - \b CAN_STS_NEWDAT - bit mask of objects with new data
//! - \b CAN_STS_MSGVAL - bit mask of objects with valid configuration
//!
//! When reading the main controller status register, a pending status
//! interrupt will be cleared.  This should be used in the interrupt handler
//! for the CAN controller if the cause is a status interrupt.  The controller
//! status register fields are as follows:
//!
//! - \b CAN_STATUS_PDA - controller in local power down mode
//! - \b CAN_STATUS_WAKE_UP - controller initiated system wake up
//! - \b CAN_STATUS_PERR - parity error detected
//! - \b CAN_STATUS_BUS_OFF - controller is in bus-off condition
//! - \b CAN_STATUS_EWARN - an error counter has reached a limit of at least 96
//! - \b CAN_STATUS_EPASS - CAN controller is in the error passive state
//! - \b CAN_STATUS_RXOK - a message was received successfully (independent of
//! any message filtering).
//! - \b CAN_STATUS_TXOK - a message was successfully transmitted
//! - \b CAN_STATUS_LEC_NONE - no error
//! - \b CAN_STATUS_LEC_STUFF - stuffing error detected
//! - \b CAN_STATUS_LEC_FORM - a format error occurred in the fixed format part
//! of a message
//! - \b CAN_STATUS_LEC_ACK - a transmitted message was not acknowledged
//! - \b CAN_STATUS_LEC_BIT1 - dominant level detected when trying to send in
//! recessive mode
//! - \b CAN_STATUS_LEC_BIT0 - recessive level detected when trying to send in
//! dominant mode
//! - \b CAN_STATUS_LEC_CRC - CRC error in received message
//!
//! The remaining status registers are 32-bit bit maps to the message objects.
//! They can be used to quickly obtain information about the status of all the
//! message objects without needing to query each one.  They contain the
//! following information:
//!
//! - \b CAN_STS_TXREQUEST - if a message object's TxRequest bit is set, that
//! means that a transmission is pending on that object.  The application can
//! use this to determine which objects are still waiting to send a message.
//! - \b CAN_STS_NEWDAT - if a message object's NewDat bit is set, that means
//! that a new message has been received in that object, and has not yet been
//! picked up by the host application
//! - \b CAN_STS_MSGVAL - if a message object's MsgVal bit is set, that means
//! it has a valid configuration programmed.  The host application can use this
//! to determine which message objects are empty/unused.
//!
//! \return Returns the value of the status register.
//
//*****************************************************************************
uint32_t
CAN_getStatus(uint32_t base, CAN_StatusReg statusReg)
{
    uint32_t status;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    switch(statusReg)
    {
        //
        // Just return the global CAN status register since that is what was
        // requested.
        //
        case CAN_STS_CONTROL:
        {
            status = HWREG(base + CAN_O_ES);
            break;
        }

        //
        // Return objects with valid transmit requests
        //
        case CAN_STS_TXREQUEST:
        {
            status = HWREG(base + CAN_O_TXRQ_21);
            break;
        }

        //
        // Return messages objects with new data
        //
        case CAN_STS_NEWDAT:
        {
            status = HWREG(base + CAN_O_NDAT_21);
            break;
        }

        //
        // Return valid message objects
        //
        case CAN_STS_MSGVAL:
        {
            status = HWREG(base + CAN_O_MVAL_21);
            break;
        }

        //
        // Unknown CAN status requested so return 0.
        //
        default:
        {
            status = 0U;
            break;
        }
    }
    return(status);
}

//*****************************************************************************
//! Reads the CAN controller error counter register.
//!
//! \param base is the base address of the CAN controller.
//! \param rxCount is a pointer to storage for the receive error counter.
//! \param txCount is a pointer to storage for the transmit error counter.
//!
//! Reads the error counter register and returns the transmit and receive error
//! counts to the caller along with a flag indicating if the controller receive
//! counter has reached the error passive limit.  The values of the receive and
//! transmit error counters are returned through the pointers provided as
//! parameters.
//!
//! After this call, \e *rxCount will hold the current receive error count
//! and \e *txCount will hold the current transmit error count.
//!
//! \return Returns \b true if the receive error count has reached the error
//! passive limit, and \b false if the error count is below the error passive
//! limit.
//
//*****************************************************************************
bool
CAN_getErrorCount(uint32_t base, uint32_t *rxCount, uint32_t *txCount)
{
    uint32_t canError;
    bool status = false;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Read the current count of transmit/receive errors.
    //
    canError = HWREG(base + CAN_O_ERRC);

    //
    // Extract the error numbers from the register value.
    //
    *rxCount = (canError & CAN_ERRC_REC_M) >> CAN_ERRC_REC_S;
    *txCount = (canError & CAN_ERRC_TEC_M) >> CAN_ERRC_TEC_S;

    if((canError & CAN_ERRC_RP) != 0U)
    {
        status = true;
    }

    return status;
}

//*****************************************************************************
//! Configures a message object in the CAN controller.
//!
//! \param base is the base address of the CAN controller.
//! \param objID is the object number to configure (1-32).
//! \param msgObject is a pointer to a structure containing message object
//! settings.
//! \param msgType indicates the type of message for this object.
//!
//! This function is used to configure any one of the 32 message objects in the
//! CAN controller.  A message object can be configured as any type of CAN
//! message object as well as several options for automatic transmission and
//! reception.  This call also allows the message object to be configured to
//! generate interrupts on completion of message receipt or transmission.  The
//! message object can also be configured with a filter/mask so that actions
//! are only taken when a message that meets certain parameters is seen on the
//! CAN bus.
//!
//! The \e msgType parameter must be one of the following values:
//!
//! - \b MSG_OBJ_TYPE_TX - CAN transmit message object.
//! - \b MSG_OBJ_TYPE_TX_REMOTE - CAN transmit remote request message object.
//! - \b MSG_OBJ_TYPE_RX - CAN receive message object.
//! - \b MSG_OBJ_TYPE_RX_REMOTE - CAN receive remote request message object.
//! - \b MSG_OBJ_TYPE_RXTX_REMOTE - CAN remote frame receive remote, then
//! transmit message object.
//!
//! The message object pointed to by \e msgObject must be populated by the
//! caller, as follows:
//!
//! - \e msgID - contains the message ID, either 11 or 29 bits.
//! - \e msgIDMask - mask of bits from \e msgID that must match if
//! identifier filtering is enabled.
//! - \e flags
//!   - Set \b MSG_OBJ_TX_INT_ENABLE flag to enable interrupt on transmission.
//!   - Set \b MSG_OBJ_RX_INT_ENABLE flag to enable interrupt on receipt.
//!   - Set \b MSG_OBJ_USE_ID_FILTER flag to enable filtering based on the
//!   identifier mask specified by \e msgIDMask.
//! - \e msgLen - the number of bytes in the message data.  This should be
//! non-zero even for a remote frame; it should match the expected bytes of the
//! data responding data frame.
//! - \e msgData - points to a buffer containing up to 8 bytes of data for a
//! data frame.
//!
//! \b Example: To send a data frame or remote frame(in response to a remote
//! request), take the following steps:
//!
//! -# Set \e msgType to \b MSG_OBJ_TYPE_TX.
//! -# Set \e msgObject->msgID to the message ID.
//! -# Set \e msgObject->flags. Make sure to set \b MSG_OBJ_TX_INT_ENABLE to
//! allow an interrupt to be generated when the message is sent.
//! -# Set \e msgObject->msgLen to the number of bytes in the data frame.
//! -# Set \e msgObject->msgData to point to an array containing the bytes
//! to send in the message.
//! -# Call this function with \e objID set to one of the 32 object buffers.
//!
//! \b Example: To receive a specific data frame, take the following steps:
//!
//! -# Set \e msgType to \b MSG_OBJ_TYPE_RX.
//! -# Set \e msgObject->msgID to the full message ID, or a partial mask to
//! use partial ID matching.
//! -# Set \e msgObject->msgIDMask bits that should be used for masking
//! during comparison.
//! -# Set \e msgObject->flags as follows:
//!   - Set \b MSG_OBJ_TX_INT_ENABLE flag to be interrupted when the data frame
//!   is received.
//!   - Set \b MSG_OBJ_USE_ID_FILTER flag to enable identifier based filtering.
//! -# Set \e msgObject->msgLen to the number of bytes in the expected data
//! frame.
//! -# The buffer pointed to by \e msgObject->msgData  and
//! \e msgObject->msgLen are not used by this call as no data is present at
//! the time of the call.
//! -# Call this function with \e objID set to one of the 32 object buffers.
//!
//! If you specify a message object buffer that already contains a message
//! definition, it will be overwritten.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_setMessage(uint32_t base, uint32_t objID, CAN_MsgObject *msgObject,
               CAN_MsgObjType msgType)
{
    uint32_t cmdMaskReg;
    uint32_t maskReg;
    uint32_t arbReg;
    uint32_t msgCtrl;
    bool transferData;
    bool useExtendedID;
    bool switchError = false;

    transferData = 0;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((objID <= 32) && (objID != 0));

    //
    // Wait for busy bit to clear
    //
    while((HWREG(base + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) == CAN_IF1CMD_BUSY)
    {
    }

    //
    // See if we need to use an extended identifier or not.
    //
    if((msgObject->msgID > CAN_MAX_11BIT_MSG_ID) ||
       ((msgObject->flags & MSG_OBJ_EXTENDED_ID) ==
        (uint32_t)MSG_OBJ_EXTENDED_ID))
    {
        useExtendedID = 1;
    }
    else
    {
        useExtendedID = 0;
    }

    //
    // This is always a write to the Message object as this call is setting a
    // message object.  This call will also always set all size bits so it sets
    // both data bits.  The call will use the CONTROL register to set control
    // bits so this bit needs to be set as well.
    //
    cmdMaskReg = (CAN_IF1CMD_DIR | CAN_IF1CMD_DATA_A | CAN_IF1CMD_DATA_B |
                  CAN_IF1CMD_CONTROL);

    //
    // Initialize the values to a known state before filling them in based on
    // the type of message object that is being configured.
    //
    arbReg = 0U;
    msgCtrl = 0U;
    maskReg = 0U;

    switch(msgType)
    {
        //
        // Transmit message object.
        //
        case MSG_OBJ_TYPE_TX:
        {
            //
            // Set the TXRQST bit and the reset the rest of the register.
            //
            msgCtrl |= CAN_IF1MCTL_TXRQST;
            arbReg = CAN_IF1ARB_DIR;
            transferData = 1;
            break;
        }

        //
        // Transmit remote request message object
        //
        case MSG_OBJ_TYPE_TX_REMOTE:
        {
            //
            // Set the TXRQST bit and the reset the rest of the register.
            //
            msgCtrl |= CAN_IF1MCTL_TXRQST;
            arbReg = 0U;
            break;
        }

        //
        // Receive message object.
        //
        case MSG_OBJ_TYPE_RX:
        {
            //
            // This clears the DIR bit along with everything else.  The TXRQST
            // bit was cleared by defaulting usMsgCtrl to 0.
            //
            arbReg = 0U;
            break;
        }

        //
        // Receive remote request message object.
        //
        case MSG_OBJ_TYPE_RX_REMOTE:
        {
            //
            // The DIR bit is set to one for remote receivers.  The TXRQST bit
            // was cleared by defaulting usMsgCtrl to 0.
            //
            arbReg = CAN_IF1ARB_DIR;

            //
            // Set this object so that it only indicates that a remote frame
            // was received and allow for software to handle it by sending back
            // a data frame.
            //
            msgCtrl = CAN_IF1MCTL_UMASK;

            //
            // Use the full Identifier by default.
            //
            maskReg = CAN_IF1MSK_MSK_M;

            //
            // Make sure to send the mask to the message object.
            //
            cmdMaskReg |= CAN_IF1CMD_MASK;
            break;
        }

        //
        // Remote frame receive remote, with auto-transmit message object.
        //
        case MSG_OBJ_TYPE_RXTX_REMOTE:
        {
            //
            // Oddly the DIR bit is set to one for remote receivers.
            //
            arbReg = CAN_IF1ARB_DIR;

            //
            // Set this object to auto answer if a matching identifier is seen.
            //
            msgCtrl = (uint32_t)((uint32_t)CAN_IF1MCTL_RMTEN |
                                 (uint32_t)CAN_IF1MCTL_UMASK);

            //
            // The data to be returned needs to be filled in.
            //
            transferData = 1;
            break;
        }

        //
        // This case should never happen due to the ASSERT statement at the
        // beginning of this function.
        //
        default:
        {
           switchError = true;
           break;
        }
    }

    if(switchError == false)
    {
        //
        // Configure the Mask Registers.
        //
        if((msgObject->flags & MSG_OBJ_USE_ID_FILTER) == MSG_OBJ_USE_ID_FILTER)
        {
            if(useExtendedID)
            {
                //
                // Set the 29 bits of Identifier mask that were requested.
                //
                maskReg = msgObject->msgIDMask & CAN_IF1MSK_MSK_M;

            }
            else
            {

                //
                // Put the 11 bit Mask Identifier into the upper bits of the
                // field in the register.
                //
                maskReg = ((msgObject->msgIDMask << CAN_IF1ARB_STD_ID_S) &
                            CAN_IF1ARB_STD_ID_M);
            }
        }

        //
        // If the caller wants to filter on the extended ID bit then set it.
        //
        if((msgObject->flags & MSG_OBJ_USE_EXT_FILTER) ==
           MSG_OBJ_USE_EXT_FILTER)
        {
            maskReg |= CAN_IF1MSK_MXTD;
        }

        //
        // The caller wants to filter on the message direction field.
        //
        if((msgObject->flags & MSG_OBJ_USE_DIR_FILTER) ==
           MSG_OBJ_USE_DIR_FILTER)
        {
            maskReg |= CAN_IF1MSK_MDIR;
        }

        if((msgObject->flags & (MSG_OBJ_USE_ID_FILTER |
           MSG_OBJ_USE_DIR_FILTER | MSG_OBJ_USE_EXT_FILTER)) != 0U)
        {
            //
            // Set the UMASK bit to enable using the mask register.
            //
            msgCtrl |= CAN_IF1MCTL_UMASK;

            //
            // Set the MASK bit so that this gets transferred to the Message
            // Object.
            //
            cmdMaskReg |= CAN_IF1CMD_MASK;
        }

        //
        // Set the Arb bit so that this gets transferred to the Message object.
        //
        cmdMaskReg |= CAN_IF1CMD_ARB;

        //
        // Configure the Arbitration registers.
        //
        if(useExtendedID)
        {
            //
            // Set the 29 bit version of the Identifier for this message
            // object. Mark the message as valid and set the extended ID bit.
            //
            arbReg |= (msgObject->msgID & CAN_IF1ARB_ID_M) |
                       CAN_IF1ARB_MSGVAL | CAN_IF1ARB_XTD;
        }
        else
        {
            //
            // Set the 11 bit version of the Identifier for this message
            // object. The lower 18 bits are set to zero. Mark the message as
            // valid.
            //
            arbReg |= ((msgObject->msgID <<CAN_IF1ARB_STD_ID_S) &
                      CAN_IF1ARB_STD_ID_M) | CAN_IF1ARB_MSGVAL;
        }

        //
        // Set the data length since this is set for all transfers.  This is
        // also a single transfer and not a FIFO transfer so set EOB bit.
        //
        msgCtrl |= (msgObject->msgLen & CAN_IF1MCTL_DLC_M);

        //
        // Mark this as the last entry if this is not the last entry in a FIFO.
        //
        if((msgObject->flags & MSG_OBJ_FIFO) == 0U)
        {
            msgCtrl |= CAN_IF1MCTL_EOB;
        }

        //
        // Enable transmit interrupts if they should be enabled.
        //
        if((msgObject->flags & MSG_OBJ_TX_INT_ENABLE) == MSG_OBJ_TX_INT_ENABLE)
        {
            msgCtrl |= CAN_IF1MCTL_TXIE;
        }

        //
        // Enable receive interrupts if they should be enabled.
        //
        if((msgObject->flags & MSG_OBJ_RX_INT_ENABLE) == MSG_OBJ_RX_INT_ENABLE)
        {
            msgCtrl |= CAN_IF1MCTL_RXIE;
        }

        //
        // Write the data out to the CAN Data registers if needed.
        //
        if(transferData)
        {
            CAN_writeDataReg(msgObject->msgData,
                             (uint32_t *)(base + CAN_O_IF1DATA),
                             msgObject->msgLen);
        }

        //
        // Write out the registers to program the message object.
        //
        HWREGH(base + CAN_O_IF1CMD + 2U) = cmdMaskReg >> 16;
        HWREG(base + CAN_O_IF1MSK) = maskReg;
        HWREG(base + CAN_O_IF1ARB) = arbReg;
        HWREG(base + CAN_O_IF1MCTL) = msgCtrl;

        //
        // Transfer the message object to the message object specified by
        // objID.
        //
        HWREGH(base + CAN_O_IF1CMD) = objID & CAN_IF1CMD_MSG_NUM_M;
    }
    return;
}

//*****************************************************************************
//! Reads a CAN message from one of the message object buffers.
//!
//! \param base is the base address of the CAN controller.
//! \param objID is the object number to read (1-32).
//! \param msgObject points to a structure containing message object fields.
//! \param clrPendingInt indicates whether an associated interrupt should be
//! cleared.
//!
//! This function is used to read the contents of one of the 32 message objects
//! in the CAN controller, and return it to the caller.  The data returned is
//! stored in the fields of the caller-supplied structure pointed to by
//! \e msgObject.  The data consists of all of the parts of a CAN message,
//! plus some control and status information.
//!
//! Normally this is used to read a message object that has received and stored
//! a CAN message with a certain identifier.  However, this could also be used
//! to read the contents of a message object in order to load the fields of the
//! structure in case only part of the structure needs to be changed from a
//! previous setting.
//!
//! When using CAN_getMessage, all of the same fields of the structure are
//! populated in the same way as when the CAN_setMessage() function is used,
//! with the following exceptions:
//!
//! \e msgObject->flags:
//!
//! - \b MSG_OBJ_NEW_DATA indicates if this is new data since the last time it
//! was read
//! - \b MSG_OBJ_DATA_LOST indicates that at least one message was received on
//! this message object, and not read by the host before being overwritten.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_getMessage(uint32_t base, uint32_t objID, CAN_MsgObject *msgObject,
               bool clrPendingInt)
{
    uint32_t cmdMaskReg;
    uint32_t maskReg;
    uint32_t arbReg;
    uint32_t msgCtrl;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((objID <= 32) && (objID != 0));

    //
    // This is always a read to the Message object as this call is setting a
    // message object.
    //
    cmdMaskReg = (CAN_IF2CMD_DATA_A | CAN_IF2CMD_DATA_B | CAN_IF2CMD_CONTROL |
                  CAN_IF2CMD_MASK | CAN_IF2CMD_ARB);

    //
    // Clear a pending interrupt and new data in a message object.
    //
    if(clrPendingInt)
    {
        cmdMaskReg |= CAN_IF2CMD_CLRINTPND | CAN_IF2CMD_TXRQST;
    }

    //
    // Set up the request for data from the message object.
    //
    HWREGH(base + CAN_O_IF2CMD + 2U) = cmdMaskReg >> 16;

    //
    // Transfer the message object to the message object specified by objID.
    //
    HWREGH(base + CAN_O_IF2CMD) = objID & CAN_IF2CMD_MSG_NUM_M;

    //
    // Wait for busy bit to clear
    //
    while((HWREG(base + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY) == CAN_IF2CMD_BUSY)
    {
    }

    //
    // Read out the IF Registers.
    //
    maskReg = HWREG(base + CAN_O_IF2MSK);
    arbReg = HWREG(base + CAN_O_IF2ARB);
    msgCtrl = HWREG(base + CAN_O_IF2MCTL);
    msgObject->flags = MSG_OBJ_NO_FLAGS;

    //
    // Determine if this is a remote frame by checking the TXRQST and DIR bits.
    //
    if((!((msgCtrl & CAN_IF2MCTL_TXRQST) == CAN_IF2MCTL_TXRQST) &&
        ((arbReg & CAN_IF2ARB_DIR) == CAN_IF2ARB_DIR)) ||
       (((msgCtrl & CAN_IF2MCTL_TXRQST) == CAN_IF2MCTL_TXRQST) &&
        (!((arbReg & CAN_IF2ARB_DIR) == CAN_IF2ARB_DIR))))
    {
        msgObject->flags |= MSG_OBJ_REMOTE_FRAME;
    }

    //
    // Get the identifier out of the register, the format depends on size of
    // the mask.
    //
    if((arbReg & CAN_IF2ARB_XTD) == CAN_IF2ARB_XTD)
    {
        //
        // Set the 29 bit version of the Identifier for this message object.
        //
        msgObject->msgID = arbReg & CAN_IF2ARB_ID_M;

        msgObject->flags |= MSG_OBJ_EXTENDED_ID;
    }
    else
    {
        //
        // The Identifier is an 11 bit value.
        //
        msgObject->msgID = (arbReg & CAN_IF2ARB_STD_ID_M) >>
                           CAN_IF2ARB_STD_ID_S;
    }

    //
    // Indicate that we lost some data.
    //
    if((msgCtrl & CAN_IF2MCTL_MSGLST) == CAN_IF2MCTL_MSGLST)
    {
        msgObject->flags |= MSG_OBJ_DATA_LOST;
    }

    //
    // Set the flag to indicate if ID masking was used.
    //
    if((msgCtrl & CAN_IF2MCTL_UMASK) == CAN_IF2MCTL_UMASK)
    {
        if((arbReg & CAN_IF2ARB_XTD) == CAN_IF2ARB_XTD)
        {
            //
            // The Identifier Mask is assumed to also be a 29 bit value.
            //
            msgObject->msgIDMask = (maskReg & CAN_IF2MSK_MSK_M);

            //
            // If this is a fully specified Mask and a remote frame then don't
            // set the MSG_OBJ_USE_ID_FILTER because the ID was not really
            // filtered.
            //
            if((msgObject->msgIDMask != 0x1fffffffU) ||
               ((msgObject->flags & MSG_OBJ_REMOTE_FRAME) == 0U))
            {
                msgObject->flags |= MSG_OBJ_USE_ID_FILTER;
            }
        }
        else
        {
            //
            // The Identifier Mask is assumed to also be an 11 bit value.
            //
            msgObject->msgIDMask = ((maskReg & CAN_IF2MSK_MSK_M) >> 18);

            //
            // If this is a fully specified Mask and a remote frame then don't
            // set the MSG_OBJ_USE_ID_FILTER because the ID was not really
            // filtered.
            //
            if((msgObject->msgIDMask != 0x7ffU) ||
               ((msgObject->flags & MSG_OBJ_REMOTE_FRAME) == 0U))
            {
                msgObject->flags |= MSG_OBJ_USE_ID_FILTER;
            }
        }

        //
        // Indicate if the extended bit was used in filtering.
        //
        if((maskReg & CAN_IF2MSK_MXTD) == CAN_IF2MSK_MXTD)
        {
            msgObject->flags |= (uint32_t)MSG_OBJ_USE_EXT_FILTER;
        }

        //
        // Indicate if direction filtering was enabled.
        //
        if((maskReg & CAN_IF2MSK_MDIR) == CAN_IF2MSK_MDIR)
        {
            msgObject->flags |= (uint32_t)MSG_OBJ_USE_DIR_FILTER;
        }
    }

    //
    // Set the interrupt flags.
    //
    if((msgCtrl & CAN_IF2MCTL_TXIE) == CAN_IF2MCTL_TXIE)
    {
        msgObject->flags |= MSG_OBJ_TX_INT_ENABLE;
    }
    if((msgCtrl & CAN_IF2MCTL_RXIE) == CAN_IF2MCTL_RXIE)
    {
        msgObject->flags |= MSG_OBJ_RX_INT_ENABLE;
    }

    //
    // See if there is new data available.
    //
    if((msgCtrl & CAN_IF2MCTL_NEWDAT) == CAN_IF2MCTL_NEWDAT)
    {
        //
        // Get the amount of data needed to be read.
        //
        msgObject->msgLen = (msgCtrl & CAN_IF2MCTL_DLC_M);

        //
        // Don't read any data for a remote frame, there is nothing valid in
        // that buffer anyway.
        //
        if((msgObject->flags & MSG_OBJ_REMOTE_FRAME) == 0U)
        {
            //
            // Read out the data from the CAN registers.
            //
            CAN_readDataReg(msgObject->msgData,
                            (uint32_t *)(base + CAN_O_IF2DATA),
                            msgObject->msgLen);
        }

        //
        // Now clear out the new data flag.
        //
        HWREG(base + CAN_O_IF2CMD + 2U) = CAN_IF2CMD_TXRQST >> 16;

        //
        // Transfer the message object to the message object specified by
        // objID.
        //
        HWREGH(base + CAN_O_IF2CMD) = objID & CAN_IF2CMD_MSG_NUM_M;

        //
        // Wait for busy bit to clear
        //
        while((HWREG(base + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY) ==
              CAN_IF2CMD_BUSY)
        {
        }

        //
        // Indicate that there is new data in this message.
        //
        msgObject->flags |= MSG_OBJ_NEW_DATA;
    }
    else
    {
        //
        // Along with the MSG_OBJ_NEW_DATA not being set the amount of data
        // needs to be set to zero if none was available.
        //
        msgObject->msgLen = 0U;
    }
}

//*****************************************************************************
//! Transfers a CAN message between the IF registers and Message RAM.
//!
//! \param base is the base address of the CAN controller.
//! \param interface is the interface to use for the transfer. Valid value are
//!        1 or 2.
//! \param objID is the object number to transfer (1-32).
//! \param direction is the of the transfer. False is Message RAM to IF, True
//!        is IF to Message RAM.
//! \param dmaRequest asserts the DMA request line after a transfer if
//!        asserted.
//!
//! This function transfers the contents of the interface registers to message
//! RAM or vice versa depending on the value passed to direction.  This
//! function is designed to be used with DMA transfers.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_transferMessage(uint32_t base, uint_least8_t interface, uint32_t objID,
                    bool direction, bool dmaRequest)
{
    uint32_t cmdMaskReg;

    ASSERT(CAN_isBaseValid(base));
    ASSERT((interface == 1) || (interface == 2));

    //
    // This is always a read to the Message object as this call is setting a
    // message object.
    //
    cmdMaskReg = (CAN_IF1CMD_DATA_A | CAN_IF1CMD_DATA_B | CAN_IF1CMD_TXRQST |
                  CAN_IF1CMD_CONTROL | CAN_IF1CMD_MASK | CAN_IF1CMD_ARB) |
                 (direction ? CAN_IF1CMD_DIR : 0) |
                 (dmaRequest ? CAN_IF1CMD_DMAACTIVE : 0);

    //
    // Ensure this IF isn't busy
    //
    while((HWREG(base + CAN_O_IF1CMD + ((interface == 2) ? 0x20U : 0)) &
          CAN_IF1CMD_BUSY) == CAN_IF1CMD_BUSY)
    {
    }

    //
    // Set up the request for data from the message object. Transfer the
    // message object to the message object specified by objID.
    //
    HWREG(base + CAN_O_IF1CMD + ((interface == 2) ? 0x20U : 0)) =
        (cmdMaskReg | (objID & CAN_IF1CMD_MSG_NUM_M));

    //
    // Wait for busy bit to clear
    //
    while((HWREG(base + CAN_O_IF1CMD + ((interface == 2) ? 0x20U : 0)) &
          CAN_IF1CMD_BUSY) == CAN_IF1CMD_BUSY)
    {
    }
}

//*****************************************************************************
//! Clears a message object so that it is no longer used.
//!
//! \param base is the base address of the CAN controller.
//! \param objID is the message object number to disable (1-32).
//!
//! This function frees the specified message object from use.  Once a message
//! object has been ``cleared,'' it will no longer automatically send or
//! receive messages, or generate interrupts.
//!
//! \return None.
//
//*****************************************************************************
void
CAN_clearMessage(uint32_t base, uint32_t objID)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((objID >= 1) && (objID <= 32));

    //
    // Wait for busy bit to clear
    //
    while((HWREG(base + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) == CAN_IF1CMD_BUSY)
    {
    }

    //
    // Clear the message value bit in the arbitration register. This indicates
    // the message is not valid.
    //
    HWREGH(base + CAN_O_IF1CMD + 2U) = (CAN_IF1CMD_DIR | CAN_IF1CMD_ARB) >> 16;
    HWREG(base + CAN_O_IF1ARB) = 0U;

    //
    // Initiate programming the message object
    //
    HWREGH(base + CAN_O_IF1CMD) = objID & CAN_IF1CMD_MSG_NUM_M;
}

//*****************************************************************************
//! CAN Global interrupt Enable function.
//!
//! \param base is the base address of the CAN controller.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables specific CAN interrupt in the global interrupt enable register
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! CAN_GLOBAL_INT_CANINT0   -Global Interrupt Enable bit for CAN INT0
//! CAN_GLOBAL_INT_CANINT1   -Global Interrupt Enable bit for CAN INT1
//!
//! \return None.
//
//*****************************************************************************
void
CAN_enableGlobalInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((intFlags & ~(CAN_GLOBAL_INT_CANINT0 |
                         CAN_GLOBAL_INT_CANINT1)) == 0);

    //
    //enable the requested interrupts
    //
    HWREG(base + CAN_O_GLB_INT_EN) = HWREG(base + CAN_O_GLB_INT_EN) | intFlags;
}

//*****************************************************************************
//! CAN Global interrupt Disable function.
//!
//! \param base is the base address of the CAN controller.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Disables the specific CAN interrupt in the global interrupt enable register
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! CAN_GLOBAL_INT_CANINT0   -Global Interrupt bit for CAN INT0
//! CAN_GLOBAL_INT_CANINT1   -Global Interrupt bit for CAN INT1
//!
//! \return None.
//
//*****************************************************************************
void
CAN_disableGlobalInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((intFlags & ~(CAN_GLOBAL_INT_CANINT0 |
                         CAN_GLOBAL_INT_CANINT1)) == 0);

    //
    //enable the requested interrupts
    //
    HWREG(base + CAN_O_GLB_INT_EN) &= ~intFlags;
}

//*****************************************************************************
//! CAN Global interrupt Clear function.
//!
//! \param base is the base address of the CAN controller.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Clear the specific CAN interrupt bit i nthe global interrupt flag register.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! CAN_GLOBAL_INT_CANINT0   -Global Interrupt bit for CAN INT0
//! CAN_GLOBAL_INT_CANINT1   -Global Interrupt bit for CAN INT1
//!
//! \return None.
//
//*****************************************************************************
void
CAN_clearGlobalInterruptStatus(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((intFlags & ~(CAN_GLOBAL_INT_CANINT0 |
                         CAN_GLOBAL_INT_CANINT1)) == 0);

    //
    //enable the requested interrupts
    //
    HWREG(base + CAN_O_GLB_INT_CLR) = intFlags;
}

//*****************************************************************************
//! CAN Global interrupt Clear function.
//!
//! \param base is the base address of the CAN controller.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Clear the specific CAN interrupt bit in the global interrupt flag register.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! CAN_GLOBAL_INT_CANINT0   -Global Interrupt bit for CAN INT0
//! CAN_GLOBAL_INT_CANINT1   -Global Interrupt bit for CAN INT1
//!
//! \return True if any of the requested interrupt bit(s) is (are) set.
//
//*****************************************************************************
bool
CAN_getGlobalInterruptStatus(uint32_t base, uint32_t intFlags)
{
    bool status = false;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((intFlags & ~(CAN_GLOBAL_INT_CANINT0 |
                         CAN_GLOBAL_INT_CANINT1)) == 0);

    //
    //enable the requested interrupts
    //
    if((HWREG(base + CAN_O_GLB_INT_FLG) & intFlags) != 0U)
    {
        status = true;
    }

    return status;
}

//*****************************************************************************
// Close the Doxygen group.
//! @}
//*****************************************************************************
