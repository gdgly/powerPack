
#define CODE_AnalogIn_Zero					11
#define CODE_AnalogIn_Span					12
#define	CODE_MIN_Analog_REF					13
#define	CODE_MAX_Analog_REF					14

// A20 아날로그 출력 모니터 1

#define	CODE_AnalMonit1Select				21
#define	CODE_AnalMonit1Zero					22
#define	CODE_AnalMonit1Span					23

// A30 아날로그 출력 모니터 1

#define	CODE_AnalMonit2Select				31
#define	CODE_AnalMonit2Zero					32
#define	CODE_AnalMonit2Span					33

// A40 디지털 입력기 모니터 1
#define	CODE_InputMonit1Select				41			// 어드레스 설정
#define	CODE_InputMonit1Disp				42			// 단위 설정
#define	CODE_InputMonit1Zero				43
#define	CODE_InputMonit1Span				44

// A50 디지털 입력기 모니터 2
#define	CODE_InputMonit2Select				51			// 어드레스 설정
#define	CODE_InputMonit2Disp				52			// 단위 설정
#define	CODE_InputMonit2Zero				53
#define	CODE_InputMonit2Span				54

// A60 디지털 입력기 모니터 3
#define	CODE_InputMonit3Select				61			// 어드레스 설정
#define	CODE_InputMonit3Disp				62			// 단위 설정
#define	CODE_InputMonit3Zero				63
#define	CODE_InputMonit3Span				64

// A70 디지털 입력기 모니터 4
#define	CODE_InputMonit4Select				71			// 어드레스 설정
#define	CODE_InputMonit4Disp				72			// 단위 설정
#define	CODE_InputMonit4Zero				73
#define	CODE_InputMonit4Span				74

// A80 디지털 입력기 모니터 5
#define	CODE_InputMonit5Select				81			// 어드레스 설정
#define	CODE_InputMonit5Disp				82			// 단위 설정
#define	CODE_InputMonit5Zero				83
#define	CODE_InputMonit5Span				84


//-------------------------------------------------
// B group
//
// digital I/O 설정 
//
//-------------------------------------------------

// 디지털 I/O 설정 
#define	CODE_BinaryInput					11		// Yea or No
#define	CODE_RelayOnRef						12
#define	CODE_RelayOffRef					13

// 브레이크 설정 
#define	CODE_BrakeOnRef						21		// Yea or No
#define	CODE_BrakeOffRef					22
#define	CODE_BrakeOnDelayTimeMsec			23
#define	CODE_BrakeOffDelayTimeMsec			24
#define	CODE_MagnetizeTimeMsec				25
#define	CODE_ZeroHoldTimeMsec				26

//-------------------------------------------------
// C group
//  
//  제어방식 및 속도 설정 
//
//-------------------------------------------------

#define	CODE_SpeedInputType					11
#define	CODE_CtrlType						12
#define	CODE_ChangeDirection				13

#define	CODE_ACC_RAMP1						21		// 가속시간 설정
#define	CODE_DEC_RAMP1						22		// 감속시간 설정
#define	CODE_ACC_RAMP2						23		// 가속시간 설정
#define	CODE_DEC_RAMP2						24		// 감속시간 설정

#define	CODE_StepRef1						31
#define	CODE_StepRef2						32
#define	CODE_StepRef3						33
#define	CODE_StepRef4						34
#define	CODE_StepRef5						35
#define	CODE_StepRef6						36
#define	CODE_StepRef7						37
#define	CODE_StepRef8						38

#define	CODE_CtrlTestMode					41
#define	CODE_REF_POS_TIME					42
#define	CODE_REF_ZERO_TIME					43
#define	CODE_REF_NEG_TIME					44	
#define	CODE_TestAcceRamp					45		// 가속시간 설정
#define	CODE_TestDeceRamp					46		// 가속시간 설정

//-------------------------------------------------
// D group
//  
//  보호레벨 설정 및 모터 상수 설정 
//
//-------------------------------------------------

#define	CODE_OverCurrLevel					11
#define	CODE_OverVoltLevel					12
#define	CODE_UndeVoltLevel					13
#define	CODE_PRECHARGING_TIMEOUT			14		// 충전 시간 초과 
#define	CODE_OverSpeedLevel					15
#define	CODE_EThermalLevel					16

#define	CODE_OC_TIMEOUT						21
#define	CODE_OV_TIMEOUT						22
#define	CODE_UV_TIMEOUT						23
#define	CODE_OS_TIMEOUT						24


