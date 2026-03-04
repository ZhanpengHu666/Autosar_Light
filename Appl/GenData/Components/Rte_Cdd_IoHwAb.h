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
 *          File:  Rte_Cdd_IoHwAb.h
 *        Config:  S32K144_Start.dpa
 *   ECU-Project:  MyECU
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Application header file for SW-C <Cdd_IoHwAb>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_CDD_IOHWAB_H
# define _RTE_CDD_IOHWAB_H

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

# include "Rte_Cdd_IoHwAb_Type.h"
# include "Rte_DataHandleType.h"


# define Cdd_IoHwAb_START_SEC_CODE
# include "Cdd_IoHwAb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_IoHwAbRunnable IoHwAbRunnable
#  define RTE_RUNNABLE_IoHwAb_TurnLightCtrlCmd_FL_Operation IoHwAb_TurnLightCtrlCmd_FL_Operation
#  define RTE_RUNNABLE_IoHwAb_TurnLightCtrlCmd_FR_Operation IoHwAb_TurnLightCtrlCmd_FR_Operation
#  define RTE_RUNNABLE_IoHwAb_TurnLightCtrlCmd_RL_Operation IoHwAb_TurnLightCtrlCmd_RL_Operation
#  define RTE_RUNNABLE_IoHwAb_TurnLightCtrlCmd_RR_Operation IoHwAb_TurnLightCtrlCmd_RR_Operation
# endif

FUNC(void, Cdd_IoHwAb_CODE) IoHwAbRunnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, Cdd_IoHwAb_CODE) IoHwAb_TurnLightCtrlCmd_FL_Operation(uint8 CtrlCmd); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, Cdd_IoHwAb_CODE) IoHwAb_TurnLightCtrlCmd_FR_Operation(uint8 CtrlCmd); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, Cdd_IoHwAb_CODE) IoHwAb_TurnLightCtrlCmd_RL_Operation(uint8 CtrlCmd); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, Cdd_IoHwAb_CODE) IoHwAb_TurnLightCtrlCmd_RR_Operation(uint8 CtrlCmd); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define Cdd_IoHwAb_STOP_SEC_CODE
# include "Cdd_IoHwAb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_CDD_IOHWAB_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
