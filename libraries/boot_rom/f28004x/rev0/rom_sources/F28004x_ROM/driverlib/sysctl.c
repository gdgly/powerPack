//###########################################################################
//
// FILE:   sysctl.c
//
// TITLE:  C28x system control driver.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright: $
//###########################################################################

#include "sysctl.h"

//*****************************************************************************
//
// SysCtl_delay()
//
//*****************************************************************************
__asm(" .def _SysCtl_delay\n"
//      " .sect \"ramfuncs\"\n"
      " .global  _SysCtl_delay\n"
      "_SysCtl_delay:\n"
      " SUB    ACC,#1\n"
      " BF     _SysCtl_delay,GEQ\n"
      " LRETR\n");

//*****************************************************************************
//
// SysCtl_getClock()
//
//*****************************************************************************
uint32_t
SysCtl_getClock(uint32_t clockInHz)
{
    //
    // Don't proceed if an MCD failure is detected.
    //
    if(SysCtl_isMCDClockFailureDetected())
    {
        //
        // OSCCLKSRC2 failure detected. Returning the INTOSC1 rate. You need
        // to handle the MCD and clear the failure.
        //
        return(SYSCTL_DEFAULT_OSC_FREQ);
    }

    if(((HWREG(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &
         SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M) ==
        ((uint32_t)SYSCTL_OSCSRC_OSC2 >> SYSCTL_OSCSRC_S)) ||
       ((HWREG(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &
         SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M) ==
        ((uint32_t)SYSCTL_OSCSRC_OSC1 >> SYSCTL_OSCSRC_S)))
    {
        // 10MHz Internal Clock
        clockInHz = SYSCTL_DEFAULT_OSC_FREQ;
    }

    //
    // If the PLL is enabled calculate its effect on the clock
    //
    if((HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL1) &
        (SYSCTL_SYSPLLCTL1_PLLEN | SYSCTL_SYSPLLCTL1_PLLCLKEN)) == 3U)
    {
        //
        // Calculate integer multiplier and fixed divide by 2
        //
        clockInHz = clockInHz * ((HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLMULT) &
                                  SYSCTL_SYSPLLMULT_IMULT_M) >>
                                 SYSCTL_SYSPLLMULT_IMULT_S);

        //
        // Calculate fractional multiplier
        //
        switch((HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLMULT) &
                SYSCTL_SYSPLLMULT_FMULT_M) >> SYSCTL_SYSPLLMULT_FMULT_S)
        {
            case 0U:
                break;

            case 1U:
                clockInHz += clockInHz / 4U;
                break;

            case 2U:
                clockInHz += clockInHz / 2U;
                break;

            case 3U:
                clockInHz += (clockInHz * 3U) / 4U;
                break;

            default:
                // Not a valid value for the FMULT register.
                break;
       }
    }

    if((HWREG(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) &
       SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M) != 0U)
    {
        clockInHz /= (2U * (HWREG(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) &
                            SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M));
    }

    return(clockInHz);
}

//*****************************************************************************
//
// SysCtl_setClock()
//
//*****************************************************************************
bool
SysCtl_setClock(uint32_t config)
{
    uint16_t divSel;
    uint16_t pllMult;

    //
    // Check the arguments.
    //
    ASSERT((config & SYSCTL_SYSDIV_M) != 0U); // SYSDIV value must be nonzero
    ASSERT((config & SYSCTL_IMULT_M) != 0U);  // IMULT value must be nonzero
    ASSERT((config & SYSCTL_OSCSRC_M) != SYSCTL_OSCSRC_M); // 3 is not valid

    //
    // Don't proceed to the PLL initialization if an MCD failure is detected.
    //
    if(SysCtl_isMCDClockFailureDetected())
    {
        //
        // OSCCLKSRC2 failure detected. Returning false. You'll need to clear
        // the MCD error.
        //
        return(false);
    }

    //
    // Ensure the PLL is out of our clock tree
    //
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL1) &= ~(SYSCTL_SYSPLLCTL1_PLLCLKEN |
                                                   SYSCTL_SYSPLLCTL1_PLLEN);
    EDIS;

    //
    // Configure Oscillator
    //
    SysCtl_selectOscSource(config & SYSCTL_OSCSRC_M);

    //
    // Configure PLL if enabled
    //
    if((config & SYSCTL_PLL_ENABLE) == SYSCTL_PLL_ENABLE)
    {
        EALLOW;
        // Program PLL multipliers
        pllMult  = (uint16_t)((config & SYSCTL_IMULT_M) <<
                              SYSCTL_SYSPLLMULT_IMULT_S);
        pllMult |= (uint16_t)(((config & SYSCTL_FMULT_M) >> SYSCTL_FMULT_S) <<
                              SYSCTL_SYSPLLMULT_FMULT_S);

        HWREGH(CLKCFG_BASE + SYSCTL_O_SYSPLLMULT) |= pllMult;

        // Enable SYSPLL
        HWREG(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL1) |= SYSCTL_SYSPLLCTL1_PLLEN;
        EDIS;

        // Wait for the SYSPLL lock
        while((HWREGH(CLKCFG_BASE + SYSCTL_O_SYSPLLSTS) &
               SYSCTL_SYSPLLSTS_LOCKS) != 1U)
        {
            // Uncomment to service the watchdog
            // SysCtl_serviceWatchdog();
        }
    }

    //
    // Configure Dividers. Set divider to produce slower output frequency to
    // limit current increase.
    //
    divSel = (uint16_t)(config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S;
    EALLOW;
    if(divSel != (126U / 2U))
    {
        HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) =
            (HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) &
             ~SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M) | (divSel + 1U);
    }
    else
    {
        HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) =
            (HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) &
             ~SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M) | divSel;
    }

    //
    // Enable PLLSYSCLK is fed from system PLL clock
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL1) |= SYSCTL_SYSPLLCTL1_PLLCLKEN;
    EDIS;

    //
    // Small delay
    //
    SysCtl_delay(35U);

    //
    // Set the divider to user value
    //
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) =
        (HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) &
         ~SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M) | divSel;
    EDIS;

    return(true);
}