#define	CODE_RATED_POWEWR_kW				21
#define	CODE_RATED_VOLTAGE_LL_rms			22
#define	CODE_RATED_CURRENT_rms				23
#define	CODE_RATED_FREQUENCY_Hz				24
#define	CODE_RATED_SPEED_rpm				25
#define	CODE_POLE							26
#define	CODE_Efficiency_Coeff				27

#define	CODE_Rs								31
#define	CODE_Rr								32
#define	CODE_Ls								33
#define	CODE_Lr								34
#define	CODE_Lm								35
#define	CODE_Jm								35

//-------------------------------------------------
// E group
//  
//  보호레벨 설정 및 모터 상수 설정 
//
//-------------------------------------------------


// 속도제어

#define	CODE_wr_FilterPoleCoeff				11
#define	CODE_wn_wr_Coeff					12
#define	CODE_MAX_wn_wr						13
#define	CODE_K_Damp_wr						14
#define	CODE_wr_DampingRatio				15


// 벡터제어 상수 
#define	CODE_SlipCompCoeff					21
#define	CODE_GammaLambda					22
#define	CODE_GammaLambda_R_Constant			23	
#define	CODE_GammaTheta_M					24
#define	CODE_GammaTheta_R					25

// 속도제어 2
#define	CODE_Default_wr_FilterPole			31
#define	CODE_Max_DeltaLambda				32
#define	CODE_Max_DeltaTheta					33
#define	CODE_Delta_wr_FilterPoleCoeff_L		34
#define	CODE_Delta_wr_FilterPoleCoeff_U		35


// 자속제어 상수
#define	CODE_FW_VoltageCoeff				41
#define	CODE_BASE_FLUX_Coeff				42
#define	CODE_ExcitationTime					43
#define	CODE_K_Damp_Fr						44
#define	CODE_GM_Fr							45
#define	CODE_PM_Fr							46


#define	CODE_AT_Freq_Leq_Req				51
#define	CODE_AT_Time_Leq_Req				52
#define	CODE_AT_Is_Coeff_Leq_Req			53			
#define	CODE_AT_Is_Coeff_Rs					54
#define	CODE_AT_Time_Rs						55
#define	CODE_AT_DeadTimeGain				56	

#define	CODE_AT_Ls_Vs_RAMP					61
#define	CODE_AT_Freq_Ls						62
#define	CODE_AT_Time_Ls						63
#define	CODE_AT_Ls_DMB_OpenTime				64
#define	CODE_AT_Te_Coeff_Jm					65
#define	CODE_AT_Time_Jm						66

#define	CODE_VF_DeadTimeGain				71
#define	CODE_VF_ExcitationTime				72
#define	CODE_VF_Fs_Coeff					73
#define	CODE_VF_Freq_TrqBoost				74
#define	CODE_VF_Vs_Coeff_TrqBoost			75	
#define	CODE_VF_Rs_ThermalCoeff				76
#define	CODE_VF_IR_Comp_FilterPole			77	
#define	CODE_VF_Slip_Comp_FilterPole		78
#define	CODE_VF_Rs							79	



//-------------------------------------------------
// F group
//  
//  Trip 이력 저장  
//
//-------------------------------------------------

#define	CODE_TripSource1					11
#define	CODE_TripCurr1						12
#define	CODE_TripVolt1						13
#define	CODE_TripHz1						14
#define	CODE_TripDay1						15
#define	CODE_TripTime1						16

#define	CODE_TripSource2					21
#define	CODE_TripCurr2						22
#define	CODE_TripVolt2						23
#define	CODE_TripHz2						24
#define	CODE_TripDay2						25
#define	CODE_TripTime2						26

#define	CODE_TripSource3					31
#define	CODE_TripCurr3						32
#define	CODE_TripVolt3						33
#define	CODE_TripHz3						34
#define	CODE_TripDay3						35
#define	CODE_TripTime3						36

#define	CODE_TripSource4					41
#define	CODE_TripCurr4						42
#define	CODE_TripVolt4						43
#define	CODE_TripHz4						44
#define	CODE_TripDay4						45
#define	CODE_TripTime4						46

#define	CODE_TripSource5					51
#define	CODE_TripCurr5						52
#define	CODE_TripVolt5						53
#define	CODE_TripHz5						54
#define	CODE_TripDay5						55
#define	CODE_TripTime5						56

#define	CODE_TripSource6					61
#define	CODE_TripCurr6						62
#define	CODE_TripVolt6						63
#define	CODE_TripHz6						64
#define	CODE_TripDay6						65
#define	CODE_TripTime6						66

#define	CODE_TripSource7					71
#define	CODE_TripCurr7						72
#define	CODE_TripVolt7						73
#define	CODE_TripHz7						74
#define	CODE_TripDay7						75
#define	CODE_TripTime7						76

