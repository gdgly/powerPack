; DCL_DF23_L2L3.asm - Pre-computed Direct Form 2 implementation in third order
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

   		.def 	_DCL_runDF23_L2
   		.def 	_DCL_runDF23_L3
   		.def	__cla_DCL_DF23_L2L3_sp

SIZEOF_LFRAME		.set	2
LFRAME_MR3			.set	0

		.align 	2
__cla_DCL_DF23_L2L3_sp	.usect ".scratchpad:Cla1Prog:_DCL_DF23_L2L3_LSECT", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_DF23_L2L3_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_DF23_L2L3_LSECT"


; C prototype: float DCL_runDF23_L2(DF23 *p, float ek);
; argument 1 = *p : controller structure address [MAR0]
; argument 2 = ek : controller input [MR0]
; return = uk : controller output [MR0]

_DCL_runDF23_L2:
		MNOP									; MAR0 load delay slot 1
		MNOP									; MAR0 load delay slot 2
		MNOP									; MAR0 load delay slot 3
		MMOV32		MR2, *MAR0[14]++			; MR2 = b0
		MRCNDD		UNC							; return call
		MMPYF32		MR1, MR0, MR2				; MR1 = ek * b0
		MMOV32		MR2, *MAR0[0]++				; MR2 = x1
		MADDF32		MR0, MR1, MR2				; MR0 = uk


; C prototype: void DCL_runDF23_L3(DF23 *p, float ek, float uk);
; argument 1 = *p : structure address [MAR0]
; argument 2 = ek : controller input [MR0]
; argument 3 = uk : u(k) controller output [MR1]
; return: void

_DCL_runDF23_L3:
		MMOV32		@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MNOP									; MAR0 load delay slot 2
		MNOP									; MAR0 load delay slot 3
		MMOV32		MR2, *MAR0[2]++				; MR2 = b0
		MMOV32		MR2, *MAR0[14]++			; MR2 = b1
		MMPYF32		MR2, MR0, MR2				; MR2 = v2
		MMOV32		MR3, *MAR0[-8]++			; MR3 = x2
		MADDF32		MR2, MR2, MR3				; MR2 = x2 + v2
		MMOV32		MR3, *MAR0[-4]++			; MR3 = a1
		MMPYF32		MR3, MR1, MR3				; MR3 = v3
		MNOP
		MSUBF32		MR2, MR2, MR3				; MR2 = x1d
		MMOV32		MR3, *MAR0[10]++			; MR3 = b2
		MMOV32		*MAR0[4]++, MR2				; save x1

		MMPYF32		MR3, MR0, MR3				; MR3 = v4
		MMOV32		MR2, *MAR0[-8]++			; MR2 = x3
		MADDF32		MR2, MR2, MR3				; MR2 = x3 + v4
		MMOV32		MR3, *MAR0[-4]++			; MR3 = a2
		MMPYF32		MR3, MR1, MR3				; MR3 = v5
		MNOP
		MSUBF32		MR2, MR2, MR3				; MR2 = x2d
		MMOV32		MR3, *MAR0[10]++			; MR3 = b3
		MMOV32		*MAR0[-4]++, MR2			; save x2

		MMPYF32		MR3, MR0, MR3				; MR3 = v6
		MMOV32		MR2, *MAR0[6]++				; MR2 = a3
		MMPYF32		MR2, MR1, MR2				; MR2 = v7
		MNOP
		MSUBF32		MR2, MR3, MR2				; MR2 = x3d
		MRCNDD		UNC							; return call
		MMOV32		*MAR0[0]++, MR2				; save x3
		MNOP
		MMOV32		MR3, @LFRAME + LFRAME_MR3	; restore MR3

		.unasg	LFRAME

; end of file
