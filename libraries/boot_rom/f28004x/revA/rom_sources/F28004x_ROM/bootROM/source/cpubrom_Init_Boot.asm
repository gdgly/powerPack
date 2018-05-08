;;###########################################################################
;;
;; FILE:    c1brom_Init_Boot.asm
;;
;; TITLE:   Boot Rom Initialization and Exit routines.
;;
;; Functions:
;;
;;     _InitBoot
;;     _ExitBoot
;;
;; Notes:
;;
;;###########################################################################
;; $TI Release: F28004x Boot ROM V1.0 $
;; $Release Date: July 2015 $
;;###########################################################################

    .global _InitBoot
    .global _ExitBoot
    .global _ExitPBISTLoc
    .def	_ExitBoot
    .def 	_ExitPBISTLoc
    .ref _cbrom_system_init
	.ref _cbrom_handle_fuse_err_if_any
    .ref _cbrom_configure_device_for_fast_boot
    .ref _cbrom_device_config

;    .ref _deviceCal


 	
 	.sect ".test_signature1"
 	.long   0xFFFFFF81			;;~(*(0x3FFFFE)) - used for production testing

    .sect ".Version"
    .global	_c1brom_version
c1brom_version:
    .word 0x0100     ; Boot ROM Version v1.0
    .word 0x0715     ; Month/Year: (ex: 0x0109 = 1/09 = Jan 2009)

;	.sect ".otp_entry_points"
;	.global	_otp_func_refs
;_otp_func_refs:
;	.ref 	_ccore_brom_otp_dummy_branch_begin_boot
;	.long 	_ccore_brom_otp_dummy_branch_begin_boot
;	.ref 	_ccore_brom_otp_dummy_branch_end_boot
;	.long 	_ccore_brom_otp_dummy_branch_end_boot
;	.ref 	_ccore_brom_otp_pie_vector_mismatch_handler
;	.long 	_ccore_brom_otp_pie_vector_mismatch_handler
;	.ref 	_ccore_brom_otp_unsupported_bmode_handler
;	.long 	_ccore_brom_otp_unsupported_bmode_handler
;	.ref 	_ccore_brom_otp_hw_bist_reset_handler
;	.long 	_ccore_brom_otp_hw_bist_reset_handler
;	.ref 	_I2C_gpio_init_for_boot
;	.long 	_I2C_gpio_init_for_boot
;	.ref 	_SCI_gpio_init_for_boot
;	.long 	_SCI_gpio_init_for_boot
;	.ref 	_SPI_gpio_init_for_boot
;	.long 	_SPI_gpio_init_for_boot
;	.ref	_SPI_alt_gpio_init_for_boot
;	.long	_SPI_alt_gpio_init_for_boot

    .sect ".InitBoot"

;-----------------------------------------------
; _InitBoot
;-----------------------------------------------
;-----------------------------------------------
; This function performs the initial boot routine
; for the boot ROM.
;
; This module performs the following actions:
;
;     1) Initalizes the stack pointer
;     2) Sets the device for C28x operating mode
;     3) Calls the main boot functions
;     4) Calls an exit routine
;-----------------------------------------------
_InitBoot:

; Initalize the stack pointer.

__stack:    .usect ".stack",0

    MOV SP, #__stack ; Initalize the stack pointer

; Initalize the device for running in C28x mode.

    C28OBJ       ; Select C28x object mode
    C28ADDR      ; Select C27x/C28x addressing
    C28MAP       ; Set blocks M0/M1 for C28x mode
    CLRC PAGE0   ; Always use stack addressing mode
    MOVW DP,#0   ; Initialize DP to point to the low 64 K
    CLRC OVM

; Set PM shift of 0
    SPM 0
; need to check for FUSEERR because we cannot trust the design if there is an error
; Hanlde any efuse errors
	MOVW         DP, #0x1741
	MOVL         ACC, @0x34
	SBF          cbrom_fuseerr_nope, EQ
	MOVB         ACC, #21
	CMPL         ACC, @0x34
	SBF          cbrom_fuseerr_reset, NEQ
	SB           cbrom_fuseerr_nope, UNC