#define	CODE_TripSource8					81
#define	CODE_TripCurr8						82
#define	CODE_TripVolt8						83
#define	CODE_TripHz8						84
#define	CODE_TripDay8						85
#define	CODE_TripTime8						86

#define	CODE_TripSource9					91
#define	CODE_TripCurr9						92
#define	CODE_TripVolt9						93
#define	CODE_TripHz9						94
#define	CODE_TripDay9						95
#define	CODE_TripTime9						96


//-------------------------------------------------
// G group
//  
//  Factory Setting 
//
//-------------------------------------------------

#define	CODE_CURRENT_A_PER_VOLT				14		// 전류센서에서 AD 컨버터 입력의 1V당 A상 전류값 	
#define	CODE_CURRENT_B_PER_VOLT				15		// 전류센서에서 AD 컨버터 입력의 1V당 B상 전류값 
#define	CODE_Vdc_PER_VOLT					16		// DC-Link 전압 센서에서 AD컨버터 입력의 1V당 전압 값   
#define	CODE_ANALOG_INPUT_PER_VOLT			17		// 아날로그 입력의 1V당 설정하고 싶은 입력 값 


// 인버터 파라미터
#define	CODE_PWM_BASE_FUND_FREQ_Hz			21	// 최대 봉㎵?주파수를 설정하기 위한 주파수 계수 
#define	CODE_PWM_TOP_FUND_FREQ_Hz			22	// 최소 스위칭 주파수를 설정하기 위한 주파수 계수
#define	CODE_TOP_PWM_FREQ_kHz				23	// 스위칭 주파수 : 단위 = kHz 
#define	CODE_BASE_PWM_FREQ_kHz				24	// 스위칭 주파수 : 단위 = kHz 
#define	CODE_MAX_CURRENT_COEFF				26


//

// A10	아날로그 지령 입력 설정

#define	CODE_AnalogIn_Zero					11
#define	CODE_AnalogIn_Span					12
#define	CODE_MIN_Analog_REF					13
#define	CODE_MAX_Analog_REF					14

// A20 아날로그 출력 모니터 1

#define	CODE_AnalMonit1Select				21
#define	CODE_AnalMonit1Zero					22
#define	CODE_AnalMonit1Span					23

// A30 아날로그 출력 모니터 1

#define	CODE_AnalMonit2Select				31
#define	CODE_AnalMonit2Zero					32
#define	CODE_AnalMonit2Span					33

// A40 디지털 입력기 모니터 1
#define	CODE_InputMonit1Select				41			// 어드레스 설정
#define	CODE_InputMonit1Disp				42			// 단위 설정
#define	CODE_InputMonit1Zero				43
#define	CODE_InputMonit1Span				44

// A50 디지털 입력기 모니터 2
#define	CODE_InputMonit2Select				51			// 어드레스 설정
#define	CODE_InputMonit2Disp				52			// 단위 설정
#define	CODE_InputMonit2Zero				53
#define	CODE_InputMonit2Span				54

// A60 디지털 입력기 모니터 3
#define	CODE_InputMonit3Select				61			// 어드레스 설정
#define	CODE_InputMonit3Disp				62			// 단위 설정
#define	CODE_InputMonit3Zero				63
#define	CODE_InputMonit3Span				64

// A70 디지털 입력기 모니터 4
#define	CODE_InputMonit4Select				71			// 어드레스 설정
#define	CODE_InputMonit4Disp				72			// 단위 설정
#define	CODE_InputMonit4Zero				73
#define	CODE_InputMonit4Span				74

// A80 디지털 입력기 모니터 5
#define	CODE_InputMonit5Select				81			// 어드레스 설정
#define	CODE_InputMonit5Disp				82			// 단위 설정
#define	CODE_InputMonit5Zero				83
#define	CODE_InputMonit5Span				84


//-------------------------------------------------
// B group
//
// digital I/O 설정 
//
//-------------------------------------------------

// 디지털 I/O 설정 
#define	CODE_BinaryInput					11		// Yea or No
#define	CODE_RelayOnRef						12
#define	CODE_RelayOffRef					13

// 브레이크 설정 
#define	CODE_BrakeOnRef						21		// Yea or No
#define	CODE_BrakeOffRef					22
#define	CODE_BrakeOnDelayTimeMsec			23
#define	CODE_BrakeOffDelayTimeMsec			24
#define	CODE_MagnetizeTimeMsec				25
#define	CODE_ZeroHoldTimeMsec				26

//-------------------------------------------------
// C group
//  
//  제어방식 및 속도 설정 
//
//-------------------------------------------------

