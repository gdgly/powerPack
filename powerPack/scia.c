#include	<header.h>
#include	<extern.h>
// include <scia,h>

// #define UARTA_BAUD_RATE			60		// 38400 PLL 5
#define UARTA_BAUD_RATE			120		// 38400

#define SCIA_RX_BUF_MAX		20
#define SCIA_TX_BUF_MAX		100

int scia_rx_start_addr=0;
int scia_rx_end_addr=0;

int scia_tx_start_addr=0;
int scia_tx_end_addr=0;
int scia_rx_msg_flag = 0;

char scia_rx_msg_box[SCIA_RX_BUF_MAX] = {0};
char scia_tx_msg_box[SCIA_TX_BUF_MAX] = {0};

void scia_fifo_init()
{
	SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
	                              // No parity,8 char bits,
	                              // async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
	                              // Disable RX ERR, SLEEP, TXWAKE

	SciaRegs.SCICTL2.bit.TXINTENA 	=1;	// debug
	SciaRegs.SCICTL2.bit.RXBKINTENA 	=0;
	SciaRegs.SCIHBAUD = 0x0000;
	SciaRegs.SCILBAUD = UARTA_BAUD_RATE;
	SciaRegs.SCICCR.bit.LOOPBKENA =0; // Enable loop back

	SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag
	SciaRegs.SCIFFTX.bit.SCIFFENA=1;
	//   ScicRegs.SCIFFTX.bit.TXFFINTCLR=1;

	SciaRegs.SCIFFTX.all=0xC020;
//****************************************************************

//	SciaRegs.SCIFFRX.all=0x0000;
//	SciaRegs.SCIFFRX.bit.RXFFIL = 0;	// irq 13 byte receive 
	ScibRegs.SCIFFRX.bit.RXFFIL 	= 13;	// 13	debug
	ScibRegs.SCIFFRX.bit.RXFFIENA 	= 1;	// 1
	ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;	// 1
	ScibRegs.SCIFFRX.bit.RXFFINT 	= 0;	// 1
	ScibRegs.SCIFFRX.bit.RXFFST		= 0;	// 5
	ScibRegs.SCIFFRX.bit.RXFIFORESET= 1;	// 1
	ScibRegs.SCIFFRX.bit.RXFFOVRCLR	= 1;	// 1
	ScibRegs.SCIFFRX.bit.RXFFOVF	= 0;	// 1
//*******************************************************************

	SciaRegs.SCIFFTX.bit.TXFFIL = 0;	// irq 15 byte receive 
	SciaRegs.SCIFFCT.all=0x00;

	SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
	SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
	SciaRegs.SCIFFRX.bit.RXFIFORESET=1;


	PieCtrlRegs.PIEIER9.bit.INTx1=1;     // SCI_RX_INT_A --> PIE Group 9, INT1
	PieCtrlRegs.PIEIER9.bit.INTx2=1;     // SCI_TX_INT_A --> PIE Group 9, INT1
	IER |= M_INT9;		// scia irq 
}

void scia_tx_msg( char * st)
{
	int i =0;
	char * str;

	str = st;

	while( *str !='\0'){		
		SciaRegs.SCITXBUF= * str++;     // Send data
		
		if(i < 16) i++;
		else 		break;
	}
}

int load_scia_tx_mail_box_char( char msg)
{
    if( msg == 0 ) return -1;

    scia_tx_msg_box[scia_tx_end_addr] = msg;

    if(scia_tx_end_addr < ( SCIA_TX_BUF_MAX-1)) scia_tx_end_addr ++;
    else                                        scia_tx_end_addr = 0;

    if(scia_tx_end_addr == scia_tx_start_addr){
        if(scia_tx_end_addr < (SCIA_TX_BUF_MAX-1)) scia_tx_start_addr++;
        else                                        scia_tx_start_addr = 0;
    }
    return 0;
}
void load_scia_tx_mail_box( char * st)
{
	int loop_ctrl = 1;
	char * str;

	str = st;

	SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag

	while(loop_ctrl){
 		scia_tx_msg_box[scia_tx_end_addr] = * str++;
		
		if(scia_tx_end_addr < ( SCIA_TX_BUF_MAX-1)) scia_tx_end_addr ++;
		else										scia_tx_end_addr = 0;

		if(scia_tx_end_addr == scia_tx_start_addr){
			if(scia_tx_end_addr < (SCIA_TX_BUF_MAX-1)) scia_tx_start_addr++;
			else										scia_tx_start_addr = 0;
		}
		if( *str == '\0') loop_ctrl = 0;
	}
	SciaRegs.SCIFFTX.bit.TXFFIENA = 1;	// Clear SCI Interrupt flag
}
		
interrupt void sciaTxFifoIsr(void)
{
    Uint16 i=0;

	while( scia_tx_end_addr != scia_tx_start_addr){

 		SciaRegs.SCITXBUF = scia_tx_msg_box[scia_tx_start_addr];

		if(scia_tx_start_addr < ( SCIA_TX_BUF_MAX-1)) scia_tx_start_addr ++;
		else											scia_tx_start_addr=0;

		if(scia_tx_end_addr == scia_tx_start_addr) break;

		i++;
		if( i > 15 ) break;
	}

	if(scia_tx_end_addr == scia_tx_start_addr) 

	SciaRegs.SCIFFTX.bit.TXFFIENA = 0;	// Clear SCI Interrupt flag

	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;	// Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x0100;     // IN9 
}

