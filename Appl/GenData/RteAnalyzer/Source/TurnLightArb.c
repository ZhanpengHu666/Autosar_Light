/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  TurnLightArb.c
 *        Config:  S32K144_Start.dpa
 *     SW-C Type:  TurnLightArb
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  C-Code implementation template for SW-C <TurnLightArb>
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

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************
 *
 * Data Types:
 * ===========
 * ComplexTurnLightONOFFType
 *   
 *
 * ComplexTurnLightPositionType
 *   
 *
 * Rte_DT_TurnLightService_0
 *   
 *
 * Rte_DT_TurnLightService_1
 *   
 *
 * Rte_DT_TurnLightService_2
 *   
 *
 * Rte_DT_TurnLightService_3
 *   
 *
 * Rte_DT_TurnLightService_4
 *   
 *
 * Rte_DT_TurnLightService_5
 *   
 *
 * Rte_DT_TurnLightService_6
 *   
 *
 *********************************************************************************************************************/

#include "Rte_TurnLightArb.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */
#include "TSC_TurnLightArb.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "string.h"

static void TurnLightArb_TestDefines(void);


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
 * Rte_DT_TurnLightService_2: Integer in interval [0...255]
 * Rte_DT_TurnLightService_3: Integer in interval [0...255]
 * Rte_DT_TurnLightService_4: Integer in interval [0...255]
 * Rte_DT_TurnLightService_5: Integer in interval [0...255]
 * Rte_DT_TurnLightService_6: Integer in interval [0...255]
 * uint8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * ComplexTurnLightONOFFType: Enumeration of integer in interval [0...255] with enumerators
 *   NORQUEST (0U)
 *   OFF (1U)
 *   ON (2U)
 * ComplexTurnLightPositionType: Enumeration of integer in interval [0...255] with enumerators
 *   NOREQUEST (0U)
 *   LEFT (1U)
 *   RIGHT (2U)
 *   ALL (3U)
 *   FRONT_LEFT (4U)
 *   MIDDLE_LEFT (5U)
 *   REAR_LEFT (6U)
 *   FRONT_RIGHT (7U)
 *   MIDDLE_RIGHT (8U)
 *   REAR_RIGHT (9U)
 * Rte_DT_TurnLightService_0: Enumeration of integer in interval [0...255] with enumerators
 *   NOREQUEST (0U)
 *   LEFT (1U)
 *   RIGHT (2U)
 *   ALL (3U)
 *   FRONT_LEFT (4U)
 *   MIDDLE_LEFT (5U)
 *   REAR_LEFT (6U)
 *   FRONT_RIGHT (7U)
 *   MIDDLE_RIGHT (8U)
 *   REAR_RIGHT (9U)
 * Rte_DT_TurnLightService_1: Enumeration of integer in interval [0...255] with enumerators
 *   NORQUEST (0U)
 *   OFF (1U)
 *   ON (2U)
 *
 * Record Types:
 * =============
 * TurnLightService: Record with elements
 *   TurnLightPosition of type Rte_DT_TurnLightService_0
 *   TurnLightOnOff of type Rte_DT_TurnLightService_1
 *   TurnLightDutyCycle of type Rte_DT_TurnLightService_2
 *   TurnLightCycle of type Rte_DT_TurnLightService_3
 *   TurnLightTimes of type Rte_DT_TurnLightService_4
 *   TurnLightNumber of type Rte_DT_TurnLightService_5
 *   TurnLightPriority of type Rte_DT_TurnLightService_6
 *
 *********************************************************************************************************************/


