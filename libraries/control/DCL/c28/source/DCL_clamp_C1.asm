; DCL_clamp_C1.asm - clamps output from immediate ARMA controller
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

		.def	_DCL_runClamp_C1

		.sect	"dclfuncs"

; This function saturates an input data value to defined upper & lower limits.
; If the input data lies definitely within limits the function returns 0,
; otherwise it returns 1.
; i.e. return 0 if (lowerLim < data < upperLim), otherwise return 1.

; C prototype: uint16_t DCL_runClamp_C1(float *data, float Umax, float Umin)
; argument 1 = *data: address of input data [XAR4]
; argument 2 = Umax : upper limit [R0H]
; argument 3 = Umin : lower limit [R1H]
; return = integer : 1 = clamped, 0 = not clamped [AL]

		.align	2

_DCL_runClamp_C1:
		.asmfunc
		ZAPA								; AL = 0
		MOV32 		R2H, *+XAR4[0]			; R2H = data
		CMPF32		R2H, R0H				; compare: data, Umax
		MOVST0		ZF, NF					; copy flags: Z = ZF, N = NF
		MOVB		AL, #1, GEQ				; data >= Umax ---> AL = 1
		MOV32		R0H, R2H, LT			; data < Umax ---> R0H = data
		CMPF32		R2H, R1H				; comapare: data, Umin
		MOVST0		ZF, NF					; copy flags: Z = ZF, N = NF
		MOVB		AL, #1, LEQ				; data <= Umin ---> AL = 1
		MOV32		R0H, R1H, LT			; data < Umin ---> R0H = Umin
		MOV32		*+XAR4[0], R0H			; &data = R0H
		LRETR
		.endasmfunc

		.end

; end of file
