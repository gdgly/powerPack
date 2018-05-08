;; TI File $Revision: /main/6 $
;; Checkin $Date: June 19, 2007   15:39:53 $
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
;; $TI Release: 2833x Boot ROM Version 1 $
;; $Release Date: June 25, 2007 $
;;###########################################################################

    .sect rsvd1
    .asg  0xFFFF,x
    .loop 0x05E3
    .word   x
    .endloop

    .end
