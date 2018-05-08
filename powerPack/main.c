#define DELAY   50000L
#include	"header.h"
#include	"extern.h"
#include	"global.h"

#if FLASH_RUN
#pragma CODE_SECTION(mainPwm, "ramfuncs");
#pragma CODE_SECTION(adcIsr, "ramfuncs");
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
Uint16 RamfuncsLoadSize;
#endif

void main( void )
{
	int trip_code,i;
	int cmd;
	double ref_in0;

	InitSysCtrl();
	InitGpio();

	gfRunTime = 0.0; 
	protect_reg.all = gDeChargeFlag = 0;
    MAIN_CHARGE_OFF;

	gMachineState = STATE_POWER_ON; 

	DINT;	IER = 0x0000; 	IFR = 0x0000;

	memcpy(&RamfuncsRunStart, &RamfuncsLoadEnd, (Uint32)&RamfuncsLoadSize);
	InitFlash();

	InitPieCtrl();
	scia_fifo_init();

	I2CA_Init();	// Initalize I2C serial eeprom and Real Time Clock;
	InitCpuTimers();   // For this example, only initialize the Cpu Timers
	ConfigCpuTimer(&CpuTimer0, 90, 1000);	// debug 2011.10.01
	StartCpuTimer0();
	InitAdc();				

	EALLOW;  // This is needed to write to EALLOW protected registers
  	PieVectTable.TINT0 		= &cpu_timer0_isr;
	PieVectTable.WAKEINT 	= &wakeint_isr;
	PieVectTable.EPWM1_INT 	= &mainPwm;
	PieVectTable.ADCINT1	= &adcIsr;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;    // This is needed to disable write to EALLOW protected registers

	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;	// Enable Adc irq
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	// Timer0 irq
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block   

	IER |= M_INT1;		// Enable CPU INT1 which is connected to CPU-Timer 0:
	IER |= M_INT8;		// scic irq 
	IER |= M_INT9;		//CAN, SCI_A
	EINT;   // Enable Global interrupt INTM
	ERTM;	// Enable Global realtime interrupt DBGM

	gPWMTripCode = 0;		// ������ �ʱ�ȭ 

	i = load_code2ram();
	if( i !=0 ) tripProc();

	while( gfRunTime < 3.0){
		check_sensor_trip();		// adc 2mscec period
		monitorProc();
		Nop();
	}
	gMachineState = STATE_READY; 
	led_state_flag=0;
	warning_fnd_flag=0;

	VariableInitialization();
	if(HardwareParameterVerification() !=0 ) tripProc();
	protect_reg.bit.UNVER_VOLT = 1;			// udd �߰� 
	protect_reg.bit.EX_TRIP = 1;
	protect_reg.bit.OVER_VOLT = 1;
	protect_reg.bit.OVER_I_ADC = 1;
	protect_reg.bit.IGBT_FAULT = 1;		// make comment at simulation
	protect_reg.bit.OVER_I = 1;

	delay_msecs(2);
	if(gPWMTripCode != 0) tripProc();	// udd
	load_sci_tx_mail_box("\n Inverter Ready " ) ; delay_msecs(5);

	for( ; ; )
	{
		if(gPWMTripCode != 0) tripProc();			// irq���� �߻�� Ʈ���� ���� ó��
		check_sensor_trip();
		if( trip_check()!=0 ) tripProc();

		strncpy(MonitorMsg," INVERTER READY     ",20);

		get_command( & cmd, & reference_in );
		digital_out_proc();
		analog_out_proc( );
		monitorProc();
        if(cmd == CMD_READ_ALL){
            sendAllCodeData();
        }
        else if( cmd == CMD_START )
		{
			trip_code = 0;
			switch( motor_ctrl_mode ) // Control Method
			{
			case 0:	trip_code = vf_frequency_control(); break;
			case 1: trip_code = vf_speed_control();  break;
			case 3: trip_code = test_run(); break;
			case CTRL_PARA_ESTIM: trip_code = parameter_estimation(); break;
			case CTRL_HYD_UNIT: trip_code = hyd_unit_loop_proc();
				break;
			}
			if( trip_code !=0 )	tripProc();
		}
	}
}