#define TurnLightArb_START_SEC_CODE
#include "TurnLightArb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TurnLightArb_Runnable_10ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_TurnLamp_FL_Out_u8_Signal(uint8 data)
 *   Std_ReturnType Rte_Write_TurnLamp_RL_Out_u8_Signal(uint8 data)
 *   Std_ReturnType Rte_Write_TurnLapm_FR_Out_u8_Signal(uint8 data)
 *   Std_ReturnType Rte_Write_TurnLapme_RR_Out_u8_Signal(uint8 data)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: TurnLightArb_Runnable_10ms_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, TurnLightArb_CODE) TurnLightArb_Runnable_10ms(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TurnLightArb_Runnable_10ms
 *********************************************************************************************************************/

  Std_ReturnType fct_status;
  boolean fct_error = 0;

  /*************************************************
  * Direct Function Accesses
  *************************************************/

  fct_status = TSC_TurnLightArb_Rte_Write_TurnLamp_FL_Out_u8_Signal(Rte_InitValue_TurnLamp_FL_Out_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightArb_Rte_Write_TurnLamp_RL_Out_u8_Signal(Rte_InitValue_TurnLamp_RL_Out_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightArb_Rte_Write_TurnLapm_FR_Out_u8_Signal(Rte_InitValue_TurnLapm_FR_Out_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  fct_status = TSC_TurnLightArb_Rte_Write_TurnLapme_RR_Out_u8_Signal(Rte_InitValue_TurnLapme_RR_Out_u8_Signal);
  switch (fct_status)
  {
    case RTE_E_OK:
      fct_error = 0;
      break;
  }

  TurnLightArb_TestDefines();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TurnLightService_TurnLightControl_Operation
 *
 * This runnable can be invoked concurrently (reentrant implementation).
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <TurnLightControl_Operation> of PortPrototype <TurnLightService>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void TurnLightService_TurnLightControl_Operation(const TurnLightService *TurnLightCtrlPara)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: TurnLightService_TurnLightControl_Operation_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, TurnLightArb_CODE) TurnLightService_TurnLightControl_Operation(P2CONST(TurnLightService, AUTOMATIC, RTE_TURNLIGHTARB_APPL_DATA) TurnLightCtrlPara) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TurnLightService_TurnLightControl_Operation
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define TurnLightArb_STOP_SEC_CODE
#include "TurnLightArb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

static void TurnLightArb_TestDefines(void)
{
  /* Primitive Types */

  Rte_DT_TurnLightService_2 Test_Rte_DT_TurnLightService_2_IV_1 = InvalidValue_Rte_DT_TurnLightService_2;

  Rte_DT_TurnLightService_3 Test_Rte_DT_TurnLightService_3_IV_1 = InvalidValue_Rte_DT_TurnLightService_3;

  Rte_DT_TurnLightService_4 Test_Rte_DT_TurnLightService_4_IV_1 = InvalidValue_Rte_DT_TurnLightService_4;

  Rte_DT_TurnLightService_5 Test_Rte_DT_TurnLightService_5_IV_1 = InvalidValue_Rte_DT_TurnLightService_5;

  Rte_DT_TurnLightService_6 Test_Rte_DT_TurnLightService_6_IV_1 = InvalidValue_Rte_DT_TurnLightService_6;

  /* Enumeration Data Types */

  ComplexTurnLightONOFFType Test_ComplexTurnLightONOFFType_V_1 = NORQUEST;
  ComplexTurnLightONOFFType Test_ComplexTurnLightONOFFType_V_2 = OFF;
  ComplexTurnLightONOFFType Test_ComplexTurnLightONOFFType_V_3 = ON;

  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_1 = NOREQUEST;
  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_2 = LEFT;
  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_3 = RIGHT;
  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_4 = ALL;
  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_5 = FRONT_LEFT;
  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_6 = MIDDLE_LEFT;
  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_7 = REAR_LEFT;
  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_8 = FRONT_RIGHT;
  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_9 = MIDDLE_RIGHT;
  ComplexTurnLightPositionType Test_ComplexTurnLightPositionType_V_10 = REAR_RIGHT;

  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_1 = NOREQUEST;
  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_2 = LEFT;
  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_3 = RIGHT;
  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_4 = ALL;
  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_5 = FRONT_LEFT;
  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_6 = MIDDLE_LEFT;
  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_7 = REAR_LEFT;
  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_8 = FRONT_RIGHT;
  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_9 = MIDDLE_RIGHT;
  Rte_DT_TurnLightService_0 Test_Rte_DT_TurnLightService_0_V_10 = REAR_RIGHT;

  Rte_DT_TurnLightService_1 Test_Rte_DT_TurnLightService_1_V_1 = NORQUEST;
  Rte_DT_TurnLightService_1 Test_Rte_DT_TurnLightService_1_V_2 = OFF;
  Rte_DT_TurnLightService_1 Test_Rte_DT_TurnLightService_1_V_3 = ON;
}

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