#define	CODE_SpeedInputType					11
#define	CODE_CtrlType						12
#define	CODE_ChangeDirection				13

#define	CODE_ACC_RAMP1						21		// 가속시간 설정
#define	CODE_DEC_RAMP1						22		// 감속시간 설정
#define	CODE_ACC_RAMP2						23		// 가속시간 설정
#define	CODE_DEC_RAMP2						24		// 감속시간 설정

#define	CODE_StepRef1						31
#define	CODE_StepRef2						32
#define	CODE_StepRef3						33
#define	CODE_StepRef4						34
#define	CODE_StepRef5						35
#define	CODE_StepRef6						36
#define	CODE_StepRef7						37
#define	CODE_StepRef8						38

#define	CODE_CtrlTestMode					41
#define	CODE_REF_POS_TIME					42
#define	CODE_REF_ZERO_TIME					43
#define	CODE_REF_NEG_TIME					44	
#define	CODE_TestAcceRamp					45		// 가속시간 설정
#define	CODE_TestDeceRamp					46		// 가속시간 설정

//-------------------------------------------------
// D group
//  
//  보호레벨 설정 및 모터 상수 설정 
//
//-------------------------------------------------

#define	CODE_OverCurrLevel					11
#define	CODE_OverVoltLevel					12
#define	CODE_UndeVoltLevel					13
#define	CODE_PRECHARGING_TIMEOUT			14		// 충전 시간 초과 
#define	CODE_OverSpeedLevel					15
#define	CODE_EThermalLevel					16

#define	CODE_OC_TIMEOUT						21
#define	CODE_OV_TIMEOUT						22
#define	CODE_UV_TIMEOUT						23
#define	CODE_OS_TIMEOUT						24


#define	CODE_RATED_POWEWR_kW				21
#define	CODE_RATED_VOLTAGE_LL_rms			22
#define	CODE_RATED_CURRENT_rms				23
#define	CODE_RATED_FREQUENCY_Hz				24
#define	CODE_RATED_SPEED_rpm				25
#define	CODE_POLE							26
#define	CODE_Efficiency_Coeff				27

#define	CODE_Rs								31
#define	CODE_Rr								32
#define	CODE_Ls								33
#define	CODE_Lr								34
#define	CODE_Lm								35
#define	CODE_Jm								35

//-------------------------------------------------
// E group
//  
//  보호레벨 설정 및 모터 상수 설정 
//
//-------------------------------------------------


// 속도제어

#define	CODE_wr_FilterPoleCoeff				11
#define	CODE_wn_wr_Coeff					12
#define	CODE_MAX_wn_wr						13
#define	CODE_K_Damp_wr						14
#define	CODE_wr_DampingRatio				15


// 벡터제어 상수 
#define	CODE_SlipCompCoeff					21
#define	CODE_GammaLambda					22
#define	CODE_GammaLambda_R_Constant			23	
#define	CODE_GammaTheta_M					24
#define	CODE_GammaTheta_R					25

// 속도제어 2
#define	CODE_Default_wr_FilterPole			31
#define	CODE_Max_DeltaLambda				32
#define	CODE_Max_DeltaTheta					33
#define	CODE_Delta_wr_FilterPoleCoeff_L		34
#define	CODE_Delta_wr_FilterPoleCoeff_U		35


// 자속제어 상수
#define	CODE_FW_VoltageCoeff				41
#define	CODE_BASE_FLUX_Coeff				42
#define	CODE_ExcitationTime					43
#define	CODE_K_Damp_Fr						44
#define	CODE_GM_Fr							45
#define	CODE_PM_Fr							46


#define	CODE_AT_Freq_Leq_Req				51
#define	CODE_AT_Time_Leq_Req				52
#define	CODE_AT_Is_Coeff_Leq_Req			53			
#define	CODE_AT_Is_Coeff_Rs					54
#define	CODE_AT_Time_Rs						55
#define	CODE_AT_DeadTimeGain				56	

#define	CODE_AT_Ls_Vs_RAMP					61
#define	CODE_AT_Freq_Ls						62
#define	CODE_AT_Time_Ls						63
#define	CODE_AT_Ls_DMB_OpenTime				64
#define	CODE_AT_Te_Coeff_Jm					65
#define	CODE_AT_Time_Jm						66

#define	CODE_VF_DeadTimeGain				71
#define	CODE_VF_ExcitationTime				72
#define	CODE_VF_Fs_Coeff					73
#define	CODE_VF_Freq_TrqBoost				74
#define	CODE_VF_Vs_Coeff_TrqBoost			75	
#define	CODE_VF_Rs_ThermalCoeff				76
#define	CODE_VF_IR_Comp_FilterPole			77	
#define	CODE_VF_Slip_Comp_FilterPole		78
#define	CODE_VF_Rs							79	



