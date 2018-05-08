// TI File $Revision: /main/1 $
// Checkin $Date: May 30, 2008   14:11:37 $
//###########################################################################
//
// FILE:   DSP2834x_SysCtrl.h
//
// TITLE:  DSP2834x Device System Control Register Definitions.
//
//###########################################################################
// $TI Release: 2834x Boot ROM V1b $
// $Release Date: June 3, 2008 $
//###########################################################################

#ifndef DSP2834x_SYS_CTRL_H
#define DSP2834x_SYS_CTRL_H


#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// System Control Individual Register Bit Definitions:
//


// PLL Status Register
struct PLLSTS_BITS   {    // bits  description
   Uint16 PLLLOCKS:1;     // 0     PLL lock status
   Uint16 rsvd1:1;        // 1     reserved
   Uint16 PLLOFF:1;       // 2     PLL off bit
   Uint16 rsvd2:1;        // 3     Missing clock status bit
   Uint16 rsvd3:1;        // 4     Missing clock clear bit
   Uint16 rsvd4:1;        // 5     Oscillator clock off
   Uint16 rsvd5:1;        // 6     Missing clock detect
   Uint16 DIVSEL:2;       // 8:7   Divide Select
   Uint16 rsvd6:7;        // 15:9  reserved
};

union PLLSTS_REG {
   Uint16              all;
   struct PLLSTS_BITS  bit;
};

// High speed peripheral clock register bit definitions:
struct HISPCP_BITS  {   // bits  description
   Uint16 HSPCLK:5;     // 4:0   Rate relative to SYSCLKOUT
   Uint16 rsvd1:11;     // 15:5  reserved
};

union HISPCP_REG {
   Uint16              all;
   struct HISPCP_BITS  bit;
};

// Low speed peripheral clock register bit definitions:
struct LOSPCP_BITS  {   // bits  description
   Uint16 LSPCLK:3;     // 2:0   Rate relative to SYSCLKOUT
   Uint16 rsvd1:13;     // 15:3  reserved
};

union LOSPCP_REG {
   Uint16              all;
   struct LOSPCP_BITS  bit;
};

// Peripheral clock control register 0 bit definitions:
struct PCLKCR0_BITS  {   // bits  description
   Uint16 rsvd1:2;       // 1:0   reserved
   Uint16 TBCLKSYNC:1;   // 2     EWPM Module TBCLK enable/sync
   Uint16 rsvd2:1;       // 3     reserved
   Uint16 I2CAENCLK:1;   // 4     Enable SYSCLKOUT to I2C-A
   Uint16 SCICENCLK:1;   // 5     Enalbe low speed clk to SCI-C
   Uint16 rsvd3:1;       // 6     reserved
   Uint16 SPIDENCLK:1;   // 7     Enable low speed clk to SPI-D
   Uint16 SPIAENCLK:1;   // 8     Enable low speed clk to SPI-A
   Uint16 rsvd4:1;       // 9     reserved
   Uint16 SCIAENCLK:1;   // 10    Enable low speed clk to SCI-A
   Uint16 SCIBENCLK:1;   // 11    Enable low speed clk to SCI-B
   Uint16 MCBSPAENCLK:1; // 12    Enable low speed clk to McBSP-A
   Uint16 MCBSPBENCLK:1; // 13    Enable low speed clk to McBSP-B
   Uint16 ECANAENCLK:1;  // 14    Enable system clk to eCAN-A
   Uint16 ECANBENCLK:1;  // 15    Enable system clk to eCAN-B
};

union PCLKCR0_REG {
   Uint16              all;
   struct PCLKCR0_BITS bit;
};

