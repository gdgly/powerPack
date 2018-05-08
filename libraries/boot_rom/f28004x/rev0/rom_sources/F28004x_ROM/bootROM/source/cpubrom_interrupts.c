//###########################################################################
//
// FILE:    ccore_bootrom_interrupts.c    
//
// TITLE:   B.C28x Boot ROM interrupt handlers
//
// Functions:
//
// Notes:
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July 2015 $
//###########################################################################

#include "bootrom.h"

void load_itrap_address (uint32_t *itrapaddress);

interrupt void cbrom_itrap_isr(void);
interrupt void cbrom_handle_nmi();
void cbrom_pie_vect_mismatch_handler();

extern uint32_t	cbrom_status;

volatile uint16_t cbrom_nmi_status;
uint32_t	iTrap_addr;

#pragma CODE_SECTION(cbrom_pie_vect_mismatch_handler, "CBROM_PIE_MISMATCH_HANDLER")
/*
 * Function to handle PIE vector mismatch handler in C-BootROM
 */
interrupt void cbrom_pie_vect_mismatch_handler()
{
	
	uint32_t EntryAddr = 0xFFFFFFFF;


    cbrom_status |= BOOTROM_GOT_A_PIEMISMATCH;

    EALLOW;

    EntryAddr = HWREG(CPUSYS_BASE + SYSCTL_O_PIEVERRADDR);
    EDIS;

    if((EntryAddr != (uint32_t)0x003FFFFF))
    {
        ((void (*)(void))EntryAddr)();
    }
    else
    {
        //let watchdog reset the system, if the error happened
        //not because of NMI fetch, else NMIWD will reset the device
        if(HWREGH(NMI_BASE + NMI_O_FLG) == 0x0)
        {
        	SysCtl_enableWatchdog();
        }

        while(1);

    }

}

/*
 * Function to handle NMI interrupts in C-BootROM
 */
interrupt void cbrom_handle_nmi()
{
    uint32_t EntryAddr;

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_10;

    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*do a dummy branch to OTP - if we later decide not to handler this the way done below*/
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }
	/*check if NMI is triggered*/
	cbrom_nmi_status = HWREGH(NMI_BASE + NMI_O_FLG); //NmiIntruptRegs.NMIFLG.all;
	do
	{
		if(cbrom_nmi_status & NMI_FLG_CLOCKFAIL) /*check for CLOCKFAIL_NMI*/
		{
			cbrom_status |= BOOTROM_GOT_A_MCLK_NMI;
			cbrom_nmi_status &= ~(NMI_FLG_CLOCKFAIL);	/*clear bit 1*/

			EALLOW;
			//NmiIntruptRegs.NMIFLGCLR.bit.CLOCKFAIL= 1;
			HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_CLOCKFAIL;
			EDIS;

			//cbrom_nmi_status = NmiIntruptRegs.NMIFLG.all;
			cbrom_nmi_status = HWREGH(NMI_BASE + NMI_O_FLG);

			/*continue to run*/
			if((cbrom_nmi_status) == NMI_FLG_NMIINT)
			{
				cbrom_nmi_status &= ~(NMI_FLG_NMIINT);	/*clear bit 0*/
				/* clear the NMIINT flag and return because there is no other NMI set*/
				EALLOW;
				//NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
				HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;
				EDIS;
				
				return;
			}
		}
        if(cbrom_nmi_status & NMI_FLG_RLNMI) /*check for PIEVECT NMI */
        {
            cbrom_status |= BOOTROM_GOT_A_RL_NMI;

            cbrom_nmi_status &= ~(NMI_FLG_RLNMI);  /*clear bit 6*/
            EALLOW;
            //NmiIntruptRegs.NMIFLGCLR.bit.RLNMI = 1;
            HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_RLNMI;
            EDIS;
        }

        //there is a reason to check these two at the end
        //d owe really need to reset the device - can't it continue to boot?
        if(cbrom_nmi_status & NMI_FLG_RAMUNCERR) /*check for C28RAMUNCERR NMI */
		{
			cbrom_status |= BOOTROM_GOT_A_RAM_UNCERR_NMI;

			//if debugger connected - give a chance to user to know the scenario
			asm("   ESTOP0");

            EALLOW;
         	asm(" MOVB ACC, #3");
        	asm(" MOVW DP, #0x17d0");
        	asm(" MOVL @0x12, ACC");
        	asm(" MOVB ACC, #0xFF");
        	asm(" MOVL @0x32, ACC");
          	asm(" MOVW DP, #0x17d1");
        	asm(" MOV  ACC, #0xF");
        	asm(" MOVL @0x12, ACC");
        	asm(" MOVB ACC, #6");
        	asm(" MOVL @0x32, ACC");
        	EDIS;
            asm(" MOV @T,#2080");
    		asm(" RPT	@T \
    			  || NOP ");

			//let NMIWD reset the device
			while(1);

//			cbrom_nmi_status &= ~(0x04);	/*clear bit 2*/
//			EALLOW;
//			NmiIntruptRegs.NMIFLGCLR.bit.C28RAMUNCERR = 1;
//			EDIS;
		}
		if(cbrom_nmi_status & NMI_FLG_FLUNCERR) /*check for C28FLUNCERR NMI */
		{
			cbrom_status |= BOOTROM_GOT_A_FLASH_UNCERR_NMI;

			//if debugger connected - give a chance to user to know the scenario
			asm("   ESTOP0");

            //let NMIWD reset the device
            while(1);

//			cbrom_nmi_status &= ~(0x08);	/*clear bit 3*/
//			EALLOW;
//			NmiIntruptRegs.NMIFLGCLR.bit.C28FLUNCERR = 1;
//			EDIS;
		}

		cbrom_nmi_status &= ~(0x01);	/*clear bit 0*/
		EALLOW;
		//NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
		HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;
		EDIS;

		//cbrom_nmi_status = NmiIntruptRegs.NMIFLG.all;
		cbrom_nmi_status = HWREGH(NMI_BASE + NMI_O_FLG);

	}while(cbrom_nmi_status & 0x01);	/*check for NMIINT bit - bit 0*/

//	while(1);
}
/*
 * Function called whenever an illegal interrupt occurs on B.C28X CPU
 */
interrupt void cbrom_itrap_isr(void)
{

	/*set boot status to indicate that C28X CPU is in iTRAP ISR, only a reset can pull it out of this*/
	cbrom_status |= BOOTROM_IN_AN_ITRAP;

	/*accessing the glob var locally -sets DP pointer for the below inline ASMs*/
	iTrap_addr = 0xFFFFFFFF;

	/*get the iTrap address (return address from interrupt) stored in stack
	 * This particular return address stored in stack will change according to 
	 * compiler optimizations, 
	 */
	load_itrap_address (&iTrap_addr);

	/*return address from interrupt will be PC location where illegal instruction is executed + 1*/
	iTrap_addr -= 1;

	SysCtl_enableWatchdog();

	//if debugger connected - give a chance to user to know the scenario
    asm("   ESTOP0");
	while(1);
}

//===========================================================================
// End of file.
//===========================================================================


