/*
 * switchingIrq.c
 *
 *  Created on: 2015. 8. 3.
 *      Author: eunwho
 */

#include        <header.h>
#include        <extern.h>

interrupt void mainPwm(void)
{
	unsigned int ChACount,ChBCount;

//--- DB Chopper
	if( gMachineState == STATE_RUN )
	{
		if( Vdc > ( over_volt_set - 30.0 ))
			EPwm4Regs.CMPA.half.CMPA = guiEpwmPeriodCount >> 2 ; // 1/4 ���
		else
			EPwm4Regs.CMPA.half.CMPA = guiEpwmPeriodCount;		// ��� off
	}
	else
		EPwm4Regs.CMPA.half.CMPA = guiEpwmPeriodCount;

//--- Ana Monitor 1,2
	//GetAnaMonitCount(&ChACount,&ChBCount);
	EPwm5Regs.CMPA.half.CMPA 	= ChACount;
	EPwm5Regs.CMPB  			= ChBCount;

//	dac_8412_out();

	Nop();
//	gPWMTripCode = trip_check();
// adc irq ���� ������ �ʴ�.
	if(gPWMTripCode){
		EPwm1Regs.CMPA.half.CMPA = 0;
		EPwm2Regs.CMPA.half.CMPA = 0;
		EPwm3Regs.CMPA.half.CMPA = 0;
		goto _PWM_TRIP;
	}

	switch(gMachineState)
	{
	case STATE_READY:
	case STATE_POWER_ON:
	case STATE_TRIP:
		EPwm1Regs.CMPA.half.CMPA = 0;
		EPwm2Regs.CMPA.half.CMPA = 0;
		EPwm3Regs.CMPA.half.CMPA = 0;
		break;

	case STATE_INIT_RUN:
		EPwm1Regs.CMPA.half.CMPA = guiEpwmPeriodCount>>1;
		EPwm2Regs.CMPA.half.CMPA = guiEpwmPeriodCount>>1;
		EPwm3Regs.CMPA.half.CMPA = guiEpwmPeriodCount>>1;
		break;

	case STATE_RUN:
	case STATE_GO_STOP:
	case STATE_WAIT_BREAK_OFF:
//		gPWMTripCode = trip_check();
		if(gPWMTripCode !=0){
			gTripSaveFlag = 1; // for Trip History Save to EEPROM in Out irq
			EPwm1Regs.CMPA.half.CMPA = 0;
			EPwm2Regs.CMPA.half.CMPA = 0;
			EPwm3Regs.CMPA.half.CMPA = 0;
		}
		else{
//	    	VoltageEstimation();
//			MotorControlProc( );
//			SpaceVectorModulation(Vs_dq_ref);
			EPwm1Regs.CMPA.half.CMPA = DutyCount[u];
			EPwm2Regs.CMPA.half.CMPA = DutyCount[v];
			EPwm3Regs.CMPA.half.CMPA = DutyCount[w];
		}
		break;

	default:
		EPwm1Regs.CMPA.half.CMPA = 0;
		EPwm2Regs.CMPA.half.CMPA = 0;
		EPwm3Regs.CMPA.half.CMPA = 0;
		break;
	}

_PWM_TRIP:
//	DELAY_US(100);		// debug

	EPwm1Regs.ETCLR.bit.INT = 1;
	// Acknowledge interrupt to recieve more interrupts from PIE group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


