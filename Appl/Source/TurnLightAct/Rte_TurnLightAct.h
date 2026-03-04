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
 *        Config:  G:/matlab/TurnLight/S32K144_SIP/MICROSAR/CBD1800257_D01_S32K1xx/Applications/S32K144_Start_new_IAR/S32K144_Start.dpa
 *     SW-C Type:  TurnLightAct
 *  Generated at:  Fri Aug  9 18:55:32 2024
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Application header file for SW-C <TurnLightAct> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_TURNLIGHTACT_H
# define _RTE_TURNLIGHTACT_H

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

# include "Rte_TurnLightAct_Type.h"
# include "Rte_DataHandleType.h"


/**********************************************************************************************************************
 * Component Data Structures and Port Data Structures
 *********************************************************************************************************************/

struct Rte_CDS_TurnLightAct
{
  /* dummy entry */
  uint8 _dummy;
};

# define RTE_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONSTP2CONST(struct Rte_CDS_TurnLightAct, RTE_CONST, RTE_CONST) Rte_Inst_TurnLightAct; /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

typedef P2CONST(struct Rte_CDS_TurnLightAct, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_Com_CAN_LA_St_DirectionLampL_u8_signal (0U)
# define Rte_InitValue_Com_CAN_LA_St_DirectionLampR_u8_signal (0U)
# define Rte_InitValue_CountSignal_Left_u8_Signal (0U)
# define Rte_InitValue_CountSignal_Right_u8_Signal (0U)
# define Rte_InitValue_TurnLampCtrlCmd_FL_u8_signal (0U)
# define Rte_InitValue_TurnLampCtrlCmd_FR_u8_signa (0U)
# define Rte_InitValue_TurnLampCtrlCmd_RL_u8_signal (0U)
# define Rte_InitValue_TurnLampCtrlCmd_RR_u8_signal (0ULL)
# define Rte_InitValue_TurnLamp_FL_Out_u8_Signal (0U)
# define Rte_InitValue_TurnLamp_RL_Out_u8_Signal (0U)
# define Rte_InitValue_TurnLapm_FR_Out_u8_Signal (0U)
# define Rte_InitValue_TurnLapme_RR_Out_u8_Signal (0U)


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLightAct_TurnLamp_FL_Out_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHTACT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLightAct_TurnLamp_RL_Out_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHTACT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLightAct_TurnLapm_FR_Out_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHTACT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_TurnLightAct_TurnLapme_RR_Out_u8_Signal(P2VAR(uint8, AUTOMATIC, RTE_TURNLIGHTACT_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_Com_CAN_LA_St_DirectionLampL_u8_signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_Com_CAN_LA_St_DirectionLampR_u8_signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_CountSignal_Left_u8_Signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_CountSignal_Right_u8_Signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_TurnLampCtrlCmd_FL_u8_signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_TurnLampCtrlCmd_FR_u8_signa(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_TurnLampCtrlCmd_RL_u8_signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightAct_TurnLampCtrlCmd_RR_u8_signal(uint64 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Read_TurnLamp_FL_Out_u8_Signal Rte_Read_TurnLightAct_TurnLamp_FL_Out_u8_Signal
# define Rte_Read_TurnLamp_RL_Out_u8_Signal Rte_Read_TurnLightAct_TurnLamp_RL_Out_u8_Signal
# define Rte_Read_TurnLapm_FR_Out_u8_Signal Rte_Read_TurnLightAct_TurnLapm_FR_Out_u8_Signal
# define Rte_Read_TurnLapme_RR_Out_u8_Signal Rte_Read_TurnLightAct_TurnLapme_RR_Out_u8_Signal


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Write_Com_CAN_LA_St_DirectionLampL_u8_signal Rte_Write_TurnLightAct_Com_CAN_LA_St_DirectionLampL_u8_signal
# define Rte_Write_Com_CAN_LA_St_DirectionLampR_u8_signal Rte_Write_TurnLightAct_Com_CAN_LA_St_DirectionLampR_u8_signal
# define Rte_Write_CountSignal_Left_u8_Signal Rte_Write_TurnLightAct_CountSignal_Left_u8_Signal
# define Rte_Write_CountSignal_Right_u8_Signal Rte_Write_TurnLightAct_CountSignal_Right_u8_Signal
# define Rte_Write_TurnLampCtrlCmd_FL_u8_signal Rte_Write_TurnLightAct_TurnLampCtrlCmd_FL_u8_signal
# define Rte_Write_TurnLampCtrlCmd_FR_u8_signa Rte_Write_TurnLightAct_TurnLampCtrlCmd_FR_u8_signa
# define Rte_Write_TurnLampCtrlCmd_RL_u8_signal Rte_Write_TurnLightAct_TurnLampCtrlCmd_RL_u8_signal
# define Rte_Write_TurnLampCtrlCmd_RR_u8_signal Rte_Write_TurnLightAct_TurnLampCtrlCmd_RR_u8_signal




# define TurnLightAct_START_SEC_CODE
# include "TurnLightAct_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *
 * Runnable Entity Name: TurnLightAct_Runnable_10ms
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
 *   Std_ReturnType Rte_Read_TurnLamp_FL_Out_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLamp_RL_Out_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLapm_FR_Out_u8_Signal(uint8 *data)
 *   Std_ReturnType Rte_Read_TurnLapme_RR_Out_u8_Signal(uint8 *data)
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_Com_CAN_LA_St_DirectionLampL_u8_signal(uint8 data)
 *   Std_ReturnType Rte_Write_Com_CAN_LA_St_DirectionLampR_u8_signal(uint8 data)
 *   Std_ReturnType Rte_Write_CountSignal_Left_u8_Signal(uint8 data)
 *   Std_ReturnType Rte_Write_CountSignal_Right_u8_Signal(uint8 data)
 *   Std_ReturnType Rte_Write_TurnLampCtrlCmd_FL_u8_signal(uint8 data)
 *   Std_ReturnType Rte_Write_TurnLampCtrlCmd_FR_u8_signa(uint8 data)
 *   Std_ReturnType Rte_Write_TurnLampCtrlCmd_RL_u8_signal(uint8 data)
 *   Std_ReturnType Rte_Write_TurnLampCtrlCmd_RR_u8_signal(uint64 data)
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_TurnLightAct_Runnable_10ms TurnLightAct_Runnable_10ms
FUNC(void, TurnLightAct_CODE) TurnLightAct_Runnable_10ms(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define TurnLightAct_STOP_SEC_CODE
# include "TurnLightAct_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_TURNLIGHTACT_H */
