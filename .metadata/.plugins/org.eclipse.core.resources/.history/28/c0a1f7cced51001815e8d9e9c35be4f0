/*
*/

#define DELAY   50000L
#include	"header.h"
#include	"extern.h"
#include	"global.h"

#if FLASH_RUN
#pragma CODE_SECTION(MainPWM, "ramfuncs");
#pragma CODE_SECTION(adcIsr, "ramfuncs");
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
Uint16 RamfuncsLoadSize;
#endif

void InitWatchDog();
extern interrupt void MainPWM(void);
extern interrupt void adcIsr(void);
extern interrupt void sciaRxFifoIsr(void);
extern interrupt void sciaTxFifoIsr(void);

float Vdc_fnd_data;

void main( void )
{
    int trip_code,loop_ctrl,temp;
	int cmd;
	float ref_in0;

	InitSysCtrl();
	InitGpio();

	gfRunTime = 0.0; 
	protect_reg.all = gDeChargeFlag = 0;
	MAIN_CHARGE_OFF;

	INIT_CHARGE_CLEAR;

	init_charge_flag = 0;
//	RESET_DRIVER_CLEAR;

	gMachineState = STATE_POWER_ON; 
	DINT;
#if FLASH_RUN
	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);
	InitFlash();
#endif
	InitPieCtrl();
	IER = 0x0000;   IFR = 0x0000;
	InitPieVectTable();

	scia_fifo_init();

	I2CA_Init();	// Initalize I2C serial eeprom and Real Time Clock;
	InitCpuTimers();   // For this example, only initialize the Cpu Timers

	ConfigCpuTimer(&CpuTimer0, 90, 1000);	// debug 2011.10.01
	StartCpuTimer0();

	PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // Enable INT 1.1 in the PIE

	EALLOW;  // This is needed to write to EALLOW protected registers
	  	PieVectTable.TINT0 		= &cpu_timer0_isr;
		PieVectTable.WAKEINT 	= &wakeint_isr;
		PieVectTable.EPWM1_INT 	= &MainPWM;

		PieVectTable.ADCINT1	= &adcIsr;
		PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
		PieVectTable.SCITXINTA = &sciaTxFifoIsr;
  	EDIS;    // This is needed to disable write to EALLOW protected registers

  	InitAdc();
//    AdcOffsetSelfCal();

  	EALLOW;
     SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

  	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;	// Enable Adc irq
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	// Timer0 irq
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // Enable INT 1.1 in the PIE ADCINT1
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;   //

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block

    IER |= M_INT1;		// Enable CPU INT1 which is connected to CPU-Timer 0:
	IER |= M_INT8;		// scic irq 
	IER |= M_INT9;		//CAN, SCI_A
    IER |= M_INT3;

    EINT;   // Enable Global interrupt INTM
	ERTM;	// Enable Global realtime interrupt DBGM

    InitWatchDog();

    ADC_SOC_CNF();
    strncpy(MonitorMsg,"POWER_ON",20);
    gPWMTripCode = 0;		//
	//init_eprom_data();
