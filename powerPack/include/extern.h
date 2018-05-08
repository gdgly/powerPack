#ifndef		__VARIABLES_
#define		__VARIABLES_

extern double rmsIu;
extern double lpfVdc;

extern unsigned int adcIu;
extern unsigned int adcIv;

extern unsigned int adcIgbtTemperature;

// global.h

extern Uint32 warning_timer_msec;

extern unsigned int xcon_data;		// expansion board xcon0,1,2,3 out data
extern int digit_position;
extern int button_input_state;
extern int fnd_buf[4];
extern int led_state_flag;
extern int fnd_blink_flag;
extern int warning_fnd_flag;

extern int giAdcAI_I1;
extern int giAdcAI_V1;
extern int giAdcAI_I2;
extern int giAdcAI_V2;
extern int giAdcTemp;
extern int scib_rx_msg_flag;
extern int scic_rx_msg_flag;
extern double analog_ref_a;
extern double analog_ref_b;

//*******************************************************
// ���� ���� 
//*******************************************************
#if USE_GRAPH
	extern double y1_data[200];
	extern double y2_data[200];
#endif


extern int blink_toggle;

extern double Vdc_factor;			// 2010 01 13
extern double Vdc_calc_offset;		// 2010 01 13 for Vdc calc 

extern int disp_fnd_mode;

#if USE_DAC_OUT
extern double * dac_point[100];
#endif

extern double dac_ch0_unit_count_value;
extern double dac_ch1_unit_count_value;
extern double dac_ch2_unit_count_value;
extern double dac_ch3_unit_count_value;

extern double ref_time;	// 2009.10.28

extern unsigned int xcon_data;		// expansion board xcon0,1,2,3 out data

extern CODE_INFO code_inform;
extern union PROTECT_FLAG protect_reg;

// codes

// --- digital_inout.h

extern union DIGITAL_OUT_FUNC relay_flag;
extern union DIGITAL_FUNCTION func_flag;	// ������ �Է��� ����� �����Ѵ�.


extern int scic_rx_start_addr;
extern int scic_rx_end_addr;

extern int scic_tx_start_addr;
extern int scic_tx_end_addr;

//extern char scic_rx_msg_box[SCIC_RX_BUF_MAX];
//extern char scic_tx_msg_box[SCIC_TX_BUF_MAX];

//-- use in udd_timer_irq
extern int terminal_input_state;
extern char TripMessage[25];


// PWM
extern double	DutyRatio[3];
extern unsigned int DutyCount[3];

// �ð� �� �ε���
extern double 	gfRunTime;
extern double	Ts;
extern double	inv_Ts;


extern double Rs;		
extern double Rr;
extern double Ls;
extern double Lr;
extern double Lm;
extern double Jm;

// Ref.

extern double	reference0;
extern double	reference1;
extern double	reference_in;
extern double	reference_out;

// ���� �� ���ļ�

extern double	we_in;
extern double	we;
extern double	we0;

extern double	frequency;
extern double	theta;
extern double	SinTheta;
extern double	CosTheta;
extern double	wr_m;			// ���ڴ��� ���� ���� �ӵ�
extern double	wr_m0;			// ���� �ӵ��� ���͸� ��
extern double	wr;
extern double	wr_ref;
extern double	wr_ref0;
extern double	wr_err;
extern double	wr_ErrInt;
extern double	w_sl;
extern double	w_sl0;
extern double	we_FW;				// ����� ���� ���� ���ļ�
extern double	we_FW1;				// ����� �������� 2 ���� ���ļ�
extern double	rpm;
extern double	rpm_m;
extern double	rpm_ref;
extern double	rpm_err;

// ����
extern double	Is_abc[3];
extern double	Is_dq[2];
extern double	Is_mag;
extern double	Is_mag_rms;
extern double	sgn_Is[3];
extern double	Is_DQ[2];
extern double	Is_DQ_max[2];
extern double	Is_DQ_ref[2];
extern double	prev_I_QS;				// --> ���� ���
extern double	Is_DQ_ErrInt[2];
extern double	Is_dq_ref[2];
extern double	Is_dq_ErrInt[2];

// ����
extern double	Vdc;	
extern double	Vs_max;	
extern double	Vs_abc[3];
extern double	Vs_abc_ref[3];
extern double	Vs_dq_ref[2];
extern double	Vs_dq[2];
extern double	Vo;					// zero sequence
extern double	Us_dq[2];
extern double	Vs_DQ[2];
extern double	Vs_DQ_max[2];
extern double	Vs_DQ_ref[2];
extern double	Vs_DQ_comp[2];
extern double	Vs_max_FW;
extern double	Vs_DQ_ref_P[2];
extern double	Vs_DQ_ref_PI[2];

