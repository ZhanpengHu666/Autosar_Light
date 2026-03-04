/* ********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 */
/*! \addtogroup Dem_DTCSelector
 *  \{
 *  \file       Dem_DTCSelector_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Savas Ates                    vissat        Vector Informatik GmbH
 *  Anna Bosch                    visanh        Vector Informatik GmbH
 *  Stefan Huebner                vishrs        Vector Informatik GmbH
 *  Thomas Dedler                 visdth        Vector Informatik GmbH
 *  Alexander Ditte               visade        Vector Informatik GmbH
 *  Matthias Heil                 vismhe        Vector Informatik GmbH
 *  Erik Jeglorz                  visejz        Vector Informatik GmbH
 *  Friederike Hitzler            visfrs        Vector Informatik GmbH
 *  Aswin Vijayamohanan Nair      visavi        Vector Informatik GmbH
 *  Fabian Wild                   viszfa        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTCSELECTOR_IMPLEMENTATION_H)
#define DEM_DTCSELECTOR_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCSelector_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Definitions.h"
#include "Dem_DTC_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \addtogroup Dem_DTCSelector_Private
 * \{
 */

/* ****************************************************************************
 % Dem_DTCSelector_SetSelectionData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_DTCSelector_SetSelectionData(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(Dem_DTCSelector_DataType, AUTOMATIC)  SelectionData
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DTCSelectorId >= Dem_Cfg_GetSizeOfDTCSelectorTable())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetDTCSelectorTable(DTCSelectorId, SelectionData);                                                                   /* SBSW_DEM_ARRAY_WRITE_DTCSELECTORTABLE */
  }  
}

/* ****************************************************************************
 % Dem_DTCSelector_GetSelectionData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_DataType, DEM_CODE) 
Dem_DTCSelector_GetSelectionData(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  return Dem_Cfg_GetDTCSelectorTable(DTCSelectorId);
}

/* ****************************************************************************
 % Dem_DTCSelector_InitGroupId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitGroupId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_DTCSelector_GroupIdType, AUTOMATIC)  GroupId
  )
{
  Dem_DTCSelector_DataType lSelectionData;

  lSelectionData = Dem_DTCSelector_GetSelectionData(DTCSelectorId);

  lSelectionData.Request.DTC = DTCNumber;
  lSelectionData.Request.DTCFormat = DTCFormat;
  lSelectionData.Request.DTCOrigin = DTCOrigin;
  lSelectionData.MemoryId = MemoryId;
  lSelectionData.Selection.GroupId = GroupId;
  lSelectionData.SelectorState = DEM_DTCSELECTOR_SELECTION_ALL_DTCS;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId, lSelectionData);
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */

/* ****************************************************************************
 % Dem_DTCSelector_InitGroupMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitGroupMask(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  GroupMask
  )
{
  Dem_DTCSelector_DataType lSelectionData;

  lSelectionData = Dem_DTCSelector_GetSelectionData(DTCSelectorId);

  lSelectionData.Request.DTC = DTCNumber;
  lSelectionData.Request.DTCFormat = DTCFormat;
  lSelectionData.Request.DTCOrigin = DTCOrigin;
  lSelectionData.MemoryId = MemoryId;
  lSelectionData.Selection.GroupMask = GroupMask;
  lSelectionData.SelectorState = DEM_DTCSELECTOR_SELECTION_GROUP;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId, lSelectionData);
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */

/* ****************************************************************************
 % Dem_DTCSelector_InitEventId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitEventId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTCSelector_DataType lSelectionData;

  lSelectionData = Dem_DTCSelector_GetSelectionData(DTCSelectorId);

  lSelectionData.Request.DTC = DTCNumber;
  lSelectionData.Request.DTCFormat = DTCFormat;
  lSelectionData.Request.DTCOrigin = DTCOrigin;
  lSelectionData.MemoryId = MemoryId;
  lSelectionData.Selection.EventId = EventId;
  lSelectionData.SelectorState = DEM_DTCSELECTOR_SELECTION_DTC;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId, lSelectionData);
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */

/* ****************************************************************************
 % Dem_DTCSelector_InitInvalid()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitInvalid(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(Dem_DTCSelector_ResultType, AUTOMATIC)  SelectorState
  )
{
  Dem_DTCSelector_DataType lSelectionData;

  lSelectionData.Request.DTC = DTCNumber;
  lSelectionData.Request.DTCFormat = DTCFormat;
  lSelectionData.Request.DTCOrigin = DTCOrigin;
  lSelectionData.MemoryId = DEM_CFG_MEMORYID_INVALID;
  lSelectionData.Selection.EventId = DEM_EVENT_INVALID;
  lSelectionData.SelectorState = SelectorState;
  lSelectionData.ActiveAsyncOps = 0;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId, lSelectionData);
}

/*!
 * \}
 */


