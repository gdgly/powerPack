; TI File $Revision: /main/2 $
; Checkin $Date: June 19, 2007   15:39:44 $
;###########################################################################
;
; FILE:    TI_Test.asm
; TITLE:   TI Test Data
;
;###########################################################################
;$TI Release: 2833x Boot ROM Version 1 $
;$Release Date: June 25, 2007 $
;###########################################################################


;----------------------------------------

     .sect "ti_prpg_sect"

_TI_PRPG_ADDR:


;----------------4K PRPG-----------------


_TI_4K_PRPG_1:
    .word 0x8873   ; 4K PRPG 1, Word 0
    .word 0x2599   ; 4K PRPG 1, Word 1
    .word 0x55f0   ; 4K PRPG 1, Word 2
    .word 0x236e   ; 4K PRPG 1, Word 3
    .word 0x2d1b   ; 4K PRPG 1, Word 4
    .word 0x9b99   ; 4K PRPG 1, Word 5
    .word 0xe66b   ; 4K PRPG 1, Word 6
    .word 0xbfb4   ; 4K PRPG 1, Word 7
    .word 0xb5d3   ; 4K PRPG 1, Word 8
    .word 0x9ba3   ; 4K PRPG 1, Word 9
    .word 0x1c0c   ; 4K PRPG 1, Word 10
    .word 0x0efd   ; 4K PRPG 1, Word 11
    .word 0x441e   ; 4K PRPG 1, Word 12
    .word 0xf205   ; 4K PRPG 1, Word 13
    .word 0x769a   ; 4K PRPG 1, Word 14
    .word 0x37f7   ; 4K PRPG 1, Word 15
    .word 0x0000   ; 4K PRPG 1, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_2:
    .word 0x083e   ; 4K PRPG 2, Word 0
    .word 0x8386   ; 4K PRPG 2, Word 1
    .word 0x0608   ; 4K PRPG 2, Word 2
    .word 0x04ec   ; 4K PRPG 2, Word 3
    .word 0x185d   ; 4K PRPG 2, Word 4
    .word 0xe904   ; 4K PRPG 2, Word 5
    .word 0x7281   ; 4K PRPG 2, Word 6
    .word 0x37e5   ; 4K PRPG 2, Word 7
    .word 0xab94   ; 4K PRPG 2, Word 8
    .word 0xec4a   ; 4K PRPG 2, Word 9
    .word 0xfdfa   ; 4K PRPG 2, Word 10
    .word 0x0dde   ; 4K PRPG 2, Word 11
    .word 0x952f   ; 4K PRPG 2, Word 12
    .word 0xe882   ; 4K PRPG 2, Word 13
    .word 0x1a6d   ; 4K PRPG 2, Word 14
    .word 0x2211   ; 4K PRPG 2, Word 15
    .word 0x0001   ; 4K PRPG 2, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_3:
    .word 0x6392   ; 4K PRPG 3, Word 0
    .word 0x160b   ; 4K PRPG 3, Word 1
    .word 0x7bee   ; 4K PRPG 3, Word 2
    .word 0x25e0   ; 4K PRPG 3, Word 3
    .word 0xfe53   ; 4K PRPG 3, Word 4
    .word 0xe311   ; 4K PRPG 3, Word 5
    .word 0x8ab2   ; 4K PRPG 3, Word 6
    .word 0x6708   ; 4K PRPG 3, Word 7
    .word 0x5afd   ; 4K PRPG 3, Word 8
    .word 0xb727   ; 4K PRPG 3, Word 9
    .word 0x681f   ; 4K PRPG 3, Word 10
    .word 0x5633   ; 4K PRPG 3, Word 11
    .word 0xc31c   ; 4K PRPG 3, Word 12
    .word 0x721c   ; 4K PRPG 3, Word 13
    .word 0x4161   ; 4K PRPG 3, Word 14
    .word 0x66e3   ; 4K PRPG 3, Word 15
    .word 0x0000   ; 4K PRPG 3, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_4:
    .word 0x65a2   ; 4K PRPG 4, Word 0
    .word 0x1a82   ; 4K PRPG 4, Word 1
    .word 0x1af7   ; 4K PRPG 4, Word 2
    .word 0xf985   ; 4K PRPG 4, Word 3
    .word 0x593a   ; 4K PRPG 4, Word 4
    .word 0x3f4f   ; 4K PRPG 4, Word 5
    .word 0xeb47   ; 4K PRPG 4, Word 6
    .word 0x395f   ; 4K PRPG 4, Word 7
    .word 0xc74c   ; 4K PRPG 4, Word 8
    .word 0xac98   ; 4K PRPG 4, Word 9
    .word 0xc6fd   ; 4K PRPG 4, Word 10
    .word 0xd786   ; 4K PRPG 4, Word 11
    .word 0x707d   ; 4K PRPG 4, Word 12
    .word 0x62f8   ; 4K PRPG 4, Word 13
    .word 0xacb8   ; 4K PRPG 4, Word 14
    .word 0x3868   ; 4K PRPG 4, Word 15
    .word 0x0001   ; 4K PRPG 4, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_5:
    .word 0x355a   ; 4K PRPG 5, Word 0
    .word 0xdc19   ; 4K PRPG 5, Word 1
    .word 0x12d0   ; 4K PRPG 5, Word 2
    .word 0xd1e5   ; 4K PRPG 5, Word 3
    .word 0x700a   ; 4K PRPG 5, Word 4
    .word 0x26d4   ; 4K PRPG 5, Word 5
    .word 0xee5b   ; 4K PRPG 5, Word 6
    .word 0x650f   ; 4K PRPG 5, Word 7
    .word 0xdc9d   ; 4K PRPG 5, Word 8
    .word 0x251f   ; 4K PRPG 5, Word 9
    .word 0xcebf   ; 4K PRPG 5, Word 10
    .word 0xd534   ; 4K PRPG 5, Word 11
    .word 0x02cc   ; 4K PRPG 5, Word 12
    .word 0xbf03   ; 4K PRPG 5, Word 13
    .word 0xad16   ; 4K PRPG 5, Word 14
    .word 0x2d1f   ; 4K PRPG 5, Word 15
    .word 0x0001   ; 4K PRPG 5, Word 16
    .word 0x0000   ; alignment


