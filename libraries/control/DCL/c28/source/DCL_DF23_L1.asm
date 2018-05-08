; DCL_DF23_L1.asm - Full Direct Form 2 implementation in third order
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

   		.def 	_DCL_runDF23_L1
   		.def	__cla_DCL_DF23_L1_sp

SIZEOF_LFRAME		.set	2
LFRAME_MR3			.set	0

		.align 	2
__cla_DCL_DF23_L1_sp	.usect ".scratchpad:Cla1Prog:_DCL_DF23_L1_LSECT", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_DF23_L1_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_DF23_L1_LSECT"


; C prototype: float DCL_runDF23_L1(DF23 *p, float ek);
; argument 1 = *p : 32-bit structure address [MAR0]
; argument 2 = ek : 32-bit floating-point [MR0]
; return = uk : 32-bit floating-point [MR0]

_DCL_runDF23_L1:
		MMOV32		@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MNOP									; MAR0 load delay slot 2
		MNOP									; MAR0 load delay slot 3

		MMOV32		MR1, *MAR0[2]++				; MR1 = b0
		MMPYF32		MR2, MR1, MR0				; MR2 = v1
||		MMOV32		MR3, *MAR0[12]++			; MR3 = b1
		MMOV32		MR1, *MAR0[2]++				; MR1 = x1
		MADDF32		MR2, MR1, MR2				; MR2 = uk

		MMPYF32		MR3, MR0, MR3				; MR3 = v2
		MMOV32		MR1, *MAR0[-8]++			; MR1 = x2
		MADDF32		MR3, MR1, MR3				; MR3 = x2 + v2
||		MMOV32		MR1, *MAR0[-4]++			; MR1 = a1
		MMPYF32		MR1, MR1, MR2				; MR1 = v3
		MNOP
		MSUBF32		MR3, MR3, MR1				; MR3 = x1d
		MMOV32		MR1, *MAR0[10]++			; MR1 = b2
		MMOV32		*MAR0[4]++, MR3				; save x1

		MMPYF32		MR1, MR0, MR1				; MR1 = v4
		MMOV32		MR3, *MAR0[-8]++			; MR3 = x3
		MADDF32		MR3, MR1, MR3				; MR3 = x3 + v4
||		MMOV32		MR1, *MAR0[-4]++			; MR1 = a2
		MMPYF32		MR1, MR1, MR2				; MR1 = v5
		MNOP
		MSUBF32		MR3, MR3, MR1				; MR3 = x2d
		MMOV32		MR1, *MAR0[10]++			; MR1 = b3
		MMOV32		*MAR0[-4]++, MR3			; save x2

		MMPYF32		MR1, MR0, MR1				; MR1 = v6
||		MMOV32		MR3, *MAR0[6]++				; MR3 = a3
		MMPYF32		MR3, MR2, MR3				; MR3 = v7
		MSUBF32		MR1, MR1, MR3				; MR1 = x3d
		MRCNDD		UNC							; return call
		MMOV32		MR0, MR2, UNC				; return uk
		MMOV32		MR3, @LFRAME + LFRAME_MR3	; restore MR3
		MMOV32		*MAR0[0]++, MR1				; save x3

		.unasg	LFRAME

; end of file
