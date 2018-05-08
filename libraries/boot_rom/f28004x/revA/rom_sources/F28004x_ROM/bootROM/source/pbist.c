//###########################################################################
//
// FILE:    pbist.c
//
// TITLE:   pbist code for C-Core
//
// Notes:
//
//###########################################################################
// $TI Release: F28004x Boot ROM V1.0 $
// $Release Date: July 2015 $
//###########################################################################


#include "pbist.h"

//
// Enable Peripherals PCLKCR0-CLA,PCLKCR10-CAN and PCLKCR22-PBIST
//
#define PBIST_ENABLE_ALL_PERIPHERAL_CLOCKS() \
                                { \
                                    HWREG(SYSCTL_PCLKCR0)  = 0x1U; \
		                            HWREG(SYSCTL_PCLKCR10) = 0x3U; \
		                            HWREG(SYSCTL_PCLKCR22) = 0x1U; \
                                  }
//
// Disable Peripherals PCLKCR0-CLA , PCLKCR10-CAN and PCLKCR22-PBIST
//
#define PBIST_DISABLE_PERIPHERAL_CLOCKS() \
                                { \
                                    HWREG(SYSCTL_PCLKCR0)  = 0x0U; \
		                            HWREG(SYSCTL_PCLKCR10) = 0x0U; \
                                    HWREG(SYSCTL_PCLKCR22) = 0x0U; \
		                         }
//
// Soft rest peripherals SOFTPRES0-CLA,SOFTPRES10-CAN,SOFTPRES11,
// 12-DUMMY to provide enough cycles so that Softpres can take effect
//
#define PBIST_SOFT_RESET_PERIPHERALS() \
                                 { \
								    HWREG(SYSCTL_SOFTPRES0)  = 0xF; \
								    HWREG(SYSCTL_SOFTPRES10) = 0xF; \
                                    asm(" RPT #14 || NOP");\
									HWREG(SYSCTL_SOFTPRES0)  = 0x0; \
								    HWREG(SYSCTL_SOFTPRES10) = 0x0; \
                                    asm(" RPT #14 || NOP");\
                                    HWREG(PBIST_PACT) = 0x0;\
									HWREGH(PBIST_PIE12_IFR) = 0x0;\
								}
//
// Initialize RAM. This code is taken from the bootrom.
//
#define PBIST_RAM_INIT() \
                    { \
                        EALLOW; \
                     	asm(" MOVB ACC, #3"); \
                    	asm(" MOVW DP, #0x17d0"); \
                    	asm(" MOVL @0x12, ACC"); \
                    	asm(" MOVB ACC, #0xFF"); \
                    	asm(" MOVL @0x32, ACC"); \
                      	asm(" MOVW DP, #0x17d1"); \
                    	asm(" MOV  ACC, #0xF"); \
                    	asm(" MOVL @0x12, ACC"); \
                    	asm(" MOVB ACC, #6"); \
                    	asm(" MOVL @0x32, ACC"); \
                    	EDIS; \
                        asm(" MOV @T,#2080"); \
                        asm(" RPT @T"); \
                        asm(" ||NOP"); \
                    }

