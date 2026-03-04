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
 *          File:  Rte_TurnLight.h
 *        Config:  S32K144_Start.dpa
 *   ECU-Project:  MyECU
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Application header file for SW-C <TurnLight>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_TURNLIGHT_H
# define _RTE_TURNLIGHT_H

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

# include "Rte_TurnLight_Type.h"
# include "Rte_DataHandleType.h"

# ifndef RTE_CORE

#  include "Com.h"


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

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_CountSignal_Left_u8_Signal (0U)
#  define Rte_InitValue_CountSignal_Right_u8_Signal (0U)
#  define Rte_InitValue_CrashIntensity_u8_Signal (0U)
#  define Rte_InitValue_EmergencyBrakeLight_u8_Signal (0U)
#  define Rte_InitValue_HazardSw_u8_Signal (0U)
#  define Rte_InitValue_IGN_Status_u8_signal (0U)
#  define Rte_InitValue_TurnLampCtrlCmd_FL_u8_signal (0U)
#  define Rte_InitValue_TurnLampCtrlCmd_FR_u8_signa (0U)
#  define Rte_InitValue_TurnLampCtrlCmd_RL_u8_signal (0U)
#  define Rte_InitValue_TurnLampCtrlCmd_RR_u8_signal (0ULL)
#  define Rte_InitValue_TurnLampFb_FL_u8_Signal (0U)
#  define Rte_InitValue_TurnLampFb_FR_u8_Signal (0U)
#  define Rte_InitValue_TurnLampFb_RL_u8_Signal (0U)
#  define Rte_InitValue_TurnLampFb_RR_u8_Signal (0U)
#  define Rte_InitValue_TurnLampSw_u8_Signal (0U)
#  define Rte_InitValue_TurnLampSwMode_u8_signa (0U)
#  define Rte_InitValue_VehicleSpeed_u16_signal (0U)
#  define Rte_InitValue_VehicleSpeed_Valid_u8_Signal (0U)
# endif


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_CountSignal_Left_u8_Signal Rte_Read_TurnLight_CountSignal_Left_u8_Signal
#  define Rte_Read_TurnLight_CountSignal_Left_u8_Signal(data) (*(data) = Rte_TurnLightAct_CountSignal_Left_u8_Signal, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_CountSignal_Right_u8_Signal Rte_Read_TurnLight_CountSignal_Right_u8_Signal
#  define Rte_Read_TurnLight_CountSignal_Right_u8_Signal(data) (*(data) = Rte_TurnLightAct_CountSignal_Right_u8_Signal, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_CrashIntensity_u8_Signal Rte_Read_TurnLight_CrashIntensity_u8_Signal
#  define Rte_Read_TurnLight_CrashIntensity_u8_Signal(data) (*(data) = 0U, ((Std_ReturnType)RTE_E_UNCONNECTED)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_EmergencyBrakeLight_u8_Signal Rte_Read_TurnLight_EmergencyBrakeLight_u8_Signal
#  define Rte_Read_TurnLight_EmergencyBrakeLight_u8_Signal(data) (Com_ReceiveSignal(ComConf_ComSignal_EmergencyBrakeLight_omsg_Receive_oCAN00_5282eb8e_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_HazardSw_u8_Signal Rte_Read_TurnLight_HazardSw_u8_Signal
#  define Rte_Read_TurnLight_HazardSw_u8_Signal(data) (Com_ReceiveSignal(ComConf_ComSignal_HazardSw_omsg_Receive_oCAN00_578d9c4d_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_IGN_Status_u8_signal Rte_Read_TurnLight_IGN_Status_u8_signal
#  define Rte_Read_TurnLight_IGN_Status_u8_signal(data) (Com_ReceiveSignal(ComConf_ComSignal_IGN_Status_omsg_Receive_oCAN00_593fdbd9_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLampCtrlCmd_FL_u8_signal Rte_Read_TurnLight_TurnLampCtrlCmd_FL_u8_signal
#  define Rte_Read_TurnLight_TurnLampCtrlCmd_FL_u8_signal(data) (*(data) = Rte_TurnLightAct_TurnLampCtrlCmd_FL_u8_signal, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLampCtrlCmd_FR_u8_signa Rte_Read_TurnLight_TurnLampCtrlCmd_FR_u8_signa
#  define Rte_Read_TurnLight_TurnLampCtrlCmd_FR_u8_signa(data) (*(data) = Rte_TurnLightAct_TurnLampCtrlCmd_FR_u8_signa, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLampCtrlCmd_RL_u8_signal Rte_Read_TurnLight_TurnLampCtrlCmd_RL_u8_signal
#  define Rte_Read_TurnLight_TurnLampCtrlCmd_RL_u8_signal(data) (*(data) = Rte_TurnLightAct_TurnLampCtrlCmd_RL_u8_signal, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLampCtrlCmd_RR_u8_signal Rte_Read_TurnLight_TurnLampCtrlCmd_RR_u8_signal
#  define Rte_Read_TurnLight_TurnLampCtrlCmd_RR_u8_signal(data) (*(data) = Rte_TurnLightAct_TurnLampCtrlCmd_RR_u8_signal, ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLampFb_FL_u8_Signal Rte_Read_TurnLight_TurnLampFb_FL_u8_Signal
#  define Rte_Read_TurnLight_TurnLampFb_FL_u8_Signal(data) (Com_ReceiveSignal(ComConf_ComSignal_TurnLampFb_FL_omsg_Receive_oCAN00_3ab29a6d_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLampFb_FR_u8_Signal Rte_Read_TurnLight_TurnLampFb_FR_u8_Signal
#  define Rte_Read_TurnLight_TurnLampFb_FR_u8_Signal(data) (Com_ReceiveSignal(ComConf_ComSignal_TurnLampFb_FR_omsg_Receive_oCAN00_a2998431_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLampFb_RL_u8_Signal Rte_Read_TurnLight_TurnLampFb_RL_u8_Signal
#  define Rte_Read_TurnLight_TurnLampFb_RL_u8_Signal(data) (Com_ReceiveSignal(ComConf_ComSignal_TurnLampFb_RL_omsg_Receive_oCAN00_cfe4432c_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLampFb_RR_u8_Signal Rte_Read_TurnLight_TurnLampFb_RR_u8_Signal
#  define Rte_Read_TurnLight_TurnLampFb_RR_u8_Signal(data) (Com_ReceiveSignal(ComConf_ComSignal_TurnLampFb_RR_omsg_Receive_oCAN00_57cf5d70_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_TurnLampSw_u8_Signal Rte_Read_TurnLight_TurnLampSw_u8_Signal
#  define Rte_Read_TurnLight_TurnLampSw_u8_Signal(data) (Com_ReceiveSignal(ComConf_ComSignal_TurnLampSw_omsg_Receive_oCAN00_92b10255_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_VehicleSpeed_u16_signal Rte_Read_TurnLight_VehicleSpeed_u16_signal
#  define Rte_Read_TurnLight_VehicleSpeed_u16_signal(data) (Com_ReceiveSignal(ComConf_ComSignal_VehicleSpeed_omsg_Receive_oCAN00_e95dd8a1_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_VehicleSpeed_Valid_u8_Signal Rte_Read_TurnLight_VehicleSpeed_Valid_u8_Signal
#  define Rte_Read_TurnLight_VehicleSpeed_Valid_u8_Signal(data) (Com_ReceiveSignal(ComConf_ComSignal_VehicleSpeed_Valid_omsg_Receive_oCAN00_6a5f4ba3_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Write_TurnLampSwMode_u8_signa Rte_Write_TurnLight_TurnLampSwMode_u8_signa
#  define Rte_Write_TurnLight_TurnLampSwMode_u8_signa(data) (RTE_E_OK) /* PRQA S 3453 */ /* MD_MSR_19.7 */


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_TURNLIGHTARB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(void, RTE_TURNLIGHTARB_APPL_CODE) TurnLightService_TurnLightControl_Operation(P2CONST(TurnLightService, AUTOMATIC, RTE_TURNLIGHTARB_APPL_DATA) TurnLightCtrlPara); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_TURNLIGHTARB_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_TurnLightService_TurnLightControl_Operation(arg1) (TurnLightService_TurnLightControl_Operation(arg1), ((Std_ReturnType)RTE_E_OK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */


# endif /* !defined(RTE_CORE) */


# define TurnLight_START_SEC_CODE
# include "TurnLight_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_TurnLight_Runnable_10ms TurnLight_Runnable_10ms
# endif

FUNC(void, TurnLight_CODE) TurnLight_Runnable_10ms(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */

# define TurnLight_STOP_SEC_CODE
# include "TurnLight_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_TURNLIGHT_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