/*
    for( ; ; ){
        Nop();
    }
*/
    if( load_code2ram() != 0 ) tripProc();
	if(HardwareParameterVerification() !=0 ) tripProc();

    VariInit();
    //lpf2ndCoeffInit( LPF_VDC_CUTOFF_FREQ,Ts, lpfVdcIn, lpfVdcOut, lpfVdcK);
    lpf2ndCoeffInit( 1000.0, Ts, lpfVdcIn, lpfVdcOut, lpfVdcK);
    lpf2ndCoeffInit( 1.0, Ts, lpfImIn, lpfImOut, lpfIrmsK);
    lpf2ndCoeffInit( 1.0, Ts, lpfIaIn, lpfIaOut, lpfIrmsK);

	IER &= ~M_INT3;      // debug for PWM
	InitEPwm_ACIM_Inverter(); 	// debug
	EPwm1Regs.ETSEL.bit.INTEN = 1;    		            // Enable INT
	IER |= M_INT3;      // debug for PWM

	gfRunTime = 0.0; 

    delay_msecs(500);

    temp = (int)(floor(codeProtectOff+0.5));

    code_protect_uv_off = 1;
    code_protect_ov_off = 1;

    if( temp != 0 )
	{
		protect_reg.bit.UNVER_VOLT = 0;			// udd �߰� 
		protect_reg.bit.EX_TRIP = 0;
		protect_reg.bit.OVER_VOLT = 0;
		protect_reg.bit.OVER_I_ADC = 0;
		protect_reg.bit.IGBT_FAULT = 0;		
		protect_reg.bit.OVER_I = 0;
	}
	else {
		if(code_protect_uv_off == 0 ) 		protect_reg.bit.UNVER_VOLT = 1;			// udd �߰� 
		if(code_protect_ov_off == 0 ) 		protect_reg.bit.OVER_VOLT = 1;
		if(code_protect_Iadc_off == 0 ) 	protect_reg.bit.OVER_I_ADC = 1;
		if(code_protect_over_I_off == 0) 	protect_reg.bit.OVER_I = 1;
		if(code_protect_IGBT_off == 0 ) 	protect_reg.bit.IGBT_FAULT = 1;		
		if(code_protect_ex_trip_off == 0 ) 	protect_reg.bit.EX_TRIP = 1;
	}

	init_charge_flag = 1;	
	while( gfRunTime < 5.0){
		get_command( & cmd, & ref_in0);
//		monitor_proc();
		Nop();
	}

	gPWMTripCode = 0;
	loop_ctrl = 1;
	gfRunTime = 0.0;

	if((codeProtectOff == 0 ) & (code_protect_uv_off == 0 )){
		while( loop_ctrl == 1){
			if( Vdc > under_volt_set ) loop_ctrl = 0;
			if( gfRunTime > 5.0) loop_ctrl = 0;
		}
		if( Vdc < under_volt_set ){
			trip_recording( CODE_under_volt_set,Vdc,"Trip Under Volt");
			tripProc();
		}
	}
	else{
		MAIN_CHARGE_ON;		//
		TRIP_OUT_OFF;
	}

	MAIN_CHARGE_ON;		    //
	init_charge_flag=0;
	gMachineState = STATE_READY; 
	INIT_CHARGE_CLEAR;

	if( gPWMTripCode !=0 )	tripProc();
	strncpy(MonitorMsg,"READY",20);delay_msecs(20);
	strncpy(gStr1,"READY",20);
	load_sci_tx_mail_box(gStr1); delay_msecs(20);
	GATE_DRIVER_ENABLE;
	for( ; ; )
	{
		if( gPWMTripCode !=0 )	tripProc();
		gPWMTripCode = trip_check();
		if( gPWMTripCode !=0 )	tripProc();
		get_command( & cmd, & ref_in0);
//		analog_out_proc( );
		if(cmd == CMD_READ_ALL ){
		    readAllCodes();
		}
		if(cmd == CMD_START){	// if( cmd == CMD_START )
			trip_code = vf_loop_control(ref_in0);		//
			if( trip_code !=0 )	tripProc();
		}
	}
}

