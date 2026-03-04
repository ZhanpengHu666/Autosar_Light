/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dcm_BaseInt.h
 *        \brief  Private data type definition and interface of DCM that are independent on core and external files
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/
#if !defined(DCM_BASEINT_H)
# define DCM_BASEINT_H
/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */

/*! Implementation version */
# define DCM_BASEINT_MAJOR_VERSION                                   10u
# define DCM_BASEINT_MINOR_VERSION                                   4u
# define DCM_BASEINT_PATCH_VERSION                                   0u
/* ----------------------------------------------
 ~&&&   Switches
---------------------------------------------- */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_SVC_2E_SUPPORT_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPE_WRITE_ENABLED                           STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_WRITE_ENABLED                           STD_OFF
#  endif

#  if (DCM_SVC_24_SUPPORT_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPE_GETSCALINGINFO_ENABLED                  STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_GETSCALINGINFO_ENABLED                  STD_OFF
#  endif

#  if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPE_DEFINE_ENABLED                          STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_DEFINE_ENABLED                          STD_OFF
#  endif

#  if (DCM_DIDMGR_DYNDID_SRCITEM_CHECK_STATE_ENABLED == STD_ON) && \
      (DCM_DIDMGR_DYNDID_CLR_ON_STATE_CHG_ENABLED    == STD_OFF)
#   define DCM_DIDMGR_DYNDID_DEEP_CHECK_ON_READ_ENABLED              STD_ON
#  else
#   define DCM_DIDMGR_DYNDID_DEEP_CHECK_ON_READ_ENABLED              STD_OFF
#  endif

#  if (DCM_DIDMGR_RANGE_SUPPORT_ENABLED   == STD_ON) || \
      (DCM_DIDMGR_EXTENDED_LOOKUP_ENABLED == STD_ON)
#   define DCM_DIDMGR_ASYNC_LOOKUP_ENABLED                           STD_ON
#  else
#   define DCM_DIDMGR_ASYNC_LOOKUP_ENABLED                           STD_OFF
#  endif

#  if (DCM_DIDMGR_ASYNC_LOOKUP_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPECONTEXT_LOOKUP_ENABLED                   STD_ON
#  else
#   define DCM_DIDMGR_OPTYPECONTEXT_LOOKUP_ENABLED                   STD_OFF
#  endif

#  if (DCM_DIDMGR_IO_MASKRECORD_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPECONTEXT_IO_ENABLED                       STD_ON
#  else
#   define DCM_DIDMGR_OPTYPECONTEXT_IO_ENABLED                       STD_OFF
#  endif

#  if (DCM_DIDMGR_PAGED_SUPPORT_ENABLED == STD_ON) && \
      (DCM_DIDMGR_VID_SUPPORT_ENABLED == STD_ON) && \
      (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
#   error "Paged DIDs are not allowed if any OBD2 VID DIDs as per AR4.2.2 are enabled!"
#  endif

#  if (DCM_DIDMGR_RANGE_SUPPORT_ENABLED == STD_ON) && \
      (DCM_DIDMGR_PAGED_SUPPORT_ENABLED == STD_ON)
#   error "DID ranges are not allowed if any paged DID is configured!"
#  endif

#  if (DCM_DIDMGR_PAGED_SUPPORT_ENABLED == STD_ON) || \
      (DCM_DIAG_CANCEL_OP_ENABLED == STD_ON)
#   define DCM_DIDMGR_CANCEL_OP_READ_ENABLED                         STD_ON
#  else
#   define DCM_DIDMGR_CANCEL_OP_READ_ENABLED                         STD_OFF
#  endif

#  if (DCM_DIDMGR_CANCEL_OP_READ_ENABLED == STD_ON) || \
      (DCM_DIAG_CANCEL_OP_ENABLED == STD_ON)
#   define DCM_DIDMGR_CANCEL_OP_ENABLED                              STD_ON
#  else
#   define DCM_DIDMGR_CANCEL_OP_ENABLED                              STD_OFF
#  endif
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Defines
---------------------------------------------- */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/* DID operation types - derive from the extern filter API */
#  define DCM_DIDMGR_OP_READ                                         DCM_DID_OP_READ
#  define DCM_DIDMGR_OP_WRITE                                        DCM_DID_OP_WRITE
#  define DCM_DIDMGR_OP_IO                                           DCM_DID_OP_IO
#  define DCM_DIDMGR_OP_SCALINGINFO                                  DCM_DID_OP_SCALINGINFO
#  define DCM_DIDMGR_OP_DEFINE                                       DCM_DID_OP_DEFINE
#  define DCM_DIDMGR_OP_ROE                                          DCM_DID_OP_ROE
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Function-like macros
---------------------------------------------- */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_DIDMGR_OP_INFO_COMBINED_ENABLED == STD_ON)
#   define Dcm_DidMgrOpInfoRedirector(opRef, opRefType)              (Dcm_CfgDidMgrOpInfoCombined[(opRef)].opRefType)                                /* PRQA S 3453, 3410 */ /* MD_MSR_19.7, MD_Dcm_AbstractTokenReplacement_3410 */
#  else
#   define Dcm_DidMgrOpInfoRedirector(opRef, opRefType)              (opRef)                                                                         /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  endif

