/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Cdd_IoHwAb.c
 *        Config:  G:/matlab/TurnLight/S32K144_SIP/MICROSAR/CBD1800257_D01_S32K1xx/Applications/S32K144_Start_new_IAR/S32K144_Start.dpa
 *     SW-C Type:  Cdd_IoHwAb
 *  Generated at:  Fri Aug  9 18:55:34 2024
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  C-Code implementation template for SW-C <Cdd_IoHwAb>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Cdd_IoHwAb.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */
#include "Dio.h"

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#define Cdd_IoHwAb_START_SEC_CODE
#include "Cdd_IoHwAb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: IoHwAbRunnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: IoHwAbRunnable_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Cdd_IoHwAb_CODE) IoHwAbRunnable(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: IoHwAbRunnable
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

FUNC(void, Cdd_IoHwAb_CODE) IoHwAb_TurnLightCtrlCmd_FL_Operation(uint8 CtrlCmd) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 ret;
    ret = Dio_ReadChannel(DioConf_DioChannel_DioChannel_PTD0);
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_PTD0,CtrlCmd);   
}
FUNC(void, Cdd_IoHwAb_CODE) IoHwAb_TurnLightCtrlCmd_FR_Operation(uint8 CtrlCmd) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 ret;
    ret = Dio_ReadChannel(DioConf_DioChannel_DioChannel_PTD1);
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_PTD1,CtrlCmd);   
}
FUNC(void, Cdd_IoHwAb_CODE) IoHwAb_TurnLightCtrlCmd_RL_Operation(uint8 CtrlCmd) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 ret;
    ret = Dio_ReadChannel(DioConf_DioChannel_DioChannel_PTD15);
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_PTD15,CtrlCmd);   
}
FUNC(void, Cdd_IoHwAb_CODE) IoHwAb_TurnLightCtrlCmd_RR_Operation(uint8 CtrlCmd) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 ret;
    ret = Dio_ReadChannel(DioConf_DioChannel_DioChannel_PTD16);
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_PTD16,CtrlCmd);   
}




#define Cdd_IoHwAb_STOP_SEC_CODE
#include "Cdd_IoHwAb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
