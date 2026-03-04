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
 *              File: StartApplicationTrusted.c
 *       Description: This StartApplication file demonstrates the use case MEMORYPROTECTION
 *********************************************************************************************************************/

#define STARTAPPLICATIONTRUSTED_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Rte_StartApplicationTrusted.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */

/**********************************************************************************************************************
 *  FUNCTIONS
 *********************************************************************************************************************/
#define StartApplicationTrusted_START_SEC_CODE
#include "StartApplicationTrusted_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplicationTrusted_OnDataRec_TrustedData
 * Description: Called when the data value to write in the IRV is set in the main application via S/R port.
 *
 *********************************************************************************************************************/
FUNC(void, StartApplicationTrusted_CODE) StartApplicationTrusted_OnDataRec_TrustedData(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 dataIn;
    uint8 dataOut;

    /* read value from main application and write it to the IRV */
    (void)Rte_Read_PpTrustedData_DeValue(&dataIn);
    Rte_IrvWrite_StartApplicationTrusted_OnDataRec_TrustedData_IrvValue(dataIn);
    /* read IRV and write the value back to the main application */
    dataOut = Rte_IrvRead_StartApplicationTrusted_OnDataRec_TrustedData_IrvValue();
    (void)Rte_Write_PpTrustedDataVerification_DeValue(dataOut);
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplicationTrusted_TriggerMemoryAccesViolation
 * Description: Called when the data value to write in the IRV is set in the main application via C/S port.
 *
 *********************************************************************************************************************/
FUNC(void, StartApplicationTrusted_CODE) StartApplicationTrusted_TriggerMemoryAccesViolation(uint8 Value) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 dataOut;

    /* write the value set in the main application to the IRV */
    Rte_IrvWrite_StartApplicationTrusted_TriggerMemoryAccesViolation_IrvValue(Value);
    /* the following statements should never be executed, because the statement above should cause a memory access violation */
    dataOut = Rte_IrvRead_StartApplicationTrusted_TriggerMemoryAccesViolation_IrvValue();
    (void)Rte_Write_PpTrustedDataVerification_DeValue(dataOut);
}

#define StartApplicationTrusted_STOP_SEC_CODE
#include "StartApplicationTrusted_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

