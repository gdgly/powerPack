; TI File $Revision: /main/4 $
; Checkin $Date: March 4, 2008   13:26:41 $
;###########################################################################
;
; FILE:    ti_test.asm
; TITLE:   TI Test Data
;
;###########################################################################
;$TI Release: 2833x/2823x Boot ROM V2 $
;$Release Date: March 4, 2008 $
;###########################################################################


;----------------------------------------

     .sect "ti_prpg_sect"

_TI_PRPG_ADDR:


;----------------4K PRPG-----------------


_TI_4K_PRPG_1:
    .word 0x297c   ; 4K PRPG 1, Word 0
    .word 0x7502   ; 4K PRPG 1, Word 1
    .word 0x2b60   ; 4K PRPG 1, Word 2
    .word 0xfe37   ; 4K PRPG 1, Word 3
    .word 0x2137   ; 4K PRPG 1, Word 4
    .word 0xe158   ; 4K PRPG 1, Word 5
    .word 0x7928   ; 4K PRPG 1, Word 6
    .word 0x0fdc   ; 4K PRPG 1, Word 7
    .word 0x2313   ; 4K PRPG 1, Word 8
    .word 0xad64   ; 4K PRPG 1, Word 9
    .word 0x7368   ; 4K PRPG 1, Word 10
    .word 0xf616   ; 4K PRPG 1, Word 11
    .word 0x2b9f   ; 4K PRPG 1, Word 12
    .word 0x679a   ; 4K PRPG 1, Word 13
    .word 0x3965   ; 4K PRPG 1, Word 14
    .word 0xc6a1   ; 4K PRPG 1, Word 15
    .word 0x0001   ; 4K PRPG 1, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_2:
    .word 0xfc9b   ; 4K PRPG 2, Word 0
    .word 0x42f1   ; 4K PRPG 2, Word 1
    .word 0x7210   ; 4K PRPG 2, Word 2
    .word 0x7e4c   ; 4K PRPG 2, Word 3
    .word 0xd135   ; 4K PRPG 2, Word 4
    .word 0xd2b8   ; 4K PRPG 2, Word 5
    .word 0x9613   ; 4K PRPG 2, Word 6
    .word 0x33e4   ; 4K PRPG 2, Word 7
    .word 0x284b   ; 4K PRPG 2, Word 8
    .word 0xafa8   ; 4K PRPG 2, Word 9
    .word 0x67f3   ; 4K PRPG 2, Word 10
    .word 0xee87   ; 4K PRPG 2, Word 11
    .word 0xe77c   ; 4K PRPG 2, Word 12
    .word 0xca05   ; 4K PRPG 2, Word 13
    .word 0x1bb0   ; 4K PRPG 2, Word 14
    .word 0x7e4f   ; 4K PRPG 2, Word 15
    .word 0x0001   ; 4K PRPG 2, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_3:
    .word 0xaa10   ; 4K PRPG 3, Word 0
    .word 0x46f5   ; 4K PRPG 3, Word 1
    .word 0xe916   ; 4K PRPG 3, Word 2
    .word 0x3381   ; 4K PRPG 3, Word 3
    .word 0xefcc   ; 4K PRPG 3, Word 4
    .word 0x7e4d   ; 4K PRPG 3, Word 5
    .word 0x5aec   ; 4K PRPG 3, Word 6
    .word 0x1942   ; 4K PRPG 3, Word 7
    .word 0x835c   ; 4K PRPG 3, Word 8
    .word 0x68ad   ; 4K PRPG 3, Word 9
    .word 0xc0ca   ; 4K PRPG 3, Word 10
    .word 0x7a36   ; 4K PRPG 3, Word 11
    .word 0x234d   ; 4K PRPG 3, Word 12
    .word 0x7f4c   ; 4K PRPG 3, Word 13
    .word 0x8bbe   ; 4K PRPG 3, Word 14
    .word 0x3b6d   ; 4K PRPG 3, Word 15
    .word 0x0001   ; 4K PRPG 3, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_4:
    .word 0xdc66   ; 4K PRPG 4, Word 0
    .word 0x9b01   ; 4K PRPG 4, Word 1
    .word 0xaf9b   ; 4K PRPG 4, Word 2
    .word 0x5e7b   ; 4K PRPG 4, Word 3
    .word 0x306f   ; 4K PRPG 4, Word 4
    .word 0x2346   ; 4K PRPG 4, Word 5
    .word 0xb255   ; 4K PRPG 4, Word 6
    .word 0x9bef   ; 4K PRPG 4, Word 7
    .word 0xc860   ; 4K PRPG 4, Word 8
    .word 0xada5   ; 4K PRPG 4, Word 9
    .word 0x26e6   ; 4K PRPG 4, Word 10
    .word 0xea0e   ; 4K PRPG 4, Word 11
    .word 0x8cae   ; 4K PRPG 4, Word 12
    .word 0x6344   ; 4K PRPG 4, Word 13
    .word 0x109b   ; 4K PRPG 4, Word 14
    .word 0xa142   ; 4K PRPG 4, Word 15
    .word 0x0000   ; 4K PRPG 4, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_5:
    .word 0xf31a   ; 4K PRPG 5, Word 0
    .word 0x128e   ; 4K PRPG 5, Word 1
    .word 0xb3d4   ; 4K PRPG 5, Word 2
    .word 0x5185   ; 4K PRPG 5, Word 3
    .word 0x4a58   ; 4K PRPG 5, Word 4
    .word 0xb1c6   ; 4K PRPG 5, Word 5
    .word 0xe0e3   ; 4K PRPG 5, Word 6
    .word 0xf296   ; 4K PRPG 5, Word 7
    .word 0x6a44   ; 4K PRPG 5, Word 8
    .word 0xa669   ; 4K PRPG 5, Word 9
    .word 0x0d23   ; 4K PRPG 5, Word 10
    .word 0xb8b9   ; 4K PRPG 5, Word 11
    .word 0x015d   ; 4K PRPG 5, Word 12
    .word 0x0f22   ; 4K PRPG 5, Word 13
    .word 0x1767   ; 4K PRPG 5, Word 14
    .word 0x14e9   ; 4K PRPG 5, Word 15
    .word 0x0000   ; 4K PRPG 5, Word 16
    .word 0x0000   ; alignment


