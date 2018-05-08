#include	<header.h>
#include	<extern.h>

#define max_I_ratio     1.5
void VariInit()
{
	float x1,x2,y1,y2;
// for Vdc calc 

    code_adc_vdc_low    = 100;
    code_Vdc_calc_low   = 10;
    code_adc_vdc_high   = 2500;
    code_Vdc_calc_high  = 300;

	x1 = code_adc_vdc_low;		y1 = code_Vdc_calc_low;
	x2 = code_adc_vdc_high;		y2 = code_Vdc_calc_high;
	Vdc_factor = ( y2-y1) / ( x2 - x1 );
	Vdc_calc_offset = (( y1 * x2 - y2 * x1 )/ (x2- x1));

    // Ts = 1.0 / SWITCHING_FREQ;  // pwm switching frequency
    // inv_Ts = SWITCHING_FREQ;
    Ts = 1.0 / codePwmFreq;  // pwm switching frequency
    inv_Ts = codePwmFreq;

    Freq_rat = codeRateHz;
    inv_Freq_rat=1.0/Freq_rat;
    inv_motor_rate_hz = 1.0 / codeRateHz; //   csk_check 2009.10.30.

	gfRunTime=0.0;

	// reference
	reference_in=0.0;
	reference_out=0.0;	// new
    theta=0.0;
	we=0.0;
}	

int HardwareParameterVerification()
{
    if ( codeRatePower >(0.99*sqrt(3.0) * codeRateVolt * codeRateCurrent)){
        trip_recording( CODE_rate_power, codeRatePower,"PW FACTOR OVER"); // POWER FACTOR OVER
        return  CODE_rate_power;
    }
    //
    if (codeRatePower<(0.2*sqrt(3.0)*codeRateVolt * codeRateCurrent)){
        trip_recording( CODE_rate_power, codeRatePower,"PW FACTOR UNDER"); // POWER FACTOR UNDER
        return  CODE_rate_power;
    }
    //
    if ( codeRateRpm < (0.85*120.0 * codeRateHz / codeMotorPole)){
        trip_recording( CODE_rate_rpm, codeRateRpm,"RATE RPM UNDER");
        return  CODE_rate_rpm;
    }
    return  0;
}

//-----------------------------------
//  End of ParameterSect.c
//-----------------------------------