// ��ũ
extern double	Te_max;
extern double	Te_ref;
extern double	Te;
extern double	Max_Trq_Coeff;

// Flux
extern double	Fs_ref0;
extern double	Fs_ref;
extern double	inv_Fs_ref;
extern double	Fs_dq[2];
extern double	Fs;
extern double	Fs1;
extern double	inv_Fs;

extern double	Fr_ref;
extern double	Fr_ref0;
extern double	inv_Fr_ref;
extern double	Fr;
extern double	inv_Fr;
extern double	Fr_Err;
extern double	Fr_ErrInt;

extern double	theta_m;		// ��谢


// VVVF-Control
extern double	Vs_ref;
extern double	Freq_ref;
extern double	Freq_slip;
extern double	Freq_out;
extern double	Slip;
extern double	Power_core;
extern double	Power_core_rat;
extern double	Power_gap;
extern double	Vs_IR_comp;
extern double	del_Vs_comp;

// �������� ��������

extern double 	wr_Cycle;
extern int		wr_CycleIndex;

extern double	Pf;
extern double 	sgn_I_QS;
extern double	Delta_wr;
extern double	I_DS0_0;
extern double	I_DS0;
extern double	I_DS_err;
extern double	DeltaLambda;
extern double	DeltaTheta;
extern double	SinCosDeltaTheta;
extern double	inv_SinCosDeltaTheta;
extern double	CosDeltaTheta;
extern double	SinDeltaTheta;
extern double	SinTheta1;
extern double	CosTheta1;
extern double	Delta_wr_Filter_Pole;

// ����Ʃ��
extern unsigned AutoTuningFlag;

extern double	Freq_set;
extern double	Re_Power;
extern double	Im_Power;

extern double	Jm_SampleData[2];
extern double	Jm_ID_wr[4];
extern double	Jm_ID_Te[4];
extern double	Jm_ID_t[4];


// Reference Func.
extern double 	IncScanRef;
extern double	IncRef;
extern double	DecRef; 

// Dead Time ���� 
extern double 	C_ce_nF;
extern double 	C_ce;
extern double 	inv_C_ce;

// Motor Name Plate Parameter

extern double	Vs_rat;
extern double	Is_rat;
extern double	inv_Is_rat;
extern double	we_rat;
extern double	inv_motor_rate_hz;
extern double	wr_rat;
extern double	wm_rat;
extern double	Te_rat;
extern double	inv_Te_rat;
extern double	Fs_rat;
extern double	Fr_rat;
extern double	Kt;
extern double	inv_Kt;
extern double	P_pair;
extern double	inv_P_pair;
extern double	rpm_Coeff;

// Machine Parameter
extern double	sigma;
extern double	sigma_Ls;
extern double	SlipCoeff;
extern double	inv_sigma_Tr;
extern double	sigma_Tr;
extern double	sigma_minus_1_div_sigma_Ls;
extern double	inv_sigma_Ls;
extern double	inv_Ls;
extern double	Tr;
extern double	inv_Tr;
extern double	inv_Ls_plus_sigma_Ls;				// ���� ���Ѱ� ���
extern double	sigma_Ls_div_1_plus_sigma;			// ���� ���Ѱ� ���
extern double	Lm_div_Lr;						// Lm/Lr
extern double	Lr_div_Lm;						// Lr/Lm

// �ι��� �Ķ����
extern double	Is_max;					// �ִ� �������

// Vector Control with/out sensor 
extern double	wn_wr;
extern double	I_QS_rat;

	
// V/F �����
extern double	S_rat;
extern double	S_lin;
extern double	Freq_slip_rat;
	
	// �ӵ� �����
extern double	Kp_wr;
extern double	Ki_wr;
	
	// �ڼ� ���� �� �ڼ� ��������
extern double	Fs_B;
extern double	inv_Fs_B;
	
// ���� �����
extern double	inv_GM_Is_square_minus_1;
extern double	inv_GM_Is;
extern double	wp_Is_Coeff;
extern double	Kp_Is_Coeff;
extern double	wp_Is;
extern double	Ki_Is;
extern double	Kp_Is;
	
// �������� ���� ����
extern double	wr_FilterPole;
	
// ����Ʃ��
extern double 	Req;
extern double	Leq;
	
//====================================
// F28335 
// EwInv ���� ����
//====================================
extern unsigned long gulStartCount;
extern unsigned int gStartInitFinish; 

// Sci.c

extern char gStr1[50];
extern char gStr2[10];

extern int gSciInFlag;
extern int scia_rx_msg_flag;

extern char gSciaRxBuf[NUM_SCI_RX_BUF+1];
extern char gSciaTxBuf[NUM_SCI_TX_BUF+1];

