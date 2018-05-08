;; TI File $Revision: /main/10 $
;; Checkin $Date: March 4, 2008   15:50:42 $
;;###########################################################################
;;
;; FILE:    ReservedSpace.asm
;;
;; TITLE:   Boot Rom reserved space init.
;;
;; Functions:
;;
;; Fill in reserved space in BOOT ROM
;; with 0xFFFF
;;
;; Notes:
;;
;;###########################################################################
;; $TI Release: 2833x/2823x Boot ROM V2 $
;; $Release Date: March 4, 2008 $
;;###########################################################################

    .sect rsvd1
    .asg  0xFFFF,x
    .loop 0x05BE
    .word   x
    .endloop

    .end
