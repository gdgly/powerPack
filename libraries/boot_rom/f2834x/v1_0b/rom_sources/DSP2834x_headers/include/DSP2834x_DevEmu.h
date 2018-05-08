// TI File $Revision: /main/1 $
// Checkin $Date: May 30, 2008   14:11:07 $
//###########################################################################
//
// FILE:   DSP2834x_DevEmu.h
//
// TITLE:  DSP2834x Device Emulation Register Definitions.
//
//###########################################################################
// $TI Release: 2834x Boot ROM V1b $
// $Release Date: June 3, 2008 $
//###########################################################################

#ifndef DSP2834x_DEV_EMU_H
#define DSP2834x_DEV_EMU_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Device Emulation Register Bit Definitions:
//
// Device Configuration Register Bit Definitions
struct DEVICECNF_BITS  {     // bits  description
   Uint16 rsvd1:3;           // 2:0   reserved
   Uint16 VMAPS:1;           // 3     VMAP Status
   Uint16 rsvd2:1;           // 4     reserved
   Uint16 XRSn:1;            // 5     XRSn Signal Status
   Uint16 rsvd3:10;          // 15:6
   Uint16 rsvd4:3;           // 18:16
   Uint16 ENPROT:1;          // 19    Enable/Disable pipeline protection
   Uint16 MONPRIV:1;         // 20    MONPRIV enable bit
   Uint16 rsvd5:1;           // 21    reserved
   Uint16 EMU0SEL:2;         // 23,22 EMU0 Mux select
   Uint16 EMU1SEL:2;         // 25,24 EMU1 Mux select
   Uint16 MCBSPCON:1;        // 26    McBSP-B to EMU0/EMU1 pins control
   Uint16 rsvd6:5;           // 31:27 reserved
};

union DEVICECNF_REG {
   Uint32                 all;
   struct DEVICECNF_BITS  bit;
};

// PARTID 
struct PARTID_BITS   {  // bits  description
   Uint16 PARTNO:8;     // 7:0   Part Number
   Uint16 PARTTYPE:8;   // 15:8  Part Type
};

union PARTID_REG {
   Uint16              all;
   struct PARTID_BITS  bit;
};

struct DEV_EMU_REGS {
   union DEVICECNF_REG DEVICECNF;  // device configuration
   union PARTID_REG    PARTID;     // Part ID
   Uint16              REVID;      // Device ID
   Uint16              PROTSTART;  // Write-Read protection start
   Uint16              PROTRANGE;  // Write-Read protection range
   Uint16              rsvd2[202];
};

//---------------------------------------------------------------------------
// Device Emulation Register References & Function Declarations:
//
extern volatile struct DEV_EMU_REGS DevEmuRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2834x_DEV_EMU_H definition

//===========================================================================
// End of file.
//===========================================================================
