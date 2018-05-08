#include	"header.h"
#include	"extern.h"


int get_code_information(int address,int cmd , CODE_INFO *  codes)
{
	int return_val;

	return_val = 0;

	if		( address < 100 )
		return_val = get_code_group0( address , cmd, codes );

	else if	( address < 200 )
		return_val = get_code_group1( address , cmd, codes );

	else if	( address < 300 )
		return_val = get_code_group2( address , cmd, codes );

	else if	( address < 400 )	
		return_val = get_code_group3( address , cmd, codes );

	else if	( address < 500 )	
		return_val = get_code_group4( address , cmd, codes );

	else if	( address < 600 )
		return_val = get_code_group5( address , cmd, codes );

	else if	( address < 700 )
		return_val = get_code_group6( address , cmd, codes );

	else if	( address < 800 )
		return_val = get_code_group7( address , cmd, codes );

	else if	( address < 900 )
		return_val = get_code_group8( address , cmd, codes );

	else return_val = -1;

	return return_val;
}

void set_code_default_int( int min, int max, int defaults, int value, int open_level, CODE_INFO * codes )
{
	codes->type 					= TYPE_INTEGER;
	codes->open_level		 		= open_level;
	(codes->code_min).ints 			= min;
	(codes->code_max).ints			= max;
	(codes->code_default).ints		= defaults;
	(codes->code_value). ints		= value;
}

void set_code_default_double(double min, double max, double defaults, double value,int open_level, CODE_INFO * codes )
{
	codes->type 					= TYPE_DOUBLE;
	codes->open_level 				= open_level;
	(codes->code_min).doubles 		= min;
	(codes->code_max).doubles		= max;
	(codes->code_default).doubles 	= defaults;
	(codes->code_value). doubles	= value;
}

// address �� 1000�� ���� ������ ������ �����͸� 
// �˻� �ϴ� ��ƾ 
int check_backup_data()
{
	UNION32	data;
	int i,j,check;
	int loop_control,address,cmd,return_value;
	
	data.dword  = 0.0;

	address = return_value = 0;	// start of address

	cmd = CMD_READ_DATA;
	address = 0;

	loop_control =  1;

	while( loop_control )	
	{
		for( i = 0 ; i <= 7 ; i++){	 // code group �� 6�� 
			for( j = 0; j <= 29 ;j++)
			{
				address = i * 100 + j ;
				check = get_code_information( address, cmd , & code_inform);
				if( !check ){
					
					// debug  address �� ��ũ�� �����ϴ� ����� �߰��� �� 
					// 2009.08.30
					read_eprom_data( address + 1000, & data);
					check = check_code_data(data, code_inform );	// check min and max boundary
					if(check){
						loop_control = 0;
						return_value = -1;
					}
				}
			}
		}
		loop_control =  0;
	}
	return return_value;
}

void save_backup_data()
{
	UNION32	data;
	int i,j,check;
	int address,cmd;
	
	data.dword  = 0.0;

	address = 0;	// start of address

	cmd = CMD_READ_DATA;
	address = 0;

	for( i = 0 ; i <= 6 ; i++){	 // code group �� 6�� 
		for( j = 0; j <= 29 ;j++)
		{
			address = i* 100 +j ;
			check = get_code_information( address, cmd , & code_inform);
			if( !check ){
				read_eprom_data( address, & data);
				write_code_2_eeprom( address + 1000,data);
			}
		}
	}
}
// address 1000�� ���Ѵ�.  


void backup_data_load()
{
	UNION32	data;
	int i,j,check;
	int loop_control,address,cmd;
	
	data.dword  = 0.0;

	address = 0;	// start of address

	cmd = CMD_READ_DATA;
	address = 0;
	loop_control =  1;
	while( loop_control )	
	{
		for( i = 0 ; i <= 7 ; i++){	 // code group �� 6�� 

			for( j = 0; j <= 29 ;j++)
			{
				address = i * 100 + j ;
				check = get_code_information( address, cmd , & code_inform);
				if( !check ){
					read_eprom_data( address+1000, & data);
					write_code_2_eeprom( address,data);

					if( code_inform.type == TYPE_DOUBLE) 
						code_inform.code_value.doubles = data.dword;
					else
						code_inform.code_value.ints = data.word.word0;

					cmd = CMD_WRITE_RAM;
					check = get_code_information( address,cmd, & code_inform);
				}
			}
		}
		loop_control = 0;
	}
}

