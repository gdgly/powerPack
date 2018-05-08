; DCL_DF23_C2C3.asm - Pre-coomputed Direct Form 2 implementation in third order
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

		.def	_DCL_runDF23_C2
		.def	_DCL_runDF23_C3

		.sect	"dclfuncs"

; C prototype: float DCL_runDF23_C2(DF23 *p, float ek)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; return = uk : controller output [R0H]

		.align	2

_DCL_runDF23_C2:
		.asmfunc
		MOV32		R1H, *+XAR4[0]			; R1H = b0
		MOV			AR0, #0xE				; AR0 = 14
		MPYF32		R0H, R0H, R1H			; R0H = ek * b0
		MOV32		R1H, *+XAR4[AR0]		; R1H = x1
		ADDF32		R0H, R0H, R1H			; R0H = uk
		LRETR
		.endasmfunc


; C prototype: void DCL_runDF23_C3(DF23 *p, float ek, float uk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = uk : u(k) output [R1H]
; return: void

		.align	2

_DCL_runDF23_C3:
		.asmfunc
		MOV32   	*SP++, R4H
		MOV32   	*SP++, R5H
		MOV32   	*SP++, R6H
		MOV32		*SP++, R7H
		MOVL		ACC, @XAR4				; ACC = &b0
		ADDB		ACC, #0x10				; ACC = &x2
		MOVL		XAR5, ACC				; XAR5 = &x2
		MOV32		R2H, *XAR4++			; R2H = b0
		MOV32		R2H, *XAR4++			; R2H = b1
		MPYF32		R3H, R0H, R2H			; R3H = v2
||		MOV32		R4H, *XAR5++			; R4H = x2
		MOV32		R2H, *XAR4++			; R2H = b2
		ADDF32		R3H, R3H, R4H			; R3H = v2 + x2
||		MOV32		R4H, *XAR4++			; R4H = b3
		MPYF32		R5H, R0H, R2H 			; R5H = v4
||		MOV32		R6H, *XAR4++			; R6H = a1
		MPYF32		R7H, R4H, R0H			; R7H = v6
||		MOV32		R4H, *XAR4++			; R4H = a2
		MPYF32		R6H, R6H, R1H			; R6H = v3
		MOV32		R0H, *XAR4++			; R0H = a3
		SUBF32		R3H, R3H, R6H			; R3H = x1d
		MPYF32		R4H, R4H, R1H			; R4H = v5
		MOV32		R2H, *XAR5				; R2H = x3
		MOV32		*XAR4++, R3H			; save x1
		ADDF32		R5H, R5H, R2H			; R5H = v4 + x3
		MPYF32		R1H, R0H, R1H			; R1H = v7
		SUBF32		R4H, R5H, R4H			; R4H = x2d
		SUBF32		R7H, R7H, R1H			; R7H = x3d
		MOV32		*XAR4++, R4H			; save x2
		MOV32		*XAR4, R7H				; save x3
	    MOV32   	R7H, *--SP, UNCF
	    MOV32   	R6H, *--SP, UNCF
		MOV32   	R5H, *--SP, UNCF
	    MOV32   	R4H, *--SP, UNCF
		LRETR
		.endasmfunc

		.end

; end of file
