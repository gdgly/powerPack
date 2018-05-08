//
// hyd_unit.c
// 2009.12.31

#include	<header.h>
#include	<extern.h>

void hyd_unit_proc(int state, double * ref_out)
{
	static int hyd_low_count=0;
	static double ref_in = 1.0;
	double hyd_sensor_input;

	static unsigned long ulCount;

 	if( ulGetNow_mSec( )== ulCount ) return;

	ulCount = ulGetNow_mSec( );
	hyd_sensor_input = analog_ref_a;

	if( state == STATE_RUN ){

		if( hyd_sensor_input < ( hyd_sensor_set_ref * hyd_high_speed_on_ratio ) ) hyd_low_count++;
		else if ( hyd_sensor_input >  hyd_sensor_set_ref ) hyd_low_count --;	

		if( hyd_low_count > 3){
			hyd_low_count = 4;
			ref_in = hyd_max_ref;
		}
		else if( hyd_low_count <= 0 ){
			hyd_low_count = 0 ;
			ref_in = digital_speed2;
		}
	}
	else	ref_in = 0.0;

	RefFunc( ref_in, ref_out );

}

int hyd_unit_loop_proc()
{
	int LoopCtrl;
	int iTripCode=0;

	int cmd;
	double fReference;

	VariableInitialization();

	iTripCode = HardwareParameterVerification();
	if( iTripCode !=0 ) return iTripCode;

	iTripCode = SL_SPEED_CNTL_Parameter();        	// csk_debug
	if( iTripCode != 0)	return iTripCode;			// csk_debug

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
		get_command(& cmd ,&fReference);	// Command�� �Է� ���� 				
		monitorProc();

		if( cmd == CMD_START) reference_in = fReference;
		else if( cmd == CMD_STOP) reference_in = 0.0;

		switch( gMachineState )
		{
		case STATE_RUN:
			if(  cmd == CMD_STOP ){
				strncpy(MonitorMsg," INV GO STOP        ",20);
				reference_in = 0.0; gMachineState = STATE_GO_STOP;
			}
			else{ 
//				if( gfRunTime < 0.25 )	reference_out = 0.05;	// debug
				// else hyd_unit_proc( gMachineState, & reference_out);
				hyd_unit_proc( gMachineState, & reference_out);
			}
		case STATE_GO_STOP:
//---- �� �õ� 
			if( cmd == CMD_START ) {
									  //"01234567890123456789"	
				strncpy(MonitorMsg," INVERTER RUN       ",20);
				gMachineState = STATE_RUN;
				hyd_unit_proc( gMachineState, & reference_out);
			}				
			else if( fabs( reference_out ) < 0.005 ){
				strncpy(MonitorMsg," INVERTER READY     ",20);
				gMachineState = STATE_READY;
				LoopCtrl =0;
			}
			else{		// debug
				hyd_unit_proc(  gMachineState, & reference_out);
			}
			break;
		}
	}
	return iTripCode;
}

void hyd_unit_control()
{
	double 	IntegralLimit;
	
	wr_ref=wr_rat * reference_out;
	
	wr_CycleIndex++;
	wr_Cycle+=Ts;
	if (wr_CycleIndex>=wr_CntlPeriodIndex)
	{
		wr_err=wr_ref-wr;
		wr_ErrInt+=Ki_wr*wr_err*inv_P_pair*wr_Cycle;
		IntegralLimit=Kp_wr*fabs(K_Damp_wr*wr_ref-wr)*inv_P_pair + Is_DQ_max[QS];
		if (wr_ErrInt>IntegralLimit)	
			wr_ErrInt=IntegralLimit;
		else if (wr_ErrInt<-IntegralLimit)	
			wr_ErrInt=-IntegralLimit;

		// Q-�� ���� ���	
		Is_DQ_ref[QS]=Kp_wr*(K_Damp_wr*wr_ref-wr)*inv_P_pair+wr_ErrInt;
		
		// �ʱ� �ڼ������ÿ��� �ӵ�������� ���б⸦ ������� �ʴ´�.

		if (gfRunTime<0.05)		wr_ErrInt=0.0;
		
		wr_Cycle=0.0;
		wr_CycleIndex=0;
	}		
	// Q-�� ���� ��� => �������� ��������
	SL_VectCntl_SFRF();	
}
// end of hyd_unit.c
