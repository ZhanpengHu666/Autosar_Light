/*
 * File: TurnLightArb.c
 *
 * Code generated for Simulink model 'TurnLightArb'.
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Sat Aug 10 07:33:58 2024
 */

#include "TurnLightArb.h"
#include "TurnLightArb_private.h"

/* Named constants for Chart: '<S1>/TurnLightOutArb' */
#define TurnLightArb_IN_CheckPriority  ((uint8)1U)
#define TurnLightArb_IN_Idle           ((uint8)2U)
#define TurnLightArb_TLOUT_DOUBLE_ON   ((uint8)2U)
#define TurnLightArb_TLOUT_NORMAL_ON   ((uint8)1U)
#define TurnLightArb_TLOUT_OFF         ((uint8)0U)
#define TurnLightArb_TLOUT_SHORT_ON    ((uint8)3U)

/* Block signals (default storage) */
B_TurnLightArb_T TurnLightArb_B;

/* Block states (default storage) */
DW_TurnLightArb_T TurnLightArb_DW;

/* Forward declaration for local functions */
static void TurnLightArb_JurgeOutputMode(const uint8 *DataTypeConversion, const
  uint8 *DataTypeConversion1);
static void TurnLightArb_CheckPriority_flow(const uint8 *DataTypeConversion,
  const uint8 *DataTypeConversion1);

