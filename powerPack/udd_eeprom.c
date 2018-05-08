//###########################################################################
//
// FILE:    I2c_eeprom.c
//
// Project : SeoHo Inverter  I2C_eeprom.c
//
// ASSUMPTIONS:
//
//    This program requires an external I2C EEPROM connected to
//    the I2C bus at address 0x51.
//###########################################################################
#include	<header.h>
#include	<extern.h>

void I2CA_Init(void)
{
   // Initialize I2C
   I2caRegs.I2CSAR = I2C_EEPROM_SLAVE_ADDR;		// Slave address - EEPROM control code

	I2caRegs.I2CPSC.all = 749;	    // Prescaler - need 7-12 Mhz on module clk (75M/750 = 0.1MHz)

   I2caRegs.I2CCLKL = 20;			// NOTE: must be non zero
   I2caRegs.I2CCLKH = 10;			// NOTE: must be non zero

	I2caRegs.I2CIER.all = 0x0;		// disable all i2c irq 2008.05.11

   I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset
   									// Stop I2C when suspended
   I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,

}

Uint16 I2CA_WriteData(int iSlaveAddr,int iMemAddr,int iData)
{
// write data
	I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset

	BACKUP_ENABLE;
	Nop(); 	Nop(); 	Nop(); Nop();

	I2caRegs.I2CFFTX.bit.TXFFINTCLR = 1;	 
	I2caRegs.I2CCNT = 3;
   I2caRegs.I2CSAR = iSlaveAddr;
  	I2caRegs.I2CDXR = (iMemAddr >> 8) & 0x00ff;			// ���� ����Ʈ 
  	I2caRegs.I2CDXR = iMemAddr & 0x00ff;	// ���� ����Ʈ 
	I2caRegs.I2CDXR = iData;		// byte write �� �ȴ�. 
  	I2caRegs.I2CMDR.all = 0x6E20;			

	Nop();

	delay_msecs(EEPROM_RW_DELAY);
	Nop();

	while(I2caRegs.I2CSTR.bit.SCD == 0); 
	BACKUP_DISABLE;
	Nop();	Nop(); 	Nop();

   return I2C_SUCCESS;
}

Uint16 I2CA_ReadData(int iSlaveAddr, int iMemAddr, int * data)
{
	// no stop 
   I2caRegs.I2CSAR = iSlaveAddr;
   I2caRegs.I2CCNT = 2;
   I2caRegs.I2CDXR = (iMemAddr>>8) & 0x00ff;
   I2caRegs.I2CDXR = iMemAddr & 0x00ff;
   I2caRegs.I2CMDR.all = 0x6620;			
	Nop();
	delay_msecs(EEPROM_RW_DELAY);
	// 
	while(I2caRegs.I2CSTR.bit.ARDY == 0); 

	I2caRegs.I2CFFRX.bit.RXFFRST = 0;		// RXFIFO Operation disable	 
	I2caRegs.I2CFFRX.bit.RXFFINT = 1;		// RXFIFO Operation disable	 

   I2caRegs.I2CSAR = iSlaveAddr;
   I2caRegs.I2CCNT = 1;
   I2caRegs.I2CMDR.all = 0x6C20;			// Send restart as master receiver stop
	delay_msecs(EEPROM_RW_DELAY);

	while(I2caRegs.I2CSTR.bit.SCD == 0); 
	
 	* data = I2caRegs.I2CDRR;
   return I2C_SUCCESS;
}

int get_eprom_address( int code_address)
{
	int addr;

	if	  (code_address < 100){
		addr = code_address;
	}
	else if(code_address < 200){
		addr = CODE_GROUP0_END + 1 + (code_address -100);
	}
	else if(code_address < 300){
		addr  = CODE_GROUP0_END + (CODE_GROUP1_END - 100);
		addr += code_address -200 + 2;
	}
	else if(code_address < 400){
		addr  = CODE_GROUP0_END + (CODE_GROUP1_END-100) + (CODE_GROUP2_END-200);
		addr += code_address -300 + 3 ;
	}
	else if(code_address < 500){
		addr  = CODE_GROUP0_END + (CODE_GROUP1_END-100) + (CODE_GROUP2_END-200);
		addr += (CODE_GROUP3_END - 300);
		addr += code_address -400 + 4 ;
	}
	else if(code_address < 600){
		addr  = CODE_GROUP0_END + (CODE_GROUP1_END-100) + (CODE_GROUP2_END-200);
		addr += (CODE_GROUP3_END - 300)+(CODE_GROUP4_END - 400);
		addr += code_address -500 + 5;
	}
	else if(code_address < 700){
		addr  = CODE_GROUP0_END + (CODE_GROUP1_END-100) + (CODE_GROUP2_END-200);
		addr += (CODE_GROUP3_END - 300)+(CODE_GROUP4_END - 400)+(CODE_GROUP5_END - 500);
		addr += code_address -600 + 6;
	}
	else if(code_address < 800){
		addr  = CODE_GROUP0_END + (CODE_GROUP1_END-100) + (CODE_GROUP2_END-200);
		addr += (CODE_GROUP3_END - 300)+(CODE_GROUP4_END - 400)+(CODE_GROUP5_END - 500);
		addr += (CODE_GROUP6_END - 600);
		addr += code_address -700 + 7;
	}
	addr = addr * 4;
	return addr;
}		

