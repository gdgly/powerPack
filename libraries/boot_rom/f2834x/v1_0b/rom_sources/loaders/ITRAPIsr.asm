;; TI File $Revision: /main/1 $
;; Checkin $Date: May 30, 2008   14:12:14 $
;;###########################################################################
;;
;; FILE:    ITRAPIsr.asm
;;
;; TITLE:   Boot ROM ITRAP ISR.
;;
;; Functions:
;;
;;     _ITRAPIsr
;;
;; Notes:
;;  
;;###########################################################################
;; $TI Release: 2834x Boot ROM V1b $
;; $Release Date: June 3, 2008 $
;;###########################################################################

    .def _ITRAPIsr

;-----------------------------------------------
; _ITRAPIsr   
;-----------------------------------------------
;-----------------------------------------------
; This is the ITRAP interrupt service routine for
; thet boot ROM CPU vector table.  This routine
; would be called should an ITRAP be encoutered 
; before the PIE module was initalized and enabled. 
; 
; This module performs the following actions:
; 
;     1) enables the watchdog
;     2) loops forever
;-----------------------------------------------
         
    .sect ".Isr"
             
_ITRAPIsr:
    SETC OBJMODE        ;Set OBJMODE for 28x object code
    EALLOW              ;Enable EALLOW protected register access
    MOVZ DP, #7029h>>6  ;Set data page for WDCR register
    MOV @7029h, #0028h  ;Clear WDDIS bit in WDCR to enable Watchdog
    EDIS                ;Disable EALLOW protected register access                             
    SB 0,UNC            ;Loop forever    
    
;eof ----------    