/* Function for Chart: '<S1>/TurnLightOutArb' */
static void TurnLightArb_JurgeOutputMode(const uint8 *DataTypeConversion, const
  uint8 *DataTypeConversion1)
{
  boolean aVarTruthTableCondition_1;
  boolean aVarTruthTableCondition_10;
  boolean aVarTruthTableCondition_11;
  boolean aVarTruthTableCondition_12;
  boolean aVarTruthTableCondition_13;
  boolean aVarTruthTableCondition_14;
  boolean aVarTruthTableCondition_15;
  boolean aVarTruthTableCondition_3;
  boolean aVarTruthTableCondition_4;
  boolean aVarTruthTableCondition_5;
  boolean aVarTruthTableCondition_6;
  boolean aVarTruthTableCondition_7;
  boolean aVarTruthTableCondition_8;
  boolean aVarTruthTableCondition_9;
  boolean tmp;
  boolean tmp_0;
  aVarTruthTableCondition_1 = *DataTypeConversion == LEFT;
  aVarTruthTableCondition_3 = *DataTypeConversion == ALL;
  aVarTruthTableCondition_4 = *DataTypeConversion == FRONT_LEFT;
  aVarTruthTableCondition_5 = *DataTypeConversion == FRONT_RIGHT;
  aVarTruthTableCondition_6 = *DataTypeConversion == REAR_LEFT;
  aVarTruthTableCondition_7 = *DataTypeConversion == REAR_RIGHT;
  aVarTruthTableCondition_8 = *DataTypeConversion1 == OFF;
  aVarTruthTableCondition_9 = *DataTypeConversion1 == ON;

  /* DataStoreRead: '<S1>/Data Store Read' */
  aVarTruthTableCondition_10 =
    TurnLightArb_DW.TurnLightCtrlCmd.TurnLightDutyCycle == 0;
  aVarTruthTableCondition_11 = TurnLightArb_DW.TurnLightCtrlCmd.TurnLightCycle ==
    8;
  aVarTruthTableCondition_12 = TurnLightArb_DW.TurnLightCtrlCmd.TurnLightCycle ==
    4;
  aVarTruthTableCondition_13 = TurnLightArb_DW.TurnLightCtrlCmd.TurnLightTimes ==
    0;
  aVarTruthTableCondition_14 = TurnLightArb_DW.TurnLightCtrlCmd.TurnLightNumber ==
    0;
  aVarTruthTableCondition_15 = TurnLightArb_DW.TurnLightCtrlCmd.TurnLightNumber ==
    3;
  if (aVarTruthTableCondition_3 && aVarTruthTableCondition_8) {
    /*  'ALL_OFF':  */
    TurnLightArb_B.TurnLight_FL_Out = TurnLightArb_TLOUT_OFF;
    TurnLightArb_B.TurnLight_FR_Out = TurnLightArb_TLOUT_OFF;
    TurnLightArb_B.TurnLight_RL_Out = TurnLightArb_TLOUT_OFF;
    TurnLightArb_B.TurnLight_RR_Out = TurnLightArb_TLOUT_OFF;
  } else if (aVarTruthTableCondition_4 && aVarTruthTableCondition_8) {
    /*  'FL_OFF':  */
    TurnLightArb_B.TurnLight_FL_Out = TurnLightArb_TLOUT_OFF;
  } else if (aVarTruthTableCondition_5 && aVarTruthTableCondition_8) {
    /*  'FR_OFF':  */
    TurnLightArb_B.TurnLight_FR_Out = TurnLightArb_TLOUT_OFF;
  } else if (aVarTruthTableCondition_6 && aVarTruthTableCondition_8) {
    /*  'RL_OFF':  */
    TurnLightArb_B.TurnLight_RL_Out = TurnLightArb_TLOUT_OFF;
  } else if (aVarTruthTableCondition_7 && aVarTruthTableCondition_8) {
    /*  'RR_OFF':  */
    TurnLightArb_B.TurnLight_RR_Out = TurnLightArb_TLOUT_OFF;
  } else {
    aVarTruthTableCondition_8 = !aVarTruthTableCondition_12;
    tmp = !aVarTruthTableCondition_15;
    if (aVarTruthTableCondition_1 && aVarTruthTableCondition_9 &&
        aVarTruthTableCondition_10 && aVarTruthTableCondition_11 &&
        aVarTruthTableCondition_8 && aVarTruthTableCondition_13 &&
        aVarTruthTableCondition_14 && tmp) {
      /*  'LEFT_NORMAL_ON':  */
      TurnLightArb_B.TurnLight_FL_Out = TurnLightArb_TLOUT_NORMAL_ON;
      TurnLightArb_B.TurnLight_RL_Out = TurnLightArb_TLOUT_NORMAL_ON;
    } else {
      tmp_0 = *DataTypeConversion == RIGHT && aVarTruthTableCondition_9 &&
        aVarTruthTableCondition_10 && aVarTruthTableCondition_11 &&
        aVarTruthTableCondition_8 && aVarTruthTableCondition_13;
      if (tmp_0 && aVarTruthTableCondition_14 && tmp) {
        /*  'RIGHT_NORMAL_ON':  */
        TurnLightArb_B.TurnLight_FR_Out = TurnLightArb_TLOUT_NORMAL_ON;
        TurnLightArb_B.TurnLight_RR_Out = TurnLightArb_TLOUT_NORMAL_ON;
      } else if (aVarTruthTableCondition_3 && aVarTruthTableCondition_9 &&
                 aVarTruthTableCondition_10 && aVarTruthTableCondition_11 &&
                 aVarTruthTableCondition_8 && aVarTruthTableCondition_13 &&
                 aVarTruthTableCondition_14 && tmp) {
        /*  'ALL_NORMAL_ON':  */
        TurnLightArb_B.TurnLight_FL_Out = TurnLightArb_TLOUT_NORMAL_ON;
        TurnLightArb_B.TurnLight_RL_Out = TurnLightArb_TLOUT_NORMAL_ON;
        TurnLightArb_B.TurnLight_FR_Out = TurnLightArb_TLOUT_NORMAL_ON;
        TurnLightArb_B.TurnLight_RR_Out = TurnLightArb_TLOUT_NORMAL_ON;
      } else {
        aVarTruthTableCondition_3 = !aVarTruthTableCondition_14;
        if (aVarTruthTableCondition_1 && aVarTruthTableCondition_9 &&
            aVarTruthTableCondition_10 && aVarTruthTableCondition_11 &&
            aVarTruthTableCondition_8 && aVarTruthTableCondition_13 &&
            aVarTruthTableCondition_3 && aVarTruthTableCondition_15) {
          /*  'LEFT_SHORT_ON':  */
          TurnLightArb_B.TurnLight_FL_Out = TurnLightArb_TLOUT_SHORT_ON;
          TurnLightArb_B.TurnLight_RL_Out = TurnLightArb_TLOUT_SHORT_ON;
        } else if (tmp_0 && aVarTruthTableCondition_3 &&
                   aVarTruthTableCondition_15) {
          /*  'RIGHT_SHORT_ON':  */
          TurnLightArb_B.TurnLight_FR_Out = TurnLightArb_TLOUT_SHORT_ON;
          TurnLightArb_B.TurnLight_RR_Out = TurnLightArb_TLOUT_SHORT_ON;
        } else {
          aVarTruthTableCondition_8 = !aVarTruthTableCondition_11;
          if (aVarTruthTableCondition_4 && aVarTruthTableCondition_9 &&
              aVarTruthTableCondition_10 && aVarTruthTableCondition_8 &&
              aVarTruthTableCondition_12 && aVarTruthTableCondition_13 &&
              aVarTruthTableCondition_14 && tmp) {
            /*  'FL_DOUBLE':  */
            TurnLightArb_B.TurnLight_FL_Out = TurnLightArb_TLOUT_DOUBLE_ON;
          } else if (aVarTruthTableCondition_5 && aVarTruthTableCondition_9 &&
                     aVarTruthTableCondition_10 && aVarTruthTableCondition_8 &&
                     aVarTruthTableCondition_12 && aVarTruthTableCondition_13 &&
                     aVarTruthTableCondition_14 && tmp) {
            /*  'FR_DOUBLE':  */
            TurnLightArb_B.TurnLight_FR_Out = TurnLightArb_TLOUT_DOUBLE_ON;
          } else if (aVarTruthTableCondition_6 && aVarTruthTableCondition_9 &&
                     aVarTruthTableCondition_10 && aVarTruthTableCondition_8 &&
                     aVarTruthTableCondition_12 && aVarTruthTableCondition_13 &&
                     aVarTruthTableCondition_14) {
            /*  'RL_DOUBLE':  */
            TurnLightArb_B.TurnLight_RL_Out = TurnLightArb_TLOUT_DOUBLE_ON;
          } else {
            if (aVarTruthTableCondition_7 && aVarTruthTableCondition_9 &&
                aVarTruthTableCondition_10 && aVarTruthTableCondition_8 &&
                aVarTruthTableCondition_12 && aVarTruthTableCondition_13 &&
                aVarTruthTableCondition_14) {
              /*  'RR_DOUBLE':  */
              TurnLightArb_B.TurnLight_RR_Out = TurnLightArb_TLOUT_DOUBLE_ON;
            }
          }
        }
      }
    }
  }
}

