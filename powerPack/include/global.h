#ifndef		__GLOBAL_VARIABLES_
#define		__GLOBAL_VARIABLES_

double rmsIu;
double lpfVdc;
unsigned int adcIu;
unsigned int adcIv;
unsigned int adcIgbtTemperature;
//=============================================
const char FndTableNumber[11] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
const char FndTableChar[26] ={0x77,0x7c,0x39,0x5e,0x79,0x71,0x7d,0x76,0x06,0x0e,0x78,0x38,
				0x55,0x54,0x5c,0x73,0xdc,0x50,0x6d,0x78,0x1c,0x1c,0x1d,0x64,0x66,0x49};

int button_input_state;
int led_state_flag;
int digit_position;
int fnd_buf[4];
int fnd_blink_flag;

char warning_fnd_data[6]={0};
unsigned long warning_timer_msec;
int warning_fnd_flag;

int giAdcAI_I1;
int giAdcAI_V1;
int giAdcAI_I2;
int giAdcAI_V2;
int giAdcTemp;
int scib_rx_msg_flag = 0;
int scic_rx_msg_flag = 0;
double analog_ref_a;
double analog_ref_b;

//***************************************************
// ������� 
//***************************************************
#if USE_GRAPH
	double y1_data[200]={0.0};
	double y2_data[200]={0.0};
#endif



//===================

int blink_toggle;

double Vdc_factor;			// 2010 01 13
double Vdc_calc_offset;		// 2010 01 13 for Vdc calc 


int disp_fnd_mode;

#if USE_DAC_OUT
double * dac_point[100];
#endif

double dac_ch0_unit_count_value;
double dac_ch1_unit_count_value;
double dac_ch2_unit_count_value;
double dac_ch3_unit_count_value;

double ref_time;
unsigned int xcon_data;		// expansion board xcon0,1,2,3 out data

CODE_INFO code_inform = {0,0,0,0,0,0,{0}};

union PROTECT_FLAG protect_reg;

int terminal_input_state;

// PWM
double	DutyRatio[3];
unsigned int DutyCount[3];

// �ð� �� �ε���
double	Ts;
double	inv_Ts;
double 	gfRunTime=0;

//=============================================
double	Freq_set=0.0;
double	Re_Power=0.0;
double	Im_Power=0.0;

double	Vs_rat;
double	Is_rat;
double	inv_Is_rat;
double	we_rat;
double inv_motor_rate_hz;

double	Is_abc[3]={0.0,0.0,0.0};
double	Is_dq[2]={0.0,0.0};
double	Is_mag=0.0;
double	Is_mag_rms=0.0;
double	Is_max;					// �ִ� ������

double	Vdc=0.0;	
double	Vs_max=0.0;	

double	Freq_out=0.0;
double	rpm=0.0;

double	reference_in=0.0;
double	reference_out=0.0;

// #if MOTOR_CONTROL
// Ref.
double	reference0=0.0;
double	reference1=0.0;

// ���� �� ���ļ�

double	we_in=0.0;
double	we=0.0;
double	we0=0.0;

double	frequency=0.0;
double	theta=0.0;
double	SinTheta=0.0;
double	CosTheta=1.0;
double	wr_m=0.0;			// ���ڴ��� ���� ���� �ӵ�
double	wr_m0=0.0;			// ���� �ӵ��� ���͸� ��
double	wr=0.0;
double	wr_ref=0.0;
double	wr_ref0=0.0;
double	wr_err=0.0;
double	wr_ErrInt=0.0;
double	w_sl=0.0;
double	w_sl0=0.0;
double	we_FW=0.0;				// ����� ���� ���� ���ļ�
double	we_FW1=0.0;				// ����� ���� 2 ���� ���ļ�
double	rpm_m=0.0;
double	rpm_ref=0.0;
double	rpm_err=0.0;

// ���
double	sgn_Is[3]={0.0,0.0,0.0};
double	Is_DQ[2]={0.0,0.0};
double	Is_DQ_max[2]={0.0,0.0};
double	Is_DQ_ref[2]={0.0,0.0};
double	prev_I_QS=0.0;				// --> ���� ���
double	Is_DQ_ErrInt[2]={0.0,0.0};
double	Is_dq_ref[2]={0.0,0.0};
double	Is_dq_ErrInt[2]={0.0,0.0};

