#include	<header.h>
#include	<extern.h>

#if USE_TEST_RUN

int test_run()
{
	int LoopCtrl;
	int iTripCode=0;

	int iCommand;
	double fReference;

	VariableInitialization();

	iTripCode = HardwareParameterVerification();
	if( iTripCode !=0 ) return iTripCode;

	iTripCode = SL_SPEED_CNTL_Parameter();        
	if( iTripCode != 0)
			return iTripCode;			// debug

	IER &= ~M_INT3;      // debug for PWM
	InitEPwm_ACIM_Inverter(); 	// debug
	EPwm1Regs.ETSEL.bit.INTEN = 1;    		            // Enable INT
	IER |= M_INT3;      // debug for PWM

	gRunFlag =1;
	strncpy(MonitorMsg," INIT MOTOR RUN     ",20);
	gfRunTime = 0.0; 
	LoopCtrl = 1;		

	reference_in = btn_start_ref;
	gMachineState = STATE_RUN;
	
	while(LoopCtrl == 1)
	{
		if(gPWMTripCode != 0){
			iTripCode = gPWMTripCode;
			LoopCtrl = 0;
			break;
		}		

		get_command(&iCommand,&fReference);	// Command�� �Է� ���� 				

		monitorProc();

		if( iCommand == CMD_START) reference_in = fReference;
		else if( iCommand == CMD_STOP) reference_in = 0.0;

		switch( gMachineState )
		{
		case STATE_RUN:
			if		 (  iCommand == CMD_NULL ) 			ramp_proc( reference_in, &reference_out);
			else if(( iCommand == CMD_SPEED_UP   ) && (reference_in <  1.0  )) reference_in += 0.01;
			else if(( iCommand == CMD_SPEED_DOWN ) && ( reference_in > 0.01 )) reference_in -= 0.01;
			else if(  iCommand == CMD_STOP ) { 
									  //"01234567890123456789"	
				strncpy(MonitorMsg," INV GO STOP        ",20);
				reference_in = 0.0; gMachineState = STATE_GO_STOP;
			}
			else if(  iCommand == CMD_START ) ramp_proc( reference_in, &reference_out);
			else{
				reference_in = 0.0; gMachineState = STATE_GO_STOP;
			}
			break;

		case STATE_GO_STOP:
//---- �� �õ� 
			if( iCommand == CMD_START ) {
									  //"01234567890123456789"	
				strncpy(MonitorMsg," INVERTER RUN       ",20);
				gMachineState = STATE_RUN;
				reference_in = fReference; 
			}				
			else if( fabs( reference_out ) < 0.01 ){
				strncpy(MonitorMsg," INVERTER READY     ",20);
				gMachineState = STATE_READY;
				LoopCtrl =0;
			}
			else{
				reference_in = 0.0;
				ramp_proc(reference_in, &reference_out);
			}
			break;
		}
	}
	return iTripCode;
}

#endif

