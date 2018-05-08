; TI File $Revision: /main/3 $
; Checkin $Date: June 3, 2008   11:03:50 $
;###########################################################################
;
; FILE:    ti_test.asm
; TITLE:   TI Test Data
;
;###########################################################################
;$TI Release: 2834x Boot ROM V1b $
;$Release Date: June 3, 2008 $
;###########################################################################


;----------------------------------------

     .sect "ti_prpg_sect"

_TI_PRPG_ADDR:


;----------------4K PRPG-----------------


_TI_4K_PRPG_1:
    .word 0xc2d1   ; 4K PRPG 1, Word 0
    .word 0x5e3f   ; 4K PRPG 1, Word 1
    .word 0x50e5   ; 4K PRPG 1, Word 2
    .word 0x128a   ; 4K PRPG 1, Word 3
    .word 0x97c2   ; 4K PRPG 1, Word 4
    .word 0x4b41   ; 4K PRPG 1, Word 5
    .word 0x7569   ; 4K PRPG 1, Word 6
    .word 0xfd33   ; 4K PRPG 1, Word 7
    .word 0x744b   ; 4K PRPG 1, Word 8
    .word 0x2e8f   ; 4K PRPG 1, Word 9
    .word 0xcd45   ; 4K PRPG 1, Word 10
    .word 0x0740   ; 4K PRPG 1, Word 11
    .word 0x7594   ; 4K PRPG 1, Word 12
    .word 0xfd5a   ; 4K PRPG 1, Word 13
    .word 0xaa0c   ; 4K PRPG 1, Word 14
    .word 0x2783   ; 4K PRPG 1, Word 15
    .word 0x0001   ; 4K PRPG 1, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_2:
    .word 0xb02d   ; 4K PRPG 2, Word 0
    .word 0xcc7a   ; 4K PRPG 2, Word 1
    .word 0xf206   ; 4K PRPG 2, Word 2
    .word 0x5730   ; 4K PRPG 2, Word 3
    .word 0xf913   ; 4K PRPG 2, Word 4
    .word 0x0beb   ; 4K PRPG 2, Word 5
    .word 0x59d4   ; 4K PRPG 2, Word 6
    .word 0x4b87   ; 4K PRPG 2, Word 7
    .word 0x6048   ; 4K PRPG 2, Word 8
    .word 0x8a7d   ; 4K PRPG 2, Word 9
    .word 0xda05   ; 4K PRPG 2, Word 10
    .word 0xedec   ; 4K PRPG 2, Word 11
    .word 0xa481   ; 4K PRPG 2, Word 12
    .word 0xdb4c   ; 4K PRPG 2, Word 13
    .word 0xbf1a   ; 4K PRPG 2, Word 14
    .word 0xcea6   ; 4K PRPG 2, Word 15
    .word 0x0001   ; 4K PRPG 2, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_3:
    .word 0x1ad1   ; 4K PRPG 3, Word 0
    .word 0x4880   ; 4K PRPG 3, Word 1
    .word 0xd37e   ; 4K PRPG 3, Word 2
    .word 0x651a   ; 4K PRPG 3, Word 3
    .word 0x6f24   ; 4K PRPG 3, Word 4
    .word 0x7db1   ; 4K PRPG 3, Word 5
    .word 0x6485   ; 4K PRPG 3, Word 6
    .word 0x4231   ; 4K PRPG 3, Word 7
    .word 0x5f51   ; 4K PRPG 3, Word 8
    .word 0xb471   ; 4K PRPG 3, Word 9
    .word 0xf28c   ; 4K PRPG 3, Word 10
    .word 0x1314   ; 4K PRPG 3, Word 11
    .word 0xb6ac   ; 4K PRPG 3, Word 12
    .word 0x8be9   ; 4K PRPG 3, Word 13
    .word 0x278c   ; 4K PRPG 3, Word 14
    .word 0x2d28   ; 4K PRPG 3, Word 15
    .word 0x0001   ; 4K PRPG 3, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_4:
    .word 0xbf9a   ; 4K PRPG 4, Word 0
    .word 0x6fdf   ; 4K PRPG 4, Word 1
    .word 0xcc52   ; 4K PRPG 4, Word 2
    .word 0x4609   ; 4K PRPG 4, Word 3
    .word 0xab0f   ; 4K PRPG 4, Word 4
    .word 0xe268   ; 4K PRPG 4, Word 5
    .word 0xc99b   ; 4K PRPG 4, Word 6
    .word 0x9cbe   ; 4K PRPG 4, Word 7
    .word 0x16d2   ; 4K PRPG 4, Word 8
    .word 0x662d   ; 4K PRPG 4, Word 9
    .word 0x29df   ; 4K PRPG 4, Word 10
    .word 0xa9a2   ; 4K PRPG 4, Word 11
    .word 0x8a7b   ; 4K PRPG 4, Word 12
    .word 0xcedc   ; 4K PRPG 4, Word 13
    .word 0x12b8   ; 4K PRPG 4, Word 14
    .word 0xa8ac   ; 4K PRPG 4, Word 15
    .word 0x0001   ; 4K PRPG 4, Word 16
    .word 0x0000   ; alignment

