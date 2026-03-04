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
 *          File:  Rte_TurnLight_Type.h
 *        Config:  S32K144_Start.dpa
 *   ECU-Project:  MyECU
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Application types header file for SW-C <TurnLight>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_TURNLIGHT_TYPE_H
# define _RTE_TURNLIGHT_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * Range, Invalidation, Enumeration and Bit Field Definitions
 *********************************************************************************************************************/

#  define InvalidValue_Rte_DT_TurnLightService_2 (0U)

#  define InvalidValue_Rte_DT_TurnLightService_3 (0U)

#  define InvalidValue_Rte_DT_TurnLightService_4 (0U)

#  define InvalidValue_Rte_DT_TurnLightService_5 (0U)

#  define InvalidValue_Rte_DT_TurnLightService_6 (0U)

#  ifndef NORQUEST
#   define NORQUEST (0U)
#  endif

#  ifndef OFF
#   define OFF (1U)
#  endif

#  ifndef ON
#   define ON (2U)
#  endif

#  ifndef NOREQUEST
#   define NOREQUEST (0U)
#  endif

#  ifndef LEFT
#   define LEFT (1U)
#  endif

#  ifndef RIGHT
#   define RIGHT (2U)
#  endif

#  ifndef ALL
#   define ALL (3U)
#  endif

#  ifndef FRONT_LEFT
#   define FRONT_LEFT (4U)
#  endif

#  ifndef MIDDLE_LEFT
#   define MIDDLE_LEFT (5U)
#  endif

#  ifndef REAR_LEFT
#   define REAR_LEFT (6U)
#  endif

#  ifndef FRONT_RIGHT
#   define FRONT_RIGHT (7U)
#  endif

#  ifndef MIDDLE_RIGHT
#   define MIDDLE_RIGHT (8U)
#  endif

#  ifndef REAR_RIGHT
#   define REAR_RIGHT (9U)
#  endif

#  ifndef NOREQUEST
#   define NOREQUEST (0U)
#  endif

#  ifndef LEFT
#   define LEFT (1U)
#  endif

#  ifndef RIGHT
#   define RIGHT (2U)
#  endif

#  ifndef ALL
#   define ALL (3U)
#  endif

#  ifndef FRONT_LEFT
#   define FRONT_LEFT (4U)
#  endif

#  ifndef MIDDLE_LEFT
#   define MIDDLE_LEFT (5U)
#  endif

#  ifndef REAR_LEFT
#   define REAR_LEFT (6U)
#  endif

#  ifndef FRONT_RIGHT
#   define FRONT_RIGHT (7U)
#  endif

#  ifndef MIDDLE_RIGHT
#   define MIDDLE_RIGHT (8U)
#  endif

#  ifndef REAR_RIGHT
#   define REAR_RIGHT (9U)
#  endif

#  ifndef NORQUEST
#   define NORQUEST (0U)
#  endif

#  ifndef OFF
#   define OFF (1U)
#  endif

#  ifndef ON
#   define ON (2U)
#  endif

# endif /* RTE_CORE */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_TURNLIGHT_TYPE_H */