extern int	gSciaTxInPoint;
extern int	gSciaTxOutPoint;
extern int	gSciaTxEndFlag;

extern int giSciCmdFunction;
extern int giSciCmdAddr;
extern double gdouSciCmdData;

extern int gMachineState;

extern int gAutoTuningSelect;		// �޴����� ���� ���� ���� �ϴ� �� 

extern int gControlMode;

extern unsigned long gulExcitTimeMsec;		// �ʱ� ���� �ð� 0.25�� 
extern int gInitChargeFlag;				// ePWM���� PWM4_A�� ���� �� �ʱ� ������ ���� 

	// Ref. Func

extern int gDeChargeFlag;
extern int	gPWMTripCode;


// �Ķ���� �� ����͸� ����Ÿ ������
extern int gTripSavePoint;		// Ʈ���� ������ ������

extern int adc_result[8];
extern int giAdcUphase;
extern int giAdcVphase;
extern int giAdcVdc	;
extern int giAdcAnaCmd;

extern TRIP_INFO TripInfo;
extern TRIP_INFO TripInfoNow;

extern int gTripFlag;
extern double AnaCmdReference;
extern Uint16	guiEpwmPeriodCount;
extern char MonitorMsg[30];
extern int gRunFlag;
extern int gTripSaveFlag;
extern double OverCurLimit;
extern int EepromSaveFlag;
//============================================
//   Auto_tunning variable
//============================================
extern double	GainUpdateTimer;
extern double	Vs_Coeff_Leq_Req;

extern double LPF_Is;
extern double LPF_Is_Square;
extern double LPF_Vs_Square;
extern double LPF_Re_Power;
extern double Is_Leq_Req;

extern int wr_ctrl_index;
extern double Freq_rat;
extern double inv_Freq_rat;

//============================================
//   CODE variable 
//============================================
extern int run_input_select;
extern int motor_ctrl_mode;
extern int motor_direction_change;
extern int ramp_func_mode;

extern double accel_time1;
extern double decel_time1;
extern double accel_time2;				// 12
extern double decel_time2;				// 13
extern double btn_start_ref;			// 14
extern double jog_speed;				// 15
extern double min_vf_ref;				// 109
extern int use_binary_input;			// 100

extern double digital_speed1;			// 21
extern double digital_speed2;			// 22
extern double digital_speed3;			// 23
extern double digital_speed4;			// 24
extern double digital_speed5;			// 25
extern double digital_speed6;			// 26
extern double digital_speed7;			// 27
extern double digital_speed8;			// 28
extern double digital_speed9;			// 29
extern double digital_speed10;			// 30
extern double digital_speed11;			// 31
extern double digital_speed12;			// 32
extern double digital_speed13;			// 33
extern double digital_speed14;			// 34
extern double digital_speed15;			// 35
extern double digital_speed16;			// 36

extern int input_func_select0;			// 40
extern int input_func_select1;			// 41
extern int input_func_select2;			// 42
extern int input_func_select3;			// 43
extern int input_func_select4;			// 44
extern int input_func_select5;			// 45
extern int input_func_select6;			// 46
extern int input_func_select7;			// 47
//extern int input_func_select8;		// 48

extern int digital_out_function0;		// 50
extern int digital_out_function1;		// 50
extern int digital_out_function2;		// 50
extern int digital_out_function3;		// 50
extern int digital_out_function4;		// 50
extern int digital_out_function5;		// 50
extern int digital_out_function6;		// 50
extern int digital_out_function7;		// 50

// group 1

extern double brake_on_up_ref;			// 101
extern double brake_on_down_ref;		// 102
extern double brake_on_down_ref;		// 103
extern double brake_off_up_ref;			// 104
extern double brake_off_down_ref;		// 105
extern double brake_on_delay_time;		// 106
extern double brake_off_dealy_time;		// 107
extern double brake_torq_boost_time;	// 108

extern double hyd_sensor_set_ref;		//	110
extern double hyd_high_speed_on_ratio;	//	111
extern double hyd_idle_ref;				//	112
extern double hyd_max_ref;				//	113
extern double hyd_decel_time;			//	114


// group2

extern double analog_cmd_in_zero1;		// 200
extern double analog_cmd_in_span1;		// 201
extern double analog_cmd_in_zero2;		// 202
extern double analog_cmd_in_span2;		// 203
extern double analog_out_select1;		// 204
extern double analog_out_zero1;		// 205
extern double analog_out_span1;		// 206
extern double analog_out_offset1;		// 207
extern double analog_out_select2;		// 208
extern double analog_out_zero2;		// 209
extern double analog_out_span2;		// 210
extern double analog_out_offset2;		// 211

