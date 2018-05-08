// EwInv File $Revision: /main/2 $
// Checkin $Date: May 13, 2008   21:50:** $
//###########################################################################
//
// FILE:	io_define.h
//
// Project:	EwInv F28335  _080413
// TITLE:	s.

#ifndef		__DIGITAL_INOUT_H_
#define		__DIGITAL_INOUT_H_
     // Set Output High

#define SIGNAL2_SET         (GpioDataRegs.GPASET.bit.GPIO8 = 1)
#define SIGNAL2_CLEAR       (GpioDataRegs.GPACLEAR.bit.GPIO8 = 1)

#define J8_2_SET            (GpioDataRegs.GPASET.bit.GPIO8 = 1)
#define J8_2_CLEAR          (GpioDataRegs.GPACLEAR.bit.GPIO8 = 1)

#define digital_out0_on()   (GpioDataRegs.GPASET.bit.GPIO13 = 1)    // relayOutAux1
#define digital_out0_off()  (GpioDataRegs.GPACLEAR.bit.GPIO13 = 1)  // relayOutAux1

#define digital_out1_on()   (GpioDataRegs.GPASET.bit.GPIO11 = 1)    // relayTripOut
#define digital_out1_off()  (GpioDataRegs.GPACLEAR.bit.GPIO11 = 1)  // relayTripOut

#define TRIP_OUT_ON     (digital_out1_on())
#define TRIP_OUT_OFF    (digital_out1_off())

#define RUN_OUT_ON      (digital_out0_on())
#define RUN_OUT_OFF     (digital_out0_off())
//#define digital_out0_on()   (GpioDataRegs.GPASET.bit.GPIO13 = 1)    // relayOutAux1
//#define digital_out0_off()  (GpioDataRegs.GPACLEAR.bit.GPIO13 = 1)  // relayOutAux1

#define MAIN_CHARGE_OFF     (GpioDataRegs.GPACLEAR.bit.GPIO10 = 1)
#define MAIN_CHARGE_ON      (GpioDataRegs.GPASET.bit.GPIO10   = 1)

#define GATE_DRIVER_ENABLE  (GpioDataRegs.GPASET.bit.GPIO7 = 1)
#define GATE_DRIVER_CLEAR   (GpioDataRegs.GPACLEAR.bit.GPIO7= 1)

#define BACKUP_ENABLE       (GpioDataRegs.GPACLEAR.bit.GPIO17 = 1)
#define BACKUP_DISABLE      (GpioDataRegs.GPASET.bit.GPIO17   = 1)

// 2017.09.01--2011.06.25
#define EX_INPUT1           GpioDataRegs.GPADAT.bit.GPIO14    // exInput1
#define RUN_INPUT           (EX_INPUT1)                         // run input

#define INIT_CHARGE_CLEAR   Nop()               // (GpioDataRegs.GPACLEAR.bit.GPIO13 = 1)
#define INIT_CHARGE_SET     Nop()               // (GpioDataRegs.GPASET.bit.GPIO13   = 1)

#define GATE_DRIVER_FAULT   (GpioDataRegs.GPADAT.bit.GPIO16)    // gateDriverFault
// #define DB_FAULT     (GpioDataRegs.GPADAT.bit.GPIO17)

struct DIGIT_FUNCTION_BITS {      
	Uint16 DRIVE_ENABLE:1;      // 0
	Uint16 MULTI_STEP_BIT0:1;	// 1
	Uint16 MULTI_STEP_BIT1:1;	// 2
	Uint16 MULTI_STEP_BIT2:1;	// 3
	Uint16 MULTI_STEP_BIT3:1;	// 4
	Uint16 FAULT_RESET:1;		// 5
	Uint16 JOG:1;				// 6
	Uint16 AI_REF_ACTIVE:1;		// 7
	Uint16 AI_LOCAL_REMOTE:1;	// 8
	Uint16 EXT_FAULT_A:1;		// 9
	Uint16 EXT_FAULT_B:1;		// 10
	Uint16 MOTOR_SELECT:1;		//
	Uint16 MB_BRAKE_STATE:1;	//
	Uint16 ACCEL_DECEL_SWITCH:1;	//
	Uint16 REF_TUNING_INC:1;	//
	Uint16 REF_TUNING_DEC:1;	//
	Uint16 ACC_DEC_BYP:1;		//
	Uint16 PID_CNTL_ENABLE:1;	//
	Uint16 AUTO_PID_MODE:1;		//
	Uint16 PID_GAIN_SEL:1;		//
	Uint16 PID_I_RESET:1;		//
	Uint16 TRQ_REF_OPT_BYP:1;	//
	Uint16 TRQ_SIGN:1;			//
	Uint16 TRQ_OUT_ZERO:1;		//
	Uint16 TIMER_RUN_ENABLE:1;	//
	Uint16 SLAVE_RUN_STATUS:1;	//
	Uint16 SYNC_CTRL_OPT_BPY:1;	//
	Uint16 FLYING_START:1;		//
	Uint16 DISABLE_PROFIBUS:1;	//
	Uint16 INVERT_DIR:1;		//
	Uint16 INVERT_RUN:1;		//
};

struct DIGITAL_OUT_BITS{
	Uint16 DRIVE_READY:1;	// driver ready
	Uint16 FAULT_OUT_A:1;
	Uint16 FAULT_OUT_B:1;
	Uint16 MOTOR_BRAKE:1;
	Uint16 RUN_STOP:1;
	Uint16 WARNING:1;
	Uint16 DIRECTION:1;
	Uint16 JOG_INPUT:1;
	Uint16 VC_LIMIT:1;
	Uint16 FREE:1;
};

union DIGITAL_OUT_FUNC{
	Uint16	all;
	struct DIGITAL_OUT_BITS bit;
};

union DIGITAL_FUNCTION
{
   Uint32               	  all;
   struct DIGIT_FUNCTION_BITS  bit;
} ;
#endif
//===================================================================
// No more.
//===================================================================
