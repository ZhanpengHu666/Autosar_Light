/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Can
 *           Program: MSR_Vector_SLP4
 *          Customer: Harman International (China) Holdings Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: FS32K148UAT0VLQR
 *    License Scope : The usage is restricted to CBD1800257_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Can_Lcfg.c
 *   Generation Time: 2021-06-07 15:44:20
 *           Project: S32K144_Start - Version 1.0
 *          Delivery: CBD1800257_D01
 *      Tool Version: DaVinci Configurator  5.18.37 SP1
 *
 *
 *********************************************************************************************************************/


#define CAN_LCFG_SOURCE

/* PRQA S 0857 EOF */ /* MD_Can_0857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/* -----------------------------------------------------------------------------
    Includes
 ----------------------------------------------------------------------------- */

#include "Can_Cfg.h"

/* -----------------------------------------------------------------------------
    Hw specific
 ----------------------------------------------------------------------------- */



/**********************************************************************************************************************
  ComStackLib
**********************************************************************************************************************/
/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  Can_CanIfChannelId
**********************************************************************************************************************/
/** 
  \var    Can_CanIfChannelId
  \brief  indirection table Can to CanIf controller ID
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_CanIfChannelIdType, CAN_CONST) Can_CanIfChannelId[1] = {
  /* Index    CanIfChannelId      Comment */
  /*     0 */             0u   /* [CT_CAN00_9df8a959] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerConfig
**********************************************************************************************************************/
/** 
  \var    Can_ControllerConfig
  \brief  Global configuration for all controllers
  \details
  Element                            Description
  BaseAddress                    
  InterruptMask1                 
  InterruptMask2                 
  RFFN                           
  CanControllerDefaultBaudrate   
  MailboxRxBasicEndIdx               the end index of the 0:n relation pointing to Can_Mailbox
  MailboxRxBasicLength               the number of relations pointing to Can_Mailbox
  MailboxRxBasicStartIdx             the start index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicEndIdx               the end index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicLength               the number of relations pointing to Can_Mailbox
  MailboxTxBasicStartIdx             the start index of the 0:n relation pointing to Can_Mailbox
  MailboxUnusedEndIdx                the end index of the 0:n relation pointing to Can_Mailbox
  MailboxUnusedLength                the number of relations pointing to Can_Mailbox
  MailboxUnusedStartIdx              the start index of the 0:n relation pointing to Can_Mailbox
  NumberOfFilters                
  NumberOfFullConfigurableFilters
  NumberOfMaxMailboxes           
  RxBasicHwStart                 
  RxBasicHwStop                  
  RxFullHwStart                  
  RxFullHwStop                   
  TxBasicHwStart                 
  TxBasicHwStop                  
  TxFullHwStart                  
  TxFullHwStop                   
  UnusedHwStart                  
  UnusedHwStop                   
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_ControllerConfigType, CAN_CONST) Can_ControllerConfig[1] = {
    /* Index    BaseAddress   InterruptMask1  InterruptMask2  RFFN          CanControllerDefaultBaudrate  MailboxRxBasicEndIdx                                                                                                                                           MailboxRxBasicLength                                                                                                                                           MailboxRxBasicStartIdx                                                                                                                                           MailboxTxBasicEndIdx                                                                                                                                           MailboxTxBasicLength                                                                                                                                           MailboxTxBasicStartIdx                                                                                                                                           MailboxUnusedEndIdx                                                                                                                                          MailboxUnusedLength                                                                                                                                          MailboxUnusedStartIdx                                                                                                                                          NumberOfFilters  NumberOfFullConfigurableFilters  NumberOfMaxMailboxes  RxBasicHwStart  RxBasicHwStop  RxFullHwStart  RxFullHwStop  TxBasicHwStart  TxBasicHwStop  TxFullHwStart  TxFullHwStop  UnusedHwStart  UnusedHwStop        Comment                         Referable Keys */
  { /*     0 */ 0x40024000uL,   0x00000101uL,   0x00000000uL, 0x00000000uL,                         500u,                   2u  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                   1u  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                     1u  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                   1u  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                   1u  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                     0u  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                  3u  /* UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                  1u  /* UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,                    2u  /* UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController) */,           0x08u,                           0x08u,                0x20u,             0u,            1u,            8u,           8u,             8u,            9u,            9u,           9u,            0u,           0u }   /* [CT_CAN00_9df8a959] */  /* [/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitBasicCan
**********************************************************************************************************************/
/** 
  \var    Can_InitBasicCan
  \brief  This table contains acceptance filter configuration values.
  \details
  Element     Description
  InitCode
  InitMask
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitBasicCanType, CAN_CONST) Can_InitBasicCan[8] = {
    /* Index    InitCode      InitMask            Comment */
  { /*     0 */ 0x00000000uL, 0x0003FFFFuL },  /* [Channel: CT_CAN00_9df8a959, Init object: 0, Filter: CanFilterMask] */
  { /*     1 */ 0x00000000uL, 0x1FFFFFFFuL },  /* [Channel: CT_CAN00_9df8a959, Init object: 0, Filters that are not configurable] */
  { /*     2 */ 0x00000000uL, 0x1FFFFFFFuL },  /* [Channel: CT_CAN00_9df8a959, Init object: 0, Filters that are not configurable] */
  { /*     3 */ 0x00000000uL, 0x1FFFFFFFuL },  /* [Channel: CT_CAN00_9df8a959, Init object: 0, Filters that are not configurable] */
  { /*     4 */ 0x00000000uL, 0x1FFFFFFFuL },  /* [Channel: CT_CAN00_9df8a959, Init object: 0, Filters that are not configurable] */
  { /*     5 */ 0x00000000uL, 0x1FFFFFFFuL },  /* [Channel: CT_CAN00_9df8a959, Init object: 0, Filters that are not configurable] */
  { /*     6 */ 0x00000000uL, 0x1FFFFFFFuL },  /* [Channel: CT_CAN00_9df8a959, Init object: 0, Filters that are not configurable] */
  { /*     7 */ 0x00000000uL, 0x1FFFFFFFuL }   /* [Channel: CT_CAN00_9df8a959, Init object: 0, Filters that are not configurable] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitBasicCanIndex
**********************************************************************************************************************/
/** 
  \var    Can_InitBasicCanIndex
  \brief  This table contains start/stop indices for the Can_InitBasicCan table.
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitBasicCanIndexType, CAN_CONST) Can_InitBasicCanIndex[1] = {
  /* Index    InitBasicCanIndex                                                                        */
  /*     0 */           0x0000u  /* Filter Start Index: Channel: CT_CAN00_9df8a959, Init object: 0 */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObject
