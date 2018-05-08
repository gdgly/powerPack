; DCL_PID_L2.asm - Parallel PID controller
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

   		.def 	_DCL_runPID_L2
		.def	__cla_DCL_runPID_L2_sp

SIZEOF_LFRAME	.set	10
LFRAME_MR3		.set	0
LFRAME_V5		.set	2
LFRAME_V6		.set	4
LFRAME_V7		.set	6
LFRAME_LK		.set	8

__cla_DCL_runPID_L2_sp	.usect ".scratchpad:Cla1Prog:_DCL_runPID_L2", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_runPID_L2_sp, LFRAME

		.sect 	"Cla1Prog:_DCL_runPID_L2"

		.align 	2

; C prototype:
; float DCL_runPID_L2(PID *p, float rk, float yk, float lk)
; argument 1 = *p : PID structure address [MAR0]
; argument 2 = rk : control loop reference [MR0]
; argument 3 = yk : control loop feedback [MR1]
; argument 4 = lk : controller saturation input [MR2]
; return = uk : control effort [MR0]

_DCL_runPID_L2:
;		MDEBUGSTOP
		MMOV32		@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MMOV32		@LFRAME + LFRAME_LK, MR2 	; save lk
		MNOP									; MAR0 load delay slot

;*** servo error ***
		MSUBF32		MR0, MR0, MR1				; MR0 = v5
||		MMOV32		MR1, *MAR0[4]++				; MR1 = Kp

;*** derivative path ***
		MMOV32		MR1, *MAR0[4]++				; MR1 = Kd
		MMPYF32		MR3, MR0, MR1				; MR3 = Kd * v5
||		MMOV32		MR1, *MAR0[4]++				; MR1 = c1
		MMPYF32		MR3, MR1, MR3				; MR3 = v1
||		MMOV32		MR1, *MAR0					; MR1 = d2
		MSUBF32		MR1, MR3, MR1				; MR1 = v1 - d2
||		MMOV32		*MAR0[2]++, MR3				; save d2
		MMOV32		MR3, *MAR0[-4]++			; MR3 = d3
		MSUBF32		MR1, MR1, MR3				; MR1 = v4
||		MMOV32		MR3, *MAR0[-10]++			; MR3 = c2
		MMPYF32		MR3, MR1, MR3				; MR3 = d3
||		MMOV32		MR2, *MAR0[14]++			; MR2 = Kp

;*** proportional path ***
		MMPYF32		MR2, MR0, MR2				; MR2 = v6
||		MMOV32		*MAR0[-12]++, MR3 			; save d3
		MADDF32		MR1, MR1, MR2				; MR1 = v4 + v6
||		MMOV32		MR3, *MAR0[16]++			; MR3 = Ki

;*** integral path ***
		MMPYF32		MR0, MR0, MR3				; MR0 = v7
||		MMOV32		MR3, *MAR0[-2]++			; MR3 = i14
		MMPYF32		MR0, MR0, MR3				; MR0 = v7 * i14
||		MMOV32		MR3, *MAR0					; MR3 = i10
		MADDF32		MR0, MR0, MR3				; MR0 = v8
		MMOV32		*MAR0[4]++, MR0				; save i10

;*** PID sum ***
		MADDF32		MR0, MR0, MR1				; MR0 = v9
||		MMOV32		MR1, *MAR0[2]++				; MR1 = Umax

;*** saturation ***
		MMOVF32		MR2, #0.0f					; MR2 = 0.0f
		MMOVF32		MR3, #1.0f					; MR3 = 1.0f
		MMINF32		MR0, MR1					; MR0 = sat+
		MMOV32		MR3, MR2, GT				; MR3 = v12
		MMOV32		MR1, *MAR0[-4]++			; MR1 = Umin
		MMAXF32		MR0, MR1					; MR0 = sat-
		MMOV32		MR3, MR2, LT				; MR3 = v12
		MRCNDD		UNC							; return call
		MMOV32		MR1, @LFRAME + LFRAME_LK	; MR1 = lk
		MMPYF32		MR2, MR1, MR3				; MR2 = lk * v12
||		MMOV32		MR3, @LFRAME + LFRAME_MR3	; restore MR3
		MMOV32		*MAR0, MR2					; save i14

		.unasg	LFRAME

; end of file
