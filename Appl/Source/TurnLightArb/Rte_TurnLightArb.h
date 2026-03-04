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
 *          File:  Rte_TurnLightArb.h
 *        Config:  G:/matlab/TurnLight/S32K144_SIP/MICROSAR/CBD1800257_D01_S32K1xx/Applications/S32K144_Start_new_IAR/S32K144_Start.dpa
 *     SW-C Type:  TurnLightArb
 *  Generated at:  Fri Aug  9 18:55:32 2024
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Application header file for SW-C <TurnLightArb> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_TURNLIGHTARB_H
# define _RTE_TURNLIGHTARB_H

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

# include "Rte_TurnLightArb_Type.h"
# include "Rte_DataHandleType.h"


/**********************************************************************************************************************
 * Component Data Structures and Port Data Structures
 *********************************************************************************************************************/

struct Rte_CDS_TurnLightArb
{
  /* dummy entry */
  uint8 _dummy;
};

# define RTE_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONSTP2CONST(struct Rte_CDS_TurnLightArb, RTE_CONST, RTE_CONST) Rte_Inst_TurnLightArb; /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

typedef P2CONST(struct Rte_CDS_TurnLightArb, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_TurnLamp_FL_Out_u8_Signal (0U)
# define Rte_InitValue_TurnLamp_RL_Out_u8_Signal (0U)
# define Rte_InitValue_TurnLapm_FR_Out_u8_Signal (0U)
# define Rte_InitValue_TurnLapme_RR_Out_u8_Signal (0U)


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightArb_TurnLamp_FL_Out_u8_Signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightArb_TurnLamp_RL_Out_u8_Signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightArb_TurnLapm_FR_Out_u8_Signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_TurnLightArb_TurnLapme_RR_Out_u8_Signal(uint8 data); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Write_TurnLamp_FL_Out_u8_Signal Rte_Write_TurnLightArb_TurnLamp_FL_Out_u8_Signal
# define Rte_Write_TurnLamp_RL_Out_u8_Signal Rte_Write_TurnLightArb_TurnLamp_RL_Out_u8_Signal
# define Rte_Write_TurnLapm_FR_Out_u8_Signal Rte_Write_TurnLightArb_TurnLapm_FR_Out_u8_Signal
# define Rte_Write_TurnLapme_RR_Out_u8_Signal Rte_Write_TurnLightArb_TurnLapme_RR_Out_u8_Signal




# define TurnLightArb_START_SEC_CODE
# include "TurnLightArb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


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

# define RTE_RUNNABLE_TurnLightArb_Runnable_10ms TurnLightArb_Runnable_10ms
FUNC(void, TurnLightArb_CODE) TurnLightArb_Runnable_10ms(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

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

# define RTE_RUNNABLE_TurnLightService_TurnLightControl_Operation TurnLightService_TurnLightControl_Operation
FUNC(void, TurnLightArb_CODE) TurnLightService_TurnLightControl_Operation(P2CONST(TurnLightService, AUTOMATIC, RTE_TURNLIGHTARB_APPL_DATA) TurnLightCtrlPara); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define TurnLightArb_STOP_SEC_CODE
# include "TurnLightArb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_TURNLIGHTARB_H */
