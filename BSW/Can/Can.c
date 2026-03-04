/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 120 */

/* STARTSINGLE_OF_MULTIPLE */

/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file     Can.c / Can_Local.h
 *  \brief    Implementation of the CAN driver
 *  \details  see functional description below
 *
 *********************************************************************************************************************/
/* ***************************************************************************
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Ml           Patrick Markl             Vector Informatik GmbH
| Bir          Holger Birke              Vector Informatik GmbH
| Rse          Robert Schelkle           Vector Informatik GmbH
| Was          Andreas Weinrauch         Vector Informatik GmbH
| Zam          Artjom Zabirko            Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Rli          Roman Linder              Vector Informatik GmbH
| Bns          Benjamin Schuetterle      Vector Informatik GmbH
| Gaz          Carsten Gauglitz          Vector Informatik GmbH
| Yoe          Yacine Ouldboukhitine     Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 2012-01-09  1.00.00  Rse    - ESCAN00056163: Initial version: Hll - Flexcan3 - Imx6 - QCC - High-End - QNX
| 2012-09-20  1.01.00  Rse    - ESCAN00062414: Support workaround for erratum ERR005829
| 2013-01-30  1.02.00  Rse    - ESCAN00065347: Support platform MPC5700
|                             - ESCAN00064665: CANbedded only: CAN messages will not be sent any more
|                             - ESCAN00066667: Support workaround for erratum e5769
|                             - ESCAN00067035: Inconsistent combination of receive handle and receive information (id, dlc, data) is indicated to upper layer
| 2013-05-21  1.03.00  Rse    - ESCAN00067478: Support FlexCAN2 derivatives for RxFifo usage
|                             - ESCAN00067660: Support the feature Mirror Mode
| 2013-07-22  1.04.00  Rse    - ESCAN00069229: Support CAN message retransmit feature for FBL driver
|                             - ESCAN00070121: Support Vybrid with FlexCAN3
| 2013-11-21  1.05.00  Rse    - ESCAN00072129: ASR4 only: change BusOff behavior to ensure recovery time of 128x11 recessive bits
|                             - ESCAN00072322: AR4-328: Predefined Runtime Measurement Points
| 2013-12-09  1.06.00  Rse    - ESCAN00072515: AutoSar only: Can_SetControllerMode(controller, CAN_T_STOP) returns CAN_OK instead of CAN_NOT_OK
|                             - ESCAN00072597: CANbedded only: Retransmit does not work if more than 22 RxFullCAN objects are used
| 2014-01-08  1.07.00  Rse    - ESCAN00072828: CANbedded only: Compiler error: identifier "canCanInterruptCounter" is undefined
|                             - ESCAN00072863: Support Cancel in Hardware with Transmission Abort feature
|                             - ESCAN00072869: Support new interface for Bus Mirroring
| 2014-01-30  1.07.01  Rse    - ESCAN00073299: Parity check only available for Vybrid and MPC5700 derivatives
| 2014-02-06  1.07.02  Rse    - Some minor MISRA improvements
|                      Rse    - ESCAN00073889: CANbedded only: Compiler error: struct has unknown field
| 2014-03-24  1.07.03  Rse    - ESCAN00074424: Indication function is called twice for the reception of one BasicCAN message
| 2014-04-16  1.08.00  Rse    - ESCAN00075110: BusOff notification is called twice for one single BusOff event (FlexCAN2)
|                             - ESCAN00075955: Remove obsolete workaround implementation for e5769
|                             - ESCAN00075964: Delete unnecessary interrupt locks
|                             - ESCAN00075507: IAR Compiler warning: the order of volatile accesses is undefined
| 2014-06-24  1.09.00  Rse    - ESCAN00076588: CAN clock settings are invalid after reinitialization, error frames occur continuously on the bus
|                             - ESCAN00076653: Implement proper mode switch to init (FREEZE) mode in CAN controller initialization process
|                             - ESCAN00076657: MAXMB value is obsolete
|                             - ESCAN00077049: CANbedded only: Support Tx FullCAN Send Delay (External PIA)
|                             - ESCAN00077083: CANbedded only: LowLevel Message is not transmitted
|                             - ESCAN00077485: OS Exception when CAN driver is handled in User Mode
| 2014-08-13  1.10.00  Rse    - ESCAN00077825: Support derivative MPC5748G CUT2
| 2014-11-10  1.10.01  Rse    - ESCAN00079385: Compiler warning: argument of type "volatile uint32 *" is incompatible with parameter of type "volatile uint16 *"
| 2014-11-27  2.00.00  Rse    - ESCAN00078072: Support full functionality for CAN-FD (Mode 2)
|                             - ESCAN00079900: CANbedded only: Extended ID message with dominant SRR-Bit does not receive
|                             - ESCAN00079901: Support ComStackLib tables for ASR403 R11
|                             - ESCAN00079494: Add loop checks for mode switching in CAN Controller initialization process
| 2015-01-21  2.00.01  Rse    - ESCAN00080716: Standard CAN message is sent as CAN-FD message with baudrate switch
| 2015-04-09  2.00.02  Was    - ESCAN00082335: Update to Core 5.00.02, R11 (Vybrid)
| 2015-05-02  2.01.00  Rse    - ESCAN00082800: Support CANbedded compatibility
| 2015-09-02  2.02.00  Zam    - ESCAN00084930: Support Extended CAN RAM Check feature
| 2015-10-14  2.03.00  Pl     - ESCAN00085860: Support S32K with FlexCAN3
| 2015-12-03  3.00.00  Rse    - ESCAN00086974: Support R14 and process 3.0
| 2016-03-17  3.01.00  Rse    - ESCAN00088969: Support Extended RAM check for MSR403
| 2016-05-30  3.01.01  Rse    - ESCAN00090210: Compiler error: parse error near ';'
| 2016-06-20  3.01.02  Rse    - Update HL-ASR 5.04.01 for issue 89754
| 2016-08-03  3.01.03  Rse    - ESCAN00091088: Callback that indicates corrupt CAN Controller is called erroneously
| 2016-08-25  3.02.00  Rse    - ESCAN00091626: Support R14 for Arm32 platforms
|                             - ESCAN00092139: Support ISO CAN-FD
|                             - ESCAN00092218: Support possibility to use a non-CAN-FD baudrate on a CAN-FD channel
|                             - ESCAN00092333: Support asymmetric mailboxes
| 2016-10-26  3.02.01  Rse    - ESCAN00092531: Linker Error: undefined symbol found 'Can_GetCanNumberOfMaxMailboxes'
| 2016-12-12  3.02.02  Rli    - ESCAN00093255: CAN FD FULL support for Little Endian Architectures
| 2017-03-30  3.02.03  Rli    - ESCAN00094552: Compiler error: identifier Controller not declared
|                             - ESCAN00094764: MWCT101xS Support
| 2017-04-21  3.03.00  Rli    - ESCAN00094816: Support of Virtual Addressing
| 2017-09-05  3.03.03  Rli    - ESCAN00096527 Compiler warning: unused argument
| 2017-10-31  5.00.00  Rli    - ESCAN00097302 Support of SafeBSW for FlexCAN3
| 2018-03-08  5.00.01  Bns    - Update HL-ASR 5.07.02 for issue 96367
|                             - ESCAN00098678 Support Extended RAM Check for S32 
| 2018-03-12  5.01.00  Gaz    - ESCAN00098459 Update to Core 6.00.00
| 2018-06-19  5.02.00  Rli    - ESCAN00099727 Support of Virtual Addressing with CAN FD Mode 2
| 2018-08-02  5.03.00  Rli    - STORYC-6186: Support Silent Mode
|                             - ESCAN00100316 IMX8: Messages not received with CAN FD configuration
| 2018-10-19  5.04.00  Yoe    - STORYC-6683: Support SafeBsw for Asymmetric Mailboxes
| 2018-10-31  5.04.01  Yoe    - STORYC-6877: Support SafeBsw for S32k1xx derivatives
| 2018-11-22  5.04.02  Rli    - STORYC-7138: Update code due to Cfg5 bugfix
|************************************************************************** */

/* \trace SPEC-1570 */
/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
/* ECO_IGNORE_BLOCK_BEGIN */
#define C_DRV_INTERNAL /* compatibility */
#define CAN_SOURCE     /* testability */
#define __CAN_SRC__              /* compatibility RTM not aware of multi driver instance */
#if !defined(__CAN_SRC__) /* driver use ORGANI without infix */ /* COV_CAN_INTERNAL */
# define __CAN_SRC__    /* for all MSR module (used by RTM) */
#endif
/* PRQA S 3109 EOF */ /* MD_Can_3109 */
/* PRQA S 0750 EOF */ /* MD_Can_0750 */
/* PRQA S 3412 EOF */ /* MD_Can_3412 */
/* PRQA S 3458 EOF */ /* MD_Can_3458 */
/* PRQA S 3453 EOF */ /* MD_Can_3453 */
/* PRQA S 0850 EOF */ /* MD_Can_0850 */
/* PRQA S 0857 EOF */ /* MD_Can_0857 */
/* PRQA S 0828 EOF */ /* MD_Can_0828 */
/* PRQA S 0715 EOF */ /* MD_Can_0715 */

/* \trace SPEC-1408, SPEC-1590, SPEC-1588 */
/* \trace SPEC-1392 */
#include "CanIf_Cbk.h"   /* for callback declaration */
/* \trace SPEC-1707 */
#include "CanIf.h"       /* for version check */
#include "Can_Local.h"    /* have to be last include due to channel define will lead to problems */


#if (CAN_DEV_ERROR_REPORT == STD_ON)
/* \trace SPEC-1596 */
# include "Det.h"
#endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
#  include "v_ver.h"
# endif
#endif

#if !defined(CAN_AMD_RUNTIME_MEASUREMENT) /* COV_CAN_COMPATIBILITY */
# define CAN_AMD_RUNTIME_MEASUREMENT STD_OFF
#endif
#if (CAN_AMD_RUNTIME_MEASUREMENT == STD_ON) /* COV_CAN_AMD_RUNTIME_MEASUREMENT */
# include "AmdRtm.h"
#endif

#if !defined(CAN_RUNTIME_MEASUREMENT_SUPPORT) /* COV_CAN_COMPATIBILITY */
# define CAN_RUNTIME_MEASUREMENT_SUPPORT STD_OFF
#endif
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
/* AR4-328 */
# define C_ENABLE_RUNTIME_MEASUREMENT_SUPPORT
# include "Rtm.h"
#endif

#if defined(C_ENABLE_CAN_FD_FULL)
# if defined(C_ENABLE_CANCEL_IN_HW) || defined(C_ENABLE_RX_QUEUE)
#  include "vstdlib.h"
# endif
#endif

/* ECO_IGNORE_BLOCK_END */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_COREVERSION           != 0x0600u) /* \trace SPEC-1699, SPEC-3837 */
# error "Source and Header file are inconsistent!"
#endif
#if (CAN_RELEASE_COREVERSION   != 0x00u)
# error "Source and Header file are inconsistent!"
#endif
#if defined(CAN_GEN_BASE_VERSION) /* COV_CAN_COMPATIBILITY */
# if (CAN_GEN_BASE_VERSION              != 0x0106u)
#  error "Source and Generated Header file are inconsistent!"
# endif
#elif defined(CAN_GEN_BASE_CFG5_VERSION) /* COV_CAN_COMPATIBILITY */
# define CAN_GEN_BASE_VERSION  CAN_GEN_BASE_CFG5_VERSION
# if (CAN_GEN_BASE_CFG5_VERSION         != 0x0103u)
#  error "Source and Generated Header file are inconsistent!"
# endif
#else
# error "No CAN_GEN_BASE_VERSION nor CAN_GEN_BASE_CFG5_VERSION is defined"
#endif
#if( DRVCAN_IMXFLEXCAN3ASR_VERSION != 0x0504)
 #error "Source and Header file are inconsistent!"
#endif

#if( DRVCAN_IMXFLEXCAN3ASR_RELEASE_VERSION != 0x02)
 #error "Source and Header file are inconsistent!"
#endif

#if( CAN_GEN_ImxFlexcan3Asr_VERSION != 0x0101)
# error "Generated Data are inconsistent!"
#endif

#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
/* The name of this constant variable is defined via v_ver.h and depends on the version of the C file. The value of the constant variable is also defined externally and is used for consistency checks, too. */
#  define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_DEF_CONST(V_NONE, uint32, CONST) DRVCAN_IMXFLEXCAN3ASR_LIB_SYMBOL = DRVCAN_IMXFLEXCAN3ASR_LIB_VERSION;   /* PRQA S 3408 */ /* MD_Can_Asr_3408_libCheck */
#  define CAN_STOP_SEC_CONST_UNSPECIFIED   /*--------------------------------*/
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif
#endif

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
#if defined(CAN_USE_NO_VECTOR_IF) /* for testability */
# define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#else
# if defined(CANIF_VENDOR_ID) /* COV_CAN_COMPATIBILITY */
#  if (CANIF_VENDOR_ID == 0x001E) /* COV_CAN_COMPATIBILITY */
#   define CAN_USE_VECTOR_IF
#   if defined(IF_ASRIFCAN_VERSION) /* COV_CAN_COMPATIBILITY */
#    if (IF_ASRIFCAN_VERSION < 0x0410) /* COV_CAN_COMPATIBILITY */
#     define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#    endif
#   endif
#  else
#   define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#  endif
# else
#  define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
# endif
#endif
/* Compatibility to CBD */
/* instead of direct canCanInterruptCounter[] use Can_GetCanInterruptCounter(Index) abstraction for ComStackLib */

#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
# define CanHookBegin_Can_Init()                              Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Init)
# define CanHookEnd_Can_Init()                                Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Init)
# define CanHookBegin_Can_InitController()                    Rtm_Start(RtmConf_RtmMeasurementPoint_Can_InitController)
# define CanHookEnd_Can_InitController()                      Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_InitController)
# define CanHookBegin_Can_SetControllerMode()                 Rtm_Start(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
# define CanHookEnd_Can_SetControllerMode()                   Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
# define CanHookBegin_Can_Write()                             Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Write)
# define CanHookEnd_Can_Write()                               Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Write)

#else /* BRS runtime measurement */
# define CanHookBegin_Can_Init()
# define CanHookEnd_Can_Init()
# define CanHookBegin_Can_InitController() \

# define CanHookEnd_Can_InitController() \

# define CanHookBegin_Can_SetControllerMode() \

# define CanHookEnd_Can_SetControllerMode() \

# define CanHookBegin_Can_Write() \

# define CanHookEnd_Can_Write() \

#endif

#define CanHookBegin_CanHL_TxConfirmation() \

#define CanHookEnd_CanHL_TxConfirmation() \

#define CanHookBegin_CanBasicCanMsgReceived() \

#define CanHookEnd_CanBasicCanMsgReceived() \

#define CanHookBegin_CanFullCanMsgReceived() \

#define CanHookEnd_CanFullCanMsgReceived() \

#define CanHookBegin_Can_MainFunction_Write() \

#define CanHookEnd_Can_MainFunction_Write() \

#define CanHookBegin_Can_MainFunction_Read() \

#define CanHookEnd_Can_MainFunction_Read() \


#if defined (MISRA_CHECK)  /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_RESET",        0277,0303,0290 /* MD_Can_0277_negation */ /* MD_Can_0303_HWaccess */ /* MD_Can_0290_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_SET",          0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG",              0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG",               0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG16",            0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG16",             0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_RESET_32BIT",  0277,0303      /* MD_Can_0277_negation */ /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_SET_32BIT",    0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_32BIT",        0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_READ_PROTECTED_REG_32BIT",         0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_CanInterruptDisable",            0303           /* MD_Can_0303_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_CanInterruptRestore",            0277,0303,0306 /* MD_Can_0277_negation */ /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pFlexCAN",                             0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanRxMask",                           0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pRXFIFO",                              0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanParityCheck",                      0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanFDRegister",                       0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "LOCAL_MAILBOX_ACCESS",                 0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "GLOBAL_MAILBOX_ACCESS",                0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanBswap32",                           0303           /* MD_Can_0303_HWaccess */ 
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_TxIsHWObjFree",                  0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsSleep",                      0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsStop",                       0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsBusOff",                     0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsPassive",                    0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsWarning",                    0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdType",                    0310,3305      /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualIdType",                    0310,3305      /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_DECODE_DLI",                       0310,3305      /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualDLC",                       0310,3305      /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualExtId",                     0488,0310,3305 /* MD_Can_0488_LL */ /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualStdId",                     0488,0310,3305 /* MD_Can_0488_LL */ /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualStdId",                     0488,0310,3305 /* MD_Can_0488_LL */ /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualExtId",                     0488,0310,3305 /* MD_Can_0488_LL */ /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualFdType",                    0310,3305      /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualFdType",                    0310,3305      /* MD_Can_0310 */ /* MD_Can_3305_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualData",                      0488           /* MD_Can_0488_LL */
#endif
/* Define chiphardware                     */
/* Constants concerning can chip registers */
/* Bitmasks of FlexCAN module configuration register CANx_MCR */
#define kFlexCAN_MDIS      ((vuint16)0x8000u)     /* Module Disable: shut down FlexCAN clocks */
#define kFlexCAN_FRZ       ((vuint16)0x4000u)     /* Freeze Enable: allow entering the freeze mode */
#define kFlexCAN_FEN       ((vuint16)0x2000u)     /* FIFO enable */
#define kFlexCAN_HALT      ((vuint16)0x1000u)     /* Halt FlexCAN: request entering the freeze mode */
#define kFlexCAN_NOT_RDY   ((vuint16)0x0800u)     /* Not Ready: FlexCAN is in DISABLE, DOZE or STOP mode */
#define kFlexCAN_WAK_MSK   ((vuint16)0x0400u)     /* Wakeup Interrupt Mask: enable wakeup interrupt generation */
#define kFlexCAN_SOFT_RST  ((vuint16)0x0200u)     /* Soft Reset: reset FlexCAN internal state and some memory mapped registers */
#define kFlexCAN_FRZ_ACK   ((vuint16)0x0100u)     /* Freeze Mode Acknowledge */
#define kFlexCAN_SUPV      ((vuint16)0x0080u)     /* Supervisor Mode */
#define kFlexCAN_SLF_WAK   ((vuint16)0x0040u)     /* FlexCAN Self Wakeup by CAN bus activity */
#define kFlexCAN_WRN_EN    ((vuint16)0x0020u)     /* Warning Interrupt Enable */
#define kFlexCAN_LPM_ACK   ((vuint16)0x0010u)     /* Low Power Mode Acknowledge */
#define kFlexCAN_WAK_SRC   ((vuint16)0x0008u)     /* Wakeup Source: enable filtered Rx input signal */
#define kFlexCAN_DOZE      ((vuint16)0x0004u)     /* Doze Mode Enable: allow MCU to switch FlexCAN into DOZE low power mode */
#define kFlexCAN_NOT_DOZE  ((vuint16)0xFFFBu)     /* Doze Mode Disable: do not allow MCU to switch FlexCAN into DOZE low power mode */
#define kFlexCAN_SRX_DIS   ((vuint16)0x0002u)     /* Self Reception Disable */
#define kFlexCAN_IRMQ      ((vuint16)0x0001u)     /* Backwards Compatibility Configuration: enable Individual Rx Masks and queue feature */

#define kFlexCAN_LPPRIO_EN ((vuint16)0x2000u)     /* Local Priority Enable */
#define kFlexCAN_AEN       ((vuint16)0x1000u)     /* Abort Enable: enables transmit abort feature */
#define kFlexCAN_FDEN      ((vuint16)0x0800u)     /* CAN FD operation enable */
#define kFlexCAN_IDAM      ((vuint16)0x0300u)     /* ID Acceptance Mode */
#define kFlexCAN_MAXMB     ((vuint16)0x003Fu)     /* Maximum Number of Message Buffers: maximum number of used message buffers = MAXMB+1 */

/* Bitmasks of FlexCAN module configuration register CANx_CTRL1 */
#define kFlexCAN_BOFF_MSK  ((vuint32)0x00008000u)   /* FlexCAN BusOff interrupt mask */
#define kFlexCAN_LOM       ((vuint32)0x00000008u)   /* FlexCAN Listen Only Mode */
#define kFlexCAN_CLK_SRC   ((vuint32)0x00002000u)   /* FlexCAN clock source mask */
#define kFlexCAN_BOFF_REC  ((vuint32)0x00000040u)   /* FlexCAN auto BusOff recovery */
#define kFlexCAN_SMP       ((vuint32)0x00000080u)   /* FlexCAN sampling mode */

/* Bitmasks of FlexCAN module configuration register CANx_ESR */
#define kFlexCAN_WAKE_INT   (vuint32)0x00000001u     /* Wake Up interrupt flag */
#define kFlexCAN_ERR_INT    (vuint32)0x00000002u     /* Error interrupt flag */
#define kFlexCAN_BOFF_INT   (vuint32)0x00000004u     /* Bus Off interrupt flag */ 
#define kFlexCAN_FCS_BOFF   (vuint32)0x00000020u     /* Fault Confinement State value for BusOff */
#define kFlexCAN_FCS_EP     (vuint32)0x00000010u     /* Fault Confinement State value for ErrorPassive */
#define kFlexCAN_FCS        (vuint32)0x00000030u     /* Fault Confinement State */
#define kFlexCAN_RXTX_WARN  (vuint32)0x00000300u
#define kFlexCAN_STATUS_INT (kFlexCAN_BOFF_INT | kFlexCAN_ERR_INT | kFlexCAN_WAKE_INT)

#define kFlexCAN_MCR               (kFlexCAN_MDIS | kFlexCAN_FRZ | kFlexCAN_HALT | kFlexCAN_NOT_RDY | kFlexCAN_FRZ_ACK | kFlexCAN_LPM_ACK)
#define kFlexCAN_FREEZE_MODE       (kFlexCAN_FRZ | kFlexCAN_HALT | kFlexCAN_NOT_RDY | kFlexCAN_FRZ_ACK) /* FlexCAN in FREEZE mode: FRZ, HALT, NOT_RDY and FRZ_ACK bit are set */
#define kFlexCAN_STOP_MODE         (kFlexCAN_NOT_RDY | kFlexCAN_LPM_ACK) /* FlexCAN in STOP powerdown mode: NOT_RDY and LPM_ACK bits set */
#define kFlexCAN_DISABLE_MODE      (kFlexCAN_MDIS | kFlexCAN_NOT_RDY | kFlexCAN_LPM_ACK) /* FlexCAN in DISABLE powerdown mode: MDIS, NOT_RDY and LPM_ACK bit are set */
#define kFlexCAN_NORMAL_MODE       ((vuint16)0x0000u) /* relevant bits for mode states must all be negated for NORMAL mode */
/* FlexCAN is DISABLED, independent from FREEZE mode:
  -> MDIS and LPM_ACK bit are necessary to identify DISABLE mode
  -> NOT_RDY must not be checked because it also influenced by FREEZE mode 
*/
#define kFlexCAN_DISABLE_ONLY_BITS (kFlexCAN_MDIS | kFlexCAN_LPM_ACK)
#define kNotFlexCAN_MCR_CFG_BTIS   (kFlexCAN_MCR | kFlexCAN_SOFT_RST | kFlexCAN_SUPV) /* user configurable bits are '0', not changeable bits are '1' */


#define kNotFlexCANErrBoff ((vuint32)0xFFFF3FFFu)

#define CANSFR_CLEAR      ((vuint32)0x00000000u)
#define CANSFR_SET        ((vuint32)0xFFFFFFFFu)

/* Macros to access the CODE-bits in the control/status word ------------------*/
#define kCodeMask         ((vuint16)0x0F00u)     /* Mask to access the CODE in the control/status word */
#define kNotDlcMask       ((vuint16)0xFF00u)
#define kNotCodeMask      ((vuint16)0xF0FFu)

/* Code definitions for receive objects */
#define kRxCodeEmpty      ((vuint16)0x0400u)    /* Message buffer is active and empty */
#define kRxCodeClear      ((vuint16)0x00F0u)    /* Mask to clear control register but leave the ID type */
#define kRxCodeOverrun    ((vuint16)0x0600u)    /* Second frame was received into a full buffer */
#define kRxCodeBusy       ((vuint16)0x0100u)    /* Receive buffer locked */

/* Code definitions for transmit objects */
#define kTxCodeTransmit     ((vuint16)0x0C40u)     /* transmit request in nominal bit rate  */
#define kTxCodeTransmitFD   ((vuint16)0xCC40u)     /* transmit request for CAN-FD: EDL (extended data length) and BRS (bit rate switch) bit must be set */
#define kNotIDEMask         ((vuint16)0xFF0Fu)
#define kTxDlcMask          ((vuint16)0x006Fu)     /* Mask to access the DLC in the control/status word */
#define kTxCodeFree         ((vuint16)0x0800u)     /* Transmit object free */
#define kTxCodeAbort        ((vuint16)0x0900u)     /* Abort message transmission */

#if defined( C_ENABLE_EXTENDED_ID )
# define kTxCodeInactive  ((vuint16)0x0820u)  /* Transmit object inactive for extended or mixed IDs */
#else
# define kTxCodeInactive  ((vuint16)0x0800u)  /* Transmit object inactive for standard IDs */
#endif

/* Code definitions for Rx FiFo ---------------------------- */
#define kRxFIFO_OVERRUN     (vuint32)0x00000080u
#define kRxFIFO_WARN        (vuint32)0x00000040u
#define kRxFIFO_NEWMSG      (vuint32)0x00000020u
#define kRxFIFO_EXT         (vuint32)0x40000000u
#define kRxFIFO_REM         (vuint32)0x80000000u
#define kRxFIFO_MASK        (vuint32)0xC0000000u
#if !defined( C_FLEXCAN_RXFIFO_MAXLOOP ) /* COV_CAN_COMPATIBILITY  */
# define C_FLEXCAN_RXFIFO_MAXLOOP  6
#endif

/* Code definitions for ctrl2 register ------------------- */
#define kFlexCAN_ECRWRE         (vuint32)0x20000000u
#define kFlexCAN_MRP            (vuint32)0x00040000u
#define kFlexCAN_RRS            (vuint32)0x00020000u
#define kFlexCAN_EACEN          (vuint32)0x00010000u
#define kFlexCAN_TASD_DEFAULT   (vuint32)0x00800000u
#define kFlexCAN_STFCNTEN       (vuint32)0x00001000u

/* Code definitions for mecr  register ------------------- */
#define kFlexCAN_ECRWRDIS       (vuint32)0x80000000u

#define kExtIDBit               (vuint32)0x80000000u

#if !defined( C_MASK_EXT_ID ) /* COV_CAN_COMPATIBILITY  */
# define C_MASK_EXT_ID ((vuint32)0xDFFFFFFFu)
#endif

#define kCanRxMaskStd     ((vuint32)0xDFFC0000u)
#if defined( C_ENABLE_EXTENDED_ID )
#  define kCanRxMaskExt   ((vuint32)0xDFFFFFFFu)
#endif

#if defined( C_ENABLE_EXTENDED_ID )
# define CAN_MSGID(x) (vuint32)(x)
#else
# define CAN_MSGID(x) ((vuint32)(x) << 16)
#endif

#define kCanRxFifoIntUnmask   ((vuint32)0xFFFFFF00u)

#define kCanMaskAll32 0xFFFFFFFFUL
#define kCanMaskAll16 0xFFFFu

/* all bits of CAN[MCR].MCR except mode and reserved bits */  
#define kCanRamCheckMaskMCR         0x24EBu

#if defined ( C_ENABLE_MB96TO127 ) || defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
# define maxmbMask                  0x007Fu
#else
# define maxmbMask                  0x003Fu
#endif

/* all bits of CAN[MCR].MAXMB except unused/reserved bits */  
#if defined( C_ENABLE_CAN_FD_USED )
# define kCanRamCheckMaskMAXMB      (0x3300u | kFlexCAN_FDEN | maxmbMask)
#else
# define kCanRamCheckMaskMAXMB      (0x3300u | maxmbMask)
#endif

#define kCanRamCheckMailboxControl  0x0F7Fu

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )

# if defined( C_ENABLE_EXTENDED_BITTIMING ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
/* mask for CAN_CTRL1 register check */
#  define kCanRamCheckMaskCONTROL1               0x0000DCF8u
# else
/* mask for CAN_CTRL1 register check */
#  define kCanRamCheckMaskCONTROL1               0xFFFFDCFFu
# endif

/* mask for CAN_ECR register check */
# define kCanRamCheckMaskECR                    0x0000FFFFu

/* mask for CAN_CBT register check */
# define kCanRamCheckMaskCBT                    0xFFEFFFFFu

# if defined( C_ENABLE_GLITCH_FILTER ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
/* mask for CAN_GFWR register check */
#  define kCanRamCheckMaskGFWR                  0x000000FFu
# endif

# if defined( V_CPU_VYBRID ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */ || defined( V_CPU_S32 ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
#  if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE ) /* COV_CAN_ENABLE_FLEXCAN_PARITY_CHECK */
/* mask for CAN_CTRL2 register check */
#   define kCanRamCheckMaskCTRL2                0x3FFF0000u
/* mask for CAN_MECR register check */
#   define kCanRamCheckMaskMECR                 0x0001E380u
#  else
/* mask for CAN_CTRL2 register check */
#  define kCanRamCheckMaskCTRL2                 0x0FFF0000u
#  endif
# endif

/* configuration check */
# if !defined( C_ENABLE_CAN_RAM_CHECK )
#  error "C_ENABLE_CAN_RAM_CHECK has to be defined if C_ENABLE_CAN_RAM_CHECK_EXTENDED is set."
# endif

# if defined( V_CPU_IMX ) || defined( V_CPU_VYBRID ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
#  error "Feature Extended RAM check is not supported for that platform! Please take a closer look at CLKSRC in CANx_CTRL1 register and MECR register)"
# endif

#endif /* C_ENABLE_CAN_RAM_CHECK_EXTENDED */

#define CanBswap32(x)                   (vuint32)  (( ((vuint32)((x) & 0xFF000000UL)) >> 24) | \
                                                    ( ((vuint32)((x) & 0x00FF0000UL)) >>  8) | \
                                                    ( ((vuint32)((x) & 0x0000FF00UL)) <<  8) | \
                                                    ( ((vuint32)((x) & 0x000000FFUL)) << 24))      /* swap b4-b3-b2-b1 to b1-b2-b3-b4 */

/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
#if defined(CAN_TXINDIRECTIONHWTOLOG) /* COV_CAN_TXINDIRECTIONHWTOLOG */
/* CAN_HL_TX_OFFSET_HW_TO_LOG(ch) not supported for LL use CanHL_GetTxHwToLogHandle or CanHL_GetTxLogToHwHandle instead */
#else
# define CAN_HL_TX_OFFSET_HW_TO_LOG(ch) (Can_GetTxOffsetHwToLog(ch)) /* used in LL */
#endif

/* for LL compatibility */
#if defined(C_ENABLE_GEN_HW_START_STOP_IDX) /* COV_CAN_GEN_HW_START_STOP_IDX */
# define CAN_HL_HW_TX_NORMAL_INDEX(hwch)     (Can_GetTxBasicHwStart(hwch))
# if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
#  define CAN_HL_HW_TX_STARTINDEX(hwch)      (Can_GetTxBasicHwStart(hwch))
# else
#  define CAN_HL_HW_TX_STARTINDEX(hwch)      (Can_GetTxFullHwStart(hwch))
# endif
# define CAN_HL_HW_TX_FULL_STARTINDEX(hwch)  (Can_GetTxFullHwStart(hwch))
# define CAN_HL_HW_UNUSED_STARTINDEX(hwch)   (Can_GetUnusedHwStart(hwch))
# define CAN_HL_HW_RX_FULL_STARTINDEX(hwch)  (Can_GetRxFullHwStart(hwch))
# define CAN_HL_HW_RX_BASIC_STARTINDEX(hwch) (Can_GetRxBasicHwStart(hwch))
# if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
#  define CAN_HL_HW_TX_STOPINDEX(hwch)       (Can_GetTxFullHwStop(hwch))
# else
#  define CAN_HL_HW_TX_STOPINDEX(hwch)       (Can_GetTxBasicHwStop(hwch))
# endif
# define CAN_HL_HW_TX_FULL_STOPINDEX(hwch)   (Can_GetTxFullHwStop(hwch))
# define CAN_HL_HW_UNUSED_STOPINDEX(hwch)    (Can_GetUnusedHwStop(hwch))
# define CAN_HL_HW_RX_FULL_STOPINDEX(hwch)   (Can_GetRxFullHwStop(hwch))
# define CAN_HL_HW_RX_BASIC_STOPINDEX(hwch)  (Can_GetRxBasicHwStop(hwch))
#else
# define CAN_ASR_HW_TX_NORMAL_INDEX(hwch)     (Can_GetHwHandle(Can_GetTxBasicHandleStart(hwch)))
# if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
#  define CAN_ASR_HW_TX_STARTINDEX(hwch)      (Can_GetHwHandle(Can_GetTxBasicHandleStart(hwch)))
# else
#  define CAN_ASR_HW_TX_STARTINDEX(hwch)      (CAN_ASR_HW_TX_FULL_STARTINDEX(hwch))
# endif
# if !defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
/* >= R19 --> size for each Object may differ for MULTIPLEXED_TRANSMISSION (please use ENABLE_GEN_HW_START_STOP_IDX instead) */
#  define CAN_ASR_HW_TX_STOPINDEX(hwch)       (CAN_ASR_HW_TX_STARTINDEX(hwch) + (Can_GetTxBasicHandleMax(hwch) * CAN_MULTIPLEXED_TX_MAX) + Can_GetTxFullHandleMax(hwch))
# endif
#  define CAN_ASR_HW_TX_FULL_STARTINDEX(hwch)  (Can_GetHwHandle(Can_GetTxFullHandleStart(hwch)))
#  define CAN_ASR_HW_TX_FULL_STOPINDEX(hwch)   (CAN_ASR_HW_TX_FULL_STARTINDEX(hwch) + Can_GetTxFullHandleMax(hwch))

# define CAN_ASR_HW_UNUSED_STARTINDEX(hwch)   (Can_GetHwHandle(Can_GetUnusedHandleStart(hwch)))
# define CAN_ASR_HW_UNUSED_STOPINDEX(hwch)   ((Can_GetUnusedHandleStart(hwch) != Can_GetUnusedHandleStop(hwch)) ? \
  (Can_GetHwHandle((Can_GetUnusedHandleStop(hwch)-1)) + Can_GetDLC_FIFO((Can_GetUnusedHandleStop(hwch)-1))) : (Can_GetHwHandle(Can_GetUnusedHandleStart(hwch))))

#  define CAN_ASR_HW_RX_FULL_STARTINDEX(hwch)  (Can_GetHwHandle(Can_GetRxFullHandleStart(hwch)))
#  define CAN_ASR_HW_RX_FULL_STOPINDEX(hwch)   ((Can_GetRxFullHandleStart(hwch) != Can_GetRxFullHandleStop(hwch)) ? \
  (Can_GetHwHandle((Can_GetRxFullHandleStop(hwch)-1))+1) : (Can_GetHwHandle(Can_GetRxFullHandleStart(hwch))))

#  define CAN_ASR_HW_RX_BASIC_STARTINDEX(hwch) (Can_GetHwHandle(Can_GetRxBasicHandleStart(hwch)))
#  define CAN_ASR_HW_RX_BASIC_STOPINDEX(hwch)  ((Can_GetRxBasicHandleStart(hwch) != Can_GetRxBasicHandleStop(hwch)) ? \
  (Can_GetHwHandle((Can_GetRxBasicHandleStop(hwch)-1)) + Can_GetDLC_FIFO((Can_GetRxBasicHandleStop(hwch)-1))) : \
  (Can_GetHwHandle(Can_GetRxBasicHandleStart(hwch))))
# if !defined(CAN_HL_HW_TX_NORMAL_INDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_NORMAL_INDEX(hwch)     CAN_ASR_HW_TX_NORMAL_INDEX(hwch)
# endif
# if !defined(CAN_HL_HW_TX_FULL_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_FULL_STARTINDEX(hwch)  CAN_ASR_HW_TX_FULL_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_TX_FULL_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_FULL_STOPINDEX(hwch)   CAN_ASR_HW_TX_FULL_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_TX_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_STARTINDEX(hwch)       CAN_ASR_HW_TX_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_TX_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_TX_STOPINDEX(hwch)        CAN_ASR_HW_TX_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_UNUSED_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_UNUSED_STARTINDEX(hwch)   CAN_ASR_HW_UNUSED_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_UNUSED_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_UNUSED_STOPINDEX(hwch)    CAN_ASR_HW_UNUSED_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_FULL_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_RX_FULL_STARTINDEX(hwch)  CAN_ASR_HW_RX_FULL_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_FULL_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_RX_FULL_STOPINDEX(hwch)   CAN_ASR_HW_RX_FULL_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_BASIC_STARTINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_RX_BASIC_STARTINDEX(hwch) CAN_ASR_HW_RX_BASIC_STARTINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_BASIC_STOPINDEX) /* COV_CAN_COMPATIBILITY  */
#  define CAN_HL_HW_RX_BASIC_STOPINDEX(hwch)  CAN_ASR_HW_RX_BASIC_STOPINDEX(hwch)
# endif
#endif
/* may be used by LL to free TX mailbox between CanLL_TxBegin and CanLL_TxEnd (only necessary when not using CanLL_TxStart return value) */
#define CAN_FREE_TX_OBJECT(obj) Can_SetActiveSendState(obj, CAN_FREE_OBJ)

#if defined(C_ENABLE_INDIVIDUAL_POLLING) || defined(CAN_HWOBJINDIVPOLLING) /* COV_CAN_HWOBJINDIVPOLLING */
/* define first index to array CanHwObjIndivPolling[][] */
#  define CAN_HWOBJINDIVPOLLING_INDEX0                     (canHwChannel)
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK)
# if !defined(CAN_RAM_CHECK_MAILBOX_RESULT) /* May be defined by test suite to stimulate RAM_CHECK failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, hwObjHandle) CanLL_IsMailboxCorrupt((hwObjHandle))
#  else
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, hwObjHandle) CanLL_IsMailboxCorrupt((ch), (hwObjHandle))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_FINISHED_CTP) /* May be defined by test suite to check RAM_CHECK finished / executed */
#  define CAN_RAM_CHECK_FINISHED_CTP(ch)
# endif
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
# if !defined(CAN_RAM_CHECK_BEGIN_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_BEGIN_REG_RESULT(ch) CanLL_InitBeginIsRegisterCorrupt()
#  else
#   define CAN_RAM_CHECK_BEGIN_REG_RESULT(ch) CanLL_InitBeginIsRegisterCorrupt((ch))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_END_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_END_REG_RESULT(ch) CanLL_InitEndIsRegisterCorrupt()
#  else
#   define CAN_RAM_CHECK_END_REG_RESULT(ch) CanLL_InitEndIsRegisterCorrupt((ch))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_READ_BACK_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  define CAN_RAM_CHECK_READ_BACK_RESULT(ch)
# endif
#endif

#define CanHL_IsStart(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_START) == CAN_STATUS_START)
#define CanHL_IsSleep(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_SLEEP) == CAN_STATUS_SLEEP)
#define CanHL_IsStop(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_STOP) == CAN_STATUS_STOP)
#define CanHL_IsBusOff(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_BUSOFF) == CAN_STATUS_BUSOFF)
#define CanHL_IsControllerInit(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_INIT) == CAN_STATUS_INIT)

#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
# define cantVIdentityMsk uint16
# define CanSetActiveIdentity(identityLog) \
{ \
  canActiveIdentityLog = (identityLog); \
  canActiveIdentityMsk = (cantVIdentityMsk) (((cantVIdentityMsk) 1) << (identityLog)); \
}
# if defined V_ACTIVE_IDENTITY_MSK
#  undef V_ACTIVE_IDENTITY_MSK  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
# endif
# define V_ACTIVE_IDENTITY_MSK                canActiveIdentityMsk
# if defined V_ACTIVE_IDENTITY_LOG
#  undef V_ACTIVE_IDENTITY_LOG  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
# endif
# define V_ACTIVE_IDENTITY_LOG                canActiveIdentityLog
#endif

#if (CAN_GENERIC_PRETRANSMIT == STD_ON)
# define PDUINFO_PTR PduInfoPtr_var
#else
# define PDUINFO_PTR PduInfo
#endif
#if defined(C_ENABLE_CAN_FD_USED)
# define PDUINFO_ID  pduInfo_var_id
# define PDUINFO_DLC pduInfo_var_dlc
#else
# define PDUINFO_ID  PDUINFO_PTR->id
# define PDUINFO_DLC PDUINFO_PTR->length
#endif

#if !defined(CAN_APPLICATION_DEM_REPORTERROR) /* COV_CAN_COMPATIBILITY */
# define CAN_APPLICATION_DEM_REPORTERROR STD_OFF
#endif
#if (CAN_APPLICATION_DEM_REPORTERROR == STD_OFF) /* COV_CAN_USER_CONFIG */
# define Can_Dem_ReportError(EventId) ( (void) Dem_ReportErrorStatus((EventId), DEM_EVENT_STATUS_FAILED) )
#endif

#if defined(C_ENABLE_CAN_FD_USED) /* also for BRS because DLC may be bigger than 8 and will be checked by CanIf */
# define CAN_DECODE_DLI(dlc) (Can_DliToBytesMap[((uint8)(dlc)) & ((uint8)0xFu)])
# define CAN_ENCODE_DLI(length) (((uint8)Can_BytesToDliMap[(length)]) & ((uint8)0x0Fu))
#else
# define CAN_DECODE_DLI(dlc) (dlc)
# define CAN_ENCODE_DLI(length) (length)
#endif
#if defined(C_ENABLE_CAN_FD_FULL)
# define CAN_MAX_RX_DATALEN         Can_GetMaxRxDataLen()
# define CAN_MAX_TX_DATALEN         Can_GetMaxTxDataLen()
# define CAN_MAX_DATALEN_OBJ(Index) Can_GetMailboxDataLen(Index)
#else
# define CAN_MAX_RX_DATALEN         8u
# define CAN_MAX_TX_DATALEN         8u
# define CAN_MAX_DATALEN_OBJ(Index) 8u
#endif
#define CanHL_IsFdMessage(id) (((id) & (Can_IdType)CAN_ID_FD_MASK) == (Can_IdType)CAN_ID_FD_MASK) /* used for LL */ /* \trace SPEC-60432, SPEC-50586 */
#define CanHL_IsFdTxBrs(ch)   (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(ch)) == CAN_FD_RXTX) /* used for LL */ /* \trace SPEC-60432, SPEC-50586 */

#if (CAN_MICROSAR_VERSION == CAN_MSR403) /* COV_CAN_MICROSAR_VERSION */
# define CAN_MULTIPLEXED_TX_MAX_OBJ(hth) ((Can_GetMailboxType(hth) == CAN_TX_BASICCAN_MUX_TYPE) ? CAN_MULTIPLEXED_TX_MAX : 1)
#else
# define CAN_MULTIPLEXED_TX_MAX_OBJ(hth) CAN_MULTIPLEXED_TX_MAX
#endif
# define CANDRV_SET_CODE_TEST_POINT(x)

#if defined( C_ENABLE_HW_LOOP_TIMER )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define   APPLCANTIMERSTART(x)   ApplCanTimerStart(x)
#  define   APPLCANTIMERLOOP(x)    ApplCanTimerLoop(x)
#  define   APPLCANTIMEREND(x)     ApplCanTimerEnd(x)
# else
#  define   APPLCANTIMERSTART(x)   ApplCanTimerStart(channel, (x))
#  define   APPLCANTIMERLOOP(x)    ApplCanTimerLoop(channel, (x))
#  define   APPLCANTIMEREND(x)     ApplCanTimerEnd(channel, (x))
# endif
#else
# define   APPLCANTIMERSTART(x)   
# define   APPLCANTIMERLOOP(x)     (vuint8)(1)
# define   APPLCANTIMEREND(x)     
#endif

#if defined ( C_ENABLE_USER_MODE_OS )
# define CAN_WRITE_PROTECTED_REG(reg, val)              osWritePeripheral16(Can_GetProtectedAreaId(canHwChannel), (vuint32)&(reg), (val))
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits)       osModifyPeripheral16(Can_GetProtectedAreaId(canHwChannel), (vuint32)&(reg), (vuint16)(~(bits)), (vuint16)0x0000u)
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)         osModifyPeripheral16(Can_GetProtectedAreaId(canHwChannel), (vuint32)&(reg), (vuint16)0xFFFFu, (bits))
# define CAN_READ_PROTECTED_REG(reg)                    osReadPeripheral16(Can_GetProtectedAreaId(canHwChannel), (vuint32)&(reg))
# define CAN_WRITE_PROTECTED_REG_32BIT(reg, val)        osWritePeripheral32(Can_GetProtectedAreaId(canHwChannel), (vuint32)&(reg), (val))
# define CAN_WRITE_PROTECTED_REG_RESET_32BIT(reg, bits) osModifyPeripheral32(Can_GetProtectedAreaId(canHwChannel), (vuint32)&(reg), (vuint32)(~(bits)), (vuint32)0x00000000u)
# define CAN_WRITE_PROTECTED_REG_SET_32BIT(reg, bits)   osModifyPeripheral32(Can_GetProtectedAreaId(canHwChannel), (vuint32)&(reg), (vuint32)0xFFFFFFFFu, (bits))
# define CAN_READ_PROTECTED_REG_32BIT(reg)              osReadPeripheral32(Can_GetProtectedAreaId(canHwChannel), (vuint32)&(reg))
#elif defined ( C_ENABLE_USER_MODE_APPL )
#  define CAN_WRITE_PROTECTED_REG(reg, val)              ApplCanWriteProtectedRegister16(&(reg), (vuint16)0xFFFFu, (val))
#  define CAN_WRITE_PROTECTED_REG_RESET(reg, bits)       ApplCanWriteProtectedRegister16(&(reg), (bits), (vuint16)0x0000u)
#  define CAN_WRITE_PROTECTED_REG_SET(reg, bits)         ApplCanWriteProtectedRegister16(&(reg), (bits), (bits))
#  define CAN_READ_PROTECTED_REG(reg)                    ApplCanReadProtectedRegister16(&(reg))
# define CAN_WRITE_PROTECTED_REG_RESET_32BIT(reg, bits) ApplCanWriteProtectedRegister32(&(reg), (bits), (vuint32)0x00000000u)
# define CAN_WRITE_PROTECTED_REG_SET_32BIT(reg, bits)   ApplCanWriteProtectedRegister32(&(reg), (bits), (bits))
# define CAN_READ_PROTECTED_REG_32BIT(reg)              ApplCanReadProtectedRegister32(&(reg))
#else
# define CAN_WRITE_PROTECTED_REG(reg, val)              (reg) = (val)
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits)       (reg) &= (vuint16)(~(bits))
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)         (reg) |= (bits)
# define CAN_READ_PROTECTED_REG(reg)                    (reg)
# define CAN_WRITE_PROTECTED_REG_RESET_32BIT(reg, bits) (reg) &= (vuint32)(~(bits))
# define CAN_WRITE_PROTECTED_REG_SET_32BIT(reg, bits)   (reg) |= (bits)
# define CAN_READ_PROTECTED_REG_32BIT(reg)              (reg)
#endif

#if defined ( C_ENABLE_USER_MODE_OS )
# define CAN_AREA(ch) Can_GetProtectedAreaId(ch)
#else
  /* dummy area */
# define CAN_AREA(ch) 0
#endif


#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

# define   CAN_DISABLE_RXTX_INTERRUPT_0TO31(canFlagPtr) (canFlagPtr)->flags1 = pFlexcan->imask1; pFlexcan->imask1 = 0
# define   CAN_RESTORE_RXTX_INTERRUPT_0TO31(canFlag)    pFlexcan->imask1 = (canFlag).flags1

# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
#  define   CAN_DISABLE_RXTX_INTERRUPT_32TO63(canFlagPtr) (canFlagPtr)->flags2 = pFlexcan->imask2; pFlexcan->imask2 = 0
#  define   CAN_RESTORE_RXTX_INTERRUPT_32TO63(canFlag)    pFlexcan->imask2 = (canFlag).flags2
# else
#  define   CAN_DISABLE_RXTX_INTERRUPT_32TO63(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_32TO63(canFlag)
# endif

# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
#  define   CAN_DISABLE_RXTX_INTERRUPT_64TO95(canFlagPtr) (canFlagPtr)->flags3 = pFlexcan->imask3; pFlexcan->imask3 = 0
#  define   CAN_RESTORE_RXTX_INTERRUPT_64TO95(canFlag)    pFlexcan->imask3 = (canFlag).flags3
# else
#  define   CAN_DISABLE_RXTX_INTERRUPT_64TO95(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_64TO95(canFlag)
# endif

# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
#  define   CAN_DISABLE_RXTX_INTERRUPT_96TO127(canFlagPtr) (canFlagPtr)->flags4 = pFlexcan->imask4; pFlexcan->imask4 = 0
#  define   CAN_RESTORE_RXTX_INTERRUPT_96TO127(canFlag)    pFlexcan->imask4 = (canFlag).flags4
# else
#  define   CAN_DISABLE_RXTX_INTERRUPT_96TO127(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT_96TO127(canFlag)
# endif
#else
# define   CAN_DISABLE_RXTX_INTERRUPT_0TO31(canFlagPtr)
# define   CAN_RESTORE_RXTX_INTERRUPT_0TO31(canFlag)
# define   CAN_DISABLE_RXTX_INTERRUPT_32TO63(canFlagPtr)
# define   CAN_RESTORE_RXTX_INTERRUPT_32TO63(canFlag)
# define   CAN_DISABLE_RXTX_INTERRUPT_64TO95(canFlagPtr)
# define   CAN_RESTORE_RXTX_INTERRUPT_64TO95(canFlag)
# define   CAN_DISABLE_RXTX_INTERRUPT_96TO127(canFlagPtr)
# define   CAN_RESTORE_RXTX_INTERRUPT_96TO127(canFlag)
#endif

#if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
# define CAN_DISABLE_BUSOFF_INTERRUPT(canFlagPtr)  (canFlagPtr)->canctrl1 = pFlexcan->control1; pFlexcan->control1 &= kNotFlexCANErrBoff
# define CAN_RESTORE_BUSOFF_INTERRUPT(canFlag)     pFlexcan->control1 |= (vuint32)((canFlag).canctrl1 & (vuint32)(~kNotFlexCANErrBoff))
#else
# define CAN_DISABLE_BUSOFF_INTERRUPT(canFlagPtr)
# define CAN_RESTORE_BUSOFF_INTERRUPT(canFlag)
#endif

#if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
# define CAN_DISABLE_WAKEUP_INTERRUPT(canFlagPtr)  (canFlagPtr)->canmcr = CAN_READ_PROTECTED_REG(pFlexcan->canmcr); CAN_WRITE_PROTECTED_REG_RESET(pFlexcan->canmcr, kFlexCAN_WAK_MSK)
# define CAN_RESTORE_WAKEUP_INTERRUPT(canFlag)     CAN_WRITE_PROTECTED_REG_SET(pFlexcan->canmcr, (vuint16)((canFlag).canmcr & kFlexCAN_WAK_MSK))
#else
# define CAN_DISABLE_WAKEUP_INTERRUPT(canFlagPtr)
# define CAN_RESTORE_WAKEUP_INTERRUPT(canFlag)
#endif

#if !defined( C_ENABLE_CAN_RXTX_INTERRUPT )   && \
    !defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) && \
    !defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
# define CanLL_CanInterruptDisable(x,y)
# define CanLL_CanInterruptRestore(x,y)
#endif   /* C_ENABLE_CAN_..._INTERRUPT */

# define CanLL_TxIsHWObjFree(canHwChannel, txObjHandle) ((GLOBAL_MAILBOX_ACCESS((canHwChannel), (txObjHandle), control) & kCodeMask) == kTxCodeFree)

# define CanLL_HwIsSleep( CAN_HW_CHANNEL_CANPARA_ONLY)  (kCanFalse != kCanFalse)  /* avoid misra warning */


#define CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY) ((CAN_READ_PROTECTED_REG((pFlexCAN(canHwChannel))->canmcr) & kFlexCAN_MCR) == kFlexCAN_FREEZE_MODE)

#define CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY) (((pFlexCAN(canHwChannel))->estat & kFlexCAN_FCS_BOFF) != 0)

#if defined( C_ENABLE_EXTENDED_STATUS )
#  define CanLL_HwIsPassive(CAN_HW_CHANNEL_CANPARA_ONLY) (((pFlexCAN(canHwChannel))->estat & kFlexCAN_FCS) == kFlexCAN_FCS_EP)
#  define CanLL_HwIsWarning(CAN_HW_CHANNEL_CANPARA_ONLY) (((pFlexCAN(canHwChannel))->estat & kFlexCAN_RXTX_WARN) != 0)
#endif /* C_ENABLE_EXTENDED_STATUS */



/***************************************************************************/
/* Constants                                                               */
/***************************************************************************/
#define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* BR:012 */
V_DEF_CONST(V_NONE, uint8, CONST) Can_MainVersion         = (uint8)CAN_SW_MAJOR_VERSION; /* PRQA S 3408 */ /* MD_Can_Asr_3408_libCheck */
V_DEF_CONST(V_NONE, uint8, CONST) Can_SubVersion          = (uint8)CAN_SW_MINOR_VERSION; /* PRQA S 3408 */ /* MD_Can_Asr_3408_libCheck */
V_DEF_CONST(V_NONE, uint8, CONST) Can_ReleaseVersion      = (uint8)CAN_SW_PATCH_VERSION; /* PRQA S 3408 */ /* MD_Can_Asr_3408_libCheck */


#if defined(C_ENABLE_CAN_FD_USED)
V_DEF_CONST(CAN_STATIC, uint8, CONST) Can_DliToBytesMap[16] = /* PRQA S 3218 */ /* MD_Can_3218 */
{
  0,  1,  2,  3,
  4,  5,  6,  7,
  8, 12, 16, 20,
 24, 32, 48, 64
};
V_DEF_CONST(CAN_STATIC, uint8, CONST) Can_BytesToDliMap[65] = /* PRQA S 3218 */ /* MD_Can_3218 */
{
/* 00..07 */  0,  1,  2,  3,  4,  5,  6,  7,
/* 08..15 */  8,  9,  9,  9,  9, 10, 10, 10,
/* 16..23 */ 10, 11, 11, 11, 11, 12, 12, 12,
/* 24..31 */ 12, 13, 13, 13, 13, 13, 13, 13,
/* 32..39 */ 13, 14, 14, 14, 14, 14, 14, 14,
/* 40..47 */ 14, 14, 14, 14, 14, 14, 14, 14,
/* 48..55 */ 14, 15, 15, 15, 15, 15, 15, 15,
/* 56..63 */ 15, 15, 15, 15, 15, 15, 15, 15,
/* 64     */ 15
};
#endif

/* Global constants with CAN driver main and subversion */

#define CanBitMask(x)      ((vuint32)((vuint32)0x01 << ((x) & (0x1F))))
#define CanInvBitMask(x)   ((vuint32)~((vuint32)0x01 << ((x) & (0x1F))))

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED ) || defined( C_ENABLE_CAN_RAM_CHECK )
/* test bit patterns for (Extended) RAM check */
V_DEF_CONST(CAN_STATIC, vuint32, CONST) ramCheckPattern32[3] =                 /* PRQA S 3218 */ /* MD_Can_3218 */
{
  0xAAAAAAAAu, 0x55555555u, 0x00000000u
};
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/* additional test bit patterns for Extended RAM check */
V_DEF_CONST(CAN_STATIC, vuint16, CONST) ramCheckPattern16[3] =                 /* PRQA S 3218 */ /* MD_Can_3218 */
{
  0xAAAAu, 0x5555u, 0x0000u
};
#endif


#define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***************************************************************************/
/* CAN-Hardware Data Definitions                                           */
/***************************************************************************/

/***************************************************************************/
/* global data definitions                                                 */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
/*! bitmask of the active channels in the current identity */
V_DEF_VAR(V_NONE, uint16, VAR_NOINIT) canActiveIdentityMsk; /* PRQA S 3408 */ /* MD_Can_Asr_3408 */
/*! the activated identity handle */
V_DEF_VAR(V_NONE, uint8, VAR_NOINIT)  canActiveIdentityLog; /* PRQA S 3408 */ /* MD_Can_Asr_3408 */
#endif


/***************************************************************************************/
/* local data definitions   (need also INFIX because STATIC may be defined to nothing) */
/***************************************************************************************/
/* \trace SPEC-1585 */
/*! Semaphore to block reentrancy for Can_MainFunction_Read() */
V_DEF_VAR(CAN_STATIC, Can_ReturnType, VAR_NOINIT) canRxTaskActive;
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
/*! Save API context in witch the DET is called (Init, InitController, SetControllerMode, disable/enableControlerInterrupts) */
V_DEF_VAR(CAN_STATIC, uint8, VAR_NOINIT) canApiContext;
#   endif
#  endif
# endif
#endif
#if defined(C_ENABLE_RX_QUEUE)
V_DEF_VAR(CAN_STATIC, uint16, VAR_NOINIT) canRxQueueMaxDataSize; /* PRQA S 3218 */ /* MD_Can_3218 */
#endif


# if defined( C_ENABLE_UPDATE_BASE_ADDRESS ) /* COV_CAN_ENABLE_UPDATE_BASE_ADDRESS */
/* RAM CATEGORY 1 START*/
#  if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
V_DEF_P2VAR(V_NONE, vuint32, VAR_NOINIT, REG_CANCELL) canLL_VirtualPtrField[kCanNumberOfHwChannels]; /* PRQA S 3408 */ /* MD_Can_Asr_3408 */
#  else
V_DEF_P2VAR(V_NONE, vuint32, VAR_NOINIT, REG_CANCELL) canLL_VirtualPtrField[kCanNumberOfMaxUsedControllers]; /* PRQA S 3408 */ /* MD_Can_Asr_3408 */
#  endif
/* RAM CATEGORY 1 END*/
# endif

#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* ! Mark module to be initialized (used to check double/none initialization) */
V_DEF_VAR(CAN_STATIC, uint8, VAR_INIT) canConfigInitFlag = CAN_STATUS_UNINIT;
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* not static because of debug/test usage */
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*! Pointer to the current configuration */
V_DEF_P2CONST (V_NONE, Can_ConfigType, VAR_INIT, CONST_PBCFG) Can_ConfigDataPtr = NULL_PTR; /* UREQ00035484 */ /* PRQA S 3408,1504 */ /* MD_Can_3408_extLinkage */
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#else
# define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
/*! Pointer to the current configuration */
V_DEF_CONSTP2CONST(V_NONE, Can_ConfigType, CONST, CONST_PBCFG) Can_ConfigDataPtr = NULL_PTR; /* PRQA S 3408,3218,1514 */ /* MD_Can_3408_extLinkage,MD_Can_3218 */
# else
/*! Pointer to the current configuration */
V_DEF_CONSTP2CONST(V_NONE, Can_ConfigType, CONST, CONST_PBCFG) Can_ConfigDataPtr = &CanConfig; /* PRQA S 3408,3218,1514 */ /* MD_Can_3408_extLinkage,MD_Can_3218 */
# endif
# define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/***************************************************************************/
/*  Safe Check                                                             */
/***************************************************************************/
#if !defined(CAN_SAFE_BSW) /* COV_CAN_COMPATIBILITY */
# define CAN_SAFE_BSW   STD_OFF
#else
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) || \
     !defined(CAN_DEV_ERROR_DETECT) || \
     defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) || \
     !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) || \
     defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) || \
     defined(C_ENABLE_PARTIAL_NETWORK) || \
     defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) || \
     defined(CAN_ENABLE_BUSOFF_SUPPORT_API) || \
     defined(CAN_ENABLE_EXTENDED_STATE_MACHINE) || \
     (CAN_EMULATE_SLEEP != STD_ON) || \
     !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) || \
     (CAN_AMD_RUNTIME_MEASUREMENT == STD_ON) || \
     !defined(C_ENABLE_GEN_HW_START_STOP_IDX) /* COV_CAN_SAFE_BSW_EXCLUSION */
#   error "Unsupported Feature activated for SafeBSW"
#  endif
# endif
#endif

/***************************************************************************/
/*  Error Check                                                            */
/***************************************************************************/
#if (CAN_TRANSMIT_BUFFER == STD_OFF) && defined(C_ENABLE_CANCEL_IN_HW)
# error "C_ENABLE_CANCEL_IN_HW need CAN_TRANSMIT_BUFFER == STD_ON (no FIFO buffering but PRIO_BY_CANID in CanIf) -> check Generated data"
#endif
# if (CAN_SLEEP_SUPPORT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON)
#  error "C_ENABLE_SLEEP_WAKEUP organified but generated like supported"
# endif
#if (CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_SLEEP_SUPPORT == STD_OFF)
# error "activated CAN_WAKEUP_SUPPORT need activated CAN_SLEEP_SUPPORT"
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
# if (CAN_LOOP_MAX == 0)
#  error "CAN_LOOP_MAX should not be generated as 0"
# endif
#else
# if (CAN_HARDWARE_CANCELLATION == STD_ON)
#  error "C_ENABLE_HW_LOOP_TIMER organified but generated like supported"
# endif
#endif
#if !defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG TX */
# if (CAN_MULTI_ECU_CONFIG == STD_ON)
#  error "C_ENABLE_MULTI_ECU_CONFIG organified but generated like supported"
# endif
#endif
#if defined(C_ENABLE_CANCEL_IN_HW)
#else
# if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
#  error "C_ENABLE_CANCEL_IN_HW organified but generated like supported"
# endif
#endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if (CAN_DEV_ERROR_DETECT == STD_OFF)
#   error "CAN_DEV_TIMEOUT_DETECT is switched on but CAN_DEV_ERROR_DETECT is not"
#  endif
# endif
#endif
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
# if defined(C_ENABLE_PARTIAL_NETWORK) /* COV_CAN_PARTIAL_NETWORK */
#  error "No need to switch on partial Network for MicroSar in version 4.x"
# endif
# if defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
#  error "BUSOFF_SUPPORT_API not supported for MicroSar in version 4.x"
# endif
# if defined(CAN_ENABLE_EXTENDED_STATE_MACHINE) /* COV_CAN_EXTENDED_STATE_MACHINE */
#  error "CAN_EXTENDED_STATE_MACHINE not supported for MicroSar in version 4.x"
# endif
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  error "CAN_DEV_TIMEOUT_DETECT not supported for MicroSar in version 4.x"
# endif
#endif
#if (CAN_MIRROR_MODE == STD_ON) && (!defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2) || (CAN_GENERIC_PRECOPY == STD_OFF))
# error "CAN_MIRROR_MODE need CAN_GENERIC_CONFIRMATION with CAN_API2 and CAN_GENERIC_PRECOPY as STD_ON"
#endif
#if !defined(CAN_MULTIPLEXED_TX_MAX)
# error "CAN_MULTIPLEXED_TX_MAX is not generated"
#endif
#if (CAN_MULTIPLEXED_TRANSMISSION == STD_ON) /* COV_CAN_MULTIPLEXED_TRANSMISSION */
# if (CAN_MULTIPLEXED_TX_MAX != 3) /* CM_CAN_HL19 */
#  error "CAN_MULTIPLEXED_TX_MAX generated with wrong value"
# endif
#else
# if (CAN_MULTIPLEXED_TX_MAX != 1) /* CM_CAN_HL19 */
#  error "CAN_MULTIPLEXED_TX_MAX generated with wrong value"
# endif
#endif
#if (CAN_RAM_CHECK != CAN_NONE)
# if defined(CAN_ENABLE_EXTENDED_STATE_MACHINE) /* COV_CAN_EXTENDED_STATE_MACHINE */
# error "Feature RAM_CHECK is not available in combination with EXTENDED_STATE_MACHINE"
/* no STOP mode called after WAKEUP but need to run RAM check */
# endif
#endif
#if (CAN_MULTIPLE_BASICCAN_TX == STD_ON)
# if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
/* cancellation does not work in CanHL_WritePrepareCancelTx for multiple BasicCAN messages, and is not useful for FIFO queue in CanIf (normally combined with multiple BCAN)*/
# error "CAN_MULTIPLE_BASICCAN_TX and CAN_HW_TRANSMIT_CANCELLATION are STD_ON but this combination is not supported"
# endif
#endif

#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
#  error "Extended RamCheck is only available for MICROSAR403"
# endif
#endif

/***************************************************************************/
/*  Functions                                                              */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) ) || defined(C_ENABLE_HW_LOOP_TIMER) /* always used for sync mode */ /* COV_CAN_MICROSAR_VERSION */

# if defined(MISRA_CHECK) /* COV_CAN_MISRA */
/* TickRefType is pointer to TickType but unknown here */
#  pragma PRQA_MACRO_MESSAGES_OFF "CanHL_ApplCanTimerStart",432
#  pragma PRQA_MACRO_MESSAGES_OFF "CanHL_ApplCanTimerEnd",432
# endif

# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( timerIdx );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( timerIdx );
# else
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( channel, (timerIdx) );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( channel, (timerIdx) );
# endif
# define CanHL_ApplCanTimerLoop( timerIdx )   if (ApplCanTimerLoop( CAN_CHANNEL_CANPARA_FIRST (timerIdx) ) != CAN_OK) \
                                              { \
                                                break; \
                                              }

# if (CAN_HW_LOOP_SUPPORT_API == STD_OFF)
/* Internal handling of HW loops (like AutoSar) - otherwise ApplCanTimer... is defined an implemented by Application */
/****************************************************************************
| NAME:             ApplCanTimerStart
****************************************************************************/
/* Used as macro to save runtime and code */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
/* \trace SPEC-1640 */
#    define ApplCanTimerStart(source)     ((void)GetCounterValue( CAN_OS_COUNTER_ID, &Can_GetCanLoopTimeout(0,(source))))
#   else
#    define ApplCanTimerStart(source)     (Can_GetCanLoopTimeout(0,(source)) = 0)
#   endif
#  else
#   if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
#    define ApplCanTimerStart(ch, source) ((void)GetCounterValue( CAN_OS_COUNTER_ID, &Can_GetCanLoopTimeout((ch),(source))))
#   else
#    define ApplCanTimerStart(ch, source) (Can_GetCanLoopTimeout((ch),(source)) = 0)
#   endif
#  endif
/****************************************************************************
| NAME:             ApplCanTimerLoop
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| ApplCanTimerLoop
Relation_Context:
OneChOpt, HardwareLoop, HardwareCancelByAppl
Relation:
DevErrorDetect, OneChOpt
HardwareLoop
PnEnable
CanDevTimeoutDetect
ProdErrorDetect
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop( CAN_CHANNEL_CANTYPE_FIRST uint8 source ) /* PRQA S 3219 */ /* MD_Can_Asr_3219 */
{ /* \trace SPEC-3952 */
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  uint8 errorId;
  uint8 apiId;
  errorId = CAN_E_NO_ERROR;
  apiId = CAN_HW_ACCESS_ID;
  retval = CAN_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and source is valid (no INIT check because may be used inside power on INIT) */
  if (source >= CAN_LOOP_AMOUNT) /* CM_CAN_HL22 */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
#  if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
  /* #100 In case of MSR4: */
    TickType elapsedTime;
    TickType startTime;
    /* #110 Calculate the elapsed since time the start of this hardware loop (identified by parameter source). */
    /* Get start time (set by ApplCanTimerStart - temporary variable because GetElapsedValue modify original data */
    startTime = Can_GetCanLoopTimeout(channel,source);
    /* Get elapsed time - from start time to now */
    /* #120 Throw DET error when GetElapsedValue() failed */
    if ( GetElapsedValue( CAN_OS_COUNTER_ID, &startTime, &elapsedTime ) != (StatusType)E_OK ) /* PRQA S 432 */ /* TickRefType is pointer to TickType but unknown here */ /* SBSW_CAN_HL37 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_TIMEOUT_DET;
    }
    else
    {
      /* #130 Check if time out occurs for HW loop checks (none mode transition) \trace SPEC-1594 */
      if ( (TickType)CAN_OS_TICK2MS( elapsedTime ) < (TickType)CAN_TIMEOUT_DURATION ) /* COV_CAN_HARDWARE_FAILURE */
      { /* no time out occur return OK */
        retval = CAN_OK;
      }
#   if defined(C_ENABLE_HW_LOOP_TIMER) /* COV_CAN_MICROSAR_VERSION */
      else
      { /* Mode Change synchronous & HW loop check */
        /* #140 Throw DET error and set hardware cancellation flag */
        if (source < CAN_LOOP_MAX) /* COV_CAN_HARDWARE_FAILURE */
        { 
          errorId = CAN_E_TIMEOUT_DET;
          Can_SetIsHardwareCanceled(channel,TRUE); /* SBSW_CAN_HL14 */
        }
      }
#   endif
    }
    CAN_DUMMY_STATEMENT(startTime); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  else
  /* #200 In case of MSR3: */
    /* #210 Increment HW loop counter */
    Can_GetCanLoopTimeout(channel,source)++; /* SBSW_CAN_HL15 */
    /* #220 Check if time out occurs */
    if ( Can_GetCanLoopTimeout(channel,source) >= CAN_TIMEOUT_DURATION ) /* \trace SPEC-3953 */
    {
#   if defined(C_ENABLE_PARTIAL_NETWORK) /* COV_CAN_PARTIAL_NETWORK */
      /* #230 Do not throw error when partial network is active for this controller */
      if ( Can_IsTimeoutCall(channel) )
#   endif
      { /* #240 Throw DET or DEM error and set hardware cancellation flag */
#   if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
        apiId = canApiContext;
        errorId = CAN_E_TIMEOUT_DET;
#   else
#    if (CAN_PROD_ERROR_DETECT == STD_ON) /* \trace SPEC-1398 */ /* is explicit ignored due to vector general requirements */
        Can_Dem_ReportError(canDemErrorTimeout); /* \trace SPEC-1726, SPEC-1725, SPEC-3846, SPEC-3824, SPEC-3928 */
#    endif
#   endif
        Can_SetIsHardwareCanceled(channel,TRUE); /* SBSW_CAN_HL14 */
      }
    }
    else
    {
  /* #300 no time out occur return OK */
      retval = CAN_OK;
    }
#  endif /* CAN_MSR3/4 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)  
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(apiId, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(apiId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/****************************************************************************
| NAME:             ApplCanTimerEnd
****************************************************************************/
/* Used as macro to save runtime and code */
/* because of possible nested timers .. timer has to be reset */
#  define ApplCanTimerEnd ApplCanTimerStart
# endif /* (CAN_HW_LOOP_SUPPORT_API == STD_OFF) */

#else /* C_ENABLE_HW_LOOP_TIMER */
/* no HW loop is used at all */
# define CanHL_ApplCanTimerStart( timerIdx )
# define CanHL_ApplCanTimerLoop( timerIdx )
# define CanHL_ApplCanTimerEnd( timerIdx )
#endif

/****************************************************************************
| NAME:             CanInit
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanInit
Relation_Context:
Relation:
OneChOpt
ChannelAmount
BusOffRecovery
HardwareLoop
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanInit( CAN_CHANNEL_CANTYPE_FIRST uint8 initObject ) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  
  /* ----- Development Error Checks ------------------------------------- */
  /* parameter initObject is already checked by caller */
  /* parameter channel is already checked by caller */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Reinitialize the controller (Call fitting controller initialization function Can_InitController()) */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
    Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(initObject - (uint8)(Can_GetInitObjectStartIndex(channel))) & 0x03u))); /* SBSW_CAN_HL03 */
#else
    Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
    CAN_DUMMY_STATEMENT(initObject); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
    /* #110 Switch to START mode if BUSOFF handling is done by application */
    /* normally CanResetBusOffStart/STOP (and CanResetBusSleep) use this call so no other action is needed.
       But when application do this call the state has to be set to START here because it will not be done in SetControllerMode(). */
    { 
      (void)Can_SetControllerMode((uint8)channel, CAN_T_START);
    }
#endif
  }
}

/****************************************************************************
| NAME:             Can_CleanUpSendState
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| Can_CleanUpSendState
Relation_Context:
Relation:
OneChOpt
MultiplexedTx
CommonCan
IfTxBuffer
TxFullCANSupport
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) Can_CleanUpSendState( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle logTxObjHandle;
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  CanObjectHandle logTxObjHandleStop;
# endif
  Can_HwHandleType Htrh;
  /* ----- Implementation ----------------------------------------------- */
  /* parameter channel is already checked by caller */
  /* #10 set all BasicCAN TX Objects to state FREE to allow a new transmission */
  Htrh = Can_GetTxBasicHandleStart(canHwChannel);
# if defined(C_ENABLE_MULTIPLE_BASICCAN_TX)
  for (; Htrh < Can_GetTxBasicHandleStop(canHwChannel); Htrh++)
# endif
  {
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST Can_GetHwHandle(Htrh));
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    logTxObjHandleStop = logTxObjHandle + (Can_HwHandleType)CAN_MULTIPLEXED_TX_MAX_OBJ(Htrh); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    for (; logTxObjHandle < logTxObjHandleStop; logTxObjHandle++)
# endif
    {
      Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
    }
  }
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  /* #20 set all FullCAN TX Objects to state FREE to allow a new transmission */
  for (Htrh = Can_GetTxFullHandleStart(canHwChannel); Htrh < Can_GetTxFullHandleStop(canHwChannel); Htrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST Can_GetHwHandle(Htrh));
    Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */ 
  }
# endif
}

/****************************************************************************
| NAME:             CanHL_StartTransition
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_StartTransition
Relation_Context:
Relation:
OneChOpt
CommonCan
HardwareLoop
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_StartTransition( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType transitionRequest;
  Can_ReturnType retval = CAN_NOT_OK; /* PRQA S 3197 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  { /* #20 HW request transition (LL) \trace SPEC-1628 */
    {
      tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
    
    #if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT ) 
      /* BusOff behaviour must ensure 128x11 recessive bits - auto-recovery is used. start mode is requested if CAN controller is not in busoff mode */
      if (Can_IsIsBusOff(channel))
      {
        pFlexCANLocal->control1 &= (vuint32)(~kFlexCAN_BOFF_REC); /* activate BusOff auto recovery */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL01 */
      }
    #else
    # if defined(C_ENABLE_SILENT_MODE)
      /* set listen only mode if silent mode is requested*/
      if (Can_GetSilentModeState(channel) == CAN_SILENT_ACTIVE)
      {
        pFlexCANLocal->control1 |= kFlexCAN_LOM; /* SBSW_CAN_LL01 */
      }
      else
      {
        pFlexCANLocal->control1 &= (vuint32)(~kFlexCAN_LOM); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL01 */
      }
    # endif
      /* request NORMAL mode - considered as CanStart mode */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */ /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit  */ /* SBSW_CAN_LL01 */
    
      /* the transition CanStop - CanStart does also leave a potential BusOff state */
      pFlexCANLocal->control1 |= kFlexCAN_BOFF_REC; /* SBSW_CAN_LL01 */
    #endif
    
      transitionRequest = kCanRequested;
    }
    if ( transitionRequest == CAN_REQUESTED ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* COV_CAN_TRANSITION_REQUEST_START */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      CanHL_ApplCanTimerStart(kCanLoopStart); /* SBSW_CAN_HL38 */
      /* #40 start Loop that wait (ASR4: short time) for transition \trace SPEC-1642, SPEC-1635, SPEC-1630 */
      do
      { /* #45 HW check mode reached (LL) */
        {
        #if !defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
          tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
        #endif
        
        #if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT ) 
          Can_GetStatusReq(channel) |= CAN_REQ_INIT_NO_STOP; /* mark ongoing state change */ /* SBSW_CAN_HL01 */
        
          /* BusOff behaviour must ensure 128x11 recessive bits - auto-recovery is used. start mode is requested if CAN controller is not in busoff mode */
          if (Can_IsIsBusOff(channel))
          {
            CanLL_HandleBusOff(CAN_CHANNEL_CANPARA_ONLY);
            
            transitionRequest = kCanFailed;
          }
          else /* no BusOff occurred */
          {
            transitionRequest = CanLL_HandleStartProcess(CAN_HW_CHANNEL_CANPARA_ONLY);
          }
          Can_GetStatusReq(channel) &= (uint8)(~(CAN_REQ_INIT_NO_STOP)); /* remove mark ongoing state change */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL01 */
        #else
          /* check if NORMAL mode is reached - considered as CanStart mode */
          if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) == kFlexCAN_NORMAL_MODE) /* SBSW_CAN_LL01 */
          {
            transitionRequest = kCanOk;
          }
          else
          {
            transitionRequest = kCanFailed;
          }
        #endif
        }
        CanHL_ApplCanTimerLoop(kCanLoopStart); /* COV_CAN_TRANSITION_REQUEST_START */
      } while ( transitionRequest != CAN_OK ); /* COV_CAN_TRANSITION_REQUEST_START */
      CanHL_ApplCanTimerEnd (kCanLoopStart); /* SBSW_CAN_HL38 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */ 
      if ( transitionRequest != CAN_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* COV_CAN_TRANSITION_REQUEST_START */
      { /* PRQA S 3201 */ /* MD_Can_3201 */
#  if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
        /* #50 ASR4: transition failed so return OK but repeat it asynchronous */
        Can_SetStatusReq(channel, CAN_REQ_START); /* Asynchronous polling on */ /* SBSW_CAN_HL01 */
        retval = CAN_OK; /* PRQA S 3197,3198 */ /* MD_MSR_14.2 */
#  endif
      }
# endif
    }
  } /* loop canHwChannel */
# if defined(C_ENABLE_HW_LOOP_TIMER)
  if (( transitionRequest == CAN_OK ) && ( !Can_IsIsHardwareCanceled(channel) )) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* COV_CAN_TRANSITION_REQUEST_START */
# else
  if ( transitionRequest == CAN_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* COV_CAN_TRANSITION_REQUEST_START */
# endif
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    /* #70 transition finished synchronous return OK and change internal state */
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_START)); /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
    /* #80 allow reinitialization in notification */
    Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
    /* #90 ASR4: call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_STARTED );
#endif
    retval = CAN_OK;
  }
  return retval;
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */

/****************************************************************************
| NAME:             CanHL_StopTransition
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_StopTransition
Relation_Context:
Relation:
OneChOpt
CommonCan
HardwareLoop
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_StopTransition( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_NOT_OK; /* PRQA S 3197 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  /* #20 ESCAN00073272 need Can_InitController() (in case of HW failure) */
  if( (Can_GetLogStatus(channel) & (CAN_STATUS_STOP | CAN_STATUS_START)) == 0 ) /* COV_CAN_HARDWARE_FAILURE */
  {
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
    Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(Can_GetLastInitObject(channel) - (uint8)Can_GetInitObjectStartIndex(channel)) & 0x03u))); /* SBSW_CAN_HL03 */
#else
    Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
#endif
  }
  {
    /* #25 set STOP request if not done in Can_InitController() before */
    Can_ReturnType transitionRequest;
    { /* #40 HW request transition (LL) \trace SPEC-1632 */
      {
        tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
        
      #if defined(C_ENABLE_SILENT_MODE)
        if ((pFlexCANLocal->control1 & kFlexCAN_LOM) == kFlexCAN_LOM)
        {
          Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
        }
      #endif
        /* request FREEZE mode - considered as CanStop mode */
        CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
        CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);    /* set FRZ bit */ /* SBSW_CAN_LL01 */
        CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_HALT);   /* set HALT bit */ /* SBSW_CAN_LL01 */
        
        transitionRequest = kCanRequested;
      }
      if ( transitionRequest == CAN_REQUESTED ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* COV_CAN_TRANSITION_REQUEST_STOP */
      { /* PRQA S 3201 */ /* MD_Can_3201 */
        CanHL_ApplCanTimerStart(kCanLoopStop); /* SBSW_CAN_HL38 */
        /* #60 start Loop that wait (ASR4: short time) for transition \trace SPEC-1636, SPEC-1635, SPEC-1630 */
        do
        { /* #65 HW check mode reached (LL) */
          {
            tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
            
            /* check if FREEZE mode is reached - considered as CanStop mode */
            if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) == kFlexCAN_FREEZE_MODE) /* SBSW_CAN_LL01 */
            {
              transitionRequest = kCanOk;
            }
            else
            {
              transitionRequest = kCanFailed;
            }
          }
          CanHL_ApplCanTimerLoop(kCanLoopStop); /* COV_CAN_TRANSITION_REQUEST_STOP */
        } while ( transitionRequest != CAN_OK ); /* COV_CAN_TRANSITION_REQUEST_STOP */
        CanHL_ApplCanTimerEnd(kCanLoopStop); /* SBSW_CAN_HL38 */
#  if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */ 
        if ( transitionRequest != CAN_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* COV_CAN_TRANSITION_REQUEST_STOP */
        { /* PRQA S 3201 */ /* MD_Can_3201 */
#   if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
          /* #70 ASR4: transition failed so return OK but repeat it asynchronous */
          Can_SetStatusReq(channel, CAN_REQ_STOP); /* Asynchronous polling on */ /* SBSW_CAN_HL01 */
          retval = CAN_OK;
#   endif
        }
#  endif
      }
    } /* loop canHwChannel */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
    if (( transitionRequest == CAN_OK ) && ( !Can_IsIsHardwareCanceled(channel) )) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* COV_CAN_TRANSITION_REQUEST_STOP */
#  else
    if ( transitionRequest == CAN_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* COV_CAN_TRANSITION_REQUEST_STOP */
#  endif
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      /* #110 transition finished synchronous return OK and change internal state */
      retval = CAN_OK;
      { /* #120 Use short initialization instead of Can_InitController() (LL) \trace SPEC-1627, SPEC-1646, SPEC-3965 */
        CanHL_StopReinit(CAN_HW_CHANNEL_CANPARA_ONLY);
      }
      Can_CleanUpSendState(CAN_CHANNEL_CANPARA_ONLY);
      Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
      /* #130 allow reinitialization in notification */
      Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
      /* #140 ASR4: call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
      CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_STOPPED );
#endif
    }
  }
  return retval;
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */

/****************************************************************************
| NAME:             CanHL_WakeupTransition
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_WakeupTransition
Relation_Context:
Relation:
OneChOpt
Wakeup
CommonCan
HardwareLoop
RamCheck, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WakeupTransition( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  /* ----- Implementation ----------------------------------------------- */
  { /* #130 emulated SLEEP (CAN_NOT_SUPPORTED is CAN_OK) (stay in STOP mode instead) \trace SPEC-1638 */
    /* #140 transition finished synchronous return OK and change internal state */
    retval = CAN_OK;
#if defined(C_ENABLE_CAN_RAM_CHECK) && !defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
      /* #150 do standard RAM check CanHL_DoRamCheck() */
    Can_SetLogStatus(channel, CAN_STATUS_UNINIT); /* Like PowerOn */ /* SBSW_CAN_HL02 */
    CanHL_DoRamCheck(CAN_CHANNEL_CANPARA_ONLY);
#endif
    /* #160 delete SLEEP for CAN_EMULATE_SLEEP and set to STOP \trace SPEC-1653 */
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
    /* #170 allow reinitialization in notification */
    Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
    /* #180 ASR4: call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_STOPPED );
#endif
  }
  return retval;
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */

#if defined(C_ENABLE_CAN_RAM_CHECK)
/****************************************************************************
| NAME:             CanHL_DoRamCheck
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_DoRamCheck
Relation_Context:
Wakeup
RamCheck
Relation:
RamCheck
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_DoRamCheck( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* SLEEP is already set as logical status for first WAKEUP after SLEEP (changed to STOP after this) */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
  /* #20 remove mark ongoing state change (force STOP transition in Can_InitController()) */
  Can_SetStatusReq(channel, Can_GetStatusReq(channel) & (uint8)(~(CAN_REQ_INIT_NO_STOP))); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL01 */
# endif
  Can_SetStatusReq(channel, Can_GetStatusReq(channel) | CAN_REQ_RAM_CHECK); /* SBSW_CAN_HL01 */
  /* #30 call Can_InitController() to perform the RAM check */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
  Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(Can_GetLastInitObject(channel) - (uint8)Can_GetInitObjectStartIndex(channel)) & 0x03u))); /* SBSW_CAN_HL03 */
# else
  Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
# endif
}
#endif /* C_ENABLE_CAN_RAM_CHECK */

/****************************************************************************
| NAME:             CanHL_SleepTransition
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_SleepTransition
Relation_Context:
Relation:
Wakeup, CommonCan
Wakeup, ExtendedStateMachine
Wakeup, PnEnable
Wakeup, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_SleepTransition( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_NOT_OK; /* PRQA S 3197 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  /* #150 no WAKEUP-source-ref: do emulated SLEEP mode \trace SPEC-1629, SPEC-1641, SPEC-1645, SPEC-3914, SPEC-3927 */
  {
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
    /* #160 controller stay in STOP mode / CAN_NOT_SUPPORTED is CAN_OK */
    retval = CAN_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#endif
#if (CAN_EMULATE_SLEEP == STD_ON) /* COV_CAN_EMULATE_SLEEP */
    retval = CAN_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_SLEEP)); /* SBSW_CAN_HL02 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
    /* #170 allow reinitialization in notification */
    Can_SetStatusReq(channel, Can_GetStatusReq(channel)& (uint8)(~(CAN_REQ_INIT_NO_STOP))); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL01 */
    /* #180 ASR4: call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_SLEEP );
# endif
#endif
  }
# if (CAN_EMULATE_SLEEP == STD_OFF) /* COV_CAN_EMULATE_SLEEP */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
# endif
  return retval;
} /* PRQA S 6010,6030,6050,6080*/ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

#if defined(C_ENABLE_CANCEL_IN_HW)
/****************************************************************************
| NAME:             CanHL_IsHigherCanIdPrio
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_IsHigherCanIdPrio
Relation_Context:
HwCancelTx
HwCancelTx, MultiplexedTx
HwCancelTx, IdenticalIdCancel
Relation:
IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_IsHigherCanIdPrio(Can_IdType CanId1, Can_IdType CanId2)
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
# if defined(C_ENABLE_MIXED_ID)
  /* #10 take care about mixed Extended and Standard ID format (shift Standard ID to match Extended format) */
  if (((CanId1) & CAN_ID_IDE_MASK) == CAN_ID_IDE_MASK)
  {
    CanId1 = CanId1 & (Can_IdType)(CAN_ID_MASK);
  } else {
    CanId1 = (Can_IdType)(((CanId1) & CAN_ID_MASK_STD) << 18);
  }
  if (((CanId2) & CAN_ID_IDE_MASK) == CAN_ID_IDE_MASK)
  {
    CanId2 = CanId2 & (Can_IdType)(CAN_ID_MASK);
  } else {
    CanId2 = (Can_IdType)(((CanId2) & CAN_ID_MASK_STD) << 18);
  }
# else
  /* #20 mask out unused bits */
  CanId1 = CanId1 & (Can_IdType)CAN_ID_MASK;
  CanId2 = CanId2 & (Can_IdType)CAN_ID_MASK;
# endif
  /* #30 compare CAN ID priority */
  if(CanId1 < CanId2)
  {
    retval = CAN_OK;
  }
  return retval;
}
#endif

#if defined(C_ENABLE_CANCEL_IN_HW) && defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
/****************************************************************************
| NAME:             CanHL_SortlogTxObjHandlePrioList
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_SortlogTxObjHandlePrioList
Relation_Context:
HwCancelTx, MultiplexedTx, IdenticalIdCancel #CanHL_WritePrepareCancelTx#
Relation:
TxBasicAmount #ActiveSendId#
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_SortlogTxObjHandlePrioList( CanHlObjectHandlePtrType logTxObjHandlePrioList )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle tmp_logTxObjHandle;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 sort element 0 and 1 */
  if ( CanHL_IsHigherCanIdPrio(Can_GetActiveSendId(logTxObjHandlePrioList[0]), Can_GetActiveSendId(logTxObjHandlePrioList[1])) == CAN_OK)
  {
    tmp_logTxObjHandle = logTxObjHandlePrioList[0];
    logTxObjHandlePrioList[0] = logTxObjHandlePrioList[1]; /* SBSW_CAN_HL21 */
    logTxObjHandlePrioList[1] = tmp_logTxObjHandle; /* SBSW_CAN_HL21 */
  }
  /* #20 sort element 1 and 2 */
  if ( CanHL_IsHigherCanIdPrio(Can_GetActiveSendId(logTxObjHandlePrioList[1]), Can_GetActiveSendId(logTxObjHandlePrioList[2])) == CAN_OK)
  {
    tmp_logTxObjHandle = logTxObjHandlePrioList[1];
    logTxObjHandlePrioList[1] = logTxObjHandlePrioList[2]; /* SBSW_CAN_HL21 */
    logTxObjHandlePrioList[2] = tmp_logTxObjHandle; /* SBSW_CAN_HL21 */
  }
  /* #30 sort element 0 and 1 again */
  if ( CanHL_IsHigherCanIdPrio(Can_GetActiveSendId(logTxObjHandlePrioList[0]), Can_GetActiveSendId(logTxObjHandlePrioList[1])) == CAN_OK)
  {
    tmp_logTxObjHandle = logTxObjHandlePrioList[0];
    logTxObjHandlePrioList[0] = logTxObjHandlePrioList[1]; /* SBSW_CAN_HL21 */
    logTxObjHandlePrioList[1] = tmp_logTxObjHandle; /* SBSW_CAN_HL21 */
  }
}
#endif

/****************************************************************************
| NAME:             CanHL_WritePrepare
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_WritePrepare
Relation_Context:
Relation:
TxFullCANSupport
HwCancelTx
HwCancelTx, MultiplexedTx
MultiplexedTx, HwCancelTx, IdenticalIdCancel
ChannelAmount
TxBasicAmount
TxFullAmount
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_WritePrepare( CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle  logTxObjHandle;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 calculate logical TX mailbox handle for FullCAN or for BasicCAN (Multiplexed TX) as start value */
  logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST Can_GetHwHandle(Hth));
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  if ( Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#endif
  { /* #20 BasicCAN preparation - search for hardware and logical transmit handle and do cancellation */
#if defined(C_ENABLE_CANCEL_IN_HW)
    CanObjectHandle logTxObjHandlePrioList[CAN_MULTIPLEXED_TX_MAX]; /* CM_CAN_HL19 */
#endif
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_ENABLE_CANCEL_IN_HW)
    uint8_least muxTx;
    uint8_least muxTx_max;
    uint8_least muxTx_use;
    muxTx_max = CAN_MULTIPLEXED_TX_MAX_OBJ(Hth); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    muxTx_use = muxTx_max;
#endif
    /* \trace SPEC-1677, SPEC-3800, SPEC-1672, SPEC-1679, SPEC-1673, SPEC-1671 */
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    for (muxTx = 0; muxTx < muxTx_max; muxTx++)
    { /* #30 over all multiplexed TX objects: find free mailbox or mailbox with identical ID*/
# if defined(C_ENABLE_CANCEL_IN_HW)
      logTxObjHandlePrioList[muxTx] = logTxObjHandle; /* SBSW_CAN_HL21 */
# endif
# if (CAN_IDENTICAL_ID_CANCELLATION == STD_ON) && defined(C_ENABLE_CANCEL_IN_HW)
      if ( ((PduInfo->id) == Can_GetActiveSendId(logTxObjHandle) ) && (Can_GetActiveSendState(logTxObjHandle) != CAN_FREE_OBJ) )
      { /* #40 Identical ID: priority 1 - cancel identical (also when free is available) */
        muxTx_use = muxTx;
        break;
      }
      if (Can_GetActiveSendState(logTxObjHandle) == CAN_FREE_OBJ)
      { /* #50 Identical ID: priority 2 - find free mailbox (no cancellation) */
        muxTx_use = muxTx; /* do not break ... next may be identical ID */
      }
# else
      if (Can_GetActiveSendState(logTxObjHandle) == CAN_FREE_OBJ)
      { /* #60 else priority 1 - find free mailbox (no cancellation) */
        break;
      }
# endif
      logTxObjHandle++;
    }
# if (CAN_IDENTICAL_ID_CANCELLATION == STD_ON) && defined(C_ENABLE_CANCEL_IN_HW)
    if (muxTx_use == muxTx_max)
    { /* #70 found no free mailbox or identical ID - so set to last valid handle */
      logTxObjHandle--;
    }
    else
    { /* #80 found free or identical mailbox - so set handle to it */
      muxTx = muxTx_use;
      logTxObjHandle = logTxObjHandlePrioList[muxTx]; /* PRQA S 3353, 3689 */ /* MD_Can_Asr_3353_logTxobjHandle, MD_Can_Asr_3689_MuxTx */
    }
# else
    if (muxTx == muxTx_max)
    { /* #90 found no free mailbox - so set to last valid handle */
      muxTx = 0; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
      logTxObjHandle--;
    } /* #100 otherwise the muxTx and logTxObjHandle are the free or to be cancelled one */
# endif
#else /* C_ENABLE_MULTIPLEXED_TRANSMISSION */
# if defined(C_ENABLE_CANCEL_IN_HW)
    muxTx = 0;
    logTxObjHandlePrioList[muxTx] = logTxObjHandle; /* SBSW_CAN_HL21 */
# endif
#endif
#if defined(C_ENABLE_CANCEL_IN_HW) /* \trace SPEC-3982, SPEC-1674 */
    CanHL_WritePrepareCancelTx(CAN_CHANNEL_CANPARA_FIRST logTxObjHandle, muxTx, muxTx_max, logTxObjHandlePrioList, PduInfo); /* SBSW_CAN_HL28 */
#endif /* (C_ENABLE_CANCEL_IN_HW) */
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_ENABLE_CANCEL_IN_HW)
    CAN_DUMMY_STATEMENT(muxTx_use); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  } /* end BasicCAN handling */
  /* #200 no special FullCAN handling needed */
#if !defined(C_ENABLE_CANCEL_IN_HW)
  CAN_DUMMY_STATEMENT(PduInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  return logTxObjHandle;
}

#if defined(C_ENABLE_CANCEL_IN_HW)
/****************************************************************************
| NAME:             CanHL_WritePrepareCancelTx
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_WritePrepareCancelTx
Relation_Context:
HwCancelTx
Relation:
DevErrorDetect
CanFdSupport
MultiplexedTx, IdenticalIdCancel
OneChOpt
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepareCancelTx( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle logTxObjHandle, uint8_least muxTx, uint8_least muxTx_max, CanHlObjectHandlePtrType logTxObjHandlePrioList, Can_PduInfoPtrType PduInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 backup ID, DLC, data, PDU for possible cancellation - as parameter to IF */
  if (Can_GetActiveSendState(logTxObjHandle) == CAN_FREE_OBJ)
  {
    /* #20 SDU pointer may be a null pointer in case the DLC is 0 - so do not copy data in this case */
    if(PduInfo->sdu != NULL_PTR)
    {
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      if(sizeof(Can_GetCanTxBasicDataBuffer(channel,muxTx)) >= PduInfo->length) /* CM_CAN_HL20 */
# endif
      {
# if defined(C_ENABLE_CAN_FD_FULL)
        /* #25 copy data with VStdLib optimized copy routine for CAN-FD messages (use alignment info) */
        VStdMemCpy((void*)Can_GetCanTxBasicDataBuffer(channel,muxTx), (void*)PduInfo->sdu, PduInfo->length); /* SBSW_CAN_HL22 */
# else
        Can_GetCanTxBasicDataBuffer(channel,muxTx)[0] = PduInfo->sdu[0]; /* PRQA S 3689 */ /* MD_Can_Asr_3689_MuxTx */ /* SBSW_CAN_HL22 */
        Can_GetCanTxBasicDataBuffer(channel,muxTx)[1] = PduInfo->sdu[1]; /* PRQA S 3689 */ /* MD_Can_Asr_3689_MuxTx */ /* SBSW_CAN_HL22 */
        Can_GetCanTxBasicDataBuffer(channel,muxTx)[2] = PduInfo->sdu[2]; /* PRQA S 3689 */ /* MD_Can_Asr_3689_MuxTx */ /* SBSW_CAN_HL22 */
        Can_GetCanTxBasicDataBuffer(channel,muxTx)[3] = PduInfo->sdu[3]; /* PRQA S 3689 */ /* MD_Can_Asr_3689_MuxTx */ /* SBSW_CAN_HL22 */
        Can_GetCanTxBasicDataBuffer(channel,muxTx)[4] = PduInfo->sdu[4]; /* PRQA S 3689 */ /* MD_Can_Asr_3689_MuxTx */ /* SBSW_CAN_HL22 */
        Can_GetCanTxBasicDataBuffer(channel,muxTx)[5] = PduInfo->sdu[5]; /* PRQA S 3689 */ /* MD_Can_Asr_3689_MuxTx */ /* SBSW_CAN_HL22 */
        Can_GetCanTxBasicDataBuffer(channel,muxTx)[6] = PduInfo->sdu[6]; /* PRQA S 3689 */ /* MD_Can_Asr_3689_MuxTx */ /* SBSW_CAN_HL22 */
        Can_GetCanTxBasicDataBuffer(channel,muxTx)[7] = PduInfo->sdu[7]; /* PRQA S 3689 */ /* MD_Can_Asr_3689_MuxTx */ /* SBSW_CAN_HL22 */
# endif
      }
    }
    Can_SetActiveSendId(logTxObjHandle, PduInfo->id); /* SBSW_CAN_HL23 */
    Can_SetActiveSendLength(logTxObjHandle, PduInfo->length); /* SBSW_CAN_HL23 */
    Can_SetActiveSendSdu(logTxObjHandle, &Can_GetCanTxBasicDataBuffer(channel,muxTx)[0]); /* PRQA S 3689 */ /* MD_Can_Asr_3689_MuxTx */ /* SBSW_CAN_HL23 */
    Can_SetActiveSendSwPduHandle(logTxObjHandle, PduInfo->swPduHandle); /* SBSW_CAN_HL23 */
  }
  else
  /* #30 no free send mailbox available */
  {
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
#  if (CAN_IDENTICAL_ID_CANCELLATION == STD_ON)
    /* #40 no identical ID found before */
    if (muxTx == muxTx_max) 
#  endif
    { /* #50 sort multiplexed TX handles to get the low priority first */
      CanHL_SortlogTxObjHandlePrioList(logTxObjHandlePrioList); /* SBSW_CAN_HL17 */
      muxTx = 0;
    }
    for (; muxTx < muxTx_max; muxTx++)
# else
    muxTx=0;
# endif
    { /* #60 no-MUX:       use 1st mailbox */
      /* #70 MUX:          iterate over all normal TX mailboxes */
      /* #80 identical ID: use only identical ID in mailbox */
      /* \trace SPEC-1753 */
# if (CAN_IDENTICAL_ID_CANCELLATION == STD_ON)
#  if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
      /* #90 identical include FD and ExtID flags */
      /* #100 finished when identical ID is already cancelled */
      if ( (Can_GetActiveSendState(logTxObjHandlePrioList[muxTx]) == CAN_CANCEL_OBJ) && (PduInfo->id == Can_GetActiveSendId(logTxObjHandlePrioList[muxTx])))
      {
        break; 
      }
      else
#  endif
      if ( ((CanHL_IsHigherCanIdPrio(PduInfo->id, Can_GetActiveSendId(logTxObjHandlePrioList[muxTx])) == CAN_OK) || (PduInfo->id == Can_GetActiveSendId(logTxObjHandlePrioList[muxTx]))) && \
           (Can_GetActiveSendState(logTxObjHandlePrioList[muxTx]) == CAN_SEND_OBJ) )
# else
      if ( ( CanHL_IsHigherCanIdPrio(PduInfo->id, Can_GetActiveSendId(logTxObjHandlePrioList[muxTx])) == CAN_OK) && \
           (Can_GetActiveSendState(logTxObjHandlePrioList[muxTx]) == CAN_SEND_OBJ) )
# endif
      /* #110 found lower priority PDU or Identical ID - ready to cancel (others may in cancel process) \trace SPEC-1747, SPEC-15133, SPEC-1685, SPEC-1690, SPEC-1692, SPEC-1676, SPEC-3856, SPEC-1683, SPEC-15126 */
      {
        Can_HwHandleType txObjHandle;
        /* #120 mark as to be cancelled by hardware */
        Can_SetActiveSendState(logTxObjHandlePrioList[muxTx], CAN_CANCEL_OBJ); /* SBSW_CAN_HL41 */
        txObjHandle    = CanHL_GetTxLogToHwHandle(CAN_CHANNEL_CANPARA_FIRST logTxObjHandlePrioList[muxTx]);
        /* #125 HW cancel mailbox (LL) */
        GLOBAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, control) = kTxCodeAbort; /* SBSW_CAN_LL03 */
        
        /* #130 do not notify IF about successful cancellation because of recursion will not work! Hardware support not possible in this case */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
        /* #140 finished - only cancel one mailbox */ 
        break; /* PRQA S 0771,3333 */ /* MD_Can_14.6 */
# endif
      }
      else
      { /* avoid MISRA warning 2004 (if else if without ending else) */
        /* \trace SPEC-1754 */
      }
    }
  }
  CAN_DUMMY_STATEMENT(muxTx_max); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
} /* PRQA S 6060,6080 */ /* MD_MSR_STPAR,MD_MSR_STMIF */
#endif /* C_ENABLE_CANCEL_IN_HW */

/****************************************************************************
| NAME:             CanHL_WriteStart
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_WriteStart
Relation_Context:
Relation:
GenericPreTransmit
CanFdSupport
GenericPreTransmit, DynamicFullCanTxID, TxFullCANSupport
IDType, MixedId, DynamicFullCanTxID, TxFullCANSupport
OneChOpt
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WriteStart( CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType Hth, CanObjectHandle logTxObjHandle, Can_PduInfoPtrType PduInfo )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 free TX mailbox found so start transmission \trace SPEC-1744 */
  if (Can_GetActiveSendState(logTxObjHandle) == CAN_FREE_OBJ)
  {
    Can_HwHandleType txObjHandle;
    Can_SduPtrType   CanMemCopySrcPtr;
#if (CAN_GENERIC_PRETRANSMIT == STD_ON)
    /* #20 temporary buffer to avoid data modification on constant data */
    Can_PduType PduInfo_var;
#endif
#if defined(C_ENABLE_CAN_FD_USED)
    Can_IdType pduInfo_var_id;
    uint8 pduInfo_var_dlc;
# if defined(C_ENABLE_CAN_FD_FULL)
    uint8 pduInfo_var_dli;
# endif
#endif
    #if defined ( C_ENABLE_CAN_FD_FULL )
    vuint32     canFDTxBuf[16];
    #else
    tFlexCANPtr pFlexCANLocal; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
    vuint32     canTxBuf[2];
    #endif
#if (CAN_GENERIC_PRETRANSMIT == STD_ON)
    Can_PduInfoPtrType_var PduInfoPtr_var;
    /* #25 PduInfo copy from ROM pointer context to RAM pointer context */
    PduInfoPtr_var = &PduInfo_var;
    PduInfo_var.id = PduInfo->id; 
    PduInfo_var.length = PduInfo->length;
    PduInfo_var.sdu = PduInfo->sdu;
    PduInfo_var.swPduHandle = PduInfo->swPduHandle;
    Appl_GenericPreTransmit( (uint8)channel, PduInfoPtr_var );  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL24 */
#  if !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) /* COV_DYNAMIC_FULLCAN_ID */
#   if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
    if (Can_GetMailboxType(Hth) == CAN_TX_FULLCAN_TYPE)
    {
      PduInfo_var.id = PduInfo->id; /* avoid overwrite of ID by Appl_GenericPreTransmit() this would lead to a wrong ID-Type within writing the DLC */
    }
#   endif
#  endif
#endif
#if defined(C_ENABLE_CAN_FD_USED)
    pduInfo_var_id = PDUINFO_PTR->id;
    if (PduInfo->length <= 8) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE)
      { /* #30 remove FD flag when no FD support is activated in this initialization structure and DLC not greater than 8 */
        /* CAN FD also support an extended payload which allows the transmission of up to 64 bytes.
        This feature also depends on the CAN FD configuration (see CanControllerFdBaudrateConfig).
        Therefore, if the CAN FD feature is enabled and the CAN FD flag is set in CanId passed to
         Can_Write(), CanDrv supports the transmission of PDUs with a length up to 64 bytes.
        If there is a request to transmit a CAN FD frame without the CAN FD feature enabled the
        frame is sent as conventional CAN frame as long as the PDU length <= 8 bytes. */
        pduInfo_var_id = pduInfo_var_id & ((Can_IdType)(CAN_ID_IDE_MASK | CAN_ID_MASK)); /* CAN_FD_   mask out the FD bit */
      }
    }
#endif
    /* #40 remember PDU and send state to use it in Confirmation function \trace SPEC-1675, SPEC-3921 */
    Can_SetActiveSendPdu(logTxObjHandle, PDUINFO_PTR->swPduHandle); /* SBSW_CAN_HL05 */
    Can_SetActiveSendState(logTxObjHandle, CAN_SEND_OBJ); /* SBSW_CAN_HL04 */
    txObjHandle =  CanHL_GetTxLogToHwHandle(CAN_CHANNEL_CANPARA_FIRST logTxObjHandle);
#if defined(C_ENABLE_CAN_FD_USED)
    /* #50 CAN FD convert data length (0-64) to DLC (0-15) and to DLI (0-8,12,16,20,24,32,48,64) */
    pduInfo_var_dlc = CAN_ENCODE_DLI(PDUINFO_PTR->length);
# if defined(C_ENABLE_CAN_FD_FULL)
    pduInfo_var_dli = CAN_DECODE_DLI(pduInfo_var_dlc);
# endif
#endif
    /* #55 HW prepare transmission (LL) */
    #if defined ( C_ENABLE_CAN_FD_FULL )
    #else
    pFlexCANLocal = pFlexCAN(canHwChannel);
    #endif
    /* #60 Set ID, ID type and DLC in HW register depend on ID type */
#if defined(C_ENABLE_EXTENDED_ID)
# if defined(C_ENABLE_MIXED_ID)
    if ( ((PDUINFO_ID) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK)
    {
#  if !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) /* COV_DYNAMIC_FULLCAN_ID */
#   if defined(C_ENABLE_TX_FULLCAN_OBJECTS) 
      if (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)
#   endif
#  endif
      {
        #  if defined( C_ENABLE_EXTENDED_ID ) /* COV_CAN_EXTENDED_ID */
        LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, msgID) = (vuint32)(MK_STDID0(PDUINFO_ID)); /* SBSW_CAN_LL03 */
        #  else
        LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, msgID) = (vuint32)(MK_STDID0(PDUINFO_ID)) << 16; /* SBSW_CAN_LL03 */
        #  endif
      }
      LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, control) = (vuint16)(((vuint16)MK_TX_DLC(PDUINFO_DLC) & kTxDlcMask) | kTxCodeFree); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL03 */
    }
    else
# endif
    {
# if !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) /* COV_DYNAMIC_FULLCAN_ID */
#  if defined(C_ENABLE_TX_FULLCAN_OBJECTS) 
      if (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)
#  endif
# endif
      {
        #  if defined( C_ENABLE_EXTENDED_ID ) /* COV_CAN_EXTENDED_ID */
        LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, msgID) = (vuint32)(MK_EXTID0(PDUINFO_ID)); /* SBSW_CAN_LL03 */
        #  else
        LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, msgID) = (vuint32)(MK_EXTID0(PDUINFO_ID)) << 16; /* SBSW_CAN_LL03 */
        #  endif
      }
      LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, control) = (vuint16)(((vuint16)MK_TX_DLC_EXT(PDUINFO_DLC) & kTxDlcMask) | kTxCodeFree); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL03 */
    }
#else
# if !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) /* COV_DYNAMIC_FULLCAN_ID */
#  if defined(C_ENABLE_TX_FULLCAN_OBJECTS) 
    if (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)
#  endif
# endif
    {
      #  if defined( C_ENABLE_EXTENDED_ID ) /* COV_CAN_EXTENDED_ID */
      LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, msgID) = (vuint32)(MK_STDID0(PDUINFO_ID)); /* SBSW_CAN_LL03 */
      #  else
      LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, msgID) = (vuint32)(MK_STDID0(PDUINFO_ID)) << 16; /* SBSW_CAN_LL03 */
      #  endif
    }
    LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, control) = (vuint16)(((vuint16)MK_TX_DLC(PDUINFO_DLC) & kTxDlcMask) | kTxCodeFree); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL03 */
#endif
    if(PDUINFO_PTR->sdu != NULL_PTR)
    { /* #70 Set CAN data in HW register (LL) - only when data pointer is not null \trace SPEC-1680, SPEC-1572, SPEC-1678, SPEC-60421 */
      CanMemCopySrcPtr = PDUINFO_PTR->sdu;
#if defined(C_ENABLE_CAN_FD_FULL)
      /* copy FD data into tx message object */
      {
        vuint8 idx, idxByte, idxWord, dataWordLen, sduWordLen, sduResLen;
        vuint32 paddingWordValue;
      
        sduWordLen = PDUINFO_PTR->length >> 2;
        sduResLen = PDUINFO_PTR->length & 0x03u;
        CanCopyFDPadding2Uint32(paddingWordValue, Can_GetMailboxFdPadding(Hth));
      
        idxByte = 0;
        for (idxWord = 0; idxWord < sduWordLen; idxWord++)
        {
          CanCopyFDDataBytes2Uint32(canFDTxBuf[(idxWord & 0x0F)], &CanMemCopySrcPtr[idxByte]); /* SBSW_CAN_LL11 */ /* CM_CAN_LL13 */
          idxByte += 4;
        }
        if (sduResLen != 0)
        {
          /* data bytes do not fit into a whole word, mix data bytes and padding value */
          canFDTxBuf[(idxWord & 0x0F)] = 0; /* SBSW_CAN_LL11 */ /* CM_CAN_LL13 */
          for (idx = idxByte; idx < PDUINFO_PTR->length; idx++)
          {
            CanAdd1FDByte2Uint32(canFDTxBuf[(idxWord & 0x0F)], CanMemCopySrcPtr[idx]); /* SBSW_CAN_LL11 */ /* SBSW_CAN_LL11 */ /* CM_CAN_LL13 */
          }
          for (idx = PDUINFO_PTR->length; idx < (PDUINFO_PTR->length + (4 - sduResLen)); idx++)
          {
            CanAdd1FDByte2Uint32(canFDTxBuf[(idxWord & 0x0F)], Can_GetMailboxFdPadding(Hth)); /* SBSW_CAN_LL11 */ /* SBSW_CAN_LL11 */ /* CM_CAN_LL13 */
          }
          idxWord++;
        }
        dataWordLen = (pduInfo_var_dli + 3) >> 2;
        for (idx = idxWord; idx < dataWordLen; idx++) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          canFDTxBuf[idx] = paddingWordValue; /* SBSW_CAN_LL10 */
        }
      
        for (idx = 0; idx < dataWordLen; idx++)
        {
          LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, data[idx]) = canFDTxBuf[idx]; /* PRQA S 3353 */ /* MD_Can_3353_LL_canFDTxBuf */ /* SBSW_CAN_LL03 */
        }
      }
#else
      /* copy data into tx message object */
      CanCopyDataBytes2Uint32(canTxBuf, CanMemCopySrcPtr); /* SBSW_CAN_LL04 */  /* SBSW_CAN_LL04 */
      LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, data[0]) = canTxBuf[0]; /* SBSW_CAN_LL03 */
      LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, data[1]) = canTxBuf[1]; /* SBSW_CAN_LL03 */
#endif
    }
    /* #80 HW start transmission (LL) */
    retval = CAN_OK; /* default is OK - LL set it to kCanFailed/CAN_NOT_OK in case of issue */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
    {
    #if defined( C_ENABLE_CAN_FD_USED )
      if ( (PDUINFO_ID & CAN_ID_FD_MASK) == CAN_ID_FD_MASK ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, control) |= kTxCodeTransmitFD; /* start tx of the message */ /* SBSW_CAN_LL03 */
      }
      else
    #endif
      {
        LOCAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, control) |= kTxCodeTransmit; /* start tx of the message */ /* SBSW_CAN_LL03 */
      }
    #if defined (C_ENABLE_WORKAROUND_ERR005829)
      /* set the reserved mailbox twice to CodeInactive. This workaround is recommended by freescale. */
      LOCAL_MAILBOX_ACCESS(canHwChannel, INDEX_RSVD_MB(canHwChannel), control) |= kTxCodeInactive; /* SBSW_CAN_LL03 */
      LOCAL_MAILBOX_ACCESS(canHwChannel, INDEX_RSVD_MB(canHwChannel), control) |= kTxCodeInactive; /* SBSW_CAN_LL03 */
    #endif
    }
    /* HW finish transmission (LL) */
  }
  else
  { /* #200 no free TX mailbox found so return busy - also in case cancellation (BasicCAN) was possible \trace SPEC-1754, SPEC-1764, SPEC-1747, SPEC-3878, SPEC-3856 */
    retval = CAN_BUSY;
  }
  CAN_DUMMY_STATEMENT(Hth); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return retval;
}  /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
/****************************************************************************
| NAME:             CanHL_StartProcessed
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_StartProcessed
Relation_Context:
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_StartProcessed( CAN_CHANNEL_CANTYPE_ONLY ) /* COV_CAN_TRANSITION_REQUEST_START */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType transitionDone;
  /* ----- Implementation ----------------------------------------------- */
  /* #5 HW check mode reached */
  {
  #if !defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
  #endif
  
  #if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT ) 
    Can_GetStatusReq(channel) |= CAN_REQ_INIT_NO_STOP; /* mark ongoing state change */ /* SBSW_CAN_HL01 */
  
    /* BusOff behaviour must ensure 128x11 recessive bits - auto-recovery is used. start mode is requested if CAN controller is not in busoff mode */
    if (Can_IsIsBusOff(channel))
    {
      CanLL_HandleBusOff(CAN_CHANNEL_CANPARA_ONLY);
      
      transitionDone = kCanFailed;
    }
    else /* no BusOff occurred */
    {
      transitionDone = CanLL_HandleStartProcess(CAN_HW_CHANNEL_CANPARA_ONLY);
    }
    Can_GetStatusReq(channel) &= (uint8)(~(CAN_REQ_INIT_NO_STOP)); /* remove mark ongoing state change */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL01 */
  #else
    /* check if NORMAL mode is reached - considered as CanStart mode */
    if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) == kFlexCAN_NORMAL_MODE) /* SBSW_CAN_LL01 */
    {
      transitionDone = kCanOk;
    }
    else
    {
      transitionDone = kCanFailed;
    }
  #endif
  }
  if ( transitionDone == CAN_OK ) /* PRQA S 3355,3356,3358,3359,3353 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_Asr_3353_CommonCanTransition */
  { /* #30 Mode changed - notify CanIf_ControllerModeIndication() and reset request */  /* PRQA S 3201 */ /* MD_Can_3201 */
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_START)); /* SBSW_CAN_HL02 */
    Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
    /* \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_STARTED );
  }
}

/****************************************************************************
| NAME:             CanHL_StopProcessed
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_StopProcessed
Relation_Context:
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_StopProcessed( CAN_CHANNEL_CANTYPE_ONLY ) /* COV_CAN_TRANSITION_REQUEST_STOP */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType transitionDone;
  /* ----- Implementation ----------------------------------------------- */
  /* #5 HW check mode reached */
  {
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
    
    /* check if FREEZE mode is reached - considered as CanStop mode */
    if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) == kFlexCAN_FREEZE_MODE) /* SBSW_CAN_LL01 */
    {
      transitionDone = kCanOk;
    }
    else
    {
      transitionDone = kCanFailed;
    }
  }
  if ( transitionDone == CAN_OK ) /* PRQA S 3355,3356,3358,3359,3353 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_Asr_3353_CommonCanTransition */
  { /* #30 Mode changed - notify CanIf_ControllerModeIndication() and reset request */  /* PRQA S 3201 */ /* MD_Can_3201 */
    { /* #40 short initialization after mode change (LL) \trace SPEC-1627, SPEC-1646, SPEC-3965 */
      CanHL_StopReinit(CAN_HW_CHANNEL_CANPARA_ONLY);
    }
    Can_CleanUpSendState(CAN_CHANNEL_CANPARA_ONLY);
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
    Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
    /* \trace SPEC-1726, SPEC-1644, SPEC-1635, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), CANIF_CS_STOPPED );
  }
}


#endif /* CAN_ENABLE_MICROSAR_VERSION_MSR40X */

/****************************************************************************
| NAME:             CanHL_GetTxHwToLogHandle
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_GetTxHwToLogHandle
Relation_Context:
TxFullCANSupport
HwCancelTx
Relation:
DevErrorDetect
OneChOpt
ChannelAmount
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_GetTxHwToLogHandle( CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwTxObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle logTxObjHandle;
  /* ----- Implementation ----------------------------------------------- */
#if defined(CAN_TXINDIRECTIONHWTOLOG) /* COV_CAN_TXINDIRECTIONHWTOLOG */
  /* #10 get logical handle from generated indirection table */
  logTxObjHandle = (CanObjectHandle) Can_GetTxIndirectionHwToLog((hwTxObjHandle) + Can_GetTxIndirectionHwToLogStart(channel));
#else
  /* #20 get logical handle by add generated offset to hardware handle */
  logTxObjHandle = (CanObjectHandle)(hwTxObjHandle + Can_GetTxOffsetHwToLog(channel));
#endif
#if (CAN_SAFE_BSW == STD_ON)
  if ((logTxObjHandle + CAN_MULTIPLEXED_TX_MAX) >= (Can_HwHandleType)Can_GetSizeOfActiveSendObject()) /* CM_CAN_HL03 */ /* COV_CAN_GENDATA_FAILURE */
  { /* just to secure SilentBSW */
    logTxObjHandle = (Can_HwHandleType)(Can_GetSizeOfActiveSendObject() - CAN_MULTIPLEXED_TX_MAX); /* -1 is used later on so don't use 0 here */
# if (CAN_DEV_ERROR_REPORT == STD_ON)  
    Can_CallDetReportError(CAN_WRITE_ID, CAN_E_PARAM_HANDLE);
# endif
  }
#endif
  return logTxObjHandle;
}

/****************************************************************************
| NAME:             CanHL_GetTxLogToHwHandle
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_GetTxLogToHwHandle
Relation_Context:
HwCancelTx
Relation:
OneChOpt
ChannelAmount
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_HwHandleType, STATIC_CODE) CanHL_GetTxLogToHwHandle( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle logTxObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_HwHandleType hwTxObjHandle;
  /* ----- Implementation ----------------------------------------------- */
#if defined(CAN_TXINDIRECTIONHWTOLOG) /* COV_CAN_TXINDIRECTIONHWTOLOG */
  /* #10 get hardware handle from generated indirection table */
  hwTxObjHandle = (Can_HwHandleType) Can_GetTxIndirectionLogToHw(logTxObjHandle);
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
#else
  /* #20 get hardware handle by subtract generated offset from logical handle */
  hwTxObjHandle = (Can_HwHandleType)(logTxObjHandle - Can_GetTxOffsetHwToLog(channel));
#endif
  return hwTxObjHandle;
}

#if defined(C_ENABLE_CAN_RAM_CHECK)
/****************************************************************************
| NAME:             CanHL_RamCheckMailboxNotification
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RamCheckMailboxNotification
Relation_Context:
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
Relation:
RamCheck
OneChOpt
ChannelAmount
TxFullAmount
TxBasicAmount
RxFullAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RamCheckMailboxNotification( CAN_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwObjHandle, Can_HwHandleType htrh ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 notify application about corrupt mailbox */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  CanIf_RamCheckCorruptMailbox((uint8)Can_GetCanToCanIfChannelMapping(channel), htrh);
# else
#  if defined(C_ENABLE_NOTIFY_CORRUPT_MAILBOX) /* with Mailbox Notification */
  Appl_CanCorruptMailbox((uint8)channel, (hwObjHandle));
#  endif
# endif
  /* #20 deactivate mailbox */
  Can_SetMailboxState(htrh, CAN_DISABLED_OBJ); /* SBSW_CAN_HL34 */
  /* #30 deactivate controller */
  Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */

  CAN_DUMMY_STATEMENT(hwObjHandle); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  CAN_DUMMY_STATEMENT(htrh); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
}
#endif


/****************************************************************************
| NAME:             CanHL_SetValue16
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_SetValue16
Relation_Context:
Relation:
RamCheck
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue16( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask ) /* PRQA S 3219 */ /* MD_Can_Asr_3219 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  uint8 result = kCanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_HL35 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    /* #20 read back value for RamCheck */
    volatile uint16 readBack;
    readBack = *regPtr;
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 3198 */ /* MD_MSR_14.2 */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
  }
# else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  CAN_DUMMY_STATEMENT(readMask); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return result;
}

/****************************************************************************
| NAME:             CanHL_SetValue32
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_SetValue32
Relation_Context:
Relation:
RamCheck
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetValue32( CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, uint32 value, uint32 readMask ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 3219 */ /* MD_Can_Asr_3219 */
{
  uint8 result = kCanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_HL35 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    /* #20 read back value for RamCheck */
    volatile uint32 readBack;
    readBack = *regPtr;
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 3198 */ /* MD_MSR_14.2 */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
  }
# else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  CAN_DUMMY_STATEMENT(readMask); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return result;
}


/****************************************************************************
| NAME:             CanHL_SetOsValue16
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_SetOsValue16
Relation_Context:
Relation:
RamCheck
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_SetOsValue16( CAN_CHANNEL_CANTYPE_FIRST uint16 area, CanChipMsgPtr16 regPtr, uint16 value, uint16 readMask ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  uint8 result = kCanFalse;
  /* #10 write register value */
  CAN_WRITE_PROTECTED_REG16(area, regPtr, value); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */ /* SBSW_CAN_HL35 */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    /* #20 read back value for RamCheck */
    volatile uint16 readBack;
    readBack = CAN_READ_PROTECTED_REG16(area, regPtr); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */ /* SBSW_CAN_HL35 */
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCanTrue; /* PRQA S 3198 */ /* MD_MSR_14.2 */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
  }
# else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  CAN_DUMMY_STATEMENT(readMask); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  CAN_DUMMY_STATEMENT(area); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return result;
}


/****************************************************************************
| NAME:             CanHL_InitBegin
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitBegin
Relation_Context:
Relation:
CommonCan
OneChOpt
RamCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitBegin( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanInitHandle  initObject; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL
  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR;
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->channel;
#endif
  initObject = initInfo->initObject;

  /* #10 Set controller to initialization mode (LL) */
  # if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
  Can_SetStartModeRequestedOfControllerData(canHwChannel, FALSE); /* SBSW_CAN_LL02 */
  # endif
  
  
  /* set the FlexCAN Controller to INIT mode */
  CanLL_SetFlexCANToInitMode(CAN_HW_CHANNEL_CANPARA_FIRST initObject);
    
  /* perform soft-reset of FlexCAN Controller */
  CanLL_ExecuteSoftReset(CAN_HW_CHANNEL_CANPARA_ONLY);

#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  /* #20 Execute pattern RamCheck */
  if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
  {
    initInfo->isChCorrupt |= CAN_RAM_CHECK_BEGIN_REG_RESULT(channel); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
  } 
#endif

  /* #30 Initialize controller registers (Begin section) (LL) */
  {
    vuint16 tmpCANmaxmb,tmpCANmcr;
    vuint32 tmpCANctrl2,tmpCANcontrol1;
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
  
    /* configure CAN[MCR].MAXMB register value */
    tmpCANmaxmb = (vuint16)(CAN_HL_HW_TX_STOPINDEX(canHwChannel) - 1)
  #if defined( C_ENABLE_CANCEL_IN_HW )
    /* set AEN bit to enable Abort feature (Cancel in Hardware) */
    | kFlexCAN_AEN
  #endif
    ; 
  #if defined( C_ENABLE_CAN_FD_USED )
    if (Can_IsHasCANFDBaudrateOfControllerConfig(canHwChannel)) /* COV_CAN_FD_BAUDRATE_AVAILABILITY */
    {
      /* set FDEN bit to enable CAN FD */
      tmpCANmaxmb |= kFlexCAN_FDEN;
    }
  #endif 
    /* write configured value to register */ 
    initInfo->isChCorrupt |= CanHL_SetOsValue16(CAN_CHANNEL_CANPARA_FIRST CAN_AREA(canHwChannel), &pFlexCANLocal->canmaxmb, tmpCANmaxmb, kCanRamCheckMaskMAXMB); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
    
    /* configure CAN[MCR].MCR register value */
    tmpCANmcr = CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kNotFlexCAN_MCR_CFG_BTIS; /* SBSW_CAN_LL01 */
    /* set IRMQ bit to allow individual buffer masking configuration */
    tmpCANmcr |= kFlexCAN_IRMQ
    /* set SRXDIS bit to disable self-reception feature */
    | kFlexCAN_SRX_DIS
  #if defined( C_ENABLE_GLITCH_FILTER ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* set WAK_SRC bit to integrate low-pass filter to protect the FLEXCAN_RX input from spurious wake up */
    | kFlexCAN_WAK_SRC
  #endif
  #if !defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
    /* set FEN bit to enable RX FIFO */
    | kFlexCAN_FEN
  #endif
    ;
  # if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_WAKEUP_SUPPORT */
    if(Can_GetCanInterruptCounter(channel) == 0)
    {
      tmpCANmcr |= kFlexCAN_WAK_MSK; /* set WAK_MSK for wakeup interrupts */
    }
  # endif
    /* write configured value to register */ 
    initInfo->isChCorrupt |= CanHL_SetOsValue16(CAN_CHANNEL_CANPARA_FIRST CAN_AREA(canHwChannel), &pFlexCANLocal->canmcr, tmpCANmcr, kCanRamCheckMaskMCR); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
   
    /* configure CAN[CTRL1] register value */
  #if defined( C_ENABLE_EXTENDED_BITTIMING ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    tmpCANcontrol1 = Can_GetControl1OfInitObject(initObject) & kFlexCAN_CLK_SRC;
  #else
    tmpCANcontrol1 = Can_GetControl1OfInitObject(initObject);
  #endif
  #if defined( C_ENABLE_FLEXCAN_SAMPLING_MODE )
    tmpCANcontrol1 |= kFlexCAN_SMP;
  #endif
    tmpCANcontrol1 |= kFlexCAN_BOFF_REC;
  # if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )  
    if(Can_GetCanInterruptCounter(channel) == 0)
    {
      tmpCANcontrol1 |= kFlexCAN_BOFF_MSK;
    }
  # endif
    initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->control1, tmpCANcontrol1, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
  
  #if defined( C_ENABLE_EXTENDED_BITTIMING ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* configure CAN[CBT] register value (extended bit timing) */
    initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->cbt, Can_GetCBTOfInitObject(initObject), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
  #endif
  
  #if defined( C_ENABLE_CAN_FD_USED )
    if (Can_IsHasCANFDBaudrateOfControllerConfig(canHwChannel)) /* COV_CAN_FD_BAUDRATE_AVAILABILITY */
    {    
      /* configure CAN[FDCTRL] register value (CAN FD control) */
      initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pCanFDRegister(canHwChannel)->fdctrl, Can_GetFDCTRLOfInitObjectFD(initObject), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
    }
    
    if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) != CAN_NONE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      /* configure CAN[FDCBT] register value (CAN FD bit timing) */
      initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pCanFDRegister(canHwChannel)->fdcbt, Can_GetFDCBTOfInitObjectFD(initObject), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
    }
  #endif
  
  #if !defined ( C_ENABLE_FLEXCAN2_DERIVATIVE ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* configure CAN[CTRL2] register value */
    tmpCANctrl2 = RFFN_VALUE(canHwChannel) | kFlexCAN_MRP | kFlexCAN_RRS | kFlexCAN_EACEN
  #if defined( V_CPU_VYBRID ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
  # if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE ) /* COV_CAN_ENABLE_FLEXCAN_PARITY_CHECK */
    | kFlexCAN_ECRWRE
  # endif
  #endif
  # if defined( C_ENABLE_TASD )
    | Can_GetTASDOfInitObject(initObject)
  # else
    | kFlexCAN_TASD_DEFAULT
  # endif
    ;
  # if defined( C_ENABLE_CAN_FD_USED )
  #  if defined (C_ENABLE_ISO_CANFD) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) != CAN_NONE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      tmpCANctrl2 |= kFlexCAN_STFCNTEN;
    }
  #  endif
  # endif
    
    initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->ctrl2, tmpCANctrl2, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
  #endif
  
  
  #if defined( V_CPU_VYBRID ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
  # if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE ) /* COV_CAN_ENABLE_FLEXCAN_PARITY_CHECK */
    /* enable write on MECR register */
    pCanParityCheck(canHwChannel)->mecr &= (vuint32)(~kFlexCAN_ECRWRDIS); /* SBSW_CAN_LL08 */
    /* configuration of MECR register */
  #  if !defined ( C_ENABLE_FLEXCAN_PARITY_CHECK ) /* COV_CAN_ENABLE_FLEXCAN_PARITY_CHECK */
    /* disable parity check functionality (not supported but enabled by default) */
    initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pCanParityCheck(canHwChannel)->mecr, (vuint32)0x00000300, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
  #  endif
    /* disable write on MECR register */
    pCanParityCheck(canHwChannel)->mecr |= kFlexCAN_ECRWRDIS; /* SBSW_CAN_LL08 */
  # endif
  #endif
  
  #if defined( C_ENABLE_GLITCH_FILTER ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* configure glitch filter register value */
    initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pCanGlitchFilter(canHwChannel)->gfwR, GLITCH_FILTER_WIDTH(canHwChannel), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
  #endif
  }

#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CAN_DUMMY_STATEMENT(initObject); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return errorId;
} /* PRQA S 6010,6050 */ /* MD_MSR_STPTH,MD_MSR_STCAL */

#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitTxFullCAN
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitTxFullCAN
Relation_Context:
TxFullCANSupport
Relation:
CommonCan
OneChOpt
RamCheck
IDType
DynamicFullCanTxID
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxFullCAN( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_HwHandleType hwObjHandle;
  Can_HwHandleType Htrh;
  CanObjectHandle logTxObjHandle;
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
# endif
  errorId = CAN_E_NO_ERROR;
  /* #10 iterate over all FullCAN TX */
  for (Htrh = Can_GetTxFullHandleStart(canHwChannel); Htrh < Can_GetTxFullHandleStop(canHwChannel); Htrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
  { /* #20 initialize FullCAN TX mailboxes */ /* PRQA S 3201 */ /* MD_Can_3201 */
    hwObjHandle = Can_GetHwHandle(Htrh);
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST hwObjHandle);
    Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #30 RAM check for FullCAN TX mailboxes */
    initInfo->isMbCorrupt = kCanFalse; /* SBSW_CAN_HL36 */
    if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
    {
      initInfo->isMbCorrupt = CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
    } 
# endif
    /* HW specific TX initialization (LL) */
    
    {
    # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
      if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
    # endif
      {
        initInfo->isMbCorrupt |= CanHL_SetValue16(CAN_CHANNEL_CANPARA_FIRST &GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kTxCodeInactive, kCanRamCheckMailboxControl); /* set transmit object inactive */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
      }
    }
# if !defined(CAN_ENABLE_DYNAMIC_FULLCAN_ID) /* if needed the initialization of ID, DLC and type is done in InitTxObj to avoid problems with uninitialized registers */ /* COV_DYNAMIC_FULLCAN_ID */
    /* #40 set ID and DLC for FullCAN TX mailboxes */
#  if defined(C_ENABLE_EXTENDED_ID)
#   if defined(C_ENABLE_MIXED_ID)
    if ( (Can_GetIDValue(Htrh) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
      if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      # endif
      {
        GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) = CAN_MSGID(MK_STDID0(Can_GetIDValue(Htrh))); /* SBSW_CAN_LL03 */
      }
      # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
      if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      # endif
      {
        GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)(MK_TX_DLC(Can_GetDLC_FIFO(Htrh))) & kTxDlcMask; /* set ID type and DLC */ /* SBSW_CAN_LL03 */
      }
    }
    else
#   endif
    {
      # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
      if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      # endif
      {
        GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) = CAN_MSGID(MK_EXTID0(Can_GetIDValue(Htrh))); /* SBSW_CAN_LL03 */
      }
      # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
      if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      # endif
      {
        GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)(MK_TX_DLC_EXT(Can_GetDLC_FIFO(Htrh))) & kTxDlcMask; /* set ID type and DLC */ /* SBSW_CAN_LL03 */
      }
    }
#  else
    # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
    errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
    if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
    # endif
    {
      GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) = CAN_MSGID(MK_STDID0(Can_GetIDValue(Htrh))); /* SBSW_CAN_LL03 */
    }
    # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
    errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
    if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
    # endif
    {
      GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)(MK_TX_DLC(Can_GetDLC_FIFO(Htrh))) & kTxDlcMask; /* set ID type and DLC */ /* SBSW_CAN_LL03 */
    }
#  endif
# endif
# if defined(C_ENABLE_CAN_RAM_CHECK)
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(Htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
    }
    if( (initInfo->isMbCorrupt == kCanTrue) || (Can_GetMailboxState(Htrh) == CAN_DISABLED_OBJ) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
      if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      # endif
      {
        GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = 0; /* deactivate transmit mailbox */ /* SBSW_CAN_LL03 */
      }
      if (initInfo->isMbCorrupt == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST hwObjHandle, Htrh);
      }
    }
# endif
  }
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# else
  CAN_DUMMY_STATEMENT(initInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return errorId;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
#endif

/****************************************************************************
| NAME:             CanHL_InitTxBasicCAN
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitTxBasicCAN
Relation_Context:
Relation:
MultiplexedTx
CommonCan
OneChOpt
RamCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxBasicCAN( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_HwHandleType hwObjHandle;
  Can_HwHandleType Htrh;
  CanObjectHandle logTxObjHandle;
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
  CanObjectHandle logTxObjHandleStop;
  uint8_least muxTx_max;
#endif
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
#endif

  Htrh = Can_GetTxBasicHandleStart(canHwChannel);
#if defined(C_ENABLE_MULTIPLE_BASICCAN_TX)
  for (; Htrh < Can_GetTxBasicHandleStop(canHwChannel); Htrh++)
#endif
  { /* #10 iterate over all logical BasicCAN TX */
    hwObjHandle = Can_GetHwHandle(Htrh); /* do not use: hwObjHandle = CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) - Htrh may used by LL */
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST hwObjHandle);
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    muxTx_max = CAN_MULTIPLEXED_TX_MAX_OBJ(Htrh); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    logTxObjHandleStop = logTxObjHandle + (Can_HwHandleType) muxTx_max;
    for (; logTxObjHandle < logTxObjHandleStop; logTxObjHandle++)
#endif
    { /* #20 initialize BasicCAN TX mailboxes */
      Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
#if defined(C_ENABLE_CAN_RAM_CHECK)
      /* #30 RAM check for BasicCAN TX mailboxes */
      if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
      {
        initInfo->isMbCorrupt = CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
      } 
      else
      {
        initInfo->isMbCorrupt = kCanFalse; /* SBSW_CAN_HL36 */
      }
#endif
      /* HW specific TX initialization (LL) */
      
      {
      # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
        errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
        if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      # endif
        {
          initInfo->isMbCorrupt |= CanHL_SetValue16(CAN_CHANNEL_CANPARA_FIRST &GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kTxCodeInactive, kCanRamCheckMailboxControl); /* set transmit object inactive */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
        }
      }
#if defined(C_ENABLE_CAN_RAM_CHECK)
      if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
      { /* PowerOn */
        Can_SetMailboxState(Htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
      }
      if( (initInfo->isMbCorrupt == kCanTrue) || (Can_GetMailboxState(Htrh) == CAN_DISABLED_OBJ) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
      { /* #45 deactivate corrupt mailbox */
        # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
        errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
        if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
        # endif
        {
          GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = 0; /* deactivate transmit mailbox */ /* SBSW_CAN_LL03 */
        }
        if (initInfo->isMbCorrupt == kCanTrue)
        {  /* #50 notify application about corrupt mailbox and deactivate controller */
          CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST hwObjHandle, Htrh);
        }
      }
#endif
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
      hwObjHandle += (Can_HwHandleType)(Can_GetDLC_FIFO(Htrh) / muxTx_max); /* PRQA S 3199,3198 */ /* MD_Can_3199_dummy */
#endif
    }
  }
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#else
  CAN_DUMMY_STATEMENT(initInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  return errorId;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */


#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitRxFullCAN
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitRxFullCAN
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
RamCheck
IDType
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxFullCAN( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_HwHandleType hwObjHandle;
  Can_HwHandleType Htrh;
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
# endif
  for (Htrh = Can_GetRxFullHandleStart(canHwChannel); Htrh < Can_GetRxFullHandleStop(canHwChannel); Htrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* #10 iterate over all FullCAN RX mailboxes */ /* PRQA S 3201 */ /* MD_Can_3201 */
    hwObjHandle=Can_GetHwHandle(Htrh);
# if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #20 RAM check for FullCAN RX mailboxes */
    initInfo->isMbCorrupt = kCanFalse; /* SBSW_CAN_HL36 */
    if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
    {
      initInfo->isMbCorrupt = CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
    } 
# endif
    /* #30 set ID for FullCAN RX mailboxes (LL) */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
    if ( (Can_GetIDValue(Htrh) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      {
      # if !defined ( C_ENABLE_CAN_FD_FULL )
        tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
      # endif
        tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel); /* pointer to FlexCAN individual receive mask registers */
      
      # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
        errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
        if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      # endif
        {
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID), CAN_MSGID(MK_STDID0(Can_GetIDValue(Htrh))), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
        
          {
            initInfo->isMbCorrupt |= CanHL_SetValue16(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kRxCodeEmpty | (vuint16)(kCanIdTypeStd), kCanRamCheckMailboxControl); /* set ID type and set mailbox ready for receive */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
          }
      
          /* initialize individual mask values for each FullCAN mailbox */
          #if defined( C_ENABLE_EXTENDED_ID ) /* COV_CAN_EXTENDED_ID */
          # if defined( C_ENABLE_MIXED_ID ) /* COV_CAN_MIXED_ID */
          if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)kCanIdTypeExt) != 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          {
            initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskExt, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
          }
          else
          {
            initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskStd, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
          }
          # else
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskExt, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
          # endif
          #else
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskStd, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
          #endif
        }
      }
    }
    else
#  endif
    {
      {
      # if !defined ( C_ENABLE_CAN_FD_FULL )
        tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
      # endif
        tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel); /* pointer to FlexCAN individual receive mask registers */
      
      # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
        errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
        if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      # endif
        {
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID), CAN_MSGID(MK_EXTID0(Can_GetIDValue(Htrh))), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
        
          {
            initInfo->isMbCorrupt |= CanHL_SetValue16(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kRxCodeEmpty | (vuint16)(kCanIdTypeExt), kCanRamCheckMailboxControl); /* set ID type and set mailbox ready for receive */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
          }
      
          /* initialize individual mask values for each FullCAN mailbox */
          #if defined( C_ENABLE_EXTENDED_ID ) /* COV_CAN_EXTENDED_ID */
          # if defined( C_ENABLE_MIXED_ID ) /* COV_CAN_MIXED_ID */
          if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)kCanIdTypeExt) != 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          {
            initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskExt, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
          }
          else
          {
            initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskStd, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
          }
          # else
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskExt, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
          # endif
          #else
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskStd, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
          #endif
        }
      }
    }
# else
    {
    # if !defined ( C_ENABLE_CAN_FD_FULL )
      tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
    # endif
      tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel); /* pointer to FlexCAN individual receive mask registers */
    
    # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
      if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
    # endif
      {
        initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID), CAN_MSGID(MK_STDID0(Can_GetIDValue(Htrh))), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
      
        {
          initInfo->isMbCorrupt |= CanHL_SetValue16(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kRxCodeEmpty | (vuint16)(kCanIdTypeStd), kCanRamCheckMailboxControl); /* set ID type and set mailbox ready for receive */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
        }
    
        /* initialize individual mask values for each FullCAN mailbox */
        #if defined( C_ENABLE_EXTENDED_ID ) /* COV_CAN_EXTENDED_ID */
        # if defined( C_ENABLE_MIXED_ID ) /* COV_CAN_MIXED_ID */
        if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)kCanIdTypeExt) != 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskExt, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
        }
        else
        {
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskStd, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
        }
        # else
        initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskExt, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
        # endif
        #else
        initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], kCanRxMaskStd, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
        #endif
      }
    }
# endif
# if defined(C_ENABLE_CAN_RAM_CHECK)
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(Htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
    }
    if( (initInfo->isMbCorrupt == kCanTrue) || (Can_GetMailboxState(Htrh) == CAN_DISABLED_OBJ) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
      if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      # endif
      {
        GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = 0; /* deactivate receive mailbox */ /* SBSW_CAN_LL03 */
      }
      if (initInfo->isMbCorrupt == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST hwObjHandle, Htrh);
      }
    }
# endif
  }

# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# else
  CAN_DUMMY_STATEMENT(initInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return errorId;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitRxBasicCAN
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitRxBasicCAN
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
RamCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxBasicCAN( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_HwHandleType hwObjHandle;
  Can_HwHandleType Htrh;
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->Controller;
# endif
  for (Htrh = Can_GetRxBasicHandleStart(canHwChannel); Htrh < Can_GetRxBasicHandleStop(canHwChannel); Htrh++) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
  { /* #10 iterate over all BasicCAN RX mailboxes */ /* PRQA S 3201 */ /* MD_Can_3201 */
    for (hwObjHandle = Can_GetHwHandle(Htrh); hwObjHandle < (Can_HwHandleType)(Can_GetHwHandle(Htrh) + Can_GetDLC_FIFO(Htrh)); hwObjHandle++)
    {
# if defined(C_ENABLE_CAN_RAM_CHECK)
      /* #20 RAM check for BasicCAN RX mailboxes */
      initInfo->isMbCorrupt = kCanFalse; /* SBSW_CAN_HL36 */
      if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
      {
        initInfo->isMbCorrupt = CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)); /* SBSW_CAN_HL36 */ /* COV_CAN_HARDWARE_FAILURE */
      } 
# endif
      /* #30 initialize BasicCAN RX mailboxes (LL) */
      {
      # if !defined ( C_ENABLE_CAN_FD_FULL )
        tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
      # endif
        vuint8 filterHandle;
      # if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
        vuint32 locMsgIDMask;
        tRXFIFOPtr pRxFIFO = pRXFIFO(canHwChannel);
      # endif
        tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel); /* pointer to FlexCAN individual receive mask registers */
      
      #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
      #  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
        errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
      if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      #  endif
        {
          filterHandle = (vuint8)(Can_GetInitBasicCanIndex(CAN_HL_INFO_INIT_PTR(initObject)) + (hwObjHandle - CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel))); /* calculate BasicCan offset */
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID), Can_GetInitCodeOfInitBasicCan(filterHandle) & (vuint32)0x1FFFFFFF, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
          initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[hwObjHandle], (Can_GetInitMaskOfInitBasicCan(filterHandle) & (vuint32)0x1FFFFFFF) | 0xC0000000u, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
      
          {
      # if defined(C_ENABLE_EXTENDED_ID)
      #  if defined(C_ENABLE_MIXED_ID)   
            if((Can_GetInitCodeOfInitBasicCan(filterHandle) & kExtIDBit) == 0)
            {
              initInfo->isMbCorrupt |= CanHL_SetValue16(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kRxCodeEmpty, kCanRamCheckMailboxControl); /* configure mailbox as receive message buffer */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
            }
            else
      #  endif
            {
              initInfo->isMbCorrupt |= CanHL_SetValue16(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), (kRxCodeEmpty | (vuint16)kCanIdTypeExt), kCanRamCheckMailboxControl); /* configure mailbox as receive message buffer */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
            }
        # else
            initInfo->isMbCorrupt |= CanHL_SetValue16(CAN_CHANNEL_CANPARA_FIRST &LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control), kRxCodeEmpty, kCanRamCheckMailboxControl); /* configure mailbox as receive message buffer */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL03 */
      # endif
          }
        }
      #else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
        for(filterHandle = 0; filterHandle < NUMBER_OF_FILTERS(canHwChannel); filterHandle++)
        {
      #  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
          errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, filterHandle);
          if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
      #  endif
          {
            if (filterHandle < NUMBER_OF_FULL_CONFIGURABLE_FILTERS(canHwChannel)) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
            {
              /* initialize individual masks for Rx Fifo */
              locMsgIDMask = Can_GetInitMaskOfInitBasicCan(Can_GetInitBasicCanIndex(CAN_HL_INFO_INIT_PTR(initObject)) + filterHandle) & (vuint32)0x1FFFFFFF;
              initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pIndivRxMask->indivRxMask[filterHandle], (vuint32)((locMsgIDMask << 1) | kRxFIFO_MASK), kCanMaskAll32); /* bits REM and EXT must always match */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
            }
      
            /* initialize Id table for Rx Fifo */
            locMsgIDMask = Can_GetInitCodeOfInitBasicCan(Can_GetInitBasicCanIndex(CAN_HL_INFO_INIT_PTR(initObject)) + filterHandle) & (vuint32)0x1FFFFFFF;
      
            /* if Extended Id */
            if((Can_GetInitCodeOfInitBasicCan(Can_GetInitBasicCanIndex(CAN_HL_INFO_INIT_PTR(initObject)) + filterHandle) & kExtIDBit) != 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
            {
              initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pRxFIFO->rxIDTAB[filterHandle], (vuint32)((locMsgIDMask << 1) | kRxFIFO_EXT), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
            }
            else
            {
              initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pRxFIFO->rxIDTAB[filterHandle], (vuint32)(locMsgIDMask << 1), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL08 */
            }
          }
        }
      #endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
      
      #if !defined ( C_ENABLE_FLEXCAN2_DERIVATIVE ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
      # if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
        /* set global mask register for Rx Fifo to 'must match' */
        initInfo->isMbCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->rxfgmask, (kRxFIFO_MASK | (vuint32)0x3FFFFFFE), kCanMaskAll32); /* bits REM and EXT must always match */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
      # endif
      #endif
      }
# if defined(C_ENABLE_CAN_RAM_CHECK)
      if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
      { /* PowerOn */
        Can_SetMailboxState(Htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
      }
      if( (initInfo->isMbCorrupt == kCanTrue) || (Can_GetMailboxState(Htrh) == CAN_DISABLED_OBJ) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
      { /* #45 deactivate corrupt mailbox */
        #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
        #  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
        errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle);
        if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
        #  endif
        {
          GLOBAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = 0; /* deactivate receive mailbox */ /* SBSW_CAN_LL03 */
        }
        #else
        {
          vuint8 mailboxHandle;
          tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
          /* deactivate RxFifo and deactivate all mailboxes that were overlaid by RxFifo engine */
          CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FEN); /* SBSW_CAN_LL01 */
        
        # if defined ( C_ENABLE_RX_FULLCAN_OBJECTS )
          for(mailboxHandle = 0; mailboxHandle < CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel); mailboxHandle++)
        # else
          for(mailboxHandle = 0; mailboxHandle < CAN_HL_HW_TX_STARTINDEX(canHwChannel); mailboxHandle++)
        # endif
          {
        #  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
            errorId = Can_CheckMaxHwMailboxHandle(canHwChannel, mailboxHandle);
            if (errorId == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
        #  endif
            {
              LOCAL_MAILBOX_ACCESS(canHwChannel, mailboxHandle, control) = 0; /* deactivate receive mailbox */ /* SBSW_CAN_LL03 */
            }
          }
        }
        #endif
        if (initInfo->isMbCorrupt == kCanTrue)
        {  /* #50 notify application about corrupt mailbox and deactivate controller */
          CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST hwObjHandle, Htrh);
        }
      }
# endif
    }
  }
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# else
  CAN_DUMMY_STATEMENT(initInfo); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return errorId;
}  /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
#endif

/****************************************************************************
| NAME:             CanHL_InitEnd_InitMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitEnd_InitMode
Relation_Context:
Relation:
CommonCan
OneChOpt
RamCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_InitMode( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanInitHandle  initObject; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->channel;
#endif
  initObject = initInfo->initObject;


  /* #20 HW specific initialization end (LL) */
  {
    vuint32 tmpCANimask1;
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
  
  #if defined ( C_ENABLE_FLEXCAN2_DERIVATIVE ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* read timestamp to unlock the RxFifo to ensure correct receive behaviour after initialization process */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).timestamp = LOCAL_MAILBOX_ACCESS(canHwChannel, CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel), timestamp); /* SBSW_CAN_LL05 */
    /* clear BusOff, Error and WakeUp interrupt flags: Workaround for ESCAN00032346 */
    initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->estat, (CANSFR_TYPE)kFlexCAN_STATUS_INT, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
  #endif
  
    if(Can_GetCanInterruptCounter(channel) == 0)
    {
  
      /* configure CAN[IMASK1] register value */
      tmpCANimask1 =  CAN_INT_MASK1(canHwChannel)
  # if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
      & kCanRxFifoIntUnmask
  # endif
      ;
  # if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  #  if !defined(C_ENABLE_RX_BASICCAN_POLLING)
      tmpCANimask1 |= kRxFIFO_NEWMSG; /* enable Rx FIFO interrupt */
  #  elif defined (C_ENABLE_INDIVIDUAL_POLLING)
      if ((CAN_INT_MASK1(canHwChannel) & (vuint32)0x01) == (vuint32)0x01) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        tmpCANimask1 |= kRxFIFO_NEWMSG; /* enable Rx FIFO interrupt */
      }
  #  endif
  # endif
      initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->imask1, tmpCANimask1, kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
  
  # if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
      initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->imask2, CAN_INT_MASK2(canHwChannel), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
  # endif  
  # if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  #  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  #  endif
    {
      initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->imask3, CAN_INT_MASK3(canHwChannel), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
    }
  # endif
  # if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
      initInfo->isChCorrupt |= CanHL_SetValue32(CAN_CHANNEL_CANPARA_FIRST &pFlexCANLocal->imask4, CAN_INT_MASK4(canHwChannel), kCanMaskAll32); /* SBSW_CAN_HL36 */ /* SBSW_CAN_LL01 */
  # endif
    }
  }

#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CAN_DUMMY_STATEMENT(initObject); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return errorId;
}

/****************************************************************************
| NAME:             CanHL_InitEnd_StopMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitEnd_StopMode
Relation_Context:
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_StopMode( CanInitInfoPtrType initInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanInitHandle  initObject; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = initInfo->channel;
#endif
  initObject = initInfo->initObject;

  /* #10 HW specific initialization transition to STOP (LL) */
  /* nothing to do: FlexcCAN is already in FREEZE mode */

#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CAN_DUMMY_STATEMENT(initObject); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return errorId;
}

/****************************************************************************
| NAME:             CanHL_StopReinit
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_StopReinit
Relation_Context:
Wakeup, RamCheck
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_StopReinit( CAN_HW_CHANNEL_CANTYPE_ONLY ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 do a short initialization instead of full Can_InitController() in case of STOP transition (CanLL_StopReinit) */
  /* #20 Delete all Pending Interrupt and Pending flags for TX,RX,BUSOFF and WAKEUP */
  {
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
    vuint16          hwObjHandle;
  #if defined ( C_ENABLE_RX_BASICCAN_OBJECTS )
  # if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  # else
    vuint8 fifoLoopCnt = 0;
  # endif
  #endif
  
    pFlexCANLocal->iflag1 = CANSFR_SET; /* clear pending Rx/Tx interrupts */ /* SBSW_CAN_LL01 */
  #if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    pFlexCANLocal->iflag2 = CANSFR_SET; /* clear pending Rx/Tx interrupts */ /* SBSW_CAN_LL01 */
  #endif  
  #if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  # if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  # endif
    {
      pFlexCANLocal->iflag3 = CANSFR_SET; /* clear pending Rx/Tx interrupts */ /* SBSW_CAN_LL01 */
    }
  #endif
  #if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    pFlexCANLocal->iflag4 = CANSFR_SET; /* clear pending Rx/Tx interrupts */ /* SBSW_CAN_LL01 */
  #endif
  
    pFlexCANLocal->estat = (vuint32)kFlexCAN_STATUS_INT; /* clear pending BusOff and error interrupts */ /* SBSW_CAN_LL01 */
  
    pFlexCANLocal->control1 &= (vuint32)(~kFlexCAN_BOFF_REC); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL01 */
  
    for(hwObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); hwObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); hwObjHandle++)
    {
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = kTxCodeInactive; /* set mailbox inactive */ /* SBSW_CAN_LL03 */
    }
  
  #if defined ( C_ENABLE_RX_FULLCAN_OBJECTS )
    for(hwObjHandle = CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel); hwObjHandle < CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel); hwObjHandle++) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) &= kRxCodeClear; /* clear control register and do not change the ID type */ /* SBSW_CAN_LL03 */
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) |= kRxCodeEmpty; /* set mailbox ready for receive */ /* SBSW_CAN_LL03 */
    }
  #endif
    
  #if defined ( C_ENABLE_RX_BASICCAN_OBJECTS )
  # if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
    for(hwObjHandle = CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel); hwObjHandle < CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel); hwObjHandle++)
    {
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) &= kRxCodeClear; /* clear control register and do not change the ID type */ /* SBSW_CAN_LL03 */
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) |= kRxCodeEmpty; /* set mailbox ready for receive */ /* SBSW_CAN_LL03 */
    }
  # else
    while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP)) /* COV_CAN_TESTSTIMULATION */
    {
      pFlexCANLocal->iflag1 = (vuint32)kRxFIFO_NEWMSG; /* clear RxFIFO pending interrupts */ /* SBSW_CAN_LL01 */
      fifoLoopCnt++;
    }
  # endif
  #endif
  }
}

/****************************************************************************
| NAME:             CanHL_InitPowerOn
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitPowerOn
Relation_Context:
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_InitPowerOn(void)
{
  /* #10 HW general power on initialization (LL) */
}

/****************************************************************************
| NAME:             CanHL_InitPowerOnChannelSpecific
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_InitPowerOnChannelSpecific
Relation_Context:
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_InitPowerOnChannelSpecific( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* #10 HW controller specific power on initialization (LL) */
  
  # if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  {
    uint8 errorId;
    errorId = CAN_E_NO_ERROR;
  /* Check for valid data array size in  tCanObject */
  #if defined ( C_ENABLE_CAN_FD_FULL )
    if ( sizeof( Can_GetRxMsgBufferOfControllerData(0).data ) < 64 ) /* PRQA S 3325 */ /* MD_Can_3325 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL01 */
  #else
    if ( sizeof( Can_GetRxMsgBufferOfControllerData(0).data ) < 8 ) /* PRQA S 3325 */ /* MD_Can_3325 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL01 */
  #endif
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      errorId = CAN_E_GENDATA;
    }
    if (kCanLoopEnterFreezeModeInit >= (vuint8)CAN_LOOP_MAX) /* PRQA S 3325 */ /* MD_Can_3325 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL02 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      errorId = CAN_E_GENDATA;
    }
  #if defined ( C_ENABLE_CAN_FD_FULL )
    if ( CANFD_MAILBOX_MAX_WORD_LENGTH(channel) > 16 ) /* PRQA S 3325 */ /* MD_Can_3325 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL12 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      errorId = CAN_E_GENDATA;
    }
  #endif
  
    if (errorId != CAN_E_NO_ERROR) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL09 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
  #  if (CAN_DEV_ERROR_REPORT == STD_ON)
      Can_CallDetReportError(CAN_INIT_ID, errorId);
  #  endif
      canConfigInitFlag = CAN_STATUS_UNINIT;
    }
  }
  # endif
  
  #if defined( C_ENABLE_UPDATE_BASE_ADDRESS ) /* COV_CAN_ENABLE_UPDATE_BASE_ADDRESS */
  # if defined (C_MULTIPLE_RECEIVE_CHANNEL)
  canLL_VirtualPtrField[channel]     = (vuint32*)ApplCanPowerOnGetBaseAddress((vuint32)(Can_GetBaseAddressOfControllerConfig(channel)), (sizeof(tFlexCAN)+0x3ff+sizeof(tCanRxMask)+0x64)); /* SBSW_CAN_LL05 */
  # else
  canLL_VirtualPtrField[0]     = (vuint32*)ApplCanPowerOnGetBaseAddress((vuint32)(Can_GetBaseAddressOfControllerConfig(0)), (sizeof(tFlexCAN)+0x3ff+sizeof(tCanRxMask)+0x64)); /* SBSW_CAN_LL05 */
  # endif
  #endif /* QWRAP / MDWRAP */
  
  
  

#if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
}

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_RxBasicMsgReceivedBegin
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxBasicMsgReceivedBegin
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxBasicMsgReceivedBegin( CanRxBasicInfoPtrType rxBasicInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL
  retval = CAN_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxBasicInfo->Controller; /* PRQA S 3199 */ /* MD_MSR_14.2 */
# endif
  rxObjHandle = rxBasicInfo->rxObjHandle; /* PRQA S 3199 */ /* MD_MSR_14.2 */

  /* #10 HW reception handling begin (LL) */
  {
  #if defined ( C_ENABLE_CAN_FD_FULL )
    vuint8 idx;
  #endif
  #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
    vuint8 loopResult = 1; /* PRQA S 3197 */ /* MD_Can_3197_LL */
  #endif
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
  
  
  #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  # if defined( C_ENABLE_PROTECTED_RX_PROCESS )
    CanNestedGlobalInterruptDisable();
  # endif
    Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, control); /* SBSW_CAN_LL05 */
    if ((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) /* COV_CAN_HARDWARE_PROCESSING_TIME */
    {
      APPLCANTIMERSTART(kCanLoopMsgReception); /* start hw loop timer */ /* SBSW_CAN_LL07 */
      do
      { /* Check busy state of receive object */
        Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, control); /* SBSW_CAN_LL05 */
        loopResult = APPLCANTIMERLOOP(kCanLoopMsgReception);
      }while(((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
      APPLCANTIMEREND(kCanLoopMsgReception); /* stop hw loop timer */ /* SBSW_CAN_LL07 */
    }
  #else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, control); /* SBSW_CAN_LL05 */
  #endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
        
    /* copy id and data to RAM buffer */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).msgID = LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, msgID); /* SBSW_CAN_LL05 */
  #if defined( C_CPUTYPE_LITTLEENDIAN ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  # if defined ( C_ENABLE_CAN_FD_FULL )
    for (idx=0; idx<CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel); idx++)
    {
      Can_GetRxMsgBufferOfControllerData(canHwChannel).data[idx] = CanBswap32(LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, data[idx])); /* PRQA S 0310,3689 */ /* MD_Can_0310,MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL05 */
    }
  # else
    Can_GetRxMsgBufferOfControllerData(canHwChannel).data[0] = CanBswap32(LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, data[0])); /* PRQA S 0310,3689 */ /* MD_Can_0310,MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL05 */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).data[1] = CanBswap32(LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, data[1])); /* PRQA S 0310,3689 */ /* MD_Can_0310,MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL05 */
  # endif
  #endif
  
  #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
    if (rxObjHandle < 32) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      pFlexCANLocal->iflag1 = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */
    }
  # if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    else 
    {
      if (rxObjHandle < 64) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        pFlexCANLocal->iflag2 = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */
      }
  #  if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
      else
      {
        if (rxObjHandle < 96) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          pFlexCANLocal->iflag3 = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */
        }
  #   if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
        else
        {
          pFlexCANLocal->iflag4 = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */
        }
  #   endif
      }
  #  endif
    }
  # endif
  
    /* to unlock only the current receive buffer the timestamp of another not-Rx message object must be read
     * reading the global timer results in a global unlock of all receive buffers */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).timestamp = LOCAL_MAILBOX_ACCESS(canHwChannel, CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel), timestamp); /* unlock current receive buffer */ /* SBSW_CAN_LL05 */
  
  # if defined( C_ENABLE_PROTECTED_RX_PROCESS )
    CanNestedGlobalInterruptRestore();
  # endif
  
  # if defined( C_ENABLE_HW_LOOP_TIMER )
    if(loopResult == 0) /* COV_CAN_TIMEOUT_DURATION */
    {    
      goto finishBasicCan; /* loop was aborted! don't process this message */ /* PRQA S 2001 */ /* MD_Can_2001 */
    }
  # endif
  #else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
    pFlexCANLocal->iflag1 = (vuint32)kRxFIFO_NEWMSG; /* clear RxFIFO pending interrupt flag after message is stored! */ /* SBSW_CAN_LL01 */
  #endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
  }

  /* #20 HW get mailbox pointer (LL) */
  (rxBasicInfo->rxInfo.pChipMsgObj) = (CanChipMsgPtr) &(Can_GetRxMsgBufferOfControllerData(canHwChannel).control); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_HL29 */

  /* #30 HW get data pointer (LL) */
  (rxBasicInfo->rxInfo.pChipData) = (CanChipDataPtr) &(Can_GetRxMsgBufferOfControllerData(canHwChannel).data[0]); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_HL29 */

  retval = CAN_OK;
/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
  goto finishBasicCan;     /* to avoid compiler warning */ /* PRQA S 2001 */ /* MD_Can_2001 */
finishBasicCan:
  return retval;
} /* PRQA S 6030 */ /* MD_MSR_STCYC*/

/****************************************************************************
| NAME:             CanHL_RxBasicMsgReceivedSearch
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxBasicMsgReceivedSearch
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxBasicMsgReceivedSearch( CanRxBasicInfoPtrType rxBasicInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL
  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxBasicInfo->Controller;
# endif
  rxObjHandle = rxBasicInfo->rxObjHandle;
  /* #20 HRH calculate (multiple BasicCAN) */
  rxBasicInfo->rxInfo.localHrh = (Can_HwHandleType)((Can_HwHandleType)rxObjHandle - CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)); /* calculate 0 based BasicCAN index */ /* SBSW_CAN_HL29 */
  rxBasicInfo->rxInfo.localHrh = (Can_HwHandleType)(rxBasicInfo->rxInfo.localHrh / (Can_GetDLC_FIFO(Can_GetRxBasicHandleStart(canHwChannel)))); /* get BasicCAN for this FIFO */ /* SBSW_CAN_HL29 */
  rxBasicInfo->rxInfo.localHrh = (Can_HwHandleType)(rxBasicInfo->rxInfo.localHrh + Can_GetRxBasicHandleStart(canHwChannel)); /* get mailbox index for this BasicCAN */ /* SBSW_CAN_HL29 */
  retval = CAN_OK;
  return retval;
}

/****************************************************************************
| NAME:             CanHL_RxBasicMsgReceivedEnd
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxBasicMsgReceivedEnd
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicMsgReceivedEnd( CanRxBasicInfoPtrType rxBasicInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxBasicInfo->Controller; /* PRQA S 3199 */ /* MD_MSR_14.2 */
# endif
  rxObjHandle = rxBasicInfo->rxObjHandle; /* PRQA S 3199 */ /* MD_MSR_14.2 */

  /* #10 HW release mailbox (LL) */


  CAN_DUMMY_STATEMENT(rxObjHandle);  /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller);   /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}

# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_RxBasicMsgReceivePolling
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxBasicMsgReceivePolling
Relation_Context:
RxBasicCANSupport, RxPolling
Relation:
CommonCan
IndividualPolling
OneChOpt
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicMsgReceivePolling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  vuint32 iFlags;
  #else
  vuint8 fifoLoopCnt = 0;
  #endif
  tFlexCANPtr pFlexCANLocal; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  pFlexCANLocal = pFlexCAN(canHwChannel);
  #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  iFlags = pFlexCANLocal->iflag1 & CAN_RXBASIC_POLL_MASK1(canHwChannel);
  # if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  iFlags |= pFlexCANLocal->iflag2 & CAN_RXBASIC_POLL_MASK2(canHwChannel);
  # endif
  # if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  #  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  #  endif
  {
    iFlags |= pFlexCANLocal->iflag3 & CAN_RXBASIC_POLL_MASK3(canHwChannel);
  }
  # endif
  # if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  iFlags |= pFlexCANLocal->iflag4 & CAN_RXBASIC_POLL_MASK4(canHwChannel);
  # endif
  if(iFlags != 0)
  {
  #else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
  if ((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
  #endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
    /* #20 loop over all BasicCAN mailboxes */
    {
      Can_HwHandleType hwObjStart;
      Can_HwHandleType hwObjStop;
      hwObjStart = (Can_HwHandleType)CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel);
      hwObjStop  = (Can_HwHandleType)CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel);
      for (rxObjHandle = hwObjStart; rxObjHandle < hwObjStop; rxObjHandle++)
      { /* over all BasicCAN mailboxes (include FIFO/Shadow) */
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) || defined(CAN_HWOBJINDIVPOLLING) /* COV_CAN_HWOBJINDIVPOLLING */
        /* #30 check individual polling flag */
        if ( Can_GetCanHwObjIndivPolling(CAN_HWOBJINDIVPOLLING_INDEX0,rxObjHandle) != (uint8)0 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
        { 
          /* #40 check mailbox pending flag */
          #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
          if (rxObjHandle < 32) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          {
            iFlags = pFlexCANLocal->iflag1;
          }
          # if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
          else 
          {
            if (rxObjHandle < 64) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
            {
              iFlags = pFlexCANLocal->iflag2;
            }
          #  if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
            else
            {
              if (rxObjHandle < 96) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
              {
                iFlags = pFlexCANLocal->iflag3;
              }
          #   if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
              else
              {
                iFlags = pFlexCANLocal->iflag4;
              }
          #   endif
            }
          #  endif
          }
          # endif
                      
          if((iFlags & CanBitMask(rxObjHandle)) != 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          {
          #else /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
          while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP)) /* COV_CAN_TESTSTIMULATION */
          {
            fifoLoopCnt++;
          #endif /* C_ENABLE_CLASSIC_MAILBOX_LAYOUT */
            /* #50 disable CAN interrupts \trace SPEC-1569, SPEC-3785 */
            Can_DisableControllerInterrupts((uint8)channel);
            /* #60 mailbox notification CanBasicCanMsgReceived() */
            CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
            /* #70 enable CAN interrupts */
            Can_EnableControllerInterrupts((uint8)channel);
          }
        }
      }
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_RxFullMsgReceivedBegin
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxFullMsgReceivedBegin
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxFullMsgReceivedBegin( CanRxFullInfoPtrType rxFullInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL
  retval = CAN_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxFullInfo->Controller;
# endif
  rxObjHandle = rxFullInfo->rxObjHandle;

  /* #10 HW reception handling begin (LL) */
  {
  #if defined ( C_ENABLE_CAN_FD_FULL )
    vuint8 idx;
  #endif
    vuint8 loopResult = 1; /* PRQA S 3197 */ /* MD_Can_3197_LL */
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
  
  #if defined( C_ENABLE_PROTECTED_RX_PROCESS )
    CanNestedGlobalInterruptDisable();
  #endif
  
    Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, control); /* SBSW_CAN_LL05 */
    if ((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) /* COV_CAN_HARDWARE_PROCESSING_TIME */
    {
      APPLCANTIMERSTART(kCanLoopMsgReception); /* start hw loop timer */ /* SBSW_CAN_LL07 */
      do
      { /* Check busy state of receive object */
        Can_GetRxMsgBufferOfControllerData(canHwChannel).control = LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, control); /* SBSW_CAN_LL05 */
        loopResult = APPLCANTIMERLOOP(kCanLoopMsgReception);
      }while(((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kRxCodeBusy) == kRxCodeBusy) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */ /* COV_CAN_TIMEOUT_DURATION */
      APPLCANTIMEREND(kCanLoopMsgReception); /* stop hw loop timer */ /* SBSW_CAN_LL07 */
    }
  
    if (rxObjHandle < 32) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      pFlexCANLocal->iflag1 = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */
    }
  #if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    else 
    {
      if (rxObjHandle < 64) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        pFlexCANLocal->iflag2 = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */
      }
  # if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
      else
      {
        if (rxObjHandle < 96) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          pFlexCANLocal->iflag3 = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */
        }
  #  if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
        else
        {
          pFlexCANLocal->iflag4 = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL01 */
        }
  #  endif
      }
  # endif
    }
  #endif
  
    /* copy id and data to RAM buffer */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).msgID = LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, msgID); /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL05 */
  #if defined( C_CPUTYPE_LITTLEENDIAN ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  # if defined ( C_ENABLE_CAN_FD_FULL )
    for (idx=0; idx<CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel); idx++)
    {
      Can_GetRxMsgBufferOfControllerData(canHwChannel).data[idx] = CanBswap32(LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, data[idx])); /* PRQA S 0310,3689 */ /* MD_Can_0310,MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL05 */
    }
  # else
    Can_GetRxMsgBufferOfControllerData(canHwChannel).data[0] = CanBswap32(LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, data[0])); /* PRQA S 0310,3689 */ /* MD_Can_0310,MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL05 */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).data[1] = CanBswap32(LOCAL_MAILBOX_ACCESS(canHwChannel, rxObjHandle, data[1])); /* PRQA S 0310,3689 */ /* MD_Can_0310,MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL05 */
  # endif
  #endif
    /* to unlock only the current receive buffer the timestamp of another not-Rx message object must be read
     * reading the global timer results in a global unlock of all receive buffers */
    Can_GetRxMsgBufferOfControllerData(canHwChannel).timestamp = LOCAL_MAILBOX_ACCESS(canHwChannel, CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel), timestamp); /* unlock current receive buffer */ /* SBSW_CAN_LL05 */
  
  #if defined( C_ENABLE_PROTECTED_RX_PROCESS )
    CanNestedGlobalInterruptRestore();
  #endif
  
  #if defined( C_ENABLE_HW_LOOP_TIMER )
    if(loopResult == 0) /* COV_CAN_TIMEOUT_DURATION */
    {    
      goto finishRxFullCan; /* loop was aborted! don't process this message */ /* PRQA S 2001 */ /* MD_Can_2001 */
    }
  #endif
  }
  
  /* #20 HW get mailbox pointer (LL) */
  (rxFullInfo->rxInfo.pChipMsgObj) = (CanChipMsgPtr) &(Can_GetRxMsgBufferOfControllerData(canHwChannel).control); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_HL30 */

  /* #30 HW get data pointer (LL) */
  (rxFullInfo->rxInfo.pChipData) = (CanChipDataPtr) &(Can_GetRxMsgBufferOfControllerData(canHwChannel).data[0]); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_HL30 */

  retval = CAN_OK;
/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
  goto finishRxFullCan;     /* to avoid compiler warning */ /* PRQA S 2001 */ /* MD_Can_2001 */
finishRxFullCan:
  return retval;
}

/****************************************************************************
| NAME:             CanHL_RxFullMsgReceivedSearch
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxFullMsgReceivedSearch
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_RxFullMsgReceivedSearch( CanRxFullInfoPtrType rxFullInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxFullInfo->channel;
# endif
  rxObjHandle = rxFullInfo->rxObjHandle;

  /* #20 HRH calculate */
  rxFullInfo->rxInfo.localHrh = (Can_HwHandleType)((Can_HwHandleType)((Can_HwHandleType)rxObjHandle - CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)) + Can_GetRxFullHandleStart(canHwChannel)); /* SBSW_CAN_HL30 */

  retval = CAN_OK;
  return retval;
}

/****************************************************************************
| NAME:             CanHL_RxFullMsgReceivedEnd
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxFullMsgReceivedEnd
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullMsgReceivedEnd( CanRxFullInfoPtrType rxFullInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  CAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  Controller = rxFullInfo->channel;
# endif
  rxObjHandle = rxFullInfo->rxObjHandle;

  /* #10 HW release mailbox (LL) */


  CAN_DUMMY_STATEMENT(rxObjHandle);  /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller);   /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}

# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_RxFullMsgReceivePolling
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxFullMsgReceivedEnd
Relation_Context:
RxFullCANSupport, RxPolling
Relation:
CommonCan
IndividualPolling
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullMsgReceivePolling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_HwHandleType Htrh;
  CanObjectHandle rxObjHandle; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  vuint32 iFlags;
  tFlexCANPtr pFlexCANLocal; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  pFlexCANLocal = pFlexCAN(canHwChannel);
  iFlags = pFlexCANLocal->iflag1 & CAN_RXFULL_POLL_MASK1(canHwChannel);
  #if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  iFlags |= pFlexCANLocal->iflag2 & CAN_RXFULL_POLL_MASK2(canHwChannel);
  #endif
  #if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  # if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  # endif
  {
    iFlags |= pFlexCANLocal->iflag3 & CAN_RXFULL_POLL_MASK3(canHwChannel);
  }
  #endif
  #if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  iFlags |= pFlexCANLocal->iflag4 & CAN_RXFULL_POLL_MASK4(canHwChannel);
  #endif
  
  if(iFlags != 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    /* #20 loop over all FullCAN mailboxes */
    for (Htrh = Can_GetRxFullHandleStart(canHwChannel); Htrh < Can_GetRxFullHandleStop(canHwChannel); Htrh++ ) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      rxObjHandle = Can_GetHwHandle(Htrh);
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) || defined(CAN_HWOBJINDIVPOLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      /* #30 check individual polling flag */
      if ( Can_GetCanHwObjIndivPolling(CAN_HWOBJINDIVPOLLING_INDEX0,rxObjHandle) != (uint8)0 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      { /* #40 check mailbox pending flag */
        if (rxObjHandle < 32) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          iFlags = pFlexCANLocal->iflag1;
        }
        #if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
        else 
        {
          if (rxObjHandle < 64) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          {
            iFlags = pFlexCANLocal->iflag2;
          }
        # if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
          else
          {
            if (rxObjHandle < 96) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
            {
              iFlags = pFlexCANLocal->iflag3;
            }
        #  if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
            else
            {
              iFlags = pFlexCANLocal->iflag4;
            }
        #  endif
          }
        # endif
        }
        #endif
                   
        if((iFlags & CanBitMask(rxObjHandle)) != 0) /* COV_CAN_MAILBOX_ORDER */
        {
          /* #50 disable CAN Interrupt \trace SPEC-1569, SPEC-3785 */
          Can_DisableControllerInterrupts((uint8)channel);
          /* #60 mailbox notification CanFullCanMsgReceived() */
          CanFullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
          /* #70 enable CAN Interrupt */
          Can_EnableControllerInterrupts((uint8)channel);
        }
      }
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* C_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_RxMsgReceivedNotification
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxMsgReceivedNotification
Relation_Context:
RxFullCANSupport, RxBasicCANSupport
Relation:
RxQueue, DevErrorDetect
RxQueue, CanFdSupport
RxQueue, GenericPreCopy, MirrorMode
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxMsgReceivedNotification( CAN_CHANNEL_CANTYPE_FIRST CanRxInfoPtrType rxInfo ) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
# if !defined(C_ENABLE_RX_QUEUE) && (CAN_GENERIC_PRECOPY == STD_ON)
  Can_ReturnType generic_retval;
# endif
  uint8 errorId;
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 RX queue */
# if defined(C_ENABLE_RX_QUEUE)
  /**************************** RxQueue handling **********************************/
    /* #20 EXCLUSIVE_AREA_4 secure RxQueue data handling */
  Can_EnterCritical(CAN_EXCLUSIVE_AREA_4);
  if (Can_GetRxQueueInfo().Count < Can_GetSizeOfRxQueueBuffer()) /* COV_CAN_GENDATA_FAILURE */
  { /* #30 Queue not full: */
    /* #45 copy HRH, ID, DLC and data to RX queue */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).Hrh = rxInfo->localHrh; /* SBSW_CAN_HL18 */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).id  = rxInfo->localId; /* SBSW_CAN_HL18 */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).dlc = rxInfo->localDlc; /* SBSW_CAN_HL18 */

#  if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (canRxQueueMaxDataSize < rxInfo->localDlc) /* CM_CAN_HL17 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_DLC;
    }
    else
#  endif
    {

#  if defined(C_ENABLE_CAN_FD_FULL)
      /* #46 copy data with VStdLib optimized copy routine for CAN-FD messages (use alignment info) */
      VStdMemCpy((void*)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).data, (void*)rxInfo->pChipData, rxInfo->localDlc); /* SBSW_CAN_HL19 */ /* PRQA S 0312 */ /* MD_Can_0312 */
#  else
      {
        uint8_least i;
        for (i = 0; i < rxInfo->localDlc; i++)
        {
          Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).data[i] = CanRxActualData(rxInfo,i); /* SBSW_CAN_HL19 */
        }
      }
#  endif
    }
      /* #47 increase pointer to next queue element */
    Can_GetRxQueueInfo().Count++;
    if (Can_GetRxQueueInfo().WriteIndex < (uint16)(Can_GetSizeOfRxQueueBuffer() - 1) ) /* CM_CAN_HL24 */
    {
      Can_GetRxQueueInfo().WriteIndex++;
    }
    else
    {
      Can_GetRxQueueInfo().WriteIndex = 0; /* CM_CAN_HL24 */
    }
  }
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  else 
  { /* #50 Queue full: last message will be lost -> overrun in queue do not change ReadIndex to override latest message because inconsistency problem (currently reading queue) */
    errorId = CAN_E_RXQUEUE;
  }
#  endif
  Can_LeaveCritical(CAN_EXCLUSIVE_AREA_4);
# else /* C_ENABLE_RX_QUEUE */
  /* #100 no RX queue */
  /* -------------------------- Interface + APPL Notifications --- */
    /* #110 call Appl_GenericPrecopy() depend on configuration and if mirror mode is active */
#  if (CAN_GENERIC_PRECOPY == STD_ON)
#   if defined(C_ENABLE_MIRROR_MODE)
  if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
  { /* do not call Appl_GenericPrecopy() in case mirror mode was disabled */
    generic_retval = CAN_OK;
  }
  else
#   endif
  { /* \trace SPEC-3960 */
    generic_retval = Appl_GenericPrecopy((uint8)channel, (rxInfo->localId & CAN_ID_MASK_IN_GENERIC_CALLOUT), rxInfo->localDlc, (Can_DataPtrType)rxInfo->pChipData);  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL06 */
  }
  if (generic_retval == CAN_OK) /* \trace SPEC-15119 */
#  endif
  { /* #120 call CanIf_RxIndication() if mirror mode is no active or Appl_GenericPrecopy() return OK \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
    CanIf_RxIndication(rxInfo->localHrh, rxInfo->localId, rxInfo->localDlc, (Can_DataPtrType)rxInfo->pChipData); /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL07 */
  }
# endif
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return errorId;
}
#endif

#if defined(C_ENABLE_RX_QUEUE)
/****************************************************************************
| NAME:             CanHL_RxQueueExecution
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_RxQueueExecution
Relation_Context:
RxQueue
Relation:
GenericPreCopy, OneChOpt, CommonCan
GenericPreCopy, OneChOpt, DevErrorDetect
GenericPreCopy, MirrorMode
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxQueueExecution( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Execute RxQueue (over all channels) */
  while ( Can_GetRxQueueInfo().Count != (uint16)0 )
  { /* #20 over all filled RxQueue elements */
# if (CAN_GENERIC_PRECOPY == STD_ON)
    Can_ReturnType generic_retval;
    CAN_CHANNEL_CANTYPE_LOCAL
    generic_retval = CAN_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).Hrh);
#   if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #30 Check controller is valid */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#   endif
#  endif
#  if defined(C_ENABLE_MIRROR_MODE)
    if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
    { /* #40 MirrorMode: only when mirror is activated for this controller */
      generic_retval = CAN_OK;
    }
    else
#  endif
    { /* #50 call Appl_GenericPrecopy() */
      generic_retval = Appl_GenericPrecopy( (uint8)channel, /* PRQA S 2004 */ /* MD_Can_Asr_2004 */
                (Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).id & CAN_ID_MASK_IN_GENERIC_CALLOUT),
                Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).dlc,
                (Can_DataPtrType)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).data );  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL06 */
    }
    if (generic_retval == CAN_OK)
# endif
    { /* #60 call CanIf_RxIndication() if Appl_GenericPrecopy() return OK or no generic precopy is used \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
      CanIf_RxIndication( Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).Hrh, /* SBSW_CAN_HL07 */
              Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).id,
              Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).dlc,
              (Can_DataPtrType)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).data ); /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL07 */
    }
    /* #70 EXCLUSIVE_AREA_4 secure RxQueue handling */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_4);
    /* #80 get next RxQueue element pointer */
    if (Can_GetRxQueueInfo().ReadIndex >= (uint16)(Can_GetSizeOfRxQueueBuffer() - 1) ) /* CM_CAN_HL25 */
    {
      Can_GetRxQueueInfo().ReadIndex = 0; /* CM_CAN_HL25 */
    }
    else
    {
      Can_GetRxQueueInfo().ReadIndex++;
    }
    Can_GetRxQueueInfo().Count--;
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_4);
  }
  return errorId;
}
#endif

#if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/****************************************************************************
| NAME:             CanHL_TxTaskConfPendingHandling
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_TxTaskConfPendingHandling
Relation_Context:
TxPolling
Relation:
CommonCan
IndividualPolling
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_TxTaskConfPendingHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  CanObjectHandle txObjHandle;
  vuint32     iFlags;
  tFlexCANPtr pFlexCANLocal; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  pFlexCANLocal = pFlexCAN(canHwChannel);
  
  iFlags = pFlexCANLocal->iflag1 & CAN_TX_POLL_MASK1(canHwChannel);
  #if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  iFlags |= pFlexCANLocal->iflag2 & CAN_TX_POLL_MASK2(canHwChannel);
  #endif
  #if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  # if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
  # endif
  {
    iFlags |= pFlexCANLocal->iflag3 & CAN_TX_POLL_MASK3(canHwChannel);
  }
  #endif
  #if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  iFlags |= pFlexCANLocal->iflag4 & CAN_TX_POLL_MASK4(canHwChannel);
  #endif
  
  if(iFlags != 0)
  {
    for ( txObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); txObjHandle++ )
    { /* #10 over all TX mailboxes */
# if defined(C_ENABLE_INDIVIDUAL_POLLING) || defined(CAN_HWOBJINDIVPOLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      if ( Can_GetCanHwObjIndivPolling(CAN_HWOBJINDIVPOLLING_INDEX0,txObjHandle) != (uint8)0 ) /* COV_CAN_HWOBJINDIVPOLLING */
# endif
      { /* #20 polling object? do individual polling */
        if (txObjHandle < 32) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          iFlags = pFlexCANLocal->iflag1;
        }
        #if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
        else 
        {
          if (txObjHandle < 64) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          {
            iFlags = pFlexCANLocal->iflag2;
          }
        # if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
          else
          {
            if (txObjHandle < 96) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
            {
              iFlags = pFlexCANLocal->iflag3;
            }
        #  if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
            else
            {
              iFlags = pFlexCANLocal->iflag4;
            }
        #  endif
          }
        # endif
        }
        #endif
        
        if( ((iFlags & CanBitMask(txObjHandle)) != 0)
        ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          /* #25 Lock CAN controller interrupts. (avoid nested call of confirmation (individual polling) and CancelTx interrupt confirmation out of Can interrupt like TP) */
          Can_DisableControllerInterrupts((uint8)channel);
          /* #30 confirmation pending - do handling \trace SPEC-1574, SPEC-3779 */
          CanHL_TxConfirmation( CAN_HW_CHANNEL_CANPARA_FIRST txObjHandle );
          Can_EnableControllerInterrupts((uint8)channel);
        }
      }
    }
  }
}
#endif

#if defined(C_ENABLE_CANCEL_TX_IN_HW) 
#endif

# if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanResetBusOffEnd
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanResetBusOffEnd(CAN_CHANNEL_CANTYPE_FIRST uint8 initObject)
{
  /* #10 Set busoff state to TRUE */
  Can_SetIsBusOff(channel, TRUE); /* SBSW_CAN_HL08 */
  CAN_DUMMY_STATEMENT(initObject); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
}
/* CODE CATEGORY 4 END */
# endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
/* CODE CATEGORY 2 START */
/****************************************************************************
| NAME:             CanLL_CanInterruptDisable
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CanChannelHandle canHwCh, tCanIntOldPtr localInterruptOldFlagPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  tFlexCANPtr pFlexcan = pFlexCAN(canHwCh); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Disable RxTx interrupts */
  CAN_DISABLE_RXTX_INTERRUPT_0TO31(localInterruptOldFlagPtr); /* SBSW_CAN_LL06 */ /* SBSW_CAN_LL01 */
  CAN_DISABLE_RXTX_INTERRUPT_32TO63(localInterruptOldFlagPtr); /* SBSW_CAN_LL06 */ /* SBSW_CAN_LL01 */
#if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwCh) > 64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#endif
  {
    CAN_DISABLE_RXTX_INTERRUPT_64TO95(localInterruptOldFlagPtr); /* SBSW_CAN_LL06 */ /* SBSW_CAN_LL01 */
  }
  CAN_DISABLE_RXTX_INTERRUPT_96TO127(localInterruptOldFlagPtr); /* SBSW_CAN_LL06 */ /* SBSW_CAN_LL01 */
  
  /* #20 Disable BusOff interrupts */
  CAN_DISABLE_BUSOFF_INTERRUPT(localInterruptOldFlagPtr); /* SBSW_CAN_LL06 */ /* SBSW_CAN_LL01 */
  
  /* #30 Disable WakeUp interrupts */
  CAN_DISABLE_WAKEUP_INTERRUPT(localInterruptOldFlagPtr); /* SBSW_CAN_LL06 */ /* SBSW_CAN_LL01 */

#if defined ( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(canHwCh); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
#endif

}
/* CODE CATEGORY 2 END */

/* CODE CATEGORY 2 START */
/****************************************************************************
| NAME:             CanLL_CanInterruptRestore
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CanChannelHandle canHwCh, tCanLLCanIntOld localInterruptOldFlag)
{
  /* ----- Local Variables ---------------------------------------------- */
  tFlexCANPtr pFlexcan = pFlexCAN(canHwCh); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Restore RxTx interrupts */
  CAN_RESTORE_RXTX_INTERRUPT_0TO31(localInterruptOldFlag); /* SBSW_CAN_LL01 */
  CAN_RESTORE_RXTX_INTERRUPT_32TO63(localInterruptOldFlag); /* SBSW_CAN_LL01 */
#if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwCh) > 64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#endif
  {
    CAN_RESTORE_RXTX_INTERRUPT_64TO95(localInterruptOldFlag); /* SBSW_CAN_LL01 */
  }
  CAN_RESTORE_RXTX_INTERRUPT_96TO127(localInterruptOldFlag); /* SBSW_CAN_LL01 */
  
  /* #20 Restore BusOff interrupts */
  CAN_RESTORE_BUSOFF_INTERRUPT(localInterruptOldFlag); /* SBSW_CAN_LL01 */
  
  /* #30 Restore WakeUp interrupts */
  CAN_RESTORE_WAKEUP_INTERRUPT(localInterruptOldFlag); /* SBSW_CAN_LL01 */

#if defined ( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(canHwCh); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
#endif
}
/* CODE CATEGORY 2 END */
#endif

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_SetFlexCANToInitMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_SetFlexCANToInitMode(CAN_HW_CHANNEL_CANTYPE_FIRST CanInitHandle initObj)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 loopResult = 1; /* PRQA S 3197,781 */ /* MD_Can_3197_LL,MD_Can_Asr_0781 */
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
  
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if FlexCAN is DISABLED or in a NON_BUSOFF state (and in NON_LOM mode) */
  if (((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_DISABLE_MODE) == kFlexCAN_DISABLE_MODE)
    || (((CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->estat) & kFlexCAN_FCS_BOFF) == 0)
#if defined(C_ENABLE_SILENT_MODE)
    && ((CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->control1) & kFlexCAN_LOM) == 0)
#endif
  )) /* SBSW_CAN_LL01 */ /* SBSW_CAN_LL01 */ /* SBSW_CAN_LL01 */ /* COV_CAN_TESTSTIMULATION */
  {
    /* #20 Check if FlexCAN is ENABLED */
    if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_DISABLE_ONLY_BITS) == 0) /* SBSW_CAN_LL01 */ /* COV_CAN_TESTSTIMULATION */
    {
      /* #30 Enter FREEZE mode (INIT mode) of FlexCAN */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_FRZ); /* SBSW_CAN_LL01 */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* SBSW_CAN_LL01 */
      if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
      {
        APPLCANTIMERSTART(kCanLoopEnterFreezeModeInit); /* start hw loop timer */ /* SBSW_CAN_LL07 */
        do  
        { /* wait for FRZACK */  
          loopResult = APPLCANTIMERLOOP(kCanLoopEnterFreezeModeInit);  
        }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */ /* SBSW_CAN_LL01 */ /* COV_CAN_TIMEOUT_DURATION */
        APPLCANTIMEREND(kCanLoopEnterFreezeModeInit); /* stop hw loop timer */ /* SBSW_CAN_LL07 */
      }
      
      /* #40 Enter DISABLE mode of FlexCAN for clock selection */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* disable FlexCAN module before clock selection */ /* SBSW_CAN_LL01 */
      if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
      {
        APPLCANTIMERSTART(kCanLoopEnterDisableMode); /* start hw loop timer */ /* SBSW_CAN_LL07 */
        do{
          /* wait for FlexCAN is disabled */
          loopResult = APPLCANTIMERLOOP(kCanLoopEnterDisableMode);
        }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */ /* SBSW_CAN_LL01 */ /* COV_CAN_TIMEOUT_DURATION */
        APPLCANTIMEREND(kCanLoopEnterDisableMode);  /* stop hw loop timer */ /* SBSW_CAN_LL07 */
      }
    }
    
    /* #50 Set FlexCAN clock source */
    if((Can_GetControl1OfInitObject(initObj) & kFlexCAN_CLK_SRC) != 0) /* COV_CAN_TESTSTIMULATION */
    {
      CAN_WRITE_PROTECTED_REG_SET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* SBSW_CAN_LL01 */
    }
    else
    {
      CAN_WRITE_PROTECTED_REG_RESET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL01 */
    }

    /* #60 Leave DISABLE mode of FlexCAN */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
    if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
    {
      APPLCANTIMERSTART(kCanLoopLeaveDisableMode); /* start hw loop timer */ /* SBSW_CAN_LL07 */
      do{
        /* wait for FlexCAN is enabled */
        loopResult = APPLCANTIMERLOOP(kCanLoopLeaveDisableMode);
      }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */ /* SBSW_CAN_LL01 */ /* COV_CAN_TIMEOUT_DURATION */
      APPLCANTIMEREND(kCanLoopLeaveDisableMode);  /* stop hw loop timer */ /* SBSW_CAN_LL07 */
    }
  }

#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
  if (loopResult == 0) /* COV_CAN_TIMEOUT_DURATION */
  {
    Can_SetIsHardwareCanceled(channel, TRUE); /* ESCAN00072515: Can_SetControllerMode(controller, CAN_T_STOP) returns CAN_OK instead of CAN_NOT_OK */ /* SBSW_CAN_HL14 */
  }
#endif
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_ExecuteSoftReset
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ExecuteSoftReset(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 loopResult = 1; /* PRQA S 3197,781 */ /* MD_Can_3197_LL,MD_Can_Asr_0781 */
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
  
  /* ----- Implementation ----------------------------------------------- */     
  /* *********************************************************************** */
  /* Perform FlexCAN soft reset.                                             */
  /* Please note: the soft reset cannot be applied while clocks are          */
  /* shut down: low power mode or clocks are not enabled.                    */
  /* Please check clock settings if soft reset cannot be finalized.          */
  /* *********************************************************************** */
  /* #10 Execute SoftReset of FlexCAN */
  CAN_WRITE_PROTECTED_REG(pFlexCANLocal->canmcr, kFlexCAN_SOFT_RST); /* SBSW_CAN_LL01 */
  if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_SOFT_RST) == kFlexCAN_SOFT_RST) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
  {
    /* wait for soft reset confirmation from hardware */
    APPLCANTIMERSTART(kCanLoopInit); /* start hw loop timer */ /* SBSW_CAN_LL07 */
    do
    { /* wait for SOFT_RST */
      loopResult = APPLCANTIMERLOOP(kCanLoopInit);
    }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_SOFT_RST) == kFlexCAN_SOFT_RST) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */ /* SBSW_CAN_LL01 */ /* COV_CAN_TIMEOUT_DURATION */
    APPLCANTIMEREND(kCanLoopInit);  /* stop hw loop timer */ /* SBSW_CAN_LL07 */
  }

#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
  if (loopResult == 0) /* COV_CAN_TIMEOUT_DURATION */
  {
    /* #20 Set global flag if hardware loop was cancelled */
    Can_SetIsHardwareCanceled(channel, TRUE); /* ESCAN00072515: Can_SetControllerMode(controller, CAN_T_STOP) returns CAN_OK instead of CAN_NOT_OK */ /* SBSW_CAN_HL14 */
  }
#endif

  /* #30 Reset SUPV bit to grant access to CAN register (except MCR register) in User Mode */
  /* set all CAN register except the MCR register in unrestricted memory space directly after soft reset */
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_SUPV); /* SBSW_CAN_LL01 */
}
/* CODE CATEGORY 4 END */
#if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_HandleBusOff
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_HandleBusOff(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call CanInit and set BusOff flag to FALSE if BusOff recovery was successful */
  if (!(CanLL_HwIsBusOff(channel)))
  {
    Can_SetIsBusOff(channel,FALSE); /* SBSW_CAN_HL08 */
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
    CanInit(channel, Can_GetLastInitObject(channel)); /* SBSW_CAN_HL18 */
#   else
    CanInit(Can_GetLastInitObject(channel)); /* SBSW_CAN_HL18 */
# endif
  }
}

/****************************************************************************
| NAME:             CanLL_HandleStartProcess
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanLL_HandleStartProcess(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType result = kCanFailed;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
  
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if START mode was not yet requested */
  if (!Can_IsStartModeRequestedOfControllerData(canHwChannel))
  {
#if defined(C_ENABLE_SILENT_MODE)
    /* set listen only mode if silent mode is requested*/
    if (Can_GetSilentModeState(channel) == CAN_SILENT_ACTIVE)
    {
      pFlexCANLocal->control1 |= kFlexCAN_LOM; /* SBSW_CAN_LL01 */
    }
    else
    {
      pFlexCANLocal->control1 &= (vuint32)(~kFlexCAN_LOM); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL01 */
    }
#endif
    /* #20 Request START mode */
    /* request NORMAL mode - considered as CanStart mode */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */ /* SBSW_CAN_LL01 */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit  */ /* SBSW_CAN_LL01 */

    /* the transition CanStop - CanStart does also leave a potential BusOff state */
    pFlexCANLocal->control1 |= kFlexCAN_BOFF_REC; /* SBSW_CAN_LL01 */

    Can_SetStartModeRequestedOfControllerData(canHwChannel, TRUE); /* SBSW_CAN_LL02 */
  }
  else
  {
    /* #30 Set result to OK if START mode was reached successfully */
    /* check if NORMAL mode is reached - considered as CanStart mode */
    if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) == kFlexCAN_NORMAL_MODE) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
    {
      result = kCanOk;
      Can_SetStartModeRequestedOfControllerData(canHwChannel, FALSE); /* SBSW_CAN_LL02 */
    }
  }
    
  return result;
}
/* CODE CATEGORY 4 END */
#endif

# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
/****************************************************************************
| NAME:             Can_CheckMaxHwMailboxHandle
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 4 START*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) Can_CheckMaxHwMailboxHandle(CanChannelHandle hwChannel, Can_HwHandleType hwObjHandle) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  uint8 errorId = CAN_E_NO_ERROR;

  /* #10 Check for maximum value of HW mailbox handle */
#  if defined ( C_ENABLE_CAN_FD_FULL )
  if ( Can_GetSizeOfFDMailboxMapping() <= (Can_GetFDHwChannelIndirectionOfControllerConfig((hwChannel)) + hwObjHandle) ) /* PRQA S 3325 */ /* MD_Can_3325 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    errorId = CAN_E_GENDATA;
  }
  CAN_DUMMY_STATEMENT(hwChannel); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
#  else
#   if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  if ( hwObjHandle >= 128 ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#   elif defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
#    if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (hwObjHandle >= NUMBER_OF_MAX_MAILBOXES(hwChannel)) /* PRQA S 3325 */ /* MD_Can_3325 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#    else
  if ( hwObjHandle >= 96 ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#    endif
#   elif defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  if ( hwObjHandle >= 64 ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#   else
#    if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (hwObjHandle >= NUMBER_OF_MAX_MAILBOXES(hwChannel)) /* PRQA S 3325 */ /* MD_Can_3325 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#    else
  if ( hwObjHandle >= 32 ) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
#    endif
#   endif
  {
    errorId = CAN_E_GENDATA;
  }
#   if !defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  CAN_DUMMY_STATEMENT(hwChannel); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
#   endif
#  endif

#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  /* #20 Throw a DET */
  if (errorId != CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */
  {
    Can_CallDetReportError( CAN_INIT_ID, errorId );
  }
#  endif
  return ( errorId );
}
/* CODE CATEGORY 4 END*/
# endif

# if defined ( V_CPU_S32 ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
#  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#   if defined ( C_ENABLE_CAN_FD_FULL )
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
  /* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  Can_CheckMaxHwFDMailboxHandle()
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) Can_CheckMaxHwFDMailboxHandle(CAN_HW_CHANNEL_CANTYPE_FIRST Can_HwHandleType hwObjHandle)
{
  uint8 errorId = CAN_E_NO_ERROR;

  /* #10 Check for maximum value of HW mailbox handle */
  if ( Can_GetSizeOfFDMailboxMapping() <= (Can_GetFDHwChannelIndirectionOfControllerConfig((canHwChannel)) + hwObjHandle) ) /* PRQA S 3325 */ /* MD_Can_3325 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    /* #20 Throw a DET */
    errorId = CAN_E_GENDATA;
#     if (CAN_DEV_ERROR_REPORT == STD_ON)
    Can_CallDetReportError( CAN_CHECK_DS_ID, errorId );
#     endif
  }

  return ( errorId );
}
/* CODE CATEGORY 4 END */
#    endif
#   endif
#  endif
# endif

# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
      defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
      defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
/****************************************************************************
| NAME:             Can_CheckSizeOfHwChannelData
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 4 START*/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) Can_CheckSizeOfHwChannelData(CanChannelHandle hwChannel) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  uint8 errorId = 0;

  /* #10 check size of canHwChannel against size of HwChannelData */
  if ( hwChannel >= kCanNumberOfChannels ) /* PRQA S 3325 */ /* MD_Can_3325 */ /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL08 */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    /* #20 Throw a DET */
    errorId = CAN_E_GENDATA;
#   if (CAN_DEV_ERROR_REPORT == STD_ON)
    Can_CallDetReportError( CAN_CHECK_DS_ID, errorId );
#   endif
  }

  return ( errorId );
}
/* CODE CATEGORY 4 END*/
#  endif
# endif


#if defined( C_ENABLE_CAN_RAM_CHECK )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_IsMailboxCorrupt
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8    result,idx,wordLength,i;
  
#if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) || defined( C_ENABLE_RX_FULLCAN_OBJECTS )
# if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
#   if !defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
  vuint8 filterHandle;
#  endif
  tCanRxMaskPtr pIndivRxMask = pCanRxMask(canHwChannel);
# endif
#endif

#if defined ( C_ENABLE_CAN_FD_FULL )  
#else
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
#endif

  /* ----- Implementation ----------------------------------------------- */
  result = kCanFalse;

# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  if (Can_CheckMaxHwMailboxHandle(canHwChannel, hwObjHandle) == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* CM_CAN_LL04 */
# endif
  {
    /* #10 DLC and IDE register check */
    LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)0x0055; /* SBSW_CAN_LL03 */
    if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)0x007F) != (vuint16)0x0055) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      result = kCanTrue;
    }
    LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)0x002A; /* SBSW_CAN_LL03 */
    if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)0x007F) != (vuint16)0x002A) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      result = kCanTrue;
    }
    LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = (vuint16)0x0000; /* SBSW_CAN_LL03 */
    if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) & (vuint16)0x007F) != (vuint16)0x0000) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      result = kCanTrue;
    }

    /* #20 Iterate test patterns */
    for(i = 0; i < 3; i++)
    {
      /* #30 ID register check */
      LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) = ramCheckPattern32[i]; /* SBSW_CAN_LL03 */
      if((LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, msgID) != ramCheckPattern32[i])) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
      {
        result = kCanTrue;
      }
      /* #40 Data register check */
# if defined ( C_ENABLE_CAN_FD_FULL )  
      wordLength = CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel);
# else
      wordLength = 2; /* check 8 data bytes */
# endif
      for (idx=0; idx<wordLength; idx++)
      {
        LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, data[idx]) = ramCheckPattern32[i]; /* SBSW_CAN_LL03 */
        if(LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, data[idx]) != ramCheckPattern32[i]) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        {
          result = kCanTrue;
        }
      }
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) || defined( C_ENABLE_RX_FULLCAN_OBJECTS )
#  if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
#   if !defined( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
      if (hwObjHandle == 0)
      {
        for(filterHandle = 0; filterHandle < NUMBER_OF_FILTERS(canHwChannel); filterHandle++)
        {
          if (filterHandle < NUMBER_OF_FULL_CONFIGURABLE_FILTERS(canHwChannel)) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          {
            pIndivRxMask->indivRxMask[hwObjHandle] = ramCheckPattern32[i]; /* SBSW_CAN_LL08 */
            if(pIndivRxMask->indivRxMask[hwObjHandle] != ramCheckPattern32[i]) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
            {
              result = kCanTrue;
            }
          }
        }
      }
      else if (hwObjHandle < CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel)) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */
#   else
      if (hwObjHandle < CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel))
#   endif
      {
        pIndivRxMask->indivRxMask[hwObjHandle] = ramCheckPattern32[i]; /* SBSW_CAN_LL08 */
        if(pIndivRxMask->indivRxMask[hwObjHandle] != ramCheckPattern32[i]) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        {
          result = kCanTrue;
        }
      }
#  endif
# endif

    }
  }
  return result;
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_InitBeginIsRegisterCorrupt
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginIsRegisterCorrupt(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint16 tmpCANmaxmb;
  vuint8 loopRamCheckCounter;
  vuint8 canRegistersRamCheckFailed;
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
# if defined ( V_CPU_S32 ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
  vuint32 tmpRamCheckPattern;
# endif
  
  /* ----- Implementation ----------------------------------------------- */
  tmpCANmaxmb = kCanRamCheckMaskMAXMB;


#if defined( C_ENABLE_CAN_FD_USED )
    if (!Can_IsHasCANFDBaudrateOfControllerConfig(canHwChannel)) /* COV_CAN_FD_BAUDRATE_AVAILABILITY */
    {
      /* Remove FD Flag in case of HwChannel does not support CANFD */
      tmpCANmaxmb &= ((vuint16) ~kFlexCAN_FDEN); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL01 */
    }
#endif
  /* #10 Check CLKSRC bit in control1 register */
  canRegistersRamCheckFailed = CanLL_CheckClockSource(CAN_HW_CHANNEL_CANPARA_ONLY);  

  /* #20 Iterate test patterns */
  for(loopRamCheckCounter = 0; loopRamCheckCounter < 3; loopRamCheckCounter++)
  {
    /* #30 Write MCR and MAXMB register */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kCanRamCheckMaskMCR); /* SBSW_CAN_LL01 */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, (ramCheckPattern16[loopRamCheckCounter] & kCanRamCheckMaskMCR)); /* SBSW_CAN_LL01 */
    
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmaxmb,tmpCANmaxmb); /* SBSW_CAN_LL01 */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmaxmb, (ramCheckPattern16[loopRamCheckCounter] & tmpCANmaxmb)); /* SBSW_CAN_LL01 */
    
    /* #40 Check the register contents */
    if(  ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kCanRamCheckMaskMCR) != (ramCheckPattern16[loopRamCheckCounter] & kCanRamCheckMaskMCR))
      || ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmaxmb) & tmpCANmaxmb) != (ramCheckPattern16[loopRamCheckCounter] & tmpCANmaxmb))) /* SBSW_CAN_LL01 */ /* SBSW_CAN_LL01 */ /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      canRegistersRamCheckFailed = kCanTrue;
      break; /* no need to carry on if check already failed */
    }
  }

  /* #50 Set all CAN register except the MCR register in unrestricted memory space */
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_SUPV); /* SBSW_CAN_LL01 */

  /* #60 Set WRNEN flag in CAN_MCR register to check TWRNMSK and RWRNMASK in CTRL1 register */
  CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_WRN_EN); /* SBSW_CAN_LL01 */

  /* #70 Iterate test patterns */
  for(loopRamCheckCounter = 0; loopRamCheckCounter < 3; loopRamCheckCounter++)
  {
    
    /* #80 Write CTRL1 register */
    pFlexCANLocal->control1 &= ~kCanRamCheckMaskCONTROL1; /* SBSW_CAN_LL01 */
    pFlexCANLocal->control1 |= ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCONTROL1; /* SBSW_CAN_LL01 */
    
# if defined( V_CPU_VYBRID ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
#  if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE ) /* COV_CAN_ENABLE_FLEXCAN_PARITY_CHECK */
    /* enable ECRWRE flag in CTRL2 register to get write access for MECR register */
    pFlexCANLocal->ctrl2 |= kFlexCAN_ECRWRE; /* SBSW_CAN_LL01 */
    /* #85 Write MECR register if available */
    pCanParityCheck(canHwChannel)->mecr &= (vuint32)(~kFlexCAN_ECRWRDIS); /* SBSW_CAN_LL08 */
    pCanParityCheck(canHwChannel)->mecr = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskMECR; /* SBSW_CAN_LL08 */
#  endif
# endif

    /* #90 Write CTRL2 register */
    pFlexCANLocal->ctrl2 = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCTRL2; /* SBSW_CAN_LL01 */
    
    /* #100 Write ECR register */
    pFlexCANLocal->ecr = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskECR; /* SBSW_CAN_LL01 */
    
    /* #110 Write IMASK1 register */
# if defined ( V_CPU_S32 ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
    tmpRamCheckPattern = ramCheckPattern32[loopRamCheckCounter];

    if(NUMBER_OF_MAX_MAILBOXES(canHwChannel) < 32) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
    {
      tmpRamCheckPattern = (vuint32) ramCheckPattern16[loopRamCheckCounter];
      pFlexCANLocal->imask1 = tmpRamCheckPattern; /* SBSW_CAN_LL01 */
    }
    else
# endif
    {
      pFlexCANLocal->imask1 = ramCheckPattern32[loopRamCheckCounter]; /* SBSW_CAN_LL01 */
    }
    
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* #120 Write IMASK2 register */
    pFlexCANLocal->imask2 = ramCheckPattern32[loopRamCheckCounter]; /* SBSW_CAN_LL01 */
# endif
  
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* #130 Write IMASK3 register */
#  if defined (C_ENABLE_ASYM_MAILBOXES) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
    if(NUMBER_OF_MAX_MAILBOXES(canHwChannel)>64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
    {
      pFlexCANLocal->imask3 = ramCheckPattern32[loopRamCheckCounter]; /* SBSW_CAN_LL01 */
    }
# endif
    
# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* #140 Write IMASK4 register */
    pFlexCANLocal->imask4 = ramCheckPattern32[loopRamCheckCounter]; /* SBSW_CAN_LL01 */
# endif
    
# if defined( C_ENABLE_EXTENDED_BITTIMING ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* #150 Write CBT register */
    pFlexCANLocal->cbt = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCBT; /* SBSW_CAN_LL01 */
# endif
    
# if defined( C_ENABLE_GLITCH_FILTER ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    /* #160 Write GFWR register */
    pCanGlitchFilter(canHwChannel)->gfwR = ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskGFWR; /* SBSW_CAN_LL08 */
# endif

    /* #170 Write RXGMASK register */
    pFlexCANLocal->rxfgmask = ramCheckPattern32[loopRamCheckCounter]; /* SBSW_CAN_LL01 */
    
    /* #180 Check the register contents  */
    if( ((pFlexCANLocal->control1 & kCanRamCheckMaskCONTROL1) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCONTROL1))      ||
        ((pFlexCANLocal->ecr & kCanRamCheckMaskECR) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskECR))                     ||
        ((pFlexCANLocal->ctrl2 & kCanRamCheckMaskCTRL2) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCTRL2))               ||
# if defined ( V_CPU_S32 ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */        
         (pFlexCANLocal->imask1 != tmpRamCheckPattern)                                                                                     ||
# else
         (pFlexCANLocal->imask1 != ramCheckPattern32[loopRamCheckCounter])                                                                 ||  
# endif
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
         (pFlexCANLocal->imask2 != ramCheckPattern32[loopRamCheckCounter])                                                                 ||
# endif
# if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
         (pFlexCANLocal->imask4 != ramCheckPattern32[loopRamCheckCounter])                                                                 ||
# endif
# if defined( C_ENABLE_EXTENDED_BITTIMING ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
        ((pFlexCANLocal->cbt & kCanRamCheckMaskCBT) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskCBT))                     ||
# endif
# if defined( C_ENABLE_GLITCH_FILTER ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
        ((pCanGlitchFilter(canHwChannel)->gfwR & kCanRamCheckMaskGFWR) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskGFWR)) ||
# endif
# if defined( V_CPU_VYBRID ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
#  if defined ( C_ENABLE_FLEXCAN_PARITY_CHECK_AVAILABLE ) /* COV_CAN_ENABLE_FLEXCAN_PARITY_CHECK */
        ((pCanParityCheck(canHwChannel)->mecr & kCanRamCheckMaskMECR) != (ramCheckPattern32[loopRamCheckCounter] & kCanRamCheckMaskMECR))   ||
#  endif
# endif
        (pFlexCANLocal->rxfgmask != ramCheckPattern32[loopRamCheckCounter])
      ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      canRegistersRamCheckFailed = kCanTrue;
    }
# if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    else
    {
#  if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
      if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
#  endif
      {
        if(pFlexCANLocal->imask3 != ramCheckPattern32[loopRamCheckCounter]) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        {
          canRegistersRamCheckFailed = kCanTrue;
        }
      }
    }
# endif
    if (canRegistersRamCheckFailed == kCanTrue) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
       break; /* no need to carry on if check already failed */
    }
  }

  return canRegistersRamCheckFailed;
}
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_CheckClockSource
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckClockSource(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint32 control1OldVal;
  vuint8 loopResult = 1; /* PRQA S 3197,781 */ /* MD_Can_3197_LL,MD_Can_Asr_0781 */
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
  vuint8 clkSrcCheckFailed = kCanFalse;
  
  /* #10 Enter DISABLE mode of FlexCAN */
  CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* disable FlexCAN module before clock selection */ /* SBSW_CAN_LL01 */
  if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
  {
    APPLCANTIMERSTART(kCanLoopEnterDisableMode); /* start hw loop timer */ /* SBSW_CAN_LL07 */
    do{
      /* wait for FlexCAN is disabled */
      loopResult = APPLCANTIMERLOOP(kCanLoopEnterDisableMode);
    }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) != kFlexCAN_LPM_ACK) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */ /* SBSW_CAN_LL01 */ /* COV_CAN_TIMEOUT_DURATION */
    APPLCANTIMEREND(kCanLoopEnterDisableMode);  /* stop hw loop timer */ /* SBSW_CAN_LL07 */
  }
      
  /* store configured value of control1 register */
  control1OldVal = CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->control1); /* SBSW_CAN_LL01 */
      
  /* #20 Perform check of Clock Source */
  CAN_WRITE_PROTECTED_REG_SET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* SBSW_CAN_LL01 */
  if((CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->control1) & kFlexCAN_CLK_SRC) != kFlexCAN_CLK_SRC) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
  {
    clkSrcCheckFailed = kCanTrue;
  }

  CAN_WRITE_PROTECTED_REG_RESET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* SBSW_CAN_LL01 */
  if((CAN_READ_PROTECTED_REG_32BIT(pFlexCANLocal->control1) & (kFlexCAN_CLK_SRC)) != 0x00u) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
  {
    clkSrcCheckFailed = kCanTrue;
  }
  
  /* #30 Reset FlexCAN clock source to configured value */
  if((control1OldVal & kFlexCAN_CLK_SRC) != 0) /* COV_CAN_TESTSTIMULATION */
  {
    CAN_WRITE_PROTECTED_REG_SET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* SBSW_CAN_LL01 */
  }
  else
  {
    CAN_WRITE_PROTECTED_REG_RESET_32BIT(pFlexCANLocal->control1, kFlexCAN_CLK_SRC); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL01 */
  }
  
  /* #40 Leave DISABLE mode of FlexCAN */
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* clear MDIS bit */ /* SBSW_CAN_LL01 */
  if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK) /* SBSW_CAN_LL01 */ /* COV_CAN_HARDWARE_PROCESSING_TIME */
  {
    APPLCANTIMERSTART(kCanLoopLeaveDisableMode); /* start hw loop timer */ /* SBSW_CAN_LL07 */
    do{
      /* wait for FlexCAN is enabled */
      loopResult = APPLCANTIMERLOOP(kCanLoopLeaveDisableMode);
    }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_LPM_ACK) == kFlexCAN_LPM_ACK) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */ /* SBSW_CAN_LL01 */ /* COV_CAN_TIMEOUT_DURATION */
    APPLCANTIMEREND(kCanLoopLeaveDisableMode);  /* stop hw loop timer */ /* SBSW_CAN_LL07 */
  }
  
  return clkSrcCheckFailed;
}
/* CODE CATEGORY 4 END */
# endif
#endif

#if defined ( V_CPU_S32 ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_ComputeMailboxInterrupt
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANTYPE_FIRST vuint32 iFlags, vuint32 iMask, CanObjectHandle startIndex) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  vuint32 activeInterrupts;
  CanObjectHandle index;
  
  activeInterrupts = iFlags & iMask;
  index = startIndex;
  /* #10 For all active pending interrupts */
  while(activeInterrupts != 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    /* #20 Compute index of active interrupt */
    while((activeInterrupts & (vuint32)0xFF) == 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      activeInterrupts >>= 8;
      index += (CanObjectHandle)8;
    }    
    if((activeInterrupts & (vuint32)0x0F) == 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      activeInterrupts >>= 4;
      index += (CanObjectHandle)4;
    }        
    while((activeInterrupts & (vuint32)0x01) == 0) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      activeInterrupts >>= 1;
      index++;
    }

#   if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#    if defined ( C_ENABLE_CAN_FD_FULL )
    if (Can_CheckMaxHwFDMailboxHandle(CAN_HW_CHANNEL_CANPARA_FIRST index) == CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */
#    endif
#   endif
    {
      /* #30 Call computation of interrupt type */
      CanLL_ComputeInterruptType(CAN_HW_CHANNEL_CANPARA_FIRST index);
    }

    index++;
    activeInterrupts = (iFlags & iMask) >> (index-startIndex);
  }
}
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
/****************************************************************************
| NAME:             CanLL_ComputeInterruptType
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ComputeInterruptType(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle index) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
# if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  /* #10 Check if pending interrupt is caused due to a FullCAN reception:
      if true call internal indication function. */
  if((index >= CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel))) /* COV_CAN_MAILBOX_ORDER */
  {
    CanFullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index);
  }
# endif
#endif

#if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  /* #20 Check if pending interrupt is caused due to a BasicCAN reception:
      if true call internal indication function. */
  if((index >= CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel))) /* COV_CAN_MAILBOX_ORDER */
  {
    CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index);
  }
#  endif
# endif
#endif

#if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  /* #30 Check if pending interrupt is caused due to a successful transmission:
      if true call internal indication function. */
  if((index >= CAN_HL_HW_TX_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_TX_STOPINDEX(canHwChannel))) /* COV_CAN_MAILBOX_ORDER */
  {
    {
      CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST index);
    }
  }    
#endif
}
/* CODE CATEGORY 1 END */
# endif
#endif

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
     defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
     defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
#define CAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*-------------------------------------------------------------------------*/

#define CAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif

#if defined( V_CPU_IMX ) || defined( V_CPU_VYBRID ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
/* **************************************************************************
| NAME:             CanInterrupt<Name>
| CALLED BY:        CanIsr<Name>_<physicalChannelIndex>()
| PRECONDITIONS:
| INPUT PARAMETERS: canHwChannel
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt structure
|                   - check for the interrupt reason ( interrupt source )
|                   - work appropriate interrupt:
|                     + status/error interrupt (BUSOFF, wakeup, error warning)
|                     + basic can receive
|                     + full can receive
|                     + can transmit
|
|                   If an RX-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   a wakeup has to be generated. 
|
|                   If an TX-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   an assertion has to be called and the interrupt has to be ignored.
|
|                   The name of BrsTimeStrt...() and BrsTimeStop...() can be adapted to 
|                   really used name of the interrupt functions.
|
************************************************************************** */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
  CanObjectHandle  index;
  vuint32  iFlags;
  vuint32  iMask1;
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  vuint32  iMask2;
# endif
# if !defined (C_ENABLE_CLASSIC_MAILBOX_LAYOUT)
#  if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#   if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  vuint8 fifoLoopCnt = 0;
#   endif
#  endif
# endif
#endif
  
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT ) || defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) || defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
  tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
#endif
  
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Start(RtmConf_RtmMeasurementPoint_CanInterrupt);
#endif
  
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
  iMask1 = pFlexCANLocal->imask1
# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# else
  & kCanRxFifoIntUnmask
# endif
  ;
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  iMask2 = pFlexCANLocal->imask2;
# endif  
#endif
    
#if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
  if((pFlexCANLocal->estat & kFlexCAN_WAKE_INT) != 0)
  {
    CanLL_WakeUpHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
  }
#endif
  
#if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
  {
    if((pFlexCANLocal->estat & kFlexCAN_BOFF_INT) != 0)
    {
      CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
    }
  }
#endif
  
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

# if !defined (C_ENABLE_CLASSIC_MAILBOX_LAYOUT)
#  if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#   if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
#    if defined(C_ENABLE_INDIVIDUAL_POLLING)
    /* additional check is necessary to ensure only objects configured for interrupt are processed here */
  if (Can_GetCanHwObjIndivPolling(CAN_HWOBJINDIVPOLLING_INDEX0, 0) == 0) /* COV_CAN_HWOBJINDIVPOLLING */
#    endif
  {
    while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP)) /* COV_CAN_TESTSTIMULATION */
    {
      fifoLoopCnt++;
      CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST 0);
    }
  }
#   endif
#  endif  /* C_ENABLE_RX_BASICCAN_OBJECTS */
# endif

  iFlags = pFlexCANLocal->iflag1 & iMask1;
  index = 0;
  while(iFlags != 0)
  {
    while((iFlags & (vuint32)0xFF) == 0)
    {
      iFlags >>= 8;
      index += (CanObjectHandle)8;
    }    
    if((iFlags & (vuint32)0x0F) == 0)
    {
      iFlags >>= 4;
      index += (CanObjectHandle)4;
    }        
    while((iFlags & (vuint32)0x01) == 0)
    {
      iFlags >>= 1;
      index++;
    }

# if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((index >= CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel)))
    {
      CanFullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index);
    }
#  endif
# endif

# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#  if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#   if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  if((index >= CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel))) /* COV_CAN_MAILBOX_ORDER */
  {
    CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index);
  }
#   endif
#  endif
# endif

# if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((index >= CAN_HL_HW_TX_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_TX_STOPINDEX(canHwChannel)))
    {
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST index);
      }
    }    
# endif

    index++;   
    iFlags = (pFlexCANLocal->iflag1 & iMask1) >> index;
  }

# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
  iFlags = pFlexCANLocal->iflag2 & iMask2;
# endif  

  index = 32;  
  while(iFlags != 0)
  {
    while((iFlags & (vuint32)0xFF) == 0)
    {
      iFlags >>= 8;
      index += (CanObjectHandle)8;    
    }
    if((iFlags & (vuint32)0x0F) == 0)
    {
      iFlags >>= 4;
      index += (CanObjectHandle)4;    
    }
    while((iFlags & (vuint32)0x01) == 0)
    {
      iFlags >>= 1;
      index++;
    }

# if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
#  if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((index >= CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel)))
    {
      CanFullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index);
    }
#  endif
# endif

# if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
#  if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
#   if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  if((index >= CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel))) /* COV_CAN_MAILBOX_ORDER */
  {
    CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index);
  }
#   endif
#  endif
# endif

# if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((index >= CAN_HL_HW_TX_STARTINDEX(canHwChannel)) && (index < CAN_HL_HW_TX_STOPINDEX(canHwChannel)))
    {
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST index);
      }
    }    
# endif
    
    index++;
# if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
    iFlags = (pFlexCANLocal->iflag2 & iMask2) >> (index-32);
# endif    
  }
#endif /* C_ENABLE_CAN_RXTX_INTERRUPT */

#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Stop(RtmConf_RtmMeasurementPoint_CanInterrupt);
#endif
} /* end of CanInterrupt */ /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 1 END */
#endif
#endif /* V_CPU_IMX */

#if defined( V_CPU_S32 ) /* COV_CAN_FLEXCAN3_ARM32_DERIVATIVE */
#if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffInterrupt
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Start(RtmConf_RtmMeasurementPoint_CanBusOffInterrupt);
#endif

# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  if (Can_CheckSizeOfHwChannelData( canHwChannel ) == 0) /* COV_CAN_GENDATA_FAILURE */
# endif
  {
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
    if (CanHL_IsControllerInit( canHwChannel )) /* COV_CAN_GENDATA_FAILURE */
# endif
    {
      /* #10 Call internal indication function if BUSOFF occurred */
      CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
    }
  }
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Stop(RtmConf_RtmMeasurementPoint_CanBusOffInterrupt);
#endif
}
/* CODE CATEGORY 1 END */
#endif
#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/****************************************************************************
| NAME:             CanMailboxInterrupt
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMailboxInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
#if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  vuint8 fifoLoopCnt;
# endif
#endif
  
  tFlexCANPtr pFlexCANLocal; /* PRQA S 781 */ /* MD_Can_Asr_0781 */
  
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Start(RtmConf_RtmMeasurementPoint_CanMailboxInterrupt);
#endif

# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
  if (Can_CheckSizeOfHwChannelData( canHwChannel ) == 0) /* COV_CAN_GENDATA_FAILURE */
# endif
  {
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
    if (CanHL_IsControllerInit( canHwChannel )) /* COV_CAN_GENDATA_FAILURE */
# endif
    {
      pFlexCANLocal = pFlexCAN(canHwChannel); /* SBSW_CAN_LL01 */

#if !defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
# if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    /* #10 Check if pending interrupt is caused due to a BasicCAN reception:
         if true call internal indication function. */
      fifoLoopCnt = 0;

#  if defined(C_ENABLE_INDIVIDUAL_POLLING)
    /* additional check is necessary to ensure only objects configured for interrupt are processed here */
      if (Can_GetCanHwObjIndivPolling(CAN_HWOBJINDIVPOLLING_INDEX0, 0) == 0) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      {
        while(((pFlexCANLocal->iflag1 & kRxFIFO_NEWMSG) != 0) && (fifoLoopCnt < C_FLEXCAN_RXFIFO_MAXLOOP)) /* COV_CAN_TESTSTIMULATION */
        {
          fifoLoopCnt++;
          CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST 0);
        }
      }
# endif
#endif

      /* #20 Call mailbox interrupt computation function for Mailboxes 0 to 31 */
      CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST pFlexCANLocal->iflag1, pFlexCANLocal->imask1, 0);
#if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
      /* #30 Call mailbox interrupt computation function for Mailboxes 32 to 63 */
      CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST pFlexCANLocal->iflag2, pFlexCANLocal->imask2, 32);
#endif
#if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
# if defined ( C_ENABLE_ASYM_MAILBOXES ) /* COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES */
  if (NUMBER_OF_MAX_MAILBOXES(canHwChannel) > 64) /* COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB */
# endif
      {
        /* #40 Call mailbox interrupt computation function for Mailboxes 64 to 95 */
        CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST pFlexCANLocal->iflag3, pFlexCANLocal->imask3, 64);
      }
#endif
#if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
      /* #50 Call mailbox interrupt computation function for Mailboxes 96 to 127 */
      CanLL_ComputeMailboxInterrupt(CAN_HW_CHANNEL_CANPARA_FIRST pFlexCANLocal->iflag4, pFlexCANLocal->imask4, 96);
#endif
    }
  }
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Stop(RtmConf_RtmMeasurementPoint_CanMailboxInterrupt);
#endif
}
#endif
#endif /* V_CPU_MPC5700 */


# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
     defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
     defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) /* COV_CAN_INTERRUPT_SUPPORT */
#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/****************************************************************************/

#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif

/****************************************************************************
| NAME:             CanHL_TxConfirmation
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_TxConfirmation
Relation_Context:
Relation:
CommonCan
DevErrorDetect, TxPolling, OneChOpt
TransmitCancellationAPI
UseVectorCanIf, IfTxBuffer, GenericConfirmation
HwCancelTx
GenericConfirmation, MirrorMode
GenericConfirmation, IDType
HwCancelTx, TransmitCancellationAPI, DevErrorDetect
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanHookBegin_CanHL_TxConfirmation();
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  /* #10 Check if parameter controller and txObjHandle is valid (only for Interrupt system, polling do this by caller) */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (((txObjHandle < CAN_HL_HW_TX_STARTINDEX(canHwChannel)) || (txObjHandle >= CAN_HL_HW_TX_STOPINDEX(canHwChannel)))) /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    CanObjectHandle logTxObjHandle;
    PduIdType tmp_pdu;
#if (CAN_CANCEL_SUPPORT_API == STD_ON)
    uint8_least tmp_state;
#endif
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    Can_ReturnType generic_retval;
#endif
    #if defined( C_ENABLE_CANCEL_IN_HW )
    vuint8 isMsgTransmitted;
    #endif
#if (defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    /* #100 EXCLUSIVE_AREA_3 needed to avoid another can_write while interface send out of queue (first send out of queue avoid inversion) or call GenericConfirmation2 (data consistency) */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_3);
#endif
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST (Can_HwHandleType)txObjHandle);
    {
      /* #120 Pre Release HW transmit object (LL) */
      if (txObjHandle < 32) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        pFlexCAN(canHwChannel)->iflag1 = CanBitMask(txObjHandle); /* clear pending interrupt flag */ /* SBSW_CAN_LL01 */
      }
      #if defined ( C_ENABLE_MB32TO63 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
      else 
      {
        if (txObjHandle < 64) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          pFlexCAN(canHwChannel)->iflag2 = CanBitMask(txObjHandle); /* clear pending interrupt flag */ /* SBSW_CAN_LL01 */
        }
      # if defined ( C_ENABLE_MB64TO95 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
        else
        {
          if (txObjHandle < 96) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          {
            pFlexCAN(canHwChannel)->iflag3 = CanBitMask(txObjHandle); /* clear pending interrupt flag */ /* SBSW_CAN_LL01 */
          }
      #  if defined ( C_ENABLE_MB96TO127 ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
          else
          {
            pFlexCAN(canHwChannel)->iflag4 = CanBitMask(txObjHandle); /* clear pending interrupt flag */ /* SBSW_CAN_LL01 */
          }
      #  endif
        }
      # endif
      }
      #endif
      /* #130 Remember PDU for confirmation parameter */
      tmp_pdu   = Can_GetActiveSendPdu(logTxObjHandle);
#if (CAN_CANCEL_SUPPORT_API == STD_ON)
      /* #140 Remember SEND STATE which may be modified due to new transmit call in indication */
      tmp_state = (uint8_least)Can_GetActiveSendState(logTxObjHandle);
#endif
#if defined(C_ENABLE_CANCEL_IN_HW) 
      /* #150 If the message was successfully transmitted (without cancellation) (LL): */
      isMsgTransmitted = (vuint8)CanLL_TxIsHWObjFree(canHwChannel, txObjHandle); /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */
      if (!isMsgTransmitted)
      {
        GLOBAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, control) = kTxCodeFree; /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL03 */
      }
      
      if (isMsgTransmitted != (vuint8)0)
#endif
      { /* #200 Set send state to free to allow next TX out of confirmation or direct (reload queue) */
        /* #210 Notify the application by call Appl_GenericConfirmation() and CanIf_TxConfirmation() */
        /*      - Appl_GenericConfirmation() if configured and mirror mode is active
                and afterwards depend of return value
                - CanIf_TxConfirmation() if generic confirmation return OK, or no generic is used, and TX is not cancelled */
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API1)
        Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
        if (Appl_GenericConfirmation( tmp_pdu ) == CAN_OK)
#elif defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
# if defined(C_ENABLE_MIRROR_MODE)
        if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
        { /* MirrorMode is inactive so call the following CanIf_TxConfirmation() */
          Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
          generic_retval = CAN_OK;
        }
        else
# endif
        { /* #230 For generic confirmation with API2 copy PDU data as parameter for Appl_GenericConfirmation() */
          Can_PduType canPdu;
          tCanTxInfoStruct canTxInfoStruct;
          
          /* get pointer to DLC and ID field in message object */
          #if defined( C_CPUTYPE_LITTLEENDIAN ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
          /* get pointer to first element in tCanMsgObj */
          canTxInfoStruct.pChipMsgObj = (CanChipMsgPtr)&(GLOBAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, timestamp)); /* PRQA S 0310,3689 */ /* MD_Can_0310,MD_Can_3689_LL_objHandle */
          #endif
          /* get pointer to datafield in message object */
          #if defined( C_CPUTYPE_LITTLEENDIAN ) /* COV_CAN_FLEXCAN3_DERIVATIVE */
          {
          # if defined ( C_ENABLE_CAN_FD_FULL )
            V_DEF_VAR(CAN_STATIC, vuint32, VAR_NOINIT) canFdTxBuf[16];
            vuint8 idx;
          
            for (idx=0; idx<CANFD_MAILBOX_MAX_WORD_LENGTH(canHwChannel); idx++)
            {
              canFdTxBuf[idx] = CanBswap32(GLOBAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, data[idx])); /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL12 */
            }
            (canTxInfoStruct.pChipData) = (CanChipDataPtr)&(canFdTxBuf); /* PRQA S 0310 */ /* MD_Can_0310 */			
          # else
            V_DEF_VAR(CAN_STATIC, vuint32, VAR_NOINIT) canTxBuf[2];
            
            canTxBuf[0] = CanBswap32(GLOBAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, data[0])); /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL13 */
            canTxBuf[1] = CanBswap32(GLOBAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, data[1])); /* PRQA S 3689 */ /* MD_Can_3689_LL_objHandle */ /* SBSW_CAN_LL13 */
          
            (canTxInfoStruct.pChipData) = (CanChipDataPtr)&(canTxBuf); /* PRQA S 0310 */ /* MD_Can_0310 */
          # endif
          }
          #endif
          
          canPdu.sdu = (Can_SduPtrType)canTxInfoStruct.pChipData; /* PRQA S 0312 */ /* MD_Can_0312 */
          canPdu.length = CAN_DECODE_DLI(CanTxActualDLC((&canTxInfoStruct)));
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanTxActualIdType((&canTxInfoStruct)) == kCanIdTypeStd)
          { /* Mixed ID */
            canPdu.id = (Can_IdType)CanTxActualStdId((&canTxInfoStruct));
          }
          else
#  endif  /* pure Extended ID */
          { /* Extended ID */
            canPdu.id = (Can_IdType)(CanTxActualExtId((&canTxInfoStruct)) | CAN_ID_IDE_MASK);
          }
# else    /* Standard ID */
          canPdu.id = CanTxActualStdId((&canTxInfoStruct));
# endif
# if defined(C_ENABLE_CAN_FD_USED)
          if ( CanTxActualFdType((&canTxInfoStruct)) == kCanFdTypeFd )
          {
            canPdu.id |= (Can_IdType)CAN_ID_FD_MASK;
          }
# endif
          canPdu.id &= CAN_ID_MASK_IN_GENERIC_CALLOUT;
          canPdu.swPduHandle = tmp_pdu;
          Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */ /* release after copy data to avoid data inconsistency */
          /* call Appl_GenericConfirmation() and in case of CAN_OK also the following CanIf_TxConfirmation() */
          generic_retval = Appl_GenericConfirmation( (uint8)channel, &canPdu ); /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL32 */
        }
        /* #300 Appl_GenericConfirmation() decide to call Indication */
        if (generic_retval == CAN_OK)
#else /* no generic confirmation */
        Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
#endif
        {
#if (CAN_CANCEL_SUPPORT_API == STD_ON)
          /* #310 If TX is SW cancelled call CanIf_CancelTxNotification() */
          if (tmp_state == CAN_CANCEL_OBJ_SW) /* COV_CAN_CANCEL_SW_STIMULATION */
          {
            CanIf_CancelTxNotification( tmp_pdu, FALSE );
          }
          else
#endif  /* #320 otherwise call CanIf_TxConfirmation() */
          {
            CanIf_TxConfirmation( tmp_pdu ); /* \trace SPEC-1726, SPEC-1571 */
          }
        }
#if (defined(CAN_ENABLE_GENERIC_CONFIRMATION_API1) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)) && (CAN_TRANSMIT_BUFFER == STD_ON)
        /* #350 otherwise no CanIf_TxConfirmation() will be called so call CanIf_CancelTxNotification() just to notify IF to restart sending out of Queue */
        else
        {
# if (CAN_CANCEL_SUPPORT_API == STD_OFF)
#  error "When using Generic Confirmation and Transmit buffer (If) the Cancel-support-api (if) has to be activated"
# else
          CanIf_CancelTxNotification( tmp_pdu, FALSE );
# endif
        }
#endif
      }
#if defined(C_ENABLE_CANCEL_TX_IN_HW)
      /* #400 otherwise mailbox is cancelled successful */
      else
      {
#  if (CAN_CANCEL_SUPPORT_API == STD_ON)
        if (tmp_state == CAN_CANCEL_OBJ_SW) /* COV_CAN_CANCEL_SW_STIMULATION */
        { /* #410 free active PDU to allow next TX out of confirmation or direct (reload queue) */
          Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ); /* SBSW_CAN_HL04 */
          /* #420 SW cancellation: just call CanIf_CancelTxNotification() (no interrupt lock used here! - worst case can_write came in between and a unnecessary cancellation appear) */
          CanIf_CancelTxNotification( tmp_pdu, TRUE );
        }
        else
#  endif
        {
#  if defined(C_ENABLE_CANCEL_IN_HW) /* COV_CAN_CANCEL_IN_HW TX */
          /* always CancelSW when only FullCAN TX is cancelled so never called */
#   if (CAN_DEV_ERROR_DETECT == STD_ON)
          /* #440 Check send state is not free now, to secure that ActiveSendPduInfo is already set before used */
          if (Can_GetActiveSendState(logTxObjHandle) == CAN_FREE_OBJ) /* COV_CAN_HARDWARE_FAILURE */
          {
            errorId = CAN_E_PARAM_HANDLE;
          }
          else
#   endif
          { /* #450 EXCLUSIVE_AREA_3 -> no call to upper layer here */
            Can_EnterCritical(CAN_EXCLUSIVE_AREA_3);
            /* #460 free active PDU to allow next TX out of confirmation or direct (reload queue) */
            Can_SetActiveSendState(logTxObjHandle, CAN_FREE_OBJ);  /* SBSW_CAN_HL04 */          
            /* #470 call CanIf_CancelTxConfirmation() to re trigger queue \trace SPEC-1726, SPEC-1725, SPEC-1684, SPEC-1689, SPEC-3932, SPEC-3908 */
#   if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
            CanIf_CancelTxConfirmation( Can_GetActiveSendSwPduHandle(logTxObjHandle), &Can_GetActiveSendPduInfo(logTxObjHandle) ); /* SBSW_CAN_HL25 */
#   else
            CanIf_CancelTxConfirmation( &Can_GetActiveSendPduInfo(logTxObjHandle) ); /* SBSW_CAN_HL25 */
#   endif
            Can_LeaveCritical(CAN_EXCLUSIVE_AREA_3);
          }
#  endif
        }
      }
#endif
      /* #500 Post release HW transmit object (LL) */
    }

#if (defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_3);
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
# if !defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  if (errorId != CAN_E_NO_ERROR) /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_TXCNF_ID, errorId);
  }
# endif
#endif
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  CanHookEnd_CanHL_TxConfirmation();
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanBasicCanMsgReceived
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanBasicCanMsgReceived
Relation_Context:
RxBasicCANSupport
Relation:
CommonCan
OneChOpt
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, TxPolling, IndividualPolling
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanRxBasicInfoStruct rxBasicInfo;
  CanHookBegin_CanBasicCanMsgReceived();
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  rxBasicInfo.Controller = Controller;
# endif
  rxBasicInfo.rxObjHandle = rxObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON) && !defined(C_ENABLE_RX_BASICCAN_POLLING)
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif 
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #25 receive handling begin CanHL_RxBasicMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanHL_RxBasicMsgReceivedBegin(&rxBasicInfo) == CAN_OK) /* SBSW_CAN_HL26 */ /* COV_CAN_RxBasicMsgReceivedBegin */
    {
# if defined(C_ENABLE_CAN_RAM_CHECK)
      /* -------------------------- RAM check failed --- */
      if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
# if defined(C_ENABLE_OVERRUN)
        /* -------------------------- Overrun --- */
        #if defined ( C_ENABLE_CLASSIC_MAILBOX_LAYOUT )
        if((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kCodeMask) == kRxCodeOverrun)
        {
        #else
        CAN_HL_INFO_RXBASIC(pFlexCANLocal) = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */
        if((CAN_HL_INFO_RXBASIC(pFlexCANLocal)->iflag1 & kRxFIFO_OVERRUN) != 0) /* COV_CAN_TESTSTIMULATION */
        {
          CAN_HL_INFO_RXBASIC(pFlexCANLocal)->iflag1 = kRxFIFO_OVERRUN | kRxFIFO_WARN; /* clear warning and overflow flag */ /* SBSW_CAN_LL09 */
        #endif
          /* #40 Overrun occur so notify upper layer \trace SPEC-1686 */
#   if (CAN_OVERRUN_NOTIFICATION == CAN_DET)
          Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_DATALOST); /* Call DET direct because Overrun will be notified additional to following DETs */
#   else /* CAN_OVERRUN_NOTIFICATION == CAN_APPL */
          Appl_CanOverrun( (uint8)channel );
#   endif
        }
# endif
        /* \trace SPEC-1346 */
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
          rxBasicInfo.rxInfo.localDlc = CAN_DECODE_DLI(CanRxActualDLC((&rxBasicInfo.rxInfo)));
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanRxActualIdType((&rxBasicInfo.rxInfo)) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID */
            rxBasicInfo.rxInfo.localId = (Can_IdType)CanRxActualStdId((&rxBasicInfo.rxInfo));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxBasicInfo.rxInfo.localId = (Can_IdType)(CanRxActualExtId((&rxBasicInfo.rxInfo)) | CAN_ID_IDE_MASK);
          }
          {
# else 
          { /* pure - standard ID */
            rxBasicInfo.rxInfo.localId = CanRxActualStdId((&rxBasicInfo.rxInfo));
# endif
# if defined(C_ENABLE_CAN_FD_USED)
            if ( CanRxActualFdType((&rxBasicInfo.rxInfo)) == kCanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxBasicInfo.rxInfo.localId |= (Can_IdType)CAN_ID_FD_MASK;
            }
            /* DLC is not bigger than expected length (8) for CLASSIC CAN msg (additional to HashTag 145) */
            if ((CanRxActualFdType((&rxBasicInfo.rxInfo)) != kCanFdTypeFd) && (rxBasicInfo.rxInfo.localDlc > 8)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
# endif
            /* -------------------------- Search HRH  --- */
            /* #130 search HRH for the given rxObjHandle CanHL_RxBasicMsgReceivedSearch() */
            if (CanHL_RxBasicMsgReceivedSearch(&rxBasicInfo) == CAN_OK) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* SBSW_CAN_HL26 */ /* COV_CAN_GENDATA_FAILURE */
            {
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_ENABLE_RX_BASICCAN_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING))
              /* #140 Check HRH is BasicCAN (already checked in polling task - do it only for interrupt) */
              if ( (rxBasicInfo.rxInfo.localHrh < Can_GetRxBasicHandleStart(canHwChannel)) || /* PRQA S 3356,3355,3358 */ /* MD_Can_13.7 */
                   (rxBasicInfo.rxInfo.localHrh >= Can_GetRxBasicHandleStop(canHwChannel)) )  /* PRQA S 3355 */ /* MD_Can_13.7 */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
              {
                errorId = CAN_E_PARAM_HANDLE;
              } 
              else
#  endif
# endif
              /* #145 DLC is not bigger than expected length from mailbox (MAX over all BasicCAN msg) */
              if (rxBasicInfo.rxInfo.localDlc > CAN_MAX_DATALEN_OBJ(rxBasicInfo.rxInfo.localHrh)) /* ESCAN00084263 */ /* PRQA S 3201 */ /* MD_Can_3201 */ /* COV_CAN_HARDWARE_FAILURE */
              {
                errorId = CAN_E_PARAM_DLC;
              }
              else
              {
                /* -------------------------- Notification --- */
                /* #150 RX queue and notification handling CanHL_RxMsgReceivedNotification() */
                errorId = CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANPARA_FIRST &rxBasicInfo.rxInfo); /* SBSW_CAN_HL26 */
              }
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_RxBasicMsgReceivedEnd() */
    CanHL_RxBasicMsgReceivedEnd(&rxBasicInfo); /* SBSW_CAN_HL26 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */ /* PRQA S 3201 */ /* MD_Can_3201 */
    Can_CallDetReportError(CAN_RXINDI_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  CanHookEnd_CanBasicCanMsgReceived();
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanFullCanMsgReceived
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanFullCanMsgReceived
Relation_Context:
RxFullCANSupport
Relation:
CommonCan
OneChOpt
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, TxPolling, IndividualPolling
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanFullCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanRxFullInfoStruct rxFullInfo;
  CanHookBegin_CanFullCanMsgReceived();
  errorId = CAN_E_NO_ERROR;
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  rxFullInfo.Controller = channel;
# endif
  rxFullInfo.rxObjHandle = rxObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #25 receive handling begin CanHL_RxFullMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanHL_RxFullMsgReceivedBegin(&rxFullInfo) == CAN_OK) /* SBSW_CAN_HL27 */ /* COV_CAN_RxFullMsgReceivedBegin */
    {
  /* -------------------------- RAM check failed --- */
# if defined(C_ENABLE_CAN_RAM_CHECK)
      if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
        /* -------------------------- Overrun --- */
# if defined(C_ENABLE_FULLCAN_OVERRUN)
        if ((Can_GetRxMsgBufferOfControllerData(canHwChannel).control & kCodeMask) == kRxCodeOverrun) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        {
          /* #40 Overrun occur so notify upper layer */
#   if (CAN_OVERRUN_NOTIFICATION == CAN_DET)
          Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_DATALOST); /* \trace SPEC-1686 */ /* Call DET direct because Overrun will be notified additional to following DETs */
#   else /* CAN_OVERRUN_NOTIFICATION == CAN_APPL */
          Appl_CanFullCanOverrun( (uint8)channel );
#   endif
        }
# endif
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
          rxFullInfo.rxInfo.localDlc = CAN_DECODE_DLI(CanRxActualDLC((&rxFullInfo.rxInfo)));
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanRxActualIdType((&rxFullInfo.rxInfo)) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID*/
            rxFullInfo.rxInfo.localId = (Can_IdType)CanRxActualStdId((&rxFullInfo.rxInfo));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxFullInfo.rxInfo.localId = (Can_IdType)(CanRxActualExtId((&rxFullInfo.rxInfo)) | CAN_ID_IDE_MASK);
          }
          {
# else 
          { /* pure - standard ID */
            rxFullInfo.rxInfo.localId = CanRxActualStdId((&rxFullInfo.rxInfo));
# endif
# if defined(C_ENABLE_CAN_FD_USED)
            if ( CanRxActualFdType((&rxFullInfo.rxInfo)) == kCanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxFullInfo.rxInfo.localId |= (Can_IdType)CAN_ID_FD_MASK;
            }
# endif
            /* -------------------------- Search HRH --- */
            /* #130 search HRH for the given rxObjHandle */
            if (CanHL_RxFullMsgReceivedSearch(&rxFullInfo) == CAN_OK) /* SBSW_CAN_HL27 */ /* COV_CAN_GENDATA_FAILURE */
            {
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_ENABLE_RX_FULLCAN_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING)) /* COV_CAN_RX_FULLCAN_POLLING */
              /* #140 Check HRH is FullCAN (already checked in polling task - do it only for interrupt) */
              if ( (rxFullInfo.rxInfo.localHrh < Can_GetRxFullHandleStart(canHwChannel)) || /* PRQA S 3356,3355,3358 */ /* MD_Can_13.7 */
                   (rxFullInfo.rxInfo.localHrh >= Can_GetRxFullHandleStop(canHwChannel)) )  /* PRQA S 3355 */ /* MD_Can_13.7 */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
              {
                errorId = CAN_E_PARAM_HANDLE;
              }
              else
#  endif
# endif
              /* #145 DLC is not bigger than expected length from mailbox */
              if (rxFullInfo.rxInfo.localDlc > CAN_MAX_DATALEN_OBJ(rxFullInfo.rxInfo.localHrh)) /* ESCAN00084263 */ /* PRQA S 3201 */ /* MD_Can_3201 */ /* COV_CAN_HARDWARE_FAILURE */
              {
                errorId = CAN_E_PARAM_DLC;
              }
              else
              {
                /* -------------------------- Notification --- */
                /* #150 RX queue and notification handling CanHL_RxMsgReceivedNotification() */
                errorId = CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANPARA_FIRST &rxFullInfo.rxInfo); /* SBSW_CAN_HL27 */
              }
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_RxFullMsgReceivedEnd() */
    CanHL_RxFullMsgReceivedEnd(&rxFullInfo); /* SBSW_CAN_HL27 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */ /* PRQA S 3201 */ /* MD_Can_3201 */
    Can_CallDetReportError(CAN_RXINDI_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  CanHookEnd_CanFullCanMsgReceived();
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

/****************************************************************************
| NAME:             CanHL_ErrorHandling
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_ErrorHandling
Relation_Context:
Relation:
CommonCan
DevErrorDetect, StatusPolling, OneChOpt
BusOffRecovery, OneChOpt
Overrun
DevErrorDetect
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_ENABLE_ERROR_POLLING) /* COV_CAN_ERROR_POLLING */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    # if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
    vuint16     hwObjHandle;
    # endif
    tFlexCANPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */ /* PRQA S 781 */ /* MD_Can_Asr_0781 */ /* SBSW_CAN_LL01 */
    /* #20 Pre Error handling (LL) */
    if((pFlexCANLocal->estat & kFlexCAN_BOFF_INT) != 0) /* COV_CAN_BUSOFF_HANDLING */
    {
      pFlexCANLocal->estat = (CANSFR_TYPE)(kFlexCAN_BOFF_INT | kFlexCAN_ERR_INT); /* clear busoff and error interrupt flags */ /* SBSW_CAN_LL01 */
    
    # if defined ( C_ENABLE_BUSOFF_RECOVERY_COMPLIANT )
      /* delete pending transmit requests */
      for(hwObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); hwObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); hwObjHandle++)
      {  
        LOCAL_MAILBOX_ACCESS(canHwChannel, hwObjHandle, control) = kTxCodeInactive; /* set all mailboxes inactive */ /* SBSW_CAN_LL03 */
      }      
    # endif
      /* #90 EXCLUSIVE_AREA_6 secure mode changes */
      Can_EnterCritical(CAN_EXCLUSIVE_AREA_6);
      /* #100 BUSOFF occur -> ECU Manager restart Controller (no ResetBusOffStart/End needed) */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
      Can_SetBusOffCounter(channel, 3); /* SBSW_CAN_HL33 */
#endif
      Can_SetIsBusOff(channel, TRUE); /* SBSW_CAN_HL08 */ /* attention: platform use this for BUSOFF 128*11 treatment!!! */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_BUSOFF); /* SBSW_CAN_HL02 */
#if !defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
      /* #110 CanResetBusOffStart need when BUSOFF handled by Application */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
      CanResetBusOffStart(channel, Can_GetLastInitObject(channel));
# else
      CanResetBusOffStart(Can_GetLastInitObject(channel));
# endif
#endif
      /* #115 Controller is in STOP mode after CanResetBusOffStart \trace SPEC-1578, SPEC-1664, SPEC-1663, SPEC-3828 */
      /* #120 Status changed to STOP - no more call of STOP from CAN Interface */
      Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
      Can_LeaveCritical(CAN_EXCLUSIVE_AREA_6);
      /* #130 notify higher layer by call CanIf_ControllerBusOff() \trace SPEC-1726, SPEC-1578 */
      CanIf_ControllerBusOff((uint8)Can_GetCanToCanIfChannelMapping(channel));
    }
    /* #200 Post Error handling (LL) */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 3356,3359 */ /* MD_Can_13.7,MD_Can_13.7 */
  { /* Throw DET if an error detected before */ /* PRQA S 3201 */ /* MD_Can_3201 */
    Can_CallDetReportError(CAN_CTRBUSOFF_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */


#define CAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*-------------------------------------------------------------------------*/

#define CAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (CAN_VERSION_INFO_API == STD_ON) /* \trace SPEC-1716, SPEC-3964 */
/****************************************************************************
| NAME:             Can_GetVersionInfo
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| Can_GetVersionInfo
Relation_Context:
VersionInfoApi
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_GetVersionInfo( Can_VersionInfoPtrType VersionInfo )
{ /* \trace SPEC-1723, SPEC-3881 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter versionInfo is an illegal null pointer \trace SPEC-1721, SPEC-3847 */
  if (VersionInfo == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  { /* #100 copy version info to given pointer parameter \trace SPEC-1717, SPEC-3845 */
    /* ----- Implementation ----------------------------------------------- */
    VersionInfo->vendorID   = CAN_VENDOR_ID; /* SBSW_CAN_HL10 */
    VersionInfo->moduleID   = CAN_MODULE_ID; /* SBSW_CAN_HL10 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
    VersionInfo->instanceID = CAN_INSTANCE_ID; /* SBSW_CAN_HL10 */
# endif
    VersionInfo->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION; /* SBSW_CAN_HL10 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_VERSION_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}
#endif

/****************************************************************************
| NAME:             Can_InitMemory
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_InitMemory
Relation_Context:
Relation:
Variant
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_InitMemory( void )
{ /* BR:011 */
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 mark driver as uninitialized \trace SPEC-1650, SPEC-3787 */
  canConfigInitFlag = CAN_STATUS_UNINIT;
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
  /* #20 reset global configuration pointer */
  Can_ConfigDataPtr = NULL_PTR;
#endif /* otherwise constant pointer is used */
  /* #30 HW reset memory */
  /* only needed by ASR (and only if variables have to be initialized but will not be done in normal init) */
#if(CAN_DEV_ERROR_DETECT == STD_OFF)
  CAN_DUMMY_STATEMENT(canConfigInitFlag); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
}

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
/****************************************************************************
| NAME:             Can_InitStruct
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/*
|<DataModelStart>| Can_InitStruct
Relation_Context:
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_InitStruct( uint8 Controller, uint8 Index )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON) && !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller and index are valid */
  if ( (channel >= kCanNumberOfChannels) || (Index >= (uint8)(Can_GetInitObjectStartIndex(channel+1) - Can_GetInitObjectStartIndex(channel))) ) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  { /* #20 set initialization structure that should be used for next controller initialization. */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel) + Index)); /* SBSW_CAN_HL11 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON) && !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INIT_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}
#endif

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if ((CAN_CHANGE_BAUDRATE_API == STD_ON) || (CAN_SET_BAUDRATE_API == STD_OFF))
/****************************************************************************
| NAME:             Can_ChangeBaudrate
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_ChangeBaudrate
Relation_Context:
ChangeBaudrate
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_ChangeBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20314 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId;
  retVal = E_NOT_OK;
  errorId = CAN_E_PARAM_BAUDRATE; /* explicit default as Issue - remove when baud rate fit */ /* \trace SPEC-20321 */
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-20338 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-20331 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
  if ( (Can_GetLogStatus(channel) & CAN_STATUS_STOP) != CAN_STATUS_STOP )
  { /* \trace SPEC-1655, SPEC-20312 */
    errorId = CAN_E_TRANSITION;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_GetInitObjectStartIndex(channel); baudrateIndex < Can_GetInitObjectStartIndex(channel+1); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 set baud rate and reinitialize controller to activate baud rate \trace SPEC-1669 */
        Can_SetLastInitObject(channel, (uint8)baudrateIndex); /* SBSW_CAN_HL11 */
        Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
        retVal = E_OK;
        errorId = CAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CHANGE_BR_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif

# if (CAN_CHANGE_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_CheckBaudrate
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_CheckBaudrate
Relation_Context:
ChangeBaudrate
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20311 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId;
  retVal = E_NOT_OK;
  errorId = CAN_E_PARAM_BAUDRATE; /* \trace SPEC-20317 */
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT \trace SPEC-20328, SPEC-20318 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels )
  { /* \trace SPEC-20335 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_GetInitObjectStartIndex(channel); baudrateIndex < Can_GetInitObjectStartIndex(channel+1); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 requested baud rate is set - return OK */
        retVal = E_OK;
        errorId = CAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CHECK_BR_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  return retVal;
}
# endif /* CAN_CHANGE_BAUDRATE_API == STD_ON */

# if (CAN_SET_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_SetBaudrate
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_SetBaudrate
Relation_Context:
ChangeBaudrate
Relation:
DevErrorDetect, OneChOpt
HardwareLoop
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{ /* \trace SPEC-50605 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  /* #5 return E_NOT_OK in case no fitting baudrate is found \trace-2622524 */
  retval = E_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-50595 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-50587 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
  if ( (Can_GetLogStatus(channel) & CAN_STATUS_STOP) != CAN_STATUS_STOP )
  { /* \trace SPEC-50584 */
    errorId = CAN_E_TRANSITION;
  }
  else
  if ( BaudRateConfigID >= (uint16)(Can_GetInitObjectStartIndex(channel+1) - Can_GetInitObjectStartIndex(channel)) )
  { /* \trace SPEC-50625, SPEC-50563 */
    errorId = CAN_E_PARAM_BAUDRATE;
  }
  else
#  endif
  { /* #50 set baud rate and reinitialize controller to activate baud rate */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel) + BaudRateConfigID)); /* SBSW_CAN_HL11 */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
    Can_SetIsHardwareCanceled(channel,FALSE); /* SBSW_CAN_HL14 */
#  endif
    Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */ /* \trace SPEC-50576, SPEC-50563, SPEC-50617 */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
    /* #60 check if hardware cancellation appear while mode change, so for the baud rate set is not successful \trace SPEC-60434 */
    if ( !Can_IsIsHardwareCanceled(channel) ) /* COV_CAN_HARDWARE_FAILURE */
#  endif
    {
      retval = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_SET_BR_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* CAN_SET_BAUDRATE_API == STD_ON */
#endif /* only MSR403 */

/****************************************************************************
| NAME:             Can_Init
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_Init
Relation_Context:
Relation:
Variant, DevErrorDetect
PrecompileAndLinktimeCRCCheck
DevErrorDetect, Variant, CommonCan
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
RxQueue
Variant
OneChOpt
RamCheck
Wakeup
PnEnable
MirrorMode
SilentMode
ChangeBaudrate
UseVectorCanIf
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_Init( Can_ConfigPtrType ConfigPtr )
{ /* \trace SPEC-1587, SPEC-3850, SPEC-3794, SPEC-1708, SPEC-3826, SPEC-3861 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CAN_CHANNEL_CANTYPE_LOCAL
  CanHookBegin_Can_Init();
  errorId = CAN_E_NO_ERROR;
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER) /* PostBuild (load+sel) */
  Can_ConfigDataPtr = ConfigPtr; /* \trace SPEC-1394, SPEC-1575 */
# if defined(CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* PostBuildLoadable */
  if (ConfigPtr == NULL_PTR)
  { /* #10 EcuM null pointer configuration check and notification */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
  }
  else
#  if (CAN_FINALMAGICNUMBER == STD_ON) /* COV_CAN_FINALMAGICNUMBER */
  if (Can_GetFinalMagicNumber() != 20510u) /* COV_CAN_GENDATA_FAILURE */
  { /* #20 EcuM wrong magic number check and notification */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
#  endif
# else
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #30 Check if all parameters are valid \trace SPEC-1724, SPEC-3789 */
  if (ConfigPtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
  /* #40 Check wrong magic number */
#   if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
  /* not CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK --> not PostBuildLoadable so CAN_FINALMAGICNUMBER is always false */
#   else
  if (Can_GetFinalMagicNumber() != 0xaffeu) /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
#   endif
#  endif
# endif
#else
  CAN_DUMMY_STATEMENT(ConfigPtr); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199, 3198 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
  ConfigPtr = Can_ConfigDataPtr; /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#endif /* CAN_ENABLE_USE_INIT_ROOT_POINTER */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag != CAN_STATUS_UNINIT)
  {
    /* #60 Check already initialized -> 2nd call is not allowed \trace SPEC-1712, SPEC-3934, SPEC-3767, SPEC-1722 */
    errorId = CAN_E_TRANSITION;
  }
  else
#endif
  if (  ( Can_GetBaseDll_GeneratorVersion()     != (uint16)CAN_GEN_BASE_VERSION ) ||  /* PRQA S 3325 */ /* MD_Can_3325 */
        ( Can_GetPlatformDll_GeneratorVersion() != (uint16)CAN_GEN_ImxFlexcan3Asr_VERSION ) ) /* COV_CAN_GENDATA_FAILURE */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    /* #70 EcuM generator and compatibility version check and notification */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* not for PostBuildSelectable */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
# else
    errorId = CAN_E_UNINIT;
# endif
#else
    EcuM_GeneratorCompatibilityError((uint16) CAN_MODULE_ID, (uint8) 0);
#endif
  }
  else
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if (CAN_CRC_CHECK == STD_ON)
  if (( Can_GetPrecompileCRC() != CAN_PRECOMPILE_CRC ) || ( Can_GetLinktimeCRC() != Can_LinktimeCRC )) /* COV_CAN_GENDATA_FAILURE */
  { /* #80 EcuM generator pre compile and link time CRC check and notification */
    EcuM_GeneratorCompatibilityError((uint16) CAN_MODULE_ID, (uint8) 0u);
  }
  else
# endif
#endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if CAN_DEV_ERROR_DETECT == STD_ON
#  if defined(CAN_ENABLE_SELECTABLE_PB) 
  if (
       (kCanNumberOfChannels > kCanNumberOfMaxUsedControllers) ||
       (kCanNumberOfUsedHwChannels > kCanNumberOfMaxUsedControllers) )
  { /* #90 check consistency of generated Data (real channel amount against maximum value) */
    errorId = CAN_E_PARAM_POINTER;
  }
  else
#  endif
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    {
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
      Can_SignedHwHandleType tmp_objcnt;
      tmp_objcnt=0;
#endif
      canRxTaskActive = CAN_FREE;
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
      canApiContext = CAN_INIT_ID;
#   endif
#  endif
# endif
#endif
#if defined(C_ENABLE_RX_QUEUE)
      /* #110 delete RxQueue (all channels) */
      Can_GetRxQueueInfo().WriteIndex = 0;  /* CM_CAN_HL24 */
      Can_GetRxQueueInfo().ReadIndex = 0;
      Can_GetRxQueueInfo().Count = 0;
      canRxQueueMaxDataSize = (uint16) (sizeof(Can_GetRxQueueBuffer(0).data) / sizeof(Can_GetRxQueueBuffer(0).data[0]));
#endif
      /* #120 Set active Identity */
#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
      CanSetActiveIdentity(Can_GetIdentitySelected());
#endif
      /* #130 HW specific power on (LL) */
      CanHL_InitPowerOn();

      canConfigInitFlag = CAN_STATUS_INIT; /* \trace SPEC-1648, SPEC-3962, SPEC-3943 */ /* before Controller initialization begin */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
      for (channel = 0; channel < kCanNumberOfChannels; channel++) /* CM_CAN_HL01 */
#endif
      { /* #132 for each controller */
#if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
        if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_FAILURE */
        { /* #134 not for inactive controller */
          continue; /* PRQA S 0770 */ /* MD_Can_0770 */
        }
#endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
# if defined(C_ENABLE_GEN_HW_START_STOP_IDX) /* generated as tool-table */
        /* #136 calculate logical TX handle (HW to log - done here because of multiple ECU) */
#  if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)Can_GetTxBasicHwStart(CAN_HL_HW_CHANNEL_STARTINDEX(channel)));
#  else
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)Can_GetTxFullHwStart(CAN_HL_HW_CHANNEL_STARTINDEX(channel)));
#  endif
# else
#  if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)Can_GetHwHandle(Can_GetTxBasicHandleStart(CAN_HL_HW_CHANNEL_STARTINDEX(channel))));
#  else
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)Can_GetHwHandle(Can_GetTxFullHandleStart(CAN_HL_HW_CHANNEL_STARTINDEX(channel))));
#  endif
# endif
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
        tmp_objcnt = (Can_SignedHwHandleType)(tmp_objcnt + (Can_SignedHwHandleType)Can_GetTxFullHandleMax(CAN_HL_HW_CHANNEL_STARTINDEX(channel)) + (Can_SignedHwHandleType)(Can_GetTxBasicHandleMax(CAN_HL_HW_CHANNEL_STARTINDEX(channel)) * CAN_MULTIPLEXED_TX_MAX));
# endif
#endif
        /* #140 initialize start up values for each controllers */
        Can_SetLogStatus(channel, CAN_STATUS_UNINIT); /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
        Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK)
        Can_SetStatusReq(channel, Can_GetStatusReq(channel) | CAN_REQ_RAM_CHECK); /* execute power on RamCheck*/ /* SBSW_CAN_HL01 */
#endif
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
        Can_SetBusOffCounter(channel, 0); /* SBSW_CAN_HL33 */
#endif
        Can_SetIsBusOff(channel, FALSE);  /* start up: no BUSOFF */ /* SBSW_CAN_HL08 */
        Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel))); /* SBSW_CAN_HL11 */
        Can_SetCanInterruptCounter(channel, 0); /* SBSW_CAN_HL12 */
#if defined(C_ENABLE_PARTIAL_NETWORK) /* COV_CAN_PARTIAL_NETWORK */
        Can_SetTimeoutCall(channel,TRUE); /* SBSW_CAN_HL13 */
#endif
#if defined(C_ENABLE_MIRROR_MODE)
        Can_SetMirrorModeState(channel, CDDMIRROR_INACTIVE); /* SBSW_CAN_HL20 */
#endif
#if defined(C_ENABLE_SILENT_MODE)
        Can_SetSilentModeState(channel, CAN_SILENT_INACTIVE); /* SBSW_CAN_HL20 */
#endif
        /* #155 HW channel specific power on */
        CanHL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANPARA_ONLY);

        /* #160 set baud rate and initialize all CAN controllers \trace SPEC-1587, SPEC-1656, SPEC-3981 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
        Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(0));      /* use always first initStruct */ /* SBSW_CAN_HL03 */
#elif defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
        Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* set to STOP mode before set baud rate to avoid DET */ /* SBSW_CAN_HL02 */
# if (CAN_SET_BAUDRATE_API == STD_ON)
        (void)Can_SetBaudrate((uint8)channel, Can_GetCanControllerDefaultBaudrateIdx(CAN_HL_HW_CHANNEL_STARTINDEX(channel)));
# else
        (void)Can_ChangeBaudrate((uint8)channel, Can_GetCanControllerDefaultBaudrate(CAN_HL_HW_CHANNEL_STARTINDEX(channel))); /* \trace SPEC-15127 */
# endif
#else
# if !defined(CAN_USE_VECTOR_IF) 
        /* #170 call Can_InitController() - For Vector ASR3 this will be done within Can Interface */
        Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
# endif
#endif
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INIT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_Init();
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_InitController
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_InitController
Relation_Context:
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
RamCheck
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
CommonCan
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
RamCheck
Wakeup
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerConfigPtrType ControllerConfigPtr )
#elif defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerBaudrateConfigPtrType Config )
#elif  defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerConfigPtrType ControllerConfigPtr )
#endif
{ /* \trace SPEC-1719, SPEC-1589, SPEC-1346, SPEC-1565, SPEC-3883 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanHookBegin_Can_InitController();
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Config pointer is valid and state is INIT \trace SPEC-3962 */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1718, SPEC-3797 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1713, SPEC-3821 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
  if (Config == NULL_PTR)
  { /* \trace SPEC-1711, SPEC-3774 */
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* \trace SPEC-1713 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
#endif
#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
  /* #50 Check controller is in active ECU - otherwise nothing to do here */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 )  /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    tCanInitInfoStruct initInfo;
    /* #100 initialization controller states and initialization objects --- */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
    Can_SetLastInitObject(channel, (uint8)((uint8)Can_GetInitObjectStartIndex(channel) + (uint8)*Config)); /* SBSW_CAN_HL11 */
#endif
    initInfo.initObject = Can_GetLastInitObject(channel);
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
    initInfo.Controller = channel;
#endif
    initInfo.isChCorrupt = kCanFalse;
    /* #110 clean up status (do not activate communication and let SLEEP and initialization to detect ram-check request) */
#if defined(C_ENABLE_CAN_RAM_CHECK) && !defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
    { /* #112 standard RAM check will be performed so delete old status CAN_DEACTIVATE_CONTROLLER */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & CAN_STATUS_INIT);  /* SBSW_CAN_HL02 */
    }
    else
#endif
    { /* #114 extended RAM check may be performed so delete old status except CAN_DEACTIVATE_CONTROLLER */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(CAN_DEACTIVATE_CONTROLLER | CAN_STATUS_INIT));  /* SBSW_CAN_HL02 */
    }
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
    canApiContext = CAN_INITCTR_ID;
#   endif
#  endif
# endif
#endif
    { /* #125 begin initialization CanHL_InitBegin() */
      {
        errorId = CanHL_InitBegin(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
      {
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
        /* #140 do TX FullCAN initialization CanHL_InitTxFullCAN()*/
        CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
        { /* do it only when no error occur before */
          errorId = CanHL_InitTxFullCAN(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
        }
#endif
        /* #150 do TX BasicCAN initialization CanHL_InitTxBasicCAN() */
        CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
        { /* do it only when no error occur before */
          errorId = CanHL_InitTxBasicCAN(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
        }
      } /* Common CAN:  TX only on first hwChannel */
#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
      /* #170 do RX FullCAN initialization CanHL_InitRxFullCAN() */
      CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
      { /* do it only when no error occur before */
        errorId = CanHL_InitRxFullCAN(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
#endif
#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
      /* #180 do RX BasicCAN initialization CanHL_InitRxBasicCAN() */
      CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
      { /* do it only when no error occur before */
        errorId = CanHL_InitRxBasicCAN(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
#endif
      /* #190 end initialization CanHL_InitEnd_InitMode() */
      CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
      { /* do it only when no error occur before */
        errorId = CanHL_InitEnd_InitMode(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
#if defined(C_ENABLE_CAN_RAM_CHECK)
      if ((Can_GetStatusReq(channel) & CAN_REQ_RAM_CHECK) == CAN_REQ_RAM_CHECK)
      { 
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
        /* #200 extended RamChecks new issue occur - notify corrupt register / deactivate controller */
        if (initInfo.isChCorrupt == kCanTrue) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        {
          CanIf_RamCheckCorruptController((uint8)Can_GetCanToCanIfChannelMapping(channel));
          Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */
        }
# else
        if( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        { /* #210 standard RAM check issue occur - call Appl_CanRamCheckFailed() */
          if (Appl_CanRamCheckFailed((uint8)channel) != CAN_DEACTIVATE_CONTROLLER)
          { /* #220 let the application decide if communication stay disabled as set by RAM check or not */
            Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(~(CAN_DEACTIVATE_CONTROLLER))); /* Application decide to activate communication in case RAM_CHECK failed */  /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
          }
        }
# endif
        CAN_RAM_CHECK_FINISHED_CTP(channel)
      }
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
      /* #230 no STOP transition for defect Controllers */
      if( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
#endif
      {
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
        /* #250 BUSOFF, WAKEUP and Re-initialization lead direct to STOP mode, otherwise it is only a re-initialization with transition afterwards. */
        if ( (Can_GetStatusReq(channel) & CAN_REQ_INIT_NO_STOP) != CAN_REQ_INIT_NO_STOP ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        { /* #260 no more polling or notification, BUSOFF, WAKEUP notified before otherwise Re-initialization only allowed in STOP mode */
          Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
#endif
          /* #270 Switch to STOP mode CanHL_InitEnd_StopMode() */
          CAN_IS_NO_ERROR(errorId) /* COV_CAN_HARDWARE_FAILURE */
          { /* do it only when no error occur before */
            errorId = CanHL_InitEnd_StopMode(&initInfo); /* SBSW_CAN_HL31 */ /* PRQA S 3198 */ /* MD_MSR_14.2 */
          }
          Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP);  /* \trace SPEC-1657, SPEC-1647 set STOP */ /* SBSW_CAN_HL02 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
        }
#endif
      }
    } /* end of loop over all HW channels */
#if (CAN_DEV_ERROR_DETECT == STD_ON) 
    if (errorId != CAN_E_NO_ERROR) /* COV_CAN_HARDWARE_FAILURE */
    { /* #275 remove controller init flag when issue occure before */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(~(CAN_STATUS_INIT))); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
    }
    else
#endif
    { /* #280 set controller init flag when no issue occure before */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | (CAN_STATUS_INIT)); /* SBSW_CAN_HL02 */
    }
#if defined(C_ENABLE_CAN_RAM_CHECK)
    Can_SetStatusReq(channel, Can_GetStatusReq(channel) & (uint8)(~(CAN_REQ_RAM_CHECK))); /* deactivate RamCheck - finished */ /* SBSW_CAN_HL01 */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ 
#endif
  } /* controller active in multiple ECU configuration */

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INITCTR_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if !defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
  CAN_DUMMY_STATEMENT(ControllerConfigPtr); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_InitController();
} /* PRQA S 6010,6050,6030,6080 */ /* MD_Can_Asr_STPTH,MD_MSR_STCAL,MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_SetControllerMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_SetControllerMode
Relation_Context:
Relation:
CommonCan
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
RamCheck
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
BusOffRecovery
ReInitStart
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition )
{ /* \trace SPEC-1715, SPEC-3894 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_ReturnType retval;
  CanHookBegin_Can_SetControllerMode();
  retval = CAN_NOT_OK;  /* \trace SPEC-1407 */ /* For successful transition it is set explicit to CAN_OK */
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Transition is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1731, SPEC-3962, SPEC-3872 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1732 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { 
    errorId = CAN_E_PARAM_CONTROLLER; /* \trace SPEC3874 */
  }
  else
# endif
#endif
#if defined(C_ENABLE_MULTI_ECU_CONFIG) /* move below channel DET check */ /* COV_CAN_MULTI_ECU_CONFIG */
  /* #40 Check controller is in active ECU */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 ) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* only for active Controller */
#endif
  { /* #50 second level check (modes and transitions) only valid when controller is in active ECU and valid */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (!CanHL_IsControllerInit(channel))
    { /* #60 Check controller is initialized \trace SPEC-3962 */
      errorId = CAN_E_UNINIT;
    }
    else
    if ((!CanHL_IsStop(channel)) && (Transition == CAN_T_START))
    { /* #70 Check No-STOP -> START-Req is invalid \trace SPEC-1637, SPEC-3862 */ /* ESCAN00073272 */
      errorId = CAN_E_TRANSITION;
    }
    else
# if (CAN_TRANSITION_CHECK == STD_ON)  /* ASR4 extension SREQ00000291 */ /* COV_CAN_USER_CONFIG */
    if ( ((!CanHL_IsStop(channel)) && (!CanHL_IsSleep(channel)) && ((Transition == CAN_T_WAKEUP) || (Transition == CAN_T_SLEEP))) ||
         ((CanHL_IsSleep(channel)) && (Transition == CAN_T_STOP)) )
    { /* #80 Check  No STOP Nor SLEEP -> SLEEP-Req   or   No SLEEP Nor STOP --> WAKEUP-Req   is invalid \trace SPEC-1654, SPEC-1649 */
      /* #90 Check  No START Nor STOP -> STOP-Req is invalid \trace SPEC-1652 */
      errorId = CAN_E_TRANSITION; /* trace SPEC-3862 */
    }
    else
# endif
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #95 controller is active (no RAM check issue): */
    if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* COV_CAN_RAM_CHECK_NO_STIMULATION */
#endif
    {
      /* ----- Implementation ----------------------------------------------- */
      /* #100 EXCLUSIVE_AREA_6 avoid nesting mode changes (e.g. same API, initialization or BUSOFF) */
      Can_EnterCritical(CAN_EXCLUSIVE_AREA_6);
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
      canApiContext = CAN_SETCTR_ID;
#   endif
#  endif
# endif
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
      /* #110 reset flag that may be set in LL-initialization or HW-loop as notification that transition failed */
      Can_SetIsHardwareCanceled(channel,FALSE); /* SBSW_CAN_HL14 */
#endif
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
      /* #120 mark ongoing state change (suppress STOP transition in Can_InitController()) */ 
      Can_SetStatusReq(channel, Can_GetStatusReq(channel) | CAN_REQ_INIT_NO_STOP); /* SBSW_CAN_HL01 */
#endif
      /* #125 HW begin mode transition */
      switch(Transition)
      {
      case CAN_T_START: /* \trace SPEC-3963 */
        /* #200 Handle --- START --- transition */
#if !defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
        if (Can_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
        { /* #210 BUSOFF occur so finish BUSOFF handling with CanResetBusOffEnd() */
          /* #215 reset BUSOFF flag - do this before CanResetBusOffEnd() so LL may overwrite it */
          Can_SetIsBusOff(channel, FALSE); /* SBSW_CAN_HL08 */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
          CanResetBusOffEnd(channel, Can_GetLastInitObject(channel));
# else
          CanResetBusOffEnd(Can_GetLastInitObject(channel));
# endif
          /* #220 do not re-initialization after BUSOFF, this will be done while CanResetBusOffStart/End() */
        }
        else
#endif
        {
#if (CAN_REINIT_START == STD_ON) 
          /* #230 additional to STOP-transition-re initialization a Can_InitController() may be activated for START transition \trace SPEC-1730 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
          Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(Can_GetLastInitObject(channel) - (uint8)Can_GetInitObjectStartIndex(channel)) & 0x03u))); /* SBSW_CAN_HL03 */
# else
          Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
# endif
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
          if ( Can_IsIsHardwareCanceled(channel) ) /* COV_CAN_HARDWARE_FAILURE */
          { /* #240 break START transition when Can_InitContoller() failed */
            break;  /* PRQA S 3333 */ /* MD_Can_14.6 */
          }
#endif
        }
        /* #250 START: set request and wait limited time and notify upper Layer - CanHL_StartTransition() */
        retval = CanHL_StartTransition(CAN_CHANNEL_CANPARA_ONLY);
        break;

      case CAN_T_STOP: /* \trace SPEC-3976 */
        /* #300 Handle --- STOP --- transition */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
        if (Can_GetBusOffCounter(channel) == 0)  /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
        {
          Can_SetIsBusOff(channel, FALSE); /* SBSW_CAN_HL08 */
        }
        else
        {
          Can_DecBusOffCounter(channel); /* SBSW_CAN_HL33 */
        }
#endif
        /* #310 ESCAN00032291: no call of STOP inside BUSOFF (avoid blocking) */
        if (!Can_IsIsBusOff(channel)) /* COV_CAN_HARDWARE_FAILURE */
        {
          /* #320 STOP: set request and wait limited time and notify upper Layer - CanHL_StopTransition() */
          retval = CanHL_StopTransition(CAN_CHANNEL_CANPARA_ONLY);
        } /* IsBusOff */
        break;

      case CAN_T_WAKEUP:
        /* #400 Handle --- WAKEUP --- transition */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* does not appear in MSR30 (synchronous) */ /* COV_CAN_MICROSAR_VERSION */
        if ( (Can_GetStatusReq(channel) & CAN_REQ_SLEEP) == CAN_REQ_SLEEP )
        { /* #410 ASR4: Check WAKEUP not allowed while transition to SLEEP \trace SPEC-1573, SPEC-1402, SPEC-1403, SPEC-3848, SPEC-1660 */
          errorId = CAN_E_TRANSITION;
        }
        else
#endif
        {
          /* #420 WAKEUP: set request and wait limited time and notify upper Layer (RAM-check, Emulated SLEEP handling) - CanHL_WakeupTransition() */
          retval = CanHL_WakeupTransition(CAN_CHANNEL_CANPARA_ONLY);
        }
        break;

      case CAN_T_SLEEP: /* \trace SPEC-3926, SPEC-1639 */
        /* #500 Handle --- SLEEP --- transition */
        /* #510 SLEEP: set request and wait limited time and notify upper Layer (Emulated SLEEP handling) - CanHL_SleepTransition() */
        retval = CanHL_SleepTransition(CAN_CHANNEL_CANPARA_ONLY);
        break; /* CAN_T_SLEEP */

      default: /* PRQA S 2018 */ /* MD_Can_Asr_2018 */
        /* #600 check unknown transition, return NOT_OK \trace SPEC-1573, SPEC-1402, SPEC-1403 */
        errorId = CAN_E_TRANSITION; /* \trace SPEC-1733, SPEC-1407 */
        break;
      } /* switch */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
      /* #700 remove mark ongoing state change (suppress STOP transition in Can_InitController()) */ 
      Can_SetStatusReq(channel, Can_GetStatusReq(channel) & (uint8)(~(CAN_REQ_INIT_NO_STOP))); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL01 */
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
      if ( Can_IsIsHardwareCanceled(channel) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #705 while mode change a hardware cancellation appear and there for the mode change is not successful */
        Can_SetIsHardwareCanceled(channel,FALSE); /* SBSW_CAN_HL14 */
        /* \trace SPEC-1573, SPEC-1402, SPEC-1403 */
        errorId = CAN_E_TRANSITION;
        retval = CAN_NOT_OK; /* \trace SPEC-3782, SPEC-3769 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
        /* #710 ASR4: no more status polling - request failed */ 
        Can_SetStatusReq(channel, CAN_REQ_NONE); /* SBSW_CAN_HL01 */
# endif
      }
#endif
      Can_LeaveCritical(CAN_EXCLUSIVE_AREA_6);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_SETCTR_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_SetControllerMode();
  return retval;
} /* PRQA S 6030,6050,6080 */ /* MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_DisableControllerInterrupts
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_DisableControllerInterrupts
Relation_Context:
Relation:
CommonCan
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
IntLock, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_DisableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1746, SPEC-3886 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1750, SPEC-3880, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1742, SPEC-3860 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* move below channel DET check */ /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #30 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1750, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_1);
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
    canApiContext = CAN_DIINT_ID;
#   endif
#  endif
# endif
#endif
    if (Can_GetCanInterruptCounter(channel) == 0)
    { /* #110 Disable only when not disabled before (count nesting) \trace SPEC-1735, SPEC-1745, SPEC-3783 */
#if (CAN_INTLOCK == CAN_DRIVER) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      { /* #120 Disable CAN interrupt for each HW channel */
        CanLL_CanInterruptDisable(canHwChannel, &Can_GetCanInterruptOldStatus(canHwChannel)); /* SBSW_CAN_HL16 */
      }
#endif
#if (CAN_INTLOCK == CAN_APPL) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      /* #130 Let application Disable CAN interrupt ApplCanInterruptDisable() */
      ApplCanInterruptDisable((uint8)channel);
#endif
    }
    Can_SetCanInterruptCounter(channel, Can_GetCanInterruptCounter(channel)+1); /* \trace SPEC-1748, SPEC-3875, SPEC-3876 */ /* SBSW_CAN_HL12 */
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_1);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_DIINT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
} /* PRQA S 6050,6080 */ /* MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_EnableControllerInterrupts
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_EnableControllerInterrupts
Relation_Context:
Relation:
CommonCan
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
CanDevTimeoutDetect, HardwareLoop, HardwareCancelByAppl, DevErrorDetect
IntLock, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_EnableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1741, SPEC-3891 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-3866, SPEC-1739, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1752, SPEC-3858 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* move below channel DET check */ /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #30 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1739, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_1);
    if (Can_GetCanInterruptCounter(channel) != 0)
    { /* #110 Enable only when disabled before (count nesting) \trace SPEC-1749, SPEC-1748, SPEC-3875 */
      Can_SetCanInterruptCounter(channel, Can_GetCanInterruptCounter(channel)-1); /* SBSW_CAN_HL12 */
#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR30) /* COV_CAN_MICROSAR_VERSION */
# if defined(CAN_ENABLE_DEV_TIMEOUT_DETECT) /* COV_CAN_DEV_TIMEOUT_DETECT */
#  if defined(C_ENABLE_HW_LOOP_TIMER)
#   if (CAN_HW_LOOP_SUPPORT_API == STD_OFF) && (CAN_DEV_ERROR_DETECT == STD_ON)
      canApiContext = CAN_ENINT_ID;
#   endif
#  endif
# endif
#endif
      if (Can_GetCanInterruptCounter(channel) == 0) /* \trace SPEC-1736, SPEC-1756, SPEC-3877 */
      {
#if (CAN_INTLOCK == CAN_DRIVER) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        { /* #120 Disable CAN interrupt for each HW channel */
          CanLL_CanInterruptRestore(canHwChannel, Can_GetCanInterruptOldStatus(canHwChannel));
        }
#endif
#if (CAN_INTLOCK == CAN_APPL) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        /* #130 Let application Enable CAN interrupt ApplCanInterruptRestore() */
        ApplCanInterruptRestore((uint8)channel);
#endif
      }
    }
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_1);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_ENINT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
} /* PRQA S 6050,6080 */ /* MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_Write
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_Write
Relation_Context:
Relation:
CommonCan
DevErrorDetect, MicrosarVersion
OneChOpt, CommonCan
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
DevErrorDetect, TxFullCANSupport
DevErrorDetect, CanFdSupport
DevErrorDetect, MixedId
RamCheck
UseVectorCanIf
DevErrorDetect
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_Write( Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo )
{ /* \trace SPEC-1751, SPEC-3887,   SPEC-1760, SPEC-1406 */
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  CanHookBegin_Can_Write();
  errorId = CAN_E_NO_ERROR;
  retval = CAN_NOT_OK; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1759, SPEC-3864 */
    errorId = CAN_E_UNINIT;
  }
  else
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
  if (Hth >= Can_GetSizeOfMailbox()) {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
#endif
  {
#if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Hth);
#endif
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# endif
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* move below channel DET check */ /* COV_CAN_MULTI_ECU_CONFIG */
    if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
    { /* #30 Check controller is in active ECU */
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# endif
    if (!CanHL_IsControllerInit(channel))
    { /* #40 Check controller is initialized \trace SPEC-1407, SPEC-3962 */
      errorId = CAN_E_UNINIT;
    }
    else
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
    if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# else
    if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# endif
    { /* \trace SPEC-1763, SPEC-3870 */
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
    if ((PduInfo == NULL_PTR) || ((PduInfo->sdu == NULL_PTR) && (PduInfo->length != 0)))
    { /* \trace SPEC-1761, SPEC-3868 */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# if !defined(C_ENABLE_CAN_FD_USED)
    if ( CanHL_IsFdMessage(PduInfo->id) )
    { /* no CAN_FD: Check parameter PduInfo->id should not have FD bit in ID */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# endif
# if defined(C_ENABLE_CAN_FD_FULL)
    if ( ((PduInfo->length > 8) && (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE)) ||
         (PduInfo->length > CAN_MAX_DATALEN_OBJ(Hth)) ) /* COV_CAN_GENDATA_FAILURE */
         { /* \trace SPEC-1758, SPEC-3865 */
      /* \trace SPEC-60433 */ /* CAN_FD: Check parameter PduInfo->length is smaller than 9 for none FD configuration
         If development error detection for the CAN module is enabled and the CAN Controller is not in CAN FD mode (no CanControllerFdBaudrateConfig):
         The function Can_Write shall raise the error CAN_E_PARAM_DLC and shall return CAN_NOT_OK if the length is more than 8 byte.() */
      /* CAN_FD: Check parameter PduInfo->length against PDU maximum size */
      errorId = CAN_E_PARAM_DLC;
    }
    else
# else
    if ( PduInfo->length > CAN_MAX_DATALEN_OBJ(Hth) ) /* CM_CAN_HL20 */
    { /* \trace SPEC-1758 */ /* Check parameter PduInfo->length against maximum buffer size */
      errorId = CAN_E_PARAM_DLC;
    }
    else
# endif
# if defined(C_ENABLE_MIXED_ID)
    if ( ((PduInfo->id & (Can_IdType)CAN_ID_IDE_MASK) != (Can_IdType)CAN_ID_IDE_MASK ) && ( (PduInfo->id & (Can_IdType)CAN_ID_MASK) > (Can_IdType)CAN_ID_MASK_STD ) )
    { /* Check parameter PduInfo->id for STD ID is in STD range (EXT is always in range) */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# endif
    if ( (PduInfo->id & (Can_IdType)CAN_ID_UNUSED_MASK) != 0 )
    { /* Check parameter PduInfo->id contains illegal bits (e.g. bigger ID value than MAX for given type) */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
#endif
    /* ----- Implementation ----------------------------------------------- */
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #150 reject deactivated mailbox (by RamCheck) */
    if (Can_GetMailboxState(Hth) == CAN_DISABLED_OBJ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      retval = CAN_NOT_OK;
    }
    else
#endif
    /* #180 check Hardware is in BUSOFF recovery state and is not able to handle a request: return BUSY \trace SPEC-1764 */
    if (Can_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
    {
      retval = CAN_NOT_OK; /* ESCAN00096369 */
    }
    else
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #200 controller is active (no RAM check issue): */
    if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_Asr_2004 */ /* COV_CAN_HARDWARE_FAILURE */
#endif
    {
      CanObjectHandle  logTxObjHandle;
      /* #210 EXCLUSIVE_AREA_2: Interrupts may not be locked and re-entrant call may occur. */
      /*                        Time in between ID search and lock of mailbox is critical 
                                (only when no Vector Interface used otherwise CanIf EXCLUSIVE_AREA is used instead) 
                                Can_Write() could be called re-entrant, there for also for polling systems the interrupts have to be locked  
                                this is essential while check for mailbox is free (in between if (free) and set to not free) and save PDU handle */
#if !defined(CAN_USE_VECTOR_IF)
      Can_EnterCritical(CAN_EXCLUSIVE_AREA_2);
#endif
      /* #220 search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary */
      logTxObjHandle = CanHL_WritePrepare(CAN_CHANNEL_CANPARA_FIRST Hth, PduInfo); /* SBSW_CAN_HL28 */
      /* #230 start transmission for given handle (if free) and return state */
      retval = CanHL_WriteStart(CAN_CHANNEL_CANPARA_FIRST Hth, logTxObjHandle, PduInfo); /* SBSW_CAN_HL28 */

#if !defined(CAN_USE_VECTOR_IF) /* No Vector Interface used, Interrupts may not be locked */
      /* avoid change of PDU information due to TX interrupt while changing */
      Can_LeaveCritical(CAN_EXCLUSIVE_AREA_2);
#endif
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_WRITE_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_Write();
  return retval;
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             ASR4.x - Can_CheckWakeup / ASR3.x - Can_Cbk_CheckWakeup
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_CheckWakeup
Relation_Context:
Relation:
Wakeup, DevErrorDetect, OneChOpt
Wakeup, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckWakeup( uint8 Controller )
{ /* \trace SPEC-1740, SPEC-3922 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  retval = E_NOT_OK; /* \trace SPEC-1407 */
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_Write
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_MainFunction_Write
Relation_Context:
Relation:
TxPolling, HwCancelTx, DevErrorDetect
TxPolling, HwCancelTx, OneChOpt
TxPolling, HwCancelTx, Variant
TxPolling, HwCancelTx, Wakeup
TxPolling, HwCancelTx, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Write( void )
{ /* \trace SPEC-3873, SPEC-1766 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_TX_POLLING) 
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  CanHookBegin_Can_MainFunction_Write();
  /* canSendSemaphor no more needed because of ControllerInterrupts disabled while Can_Write() */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3784, SPEC-1767,  SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* one controller optimization is always off */ /* COV_CAN_MULTI_ECU_CONFIG */
      if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON) /* \trace SPEC-1573, SPEC-1402, SPEC-1403 */
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */ /* \trace SPEC-3962 */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
# if (CAN_EMULATE_SLEEP == STD_ON) /* COV_CAN_EMULATE_SLEEP */
        if ( !CanHL_IsSleep(channel) )
# endif
        { /* #60 do not access CAN hardware in SLEEP */
          {
# if defined(C_ENABLE_TX_POLLING) /* always true when no hw-cancel is supported */ /* COV_CAN_TX_POLLING TX */
            /* #100 do confirmation handling for pending mailboxes */
            CanHL_TxTaskConfPendingHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
# if defined(C_ENABLE_CANCEL_TX_IN_HW) 
# endif /* defined(C_ENABLE_CANCEL_TX_IN_HW) */
          } /* CanHL_IsSleep */
        } /* end of loop over all HW channels */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_WRITE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif

#else
  CanHookBegin_Can_MainFunction_Write();
#endif /* C_ENABLE_TX_POLLING */
  CanHookEnd_Can_MainFunction_Write();
}

/****************************************************************************
| NAME:             Can_MainFunction_Read
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_MainFunction_Read
Relation_Context:
Relation:
DevErrorDetect
RxPolling, OneChOpt
RxPolling, Variant
RxPolling, DevErrorDetect
RxPolling, Wakeup
RxPolling, CommonCan
RxPolling, RxFullCANSupport
RxPolling, RxBasicCANSupport
RxQueue
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Read( void )
{ /* \trace SPEC-3871, SPEC-1776 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanHookBegin_Can_MainFunction_Read();
  errorId = CAN_E_NO_ERROR; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check Driver is initialized \trace SPEC-3841, SPEC-1784, SPEC-3852,  SPEC-3962 */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  {
    errorId = CAN_E_UNINIT; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  }
  else
#endif
  /* ----- Implementation ----------------------------------------------- */
  /* #20 semaphore to secure parallel access to RX buffers interrupt or polling \trace SPEC-1569, SPEC-3785 */
  if ( canRxTaskActive == CAN_FREE)  /* PRQA S 2004 */ /* MD_Can_Asr_2004 */
  {
#if defined(C_ENABLE_RX_POLLING) /* COV_CAN_RX_POLLING */
    CAN_CHANNEL_CANTYPE_LOCAL
#endif
    canRxTaskActive = CAN_BUSY; /* PRQA S 3198 */ /* MD_MSR_14.2 */
#if defined(C_ENABLE_RX_POLLING) /* \trace SPEC-1782, SPEC-3771 */ /* COV_CAN_RX_POLLING */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #30 iterate over all active controller */
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* one controller optimization is always off */ /* COV_CAN_MULTI_ECU_CONFIG */
      if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #60 Check controller is initialized \trace SPEC-3962 */
        errorId = CAN_E_UNINIT; /* PRQA S 3198 */ /* MD_MSR_14.2 */
      }
      else
# endif
      {
# if (CAN_EMULATE_SLEEP == STD_ON) /* COV_CAN_EMULATE_SLEEP */
        if ( !CanHL_IsSleep(channel) )
# endif
        { /* #70 do not access CAN hardware in SLEEP */
          { /* #80 over all HW channel \trace SPEC-3814, SPEC-1774 */
# if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
            /* #90 search for all pending FullCAN mailbox objects and call notification */
            CanHL_RxFullMsgReceivePolling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
# if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
            /* #100 search for all pending BasicCAN mailbox objects and call notification */
            CanHL_RxBasicMsgReceivePolling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
          } /* CanHL_IsSleep */
        } /* end of loop over all HW channels */
      }
    }
#endif /* C_ENABLE_RX_POLLING */
#if defined(C_ENABLE_RX_QUEUE)
    /* #200 execute RxQueue CanHL_RxQueueExecution() */
    errorId |= CanHL_RxQueueExecution();
#endif
    canRxTaskActive = CAN_FREE;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 3356,3359 */ /* MD_Can_13.7,MD_Can_13.7 */
  { /* Throw DET if an error detected before */ /* PRQA S 3201 */ /* MD_Can_3201 */
    Can_CallDetReportError(CAN_MAINFCT_READ_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
  CanHookEnd_Can_MainFunction_Read();
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_BusOff
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_MainFunction_BusOff
Relation_Context:
Relation:
StatusPolling, DevErrorDetect
StatusPolling, OneChOpt
StatusPolling, Variant
StatusPolling, Wakeup
StatusPolling, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_BusOff( void )
{ /* \trace SPEC-1783, SPEC-3867 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_ERROR_POLLING) /* \trace SPEC-1778, SPEC-3818 */ /* COV_CAN_ERROR_POLLING */
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3835,  SPEC-1780, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if defined(C_ENABLE_MULTI_ECU_CONFIG) /* one controller optimization is always off */ /* COV_CAN_MULTI_ECU_CONFIG */
      if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */ /* \trace SPEC-3962 */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
# if (CAN_EMULATE_SLEEP == STD_ON) /* COV_CAN_EMULATE_SLEEP */
        if ( !CanHL_IsSleep(channel) )
# endif
        { /* #60 do not access CAN hardware in SLEEP */
          { /* #70 loop over all HW controllers and call CanHL_ErrorHandling() \trace SPEC-1772, SPEC-3790 */
            /* #80 disable CAN interrupts */
            Can_DisableControllerInterrupts((uint8)channel);
            CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
            Can_EnableControllerInterrupts((uint8)channel);
          }
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_BO_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
#endif /* C_ENABLE_ERROR_POLLING */
}


/****************************************************************************
| NAME:             Can_MainFunction_Wakeup
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_MainFunction_Wakeup
Relation_Context:
Relation:
WakeupPolling, Wakeup, DevErrorDetect
WakeupPolling, Wakeup, OneChOpt
WakeupPolling, Wakeup, Variant
WakeupPolling, Wakeup, CommonCan
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Wakeup( void )
{ /* \trace SPEC-1770, SPEC-3885 */
  /* ----- Local Variables ---------------------------------------------- */
}

#if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40X) /* COV_CAN_MICROSAR_VERSION */
/****************************************************************************
| NAME:             Can_MainFunction_Mode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_MainFunction_Mode
Relation_Context:
Relation:
DevErrorDetect
OneChOpt
Variant
Wakeup
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Mode( void )
{ /* \trace SPEC-1775 */
  /* ----- Local Variables ---------------------------------------------- */
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1779, SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  endif
  { /* #15 EXCLUSIVE_AREA_6 avoid nesting mode changes (e.g. same API, initialization or BUSOFF) */
    /* ----- Implementation ----------------------------------------------- */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_6);
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0; channel < kCanNumberOfChannels; channel++) /* CM_CAN_HL01 */
#  endif
    { /* #20 over all active controller */
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* one controller optimization is always off */ /* COV_CAN_MULTI_ECU_CONFIG */
      if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
#  elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
#  endif
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */ /* \trace SPEC-1779, SPEC-3962 */
        errorId = CAN_E_UNINIT;
      }
      else
#  endif
      {
        switch (Can_GetStatusReq(channel))
        { /* #55 only one transition request at one time is possible */
          case CAN_REQ_START: /* COV_CAN_TRANSITION_REQUEST_START */
            /* #60 check/handle START transition \trace SPEC-1771 */
            CanHL_StartProcessed(CAN_CHANNEL_CANPARA_ONLY);
            break;
          case CAN_REQ_STOP: /* COV_CAN_TRANSITION_REQUEST_STOP */
            /* #70 check/handle STOP transition \trace SPEC-1771 */
            CanHL_StopProcessed(CAN_CHANNEL_CANPARA_ONLY);
            break;
          case CAN_REQ_NONE:
            break;
          default:
            /* #100 check illegal transition request */
            errorId = CAN_E_TRANSITION;
            break;
        }
      }
    } /* over all channels*/
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_6);
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_MODE_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
} /* PRQA S 6030,6050 */ /* MD_MSR_STCYC,MD_MSR_STCAL */

#endif

/****************************************************************************
| NAME:             Can_CancelTx
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_CancelTx
Relation_Context:
Relation:
TransmitCancellationAPI, CommonCan
TransmitCancellationAPI, DevErrorDetect
TransmitCancellationAPI, TxFullCANSupport
TransmitCancellationAPI, OneChOpt, CommonCan
TransmitCancellationAPI, DevErrorDetect, OneChOpt
TransmitCancellationAPI, DevErrorDetect, Variant
TransmitCancellationAPI, MultiplexedTx, TxFullCANSupport
TransmitCancellationAPI, MultiplexedTx, HwCancelTx
ChannelAmount
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_CancelTx( Can_HwHandleType Hth, PduIdType PduId )
{
  /* ----- Local Variables ---------------------------------------------- */
#if (CAN_CANCEL_SUPPORT_API == STD_ON)
  CAN_CHANNEL_CANTYPE_LOCAL
  Can_HwHandleType txObjHandle;
  CanObjectHandle logTxObjHandle;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if defined(CAN_ENABLE_MICROSAR_VERSION_MSR403) /* COV_CAN_MICROSAR_VERSION */
  if (Hth >= Can_GetSizeOfMailbox())
  { /* #20 Check Hth is in range */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#  endif
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# else
  if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# endif
  { /* #30 Check Hth is FullCAN or BasicCAN */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
# if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Hth);
# endif
    txObjHandle = Can_GetHwHandle(Hth);
    logTxObjHandle = CanHL_GetTxHwToLogHandle(CAN_CHANNEL_CANPARA_FIRST txObjHandle);  
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #40 Check parameter controller is in range */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
    if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 ) /* COV_CAN_GENDATA_FAILURE */
    { /* #50 Check controller is in active ECU */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    { /* #60 Check parameter controller is valid */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
    if (!CanHL_IsControllerInit(channel))
    { /* #70 Check controller is initialized \trace SPEC-3962 */
      errorId = CAN_E_UNINIT;
    }
    else
# endif
    {
      /* ----- Implementation ----------------------------------------------- */
# if defined (C_ENABLE_TX_FULLCAN_OBJECTS)
      if ( Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
# endif
      { /* #100 is BasicCAN */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) /* \trace SPEC-1677, SPEC-3957 */
        uint8_least muxTx;
        uint8_least muxTx_max;
        muxTx_max = CAN_MULTIPLEXED_TX_MAX_OBJ(Hth); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        for (muxTx = 0; muxTx < muxTx_max; muxTx++)
# endif
        { /* #110 over all Multiplexed TX objects - search for handle */
          if (Can_GetActiveSendPdu(logTxObjHandle) == PduId)
          {
            if ((Can_GetActiveSendState(logTxObjHandle) == CAN_SEND_OBJ)
# if defined(C_ENABLE_CANCEL_TX_IN_HW)
                || (Can_GetActiveSendState(logTxObjHandle) == CAN_CANCEL_OBJ)
# endif
                )  /* COV_CAN_CANCEL_SW_STIMULATION */
            { /* #120 PDU found in active send list - handle found */
              Can_SetActiveSendState(logTxObjHandle, CAN_CANCEL_OBJ_SW); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
              /* #130 CANCEL_IN_HW is active - just suppress TX confirmation */
# if defined(C_ENABLE_CANCEL_IN_HW)
              { /* #140 LL TX cancel in HW */ /* \trace SPEC-1690, SPEC-3947 */
                GLOBAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, control) = kTxCodeAbort; /* SBSW_CAN_LL03 */
                
              }
# endif
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
              break;
# endif
            }
          }
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
          logTxObjHandle++;
          txObjHandle++;
# endif
        }
      }
# if defined (C_ENABLE_TX_FULLCAN_OBJECTS)
      else
      { /* #200 is FullCAN */
        if (Can_GetActiveSendPdu(logTxObjHandle) == PduId)
        {
          if ((Can_GetActiveSendState(logTxObjHandle) == CAN_SEND_OBJ)
#  if defined(C_ENABLE_CANCEL_TX_IN_HW)
              || (Can_GetActiveSendState(logTxObjHandle) == CAN_CANCEL_OBJ)
#  endif
             )  /* COV_CAN_CANCEL_SW_STIMULATION */
          { /* #210 mailbox to cancel is valid (PDU, handle, send state OK) */
            Can_SetActiveSendState(logTxObjHandle, CAN_CANCEL_OBJ_SW); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
            /* #220 CANCEL_FULLCAN_IN_HW is active - just suppress TX confirmation */
#  if defined(C_ENABLE_CANCEL_TX_IN_HW)
            { /* #230 LL TX cancel in HW */ /* \trace SPEC-1690, SPEC-3947 */
              GLOBAL_MAILBOX_ACCESS(canHwChannel, txObjHandle, control) = kTxCodeAbort; /* SBSW_CAN_LL03 */
              
            }
#  endif
          }
        }
      }
# endif
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_WRITE_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#else /* CAN_CANCEL_SUPPORT_API == STD_ON */
  CAN_DUMMY_STATEMENT(Hth); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
  CAN_DUMMY_STATEMENT(PduId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif /* CAN_CANCEL_SUPPORT_API == STD_ON */
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_ResetBusOffStart
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_ResetBusOffStart
Relation_Context:
Relation:
BusOffRecovery, DevErrorDetect, OneChOpt
BusOffRecovery, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_ResetBusOffStart( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #40 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* #50 Check controller is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #60 do BUSOFF handling begin by call CanResetBusOffStart() - controller should be stopped afterwards but does not wait for bus transition here */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    CanResetBusOffStart(channel, Can_GetLastInitObject(channel));
# else
    CanResetBusOffStart(Can_GetLastInitObject(channel));
    CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CTRBUSOFF_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#  endif
#else
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif /* ( BUSOFF_SUPPORT_API ) */
}

/****************************************************************************
| NAME:             Can_ResetBusOffEnd
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_ResetBusOffEnd
Relation_Context:
Relation:
BusOffRecovery, DevErrorDetect, OneChOpt
BusOffRecovery, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_ResetBusOffEnd( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(CAN_ENABLE_BUSOFF_SUPPORT_API) /* COV_CAN_BUSOFF_SUPPORT_API */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #40 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* #50 Check controller is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  { /* #60 reset BUSOFF flag do this before CanResetBusOffEnd() so LL may overwrite it */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetIsBusOff(channel,FALSE); /* SBSW_CAN_HL08 */ 
    /* #70 do BUSOFF finish handling by call CanResetBusOffEnd() - controller should be re initialized afterwards */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    CanResetBusOffEnd(channel, Can_GetLastInitObject(channel));
    CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# else
    CanResetBusOffEnd(Can_GetLastInitObject(channel));
    CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CTRBUSOFF_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
#else
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif /* ( BUSOFF_SUPPORT_API ) */
}

#if (CAN_GET_STATUS == STD_ON)
/****************************************************************************
| NAME:             Can_GetStatus
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_GetStatus
Relation_Context:
Relation:
CanGetStatus, CommonCan
CanGetStatus, DevErrorDetect, OneChOpt
CanGetStatus, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, uint8, CODE) Can_GetStatus( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = CAN_STATUS_INCONSISTENT; /* PRQA S 3198 */ /* MD_MSR_14.2 */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if defined(C_ENABLE_MULTI_ECU_CONFIG) /* COV_CAN_MULTI_ECU_CONFIG */
  if ( (cantVIdentityMsk)(Can_GetChannelIdentityAssignment(channel) & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* #40 Check controller is in active ECU */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  elif (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* #50 Check controller is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 set logical state as return value */
    canReturnCode = (uint8)Can_GetLogStatus(channel); /* PRQA S 3198 */ /* MD_MSR_14.2 */
    if ( CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #150 set BUSOFF - BUSOFF can only happen on first HW channel (with TX objects) */
      canReturnCode |= CAN_STATUS_BUSOFF;
    }
# if defined(C_ENABLE_EXTENDED_STATUS) /* COV_CAN_EXTENDED_STATUS */
    {    
      if ( CanLL_HwIsPassive(CAN_HW_CHANNEL_CANPARA_ONLY) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #160 set Error Passive */
        canReturnCode |= CAN_STATUS_PASSIVE;
      }    
      if ( CanLL_HwIsWarning(CAN_HW_CHANNEL_CANPARA_ONLY) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #170 set Error Warning */
        canReturnCode |= CAN_STATUS_WARNING;
      }
    }
# endif /* C_ENABLE_EXTENDED_STATUS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return (uint8)canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if defined(C_ENABLE_MIRROR_MODE)
/****************************************************************************
| NAME:             Can_SetMirrorMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_SetMirrorMode
Relation_Context:
MirrorMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_SetMirrorMode( uint8 Controller , CddMirror_MirrorModeType mirrorMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set mirror mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetMirrorModeState(channel, mirrorMode); /* SBSW_CAN_HL20 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}
#endif

#if defined(C_ENABLE_SILENT_MODE)
/****************************************************************************
| NAME:             Can_SetSilentMode
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_SetSilentMode
Relation_Context:
SilentMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetSilentMode( uint8 Controller, Can_SilentModeType silentMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Std_ReturnType retVal;
  errorId = CAN_E_NO_ERROR;
  retVal = E_NOT_OK;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set mirror mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetSilentModeState(channel, silentMode); /* SBSW_CAN_HL20 */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
  return retVal;
}
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
/****************************************************************************
| NAME:             Can_RamCheckExecute
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_RamCheckExecute
Relation_Context:
RamCheck
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckExecute( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 Do RamCheck by execute Can_InitController() with activated check */
    /* ----- Implementation ----------------------------------------------- */
    CanHL_DoRamCheck(CAN_CHANNEL_CANPARA_ONLY);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}

/****************************************************************************
| NAME:             Can_RamCheckEnableMailbox
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_RamCheckEnableMailbox
Relation_Context:
RamCheck
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckEnableMailbox( Can_HwHandleType htrh )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
  if (htrh >= Can_GetSizeOfMailbox()) { /* CM_CAN_HL28 */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #15 disable controller to force reinitialization afterwards in Can_RamCheckEnableController() */
    Can_SetLogStatus(Can_GetMailboxController(htrh), CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL40 */
    /* #20 reactivate mailbox */
    Can_SetMailboxState(htrh, CAN_ENABLE_OBJ); /* SBSW_CAN_HL34 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}

/****************************************************************************
| NAME:             Can_RamCheckEnableController
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| Can_RamCheckEnableController
Relation_Context:
RamCheck
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckEnableController( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-3962 */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  {

    /* ----- Implementation ----------------------------------------------- */
    /* #30 activate controller only when currently disabled */
    if ( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      /* #40 call Can_InitController() to activate mailboxes and controller after RAM check issue */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(~(CAN_DEACTIVATE_CONTROLLER)));  /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
# if defined(CAN_ENABLE_MICROSAR_VERSION_MSR40) /* COV_CAN_MICROSAR_VERSION */
      Can_InitController((uint8)channel, &Can_GetControllerBaudrateConfig(((uint8)(Can_GetLastInitObject(channel) - (uint8)Can_GetInitObjectStartIndex(channel)) & 0x03u))); /* SBSW_CAN_HL03 */
# else
      Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL03 */
# endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* dummy assignment avoid compiler warning */ /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
}
#endif

#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/****************************************************************************/

/****************************************************************************/
/*  excluded Requirements                                                   */
/****************************************************************************/
/* part of other component: SPEC-1597, SPEC-3898, SPEC-3972 */
/* Currently no use-case / not supported: SPEC-1601, SPEC-3889, SPEC-1592, SPEC-1582 */

/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_Can_Asr_Unused
Misra Rule Major
  Reason: Symbol not needed in each configuration or for each platform/derivative
  Risk: None
  Prevention: None

MD_Can_Asr_0781
Misra Rule 5.6
  Reason: Same name is used for same kind of data
  Risk: None
  Prevention: None

MD_Can_Asr_3408_libCheck
Misra Rule 8.8
  Reason: external linkage used for library check
  Risk: library check failed.
  Prevention: Integration test version check

MD_Can_Asr_3447
Misra Rule 8.8
  Reason: external linkage but not in header file because this is only used for Driver internal
  Risk: Symbolic conflict for other module
  Prevention: module prefix are part of symbol and possible conflicts checked by linker

MD_Can_Asr_3408
Misra Rule 8.8
  Reason: external linkage but not in header file because this is only used for Driver internal
  Risk: Symbolic conflict for other module
  Prevention: module prefix are part of symbol and possible conflicts checked by linker

MD_Can_Asr_3451
Misra Rule 8.8
  Reason: external linked symbol used in more than one file but should not be declared in header to prevent a external visibility
  Risk: different declaration of same object
  Prevention: possible conflicts checked by linker

MD_Can_Asr_3353_logTxobjHandle
Misra Rule 9.1
  Reason: Because CAN_MULTIPLEXED_TX_MAX is at least 1 the variable logTxobjHandle_use is always set before
  Risk: None
  Prevention: None

MD_Can_Asr_3353_CommonCanTransition
Misra Rule 9.1
  Reason: TransitionDone will be set depend on CommonCAN loop usage. Because CommonCAN loop will always be entered the value will be set.
  Risk: None
  Prevention: None

MD_Can_Asr_3418
Misra Rule 12.10
  Reason: comma operator in for-loop header used to get a compact code
  Risk: None
  Prevention: None

MD_Can_Asr_2018
Misra Rule 14.1
  Reason: default case is not necessary for all configurations
  Risk: None
  Prevention: None

MD_Can_Asr_3219
Misra Rule 14.1
  Reason: static function is not used depend on configuration aspect. No preprocessor used here to avoid unreadable code.
  Risk: None
  Prevention: None

MD_Can_Asr_2004
Misra Rule 14.10
  Reason: no default handling needed for if-else-if here
  Risk: missing default handling
  Prevention: Review

MD_Can_Asr_0881_abstract
Misra Rule 19.12
  Reason: Compiler abstraction need replacement of classes to avoid name conflict. Order of ## operator is irrelevant here.
  Risk: None
  Prevention: None

MD_Can_Asr_3689_MuxTx
Misra Rule 21.1
  Reason: muxTx index seems to be out of bounds for the array canTxBasicDataBuffer but it is limited to maximum size of array.
  Risk: None
  Prevention: Review

MD_Can_Asr_STPTH
Misra Metric STPTH
  Reason: control structure to evaluate ErrorId used sequential instead of nested to increase readability. PTH is 128 times lower than the worst case value from QAC.
  Risk: None
  Prevention: Review

MD_Can_3436:
Major
  Reason: Compatibility define used here.
  Risk: name conflict.
  Prevention: Code review and compiler check for name conflicts.

MD_Can_3198:
Redundancy
  Reason: Explicit variable initialization for robustness reasons.
  Risk: None.
  Prevention: None.

MD_Can_3199_dummy:
Redundancy
  Reason: Dummy assignment used to satisfy API parameters that are never used.
  Risk: None.
  Prevention: None.

MD_Can_0715:
Misra Rule 1.1
  Reason: Complex code structure used and not split in modules or functions to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_Can_0828:
Misra Rule 1.1
  Reason: Nesting of #if statements bigger than 8 depends on configuration aspects.
  Risk: Compiler does not support that.
  Prevention: Used Compilers checked and limitations form ANSI is not relevant.

MD_Can_0857:
Misra Rule 1.1
  Reason: Macros used to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_Can_0505:
Misra Rule 1.2
  Reason: Assertion prevents dereferencing a NULL pointer.
  Risk: Undefined behaviour.
  Prevention: Code inspection.

MD_Can_0277_negation:
Misra Rule 3.1
  Reason: Negation of an unsigned value used to mask bits.
  Risk: None.
  Prevention: None.

MD_Can_0277_invalid:
Misra Rule 3.1
  Reason: Define a invalid value by use highest value of the given data type.
  Risk: None.
  Prevention: None.

MD_Can_0777:
Misra Rule 5.1
  Reason: Naming pattern leads to identifiers that are not distinct in the first 31 characters.
  Risk: Name conflicts and portability problems.
  Prevention: Verify correct behavior for used platforms/compilers in the component test.

MD_Can_0781:
Misra Rule 5.6
  Reason: Use same identifiers for variables and struct members as part of the HL-LL interface to indicate the same information.
  Risk: Misusage of the identifiers.
  Prevention: Code inspection and test of the different variants in the component test to verify that the identifiers are used according to the defined interface.

MD_Can_3218:
Misra Rule 8.7
  Reason: The usage of variables depend on configuration aspects and may be used only once, or defined global to improve overview.
  Risk: Name conflict.
  Prevention: Compiler optimize and check for name conflicts.

MD_Can_3207:
Misra Rule 8.7
  Reason: The usage of variables depend on configuration aspects and may be used or not once in this particular configuration.
  Risk: Unnecessary RAM occupied.
  Prevention: Compiler optimize and check for name conflicts.

MD_Can_3408_extLinkage:
Misra Rule 8.8
  Reason: Declaration of generated data is only internal to restrict visibility.
  Risk: None.
  Prevention: None.

MD_Can_3447:
Misra Rule 8.8
  Reason: This appears only in internal test configurations.
  Risk: Symbolic conflict for other module.
  Prevention: None.

MD_Can_3684:
Misra Rule 8.12
  Reason: Arrays declared without size, because size depends on configuration and is unknown here, especially for linktime tables.
  Risk: Data access outside table.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3760_LogToHw:
Misra Rule 10.01
  Reason: Calculating hardware index out of logical need a negative value in calcuation, but result is always positive.
  Risk: Data access out of bounce.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_1281:
Misra Rule 10.6
  Reason: Type of casting variable can be configured.
  Risk: Wrong size of data type could be used.
  Prevention: Code inspection.

MD_Can_0303_HWaccess:
Misra Rule 11.3
  Reason: Hardware access need pointer to CAN cell as volatile.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.

MD_Can_0310:
Misra Rule 11.4
  Reason: Cast increase performance here.
  Risk: pointer Alignment does not fit and wrong memory is accessed.
  Prevention: Code inspection and component test.

MD_Can_0311:
Misra Rule 11.5
  Reason: Const pointer used only for read access. Same macro is used also for none const pointer.
  Risk: None.
  Prevention: None.

MD_Can_0312:
Misra Rule 11.5
  Reason: Cast to none volatile pointer is ok here because usage of data is read only here.
  Risk: Upper Layer has to make sure that there is no write access to this data.
  Prevention: Documentation of API.

MD_Can_13.7:
Misra Rule 13.7
  Reason: Result or value is always true or false depend on configuration aspect and used platform specific implementation.
  Risk: Incorrect platform specific return will be ignored.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3201:
Misra Rule 14.1
  Reason: Configuration or platform specific dependent unreachable code.
  Risk: Incorrect behavior depend on settings.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3325:
Misra Rule 14.1
  Reason: This control expression is always true or false depend on configuration aspect and used platform specific implementation.
  Risk: Incorrect behavior depend on settings.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3109:
Misra Rule 14.3
  Reason: Empty statements occur multiple times because macros used like functions, and configuration aspects may deactivate complete functionality.
  Risk: Functionality unexpected missing.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_2001:
Misra Rule 14.4
  Reason: 'goto' statement used to optimize code (readability and runtime).
  Risk: Incorrect jump.
  Prevention: Code inspection.

MD_Can_0770:
Misra Rule 14.5
  Reason: 'continue' statement used to optimize code (readability and runtime).
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_Can_14.6:
Misra Rule 14.6
  Reason: Multiple break used for optimize code runtime.
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_Can_2006:
Misra Rule 14.7
  Reason: Multiple return path used to optimize code (readability and runtime).
  Risk: Return a function too soon.
  Prevention: Code inspection.

MD_Can_1330:
Misra Rule 16.4
  Reason: No impact on functionality, due to different configurations the function paramters can be different.
  Risk: Traceability could be diffcult.
  Prevention: Code inspection.

MD_Can_1334:
Misra Rule 16.4
  Reason: No impact on functionality, due to different configurations the function paramters can be different.
  Risk: Traceability could be diffcult.
  Prevention: Code inspection.

MD_Can_3673:
Misra Rule 16.7
  Reason: No change due to compatibility of the API.
  Risk: Data could be modified without intention.
  Prevention: Code inspection.

MD_Can_17.4:
Misra Rule 17.4
  Reason: Pointer arithmetic used multiple times to optimize runtime.
  Risk: Access wrong memory.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_0750:
Misra Rule 18.4
  Reason: Using union type to handel configuration specific data access.
  Risk: Misinterpreted data.
  Prevention: Code inspection.

MD_Can_0759:
Misra Rule 18.4
  Reason: Using union type to handle configuration specific data access.
  Risk: Misinterpreted data.
  Prevention: Code inspection.

MD_Can_3412:
Misra Rule 19.4
  Reason: Complex Macros with unrecognised code-fragment used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_3458:
Misra Rule 19.4
  Reason:Complex Macros with unbraced code statement blocks used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_3460:
Misra Rule 19.4
  Reason: 'void' used as macro to get configuration specific API.
  Risk: Readability reduced.
  Prevention: Compile test.

MD_Can_0841:
Misra Rule 19.6
  Reason:Undefine macro for compatibility reasons and re-usage of platform specific code.
  Risk: Meaning of macro is uncertain and may lead to wrong implementation.
  Prevention: Code inspection, compile tests and runtime tests.

MD_Can_3453:
Misra Rule 19.7
  Reason: Complex Macros used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_0850:
Misra Rule 19.8
  Reason: Macro argument is empty depend on usage of compiler abstraction.
  Risk: None.
  Prevention: Code inspection.

MD_Can_3410:
Misra Rule 19.10
  Reason: Parameter used in structures that does not allow brackets.
  Risk: None atomic parameter lead to compile errors.
  Prevention: Used parameter is always atomic depend on usage.

MD_Can_0342:
Misra Rule 19.13
  Reason: Glue operator used to abstract AuotSar compiler abstraction.
  Risk: Only K&R compiler support glue operator.
  Prevention: Compile test show whether compiler accept glue operator.

MD_Can_0291:
Misra Rule 21.1
  Reason: 'if' query prevents negative arithmetic result.
  Risk: Index of array could be negative and therefore undefined.
  Prevention: Code inspection.

MD_Can_3382:
Misra Rule 21.1
  Reason: 'if' query prevents overflow arithmetic result.
  Risk: Index of array could exceed dimension (due to overflow) and therefore undefined.
  Prevention: Code inspection.

MD_Can_3689:
Misra Rule 21.1
  Reason: Assertion prevents out of bound indexing.
  Risk: Undefined behaviour.
  Prevention: Code inspection. Index cannot exceed the maximum dimension of the array.


MD_Can_0306_HWaccess:
Misra Rule 11.3
  Reason:    Hardware access need pointer to CAN cell as integral type.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.

MD_Can_3408_LL:
Misra Rule 8.8
  Reason: external linkage but not in header file because this is only used for Driver internal
  Risk: Symbolic conflict for other module
  Prevention: module prefix are part of symbol and possible conflicts checked by linker

MD_Can_3415_LL_RHsideEffect:
Misra Rule 12.4
  Reason: Right hand side evaluation does not need to take place in the case where the left hand side evaluates to false.
  Risk: Right hand evaluation might include important necessary code
  Prevention: Code review and runtime tests

MD_Can_0488_LL:
Misra Rule 17.4
  Reason: performing pointer arithmetic
  Risk: Segmentation faults or storage violations
  Prevention: Code review and runtime tests
  
MD_Can_0489_LL:
Misra Rule 17.4
  Reason: Increment or decrement operation performed on pointer
  Risk: Segmentation faults or storage violations
  Prevention: Code review and runtime tests
  
MD_Can_3353_LL_canFDTxBuf:
Misra Rule 9.1
  Reason: The variable canFDTxBuf is always set before used
  Risk: None
  Prevention: Code review and runtime tests
  
MD_Can_3197_LL:
  Reason: The initialiser for 'loopResult' is always modified before being used. 
  Risk: None
  Prevention: Code review and runtime tests
  
MD_Can_3689_LL_objHandle:
Misra Rule 21.1
  Reason: objHandle seems to be out of bounds for the array canObject but it is limited to maximum size of array
  Risk: None
  Prevention: Code review and runtime tests
  
MD_Can_3305_LL:
  Reason: Pointer cast to stricter alignment. Cast corresponds to alignment requirements of supported compilers. 
  Risk: None
  Prevention: Code review and runtime tests
  
MD_Can_0290_LL:
Misra Rule 21.1
  Reason: bit negation of unsigned varible and assign to register
  Risk: None
  Prevention: Code review and runtime tests
*/

/****************************************************************************/
/*  Silent deviations                                                       */
/****************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CAN_HL01
 \DESCRIPTION Write access to CanStatusReq with controller as index. Controller index is checked against sizeof CanStatusReq in Can_SetControllerMode(), Can_RamCheckExecute(), Can_MainFunction_Mode(), Can_Init() and Can_InitController().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL02
 \DESCRIPTION Write access to CanLogStatus with controller as index. Controller index is checked against sizeof CanLogStatus in Can_SetControllerMode(), CanHL_ErrorHandling(), Can_RamCheckEnableController(), Can_MainFunction_Mode(), Can_Init() and Can_InitController().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL03
 \DESCRIPTION Call Can_InitController() with parameter configuration pointer, which is never been used within MSR403. Error directive ensures that preprocessor switch MSR403 is set in SafeBSW context.
 \COUNTERMEASURE \N The configuration pointer is never used in called function (only used for MSR401 to get data).

\ID SBSW_CAN_HL04
 \DESCRIPTION Write access to CanActiveSendState with logTxObjHandle as index. LogTxObjHandle is checked against size of ActiveSendObject in Can_CleanUpSendState(), CanHL_WritePrepare(), CanHL_InitTxFullCAN(), CanHL_InitTxBasicCAN(), CanHL_TxTaskCancelationHandling(), CanHL_TxConfirmation() and Can_CancelTx().
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL05
 \DESCRIPTION Write access to CanActiveSendPdu with logTxObjHandle as index. LogTxObjHandle is checked against size of ActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL06
 \DESCRIPTION Call Can_GenericPrecopy() with parameter data pointer. The data pointer is only used for read access and it is always a valid pointer (module local defined).
 \COUNTERMEASURE \R [CM_CAN_HL25]

\ID SBSW_CAN_HL07
 \DESCRIPTION Call CanIf_RxIndication() with parameter data pointer. The data pointer is only used for read access. Parameter is of type P2CONST in API.
 \COUNTERMEASURE \R [CM_CAN_HL25]

\ID SBSW_CAN_HL08
 \DESCRIPTION Write access to CanIsBusOff with controller as index. Controller index is checked against sizeof CanIsBusOff in Can_SetControllerMode(), CanHL_ErrorHandling() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL09
 \DESCRIPTION Write access to CanIsWakeup with controller as index. Controller index is checked against sizeof CanIsWakeup in CanHL_WakeUpHandling(), Can_CheckWakeup(), Can_InitController() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL10
 \DESCRIPTION Write access to VersionInfo pointer within function Can_GetVersionInfo()
 \COUNTERMEASURE \N caller of Can_GetVersionInfo() has to ensure that VersionInfo pointer is valid. (global description available)

\ID SBSW_CAN_HL11
 \DESCRIPTION Write access to CanLastInitObject with controller as index. Controller index is checked against sizeof CanLastInitObject in Can_InitStruct(), Can_ChangeBaudrate(), Can_SetBaudrate() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL12
 \DESCRIPTION Write access to CanInterruptCounter with controller as index. Controller index is checked against sizeof CanInterruptCounter in Can_Init(), Can_EnableControllerInterrupts() and Can_DisableControllerInterrupts()
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL13
 \DESCRIPTION Write access to CanTimeoutCall with controller as index. Controller index is checked against sizeof CanTimeoutCall in Can_Init(), Can_SetControllerMode() and Can_Mainfunction_Mode().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL14
 \DESCRIPTION Write access to CanIsHardwareCanceled with controller as index. Controller index is checked against sizeof CanIsHardwareCanceled in Can_Init(), Can_SetControllerMode(), Can_SetBaudrate() and ApplCanTimerLoop().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL15
 \DESCRIPTION Write access to CanLoopTimeout with controller and source as index. Controller index is checked against sizeof CanLoopTimeout.
 \COUNTERMEASURE \R [CM_CAN_HL01]
                 \R [CM_CAN_HL22]

\ID SBSW_CAN_HL16
 \DESCRIPTION Call CanLL_CanInterruptDisable() with parameter CanInterruptOldStatus as pointer (compiler secures used type in function declaration fitting to given pointer parameter type).
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL17
 \DESCRIPTION Call CanHL_SortlogTxObjHandlePrioList() with parameter logTxObjHandlePrioList as pointer (module local defined).
 \COUNTERMEASURE \N [CM_CAN_HL19]

\ID SBSW_CAN_HL18
 \DESCRIPTION Write access to CanRxQueueBuffer with queue write index. Write index is checked against size of CanRxQueueBuffer.
 \COUNTERMEASURE \R [CM_CAN_HL24]

\ID SBSW_CAN_HL19
 \DESCRIPTION Write access to CanRxQueueBuffer.data with queue write index and data index. Write index is checked against size of CanRxQueueBuffer. (see also generator CM_CAN_HL04 qualified use case CSL02)
 \COUNTERMEASURE \R [CM_CAN_HL24]
                 \R [CM_CAN_HL17]

\ID SBSW_CAN_HL20
 \DESCRIPTION Write access to CanMirrorModeState with controller as index. Controller is checked against size of CanMirrorModeState.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL21
 \DESCRIPTION Write access to logTxObjHandlePrioList with muxTx as index. Index is checked against size of logTxObjHandlePrioList.
 \COUNTERMEASURE \R [CM_CAN_HL19]

\ID SBSW_CAN_HL22
 \DESCRIPTION Write access to CanTxBasicDataBuffer with controller, muxTx and dataByte as index. Controller Index is checked against size of CanTxBasicDataBuffer (first dimension). Second dimension is statically defined CAN_MULTIPLEXED_TX_MAX and given as user type in ComStackLib. Third dimension is checked against size of table.
 \COUNTERMEASURE \R [CM_CAN_HL01]
                 \R [CM_CAN_HL20]

\ID SBSW_CAN_HL23
 \DESCRIPTION Write access to CanActiveSendPduInfo with logTxObjHandle as index. LogTxObjHandle is checked against size of CanActiveSendPduInfo.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL24
 \DESCRIPTION Call Appl_GenericPreTransmit() with parameter PduInfoPtr_var pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL25
 \DESCRIPTION Call CanIf_CancelTxConfirmation() with parameter CanActiveSendPduInfo[logTxObjHandle] as pointer (module local defined).
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL26
 \DESCRIPTION Call CanHL_RxBasicMsgReceivedBegin(), CanHL_RxBasicMsgReceivedSearch(), CanHL_RxMsgReceivedNotification() and CanHL_RxBasicMsgReceivedEnd() with parameter rxBasicInfo pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL27
 \DESCRIPTION Call CanHL_RxFullMsgReceivedBegin(), CanHL_RxFullMsgReceivedSearch(), CanHL_RxFullReceivedNotification() and CanHL_RxFullMsgReceivedEnd() with parameter rxFullInfo pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL28
 \DESCRIPTION Call CanHL_WritePrepare(), CanHL_WriteStart() and CanHL_WritePrepareCancelTx() with parameter PduInfo pointer secured by caller part of Can_Write() description.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter.

\ID SBSW_CAN_HL29
 \DESCRIPTION Write access to rxBasicInfo (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL30
 \DESCRIPTION Write access to rxFullInfo (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL31
 \DESCRIPTION Call Initialization subroutines with initInfo pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL32
 \DESCRIPTION Call Appl_GenericConfirmation with canPdu pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL33
 \DESCRIPTION Write access to CanBusOffCounter with controller as index. Controller index is checked against sizeof CanBusOffCounter in Can_SetControllerMode(), CanHL_ErrorHandling() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL34
 \DESCRIPTION Write access to CanMailboxState with mailbox handle as index. Index secured by ComStackLib [CM_CAN_HL29] and [CM_CAN_HL30] and checked against size of CanMailboxState.
 \COUNTERMEASURE \R [CM_CAN_HL28]

\ID SBSW_CAN_HL35
 \DESCRIPTION Call with pointer to CAN cell register for write and read access.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter.

\ID SBSW_CAN_HL36
 \DESCRIPTION Write access to initInfo structure as pointer (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL37
 \DESCRIPTION Call GetElapsedValue with timer value pointers as parameter (module local defined).
 \COUNTERMEASURE \N The timer values are static and always valid.

\ID SBSW_CAN_HL38
 \DESCRIPTION Call GetCounterValue with timer value pointers as parameter. definition of kCanLoopXXX as index in LoopTimeout table is always smaller than the dimension of the table given as static user type in ComStackLib.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL39
 \DESCRIPTION Undefine preprocessor switch to stimulate user defined feature (only test purpose).
 \COUNTERMEASURE \N Redefinement activates a none documented feature.

\ID SBSW_CAN_HL40
 \DESCRIPTION Write access to CanLogStatus with controller as index. Controller is secured by qualified use-case CSL03 of ComStackLib.
 \COUNTERMEASURE \N [CM_CAN_HL02]

\ID SBSW_CAN_HL41
 \DESCRIPTION Write access to CanActiveSendState with logTxObjHandle as index. logTxObjHandle is temporary stored in a list of [1,3] elements where each element is initialized to a valid value and always written with size check before.
 \COUNTERMEASURE \R [CM_CAN_HL03]



\ID SBSW_CAN_LL01
 \DESCRIPTION Access to a hardware register (Global section) of the FlexCAN module using a pointer access. Pointer is derived using channel as index. Channel is checked by caller. (see also generator CM_CAN_LL10 qualified use case CSL02)
 \COUNTERMEASURE \R [CM_CAN_LL03]
                 \R [CM_CAN_LL05]
                 \S [CM_CAN_LL06]
                 \R [CM_CAN_LL08]

\ID SBSW_CAN_LL02
 \DESCRIPTION Write access to CanStartModeRequested with channel as index.
 \COUNTERMEASURE \R [CM_CAN_LL03]

\ID SBSW_CAN_LL03
 \DESCRIPTION Access to a hardware register (mailbox section) of the FlexCAN module using a structure access. In addition it is referenced by the global FlexCAN module pointer that refernces the channel.
 \COUNTERMEASURE \R [CM_CAN_LL03]
                 \R [CM_CAN_LL04]
                 \R [CM_CAN_LL05]
                 \S [CM_CAN_LL06]
                 \R [CM_CAN_LL08]
                 \S [CM_CAN_LL11]

\ID SBSW_CAN_LL04
 \DESCRIPTION Write access to canTxBuf with dedicated integers as index.
 \COUNTERMEASURE \N Type of static CanTxBuf structure.

 \ID SBSW_CAN_LL05
 \DESCRIPTION Write access to generated CanRxMsgBuffer with channel as index.
 \COUNTERMEASURE \R [CM_CAN_LL01]
                 \R [CM_CAN_LL03]
                 \R [CM_CAN_LL08]
                 \R [CM_CAN_LL09]

\ID SBSW_CAN_LL06
 \DESCRIPTION Write access to localInterruptOldFlagPtr.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter. See SBSW_CAN_HL16.

\ID SBSW_CAN_LL07
 \DESCRIPTION Call GetCounterValue with timer index as parameter.
 \COUNTERMEASURE \R [CM_CAN_LL02]

\ID SBSW_CAN_LL08
 \DESCRIPTION Write access to section of the FlexCAN using a pointer derived from the FlexCAN module's base address (RXFIFO, CanRxMask, CanGlitchFilter, CanParityCheck, DebugRegister, CanFDRegister, IndivRxMask).
 \COUNTERMEASURE \R [CM_CAN_LL03]
                 \R [CM_CAN_LL04]
                 \R [CM_CAN_LL05]
                 \S [CM_CAN_LL06]

\ID SBSW_CAN_LL09
 \DESCRIPTION Access to a hardware register (Global section) of the FlexCAN module using a structure access. Pointer is stored in initInfo structure. (See SBSW_CAN_HL29)
 \COUNTERMEASURE \R [CM_CAN_LL03]
                 \R [CM_CAN_LL05]
                 \S [CM_CAN_LL06]
                 \R [CM_CAN_LL07]
                 \R [CM_CAN_LL08]

\ID SBSW_CAN_LL10
 \DESCRIPTION Write access to canFDTxBuf with index.
 \COUNTERMEASURE \N pduInfo_var_dli never exceeds maximum value of 64 bytes (this is secured by core: Can_DliToBytesMap, Can_BytesToDliMap). Thus it is ensured that sduWordLen and dataWordLen never exceeds size of canFDTxBuf.

\ID SBSW_CAN_LL11
 \DESCRIPTION Write access to canFDTxBuf with unsecured maximum value from caller.
 \COUNTERMEASURE \R [CM_CAN_LL13]

\ID SBSW_CAN_LL12
 \DESCRIPTION Write access to canFDTxBuf with index .
 \COUNTERMEASURE \R [CM_CAN_LL12]

\ID SBSW_CAN_LL13
 \DESCRIPTION Write access to canTxBuf with static index.
 \COUNTERMEASURE \N the memory access is warranty by the static index used (0,1).


SBSW_JUSTIFICATION_END */

/* Counter measurement description

\CM_CAN_HL01 A runtime check ensures controller index is always smaller than number of elements in arrays with controller amount as dimension (Qualified use-case CSL01 of ComStackLib size of ControllerData).
\CM_CAN_HL02 Qualified use-case CSL03 of ComStackLib (CanMailbox.ControllerConfigIdx is always in range of controller ControllerData)
\CM_CAN_HL03 A runtime check ensures logObjHandle is in valid range for Can_ActiveSendObject table (Qualified use-case CSL01 of ComStackLib - Can_ActiveSendObject size is extended by CAN_MULTIPLEXED_TX_MAX within generator to allow an access to logObjHandle+CAN_MULTIPLEXED_TX_MAX).
\CM_CAN_HL04 Qualified use-case CSL02 of ComStackLib (size of CanTxBasicDataBuffer == size of ControllerData).
\CM_CAN_HL17 A runtime check ensures DLC index is always smaller than the dimension of CanRxQueueBuffer.data.
\CM_CAN_HL18 A runtime check ensures HRH values is always in range of start stop index of the given mailbox type. (Qualified use-case CSL03 of ComStackLib - start-stop index fit to mailbox entrys)
\CM_CAN_HL19 Static defined size of logTxObjHandlePrioList (muxTx limited to 1 or 3 by preprocessor define), or pointer to this static variable used.
\CM_CAN_HL20 A runtime check ensures size of CanTxBasicDataBuffer (dataByte). For CAN-FD it is checked against the size of the table. For none CAN-FD size is checked against 8 as defined.
\CM_CAN_HL22 A runtime check ensures source index for LoopTimeout array is always smaller than the dimension of LoopTimeout.
\CM_CAN_HL24 A runtime check ensures RxQueue write index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM_CAN_HL25 A runtime check ensures RxQueue read index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM_CAN_HL28 A runtime check ensures htrh index is always smaller than the dimension of CanMailboxState (Qualified use-case CSL01 of ComStackLib).
\CM_CAN_HL29 Qualified use-case CSL02 of ComStackLib (size of CanMailboxState == size of CanMailbox) 
\CM_CAN_HL30 Qualified use-case CSL03 of ComStackLib (CanMailbox - CanController Start/Stop HtrhIndex).


\CM_CAN_LL01 CanRxMsgBuffer size is checked during PowerOnInit against static defined size and is secured by a DET; canConfigInitFlag is set to CAN_STATUS_UNINIT.
\CM_CAN_LL02 Loop timeout is checked during PowerOnInit against maximum value CAN_MAX_LOOP) and is secured by a DET; canConfigInitFlag is set to CAN_STATUS_UNINIT.
\CM_CAN_LL03 Is covered by CM_CAN_HL01: A runtime check ensures controller index is always smaller than number of elements in arrays with controller amount as dimension (Qualified use-case CSL01 of ComStackLib size of ControllerData).
\CM_CAN_LL04 HwObjHandle for mailbox and individual receive masks index is secured by a runtime check and in addition it is secured by a DET.
\CM_CAN_LL05 TCASE-429: Code inspection ensures that the defined access structures match the memory structure of the FlexCAN module.
\CM_CAN_LL06 User must verify that the generated base address(es) for the FlexCAN controller matches to the used derivative (see SMI-192320).
\CM_CAN_LL07 Access to initInfo structure is secured by caller. See SBSW_CAN_HL36.
\CM_CAN_LL08 channel number is checked in interrupt (runtime check). In addition it is secured by a DET.
\CM_CAN_LL09 CanRxMsgBuffer size is checked during PowerOnInit and is secured by a DET; canConfigInitFlag is set to CAN_STATUS_UNINIT.
\CM_CAN_LL10 Qualified use-case CSL02 of ComStackLib (size of Can_GetBaseAddressOfControllerConfig == size of CanControllerData).
\CM_CAN_LL11 User must verify that the generated mailbox addresses in case of FD mode 2 matches the address range of the used derivative (see SMI-192320).
\CM_CAN_LL12 CANFD_MAILBOX_MAX_WORD_LENGTH() is checked during PowerOnInit against static defined size and is secured by a DET; canConfigInitFlag is set to CAN_STATUS_UNINIT.
\CM_CAN_LL13 sduLen is restricted to maximum buffer size


*/

/****************************************************************************/
/*  Coverage Justification                                                  */
/****************************************************************************/
/* START_COVERAGE_JUSTIFICATION

\ID COV_CAN_MISRA
  \ACCEPT XF
  \ACCEPT TX
  \REASON only used for MISRA analysis not active in production code.

\ID COV_CAN_COMPATIBILITY
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX xf xf
  \ACCEPT XF tf tf
  \REASON The condition checks whether a switch is defined and conditionally assigns a default value. This is used to ensure compatibility to older AUTOSAR/Component versions. 

\ID COV_CAN_INTERNAL
  \ACCEPT XF
  \ACCEPT TX
  \REASON This switch is always active within CAN driver context. Secure visibility of internal interface and cannot be stimulated to off while test. The code is verified by code inspection.

\ID COV_CAN_USER_CONFIG
  \ACCEPT TX
  \REASON This switch is used to ensure compatibility to none Vector stacks. It will be deactivated on demand in a special integration SIP. The code is verified by code inspection.

\ID COV_CAN_CANCEL_SW_STIMULATION
  \ACCEPT TF
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TF tf xf
  \REASON It is not possible to stimulate a sw cancellation while the message is already start to send when hw cancellation is active. The code is verified by code inspection.

\ID COV_CAN_MICROSAR_VERSION
  \ACCEPT TX
  \ACCEPT TX tx tx
  \ACCEPT TX tx xf
  \ACCEPT TX xf tx
  \ACCEPT TX xf xf
  \ACCEPT TX tx tf
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT TF tx tf
  \ACCEPT TF xf tf
  \ACCEPT TF tf tx
  \REASON The MicroSar version is not changeable in a project. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_MULTI_ECU_CONFIG
  \ACCEPT XF
  \REASON The feature Multiple ECU Configurations is not supported for MSR403 but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_AMD_RUNTIME_MEASUREMENT
  \ACCEPT XF
  \REASON The feature AMD Runtime Measurement is not supported for SafeBSW but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_DEV_TIMEOUT_DETECT
  \ACCEPT XF
  \REASON The feature Develop Timeout Detect is not supported for SafeBSW but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_BUSOFF_SUPPORT_API
  \ACCEPT TX
  \ACCEPT XF
  \REASON The feature Busoff Support API is not supported for SafeBSW but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_EXTENDED_STATE_MACHINE
  \ACCEPT XF
  \REASON The feature Extended State Machine is not supported for SafeBSW but will be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_DYNAMIC_FULLCAN_ID
  \ACCEPT TX
  \ACCEPT XF
  \REASON The feature Dynamic FullCAN ID is always supported for SafeBSW but may be not used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_FINALMAGICNUMBER
  \ACCEPT TX
  \REASON Switch is always true is OK here no side effect will occur when switch is false verified by review.

\ID COV_CAN_SAFE_BSW_EXCLUSION
  \ACCEPT XF xf tx xf tx xf xf xf xf xf xf tx xf tx
  \REASON SafeBsw restricted feature will not be enforced to be deactivated or activated.

\ID COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \REASON BUSOFF not stimulated in each configruation. The behavior does not depend on each configuration variant but TCASE-274 takes long runtime and will not be executed for each configuration.   

\ID COV_CAN_WAKEUP_CHANNEL_NOT_IN_ALL_CONFIG
  \ACCEPT XF
  \ACCEPT TX
  \REASON Wakeup may be always activated or deactivated depend on configuration. Not all configurations contain activated or deactivated wakeup for at least one controller, but is sufficiantly tested in some configuations with both settings.

---------------- LL ------------------


\ID COV_CAN_GEN_HW_START_STOP_IDX
  \ACCEPT TX
  \REASON The feature GEN_HW_START_STOP is always supported for SafeBSW but may be not used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_PARTIAL_NETWORK
  \ACCEPT XF
  \REASON The feature Partial Network is not supported for SafeBSW but be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_MULTIPLE_BASICCAN_TX
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_SLEEP_SUPPORT
  \ACCEPT XF
  \REASON The feature is platform specific - always inactive.

\ID COV_CAN_WAKEUP_SUPPORT
  \ACCEPT XF
  \ACCEPT XF xf xf
  \REASON The feature is platform specific - always inactive.

\ID COV_CAN_EMULATE_SLEEP
  \ACCEPT TX
  \ACCEPT TX tf tx
  \ACCEPT TX tx tx
  \ACCEPT TX xf tx
  \ACCEPT XF
  \REASON The feature Emulated Sleep is always supported for SafeBSW but used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_TX_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_BASICCAN_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_FULLCAN_POLLING
  \ACCEPT TF
  \REASON The feature configuration specific - fully supported.

\ID COV_CAN_ERROR_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_WAKEUP_POLLING
  \ACCEPT XF
  \REASON The feature is platform specific - always inactive.

\ID COV_CAN_INDIVIDUAL_POLLING
  \ACCEPT TF
  \REASON The feature is platform and Project specific.

\ID COV_CAN_TX_POLLING_OR_CANCEL_IN_HW_TASK
  \ACCEPT TF tf tf tx
  \ACCEPT TF tf tf xf
  \REASON The feature is platform specific - C_HL_ENABLE_CANCEL_IN_HW_TASK is always true or false.

\ID COV_CAN_GENERIC_CONFIRMATION_API2
  \ACCEPT TF
  \REASON The feature is platform and Project specific - fully supported.

\ID COV_CAN_FD_SUPPORT
  \ACCEPT TF
  \REASON The feature is platform and Project specific - fully supported.

\ID COV_CAN_MULTIPLE_BASICCAN
  \ACCEPT TF
  \REASON The feature is platform and Project specific - fully supported.

\ID COV_CAN_TX_FULLCAN_OBJECTS
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_FULLCAN_OBJECTS
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_HW_TRANSMIT_CANCELLATION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_CANCEL_IN_HW
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_HARDWARE_CANCELLATION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_EXTENDED_ID
  \ACCEPT TF
  \ACCEPT TX
  \ACCEPT XF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_MIXED_ID
  \ACCEPT TF
  \ACCEPT TX
  \ACCEPT XF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_SECURE_TEMP_BUFFER
  \ACCEPT XF
  \REASON The feature is platform specific - always inactive.

\ID COV_CAN_COMMON_CAN
  \ACCEPT XF
  \REASON The feature is platform specific - always inactive.

\ID COV_CAN_OVERRUN_NOTIFICATION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_MULTIPLEXED_TRANSMISSION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_QUEUE
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_TXINDIRECTIONHWTOLOG
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_HW_LAYOUT_TXBASIC_FIRST
  \ACCEPT TX
  \REASON The feature is platform specific - always activated.

\ID COV_CAN_TX_FULLCAN_HWHANDLE_REVERSE
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_RX_FULLCAN_HWHANDLE_REVERSE
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_BASICCAN_HWHANDLE_REVERSE
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_EXTENDED_STATUS
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_OVERRUN_IN_STATUS
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_RxBasicMsgReceivedBegin
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_RxFullMsgReceivedBegin
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_HW_EXIT_TRANSMIT
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_HARDWARE_FAILURE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT TF tf xf
  \ACCEPT TF tf tx
  \ACCEPT TF tx tf
  \REASON The condition checks for hardware failures that cannot be stimulated. The code is verified by code inspection.

\ID COV_CAN_GENDATA_FAILURE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT TF tf xf
  \REASON The condition checks for generated data failures that cannot be simulated. The code is verified by code inspection.

\ID COV_CAN_GENDATA_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF
  \REASON Generated data does not contain all data sets but checked in code. Not encapsulated with preprocessor switch to simplify code.

\ID COV_CAN_OS_USAGE
  \ACCEPT TX
  \ACCEPT TX xf tx
  \ACCEPT TX tx xf
  \ACCEPT TX xf tf
  \ACCEPT TF tf tf
  \ACCEPT TF tx tf
  \ACCEPT TF xf tx
  \ACCEPT TF xf xf
  \ACCEPT XF
  \ACCEPT TF
  \ACCEPT XF xf tx
  \ACCEPT XF xf tf
  \REASON Os may be used in component test or not. The code is verified by code inspection.

\ID COV_CAN_LOCK_ISR_BY_APPL
  \ACCEPT TX tf tf
  \ACCEPT TF xf tf
  \REASON CAN interrupts never locked by application only within tests. It is not part of the component test to check application code. The code is verified by code inspection.

\ID COV_CAN_RAM_CHECK
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RAM_CHECK_EXTENDED
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_TIMEOUT_DURATION
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xx
  \ACCEPT TF tf tx
  \REASON Hardware loop time out is not covered in all configurations.

\ID COV_CAN_TRANSITION_REQUEST_START
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX tx tx
  \ACCEPT TF tf tf
  \ACCEPT TF tf tx
  \REASON Mode transition is not covered in all configurations (only with busoff tests).

\ID COV_CAN_TRANSITION_REQUEST_STOP
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX tx tx
  \ACCEPT TF tf tx
  \ACCEPT TF tf tf
  \REASON Mode transition is not covered in all configurations (only with disturbance tests).

\ID COV_CAN_TRANSITION_REQUEST_WAKEUP
  \ACCEPT TF
  \ACCEPT TF tf tf
  \REASON Mode transition is platform specific always true or false.

\ID COV_CAN_TRANSITION_REQUEST_SLEEP
  \ACCEPT TF
  \ACCEPT TF tf tf
  \REASON Mode transition is platform specific always true or false.

\ID COV_CAN_BASICCAN_SEARCH_LINEAR
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Received BasicCAN mailbox is always a valid object and found while search.

\ID COV_CAN_FULLCAN_SEARCH_LINEAR
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Received FullCAN mailbox is always a valid object and found while search.

\ID COV_CAN_RAM_CHECK_NO_STIMULATION
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf
  \ACCEPT XF xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf xf
  \REASON some configurations do not stimulate RamCheck by test suite, to check the standard CAN driver behaviour.

\ID COV_CAN_SAFE_BSW
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_FLEXCAN3_DERIVATIVE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX tf tx
  \ACCEPT TX tx xf
  \ACCEPT TX xf tx
  \ACCEPT TX xf xf
  \ACCEPT TX tx tx
  \ACCEPT XF xf xf
  \REASON Feature availability depends on FlexCAN3 derivative.

\ID COV_CAN_FLEXCAN3_ARM32_DERIVATIVE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT TX xf tx
  \REASON Feature availability depends on ARM32 FlexCAN3 derivatives.

\ID COV_CAN_FLEXCAN3_DERIVATIVE_ASYM_MAILBOXES
  \ACCEPT TX
  \ACCEPT XF
  \REASON Feature only available with FlexCAN3 derivatives containing an asymmetric number of hardware Mailboxes

\ID COV_CAN_FLEXCAN3_DERIVATIVE_NUMBER_OF_HW_MB
  \ACCEPT TX
  \ACCEPT XF
  \REASON Depending of the Maximum number of Hardware Mailboxes supported by each channels

\ID COV_CAN_INTERRUPT_SUPPORT
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF tf tf xf
  \ACCEPT TF tf tf tx
  \REASON WAKEUP interrrupt not supported for SafeBsw.

\ID COV_CAN_ENABLE_UPDATE_BASE_ADDRESS
  \ACCEPT TF
  \ACCEPT XF xf xf xf
  \ACCEPT TF xf xf tf
  \REASON Virtual Addressing: only Update Base Address Procedure supported for SafeBsw.

\ID  COV_CAN_ENABLE_FLEXCAN_PARITY_CHECK
  \ACCEPT TX
  \ACCEPT XF
  \REASON FlexCAN Parity Check is available for this derivative and is enabled by default but is not supported by the driver. Needs to be disabled.

\ID COV_CAN_EQUAL_CHANNEL_LAYOUT
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF
  \REASON The test is executed on defined channels. The channel layout is equal for each channel.

\ID COV_CAN_CLASSIC_MAILBOX_LAYOUT_COMPATABILITY
  \ACCEPT TX xf xf
  \REASON CLASSIC_MAILBOX_LAYOUT is needed for CAN_FD enabled.

\ID COV_CAN_POSTBUILD_VARIANT_SUPPORT
  \ACCEPT XF
  \ACCEPT TF tf xf
  \REASON Availabilty check. Is always defined. Is set to STD_ON or STD_OFF.

\ID COV_CAN_FD_BAUDRATE_AVAILABILITY
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF
  \REASON Generated data does not contain all data sets but checked in code. Not encapsulated with preprocessor switch to simplify code.

\ID COV_CAN_HARDWARE_PROCESSING_TIME
  \ACCEPT TX
  \ACCEPT XF
  \REASON Hardware processing time cannot be influenced. Is either true or false.

\ID COV_CAN_TESTSTIMULATION
  \ACCEPT XF
  \ACCEPT TX xf tx
  \ACCEPT TX tf tx
  \ACCEPT TF xf tf
  \ACCEPT XF xf xx
  \ACCEPT TF tf tx
  \ACCEPT TF xf tx tf
  \ACCEPT TF xf tf tf
  \ACCEPT TF tf tx tf
  \REASON Not in all configurations.

\ID COV_CAN_MAILBOX_ORDER
  \ACCEPT TF tx tf
  \ACCEPT TF tf tx
  \ACCEPT TX tx tx
  \ACCEPT XF tf xf
  \ACCEPT XF tx xf
  \ACCEPT TX
  \REASON Depends on order of generated RX, TX Basic CAN or Full CAN objects.

\ID COV_CAN_BUSOFF_HANDLING
  \ACCEPT TX
  \ACCEPT TF
  \REASON Is always true in 'CanHL_ErrorHandling()' when it is only called due to busoff.

\ID \ID COV_CAN_HWOBJINDIVPOLLING
  \ACCEPT X
  \ACCEPT TF
  \ACCEPT TX
  \ACCEPT XF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_SAFE_BSW_EXCLUSION_FLEXCAN3
  \ACCEPT XF xf xf
  \ACCEPT XF xf xf xf xf
  \REASON SafeBsw restricted feature will not be enforced to be deactivated or activated.

\ID COV_CAN_OSCAT_CONFIG_CHECK
  \ACCEPT XF
  \ACCEPT TX
  \REASON The 'osdISrCan_xx' define is only available in case OSEK OS is used. Only used to verify correct configuration and does not influence the runtime code.

\ID COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG
  \ACCEPT TF tx tf tf
  \ACCEPT TF tf tx tf
  \ACCEPT TF tf tf tx
  \ACCEPT TF tx tf
  \ACCEPT TF tf tx
  \REASON Generated data does not contain all data sets but checked in code. Not encapsulated with preprocessor switch to simplify code.


END_COVERAGE_JUSTIFICATION */ 


/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 120 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 120 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Flexcan3Asr Erzeugungsgangnummer: 120 */

/************   Organi, Version 3.9.2 Vector-Informatik GmbH  ************/
