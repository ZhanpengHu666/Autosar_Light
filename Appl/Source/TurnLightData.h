/*
 * File: TurnLightData.h
 *
 * Code generated for Simulink model 'TurnLight'.
 *
 * Model version                  : 1.33
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Mon Aug  5 19:16:20 2024
 *
 * Target selection: autosar.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_TurnLightData_h_
#define RTW_HEADER_TurnLightData_h_

# define TurnLight_START_SEC_CODE
# include "TurnLight_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
enum 
{
    NORMAL = 0,
    SHORT,
    OPEN
}DiagStType;

enum 
{
    ALLOFF = 0,
    ALLON,
    LEFTSHORT,
    LEFTLONG,
    RIGHTSHORT,
    RIGHTLONG
}TurnLightDecideStType;

# define TurnLight_STOP_SEC_CODE
# include "TurnLight_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Model Code Variants */
#endif                                 /* RTW_HEADER_TurnLight_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