//-------------------------------------------------
// F group
//  
//  Trip 이력 저장  
//
//-------------------------------------------------

#define	CODE_TripSource1					11
#define	CODE_TripCurr1						12
#define	CODE_TripVolt1						13
#define	CODE_TripHz1						14
#define	CODE_TripDay1						15
#define	CODE_TripTime1						16

#define	CODE_TripSource2					21
#define	CODE_TripCurr2						22
#define	CODE_TripVolt2						23
#define	CODE_TripHz2						24
#define	CODE_TripDay2						25
#define	CODE_TripTime2						26

#define	CODE_TripSource3					31
#define	CODE_TripCurr3						32
#define	CODE_TripVolt3						33
#define	CODE_TripHz3						34
#define	CODE_TripDay3						35
#define	CODE_TripTime3						36

#define	CODE_TripSource4					41
#define	CODE_TripCurr4						42
#define	CODE_TripVolt4						43
#define	CODE_TripHz4						44
#define	CODE_TripDay4						45
#define	CODE_TripTime4						46

#define	CODE_TripSource5					51
#define	CODE_TripCurr5						52
#define	CODE_TripVolt5						53
#define	CODE_TripHz5						54
#define	CODE_TripDay5						55
#define	CODE_TripTime5						56

#define	CODE_TripSource6					61
#define	CODE_TripCurr6						62
#define	CODE_TripVolt6						63
#define	CODE_TripHz6						64
#define	CODE_TripDay6						65
#define	CODE_TripTime6						66

#define	CODE_TripSource7					71
#define	CODE_TripCurr7						72
#define	CODE_TripVolt7						73
#define	CODE_TripHz7						74
#define	CODE_TripDay7						75
#define	CODE_TripTime7						76

#define	CODE_TripSource8					81
#define	CODE_TripCurr8						82
#define	CODE_TripVolt8						83
#define	CODE_TripHz8						84
#define	CODE_TripDay8						85
#define	CODE_TripTime8						86

#define	CODE_TripSource9					91
#define	CODE_TripCurr9						92
#define	CODE_TripVolt9						93
#define	CODE_TripHz9						94
#define	CODE_TripDay9						95
#define	CODE_TripTime9						96


//-------------------------------------------------
// G group
//  
//  Factory Setting 
//
//-------------------------------------------------

#define	CODE_CURRENT_A_PER_VOLT				14		// 전류센서에서 AD 컨버터 입력의 1V당 A상 전류값 	
#define	CODE_CURRENT_B_PER_VOLT				15		// 전류센서에서 AD 컨버터 입력의 1V당 B상 전류값 
#define	CODE_Vdc_PER_VOLT					16		// DC-Link 전압 센서에서 AD컨버터 입력의 1V당 전압 값   
#define	CODE_ANALOG_INPUT_PER_VOLT			17		// 아날로그 입력의 1V당 설정하고 싶은 입력 값 


// 인버터 파라미터
#define	CODE_PWM_BASE_FUND_FREQ_Hz			21	// 최대 스위칭 주파수를 설정하기 위한 주파수 계수 
#define	CODE_PWM_TOP_FUND_FREQ_Hz			22	// 최소 스위칭 주파수를 설정하기 위한 주파수 계수
#define	CODE_TOP_PWM_FREQ_kHz				23	// 스위칭 주파수 : 단위 = kHz 
#define	CODE_BASE_PWM_FREQ_kHz				24	// 스위칭 주파수 : 단위 = kHz 
#define	CODE_MAX_CURRENT_COEFF				26


#define CODE_VF_ExcitationTime				101	// debug
#define CODE_Fs_CntlPeriodIndex				102
#define CODE_VF_ExcitationCurrentCoeff			103
#define CODE_Fr_CntlPeriodIndex				104
#define CODE_VF_ExcitationCurrentCoeff			105

/*
AGroupDecoder(int Code, int *Addres ,char *Message)
{
	 
	switch(Code)
	{
	case 11:	
		Address	= 1; 
		strcpy(st,"ANA Zero Set");
		break;		// 아날로그 영점 조정
		
	
	
	
	case 12:	Address	= 2; break;
	case 13:	Address	= 3; break;
	case 14:	Address	= 4; break;
	case 15:	Address	= 5; break;
	
	case 21:	Address	= 6; break;
	case 11:	Address	= 7; break;
	case 11:	Address	= 8; break;
	case 11:	Address	= 9; break;
	case 11:	Address	= 10; break;
			
}
*/

	