//*****************************************************************************
//
// Test Memory on Power on Reset
//
//*****************************************************************************
uint32_t PBIST_PORMemoryTest(void)
{
    register uint32_t status;
	register uint32_t count;

	DINT;   // Disable Global __interrupt INTM
    DRTM;   // Disable Global realtime __interrupt DBGM
    EALLOW;
	// Enable all peripheral clocks.
    PBIST_ENABLE_ALL_PERIPHERAL_CLOCKS();
	// Disable PBIST interrupt from propagating to the CPU
	HWREGH(PBIST_PIE12_IER) = 0;
    EDIS;
	// Enable PBIST clock
	HWREG(PBIST_PACT) = 0x1U;
    // Write to override register
	HWREG(PBIST_OVERRIDE) = 0x9U;
	// Write to DLRT register
	HWREG(PBIST_DLRT) = 0x10;


    /*-Always fail code.March 13n is run on TMU ROM */
    HWREG(PBIST_RINFOL) =  PBIST_RINFOL_ROM_MEM_GROUP ;
	HWREG(PBIST_RINFOU) = 0x0;
	HWREG(PBIST_ALGO)   = PBIST_ALGO_TMU_ROM_FAIL_ALGO;
   	// Write 0x0 to Override
	HWREG(PBIST_OVERRIDE) = 0x0U;

	// Write 0x14 to DLRT
	HWREG(PBIST_DLRT) = 0x14U;


	// 1500 clock cycles are taken for PBIST to start testing and report the
	// first fail,PBIST to release an interrupt. Count gets decremented every
	// 16 cycles according to following loop structure.A safe value for
    // count would be decimal  of 750.

    count = 750U;
	while (HWREGH(PBIST_PIE12_IFR) != 0x8U)
	{
         if(count-- < 0x1U)
		 {
	         EALLOW;
			 PBIST_SOFT_RESET_PERIPHERALS();
			 PBIST_DISABLE_PERIPHERAL_CLOCKS();
             EDIS;
			// PBIST is taking too long. Return with an error message
			return(PBIST_ALWAYSFAIL_TIMEOUT_ERROR);
		 }
	}
	
	// Either of the bits are set in case of failure
    if((HWREG(PBIST_FAIL_STATUS_0) == 0) && (HWREG(PBIST_FAIL_STATUS_1) == 0))
    {
        // None of the bits are set. PBIST is not properly reporting error
		// condition.
		EALLOW;
		PBIST_SOFT_RESET_PERIPHERALS();
		PBIST_DISABLE_PERIPHERAL_CLOCKS();
        EDIS;
        return(PBIST_ALWAYSFAIL_INCORRECT_OPERATION);
	}
    else
	{
	     /* PBIST operation is correct and is able to detect a failure.
		   configure PBIST for testing memories*/
	    EALLOW;
        HWREGH(PBIST_PIE12_IFR) = 0x0U;
        EDIS;
		HWREG(PBIST_DLRT) = 0x16U;
        HWREG(PBIST_STR) = 0x1U;
        

        // Wait for PBIST to flush out failure data and release control of TMU
        // ROM.9000 cycles are required , count gets decremented every 15
		// cycles.Safe value would be decimal of 4500
 	    count = 4500U;
        while(HWREGH(PBIST_PIE12_IFR) != 0x8U)
	    {
             if(count-- < 0x1U)
	    	 {
	    	      EALLOW;
	    		  PBIST_SOFT_RESET_PERIPHERALS();
				  PBIST_DISABLE_PERIPHERAL_CLOCKS();
	    		  EDIS;
	    		 // PBIST is taking too long. Return with an error message
	    		 return(PBIST_DOUBLEINT_TIMEOUT_ERROR);
	    	 }
        }
        //making PBIST interrupt flag zero to detect next interrupt
        HWREGH(PBIST_PIE12_IFR) = 0x0U;
        HWREG(PBIST_DLRT)      = 0x0U;
        //Restoring PBIST registers to default value
        HWREG(PBIST_OVERRIDE)  = 0x9U;
        HWREG(PBIST_DLRT)      = 0x10U;
        HWREG(PBIST_RINFOL) = 0xFFFFFFFFU;
        HWREG(PBIST_RINFOU) = 0xFFFFFFFFU;
        // Enable all RAM and all ROM but BOOTROM Algorithm groups.
	    HWREG(PBIST_ALGO) = PBIST_ALGO_ALL_ROM_RAM;

		 // Check TMU Capability
        if((HWREG(SYSCTL_DC1) & SYSCTL_DC1_CPU1_FPU_TMU)
	                               != SYSCTL_DC1_CPU1_FPU_TMU)
        {
	    	// Remove TMU ROM from the algorithm group
	    	HWREG(PBIST_ALGO) = HWREG(PBIST_ALGO) & ~PBIST_ALGO_TMU_ROM;
        }
        // Check CLA Capability
	    if((HWREG(SYSCTL_DC1) & SYSCTL_DC1_CPU1_CLA1) != SYSCTL_DC1_CPU1_CLA1)
        {
	    	// Remove CLA ROM from the algorithm group
	    	HWREG(PBIST_ALGO) = HWREG(PBIST_ALGO) &  ~PBIST_ALGO_CLA_ROM;
	    }
	    // Check DCAN Capability
	    if((HWREG(SYSCTL_DC11) & SYSCTL_DC11_CAN_A) != SYSCTL_DC11_CAN_A)
        {
            // Take out March13n- dual port of DCAN A
	    	HWREG(PBIST_ALGO) = HWREG(PBIST_ALGO) &
     			~PBIST_ALGO_MARCH13N_DUAL_PORT_DCANA;
        }
        if((HWREG(SYSCTL_DC11) & SYSCTL_DC11_CAN_B) != SYSCTL_DC11_CAN_B)
        {
            // Take out March13n- dual port of DCAN B
	    	HWREG(PBIST_ALGO) = HWREG(PBIST_ALGO) &
     			~PBIST_ALGO_MARCH13N_DUAL_PORT_DCANB;
        }

	    // Write 0x1 to Override
	    HWREG(PBIST_OVERRIDE) = 0x1U;
	    // Write 0x214 to DLRT GO/NO-GO bit is set to make sure PBIST releases
		// control of memory if genuine failure occurs.
	    HWREG(PBIST_DLRT) = 0x214U;
	    
	    // 140000 clock cycles are required to finish testing all the memories.
	    // Count gets decremented every 15 cycles.
        // Wait for a predetermined amount of count value.Safe count value
		// would be decimal of 70000

	    count = (uint32_t)70000;
		
        while(HWREGH(PBIST_PIE12_IFR) != 0x8U)
	    {
	         if(count-- < 0x1U)
	    	 {
	    	    EALLOW;
	    		PBIST_SOFT_RESET_PERIPHERALS();
				PBIST_DISABLE_PERIPHERAL_CLOCKS();
				EDIS; 
                // Initialize RAM before exiting.
				PBIST_RAM_INIT();
	    		// PBIST is taking too long. Return with an error message
	    		return(PBIST_MEMORYTEST_TIMEOUT_ERROR);
	    	 }
	     }
	     status = PBIST_MEMORY_TEST_PASS;
         // If any bits of FSR0 and/or FSR1 registers are set we issue error
	     if((HWREG(PBIST_FAIL_STATUS_0) == 1U) ||
	        (HWREG(PBIST_FAIL_STATUS_1) == 1U))
	     {
	         // Some bits are set. We have error condition.
	    	 status = PBIST_MEMORY_FAIL_ERROR;
	     }

		 EALLOW;
	     // First Soft reset certain CLA,CAN then disable all peripheral
		 // clocks except PBIST
	     PBIST_SOFT_RESET_PERIPHERALS();
	     PBIST_DISABLE_PERIPHERAL_CLOCKS();
		 EDIS;
		 // Initialize RAM before exiting.
		 PBIST_RAM_INIT();
    }

	return(status);
}

//===========================================================================
// No more.
//===========================================================================