void InitEPwm_ACIM_Inverter()
{  
	EPwm1Regs.ETSEL.bit.INTEN = 0;    		            // Enable INT
	guiEpwmPeriodCount =	(Uint16)( ( F_OSC / igbt_pwm_freq )  * DSP28_PLLCR * 0.5 * 0.5 );

	EPwm1Regs.TBPRD =  guiEpwmPeriodCount;				// Set timer period
	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           	// Phase is 0
	EPwm1Regs.TBCTR = 0x0000;                      	// Clear counter

	// Setup TBCLK
	EPwm1Regs.TBCTL.bit.PHSDIR = TB_UP;	// Count up
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// Count up
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;			// Disable phase loading
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;					// Clock ratio to SYSCLKOUT
	EPwm1Regs.TBCTL.bit.CLKDIV = 0;

	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;		// Load registers every ZERO
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;   

	// Setup compare 
	EPwm1Regs.CMPA.half.CMPA = 0;
   
	// Set actions
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;					// Set PWM1A on Zero
	EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
   
	EPwm1Regs.DBCTL.bit.OUT_MODE 	= DB_FULL_ENABLE;
	EPwm1Regs.DBCTL.bit.POLSEL 		= DB_ACTV_LOC;
	EPwm1Regs.DBCTL.bit.IN_MODE 	= DBA_ALL;
	EPwm1Regs.DBRED = DEAD_TIME_COUNT;					// debug set to 4usec
	EPwm1Regs.DBFED = DEAD_TIME_COUNT;
	// Setup TBCLK
	EPwm2Regs.TBPRD =  guiEpwmPeriodCount;				// Set timer period

	EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;	// Count up
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 		// Count up
	EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;        		// Disable phase loading
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;       			// Clock ratio to SYSCLKOUT
	EPwm2Regs.TBCTL.bit.CLKDIV = 0;          			// Slow just to observe on the scope

	// Setup compare 
	EPwm2Regs.CMPA.half.CMPA = 0;

	// Set actions
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;             		// Set PWM2A on Zero
	EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
	// Active Low complementary PWMs - setup the deadband
	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;
	EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm2Regs.DBRED = DEAD_TIME_COUNT;
	EPwm2Regs.DBFED = DEAD_TIME_COUNT;
	EPwm2Regs.ETSEL.bit.INTEN = 0;                 		// Enable INT

	EPwm3Regs.TBPRD =  guiEpwmPeriodCount;				// Set timer period
	EPwm3Regs.TBCTL.bit.PHSDIR = TB_UP;	// Count up
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 		// Count up
	EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE; 				// 
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;				// 
	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;				// Slow so we can observe on the scope
	EPwm3Regs.CMPA.half.CMPA = 0;
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;              // Set PWM3A on Zero
	EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;
	EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm3Regs.DBRED = DEAD_TIME_COUNT;
	EPwm3Regs.DBFED = DEAD_TIME_COUNT;
	EPwm3Regs.ETSEL.bit.INTEN = 0;                  // Enable INT

	//------------------------------
	//InitEPwm4   A == db B INIT_Charge 
	//------------------------------

	EPwm4Regs.TBPRD =  guiEpwmPeriodCount;			// Set timer period
	EPwm4Regs.TBCTL.bit.PHSDIR = TB_UP;				//

	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// Count up
	EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE; 

	EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	// Setup compare 
	EPwm4Regs.CMPA.half.CMPA =  guiEpwmPeriodCount;
	EPwm4Regs.CMPB			=  guiEpwmPeriodCount;

	// Set actions
	EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM4A on Zero
	EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;

	EPwm4Regs.AQCTLB.bit.CBU = AQ_SET;              // Set PWM4B on Zero
	EPwm4Regs.AQCTLB.bit.CBD = AQ_CLEAR;

	// Active high complementary PWMs - Setup the deadband
	EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
	EPwm4Regs.ETSEL.bit.INTEN = 0;                  // Enable INT

	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;	// Select INT on Zero event
	EPwm1Regs.ETPS.bit.INTPRD = 1;   // Generate interrupt on the 1st event
	EPwm1Regs.ETCLR.bit.INT = 1;     //  

	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 	= 1;  // GPIO0 = PWM1A
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 	= 1;  // GPIO1 = PWM1B
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 	= 1;  // GPIO2 = PWM2A
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 	= 1;  // GPIO3 = PWM2B
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 	= 1;  // GPIO4 = PWM3A
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 	= 1;  // GPIO5 = PWM3B
	EDIS;

	EPwm1Regs.ETSEL.bit.SOCAEN = 1;   // Enable SOC on A group
	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO; // ET_CTR_PRD?
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;        // Generate pulse on 1st event

	PieCtrlRegs.PIEIER3.all = M_INT1;	// ePWM
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
   EALLOW;
   SysCtrlRegs.SCSR = BIT1;
   EDIS;
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER1.bit.INTx8 = 1;   // Enable PIE Gropu 1 INT8
   IER |= M_INT1;                       // Enable CPU int1
   EINT;                                // Enable Global Interrupts
   ServiceDog();
   EALLOW;
   SysCtrlRegs.WDCR = 0x0028;   
   EDIS;
}
//--- end of file
