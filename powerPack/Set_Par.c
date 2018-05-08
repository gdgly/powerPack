#include	<header.h>
#include	<extern.h>

int HardwareParameterVerification()
{
	if ( motor_rate_power >(0.99*sqrt(3.0) * motor_rate_volt * motor_rate_current)){
		trip_recording( CODE_motor_rate_power, motor_rate_power,"POWER FACTOR OVER");
		return	CODE_motor_rate_power;
	}	
	// ������ 20%���Ϸ� �����Ǿ��� ��� 
	if (motor_rate_power<(0.2*sqrt(3.0)*motor_rate_volt*motor_rate_current)){
		trip_recording( CODE_motor_rate_power, motor_rate_power,"POWER FACTOR UNDER");
		return	CODE_motor_rate_power;
	}
	// ���� ������ 15%�̻����� ������ ��� : ��ü�� 2% 
	if (motor_rate_rpm < (0.85*120.0 * motor_rate_hz / motor_pole)){
		trip_recording( CODE_motor_rate_rpm, motor_rate_rpm,"RATE RPM UNDER");
		return	CODE_motor_rate_rpm;
	}
	Vs_rat=sqrt(2.0)/sqrt(3.0)*motor_rate_volt;			// �������� ��ũ ��

	Is_rat=sqrt(2.0)*motor_rate_current;

	inv_Is_rat=1.0/Is_rat;
	Freq_rat = motor_rate_hz;
	we_rat=PI_2*Freq_rat;

	inv_Freq_rat=1.0/Freq_rat;

	inv_motor_rate_hz = 1.0 / motor_rate_hz; //   csk_check 2009.10.30
	wr_rat=PI_2*motor_pole*motor_rate_rpm/120.0;			// rpm -> rad/sec
	wm_rat=wr_rat*(2.0/motor_pole);
	Te_rat=motor_rate_power/wm_rat;

	inv_Te_rat=1.0/Te_rat;
	Fs_rat=Vs_rat/we_rat;

	Kt=(3.0/2.0)*(motor_pole/2.0);
	inv_Kt=1.0/Kt;
	P_pair=(motor_pole/2.0);
	inv_P_pair=1.0/P_pair;
	rpm_Coeff=60.0*inv_P_pair/PI_2;				// ȸ����/��
	
	// V/F ������ ���� ����
	S_rat=(we_rat-wr_rat)/we_rat;
	S_lin=(motor_pole/PI)*(S_rat*Freq_rat)/Te_rat;				// ==> V/f ���� : ���� ����
	Freq_slip_rat=S_rat*Freq_rat;

	//-------------------------------------------------
	inv_Ts = igbt_pwm_freq;
	Ts = 1.0 / igbt_pwm_freq;	// debug

	Is_max = Is_rat * Is_Max_Coeff ;	// added 2009.11.01	
	OverCurLimit = Is_max *2;			// added 2009.11.01  _debug

	return	0;	
}	

//**************************************

#if USE_ROM_TEST
// V/F��� �ʿ��� �Ķ����
int VF_Cntl_Parameter()
{
	if ( (VF_DeadTimeGain<0.0) || (VF_DeadTimeGain>2.0) )
		return	CODE_VF_DeadTimeGain;
	if ( (VF_ExcitationTime<0.0) ||(VF_ExcitationTime>3.5) ) 
		return	CODE_VF_ExcitationTime;
	if ( (VF_Fs_Coeff<0.3) || (VF_Fs_Coeff>3.0) )
		return	CODE_VF_Fs_Coeff;
	if ( (VF_Freq_TrqBoost<0.0) || (VF_Freq_TrqBoost>10.0) )
		return	CODE_VF_Freq_TrqBoost;	
	if ( (VF_Vs_Coeff_TrqBoost<0.0) || (VF_Vs_Coeff_TrqBoost>0.2) )
		return	CODE_VF_Vs_Coeff_TrqBoost;
	if ( (VF_Rs_ThermalCoeff<0.8) || (VF_Rs_ThermalCoeff>3.0) )
		return	CODE_VF_Rs_ThermalCoeff;
	if ( (VF_IR_Comp_FilterPole<5.0) || (VF_IR_Comp_FilterPole>1000.0) )
		return	CODE_VF_IR_Comp_FilterPole;
	if  ( (VF_Slip_Comp_FilterPole<5.0) || (VF_Slip_Comp_FilterPole>1000.0) )	 
		return	CODE_VF_Slip_Comp_FilterPole;
	if ( (VF_Rs<0.0) || (VF_Rs>50.0) )
		return	CODE_VF_Rs;
	
	// �Ķ���� ������ ����.
	return	0;
}	
#endif

