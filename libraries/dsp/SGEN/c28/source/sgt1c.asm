;======================================================================
;
; File Name     : SGT1C.ASM
; 
; Originator    : Advanced Embedded Control (AEC)
;                 Texas Instruments Inc.
; 
; Description   : This file contain source code for single channel
;                 SIN generator module(Using Direct Table look-up)
;                 * Direct Table look-up implementation provides, Standard
;                 THD and Standard phase Resolution
;               
; Routine Type  : CcA
;               
; Date          : 27/12/2001 (DD/MM/YYYY)
;======================================================================
; Description:
;                            ___________________
;                           |                   |
;        gain   o---------->|                   |
;        offset o---------->|     SGENT_1       |----->o OUT
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
                .def    _SGENT_1_calc      
                .ref    SINTAB_360
                              
_SGENT_1_calc:      
            SETC    SXM,OVM         ; XAR4->freq
                            
; Obtain the step value in pro-rata with the freq input         
            MOV     T,*XAR4++       ; XAR4->step_max, T=freq
            MPY     ACC,T,*XAR4++   ; XAR4->alpha, ACC=freq*step_max (Q15)
            MOVH    AL,ACC<<1           
            
; Increment the angle "alpha" by step value             
            ADD     AL,*XAR4        ; AL=(freq*step_max)+alpha  (Q0)
            MOV     *XAR4,AL        ; XAR4->alpha, alpha=alpha+step (Unsigned 8.8 format)   

; Obtain the SIN of the angle "X=alpha" using direct Look-up Table            
            MOVL    XAR5,#SINTAB_360
            MOVB    XAR0,#0         
            MOVB    AR0,AL.MSB      ; AR0=indice (alpha/2^8)
            MOV     T,*+XAR5[AR0]   ; T=Y=*(SINTAB_360 + indice)

; Scale the SIN output with the gain and add offset           
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR4[3],AH    ; out=Y*gain+offset
        	CLRC 	OVM
        	LRETR
            