_TI_4K_PRPG_5:
    .word 0xe540   ; 4K PRPG 5, Word 0
    .word 0x10a1   ; 4K PRPG 5, Word 1
    .word 0x5125   ; 4K PRPG 5, Word 2
    .word 0xdcd4   ; 4K PRPG 5, Word 3
    .word 0xff09   ; 4K PRPG 5, Word 4
    .word 0x5df8   ; 4K PRPG 5, Word 5
    .word 0x0723   ; 4K PRPG 5, Word 6
    .word 0x8af1   ; 4K PRPG 5, Word 7
    .word 0x0249   ; 4K PRPG 5, Word 8
    .word 0xfb5f   ; 4K PRPG 5, Word 9
    .word 0x1436   ; 4K PRPG 5, Word 10
    .word 0x4ecc   ; 4K PRPG 5, Word 11
    .word 0x5967   ; 4K PRPG 5, Word 12
    .word 0x5608   ; 4K PRPG 5, Word 13
    .word 0xc2b5   ; 4K PRPG 5, Word 14
    .word 0x5078   ; 4K PRPG 5, Word 15
    .word 0x0000   ; 4K PRPG 5, Word 16
    .word 0x0000   ; alignment


;---------------64K PRPG-----------------


_TI_64K_PRPG_1:
    .word 0x3bb5   ; 64K PRPG 1, Word 0
    .word 0x8d11   ; 64K PRPG 1, Word 1
    .word 0x65f6   ; 64K PRPG 1, Word 2
    .word 0xa9d1   ; 64K PRPG 1, Word 3
    .word 0xff42   ; 64K PRPG 1, Word 4
    .word 0x3dd4   ; 64K PRPG 1, Word 5
    .word 0xe253   ; 64K PRPG 1, Word 6
    .word 0x29a3   ; 64K PRPG 1, Word 7
    .word 0x3e58   ; 64K PRPG 1, Word 8
    .word 0x4fbf   ; 64K PRPG 1, Word 9
    .word 0x7747   ; 64K PRPG 1, Word 10
    .word 0x4420   ; 64K PRPG 1, Word 11
    .word 0xa8cc   ; 64K PRPG 1, Word 12
    .word 0xfe5c   ; 64K PRPG 1, Word 13
    .word 0x5fae   ; 64K PRPG 1, Word 14
    .word 0x238a   ; 64K PRPG 1, Word 15
    .word 0x0000   ; 64K PRPG 1, Word 16
    .word 0x0000   ; alignment

_TI_64K_PRPG_2:
    .word 0xd5ed   ; 64K PRPG 2, Word 0
    .word 0xf3f1   ; 64K PRPG 2, Word 1
    .word 0x3e50   ; 64K PRPG 2, Word 2
    .word 0xc922   ; 64K PRPG 2, Word 3
    .word 0xcf5b   ; 64K PRPG 2, Word 4
    .word 0x45e8   ; 64K PRPG 2, Word 5
    .word 0x940e   ; 64K PRPG 2, Word 6
    .word 0x21a2   ; 64K PRPG 2, Word 7
    .word 0xc81e   ; 64K PRPG 2, Word 8
    .word 0x2952   ; 64K PRPG 2, Word 9
    .word 0x1683   ; 64K PRPG 2, Word 10
    .word 0x1f80   ; 64K PRPG 2, Word 11
    .word 0x5240   ; 64K PRPG 2, Word 12
    .word 0x2fb7   ; 64K PRPG 2, Word 13
    .word 0x9f08   ; 64K PRPG 2, Word 14
    .word 0x4fd2   ; 64K PRPG 2, Word 15
    .word 0x0001   ; 64K PRPG 2, Word 16
    .word 0x0000   ; alignment

_TI_64K_PRPG_3:
    .word 0x7c18   ; 64K PRPG 3, Word 0
    .word 0x5a3d   ; 64K PRPG 3, Word 1
    .word 0x82b3   ; 64K PRPG 3, Word 2
    .word 0x65d8   ; 64K PRPG 3, Word 3
    .word 0x08f9   ; 64K PRPG 3, Word 4
    .word 0x8b39   ; 64K PRPG 3, Word 5
    .word 0x462d   ; 64K PRPG 3, Word 6
    .word 0x67ff   ; 64K PRPG 3, Word 7
    .word 0x8e3c   ; 64K PRPG 3, Word 8
    .word 0x3353   ; 64K PRPG 3, Word 9
    .word 0x1315   ; 64K PRPG 3, Word 10
    .word 0x4508   ; 64K PRPG 3, Word 11
    .word 0x53e4   ; 64K PRPG 3, Word 12
    .word 0xea25   ; 64K PRPG 3, Word 13
    .word 0xb862   ; 64K PRPG 3, Word 14
    .word 0x31bb   ; 64K PRPG 3, Word 15
    .word 0x0000   ; 64K PRPG 3, Word 16
    .word 0x0000   ; alignment