// ���
double	Vs_abc[3]={0.0,0.0,0.0};
double	Vs_abc_ref[3]={0.0,0.0,0.0};
double	Vs_dq_ref[2]={0.0,0.0};
double	Vs_dq[2]={0.0,0.0};
double	Vo=0.0;					// zero sequence
double	Us_dq[2]={0.0,0.0};
double	Vs_DQ[2]={0.0,0.0};
double	Vs_DQ_max[2]={0.0,0.0};
double	Vs_DQ_ref[2]={0.0,0.0};
double	Vs_DQ_comp[2]={0.0,0.0};
double	Vs_max_FW=0.0;
double	Vs_DQ_ref_P[2]={0.0,0.0};
double	Vs_DQ_ref_PI[2]={0.0,0.0};

// ��ũ
double	Te_max=0.0;
double	Te_ref=0.0;
double	Te=0.0;
double	Max_Trq_Coeff=0.0;

// Flux
double	Fs_ref0=0.0;
double	Fs_ref=0.0;
double	inv_Fs_ref=0.0;
double	Fs_dq[2]={0.0,0.0};
double	Fs=0.0;
double	Fs1=0.0;
double	inv_Fs=0.0;

double	Fr_ref=0.0;
double	Fr_ref0=0.0;
double	inv_Fr_ref=0.0;
double	Fr=0.0;
double	inv_Fr=0.0;
double	Fr_Err=0.0;
double	Fr_ErrInt=0.0;

double	theta_m=0.0;		// ��谢

// VVVF-Control
double	Vs_ref=0.0;
double	Freq_ref=0.0;
double	Freq_slip=0.0;
double	Slip=0.0;
double	Power_core=0.0;
double	Power_core_rat=0.0;
double	Power_gap=0.0;
double	Vs_IR_comp=0.0;
double	del_Vs_comp=0.0;


// �������� ��������

double 	wr_Cycle=0.0;
int		wr_CycleIndex=0;

double	Pf=0.0;
double 	sgn_I_QS=0.0;
double	Delta_wr=0.0;
double	I_DS0_0=0.0;
double	I_DS0=0.0;
double	I_DS_err=0.0;
double	DeltaLambda=0.0;
double	DeltaTheta=0.0;
double	SinCosDeltaTheta=0.0;
double	inv_SinCosDeltaTheta=0.0;
double	CosDeltaTheta=0.0;
double	SinDeltaTheta=0.0;
double	SinTheta1=0.0;
double	CosTheta1=0.0;
double	Delta_wr_Filter_Pole=0.0;

// Reference Func.
double 	IncScanRef=0.0;
double	IncRef=0.0;
double	DecRef=0.0; 

	// �ʱ�����	

// Dead Time ���� 
double 	C_ce_nF;
double 	C_ce;
double 	inv_C_ce;

// Motor Name Plate Parameter
	

double	inv_motor_rat_hz;
double	wr_rat;
double	wm_rat;
double	Te_rat;
double	inv_Te_rat;
double	Fs_rat;
double	Fr_rat;
double	Kt;
double	inv_Kt;
double	P_pair;
double	inv_P_pair;
double	rpm_Coeff;

// Machine Parameter
double	sigma;
double	sigma_Ls;
double	SlipCoeff;
double	inv_sigma_Tr;
double	sigma_Tr;
double	sigma_minus_1_div_sigma_Ls;
double	inv_sigma_Ls;
double	inv_Ls;
double	Tr;
double	inv_Tr;
double	inv_Ls_plus_sigma_Ls;				// ��� ���Ѱ� ���
double	sigma_Ls_div_1_plus_sigma;			// ��� ���Ѱ� ���
double	Lm_div_Lr;						// Lm/Lr
double	Lr_div_Lm;						// Lr/Lm

// Vector Control with/out sensor 
double	wn_wr;
double	I_QS_rat;
double inv_I_QS_rat;
	
// V/F �����
double	S_rat;
double	S_lin;
double	Freq_slip_rat;
	
	// �ӵ� �����
double	Kp_wr;
double	Ki_wr;
	
	// �ڼ� ���� �� �ڼ� ��������
double	Fs_B;
double	inv_Fs_B;
	
// ��� �����
double	inv_GM_Is_square_minus_1;
double	inv_GM_Is;
double	wp_Is_Coeff;
double	Kp_Is_Coeff;
double	wp_Is;
double	Ki_Is;
double	Kp_Is;
	
// �������� ���� ����
double	wr_FilterPole;
	
// ����Ʃ��

unsigned AutoTuningFlag=0;

#if	AUTO_TUNING_TEST

double	Jm_SampleData[2]={0.0,0.0};
double	Jm_ID_wr[4]={0.0,0.0,0.0,0.0};
double	Jm_ID_Te[4]={0.0,0.0,0.0,0.0};
double	Jm_ID_t[4]={0.0,0.0,0.0,0.0};