interrupt void sciaRxFifoIsr(void)
{
	int i;

	for( i =0 ; i< 13 ; i++){ 
		scia_rx_msg_box[i] = SciaRegs.SCIRXBUF.all;	 // Read data
	}
	
	SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

	scia_rx_msg_flag = 1;

	PieCtrlRegs.PIEACK.all|=0x0100;     // IN9 
}

// read data format   "9:4:123:x.xxxe-x"
// write data format  "9:6:123:1.234e-3"
void scia_cmd_proc( int * sci_cmd, double * sci_ref)
{
	double data;
	int addr,check;
	char str[30]={0};
	 
	* sci_cmd = CMD_NULL;
	* sci_ref = 0.0;

	if( scia_rx_msg_flag == 0) return;

	scia_rx_msg_flag = 0;

	if ( scia_rx_msg_box[0] != '9') return;
	
	addr =  (scia_rx_msg_box[4]- '0')* 100 +(scia_rx_msg_box[5]- '0')*10 + (scia_rx_msg_box[6]- '0');
	scia_rx_msg_box[16]=0;
	data =  atof( & scia_rx_msg_box[8]);
	
	// regist write function decoding
	if( scia_rx_msg_box[2] == '6'){
		if( addr == 900 ){
			check = (int)data;
			if(check == 10){
				* sci_cmd = CMD_START; * sci_ref = data;
				load_scia_tx_mail_box("\n UART CMD_START");		
			}
			else if( check == 20 ){
				* sci_cmd = CMD_STOP;  * sci_ref = 0.0;
				load_scia_tx_mail_box("\n UART CMD_STOP");		
			}
			else if( check == 30 ){
				* sci_cmd = CMD_RESET;  * sci_ref = 0.0;
				load_scia_tx_mail_box("\n UART CMD_RESET");		
			}
			else if( data == 40 ){
				* sci_cmd = CMD_SAVE;  * sci_ref = 0.0;
				load_scia_tx_mail_box("\n UART CMD_SAVE");		
			}
			else if( data == 80 ){
				* sci_cmd = CMD_NULL;  * sci_ref = 0.0;
				get_adc_offset();
			}
			else if( data == 90 ){
				* sci_cmd = CMD_NULL;  * sci_ref = 0.0;
				load_scia_tx_mail_box("\n EEPROM init Start");		
				check = init_eprom_data();		// 0�� �ƴϸ� address value
				if( check != 0) load_scia_tx_mail_box("\n EEPROM init Fail");		
				else		load_scia_tx_mail_box("\n EEPROM init Success");
			}
			else{
				load_scia_tx_mail_box("\n Illegal CMD data");		
			}
		}
		else{
			// registor_write_proc(addr,data);
			check = SaveDataProc(addr, data);
			Nop();
		}
	}
	else if(scia_rx_msg_box[2] == '4'){
	
		if(addr == 901){	//	monitor state
			check = (int)data;
			if(check == 0){
				switch(gMachineState){
					case STATE_POWER_ON:	load_scia_tx_mail_box("\n POWER_ON"); break;		
					case STATE_READY: 		load_scia_tx_mail_box("\n STATE_READY"); break;		
					case STATE_RUN: 		load_scia_tx_mail_box("\n STATE_RUN"); break;		
					case STATE_TRIP: 		load_scia_tx_mail_box("\n STATE_TRIP"); break;		
					case STATE_INIT_RUN: 	load_scia_tx_mail_box("\n STATE_INIT_RUN"); break;		
					case STATE_GO_STOP: 	load_scia_tx_mail_box("\n STATE_GO_STOP"); break;		
					case STATE_WAIT_BREAK_OFF: load_scia_tx_mail_box("\n STATE_WAIT_BREAK_OFF"); break;	
					default: 				load_scia_tx_mail_box("\n Unknown State"); break;
				}
			}
			return;
		}
		else if(addr == 902){	//	���� ���� read
			check = (int)data;
			
			// check �� ���� ������ �����ͷ� �ξ ó�� �Ѵ�. 
			snprintf( str,30,"\n Vdc =%10.3e \n",Vdc);	load_scia_tx_mail_box(str); 
			return;
		}

		check = get_code_information( addr, CMD_READ_DATA , & code_inform);
	
		if( check == 0 ){
			load_scia_tx_mail_box(code_inform.disp);		
			if( code_inform.type == TYPE_DOUBLE )
				snprintf( str,30," :: read data =%10.3e \n",code_inform.code_value.doubles);
			else
				snprintf( str,30," :: read data =%10d \n",code_inform.code_value.ints);
			
			load_scia_tx_mail_box(str);		
		}
		else{
			load_scia_tx_mail_box("Error Invalid Address");		
		}
	}
}
//--- end of file
