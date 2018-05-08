#ifndef		__EWINV_DEFINE_
#define		__EWINV_DEFINE_


#define SCIC_TX_BUF_MAX			50
#define SCIC_RX_BUF_MAX			1

#define BUTTON_ROOT				0
#define	BUTTON_SELECT_FUNCTION	1
#define	BUTTON_CHANGE_DATA		2

#define XINT_INPUT			0x0050
#define DO_CP				0x0070

#define BLINK_PERIOD_MSEC	400

#define LED_STOP			0x0002
#define LED_RUN				0x0004
#define LED_ERROR			0x0008
#define LED_ALARM			0x0010
#define LED_COLON			0x0020
#define LED_ALL				0x0040

#define FND_DIGIT0_DP		0x0100
#define FND_DIGIT1_DP		0x0200
#define FND_DIGIT2_DP		0x0400
#define FND_DIGIT3_DP		0x0800

#define BTN_NULL			0
#define BTN_SAVE			1
#define BTN_RUN				2
#define BTN_STOP			3
#define BTN_SET				4
#define BTN_ESC				5
#define BTN_RIGHT			6
#define BTN_UP				7
#define BTN_DOWN			8

#define	BLINK_DIGIT0	0x0001
#define	BLINK_DIGIT1	0x0002
#define	BLINK_DIGIT2	0x0004
#define	BLINK_DIGIT3	0x0008

#define	BLINK_COLON		0x0010
#define	BLINK_STOP		0x0020
#define	BLINK_RUN		0x0040
#define	BLINK_TRIP		0x0080
#define	BLINK_ALARM		0x0100


//*******************************************
// Program Control 
//*******************************************
#define INIT_POWER_USE_PWM		0
#define DEBUG_MODE  			0
#define MAIN_POWER_OFF			0
#define MAIN_POWER_ON			1

#define TRIP_CHECK_ENABLE		1

#define	SCALAR_TEST				1
#define	VECTOR_TEST				1


#define	INV_AUTO_TUNING_TEST	1
#define	AUTO_TUNING_TEST		0

#define	BOOT_ROM_MODE			0
#define	BOOT_RAM_MODE			1

//*******************************************
// Program Control 
//*******************************************

#define EEPROM_RW_DELAY		10	

#define DEAD_TIME_COUNT			320

#define TRIP_BACKUP_ADDR		20000		
#define EPROM_ADDR_TRIP_POINT	30000

typedef struct
{
	signed   byte0	:8;	/* LSB */
	unsigned byte1	:8;
	unsigned byte2	:8;	/* sign + MSB */
	signed   byte3	:8;	/* exponent */
} ROM_DATA;

typedef union
{
	double	dword;			/* float word : 32bit */
	struct
	{
		int word0;		/* 하위 16비트(least siginificant word) */
		int word1;		/* 상위 16비트(most siginificant word) */
	} word;	
	struct
	{
		unsigned byte0	:8;	/* LSB */
		unsigned byte1	:8;
		unsigned byte2	:8;	/* sign + MSB */
		unsigned byte3	:8;	/* exponent */
	} byte;
} UNION32;

//---  New 2008.02.20

// - gMachineState
#define	SWITCHING_TIME			4e-4

#define	STATE_POWER_ON			0
#define	STATE_READY				'0'
#define	STATE_RUN				'1'
#define	STATE_TRIP				'2'
#define	STATE_INIT_RUN			'3'
#define	STATE_GO_STOP			'4'
#define	STATE_WAIT_BREAK_OFF	'5'


// I2C
#define ADDR_24LC32	0x0051		// address of 24ls32 serial eeprom

#define I2C_EEPROM_SLAVE_ADDR 	0x51
#define I2C_NUMBYTES          	4
#define I2C_EEPROM_HIGH_ADDR  	0x00
#define I2C_EEPROM_LOW_ADDR   	0x30

#define CMD_NULL			  	0
#define CMD_START				0x0041	//'A'
#define CMD_STOP				0x0042	//'B'
#define CMD_RESET				0x0043	//'C'
#define CMD_SPEED_UP			0x0044	//'D'	
#define CMD_SPEED_DOWN			0x0045	//'E'
#define CMD_READ_DATA			0x0046	//'F'
#define CMD_WRITE_RAM			0x0047	//'G'
#define CMD_WRITE_ROM			0x0048	//'H'
#define CMD_READ_ALL			0x0049	//'I'
#define CMD_WRITE_ALL			0x004A	//'J'
#define CMD_CODE_MSG			0x004B	//'K'
#define CMD_WRITE_CHECK			0x004C	//'L'
#define CMD_MONITOR				0x004D	//'M'

#define CMD_BTN_SAVE			0x0051	//'Q'

// #define CMD_TIMER				0x004E	//'N'
// #define CMD_TRIP_VIEW			0x004F	//'O'

#define CTRL_SCALAR				0
#define CTRL_VECTOR				1
#define CTRL_TORQ				2
#define CTRL_PARA_ESTIM			3
#define CTRL_TEST				4

#define ID_AT_LEQ_REQ			1
#define ID_AT_RS				2
#define ID_AT_LS				3
#define ID_AT_JM				4

// TripProc.c

#define ADDR_TRIP_VIEW_CODE		'1'

#define ADDR_TRIP_VIEW_MSG		'2'
#define ADDR_TRIP_VIEW_TIME		'3'
#define ADDR_TRIP_VIEW_DATA		'4'

#define ADDR_TRIP_VIEW_I		'5'
#define ADDR_TRIP_VIEW_VDC		'6'
#define ADDR_TRIP_VIEW_HZ		'7'

#endif

