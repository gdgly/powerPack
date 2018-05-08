// code_proc.c
//   header file : code_proc.h
//

#include	"header.h"
#include	"extern.h"

int get_code_group0(int addr ,int cmd, CODE_INFO * codes)
{

	switch(addr)
	{
	case CODE_run_input_select:	
		strncpy(codes->disp, "run_input_select",40);
		if( cmd == CMD_WRITE_RAM ) run_input_select = (codes->code_value).ints;
		set_code_default_int(0,4,0,run_input_select,0,codes);
		break;
	
	case CODE_motor_ctrl_mode:	// 
		strncpy(codes->disp, "motor_ctrl_mode",40);
		if( cmd == CMD_WRITE_RAM ) motor_ctrl_mode = (codes->code_value).ints;
		set_code_default_int(0,7,7,motor_ctrl_mode,0,codes);
		break;
	
	case CODE_motor_direction_change:	
		strncpy(codes->disp, "motor_direction_change ON(1)/OFF",40);
		if( cmd == CMD_WRITE_RAM ) motor_direction_change = (codes->code_value).ints;
		set_code_default_int(0,1,0,motor_direction_change,0,codes);
		break;
	
	case CODE_ramp_func_mode:
		strncpy(codes->disp, "ramp_func_mode",40);
		if( cmd == CMD_WRITE_RAM ) ramp_func_mode = (codes->code_value).ints;
		set_code_default_int(0,3,0,ramp_func_mode,0,codes);
		break;
	
	case CODE_accel_time1:	
		strncpy(codes->disp, "accel_time1 (sec)",40);
		if( cmd == CMD_WRITE_RAM ) accel_time1 = (codes->code_value).doubles;
		set_code_default_double(0.0,3000.0,5.0,accel_time1,0,codes);
		break;
	
	case CODE_decel_time1:
		strncpy(codes->disp, "decel_time1 (sec)",40);
		if( cmd == CMD_WRITE_RAM ) decel_time1 = (codes->code_value).doubles;
		set_code_default_double(0.0,3000.0,5.0,decel_time1,0,codes);
		break;
	
	case CODE_accel_time2:	
		strncpy(codes->disp, "accel_time2 (sec)",40);
		if( cmd == CMD_WRITE_RAM ) accel_time2 = (codes->code_value).doubles;
		set_code_default_double(0.0,3000.0,5.0,accel_time2,0,codes);
		break;
	
	case CODE_decel_time2:	
		strncpy(codes->disp, "decel_time2 (sec)",40);
		if( cmd == CMD_WRITE_RAM ) decel_time2 = (codes->code_value).doubles;
		set_code_default_double(0.0,3000.0,5.0,decel_time2,0,codes);
		break;
	
	case CODE_btn_start_ref:	
		strncpy(codes->disp, "btn_start_ref(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) btn_start_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.0,btn_start_ref,0,codes);
		break;
	
	case CODE_jog_speed:	
		strncpy(codes->disp, "jog_speed (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) jog_speed = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.05,jog_speed,0,codes);
		break;
	
	case CODE_min_vf_ref:	
		strncpy(codes->disp, "min_vf_ref (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) min_vf_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,0.5,0.01,min_vf_ref,0,codes);
		break;

	case CODE_use_binary_input:		
		strncpy(codes->disp, "use_binary_input Set(1)/Off(0)",40);
		if( cmd == CMD_WRITE_RAM ) use_binary_input = (codes->code_value).ints;
		set_code_default_int(0,1,0,use_binary_input,0,codes);
		break;
	
//--------------------------------------
//
	case CODE_digital_speed1:	
		strncpy(codes->disp, "digital_speed1 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) digital_speed1 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.5,0.1,digital_speed1,0,codes);
		break;

	case CODE_digital_speed2:	
		strncpy(codes->disp, "digital_speed2 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) digital_speed2 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.5,0.2,digital_speed2,0,codes);
		break;

	case CODE_digital_speed3:	
		strncpy(codes->disp, "digital_speed3 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) digital_speed3 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.5,0.3,digital_speed3,0,codes);
		break;

	case CODE_digital_speed4:	
		strncpy(codes->disp, "digital_speed1 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) digital_speed4 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.5,0.4,digital_speed4,0,codes);
		break;

	case CODE_digital_speed5:	
		strncpy(codes->disp, "digital_speed5 (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) digital_speed5 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.5,0.5,digital_speed5,0,codes);
		break;

	case CODE_input_func_select0:	
		strncpy(codes->disp, "input_func_select0",40);
		if( cmd == CMD_WRITE_RAM ) input_func_select0 = (codes->code_value).ints;
		set_code_default_int(0,29,0,input_func_select0,0,codes);
		break;

	case CODE_input_func_select1:	
		strncpy(codes->disp, "input_func_select1",40);
		if( cmd == CMD_WRITE_RAM ) input_func_select1 = (codes->code_value).ints;
		set_code_default_int(0,29,0,input_func_select1,0,codes);
		break;

	case CODE_input_func_select2:	
		strncpy(codes->disp, "input_func_select2",40);
		if( cmd == CMD_WRITE_RAM ) input_func_select2 = (codes->code_value).ints;
		set_code_default_int(0,29,2,input_func_select2,0,codes);
		break;

	case CODE_input_func_select3:	
		strncpy(codes->disp, "input_func_select3",40);
		if( cmd == CMD_WRITE_RAM ) input_func_select3 = (codes->code_value).ints;
		set_code_default_int(0,29,3,input_func_select3,0,codes);
		break;

	case CODE_input_func_select4:	
		strncpy(codes->disp, "input_func_select4",40);
		if( cmd == CMD_WRITE_RAM ) input_func_select4 = (codes->code_value).ints;
		set_code_default_int(0,29,4,input_func_select4,0,codes);
		break;
	case CODE_GROUP0_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}

int get_code_group1(int addr ,int cmd, CODE_INFO * codes)
{
	switch(addr)
	{
	case CODE_brake_on_up_ref:	
		strncpy(codes->disp, "brake_on_up_ref(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) brake_on_up_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.005,brake_on_up_ref,0,codes);
		break;
	
	case CODE_brake_on_down_ref:	
		strncpy(codes->disp, "brake_on_down_ref(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) brake_on_down_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.005,brake_on_down_ref,0,codes);
		break;
	
	case CODE_brake_off_up_ref:	
		strncpy(codes->disp, "brake_off_up_ref(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) brake_off_up_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.005,brake_off_up_ref,0,codes);
		break;
	
	case CODE_brake_off_down_ref:	
		strncpy(codes->disp, "brake_off_down_ref(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) brake_off_down_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.005,brake_off_down_ref,0,codes);
		break;
	
	case CODE_brake_on_delay_time:	
		strncpy(codes->disp, "brake_on_delay_time(sec)",40);
		if( cmd == CMD_WRITE_RAM ) brake_on_delay_time = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.25,brake_on_delay_time,0,codes);
		break;
	
	case CODE_brake_off_dealy_time:	
		strncpy(codes->disp, "brake_off_dealy_time(sec)",40);
		if( cmd == CMD_WRITE_RAM ) brake_off_dealy_time = (codes->code_value).doubles;
		set_code_default_double(0.0,5.0,0.25,brake_off_dealy_time,0,codes);
		break;
	
	case CODE_brake_torq_boost_time:	
		strncpy(codes->disp, "brake_torq_boost_time (sec)",40);
		if( cmd == CMD_WRITE_RAM ) brake_torq_boost_time = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.25,brake_torq_boost_time,0,codes);
		break;

#if HYD_UNIT

	case CODE_hyd_sensor_set_ref:	// ���м��� ���� �� 
		strncpy(codes->disp, "hyd_sensor_set_ref(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) hyd_sensor_set_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.5,hyd_sensor_set_ref,0,codes);
		break;

	case CODE_hyd_high_speed_on_ratio:	// high speed�� �����ϴ� ���ذ�  
		strncpy(codes->disp, "hyd_high_speed_on_ratio(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) hyd_high_speed_on_ratio = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.8,hyd_high_speed_on_ratio,0,codes);
		break;

	case CODE_hyd_idle_ref:	// idle speed ref
		strncpy(codes->disp, "hyd_idle_ref(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) hyd_idle_ref = (codes->code_value).doubles;
		set_code_default_double(0.0,0.5,0.1,hyd_idle_ref,0,codes);
		break;

	case CODE_hyd_max_ref:	// max (high) speed ref 
		strncpy(codes->disp, "hyd_max_ref(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) hyd_max_ref = (codes->code_value).doubles;
		set_code_default_double(0.2,2.0,1.0,hyd_max_ref,0,codes);
		break;

	case CODE_hyd_decel_time:	// decel time to idle speed 
		strncpy(codes->disp, "hyd_decel_time(sec)",40);
		if( cmd == CMD_WRITE_RAM ) hyd_decel_time = (codes->code_value).doubles;
		set_code_default_double(0.0,30.0,3.0,hyd_decel_time,0,codes);
		break;
#endif

	case CODE_GROUP1_END:
		return -2;
			
	default:
		return -1;
	}
	return 0;
}

int get_code_group2(int addr ,int cmd, CODE_INFO * codes )
{
	
	switch(addr)
	{
	case CODE_analog_cmd_in_zero1:	
		strncpy(codes->disp, "Analog Cmd1 in Zero",40);
		if( cmd == CMD_WRITE_RAM ) analog_cmd_in_zero1 = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,analog_cmd_in_zero1,0,codes);
		break;

	case CODE_analog_cmd_in_span1:	
		strncpy(codes->disp, "Analog Cmd1 in Span",40);
		if( cmd == CMD_WRITE_RAM ) analog_cmd_in_span1 = (codes->code_value).doubles;
		set_code_default_double(0.5,2.0,1.0,analog_cmd_in_span1,0,codes);
		break;

	case CODE_analog_cmd_in_zero2:	
		strncpy(codes->disp, "Analog Cmd2 in Zero",40);
		if( cmd == CMD_WRITE_RAM ) analog_cmd_in_zero2 = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,analog_cmd_in_zero2,0,codes);
		break;

	case CODE_analog_cmd_in_span2:	
		strncpy(codes->disp, "Analog Cmd2 in Span",40);
		if( cmd == CMD_WRITE_RAM ) analog_cmd_in_span2 = (codes->code_value).doubles;
		set_code_default_double(0.5,2.0,1.0,analog_cmd_in_span2,0,codes);
		break;

	case CODE_analog_out_select1:		
		strncpy(codes->disp, "analog_out_select1",40);
		if( cmd == CMD_WRITE_RAM ) analog_out_select1 = (codes->code_value).ints;
		set_code_default_int(0,9,0,analog_out_select1,0,codes);
		break;

	case CODE_analog_out_zero1:	
		strncpy(codes->disp, "analog_out_zero1",40);
		if( cmd == CMD_WRITE_RAM ) analog_out_zero1 = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,analog_out_zero1,0,codes);
		break;

	case CODE_analog_out_span1:	
		strncpy(codes->disp, "analog_out_span1",40);
		if( cmd == CMD_WRITE_RAM ) analog_out_span1 = (codes->code_value).doubles;
		set_code_default_double(0.5,2.0,1.0,analog_out_span1,0,codes);
		break;

	case CODE_analog_out_offset1:	
		strncpy(codes->disp, "analog_out_offset1",40);
		if( cmd == CMD_WRITE_RAM ) analog_out_offset1 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.0,analog_out_span1,0,codes);
		break;

//--- Analog Monitor 2
	case CODE_analog_out_select2:		
		strncpy(codes->disp, "analog_out_select1",40);
		if( cmd == CMD_WRITE_RAM ) analog_out_select1 = (codes->code_value).ints;
		set_code_default_int(0,9,0,analog_out_select1,0,codes);
		break;

	case CODE_analog_out_zero2:	
		strncpy(codes->disp, "analog_out_zero2",40);
		if( cmd == CMD_WRITE_RAM ) analog_out_zero2 = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,analog_out_zero2,0,codes);
		break;

	case CODE_analog_out_span2:	
		strncpy(codes->disp, "analog_out_span2",40);
		if( cmd == CMD_WRITE_RAM ) analog_out_span2 = (codes->code_value).doubles;
		set_code_default_double(0.5,2.0,1.0,analog_out_span2,0,codes);
		break;

	case CODE_analog_out_offset2:	
		strncpy(codes->disp, "analog_out_offset2",40);
		if( cmd == CMD_WRITE_RAM ) analog_out_offset2 = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.0,analog_out_span2,0,codes);
		break;
	case CODE_GROUP2_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}

// Inverter protection 
int get_code_group3(int addr ,int cmd, CODE_INFO * codes)
{

	switch(addr)
	{
	case CODE_over_current_level:	
		strncpy(codes->disp, "over_currebt_level(%)",40);
		if( cmd == CMD_WRITE_RAM ) over_current_level = (codes->code_value).doubles;
		set_code_default_double(20.0,200.0,120.0,over_current_level,0,codes);
		break;
		
	case CODE_over_volt_set:	
		strncpy(codes->disp, "over_volt_set (V)",40);
		if( cmd == CMD_WRITE_RAM ) over_volt_set = (codes->code_value).doubles;
		set_code_default_double(100.0,780.0,370.0,over_volt_set,0,codes);
		break;
		
	case CODE_under_volt_set:	
		strncpy(codes->disp, "under_volt_set(V)",40);
		if( cmd == CMD_WRITE_RAM ) under_volt_set = (codes->code_value).doubles;
		set_code_default_double(50.0,780.0,240.0,under_volt_set,0,codes);
		break;
		
	case CODE_over_speed_level:	
		strncpy(codes->disp, "over_speed_level(%)",40);
		if( cmd == CMD_WRITE_RAM ) over_speed_level = (codes->code_value).doubles;
		set_code_default_double(20.0,200.0,120.0,over_speed_level,0,codes);
		break;
		
	case CODE_e_thermal_level:	
		strncpy(codes->disp, "e_thermal_level (%)",40);
		if( cmd == CMD_WRITE_RAM ) e_thermal_level = (codes->code_value).doubles;
		set_code_default_double(20.0,200.0,120.0,e_thermal_level,0,codes);
		break;
		
	case CODE_pre_charge_time:	
		strncpy(codes->disp, "pre_charge_time",40);
		if( cmd == CMD_WRITE_RAM ) pre_charge_time = (codes->code_value).doubles;
		set_code_default_double(3.0,30.0,5.0,pre_charge_time,0,codes);
		break;
		
	case CODE_Is_Max_Coeff:	
		strncpy(codes->disp, "Is_Max_Coeff (pu)",40);
		if( cmd == CMD_WRITE_RAM ) Is_Max_Coeff = (codes->code_value).doubles;
		set_code_default_double(0.5,2.0,1.5,Is_Max_Coeff,0,codes);
		break;

	case CODE_over_I_time:	
		strncpy(codes->disp, "over_I_time (sec)",40);
		if( cmd == CMD_WRITE_RAM ) over_I_time = (codes->code_value).doubles;
		set_code_default_double(0.5,600.0,60.0,over_I_time,0,codes);
		break;

	case CODE_adc_vdc_100:	
		strncpy(codes->disp, "adc_vdc_100 (sec)",40);
		if( cmd == CMD_WRITE_RAM ) adc_vdc_100 = (codes->code_value).doubles;
		set_code_default_double(500.0,2000.0,965.0,adc_vdc_100,0,codes);
		break;

	case CODE_adc_vdc_300:	
		strncpy(codes->disp, "adc_vdc_300 (sec)",40);
		if( cmd == CMD_WRITE_RAM ) adc_vdc_300 = (codes->code_value).doubles;
		set_code_default_double(1000.0,4000.0,2900.0,adc_vdc_300,0,codes);
		break;

	case CODE_GROUP3_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}

// Motor Parameter

int get_code_group4(int addr ,int cmd, CODE_INFO * codes)
{
	switch(addr)
	{
	case CODE_motor_rate_power:	
		strncpy(codes->disp, "motor_rate_power",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_power = (codes->code_value).doubles;
		set_code_default_double(100,2.0e+6,750,motor_rate_power,0,codes);
		break;
		
	case CODE_motor_rate_volt:	
		strncpy(codes->disp, "motor_rate_volt (Vrms)",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_volt = (codes->code_value).doubles;
		set_code_default_double(100.0,500.0,220.0,motor_rate_volt,0,codes);
		break;
		
	case CODE_motor_rate_current:	
		strncpy(codes->disp, "motor_rate_current (A)",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_current = (codes->code_value).doubles;
		set_code_default_double(1.0,2000.0,3.7,motor_rate_current,0,codes);
		break;
		
	case CODE_motor_rate_hz:	
		strncpy(codes->disp, "motor_rate_hz (Hz)",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_hz = (codes->code_value).doubles;
		set_code_default_double(30.0,120.0,60.0,motor_rate_hz,0,codes);
		break;
		
	case CODE_motor_rate_rpm:	
		strncpy(codes->disp, "motor_rate_rpm",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_rpm = (codes->code_value).doubles;
		set_code_default_double(500,8000.0,1710.0,motor_rate_rpm,0,codes);
		break;
		
	case CODE_motor_pole:	
		strncpy(codes->disp, "motor_pole ",40);
		if( cmd == CMD_WRITE_RAM ) motor_pole = (codes->code_value).ints;
		set_code_default_int(2,20,4,motor_pole,0,codes);
		break;
	
	case CODE_motor_rate_effiency:	
		strncpy(codes->disp, "motor_rate_effiency (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) motor_rate_effiency = (codes->code_value).doubles;
		set_code_default_double(0.2,0.99,0.71,motor_rate_effiency,0,codes);
		break;

#if VECTOR_TEST		
	case CODE_Rs:	
		strncpy(codes->disp, "Motor State Rs(Ohm)",40);
		if( cmd == CMD_WRITE_RAM ) Rs = (codes->code_value).doubles;
		set_code_default_double(0.002,20.0,5.5453,Rs,0,codes);
		break;
		
	case CODE_Rr:	
		strncpy(codes->disp, "Motor Rotor Rr(Ohm)",40);
		if( cmd == CMD_WRITE_RAM ) Rr = (codes->code_value).doubles;
		set_code_default_double(0.002,20.0,5.5453,Rr,0,codes);
		break;
		
	case CODE_Ls:	
		strncpy(codes->disp, "Motor State Ls(H)",40);
		if( cmd == CMD_WRITE_RAM ) Ls = (codes->code_value).doubles;
		set_code_default_double(0.002,1.0,0.252,Ls,0,codes);
		break;
		
	case CODE_Lr:	
		strncpy(codes->disp, "Motor State Lr(H)",40);
		if( cmd == CMD_WRITE_RAM ) Lr = (codes->code_value).doubles;
		set_code_default_double(0.002,1.0,0.252,Lr,0,codes);
		break;
		
	case CODE_Lm:	
		strncpy(codes->disp, "Motor Mutual Lm(H)",40);
		if( cmd == CMD_WRITE_RAM ) Lm = (codes->code_value).doubles;
		set_code_default_double(0.002,1.0,0.232,Lm,0,codes);
		break;
		
	case CODE_Jm:	
		strncpy(codes->disp, "Motor Intertia Jm",40);
		if( cmd == CMD_WRITE_RAM ) Jm = (codes->code_value).doubles;
		set_code_default_double(1.0e-4,100.0,5.0,Jm,0,codes);
		break;
#endif
	case CODE_GROUP4_END:
		return -2;
		
	default:
		return -1;
	}
	return 0;
}

int get_code_group5(int addr ,int cmd, CODE_INFO * codes)
{
	switch(addr)
	{
	case CODE_I_sense_value:	
		strncpy(codes->disp, "I_sense_value (A)",40);
		if( cmd == CMD_WRITE_RAM ) I_sense_value = (codes->code_value).doubles;
		set_code_default_double(5.0,2000.0,15.0,I_sense_value ,0,codes);
		break;
		
	case CODE_u_phase_I_sense_zero:	
		strncpy(codes->disp, "u_phase_I_sense_zero(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) u_phase_I_sense_zero = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,u_phase_I_sense_zero,0,codes);
		break;
		
	case CODE_u_phase_I_sense_span:	
		strncpy(codes->disp, "u_phase_I_sense_span (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) u_phase_I_sense_span = (codes->code_value).doubles;
		set_code_default_double(0.5,1.5,1.0,u_phase_I_sense_span,0,codes);
		break;
		
	case CODE_v_phase_I_sense_zero:	
		strncpy(codes->disp, "v_phase_I_sense_zero(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) v_phase_I_sense_zero = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,v_phase_I_sense_zero,0,codes);
		break;
		
	case CODE_v_phase_I_sense_span:	
		strncpy(codes->disp, "v_phase_I_sense_span (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) v_phase_I_sense_span = (codes->code_value).doubles;
		set_code_default_double(0.5,1.5,1.0,v_phase_I_sense_span,0,codes);
		break;
				
	case CODE_vdc_sense_zero:	
		strncpy(codes->disp, "vdc_sense_zero (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) vdc_sense_zero = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.0,vdc_sense_zero,0,codes);
		break;
		
	case CODE_vdc_sense_span:	
		strncpy(codes->disp, "vdc_sense_span (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) vdc_sense_span = (codes->code_value).doubles;
		set_code_default_double(0.5,1.5,1.0,vdc_sense_span,0,codes);
		break;
		
	case CODE_encoder_pulse_one_turn:	
		strncpy(codes->disp, "encoder_pulse_one_turn 1 turn",40);
		if( cmd == CMD_WRITE_RAM ) encoder_pulse_one_turn = (codes->code_value).ints;
		set_code_default_int(200,2000,1000,encoder_pulse_one_turn,0,codes);
		break;
	
	case CODE_igbt_pwm_freq:	
		strncpy(codes->disp, "igbt_pwm_freq (Hz)",40);
		if( cmd == CMD_WRITE_RAM ) igbt_pwm_freq = (codes->code_value).doubles;
		set_code_default_double(500.0,10000.0,2500.0,igbt_pwm_freq,0,codes);
		break;

	case CODE_adc_u_offset:	
		strncpy(codes->disp, "adc_u_offset",40);
		if( cmd == CMD_WRITE_RAM ) adc_u_offset = (codes->code_value).ints;
		set_code_default_int(1700,2700,2500,adc_u_offset,0,codes);
		break;
	
	case CODE_adc_v_offset:	
		strncpy(codes->disp, "adc_v_offset",40);
		if( cmd == CMD_WRITE_RAM ) adc_v_offset = (codes->code_value).ints;
		set_code_default_int(1700,2700,2500,adc_v_offset,0,codes);
		break;
	
	case CODE_GROUP5_END:
		return -2;
		
	default:
		return -1;
	}
	return 0;
}

int get_code_group6(int addr ,int cmd, CODE_INFO * codes)
{
	switch(addr)
	{

#if USE_ROM_TEST
	case CODE_VF_DeadTimeGain:	
		strncpy(codes->disp, "VF_DeadTimeGain",40);
		if( cmd == CMD_WRITE_RAM ) VF_DeadTimeGain = (codes->code_value).doubles;
		set_code_default_double(0.0,2.0,1.0,VF_DeadTimeGain,0,codes);
		break;
		
	case CODE_VF_ExcitationTime:	
		strncpy(codes->disp, "VF_ExcitationTime",40);
		if( cmd == CMD_WRITE_RAM ) VF_ExcitationTime = (codes->code_value).doubles;
		set_code_default_double(0.0,3.5,1.0,VF_ExcitationTime,0,codes);
		break;
		
	case CODE_VF_Fs_Coeff:	
		strncpy(codes->disp, "VF_Fs_Coeff (p.u)",40);
		if( cmd == CMD_WRITE_RAM ) VF_Fs_Coeff = (codes->code_value).doubles;
		set_code_default_double(0.3,3.0,1.0,VF_Fs_Coeff,0,codes);
		break;
		
	case CODE_VF_Freq_TrqBoost:	
		strncpy(codes->disp, "VF_Freq_TrqBoost",40);
		if( cmd == CMD_WRITE_RAM ) VF_Freq_TrqBoost = (codes->code_value).doubles;
		set_code_default_double(0.0,10.0,1.5, VF_Freq_TrqBoost ,0,codes);
		break;

	case CODE_VF_Vs_Coeff_TrqBoost:	
		strncpy(codes->disp, "VF_Vs_Coeff_TrqBoost",40);
		if( cmd == CMD_WRITE_RAM ) VF_Vs_Coeff_TrqBoost = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.1, VF_Vs_Coeff_TrqBoost ,0,codes);
		break;

	case CODE_VF_Rs_ThermalCoeff:	
		strncpy(codes->disp, "VF_Rs_ThermalCoeff",40);
		if( cmd == CMD_WRITE_RAM ) VF_Rs_ThermalCoeff = (codes->code_value).doubles;
		set_code_default_double(0.8,3.0,1.05, VF_Rs_ThermalCoeff ,0,codes);
		break;

	case CODE_VF_IR_Comp_FilterPole:	
		strncpy(codes->disp, "VF_IR_Comp_FilterPole",40);
		if( cmd == CMD_WRITE_RAM ) VF_IR_Comp_FilterPole = (codes->code_value).doubles;
		set_code_default_double(5.0,1000.0,100.0, VF_IR_Comp_FilterPole ,0,codes);
		break;

	case CODE_VF_Slip_Comp_FilterPole:	
		strncpy(codes->disp, "VF_Slip_Comp_FilterPole",40);
		if( cmd == CMD_WRITE_RAM ) VF_Slip_Comp_FilterPole = (codes->code_value).doubles;
		set_code_default_double(5.0,1000.0,20.0, VF_Slip_Comp_FilterPole ,0,codes);
		break;

	case CODE_VF_Rs:	
		strncpy(codes->disp, "VF_Rs",40);
		if( cmd == CMD_WRITE_RAM ) VF_Rs = (codes->code_value).doubles;
		set_code_default_double(0.0,50.0,0.0, VF_Rs ,0,codes);
		break;

// auto tuning 
	case CODE_AT_Freq_Leq_Req:	
		strncpy(codes->disp, "Freq for find LeqReq(Hz)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Freq_Leq_Req = (codes->code_value).doubles;
		set_code_default_double(5.0,30.0,15.0,AT_Freq_Leq_Req,0,codes);
		break;

	case CODE_AT_Time_Leq_Req:	
		strncpy(codes->disp, "AT_Time_Leq_Req(sec)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Time_Leq_Req = (codes->code_value).doubles;
		set_code_default_double(3.0,30.0,6.0,AT_Time_Leq_Req,0,codes);
		break;

	case CODE_AT_Is_Coeff_Leq_Req:	
		strncpy(codes->disp, "AT_Is_Coeff_Leq_Req(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Is_Coeff_Leq_Req = (codes->code_value).doubles;
		set_code_default_double(0.4,1.5,1.0,AT_Is_Coeff_Leq_Req,0,codes);
		break;

	case CODE_AT_Is_Coeff_Rs:	
		strncpy(codes->disp, "AT_Is_Coeff_Rs(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Is_Coeff_Rs = (codes->code_value).doubles;
		set_code_default_double(0.4,1.5,1.0,AT_Is_Coeff_Rs,0,codes);
		break;

	case CODE_AT_Time_Rs:	
		strncpy(codes->disp, "AT_Time_Rs(sec)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Time_Rs = (codes->code_value).doubles;
		set_code_default_double(3.0,30.0,6.0,AT_Time_Rs,0,codes);
		break;

	case CODE_AT_DeadTimeGain:	
		strncpy(codes->disp, "AT_DeadTimeGain(p.u)",40);
		if( cmd == CMD_WRITE_RAM ) AT_DeadTimeGain = (codes->code_value).doubles;
		set_code_default_double(0.0,1.2,1.0,AT_DeadTimeGain,0,codes);
		break;

	case CODE_AT_Ls_Vs_RAMP:	
		strncpy(codes->disp, "AT_Ls_Vs_RAMP(sec)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Ls_Vs_RAMP = (codes->code_value).doubles;
		set_code_default_double(0.5,5.0,0.5,AT_Ls_Vs_RAMP,0,codes);
		break;

	case CODE_AT_Freq_Ls:	
		strncpy(codes->disp, "AT_Freq_Ls(Hz)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Freq_Ls = (codes->code_value).doubles;
		set_code_default_double(1.5,10.0,4.0,AT_Freq_Ls,0,codes);
		break;

	case CODE_AT_Time_Ls:	
		strncpy(codes->disp, "AT_Time_Ls(sec)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Time_Ls = (codes->code_value).doubles;
		set_code_default_double(4.0,30.0,7.0,AT_Time_Ls,0,codes);
		break;

	case CODE_AT_Ls_DMB_OpenTime:	
		strncpy(codes->disp, "AT_Ls_DMB_OpenTime (sec)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Ls_DMB_OpenTime = (codes->code_value).doubles;
		set_code_default_double(0.0,2.0,0.6,AT_Ls_DMB_OpenTime,0,codes);
		break;

	case CODE_AT_Te_Coeff_Jm:	
		strncpy(codes->disp, "AT_Te_Coeff_Jm",40);
		if( cmd == CMD_WRITE_RAM ) AT_Te_Coeff_Jm = (codes->code_value).doubles;
		set_code_default_double(0.2,1.0,0.5,AT_Te_Coeff_Jm,0,codes);
		break;

	case CODE_AT_Time_Jm:	
		strncpy(codes->disp, "AT_Time_Jm(sec)",40);
		if( cmd == CMD_WRITE_RAM ) AT_Time_Jm = (codes->code_value).doubles;
		set_code_default_double(0.3,2.0,0.4,AT_Time_Jm,0,codes);
		break;

	case CODE_Jm_ID_ENABLE:	
		strncpy(codes->disp, "Estim Jm Enable",40);
		if( cmd == CMD_WRITE_RAM )Jm_ID_ENABLE = (codes->code_value).ints;
		set_code_default_int(0,1,1,Jm_ID_ENABLE,0,codes);
		break;
#endif
	case CODE_posi_duration_time:	
		strncpy(codes->disp, "posi_duration_time (sec)",40);
		if( cmd == CMD_WRITE_RAM ) posi_duration_time = (codes->code_value).doubles;
		set_code_default_double(0.0,30.0,3.0,posi_duration_time,0,codes);
		break;

	case CODE_zero_duration_time:	
		strncpy(codes->disp, "zero_duration_time (sec)",40);
		if( cmd == CMD_WRITE_RAM ) zero_duration_time = (codes->code_value).doubles;
		set_code_default_double(0.0,30.0,3.0,zero_duration_time,0,codes);
		break;

	case CODE_nega_duration_time:	
		strncpy(codes->disp, "nega_duration_time (sec)",40);
		if( cmd == CMD_WRITE_RAM ) nega_duration_time = (codes->code_value).doubles;
		set_code_default_double(0.0,30.0,3.0,nega_duration_time,0,codes);
		break;

	case CODE_test_accel_time:	
		strncpy(codes->disp, "test_accel_time (sec)",40);
		if( cmd == CMD_WRITE_RAM ) test_accel_time = (codes->code_value).doubles;
		set_code_default_double(0.0,30.0,3.0,test_accel_time,0,codes);
		break;

	case CODE_test_decel_time:	
		strncpy(codes->disp, "test_decel_time (sec)",40);
		if( cmd == CMD_WRITE_RAM ) test_decel_time = (codes->code_value).doubles;
		set_code_default_double(0.0,30.0,3.0,test_decel_time,0,codes);
		break;

	case CODE_GROUP6_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}

int get_code_group7(int addr ,int cmd, CODE_INFO * codes)
{

	switch(addr)
	{

#if USE_VECTOR_CODE
	case CODE_wr_FilterPoleCoeff:	// 700
		strncpy(codes->disp, "wr_FilterPoleCoeff",40);
		if( cmd == CMD_WRITE_RAM ) wr_FilterPoleCoeff = (codes->code_value).doubles;
		set_code_default_double(5.0,30.0,15.0,wr_FilterPoleCoeff,0,codes);
		break;

	case CODE_wn_wr_Coeff:	// 701
		strncpy(codes->disp, "wn_wr_Coeff",40);
		if( cmd == CMD_WRITE_RAM ) wn_wr_Coeff = (codes->code_value).doubles;
		set_code_default_double(2.0,30.0,5.0,wn_wr_Coeff,0,codes);
		break;

	case CODE_Max_wn_wr:	// 702
		strncpy(codes->disp, "Max_wn_wr",40);
		if( cmd == CMD_WRITE_RAM ) Max_wn_wr = (codes->code_value).doubles;
		set_code_default_double(0.3,60,24.0,Max_wn_wr,0,codes);
		break;

	case CODE_K_Damp_wr:	// 703
		strncpy(codes->disp, "K_Damp_wr",40);
		if( cmd == CMD_WRITE_RAM ) K_Damp_wr = (codes->code_value).doubles;
		set_code_default_double(0.05,1.0,0.45,K_Damp_wr,0,codes);
		break;

	case CODE_wr_DampingRatio:	// 704
		strncpy(codes->disp, "wr_DampingRatio",40);
		if( cmd == CMD_WRITE_RAM ) wr_DampingRatio = (codes->code_value).doubles;
		set_code_default_double(0.6,1.5,0.8,wr_DampingRatio,0,codes);
		break;

	case CODE_wr_CntlPeriodIndex:	// 705
		strncpy(codes->disp, "wr_CntlPeriodIndex",40);
		if( cmd == CMD_WRITE_RAM ) wr_CntlPeriodIndex = (codes->code_value).ints;
		set_code_default_int(1,30,1,wr_CntlPeriodIndex,0,codes);
		break;

	case CODE_FW_VoltageCoeff:	// 706
		strncpy(codes->disp, "FW_VoltageCoeff",40);
		if( cmd == CMD_WRITE_RAM ) FW_VoltageCoeff = (codes->code_value).doubles;
		set_code_default_double(0.2,1.2,1.0,FW_VoltageCoeff,0,codes);
		break;

	case CODE_Base_Flux_Coeff:	// 707
		strncpy(codes->disp, "Base_Flux_Coeff",40);
		if( cmd == CMD_WRITE_RAM ) Base_Flux_Coeff = (codes->code_value).doubles;
		set_code_default_double(0.1,2.5,0.92,Base_Flux_Coeff,0,codes);
		break;

	case CODE_ExcitationTime:	// 708
		strncpy(codes->disp, "ExcitationTime",40);
		if( cmd == CMD_WRITE_RAM ) ExcitationTime = (codes->code_value).doubles;
		set_code_default_double(0.1,3.0,0.25,ExcitationTime,0,codes);
		break;

	case CODE_K_Damp_Fr:	// 709
		strncpy(codes->disp, "K_Damp_Fr",40);
		if( cmd == CMD_WRITE_RAM ) K_Damp_Fr = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.45,K_Damp_Fr,0,codes);
		break;

	case CODE_GM_Fr:	// 710
		strncpy(codes->disp, "GM_Fr",40);
		if( cmd == CMD_WRITE_RAM ) GM_Fr = (codes->code_value).doubles;
		set_code_default_double(2.5,25.0,7.0,GM_Fr,0,codes);
		break;

	case CODE_PM_Fr:	// 711
		strncpy(codes->disp, "PM_Fr",40);
		if( cmd == CMD_WRITE_RAM ) PM_Fr = (codes->code_value).doubles;
		set_code_default_double(0.15,1.3,0.785,PM_Fr,0,codes);
		break;

	case CODE_K_Damp_Is:	// 715
		strncpy(codes->disp, "K_Damp_Is",40);
		if( cmd == CMD_WRITE_RAM ) K_Damp_Is = (codes->code_value).doubles;
		set_code_default_double(0.1,1.0,0.45,K_Damp_Is,0,codes);
		break;

	case CODE_GM_Is:	// 716
		strncpy(codes->disp, "GM_Is",40);
		if( cmd == CMD_WRITE_RAM ) GM_Is = (codes->code_value).doubles;
		set_code_default_double(2.5,10.0,7.0,GM_Is,0,codes);
		break;

	case CODE_PM_Is:	// 717
		strncpy(codes->disp, "PM_Is",40);
		if( cmd == CMD_WRITE_RAM ) PM_Is = (codes->code_value).doubles;
		set_code_default_double(0.15,1.3,0.785,PM_Is,0,codes);
		break;
//--- vector control
	case CODE_Default_wr_FilterPole:	// 720
		strncpy(codes->disp, "Default_wr_FilterPole",40);
		if( cmd == CMD_WRITE_RAM ) Default_wr_FilterPole = (codes->code_value).doubles;
		set_code_default_double(20.0,500.0,200.0,Default_wr_FilterPole,0,codes);
		break;

	case CODE_SlipCompCoeff:	// 721
		strncpy(codes->disp, "SlipCompCoeff",40);
		if( cmd == CMD_WRITE_RAM ) SlipCompCoeff = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.2,SlipCompCoeff,0,codes);
		break;

	case CODE_GammaLambda:	// 722
		strncpy(codes->disp, "GammaLambda",40);
		if( cmd == CMD_WRITE_RAM ) GammaLambda = (codes->code_value).doubles;
		set_code_default_double(0.0,2.0,1.0,GammaLambda,0,codes);
		break;

	case CODE_GammaLambda_R_Constant:	// 723
		strncpy(codes->disp, "GammaLambda_R_Constant",40);
		if( cmd == CMD_WRITE_RAM ) GammaLambda_R_Constant = (codes->code_value).doubles;
		set_code_default_double(3.0,100.0,20.0,GammaLambda_R_Constant,0,codes);
		break;

	case CODE_Max_DeltaLambda:	// 724
		strncpy(codes->disp, "Max_DeltaLambda",40);
		if( cmd == CMD_WRITE_RAM ) Max_DeltaLambda = (codes->code_value).doubles;
		set_code_default_double(0.0,0.2,0.05,Max_DeltaLambda,0,codes);
		break;

	case CODE_GammaTheta_M:	// 725
		strncpy(codes->disp, "GammaTheta_M",40);
		if( cmd == CMD_WRITE_RAM ) GammaTheta_M = (codes->code_value).doubles;
		set_code_default_double(0.0,1.0,0.2,GammaTheta_M,0,codes);
		break;

	case CODE_GammaTheta_R:	// 726
		strncpy(codes->disp, "GammaTheta_R",40);
		if( cmd == CMD_WRITE_RAM ) GammaTheta_R = (codes->code_value).doubles;
		set_code_default_double(0.0,3.0,1.0,GammaTheta_R,0,codes);
		break;

	case CODE_Max_DeltaTheta:	// 727
		strncpy(codes->disp, "Max_DeltaTheta",40);
		if( cmd == CMD_WRITE_RAM ) Max_DeltaTheta = (codes->code_value).doubles;
		set_code_default_double(0.0,0.05,0.015,Max_DeltaTheta,0,codes);
		break;

	case CODE_Delta_wr_FilterPoleCoeff_L:	// 728
		strncpy(codes->disp, "Delta_wr_FilterPoleCoeff_L",40);
		if( cmd == CMD_WRITE_RAM ) Delta_wr_FilterPoleCoeff_L = (codes->code_value).doubles;
		set_code_default_double(0.1,20.0,0.5,Delta_wr_FilterPoleCoeff_L,0,codes);
		break;

	case CODE_Delta_wr_FilterPoleCoeff_U:	// 729
		strncpy(codes->disp, "Delta_wr_FilterPoleCoeff_U",40);
		if( cmd == CMD_WRITE_RAM ) Delta_wr_FilterPoleCoeff_U = (codes->code_value).doubles;
		set_code_default_double(0.1,20.0,3.0,Delta_wr_FilterPoleCoeff_U,0,codes);
		break;
#endif
	case CODE_GROUP7_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}

int get_code_group8(int addr ,int cmd, CODE_INFO * codes)
{
	int temp_cmd;

	temp_cmd = cmd;	// for warring message 

	switch(addr)
	{
	case CODE_Data_Check:	
		strncpy(codes->disp, "Backup Data Check",40);
		break;

	case CODE_Data_Backup:	
		strncpy(codes->disp, "Code Data Backup",40);
		break;

	case CODE_Data_Load:	
		strncpy(codes->disp, "Backup Data Load",40);
		break;

	case CODE_Data_Init:	
		strncpy(codes->disp, "Backup Data Init",40);
		break;

	case CODE_get_adc_offset:	
		strncpy(codes->disp, "get_adc_offset",40);
		break;

	case CODE_get_adc_vdc_100:	
		strncpy(codes->disp, "get_adc_vdc_100",40);
		break;

	case CODE_get_adc_vdc_300:	
		strncpy(codes->disp, "get_adc_vdc_300",40);
		break;

	case CODE_GROUP8_END:
		return -2;

	default:
		return -1;
	}
	return 0;
}
// end of file