**********************************************************************************************************************/
/** 
  \var    Can_InitObject
  \brief  This table contains information about the init object: e.g. bustiming register contents.
  \details
  Element     Description
  CBT     
  Control1
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitObjectType, CAN_CONST) Can_InitObject[1] = {
    /* Index    CBT           Control1            Comment */
  { /*     0 */ 0x80E018A5uL, 0x072D2006uL }   /* ["CT_CAN00_9df8a959 - CanControllerBaudrateConfig", init object index: 0] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectBaudrate
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectBaudrate
  \brief  baudrates ('InitStruct' as index)
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitObjectBaudrateType, CAN_CONST) Can_InitObjectBaudrate[1] = {
  /* Index    InitObjectBaudrate      Comment */
  /*     0 */               500u   /* [CT_CAN00_9df8a959 - CanControllerBaudrateConfig] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectStartIndex
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectStartIndex
  \brief  Start index of 'InitStruct' / baudratesets (controllers as index)
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitObjectStartIndexType, CAN_CONST) Can_InitObjectStartIndex[2] = {
  /* Index    InitObjectStartIndex      Comment */
  /*     0 */                   0u,  /* [CT_CAN00_9df8a959] */
  /*     1 */                   1u   /* [stop index] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_Mailbox
**********************************************************************************************************************/
/** 
  \var    Can_Mailbox
  \brief  mailbox configuration (over all controllers)
  \details
  Element                Description
  ControllerConfigIdx    the index of the 1:1 relation pointing to Can_ControllerConfig
  IDValue            
  DLC_FIFO           
  HwHandle           
  MailboxType        
  MaxDataLen         
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_MailboxType, CAN_CONST) Can_Mailbox[3] = {
    /* Index    ControllerConfigIdx                                                        IDValue  DLC_FIFO  HwHandle  MailboxType                                MaxDataLen        Comment                            Referable Keys */
  { /*     0 */                  0u  /* /ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 */, 0x0000u,       1u,       8u, CAN_TX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX,         8u },  /* [CN_CAN00_5e566ad9_Tx] */  /* [/ActiveEcuC/Can/CanConfigSet/CN_CAN00_5e566ad9_Tx (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanHardwareObject), /ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959, TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController)] */
  { /*     1 */                  0u  /* /ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 */, 0x0000u,       1u,       0u, CAN_RX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX,         8u },  /* [CN_CAN00_770af0b0_Rx] */  /* [/ActiveEcuC/Can/CanConfigSet/CN_CAN00_770af0b0_Rx (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanHardwareObject), /ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959, RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController)] */
  { /*     2 */                  0u  /* /ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 */, 0x0000u,      23u,       9u,  CAN_UNUSED_CAN_TYPE_MAILBOXTYPEOFMAILBOX,         0u }   /* []                     */  /* [undefined, /ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959, UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_9df8a959 (DefRef: /MICROSAR/Can_ImxFlexcan3/Can/CanConfigSet/CanController)] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_TxOffsetHwToLog
**********************************************************************************************************************/
/** 
  \var    Can_TxOffsetHwToLog
  \brief  tx hardware to logical handle indirection table
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_TxOffsetHwToLogType, CAN_CONST) Can_TxOffsetHwToLog[1] = {
  /* Index    TxOffsetHwToLog      Comment */
  /*     0 */              -8   /* [CT_CAN00_9df8a959] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_ActiveSendObject
**********************************************************************************************************************/
/** 
  \var    Can_ActiveSendObject
  \brief  temporary data for TX object
  \details
  Element    Description
  Pdu        buffered PduId for confirmation or cancellation
  State      send state like cancelled or send activ
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Can_ActiveSendObjectType, CAN_VAR_NOINIT) Can_ActiveSendObject[2];
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerData
**********************************************************************************************************************/
/** 
  \var    Can_ControllerData
  \brief  struct for all controller related variable data
  \details
  Element                  Description
  BusOffCounter            This variable stores the busoff recovery timeout counter.
  CanInterruptCounter      CAN interrupt disable counter for each controller
  IsBusOff                 CAN state for each controller: busoff occur
  LastInitObject           last set baudrate for reinit
  LogStatus                CAN state for each controller: UNINIT=0x00, START=0x01, STOP=0x02, INIT=0x04, INCONSISTENT=0x08, WARNING =0x10, PASSIVE=0x20, BUSOFF=0x40, SLEEP=0x80
  StartModeRequested       This variable stores if the start mode is of a special CAN Controller is already requested in the busoff recovery process.
  StatusReq                CAN state request for each controller: START=0x01, STOP=0x02, WAKEUP=0x08, SLEEP=0x80
  CanInterruptOldStatus    last CAN interrupt status for restore interrupt for each controller
  LoopTimeout              hw loop timeout for each controller
  RxMsgBuffer              This variable stores received values (ID, DLC, DATA) in the reception process.
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Can_ControllerDataType, CAN_VAR_NOINIT) Can_ControllerData[1];
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/




