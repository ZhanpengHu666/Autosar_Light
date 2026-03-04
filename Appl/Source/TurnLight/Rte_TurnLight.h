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
 *        Config:  G:/matlab/TurnLight/S32K144_SIP/MICROSAR/CBD1800257_D01_S32K1xx/Applications/S32K144_Start_new_IAR/S32K144_Start.dpa
 *     SW-C Type:  TurnLight
 *  Generated at:  Fri Aug  9 18:55:32 2024
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Application header file for SW-C <TurnLight> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_TURNLIGHT_H
# define _RTE_TURNLIGHT_H

# ifdef RTE_APPLICATION_HEADER_FILE
#  error Multiple application header files included.
# endif
# define RTE_APPLICATION_HEADER_FILE
# ifndef RTE_PTR2ARRAYBASETYPE_PASSING
#  define RTE_PTR2ARRAYBASETYPE_PASSING
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_TurnLight_Type.h"
# include "Rte_DataHandleType.h"


/**********************************************************************************************************************
 * Component Data Structures and Port Data Structures
 *********************************************************************************************************************/

struct Rte_CDS_TurnLight
{
  /* dummy entry */
  uint8 _dummy;
};

# define RTE_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONSTP2CONST(struct Rte_CDS_TurnLight, RTE_CONST, RTE_CONST) Rte_Inst_TurnLight; /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

