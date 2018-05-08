//###########################################################################
//
// FILE:   pbist.h
//
// TITLE:  
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright: $
//###########################################################################

#include <stdint.h>

#ifndef EALLOW
#define EALLOW __asm(" EALLOW")
#endif
#ifndef DINT
#define DINT   __asm(" setc INTM")
#endif
#ifndef DRTM
#define DRTM   __asm(" setc DBGM")
#endif
#ifndef EDIS
#define EDIS   __asm(" EDIS")
#endif

#ifndef HWREG
#define HWREG(x)      (*((volatile uint32_t *)(x))) 
#endif
#ifndef HWREGH
#define HWREGH(x)     (*((volatile uint16_t *)(x)))
#endif

//*****************************************************************************
//
// Registers and their bits descriptions
//
//*****************************************************************************

//
// PBIST register addresses
//
#define PBIST_DLRT              0x5E364 // PBIST Data Logger Register
#define PBIST_STR               0x5E36C // Resume testing
#define PBIST_PACT              0x5E380 // PBIST Activate Register
#define PBIST_OVERRIDE          0x5E388 // PBIST Override Register
#define PBIST_FAIL_STATUS_0     0x5E390 // Fail Status - Port 0
#define PBIST_FAIL_STATUS_1     0x5E394 // Fail Status - Port 1
#define PBIST_ALGO              0x5E3C4 // PBIST Algorithm Register
#define PBIST_RINFOL            0x5E3C8 // RAM Info Mask Register Lower
#define PBIST_RINFOU            0x5E3CC // RAM Info Mask Register Higher

//
// System Device Capability register addresses
//
#define SYSCTL_DC1       (0x0005D000U + 0x12U)  // FPU, TMU, VCU, CLA
#define SYSCTL_DC11      (0x0005D000U + 0x26U)  // CAN A and CAN B features
#define SYSCTL_DC18      (0x0005D000U + 0x34U)  // LS0 - LS7
#define SYSCTL_DC20      (0x0005D000U + 0x38U)  // GS0 - GS3

//
// Peripheral Clock gating register addresses
//
#define SYSCTL_PCLKCR0   (0x0005D300U + 0x22U)
#define SYSCTL_PCLKCR1   (0x0005D300U + 0x24U)
#define SYSCTL_PCLKCR2   (0x0005D300U + 0x26U)
#define SYSCTL_PCLKCR3   (0x0005D300U + 0x28U)
#define SYSCTL_PCLKCR4   (0x0005D300U + 0x2AU)
#define SYSCTL_PCLKCR5   (0x0005D300U + 0x2CU)
#define SYSCTL_PCLKCR6   (0x0005D300U + 0x2EU)
#define SYSCTL_PCLKCR7   (0x0005D300U + 0x30U)
#define SYSCTL_PCLKCR8   (0x0005D300U + 0x32U)
#define SYSCTL_PCLKCR9   (0x0005D300U + 0x34U)
#define SYSCTL_PCLKCR10  (0x0005D300U + 0x36U)
#define SYSCTL_PCLKCR11  (0x0005D300U + 0x38U)
#define SYSCTL_PCLKCR12  (0x0005D300U + 0x3AU)
#define SYSCTL_PCLKCR13  (0x0005D300U + 0x3CU)
#define SYSCTL_PCLKCR14  (0x0005D300U + 0x3EU)
#define SYSCTL_PCLKCR15  (0x0005D300U + 0x40U)
#define SYSCTL_PCLKCR16  (0x0005D300U + 0x42U)
#define SYSCTL_PCLKCR17  (0x0005D300U + 0x44U)
#define SYSCTL_PCLKCR18  (0x0005D300U + 0x46U)
#define SYSCTL_PCLKCR19  (0x0005D300U + 0x48U)
#define SYSCTL_PCLKCR20  (0x0005D300U + 0x4AU)
#define SYSCTL_PCLKCR21  (0x0005D300U + 0x4CU)
#define SYSCTL_PCLKCR22  (0x0005D300U + 0x4EU)