#if VECTOR_TEST

int COMMON_VECT_CNTL_ParameterVerification()
{
	double	In;			// ������ ���� ���

	// ���� �Ķ���� ����
	if ( (Rs<2.0e-3) || (Rs>20.0) )				return	CODE_Rs;
	if ( (Rr<2.0e-3) || (Rr>20.0) )				return	CODE_Rr;
	if ( (Ls<2.0e-3) || (Ls>1.0) )				return	CODE_Ls;
	if ( (Lr<2.0e-3) || (Lr>1.0) )				return	CODE_Lr;
	if ( (Lm<2.0e-3) || (Lm>1.0) )				return	CODE_Lm;
	if ( (Lm>(0.985*Ls)) || (Lm>(0.985*Lr)) )	return	CODE_Lm;

	// ������ ������ ���������� 10% ~ 80%�� �ƴ� ���	
	In=Vs_rat/(we_rat*Ls);								// ������ ���� ���	
	if ( (In<(0.1*Is_rat)) || (In>(0.8*Is_rat))) return	CODE_Ls;			
	if ( (Lr<(0.9*Ls)) || (Lr>(1.1*Ls)) )		return	CODE_Lr;
	
	// ������ 
	Tr=Lr/Rr;
	if ( (Tr<0.02) || (Tr>2.0) )						// ������ : 0.02 ~ 2.0��
		return	ERR_Tr_Over;
	
	// ������ ����
	if ( (Rs<(0.5*Rr)) || (Rs>(20.0*Rr)) )
		return	CODE_Rs;
	
	// ���� �δ��Ͻ��� ����
	sigma_Ls=Ls-(Lm*Lm)/Lr;
	sigma=sigma_Ls/Ls;
	if (sigma<0.02) 
			return	ERR_sigma_Under;					// �����ڼ��� �۰� ������ ���
	else if (sigma>0.2)
			return	ERR_sigma_Over;						// �����ڼ��� ũ�� ������ ���
	
	// ��Ÿ �Ķ���� ���
	inv_Tr=1.0/Tr;
	inv_Ls=1.0/Ls;
//	inv_Lm=1.0/Lm;
	SlipCoeff=Ls/Tr;
	sigma_Tr=sigma*Tr;
	inv_sigma_Tr=1.0/sigma_Tr;
	sigma_minus_1_div_sigma_Ls=(sigma-1.0)/sigma_Ls;
	inv_sigma_Ls=1.0/sigma_Ls;
	inv_Ls_plus_sigma_Ls=1.0/(sigma_Ls+Ls);				// ���� ���Ѱ� ���
	sigma_Ls_div_1_plus_sigma=sigma_Ls/(1.0+sigma);		// ���� ���Ѱ� ���
	Lm_div_Lr=Lm/Lr;
	Lr_div_Lm=Lr/Lm;
	
	// ���������
	if ( (K_Damp_Is<0.1) || (K_Damp_Is>1.0) )				return	CODE_K_Damp_Is;
	if ( (PM_Is<(PI/20.0)) || (PM_Is>(5.0*PI/12.0)) )		return	CODE_PM_Is;
	if ( (GM_Is<2.5) || (GM_Is>10.0) )						return	CODE_GM_Is;	
	
	// ���� ����� ���� 
	inv_GM_Is_square_minus_1=1.0/(GM_Is*GM_Is-1.0);			// 1.0/(GM*GM-1.0)						
	inv_GM_Is=1.0/GM_Is;		
	wp_Is_Coeff=(GM_Is*PM_Is+PI_1_2*GM_Is*(GM_Is-1.0))*inv_GM_Is_square_minus_1;
	Kp_Is_Coeff=sigma_Ls*inv_GM_Is;

	wp_Is=wp_Is_Coeff*inv_Ts;					// Td_Is=Ts
	Kp_Is=Kp_Is_Coeff*wp_Is;
	Ki_Is=Kp_Is*(2.0*wp_Is-inv_PI_1_4*wp_Is*wp_Is*Ts+(Rs+Rr)*inv_sigma_Ls);

	if (Ki_Is<=10.0)					return	ERR_Ki_Is_Under;			// ��������� ���� ����
	if (Kp_Is>Ki_Is)					return	ERR_Kp_Is_Over;
	else if (Kp_Is<0.0)					return	ERR_Kp_Is_Under;
				
	// �Ķ���� ������ ����.
	return	0;	
}	


