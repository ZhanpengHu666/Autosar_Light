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
 *              File: Os_Hal_EntryAsm_Lcfg.asm
 *   Generation Time: 2021-04-09 15:46:07
 *           Project: S32K144_Start - Version 1.0
 *          Delivery: CBD1800257_D01
 *      Tool Version: DaVinci Configurator  5.18.37 SP1
 *
 *
 *********************************************************************************************************************/

#include "Os_Cfg.h"
#if defined(OS_CFG_COMPILER_IAR)
# include "Os_Hal_Entry_IAR.inc"
#else
# include "Os_Hal_Entry.inc"
#endif

  OS_HAL_ASM_PRESERVE8

  OS_HAL_ASM_CODE_SECTION(OS_CODE)

  OS_HAL_ASM_ALIGN4
  OS_HAL_ASM_CODE_SECTION(OS_INTVEC_CORE0_CODE)

  /* Export of the ISR wrappers on OsCore0 */
  OS_HAL_ASM_EXPORT(Os_Isr_Core0_Interrupt_15)
  OS_HAL_ASM_EXPORT(Os_Isr_Core0_Interrupt_94)
  OS_HAL_ASM_EXPORT(Os_Isr_Core0_Interrupt_97)
  OS_HAL_ASM_EXPORT(Os_Isr_Core0_Interrupt_98)
  
    
   /* Definitions of the ISR wrappers on OsCore0 */
  OS_HAL_ASM_IMPORT(OsCfg_Isr_CounterIsr_SystemTimer)
  OS_HAL_ASM_THUMB_FUNCTION
OS_HAL_ASM_FUNCTION_BEGIN(Os_Isr_Core0_Interrupt_15)
  Os_Hal_Cat2Entry_Interrupt OsCfg_Isr_CounterIsr_SystemTimer  
  OS_HAL_ASM_FUNCTION_END(Os_Isr_Core0_Interrupt_15)
    
  OS_HAL_ASM_IMPORT(OsCfg_Isr_CanIsr_0_BusOff)
  OS_HAL_ASM_THUMB_FUNCTION
OS_HAL_ASM_FUNCTION_BEGIN(Os_Isr_Core0_Interrupt_94)
  Os_Hal_Cat2Entry_Interrupt OsCfg_Isr_CanIsr_0_BusOff  
  OS_HAL_ASM_FUNCTION_END(Os_Isr_Core0_Interrupt_94)
    
  OS_HAL_ASM_IMPORT(OsCfg_Isr_CanIsr_0_MB00To15)
  OS_HAL_ASM_THUMB_FUNCTION
OS_HAL_ASM_FUNCTION_BEGIN(Os_Isr_Core0_Interrupt_97)
  Os_Hal_Cat2Entry_Interrupt OsCfg_Isr_CanIsr_0_MB00To15  
  OS_HAL_ASM_FUNCTION_END(Os_Isr_Core0_Interrupt_97)
    
  OS_HAL_ASM_IMPORT(OsCfg_Isr_CanIsr_0_MB16To31)
  OS_HAL_ASM_THUMB_FUNCTION
OS_HAL_ASM_FUNCTION_BEGIN(Os_Isr_Core0_Interrupt_98)
  Os_Hal_Cat2Entry_Interrupt OsCfg_Isr_CanIsr_0_MB16To31  
  OS_HAL_ASM_FUNCTION_END(Os_Isr_Core0_Interrupt_98)
    
  



  OS_HAL_ASM_ALIGN4
  OS_HAL_ASM_MODULE_END

