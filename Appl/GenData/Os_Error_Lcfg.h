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
 *              File: Os_Error_Lcfg.h
 *   Generation Time: 2021-06-21 14:32:33
 *           Project: S32K144_Start - Version 1.0
 *          Delivery: CBD1800257_D01
 *      Tool Version: DaVinci Configurator  5.18.37 SP1
 *
 *
 *********************************************************************************************************************/

#if !defined (OS_ERROR_LCFG_H)                                                       /* PRQA S 0883 */ /* MD_Os_0883 */
# define OS_ERROR_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Error_Cfg.h"
# include "Os_Error_Types.h"

/* Os kernel module dependencies */

/* Os hal dependencies */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* Os code start and end label declarations */
extern uint8 OS_CODE_BLOCK$$Base[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */ /* PRQA S 0289, 1002, 3684 */ /* MD_Os_0289_LinkerSymbol, MD_Os_1002_LinkerSymbol, MD_Os_3684_LinkerSymbol */
extern uint8 OS_CODE_BLOCK$$Limit[]; /* PRQA S 3684 */ /* MD_Os_3684_LinkerSymbol */ /* PRQA S 1002, 3684 */ /* MD_Os_1002_LinkerSymbol, MD_Os_3684_LinkerSymbol */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Object reference table for Os code sections. */
extern CONSTP2CONST(Os_LinkerSectionLabelsType, OS_CONST, OS_CONST) OsCfg_OsCode_Sections[OS_CFG_NUM_OSCODE_SECTIONS + 1];

# define OS_STOP_SEC_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_ERROR_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Error_Lcfg.h
 *********************************************************************************************************************/
