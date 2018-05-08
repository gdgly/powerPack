// Company 	: Eunwho Power Electonics  
// FILE		: switching_irq.c
// Project 	: KERI back2back inverter
// PCB		: regen_dsp_110513 & regen_sen_110513
// date		: 2011-0105	by Cheoung Soon-Gil
// rev data : 2011.1013  cheoung soon gil

#include        <header.h>
#include        <extern.h>

int dacCount = 0;

interrupt void MainPWM(void)
{
	static int invt_PWM_Port_Set_flag = 0;
	float modulationRatio;

#if TEST_ADC_CENTER
	J8_2_SET;
#endif

	switch(gMachineState)
	{
    case STATE_TRIP:
        invt_PWM_Port_Set_flag = 0;
//      ePwmPortOff(); // converter PWM gate OFF
        break;

    case STATE_READY:
	case STATE_POWER_ON:
        EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
        EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
		break;

	case STATE_INIT_RUN:
		if( invt_PWM_Port_Set_flag == 0 ){
			ePwmEnable();
			invt_PWM_Port_Set_flag = 1;
		}
		else{
			EPwm1Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
			EPwm2Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
			EPwm3Regs.CMPA.half.CMPA = MAX_PWM_CNT>>1;
		}
		break;

	case STATE_RUN:
	case STATE_GO_STOP:
	case STATE_WAIT_BREAK_OFF:		

	    we = codeRateHz * reference_out;
	    theta += we * Ts;
        while (theta >= PI_2 ){ theta -= PI_2;}
        if (theta < 0.0 ) theta = 0.0;

        modulationRatio = reference_out;
        singlePhaseModulation(modulationRatio, theta, DutyRatio);

        DutyCount[0] = MAX_PWM_CNT * DutyRatio[0];
        DutyCount[1] = MAX_PWM_CNT * DutyRatio[1];
        DutyCount[2] = MAX_PWM_CNT * DutyRatio[2];

        EPwm1Regs.CMPA.half.CMPA = DutyCount[0];
        EPwm2Regs.CMPA.half.CMPA = DutyCount[1];
        EPwm3Regs.CMPA.half.CMPA = DutyCount[2];
        break;

	default: 
		invt_PWM_Port_Set_flag = 0;
		ePwmPortOff(); // converter PWM gate OFF
		break;
	}

	digital_out_proc();
//---

	if(dacCount<300){
	    y1_data[dacCount] = DutyRatio[1];
	    y2_data[dacCount] = DutyRatio[2];
        //y1_data[dacCount] = adcIuPhase /4096.0 ;
        //y2_data[dacCount] = adcIvPhase /4096.0 ;
        //y1_data[dacCount] = adcExSensor /4096.0 ;
        //y2_data[dacCount] = adcCmdAnalog /4096.0 ;
	    dacCount ++;
	}
	else dacCount = 0;

	EPwm1Regs.ETCLR.bit.INT = 1;	
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

#if TEST_ADC_CENTER
	J8_2_CLEAR;	// debug
#endif

}

 // end of switching_irq.c 

