//#############################################################################
//
// FILE:    f28004x_pmbus_stack_lnk.cmd.cmd
//
// TITLE:   Linker Command File for PMBUS library examples that run 
//          on the 28004x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          28004x
//
// Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
// $TI Release: C28x PMBus Communications Stack Library v1.00.00.00 $
// $Release Date: May 22, 2017 $
//#############################################################################
// NOTES:
// 1. In addition to this memory linker command file, add the header linker 
//    command file directly to the project. The header linker command file is 
//    required to link the peripheral structures to the proper locations within
//    the memory map.
//    
//    The header linker files are found in 
//    controlSUITE\device_support\F28004x(D/S)\<version>\F28004x_headers\cmd
//    
//    For BIOS applications add:      F28004x(D/S)_Headers_BIOS_cpuX.cmd
//    For nonBIOS applications add:   F28004x(D/S)_Headers_nonBIOS_cpuX.cmd
//
// 2. Memory blocks on F28004x are uniform (ie same physical memory) in both 
//    PAGE 0 and PAGE 1. That is, the same memory region should not be defined 
//    for both PAGE 0 and PAGE 1. Doing so will result in corruption of program
//    and/or data.
//    
//    Contiguous SARAM memory blocks can be combined if required to create a 
//    larger memory block.
//
//#############################################################################

#if (!defined(_PMBUS_MASTER) && !defined(_PMBUS_SLAVE))
#error Requires either _PMBUS_MASTER or _PMBUS_SLAVE to be defined, do this \
from the project properties, C2000 Linker -> Advanced Options -> \
Command File Preprocessing -> --define. Dont forget to also define the \
variable in the predefined symbols under the compiler setting.
#endif //(!defined(_MASTER) || !defined(_SLAVE))

#if (!defined(_RAM) && !defined(_FLASH))
#error Requires either _RAM or _FLASH to be defined, do this \
from the project properties, C2000 Linker -> Advanced Options -> \
Command File Preprocessing -> --define. Dont forget to also define the \
variable in the predefined symbols under the compiler setting.
#endif //(!defined(_RAM) || !defined(_FLASH))

MEMORY
{
PAGE 0 :
   // BEGIN is used for the "boot to SARAM" bootloader mode
#if defined(_RAM)
   BEGIN           : origin = 0x000000, length = 0x000002
#elif defined(_FLASH)
   BEGIN           : origin = 0x080000, length = 0x000002
#endif 
   RAMM0           : origin = 0x000122, length = 0x0002DE
   RAMM1           : origin = 0x000400, length = 0x000400
   
   RAMLS0          : origin = 0x008000, length = 0x000800
   RAMLS1          : origin = 0x008800, length = 0x000800
   RAMLS2          : origin = 0x009000, length = 0x000800
   RAMLS3          : origin = 0x009800, length = 0x000800
   
   RAMGS0          : origin = 0x00C000, length = 0x002000
   RAMGS1          : origin = 0x00E000, length = 0x002000
   RAMGS2          : origin = 0x010000, length = 0x002000
   RAMGS3          : origin = 0x012000, length = 0x002000
   
   RESET           : origin = 0x3FFFC0, length = 0x000002
   
   FLASHA          : origin = 0x080002, length = 0x001FFE // on-chip Flash
   FLASHC          : origin = 0x084000, length = 0x002000 // on-chip Flash
   FLASHD          : origin = 0x086000, length = 0x002000 // on-chip Flash
   FLASHE          : origin = 0x088000, length = 0x008000 // on-chip Flash
   FLASHF          : origin = 0x090000, length = 0x008000 // on-chip Flash
   FLASHG          : origin = 0x098000, length = 0x008000 // on-chip Flash

   // location of PMBUS registers
   PMBUS           : origin = 0x006400, length = 0x000020 

PAGE 1 :
   // Part of M0, BOOT rom will use this for stack 
   BOOT_RSVD       : origin = 0x000002, length = 0x000120   

   RAMLS4          : origin = 0x00A000, length = 0x000800
   RAMLS5          : origin = 0x00A800, length = 0x000800
   RAMLS6          : origin = 0x00B000, length = 0x000800
   RAMLS7          : origin = 0x00B800, length = 0x000800
   

   FLASHB          : origin = 0x082000, length = 0x002000 // on-chip Flash
}
 
SECTIONS
{
   codestart       : > BEGIN,     PAGE = 0
#if defined(_RAM)
   .TI.ramfunc     : > RAMM0,     PAGE = 0
   .text           :>> RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3,
                                  PAGE = 0
   .cinit          : > RAMGS0,    PAGE = 0
   
   .pinit          : > RAMGS0,    PAGE = 0
   .switch         : > RAMGS0,    PAGE = 0
   .econst         : > RAMLS4,    PAGE = 1
#elif defined(_FLASH)
   .TI.ramfunc     :  LOAD = FLASHC,
                      RUN = RAMLS1,
                      RUN_START(_RamfuncsRunStart),
                      LOAD_START(_RamfuncsLoadStart),
                      LOAD_SIZE(_RamfuncsLoadSize),
                      PAGE = 0
                      {
                      --library=driverlib.lib<flash.obj> (.text)
                      }

   .text           : > FLASHA,    PAGE = 0
   .cinit          : > FLASHC,    PAGE = 0

   .pinit          : > FLASHC,    PAGE = 0
   .switch         : > FLASHC,    PAGE = 0
   .econst         : > FLASHB,    PAGE = 1
#endif //defined(_RAM)
   PMBUSRegsFile    : > PMBUS,     PAGE = 0 // Easy Debugging
   
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT // not used

   .cio             : > RAMLS4,    PAGE = 1
   .sysmem          : > RAMLS4,    PAGE = 1

   .stack           : > RAMLS4,    PAGE = 1
   .ebss            : > RAMLS5,    PAGE = 1
   .esysmem         : > RAMLS4,    PAGE = 1
}
//
//===========================================================================
// End of file.
//===========================================================================
//
