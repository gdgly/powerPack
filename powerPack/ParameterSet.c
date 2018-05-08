#include	<header.h>
#include	<extern.h>

void VariableInitialization()
{
#if MAIN_POWER_ON
	double x1,x2,y1,y2;

	x1 = adc_vdc_100;		y1 = 100.0;
	x2 = adc_vdc_300;		y2 = 300.0;

//	Vdc =  linear_eq(x1,x2,y1,y2,fTemp1);
//	y = (( y2-y1) / ( x2 - x1 )) * x  + (( y1 * x2 - y2 * x1 )/ (x2- x1));

	Vdc_factor = ( y2-y1) / ( x2 - x1 );
	Vdc_calc_offset = (( y1 * x2 - y2 * x1 )/ (x2- x1));
#endif 

	C_ce_nF=(3.5-0.8)/(1000.0-100.0)*(2.0*Is_rat-100.0)+0.8;	// 1000A -> 3.5nF, 100A -> 0.8nF
	C_ce=1.0e-9*C_ce_nF;
	inv_C_ce=1.0/C_ce;

	// 시간 및 인덱스
	gfRunTime=0.0;
	wr_Cycle=0.0;
	wr_CycleIndex=0;

	// reference
	reference0=0.0;
	reference1=0.0;
	reference_in=0.0;
	reference_out=0.0;	// new
	
	// 각도, 주파수, 속도
	we_in=0.0;
	we=0.0;
	we0=0.0;
	frequency=0.0;
	theta=0.0;
	SinTheta=0.0;
	CosTheta=1.0;
	CosDeltaTheta=0.0;
	SinDeltaTheta=1.0;

	wr_m0=0.0;
	wr_m=0.0;				// 실제 속도의 필터링 초기값 = 실제 속도 
	wr=0.0;
	wr_ref=0.0;
	wr_ref=0.0;
	wr_err=0.0;
	wr_ErrInt=0.0;				// 속도제어기의 적분량 
	w_sl=0.0;
	w_sl0=0.0;
	rpm=0.0;
	rpm_m=0.0;
	theta_m=0.0;
	rpm_ref=0.0;
	rpm_err=0.0;
	
	// 전류
	Is_dq[ds]=Is_dq[qs]=0.0;
	Is_mag=0.0;
	Is_mag_rms=0.0;
	sgn_Is[as]=sgn_Is[bs]=sgn_Is[cs]=0.0;
	
	Is_DQ[DS]=Is_DQ[QS]=0.0;
	Is_DQ_max[DS]=Is_DQ_max[QS]=0.0;
	Is_DQ_ref[DS]=Is_DQ_ref[QS]=0.0;
	
	prev_I_QS=0.0;
	
	Is_DQ_ErrInt[DS]=Is_DQ_ErrInt[QS]=0.0;			// 전류제어기의 적분량
	
	// 전압
	Vs_max=0.0;	
	Vs_abc[as]=Vs_abc[bs]=Vs_abc[cs]=0.0;
	Vs_abc_ref[as]=Vs_abc_ref[bs]=Vs_abc_ref[cs]=0.0;
	Vs_dq_ref[ds]=Vs_dq_ref[qs]=0.0;
	Vs_dq[ds]=Vs_dq[qs]=0.0;
	Vo=0.0;			
	Us_dq[ds]=Us_dq[qs]=0.0;
	Vs_DQ[DS]=Vs_DQ[QS]=0.0;
	Vs_DQ_max[DS]=Vs_DQ_max[QS]=0.0;
	Vs_DQ_ref[DS]=Vs_DQ_ref[QS]=0.0;
	Vs_DQ_comp[DS]=Vs_DQ_comp[QS]=0.0;
	Vs_max_FW=0.0;
	Vs_DQ_ref_P[DS]=Vs_DQ_ref_P[QS]=0.0;
	Vs_DQ_ref_PI[DS]=Vs_DQ_ref_PI[QS]=0.0;
	
	// 토크
	Te_max=0.0;
	Te_ref=0.0;
	Te=0.0;
	
	// 자속
	Fs_ref0=0.0;
	Fs_ref=0.0;
	inv_Fs_ref=0.0;
	Fs_dq[ds]=Fs_dq[qs]=0.0;
	Fs=0.0;
	inv_Fs=0.0;
	Fr_ref=0.0;
	Fr_ref0=0.0;
	inv_Fr_ref=0.0;
	Fr=0.0;
	inv_Fr=0.0;
	Fr_Err=0.0;
	Fr_ErrInt=0.0;
	
	// VVVF-Control
	Vs_ref=0.0;
	Freq_ref=0.0;
	Freq_slip=0.0;
	Freq_out=0.0;
	Slip=0.0;
	Power_core=0.0;
	Power_core_rat=0.0;
	Power_gap=0.0;
	Vs_IR_comp=0.0;
	del_Vs_comp=0.0;
	
	// 센스리스 벡터제어
	Pf=0.0;
	sgn_I_QS=0.0;
	Delta_wr=0.0;
	I_DS0_0=0.0;
	I_DS0=0.0;
	I_DS_err=0.0;
	
	// 오토튜닝
	GainUpdateTimer=0.0;
	AutoTuningFlag=0;
	LPF_Is_Square=0.0;
	LPF_Is=0.0;
	LPF_Re_Power=0.0;
	LPF_Vs_Square=0.0;
	Vs_Coeff_Leq_Req=0.0;
	Is_dq_ref[ds]=Is_dq_ref[qs]=0.0;
	Is_dq_ErrInt[ds]=Is_dq_ErrInt[qs]=0.0;

	Freq_set=0.0;
	Re_Power=0.0;
	Im_Power=0.0;
	ref_time = 0.0; //new		
}	

//-----------------------------------
//  End of ParameterSect.c
//-----------------------------------

