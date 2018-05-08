//
// analog.c
// 2012.04.12
// Eunwho Power Electronics
// by Cheoung Soon Gil
// revision :
#include	<header.h>
#include	<extern.h>

void ADC_SOC_CNF( )
{
    extern void DSP28x_usDelay(Uint32 Count);

    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1; // Enable non-overlap mode
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcRegs.INTSEL1N2.bit.INT1E = 1;        // enable ADC interrupt 1
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0; // set ADCInterrupt 1 to auto clr

    AdcRegs.INTSEL1N2.bit.INT1SEL = 1;      // IntChSel causes ADCInterrupt 1

    AdcRegs.ADCSOC0CTL.bit.CHSEL= 0;        // I_u
    AdcRegs.ADCSOC1CTL.bit.CHSEL= 1;        // I_v
    AdcRegs.ADCSOC2CTL.bit.CHSEL= 8;        // Vdc
    AdcRegs.ADCSOC3CTL.bit.CHSEL= 9;        // IGBT_Temp
    AdcRegs.ADCSOC4CTL.bit.CHSEL= 3;        // Ex_sensor
    AdcRegs.ADCSOC5CTL.bit.CHSEL= 5;        // Ex_sensor

    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL = 5;
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL = 5;

    AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC1CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC2CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC3CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC4CTL.bit.ACQPS = 6;
    AdcRegs.ADCSOC5CTL.bit.ACQPS = 6;
//    AdcRegs.ADCSAMPLEMODE.all = 0;      // Simultaneous sample mode
    EDIS;
}
#define adcIuOffset     2585
#define adcIvOffset     2578
//--- 전류의 계산 : 66mV / A  :  3.3V -> 50A, 1 count = 50 / 4096 = 0.012207
#define I_RATIO         0.012207

interrupt void adcIsr(void)
{
//    float fTemp1,fTemp2;
//    int temp;

    adc_result[0] = AdcResult.ADCRESULT0;
    adc_result[1] = AdcResult.ADCRESULT1;
    adc_result[2] = AdcResult.ADCRESULT2;
    adc_result[3] = AdcResult.ADCRESULT3;
    adc_result[4] = AdcResult.ADCRESULT4;
    adc_result[5] = AdcResult.ADCRESULT5;
// 전류의 계산 : 66mV / A  :  3.3V -> 50A, 1 count = 50 / 4096 = 0.012207
/*
//    Is_abc[as] = sensIu = ( adcIu - codeIaOffset ) * I_RATIO;
//    Is_abc[bs] = sensIv = ( adcIv - codeIbOffset ) * I_RATIO;

//    Is_abc[as] = - I_sense_value * (fTemp1) * u_phase_I_sense_span - u_phase_I_sense_zero;
//    Is_abc[bs] = - I_sense_value * (fTemp2) * v_phase_I_sense_span - v_phase_I_sense_zero;

    Is_abc[cs] =-(Is_abc[as]+Is_abc[bs]);
    Is_dq[ds] = Is_abc[as];

    Is_dq[qs] = 0.577350*Is_abc[as]+1.15470*Is_abc[bs];
    Is_mag = sqrt(Is_dq[ds]*Is_dq[ds]+Is_dq[qs]*Is_dq[qs]);           // Àü·ùÅ©±â
    Is_mag_rms = 0.707106*Is_mag;
//    analog_ref_a = ((double) (giAdcAI_V1)) * 0.0002441406250;

    sensVdc = Vdc_factor * (double) adcVdc + Vdc_calc_offset ;
    // Vdc = Vdc_factor * fTemp1 + Vdc_calc_offset;

    lpfVdcIn[0] = sensVdc;
    lpf2nd( lpfVdcIn, lpfVdcOut, lpfVdcK);
    Vdc = lpfVdc = lpfVdcOut[0];

    lpfIuIn[0] = sensIu * sensIu;
    lpf2nd( lpfIuIn, lpfIuOut, lpfIuRmsK);
    rmsIu = lpfIuOut[0] * INV_ROOT2;

    lpfIvIn[0] = sensIv * sensIv;
    lpf2nd( lpfIvIn, lpfIvOut, lpfIvRmsK);
    rmsIv = lpfIvOut[0] * INV_ROOT2;

    temp = (int)(floor(codeSetVdc+0.5));
    if(temp != 0 ) Vdc =300.0;
*/
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
    return;
}

void analog_input_proc( double * referenc)
{
	* referenc = analog_ref_a * analog_cmd_in_span1 - analog_cmd_in_zero1;
}

void analog_out_proc( )
{
}

int check_sensor_trip()
{
	int TripCode;

	Nop();

	if( ( TripCode = CheckOverCurrent()) != 0 ) return TripCode ;	// debug
	if( ( TripCode = CheckOverVolt()   ) != 0 ) return TripCode ;
	if( ( TripCode = CheckUndeVolt()   ) != 0 ) return TripCode ;	// ���������� ������ �Ѵ�. 
	return 0;
}
	
// end of file
