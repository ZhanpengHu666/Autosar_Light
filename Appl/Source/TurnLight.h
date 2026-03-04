/*
 * File: TurnLight.h
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

#ifndef RTW_HEADER_TurnLight_h_
#define RTW_HEADER_TurnLight_h_
#ifndef TurnLight_COMMON_INCLUDES_
#define TurnLight_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_TurnLight.h"
#endif                                 /* TurnLight_COMMON_INCLUDES_ */

#include "TurnLight_types.h"

/* Macros for accessing real-time model data structure */

/* Block signals (default storage) */
typedef struct tag_B_TurnLight_T {
  uint8 TurnLight_Decide;              /* '<S2>/TurnLightSelector' */
  uint8 TurnLampSWRst;                 /* '<S2>/TurnLightCtrlLogic' */
  uint8 TurnLampSWMode;                /* '<S2>/TurnLightCtrlLogic' */
} B_TurnLight_T;

/* Block states (default storage) for system '<Root>' */
typedef struct tag_DW_TurnLight_T {
  uint32 temporalCounter_i1;           /* '<S2>/HazardCtrlLogic' */
  uint8 LeftRetry;                     /* '<S2>/Data Store Memory' */
  uint8 RightRetry;                    /* '<S2>/Data Store Memory1' */
  uint8 is_active_c2_TurnLight;        /* '<S2>/TurnLightSelector' */
  uint8 is_c2_TurnLight;               /* '<S2>/TurnLightSelector' */
  uint8 HazardLightRqst_prev;          /* '<S2>/TurnLightSelector' */
  uint8 HazardLightRqst_start;         /* '<S2>/TurnLightSelector' */
  uint8 TurnLightSwRqst_prev;          /* '<S2>/TurnLightSelector' */
  uint8 TurnLightSwRqst_start;         /* '<S2>/TurnLightSelector' */
  uint8 is_active_c4_TurnLight;        /* '<S2>/TurnLightDiag' */
  uint8 is_FLDIAG;                     /* '<S2>/TurnLightDiag' */
  uint8 is_FRDIAG;                     /* '<S2>/TurnLightDiag' */
  uint8 is_RLDIAG;                     /* '<S2>/TurnLightDiag' */
  uint8 is_RRDIAG;                     /* '<S2>/TurnLightDiag' */
  uint8 is_active_c3_TurnLight;        /* '<S2>/TurnLightCtrlLogic' */
  uint8 is_c3_TurnLight;               /* '<S2>/TurnLightCtrlLogic' */
  uint8 is_LEFT;                       /* '<S2>/TurnLightCtrlLogic' */
  uint8 is_RIGHT;                      /* '<S2>/TurnLightCtrlLogic' */
  uint8 TurnLapmCount;                 /* '<S2>/TurnLightCtrlLogic' */
  uint8 is_active_c1_TurnLight;        /* '<S2>/HazardCtrlLogic' */
  uint8 is_c1_TurnLight;               /* '<S2>/HazardCtrlLogic' */
  uint8 CrashIntensity_prev;           /* '<S2>/HazardCtrlLogic' */
  uint8 CrashIntensity_start;          /* '<S2>/HazardCtrlLogic' */
  uint8 HazardSw_prev;                 /* '<S2>/HazardCtrlLogic' */
  uint8 HazardSw_start;                /* '<S2>/HazardCtrlLogic' */
  uint8 EmergencyBrakeLight_prev;      /* '<S2>/HazardCtrlLogic' */
  uint8 EmergencyBrakeLight_start;     /* '<S2>/HazardCtrlLogic' */
} DW_TurnLight_T;

/* Block signals (default storage) */
extern B_TurnLight_T TurnLight_B;

/* Block states (default storage) */
extern DW_TurnLight_T TurnLight_DW;

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
 * '<Root>' : 'TurnLight'
 * '<S1>'   : 'TurnLight/TurnLight_Init'
 * '<S2>'   : 'TurnLight/TurnLight_Runnable_10ms_sys'
 * '<S3>'   : 'TurnLight/TurnLight_Runnable_10ms_sys/HazardCtrlLogic'
 * '<S4>'   : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLightCtrlLogic'
 * '<S5>'   : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLightDiag'
 * '<S6>'   : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLightSelector'
 * '<S7>'   : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_ALLOFF'
 * '<S8>'   : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_ALLON'
 * '<S9>'   : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_FLDouble_Open'
 * '<S10>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_FLOFF_Short'
 * '<S11>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_FRDouble_Open'
 * '<S12>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_FROFF_Short'
 * '<S13>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_LeftLong'
 * '<S14>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_LeftLong1'
 * '<S15>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_LeftShort'
 * '<S16>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_RLDouble_Open'
 * '<S17>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_RLOFF_Short'
 * '<S18>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_RRDouble_Open'
 * '<S19>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_RRDouble_Short'
 * '<S20>'  : 'TurnLight/TurnLight_Runnable_10ms_sys/TurnLight_RightShort'
 */
#endif                                 /* RTW_HEADER_TurnLight_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
