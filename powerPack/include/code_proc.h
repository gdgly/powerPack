#ifndef		__CODE_PROC_H_
#define		__CODE_PROC_H_	

// #define SWITCH_FREQ			2500	// 090920
// #define SWITCH_FREQ			1750	// 090920

#define TYPE_INTEGER		0
#define TYPE_DOUBLE			1

#define CODE_GROUP0_END		58
#define CODE_GROUP1_END		115		// 2009.12.31
#define CODE_GROUP2_END		226
#define CODE_GROUP3_END		312
#define CODE_GROUP4_END		413
#define CODE_GROUP5_END		512
#define CODE_GROUP6_END		629
#define CODE_GROUP7_END		730
#define CODE_GROUP8_END		807


//======================================
// Code address
//======================================
// group 0

#define CODE_run_input_select			0
#define CODE_motor_ctrl_mode			1
#define CODE_motor_direction_change		2
#define CODE_ramp_func_mode				3

#define CODE_accel_time1				10
#define CODE_decel_time1				11
#define CODE_accel_time2				12
#define CODE_decel_time2				13
#define CODE_btn_start_ref				14
#define CODE_jog_speed					15
#define CODE_min_vf_ref					16
#define CODE_use_binary_input			17

#define CODE_digital_speed1				21
#define CODE_digital_speed2				22
#define CODE_digital_speed3				23
#define CODE_digital_speed4				24
#define CODE_digital_speed5				25
#define CODE_digital_speed6				26
#define CODE_digital_speed7				27
#define CODE_digital_speed8				28
#define CODE_digital_speed9				29
#define CODE_digital_speed10			30
#define CODE_digital_speed11			31
#define CODE_digital_speed12			32
#define CODE_digital_speed13			33
#define CODE_digital_speed14			34
#define CODE_digital_speed15			35
#define CODE_digital_speed16			36

#define CODE_input_func_select0			40
#define CODE_input_func_select1			41
#define CODE_input_func_select2			42
#define CODE_input_func_select3			43
#define CODE_input_func_select4			44
#define CODE_input_func_select5			45
#define CODE_input_func_select6			46
#define CODE_input_func_select7			47
//#define CODE_input_func_select8			48

#define CODE_digital_out_function0		50
#define CODE_digital_out_function1		51
#define CODE_digital_out_function2		52
#define CODE_digital_out_function3		53
#define CODE_digital_out_function4		54
#define CODE_digital_out_function5		55
#define CODE_digital_out_function6		56
#define CODE_digital_out_function7		57

// group 1

#define CODE_brake_on_up_ref			100
#define CODE_brake_on_down_ref			101
#define CODE_brake_off_up_ref			102
#define CODE_brake_off_down_ref			103
#define CODE_brake_on_delay_time		104
#define CODE_brake_off_dealy_time		105
#define CODE_brake_torq_boost_time		106

#define CODE_hyd_sensor_set_ref			110
#define CODE_hyd_high_speed_on_ratio	111
#define CODE_hyd_idle_ref				112
#define CODE_hyd_max_ref				113
#define CODE_hyd_decel_time				114

// group2

#define CODE_analog_cmd_in_zero1		200
#define CODE_analog_cmd_in_span1		201
#define CODE_analog_cmd_in_zero2		202
#define CODE_analog_cmd_in_span2		203
#define CODE_analog_out_select1			204
#define CODE_analog_out_zero1			205
#define CODE_analog_out_span1			206
#define CODE_analog_out_offset1			207
#define CODE_analog_out_select2			208
#define CODE_analog_out_zero2			209
#define CODE_analog_out_span2			210
#define CODE_analog_out_offset2			211

#define CODE_dac_ch0_select				213
#define CODE_dac_ch0_max				214
#define CODE_dac_ch0_offset				215

#define CODE_dac_ch1_select				216
#define CODE_dac_ch1_max				217
#define CODE_dac_ch1_offset				218

#define CODE_dac_ch2_select				220
#define CODE_dac_ch2_max				221
#define CODE_dac_ch2_offset				222

#define CODE_dac_ch3_select				223
#define CODE_dac_ch3_max				224
#define CODE_dac_ch3_offset				225



// group3
#define CODE_over_current_level			300
#define CODE_over_volt_set				301
#define CODE_under_volt_set				302
#define CODE_over_speed_level			303
#define CODE_e_thermal_level			304
#define CODE_pre_charge_time			305
#define CODE_Is_Max_Coeff				306
#define CODE_over_I_time				307

#define CODE_adc_vdc_100				310	// 2010.01.09
#define CODE_adc_vdc_300				311