//
// Peripheral soft reset register addresses
//
#define SYSCTL_SOFTPRES0        (0x0005D000U + 0x82U)                                     
#define SYSCTL_SOFTPRES1        (0x0005D000U + 0x84U)
#define SYSCTL_SOFTPRES2        (0x0005D000U + 0x86U)                                     
#define SYSCTL_SOFTPRES3        (0x0005D000U + 0x88U)                                     
#define SYSCTL_SOFTPRES4        (0x0005D000U + 0x8AU)                                     
#define SYSCTL_SOFTPRES5        (0x0005D000U + 0x8CU)                                     
#define SYSCTL_SOFTPRES6        (0x0005D000U + 0x8EU)                                     
#define SYSCTL_SOFTPRES7        (0x0005D000U + 0x90U)                                     
#define SYSCTL_SOFTPRES8        (0x0005D000U + 0x92U)                                     
#define SYSCTL_SOFTPRES9        (0x0005D000U + 0x94U)                                     
#define SYSCTL_SOFTPRES10       (0x0005D000U + 0x96U)                                     
#define SYSCTL_SOFTPRES11       (0x0005D000U + 0x98U)
#define SYSCTL_SOFTPRES12       (0x0005D000U + 0x9AU)
#define SYSCTL_SOFTPRES13       (0x0005D000U + 0x9CU)                                     
#define SYSCTL_SOFTPRES14       (0x0005D000U + 0x9EU)                                     
#define SYSCTL_SOFTPRES15       (0x0005D000U + 0xA0U)                                     
#define SYSCTL_SOFTPRES16       (0x0005D000U + 0xA2U)                                     
#define SYSCTL_SOFTPRES17       (0x0005D000U + 0xA4U)                                     
#define SYSCTL_SOFTPRES18       (0x0005D000U + 0xA6U)                                     
#define SYSCTL_SOFTPRES19       (0x0005D000U + 0xA8U)                                     
#define SYSCTL_SOFTPRES20       (0x0005D000U + 0xAAU)                                     
#define SYSCTL_SOFTPRES21       (0x0005D000U + 0xACU)

//
// PBIST pie interrupt register
//
#define PBIST_PIE12_IER         (0x0CE0U + 0x18U)
#define PBIST_PIE12_IFR         (0x0CE0U + 0x19U)

//
// RAM init start and check registers 
//
#define RAM_INIT_START          0x0005F412U                                 
#define RAM_INIT_CHECK          0x0005F414U
//
// ALGO register bits description
//
#define PBIST_ALGO_TRIPLE_READ_PBIST_ROM         ((uint32_t)1 << 0)
#define PBIST_ALGO_TRIPLE_READ_SECURE_ROM        ((uint32_t)1 << 1)
#define PBIST_ALGO_TRIPLE_READ_BOOT_ROM_1        ((uint32_t)1 << 2)
#define PBIST_ALGO_TRIPLE_READ_CLA1_DATA_ROM     ((uint32_t)1 << 3)
#define PBIST_ALGO_TRIPLE_READ_CLA1_PROGRAM_ROM  ((uint32_t)1 << 4)
#define PBIST_ALGO_TRIPLE_READ_TMU_S1I_ROM       ((uint32_t)1 << 5)
#define PBIST_ALGO_TRIPLE_READ_TMU_S2I_ROM       ((uint32_t)1 << 6)
#define PBIST_ALGO_TRIPLE_READ_TMU_Y0_ROM        ((uint32_t)1 << 7)
#define PBIST_ALGO_TRIPLE_READ_BOOT_ROM_2        ((uint32_t)1 << 8)
#define PBIST_ALGO_MARCH13N_SINGLE_PORT          ((uint32_t)1 << 11)
#define PBIST_ALGO_MARCH13N_DUAL_PORT_DCANA      ((uint32_t)1 << 13)
#define PBIST_ALGO_MARCH13N_DUAL_PORT_DCANB      ((uint32_t)1 << 14)

