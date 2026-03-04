/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                            All rights reserved.
 *              This software is copyright protected and proprietary to Vector Informatik GmbH.
 *              Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *              All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  EXAMPLE CODE ONLY
 *  -------------------------------------------------------------------------------------------------------------------
 *              This Example Code is only intended for illustrating an example of a possible BSW integration and BSW
 *              configuration. The Example Code has not passed any quality control measures and may be incomplete. The
 *              Example Code is neither intended nor qualified for use in series production. The Example Code as well
 *              as any of its modifications and/or implementations must be tested with diligent care and must comply
 *              with all quality requirements which are necessary according to the state of the art before their use.
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: StartApplicationMemoryAccessState.c
 *       Description: This StartApplication file demonstrates the use case MEMORYPROTECTION
 *********************************************************************************************************************/

#define STARTAPPLICATIONMEMORYACCESSSTATE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Rte_StartApplicationMemoryAccessState.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */
#include "StartApplicationMemoryAccessState.h"


/**********************************************************************************************************************
 *  FUNCTIONS
 *********************************************************************************************************************/
#define StartApplicationMemoryAccessState_START_SEC_CODE
#include "StartApplicationMemoryAccessState_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplicationMemoryAccessState_Init
 * Description: Called during startup. Initialize PIMs.
 *
 *********************************************************************************************************************/
FUNC(void, StartApplicationMemoryAccessState_CODE) StartApplicationMemoryAccessState_Init(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    *Rte_Pim_PimMemoryAccessState() = FALSE;
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplicationMemoryAccessState_GetState
 * Description: Get the current state, called from the application.
 *
 *********************************************************************************************************************/
FUNC(void, StartApplicationMemoryAccessState_CODE) StartApplicationMemoryAccessState_GetState(P2VAR(boolean, AUTOMATIC, RTE_STARTAPPLICATIONMEMORYACCESSSTATE_APPL_VAR) State) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    *State = *Rte_Pim_PimMemoryAccessState();
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplicationMemoryAccessState_Reset
 * Description: Reset the current state, called from the application.
 *
 *********************************************************************************************************************/
FUNC(void, StartApplicationMemoryAccessState_CODE) StartApplicationMemoryAccessState_Reset(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    *Rte_Pim_PimMemoryAccessState() = FALSE;
}

/**********************************************************************************************************************
 *
 * Function Entity Name: StartApplicationMemoryAccessState_SetState
 * Description: Set the current state, called from the protection hook.
 *
 *********************************************************************************************************************/
FUNC(void, StartApplicationMemoryAccessState_CODE) StartApplicationMemoryAccessState_SetState(boolean State)
{
    *Rte_Pim_PimMemoryAccessState() = State;
}

#define StartApplicationMemoryAccessState_STOP_SEC_CODE
#include "StartApplicationMemoryAccessState_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

