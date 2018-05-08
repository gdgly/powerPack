//###########################################################################
//
// FILE:   bootrom.h
//
// TITLE:  BootROM Definitions.
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July , 2015 $
// $Copyright:  $
//###########################################################################

//------CAN bit timing parameters------//
//This code does compile-time calculation of CAN bit timing parameters based on user-provided
//input settings. There are some error checks at the end, but you (the user) are ultimately
//responsible for verifying and testing the final register value. See section 12 of the CAN
//user guide in your F28M35x, F28M36x, or F28x7x TRM for aan explanation of CAN timings and
//associated requirements. The main requirements are:
//
//1. One CAN bit must take between 8 and 25 time quanta.
//2. Tseg1 and Tseg2 must fit into their respective register fields.
//3. The synchronization jump width cannot be longer than either phase segment.
//
//The calculated bit timing register values is #defined as CAN_CALC_BTRREG.

//There are three user-controlled parameters that must be #defined before #including this header.
//They are (with examples):
//
//Bit rate  (bits/sec)  CAN bit rate -- must match the rest of the CAN network
//CANCLK    (hertz)     CAN module peripheral clock frequency before the bit rate prescaler
//Bit time  (Tq)        Number of time quanta per bit; the ratio of prescaled bit clock frequency to bit rate
//#define CAN_CALC_BITRATE  50000L
//#define CAN_CALC_CANCLK   10000000L
//#define CAN_CALC_BITTIME  20

//Other parameters are defined according to the instructions in section 12.2.1
//of the CAN spec. Exception: This code rounds PhSeg1 up and PhSeg2 down since a
//later sample time works better on most networks. This is implemented by rounding
//down PhSeg2 first, then computing PhSeg1 as Tphase - PhSeg2. Calculating in this
//order also lets us limit Tseg2 to 8 so it will fit in the register.
//
//BRP       -           Bit rate prescaler, which divides down CANCLK to provide the bit clock
//Tsync		(Tq)		Synchronization time delay: Fixed at 1 Tq by the CAN protocol
//Tprop		(Tq)		Propagation delay: <2 microseconds for a <1000 foot bus; assumed to be <2 Tq
//Tphase	(Tq)		Phase compensation buffer for oscillator tolerance: The remainder of the bit time
//PhSeg1	(Tq)		Phase segment 1: Pre-sample buffer; half of the phase time, rounded up (<=16)
//PhSeg2	(Tq)		Phase segment 2: Post-sample buffer; half of the phase time, rounded down (<=8)
#define _CAN_CALC_BRP       (CAN_CALC_CANCLK / (CAN_CALC_BITRATE * CAN_CALC_BITTIME))
#define _CAN_CALC_TSYNC		1ul
#define _CAN_CALC_TPROP		2ul
#define _CAN_CALC_TPHASE	(CAN_CALC_BITTIME - (_CAN_CALC_TSYNC + _CAN_CALC_TPROP))
#define _CAN_CALC_PHSEG2	((_CAN_CALC_TPHASE / 2ul <= 8ul) ? _CAN_CALC_TPHASE / 2ul : 8ul)
#define _CAN_CALC_PHSEG1	(_CAN_CALC_TPHASE - _CAN_CALC_PHSEG2)

//These parameters are then converted into register values. All parameters
//are -1 in the register:
//
//Tseg1		(Tq)		Everything between sync and sample: Tprop + PhSeg1; MUST BE LESS THAN 16
//Tseg2		(Tq)		Everything between sample and next time: PhSeg2; MUST BE LESS THAN 8
//Tsjw		(Tq)		Synchronization jump width: The lesser of 4 and PhSeg1/2
//BRPEREG	-			Upper 4 bits of bit prescaler; SUBTRACT ONE FROM BRP BEFORE COMPUTING THIS
//BRPREG	-			Lower 6 bits of bit prescaler; SUBTRACT ONE FROM BRP BEFORE COMPUTING THIS
#define _CAN_CALC_TSEG1		((_CAN_CALC_PHSEG1 + _CAN_CALC_TPROP) - 1ul)
#define _CAN_CALC_TSEG2		(_CAN_CALC_PHSEG2 - 1ul)
#define _CAN_CALC_TSJW		(((_CAN_CALC_PHSEG2 > 4ul) ? 4ul : _CAN_CALC_PHSEG2) - 1ul)
#define _CAN_CALC_BRPEREG	((_CAN_CALC_BRP - 1ul) / 64ul)
#define _CAN_CALC_BRPREG	((_CAN_CALC_BRP - 1ul) % 64ul)

//The final result -- a value to write to the bit timing register
#define CAN_CALC_BTRREG		(_CAN_CALC_BRPEREG<<16ul | _CAN_CALC_TSEG2<<12ul | _CAN_CALC_TSEG1<<8ul | _CAN_CALC_TSJW<<6ul | _CAN_CALC_BRPREG)

//Error and sanity checks. If the bit time is valid, the code should guarantee that
//the other values are also valid, but more error checking never hurt anyone. If you
//get a Tseg1, Tseg2, or Tsjw error without a bit time error, it means there's a bug
//in the calculation code, and you should complain on the C2000 E2E forum.
#if (CAN_CALC_BITRATE > 1000000)
	#error "Can config error: Bit rate cannot exceed 1000000 Hz!
#endif
#if (CAN_CALC_BITTIME < 8)
	#error "CAN config error: Bit time cannot be less than 8 time quanta!"
#elif (CAN_CALC_BITTIME > 25)
	#error "CAN config error: Bit time cannot exceed 25 time quanta!"
#endif
#if (_CAN_CALC_BRP * CAN_CALC_BITTIME * CAN_CALC_BITRATE != CAN_CALC_CANCLK)
	#error "CAN config error: These settings require a fractional prescaler! (CAN_CALC_BITRATE * CAN_CLK_BITTIME) must evenly divide CAN_CALC_CANCLK.
#endif
#if (_CAN_CALC_TSEG1 >= 16)
	#error "CAN config error: Tseg1 register value cannot be greater than 15! Something is broken in the calculation routine."
#endif
#if (_CAN_CALC_TSEG2 >= 8)
	#error "CAN config error: Tseg2 register value cannot be greater than 7! Something is broken in the calculation routine."
#endif
#if (_CAN_CALC_TSJW > _CAN_CALC_PHSEG1 || _CAN_CALC_TSJW > _CAN_CALC_PHSEG2)
	#error "CAN config error: Tsjw cannot be greater than PhSeg1 or PhSeg2! Something is broken in the calculation routine."
#endif
