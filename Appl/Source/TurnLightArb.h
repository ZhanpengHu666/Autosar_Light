/*
 * File: TurnLightArb.h
 *
 * Code generated for Simulink model 'TurnLightArb'.
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Sat Aug 10 07:33:58 2024
 */

#ifndef RTW_HEADER_TurnLightArb_h_
#define RTW_HEADER_TurnLightArb_h_
#ifndef TurnLightArb_COMMON_INCLUDES_
#define TurnLightArb_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_TurnLightArb.h"
#endif                                 /* TurnLightArb_COMMON_INCLUDES_ */

#include "TurnLightArb_types.h"

/* Child system includes */
#include "TurnLightService_TurnLightControl_Operation_private.h"

/* Macros for accessing real-time model data structure */

/* Block signals (default storage) */
typedef struct tag_B_TurnLightArb_T {
  uint8 TurnLight_FL_Out;              /* '<S1>/TurnLightOutArb' */
  uint8 TurnLight_FR_Out;              /* '<S1>/TurnLightOutArb' */
  uint8 TurnLight_RL_Out;              /* '<S1>/TurnLightOutArb' */
  uint8 TurnLight_RR_Out;              /* '<S1>/TurnLightOutArb' */
} B_TurnLightArb_T;

/* Block states (default storage) for system '<Root>' */
typedef struct tag_DW_TurnLightArb_T {
  TurnLightService TurnLightCtrlCmd;   /* '<Root>/Data Store Memory' */
  uint8 CurrentPriority;               /* '<Root>/Data Store Memory2' */
  uint8 is_active_c3_TurnLightArb;     /* '<S1>/TurnLightOutArb' */
  uint8 is_c3_TurnLightArb;            /* '<S1>/TurnLightOutArb' */
  boolean IsFunctionCall;              /* '<Root>/Data Store Memory1' */
} DW_TurnLightArb_T;

/* Block signals (default storage) */
extern B_TurnLightArb_T TurnLightArb_B;

/* Block states (default storage) */
extern DW_TurnLightArb_T TurnLightArb_DW;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'TurnLightArb'
 * '<S1>'   : 'TurnLightArb/Runnable_10ms_sys'
 * '<S2>'   : 'TurnLightArb/TurnLightArb_Init'
 * '<S3>'   : 'TurnLightArb/TurnLightService'
 * '<S4>'   : 'TurnLightArb/Runnable_10ms_sys/TurnLightOutArb'
 * '<S5>'   : 'TurnLightArb/TurnLightService/TurnLightService_TurnLightControl_Operation_sys'
 */
#endif                                 /* RTW_HEADER_TurnLightArb_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
