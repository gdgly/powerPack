; DCL_PID_C4.asm - Parallel PID controller
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

   		.def	_DCL_runPID_C4

		.sect	"dclfuncs"

; C prototype: float DCL_runPID_C4(PID *p, float rk, float yk, float lk)
; argument 1 = *p : 32-bit PID structure address [XAR4]
; argument 2 = rk : 32-bit floating-point reference [R0H]
; argument 3 = yk : 32-bit floating-point feedback [R1H]
; argument 4 = lk : 32-bit floating-point saturation input [R2H]
; return = uk : 32-bit floating-point [R0H]

		.align	2

_DCL_runPID_C4:
		.asmfunc
; context save
		MOV32   	*SP++, R4H
		MOV32   	*SP++, R5H
		MOV32   	*SP++, R6H

; servo error
		SUBF32		R1H, R0H, R1H				; R1H = ek = rk - yk

; derivative path
		MOV32		R3H, *+XAR4[4]				; R3H = Kd
		MOV			AR0, #8						; AR0 = 8
		MPYF32		R5H, R1H, R3H				; R5H = Kd * ek
||		MOV32		R4H, *+XAR4[AR0]			; R4H = c1
		MOV			AR0, #0xC					; AR0 = 12
		MPYF32		R3H, R4H, R5H				; R3H = v1 = Kd * ek * c1
||		MOV32		R6H, *+XAR4[AR0]			; R6H = d2
		MOV			AR1, #0xE					; AR1 = 14
		SUBF32		R4H, R3H, R6H				; R4H = v1 - d2
		MOV32		R5H, *+XAR4[AR1]			; R5H = d3
		SUBF32		R4H, R4H, R5H				; R4H = v4 = v1 - d2 - d3
||		MOV32		*+XAR4[AR0], R3H			; save d2
		MOV			AR0, #0xA					; AR0 = 10
		MOV32		R6H, *+XAR4[AR0]			; R6H = c2
		MPYF32		R5H, R6H, R4H				; R5H = d3 = c2 * v4
		MOV			AR0, #0x12					; AR0 = 18
		MOV32		*+XAR4[AR1], R5H			; save d3

; integral path
		MOV32		R3H, *+XAR4[2]				; R3H = Ki
		MPYF32		R5H, R1H, R3H				; R5H = v7
		MOV32		R6H, *+XAR4[AR0] 			; R6H = i14
		MPYF32		R5H, R6H, R5H				; R5H = v7 * i14
		MOV			AR0, #0x10					; AR0 = 16
		MOV32		R0H, *+XAR4[AR0] 			; R0H = i10
		ADDF32		R5H, R0H, R5H				; R5H = v8

; proportional path
		MOV32		R3H, *+XAR4[0]				; R3H = Kp
		MPYF32		R6H, R1H, R3H				; R6H = v6

; PID sum
		ADDF32		R4H, R5H, R4H				; R4H = v4 + v8
		MOV32		*+XAR4[AR0], R5H			; save i10
		ADDF32		R1H, R4H, R6H				; R1H = v9

; output saturation
		ZERO		R0H							; R0H = 0.0f
		ADDF32		R6H, R0H, #1.0				; R6H = 1.0f
		MOV			AR1, #0x14					; AR1 = 20
		MOV32		R3H, *+XAR4[AR1]			; R3H = Umax
		MINF32		R1H, R3H					; sat v9
||		MOV32		R6H, R0H					; R6H = 0.0f if sat
		MOV			AR1, #0x16					; AR1 = 22
		MOV32		R3H, *+XAR4[AR1]			; R3H = Umin
		MAXF32		R1H, R3H					; sat v9
||		MOV32		R6H, R0H					; R6H = 0.0f if sat = v12
		MPYF32		R3H, R2H, R6H				; R3H = i14
		MOV32		R0H, R1H					; R0H = uk
		MOV			AR0, #0x12					; AR0 = 18
		MOV32		*+XAR4[AR0], R3H			; save i14

; context restore
		MOV32   	R6H, *--SP, UNCF
	    MOV32   	R5H, *--SP, UNCF
	    MOV32   	R4H, *--SP, UNCF
		LRETR
		.endasmfunc

		.end

; end of file
