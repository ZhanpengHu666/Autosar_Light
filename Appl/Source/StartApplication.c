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
 *              File: StartApplication.c
 *       Description: This StartApplication demonstrates following use cases:
 *                    COM, DIAG, MEM, MEMORYPROTECTION, NM, WDG
 *********************************************************************************************************************/

#define STARTAPPLICATION_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Rte_StartApplication.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK User Includes>
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL MACROS
**********************************************************************************************************************/
/*-----------------------------
  General
-----------------------------*/
#define STARTAPPLICATION_INVALID_SIGNAL_VALUE 0xFF
#if !defined (STARTAPPLICATION_LOCAL)
# define STARTAPPLICATION_LOCAL static
#endif

/* Bit masks */
#define STARTAPPLICATION_MASK_1_BIT                                      0x01u
#define STARTAPPLICATION_MASK_2_BIT                                      0x03u
#define STARTAPPLICATION_MASK_3_BIT                                      0x07u
#define STARTAPPLICATION_MASK_4_BIT                                      0x0Fu
#define STARTAPPLICATION_MASK_5_BIT                                      0x1Fu
#define STARTAPPLICATION_MASK_6_BIT                                      0x3Fu
#define STARTAPPLICATION_MASK_7_BIT                                      0x7Fu
#define STARTAPPLICATION_MASK_8_BIT                                      0xFFu

/*-----------------------------
  MEM use case
-----------------------------*/
#define STARTAPPLICATION_MEM_BLOCK_ID_BLOCK1                             0u
#define STARTAPPLICATION_MEM_BLOCK_ID_BLOCK2                             1u

/* Control and data signal layout handling */
#define STARTAPPLICATION_RX_DATA_MEM_POS_DATA_VALUE                      0u
#define STARTAPPLICATION_RX_DATA_MEM_POS_WRITE_SELECTED                  5u
#define STARTAPPLICATION_RX_DATA_MEM_POS_BLOCK_ID                        6u

#define STARTAPPLICATION_TX_DATA_MEM_POS_DATA_VALUE                      0u
#define STARTAPPLICATION_TX_DATA_MEM_POS_BLOCK_ID                        7u
#define STARTAPPLICATION_TX_CTRL_MEM_POS_BLOCK_STATE                     0u
#define STARTAPPLICATION_TX_CTRL_MEM_POS_BLOCK_ID                        7u

#define STARTAPPLICATION_RX_DATA_MEM_DATA_VALUE(value)                   (((value) >> STARTAPPLICATION_RX_DATA_MEM_POS_DATA_VALUE) & STARTAPPLICATION_MASK_5_BIT) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define STARTAPPLICATION_RX_DATA_MEM_WRITE_SELECTED(value)               (((value) >> STARTAPPLICATION_RX_DATA_MEM_POS_WRITE_SELECTED) & STARTAPPLICATION_MASK_1_BIT) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define STARTAPPLICATION_RX_DATA_MEM_BLOCK_ID(value)                     (((value) >> STARTAPPLICATION_RX_DATA_MEM_POS_BLOCK_ID) & STARTAPPLICATION_MASK_1_BIT) /* PRQA S 3453 */ /* MD_MSR_19.7 */

#define STARTAPPLICATION_TX_DATA_MEM_DATA_VALUE(value)                   (((value) & STARTAPPLICATION_MASK_5_BIT) << STARTAPPLICATION_TX_DATA_MEM_POS_DATA_VALUE) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define STARTAPPLICATION_TX_DATA_MEM_BLOCK_ID(value)                     (((value) & STARTAPPLICATION_MASK_1_BIT) << STARTAPPLICATION_TX_DATA_MEM_POS_BLOCK_ID) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define STARTAPPLICATION_TX_CTRL_MEM_BLOCK_STATE(value)                  (((value) & STARTAPPLICATION_MASK_3_BIT) << STARTAPPLICATION_TX_CTRL_MEM_POS_BLOCK_STATE) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define STARTAPPLICATION_TX_CTRL_MEM_BLOCK_ID(value)                     (((value) & STARTAPPLICATION_MASK_1_BIT) << STARTAPPLICATION_TX_CTRL_MEM_POS_BLOCK_ID) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*-----------------------------
  NM use case
-----------------------------*/
#define STARTAPPLICATION_NM_COMM_CHANNEL_INVALID                         0xFFu
#define STARTAPPLICATION_NM_NUMBER_OF_CHANNELS                           1u
#define STARTAPPLICATION_NM_COMM_MODE_MASK                               0x80u
#define STARTAPPLICATION_NM_COMM_CHANNEL_MASK                            0x7Fu
#define STARTAPPLICATION_NM_MAX_COMMUSERS                                1u

/* Timer for Bus Sleep Mode */
#define STARTAPPLICATION_NM_DURATION_T1                                  20u /* T1 as multiples of cyclic runnable period 250ms */
#define STARTAPPLICATION_NM_DURATION_T2                                  20u /* T2 as multiples of cyclic runnable period 250ms */

/*-----------------------------
  WDG use case
-----------------------------*/
#define STARTAPPLICATION_WDG_CHECKPOINT_ID                               0u

