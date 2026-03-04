/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 *  \addtogroup   Os_Hal_Context
 *  \{
 *
 *  \file       Os_Hal_ContextAsm.asm
 *  \brief      Assembler parts of context switching primitives for ARMv7-M.
 *  \internal
 *   Hardware manuals: See derivative specific header (Os_Hal_Derivative_*Int.h)
 *   Errata sheets: See derivative specific header
 *   Specifics: -
 *   Used registers and bits: General Purpose and System Registers
 *   Operating modes: -
 *   Hardware features related to independence or partitioning: -
 *   Access mechanism: Core special function registers
 *   Hardware diagnostics: -
 *  \endinternal
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

# include "Os_Hal_Derivative.h"

# include "Os_Hal_ContextAsm_v7m.inc"

  OS_HAL_ASM_MODULE_END