extern int dac_ch0_select;
extern double dac_ch0_max;	
extern double dac_ch0_offset;

extern int dac_ch1_select;
extern double dac_ch1_max;	
extern double dac_ch1_offset;

extern int dac_ch2_select;
extern double dac_ch2_max;	
extern double dac_ch2_offset;

extern int dac_ch3_select;
extern double dac_ch3_max;	
extern double dac_ch3_offset;

// group3
extern double over_current_level;		// 300
extern double over_volt_set;			// 301
extern double under_volt_set;			// 302
extern double over_speed_level;		// 303
extern double e_thermal_level;			// 304
extern double pre_charge_time;			// 305
extern double Is_Max_Coeff;			// 306
extern double over_I_time;				// 307

extern double adc_vdc_100;				// 310
extern double adc_vdc_300;				// 311

//group 4
extern double motor_rate_power;		// 400
extern double motor_rate_volt;			// 401
extern double motor_rate_current;		// 402
extern double motor_rate_hz;			// 403
extern double motor_rate_rpm;			// 404
extern double motor_pole;				// 405
extern double motor_rate_effiency;		// 406	

extern double Rs;						// 407
extern double Rr;						// 408
extern double Ls;						// 409
extern double Lr;						// 410
extern double Lm;						// 411
extern double Jm;						// 412

// group5
extern double I_sense_value;			// 500
extern double u_phase_I_sense_zero;		// 501
extern double u_phase_I_sense_span;		// 502
extern double v_phase_I_sense_zero;		// 503
extern double v_phase_I_sense_span;		// 504
extern double vdc_sense_zero;			// 505
extern double vdc_sense_span;			// 506
extern int encoder_pulse_one_turn;		// 507
extern double igbt_pwm_freq;			// 508

extern int adc_u_offset;				// 510
extern int adc_v_offset;				// 511

// group6
extern double VF_DeadTimeGain;			// 600
extern double VF_ExcitationTime;		// 601
extern double VF_Fs_Coeff;				// 602
extern double VF_Freq_TrqBoost;			// 603
extern double VF_Vs_Coeff_TrqBoost;		// 604
extern double VF_Rs_ThermalCoeff;		// 605
extern double VF_IR_Comp_FilterPole;	// 606
extern double VF_Slip_Comp_FilterPole;	// 607
extern double VF_Rs;

extern double AT_Freq_Leq_Req;			// 610
extern double AT_Time_Leq_Req;			// 611
extern double AT_Is_Coeff_Leq_Req;		// 612

extern double AT_Is_Coeff_Rs;			// 613
extern double AT_Time_Rs;				// 614

extern double AT_DeadTimeGain;			// 615
extern double AT_Ls_Vs_RAMP;			// 616
extern double AT_Freq_Ls;				// 617
extern double AT_Time_Ls;				// 618
extern double AT_Ls_DMB_OpenTime;		// 619				

extern double AT_Te_Coeff_Jm;			// 620
extern double AT_Time_Jm;				// 621
extern int Jm_ID_ENABLE;				// 622

extern double posi_duration_time;		// 624	
extern double zero_duration_time;		// 625
extern double nega_duration_time;		// 626
extern double test_accel_time;			// 627	
extern double test_decel_time;			// 628

// group 7 advance control vaiable 

extern double wr_FilterPoleCoeff;		// 700
extern double wn_wr_Coeff;				// 701
extern double Max_wn_wr;				// 702
extern double K_Damp_wr;				// 703
extern double wr_DampingRatio;			// 704
extern int wr_CntlPeriodIndex;			// 705

// �ڼ� ����
extern double FW_VoltageCoeff;			// 706
extern double Base_Flux_Coeff;			// 707
extern double ExcitationTime;			// 708
extern double K_Damp_Fr;				// 709
extern double GM_Fr;					// 710
extern double PM_Fr;					// 711

extern double K_Damp_Is;				// 715
extern double GM_Is;					// 716
extern double PM_Is;					// 717

// �������� ���� ����
extern double Default_wr_FilterPole;	// 720
extern double SlipCompCoeff;			// 721
extern double GammaLambda;				// 722
extern double GammaLambda_R_Constant;	// 723	
extern double Max_DeltaLambda;			// 724
extern double GammaTheta_M;			// 725
extern double GammaTheta_R;			// 726
extern double Max_DeltaTheta;			// 727
extern double Delta_wr_FilterPoleCoeff_L; //728
extern double Delta_wr_FilterPoleCoeff_U; //729

extern double Data_Check;				// 800
extern double Data_Backup;				// 801
extern double Data_Load;				// 802
extern double Data_Init;				// 803


//***********************************************************

#endif

