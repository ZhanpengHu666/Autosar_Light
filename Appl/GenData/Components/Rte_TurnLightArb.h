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
 *          File:  Rte_TurnLightArb.h
 *        Config:  S32K144_Start.dpa
 *   ECU-Project:  MyECU
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Application header file for SW-C <TurnLightArb>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_TURNLIGHTARB_H
# define _RTE_TURNLIGHTARB_H

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

# include "Rte_TurnLightArb_Type.h"
# include "Rte_DataHandleType.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * extern declaration of RTE buffers for optimized macro implementation
 *********************************************************************************************************************/
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

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

#  define Rte_InitValue_TurnLamp_FL_Out_u8_Signal (0U)
#  define Rte_InitValue_TurnLamp_RL_Out_u8_Signal (0U)
#  define Rte_InitValue_TurnLapm_FR_Out_u8_Signal (0U)
#  define Rte_InitValue_TurnLapme_RR_Out_u8_Signal (0U)
# endif


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Write_TurnLamp_FL_Out_u8_Signal Rte_Write_TurnLightArb_TurnLamp_FL_Out_u8_Signal
#  define Rte_Write_TurnLightArb_TurnLamp_FL_Out_u8_Signal(data) (Rte_TurnLightArb_TurnLamp_FL_Out_u8_Signal = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Write_TurnLamp_RL_Out_u8_Signal Rte_Write_TurnLightArb_TurnLamp_RL_Out_u8_Signal
#  define Rte_Write_TurnLightArb_TurnLamp_RL_Out_u8_Signal(data) (Rte_TurnLightArb_TurnLamp_RL_Out_u8_Signal = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Write_TurnLapm_FR_Out_u8_Signal Rte_Write_TurnLightArb_TurnLapm_FR_Out_u8_Signal
#  define Rte_Write_TurnLightArb_TurnLapm_FR_Out_u8_Signal(data) (Rte_TurnLightArb_TurnLapm_FR_Out_u8_Signal = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Write_TurnLapme_RR_Out_u8_Signal Rte_Write_TurnLightArb_TurnLapme_RR_Out_u8_Signal
#  define Rte_Write_TurnLightArb_TurnLapme_RR_Out_u8_Signal(data) (Rte_TurnLightArb_TurnLapme_RR_Out_u8_Signal = (data), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */


# endif /* !defined(RTE_CORE) */


# define TurnLightArb_START_SEC_CODE
# include "TurnLightArb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_TurnLightArb_Runnable_10ms TurnLightArb_Runnable_10ms
#  define RTE_RUNNABLE_TurnLightService_TurnLightControl_Operation TurnLightService_TurnLightControl_Operation
# endif

FUNC(void, TurnLightArb_CODE) TurnLightArb_Runnable_10ms(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, TurnLightArb_CODE) TurnLightService_TurnLightControl_Operation(P2CONST(TurnLightService, AUTOMATIC, RTE_TURNLIGHTARB_APPL_DATA) TurnLightCtrlPara); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define TurnLightArb_STOP_SEC_CODE
# include "TurnLightArb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_TURNLIGHTARB_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