/*!
 * \addtogroup Dem_DTCSelector_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_DTCSelector_GetGroupId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_GroupIdType, DEM_CODE)
Dem_DTCSelector_GetGroupId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  Dem_DTCSelector_GroupIdType lReturnValue;

  if (Dem_DTCSelector_GetSelectionData(DTCSelectorId).SelectorState == DEM_DTCSELECTOR_SELECTION_ALL_DTCS)
  {
    lReturnValue = Dem_DTCSelector_GetSelectionData(DTCSelectorId).Selection.GroupId;
  }
  else
  {
    lReturnValue = DEM_DTCSELECTOR_GROUP_INVALID;
  }
  return lReturnValue;
}

#if (DEM_CFG_CLEAR_GROUP_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_DTCSelector_GetGroupMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_GetGroupMask(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  uint8 lReturnValue;

  if (Dem_DTCSelector_GetSelectionData(DTCSelectorId).SelectorState == DEM_DTCSELECTOR_SELECTION_GROUP)
  {
    lReturnValue = Dem_DTCSelector_GetSelectionData(DTCSelectorId).Selection.GroupMask;
  }
  else
  {
    lReturnValue = DEM_CFG_GROUPMASK_NONE;
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_DTCSelector_GetEventId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCSelector_GetEventId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  Dem_EventIdType lReturnValue;

  if (Dem_DTCSelector_GetSelectionData(DTCSelectorId).SelectorState == DEM_DTCSELECTOR_SELECTION_DTC)
  {
    lReturnValue = Dem_DTCSelector_GetSelectionData(DTCSelectorId).Selection.EventId;
  }
  else
  {
    lReturnValue = DEM_EVENT_INVALID;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTCSelector_GetMemoryId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_GetMemoryId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  uint8 lReturnValue;

  if (Dem_DTCSelector_GetSelectionData(DTCSelectorId).SelectorState != DEM_DTCSELECTOR_SELECTION_NO_MATCH)
  {
    lReturnValue = Dem_DTCSelector_GetSelectionData(DTCSelectorId).MemoryId;
  }
  else
  {
    lReturnValue = DEM_CFG_MEMORYID_INVALID;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTCSelector_GetSelectionResult()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_ResultType, DEM_CODE)
Dem_DTCSelector_GetSelectionResult(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  return Dem_DTCSelector_GetSelectionData(DTCSelectorId).SelectorState;
}

/* ****************************************************************************
 % Dem_DTCSelector_GetSelectionArguments
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_RequestType, DEM_CODE) Dem_DTCSelector_GetSelectionArguments(
  CONST(uint8, AUTOMATIC)  DTCSelectorId
  )
{
  return Dem_DTCSelector_GetSelectionData(DTCSelectorId).Request;
}

/*!
 * \}
 */

/*!
 * \addtogroup Dem_DTCSelector_Private
 * \{
 */

/************************************************************************************************************
 %  Dem_DTCSelector_FindGroupFromUdsDtc
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_FindGroupMaskFromUdsDtc(
  CONST(uint32, AUTOMATIC)  DTC
  )
{
  uint8 lGroupMask;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTC)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lGroupMask = DEM_DTCSELECTOR_GROUP_INVALID;
#if (DEM_CFG_DTCGROUPMASK == STD_ON)
  {
    uint8_least lGroupIterator;
    for (lGroupIterator = 0; lGroupIterator < Dem_Cfg_GetSizeOfDtcGroupMask(); lGroupIterator++)
    {
      if (Dem_Cfg_GetUdsGroupDtcOfDtcGroupMask(lGroupIterator) == DTC)
      {
        lGroupMask = Dem_Cfg_GetGroupMaskOfDtcGroupMask(lGroupIterator);
        break;
      }
    }
  }
#endif

  return lGroupMask;
}

/* ****************************************************************************
 % Dem_DTCSelector_TestForAllDtc
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_GroupIdType, DEM_CODE)
Dem_DTCSelector_TestForAllDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat
  )
{
  Dem_DTCSelector_GroupIdType lReturnValue;

  if ( (DTCFormat == DEM_DTC_FORMAT_UDS)
    || (DTCFormat == DEM_DTC_FORMAT_OBD) )
  {
    if (DTC == DEM_DTC_GROUP_ALL_DTCS)
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_ALL_DTCS;
    }
    else if (DTC == DEM_DTC_GROUP_EMISSION_REL_DTCS)
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_EMISSION_RELATED;
    }
    else if (DTC == DEM_DTC_GROUP_WWHOBD_DTCS)
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC;
    }
    else
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_INVALID;
    }
  }
  else
  {
    /* DTC Format J1939 */
    if (DTC == DEM_DTC_GROUP_ALL_DTCS)
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_ALL_DTCS;
    }
    else
    {
      lReturnValue = DEM_DTCSELECTOR_GROUP_INVALID;
    }
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTCSelector_TestForGroupDtc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_TestForGroupDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat
  )
{
  uint8 lReturnValue;
  if (DTCFormat == DEM_DTC_FORMAT_UDS)
  {
    lReturnValue = Dem_DTCSelector_FindGroupMaskFromUdsDtc(DTC);
  }
  else
  {
    lReturnValue = DEM_CFG_GROUPMASK_NONE;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTCSelector_TestForSingleDtc
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCSelector_TestForSingleDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_EventIdType lEventId;

  if (DTCFormat == DEM_DTC_FORMAT_UDS)
  {
    if (DTC == 0)
    {
      lEventId = DEM_EVENT_INVALID;
    }
    else
    {
      lEventId = Dem_Cfg_GetMasterEvent(Dem_Cfg_FindEventFromUdsDtc(DTC, MemoryId));
    }
  }
  else
#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  if (DTCFormat == DEM_DTC_FORMAT_J1939)
  {
    if (DTC == 0)
    { /* DTC does not exist */
      lEventId = DEM_EVENT_INVALID;
    }
    else
    { /* Dem_Cfg_FindEventFromJ1939Dtc can not be called with '0' */
      lEventId = Dem_Cfg_GetMasterEvent(Dem_Cfg_FindEventFromJ1939Dtc(DTC, MemoryId));
    }
  }
  else
#endif
  {
    lEventId = DEM_EVENT_INVALID;
  }

  return lEventId;
}

/* ****************************************************************************
 % Dem_DTCSelector_TestForSupportedMemoryId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCSelector_TestForSupportedMemoryId(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  boolean lReturnValue;

  lReturnValue = FALSE;
  switch (MemoryId)
    {
    case DEM_CFG_MEMORYID_PRIMARY:
      lReturnValue = TRUE;
      break;

# if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    case DEM_CFG_MEMORYID_SECONDARY:
      lReturnValue = TRUE;
      break;
# endif

# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    case DEM_CFG_MEMORYID_PERMANENT:
      lReturnValue = TRUE;
      break;
# endif

    default:
      /* FALSE */
      break;
    }
  return lReturnValue;
}

