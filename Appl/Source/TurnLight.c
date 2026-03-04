/*
 * File: TurnLight.c
 *
 * Code generated for Simulink model 'TurnLight'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Sat Aug 10 08:20:22 2024
 *
 * Target selection: autosar.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TurnLight.h"
#include "TurnLight_private.h"

/* Named constants for Chart: '<S2>/HazardCtrlLogic' */
#define TurnLight_IN_NO_ACTIVE_CHILD   ((uint8)0U)
#define TurnLight_IN_OFF               ((uint8)1U)
#define TurnLight_IN_ON_Crash          ((uint8)2U)
#define TurnLight_IN_ON_SW             ((uint8)3U)
#define TurnLight_IN_On_EmergencyBrake ((uint8)4U)

/* Named constants for Chart: '<S2>/TurnLightCtrlLogic' */
#define TurnLight_IN_Check1            ((uint8)1U)
#define TurnLight_IN_Check2            ((uint8)2U)
#define TurnLight_IN_IDLE              ((uint8)1U)
#define TurnLight_IN_LEFT              ((uint8)2U)
#define TurnLight_IN_LongFlash         ((uint8)3U)
#define TurnLight_IN_RIGHT             ((uint8)3U)
#define TurnLight_IN_ShortFlash        ((uint8)4U)

/* Named constants for Chart: '<S2>/TurnLightDiag' */
#define TurnLight_IN_OPEN              ((uint8)2U)
#define TurnLight_IN_SHORT             ((uint8)3U)

/* Named constants for Chart: '<S2>/TurnLightSelector' */
#define TurnLight_IN_ALLOFF            ((uint8)1U)
#define TurnLight_IN_ALLON             ((uint8)2U)
#define TurnLight_IN_LEFTON            ((uint8)3U)
#define TurnLight_IN_RIGHTON           ((uint8)4U)

/* Block signals (default storage) */
B_TurnLight_T TurnLight_B;

/* Block states (default storage) */
DW_TurnLight_T TurnLight_DW;

/* Forward declaration for local functions */
static void TurnLigh_DecideRightLongOrShort(void);
static void TurnLight_DecideLeftLongOrShort(void);

/* Output and update for function-call system: '<S2>/TurnLight_ALLOFF' */
void TurnLight_TurnLight_ALLOFF(void)
{
  TurnLightService rtb_BusCreator_le;

  /* BusCreator: '<S7>/Bus Creator' incorporates:
   *  Constant: '<S7>/Constant'
   *  Constant: '<S7>/Constant1'
   *  Constant: '<S7>/Constant2'
   *  Constant: '<S7>/Constant3'
   *  Constant: '<S7>/Constant4'
   *  Constant: '<S7>/Constant5'
   *  Constant: '<S7>/Constant6'
   */
  rtb_BusCreator_le.TurnLightPosition = ALL;
  rtb_BusCreator_le.TurnLightOnOff = OFF;
  rtb_BusCreator_le.TurnLightDutyCycle = 0U;
  rtb_BusCreator_le.TurnLightCycle = 8U;
  rtb_BusCreator_le.TurnLightTimes = 0U;
  rtb_BusCreator_le.TurnLightNumber = 0U;
  rtb_BusCreator_le.TurnLightPriority = 3U;

  /* FunctionCaller: '<S7>/TurnLightService_TurnLightControl_Operation' incorporates:
   *  BusCreator: '<S7>/Bus Creator'
   */
  Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator_le);
}

/* Output and update for function-call system: '<S2>/TurnLight_ALLON' */
void TurnLight_TurnLight_ALLON(void)
{
  TurnLightService rtb_BusCreator_oj;

  /* BusCreator: '<S8>/Bus Creator' incorporates:
   *  Constant: '<S8>/Constant'
   *  Constant: '<S8>/Constant1'
   *  Constant: '<S8>/Constant2'
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant4'
   *  Constant: '<S8>/Constant5'
   *  Constant: '<S8>/Constant6'
   */
  rtb_BusCreator_oj.TurnLightPosition = ALL;
  rtb_BusCreator_oj.TurnLightOnOff = ON;
  rtb_BusCreator_oj.TurnLightDutyCycle = 0U;
  rtb_BusCreator_oj.TurnLightCycle = 8U;
  rtb_BusCreator_oj.TurnLightTimes = 0U;
  rtb_BusCreator_oj.TurnLightNumber = 0U;
  rtb_BusCreator_oj.TurnLightPriority = 3U;

  /* FunctionCaller: '<S8>/TurnLightService_TurnLightControl_Operation' incorporates:
   *  BusCreator: '<S8>/Bus Creator'
   */
  Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator_oj);
}

/* Function for Chart: '<S2>/TurnLightSelector' */
static void TurnLigh_DecideRightLongOrShort(void)
{
  TurnLightService rtb_BusCreator;

  /*  决策闪烁模式  */
  if (TurnLight_B.TurnLampSWMode == 1) {
    /* Outputs for Function Call SubSystem: '<S2>/TurnLight_RightShort' */
    /* BusCreator: '<S20>/Bus Creator' incorporates:
     *  Constant: '<S20>/Constant'
     *  Constant: '<S20>/Constant1'
     *  Constant: '<S20>/Constant2'
     *  Constant: '<S20>/Constant3'
     *  Constant: '<S20>/Constant4'
     *  Constant: '<S20>/Constant5'
     *  Constant: '<S20>/Constant6'
     */
    rtb_BusCreator.TurnLightPosition = RIGHT;
    rtb_BusCreator.TurnLightOnOff = ON;
    rtb_BusCreator.TurnLightDutyCycle = 0U;
    rtb_BusCreator.TurnLightCycle = 8U;
    rtb_BusCreator.TurnLightTimes = 0U;
    rtb_BusCreator.TurnLightNumber = 3U;
    rtb_BusCreator.TurnLightPriority = 3U;

    /* FunctionCaller: '<S20>/TurnLightService_TurnLightControl_Operation' incorporates:
     *  BusCreator: '<S20>/Bus Creator'
     */
    Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

    /* End of Outputs for SubSystem: '<S2>/TurnLight_RightShort' */
    TurnLight_B.TurnLight_Decide = RIGHTSHORT;
  } else {
    /* Outputs for Function Call SubSystem: '<S2>/TurnLight_LeftLong1' */
    /* BusCreator: '<S14>/Bus Creator' incorporates:
     *  Constant: '<S14>/Constant'
     *  Constant: '<S14>/Constant1'
     *  Constant: '<S14>/Constant2'
     *  Constant: '<S14>/Constant3'
     *  Constant: '<S14>/Constant4'
     *  Constant: '<S14>/Constant5'
     *  Constant: '<S14>/Constant6'
     */
    rtb_BusCreator.TurnLightPosition = RIGHT;
    rtb_BusCreator.TurnLightOnOff = ON;
    rtb_BusCreator.TurnLightDutyCycle = 0U;
    rtb_BusCreator.TurnLightCycle = 8U;
    rtb_BusCreator.TurnLightTimes = 0U;
    rtb_BusCreator.TurnLightNumber = 0U;
    rtb_BusCreator.TurnLightPriority = 3U;

    /* FunctionCaller: '<S14>/TurnLightService_TurnLightControl_Operation' incorporates:
     *  BusCreator: '<S14>/Bus Creator'
     */
    Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

    /* End of Outputs for SubSystem: '<S2>/TurnLight_LeftLong1' */
    TurnLight_B.TurnLight_Decide = RIGHTLONG;
  }
}

