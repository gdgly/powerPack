; DCL_DF22_C2C3.asm - Pre-computed Direct Form 2 implementation in second order
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

		.def	_DCL_runDF22_C2
		.def	_DCL_runDF22_C3

		.sect	"dclfuncs"

; C prototype: float DCL_runDF22_C2(DF22 *p, float ek)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; return = uk : controller output [R0H]

		.align	2

_DCL_runDF22_C2:
		.asmfunc
		MOV32		R1H, *+XAR4[0]			; R1H = b0
		MOV			AR0, #0xA				; AR0 = 10
		MPYF32		R0H, R0H, R1H			; R0H = ek * b0
		MOV32		R1H, *+XAR4[AR0]		; R1H = x1
		ADDF32		R0H, R0H, R1H			; R0H = uk
		LRETR
		.endasmfunc

; C prototype: void DCL_runDF22_C3(DF22 *p, float ek, float uk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = uk : u(k) output [R1H]
; return: void

		.align	2

_DCL_runDF22_C3:
		.asmfunc
		MOV32   	*SP++, R4H
		MOV32   	*SP++, R5H
		MOV32   	*SP++, R6H
		MOV32		*SP++, R7H
		MOV32		R2H, *XAR4++			; XAR4 = &b1
		MOV32		R2H, *XAR4++			; R2H = b1
		MPYF32		R3H, R2H, R0H			; R3H = v1
||		MOV32		R4H, *XAR4++			; R4H = b2
		MPYF32		R5H, R4H, R0H			; R5H = v2
||		MOV32		R6H, *XAR4++			; R6H = a1
		MPYF32		R7H, R6H, R1H			; R7H = v3
||		MOV32		R0H, *XAR4++			; R0H = a2, XAR4 = &x1
		MPYF32		R0H, R0H, R1H			; R0H = v4
||		MOV32		R2H, *+XAR4[2]			; R2H = x2
		ADDF32		R3H, R3H, R2H			; R3H = v1 + x2
		SUBF32		R5H, R5H, R0H			; R5H = x2d
		SUBF32		R2H, R3H, R7H			; R2H = x1d
||	    MOV32   	R7H, *--SP				; [CODEGEN-1534]
		MOV32		*+XAR4[2], R5H			; save x2
		MOV32		*+XAR4[0], R2H			; save x1
	    MOV32   	R6H, *--SP, UNCF
		MOV32   	R5H, *--SP, UNCF
	    MOV32   	R4H, *--SP, UNCF
		LRETR
		.endasmfunc

		.end

; end of file