//**********************************************************


// �������� ������� �ʿ��� �Ķ���� �̸�,
// �������� ��ũ���� �� �ӵ������ �Ķ���Ϳ��� �������� ���ȴ�.
int COMMON_SL_VECT_CNTL_ParameterVerification()
{
	int ErrCode;
	
	// �������� ������� �ʿ��� �Ķ���͸� �а� �����Ѵ�.
	ErrCode=COMMON_VECT_CNTL_ParameterVerification();	

	if (ErrCode!=0)				return	ErrCode;		
		
	// �������� ���� ����
	if ( (Default_wr_FilterPole<20.0) || (Default_wr_FilterPole>500.0) ) return	CODE_Default_wr_FilterPole;
	if ( (SlipCompCoeff<0.0) || (SlipCompCoeff>1.0) )					 return	CODE_SlipCompCoeff;
	if ( (GammaLambda<0.0) || (GammaLambda>2.0) )						 return	CODE_GammaLambda;
	if (GammaLambda_R_Constant<3.0)										return	CODE_GammaLambda_R_Constant;
	if ( (Max_DeltaLambda<0.0) || (Max_DeltaLambda>0.2) )				return	CODE_Max_DeltaLambda;
	if ( (GammaTheta_M<0.0) || (GammaTheta_M>1.0) )						return	CODE_GammaTheta_M;
	if ( (GammaTheta_R<0.0) || (GammaTheta_R>3.0) )					return	CODE_GammaTheta_R;
	if ( (Max_DeltaTheta<0.0) || (Max_DeltaTheta>0.05) )			return	CODE_Max_DeltaTheta;
	
	if ( (Delta_wr_FilterPoleCoeff_L<0.1) || (Delta_wr_FilterPoleCoeff_L>20.0) )
		return	CODE_Delta_wr_FilterPoleCoeff_L;
	
	if ( (Delta_wr_FilterPoleCoeff_U<0.1) || (Delta_wr_FilterPoleCoeff_U>20.0) )
		return	CODE_Delta_wr_FilterPoleCoeff_U;
	if ( (FW_VoltageCoeff<0.2) || (FW_VoltageCoeff>1.2) )			// ����� ���� ���� ���	
		return	CODE_FW_VoltageCoeff;
	if ( (Base_Flux_Coeff<0.1) || (Base_Flux_Coeff>2.5) )			// Base Flux < 250%
		return	CODE_Base_Flux_Coeff;
	if ( (ExcitationTime<0.1) || (ExcitationTime>3.0) )	
		return	CODE_ExcitationTime;
			
	Fs_B=Base_Flux_Coeff*Fs_rat;
	inv_Fs_B=1.0/Fs_B;	
	Fs_ref=Fs_B;	
 // 	HalfExcitationTime=0.5*ExcitationTime;
	
	// �ӵ� ���� �� ����/�ڼ�/�ӵ� ���� ���� �Ķ����
	I_QS_rat=(2.0/3.0)*inv_P_pair*Te_rat/Fs_B;
//	inv_I_QS_rat=1.0/I_QS_rat;
	inv_Te_rat=1.0/Te_rat;
	
	wr_FilterPole=Default_wr_FilterPole;				// �ӵ� �������� ���� ��
	wn_wr=wr_FilterPole/10.0;							// �ӵ��� �뿪���� ���� ���� 1/10�� ����
	if (wn_wr>Max_wn_wr)	wn_wr=Max_wn_wr;			// max_wn_wr*10.0 ==> measurement noise cutoff frequency
	
	
	// �Ķ���� ������ ����.
	return	0;	
}	