/* Function for Chart: '<S1>/TurnLightOutArb' */
static void TurnLightArb_CheckPriority_flow(const uint8 *DataTypeConversion,
  const uint8 *DataTypeConversion1)
{
  /* DataStoreRead: '<S1>/Data Store Read' */
  if (TurnLightArb_DW.TurnLightCtrlCmd.TurnLightPriority >=
      TurnLightArb_DW.CurrentPriority) {
    TurnLightArb_DW.CurrentPriority =
      TurnLightArb_DW.TurnLightCtrlCmd.TurnLightPriority;
    TurnLightArb_DW.IsFunctionCall = false;
    TurnLightArb_JurgeOutputMode(DataTypeConversion, DataTypeConversion1);
  }

  /* End of DataStoreRead: '<S1>/Data Store Read' */
}

/* Model step function for TID1 */
void TurnLightArb_Runnable_10ms(void)  /* Explicit Task: Runnable_10ms */
{
  uint8 DataTypeConversion;
  uint8 DataTypeConversion1;

  /* RootInportFunctionCallGenerator generated from: '<Root>/Runnable_10ms' incorporates:
   *  SubSystem: '<Root>/Runnable_10ms_sys'
   */
  /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
   *  DataStoreRead: '<S1>/Data Store Read'
   */
  DataTypeConversion = TurnLightArb_DW.TurnLightCtrlCmd.TurnLightPosition;

  /* DataTypeConversion: '<S1>/Data Type Conversion1' incorporates:
   *  DataStoreRead: '<S1>/Data Store Read'
   */
  DataTypeConversion1 = TurnLightArb_DW.TurnLightCtrlCmd.TurnLightOnOff;

  /* Chart: '<S1>/TurnLightOutArb' */
  if (TurnLightArb_DW.is_active_c3_TurnLightArb == 0U) {
    TurnLightArb_DW.is_active_c3_TurnLightArb = 1U;
    TurnLightArb_DW.is_c3_TurnLightArb = TurnLightArb_IN_Idle;
  } else if (TurnLightArb_DW.is_c3_TurnLightArb == TurnLightArb_IN_CheckPriority)
  {
    if (!TurnLightArb_DW.IsFunctionCall) {
      TurnLightArb_DW.is_c3_TurnLightArb = TurnLightArb_IN_Idle;
    }
  } else {
    /* case IN_Idle: */
    if (TurnLightArb_DW.IsFunctionCall) {
      TurnLightArb_DW.is_c3_TurnLightArb = TurnLightArb_IN_CheckPriority;
      TurnLightArb_CheckPriority_flow(&DataTypeConversion, &DataTypeConversion1);
    }
  }

  /* End of Chart: '<S1>/TurnLightOutArb' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/Runnable_10ms' */

  /* Outport: '<Root>/TurnLamp_FL_Out_u8_Signal' */
  (void)Rte_Write_TurnLamp_FL_Out_u8_Signal(TurnLightArb_B.TurnLight_FL_Out);

  /* Outport: '<Root>/TurnLamp_RL_Out_u8_Signal' */
  (void)Rte_Write_TurnLamp_RL_Out_u8_Signal(TurnLightArb_B.TurnLight_RL_Out);

  /* Outport: '<Root>/TurnLapm_FR_Out_u8_Signal' */
  (void)Rte_Write_TurnLapm_FR_Out_u8_Signal(TurnLightArb_B.TurnLight_FR_Out);

  /* Outport: '<Root>/TurnLapme_RR_Out_u8_Signal' */
  (void)Rte_Write_TurnLapme_RR_Out_u8_Signal(TurnLightArb_B.TurnLight_RR_Out);
}