double 	Req;
double	Leq;
#endif

// #endif
	
//====================================
// F28335 
// EwInv ���� ����
//====================================

unsigned long gulStartCount;

unsigned int gStartInitFinish; 

// Sci.c

char gStr1[50] = {0};
char gStr2[10] = {0};

int gSciInFlag;

char gSciaRxBuf[NUM_SCI_RX_BUF+1];
char gSciaTxBuf[NUM_SCI_TX_BUF+1];

int	gSciaTxInPoint;
int	gSciaTxOutPoint;
int	gSciaTxEndFlag;

int giSciCmdFunction;
int giSciCmdAddr;
double gdouSciCmdData;

int gMachineState=0;

int gAutoTuningSelect;		// �޴����� ���� ���� ���� �ϴ� �� 

int gControlMode;

int gInitChargeFlag;				// ePWM���� PWM4_A�� ���� �� �ʱ� ������ ���� 

	// Ref. Func

int gDeChargeFlag;
int	gPWMTripCode;

// �Ķ���� �� ����͸� ����Ÿ ������
int gTripSavePoint;		// Ʈ���� ������ ������

int adc_result[8]={0};
int	giAdcUphase=0 ;
int	giAdcVphase=0 ;
int	giAdcVdc	;
int giAdcAnaCmd;


union DIGITAL_FUNCTION func_flag;	// ������ �Է��� ����� �����Ѵ�.

union DIGITAL_OUT_FUNC relay_flag;

TRIP_INFO TripInfo = {0,0,0,0,0,"2008:07:24  00:01:23"," No Trip Data       "};

//TRIP_INFO TripInfoNow={0,0,0,0,0,"01234567890123456789","01234567890123456789"};
TRIP_INFO TripInfoNow = {0,0,0,0,0,"2008:07:24  00:01:23"," No Trip Data       "};

int gTripFlag = 0;
double AnaCmdReference=0;

Uint16	guiEpwmPeriodCount;

char MonitorMsg[30]={0};

int gRunFlag=0;
int gTripSaveFlag=0;

double OverCurLimit;
int EepromSaveFlag;

//============================================
//   CODE variable 
//============================================
int run_input_select;
int motor_ctrl_mode;
int motor_direction_change;
int ramp_func_mode;

double accel_time1;
double decel_time1;
double accel_time2;				// 12
double decel_time2;				// 13
double btn_start_ref;			// 14
double jog_speed;				// 15
double min_vf_ref;				// 109
int use_binary_input;			// 100

double digital_speed1;			// 21
double digital_speed2;			// 22
double digital_speed3;			// 23
double digital_speed4;			// 24
double digital_speed5;			// 25
double digital_speed6;			// 26
double digital_speed7;			// 27
double digital_speed8;			// 28
double digital_speed9;			// 29
double digital_speed10;			// 30
double digital_speed11;			// 31
double digital_speed12;			// 32
double digital_speed13;			// 33
double digital_speed14;			// 34
double digital_speed15;			// 35
double digital_speed16;			// 36

int input_func_select0;			// 41
int input_func_select1;			// 41
int input_func_select2;			// 42
int input_func_select3;			// 43
int input_func_select4;			// 44
int input_func_select5;			// 45
int input_func_select6;			// 46
int input_func_select7;			// 47
//int input_func_select8;			// 48

int digital_out_function0;		// 50
int digital_out_function1;		// 51
int digital_out_function2;		// 52
int digital_out_function3;		// 53
int digital_out_function4;		// 54
int digital_out_function5;		// 55
int digital_out_function6;		// 56
int digital_out_function7;		// 57

// group 1

double brake_on_up_ref;			// 101
double brake_on_down_ref;		// 102
double brake_on_down_ref;		// 103
double brake_off_up_ref;		// 104
double brake_off_down_ref;		// 105
double brake_on_delay_time;		// 106
double brake_off_dealy_time;	// 107
double brake_torq_boost_time;	// 108

double hyd_sensor_set_ref;		//	110
double hyd_high_speed_on_ratio;	//	111
double hyd_idle_ref;			//	112
double hyd_max_ref;				//	113
double hyd_decel_time;			//	114

// group2

double analog_cmd_in_zero1;		// 200
double analog_cmd_in_span1;		// 201
double analog_cmd_in_zero2;		// 202
double analog_cmd_in_span2;		// 203
double analog_out_select1;		// 204
double analog_out_zero1;		// 205
double analog_out_span1;		// 206
double analog_out_offset1;		// 207
double analog_out_select2;		// 208
double analog_out_zero2;		// 209
double analog_out_span2;		// 210
double analog_out_offset2;		// 211

