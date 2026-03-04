/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  TurnLightAct.c
 *        Config:  S32K144_Start.dpa
 *     SW-C Type:  TurnLightAct
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  C-Code implementation template for SW-C <TurnLightAct>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0614 EOF */ /* MD_Rte_TestCode */

/* PRQA S 3109 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3112 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3197 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3198 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3199 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3201 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3203 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3205 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3206 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3218 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3229 EOF */ /* MD_Rte_TestCode */
/* PRQA S 2002 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3334 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3417 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3426 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3453 EOF */ /* MD_Rte_TestCode */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_TurnLightAct.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */
#include "TSC_TurnLightAct.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "string.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * uint64: Integer in interval [0...18446744073709551615] (standard type)
 * uint8: Integer in interval [0...255] (standard type)
 *
 *********************************************************************************************************************/


#define TurnLightAct_START_SEC_CODE
#include "TurnLightAct_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

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
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_IoHwAb_TurnLightCtrlCmd_FL_Operation(uint8 CtrlCmd)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_IoHwAb_TurnLightCtrlCmd_FR_Operation(uint8 CtrlCmd)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_IoHwAb_TurnLightCtrlCmd_RL_Operation(uint8 CtrlCmd)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_IoHwAb_TurnLightCtrlCmd_RR_Operation(uint8 CtrlCmd)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: TurnLightAct_Runnable_10ms_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, TurnLightAct_CODE) TurnLightAct_Runnable_10ms(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TurnLightAct_Runnable_10ms
 *********************************************************************************************************************/

  Std_ReturnType fct_status;
  boolean fct_error = 0;

  uint8 Read_TurnLamp_FL_Out_u8_Signal;
  uint8 Read_TurnLamp_RL_Out_u8_Signal;
  uint8 Read_TurnLapm_FR_Out_u8_Signal;
  uint8 Read_TurnLapme_RR_Out_u8_Signal;

  /*************************************************
  * Direct Function Accesses
  *************************************************/

  fct_status = TSC_TurnLightAct_Rte_Read_TurnLamp_FL_Out_u8_Signal(&Read_TurnLamp_FL_Out_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
    case RTE_E_UNCONNECTED:
      fct_error = 1;
      break;
    case RTE_E_NEVER_RECEIVED:
      fct_error = 1;
      break;
    case RTE_E_INVALID:
      fct_error = 1;
      break;
    case RTE_E_MAX_AGE_EXCEEDED:
      fct_error = 1;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Read_TurnLamp_RL_Out_u8_Signal(&Read_TurnLamp_RL_Out_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
    case RTE_E_UNCONNECTED:
      fct_error = 1;
      break;
    case RTE_E_NEVER_RECEIVED:
      fct_error = 1;
      break;
    case RTE_E_INVALID:
      fct_error = 1;
      break;
    case RTE_E_MAX_AGE_EXCEEDED:
      fct_error = 1;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Read_TurnLapm_FR_Out_u8_Signal(&Read_TurnLapm_FR_Out_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
    case RTE_E_UNCONNECTED:
      fct_error = 1;
      break;
    case RTE_E_NEVER_RECEIVED:
      fct_error = 1;
      break;
    case RTE_E_INVALID:
      fct_error = 1;
      break;
    case RTE_E_MAX_AGE_EXCEEDED:
      fct_error = 1;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Read_TurnLapme_RR_Out_u8_Signal(&Read_TurnLapme_RR_Out_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
    case RTE_E_UNCONNECTED:
      fct_error = 1;
      break;
    case RTE_E_NEVER_RECEIVED:
      fct_error = 1;
      break;
    case RTE_E_INVALID:
      fct_error = 1;
      break;
    case RTE_E_MAX_AGE_EXCEEDED:
      fct_error = 1;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Write_Com_CAN_LA_St_DirectionLampL_u8_signal(Rte_InitValue_Com_CAN_LA_St_DirectionLampL_u8_signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Write_Com_CAN_LA_St_DirectionLampR_u8_signal(Rte_InitValue_Com_CAN_LA_St_DirectionLampR_u8_signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Write_CountSignal_Left_u8_Signal(Rte_InitValue_CountSignal_Left_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Write_CountSignal_Right_u8_Signal(Rte_InitValue_CountSignal_Right_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Write_TurnLampCtrlCmd_FL_u8_signal(Rte_InitValue_TurnLampCtrlCmd_FL_u8_signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Write_TurnLampCtrlCmd_FR_u8_signa(Rte_InitValue_TurnLampCtrlCmd_FR_u8_signa);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Write_TurnLampCtrlCmd_RL_u8_signal(Rte_InitValue_TurnLampCtrlCmd_RL_u8_signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Write_TurnLampCtrlCmd_RR_u8_signal(Rte_InitValue_TurnLampCtrlCmd_RR_u8_signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Call_IoHwAb_TurnLightCtrlCmd_FL_Operation(0U);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
    case RTE_E_UNCONNECTED:
      fct_error = 1;
      break;
    case RTE_E_TIMEOUT:
      fct_error = 1;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Call_IoHwAb_TurnLightCtrlCmd_FR_Operation(0U);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
    case RTE_E_UNCONNECTED:
      fct_error = 1;
      break;
    case RTE_E_TIMEOUT:
      fct_error = 1;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Call_IoHwAb_TurnLightCtrlCmd_RL_Operation(0U);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
    case RTE_E_UNCONNECTED:
      fct_error = 1;
      break;
    case RTE_E_TIMEOUT:
      fct_error = 1;
      break;
  }

  fct_status = TSC_TurnLightAct_Rte_Call_IoHwAb_TurnLightCtrlCmd_RR_Operation(0U);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
    case RTE_E_UNCONNECTED:
      fct_error = 1;
      break;
    case RTE_E_TIMEOUT:
      fct_error = 1;
      break;
  }


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define TurnLightAct_STOP_SEC_CODE
#include "TurnLightAct_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_TestCode:
     Reason:     This justification is used within the generated test code by the Rte Analyzer.
     Risk:       No functional risk.
     Prevention: Not required.

*/