cbrom_fuseerr_reset:
	EALLOW
; WdRegs.WDCR.all = 0x028;
	MOVW         DP, #0x1c0
	MOVB         @0x29, #0x28, UNC
; EDIS;
	EDIS
	ESTOP0			; to let execution stop here when debugger is connected
; while(1);
	SB           0, UNC
cbrom_fuseerr_nope:
; disable WDOG, else we need to keep it feeding
cbrom_disable_wdog:
	EALLOW
;   WdRegs.WDCR.all = 0x028; - to enable WDOG
;  	WdRegs.WDCR.all = 0x068; - to disable WDOG
	MOVW         DP, #0x1c0
	MOVB         @0x29, #0x68, UNC
; 39     	EDIS;//get the WDOG enable code in assembly
	EDIS
; initialize 32 locations so M0 RAM can be used for stack
	MOV          AL, #0x20
	MOV			 AH, #0
ram_zero_loop_0:
	MOV          *SP++,#0		;;zero stack
	SUBB		 ACC, #1
	BF			 ram_zero_loop_0,GEQ
    MOV SP, #__stack ; re-Initalize the stack pointer
;
; configure flash to keep it stay in active mode after power up
; this has to be done for every reset
; no stack access is allowed to check during AVV
; enable PLL as well while flash powers up for XRSn and POR resets
	LCR _cbrom_configure_device_for_fast_boot

; check reset cause here if not POR or XRSn then skip
; device config and RAM-inits below and go to clean up ROM stack
	MOVW         DP, #0x174e ; DP is 64 in length
	MOVL         ACC, @0x0
	MOVB         AH, #0x0
	ANDB         AL, #0x3
	TEST         ACC
	SBF          stack_init, EQ

; OTP device Config
	LCR _cbrom_device_config

;119     {
cbrom_handle_ram_inits:
;            HWREG(MEMCFG_BASE + MEMCFG_O_DXINIT)   |= MEMCFG_SECT_DX_ALL;
;            HWREG(MEMCFG_BASE + MEMCFG_O_LSXINIT)  |= MEMCFG_SECT_LSX_ALL;
;            HWREG(MEMCFG_BASE + MEMCFG_O_GSXINIT)  |= MEMCFG_SECT_GSX_ALL;
;            HWREG(MEMCFG_BASE + MEMCFG_O_MSGXINIT) |= MEMCFG_SECT_MSGX_ALL;

;124         if(CpuSysRegs.RESC.all & (SYSCTL_RESC_POR))
	MOVW         DP, #0x174e
	MOVL         ACC, @0x0
	MOVB         AH, #0x0; check reset cause
	ANDB         AL, #0x1  ; if not POR thenskip
	TEST         ACC
	SBF          stack_init, EQ
;127             EALLOW;
	EALLOW
;129             MemCfgRegs.DxINIT.all = 0x0003;// bit0-M0, 1-M1
	MOVB         ACC, #3
	MOVW         DP, #0x17d0
	MOVL         @0x12, ACC
;130             MemCfgRegs.LSxINIT.all = 0x00FF;    //LS0 - LS7
	MOVB         ACC, #0xFF
	MOVL         @0x32, ACC
;    *(int *)0x5F452 =0xFFFF;      /* RAM INIT FOR GS0..GS3 Memory    */
	MOVW         DP, #0x17d1
	MOV          ACC, #0xF
	MOVL         @0x12, ACC

;163                 MemCfgRegs.MSGxINIT.all = 0x0006;
	MOVB         ACC, #6
	MOVL         @0x32, ACC
;133             EDIS;
	EDIS
ram_init_wait1:						;; wait 2048 + 32(=buffer)cycles for RAM init to complete
    MOV     @T,#2080
    RPT      @T
    ||NOP
;137         }
	SB           c1brom_handle_ram_inits_done, UNC

stack_init:							;; here means this is not POR, so just zero out the stack, 128 words
	EALLOW