;-----------------MISR------------------

     .sect "ti_misr_sect"

_TI_MISR_ADDR:


;----------------4K MISR-----------------


_TI_4K_MISR_1:
    .word 0x311c   ; 4K MISR 1, Word 0
    .word 0xc2c8   ; 4K MISR 1, Word 1
    .word 0x36bb   ; 4K MISR 1, Word 2
    .word 0xfb55   ; 4K MISR 1, Word 3
    .word 0x4d7c   ; 4K MISR 1, Word 4
    .word 0x9dbb   ; 4K MISR 1, Word 5
    .word 0x91c0   ; 4K MISR 1, Word 6
    .word 0x9334   ; 4K MISR 1, Word 7

_TI_4K_MISR_2:
    .word 0xd015   ; 4K MISR 2, Word 0
    .word 0xccb5   ; 4K MISR 2, Word 1
    .word 0x96a6   ; 4K MISR 2, Word 2
    .word 0x009a   ; 4K MISR 2, Word 3
    .word 0xb33d   ; 4K MISR 2, Word 4
    .word 0xc0a9   ; 4K MISR 2, Word 5
    .word 0x5c61   ; 4K MISR 2, Word 6
    .word 0x2ad0   ; 4K MISR 2, Word 7

_TI_4K_MISR_3:
    .word 0x74a2   ; 4K MISR 3, Word 0
    .word 0x3d88   ; 4K MISR 3, Word 1
    .word 0x6855   ; 4K MISR 3, Word 2
    .word 0x866f   ; 4K MISR 3, Word 3
    .word 0x348d   ; 4K MISR 3, Word 4
    .word 0xfafa   ; 4K MISR 3, Word 5
    .word 0xe9c5   ; 4K MISR 3, Word 6
    .word 0xe94b   ; 4K MISR 3, Word 7

_TI_4K_MISR_4:
    .word 0x7183   ; 4K MISR 4, Word 0
    .word 0x7220   ; 4K MISR 4, Word 1
    .word 0x8ce5   ; 4K MISR 4, Word 2
    .word 0x9515   ; 4K MISR 4, Word 3
    .word 0x85b8   ; 4K MISR 4, Word 4
    .word 0x3489   ; 4K MISR 4, Word 5
    .word 0x631c   ; 4K MISR 4, Word 6
    .word 0x7bd6   ; 4K MISR 4, Word 7

_TI_4K_MISR_5:
    .word 0xbd03   ; 4K MISR 5, Word 0
    .word 0x1947   ; 4K MISR 5, Word 1
    .word 0xd47c   ; 4K MISR 5, Word 2
    .word 0x6275   ; 4K MISR 5, Word 3
    .word 0xee14   ; 4K MISR 5, Word 4
    .word 0x0b87   ; 4K MISR 5, Word 5
    .word 0x6c67   ; 4K MISR 5, Word 6
    .word 0x9232   ; 4K MISR 5, Word 7


;---------------64K MISR-----------------


_TI_64K_MISR_1:
    .word 0x4508   ; 64K MISR 1, Word 0
    .word 0xec39   ; 64K MISR 1, Word 1
    .word 0xb46c   ; 64K MISR 1, Word 2
    .word 0x8193   ; 64K MISR 1, Word 3
    .word 0x6305   ; 64K MISR 1, Word 4
    .word 0x850e   ; 64K MISR 1, Word 5
    .word 0x5069   ; 64K MISR 1, Word 6
    .word 0x0463   ; 64K MISR 1, Word 7

_TI_64K_MISR_2:
    .word 0xa0b0   ; 64K MISR 2, Word 0
    .word 0xb1fa   ; 64K MISR 2, Word 1
    .word 0xa81d   ; 64K MISR 2, Word 2
    .word 0x8935   ; 64K MISR 2, Word 3
    .word 0x7cb0   ; 64K MISR 2, Word 4
    .word 0x17ab   ; 64K MISR 2, Word 5
    .word 0xe484   ; 64K MISR 2, Word 6
    .word 0xa141   ; 64K MISR 2, Word 7

_TI_64K_MISR_3:
    .word 0xd5c7   ; 64K MISR 3, Word 0
    .word 0x8285   ; 64K MISR 3, Word 1
    .word 0x13cc   ; 64K MISR 3, Word 2
    .word 0x1bbe   ; 64K MISR 3, Word 3
    .word 0x2f61   ; 64K MISR 3, Word 4
    .word 0x98c2   ; 64K MISR 3, Word 5
    .word 0x862e   ; 64K MISR 3, Word 6
    .word 0xe0ce   ; 64K MISR 3, Word 7


;---------------The End-------------------

