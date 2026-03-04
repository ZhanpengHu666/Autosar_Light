/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte_TurnLightAct.h
 *        Config:  S32K144_Start.dpa
 *   ECU-Project:  MyECU
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Application header file for SW-C <TurnLightAct>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_TURNLIGHTACT_H
# define _RTE_TURNLIGHTACT_H

# ifndef RTE_CORE
#  ifdef RTE_APPLICATION_HEADER_FILE
#   error Multiple application header files included.
#  endif
#  define RTE_APPLICATION_HEADER_FILE
#  ifndef RTE_PTR2ARRAYBASETYPE_PASSING
#   define RTE_PTR2ARRAYBASETYPE_PASSING
#  endif
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_TurnLightAct_Type.h"
# include "Rte_DataHandleType.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * extern declaration of RTE buffers for optimized macro implementation
 *********************************************************************************************************************/
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern VAR(uint8, RTE_VAR_NOINIT) Rte_TurnLightAct_CountSignal_Left_u8_Signal; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint8, RTE_VAR_NOINIT) Rte_TurnLightAct_CountSignal_Right_u8_Signal; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint8, RTE_VAR_NOINIT) Rte_TurnLightAct_TurnLampCtrlCmd_FL_u8_signal; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint8, RTE_VAR_NOINIT) Rte_TurnLightAct_TurnLampCtrlCmd_FR_u8_signa; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint8, RTE_VAR_NOINIT) Rte_TurnLightAct_TurnLampCtrlCmd_RL_u8_signal; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint64, RTE_VAR_NOINIT) Rte_TurnLightAct_TurnLampCtrlCmd_RR_u8_signal; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint8, RTE_VAR_NOINIT) Rte_TurnLightArb_TurnLamp_FL_Out_u8_Signal; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint8, RTE_VAR_NOINIT) Rte_TurnLightArb_TurnLamp_RL_Out_u8_Signal; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint8, RTE_VAR_NOINIT) Rte_TurnLightArb_TurnLapm_FR_Out_u8_Signal; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint8, RTE_VAR_NOINIT) Rte_TurnLightArb_TurnLapme_RR_Out_u8_Signal; /* PRQA S 0850 */ /* MD_MSR_19.8 */

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_Com_CAN_LA_St_DirectionLampL_u8_signal (0U)
#  define Rte_InitValue_Com_CAN_LA_St_DirectionLampR_u8_signal (0U)
#  define Rte_InitValue_CountSignal_Left_u8_Signal (0U)
#  define Rte_InitValue_CountSignal_Right_u8_Signal (0U)
#  define Rte_InitValue_TurnLampCtrlCmd_FL_u8_signal (0U)
#  define Rte_InitValue_TurnLampCtrlCmd_FR_u8_signa (0U)
#  define Rte_InitValue_TurnLampCtrlCmd_RL_u8_signal (0U)
#  define Rte_InitValue_TurnLampCtrlCmd_RR_u8_signal (0ULL)
#  define Rte_InitValue_TurnLamp_FL_Out_u8_Signal (0U)
#  define Rte_InitValue_TurnLamp_RL_Out_u8_Signal (0U)
#  define Rte_InitValue_TurnLapm_FR_Out_u8_Signal (0U)
#  define Rte_InitValue_TurnLapme_RR_Out_u8_Signal (0U)
# endif


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_Com_CAN_LA_St_DirectionLampL_u8_signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_Com_CAN_LA_St_DirectionLampR_u8_signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_TurnLamp_FL_Out_u8_Signal Rte_Read_TurnLightAct_TurnLamp_FL_Out_u8_Signal
#  define Rte_Read_TurnLightAct_TurnLamp_FL_Out_u8_Signal(data) (*(data) = Rte_TurnLightArb_TurnLamp_FL_Out_u8_Signal, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLamp_RL_Out_u8_Signal Rte_Read_TurnLightAct_TurnLamp_RL_Out_u8_Signal
#  define Rte_Read_TurnLightAct_TurnLamp_RL_Out_u8_Signal(data) (*(data) = Rte_TurnLightArb_TurnLamp_RL_Out_u8_Signal, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLapm_FR_Out_u8_Signal Rte_Read_TurnLightAct_TurnLapm_FR_Out_u8_Signal
#  define Rte_Read_TurnLightAct_TurnLapm_FR_Out_u8_Signal(data) (*(data) = Rte_TurnLightArb_TurnLapm_FR_Out_u8_Signal, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLapme_RR_Out_u8_Signal Rte_Read_TurnLightAct_TurnLapme_RR_Out_u8_Signal
#  define Rte_Read_TurnLightAct_TurnLapme_RR_Out_u8_Signal(data) (*(data) = Rte_TurnLightArb_TurnLapme_RR_Out_u8_Signal, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Write_Com_CAN_LA_St_DirectionLampL_u8_signal Rte_Write_TurnLightAct_Com_CAN_LA_St_DirectionLampL_u8_signal
#  define Rte_Write_Com_CAN_LA_St_DirectionLampR_u8_signal Rte_Write_TurnLightAct_Com_CAN_LA_St_DirectionLampR_u8_signal
#  define Rte_Write_CountSignal_Left_u8_Signal Rte_Write_TurnLightAct_CountSignal_Left_u8_Signal
#  define Rte_Write_TurnLightAct_CountSignal_Left_u8_Signal(data) (Rte_TurnLightAct_CountSignal_Left_u8_Signal = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Write_CountSignal_Right_u8_Signal Rte_Write_TurnLightAct_CountSignal_Right_u8_Signal
#  define Rte_Write_TurnLightAct_CountSignal_Right_u8_Signal(data) (Rte_TurnLightAct_CountSignal_Right_u8_Signal = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Write_TurnLampCtrlCmd_FL_u8_signal Rte_Write_TurnLightAct_TurnLampCtrlCmd_FL_u8_signal
#  define Rte_Write_TurnLightAct_TurnLampCtrlCmd_FL_u8_signal(data) (Rte_TurnLightAct_TurnLampCtrlCmd_FL_u8_signal = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Write_TurnLampCtrlCmd_FR_u8_signa Rte_Write_TurnLightAct_TurnLampCtrlCmd_FR_u8_signa
#  define Rte_Write_TurnLightAct_TurnLampCtrlCmd_FR_u8_signa(data) (Rte_TurnLightAct_TurnLampCtrlCmd_FR_u8_signa = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Write_TurnLampCtrlCmd_RL_u8_signal Rte_Write_TurnLightAct_TurnLampCtrlCmd_RL_u8_signal
#  define Rte_Write_TurnLightAct_TurnLampCtrlCmd_RL_u8_signal(data) (Rte_TurnLightAct_TurnLampCtrlCmd_RL_u8_signal = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Write_TurnLampCtrlCmd_RR_u8_signal Rte_Write_TurnLightAct_TurnLampCtrlCmd_RR_u8_signal
#  define Rte_Write_TurnLightAct_TurnLampCtrlCmd_RR_u8_signal(data) (Rte_TurnLightAct_TurnLampCtrlCmd_RR_u8_signal = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_CDD_IOHWAB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CDD_IOHWAB_APPL_CODE) IoHwAb_TurnLightCtrlCmd_FL_Operation(uint8 CtrlCmd); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CDD_IOHWAB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_IoHwAb_TurnLightCtrlCmd_FL_Operation(arg1) (IoHwAb_TurnLightCtrlCmd_FL_Operation(arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CDD_IOHWAB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CDD_IOHWAB_APPL_CODE) IoHwAb_TurnLightCtrlCmd_FR_Operation(uint8 CtrlCmd); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CDD_IOHWAB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_IoHwAb_TurnLightCtrlCmd_FR_Operation(arg1) (IoHwAb_TurnLightCtrlCmd_FR_Operation(arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CDD_IOHWAB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CDD_IOHWAB_APPL_CODE) IoHwAb_TurnLightCtrlCmd_RL_Operation(uint8 CtrlCmd); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CDD_IOHWAB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_IoHwAb_TurnLightCtrlCmd_RL_Operation(arg1) (IoHwAb_TurnLightCtrlCmd_RL_Operation(arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_CDD_IOHWAB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_CDD_IOHWAB_APPL_CODE) IoHwAb_TurnLightCtrlCmd_RR_Operation(uint8 CtrlCmd); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_CDD_IOHWAB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_IoHwAb_TurnLightCtrlCmd_RR_Operation(arg1) (IoHwAb_TurnLightCtrlCmd_RR_Operation(arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */


# endif /* !defined(RTE_CORE) */


# define TurnLightAct_START_SEC_CODE
# include "TurnLightAct_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_TurnLightAct_Runnable_10ms TurnLightAct_Runnable_10ms
# endif

FUNC(void, TurnLightAct_CODE) TurnLightAct_Runnable_10ms(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */

# define TurnLightAct_STOP_SEC_CODE
# include "TurnLightAct_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_TURNLIGHTACT_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