// �������� ��ũ��� �ʿ��� �Ķ����
int SL_TORQUE_CNTL_Parameter()
{
	int ErrCode;
	
	// �������� ������� �ʿ��� �Ķ���͸� �а� �����Ѵ�.
	ErrCode=COMMON_SL_VECT_CNTL_ParameterVerification();
	if (ErrCode!=0)
		return	ErrCode;
	
	// ��ũ ��� �ʿ��� �Ķ����
	wr_FilterPole=Default_wr_FilterPole;			// ��ũ������� ����Ʈ ���� �����, �ӵ������忡���� �ٸ� ���� ���
	
	// �Ķ���� ������ ����.
	return	0;
}

	
// �������� �ӵ���� �ʿ��� �Ķ����	
int SL_SPEED_CNTL_Parameter()	
{
	int ErrCode;
	
	// �������� ������� �ʿ��� �Ķ���͸� �а� �����Ѵ�.
	ErrCode=COMMON_SL_VECT_CNTL_ParameterVerification();
	if (ErrCode!=0)
		return	ErrCode;
		
	// �ӵ������	
	if ( (wr_CntlPeriodIndex<1) || (wr_CntlPeriodIndex>30) )
		return	CODE_wr_CntlPeriodIndex;	
		
	if ( (K_Damp_wr<0.05) || (K_Damp_wr>1.0) )
		return	CODE_K_Damp_wr;
	
	if ( (wr_DampingRatio<0.6) || (wr_DampingRatio>1.5) )
		return	CODE_wr_DampingRatio;
		
	if ( (wr_FilterPoleCoeff<5.0) || (wr_FilterPoleCoeff>30.0) )
		return	CODE_wr_FilterPoleCoeff;	
		
	if ( (wn_wr_Coeff<2.0) || (wn_wr_Coeff>30.0) )
		return	CODE_wn_wr_Coeff;
		
	if ( (Max_wn_wr<(2.0*PI*0.5)) || (Max_wn_wr>(2.0*PI*10.0)) )
		return	CODE_Max_wn_wr;
		
	if ( (Jm<0.0001) || (Jm>100.0) )
		return	CODE_Jm;	
	
	//  �ӵ������ ����
	I_QS_rat=(2.0/3.0)*inv_P_pair*Te_rat/Fs_rat;
//	inv_I_QS_rat=1.0/I_QS_rat;
	inv_Te_rat=1.0/Te_rat;
	
	wn_wr=wn_wr_Coeff*( (P_pair*Te_rat/wr_rat)/Jm );	// speed rising time=(P/2.0)*(Te_rat/wr_rat)/Jm				
	if (wn_wr>Max_wn_wr)	wn_wr=Max_wn_wr;	// max_wn_wr*10.0 ==> measurement noise cutoff frequency

	wr_FilterPole=wr_FilterPoleCoeff*wn_wr;			// �ӵ� �������� ���� ��
	Kp_wr=(Jm*2.0*wr_DampingRatio*wn_wr)*(inv_Kt/Fs_B);
	Ki_wr=(Jm*wn_wr*wn_wr)*(inv_Kt/Fs_B);
	
	// �Ķ���� ������ ����.
	return	0;
}
#endif
	
	
#if AUTO_TUNING_TEST	
// ����Ʃ�׸�忡�� ���Ǵ� �Ķ����
int AUTO_TUNING_Parameter()
{
	// �������� �Ķ����
	if ( (Base_Flux_Coeff<0.3) || (Base_Flux_Coeff>3.0) )				// ����� ���� �ڼ� ����
		return	CODE_Base_Flux_Coeff;
	
	// V/F ��� �Ķ���Ͱ� �ʿ��ϹǷ� �Ķ���� ������ ����Ǿ�� �Ѵ�.
	if ( (VF_Freq_TrqBoost<0.0) || (VF_Freq_TrqBoost>10.0) )
		return	CODE_VF_Freq_TrqBoost;	
	if ( (VF_Vs_Coeff_TrqBoost<0.0) || (VF_Vs_Coeff_TrqBoost>0.2) )
		return	CODE_VF_Vs_Coeff_TrqBoost;
	if ( (VF_Rs_ThermalCoeff<0.8) || (VF_Rs_ThermalCoeff>3.0) )
		return	CODE_VF_Rs_ThermalCoeff;
	if ( (VF_IR_Comp_FilterPole<5.0) || (VF_IR_Comp_FilterPole>1000.0) )
		return	CODE_VF_IR_Comp_FilterPole;
	if  ( (VF_Slip_Comp_FilterPole<5.0) || (VF_Slip_Comp_FilterPole>1000.0) )	 
		return	CODE_VF_Slip_Comp_FilterPole;	
		
	//-------------------------------------------------------------------------
	
	if ( (AT_Freq_Leq_Req<5.0) || (AT_Freq_Leq_Req>60.0) )
		return	CODE_AT_Freq_Leq_Req;
	if ( (AT_Time_Leq_Req<2.5) || (AT_Time_Leq_Req>30.0) )
		return	CODE_AT_Time_Leq_Req;
	if ( (AT_Is_Coeff_Leq_Req<0.4) || (AT_Is_Coeff_Leq_Req>Is_Max_Coeff) )
		return	CODE_AT_Is_Coeff_Leq_Req;
		
	if ( (AT_Is_Coeff_Rs<0.4) || (AT_Is_Coeff_Rs>Is_Max_Coeff) )
		return	CODE_AT_Is_Coeff_Rs;
	if ( (AT_Time_Rs<2.0) || (AT_Time_Rs>30.0) )
		return	CODE_AT_Time_Rs;
	
	if ( (AT_DeadTimeGain<0.0) || (AT_DeadTimeGain>1.2) )
		return	CODE_AT_DeadTimeGain;	
	if ( (AT_Ls_Vs_RAMP<0.5) || (AT_Ls_Vs_RAMP>5.0) )
		return	CODE_AT_Ls_Vs_RAMP;
	if ( (AT_Freq_Ls<1.5) || (AT_Freq_Ls>10.0) )				
		return	CODE_AT_Freq_Ls;
	if ( (AT_Time_Ls<4.0) || (AT_Time_Ls>30.0) )
		return	 CODE_AT_Time_Ls;	
	if ( (AT_Ls_DMB_OpenTime<0.0) || (AT_Ls_DMB_OpenTime>2.0) )
		return	CODE_AT_Ls_DMB_OpenTime;
	
	if ( (AT_Te_Coeff_Jm<0.2) || (AT_Te_Coeff_Jm>1.0) )
		return	CODE_AT_Te_Coeff_Jm;
	if ( (AT_Time_Jm<0.249) || (AT_Time_Jm>2.0) )
		return	CODE_AT_Time_Jm;	
	
	
	// ���������
	if ( (K_Damp_Is<0.1) || (K_Damp_Is>1.01) )
		return	CODE_K_Damp_Is;
	if ( (PM_Is<(PI/20.0)) || (PM_Is>(5.0*PI/12.0)) )
		return	CODE_PM_Is;
	if ( (GM_Is<2.5) || (GM_Is>10.0) )
		return	CODE_GM_Is;	
	
	if ( (Jm_ID_ENABLE<0) || (Jm_ID_ENABLE>1) )
		return	CODE_Jm_ID_ENABLE;
	
	// �Ķ���� ������ ����.
	return	0;	
}		

#endif