;   WdRegs.WDCR.all = 0x028; - to enable WDOG
;  	WdRegs.WDCR.all = 0x068; - to disable WDOG
	MOVW         DP, #0x1c0
	MOVB         @0x29, #0x68, UNC
; 39     	EDIS;
	EDIS

	MOV          AL, #0xE0
	MOV			 AH, #0
ram_zero_loop:
	MOV          *SP++,#0		;;zero stack
	SUBB		 ACC, #1
	BF			 ram_zero_loop,GEQ
stack_init_done:
    MOV SP, #__stack ; re-Initalize the stack pointer

c1brom_handle_ram_inits_done: ; C$L9:
; Start C-bootROM
    MOVW DP,#0   ; Initialize DP to point to the low 64 K
    CLRC OVM

; Set PM shift of 0

    SPM 0

	LCR	_cbrom_system_init

; Cleanup and exit.  At this point the EntryAddr
; is located in the ACC register
_ExitPBISTLoc:
    BF  _ExitBoot,UNC

;-----------------------------------------------
; _ExitBoot
;-----------------------------------------------
;-----------------------------------------------
;This module cleans up after the boot loader
;
; 1) Make sure the stack is deallocated.
;    SP = 0x400 after exiting the boot
;    loader
; 2) Push 0 onto the stack so RPC will be
;    0 after using LRETR to jump to the
;    entry point
; 2) Load RPC with the entry point
; 3) Clear all XARn registers
; 4) Clear ACC, P and XT registers
; 5) LRETR - this will also clear the RPC
;    register since 0 was on the stack
;-----------------------------------------------

_ExitBoot:

;-----------------------------------------------
;   Insure that the stack is deallocated
;-----------------------------------------------

    MOV SP,#__stack

;-----------------------------------------------
; Clear the bottom of the stack.  This will endup
; in RPC when we are finished
;-----------------------------------------------

    MOV  *SP++,#0
    MOV  *SP++,#0

;-----------------------------------------------
; Load RPC with the entry point as determined
; by the boot mode.  This address will be returned
; in the ACC register.
;-----------------------------------------------

    PUSH ACC
    POP  RPC

;-----------------------------------------------
; Put registers back in their reset state.
;
; Clear all the XARn, ACC, XT, and P and DP
; registers
;
; NOTE: Leave the device in C28x operating mode
;       (OBJMODE = 1, AMODE = 0)
;-----------------------------------------------
    ZAPA
    MOVL  XT,ACC
    MOVZ  AR0,AL
    MOVZ  AR1,AL
    MOVZ  AR2,AL
    MOVZ  AR3,AL
    MOVZ  AR4,AL
    MOVZ  AR5,AL
    MOVZ  AR6,AL
    MOVZ  AR7,AL
    MOVW  DP, #0

;------------------------------------------------
;   Restore ST0 and ST1.  Note OBJMODE is
;   the only bit not restored to its reset state.
;   OBJMODE is left set for C28x object operating
;   mode.
;
;  ST0 = 0x0000     ST1 = 0x0A0B
;  15:10 OVC = 0    15:13      ARP = 0
;   9: 7  PM = 0       12       XF = 0
;      6   V = 0       11  M0M1MAP = 1
;      5   N = 0       10  reserved
;      4   Z = 0        9  OBJMODE = 1
;      3   C = 0        8    AMODE = 0
;      2  TC = 0        7 IDLESTAT = 0
;      1 OVM = 0        6   EALLOW = 0
;      0 SXM = 0        5     LOOP = 0
;                       4      SPA = 0
;                       3     VMAP = 1
;                       2    PAGE0 = 0
;                       1     DBGM = 1
;                       0     INTM = 1
;-----------------------------------------------

    MOV  *SP++,#0
    MOV  *SP++,#0x0A0B
    POP  ST1
    POP  ST0

;------------------------------------------------
;   Jump to the EntryAddr as defined by the
;   boot mode selected and continue execution
;-----------------------------------------------

    LRETR

;eof ----------
