; DCL_frwlog.asm - fast read & write operations to floating-point data log [DCL_fdlog.h]
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

		.def	_DCL_freadLog
		.def	_DCL_fwriteLog

		.sect	"dclfuncs"

; C prototype: float DCL_freadLog(FDLOG *p);
; argument 1 = *p: address of FDLOG structure [XAR4]
; return = FDLOG data [R0H]

		.align	2

_DCL_freadLog:
		.asmfunc
		MOVL		XAR0, *+XAR4[4]				; XAR0 = p.dptr
		MOVL		ACC, *+XAR4[0]				; ACC = p.fptr
		MOV32		R0H, *XAR0++				; R0H = data, XAR0 = p.dptr + 1
		MOVL		*+XAR4[4], XAR0				; save dptr
		MOVL		P, XAR0						; P = dptr
		SUBUL		P, *+XAR4[2]				; P = dptr - lptr
		MOVL		*+XAR4[4], ACC, GT			; wrap if p.lptr < (p.dptr + 1)
		LRETR
		.endasmfunc

; C prototype: float DCL_fwriteLog(FDLOG *p, float data);
; argument 1 = *p: address of FDLOG structure [XAR4]
; argument 2 = data: input FDLOG data [R0H]
; return = over-written FDLOG data [R0H]

		.align	2

_DCL_fwriteLog:
		.asmfunc
		MOVL		XAR0, *+XAR4[4]				; XAR0 = p.dptr
		MOVL		ACC, *XAR0					; ACC = old data
		MOV32		*XAR0++, R0H				; write new data, XAR0 = p.dptr + 1
		MOV32		R0H, ACC					; save old data to R0H [4 delay slots]
		MOVL		ACC, *+XAR4[0]				; ACC = p.fptr
		MOVL		*+XAR4[4], XAR0				; save dptr
		MOVL		P, XAR0						; P = dptr
		SUBUL		P, *+XAR4[2]				; P = dptr - lptr
		MOVL		*+XAR4[4], ACC, GT			; wrap if p.lptr < (p.dptr + 1)
		LRETR
		.endasmfunc

		.end

; end of file