;---------------64K PRPG-----------------


_TI_64K_PRPG_1:
    .word 0x297c   ; 64K PRPG 1, Word 0
    .word 0x7502   ; 64K PRPG 1, Word 1
    .word 0x2b60   ; 64K PRPG 1, Word 2
    .word 0xfe37   ; 64K PRPG 1, Word 3
    .word 0x2137   ; 64K PRPG 1, Word 4
    .word 0xe158   ; 64K PRPG 1, Word 5
    .word 0x7928   ; 64K PRPG 1, Word 6
    .word 0x0fdc   ; 64K PRPG 1, Word 7
    .word 0x2313   ; 64K PRPG 1, Word 8
    .word 0xad64   ; 64K PRPG 1, Word 9
    .word 0x7368   ; 64K PRPG 1, Word 10
    .word 0xf616   ; 64K PRPG 1, Word 11
    .word 0x2b9f   ; 64K PRPG 1, Word 12
    .word 0x679a   ; 64K PRPG 1, Word 13
    .word 0x3965   ; 64K PRPG 1, Word 14
    .word 0xc6a1   ; 64K PRPG 1, Word 15
    .word 0x0001   ; 64K PRPG 1, Word 16
    .word 0x0000   ; alignment

_TI_64K_PRPG_2:
    .word 0xa8fa   ; 64K PRPG 2, Word 0
    .word 0x3f0c   ; 64K PRPG 2, Word 1
    .word 0xb0c1   ; 64K PRPG 2, Word 2
    .word 0x6f52   ; 64K PRPG 2, Word 3
    .word 0x989b   ; 64K PRPG 2, Word 4
    .word 0x09b9   ; 64K PRPG 2, Word 5
    .word 0x35d4   ; 64K PRPG 2, Word 6
    .word 0xa855   ; 64K PRPG 2, Word 7
    .word 0x5931   ; 64K PRPG 2, Word 8
    .word 0x4b25   ; 64K PRPG 2, Word 9
    .word 0x38d3   ; 64K PRPG 2, Word 10
    .word 0xdaa8   ; 64K PRPG 2, Word 11
    .word 0xb4eb   ; 64K PRPG 2, Word 12
    .word 0x0d5d   ; 64K PRPG 2, Word 13
    .word 0x984c   ; 64K PRPG 2, Word 14
    .word 0x1896   ; 64K PRPG 2, Word 15
    .word 0x0000   ; 64K PRPG 2, Word 16
    .word 0x0000   ; alignment

_TI_64K_PRPG_3:
    .word 0x625d   ; 64K PRPG 3, Word 0
    .word 0xe796   ; 64K PRPG 3, Word 1
    .word 0xfb21   ; 64K PRPG 3, Word 2
    .word 0xf2d3   ; 64K PRPG 3, Word 3
    .word 0xa190   ; 64K PRPG 3, Word 4
    .word 0x6304   ; 64K PRPG 3, Word 5
    .word 0x6d7b   ; 64K PRPG 3, Word 6
    .word 0xdb0a   ; 64K PRPG 3, Word 7
    .word 0xded7   ; 64K PRPG 3, Word 8
    .word 0xecf3   ; 64K PRPG 3, Word 9
    .word 0xb02c   ; 64K PRPG 3, Word 10
    .word 0xe3b2   ; 64K PRPG 3, Word 11
    .word 0xe0b5   ; 64K PRPG 3, Word 12
    .word 0xc533   ; 64K PRPG 3, Word 13
    .word 0x7a4e   ; 64K PRPG 3, Word 14
    .word 0x6c94   ; 64K PRPG 3, Word 15
    .word 0x0000   ; 64K PRPG 3, Word 16
    .word 0x0000   ; alignment