/* Output function */
void TurnLightService_TurnLightControl_Operation(const TurnLightService
  *TurnLightCtrlPara)
{
  /* Outputs for Function Call SubSystem: '<S3>/TurnLightService_TurnLightControl_Operation_sys' */
  /* DataStoreWrite: '<S5>/Data Store Write1' incorporates:
   *  Constant: '<S5>/Constant'
   */
  TurnLightArb_DW.IsFunctionCall = true;

  /* SignalConversion generated from: '<S5>/TurnLightCtrlPara' incorporates:
   *  DataStoreWrite: '<S5>/Data Store Write'
   */
  TurnLightArb_DW.TurnLightCtrlCmd = *TurnLightCtrlPara;

  /* End of Outputs for SubSystem: '<S3>/TurnLightService_TurnLightControl_Operation_sys' */
}

/* Model initialize function */
void TurnLightArb_Init(void)
{
  /* SystemInitialize for Outport: '<Root>/TurnLamp_FL_Out_u8_Signal' */
  (void)Rte_Write_TurnLamp_FL_Out_u8_Signal(TurnLightArb_B.TurnLight_FL_Out);

  /* SystemInitialize for Outport: '<Root>/TurnLamp_RL_Out_u8_Signal' */
  (void)Rte_Write_TurnLamp_RL_Out_u8_Signal(TurnLightArb_B.TurnLight_RL_Out);

  /* SystemInitialize for Outport: '<Root>/TurnLapm_FR_Out_u8_Signal' */
  (void)Rte_Write_TurnLapm_FR_Out_u8_Signal(TurnLightArb_B.TurnLight_FR_Out);

  /* SystemInitialize for Outport: '<Root>/TurnLapme_RR_Out_u8_Signal' */
  (void)Rte_Write_TurnLapme_RR_Out_u8_Signal(TurnLightArb_B.TurnLight_RR_Out);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
