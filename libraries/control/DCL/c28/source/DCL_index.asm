; DCL_index.asm - computes performance indices from TCM data
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

		.def	_DCL_runITAE_C1
		.def	_DCL_runIAE_C1
		.def	_DCL_runIES_C1

		.sect	"dclfuncs"

; C prototype: float DCL_runITAE_C1(FDLOG *elog, float prd)
; argument 1 = *elog: address of input data [XAR4]
; argument 2 = prd : sample period in seconds [R0H]
; return = ITAE index [R0H]

		.align	2

_DCL_runITAE_C1:
		.asmfunc
		MOVL		ACC, *+XAR4[2]				; ACC = elog.lptr
		SUBL		ACC, *+XAR4[0]				; ACC = buffer length
		LSR			AL, #1						; N/2
		MOV			AR7, AL
		ZERO		R2H
		ZERO		R3H
		MOVL		XAR5, *XAR4
;--- repeat loop
		RPTB		_ITAE_END, AR7
		MOV32		R1H, *XAR5++				; R1H = data
		ABSF32		R1H, R1H					; R1H = abs(data)
		MPYF32		R1H, R1H, R3H				; R1H = abs(data) * time
		ADDF32		R3H, R3H, R0H				; R3H = time
		ADDF32		R2H, R2H, R1H				; R2H = cumulative index
_ITAE_END
		NOP
		MOV32		R0H, R2H
		LRETR
		.endasmfunc

		.page

; C prototype: float DCL_runIAE_C1(FDLOG *elog)
; argument 1 = *elog: address of input data [XAR4]
; return = IAE index [R0H]

		.align	2

_DCL_runIAE_C1:
		.asmfunc
		MOVL		ACC, *+XAR4[2]				; ACC = elog.lptr
		SUBL		ACC, *+XAR4[0]				; ACC = buffer length
		LSR			AL, #1						; N/2
		MOV			AR7, AL
		ZERO		R0H
		MOVL		XAR5, *XAR4
;--- repeat loop
		RPTB		_IAE_END, AR7
		MOV32		R1H, *XAR5++				; R1H = data
		ABSF32		R1H, R1H					; R1H = abs(data)
		ADDF32		R0H, R0H, R1H				; R0H = cumulative index
		NOP
		NOP
		NOP
_IAE_END
		LRETR
		.endasmfunc

		.page

; C prototype: float DCL_runIES_C1(FDLOG *elog)
; argument 1 = *elog: address of input data [XAR4]
; return = IES index [R0H]

		.align	2

_DCL_runIES_C1:
		.asmfunc
		MOVL		ACC, *+XAR4[2]				; ACC = elog.lptr
		SUBL		ACC, *+XAR4[0]				; ACC = buffer length (N) in 16-bit words
		LSR			AL, #1						; N in 32-bit words
		MOV			AR7, AL						; AR7 = loop count
		ZERO		R0H
		MOVL		XAR5, *XAR4
;--- repeat loop
		RPTB		_IES_END, AR7
		MOV32		R1H, *XAR5++				; R1H = data
		MPYF32		R2H, R1H, R1H				; R2H = data^2
		NOP
		ADDF32		R0H, R0H, R2H				; R0H = cumulative index
		NOP
		NOP
_IES_END
		LRETR
		.endasmfunc

		.end

; end of file
