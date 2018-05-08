/*
// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:53:39 $
//###########################################################################
//
// FILE:    F28M35x_C28_boot_rom_lnk.cmd
//
// TITLE:   boot rom linker command file
//
//
//###########################################################################
// $TI Release: F2837x Boot ROM V1.0 $
// $Release Date: October 2013 $
//###########################################################################
*/
-u _enable_unbonded_pullups_80_pin

MEMORY
{
PAGE 0 :
		 ROM_SIGNATURE			: origin = 0x3F0000, length = 0x000002 //, fill = 0xFFFF
		 PLC_LITE				: origin = 0x3F0002, length = 0x001000 //, fill = 0xFFFF
		 PLC_COM				: origin = 0x3F1002, length = 0x0007A0 //, fill = 0xFFFF

		 RESERVED_01			: origin = 0x3F17A2, length = 0x00005E //, fill = 0xFFFF

         APPBOOT				: origin = 0x3F1800, length = 0x000300 //, fill = 0xFFFF
		 DFU					: origin = 0x3F1B00, length = 0x001600 //, fill = 0xFFFF /*actual length = 0x1300, 0x300 is buffer*/
		 PLC_G3					: origin = 0x3F3100, length = 0x002260 //, fill = 0xFFFF /*taken out the 0x400 size 1024 pt VCU0 twiddle factor*/
		 PLCTABLES				: origin = 0x3F5360, length = 0x000490 /*, fill = 0xFFFF*/
		 RESERVED_02			: origin = 0x3F57F0, length = 0x000010  /*Alignment to 1KW boundary*/

		 PLC_MM_TABLES			: origin = 0x3F5800, length = 0x001902 //, fill = 0xFFFF  /*AES and IQ Cos*/
		 RESERVED_03			: origin = 0x3F7102, length = 0x0000FE /*Alignment to 1KW boundary*/

		 SYSBIOS_ROM			: origin = 0x3F7200, length = 0x002000/*, fill = 0xFFFF*/

		 FPU32_TWIDDLE_TABLE	: origin = 0x3F9200, length = 0x001800

         BOOT       			: origin = 0x3FAA00, length = 0x003FD0 /*, fill = 0xFFFF*/

		 BOOT_PBIST_CHECKSUM	: origin = 0x3FE9D0, length = 0x000042
		 CPU_SPINTAC_DATA_ROM   : origin = 0x3FEA12, length = 0x000010 //, fill = 0xFFFF
		 CPU_FAST_DATA_ROM		: origin = 0x3FEA22, length = 0x000100 //, fill = 0xFFFF

         FLASHAPI_IN_ROM		: origin = 0x3FEB22, length = 0x001400 //, fill = 0xFFFF

		 PIE_MISMATCH_HANDLER	: origin = 0x3FFF22, length = 0x000050 //, fill = 0xFFFF
         CRCTABLE_ROM			: origin = 0x3FFF72, length = 0x000008 //, fill = 0xFFFF
         VERSION    			: origin = 0x3FFF7A, length = 0x000002
         CHECKSUM   			: origin = 0x3FFF7C, length = 0x000042
         VECS       			: origin = 0x3FFFBE, length = 0x000042

		 SYSBIOS_FLASH			: origin = 0x081010, length = 0x0003df


PAGE 1 :
         EBSS       			: origin = 0x002,    length = 0x000010
         BOOTMODE_VAR			: origin = 0x012,	 length = 0x000002
         STACK      			: origin = 0x014,    length = 0x0000E0
         SYSBIOS_RAM			: origin = 0x780, 	 length = 0x000080
}

SECTIONS
{
	GROUP : load = PLCTABLES, 				PAGE = 0,	ALIGN(2)
	{
		 primeTxPreamble
		 primeRxPreamble
		 primePrefTable
	}
	GROUP : load = PLC_MM_TABLES, 				PAGE = 0,	ALIGN(2)
	{
		 PLC_TABLE
		 IQmathTables
	}

	GROUP : load = FPU32_TWIDDLE_TABLE, 				PAGE = 0,	ALIGN(2)
	{
		 .CFFT_f32_twiddleFactors
		 .FFT_f32_twiddleFactors
		 tf512pFFTTable
	}

		 .test_signature1: 		load = ROM_SIGNATURE				PAGE = 0
		 .bootrom_func: 	load = CRCTABLE_ROM,			PAGE = 0
         .InitBoot: 		load = BOOT,     				PAGE = 0
         .text: 			load = BOOT,     				PAGE = 0
         .CKSUMFUNCS: 		load = BOOT,						PAGE = 0,	ALIGN(2)
         .Isr: 				load = BOOT,     				PAGE = 0
         .BootVecs: 		load = VECS,     				PAGE = 0
         .PBIST_CKSUMLOC:   load = BOOT_PBIST_CHECKSUM,  	PAGE = 0,	ALIGN(2)
         .CKSUMLOC: 		load = CHECKSUM,  				PAGE = 0,	ALIGN(2)
         .Version: 			load = VERSION,   				PAGE = 0
         .stack: 			load = STACK,     				PAGE = 1
         .ebss: 			load = EBSS,      				PAGE = 1
		 .econst: 			load = BOOT,						PAGE = 0, 	ALIGN(2)
		 USER_BOOTMODEVAR: 	load = BOOTMODE_VAR,			PAGE = 1

         SYSBIOSROM: 		load = SYSBIOS_ROM,		PAGE = 0
         {
            -l rtos_rom_image.obj(sysbios_1)
            -l rtos_rom_image.obj(sysbios_2)
         }

		CBROM_PIE_MISMATCH_HANDLER:	load = PIE_MISMATCH_HANDLER, PAGE =0
}


