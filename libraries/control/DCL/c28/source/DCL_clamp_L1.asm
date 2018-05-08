; DCL_clamp_L1.asm - clamps output from immediate ARMA controller on CLA
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

   		.def 	_DCL_runClamp_L1

SIZEOF_LFRAME		.set	4
LFRAME_MR3			.set	0
LFRAME_ONE			.set	2

		.align 	2
__cla_DCL_clamp_L1_sp	.usect ".scratchpad:Cla1Prog:_DCL_clamp_L1_LSECT", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_clamp_L1_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_clamp_L1_LSECT"

; This function saturates an input data value to defined upper & lower limits.
; If the input data lies definitely within limits the function returns 0.0f,
; otherwise it returns 1.0f.  The return value can be used by the pre-computed
; controller to test for saturation.
; i.e. return 0.0f if (Umin < data < Umax), otherwise return 1.0f
; Returns 1.0f if data lies at the boundary: (data == Umax) or (data == Umin).
; Returns 1.0f if limits are invalid: (Umax < Umin).

; C prototype: float DCL_runClamp_L1(float *data, float Umax, float Umin)
; argument 1 = *data: address of input data [MAR0]
; argument 2 = Umax : upper limit [MR0]
; argument 3 = Umin : lower limit [MR1]
; return = float : 1.0f = clamped, 0.0f = not clamped [MR0]

_DCL_runClamp_L1:
		MMOV32		@LFRAME + LFRAME_MR3, MR3		; save MR3
		MMOVF32		MR3, #1.0f						; MR3 = 1.0f
		MMOV32		@LFRAME + LFRAME_ONE, MR3		; save constant
		MMOVF32		MR3, #0.0f						; MR3 = 0.0f
		MMOV32		MR2, *MAR0						; MR2 = data
		MMINF32		MR0, MR2						; if (MR0 >  MR2)  {MR0 = MR2, ZF = 0, NF = 0} elseif (MR0 == MR2) {ZF = 1, NF = 0} else {ZF = 0, NF = 1}
		MMOV32		MR3, @LFRAME + LFRAME_ONE, LEQ	; if (data >= Umax) {MR3 = 1.0f}
		MMAXF32		MR0, MR1						; if (MR0 < MR1) {MR0 = MR1, ZF = 0, NF = 1} elseif (MR0 == MR1) {ZF = 1, NF = 0} else {ZF = 0, NF = 0}
		MMOV32		MR3, @LFRAME + LFRAME_ONE, LEQ	; if (data <= Umin) {MR3 = 1.0f}
		MRCNDD		UNC								; return call
		MMOV32		*MAR0, MR0						; update data
		MMOV32		MR0, MR3						; return MR3
		MMOV32		MR3, @LFRAME + LFRAME_MR3		; restore MR3
		.unasg	LFRAME

; end of file