#  define Dcm_CfgDidMgrGetDidInfo(pDidInfoContext)                   (&Dcm_CfgDidMgrDidInfo[(pDidInfoContext)->Descriptor.DidInfoIdx])               /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_CfgDidMgrGetDidOpInfo(pDidInfoContext)                 (&Dcm_CfgDidMgrDidOpInfo[(pDidInfoContext)->Descriptor.DidOpInfoIdx])           /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_CfgDidMgrGetDidOpClassInfo(pDidInfoContext)            (&Dcm_CfgDidMgrDidOpClassInfo[(pDidInfoContext)->Descriptor.DidOpClassInfoIdx]) /* PRQA S 3453 */ /* MD_MSR_19.7 */

#  define Dcm_DidMgrGetRoeEventId(pDidInfoContext)                   (Dcm_CfgDidMgrOpInfoRoE[Dcm_DidMgrOpInfoRedirector((pDidInfoContext)->OpRef, OpRefRoE)].EventId) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Typedefs
---------------------------------------------- */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
typedef P2CONST(Dcm_CfgDidMgrDidInfoType, TYPEDEF, DCM_CONST)            Dcm_DidMgrDidInfoPtrType;
typedef P2CONST(Dcm_CfgDidMgrDidOpInfoType, TYPEDEF, DCM_CONST)          Dcm_DidMgrDidOpInfoPtrType;
typedef P2CONST(Dcm_CfgDidMgrDidOpClassInfoType, TYPEDEF, DCM_CONST)     Dcm_DidMgrDidOpClassInfoPtrType;
typedef P2CONST(Dcm_CfgDidMgrSignalOpClassInfoType, TYPEDEF, DCM_CONST)  Dcm_DidMgrSignalOpClassInfoPtrType;

/*! Context information of a Did processing */
struct DCM_DIDMGRDIDOPTYPEWORKCONTEXTTYPE_TAG
{
  Dcm_CfgDidMgrSignalOpClassRefMemType  SignalOpClassInfoRef;  /*!< Reference to Dcm_CfgDidMgrSignalOpClassInfo[] entry */
  Dcm_CfgDidMgrSignalIterMemType        NumSignals;            /*!< Number of DID signals */
};
typedef struct DCM_DIDMGRDIDOPTYPEWORKCONTEXTTYPE_TAG Dcm_DidMgrDidOpTypeBaseContextType;

/*! Context information of the read operation */
struct DCM_DIDMGROPTYPEREADCONTEXTTYPE_TAG
{
  Dcm_CfgDidMgrOptimizedDidLengthType  Progress;         /*!< Read progress of the current signal */
  Dcm_CfgDidMgrSignalLengthType        RemainingLength;  /*!< Complete length of the current signal */
  Dcm_OpStatusType                     OpStatus;         /*!< Current operation status */
};
typedef struct DCM_DIDMGROPTYPEREADCONTEXTTYPE_TAG Dcm_DidMgrOpTypeReadContextType;

#  if (DCM_DIDMGR_OPTYPECONTEXT_LOOKUP_ENABLED == STD_ON)
typedef uint8 Dcm_DidMgrDidLookUpStateType;
/*! Context information of the Did lookup state */
struct DCM_DIDMGRLOOKUPCONTEXTTYPE_TAG
{
  Dcm_DidMgrDidLookUpStateType State;  /*!< Lookup state (range/concrete/external filtered) of a Did */
};
typedef struct DCM_DIDMGRLOOKUPCONTEXTTYPE_TAG Dcm_DidMgrLookUpContextType;
#  endif

#  if (DCM_DIDMGR_OPTYPECONTEXT_IO_ENABLED == STD_ON)
/*! Context information of the IO operation */
struct DCM_DIDMGROPTYPEIOCONTEXTTYPE_TAG
{
  Dcm_ReadOnlyMsgType             EnableMaskPtr;           /*!< Pointer to CEMR of request */
#   if (DCM_DIDMGR_OPCLS_IO_ANY_WITH_EXT_CEMR_ENABLED == STD_ON)
  uint32                          ControlEnableMaskRecord; /*!< CEMR as a value */
#   endif
#   if (DCM_DIDMGR_OPCLS_IO_ANY_WITH_INT_CEMR_ENABLED == STD_ON)
  boolean                         OperExecuted;            /*!< Operation executed flag */
  Dcm_CfgDidMgrSignalIterMemType  SignalIter;              /*!< IODID signal iterator */
  Dcm_MsgItemType                 BitScanner;              /*!< Currently scanned bit of CEMR */
#   endif
};
typedef struct DCM_DIDMGROPTYPEIOCONTEXTTYPE_TAG Dcm_DidMgrOpTypeIoContextType;
#  endif