/**********************************************************************************************************************
  LOCAL DATA TYPES
**********************************************************************************************************************/
/* Represents Set-/Reset-Action of DEM Monitor event */
typedef enum { STARTAPPLICATION_DIAG_SETEVENTTOPASSED = 0, STARTAPPLICATION_DIAG_SETEVENTTOFAILED = 1, STARTAPPLICATION_DIAG_RESETCOUNTER = 2 } StartApplicationEnumDiagEventType;
/* Represents all supported return codes which are transmitted by DUT via TX control signal */
typedef enum { STARTAPPLICATION_RETURN_CODE_OK = 0, STARTAPPLICATION_RETURN_CODE_ERROR = 1, STARTAPPLICATION_RETURN_CODE_UNKNOWN_COMPONENT = 2, STARTAPPLICATION_RETURN_CODE_PENDING = 3 } StartApplication_EnumCtrlReturnCodeType;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define StartApplication_START_SEC_CODE
#include "StartApplication_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_SendCtrl(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_SendData(void);
STARTAPPLICATION_LOCAL FUNC(uint8, StartApplication_CODE) StartApplication_ReadData(void);
STARTAPPLICATION_LOCAL FUNC(uint8, StartApplication_CODE) StartApplication_ReadCtrl(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_CalculateRxData(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_CalculateTxData(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_RXTX_Cyclic(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_ReadRxData(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_TXONLY_Cyclic(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_WriteTxData(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_DIAG_Cyclic(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_DIAG_OnDataRec_RxData(VAR(uint8, AUTOMATIC) rxDataBuffer);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_Cyclic(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_OnDataRec_RxData(VAR(uint8, AUTOMATIC) rxDataBuffer);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_DetermineTxCtrlSignal(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_DetermineTxDataSignal(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_OnDataRec_RxCtrl(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_JobFinished(VAR(NvM_ServiceIdType, AUTOMATIC) ServiceId, VAR(NvM_RequestResultType, AUTOMATIC) JobResult, VAR(uint8, AUTOMATIC) blockId);
STARTAPPLICATION_LOCAL FUNC(P2VAR(EnumMEM_BlockStateType, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR), StartApplication_CODE) StartApplication_MEM_GetBlockStatePim(VAR(uint8, AUTOMATIC) blockId);
STARTAPPLICATION_LOCAL FUNC(P2VAR(uint8, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR), StartApplication_CODE) StartApplication_MEM_GetDataBufferPim(VAR(uint8, AUTOMATIC) blockId);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_WriteBlock(VAR(uint8, AUTOMATIC) blockId, VAR(uint8, AUTOMATIC) dataValue);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_RequestComMode(uint8 channel, ComM_ModeType comMode);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_RequestComMUser(uint8 user);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_SetActiveComMUser(uint8 channel);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_GetCurrentComMode(uint8 channel, ComM_ModeType* comMode);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_OnDataRec_RxData(uint8 rxDataBuffer);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_DetermineTxCtrlSignal(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_HandleActiveChannel(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_HandleInactiveChannels(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_WDG_OnDataRec_RxData(VAR(uint8, AUTOMATIC) rxData);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_WDG_DetermineTxDataSignal(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_WDG_HandleCheckpoint(void);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEMORYPROTECTION_OnDataRec_RxData(VAR(uint8, AUTOMATIC) rxData);
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEMORYPROTECTION_DetermineTxDataSignal(void);

/**********************************************************************************************************************
 *  RUNNABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_Init
 * Description: Called during startup
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_Init(void)
{
    *Rte_Pim_ActiveComponent() = STARTAPPLICATION_ACTIVE_COMPONENT_WDG;
    *Rte_Pim_Uptime() = 0u;
    *Rte_Pim_TxCtrlSigValue() = STARTAPPLICATION_RETURN_CODE_OK;
    *Rte_Pim_TxDataSigValue() = 0;
    *Rte_Pim_COM_RxSigValue0() = 0;
    *Rte_Pim_COM_TxSigValue0() = 0;

    *Rte_Pim_NM_ActiveComMChannel() = STARTAPPLICATION_NM_COMM_CHANNEL_INVALID;
    *Rte_Pim_NM_BusSleepModeTimer() = 0u;
    *Rte_Pim_NM_ApplState() = NM_APPL_STATE_FULL_COMM_EXTERN;
    *Rte_Pim_NM_ActiveChannelHasFullComRequest() = FALSE;
    *Rte_Pim_NM_ActiveComMUsers() = 0u;

    *Rte_Pim_WDG_AliveCycle() = 1u;
    *Rte_Pim_WDG_AliveTimer() = 0u;

    *Rte_Pim_MEM_ActiveBlock() = 0u;
    *Rte_Pim_MEM_DataBuffer1() = 0xFFu;
    *Rte_Pim_MEM_DataBuffer2() = 0xFFu;
    *Rte_Pim_MEM_BlockState1() = MEM_STATE_UNKNOWN;
    *Rte_Pim_MEM_BlockState2() = MEM_STATE_UNKNOWN;

    *Rte_Pim_DIAG_LastRxData() = STARTAPPLICATION_INVALID_SIGNAL_VALUE;

    /* Request full communication for all ComM Users */
    (void)Rte_Call_UR_CN_CAN_52ce3533_RequestComMode (COMM_FULL_COMMUNICATION);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK StartApplication_Init>
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/

} /* PRQA S 6050 */ /* MD_StartApplication_STCAL_6050 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_Cyclic10ms
 * Description: Called every 0.01 seconds
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_Cyclic10ms(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    if(STARTAPPLICATION_ACTIVE_COMPONENT_WDG == *Rte_Pim_ActiveComponent())
    {
        StartApplication_WDG_HandleCheckpoint();
    }
    else
    {
        (void)Rte_Call_PpAliveWdgMSupervisedEntity_StartApplication_CheckpointReached(STARTAPPLICATION_WDG_CHECKPOINT_ID);
    }
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_Cyclic1000ms
 * Description: Called every 1.0 seconds
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_Cyclic1000ms(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    if(*Rte_Pim_Uptime() < 255)
    {
        (*Rte_Pim_Uptime())++;
    }
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_Cyclic1ms
 * Description: Called every 0.001 seconds
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_Cyclic1ms(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    /* nothing to be done cyclically every 1 ms */
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_Cyclic250ms
 * Description: Called every 0.25 seconds
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_Cyclic250ms(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    switch(*Rte_Pim_ActiveComponent())
    {
        case STARTAPPLICATION_ACTIVE_COMPONENT_COM_RXTX:
        {
            StartApplication_COM_RXTX_Cyclic();
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_COM_TXONLY:
        {
            StartApplication_COM_TXONLY_Cyclic();
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_MEM:
        {
            StartApplication_MEM_Cyclic();
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_DIAG:
        {
            StartApplication_DIAG_Cyclic();
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_NM:
        {
            StartApplication_NM_HandleActiveChannel();
            StartApplication_NM_DetermineTxCtrlSignal();
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_WDG:
        {
            StartApplication_WDG_DetermineTxDataSignal();
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_MEMORYPROTECTION:
        {
            StartApplication_MEMORYPROTECTION_DetermineTxDataSignal();
            break;
        }
        default:
        {
            break;
        }
    }
    StartApplication_NM_HandleInactiveChannels();
    if((*Rte_Pim_ActiveComponent() != STARTAPPLICATION_ACTIVE_COMPONENT_COM_RXTX)
      && (*Rte_Pim_ActiveComponent() != STARTAPPLICATION_ACTIVE_COMPONENT_COM_TXONLY))
    {
        StartApplication_SendData();
        StartApplication_SendCtrl();
    }

} /* PRQA S 6050 */ /* MD_StartApplication_STCAL_6050 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_DIAG_ConditionCheckRead
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_DIAG_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_STARTAPPLICATION_APPL_DATA) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    *ErrorCode = E_OK;
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_DIAG_DcmReadData
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(void, StartApplication_CODE)StartApplication_DIAG_DcmReadData(P2VAR(uint8, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(void, StartApplication_CODE)StartApplication_DIAG_DcmReadData(P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
    Data[0] = (uint8) (Rte_IrvRead_StartApplication_DIAG_DcmReadData_IrvOccuranceCounterDid() >> 8);
    Data[1] = (uint8) (Rte_IrvRead_StartApplication_DIAG_DcmReadData_IrvOccuranceCounterDid() & 0xFF);
# else
    (*Data)[0] = (uint8) (Rte_IrvRead_StartApplication_DIAG_DcmReadData_IrvOccuranceCounterDid() >> 8);
    (*Data)[1] = (uint8) (Rte_IrvRead_StartApplication_DIAG_DcmReadData_IrvOccuranceCounterDid() & 0xFF);
# endif
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_DIAG_DcmWriteData
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(void, StartApplication_CODE)StartApplication_DIAG_DcmWriteData(P2CONST(uint8, AUTOMATIC, RTE_STARTAPPLICATION_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(void, StartApplication_CODE) StartApplication_DIAG_DcmWriteData(P2CONST(Dcm_Data2ByteType, AUTOMATIC, RTE_STARTAPPLICATION_APPL_DATA) Data, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
    Rte_IrvWrite_StartApplication_DIAG_DcmWriteData_IrvOccuranceCounterDid((uint16)(((uint16)Data[0] << 8) | (Data[1] & 0xFF)));
# else
    Rte_IrvWrite_StartApplication_DIAG_DcmWriteData_IrvOccuranceCounterDid((uint16)(((uint16)(*Data)[0] << 8) | ((*Data)[1] & 0xFF)));
# endif
    *ErrorCode = E_OK;
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_DIAG_DemReadData
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(void, StartApplication_CODE)StartApplication_DIAG_DemReadData(P2VAR(uint8, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(void, StartApplication_CODE)StartApplication_DIAG_DemReadData(P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
    Data[0] = (uint8) (Rte_IrvRead_StartApplication_DIAG_DemReadData_IrvOccuranceCounterDid() >> 8);
    Data[1] = (uint8) (Rte_IrvRead_StartApplication_DIAG_DemReadData_IrvOccuranceCounterDid() & 0xFF);
# else
    (*Data)[0] = (uint8) (Rte_IrvRead_StartApplication_DIAG_DemReadData_IrvOccuranceCounterDid() >> 8);
    (*Data)[1] = (uint8) (Rte_IrvRead_StartApplication_DIAG_DemReadData_IrvOccuranceCounterDid() & 0xFF);
# endif
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_MEM_JobFinished_StartApplication_NvMBlock1
 * Description: Called by NvM BSW Module if a job for the StartApplication NvM block was processed
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_MEM_JobFinished_StartApplication_NvMBlock1(VAR(NvM_ServiceIdType, AUTOMATIC) ServiceId, VAR(NvM_RequestResultType, AUTOMATIC) JobResult) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    StartApplication_MEM_JobFinished(ServiceId, JobResult, STARTAPPLICATION_MEM_BLOCK_ID_BLOCK1);
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_MEM_JobFinished_StartApplication_NvMBlock2
 * Description: Called by NvM BSW Module if a job for the StartApplication NvM block was processed
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_MEM_JobFinished_StartApplication_NvMBlock2(VAR(NvM_ServiceIdType, AUTOMATIC) ServiceId, VAR(NvM_RequestResultType, AUTOMATIC) JobResult) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    StartApplication_MEM_JobFinished(ServiceId, JobResult, STARTAPPLICATION_MEM_BLOCK_ID_BLOCK2);
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_OnDataRec_RxCtrl
 * Description: the value of the ctrl rx signal determines which use case is active
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_OnDataRec_RxCtrl(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 channel;
    uint8 rxCtrlBuffer = StartApplication_ReadCtrl();
    if(*Rte_Pim_ActiveComponent() == (EnumActiveComponentType)rxCtrlBuffer)
    {
        return;
    }
    switch((EnumActiveComponentType)rxCtrlBuffer)
    {
        case STARTAPPLICATION_ACTIVE_COMPONENT_COM_RXTX:
        case STARTAPPLICATION_ACTIVE_COMPONENT_COM_TXONLY:
        {
            *Rte_Pim_ActiveComponent() = (EnumActiveComponentType)rxCtrlBuffer;
            *Rte_Pim_TxCtrlSigValue() = STARTAPPLICATION_RETURN_CODE_OK;
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_MEM:
        {
            *Rte_Pim_ActiveComponent() = (EnumActiveComponentType)rxCtrlBuffer;
            StartApplication_MEM_OnDataRec_RxCtrl();
            *Rte_Pim_TxCtrlSigValue() = STARTAPPLICATION_RETURN_CODE_OK;
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_DIAG:
        {
            *Rte_Pim_ActiveComponent() = (EnumActiveComponentType)rxCtrlBuffer;
            *Rte_Pim_DIAG_LastRxData() = STARTAPPLICATION_INVALID_SIGNAL_VALUE;
            *Rte_Pim_TxCtrlSigValue() = STARTAPPLICATION_RETURN_CODE_OK;
            (void)Rte_Call_PpDemOpCycle_PowerCycle_SetOperationCycleState (DEM_CYCLE_STATE_START);
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_NM:
        {
            *Rte_Pim_ActiveComponent() = (EnumActiveComponentType)rxCtrlBuffer;
            *Rte_Pim_TxCtrlSigValue() = STARTAPPLICATION_RETURN_CODE_OK;
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_WDG:
        {
            *Rte_Pim_ActiveComponent() = (EnumActiveComponentType)rxCtrlBuffer;
            *Rte_Pim_TxCtrlSigValue() = STARTAPPLICATION_RETURN_CODE_OK;
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_MEMORYPROTECTION:
        {
            *Rte_Pim_ActiveComponent() = (EnumActiveComponentType)rxCtrlBuffer;
            *Rte_Pim_TxCtrlSigValue() = STARTAPPLICATION_RETURN_CODE_OK;
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_INVALID:
        {
            /* Do nothing here */
            break;
        }
        default:
        {
            *Rte_Pim_TxCtrlSigValue() = STARTAPPLICATION_RETURN_CODE_UNKNOWN_COMPONENT;
            break;
        }
    }
    /* Switch the test application state of all channels to the init state NM_APPL_STATE_FULL_COMM_EXTERN */
    for (channel=0; channel<STARTAPPLICATION_NM_NUMBER_OF_CHANNELS; channel++)
    {
        *Rte_Pim_NM_ApplState() = NM_APPL_STATE_FULL_COMM_EXTERN;
    }
    StartApplication_SendCtrl();

} /* PRQA S 2006, 6030 */ /* MD_MSR_14.7, MD_MSR_STCYC */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_OnDataRec_RxData
 * Description: handle received data dependent on the active use case
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_OnDataRec_RxData(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 rxDataBuffer = StartApplication_ReadData();
    if(rxDataBuffer == STARTAPPLICATION_INVALID_SIGNAL_VALUE)
    {
        return;
    }
    switch(*Rte_Pim_ActiveComponent())
    {
        case STARTAPPLICATION_ACTIVE_COMPONENT_MEM:
        {
            StartApplication_MEM_OnDataRec_RxData(rxDataBuffer);
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_DIAG:
        {
            StartApplication_DIAG_OnDataRec_RxData(rxDataBuffer);
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_NM:
        {
            StartApplication_NM_OnDataRec_RxData(rxDataBuffer);
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_WDG:
        {
            StartApplication_WDG_OnDataRec_RxData(rxDataBuffer);
            break;
        }
        case STARTAPPLICATION_ACTIVE_COMPONENT_MEMORYPROTECTION:
        {
            StartApplication_MEMORYPROTECTION_OnDataRec_RxData(rxDataBuffer);
            break;
        }
        default:
        {
            break;
        }
    }

} /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StartApplication_MEMORYPROTECTION_Cyclic10ms
 * Description: Called every 0.01 seconds.
 * Provokes a memory access violation in the trusted application in case a invalid access is requested.
 *
 *********************************************************************************************************************/
FUNC(void, StartApplication_CODE) StartApplication_MEMORYPROTECTION_Cyclic10ms(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    DtMemoryProtectionDataElementType data;

    if(STARTAPPLICATION_ACTIVE_COMPONENT_MEMORYPROTECTION == *Rte_Pim_ActiveComponent())
    {
        Rte_IrvRead_StartApplication_MEMORYPROTECTION_Cyclic10ms_IrvMemoryProtectionData(&data);
        if(TRUE == data.InvalidAccess)
        {
            data.InvalidAccess = FALSE;
            Rte_IrvWrite_StartApplication_MEMORYPROTECTION_Cyclic10ms_IrvMemoryProtectionData(&data);

            (void)Rte_Call_PpTrustedDataInvalid_Write(data.Value);
        }
        /* else is handled by StartApplication_MEMORYPROTECTION_OnDataRec_RxData */
    }
}

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  START OF FUNCTIONS FOR INTER ECU COMMUNICATION
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_SendCtrl(void)
{
    (void)Rte_Write_PpSignal_StartAppl_TxCtrl_MyECU_omsg_StartAppl_Tx_MyECU_oCAN_b45ea6bd_Tx_DeSignal_StartAppl_TxCtrl_MyECU_omsg_StartAppl_Tx_MyECU_oCAN_b45ea6bd_Tx(*Rte_Pim_TxCtrlSigValue());
}

STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_SendData(void)
{
    (void)Rte_Write_PpSignal_StartAppl_TxData_MyECU_omsg_StartAppl_Tx_MyECU_oCAN_8c58228b_Tx_DeSignal_StartAppl_TxData_MyECU_omsg_StartAppl_Tx_MyECU_oCAN_8c58228b_Tx(*Rte_Pim_TxDataSigValue());
}

STARTAPPLICATION_LOCAL FUNC(uint8, StartApplication_CODE) StartApplication_ReadData(void)
{
    uint8 result = 0;
    (void)Rte_Read_PpSignal_StartAppl_RxData_MyECU_omsg_StartAppl_Rx_MyECU_oCAN_315f9453_Rx_DeSignal_StartAppl_RxData_MyECU_omsg_StartAppl_Rx_MyECU_oCAN_315f9453_Rx(&result);
    return result;
}

STARTAPPLICATION_LOCAL FUNC(uint8, StartApplication_CODE) StartApplication_ReadCtrl(void)
{
    uint8 result = 0;
    (void)Rte_Read_PpSignal_StartAppl_RxCtrl_MyECU_omsg_StartAppl_Rx_MyECU_oCAN_09591065_Rx_DeSignal_StartAppl_RxCtrl_MyECU_omsg_StartAppl_Rx_MyECU_oCAN_09591065_Rx(&result);
    return result;
}

/**********************************************************************************************************************
 *  END OF FUNCTIONS FOR INTER ECU COMMUNICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_COM_CalculateRxData
 * Description: Calculate a substitute value for the RX signals with the same algorithm as the Tester based on the current value of the RxData signal.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_CalculateRxData(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 rxDataBuffer = 0;
    (void)Rte_Read_PpSignal_StartAppl_RxData_MyECU_omsg_StartAppl_Rx_MyECU_oCAN_315f9453_Rx_DeSignal_StartAppl_RxData_MyECU_omsg_StartAppl_Rx_MyECU_oCAN_315f9453_Rx(&rxDataBuffer);
    if( STARTAPPLICATION_INVALID_SIGNAL_VALUE != rxDataBuffer )
    {
        *Rte_Pim_COM_RxSigValue0() = rxDataBuffer;
    }
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_COM_CalculateTxData
 * Description: Calculate the value of the Tx signals based on the current value of the corresponding Rx signals.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_CalculateTxData(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    *Rte_Pim_COM_TxSigValue0() = *Rte_Pim_COM_RxSigValue0();                       /* Scale uint8 [0 ... 0xff] to uint8 [0 ... 0xff] */
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_COM_RXTX_Cyclic
 * Description: Called by StartApplication_Cyclic250ms runnable if COM RxTx use case is active
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_RXTX_Cyclic(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    StartApplication_COM_ReadRxData();
    StartApplication_COM_CalculateTxData();
    StartApplication_COM_WriteTxData();
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_COM_ReadRxData
 * Description: Read the current value of the RX signals from the sender/receiver ports
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_ReadRxData(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 rxDataBuffer = 0;
    (void)Rte_Read_PpSignal_StartAppl_RxData_MyECU_omsg_StartAppl_Rx_MyECU_oCAN_315f9453_Rx_DeSignal_StartAppl_RxData_MyECU_omsg_StartAppl_Rx_MyECU_oCAN_315f9453_Rx(&rxDataBuffer);
    if( STARTAPPLICATION_INVALID_SIGNAL_VALUE != rxDataBuffer )
    {
        *Rte_Pim_COM_RxSigValue0() = rxDataBuffer;
    }
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_COM_TXONLY_Cyclic
 * Description: Called by StartApplication_Cyclic250ms runnable if COM TxOnly use case is active
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_TXONLY_Cyclic(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    StartApplication_COM_CalculateRxData();
    StartApplication_COM_CalculateTxData();
    StartApplication_COM_WriteTxData();
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_COM_WriteTxData
 * Description: Write the current value of the TX signals from the sender/receiver ports
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_COM_WriteTxData(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    (void)Rte_Write_PpSignal_StartAppl_TxData_MyECU_omsg_StartAppl_Tx_MyECU_oCAN_8c58228b_Tx_DeSignal_StartAppl_TxData_MyECU_omsg_StartAppl_Tx_MyECU_oCAN_8c58228b_Tx(*Rte_Pim_COM_TxSigValue0());
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_DIAG_Cyclic
 * Description: Called by StartApplication_Cyclic250ms runnable if DIAG use case is active
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_DIAG_Cyclic(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    *Rte_Pim_TxDataSigValue() = (uint8) Rte_IrvRead_StartApplication_Cyclic250ms_IrvOccuranceCounterDid();
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_DIAG_OnDataRec_RxData
 * Description: Called by StartApplication_OnDataRec_RxData runnable if DIAG use case is active
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_DIAG_OnDataRec_RxData(VAR(uint8, AUTOMATIC) rxDataBuffer) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    if( *Rte_Pim_DIAG_LastRxData() != rxDataBuffer )
    {
        *Rte_Pim_DIAG_LastRxData() = rxDataBuffer;
        switch ( (StartApplicationEnumDiagEventType) (rxDataBuffer & 0x03) ) /* use last two bits only */
        {
            case STARTAPPLICATION_DIAG_SETEVENTTOPASSED:
            {
                VAR(uint16, RTE_VAR_NOINIT) tempCounter;
                (void)Rte_Call_PpDiagnosticMonitor_DEM_EVENT_StartApplication_SetEventStatus(DEM_EVENT_STATUS_PASSED);
                tempCounter = Rte_IrvRead_StartApplication_OnDataRec_RxData_IrvOccuranceCounterDid();
                tempCounter++;
                Rte_IrvWrite_StartApplication_OnDataRec_RxData_IrvOccuranceCounterDid(tempCounter);
                break;
            }
            case STARTAPPLICATION_DIAG_SETEVENTTOFAILED:
            {
                VAR(uint16, RTE_VAR_NOINIT) tempCounter;
                (void)Rte_Call_PpDiagnosticMonitor_DEM_EVENT_StartApplication_SetEventStatus(DEM_EVENT_STATUS_FAILED);
                tempCounter = Rte_IrvRead_StartApplication_OnDataRec_RxData_IrvOccuranceCounterDid();
                tempCounter++;
                Rte_IrvWrite_StartApplication_OnDataRec_RxData_IrvOccuranceCounterDid(tempCounter);
                break;
            }
            case STARTAPPLICATION_DIAG_RESETCOUNTER:
            {
                Rte_IrvWrite_StartApplication_OnDataRec_RxData_IrvOccuranceCounterDid(0);
                break;
            }
            default: break;
        }
    }

}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEM_Cyclic
 * Description: Called by StartApplication_Cyclic250ms runnable if MEM use case is active.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_Cyclic(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    /* if no transaction is active for block 1 and the last transaction was not a read job */
    if ( (*Rte_Pim_MEM_BlockState1() == MEM_STATE_WRITE_FINISHED) || (*Rte_Pim_MEM_BlockState1() == MEM_STATE_WRITE_FAILED) )
    {
        /* signalize read pending */
        *Rte_Pim_MEM_BlockState1() = MEM_STATE_READ_PENDING;
        /* reset data buffer start read job */
        *Rte_Pim_MEM_DataBuffer1() = 0xFFu;
        (void)Rte_Call_PpPS_StartApplication_NvMBlock1_ReadBlock(Rte_Pim_MEM_DataBuffer1());
    }

    /* if no transaction is active for block 2 and the last transaction was not a read job */
    if ( (*Rte_Pim_MEM_BlockState2() == MEM_STATE_WRITE_FINISHED) || (*Rte_Pim_MEM_BlockState2() == MEM_STATE_WRITE_FAILED) )
    {
        /* signalize read pending */
        *Rte_Pim_MEM_BlockState2() = MEM_STATE_READ_PENDING;
        /* reset data buffer start read job */
        *Rte_Pim_MEM_DataBuffer2() = 0xFFu;
        (void)Rte_Call_PpPS_StartApplication_NvMBlock2_ReadBlock(Rte_Pim_MEM_DataBuffer2());
    }
    StartApplication_MEM_DetermineTxCtrlSignal();
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEM_DetermineTxCtrlSignal
 * Description: Set the values for the TxCtrl signal.
 *              Following data is set:
 *
 *              Bit       0     1     2     3     4     5     6     7
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *              TxCtrl | BlockState      | -                     |Block|
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *              BlockState: The block state of the currently active block.
 *              Block:      The currently active block.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_DetermineTxCtrlSignal(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    EnumMEM_BlockStateType* blockState = StartApplication_MEM_GetBlockStatePim(*Rte_Pim_MEM_ActiveBlock());
    *Rte_Pim_TxCtrlSigValue() = STARTAPPLICATION_TX_CTRL_MEM_BLOCK_STATE(*blockState);
    *Rte_Pim_TxCtrlSigValue() |= STARTAPPLICATION_TX_CTRL_MEM_BLOCK_ID(*Rte_Pim_MEM_ActiveBlock());
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEM_DetermineTxDataSignal
 * Description: Set the values for the TxData signal.
 *              Following data is set:
 *
 *              Bit       0     1     2     3     4     5     6     7
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *              TxData | DataValue                   | -         |Block|
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *              DataValue: The value which was read from the currently active block.
 *              Block:     The currently active block.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_DetermineTxDataSignal(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8* dataBuffer = StartApplication_MEM_GetDataBufferPim(*Rte_Pim_MEM_ActiveBlock());
    *Rte_Pim_TxDataSigValue() = STARTAPPLICATION_TX_DATA_MEM_DATA_VALUE(*dataBuffer);
    *Rte_Pim_TxDataSigValue() |= STARTAPPLICATION_TX_DATA_MEM_BLOCK_ID(*Rte_Pim_MEM_ActiveBlock());

}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEM_OnDataRec_RxData
 * Description: Called by StartApplication_OnDataRec_RxData runnable if MEM use case is active.
 *              Following data is received:
 *
 *              Bit       0     1     2     3     4     5     6     7
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *              RxData | DataValue                   |Write|Block|  -  |
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *              DataValue: The value which will be written to the active block.
 *              Write:     If set the data value will be written to the active block.
 *              Block:     Sets the active block.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_OnDataRec_RxData(VAR(uint8, AUTOMATIC) rxDataBuffer) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 dataValue;
    uint8 writeBlock;
    EnumMEM_BlockStateType* blockStateOfActiveBlock;

    *Rte_Pim_MEM_ActiveBlock() = STARTAPPLICATION_RX_DATA_MEM_BLOCK_ID(rxDataBuffer);
    writeBlock = STARTAPPLICATION_RX_DATA_MEM_WRITE_SELECTED(rxDataBuffer);
    dataValue = STARTAPPLICATION_RX_DATA_MEM_DATA_VALUE(rxDataBuffer);
    blockStateOfActiveBlock = StartApplication_MEM_GetBlockStatePim(*Rte_Pim_MEM_ActiveBlock());

    if (writeBlock == 1)
    {
        /* if a write is requested and if no transaction is made on the block and the last transaction was not a write job */
        if ( (*blockStateOfActiveBlock == MEM_STATE_READ_FINISHED) || (*blockStateOfActiveBlock == MEM_STATE_READ_FAILED) )
        {
            /* signalize write pending */
            *blockStateOfActiveBlock = MEM_STATE_WRITE_PENDING;
            /* start write job */
            StartApplication_MEM_WriteBlock(*Rte_Pim_MEM_ActiveBlock(), dataValue);
        }
    }
    else
    {
        /* if only the active block was changed and a read job already finished */
        if (*blockStateOfActiveBlock == MEM_STATE_READ_FINISHED)
        {
            /* send the last read value */
            StartApplication_MEM_DetermineTxDataSignal();
        }
    }

    StartApplication_MEM_DetermineTxCtrlSignal();
    StartApplication_SendCtrl();
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEM_OnDataRec_RxCtrl
 * Description: Called by StartApplication_OnDataRec_RxCtrl runnable if MEM use case is active.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_OnDataRec_RxCtrl(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    *Rte_Pim_TxDataSigValue() = 0u;

    /* activate initial read after use case activation for both blocks */
    if ( (*Rte_Pim_MEM_BlockState1() != MEM_STATE_READ_PENDING) && (*Rte_Pim_MEM_BlockState1() != MEM_STATE_WRITE_PENDING) )
    {
        *Rte_Pim_MEM_BlockState1() = MEM_STATE_WRITE_FINISHED;
    }
    if ( (*Rte_Pim_MEM_BlockState2() != MEM_STATE_READ_PENDING) && (*Rte_Pim_MEM_BlockState2() != MEM_STATE_WRITE_PENDING) )
    {
        *Rte_Pim_MEM_BlockState2() = MEM_STATE_WRITE_FINISHED;
    }
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEM_JobFinished
 * Description: Called from the StartApplication_MEM_JobFinished_XXX runnables.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_JobFinished(
    VAR(NvM_ServiceIdType, AUTOMATIC) ServiceId,
    VAR(NvM_RequestResultType, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) blockId) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    EnumMEM_BlockStateType* blockState = StartApplication_MEM_GetBlockStatePim(blockId);

    switch (ServiceId)
    {
        case NVM_WRITE_BLOCK:
            /* write job finished */
            if (JobResult == NVM_REQ_OK)
            {
                *blockState = MEM_STATE_WRITE_FINISHED;
            }
            else
            {
                *blockState = MEM_STATE_WRITE_FAILED;
            }
            break;
        case NVM_READ_BLOCK:
            /* read job finished */
            if (JobResult == NVM_REQ_OK)
            {
                if (*Rte_Pim_MEM_ActiveBlock() == blockId)
                {
                    StartApplication_MEM_DetermineTxDataSignal();
                    StartApplication_SendData();
                }
                *blockState = MEM_STATE_READ_FINISHED;
            }
            else
            {
                *blockState = MEM_STATE_READ_FAILED;
            }
            break;
        default:
            /* nothing to do for other ServiceIDs */
            break;
    }
    if ( (*Rte_Pim_ActiveComponent() == STARTAPPLICATION_ACTIVE_COMPONENT_MEM) && (*Rte_Pim_MEM_ActiveBlock() == blockId) )
    {
        StartApplication_MEM_DetermineTxCtrlSignal();
        StartApplication_SendCtrl();
    }
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEM_GetBlockStatePim
 * Description: Return a pointer to the PIM containing with current state of the given block ID.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(P2VAR(EnumMEM_BlockStateType, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR), StartApplication_CODE) StartApplication_MEM_GetBlockStatePim(
    VAR(uint8, AUTOMATIC) blockId) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    EnumMEM_BlockStateType* result;
    if (blockId == STARTAPPLICATION_MEM_BLOCK_ID_BLOCK1)
    {
        result = Rte_Pim_MEM_BlockState1();
    }
    else /* blockId == STARTAPPLICATION_MEM_BLOCK_ID_BLOCK2 */
    {
        result = Rte_Pim_MEM_BlockState2();
    }
    return result;
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEM_GetDataBufferPim
 * Description: Return a pointer to the PIM for the data buffer of the given block ID.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(P2VAR(EnumMEM_BlockStateType, AUTOMATIC, RTE_STARTAPPLICATION_APPL_VAR), StartApplication_CODE) StartApplication_MEM_GetDataBufferPim(
    VAR(uint8, AUTOMATIC) blockId) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8* result;
    if (blockId == STARTAPPLICATION_MEM_BLOCK_ID_BLOCK1)
    {
        result = Rte_Pim_MEM_DataBuffer1();
    }
    else /* blockId == STARTAPPLICATION_MEM_BLOCK_ID_BLOCK2 */
    {
        result = Rte_Pim_MEM_DataBuffer2();
    }
    return result;
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEM_WriteBlock
 * Description: Write the given data value to the given block ID using the corresponding data buffer.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEM_WriteBlock(
    VAR(uint8, AUTOMATIC) blockId,
    VAR(uint8, AUTOMATIC) dataValue) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    if (blockId == STARTAPPLICATION_MEM_BLOCK_ID_BLOCK1)
    {
        *Rte_Pim_MEM_DataBuffer1() = dataValue;
        (void)Rte_Call_PpPS_StartApplication_NvMBlock1_WriteBlock(Rte_Pim_MEM_DataBuffer1());
    }
    else /* blockId == STARTAPPLICATION_MEM_BLOCK_ID_BLOCK2 */
    {
        *Rte_Pim_MEM_DataBuffer2() = dataValue;
        (void)Rte_Call_PpPS_StartApplication_NvMBlock2_WriteBlock(Rte_Pim_MEM_DataBuffer2());
    }
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_NM_OnDataRec_RxData
 * Description: handle received data dependent on the active NM use case
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_OnDataRec_RxData(uint8 rxDataBuffer) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 requestedChannel;

    /* Activate the requested communication channel which is set in the remaining bits of the 8bit RxData signal and request the communication mode */
    requestedChannel = rxDataBuffer & (uint8)STARTAPPLICATION_NM_COMM_CHANNEL_MASK;

    if (requestedChannel < STARTAPPLICATION_NM_NUMBER_OF_CHANNELS)
    {
        if (*Rte_Pim_NM_ActiveComMChannel() != requestedChannel)
        {
            /* The channel under test has changed */
            *Rte_Pim_NM_ActiveComMChannel() = requestedChannel;
            /* The new channel is currently in mode FULL_COMM_EXTERN */
            *Rte_Pim_NM_ApplState() = NM_APPL_STATE_FULL_COMM_EXTERN;
            /* The channel requires one or more ComM Users */
            StartApplication_NM_SetActiveComMUser(*Rte_Pim_NM_ActiveComMChannel());
        }
        /* Get the communication mode from the highest bit of the 8bit RxData signal: 1 = FULL communication, 0 = no communication */
        *Rte_Pim_NM_ActiveChannelHasFullComRequest() = (rxDataBuffer & (uint8)STARTAPPLICATION_NM_COMM_MODE_MASK) != 0;
        StartApplication_NM_DetermineTxCtrlSignal();
    }
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_NM_RequestComMode
 * Description: Request the given ComM communication mode for the given channel.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_RequestComMode(uint8 channel, ComM_ModeType comMode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    Std_ReturnType retValue = E_OK;
    if (channel >= STARTAPPLICATION_NM_NUMBER_OF_CHANNELS)
    {
        return;
    }
    switch(channel)
    {
        case 0: /* CT_CAN00*/
        {
            retValue |= Rte_Call_UR_CN_CAN_52ce3533_RequestComMode (comMode);
            break;
        }
        default: /* PRQA S 2018 */ /* MD_StartApplication_2018 */
        {
            retValue = E_NOT_OK;
            break;
        }
    }

} /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_NM_RequestComMUser
 * Description: Request the COMM_FULL_COMMUNICATION for given ComMUser.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_RequestComMUser(uint8 user) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    Std_ReturnType retValue = E_OK;
    switch(user)
    {
        case 0:
        {
            retValue |= Rte_Call_UR_CN_CAN_52ce3533_RequestComMode (COMM_FULL_COMMUNICATION);
            break;
        }
        default:
        {
            retValue = E_NOT_OK;
            break;
        }
    }
} /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_StartApplication_STCAL_6050 */

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_NM_GetCurrentComMode
 * Description: Get the highest ComM mode of all users mapped to the given channel.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_GetCurrentComMode(uint8 channel, ComM_ModeType* comMode)
{
    *comMode = COMM_NO_COMMUNICATION;
    switch(channel)
    {
        case 0: /* CT_CAN00*/
        {
            Std_ReturnType retValue;
            ComM_ModeType userComMode = COMM_NO_COMMUNICATION;
            retValue = Rte_Call_UR_CN_CAN_52ce3533_GetCurrentComMode (&userComMode);
            if ( (retValue == E_OK) && (userComMode > *comMode) )
            {
                *comMode = userComMode;
            }
            break;
        }
        default:
        {
            break;
        }
    }
} /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_NM_SetActiveComMUser
 * Description: Set the active ComM Users for the given channel.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_SetActiveComMUser(uint8 channel) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    switch (channel)
    {
        case 0: /* CT_CAN00*/
        {
            *Rte_Pim_NM_ActiveComMUsers() = 1 << 0;
            break;
        }
        default:
        {
            *Rte_Pim_NM_ActiveComMUsers() = 0;
            break;
        }
    }
}

/**********************************************************************************************************************
 * StartApplication_NM_HandleActiveChannel()
 *********************************************************************************************************************/
/*! \brief       Execute the state machine for the active channel.
 *  \details     In case NoCom is requested for the active channel
 *               Otherwise calling the function has no effect.
 *  \pre         The NM use case is active and the active channel is valid
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
*********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_HandleActiveChannel(void)
{
    if (STARTAPPLICATION_ACTIVE_COMPONENT_NM != *Rte_Pim_ActiveComponent())
    {
        return;
    }
    if ( STARTAPPLICATION_NM_COMM_CHANNEL_INVALID == *Rte_Pim_NM_ActiveComMChannel())
    {
        return;
    }
    if (FALSE != *Rte_Pim_NM_ActiveChannelHasFullComRequest())
    {
        *Rte_Pim_NM_BusSleepModeTimer() = 0;
        *Rte_Pim_NM_ApplState() = NM_APPL_STATE_FULL_COMM_EXTERN;
        StartApplication_NM_RequestComMode(*Rte_Pim_NM_ActiveComMChannel(), COMM_FULL_COMMUNICATION);
    }
    else
    {
        switch(*Rte_Pim_NM_ApplState())
        {
            case NM_APPL_STATE_FULL_COMM_EXTERN:
            {
                /* Tester has switched to no communication */
                StartApplication_NM_RequestComMode(*Rte_Pim_NM_ActiveComMChannel(), COMM_NO_COMMUNICATION);
                *Rte_Pim_NM_ApplState() = NM_APPL_STATE_NO_COMM_EXTERN;
                *Rte_Pim_NM_BusSleepModeTimer() = 0;
                break;
            }
            case NM_APPL_STATE_NO_COMM_EXTERN:
            {
                ComM_ModeType comMMode;
                StartApplication_NM_GetCurrentComMode(*Rte_Pim_NM_ActiveComMChannel(), &comMMode);
                if (0 == *Rte_Pim_NM_BusSleepModeTimer())
                {
                    /* Timer T1 is not running */
                    if (COMM_NO_COMMUNICATION == comMMode)
                    {
                        /* Bus is in NoCom --> start timer T1 */
                        *Rte_Pim_NM_BusSleepModeTimer() = STARTAPPLICATION_NM_DURATION_T1;
                    }
                }
                else
                {
                    /* Timer T1 is running */
                    if (*Rte_Pim_NM_BusSleepModeTimer() > 1)
                    {
                        (*Rte_Pim_NM_BusSleepModeTimer())--;
                        if (COMM_FULL_COMMUNICATION == comMMode)
                        {
                            /* Bus is in FullCom although it was not requested --> wakeup by bus occurred */
                            /* Stop timer T1, it will be restarted once the channel is in NoCom */
                            *Rte_Pim_NM_BusSleepModeTimer() = 0;
                        }
                    }
                    else
                    {
                        /* T1 timer has expired, request full communication, restart the T2 timer, switch to the internal full communication state */
                        StartApplication_NM_RequestComMode(*Rte_Pim_NM_ActiveComMChannel(), COMM_FULL_COMMUNICATION);
                        *Rte_Pim_NM_ApplState() = NM_APPL_STATE_FULL_COMM_INTERN;
                        *Rte_Pim_NM_BusSleepModeTimer() = STARTAPPLICATION_NM_DURATION_T2;
                    }
                }
                break;
            }
            case NM_APPL_STATE_FULL_COMM_INTERN:
            {
                if (0 != *Rte_Pim_NM_BusSleepModeTimer())
                {
                    /* Timer T2 is running */
                    if (*Rte_Pim_NM_BusSleepModeTimer() > 1)
                    {
                        (*Rte_Pim_NM_BusSleepModeTimer())--;
                        StartApplication_NM_DetermineTxCtrlSignal();
                    }
                    else
                    {
                        /* T2 timer has expired, request no communication, restart the T1 timer, send the TxCtrl signal with value 0 (=no communication) and switch to the external no communication state */
                        StartApplication_NM_RequestComMode(*Rte_Pim_NM_ActiveComMChannel(), COMM_NO_COMMUNICATION);
                        *Rte_Pim_NM_BusSleepModeTimer() = 0;
                        *Rte_Pim_NM_ApplState() = NM_APPL_STATE_NO_COMM_EXTERN;
                        StartApplication_NM_DetermineTxCtrlSignal();
                    }
                }
                break;
            }
            default:
            {
                *Rte_Pim_NM_ApplState() = NM_APPL_STATE_FULL_COMM_EXTERN; /* Set to init state */
                break;
            }
        } /* end of switch(*Rte_Pim_NM_ApplState()[channel]) */
    }
} /* PRQA S 2006, 6030, 6080 */ /* MD_MSR_14.7, MD_MSR_STCYC, MD_MSR_STMIF */

/**********************************************************************************************************************
 * StartApplication_NM_HandleInactiveChannels
 *********************************************************************************************************************/
/*! \brief       Request FullCommunication for each channel unless the channel is the active channel in the NM use case.
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
*********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_HandleInactiveChannels(void)
{
    uint8 i;
    if (*Rte_Pim_ActiveComponent() == STARTAPPLICATION_ACTIVE_COMPONENT_NM)
    {
        for (i = 0; i < STARTAPPLICATION_NM_MAX_COMMUSERS; i++)
        {
            if (0 == (*Rte_Pim_NM_ActiveComMUsers() & (uint32)(1 << i)))
            {
                StartApplication_NM_RequestComMUser(i);
            }
        }
    }
    else
    {
        for (i = 0; i < STARTAPPLICATION_NM_NUMBER_OF_CHANNELS; i++)
        {
            StartApplication_NM_RequestComMode(i, COMM_FULL_COMMUNICATION);
        }
    }
}


/**********************************************************************************************************************
 * StartApplication_NM_DetermineTxCtrlSignal()
 *********************************************************************************************************************/
/*! \brief       Set the TxCtrl signal as follows: Bits 0..5 = channel, Bit 6 = internal NW request, Bit 7: external NW request
 *  \pre         The NM use case is active
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
*********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_NM_DetermineTxCtrlSignal(void)
{
    *Rte_Pim_TxCtrlSigValue() = *Rte_Pim_NM_ActiveComMChannel();
    if (NM_APPL_STATE_FULL_COMM_INTERN == *Rte_Pim_NM_ApplState())
    {
        *Rte_Pim_TxCtrlSigValue() |= 0x40u;
    }
    if (NM_APPL_STATE_FULL_COMM_EXTERN == *Rte_Pim_NM_ApplState())
    {
        *Rte_Pim_TxCtrlSigValue() |= 0x80u;
    }
}


/**********************************************************************************************************************
 * StartApplication_WDG_OnDataRec_RxData()
 *********************************************************************************************************************/
/*! \brief       Set the alive indication cycle time to the value received via RxData signal.
 *  \details     Called by StartApplication_OnDataRec_RxData runnable.
 *  \pre         The WDG use case is active
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
*********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_WDG_OnDataRec_RxData(VAR(uint8, AUTOMATIC) rxData) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    /* Ignore RxData values for 1 second after startup to prevent a possible reset caused by old too high RxData values */
    if(0 < *Rte_Pim_Uptime())
    {
        *Rte_Pim_WDG_AliveCycle() = rxData/10;
    }
}

/**********************************************************************************************************************
 * StartApplication_WDG_DetermineTxDataSignal()
 *********************************************************************************************************************/
/*! \brief       Set the TxData signal to the current uptime.
 *  \pre         The WDG use case is active
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
*********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_WDG_DetermineTxDataSignal(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    *Rte_Pim_TxDataSigValue() = *Rte_Pim_Uptime();
}

/**********************************************************************************************************************
 * StartApplication_WDG_HandleCheckpoint()
 *********************************************************************************************************************/
/*! \brief       Call CheckpointReached of the WdgM depending on the given cycle time.
 *  \pre         The WDG use case is active
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
*********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_WDG_HandleCheckpoint(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    if(*Rte_Pim_WDG_AliveTimer() >= *Rte_Pim_WDG_AliveCycle())
    {
        (void)Rte_Call_PpAliveWdgMSupervisedEntity_StartApplication_CheckpointReached(STARTAPPLICATION_WDG_CHECKPOINT_ID);
        *Rte_Pim_WDG_AliveTimer() = 0;
    }
    (*Rte_Pim_WDG_AliveTimer())++;
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEMORYPROTECTION_OnDataRec_RxData
 * Description: Called by StartApplication_OnDataRec_RxData runnable if the MEMORYPROTECTION use case is active.
 *              Propagate the received DataValue to the trusted application.
 *              Following data is received:
 *
 *              Bit       0     1     2     3     4     5     6     7
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *              RxData | DataValue                         | Mode|  -  |
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *              DataValue: The data value which will be sent to the trusted application.
 *              Mode:      Valid or invalid access of the IRV of the trusted application.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEMORYPROTECTION_OnDataRec_RxData(VAR(uint8, AUTOMATIC) rxData) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    DtMemoryProtectionDataElementType data;
    data.Value = rxData & 0x3F;
    data.InvalidAccess = ((rxData >> 6) & 0x01) == 0x01 ? TRUE : FALSE;

    /* reset current violation state */
    (void)Rte_Call_PpMemoryAccessViolationState_Reset();

    Rte_IrvWrite_StartApplication_OnDataRec_RxData_IrvMemoryProtectionData(&data);

    if(FALSE == data.InvalidAccess)
    {
        (void)Rte_Write_PpTrustedData_DeValue(data.Value);
    }
    /* else is handled by StartApplication_MEMORYPROTECTION_Cyclic10ms */
}

/**********************************************************************************************************************
 *
 * Local Function Entity Name: StartApplication_MEMORYPROTECTION_DetermineTxDataSignal
 * Description: Set the values for the TxData signal.
 *              Following data is set:
 *
 *              Bit       0     1     2     3     4     5     6     7
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *              TxData | DataValue                         |State|  -  |
 *                     +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *              DataValue: The IRV value which was set from the trusted application.
 *              State:     The result of the last write access to the IRV of the trusted application.
 *
 *********************************************************************************************************************/
STARTAPPLICATION_LOCAL FUNC(void, StartApplication_CODE) StartApplication_MEMORYPROTECTION_DetermineTxDataSignal(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
    uint8 data;
    boolean state;

    (void)Rte_Read_PpTrustedDataVerification_DeValue(&data);
    (void)Rte_Call_PpMemoryAccessViolationState_GetState(&state);
    *Rte_Pim_TxDataSigValue() = data & 0x3F;
    if(TRUE == state)
    {
        *Rte_Pim_TxDataSigValue() |= 0x40;
    }
}

#define StartApplication_STOP_SEC_CODE
#include "StartApplication_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:

  MD_StartApplication_2018: MISRA rule: 14.1
      Reason:     Default label is provided as a defensive measure against possible future code changes and to comply with rule 15.3.
      Risk:       There is no risk.
      Prevention: Not applicable.

  MD_StartApplication_STCAL_6050:
    Reason:     Number of distinct function calls depends on the configuration.
    Risk:       There is no risk.
    Prevention: Not applicable.
*/

/**********************************************************************************************************************
  END OF FILE: StartApplication.c
**********************************************************************************************************************/