;---------------64K PRPG-----------------


_TI_64K_PRPG_1:
    .word 0x8873   ; 64K PRPG 1, Word 0
    .word 0x2599   ; 64K PRPG 1, Word 1
    .word 0x55f0   ; 64K PRPG 1, Word 2
    .word 0x236e   ; 64K PRPG 1, Word 3
    .word 0x2d1b   ; 64K PRPG 1, Word 4
    .word 0x9b99   ; 64K PRPG 1, Word 5
    .word 0xe66b   ; 64K PRPG 1, Word 6
    .word 0xbfb4   ; 64K PRPG 1, Word 7
    .word 0xb5d3   ; 64K PRPG 1, Word 8
    .word 0x9ba3   ; 64K PRPG 1, Word 9
    .word 0x1c0c   ; 64K PRPG 1, Word 10
    .word 0x0efd   ; 64K PRPG 1, Word 11
    .word 0x441e   ; 64K PRPG 1, Word 12
    .word 0xf205   ; 64K PRPG 1, Word 13
    .word 0x769a   ; 64K PRPG 1, Word 14
    .word 0x37f7   ; 64K PRPG 1, Word 15
    .word 0x0000   ; 64K PRPG 1, Word 16
    .word 0x0000   ; alignment

_TI_64K_PRPG_2:
    .word 0xb1c2   ; 64K PRPG 2, Word 0
    .word 0x4fa4   ; 64K PRPG 2, Word 1
    .word 0x39d9   ; 64K PRPG 2, Word 2
    .word 0xb3b0   ; 64K PRPG 2, Word 3
    .word 0xd0d7   ; 64K PRPG 2, Word 4
    .word 0x19fe   ; 64K PRPG 2, Word 5
    .word 0x5554   ; 64K PRPG 2, Word 6
    .word 0x0459   ; 64K PRPG 2, Word 7
    .word 0x7b0d   ; 64K PRPG 2, Word 8
    .word 0x70d0   ; 64K PRPG 2, Word 9
    .word 0x7a54   ; 64K PRPG 2, Word 10
    .word 0x536c   ; 64K PRPG 2, Word 11
    .word 0x13ce   ; 64K PRPG 2, Word 12
    .word 0xc8c0   ; 64K PRPG 2, Word 13
    .word 0x726c   ; 64K PRPG 2, Word 14
    .word 0x39aa   ; 64K PRPG 2, Word 15
    .word 0x0000   ; 64K PRPG 2, Word 16
    .word 0x0000   ; alignment

_TI_64K_PRPG_3:
    .word 0x9b7a   ; 64K PRPG 3, Word 0
    .word 0x383c   ; 64K PRPG 3, Word 1
    .word 0xd9de   ; 64K PRPG 3, Word 2
    .word 0x0a48   ; 64K PRPG 3, Word 3
    .word 0x989b   ; 64K PRPG 3, Word 4
    .word 0xec08   ; 64K PRPG 3, Word 5
    .word 0x4650   ; 64K PRPG 3, Word 6
    .word 0x4c9f   ; 64K PRPG 3, Word 7
    .word 0x7c65   ; 64K PRPG 3, Word 8
    .word 0xf669   ; 64K PRPG 3, Word 9
    .word 0xf50a   ; 64K PRPG 3, Word 10
    .word 0xce8e   ; 64K PRPG 3, Word 11
    .word 0x37bc   ; 64K PRPG 3, Word 12
    .word 0x78c6   ; 64K PRPG 3, Word 13
    .word 0xff3f   ; 64K PRPG 3, Word 14
    .word 0x2797   ; 64K PRPG 3, Word 15
    .word 0x0000   ; 64K PRPG 3, Word 16
    .word 0x0000   ; alignment