typedef P2CONST(struct Rte_CDS_TurnLight, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_CountSignal_Left_u8_Signal (0U)
# define Rte_InitValue_CountSignal_Right_u8_Signal (0U)
# define Rte_InitValue_CrashIntensity_u8_Signal (0U)
# define Rte_InitValue_EmergencyBrakeLight_u8_Signal (0U)
# define Rte_InitValue_HazardSw_u8_Signal (0U)
# define Rte_InitValue_IGN_Status_u8_signal (0U)
# define Rte_InitValue_TurnLampCtrlCmd_FL_u8_signal (0U)
# define Rte_InitValue_TurnLampCtrlCmd_FR_u8_signa (0U)
# define Rte_InitValue_TurnLampCtrlCmd_RL_u8_signal (0U)
# define Rte_InitValue_TurnLampCtrlCmd_RR_u8_signal (0ULL)
# define Rte_InitValue_TurnLampFb_FL_u8_Signal (0U)
# define Rte_InitValue_TurnLampFb_FR_u8_Signal (0U)
# define Rte_InitValue_TurnLampFb_RL_u8_Signal (0U)
# define Rte_InitValue_TurnLampFb_RR_u8_Signal (0U)
# define Rte_InitValue_TurnLampSw_u8_Signal (0U)
# define Rte_InitValue_TurnLampSwMode_u8_signa (0U)
# define Rte_InitValue_VehicleSpeed_u16_signal (0U)
# define Rte_InitValue_VehicleSpeed_Valid_u8_Signal (0U)


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_CountSignal_Left_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_CountSignal_Right_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_CrashIntensity_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_EmergencyBrakeLight_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_HazardSw_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_IGN_Status_u8_signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_TurnLampCtrlCmd_FL_u8_signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_TurnLampCtrlCmd_FR_u8_signa(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_TurnLampCtrlCmd_RL_u8_signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_TurnLampCtrlCmd_RR_u8_signal(P2VAR(uint64, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_TurnLampFb_FL_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_TurnLampFb_FR_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_TurnLampFb_RL_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_TurnLampFb_RR_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_TurnLampSw_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_VehicleSpeed_u16_signal(P2VAR(uint16, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLight_VehicleSpeed_Valid_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLight_TurnLampSwMode_u8_signa(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_TurnLight_TurnLightService_TurnLightControl_Operation(P2CONST(TurnLightService, AUTOMATIC, RTE_TURNLIGHT_APPL_DATA) TurnLightCtrlPara); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Read_CountSignal_Left_u8_Signal Rte_Read_TurnLight_CountSignal_Left_u8_Signal
# define Rte_Read_CountSignal_Right_u8_Signal Rte_Read_TurnLight_CountSignal_Right_u8_Signal
# define Rte_Read_CrashIntensity_u8_Signal Rte_Read_TurnLight_CrashIntensity_u8_Signal
# define Rte_Read_EmergencyBrakeLight_u8_Signal Rte_Read_TurnLight_EmergencyBrakeLight_u8_Signal
# define Rte_Read_HazardSw_u8_Signal Rte_Read_TurnLight_HazardSw_u8_Signal
# define Rte_Read_IGN_Status_u8_signal Rte_Read_TurnLight_IGN_Status_u8_signal
# define Rte_Read_TurnLampCtrlCmd_FL_u8_signal Rte_Read_TurnLight_TurnLampCtrlCmd_FL_u8_signal
# define Rte_Read_TurnLampCtrlCmd_FR_u8_signa Rte_Read_TurnLight_TurnLampCtrlCmd_FR_u8_signa
# define Rte_Read_TurnLampCtrlCmd_RL_u8_signal Rte_Read_TurnLight_TurnLampCtrlCmd_RL_u8_signal
# define Rte_Read_TurnLampCtrlCmd_RR_u8_signal Rte_Read_TurnLight_TurnLampCtrlCmd_RR_u8_signal
# define Rte_Read_TurnLampFb_FL_u8_Signal Rte_Read_TurnLight_TurnLampFb_FL_u8_Signal
# define Rte_Read_TurnLampFb_FR_u8_Signal Rte_Read_TurnLight_TurnLampFb_FR_u8_Signal
# define Rte_Read_TurnLampFb_RL_u8_Signal Rte_Read_TurnLight_TurnLampFb_RL_u8_Signal
# define Rte_Read_TurnLampFb_RR_u8_Signal Rte_Read_TurnLight_TurnLampFb_RR_u8_Signal
# define Rte_Read_TurnLampSw_u8_Signal Rte_Read_TurnLight_TurnLampSw_u8_Signal
# define Rte_Read_VehicleSpeed_u16_signal Rte_Read_TurnLight_VehicleSpeed_u16_signal
# define Rte_Read_VehicleSpeed_Valid_u8_Signal Rte_Read_TurnLight_VehicleSpeed_Valid_u8_Signal


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Write_TurnLampSwMode_u8_signa Rte_Write_TurnLight_TurnLampSwMode_u8_signa


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (C/S invocation)
 *********************************************************************************************************************/
# define Rte_Call_TurnLightService_TurnLightControl_Operation Rte_Call_TurnLight_TurnLightService_TurnLightControl_Operation




# define TurnLight_START_SEC_CODE
# include "TurnLight_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *
 * Runnable Entity Name: TurnLight_Runnable_10ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_CountSignal_Left_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_CountSignal_Right_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_CrashIntensity_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_EmergencyBrakeLight_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_HazardSw_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_IGN_Status_u8_signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLampCtrlCmd_FL_u8_signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLampCtrlCmd_FR_u8_signa(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLampCtrlCmd_RL_u8_signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLampCtrlCmd_RR_u8_signal(uint64 *data)
 *   Std_ReturnType Rte_Read_TurnLampFb_FL_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLampFb_FR_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLampFb_RL_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLampFb_RR_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLampSw_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_VehicleSpeed_u16_signal(uint16 *data)
 *   Std_ReturnType Rte_Read_VehicleSpeed_Valid_u8_Signal(uint8 *data)
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_TurnLampSwMode_u8_signa(uint8 data)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_TurnLightService_TurnLightControl_Operation(const TurnLightService *TurnLightCtrlPara)
 *     Synchronous Server Invocation. Timeout: 10ms
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_TurnLight_Runnable_10ms TurnLight_Runnable_10ms
FUNC(void, TurnLight_CODE) TurnLight_Runnable_10ms(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define TurnLight_STOP_SEC_CODE
# include "TurnLight_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_TURNLIGHT_H */
