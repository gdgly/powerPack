/* Example_F28069_PID.c
 *
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED  
 *
*/

// header files
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "F2806x_GlobalPrototypes.h"
#include "DCL.h"

// function prototypes
extern interrupt void control_Isr(void);

// global  variables
long IdleLoopCount = 0;
long IsrCount = 0;
float rk = 0.25f;
float yk;
float lk;
float uk;
PID pid1 = PID_DEFAULTS;
float Duty;


/* main */
main()
{
	/* initialise system */
	InitSysCtrl();							// [F2806x_SysCtrl.c]
	DINT;									// disable interrupts
	IER = 0x0000;
	IFR = 0x0000;
	InitPieCtrl();							// initialise PIE control registers [F2806x_PieCtrl.c]
	InitPieVectTable();						// initialise PIE vector table [F2806x_PieVect.c]
	EALLOW;
	PieVectTable.ADCINT1 = &control_Isr;	// [F28069_PID_cisr.c]
	EDIS;

	/* configure ePWM1 */
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	InitEPwm();								// [F2806x_EPwm.c]
	EPwm1Regs.TBCTL.bit.CTRMODE = 3;		// freeze TB counter
	EPwm1Regs.TBCTL.bit.PRDLD = 1;  		// immediate load
	EPwm1Regs.TBCTL.bit.PHSEN = 0;	   		// disable phase loading
	EPwm1Regs.TBCTL.bit.SYNCOSEL = 3;		// disable SYNCOUT signal
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;		// TBCLK = SYSCLKOUT
	EPwm1Regs.TBCTL.bit.CLKDIV = 0;			// clock divider = /1
	EPwm1Regs.TBCTL.bit.FREE_SOFT = 2;		// free run on emulation suspend
	EPwm1Regs.TBPRD = 0x2328;	          	// set period for ePWM1 (0x2328 = 10kHz)
	EPwm1Regs.TBPHS.all = 0;			    // time-base Phase Register
	EPwm1Regs.TBCTR = 0;					// time-base Counter Register
	EPwm1Regs.ETSEL.bit.SOCAEN = 1;        	// enable SOC on A group
	EPwm1Regs.ETSEL.bit.SOCASEL = 1;       	// select SOC from zero match
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;        	// generate pulse on 1st event
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;		// enable shadow mode
	EPwm1Regs.CMPCTL.bit.LOADAMODE = 2; 	// reload on CTR=zero
	EPwm1Regs.CMPA.half.CMPA = 0x0080;	 	// set compare A value
	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;		// HIGH on CMPA up match
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;	// LOW on zero match
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;

	/* configure ADC */
	InitAdc();								// [F2806x_Adc.c]
	EALLOW;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 0;	// early interrupt generation
	AdcRegs.INTSEL1N2.bit.INT1E = 1;		// enabled ADCINT1
	AdcRegs.INTSEL1N2.bit.INT1CONT = 0;		// disable ADCINT1 continuous mode
	AdcRegs.INTSEL1N2.bit.INT1SEL = 1;		// setup EOC1 to trigger ADCINT1
	AdcRegs.INTSEL1N2.bit.INT2E = 0;	    // enable ADCINT2
	AdcRegs.INTSEL1N2.bit.INT2CONT = 0;	    // disable ADCINT1 continuous mode
	AdcRegs.INTSEL1N2.bit.INT2SEL = 0;	    // setup EOC1 to trigger ADCINT2
	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0;		// set SOC0 channel select to ADCINA0
	AdcRegs.ADCSOC1CTL.bit.CHSEL = 8;		// set SOC1 channel select to ADCINB0
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 5;		// set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;		// set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;		// set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC1CTL.bit.ACQPS = 6;		// set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	EDIS;

	/* configure GPIO */
	InitGpio();  							// [F2806x_Gpio.c]
	EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;	// GPIO34 = I/O pin
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;		// GPIO34 = output
	GpioDataRegs.GPBSET.bit.GPIO34 = 1;		// GPIO34 = 1
	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;	// GPIO39 = I/O pin
	GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;		// GPIO39 = output
	GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;	// GPIO39 = 0
	EDIS;

	/* initialise controller variables */
	pid1.Kp = 9.0f;
	pid1.Ki = 0.015f;
	pid1.Kd = 0.35f;
	pid1.Kr = 1.0f;
	pid1.c1 = 188.0296600613396f;
	pid1.c2 = 0.880296600613396f;
	pid1.d2 = 0.0f;
	pid1.d3 = 0.0f;
	pid1.i10 = 0.0f;
	pid1.i14 = 1.0f;
	pid1.Umax = 1.0f;
	pid1.Umin = -1.0f;

	rk = 0.25f;								// initial value for control reference
	lk = 1.0f;								// control loop not saturated

	/* enable interrupts */
	PieCtrlRegs.PIEIER1.bit.INTx1 = 1; 		// enable PIE INT 1.1 (ADCINT1) - [adcisr]
	IER |= M_INT1;							// enable core interrupt 1 (ADC) - [control_isr]
	SetDBGIER(0x0001);						// enable real-time debug interupts
	EINT;          							// enable global interrupt mask

	EALLOW;
	EPwm1Regs.TBCTL.bit.CTRMODE = 0;		// PWM1 timer: count up and start
	EDIS;

	/* idle loop */
	while(1)
	{
		IdleLoopCount++;					// increment loop counter
		asm(" NOP");
	} // while

} // main


/* control ISR: triggered by ADC EOC */
interrupt void control_Isr(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

	// read ADC channel
	yk = ((float) AdcResult.ADCRESULT0 - 2048.0f) / 2047.0f;
	lk = (float) AdcResult.ADCRESULT1;

	// external clamp for anti-windup reset
	DCL_runClamp_C1(&lk, 1.0f, 0.0f);

	// run PID controller
	uk = DCL_runPID_C4(&pid1, rk, yk, lk);

	// write u(k) to PWM
	Duty = (uk / 2.0f + 0.5f) * (float) EPwm1Regs.TBPRD;
	EPwm1Regs.CMPA.half.CMPA = (Uint16) Duty;

	IsrCount++;
}


/* end of file */
