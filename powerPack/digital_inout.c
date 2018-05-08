#include	<header.h>
#include	<extern.h>

void set_digit_input_funtion(int , int function_option );
void digit_run_dir_chk( );

double multi_step_proc( );
void fault_reset(){	Nop();}
void driver_enable_proc(){	Nop();}
void input_ai_ref_active_proc(){	Nop();}
void input_ai_local_remote_proc(){	Nop();}
void input_ext_fault_b_proc(){	Nop();}
void input_motor_select_proc(){	Nop();}
void input_mb_brake_state_proc(){	Nop(); }
void input_acel_decel_switch_proc(){	Nop();}
void input_ref_tunning_inc_proc(){	Nop();}
void input_ref_tunning_dec_proc(){	Nop();}
void input_acc_dec_byp_proc(){	Nop();}

void input_ext_fault_a_proc()
{
	trip_recording( TRIP_EXT_A, gfRunTime,"TRIP EXT A: runtime save");
	gPWMTripCode = TRIP_EXT_A;
}

int input_state(int port)
{
}
void set_digit_input_funtion( int input_state, int function_option )
{
}
double multi_step_proc( )
{
}
void digit_run_dir_chk( )
{
}
void digital_input_proc(int * cmd, double * ref )
{
}
int digital_port_check( int out_function )
{
}  	
void digital_out_proc()		// debug
{
}
// end of file
