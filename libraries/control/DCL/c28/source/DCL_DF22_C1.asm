; DCL_DF22_C1.asm - Full Direct Form 2 implementation in second order
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

		.def	_DCL_runDF22_C1

		.sect	"dclfuncs"

; C prototype: float DCL_runDF22_C1(DF22 *p, float ek)
; argument 1 = *p : 32-bit ARMA structure address [XAR4]
; argument 2 = ek : 32-bit floating-point input [R0H]
; return = uk : 32-bit floating-point [R0H]

		.align	2

_DCL_runDF22_C1:
		.asmfunc
		MOV32   	*SP++, R4H
		MOV32   	*SP++, R5H
		MOV32   	*SP++, R6H
		MOV32		*SP++, R7H
		MOV32		R2H, *XAR4++			; R2H = b0
		MPYF32		R3H, R2H, R0H			; R3H = v0 = b0 * ek
||		MOV32		R4H, *XAR4++			; R4H = b1
		MPYF32		R5H, R4H, R0H			; R5H = v1 = b1 * ek
||		MOV32		R6H, *XAR4++			; R6H = b2
		MPYF32		R4H, R6H, R0H			; R4H = v2 = b2 * ek
||		MOV32		R7H, *XAR4++			; R7H = a1
		MOV32		R0H, *XAR4++			; R0H = a2
		MOV32		R6H, *XAR4++			; R6H = x1
		ADDF32		R1H, R3H, R6H			; R1H = uk = v0 + x1
||		MOV32		R2H, *XAR4				; R2H = x2
		ADDF32		R5H, R5H, R2H			; R5H = v1 + x2
		MPYF32		R6H, R7H, R1H			; R6H = v3 = a1 * uk
		MPYF32		R7H, R0H, R1H			; R7H = v4 = a2 * uk
		SUBF32		R5H, R5H, R6H			; R5H = x1d = v1 + x2 - v3
		SUBF32		R6H, R4H, R7H			; R6H = x2d = v2 - v4
||	    MOV32   	R7H, *--SP, UNCF
		MOV32		R0H, R1H, UNCF			; return uk
		MOV32		*XAR4, R6H				; save x2
		MOV32		*--XAR4, R5H			; save x1
	    MOV32   	R6H, *--SP, UNCF
		MOV32   	R5H, *--SP, UNCF
	    MOV32   	R4H, *--SP, UNCF
		LRETR
		.endasmfunc

		.end

; end of file
