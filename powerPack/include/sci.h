/////////////////////////////////////////////////////////////////////////
//
//	Project Name 	: Input for EW Inverter  
//	Fiele Name	 	: F283x_Sci.h
//
//  Start 			: 2008.05.27 Wednesday
//	Edit 			: 2008.05.21
///////////////////////////////////////////////////////////////////////////
//
// 19600 high speed
//

#ifndef DSP283X_SCI_H
#define DSP283X_SCI_H




#define NUM_SCI_RX_BUF				16			

#define SCI_RX_HEAD_BYTE			0

// define for endless loop
#define MAX_SCI_TX_COUNT 			23
// Sci Tx buf의 크기 설정 
#define NUM_SCI_TX_BUF				23			

#define SCI_CMD_START				0x0041	//'A'
#define SCI_CMD_STOP				0x0042	//'B'
#define SCI_CMD_RESET				0x0043	//'C'
#define SCI_CMD_SPEED_UP			0x0044	//'D'	
#define SCI_CMD_SPEED_DOWN			0x0045	//'E'
#define SCI_CMD_READ_DATA			0x0046	//'F'
#define SCI_CMD_WRITE_RAM			0x0047	//'G'
#define SCI_CMD_WRITE_ROM			0x0048	//'H'
#define SCI_CMD_READ_ALL			0x0049	//'I'
#define SCI_CMD_WRITE_ALL			0x004A	//'J'
#define SCI_CMD_CODE_MSG			0x004B	//'K'
// #define SCI_CMD_WRITE_CHECK			0x004C	//'L'	// debug
#define SCI_CMD_MONITOR				0x004D	//'M'
#define SCI_CMD_TIMER				0x004E	//'N'
#define SCI_CMD_TRIP_VIEW			0x004F	//'O'
#define SCI_CMD_TX_RESET			0x0050	//'P'
#define SCI_CMD_BTN_SAVE			0x0051	//'Q'
// Monitor Address

#define MONITOR_ADDR_RPM			701		// H01
#define MONITOR_ADDR_I_RMS			702
#define MONITOR_ADDR_VDC			703
#define MONITOR_ADDR_INPUT			704


#endif

//========================================
// End of F283X_Sci.h
//========================================
