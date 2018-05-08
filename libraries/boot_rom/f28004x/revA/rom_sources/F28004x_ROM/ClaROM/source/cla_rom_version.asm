;;###########################################################################
;;
;; FILE:    cla_rom_version.asm
;;
;; TITLE:   CLA data ROM Version and checksum values.
;;
;; Functions:
;;
;;
;; Notes:
;;
;;###########################################################################
;; $TI Release: F28004x Boot ROM V1.0 $
;; $Release Date: July 2015 $
;;###########################################################################

    .sect ".CROMVersion"
    .word 0x0100     ; Boot ROM Version v1.0
    .word 0x0715     ; Month/Year: (ex: 0x0109 = 1/09 = Jan 2009)

