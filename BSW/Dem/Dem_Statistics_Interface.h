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
/*! \ingroup    Dem_Master 
 *  \defgroup   Dem_Statistics Statistics
 *  \{
 *  \file       Dem_Statistics_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the Statistics subcomponent which calculates global and event related statistics.
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

#if !defined (DEM_STATISTICS_INTERFACE_H)
#define DEM_STATISTICS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Statistics_Types.h"

/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Statistics_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Statistics_GetFirstFailedEvent
 *****************************************************************************/
/*!
 * \brief         Get the first failed event.
 *
 * \details       Get the first failed event.
 *
 * \return        The first failed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstFailedEvent(
  void
  );

/* ****************************************************************************
 * Dem_Statistics_SetFirstFailedEvent
 *****************************************************************************/
/*!
 * \brief         Set the first failed event.
 *
 * \details       Set the first failed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstFailedEvent(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Statistics_GetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Get the first confirmed event.
 *
 * \details       Get the first confirmed event.
 *
 * \return        The first confirmed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstConfirmedEvent(
  void
  );


/* ****************************************************************************
 * Dem_Statistics_SetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Set the first confirmed event.
 *
 * \details       Set the first confirmed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstConfirmedEvent(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Statistics_GetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * \brief         Get the most recently failed event.
 *
 * \details       Get the most recently failed event.
 *
 * \return        The most recently failed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentFailedEvent(
  void
  );

/* ****************************************************************************
 * Dem_Statistics_SetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * \brief         Set the most recently failed event.
 *
 * \details       Set the most recently failed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentFailedEvent(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Statistics_GetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Get the most recently confirmed event.
 *
 * \details       Get the most recently confirmed event.
 *
 * \return        The most recently confirmed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentConfirmedEvent(
  void
  );

/* ****************************************************************************
 * Dem_Statistics_SetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Set the most recently confirmed event.
 *
 * \details       Set the most recently confirmed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentConfirmedEvent(
  Dem_EventIdType EventId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Statistics_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Statistics_UpdateGlobalFailureStatistics
 *****************************************************************************/
/*!
 * \brief         This function updates global failure statistics.
 *
 * \details       This function updates global failure statistics like first
 *                and most recently failed event, first and most recently 
 *                confirmed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Effects
 *                Trigger flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_UpdateGlobalFailureStatistics(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects
  );


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_STATISTICS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Statistics_Interface.h
 *********************************************************************************************************************/
