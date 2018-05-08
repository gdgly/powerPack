;======================================================================
;
; File Name     : SGHP1C.ASM
; 
; Originator    : Advanced Embedded Control (AEC)
;                 Texas Instruments Inc.
; 
; Description   : This file contain source code for High performance single channel
;                 SIN generator module(32-bit Integrater, Table look-up and linear Interpolation)
;               
; Routine Type  : "CcA Only"
;                               
; Date          : 28/12/2001 (DD/MM/YYYY)
;======================================================================
; Description:
;                            ___________________
;                           |                   |
;        gain   o---------->|                   |
;        offset o---------->|     SGENHP_1      |----->o OUT
;        freq   o---------->|                   |
;                           |___________________|
;
;======================================================================
; ###########################################################################
; $TI Release: C28x SGEN Library v1.02.00.00 $
; $Release Date: Mon May 22 15:47:31 CDT 2017 $
; $Copyright: Copyright (C) 2011-2017 Texas Instruments Incorporated -
;             http://www.ti.com/ ALL RIGHTS RESERVED $
; ###########################################################################

; Module definition for external reference
                .def    _SGENHP_1_calc     
                .ref    SINTAB_360
                             
_SGENHP_1_calc:  
            SETC    SXM             
            ADDB	XAR4,#2			; XAR4->freq
            MOVL    XAR5,#SINTAB_360
                            
; Obtain the step value in pro-rata with the freq input         
            MOVL    XT,*XAR4++      ; XAR4->step_max, T=freq
            QMPYL   ACC,XT,*XAR4    ; ACC=freq*step_max 
            IMPYL   P,XT,*XAR4++    ; XAR4->alpha
            LSL64   ACC:P,1         ; ACC=freq*step_max in Q0 format

; Add the step value = (freq*stepmax) to alpha (32-bit addition)
            CLRC    OVM
            ADDL    ACC,*XAR4       ; ACC=(freq*step_max)+alpha  (Q0)
            MOVL    *XAR4,ACC       ; XAR4->alpha, alpha=alpha+step (Unsigned 8.24 format) 
            SETC    OVM           
           
; Obtain the SIN of the angle "X=alpha" using Look-up Table and Linear Interpolation method
            MOVB    XAR0,#0   
            MOVB    AR0,AH.MSB      ; AR0=indice (alpha/2^8)
            MOVH    AL,ACC<<7       ; AL=(X-X1) in Q15 format
            AND     ACC,#7fffh  
            MOV     T,AL            ; T=X-X1 in Q15 format  

            MOV     ACC,*+XAR5[AR0] ; ACC=Y1=*(SINTAB_360 + indice)  in Q15
            ADDB    XAR0,#1
            MOV     PL,*+XAR5[AR0]  ; PL=Y2
            SUB     PL,AL           ; PL=Y2-Y1 in Q15 
            MPY     P,T,PL          ; P=Y2-Y1 in Q30
            LSL     ACC,15          ; ACC=Y1 in Q30
            ADDL    ACC,P           ; Y=Y1+(Y2-Y1)*(X-X1)  in Q30
            MOVH    T,ACC<<1        ; T=Y in Q15 format Q15
      
; Scale the SIN output with the gain and add offset   
            MPY     ACC,T,*+XAR4[2] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[3]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR4[4],AH    ; out=Y*gain+offset
            CLRC    OVM
            LRETR

            