/* Function for Chart: '<S2>/TurnLightSelector' */
static void TurnLight_DecideLeftLongOrShort(void)
{
  TurnLightService rtb_BusCreator_ak;

  /*  决策闪烁模式  */
  if (TurnLight_B.TurnLampSWMode == 1) {
    /* Outputs for Function Call SubSystem: '<S2>/TurnLight_LeftShort' */
    /* BusCreator: '<S15>/Bus Creator' incorporates:
     *  Constant: '<S15>/Constant'
     *  Constant: '<S15>/Constant1'
     *  Constant: '<S15>/Constant2'
     *  Constant: '<S15>/Constant3'
     *  Constant: '<S15>/Constant4'
     *  Constant: '<S15>/Constant5'
     *  Constant: '<S15>/Constant6'
     */
    rtb_BusCreator_ak.TurnLightPosition = LEFT;
    rtb_BusCreator_ak.TurnLightOnOff = ON;
    rtb_BusCreator_ak.TurnLightDutyCycle = 0U;
    rtb_BusCreator_ak.TurnLightCycle = 8U;
    rtb_BusCreator_ak.TurnLightTimes = 0U;
    rtb_BusCreator_ak.TurnLightNumber = 3U;
    rtb_BusCreator_ak.TurnLightPriority = 3U;

    /* FunctionCaller: '<S15>/TurnLightService_TurnLightControl_Operation' incorporates:
     *  BusCreator: '<S15>/Bus Creator'
     */
    Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator_ak);

    /* End of Outputs for SubSystem: '<S2>/TurnLight_LeftShort' */
    TurnLight_B.TurnLight_Decide = LEFTSHORT;
  } else {
    /* Outputs for Function Call SubSystem: '<S2>/TurnLight_LeftLong' */
    /* BusCreator: '<S13>/Bus Creator' incorporates:
     *  Constant: '<S13>/Constant'
     *  Constant: '<S13>/Constant1'
     *  Constant: '<S13>/Constant2'
     *  Constant: '<S13>/Constant3'
     *  Constant: '<S13>/Constant4'
     *  Constant: '<S13>/Constant5'
     *  Constant: '<S13>/Constant6'
     */
    rtb_BusCreator_ak.TurnLightPosition = LEFT;
    rtb_BusCreator_ak.TurnLightOnOff = ON;
    rtb_BusCreator_ak.TurnLightDutyCycle = 0U;
    rtb_BusCreator_ak.TurnLightCycle = 8U;
    rtb_BusCreator_ak.TurnLightTimes = 0U;
    rtb_BusCreator_ak.TurnLightNumber = 0U;
    rtb_BusCreator_ak.TurnLightPriority = 3U;

    /* FunctionCaller: '<S13>/TurnLightService_TurnLightControl_Operation' incorporates:
     *  BusCreator: '<S13>/Bus Creator'
     */
    Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator_ak);

    /* End of Outputs for SubSystem: '<S2>/TurnLight_LeftLong' */
    TurnLight_B.TurnLight_Decide = LEFTLONG;
  }
}