// Peripheral clock control register 1 bit definitions:
struct PCLKCR1_BITS  {    // bits  description
   Uint16 EPWM1ENCLK:1;   // 0     Enable SYSCLKOUT to EPWM1
   Uint16 EPWM2ENCLK:1;   // 1     Enable SYSCLKOUT to EPWM2
   Uint16 EPWM3ENCLK:1;   // 2     Enable SYSCLKOUT to EPWM3
   Uint16 EPWM4ENCLK:1;   // 3     Enable SYSCLKOUT to EPWM4
   Uint16 EPWM5ENCLK:1;   // 4     Enable SYSCLKOUT to EPWM5
   Uint16 EPWM6ENCLK:1;   // 5     Enable SYSCLKOUT to EPWM6
   Uint16 EPWM7ENCLK:1;   // 6     Enable SYSCLKOUT to EPWM7
   Uint16 EPWM8ENCLK:1;   // 7     Enable SYSCLKOUT to EPWM8
   Uint16 ECAP1ENCLK:1;   // 8     Enable SYSCLKOUT to ECAP1
   Uint16 ECAP2ENCLK:1;   // 9     Enable SYSCLKOUT to ECAP2
   Uint16 ECAP3ENCLK:1;   // 10    Enable SYSCLKOUT to ECAP3
   Uint16 ECAP4ENCLK:1;   // 11    Enable SYSCLKOUT to ECAP4
   Uint16 ECAP5ENCLK:1;   // 12    Enable SYSCLKOUT to ECAP5
   Uint16 ECAP6ENCLK:1;   // 13    Enable SYSCLKOUT to ECAP6
   Uint16 EQEP1ENCLK:1;   // 14    Enable SYSCLKOUT to EQEP1
   Uint16 EQEP2ENCLK:1;   // 15    Enable SYSCLKOUT to EQEP2
};

union PCLKCR1_REG {
   Uint16              all;
   struct PCLKCR1_BITS bit;
};

// Peripheral clock control register 2 bit definitions:
struct PCLKCR2_BITS  {    // bits  description
   Uint16 EPWM9ENCLK:1;   // 0     Enable SYSCLKOUT to EPWM9
   Uint16 rsvd1:7;        // 7:1   reserved
   Uint16 EQEP3ENCLK:1;   // 8     Enable SYSCLKOUT to ECAP1
   Uint16 rsvd2:7;        // 15:9  reserved
};

union PCLKCR2_REG {
   Uint16              all;
   struct PCLKCR2_BITS bit;
};

// Peripheral clock control register 3 bit definitions:
struct PCLKCR3_BITS  {        // bits  description
   Uint16 rsvd1:8;            // 7:0   reserved
   Uint16 CPUTIMER0ENCLK:1;   // 8     Enable SYSCLKOUT to CPU-Timer 0
   Uint16 CPUTIMER1ENCLK:1;   // 9     Enable SYSCLKOUT to CPU-Timer 1
   Uint16 CPUTIMER2ENCLK:1;   // 10    Enable SYSCLKOUT to CPU-Timer 2
   Uint16 DMAENCLK:1;         // 11    Enable the DMA clock
   Uint16 XINTFENCLK:1;       // 12    Enable SYSCLKOUT to XINTF
   Uint16 GPIOINENCLK:1;      // 13    Enable GPIO input clock
   Uint16 rsvd2:2;            // 15:14 reserved
};

union PCLKCR3_REG {
   Uint16              all;
   struct PCLKCR3_BITS bit;
};



// PLL control register bit definitions:
struct PLLCR_BITS {      // bits  description
   Uint16 DIV:5;         // 4:0   Set clock ratio for the PLL
   Uint16 rsvd1:11;      // 15:5  reserved
};

union PLLCR_REG {
   Uint16             all;
   struct PLLCR_BITS  bit;
};

// Low Power Mode 0 control register bit definitions:
struct LPMCR0_BITS {     // bits  description
   Uint16 LPM:2;         // 1:0   Set the low power mode
   Uint16 QUALSTDBY:6;   // 7:2   Qualification
   Uint16 rsvd1:7;       // 14:8  reserved
   Uint16 WDINTE:1;      // 15    Enables WD to wake the device from STANDBY
};

union LPMCR0_REG {
   Uint16              all;
   struct LPMCR0_BITS  bit;
};

struct EXTSOCPOL_BITS {     // bits  description
    Uint16 SOCA1POLSEL:1;   // 0     External ADC SOCA1 polarity select
    Uint16 SOCB1POLSEL:1;   // 1     External ADC SOCB1 polarity select
    Uint16 SOCA2POLSEL:1;   // 2     External ADC SOCA2 polarity select
    Uint16 SOCB2POLSEL:1;   // 3     External ADC SOCB2 polarity select
    Uint16 SOCA3POLSEL:1;   // 4     External ADC SOCA3 polarity select
    Uint16 SOCB3POLSEL:1;   // 5     External ADC SOCB3 polarity select
    Uint16 rsvd1:10;        // 15:6  reserved
};

