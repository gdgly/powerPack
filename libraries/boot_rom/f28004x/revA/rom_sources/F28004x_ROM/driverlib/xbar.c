//###########################################################################
//
// FILE:   xbar.c
//
// TITLE:  C28x X-Bar driver.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  $
//###########################################################################

#include "xbar.h"

//*****************************************************************************
//
// XBar_setOutputMuxConfig
//
//*****************************************************************************
void
XBar_setOutputMuxConfig(XBar_OutputNum output, XBar_OutputMuxConfig muxConfig)
{
    uint32_t shift;
    uint16_t offset;

    //
    // If the configuration is for MUX16-31, we'll need an odd value to index
    // into the config registers.
    //
    if(((uint32_t)muxConfig & 0x2000U) != 0U)
    {
        offset = ((uint16_t)output << 1U) + 2U;
    }
    else
    {
        offset = (uint16_t)output << 1U;
    }

    //
    // Extract the shift from the input value.
    //
    shift = ((uint32_t)muxConfig >> 8U) & 0x7FU;

    //
    // Write the requested muxing value for this XBAR output.
    //
    EALLOW;

    HWREG(XBAR_OUTPUT_CFG_REG_BASE + offset) =
        (HWREG(XBAR_OUTPUT_CFG_REG_BASE + offset) &
         ~((uint32_t)0x3U << shift)) |
        (((uint32_t)muxConfig & 0x3U) << shift);

    EDIS;
}

//*****************************************************************************
//
// XBar_setEPWMMuxConfig
//
//*****************************************************************************
void
XBar_setEPWMMuxConfig(XBar_TripNum trip, XBar_EPWMMuxConfig muxConfig)
{
    uint32_t shift;
    uint16_t offset;

    //
    // If the configuration is for MUX16-31, we'll need an odd value to index
    // into the config registers.
    //
    if(((uint32_t)muxConfig & 0x2000U) != 0U)
    {
        offset = ((uint16_t)trip << 1U) + 2U;
    }
    else
    {
        offset = (uint16_t)trip << 1U;
    }

    //
    // Extract the shift from the input value.
    //
    shift = ((uint32_t)muxConfig >> 8U) & 0x7FU;

    //
    // Write the requested muxing value for this XBAR trip.
    //
    EALLOW;

    HWREG(XBAR_EPWM_CFG_REG_BASE + offset) =
        (HWREG(XBAR_EPWM_CFG_REG_BASE + offset) & ~((uint32_t)0x3U << shift)) |
        (((uint32_t)muxConfig & 0x3U) << shift);

    EDIS;
}

//*****************************************************************************
//
// XBar_getInputFlagStatus
//
//*****************************************************************************
bool
XBar_getInputFlagStatus(XBar_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    //
    // Determine flag register offset.
    //
    switch((uint16_t)inputFlag & XBAR_INPUT_FLG_REG_M)
    {
        case XBAR_INPUT_FLG_REG_1:
            offset = XBAR_O_FLG1;
            break;

        case XBAR_INPUT_FLG_REG_2:
            offset = XBAR_O_FLG2;
            break;

        case XBAR_INPUT_FLG_REG_3:
            offset = XBAR_O_FLG3;
            break;

        case XBAR_INPUT_FLG_REG_4:
            offset = XBAR_O_FLG4;
            break;

        default:
            // This should never happen if a valid inputFlag value is used.
            break;
    }

    //
    // Get the status of the X-Bar input latch.
    //
    inputMask = (uint32_t)1U << ((uint32_t)inputFlag & XBAR_INPUT_FLG_INPUT_M);
    if((HWREG(XBAR_BASE + offset) & inputMask) != 0U)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

//*****************************************************************************
//
// XBar_clearInputFlag
//
//*****************************************************************************
void
XBar_clearInputFlag(XBar_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    //
    // Determine flag clear register offset.
    //
    switch((uint16_t)inputFlag & XBAR_INPUT_FLG_REG_M)
    {
        case XBAR_INPUT_FLG_REG_1:
            offset = XBAR_O_CLR1;
            break;

        case XBAR_INPUT_FLG_REG_2:
            offset = XBAR_O_CLR2;
            break;

        case XBAR_INPUT_FLG_REG_3:
            offset = XBAR_O_CLR3;
            break;

        case XBAR_INPUT_FLG_REG_4:
            offset = XBAR_O_CLR4;
            break;

        default:
            // This should never happen if a valid inputFlag value is used.
            break;
    }

    //
    // Set the bit that clears the X-Bar input latch.
    //
    inputMask = (uint32_t)1U << ((uint32_t)inputFlag & XBAR_INPUT_FLG_INPUT_M);
    HWREG(XBAR_BASE + offset) |= inputMask;
}