void write_code_2_eeprom(int address,UNION32 data)
{
	int eprom_addr;

	eprom_addr = get_eprom_address(address);

	I2CA_WriteData(ADDR_24LC32,eprom_addr+0,data.byte.byte0);
	I2CA_WriteData(ADDR_24LC32,eprom_addr+1,data.byte.byte1);
	I2CA_WriteData(ADDR_24LC32,eprom_addr+2,data.byte.byte2);
	I2CA_WriteData(ADDR_24LC32,eprom_addr+3,data.byte.byte3);
}

void read_eprom_data(int address, UNION32 * u32data)
{
	int eprom_addr,iTemp;

	eprom_addr = get_eprom_address(address);
	
	I2CA_ReadData(ADDR_24LC32,eprom_addr+0,&iTemp); (u32data->byte).byte0 = iTemp;	
	I2CA_ReadData(ADDR_24LC32,eprom_addr+1,&iTemp); (u32data->byte).byte1 = iTemp;	
	I2CA_ReadData(ADDR_24LC32,eprom_addr+2,&iTemp); (u32data->byte).byte2 = iTemp;	
	I2CA_ReadData(ADDR_24LC32,eprom_addr+3,&iTemp); (u32data->byte).byte3 = iTemp;	
}

void data_under_proc(int type, UNION32 u32data)
{
	int trip_code;
	double trip_data;
	char str[50]={0};
	
	load_sci_tx_mail_box("Trip : Data Under" );
	delay_msecs(100);

	if(type ==TYPE_INTEGER){
		snprintf( str,30,"Trip data=%d : ",u32data.word.word0);
		load_sci_tx_mail_box( str );

		trip_data = (double) u32data.word.word0;
	}
	else{
		snprintf( str,40,"Trip data=%0.2e : ",u32data.dword);
		load_sci_tx_mail_box( str );
		trip_data = u32data.dword;
	}
	trip_code = 10;	// debug
	trip_recording( trip_code, trip_data,"Data Under");
}

void data_over_proc(int type, UNION32 u32data)
{
	int trip_code;
	double trip_data;
	char str[50]={0};
	
	load_sci_tx_mail_box("Trip : Data Over" );
	delay_msecs(100);

	if(type ==TYPE_INTEGER){
		snprintf( str,30,"Trip data=%d : ",u32data.word.word0);
		load_sci_tx_mail_box( str );
		trip_data = (double) u32data.word.word0;
	}
	else{
		snprintf( str,30,"Trip data=%0.2e : ",u32data.dword);
		load_sci_tx_mail_box( str );
		trip_data = u32data.dword;
	}

	trip_code = 10; // debug
	trip_recording( trip_code, trip_data,"Data Over");
}

void invalid_address_proc(int address )
{
	int trip_code;
	double trip_data;
	char str[50]={0};
	
	load_sci_tx_mail_box("Trip Invalid Address " );
	delay_msecs(100);
	snprintf( str,30,"Trip Address=%d : ",address);
	load_sci_tx_mail_box( str );

	trip_code = address;
	trip_data = 0.0;
	trip_recording( trip_code, trip_data,"Invalid Address");
}
// debug

int check_code_data(UNION32 u32data, CODE_INFO codes )
{
	int return_value;

	if( codes.type == TYPE_INTEGER){
		if( ( codes.code_min.ints) > u32data.word.word0 ){
			data_under_proc(TYPE_INTEGER, u32data);	
			return_value = -1;
		}
		else if( (codes.code_max.ints) < u32data.word.word0 ){
			data_over_proc(TYPE_INTEGER, u32data);	
			return_value = -1;
		}			
		else {
			return_value = 0;
		}	 
	}	
	else {		//  code_inform->Type == TYPE_DOUBLE
		if( ( codes.code_min.doubles) > u32data.dword ){
			data_under_proc(TYPE_DOUBLE, u32data);	
			return_value = -1;
		}
		else if( ( codes.code_max.doubles) < u32data.dword ){
			data_over_proc(TYPE_DOUBLE, u32data);	
			return_value = -1;
		}			
		else {
			return_value = 0;
		}	 
	}	
	return return_value;   
}

int load_code2ram()
{
	UNION32	u32data;
	int check;
	int loop_ctrl,address,cmd,return_value;
	char str[30]={0};

	u32data.dword  = 0.0;

	address = return_value = 0;	// start of address

	loop_ctrl =  1;
	cmd = CMD_READ_DATA;
	address = 0;
	while( loop_ctrl )	
	{
		monitorProc();
		cmd = CMD_READ_DATA;
		check = get_code_information( address, cmd , & code_inform);

		if( check == 0){
			read_eprom_data( address, & u32data);
			check = check_code_data( u32data, code_inform);	// check min and max boundary
			if(check){
				
				TripInfoNow.CODE = address;
				TripInfoNow.VDC = 0.0;
				TripInfoNow.HZ = 0.0;
							
				load_sci_tx_mail_box("\n***************************\n" );
				load_sci_tx_mail_box(" Code Data Error:\n");
				snprintf( str,30," address=%d \n",address);	load_sci_tx_mail_box( str );
				load_sci_tx_mail_box("***************************\n" );
				loop_ctrl = 0;
				return_value = address;
				break;
			}
			else{
				if(( code_inform.type)==TYPE_INTEGER){
					code_inform.code_value.ints = u32data.word.word0;
				}
				else{
			 	 	code_inform.code_value.doubles = u32data.dword;
				}
				// delay_msecs(10);
				cmd = CMD_WRITE_RAM;
				check = get_code_information( address,cmd, & code_inform);
			}
			address++;
		}
		else if( check == -2) address = ( address / 100 )*100 + 100;
		else address ++;

		if( address >= CODE_GROUP7_END ) return 0;
	}
	return return_value;
}
//--- end of file
