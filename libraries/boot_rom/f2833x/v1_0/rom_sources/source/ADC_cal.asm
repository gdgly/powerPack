;; TI File $Revision: /main/2 $
;; Checkin $Date: June 8, 2007   10:12:37 $
;;###########################################################################
;;
;; FILE:    ADC_cal.asm
;;
;; TITLE:   2833x Boot Rom ADC Cal routine.
;;
;; Functions:
;;
;;     _ADC_cal
;;
;; Notes:
;;
;;###########################################################################
;; $TI Release: 2833x Boot ROM Version 1 $
;; $Release Date: June 25, 2007 $
;;###########################################################################

    .def _ADC_cal
	.asg "0x711C",   ADCREFSEL_LOC

;-----------------------------------------------
; _ADC_cal
;-----------------------------------------------
;-----------------------------------------------
; This is the ADC cal routine for the boot ROM
; This will be programmed into the TI half of the OTP
; and called during boot.
;
; This function assumes that the clocks have been
; enabled to the ADC module.
;-----------------------------------------------

    .sect ".adc_cal"

_ADC_cal
    MOVW  DP,   #ADCREFSEL_LOC >> 6
    MOV   @28,  #0xAAAA
    MOV   @29,  #0xBBBB
    LRETR
;eof ----------
