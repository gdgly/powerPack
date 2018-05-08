; DCL_DF13_C2C3.asm - Pre-computed Direct Form 1 implementation in third order
;
; Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
; ALL RIGHTS RESERVED 

		.sect	"dclfuncs"

		.def	_DCL_runDF13_C2
		.def	_DCL_runDF13_C3

; C prototype: float DCL_runDF13_C2(DF13 *p, float ek, float vk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = vk : partial product [R1H]
; return = uk : controller output [R0H]

_DCL_runDF13_C2:
		.asmfunc
		MOV32	R2H, *+XAR4[0]				; R2H = b0
		MPYF32	R0H, R0H, R2H				; R0H = e(k) * b0
		MOV 	AR0, #0x18					; AR0 = 24
		ADDF32	R0H, R0H, R1H				; R0H = u(k)
		LRETR
		.endasmfunc

; C prototype: float DCL_runDF13_C3(DF13 *p, float ek, float uk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = uk : controller output [R1H]
; return : v(k)

_DCL_runDF13_C3:
		.asmfunc
; context save
		PUSH  	XAR5
		MOV32   *SP++, R4H
		MOV32   *SP++, R5H
		MOV32   *SP++, R6H
		MOV32   *SP++, R7H

; initialise pointers
		MOVL	ACC, @XAR4					; ACC = &p(0) = &b0
		ADDB	ACC, #0x10					; ACC = &p(8) = &d0
		MOVL	XAR5, ACC					; XAR5 = &d0
		MOV32	*XAR5++, R0H				; save d0, XAR5 = d1

; v1 = e(k) * b1
		MOV32	R2H, *XAR4++				; R2H = b0
		MOV32	R2H, *XAR4++				; R2H = b1
		MPYF32	R3H, R2H, R0H				; R3H = v1
||		MOV32	R4H, *XAR5					; R4H = d1
		MOV32	*XAR5++, R0H				; save e(k-1)

; v2 = e(k-1) * b2
		MOV32	R5H, *XAR4++				; R5H = b2
		MPYF32	R2H, R5H, R4H				; R2H = v2
||		MOV32	R6H, *XAR5					; R6H = d2
		MOV32	*XAR5++, R4H				; save e(k-2)

; v3 = e(k-3) * b3
		MOV32	R5H, *XAR4++				; R5H = b3
		MPYF32	R7H, R5H, R6H				; R7H = v2
||		MOV32	*XAR5++, R6H				; save e(k-3)

; save v123
		ADDF32	R0H, R3H, R2H				; R0H = v1 + v2
		MOV32	R5H, *XAR4++				; R5H = a0
		ADDF32	R0H, R0H, R7H				; R0H = v1 + v2 + v3
||		MOV32	R5H, *XAR4++				; R5H = a1

; v4 = u(k) * a1
		MPYF32	R2H, R1H, R5H				; R2H = v4
||		MOV32	*XAR5++, R1H				; XAR5 = &d5
		MOV32	R3H, *XAR5					; R3H = d5
		SUBF32	R0H, R0H, R2H				; R0H = v1 + v2 + v3 - v4
		MOV32	*XAR5++, R1H				; save u(k-1)

; v5 = u(k-1) * a2
		MOV32	R4H, *XAR4++				; R4H = a2
		MPYF32	R5H, R4H, R3H				; R5H = v5
||		MOV32	R1H, *XAR5					; R2H = d6
		MOV32	*XAR5++, R3H				; save u(k-2)

; v6 = u(k-2) * a3
		SUBF32	R0H, R0H, R5H				; R0H = v1 + v2 + v3 - v4 - v5
||		MOV32	R6H, *XAR4					; R6H = a3
		MPYF32	R7H, R6H, R1H				; R7H = v7
		MOV32	*XAR5, R1H					; save u(k-3)
		SUBF32	R0H, R0H, R7H				; save v(k+1)

; context restore
	    MOV32   R7H, *--SP, UNCF			; do not parallel with previous SUBF32
		MOV32   R6H, *--SP, UNCF
	    MOV32   R5H, *--SP, UNCF
	    MOV32   R4H, *--SP, UNCF
		POP   	XAR5
		LRETR
		.endasmfunc

		.end

; end of file
