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
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: Harman International (China) Holdings Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: FS32K148UAT0VLQR
 *    License Scope : The usage is restricted to CBD1800257_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_MemoryProtection_Cfg.h
 *   Generation Time: 2021-04-15 16:21:19
 *           Project: S32K144_Start - Version 1.0
 *          Delivery: CBD1800257_D01
 *      Tool Version: DaVinci Configurator  5.18.37 SP1
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_MEMORYPROTECTION_CFG_H)                                             /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_MEMORYPROTECTION_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Defines whether memory protection is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_MEMORY_PROTECTION                          (STD_OFF)

/*! Defines whether access rights switching for applications is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_MEMORY_PROTECTION_FOR_APPLICATIONS         (STD_OFF)

/*! Defines whether access rights switching for threads is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_MEMORY_PROTECTION_FOR_THREADS              (STD_OFF)

/*! Defines whether the OS has write access to OS data in privileged mode (STD_ON) or not (STD_OFF). */
# define OS_CFG_MEMORY_PROTECTION_FOR_TRUSTED              (STD_OFF)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_MEMORYPROTECTION_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_MemoryProtection_Cfg.h
 *********************************************************************************************************************/
