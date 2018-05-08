;; TI File $Revision: /main/1 $
;; Checkin $Date: May 30, 2008   14:12:19 $
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
;; $TI Release: 2834x Boot ROM V1b $
;; $Release Date: June 3, 2008 $
;;###########################################################################

    .sect rsvd1
    .asg  0xFFFF,x
    .loop 0x0594
    .word   x
    .endloop

    .end
