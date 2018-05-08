#include	<header.h>
#include	<extern.h>

void monitor_proc()		// need_edit
{
    static int monitorCount=0;
    int i;
	char str[50]= {0};

	Uint32 RunTimeMsec=0 ;
	static unsigned long StartTimeMsec = 0 ;

	RunTimeMsec = ulGetTime_mSec( StartTimeMsec);
	if(RunTimeMsec < 1500) return;	// 1500msec
	StartTimeMsec = ulGetNow_mSec( );

	if( gMachineState == STATE_POWER_ON ){
        load_scia_tx_mail_box(" \n");
		snprintf( gStr1,10,"Vdc =%.f : ",Vdc);
		load_sci_tx_mail_box(gStr1);delay_msecs(10);
		for( i = 0 ; i < 5 ; i++ ){
		    snprintf( str,19,"No%d=%4d : ",i,adc_result[monitorCount]);
	        load_scia_tx_mail_box(str);
		}
	}
	else if( gMachineState == STATE_TRIP ){
        load_scia_tx_mail_box(" \n");
        load_scia_tx_mail_box("TRIP");
        load_scia_tx_mail_box(TripInfoNow.MSG);
        sprintf( gStr1,"CODE=%d : ",TripInfoNow.CODE)    ; load_scia_tx_mail_box(gStr1);
        sprintf( gStr1,"DATA=%.2e : ",TripInfoNow.DATA)    ; load_scia_tx_mail_box(gStr1);
        sprintf( gStr1,"Irms=%.2e : ",TripInfoNow.CURRENT) ; load_scia_tx_mail_box(gStr1);
        sprintf( gStr1,"RPM =%.2e : ",TripInfoNow.RPM)     ; load_scia_tx_mail_box(gStr1);
        sprintf( gStr1,"Vdc =%.2e",TripInfoNow.VDC)     ; load_scia_tx_mail_box(gStr1);
    }
    else {
        load_scia_tx_mail_box("\n");
        load_scia_tx_mail_box(MonitorMsg);
        load_scia_tx_mail_box(" : ");
        sprintf( gStr1,"Out =%.1f",codeRateHz * reference_out); load_scia_tx_mail_box(gStr1);
        load_scia_tx_mail_box(" : ");
        sprintf( gStr1,"Im  =%.1f",rmsIm); load_scia_tx_mail_box(gStr1);
        load_scia_tx_mail_box(" : ");
        sprintf( gStr1,"Ia  =%.1f",rmsIa); load_scia_tx_mail_box(gStr1);
        load_scia_tx_mail_box(" : ");
        sprintf( gStr1,"Vdc =%.f",lpfVdc); load_scia_tx_mail_box(gStr1);
        //load_scia_tx_mail_box("Rod Mckuen Welcome to winter!\n");
	}
}

void GetInputMark(char * str)
{
	strncpy(str,"xxxx",20);			// debug

/*
	char str2[30]= "TEST";
	str2[0] = 'I';
	str2[1] = 'N';
	str2[2] = 'P';
	str2[3] = 'U';
	str2[4] = 'T';
	str2[5] = '[';

	if(terminal_input_state & 0x0001 ) 	str2[6] = 'I';
	else								str2[6] = 'O';

	if(terminal_input_state & 0x0002 ) 	str2[7] = 'I';
	else								str2[7] = 'O';

	if(terminal_input_state & 0x0004 ) 	str2[8] = 'I';
	else								str2[8] = 'O';

	if(terminal_input_state & 0x0008 ) 	str2[9] = 'I';
	else								str2[9] = 'O';

	if(terminal_input_state & 0x0010 ) 	str2[10] = 'I';
	else								str2[10] = 'O';

	if(terminal_input_state & 0x0020 ) 	str2[11] = 'I';
	else								str2[11] = 'O';

	if(terminal_input_state & 0x0040 ) 	str2[12] = 'I';
	else								str2[12] = 'O';

	if(terminal_input_state & 0x0080 ) 	str2[13] = 'I';
	else								str2[13] = 'O';

	str2[18] = ']';
	str2[19] = '_'; 
	str2[20] = 0; 
	strncpy(str,str2,20);
*/
}

//==================================
// End of file.
//==================================