union EXTSOCPOL_REG {
	Uint16                 all;
	struct EXTSOCPOL_BITS  bit;
};

struct FASTMEM_BITS {       // bits  description
	Uint16 ENFAST:1;		// 0     Enable 0 wait-state memory
	Uint16 rsvd1:15;        // 15:1  reserved
};

union FASTMEM_REG {
	Uint16                 all;
	struct FASTMEM_BITS    bit;
};

//---------------------------------------------------------------------------
// System Control Register File:
//
struct SYS_CTRL_REGS {
   Uint16                rsvd7;     // 0
   union   PLLSTS_REG    PLLSTS;    // 1
   Uint16                rsvd1[7];  // 2-8
   union   PCLKCR2_REG   PCLKCR2;   // 9 : Peripheral clock control register
   union   HISPCP_REG    HISPCP;    // 10: High-speed peripheral clock pre-scaler
   union   LOSPCP_REG    LOSPCP;    // 11: Low-speed peripheral clock pre-scaler
   union   PCLKCR0_REG   PCLKCR0;   // 12: Peripheral clock control register
   union   PCLKCR1_REG   PCLKCR1;   // 13: Peripheral clock control register
   union   LPMCR0_REG    LPMCR0;    // 14: Low-power mode control register 0
   Uint16                rsvd2;     // 15: reserved
   union   PCLKCR3_REG   PCLKCR3;   // 16: Peripheral clock control register
   union   PLLCR_REG     PLLCR;     // 17: PLL control register
   // No bit definitions are defined for SCSR because
   // a read-modify-write instruction can clear the WDOVERRIDE bit
   Uint16                SCSR;      // 18: System control and status register
   Uint16                WDCNTR;    // 19: WD counter register
   Uint16                rsvd4;     // 20
   Uint16                WDKEY;     // 21: WD reset key register
   Uint16                rsvd5[3];  // 22-24
   // No bit definitions are defined for WDCR because
   // the proper value must be written to the WDCHK field
   // whenever writing to this register.
   Uint16                WDCR;      // 25: WD timer control register
   Uint16                rsvd6[5];  // 26-30
   union   EXTSOCPOL_REG EXTSOCPOL; // 31: External ADC polarity select register
   union   FASTMEM_REG   FASTMEM;   // 32: Memory programmable wait states
};


/* --------------------------------------------------- */
/* CSM Registers                                       */
/*                                                     */
/* ----------------------------------------------------*/

/* CSM Status & Control register bit definitions */
struct  CSMSCR_BITS {      // bit   description
   Uint16     SECURE:1;    // 0     Secure flag
   Uint16     rsvd1:14;    // 14-1  reserved
   Uint16     FORCESEC:1;  // 15    Force Secure control bit

};

/* Allow access to the bit fields or entire register */
union CSMSCR_REG {
   Uint16             all;
   struct CSMSCR_BITS bit;
};



/* Password locations  - there is no security on this device. These locations support
   compatibility with legacy C28x designs.                                              */
struct  CSM_PWL {
   Uint16   PSWD0;  // PSWD bits 15-0
   Uint16   PSWD1;  // PSWD bits 31-16
   Uint16   PSWD2;  // PSWD bits 47-32
   Uint16   PSWD3;  // PSWD bits 63-48
   Uint16   PSWD4;  // PSWD bits 79-64
   Uint16   PSWD5;  // PSWD bits 95-80
   Uint16   PSWD6;  // PSWD bits 111-96
   Uint16   PSWD7;  // PSWD bits 127-112
};



//---------------------------------------------------------------------------
// System Control External References & Function Declarations:
//
extern volatile struct SYS_CTRL_REGS SysCtrlRegs;
extern volatile struct CSM_PWL CsmPwl;



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2834x_SYS_CTRL_H definition

//===========================================================================
// End of file.
//===========================================================================

