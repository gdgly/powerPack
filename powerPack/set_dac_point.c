#include	<header.h>
#include	<extern.h>

#if USE_DAC_OUT

#define DAC_rpm				0
#define DAC_rpm_m			1
#define DAC_Freq_out		2
#define DAC_reference_in	3
#define DAC_reference_out	4
#define DAC_frequency		5

#define DAC_Te				6
#define DAC_Te_max			7
#define DAC_Te_ref			8
#define DAC_Vdc				9

#define DAC_I_a				10
#define DAC_I_b				11
#define DAC_I_c				12
#define DAC_Is_dq_d			13
#define DAC_Is_dq_q			14
#define DAC_Is_mag			15
#define DAC_Is_mag_rms		16
#define DAC_Is_DQ_D			17
#define DAC_Is_DQ_Q			18
#define DAC_Is_DQ_ref_D		19
#define DAC_Is_DQ_ref_Q		20
#define DAC_prev_I_QS		21
#define DAC_Is_DQ_ErrInt_D	22
#define DAC_Is_DQ_ErrInt_Q	23
#define DAC_Is_dq_ref_d		24
#define DAC_Is_dq_ref_q		25
#define DAC_Is_dq_ErrInt_d	26
#define DAC_Is_dq_ErrInt_q	27

#define DAC_Vs_a			30
#define DAC_Vs_b			31
#define DAC_Vs_c			32
#define DAC_Vs_abc_ref_a	33
#define DAC_Vs_abc_ref_b	34
#define DAC_Vs_abc_ref_c	35
#define DAC_Vs_dq_ref_d		36
#define DAC_Vs_dq_ref_q		37
#define DAC_Vs_dq_d			38
#define DAC_Vs_dq_q			39
#define DAC_Vo				40
#define DAC_Us_dq_d			41
#define DAC_Us_dq_q			42
#define DAC_Vs_DQ_D			43
#define DAC_Vs_DQ_Q			44
#define DAC_Vs_DQ_max_D		45
#define DAC_Vs_DQ_max_Q		46
#define DAC_Vs_DQ_ref_D		47
#define DAC_Vs_DQ_ref_Q		48
#define DAC_Vs_DQ_comp_D	49
#define DAC_Vs_DQ_comp_Q	50

#define DAC_we_in			51
#define DAC_we				52
#define DAC_we0				53
#define DAC_wr_m			54
#define DAC_wr_m0			55
#define DAC_wr				56
#define DAC_wr_ref			57
#define DAC_wr_ref0			58
#define DAC_wr_err			59
#define DAC_wr_ErrInt		60
#define DAC_w_sl			61
#define DAC_w_sl0			62

#define DAC_theta			65
#define DAC_theta_m			66
#define DAC_SineTheta		67
#define DAC_CosTheta		68

#define DAC_Fs_ref0			70
#define DAC_Fs_ref			71
#define DAC_Fs_dq_d			73
#define DAC_Fs_dq_q			74
#define DAC_Fs				75
#define DAC_Fs1				76
#define DAC_Fr_ref			77
#define DAC_Fr_ref0			78
#define DAC_Fr				79
#define DAC_Fr_Err			80
#define DAC_Fr_ErrInt		81

#define DAC_Vs_ref			82
#define DAC_Freq_ref		83
#define DAC_Freq_slip		84
#define DAC_Slip			85

#define DAC_Vs_IR_comp		86
#define DAC_del_Vs_comp		87

#define DAC_SinCosDeltaTheta	90
#define DAC_CosDeltaTheta		91
#define DAC_SinDeltaTheta		92

#define DAC_Delta_wr		93
#define DAC_I_DS0_0			94
#define DAC_I_DS0			95
#define DAC_I_DS_err		96
#define DAC_DeltaLambda		97
#define DAC_DeltaTheta		98

