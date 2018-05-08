//=========================================
//
//  vector_control.c
//   2009.08.30
//=========================================

#include	<header.h>
#include	<extern.h>

#if VECTOR_TEST==0

int vector_control()
{
	return 0;
}

int pwm_regenerat_convert()
{
	return 0;
}

void sl_vector_variable_init()
{
}
#else 

void PI_Damp_Controller(double limit,double Ts, double damp_factor, double Kp,double Ki,double ref,double feedback,double *integral,double *output)
{
	*integral+=Ki*(ref-feedback)*Ts;
	if (*integral>fabs(limit))			*integral=fabs(limit);
	else if (*integral<-fabs(limit))	*integral=-fabs(limit);
	*output=Kp*(damp_factor*ref-feedback)+*integral;
}


int vector_control()
{
	return 0;
}

#endif