//
// The following are defines for the bit fields in the DC1 register
//
#define SYSCTL_DC1_CPU1_FPU_TMU   0x1U         // CPU1's FPU1+TMU1
#define SYSCTL_DC1_CPU1_VCU       0x4U         // CPU1's VCU
#define SYSCTL_DC1_CPU1_CLA1      0x40U        // CPU1.CLA1
//
// The following are defines for the bit fields in the DC11 register
//
#define SYSCTL_DC11_CAN_A         0x1U         // CAN_A
#define SYSCTL_DC11_CAN_B         0x2U         // CAN_B


//*****************************************************************************
//
// Defines used in the code
//
//*****************************************************************************
/*
#define PBIST_TIMEOUT_ERROR                 0x1U
#define PBIST_MEMORY_FAIL_ERROR             0x10U
#define PBIST_MEMORY_TEST_PASS              0x100U
#define PBIST_MEMORY_TEST_INVALID_MEMORY    0x1000U
#define PBIST_INCORRECT_OPERATION           0x10000U
#define PBIST_RAM_INIT_FAIL                 0x100000U
*/

//*****************************************************************************
//
// Defines for returning 32 bit values
//
//*****************************************************************************
#define PBIST_ALWAYSFAIL_TIMEOUT_ERROR       0xFF00FF00U
#define PBIST_ALWAYSFAIL_INCORRECT_OPERATION 0xFF11FF00U
#define PBIST_DOUBLEINT_TIMEOUT_ERROR        0xFF22FF00U
#define PBIST_MEMORYTEST_TIMEOUT_ERROR       0xFF33FF00U
#define PBIST_MEMORY_FAIL_ERROR              0xFF44FF00U
#define PBIST_MEMORY_TEST_PASS               0xFFFFFFFFU

//
// TMU ROM Algo group
//
#define PBIST_ALGO_TMU_ROM        ( PBIST_ALGO_TRIPLE_READ_TMU_S1I_ROM | \
                                    PBIST_ALGO_TRIPLE_READ_TMU_S2I_ROM | \
                                    PBIST_ALGO_TRIPLE_READ_TMU_Y0_ROM )
//
// CLA ROM Algo group
//
#define PBIST_ALGO_CLA_ROM        ( PBIST_ALGO_TRIPLE_READ_CLA1_DATA_ROM | \
                                    PBIST_ALGO_TRIPLE_READ_CLA1_PROGRAM_ROM )									

#define PBIST_ALGO_MARCH13N_DUAL_PORT ( PBIST_ALGO_MARCH13N_DUAL_PORT_DCANA | \
                                         PBIST_ALGO_MARCH13N_DUAL_PORT_DCANB)

//
// All ROM except BOOTROM and RAM test algorithms selection
//
#define PBIST_ALGO_ALL_ROM_RAM    ( PBIST_ALGO_TRIPLE_READ_PBIST_ROM | \
                                    PBIST_ALGO_TRIPLE_READ_SECURE_ROM | \
                                    PBIST_ALGO_CLA_ROM | \
                                    PBIST_ALGO_TMU_ROM | \
                                    PBIST_ALGO_MARCH13N_SINGLE_PORT | \
                                    PBIST_ALGO_MARCH13N_DUAL_PORT )
									
//
// Definitions related to always-fail portion
//
#define PBIST_RINFOL_ROM_MEM_GROUP            ((uint32_t)1 << 5)
#define PBIST_ALGO_TMU_ROM_FAIL_ALGO          ((uint32_t)1 << 11)

//*****************************************************************************
//
// Test Memory on Power on Reset 
//
//*****************************************************************************
extern uint32_t PBIST_PORMemoryTest(void);