void InitEPwm_ACIM_Inverter()
{  
	EPwm1Regs.ETSEL.bit.INTEN = 0;    		        // Enable INT
//	MAX_PWM_CNT = (Uint16)( ( F_OSC * DSP28_PLLCR / SWITCHING_FREQ ) * 0.5 * 0.5 * 0.5);
	MAX_PWM_CNT = (Uint16)( ( F_OSC * DSP28_PLLCR / codePwmFreq ) * 0.5 * 0.5 * 0.5);
	inv_MAX_PWM_CNT = 1.0 / MAX_PWM_CNT;

//--- PWM Module1
	EPwm1Regs.TBPRD                 =  MAX_PWM_CNT;			// Set timer period
	EPwm1Regs.TBPHS.half.TBPHS      = 0x0000; // Phase is 0
    EPwm1Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN;  //
    EPwm1Regs.TBCTL.bit.PHSEN       = TB_DISABLE;   // 2017.09.05
    EPwm1Regs.TBCTL.bit.PRDLD       = TB_SHADOW;    // 2017.09.05
    EPwm1Regs.TBCTL.bit.SYNCOSEL    = TB_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;	// Load registers every ZERO
	EPwm1Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;
	EPwm1Regs.AQCTLA.bit.CAU        = AQ_CLEAR;
	EPwm1Regs.AQCTLA.bit.CAD        = AQ_SET;
	EPwm1Regs.DBCTL.bit.OUT_MODE 	= DB_FULL_ENABLE;
	EPwm1Regs.DBCTL.bit.POLSEL 	    = DB_ACTV_LOC;
	EPwm1Regs.DBRED                 = DEAD_TIME_COUNT; // debug set to 4usec
	EPwm1Regs.DBFED                 = DEAD_TIME_COUNT;
    EPwm1Regs.CMPA.half.CMPA        = MAX_PWM_CNT;
//--- Set PWM2
	EPwm2Regs.TBPRD                 =  MAX_PWM_CNT;				// Set timer period
    EPwm2Regs.TBPHS.half.TBPHS      = 0x0000;            // Phase is 0
	EPwm2Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN; 		// Count up
    EPwm2Regs.TBCTL.bit.PHSEN       = TB_ENABLE;
    EPwm2Regs.TBCTL.bit.PRDLD       = TB_SHADOW;          // 2017.09.05
    EPwm2Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;
    EPwm2Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;
    EPwm2Regs.AQCTLA.bit.CAU        = AQ_CLEAR;
    EPwm2Regs.AQCTLA.bit.CAD        = AQ_SET;
	EPwm2Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;
	EPwm2Regs.DBCTL.bit.POLSEL      = DB_ACTV_LOC;
	EPwm2Regs.DBRED                 = DEAD_TIME_COUNT;
	EPwm2Regs.DBFED                 = DEAD_TIME_COUNT;
    EPwm2Regs.CMPA.half.CMPA        = MAX_PWM_CNT;
//	EPwm2Regs.ETSEL.bit.INTEN = 0;

//Set PWM3 
	EPwm3Regs.TBPRD =  MAX_PWM_CNT;			// Set timer period
    EPwm3Regs.TBPHS.half.TBPHS      = 0x0000;               // Phase is 0
	EPwm3Regs.TBCTL.bit.CTRMODE 	= TB_COUNT_UPDOWN; 	// Count up
	EPwm3Regs.TBCTL.bit.PHSEN 		= TB_ENABLE; 
    EPwm3Regs.TBCTL.bit.PRDLD       = TB_SHADOW;          // 2017.09.05
	EPwm3Regs.TBCTL.bit.SYNCOSEL 	= TB_SYNC_IN;        	
    EPwm3Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;
    EPwm3Regs.AQCTLA.bit.CAU        = AQ_CLEAR;
    EPwm3Regs.AQCTLA.bit.CAD        = AQ_SET;
    EPwm3Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;
    EPwm3Regs.DBCTL.bit.POLSEL      = DB_ACTV_LOC;
	EPwm3Regs.CMPA.half.CMPA 		= MAX_PWM_CNT;
	EPwm3Regs.DBRED 				= DEAD_TIME_COUNT;
	EPwm3Regs.DBFED 				= DEAD_TIME_COUNT;
//	EPwm3Regs.ETSEL.bit.INTEN 		= 0;

//Set PWM4 
	EPwm4Regs.TBPRD =  MAX_PWM_CNT;			// Set timer period

	EPwm4Regs.TBCTL.bit.PHSDIR 		= TB_UP;				// Count up
	EPwm4Regs.TBCTL.bit.CTRMODE 	= TB_COUNT_UPDOWN; 	// Count up
	EPwm4Regs.TBCTL.bit.HSPCLKDIV 	= TB_DIV1;		// 
	EPwm4Regs.TBCTL.bit.CLKDIV 		= TB_DIV1;			// Slow so we can observe on the scope

	EPwm4Regs.TBPHS.half.TBPHS 		= 0x0000;           	// Phase is 0
	EPwm4Regs.TBCTL.bit.PHSEN 		= TB_ENABLE; 
	EPwm4Regs.TBCTL.bit.SYNCOSEL 	= TB_SYNC_IN;        	

	EPwm4Regs.CMPA.half.CMPA 		= MAX_PWM_CNT;

	EPwm4Regs.AQCTLA.bit.CAU 		= AQ_SET;	 
	EPwm4Regs.AQCTLA.bit.CAD 		= AQ_CLEAR;

	EPwm4Regs.DBCTL.bit.OUT_MODE 	= DB_FULL_ENABLE;
	EPwm4Regs.DBCTL.bit.POLSEL 		= DB_ACTV_HIC;

	EPwm4Regs.DBCTL.bit.IN_MODE 	= DBA_ALL;
	EPwm4Regs.DBRED 				= DEAD_TIME_COUNT;
	EPwm4Regs.DBFED 				= DEAD_TIME_COUNT;
	EPwm4Regs.ETSEL.bit.INTEN 		= 0;                  

	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;	// Select INT on Zero event
	EPwm1Regs.ETPS.bit.INTPRD = 1;   // Generate interrupt on the 1st event
	EPwm1Regs.ETCLR.bit.INT = 1;     //  

//	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// Enable SOCA from ePWM to start SEQ1
//	AdcRegs.ADCTRL3.all = 0x00FE;  // Power up bandgap/reference/ADC circuits

	EPwm1Regs.ETSEL.bit.SOCAEN = 1;   // Enable SOC on A group
	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;//
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;        // Generate pulse on 1st event

	PieCtrlRegs.PIEIER3.all = M_INT1;	// ePWM
    // PieCtrlRegs.PIEIER3.bit.INTx1 = PWM1_INT_ENABLE;
}

interrupt void wakeint_isr(void)
{
	static int WakeCount = 0; 

	WakeCount++;
	
	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

void InitWatchDog()
{
	// Enable watch dog
// Write to the whole SCSR register to avoid clearing WDOVERRIDE bit

   EALLOW;
   SysCtrlRegs.SCSR = BIT1;
   EDIS;

// Enable WAKEINT in the PIE: Group 1 interrupt 8
// Enable INT1 which is connected to WAKEINT:
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER1.bit.INTx8 = 1;   // Enable PIE Gropu 1 INT8
   IER |= M_INT1;                       // Enable CPU int1
   EINT;                                // Enable Global Interrupts

   ServiceDog();

   EALLOW;
   SysCtrlRegs.WDCR = 0x0028;   
   EDIS;
}

//=========================================
// No more.
//=========================================