;-----------------MISR------------------

     .sect "ti_misr_sect"

_TI_MISR_ADDR:


;----------------4K MISR-----------------


_TI_4K_MISR_1:
    .word 0x1843   ; 4K MISR 1, Word 0
    .word 0xe44e   ; 4K MISR 1, Word 1
    .word 0x6d63   ; 4K MISR 1, Word 2
    .word 0x1058   ; 4K MISR 1, Word 3
    .word 0x5090   ; 4K MISR 1, Word 4
    .word 0x7921   ; 4K MISR 1, Word 5
    .word 0x541b   ; 4K MISR 1, Word 6
    .word 0x8663   ; 4K MISR 1, Word 7

_TI_4K_MISR_2:
    .word 0xa96d   ; 4K MISR 2, Word 0
    .word 0x7e0a   ; 4K MISR 2, Word 1
    .word 0x27e7   ; 4K MISR 2, Word 2
    .word 0xb87b   ; 4K MISR 2, Word 3
    .word 0x050b   ; 4K MISR 2, Word 4
    .word 0x45f7   ; 4K MISR 2, Word 5
    .word 0x52c8   ; 4K MISR 2, Word 6
    .word 0x0220   ; 4K MISR 2, Word 7

_TI_4K_MISR_3:
    .word 0x751f   ; 4K MISR 3, Word 0
    .word 0x2b27   ; 4K MISR 3, Word 1
    .word 0x34cd   ; 4K MISR 3, Word 2
    .word 0xd680   ; 4K MISR 3, Word 3
    .word 0x4e50   ; 4K MISR 3, Word 4
    .word 0xe53f   ; 4K MISR 3, Word 5
    .word 0xb3e7   ; 4K MISR 3, Word 6
    .word 0x066a   ; 4K MISR 3, Word 7

_TI_4K_MISR_4:
    .word 0x03a3   ; 4K MISR 4, Word 0
    .word 0x2f52   ; 4K MISR 4, Word 1
    .word 0x5587   ; 4K MISR 4, Word 2
    .word 0xa5cb   ; 4K MISR 4, Word 3
    .word 0xb908   ; 4K MISR 4, Word 4
    .word 0xbb92   ; 4K MISR 4, Word 5
    .word 0xe7e4   ; 4K MISR 4, Word 6
    .word 0x2e71   ; 4K MISR 4, Word 7

_TI_4K_MISR_5:
    .word 0xd104   ; 4K MISR 5, Word 0
    .word 0x6f18   ; 4K MISR 5, Word 1
    .word 0xba6c   ; 4K MISR 5, Word 2
    .word 0xe594   ; 4K MISR 5, Word 3
    .word 0xd74d   ; 4K MISR 5, Word 4
    .word 0x2d2d   ; 4K MISR 5, Word 5
    .word 0x8088   ; 4K MISR 5, Word 6
    .word 0x9159   ; 4K MISR 5, Word 7


;---------------64K MISR-----------------


_TI_64K_MISR_1:
    .word 0xac4b   ; 64K MISR 1, Word 0
    .word 0xd709   ; 64K MISR 1, Word 1
    .word 0xcf3b   ; 64K MISR 1, Word 2
    .word 0x198f   ; 64K MISR 1, Word 3
    .word 0xd6e7   ; 64K MISR 1, Word 4
    .word 0x2dcc   ; 64K MISR 1, Word 5
    .word 0x0ab6   ; 64K MISR 1, Word 6
    .word 0xe0c2   ; 64K MISR 1, Word 7

_TI_64K_MISR_2:
    .word 0x59d0   ; 64K MISR 2, Word 0
    .word 0xae96   ; 64K MISR 2, Word 1
    .word 0x3277   ; 64K MISR 2, Word 2
    .word 0x68b2   ; 64K MISR 2, Word 3
    .word 0x604b   ; 64K MISR 2, Word 4
    .word 0xf760   ; 64K MISR 2, Word 5
    .word 0xde3e   ; 64K MISR 2, Word 6
    .word 0xca7d   ; 64K MISR 2, Word 7

_TI_64K_MISR_3:
    .word 0x4282   ; 64K MISR 3, Word 0
    .word 0x6e79   ; 64K MISR 3, Word 1
    .word 0xf474   ; 64K MISR 3, Word 2
    .word 0x9440   ; 64K MISR 3, Word 3
    .word 0x7023   ; 64K MISR 3, Word 4
    .word 0x9073   ; 64K MISR 3, Word 5
    .word 0x5e97   ; 64K MISR 3, Word 6
    .word 0xa5e3   ; 64K MISR 3, Word 7


;---------------The End-------------------