typedef union
{                                                                                                                                                    /* PRQA S 0750 */ /* MD_Dcm_Optimize_0750 */
  Dcm_DidMgrOpTypeReadContextType           Read;         /*!< Context information of the read operation */
#  if (DCM_DIDMGR_OPTYPECONTEXT_LOOKUP_ENABLED == STD_ON)
  Dcm_DidMgrLookUpContextType               LookUp;       /*!< Context information of the Did lookup state */
#  endif
#  if (DCM_DIDMGR_OPTYPECONTEXT_IO_ENABLED == STD_ON)
  Dcm_DidMgrOpTypeIoContextType             Io;           /*!< Context information of the Io operation */
#  endif
}Dcm_DidMgrDidSharedOpTypeContextType;

/*! Context information of the Did operation */
struct DCM_DIDMGRDIDOPTYPECONTEXTTYPE_TAG
{
  Dcm_DidMgrDidOpTypeBaseContextType    Base;    /*!< Context of Did processing */
  Dcm_DidMgrDidSharedOpTypeContextType  OpType;  /*!< Operation context of a Did */
};
typedef struct DCM_DIDMGRDIDOPTYPECONTEXTTYPE_TAG Dcm_DidMgrDidOpTypeContextType;
typedef P2VAR(Dcm_DidMgrDidOpTypeContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_DidMgrDidOpTypeContextPtrType;
typedef P2CONST(Dcm_DidMgrDidOpTypeContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_DidMgrDidOpTypeContextConstPtrType;

/*! Shared Did manager descriptor data type */
struct DCM_DIDMGRDIDDESCRIPTORTYPE_TAG
{
  Dcm_CfgDidMgrDidInfoRefType           DidInfoIdx;         /*!< Reference to Dcm_CfgDidMgrDidInfo[] entry */
  Dcm_CfgDidMgrOpHandleMemType          DidOpInfoIdx;       /*!< Reference to Dcm_CfgDidMgrDidOpInfo[] entry */
  Dcm_CfgDidMgrDidOpClassHandleMemType  DidOpClassInfoIdx;  /*!< Reference to Dcm_CfgDidMgrDidOpClassInfo[] entry */
};
typedef struct DCM_DIDMGRDIDDESCRIPTORTYPE_TAG Dcm_DidMgrDidDescriptorType;

/*! Context information of the DID */
struct DCM_DIDMGRDIDINFOCONTEXTTYPE_TAG
{
  Dcm_DidMgrDidDescriptorType  Descriptor;      /*!< Descriptor of the Did */
  uint16                       Did;             /*!< Identifier value of the Did */
  Dcm_DidMgrDidLengthType      DidLength;       /*!< Length of the Did */
  Dcm_DidMgrDidLengthType      ReservedLength;  /*!< Buffer size which has to be reserved to be able to read the Did */
};
typedef struct DCM_DIDMGRDIDINFOCONTEXTTYPE_TAG Dcm_DidMgrDidInfoContextType;
typedef P2VAR(Dcm_DidMgrDidInfoContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_DidMgrDidInfoContextPtrType;
typedef P2CONST(Dcm_DidMgrDidInfoContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_DidMgrDidInfoContextConstPtrType;
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Module internal API function declarations
---------------------------------------------- */
# define DCM_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*lint -restore */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrGetDidInfo()
 *********************************************************************************************************************/
/*! \brief          Returns some information of a specific DID.
 *  \details        Looks for the DID to get its corresponding DidInfo and DidOpInfo (up to 32767 items).
 *  \param[in]      opStatus             The current operation status
 *  \param[in,out]  pDidInfoContext      Contains DID Information
 *  \param[in,out]  pDidOpTypeContext    Contains DID operation state
 *  \param[in]      didOp                The lookup DID operation context
 *  \return         DCM_E_OK             Positive look up result
 *  \return         DCM_E_NOT_OK         Negative look up result
 *  \return         DCM_E_PENDING        Final result is pending, retry later
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \pre            The DID number must be set by the caller (pDidInfoContext->Did is valid).
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrGetDidInfo(Dcm_OpStatusType                  opStatus
                                                   ,Dcm_DidMgrDidInfoContextPtrType   pDidInfoContext
                                                   ,Dcm_DidMgrDidOpTypeContextPtrType pDidOpTypeContext
                                                   ,Dcm_DidMgrOpOptType               didOp);
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*lint -restore */
#endif /* !defined(DCM_BASEINT_H) */
/* ********************************************************************************************************************
 * END OF FILE: Dcm_BaseInt.h
 * ******************************************************************************************************************** */