/* Model step function for TID1 */
void TurnLight_Runnable_10ms(void)  /* Explicit Task: TurnLight_Runnable_10ms */
{
  TurnLightService rtb_BusCreator;
  sint32 tmp;
  uint16 tmpRead_a;
  uint8 HazardRqst;
  uint8 tmpRead;
  uint8 tmpRead_0;
  uint8 tmpRead_1;
  uint8 tmpRead_2;
  uint8 tmpRead_3;
  uint8 tmpRead_4;
  uint8 tmpRead_5;
  uint8 tmpRead_6;
  uint8 tmpRead_7;
  uint8 tmpRead_8;
  uint8 tmpRead_9;
  uint8 tmpRead_b;
  boolean guard1 = false;
  boolean guard2 = false;

  /* Inport: '<Root>/HazardSw_u8_Signal' */
  (void)Rte_Read_HazardSw_u8_Signal(&HazardRqst);

  /* Inport: '<Root>/EmergencyBrakeLight_u8_Signal' */
  (void)Rte_Read_EmergencyBrakeLight_u8_Signal(&tmpRead_1);

  /* Inport: '<Root>/CrashIntensity_u8_Signal' */
  (void)Rte_Read_CrashIntensity_u8_Signal(&tmpRead_0);

  /* RootInportFunctionCallGenerator generated from: '<Root>/TurnLight_Runnable_10ms' incorporates:
   *  SubSystem: '<Root>/TurnLight_Runnable_10ms_sys'
   */
  /* Chart: '<S2>/TurnLightCtrlLogic' incorporates:
   *  Inport: '<Root>/CountSignal_Left_u8_Signal'
   *  Inport: '<Root>/IGN_Status_u8_signal'
   *  Inport: '<Root>/TurnLampSw_u8_Signal'
   */
  if (TurnLight_DW.is_active_c3_TurnLight == 0U) {
    TurnLight_DW.is_active_c3_TurnLight = 1U;
    TurnLight_DW.is_c3_TurnLight = TurnLight_IN_IDLE;
    TurnLight_B.TurnLampSWMode = 0U;
    TurnLight_B.TurnLampSWRst = 0U;
    TurnLight_DW.TurnLapmCount = 0U;
  } else {
    (void)Rte_Read_CountSignal_Left_u8_Signal(&tmpRead);
    (void)Rte_Read_IGN_Status_u8_signal(&tmpRead_2);
    (void)Rte_Read_TurnLampSw_u8_Signal(&tmpRead_9);
    switch (TurnLight_DW.is_c3_TurnLight) {
     case TurnLight_IN_IDLE:
      TurnLight_B.TurnLampSWMode = 0U;
      TurnLight_B.TurnLampSWRst = 0U;
      if (((tmpRead_2 == 2) || (tmpRead_2 == 3)) && (tmpRead_9 == 1)) {
        TurnLight_DW.is_c3_TurnLight = TurnLight_IN_LEFT;
        TurnLight_DW.is_LEFT = TurnLight_IN_Check1;
        tmp = TurnLight_DW.TurnLapmCount + 1;
        if (TurnLight_DW.TurnLapmCount + 1 > 255) {
          tmp = 255;
        }

        TurnLight_DW.TurnLapmCount = (uint8)tmp;
      } else {
        if (((tmpRead_2 == 2) || (tmpRead_2 == 3)) && (tmpRead_9 == 2)) {
          TurnLight_DW.is_c3_TurnLight = TurnLight_IN_RIGHT;
          TurnLight_DW.is_RIGHT = TurnLight_IN_Check1;
          tmp = TurnLight_DW.TurnLapmCount + 1;
          if (TurnLight_DW.TurnLapmCount + 1 > 255) {
            tmp = 255;
          }

          TurnLight_DW.TurnLapmCount = (uint8)tmp;
        }
      }
      break;

     case TurnLight_IN_LEFT:
      switch (TurnLight_DW.is_LEFT) {
       case TurnLight_IN_Check1:
        if (tmpRead_9 != 1) {
          TurnLight_DW.is_LEFT = TurnLight_IN_NO_ACTIVE_CHILD;
          TurnLight_DW.is_c3_TurnLight = TurnLight_IN_IDLE;
          TurnLight_B.TurnLampSWMode = 0U;
          TurnLight_B.TurnLampSWRst = 0U;
          TurnLight_DW.TurnLapmCount = 0U;
        } else if (TurnLight_DW.TurnLapmCount > 10) {
          TurnLight_DW.is_LEFT = TurnLight_IN_Check2;
          TurnLight_B.TurnLampSWRst = 1U;
        } else {
          tmp = TurnLight_DW.TurnLapmCount + 1;
          if (TurnLight_DW.TurnLapmCount + 1 > 255) {
            tmp = 255;
          }

          TurnLight_DW.TurnLapmCount = (uint8)tmp;
        }
        break;

       case TurnLight_IN_Check2:
        TurnLight_B.TurnLampSWRst = 1U;
        if ((TurnLight_DW.TurnLapmCount <= 70) && (tmpRead_9 == 0)) {
          TurnLight_DW.is_LEFT = TurnLight_IN_ShortFlash;
          TurnLight_B.TurnLampSWMode = 1U;
        } else if ((TurnLight_DW.TurnLapmCount > 70) && (tmpRead_9 == 1)) {
          TurnLight_DW.is_LEFT = TurnLight_IN_LongFlash;
          TurnLight_B.TurnLampSWMode = 2U;
        } else {
          tmp = TurnLight_DW.TurnLapmCount + 1;
          if (TurnLight_DW.TurnLapmCount + 1 > 255) {
            tmp = 255;
          }

          TurnLight_DW.TurnLapmCount = (uint8)tmp;
        }
        break;

       case TurnLight_IN_LongFlash:
        TurnLight_B.TurnLampSWMode = 2U;
        if ((tmpRead_9 == 0) || (tmpRead_2 == 0)) {
          TurnLight_DW.is_LEFT = TurnLight_IN_NO_ACTIVE_CHILD;
          TurnLight_DW.is_c3_TurnLight = TurnLight_IN_IDLE;
          TurnLight_B.TurnLampSWMode = 0U;
          TurnLight_B.TurnLampSWRst = 0U;
          TurnLight_DW.TurnLapmCount = 0U;
        }
        break;

       default:
        /* case IN_ShortFlash: */
        TurnLight_B.TurnLampSWMode = 1U;
        if (tmpRead == 3) {
          TurnLight_DW.is_LEFT = TurnLight_IN_NO_ACTIVE_CHILD;
          TurnLight_DW.is_c3_TurnLight = TurnLight_IN_IDLE;
          TurnLight_B.TurnLampSWMode = 0U;
          TurnLight_B.TurnLampSWRst = 0U;
          TurnLight_DW.TurnLapmCount = 0U;
        }
        break;
      }
      break;

     default:
      /* case IN_RIGHT: */
      switch (TurnLight_DW.is_RIGHT) {
       case TurnLight_IN_Check1:
        if (tmpRead_9 != 2) {
          TurnLight_DW.is_RIGHT = TurnLight_IN_NO_ACTIVE_CHILD;
          TurnLight_DW.is_c3_TurnLight = TurnLight_IN_IDLE;
          TurnLight_B.TurnLampSWMode = 0U;
          TurnLight_B.TurnLampSWRst = 0U;
          TurnLight_DW.TurnLapmCount = 0U;
        } else if (TurnLight_DW.TurnLapmCount > 10) {
          TurnLight_DW.is_RIGHT = TurnLight_IN_Check2;
          TurnLight_B.TurnLampSWRst = 2U;
        } else {
          tmp = TurnLight_DW.TurnLapmCount + 1;
          if (TurnLight_DW.TurnLapmCount + 1 > 255) {
            tmp = 255;
          }

          TurnLight_DW.TurnLapmCount = (uint8)tmp;
        }
        break;

       case TurnLight_IN_Check2:
        TurnLight_B.TurnLampSWRst = 2U;
        if ((TurnLight_DW.TurnLapmCount <= 70) && (tmpRead_9 == 0)) {
          TurnLight_DW.is_RIGHT = TurnLight_IN_ShortFlash;
          TurnLight_B.TurnLampSWMode = 1U;
        } else if ((TurnLight_DW.TurnLapmCount > 70) && (tmpRead_9 == 2)) {
          TurnLight_DW.is_RIGHT = TurnLight_IN_LongFlash;
          TurnLight_B.TurnLampSWMode = 2U;
        } else {
          tmp = TurnLight_DW.TurnLapmCount + 1;
          if (TurnLight_DW.TurnLapmCount + 1 > 255) {
            tmp = 255;
          }

          TurnLight_DW.TurnLapmCount = (uint8)tmp;
        }
        break;

       case TurnLight_IN_LongFlash:
        TurnLight_B.TurnLampSWMode = 2U;
        if ((tmpRead_9 == 0) || (tmpRead_2 == 0)) {
          TurnLight_DW.is_RIGHT = TurnLight_IN_NO_ACTIVE_CHILD;
          TurnLight_DW.is_c3_TurnLight = TurnLight_IN_IDLE;
          TurnLight_B.TurnLampSWMode = 0U;
          TurnLight_B.TurnLampSWRst = 0U;
          TurnLight_DW.TurnLapmCount = 0U;
        }
        break;

       default:
        /* case IN_ShortFlash: */
        TurnLight_B.TurnLampSWMode = 1U;
        if (tmpRead == 3) {
          TurnLight_DW.is_RIGHT = TurnLight_IN_NO_ACTIVE_CHILD;
          TurnLight_DW.is_c3_TurnLight = TurnLight_IN_IDLE;
          TurnLight_B.TurnLampSWMode = 0U;
          TurnLight_B.TurnLampSWRst = 0U;
          TurnLight_DW.TurnLapmCount = 0U;
        }
        break;
      }
      break;
    }
  }

  /* End of Chart: '<S2>/TurnLightCtrlLogic' */

  /* Chart: '<S2>/HazardCtrlLogic' incorporates:
   *  Inport: '<Root>/VehicleSpeed_Valid_u8_Signal'
   *  Inport: '<Root>/VehicleSpeed_u16_signal'
   */
  if (TurnLight_DW.temporalCounter_i1 < 131071U) {
    TurnLight_DW.temporalCounter_i1++;
  }

  TurnLight_DW.CrashIntensity_prev = TurnLight_DW.CrashIntensity_start;
  TurnLight_DW.CrashIntensity_start = tmpRead_0;
  TurnLight_DW.HazardSw_prev = TurnLight_DW.HazardSw_start;
  TurnLight_DW.HazardSw_start = HazardRqst;
  TurnLight_DW.EmergencyBrakeLight_prev = TurnLight_DW.EmergencyBrakeLight_start;
  TurnLight_DW.EmergencyBrakeLight_start = tmpRead_1;
  if (TurnLight_DW.is_active_c1_TurnLight == 0U) {
    TurnLight_DW.CrashIntensity_prev = tmpRead_0;
    TurnLight_DW.HazardSw_prev = HazardRqst;
    TurnLight_DW.EmergencyBrakeLight_prev = tmpRead_1;
    TurnLight_DW.is_active_c1_TurnLight = 1U;
    TurnLight_DW.is_c1_TurnLight = TurnLight_IN_OFF;
    HazardRqst = 0U;
  } else {
    switch (TurnLight_DW.is_c1_TurnLight) {
     case TurnLight_IN_OFF:
      HazardRqst = 0U;
      if ((TurnLight_DW.CrashIntensity_prev != TurnLight_DW.CrashIntensity_start)
          && (TurnLight_DW.CrashIntensity_prev == 0)) {
        TurnLight_DW.is_c1_TurnLight = TurnLight_IN_ON_Crash;
        TurnLight_DW.temporalCounter_i1 = 0U;
        HazardRqst = 1U;
      } else if ((TurnLight_DW.EmergencyBrakeLight_prev !=
                  TurnLight_DW.EmergencyBrakeLight_start) &&
                 (TurnLight_DW.EmergencyBrakeLight_start == 1)) {
        TurnLight_DW.is_c1_TurnLight = TurnLight_IN_On_EmergencyBrake;
        HazardRqst = 1U;
      } else {
        if ((TurnLight_DW.HazardSw_prev != TurnLight_DW.HazardSw_start) &&
            (TurnLight_DW.HazardSw_start == 1)) {
          TurnLight_DW.is_c1_TurnLight = TurnLight_IN_ON_SW;
          HazardRqst = 1U;
        }
      }
      break;

     case TurnLight_IN_ON_Crash:
      HazardRqst = 1U;
      if (((tmpRead_0 != 0) && (TurnLight_DW.temporalCounter_i1 >= 500U) &&
           ((TurnLight_DW.HazardSw_prev != TurnLight_DW.HazardSw_start) &&
            (TurnLight_DW.HazardSw_start == 1))) || ((tmpRead_0 != 0) &&
           (TurnLight_DW.temporalCounter_i1 >= 90000U))) {
        TurnLight_DW.is_c1_TurnLight = TurnLight_IN_OFF;
        HazardRqst = 0U;
      }
      break;

     case TurnLight_IN_ON_SW:
      HazardRqst = 1U;
      if ((TurnLight_DW.HazardSw_prev != TurnLight_DW.HazardSw_start) &&
          (TurnLight_DW.HazardSw_start == 1)) {
        TurnLight_DW.is_c1_TurnLight = TurnLight_IN_OFF;
        HazardRqst = 0U;
      }
      break;

     default:
      /* case IN_On_EmergencyBrake: */
      HazardRqst = 1U;
      (void)Rte_Read_VehicleSpeed_u16_signal(&tmpRead_a);
      (void)Rte_Read_VehicleSpeed_Valid_u8_Signal(&tmpRead_b);
      if (((tmpRead_1 == 1) && ((TurnLight_DW.HazardSw_prev !=
             TurnLight_DW.HazardSw_start) && (TurnLight_DW.HazardSw_start == 1)))
          || ((tmpRead_1 == 1) && (tmpRead_a > 15) && (tmpRead_b == 1))) {
        TurnLight_DW.is_c1_TurnLight = TurnLight_IN_OFF;
        HazardRqst = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<S2>/HazardCtrlLogic' */

  /* Chart: '<S2>/TurnLightSelector' */
  TurnLight_DW.HazardLightRqst_prev = TurnLight_DW.HazardLightRqst_start;
  TurnLight_DW.HazardLightRqst_start = HazardRqst;
  TurnLight_DW.TurnLightSwRqst_prev = TurnLight_DW.TurnLightSwRqst_start;
  TurnLight_DW.TurnLightSwRqst_start = TurnLight_B.TurnLampSWRst;
  if (TurnLight_DW.is_active_c2_TurnLight == 0U) {
    TurnLight_DW.HazardLightRqst_prev = HazardRqst;
    TurnLight_DW.TurnLightSwRqst_prev = TurnLight_B.TurnLampSWRst;
    TurnLight_DW.is_active_c2_TurnLight = 1U;
    TurnLight_DW.is_c2_TurnLight = TurnLight_IN_ALLOFF;

    /* Outputs for Function Call SubSystem: '<S2>/TurnLight_ALLOFF' */
    TurnLight_TurnLight_ALLOFF();

    /* End of Outputs for SubSystem: '<S2>/TurnLight_ALLOFF' */
    TurnLight_B.TurnLight_Decide = ALLOFF;
  } else {
    guard1 = false;
    guard2 = false;
    switch (TurnLight_DW.is_c2_TurnLight) {
     case TurnLight_IN_ALLOFF:
      if (TurnLight_B.TurnLampSWRst == 1) {
        TurnLight_DW.is_c2_TurnLight = TurnLight_IN_LEFTON;
        TurnLight_DW.LeftRetry = 0U;
        TurnLight_DecideLeftLongOrShort();
      } else if (TurnLight_B.TurnLampSWRst == 2) {
        TurnLight_DW.is_c2_TurnLight = TurnLight_IN_RIGHTON;
        TurnLight_DW.RightRetry = 0U;
        TurnLigh_DecideRightLongOrShort();
      } else {
        if (HazardRqst == 1) {
          TurnLight_DW.is_c2_TurnLight = TurnLight_IN_ALLON;

          /* Outputs for Function Call SubSystem: '<S2>/TurnLight_ALLON' */
          TurnLight_TurnLight_ALLON();

          /* End of Outputs for SubSystem: '<S2>/TurnLight_ALLON' */
          TurnLight_B.TurnLight_Decide = ALLON;
        }
      }
      break;

     case TurnLight_IN_ALLON:
      if ((HazardRqst == 1) && ((TurnLight_DW.TurnLightSwRqst_prev !=
            TurnLight_DW.TurnLightSwRqst_start) &&
           (TurnLight_DW.TurnLightSwRqst_start == 2))) {
        guard1 = true;
      } else if ((HazardRqst == 1) && ((TurnLight_DW.TurnLightSwRqst_prev !=
                   TurnLight_DW.TurnLightSwRqst_start) &&
                  (TurnLight_DW.TurnLightSwRqst_start == 1))) {
        guard2 = true;
      } else if ((TurnLight_B.TurnLampSWRst == 2) &&
                 ((TurnLight_DW.HazardLightRqst_prev !=
                   TurnLight_DW.HazardLightRqst_start) &&
                  (TurnLight_DW.HazardLightRqst_start == 0))) {
        guard1 = true;
      } else if ((TurnLight_B.TurnLampSWRst == 1) &&
                 ((TurnLight_DW.HazardLightRqst_prev !=
                   TurnLight_DW.HazardLightRqst_start) &&
                  (TurnLight_DW.HazardLightRqst_start == 0))) {
        guard2 = true;
      } else {
        if (HazardRqst == 0) {
          TurnLight_DW.is_c2_TurnLight = TurnLight_IN_ALLOFF;

          /* Outputs for Function Call SubSystem: '<S2>/TurnLight_ALLOFF' */
          TurnLight_TurnLight_ALLOFF();

          /* End of Outputs for SubSystem: '<S2>/TurnLight_ALLOFF' */
          TurnLight_B.TurnLight_Decide = ALLOFF;
        }
      }
      break;

     case TurnLight_IN_LEFTON:
      if (((TurnLight_B.TurnLampSWRst == 1) &&
           ((TurnLight_DW.HazardLightRqst_prev !=
             TurnLight_DW.HazardLightRqst_start) &&
            (TurnLight_DW.HazardLightRqst_start == 1))) || ((HazardRqst == 1) &&
           ((TurnLight_DW.TurnLightSwRqst_prev !=
             TurnLight_DW.TurnLightSwRqst_start) &&
            (TurnLight_DW.TurnLightSwRqst_prev == 1)))) {
        TurnLight_DW.is_c2_TurnLight = TurnLight_IN_ALLON;

        /* Outputs for Function Call SubSystem: '<S2>/TurnLight_ALLON' */
        TurnLight_TurnLight_ALLON();

        /* End of Outputs for SubSystem: '<S2>/TurnLight_ALLON' */
        TurnLight_B.TurnLight_Decide = ALLON;
      } else if (TurnLight_B.TurnLampSWRst == 0) {
        TurnLight_DW.is_c2_TurnLight = TurnLight_IN_ALLOFF;

        /* Outputs for Function Call SubSystem: '<S2>/TurnLight_ALLOFF' */
        TurnLight_TurnLight_ALLOFF();

        /* End of Outputs for SubSystem: '<S2>/TurnLight_ALLOFF' */
        TurnLight_B.TurnLight_Decide = ALLOFF;
      } else {
        if (TurnLight_DW.LeftRetry == 1) {
          TurnLight_DW.is_c2_TurnLight = TurnLight_IN_LEFTON;
          TurnLight_DW.LeftRetry = 0U;
          TurnLight_DecideLeftLongOrShort();
        }
      }
      break;

     default:
      /* case IN_RIGHTON: */
      if (((TurnLight_B.TurnLampSWRst == 2) &&
           ((TurnLight_DW.HazardLightRqst_prev !=
             TurnLight_DW.HazardLightRqst_start) &&
            (TurnLight_DW.HazardLightRqst_start == 1))) || ((HazardRqst == 1) &&
           ((TurnLight_DW.TurnLightSwRqst_prev !=
             TurnLight_DW.TurnLightSwRqst_start) &&
            (TurnLight_DW.TurnLightSwRqst_prev == 2)))) {
        TurnLight_DW.is_c2_TurnLight = TurnLight_IN_ALLON;

        /* Outputs for Function Call SubSystem: '<S2>/TurnLight_ALLON' */
        TurnLight_TurnLight_ALLON();

        /* End of Outputs for SubSystem: '<S2>/TurnLight_ALLON' */
        TurnLight_B.TurnLight_Decide = ALLON;
      } else if (TurnLight_B.TurnLampSWRst == 0) {
        TurnLight_DW.is_c2_TurnLight = TurnLight_IN_ALLOFF;

        /* Outputs for Function Call SubSystem: '<S2>/TurnLight_ALLOFF' */
        TurnLight_TurnLight_ALLOFF();

        /* End of Outputs for SubSystem: '<S2>/TurnLight_ALLOFF' */
        TurnLight_B.TurnLight_Decide = ALLOFF;
      } else {
        if (TurnLight_DW.RightRetry == 1) {
          TurnLight_DW.is_c2_TurnLight = TurnLight_IN_RIGHTON;
          TurnLight_DW.RightRetry = 0U;
          TurnLigh_DecideRightLongOrShort();
        }
      }
      break;
    }

    if (guard2) {
      TurnLight_DW.is_c2_TurnLight = TurnLight_IN_LEFTON;
      TurnLight_DW.LeftRetry = 0U;
      TurnLight_DecideLeftLongOrShort();
    }

    if (guard1) {
      TurnLight_DW.is_c2_TurnLight = TurnLight_IN_RIGHTON;
      TurnLight_DW.RightRetry = 0U;
      TurnLigh_DecideRightLongOrShort();
    }
  }

  /* End of Chart: '<S2>/TurnLightSelector' */

  /* Chart: '<S2>/TurnLightDiag' incorporates:
   *  Inport: '<Root>/TurnLampCtrlCmd_FL_u8_signal'
   *  Inport: '<Root>/TurnLampCtrlCmd_FR_u8_signa'
   *  Inport: '<Root>/TurnLampCtrlCmd_RL_u8_signal'
   *  Inport: '<Root>/TurnLampFb_FL_u8_Signal'
   *  Inport: '<Root>/TurnLampFb_FR_u8_Signal'
   *  Inport: '<Root>/TurnLampFb_RL_u8_Signal'
   */
  if (TurnLight_DW.is_active_c4_TurnLight == 0U) {
    TurnLight_DW.is_active_c4_TurnLight = 1U;
    TurnLight_DW.is_FLDIAG = TurnLight_IN_IDLE;
    TurnLight_DW.is_FRDIAG = TurnLight_IN_IDLE;
    TurnLight_DW.is_RLDIAG = TurnLight_IN_IDLE;
    TurnLight_DW.is_RRDIAG = TurnLight_IN_IDLE;
  } else {
    (void)Rte_Read_TurnLampFb_FL_u8_Signal(&tmpRead_6);
    (void)Rte_Read_TurnLampCtrlCmd_FL_u8_signal(&tmpRead_3);
    switch (TurnLight_DW.is_FLDIAG) {
     case TurnLight_IN_IDLE:
      if ((tmpRead_6 == 1) && (tmpRead_3 == 1)) {
        TurnLight_DW.is_FLDIAG = TurnLight_IN_SHORT;

        /* Outputs for Function Call SubSystem: '<S2>/TurnLight_FLOFF_Short' */
        /* BusCreator: '<S10>/Bus Creator' incorporates:
         *  Constant: '<S10>/Constant'
         *  Constant: '<S10>/Constant1'
         *  Constant: '<S10>/Constant2'
         *  Constant: '<S10>/Constant3'
         *  Constant: '<S10>/Constant4'
         *  Constant: '<S10>/Constant5'
         *  Constant: '<S10>/Constant6'
         */
        rtb_BusCreator.TurnLightPosition = FRONT_LEFT;
        rtb_BusCreator.TurnLightOnOff = OFF;
        rtb_BusCreator.TurnLightDutyCycle = 0U;
        rtb_BusCreator.TurnLightCycle = 0U;
        rtb_BusCreator.TurnLightTimes = 0U;
        rtb_BusCreator.TurnLightNumber = 0U;
        rtb_BusCreator.TurnLightPriority = 2U;

        /* FunctionCaller: '<S10>/TurnLightService_TurnLightControl_Operation' incorporates:
         *  BusCreator: '<S10>/Bus Creator'
         */
        Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

        /* End of Outputs for SubSystem: '<S2>/TurnLight_FLOFF_Short' */
      } else {
        if ((tmpRead_6 == 2) && (tmpRead_3 == 1)) {
          TurnLight_DW.is_FLDIAG = TurnLight_IN_OPEN;

          /* Outputs for Function Call SubSystem: '<S2>/TurnLight_FLDouble_Open' */
          /* BusCreator: '<S9>/Bus Creator' incorporates:
           *  Constant: '<S9>/Constant'
           *  Constant: '<S9>/Constant1'
           *  Constant: '<S9>/Constant2'
           *  Constant: '<S9>/Constant3'
           *  Constant: '<S9>/Constant4'
           *  Constant: '<S9>/Constant5'
           *  Constant: '<S9>/Constant6'
           */
          rtb_BusCreator.TurnLightPosition = FRONT_LEFT;
          rtb_BusCreator.TurnLightOnOff = ON;
          rtb_BusCreator.TurnLightDutyCycle = 0U;
          rtb_BusCreator.TurnLightCycle = 4U;
          rtb_BusCreator.TurnLightTimes = 0U;
          rtb_BusCreator.TurnLightNumber = 0U;
          rtb_BusCreator.TurnLightPriority = 2U;

          /* FunctionCaller: '<S9>/TurnLightService_TurnLightControl_Operation' incorporates:
           *  BusCreator: '<S9>/Bus Creator'
           */
          Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

          /* End of Outputs for SubSystem: '<S2>/TurnLight_FLDouble_Open' */
        }
      }
      break;

     case TurnLight_IN_OPEN:
      if (tmpRead_6 == 0) {
        TurnLight_DW.LeftRetry = 1U;
        TurnLight_DW.is_FLDIAG = TurnLight_IN_IDLE;
      }
      break;

     default:
      /* case IN_SHORT: */
      if (TurnLight_B.TurnLight_Decide == ALLOFF) {
        TurnLight_DW.is_FLDIAG = TurnLight_IN_IDLE;
      }
      break;
    }

    (void)Rte_Read_TurnLampFb_FR_u8_Signal(&tmpRead_7);
    switch (TurnLight_DW.is_FRDIAG) {
     case TurnLight_IN_IDLE:
      (void)Rte_Read_TurnLampCtrlCmd_FR_u8_signa(&tmpRead_4);
      if ((tmpRead_7 == 1) && (tmpRead_4 == 1)) {
        TurnLight_DW.is_FRDIAG = TurnLight_IN_SHORT;

        /* Outputs for Function Call SubSystem: '<S2>/TurnLight_FROFF_Short' */
        /* BusCreator: '<S12>/Bus Creator' incorporates:
         *  Constant: '<S12>/Constant'
         *  Constant: '<S12>/Constant1'
         *  Constant: '<S12>/Constant2'
         *  Constant: '<S12>/Constant3'
         *  Constant: '<S12>/Constant4'
         *  Constant: '<S12>/Constant5'
         *  Constant: '<S12>/Constant6'
         */
        rtb_BusCreator.TurnLightPosition = FRONT_RIGHT;
        rtb_BusCreator.TurnLightOnOff = OFF;
        rtb_BusCreator.TurnLightDutyCycle = 0U;
        rtb_BusCreator.TurnLightCycle = 0U;
        rtb_BusCreator.TurnLightTimes = 0U;
        rtb_BusCreator.TurnLightNumber = 0U;
        rtb_BusCreator.TurnLightPriority = 2U;

        /* FunctionCaller: '<S12>/TurnLightService_TurnLightControl_Operation' incorporates:
         *  BusCreator: '<S12>/Bus Creator'
         */
        Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

        /* End of Outputs for SubSystem: '<S2>/TurnLight_FROFF_Short' */
      } else {
        if ((tmpRead_7 == 2) && (tmpRead_4 == 1)) {
          TurnLight_DW.is_FRDIAG = TurnLight_IN_OPEN;

          /* Outputs for Function Call SubSystem: '<S2>/TurnLight_FRDouble_Open' */
          /* BusCreator: '<S11>/Bus Creator' incorporates:
           *  Constant: '<S11>/Constant'
           *  Constant: '<S11>/Constant1'
           *  Constant: '<S11>/Constant2'
           *  Constant: '<S11>/Constant3'
           *  Constant: '<S11>/Constant4'
           *  Constant: '<S11>/Constant5'
           *  Constant: '<S11>/Constant6'
           */
          rtb_BusCreator.TurnLightPosition = FRONT_RIGHT;
          rtb_BusCreator.TurnLightOnOff = ON;
          rtb_BusCreator.TurnLightDutyCycle = 0U;
          rtb_BusCreator.TurnLightCycle = 4U;
          rtb_BusCreator.TurnLightTimes = 0U;
          rtb_BusCreator.TurnLightNumber = 0U;
          rtb_BusCreator.TurnLightPriority = 2U;

          /* FunctionCaller: '<S11>/TurnLightService_TurnLightControl_Operation' incorporates:
           *  BusCreator: '<S11>/Bus Creator'
           */
          Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

          /* End of Outputs for SubSystem: '<S2>/TurnLight_FRDouble_Open' */
        }
      }
      break;

     case TurnLight_IN_OPEN:
      if (tmpRead_7 == 0) {
        TurnLight_DW.RightRetry = 1U;
        TurnLight_DW.is_FRDIAG = TurnLight_IN_IDLE;
      }
      break;

     default:
      /* case IN_SHORT: */
      if (TurnLight_B.TurnLight_Decide == ALLOFF) {
        TurnLight_DW.is_FRDIAG = TurnLight_IN_IDLE;
      }
      break;
    }

    (void)Rte_Read_TurnLampFb_RL_u8_Signal(&tmpRead_8);
    switch (TurnLight_DW.is_RLDIAG) {
     case TurnLight_IN_IDLE:
      (void)Rte_Read_TurnLampCtrlCmd_RL_u8_signal(&tmpRead_5);
      if ((tmpRead_8 == 1) && (tmpRead_5 == 1)) {
        TurnLight_DW.is_RLDIAG = TurnLight_IN_SHORT;

        /* Outputs for Function Call SubSystem: '<S2>/TurnLight_RLOFF_Short' */
        /* BusCreator: '<S17>/Bus Creator' incorporates:
         *  Constant: '<S17>/Constant'
         *  Constant: '<S17>/Constant1'
         *  Constant: '<S17>/Constant2'
         *  Constant: '<S17>/Constant3'
         *  Constant: '<S17>/Constant4'
         *  Constant: '<S17>/Constant5'
         *  Constant: '<S17>/Constant6'
         */
        rtb_BusCreator.TurnLightPosition = REAR_LEFT;
        rtb_BusCreator.TurnLightOnOff = OFF;
        rtb_BusCreator.TurnLightDutyCycle = 0U;
        rtb_BusCreator.TurnLightCycle = 0U;
        rtb_BusCreator.TurnLightTimes = 0U;
        rtb_BusCreator.TurnLightNumber = 0U;
        rtb_BusCreator.TurnLightPriority = 2U;

        /* FunctionCaller: '<S17>/TurnLightService_TurnLightControl_Operation' incorporates:
         *  BusCreator: '<S17>/Bus Creator'
         */
        Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

        /* End of Outputs for SubSystem: '<S2>/TurnLight_RLOFF_Short' */
      } else {
        if ((tmpRead_8 == 2) && (tmpRead_3 == 1)) {
          TurnLight_DW.is_RLDIAG = TurnLight_IN_OPEN;

          /* Outputs for Function Call SubSystem: '<S2>/TurnLight_RLDouble_Open' */
          /* BusCreator: '<S16>/Bus Creator' incorporates:
           *  Constant: '<S16>/Constant'
           *  Constant: '<S16>/Constant1'
           *  Constant: '<S16>/Constant2'
           *  Constant: '<S16>/Constant3'
           *  Constant: '<S16>/Constant4'
           *  Constant: '<S16>/Constant5'
           *  Constant: '<S16>/Constant6'
           */
          rtb_BusCreator.TurnLightPosition = REAR_LEFT;
          rtb_BusCreator.TurnLightOnOff = ON;
          rtb_BusCreator.TurnLightDutyCycle = 0U;
          rtb_BusCreator.TurnLightCycle = 4U;
          rtb_BusCreator.TurnLightTimes = 0U;
          rtb_BusCreator.TurnLightNumber = 0U;
          rtb_BusCreator.TurnLightPriority = 2U;

          /* FunctionCaller: '<S16>/TurnLightService_TurnLightControl_Operation' incorporates:
           *  BusCreator: '<S16>/Bus Creator'
           */
          Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

          /* End of Outputs for SubSystem: '<S2>/TurnLight_RLDouble_Open' */
        }
      }
      break;

     case TurnLight_IN_OPEN:
      if (tmpRead_8 == 0) {
        TurnLight_DW.LeftRetry = 1U;
        TurnLight_DW.is_RLDIAG = TurnLight_IN_IDLE;
      }
      break;

     default:
      /* case IN_SHORT: */
      if (TurnLight_B.TurnLight_Decide == ALLOFF) {
        TurnLight_DW.is_RLDIAG = TurnLight_IN_IDLE;
      }
      break;
    }

    switch (TurnLight_DW.is_RRDIAG) {
     case TurnLight_IN_IDLE:
      if ((tmpRead_6 == 1) && (tmpRead_3 == 1)) {
        TurnLight_DW.is_RRDIAG = TurnLight_IN_SHORT;

        /* Outputs for Function Call SubSystem: '<S2>/TurnLight_RRDouble_Short' */
        /* BusCreator: '<S19>/Bus Creator' incorporates:
         *  Constant: '<S19>/Constant'
         *  Constant: '<S19>/Constant1'
         *  Constant: '<S19>/Constant2'
         *  Constant: '<S19>/Constant3'
         *  Constant: '<S19>/Constant4'
         *  Constant: '<S19>/Constant5'
         *  Constant: '<S19>/Constant6'
         */
        rtb_BusCreator.TurnLightPosition = REAR_RIGHT;
        rtb_BusCreator.TurnLightOnOff = OFF;
        rtb_BusCreator.TurnLightDutyCycle = 0U;
        rtb_BusCreator.TurnLightCycle = 0U;
        rtb_BusCreator.TurnLightTimes = 0U;
        rtb_BusCreator.TurnLightNumber = 0U;
        rtb_BusCreator.TurnLightPriority = 2U;

        /* FunctionCaller: '<S19>/TurnLightService_TurnLightControl_Operation' incorporates:
         *  BusCreator: '<S19>/Bus Creator'
         */
        Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

        /* End of Outputs for SubSystem: '<S2>/TurnLight_RRDouble_Short' */
      } else {
        if ((tmpRead_6 == 2) && (tmpRead_3 == 1)) {
          TurnLight_DW.is_RRDIAG = TurnLight_IN_OPEN;

          /* Outputs for Function Call SubSystem: '<S2>/TurnLight_RRDouble_Open' */
          /* BusCreator: '<S18>/Bus Creator' incorporates:
           *  Constant: '<S18>/Constant'
           *  Constant: '<S18>/Constant1'
           *  Constant: '<S18>/Constant2'
           *  Constant: '<S18>/Constant3'
           *  Constant: '<S18>/Constant4'
           *  Constant: '<S18>/Constant5'
           *  Constant: '<S18>/Constant6'
           */
          rtb_BusCreator.TurnLightPosition = REAR_RIGHT;
          rtb_BusCreator.TurnLightOnOff = ON;
          rtb_BusCreator.TurnLightDutyCycle = 0U;
          rtb_BusCreator.TurnLightCycle = 4U;
          rtb_BusCreator.TurnLightTimes = 0U;
          rtb_BusCreator.TurnLightNumber = 0U;
          rtb_BusCreator.TurnLightPriority = 2U;

          /* FunctionCaller: '<S18>/TurnLightService_TurnLightControl_Operation' incorporates:
           *  BusCreator: '<S18>/Bus Creator'
           */
          Rte_Call_TurnLightService_TurnLightControl_Operation(&rtb_BusCreator);

          /* End of Outputs for SubSystem: '<S2>/TurnLight_RRDouble_Open' */
        }
      }
      break;

     case TurnLight_IN_OPEN:
      if (tmpRead_6 == 0) {
        TurnLight_DW.RightRetry = 1U;
        TurnLight_DW.is_RRDIAG = TurnLight_IN_IDLE;
      }
      break;

     default:
      /* case IN_SHORT: */
      if (TurnLight_B.TurnLight_Decide == ALLOFF) {
        TurnLight_DW.is_RRDIAG = TurnLight_IN_IDLE;
      }
      break;
    }
  }

  /* End of Chart: '<S2>/TurnLightDiag' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/TurnLight_Runnable_10ms' */

  /* Outport: '<Root>/TurnLampSwMode_u8_signa' */
  (void)Rte_Write_TurnLampSwMode_u8_signa(0U);
}

/* Model initialize function */
void TurnLight_Init(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