int SaveDataProc(int addr, double data)
{
	int cmd,i,return_value;
	char SciBuf[30]={0};
	UNION32 u32data,u32data2;

	return_value = 0;

	cmd = CMD_READ_DATA;

	i = get_code_information( addr,cmd,&code_inform); 

	if( i != 0 ) goto _SAVE_ERROR_INVALID_ADDR;   

	if( addr >= 800 ){

		if( data < 1.22 ) goto _SAVE_ERROR_INVALID_DATA; 
		if( data > 1.24 ) goto _SAVE_ERROR_INVALID_DATA; 
		switch(addr)
		{
		case CODE_Data_Check: 	return_value = check_backup_data();	break;
		case CODE_Data_Backup:	save_backup_data();	break;
		case CODE_Data_Load:	backup_data_load();	break;
		case CODE_Data_Init:	init_eprom_data();	break;
		case CODE_get_adc_offset:	get_adc_offset();	break;
		case CODE_get_adc_vdc_100:	get_adc_vdc_100();	break;
		case CODE_get_adc_vdc_300:	get_adc_vdc_300();	break;
		default:
			goto _SAVE_ERROR_INVALID_ADDR;
		}
		return return_value;
	}

	if( code_inform.type == TYPE_INTEGER){
		if( (code_inform.code_min.ints)  > (int)data ){
			goto _SAVE_ERROR_DATA_UNDER;
		}
		else if( (code_inform.code_max.ints) < (int)data){
			goto _SAVE_ERROR_DATA_OVER;
		}
		else {
//			u32data.word.word1 = 0;
			u32data.word.word0 = (int)data;
			read_eprom_data( addr, & u32data2);
			if( u32data.word.word0 != u32data2.word.word0 ){
				write_code_2_eeprom( addr, u32data);
				read_eprom_data( addr, & u32data2);				
				if( u32data.word.word0 != u32data2.word.word0 ) goto _EEPROM_WRITE_ERROR;
				code_inform.code_value.ints = (int)data;
				cmd = CMD_WRITE_RAM;
				get_code_information( addr,cmd, & code_inform);
				load_sci_tx_mail_box("\n OK write success") ;
			}
			else{
				load_sci_tx_mail_box("\n Equal Data write skipped");
			}
			return 0;
		}	 
	}	
	else {		//  code_inform->Type == TYPE_DOUBLE
		if( ( code_inform.code_min.doubles) > data ){
			goto _SAVE_ERROR_DATA_UNDER;
		}
		else if( ( code_inform.code_max.doubles) < data ){
			goto _SAVE_ERROR_DATA_OVER;
		}			
		else {
			u32data.dword = data;
			read_eprom_data( addr, & u32data2);
			if( u32data.dword != u32data2.dword ){
				write_code_2_eeprom( addr, u32data);
				read_eprom_data( addr, & u32data2);

				if( u32data.dword != u32data2.dword ) goto _EEPROM_WRITE_ERROR;

				code_inform.code_value.doubles = data;
				cmd = CMD_WRITE_RAM;
				get_code_information( addr,cmd, & code_inform);
				load_sci_tx_mail_box("\n OK write success") ;
			}
			else{
				load_sci_tx_mail_box("\n Equal Data write skipped");
			}
			return 0;
		}	 
	}	

_SAVE_ERROR_INVALID_ADDR:
//	strcpy(SciBuf, "ADDR");
//	MmiErrMsgBlinkStart(SciBuf);
	strcpy(SciBuf,"\n Invalid Address" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_UNDER:

//	strcpy(SciBuf, "UNDE");
//	MmiErrMsgBlinkStart(SciBuf);

	strcpy(SciBuf,"\n Input data under" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_DATA_OVER:
//	strcpy(SciBuf, "OVER");
//	MmiErrMsgBlinkStart(SciBuf);
	strcpy(SciBuf,"\n Input data over" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_SAVE_ERROR_INVALID_DATA:
//	strcpy(SciBuf, "DATA");
//	MmiErrMsgBlinkStart(SciBuf);
	strcpy(SciBuf,"\n Invalid data " );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;

_EEPROM_WRITE_ERROR:
//	strcpy(SciBuf, "DATA");
//	MmiErrMsgBlinkStart(SciBuf);
	strcpy(SciBuf,"\n Eeprom write error" );
	load_sci_tx_mail_box(SciBuf) ;
	return -1;
}


int init_eprom_data()
{
	UNION32	data,data2;
	int check;
	int address,cmd,loop_ctrl;
	int return_value;

	data.dword  = 0.0;

	cmd = CMD_READ_DATA;
	address = return_value = 0;
	
	loop_ctrl = 1;

	while(loop_ctrl)
	{
		cmd = CMD_READ_DATA;
		check = get_code_information( address, cmd , & code_inform);

		if( check==0 ){
			if( code_inform.type == TYPE_DOUBLE){ 
				data.dword = code_inform.code_default.doubles;
			}
			else{
				data.word.word0 = code_inform.code_default.ints;
			}

			read_eprom_data(address, & data2 );

			if( data.dword != data2.dword)	write_code_2_eeprom( address,data);

			read_eprom_data(address, & data2 );

			if( data.dword != data2.dword)
			{
				loop_ctrl = 0;
				return_value = -1;
				load_scia_tx_mail_box("Trip : eeprom write" );
				delay_msecs(100);
				break;
			}	 
			code_inform.code_value.doubles = data.dword;
			cmd = CMD_WRITE_RAM;
			check = get_code_information( address,cmd, & code_inform);
			address ++;
		}
		else if( check == -2) address = (address/100)*100 + 100;
		else address ++; 		

		if( address >= CODE_GROUP7_END ) return 0;
	}
	return return_value;
}
void readAllCodes()
{
 /*
    int check;
    int addr,cmd;

    cmd = CMD_READ_DATA;
    for( addr = 0 ; addr <= CODE_END ; addr++){
        check = get_code_information( addr, cmd , & code_inform);
        if( !check ){
            snprintf( gStr1,20,"%d,",addr); load_scia_tx_mail_box(gStr1);
            snprintf( gStr1,20,"%.3e,",code_inform.code_value);load_scia_tx_mail_box(gStr1); delay_msecs(10);
            load_scia_tx_mail_box(code_inform.disp);
            snprintf( gStr1,20,",%.3e,",code_inform.code_min);load_scia_tx_mail_box(gStr1); delay_msecs(10);
            snprintf( gStr1,20,"%.3e;",code_inform.code_max);load_scia_tx_mail_box(gStr1); delay_msecs(10);
        }
    }
    load_scia_tx_mail_box("\n");
*/
}

// end of code_proc.c