int dac_ch0_select;
double dac_ch0_max;	
double dac_ch0_offset;

int dac_ch1_select;
double dac_ch1_max;	
double dac_ch1_offset;

int dac_ch2_select;
double dac_ch2_max;	
double dac_ch2_offset;

int dac_ch3_select;
double dac_ch3_max;	
double dac_ch3_offset;

// group3
double over_current_level;		// 300
double over_volt_set;			// 301
double under_volt_set;			// 302
double over_speed_level;		// 303
double e_thermal_level;			// 304
double pre_charge_time;			// 305
double Is_Max_Coeff;			// 306
double over_I_time;				// 307

double adc_vdc_100;				// 310
double adc_vdc_300;				// 311


//group 4
double motor_rate_power;		// 400
double motor_rate_volt;			// 401
double motor_rate_current;		// 402
double motor_rate_hz;			// 403
double motor_rate_rpm;			// 404
double motor_pole;				// 405
double motor_rate_effiency;		// 406	

double Rs;						// 407
double Rr;						// 408
double Ls;						// 409
double Lr;						// 410
double Lm;						// 411
double Jm;						// 412

// group5
double I_sense_value;			// 500
double u_phase_I_sense_zero;	// 501
double u_phase_I_sense_span;	// 502
double v_phase_I_sense_zero;	// 503
double v_phase_I_sense_span;	// 504
double vdc_sense_zero;			// 505
double vdc_sense_span;			// 506
int encoder_pulse_one_turn;		// 507
double igbt_pwm_freq;			// 508

int adc_u_offset;				// 510
int adc_v_offset;				// 511

// group6
double VF_DeadTimeGain;			// 600
double VF_ExcitationTime;		// 601
double VF_Fs_Coeff;				// 602
double VF_Freq_TrqBoost;		// 603
double VF_Vs_Coeff_TrqBoost;	// 604
double VF_Rs_ThermalCoeff;		// 605
double VF_IR_Comp_FilterPole;	// 606
double VF_Slip_Comp_FilterPole;	// 607
double VF_Rs;


double AT_Freq_Leq_Req;			// 610
double AT_Time_Leq_Req;			// 611
double AT_Is_Coeff_Leq_Req;		// 612

double AT_Is_Coeff_Rs;			// 613
double AT_Time_Rs;				// 614

double AT_DeadTimeGain;			// 615
double AT_Ls_Vs_RAMP;			// 616
double AT_Freq_Ls;				// 617
double AT_Time_Ls;				// 618
double AT_Ls_DMB_OpenTime;		// 619				

double AT_Te_Coeff_Jm;			// 620
double AT_Time_Jm;				// 621
int Jm_ID_ENABLE;				// 622

double posi_duration_time;		// 624	
double zero_duration_time;		// 625
double nega_duration_time;		// 626
double test_accel_time;			// 627	
double test_decel_time;			// 628

// group 7 advance control vaiable 

double wr_FilterPoleCoeff;		// 700
double wn_wr_Coeff;				// 701
double Max_wn_wr;				// 702
double K_Damp_wr;				// 703
double wr_DampingRatio;			// 704
int wr_CntlPeriodIndex;			// 705
	
// �ڼ� ����
double FW_VoltageCoeff;			// 706
double Base_Flux_Coeff;			// 707
double ExcitationTime;			// 708
double K_Damp_Fr;				// 709
double GM_Fr;					// 710
double PM_Fr;					// 711

double K_Damp_Is;				// 715
double GM_Is;					// 716
double PM_Is;					// 717

// �������� ���� ����
double Default_wr_FilterPole;	// 720
double SlipCompCoeff;			// 721
double GammaLambda;				// 722
double GammaLambda_R_Constant;	// 723	
double Max_DeltaLambda;			// 724
double GammaTheta_M;			// 725
double GammaTheta_R;			// 726
double Max_DeltaTheta;			// 727
double Delta_wr_FilterPoleCoeff_L; //728
double Delta_wr_FilterPoleCoeff_U; //729

double Data_Check;				// 800
double Data_Backup;				// 801
double Data_Load;				// 802
double Data_Init;				// 803

//=====================================================

double	GainUpdateTimer;
double	Vs_Coeff_Leq_Req;

double LPF_Is;
double LPF_Is_Square;
double LPF_Vs_Square;
double LPF_Re_Power;

double	Is_Leq_Req;

int wr_ctrl_index			= 1;

double Freq_rat;
double inv_Freq_rat;
#endif

