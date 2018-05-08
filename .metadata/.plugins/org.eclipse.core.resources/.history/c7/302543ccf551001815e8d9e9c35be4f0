#include	<header.h>
#include	<extern.h>

#define min_vf_ref  0.05

int vf_loop_control(float cmd_ref)
{
	int LoopCtrl;
	int trip_code=0;
	int command;
	float ref_in0;

//	simple_scalar_control_variable_init();

	VariInit();
	trip_code = HardwareParameterVerification();
	reference_in = cmd_ref;

	if( trip_code !=0 ) return trip_code;

	IER &= ~M_INT3;      // debug for PWM
	InitEPwm_ACIM_Inverter(); 	// debug
	EPwm1Regs.ETSEL.bit.INTEN = 1;    		            // Enable INT
	IER |= M_INT3;      // debug for PWM

	gRunFlag =1;
	strncpy(MonitorMsg,"INIT_RUN",20);
	gfRunTime = 0.0; 
	LoopCtrl = 1;		
	gMachineState = STATE_INIT_RUN;

	while(LoopCtrl == 1)
	{
		Nop();
		
		trip_code = trip_check();
		if( trip_code !=0 ){
			LoopCtrl = 0;
		}
		get_command( & command, & ref_in0);	            //
		Nop();

		if( command == CMD_START ) reference_in = ref_in0;

		switch( gMachineState )
		{
		case STATE_INIT_RUN:
			if( command == CMD_STOP){LoopCtrl= 0;}						
			else if( gfRunTime < 0.2 ){
				Freq_ref=0.0;	rpm_ref=0.0; reference_out = 0.0;				
			}
			else{
				strncpy(MonitorMsg,"RUN",20);
				gMachineState = STATE_RUN;
			}
			break;

		case STATE_RUN:

			Nop();
			if( command == CMD_NULL ) ramp_proc(reference_in, &reference_out);
			else if( command == CMD_STOP ) { 
				strncpy(MonitorMsg,"GO_STOP",20);
				reference_in = 0.0; 
				gMachineState = STATE_GO_STOP;
			}
			else if( command == CMD_SPEED_UP ){
				reference_in += 0.05;
				if( reference_in > 1.0 ) reference_in = 1.0;
			}
			else if( command == CMD_SPEED_DOWN ){
				reference_in -= 0.05;
				if( reference_in < -1.0 ) reference_in = -1.0;
			}
			else if( command == CMD_START ){
				ramp_proc(reference_in, & reference_out);
			}
			break;

		case STATE_GO_STOP:
			if( command == CMD_START ) {
				strncpy(MonitorMsg,"RUN",20);
				gMachineState = STATE_RUN;
				// reference_in = reference_out; 
			}				
			else if ((fabs(reference_out) <= min_vf_ref )){
                strncpy(MonitorMsg,"READY",20);
				gMachineState = STATE_READY; reference_out = Freq_out = 0.0; LoopCtrl = 0;
			}
			else{
				reference_in = 0.0;
				ramp_proc(reference_in, &reference_out);
			}
			break;
		}
	}

	return trip_code;
}		

//===========================================================================
// End of file.
//===========================================================================

