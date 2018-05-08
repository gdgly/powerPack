;; TI File $Revision: /main/3 $
;; Checkin $Date: May 8, 2007   12:28:28 $
;;###########################################################################
;;
;; FILE:    ITRAPIsr.asm
;;
;; TITLE:   2833x Boot Rom ITRAP ISR.
;;
;; Functions:
;;
;;     _ITRAPIsr
;;
;; Notes:
;;  
;;###########################################################################
;; $TI Release: 2833x/2823x Boot ROM V2 $
;; $Release Date: March 4, 2008 $
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
