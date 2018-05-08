/*
// TI File $Revision: /main/11 $
// Checkin $Date: March 4, 2008   15:51:17 $
//###########################################################################
//
// FILE:    F2833x_boot_rom_lnk.cmd
//
// TITLE:   F2833x boot rom linker command file
//
//
//###########################################################################
// $TI Release: 2833x/2823x Boot ROM V2 $
// $Release Date: March 4, 2008 $
//###########################################################################
*/


MEMORY
{
PAGE 0 :
         IQTABLES  : origin = 0x3FE000, length = 0x000b50
         IQTABLES2 : origin = 0x3FEB50, length = 0x00008c
         FPUTABLES : origin = 0x3FEBDC, length = 0x0006A0
         TI_PRPG   : origin = 0x3FF27C, length = 0x000090
         TI_MISR   : origin = 0x3FF30C, length = 0x000040
         BOOT      : origin = 0x3FF34C, length = 0x0006AF
         RSVD1     : origin = 0x3FF9FB, length = 0x0005BE
         FLASH_API : origin = 0x3FFFB9, length = 0x000001
         VERSION   : origin = 0x3FFFBA, length = 0x000002
         CHECKSUM  : origin = 0x3FFFBC, length = 0x000004
         VECS      : origin = 0x3FFFC0, length = 0x000040

         ADC_CAL   : origin = 0x380080, length = 0x000009

PAGE 1 :
         EBSS      : origin = 0x002, length = 0x004
         STACK     : origin = 0x006, length = 0x200
}

SECTIONS
{

         IQmathTables : load = IQTABLES,  PAGE = 0
         IQmathTables2: load = IQTABLES2, PAGE = 0
         FPUmathTables: load = FPUTABLES, PAGE = 0
         .InitBoot    : load = BOOT,      PAGE = 0
         .text        : load = BOOT,      PAGE = 0
         .Isr         : load = BOOT,      PAGE = 0
         .Flash       : load = FLASH_API  PAGE = 0
         .BootVecs    : load = VECS,      PAGE = 0
         .Checksum    : load = CHECKSUM,  PAGE = 0
         .Version     : load = VERSION,   PAGE = 0
         .stack       : load = STACK,     PAGE = 1
         .ebss        : load = EBSS,      PAGE = 1
         rsvd1        : load = RSVD1,     PAGE = 0
         ti_prpg_sect : load = TI_PRPG,   PAGE = 0
         ti_misr_sect : load = TI_MISR,   PAGE = 0
         .adc_cal     : load = ADC_CAL,   PAGE = 0, TYPE = NOLOAD
}


