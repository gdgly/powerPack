; DCL_DF22_L1.asm - Full Direct Form 2 implementation in second order
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

   		.def 	_DCL_runDF22_L1
   		.def	__cla_DCL_DF22_L1_sp

SIZEOF_LFRAME		.set	2
LFRAME_MR3			.set	0

		.align 	2
__cla_DCL_DF22_L1_sp	.usect ".scratchpad:Cla1Prog:_DCL_DF22_L1_LSECT", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_DF22_L1_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_DF22_L1_LSECT"

; C prototype: float DCL_runDF22_L1(DF22 *p, float ek)
; argument 1 = *p : structure address [MAR0]
; argument 2 = ek : controller input [MR0]
; return = uk : controller output [MR0]

_DCL_runDF22_L1:
		MMOV32		@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MNOP									; MAR0 load delay
		MNOP									; MAR0 load delay
		MMOV32		MR1, *MAR0[10]++			; MR1 = b0
		MMPYF32		MR2, MR0, MR1				; MR2 = v0
||		MMOV32		MR3, *MAR0[-8]++			; MR3 = x1
		MADDF32		MR1, MR2, MR3				; MR1 = uk
||		MMOV32		MR3, *MAR0[10]++			; MR3 = b1
		MMPYF32		MR2, MR0, MR3				; MR2 = v1
||		MMOV32		MR3, *MAR0[-6]++			; MR3 = x2
		MADDF32		MR3, MR2, MR3				; MR3 = v1 + x2
||		MMOV32		MR2, *MAR0[4]++				; MR2 = a1
		MMPYF32		MR2, MR2, MR1				; MR2 = v3
		MNOP									; MR2 delay slot
		MSUBF32		MR3, MR3, MR2				; MR3 = x1d
		MMOV32		*MAR0[-6]++, MR3			; save x1
		MMOV32		MR3, *MAR0[4]++				; MR3 = b2
		MMPYF32		MR2, MR0, MR3				; MR2 = v2
||		MMOV32		MR3, *MAR0[4]++				; MR3 = a2
		MMOV32		MR0, MR1					; return uk
		MMPYF32		MR1, MR1, MR3				; MR1 = v4
		MRCNDD		UNC							; return call
		MSUBF32		MR3, MR2, MR1				; MR3 = x2d
		MMOV32		*MAR0, MR3					; save x2
		MMOV32		MR3, @LFRAME + LFRAME_MR3	; restore MR3

		.unasg	LFRAME

; end of file
