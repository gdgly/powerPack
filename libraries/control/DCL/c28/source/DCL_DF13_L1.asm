; DCL_DF13_L1.asm - Full Direct Form 1 implementation in third order
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

   		.def	_DCL_runDF13_L1
   		.def	__cla_DCL_DF13_L1_sp

SIZEOF_LFRAME		.set	6
LFRAME_MR1			.set	0
LFRAME_MR3			.set	2
LFRAME_MAR0			.set	4
LFRAME_MAR1			.set	5

		.align 	2
__cla_DCL_DF13_L1_sp	.usect ".scratchpad:Cla1Prog:_DCL_DF13_L1_LSECT", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_DF13_L1_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_DF13_L1_LSECT"

; C prototype: float DCL_runDF13_L1(DF13 *p, float ek);
; argument 1 = *p : 32-bit structure address [MAR0]
; argument 2 = ek : 32-bit floating-point [MR0]
; return = uk : 32-bit floating-point [MR0]

_DCL_runDF13_L1:
		MMOV32		@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MNOP									; MAR0 read stall
		MNOP									; MAR0 read stall
		MMOV16		@LFRAME + LFRAME_MAR0, MAR0 ; store MAR0 to frame
		MMOV16		@LFRAME + LFRAME_MAR1, MAR1 ; store MAR1 to frame
		MNOP									; MAR0 read stall
		MMOVZ16 	MR2, @LFRAME + LFRAME_MAR0  ; MR2 = &b0
		MMOV16  	MAR1, MR2, #0x10			; MAR1 = &d0
		MMOV32		MR1, *MAR0[2]++				; MR1 = b0
		MNOP									; MAR1 load stall

		MMPYF32		MR2, MR0, MR1				; MR2 = v0
		MMOV32		*MAR1[2]++, MR0				; save d0
		MMOV32		MR0, *MAR0[2]++				; MR0 = b1
		MMOV32		MR1, *MAR1[2]++				; MR1 = d1

		MMPYF32		MR3, MR0, MR1				; MR3 = v1
		MMOV32		MR0, *MAR0[2]++				; MR0 = b2
		MADDF32		MR2, MR2, MR3				; MR2 = v0 + v1
||		MMOV32		MR1, *MAR1[2]++				; MR1 = d2

		MMPYF32		MR3, MR0, MR1				; MR3 = v2
		MMOV32		MR0, *MAR0[4]++				; MR0 = b3
		MADDF32		MR2, MR2, MR3				; MR2 = v0 + v1 + v2
||		MMOV32		MR1, *MAR1[4]++				; MR1 = d3

		MMPYF32		MR3, MR0, MR1				; MR3 = v3
		MMOV32		MR0, *MAR0[2]++				; MR0 = a1
		MADDF32		MR2, MR2, MR3				; MR2 = v0 + v1 + v2 + v3
||		MMOV32		MR1, *MAR1[2]++				; MR1 = d5

		MMPYF32		MR3, MR0, MR1				; MR3 = v5
		MMOV32		MR0, *MAR0[2]++				; MR0 = a2
		MSUBF32		MR2, MR2, MR3				; MR2 = v0 + v1 + v2 + v3 - v5
||		MMOV32		MR1, *MAR1[2]++				; MR1 = d6

		MMPYF32		MR3, MR0, MR1				; MR3 = v6
		MMOV32		MR0, *MAR0[14]++			; MR0 = a3, MAR0 = &d6
		MSUBF32		MR2, MR2, MR3				; MR2 = v0 + v1 + v2 + v3 - v5 - v6
||		MMOV32		MR1, *MAR1[-6]++			; MR1 = d7, MAR1 = &d4

		MMPYF32		MR3, MR0, MR1				; MR3 = v7
		MNOP
		MSUBF32		MR0, MR2, MR3				; MR0 = v0 + v1 + v2 + v3 - v5 - v6 - v7
		MNOP
		MMOV32		*MAR1[-6]++, MR0			; save uk = d4

		MMOVD32		MR1, *MAR0[-2]++			; u(k-3) <- u(k-2)
		MMOVD32		MR1, *MAR0[-2]++			; u(k-2) <- u(k-1)
		MMOVD32		MR1, *MAR0[-4]++			; u(k-1) <- u(k)
		MMOVD32		MR1, *MAR0[-2]++			; e(k-3) <- e(k-2)
		MMOVD32		MR1, *MAR0[-2]++			; e(k-2) <- e(k-1)
		MRCNDD		UNC							; return call
		MMOVD32		MR1, *MAR0					; e(k-1) <- e(k)
		MMOV16		MAR1, @LFRAME + LFRAME_MAR1	; restore MAR1
		MMOV32		MR3, @LFRAME + LFRAME_MR3	; restore MR3

		.unasg		LFRAME

; end of file
