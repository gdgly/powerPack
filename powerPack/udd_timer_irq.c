/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: Inverter for 
//	Fiele Name	 	: Timer_Irq_Proc.c
//
//  Start 			: 2009.07.09 sunday
//
///////////////////////////////////////////////////////////////////////////
#include	<header.h>
#include	<extern.h>

void NormalFndProc( )
{
/*
    static int digit_count=0;
	int i,j;

	int xint_bus_data,temp;

	if( digit_count >= 4 ) digit_count = 0;
	else				  		  digit_count ++;

	if(fnd_buf[digit_count] < 0 ){
		temp = -fnd_buf[digit_count];
		xint_bus_data = FndTableNumber[temp];
	}
	else if( fnd_buf[digit_count] < 'A' ){
		temp = fnd_buf[digit_count];
		xint_bus_data = FndTableNumber[temp];
	}
	else {
		temp = fnd_buf[digit_count]-'A';;
		xint_bus_data = FndTableChar[temp];
	}

	switch(digit_count){
	case 0:
		if( led_state_flag & FND_DIGIT0_DP ) xint_bus_data |= 0x0080;
		if( blink_toggle && ( fnd_blink_flag & BLINK_DIGIT0 ))	xint_bus_data = 0x0000;	
		break;

	case 1:
		if( led_state_flag & FND_DIGIT1_DP ) xint_bus_data |= 0x0080;
		if( blink_toggle &&( fnd_blink_flag & BLINK_DIGIT1 ))	xint_bus_data = 0x0000;	
		break;

	case 2:
		if( led_state_flag & FND_DIGIT2_DP ) xint_bus_data |= 0x0080;
		if( blink_toggle && ( fnd_blink_flag & BLINK_DIGIT2 ))	xint_bus_data = 0x0000;	
		break;

	case 3:
		if( led_state_flag & FND_DIGIT3_DP ) xint_bus_data |= 0x0080;
		if( blink_toggle && ( fnd_blink_flag & BLINK_DIGIT3 ))	xint_bus_data = 0x0000;	
		break;

	case 4:
		xint_bus_data = led_state_flag; 
		if(blink_toggle){
			if( fnd_blink_flag & BLINK_STOP )	xint_bus_data &= ~LED_STOP;
			if( fnd_blink_flag & BLINK_RUN  )	xint_bus_data &= ~LED_RUN;
			if( fnd_blink_flag & BLINK_TRIP )	xint_bus_data &= ~LED_TRIP;
			if( fnd_blink_flag & BLINK_ALARM )	xint_bus_data &= ~LED_ALARM;
			if( fnd_blink_flag & BLINK_COLON )	xint_bus_data &= ~LED_COLON;
		}
		break;
	}

	i = digit_count;
	j = 0x0001;
	while( i ){ j = j << 1;i--;}
	
	xint_bus_data = ( xint_bus_data << 8 );
	xint_bus_data += j;
	ZONE0_BUF[DO_CP] = ~xint_bus_data;		
*/
}

void WarningFndProc( )
{
/*
    static int digit_count=0;
	int xint_bus_data;
	int i,j;

	warning_timer_msec --;
	if( warning_timer_msec == 0 ){
	 	warning_fnd_flag = 0; // return to normal fnd  
		return;
	}

	if( digit_count >= 4 ) digit_count = 0;
	else				  		  digit_count ++;

	if( blink_toggle && ( fnd_blink_flag & BLINK_DIGIT0 ))	xint_bus_data = 0x0000;	

	i = digit_count;
	j = 0x0001;
	while( i ){
		j = j << 1
		;i--;
		Nop();
	}
	
	xint_bus_data = warning_fnd_data[digit_count];
	xint_bus_data = ( xint_bus_data << 8 ) & 0xFF00;
	xint_bus_data += j;
	Nop();
	ZONE0_BUF[DO_CP] = ~xint_bus_data;		
*/
}

interrupt void cpu_timer0_isr(void)
{
	static Uint32 blink_toggle_msec;
	CpuTimer0.InterruptCount++;
	blink_toggle_msec ++;
	gfRunTime += 0.001;
	ref_time += 0.001;

	if( BLINK_PERIOD_MSEC < blink_toggle_msec ){
		blink_toggle_msec = 0;
		if( blink_toggle ) 	blink_toggle = 0;
		else				blink_toggle = 1;
	}

	Nop();
	ServiceDog();
	if(warning_fnd_flag) WarningFndProc();
	else	NormalFndProc();

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}