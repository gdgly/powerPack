//
// project  : singlePhase Inverter, from back to back inverter
// pcb		: G0723 tms320F28069
// work dir : f28069/singlePhaseinv
// date		: 2017.09.08 Tuesday by Soonkil Jung CEO Eunwho Power Electronics
#include	<header.h>
#include	<extern.h>
#define LPF_ZETA     0.707
//--- DC link Voltage Low Pass
//float lpfIrmsK[4];
void lpf2ndCoeffInit( float cutoff_freq, float T_sample, float *x, float *y, float *k)
{	
	double omega_n;
	omega_n = 2.0 * PI * cutoff_freq ;
	* x = * (x + 1) = *(x + 2 ) = 0.0 ;
	* y = * (y + 1) = *(y +2) = 0.0 ;
	* k = 1./ (4.+4.* LPF_ZETA * omega_n * T_sample + omega_n * omega_n * T_sample * T_sample);
	*(k+1) = 8.0 - 2.0 * omega_n * omega_n * T_sample * T_sample;
	*(k+2) = 4.0 * LPF_ZETA * omega_n * T_sample - omega_n * omega_n * T_sample * T_sample -4.0;
	*(k+3) = omega_n * omega_n * T_sample * T_sample;
}
void lpf2nd(float * x,float * y, float * K)
{
	int i;
	float k[4];
	for ( i = 0 ; i< 4; i++)	k[i] = *(K + i);
    *y = k[0]*( k[1]*( *(y+1)) + k[2]*( *(y+2)) + k[3]*( (*x) + 2.*(*(x+1)) + (*(x+2))) );
	*(y+2) = *(y+1);	*(y+1) = * y;
	*(x+2) = *(x+1);    *(x+1) = * x;
}
// end of low_pass_filter
