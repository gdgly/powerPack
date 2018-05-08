; DCL_DF13_C1.asm - Full Direct Form 1 implementation in third order
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

		.def	_DCL_runDF13_C1

		.sect	"dclfuncs"

; C prototype: float DCL_runDF13_C1(DF13 *p, float ek)
; argument 1 = *p : 32-bit ARMA structure address [XAR4]
; argument 2 = ek : 32-bit floating-point input [R0H]
; return = uk : 32-bit floating-point [R0H]

; XAR4 = coefficient pointer
; XAR5 = data pointer

		.align	2

_DCL_runDF13_C1:
		.asmfunc
; context save
		PUSH  		XAR5
		MOV32   	*SP++, R4H
		MOV32   	*SP++, R5H

; initialize pointers
		MOVL		ACC, @XAR4				; ACC = &p(0) = &b0
		ADDB		ACC, #0x10				; ACC = &p(8) = &d0
		MOVL		XAR5, ACC				; XAR5 = &d0
		MOV32		*XAR5++, R0H			; save d0, XAR5 = &d1

; v0 = b0 * d0
		MOV32		R1H, *XAR4++			; R1H = b0
		MPYF32		R2H, R0H, R1H			; R2H = v0
||		MOV32		R3H, *XAR5				; R3H = d1
		MOV32		*XAR5++, R0H			; save d0

; v1 = b1 * d1
		MOV32		R1H, *XAR4++			; R1H = b1
		MPYF32		R4H, R1H, R3H			; R4H = v1
||		MOV32		R5H, *XAR5				; R5H = d2
		MOV32		*XAR5++, R3H			; save d1

; v2 = b2 * d2
 		ADDF32		R0H, R2H, R4H			; R0H = v01
|| 		MOV32		R1H, *XAR4++			; R1H = b2
 		MPYF32		R2H, R1H, R5H			; R2H = v2
|| 		MOV32		R4H, *XAR5				; R4H = d3
 		MOV32		*XAR5++, R5H			; save d2

; v3 = b3 * d3
 		ADDF32		R0H, R0H, R2H			; R0H = v012
|| 		MOV32		R1H, *XAR4++			; R1H = b3
		MPYF32		R3H, R1H, R4H			; R3H = v3
		MOV32		R2H, *+XAR5[6]			; R2H = d7

; XAR4 = &a0, XAR5 = &d4.  Indirect offset addressing from here.

; v7 = a3 * d7
		ADDF32		R0H, R0H, R3H			; R0H = v0123
||		MOV32		R1H, *+XAR4[6]			; R1H = a3
		MPYF32		R3H, R1H, R2H			; R3H = v7
		MOV32		R4H, *+XAR5[4]			; R4H = d6
		MOV32		*+XAR5[6], R4H			; save d6

; v6 = a2 * d6
		SUBF32		R0H, R0H, R3H			; R0H = v01237
||		MOV32		R1H, *+XAR4[4]			; R1H = a2
		MPYF32		R2H, R1H, R4H			; R2H = v6
		MOV32		R5H, *+XAR5[2]			; R5H = d5
		MOV32		*+XAR5[4], R5H			; save d5

; v5 = a1 * d5
		SUBF32		R0H, R0H, R2H			; R0H = v012367
||		MOV32		R1H, *+XAR4[2]			; R1H = a1
		MPYF32		R2H, R1H, R5H			; R2H = v5
	    MOV32   	R5H, *--SP, UNCF
		SUBF32		R0H, R0H, R2H			; R0H = v0123567
	    MOV32   	R4H, *--SP, UNCF
		MOV32		*+XAR5[2], R0H			; save d4
		MOV32		*+XAR5[0], R0H			; save u(k)
		POP   		XAR5
		LRETR
		.endasmfunc

		.end

; end of file
