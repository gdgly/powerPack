#ifndef		_BUTTON_PROC_H_
#define		_BUTTON_PROC_H_

#define led_stop_on() 	( led_state_flag |= LED_STOP )
#define led_stop_off() 	( led_state_flag &= (~LED_STOP) )

#define led_run_on() 	( led_state_flag |= LED_RUN )
#define led_run_off() 	( led_state_flag &= (~LED_RUN))

#define led_trip_on() 	( led_state_flag |= LED_TRIP )
#define led_trip_off()	( led_state_flag &= (~LED_TRIP))

#define led_alarm_on() 	( led_state_flag |= LED_ALARM )
#define led_alarm_off()	( led_state_flag &= (~LED_ALARM))

#define led_colon_on() 	( led_state_flag |= LED_COLON )
#define led_colon_off()	( led_state_flag &= (~LED_COLON))

#define led_all_off()	( led_state_flag = 0 )

#define fnd_digit0_dp_on()	(led_state_flag |= FND_DIGIT0_DP)
#define fnd_digit0_dp_off()	(led_state_flag &= ~FND_DIGIT0_DP)

#define fnd_digit1_dp_on()	(led_state_flag |= FND_DIGIT1_DP)
#define fnd_digit1_dp_off()	(led_state_flag &= ~FND_DIGI1_DP)

#define fnd_digit2_dp_on()	(led_state_flag |= FND_DIGIT2_DP)
#define fnd_digit2_dp_off()	(led_state_flag &= ~FND_DIGIT2_DP)

#define fnd_digit3_dp_on()	(led_state_flag |= FND_DIGIT3_DP)
#define fnd_digit3_dp_off()	(led_state_flag &= ~FND_DIGIT3_DP)

#define fnd_digit_dp_all_off()	(led_state_flag &= 0xf0ff)

//------------------------------------------
// Fnd blink proc
//------------------------------------------

#define	fnd_blink_all_on()		(fnd_blink_flag = 0xFFFF)
#define	fnd_blink_all_off()		(fnd_blink_flag = 0x0000)

#define fnd_blink_digit0_on()	(fnd_blink_flag |= BLINK_DIGIT0)
#define fnd_blink_digit0_off()	(fnd_blink_flag &= (~BLINK_DIGIT0))

#define fnd_blink_digit1_on()	(fnd_blink_flag |= BLINK_DIGIT1)
#define fnd_blink_digit1_off()	(fnd_blink_flag &= (~BLINK_DIGIT1))

#define fnd_blink_digit2_on()	(fnd_blink_flag |= BLINK_DIGIT2)
#define fnd_blink_digit2_off()	(fnd_blink_flag &= (~BLINK_DIGIT2))

#define fnd_blink_digit3_on()	(fnd_blink_flag |= BLINK_DIGIT3)
#define fnd_blink_digit3_off()	(fnd_blink_flag &= (~BLINK_DIGIT3))

#define fnd_blink_colon_on()	(fnd_blink_flag |= BLINK_COLON)
#define fnd_blink_colon_off()	(fnd_blink_flag &= (~BLINK_COLON))

#define fnd_blink_stop_on()		(fnd_blink_flag |= BLINK_STOP)
#define fnd_blink_stop_off()	(fnd_blink_flag &= (~BLINK_STOP))

#define fnd_blink_run_on()		(fnd_blink_flag |= BLINK_RUN)
#define fnd_blink_run_off()		(fnd_blink_flag &= (~BLINK_RUN))

#define fnd_blink_trip_on()		(fnd_blink_flag |= BLINK_TRIP)
#define fnd_blink_trip_off()	(fnd_blink_flag &= (~BLINK_TRIP))

#define fnd_blink_alarm_on()	(fnd_blink_flag |= BLINK_ALARM)
#define fnd_blink_alarm_off()	(fnd_blink_flag &= (~BLINK_ALARM))

#endif