//*****************************************************************************
//
// SysCtl_selectXTAL()
//
//*****************************************************************************
void
SysCtl_selectXTAL(void)
{
    // Turn on XTAL and select crystal mode
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_OSCOFF;
    HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_SE;
    EDIS;

    // Wait for the X1 clock to saturate
    HWREG(CLKCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
    while(HWREGH(CLKCFG_BASE + SYSCTL_O_X1CNT) != 0x3FFU)
    {
    }

    // Clk Src = XTALOSC
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &=
        ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M;
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |=
        SYSCTL_OSCSRC_XTAL >> SYSCTL_OSCSRC_S;
    EDIS;

    // If a missing clock failure was detected, try waiting for the X1 counter
    // to saturate again. Consider modifying this code to add a 10ms timeout.
    while(SysCtl_isMCDClockFailureDetected())
    {
        // Clear the MCD failure
        SysCtl_resetMCD();

        // Wait for the X1 clock to saturate
        HWREG(CLKCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
        while(HWREGH(CLKCFG_BASE + SYSCTL_O_X1CNT) != 0x3FFU)
        {
        }

        // Clk Src = XTALOSC
        EALLOW;
        HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &=
            ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M;
        HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |=
            SYSCTL_OSCSRC_XTAL >> SYSCTL_OSCSRC_S;
        EDIS;
    }
}

//*****************************************************************************
//
// SysCtl_selectXTALSingleEnded()
//
//*****************************************************************************
void
SysCtl_selectXTALSingleEnded(void)
{
    // Turn on XTAL and select single-ended mode.
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_OSCOFF;
    HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_SE;
    EDIS;

    // Wait for the X1 clock to saturate
    HWREG(CLKCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
    while(HWREGH(CLKCFG_BASE + SYSCTL_O_X1CNT) != 0x3FFU)
    {
    }

    // Clk Src = XTALOSC
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &=
        ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M;
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |=
        SYSCTL_OSCSRC_XTAL >> SYSCTL_OSCSRC_S;
    EDIS;

    // Something is wrong with the oscillator module. Replace the ESTOP0 with
    // an appropriate error-handling routine.
    while(SysCtl_isMCDClockFailureDetected())
    {
        ESTOP0;
    }
}

//*****************************************************************************
//
// SysCtl_selectOscSource()
//
//*****************************************************************************
void
SysCtl_selectOscSource(uint32_t oscSource)
{
    ASSERT((oscSource == SYSCTL_OSCSRC_OSC1) |
           (oscSource == SYSCTL_OSCSRC_OSC2) |
           (oscSource == SYSCTL_OSCSRC_XTAL) |
           (oscSource == SYSCTL_OSCSRC_XTAL_SE));

    //
    // Select the specified source.
    //
    switch(oscSource)
    {
    case SYSCTL_OSCSRC_OSC2:
        EALLOW;
        // Turn on INTOSC2
        HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &=
            ~SYSCTL_CLKSRCCTL1_INTOSC2OFF;
        // Clk Src = INTOSC2
        HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &=
            ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M;
        EDIS;
        break;

    case SYSCTL_OSCSRC_XTAL:
        // Select XTAL in crystal mode and wait for it to power up
        SysCtl_selectXTAL();
        break;

    case SYSCTL_OSCSRC_XTAL_SE:
        // Select XTAL in single-ended mode and wait for it to power up
        SysCtl_selectXTALSingleEnded();
        break;

    case SYSCTL_OSCSRC_OSC1:
        // Clk Src = INTOSC1
        EALLOW;
        HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &=
            ~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M;
        HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |=
            SYSCTL_OSCSRC_OSC1 >> SYSCTL_OSCSRC_S;
        EDIS;
        break;

    default:
        // Do nothing. Not a valid oscSource value.
        break;
    }
}

//*****************************************************************************
//
// SysCtl_getLowSpeedClock()
//
//*****************************************************************************
uint32_t
SysCtl_getLowSpeedClock(uint32_t clockInHz)
{
    //
    // Get the main system clock
    //
    clockInHz = SysCtl_getClock(clockInHz);

    //
    // Apply the divider to the main clock
    //
    if((HWREG(CLKCFG_BASE + SYSCTL_O_LOSPCP) &
        SYSCTL_LOSPCP_LSPCLKDIV_M) != 0U)
    {
        clockInHz /= (2U * (HWREG(CLKCFG_BASE + SYSCTL_O_LOSPCP) &
                            SYSCTL_LOSPCP_LSPCLKDIV_M));
    }

    return(clockInHz);
}
