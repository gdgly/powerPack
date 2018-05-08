/* ==============================================================================
System Name:  EwInv 

File Name:	fault.h

Description:

Originator:	Induction Motor Sensorless Vector Control systems Group
            - Eunwho Power Electronics-

Hardware System : In this software, suported PCB is EwInv-55k-v1 2008.04.05
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-19-2008	Version 0.01: Setup Outline  
=================================================================================
*/
#ifndef		_ERROR_CODE_DEFINITION_
#define		_ERROR_CODE_DEFINITION_

// 파라미터 오류 코드 	: 1 ~ 799

#define ERR_DB_IGBT							818
#define ERR_PWM_IGBT						819
#define ERR_IGBT_UH							811
#define ERR_IGBT_UL							812
#define ERR_IGBT_VH							813
#define ERR_IGBT_VL							814
#define ERR_IGBT_WH							815
#define ERR_IGBT_WL							816
#define ERR_IGBT_DB							817
//#define ERR_IGBT_RESET						818

#define	ERR_OC0								821
#define	ERR_OC								822
#define	ERR_UC0								823
#define	ERR_OV0								824
#define	ERR_OV								825
#define	ERR_UV0								826
#define	ERR_UV								827
#define	ERR_OS0								828
#define	ERR_OS								829

#define	ERR_SUV								831	
#define	ERR_SOV								832
#define	ERR_SOC								833
#define ERR_OVER_CURRENT_U_PHASE			834 
#define ERR_OVER_CURRENT_V_PHASE			835 

#define ERR_INVALID_CTRL_MODE				836

#define	ERR_NAME_PLATE_PAR_MISMATCH			841
#define	ERR_NAME_PLATE_PAR_MISMATCH0		842
#define	ERR_NAME_PLATE_PAR_MISMATCH1		843

#define	ERR_PM_Is							844
#define	ERR_GM_Is							845
#define	ERR_K_Damp_Is						846


#define	ERR_Tr_Over							851
#define	ERR_Tr_Under						852
#define	ERR_sigma_Under						853
#define	ERR_sigma_Over						854
#define	ERR_Ki_Is_Under						856
#define	ERR_Kp_Is_Over						857
#define	ERR_Kp_Is_Under						858

#define	ERR_EXCITATION_TIME					859

// SCI 
#define ERR_SCI_CMD_ADDR_GROUP_UNDER		861
#define ERR_SCI_CMD_ADDR_GROUP_OVER			862
#define ERR_SCI_CMD_ADDR_1ST_UNDER			863
#define ERR_SCI_CMD_ADDR_1ST_OVER			864
#define ERR_SCI_CMD_ADDR_2ND_UNDER			865
#define ERR_SCI_CMD_ADDR_2ND_OVER			867

// 오토튜닝 오류
#define	ERR_Req_Under						920
#define	ERR_Req_Over						921
#define	ERR_Leq_Under0						923
#define	ERR_Leq_Over0						924
#define	ERR_Rs_Under						925
#define	ERR_Rs_Over							926
#define	ERR_Ls_Over0						927
#define	ERR_Ls_Under0						928	
#define	ERR_Ls_Under1						929
#define	ERR_Ls_Over1						930
#define	ERR_Leq_Over1						931
#define	ERR_Rr_Over							932
#define	ERR_Rr_Under						933
#define	ERR_Jm_Under						934
#define	ERR_Jm_Over							945
#define	ERR_WRONG_INTERRUPT_CMD				950

// 하드웨어 프로텍션 (TMS320F240)
#define	ERR_PRECHARGING_FAIL				960		// 초기 충전 실패 
#define	ERR_PWM								961
#define	ERR_HOC								962
#define	ERR_HOV								963
#define	ERR_HUV								964
#define	ERR_OVER_HEAT						965

#define	ERR_EXT_TRIP						966
#define	TRIP_EXT_A							967

#define	ERR_PWM_CNT							971		// 스위칭 주기의 카운터 값 오류 

#define	ERR_INV_DISABLE						972		// 운전중 인버터 디스에이블 

struct TRIP_INFO_DEFINE {
	int		CODE;				// 1
	float	CURRENT;			// 5
	float	VDC;				// 6
	float	HZ;					// 7
	float	DATA;				// 4
	char 	TIME[31];			// 3
	char 	MSG[41];			// 2
};

typedef struct TRIP_INFO_DEFINE TRIP_INFO;

struct PROTECT_BITS {      // bits description
	Uint16  OVER_VOLT	:1;	
	Uint16  UNVER_VOLT	:1; 
	Uint16  OVER_I  		:1; 
	Uint16  LOW_I		:1; 
	Uint16  OVER_I_ADC	:1; 
	Uint16  LOW_I_ADC	:1;
	Uint16  OVER_LOAD	:1; 
	Uint16  LOW_LOAD		:1;
	Uint16  OVER_SPEED	:1; 
	Uint16  LOW_SPEED	:1; 
	Uint16  IGBT_FAULT	:1;
	Uint16  EX_TRIP		:1; 
	Uint16	OVER_HEAT	:1;
};

union PROTECT_FLAG{
   Uint16               all;
   struct PROTECT_BITS  bit;
};  

#endif