/*!
 * \}
 */


/*!
 * \addtogroup Dem_DTCSelector_Public
 * \{
 */

/* ****************************************************************************
 % Dem_DTCSelector_InitDefault()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitDefault(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  Dem_DTCSelector_InitInvalid(DTCSelectorId, 
                              DEM_CFG_DTC_UDS_INVALID, 
                              DEM_DTC_FORMAT_INVALID, 
                              DEM_DTC_ORIGIN_INVALID, 
                              DEM_DTCSELECTOR_SELECTION_INIT);
}

/* ****************************************************************************
 % Dem_DTCSelector_SelectDTC()
 *****************************************************************************/
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_SelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_DTCSelector_GroupIdType lGroupId;

  if (Dem_DTCSelector_TestForSupportedMemoryId(MemoryId) == FALSE)
  {
    Dem_DTCSelector_InitInvalid(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN);
  }
  else
  {
    lGroupId = Dem_DTCSelector_TestForAllDtc(DTCNumber, DTCFormat);
    if (lGroupId != DEM_DTCSELECTOR_GROUP_INVALID)
    {
      Dem_DTCSelector_InitGroupId(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, MemoryId, lGroupId);
    }
    else
    {
      uint8 lGroupMask;
      lGroupMask = Dem_DTCSelector_TestForGroupDtc(DTCNumber, DTCFormat);
      if (lGroupMask != DEM_CFG_GROUPMASK_NONE)
      {
        Dem_DTCSelector_InitGroupMask(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, MemoryId, lGroupMask);
      }
      else
      {
        Dem_EventIdType lEventId;
        lEventId = Dem_DTCSelector_TestForSingleDtc(DTCNumber, DTCFormat, MemoryId);
        if (lEventId != DEM_EVENT_INVALID)
        {
          Dem_DTCSelector_InitEventId(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, MemoryId, lEventId);
        }
        else
        {
          Dem_DTCSelector_InitInvalid(DTCSelectorId, DTCNumber, DTCFormat, DTCOrigin, DEM_DTCSELECTOR_SELECTION_NO_MATCH);
        }
      }
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTCSelector_LockSelectDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_LockSelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  Dem_DTCSelector_DataType lSelectionData;

  lSelectionData = Dem_DTCSelector_GetSelectionData(DTCSelectorId);
  Dem_Internal_AssertReturnVoid(lSelectionData.ActiveAsyncOps < 255, DEM_E_INCONSISTENT_STATE)
  lSelectionData.ActiveAsyncOps++;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId, lSelectionData);
}

/* ****************************************************************************
 % Dem_DTCSelector_ReleaseSelectDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_ReleaseSelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  Dem_DTCSelector_DataType lSelectionData;

  lSelectionData = Dem_DTCSelector_GetSelectionData(DTCSelectorId);
  Dem_Internal_AssertReturnVoid(lSelectionData.ActiveAsyncOps > 0, DEM_E_INCONSISTENT_STATE)
  lSelectionData.ActiveAsyncOps--;

  Dem_DTCSelector_SetSelectionData(DTCSelectorId, lSelectionData);
}

/* ****************************************************************************
 % Dem_DTCSelector_TestSelectDTCLocked()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCSelector_TestSelectDTCLocked(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  )
{
  return (boolean) (Dem_DTCSelector_GetSelectionData(DTCSelectorId).ActiveAsyncOps > 0);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DTCSELECTOR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCSelector_Implementation.h
 *********************************************************************************************************************/