//group 4
#define CODE_motor_rate_power			400
#define CODE_motor_rate_volt			401
#define CODE_motor_rate_current			402
#define CODE_motor_rate_hz				403
#define CODE_motor_rate_rpm				404
#define CODE_motor_pole					405
#define CODE_motor_rate_effiency		406	

#define CODE_Rs							407
#define CODE_Rr							408
#define CODE_Ls							409
#define CODE_Lr							410
#define CODE_Lm							411
#define CODE_Jm							412

// group5
#define CODE_I_sense_value				500
#define CODE_u_phase_I_sense_zero		501
#define CODE_u_phase_I_sense_span		502
#define CODE_v_phase_I_sense_zero		503
#define CODE_v_phase_I_sense_span		504
#define CODE_vdc_sense_zero				505
#define CODE_vdc_sense_span				506
#define CODE_encoder_pulse_one_turn		507
#define CODE_igbt_pwm_freq				508

#define CODE_adc_u_offset				510
#define CODE_adc_v_offset				511

// group6
#define CODE_VF_DeadTimeGain			600
#define CODE_VF_ExcitationTime			601
#define CODE_VF_Fs_Coeff				602
#define CODE_VF_Freq_TrqBoost			603
#define CODE_VF_Vs_Coeff_TrqBoost		604
#define CODE_VF_Rs_ThermalCoeff			605
#define CODE_VF_IR_Comp_FilterPole		606
#define CODE_VF_Slip_Comp_FilterPole	607
#define CODE_VF_Rs						608

#define CODE_AT_Freq_Leq_Req			610
#define CODE_AT_Time_Leq_Req			611
#define CODE_AT_Is_Coeff_Leq_Req		612

#define CODE_AT_Is_Coeff_Rs				613
#define CODE_AT_Time_Rs					614

#define CODE_AT_DeadTimeGain			615
#define CODE_AT_Ls_Vs_RAMP				616
#define CODE_AT_Freq_Ls					617
#define CODE_AT_Time_Ls					618
#define CODE_AT_Ls_DMB_OpenTime			619				

#define CODE_AT_Te_Coeff_Jm				620
#define CODE_AT_Time_Jm					621
#define CODE_Jm_ID_ENABLE				622

#define CODE_posi_duration_time			624	
#define CODE_zero_duration_time			625
#define CODE_nega_duration_time			626
#define CODE_test_accel_time			627	
#define CODE_test_decel_time			628

// group 7 advance control vaiable 

#define	CODE_wr_FilterPoleCoeff				700
#define	CODE_wn_wr_Coeff					701
#define	CODE_Max_wn_wr						702
#define	CODE_K_Damp_wr						703
#define	CODE_wr_DampingRatio				704
#define CODE_wr_CntlPeriodIndex				705
// 자속 제어
#define	CODE_FW_VoltageCoeff				706
#define	CODE_Base_Flux_Coeff				707
#define	CODE_ExcitationTime					708
#define	CODE_K_Damp_Fr						709
#define	CODE_GM_Fr							710
#define	CODE_PM_Fr							711

#define	CODE_K_Damp_Is						715
#define	CODE_GM_Is							716
#define	CODE_PM_Is							717

// 센스리스 벡터 제어
#define	CODE_Default_wr_FilterPole			720
#define	CODE_SlipCompCoeff					721
#define	CODE_GammaLambda					722
#define	CODE_GammaLambda_R_Constant			723	
#define	CODE_Max_DeltaLambda				724
#define	CODE_GammaTheta_M					725
#define	CODE_GammaTheta_R					726
#define	CODE_Max_DeltaTheta					727
#define	CODE_Delta_wr_FilterPoleCoeff_L		728
#define	CODE_Delta_wr_FilterPoleCoeff_U		729

#define CODE_Data_Check						800
#define CODE_Data_Backup					801
#define CODE_Data_Load						802
#define CODE_Data_Init						803
#define CODE_get_adc_offset					804

#define CODE_get_adc_vdc_100				805
#define CODE_get_adc_vdc_300				806

//--- end of code address


union CODE_MIN{
	int 	ints;
	double 	doubles;
};

union CODE_MAX {
	int 	ints;
	double 	doubles;
};

union CODE_DEFAULT {
	int 	ints;
	double 	doubles;
};

union CODE_VALUE {
	int 	ints;
	double 	doubles;
};

struct CODE_INFO_DEFINE {
	int		type;	
	int	  	open_level	;
	union CODE_MIN 		code_min ;
	union CODE_MAX 		code_max ;
	union CODE_DEFAULT 	code_default;
	union CODE_VALUE	code_value;
	char   disp[40];
};
typedef struct CODE_INFO_DEFINE CODE_INFO;

#endif