// 회전수 출력 
void set_dac_point()
{
	dac_point[DAC_rpm]= & rpm;
	dac_point[DAC_rpm_m]= & rpm_m;
//	dac_point[DAC_rpm_ref]= & rpm_ref;
//	dac_point[DAC_rpm_err]= & rpm_err;

	dac_point[DAC_Freq_out]= & Freq_out;

	dac_point[DAC_reference_in]= & reference_in;
	dac_point[DAC_reference_out]= & reference_out;

// 전류 
	dac_point[DAC_I_a]= & Is_abc[0];
	dac_point[DAC_I_b]= & Is_abc[1];
	dac_point[DAC_I_c]= & Is_abc[2];

	dac_point[DAC_Is_dq_d]= & Is_dq[0];
	dac_point[DAC_Is_dq_q]= & Is_dq[1];

	dac_point[DAC_Is_mag]= & Is_mag;
	dac_point[DAC_Is_mag_rms]= & Is_mag_rms;

	dac_point[DAC_Vdc]= & Vdc;	

// 각도 및 주파수

	dac_point[DAC_we_in]= & we_in;
	dac_point[DAC_we]= & we;
	dac_point[DAC_we0]= & we0;

	dac_point[DAC_frequency]= & frequency;

	dac_point[DAC_theta]= & theta;
	dac_point[DAC_theta_m]= & theta_m;		// 기계각

	dac_point[DAC_SineTheta]= & SinTheta;
	dac_point[DAC_CosTheta]= & CosTheta;
	dac_point[DAC_wr_m]= & wr_m;			// 엔코더로 부터 읽은 속도
	dac_point[DAC_wr_m0]= & wr_m0;			// 실제 속도의 필터링 값
	dac_point[DAC_wr]= & wr;
	dac_point[DAC_wr_ref]= & wr_ref;
	dac_point[DAC_wr_ref0]= & wr_ref0;
	dac_point[DAC_wr_err]= & wr_err;
	dac_point[DAC_wr_ErrInt]= & wr_ErrInt;
	dac_point[DAC_w_sl]= & w_sl;
	dac_point[DAC_w_sl0]= & w_sl0;


// 전류
	dac_point[DAC_Is_DQ_D]= & Is_DQ[0];
	dac_point[DAC_Is_DQ_Q]= & Is_DQ[1];

	dac_point[DAC_Is_DQ_ref_D]= & Is_DQ_ref[0];
	dac_point[DAC_Is_DQ_ref_Q]= & Is_DQ_ref[1];

	dac_point[DAC_prev_I_QS]= & prev_I_QS;				// --> 슬립 계산

	dac_point[DAC_Is_DQ_ErrInt_D]= & Is_DQ_ErrInt[0];
	dac_point[DAC_Is_DQ_ErrInt_Q]= & Is_DQ_ErrInt[1];

	dac_point[DAC_Is_dq_ref_d]= & Is_dq_ref[0];
	dac_point[DAC_Is_dq_ref_q]= & Is_dq_ref[1];

	dac_point[DAC_Is_dq_ErrInt_d]= & Is_dq_ErrInt[0];
	dac_point[DAC_Is_dq_ErrInt_q]= & Is_dq_ErrInt[1];

// 전압
	dac_point[DAC_Vs_a]= & Vs_abc[0];
	dac_point[DAC_Vs_b]= & Vs_abc[1];
	dac_point[DAC_Vs_c]= & Vs_abc[2];

	dac_point[DAC_Vs_abc_ref_a]= & Vs_abc_ref[0];
	dac_point[DAC_Vs_abc_ref_b]= & Vs_abc_ref[1];
	dac_point[DAC_Vs_abc_ref_c]= & Vs_abc_ref[2];

	dac_point[DAC_Vs_dq_ref_d]= & Vs_dq_ref[0];
	dac_point[DAC_Vs_dq_ref_q]= & Vs_dq_ref[1];

	dac_point[DAC_Vs_dq_d]= & Vs_dq[0];
	dac_point[DAC_Vs_dq_q]= & Vs_dq[1];

	dac_point[DAC_Vo]= & Vo;					// zero sequence

	dac_point[DAC_Us_dq_d]= & Us_dq[0];
	dac_point[DAC_Us_dq_q]= & Us_dq[1];

	dac_point[DAC_Vs_DQ_D]= & Vs_DQ[0];
	dac_point[DAC_Vs_DQ_Q]= & Vs_DQ[1];

	dac_point[DAC_Vs_DQ_max_D]= & Vs_DQ_max[0];
	dac_point[DAC_Vs_DQ_max_Q]= & Vs_DQ_max[1];
	
	dac_point[DAC_Vs_DQ_ref_D]= & Vs_DQ_ref[0];
	dac_point[DAC_Vs_DQ_ref_Q]= & Vs_DQ_ref[1];

	dac_point[DAC_Vs_DQ_comp_D]= & Vs_DQ_comp[0];
	dac_point[DAC_Vs_DQ_comp_Q]= & Vs_DQ_comp[1];

// 토크
	dac_point[DAC_Te_max]= & Te_max;
	dac_point[DAC_Te_ref]= & Te_ref;
	dac_point[DAC_Te]= & Te;

// Flux
	dac_point[DAC_Fs_ref0]= & Fs_ref0;
	dac_point[DAC_Fs_ref]= & Fs_ref;
//	dac_point[DAC_inv_Fs_ref]= & inv_Fs_ref;
	dac_point[DAC_Fs_dq_d]= & Fs_dq[0];
	dac_point[DAC_Fs_dq_q]= & Fs_dq[1];

	dac_point[DAC_Fs]= & Fs;
	dac_point[DAC_Fs1]= & Fs1;

	dac_point[DAC_Fr_ref]= & Fr_ref;
	dac_point[DAC_Fr_ref0]= & Fr_ref0;

	dac_point[DAC_Fr]= & Fr;
	dac_point[DAC_Fr_Err]= & Fr_Err;
	dac_point[DAC_Fr_ErrInt]= & Fr_ErrInt;

// VVVF-Control
	dac_point[DAC_Vs_ref]= & Vs_ref;
	dac_point[DAC_Freq_ref]= & Freq_ref;
	dac_point[DAC_Freq_slip]= & Freq_slip;
	dac_point[DAC_Slip]= & Slip;
//	dac_point[DAC_Power_core]= & Power_core;
//	dac_point[DAC_Power_core_rat]= & Power_core_rat;
//	dac_point[DAC_Power_gap]= & Power_gap;
	dac_point[DAC_Vs_IR_comp]= & Vs_IR_comp;
	dac_point[DAC_del_Vs_comp]= & del_Vs_comp;

// 센스리스 벡터제어

	dac_point[DAC_Delta_wr]= & Delta_wr;
	dac_point[DAC_I_DS0_0]= & I_DS0_0;
	dac_point[DAC_I_DS0]= & I_DS0;
	dac_point[DAC_I_DS_err]= & I_DS_err;
	dac_point[DAC_DeltaLambda]= & DeltaLambda;
	dac_point[DAC_DeltaTheta]= & DeltaTheta;
	dac_point[DAC_SinCosDeltaTheta]= & SinCosDeltaTheta;
	dac_point[DAC_CosDeltaTheta]= & CosDeltaTheta;
	dac_point[DAC_SinDeltaTheta]= & SinDeltaTheta;
}
#endif

