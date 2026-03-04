/*
 * File: TurnLightAct.h
 *
 * Code generated for Simulink model 'TurnLightAct'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Fri Aug  9 20:03:26 2024
 *
 * Target selection: autosar.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_TurnLightAct_h_
#define RTW_HEADER_TurnLightAct_h_
#ifndef TurnLightAct_COMMON_INCLUDES_
#define TurnLightAct_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Rte_TurnLightAct.h"
#endif                                 /* TurnLightAct_COMMON_INCLUDES_ */

#include "TurnLightAct_types.h"

/* Macros for accessing real-time model data structure */

/* Block signals (default storage) */
typedef struct tag_B_TurnLightAct_T {
  uint8 TurnLampCtrlCmd;               /* '<S6>/TurnLampActuator1' */
  uint8 Counter;                       /* '<S6>/TurnLampActuator1' */
  uint8 TurnLampCtrlCmd_c;             /* '<S5>/TurnLampActuator' */
  uint8 Counter_c;                     /* '<S5>/TurnLampActuator' */
  uint8 TurnLampCtrlCmd_n;             /* '<S4>/TurnLampActuator1' */
  uint8 Counter_f;                     /* '<S4>/TurnLampActuator1' */
  uint8 TurnLampCtrlCmd_c2;            /* '<S3>/TurnLampActuator' */
  uint8 Counter_e;                     /* '<S3>/TurnLampActuator' */
} B_TurnLightAct_T;

/* Block states (default storage) for system '<Root>' */
typedef struct tag_DW_TurnLightAct_T {
  uint8 is_active_c1_TurnLightActLib;  /* '<S6>/TurnLampActuator1' */
  uint8 is_c1_TurnLightActLib;         /* '<S6>/TurnLampActuator1' */
  uint8 is_Normal;                     /* '<S6>/TurnLampActuator1' */
  uint8 is_Double;                     /* '<S6>/TurnLampActuator1' */
  uint8 temporalCounter_i1;            /* '<S6>/TurnLampActuator1' */
  uint8 is_active_c3_TurnLightActLib;  /* '<S5>/TurnLampActuator' */
  uint8 is_c3_TurnLightActLib;         /* '<S5>/TurnLampActuator' */
  uint8 is_Normal_p;                   /* '<S5>/TurnLampActuator' */
  uint8 is_Double_b;                   /* '<S5>/TurnLampActuator' */
  uint8 temporalCounter_i1_l;          /* '<S5>/TurnLampActuator' */
  uint8 is_active_c1_TurnLightActLib_g;/* '<S4>/TurnLampActuator1' */
  uint8 is_c1_TurnLightActLib_k;       /* '<S4>/TurnLampActuator1' */
  uint8 is_Normal_c;                   /* '<S4>/TurnLampActuator1' */
  uint8 is_Double_l;                   /* '<S4>/TurnLampActuator1' */
  uint8 temporalCounter_i1_h;          /* '<S4>/TurnLampActuator1' */
  uint8 is_active_c3_TurnLightActLib_f;/* '<S3>/TurnLampActuator' */
  uint8 is_c3_TurnLightActLib_g;       /* '<S3>/TurnLampActuator' */
  uint8 is_Normal_n;                   /* '<S3>/TurnLampActuator' */
  uint8 is_Double_d;                   /* '<S3>/TurnLampActuator' */
  uint8 temporalCounter_i1_n;          /* '<S3>/TurnLampActuator' */
} DW_TurnLightAct_T;

/* Block signals (default storage) */
extern B_TurnLightAct_T TurnLightAct_B;

/* Block states (default storage) */
extern DW_TurnLightAct_T TurnLightAct_DW;

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
 * '<Root>' : 'TurnLightAct'
 * '<S1>'   : 'TurnLightAct/Runnable_10ms_sys'
 * '<S2>'   : 'TurnLightAct/TurnLightAct_Init'
 * '<S3>'   : 'TurnLightAct/Runnable_10ms_sys/FL_TurnLightActuator'
 * '<S4>'   : 'TurnLightAct/Runnable_10ms_sys/FR_TurnLightActuator'
 * '<S5>'   : 'TurnLightAct/Runnable_10ms_sys/RL_TurnLightActuator'
 * '<S6>'   : 'TurnLightAct/Runnable_10ms_sys/RR_TurnLightActuator'
 * '<S7>'   : 'TurnLightAct/Runnable_10ms_sys/FL_TurnLightActuator/Function-Call Subsystem'
 * '<S8>'   : 'TurnLightAct/Runnable_10ms_sys/FL_TurnLightActuator/TurnLampActuator'
 * '<S9>'   : 'TurnLightAct/Runnable_10ms_sys/FR_TurnLightActuator/Function-Call Subsystem1'
 * '<S10>'  : 'TurnLightAct/Runnable_10ms_sys/FR_TurnLightActuator/TurnLampActuator1'
 * '<S11>'  : 'TurnLightAct/Runnable_10ms_sys/RL_TurnLightActuator/Function-Call Subsystem2'
 * '<S12>'  : 'TurnLightAct/Runnable_10ms_sys/RL_TurnLightActuator/TurnLampActuator'
 * '<S13>'  : 'TurnLightAct/Runnable_10ms_sys/RR_TurnLightActuator/Function-Call Subsystem3'
 * '<S14>'  : 'TurnLightAct/Runnable_10ms_sys/RR_TurnLightActuator/TurnLampActuator1'
 */
#endif                                 /* RTW_HEADER_TurnLightAct_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