;-----------------MISR------------------

     .sect "ti_misr_sect"

_TI_MISR_ADDR:


;----------------4K MISR-----------------


_TI_4K_MISR_1:
    .word 0x3543    ; 4K MISR 1, Word 0
    .word 0xcad5   ; 4K MISR 1, Word 1
    .word 0xf253   ; 4K MISR 1, Word 2
    .word 0xc910   ; 4K MISR 1, Word 3
    .word 0xf5cf   ; 4K MISR 1, Word 4
    .word 0x8d0b   ; 4K MISR 1, Word 5
    .word 0xcda2   ; 4K MISR 1, Word 6
    .word 0xc8cc    ; 4K MISR 1, Word 7

_TI_4K_MISR_2:
    .word 0x7503   ; 4K MISR 2, Word 0
    .word 0x61f2   ; 4K MISR 2, Word 1
    .word 0x8fbb   ; 4K MISR 2, Word 2
    .word 0xdb2b   ; 4K MISR 2, Word 3
    .word 0xae4d   ; 4K MISR 2, Word 4
    .word 0xedeb   ; 4K MISR 2, Word 5
    .word 0xb7b4   ; 4K MISR 2, Word 6
    .word 0xcedd   ; 4K MISR 2, Word 7

_TI_4K_MISR_3:
    .word 0x83c2   ; 4K MISR 3, Word 0
    .word 0x3cae   ; 4K MISR 3, Word 1
    .word 0x34ad   ; 4K MISR 3, Word 2
    .word 0x43eb   ; 4K MISR 3, Word 3
    .word 0x456c   ; 4K MISR 3, Word 4
    .word 0x7d6d   ; 4K MISR 3, Word 5
    .word 0x8f5e   ; 4K MISR 3, Word 6
    .word 0x7681   ; 4K MISR 3, Word 7

_TI_4K_MISR_4:
    .word 0xc2df   ; 4K MISR 4, Word 0
    .word 0x8683   ; 4K MISR 4, Word 1
    .word 0x6715   ; 4K MISR 4, Word 2
    .word 0xc8f1   ; 4K MISR 4, Word 3
    .word 0x2e33   ; 4K MISR 4, Word 4
    .word 0x9b42   ; 4K MISR 4, Word 5
    .word 0x5dab   ; 4K MISR 4, Word 6
    .word 0xaa29   ; 4K MISR 4, Word 7

_TI_4K_MISR_5:
    .word 0xede1   ; 4K MISR 5, Word 0
    .word 0xdb42   ; 4K MISR 5, Word 1
    .word 0xf289   ; 4K MISR 5, Word 2
    .word 0x4438   ; 4K MISR 5, Word 3
    .word 0x6f2b   ; 4K MISR 5, Word 4
    .word 0x604f   ; 4K MISR 5, Word 5
    .word 0xb1be   ; 4K MISR 5, Word 6
    .word 0x3efd   ; 4K MISR 5, Word 7


;---------------64K MISR-----------------


_TI_64K_MISR_1:
    .word 0x789a   ; 64K MISR 1, Word 0
    .word 0x27a9   ; 64K MISR 1, Word 1
    .word 0xdc0a   ; 64K MISR 1, Word 2
    .word 0x29f5   ; 64K MISR 1, Word 3
    .word 0x344d   ; 64K MISR 1, Word 4
    .word 0x27f3   ; 64K MISR 1, Word 5
    .word 0xaa36   ; 64K MISR 1, Word 6
    .word 0xf18d   ; 64K MISR 1, Word 7

_TI_64K_MISR_2:
    .word 0x5f46   ; 64K MISR 2, Word 0
    .word 0xfd81   ; 64K MISR 2, Word 1
    .word 0xc2a6   ; 64K MISR 2, Word 2
    .word 0xfdb1   ; 64K MISR 2, Word 3
    .word 0x08c0   ; 64K MISR 2, Word 4
    .word 0x9da9   ; 64K MISR 2, Word 5
    .word 0x7991   ; 64K MISR 2, Word 6
    .word 0x0b47   ; 64K MISR 2, Word 7

_TI_64K_MISR_3:
    .word 0xede8   ; 64K MISR 3, Word 0
    .word 0x5236   ; 64K MISR 3, Word 1
    .word 0x2820   ; 64K MISR 3, Word 2
    .word 0x9a4d   ; 64K MISR 3, Word 3
    .word 0x4223   ; 64K MISR 3, Word 4
    .word 0x9aef   ; 64K MISR 3, Word 5
    .word 0x6c20   ; 64K MISR 3, Word 6
    .word 0x66fd   ; 64K MISR 3, Word 7


;---------------The End-------------------

