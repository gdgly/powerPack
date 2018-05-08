/*
// TI File $Revision: /main/3 $
// Checkin $Date: March 3, 2011   13:45:53 $
//###########################################################################
//
// FILE:    F28069.cmd
//
// TITLE:   Linker Command File For F28069 Device
//
//###########################################################################
// $TI Release: $ 
// $Release Date: $ 
//###########################################################################
*/

MEMORY
{
PAGE 0 :   /* Program Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE1 for data allocation */
   RAML0       : origin = 0x008000, length = 0x000800     /* on-chip RAM block L0 */
   RAML1       : origin = 0x008800, length = 0x000400     /* on-chip RAM block L1 */
   OTP         : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */

/*   FLASHH      : origin = 0x3D8000, length = 0x004000     /* on-chip FLASH */
   FLASHHG     : origin = 0x3D8000, length = 0x008000     /* on-chip FLASH */
/*   FLASHG      : origin = 0x3DC000, length = 0x004000     /* on-chip FLASH */
   FLASHF      : origin = 0x3E0000, length = 0x004000     /* on-chip FLASH */
   FLASHE      : origin = 0x3E4000, length = 0x004000     /* on-chip FLASH */   
   FLASHD      : origin = 0x3E8000, length = 0x004000     /* on-chip FLASH */
   FLASHC      : origin = 0x3EC000, length = 0x004000     /* on-chip FLASH */
   FLASHA      : origin = 0x3F4000, length = 0x003F80     /* on-chip FLASH */
   CSM_RSVD    : origin = 0x3F7F80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   BEGIN       : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
   CSM_PWL_P0  : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */

   FPUTABLES   : origin = 0x3FD860, length = 0x0006A0	  /* FPU Tables in Boot ROM */
   IQTABLES    : origin = 0x3FDF00, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2   : origin = 0x3FEA50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
   IQTABLES3   : origin = 0x3FEADC, length = 0x0000AA	  /* IQ Math Tables in Boot ROM */

   ROM         : origin = 0x3FF3B0, length = 0x000C10     /* Boot ROM */
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */

PAGE 1 :   /* Data Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE0 for program allocation */
           /* Registers remain on PAGE1                                                  */

   BOOT_RSVD   : origin = 0x000000, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */
   RAMM0       : origin = 0x000050, length = 0x0003B0     /* on-chip RAM block M0 */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAML2       : origin = 0x008C00, length = 0x000400     /* on-chip RAM block L2 */
   RAML3       : origin = 0x009000, length = 0x001000	  /* on-chip RAM block L3 */
   RAML4       : origin = 0x00A000, length = 0x002000     /* on-chip RAM block L4 */
   RAML5_8     : origin = 0x00C000, length = 0x008000     /* on-chip RAM block L5 */
/*   RAML6       : origin = 0x00E000, length = 0x002000     /* on-chip RAM block L6 */
/*   RAML7       : origin = 0x010000, length = 0x002000     /* on-chip RAM block L7 */
/*   RAML8       : origin = 0x012000, length = 0x002000     /* on-chip RAM block L8 */
   USB_RAM     : origin = 0x040000, length = 0x000800     /* USB RAM		  */   
   FLASHB      : origin = 0x3F0000, length = 0x004000     /* on-chip FLASH */     
}

/* Allocate sections to memory blocks.
   Note:
         codestart user defined section in DSP28_CodeStartBranch.asm used to redirect code
                   execution when booting to flash
         ramfuncs  user defined section to store functions that will be copied from Flash into RAM
*/


SECTIONS
{

   /* Allocate program areas: */
   .cinit              : > FLASHA,     PAGE = 0
   .pinit              : > FLASHA,     PAGE = 0
   .text               : > FLASHHG,     PAGE = 0
   codestart           : > BEGIN,      PAGE = 0
   ramfuncs            : LOAD = FLASHD,
                         RUN = RAML0,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         PAGE = 0
   csmpasswds          : > CSM_PWL_P0, PAGE = 0
   csm_rsvd            : > CSM_RSVD,   PAGE = 0
   /* Allocate uninitalized data sections: */
/*   .stack              : > RAMM0,      PAGE = 1  */
   .stack              : > RAML3,      PAGE = 1
   .ebss               : > RAML4,      PAGE = 1
   .esysmem            : > RAML5_8,      PAGE = 1

   /* Initalized sections to go in Flash */
   /* For SDFlash to program these, they must be allocated to page 0 */
   .econst             : > FLASHA,     PAGE = 0
   .switch             : > FLASHA,     PAGE = 0

   /* Allocate IQ math areas: */
   IQmath              : > FLASHA,     PAGE = 0            /* Math Code */
   IQmathTables        : > IQTABLES,   PAGE = 0, TYPE = NOLOAD
   
   /* Allocate FPU math areas: */
   FPUmathTables       : > FPUTABLES,  PAGE = 0, TYPE = NOLOAD
   
/*   DMARAML5	           : > RAML5,      PAGE = 1			*/
/*   DMARAML6	           : > RAML6,      PAGE = 1			*/
/*   DMARAML7	           : > RAML7,      PAGE = 1			*/
/*   DMARAML8	           : > RAML8,      PAGE = 1			*/
   .reset              : > RESET,      PAGE = 0, TYPE = DSECT
   vectors             : > VECTORS,    PAGE = 0, TYPE = DSECT

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

