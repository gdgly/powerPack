//###########################################################################
//
// FILE:   i2c.c
//
// TITLE:  Stellaris style wrapper driver for C28x I2C peripheral.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright: $
//###########################################################################

#include <stdbool.h>
#include <stdint.h>
#include "i2c.h"

//*****************************************************************************
//
// I2C_initMaster
//
//*****************************************************************************
void
I2C_initMaster(uint32_t base, uint32_t sysclkHz, uint32_t bitRate,
               I2C_DutyCycle dutyCycle)
{
    uint32_t modPrescale;
    uint32_t divider;
    uint32_t dValue;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));
    ASSERT((10000000U / bitRate) >  10U);

    //
    // Set the prescaler for the module clock.
    //
    modPrescale = (sysclkHz / 10000000U) - 1U;
    HWREGH(base + I2C_O_PSC) = I2C_PSC_IPSC_M & modPrescale;

    switch(modPrescale)
    {
        case 0U:
            dValue = 7U;
            break;

        case 1U:
            dValue = 6U;
            break;

        default:
            dValue = 5U;
            break;
    }

    //
    // Set the divider for the time low
    //
    divider = (10000000U / bitRate) - (2U * dValue);

    if(dutyCycle == I2C_DUTYCYCLE_50)
    {
        HWREGH(base + I2C_O_CLKH) = divider / 2U;
    }
    else
    {
        HWREGH(base + I2C_O_CLKH) = divider / 3U;
    }


    HWREGH(base + I2C_O_CLKL) = divider - HWREGH(base + I2C_O_CLKH);
}

//*****************************************************************************
//
// I2C_registerBasicInterrupt
//
//*****************************************************************************
void
I2C_registerBasicInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNum;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Determine the interrupt number based on the I2C port.
    //
    intNum = I2C_getBasicIntNumber(base);

    ASSERT(intNum != 0);

    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    Interrupt_register(intNum, handler);

    //
    // Enable the I2C interrupt.
    //
    Interrupt_enable(intNum);
}

//*****************************************************************************
//
// I2C_unregisterBasicInterrupt
//
//*****************************************************************************
void
I2C_unregisterBasicInterrupt(uint32_t base)
{
    uint32_t intNum;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Determine the interrupt number based on the I2C port.
    //
    intNum = I2C_getBasicIntNumber(base);

    ASSERT(intNum != 0);

    //
    // Disable the interrupt.
    //
    Interrupt_disable(intNum);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregister(intNum);
}

//*****************************************************************************
//
// I2C_registerFIFOInterrupt
//
//*****************************************************************************
void
I2C_registerFIFOInterrupt(uint32_t base, void (*handler)(void))
{
    uint32_t intNum;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Determine the interrupt number based on the I2C port.
    //
    intNum = I2C_getFIFOIntNumber(base);

    ASSERT(intNum != 0);

    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    Interrupt_register(intNum, handler);

    //
    // Enable the I2C interrupt.
    //
    Interrupt_enable(intNum);
}

//*****************************************************************************
//
// I2C_unregisterFIFOInterrupt
//
//*****************************************************************************
void
I2C_unregisterFIFOInterrupt(uint32_t base)
{
    uint32_t intNum;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Determine the interrupt number based on the I2C port.
    //
    intNum = I2C_getFIFOIntNumber(base);

    ASSERT(intNum != 0);

    //
    // Disable the interrupt.
    //
    Interrupt_disable(intNum);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregister(intNum);
}

//*****************************************************************************
//
// I2C_enableInterrupt
//
//*****************************************************************************
void
I2C_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Enable the desired basic interrupts
    //
    HWREGH(base + I2C_O_IER) |= (intFlags & 0x00FFU);

    //
    // Enabling addressed-as-slave interrupt separately because its bit is
    // different between the IER and STR registers.
    //
    if((intFlags & I2C_INT_ADDR_SLAVE) != 0U)
    {
        HWREGH(base + I2C_O_IER) |= I2C_IER_AAS;
    }

    //
    // Enable desired FIFO interrupts.
    //
    if((intFlags & I2C_INT_TXFF) != 0U)
    {
        HWREGH(base + I2C_O_FFTX) |= I2C_FFTX_TXFFIENA;
    }

    if((intFlags & I2C_INT_RXFF) != 0U)
    {
        HWREGH(base + I2C_O_FFRX) |= I2C_FFRX_RXFFIENA;
    }
}

//*****************************************************************************
//
// I2C_disableInterrupt
//
//*****************************************************************************
void
I2C_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Disable the desired basic interrupts.
    //
    HWREGH(base + I2C_O_IER) &= ~(intFlags & 0x00FFU);

    //
    // Disabling addressed-as-slave interrupt separately because its bit is
    // different between the IER and STR registers.
    //
    if((intFlags & I2C_INT_ADDR_SLAVE) != 0U)
    {
        HWREGH(base + I2C_O_IER) &= ~I2C_IER_AAS;
    }

    //
    // Disable the desired FIFO interrupts.
    //
    if((intFlags & I2C_INT_TXFF) != 0U)
    {
        HWREGH(base + I2C_O_FFTX) &= ~(I2C_FFTX_TXFFIENA);
    }

    if((intFlags & I2C_INT_RXFF) != 0U)
    {
        HWREGH(base + I2C_O_FFRX) &= ~(I2C_FFRX_RXFFIENA);
    }
}

//*****************************************************************************
//
// I2C_getInterruptStatus
//
//*****************************************************************************
uint32_t
I2C_getInterruptStatus(uint32_t base)
{
    uint32_t temp;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Return only the status bits associated with interrupts.
    //
    temp = (uint32_t)(HWREGH(base + I2C_O_STR) & I2C_STR_INTMASK);

    //
    // Read FIFO interrupt flags.
    //
    if((HWREGH(base + I2C_O_FFTX) & I2C_FFTX_TXFFINT) != 0U)
    {
        temp |= I2C_INT_TXFF;
    }

    if((HWREGH(base + I2C_O_FFRX) & I2C_FFRX_RXFFINT) != 0U)
    {
        temp |= I2C_INT_RXFF;
    }

    return(temp);
}

//*****************************************************************************
//
// I2C_clearInterruptStatus
//
//*****************************************************************************
void
I2C_clearInterruptStatus(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Clear the interrupt flags that are located in STR.
    //
    HWREGH(base + I2C_O_STR) |= ((uint16_t)intFlags & I2C_STR_INTMASK);

    //
    // Clear the FIFO interrupt flags if needed.
    //
    if((intFlags & I2C_INT_TXFF) != 0U)
    {
        HWREGH(base + I2C_O_FFTX) |= I2C_FFTX_TXFFINTCLR;
    }

    if((intFlags & I2C_INT_RXFF) != 0U)
    {
        HWREGH(base + I2C_O_FFRX) |= I2C_FFRX_RXFFINTCLR;
    }
}
