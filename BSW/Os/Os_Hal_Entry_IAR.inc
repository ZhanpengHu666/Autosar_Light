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
 * \addtogroup   Os_Hal_Entry
 * \{
 *
 * \file  Os_Hal_Entry_IAR.inc
 * \brief  This component handles hardware exceptions and interrupts.
 * \internal
 *  Hardware manuals: See derivative specific header (Os_Hal_Derivative_*Int.h)
 *  Errata sheets:    See derivative specific header
 *  Specifics: -
 *  Used registers and bits: General Purpose and System Registers
 *  Operating modes: -
 *  Hardware features related to independence or partitioning: -
 *  Access mechanism: Core special function registers
 *  Hardware diagnostics: -
 * \endinternal
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined (OS_HAL_ENTRY_INC)
# define OS_HAL_ENTRY_INC

# include "Os_Hal_Derivative.h"
# include "Os_Hal_Entry_Cfg.h"
# include "Os_Hal_MemoryProtection_Cfg.h"
# include "Os_Hal_Compiler.inc"

  OS_HAL_ASM_IMPORT(Os_IsrRun)

# if defined(OS_CFG_DERIVATIVEGROUP_CYT2BX)
#  include "Os_Hal_Entry_IAR_CYT2.inc"
# elif defined(OS_CFG_DERIVATIVEGROUP_IMX8X)
#  include "Os_Hal_Entry_IAR_IMX8x.inc"
# endif /* OS_CFG_DERIVATIVE_<> */

/***********************************************************************************************************************
 *  Os_Hal_Cat2Entry_Interrupt()
 **********************************************************************************************************************/
/*! \brief        Low level ISR handler which saves minimum of interrupted context to be able to call high level ISR
 *                handler.
 *  \details
 *
 *  \param[in]    IsrConfig  ISR configuration which shall be executed by high level ISR handler.
 *
 *  \context      ANY
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
Os_Hal_Cat2Entry_Interrupt MACRO IsrConfig
  mrs  r2, basepri
  mov  r3, #OS_CFG_HAL_GLOBAL_DISABLE_LEVEL
  msr  basepri, r3        ; disable all interrupts
  mrs  r1, control
  push {r1-r2, lr}
  mov  r2, #0
  msr  control, r2

  sub  sp, sp, #0x20      ; reserve the space for the frame copy
  mov  r1, #0x1000000     ; prepare xPSR with only T bit set
  str  r1, [sp, #0x1C]
  mov  lr, #0xFFFFFFF9
  add  r1, pc, #0x8       ; Dependend on the placement of this instruction
                          ; the result will be address of the "nop"
                          ; or the "ldr" instruction
  str  r1, [sp, #0x18]    ; replace the PC in the exceptions frame
  dsb
  bx   lr

  ; continue in thread mode here
  nop
  ; or here
  ldr  r0, =OS_HAL_ASM_MACRO_PARAM_IN_BODY(IsrConfig)
  bl   Os_IsrRun          ; call the main ISR wrapper
  pop  {r1-r2, lr}        ; restore the interrupt level
  mov  r0, sp             ; prepare the exception frame pointer for RFE
  msr  basepri, r2        ; restore the interrupt level before interrupt
  svc  #2                 ; use SvCall to unstack the original exception frame
  b    .
  ENDM


/***********************************************************************************************************************
 *  Os_Hal_Entry_Interrupt()
 **********************************************************************************************************************/
/*! \brief        Branches to given JumpTarget.
 *  \details      Used for Cat1 and Cat0 Interrupts.
 *  Set PC = JumpTarget.
 *
 *  \param[in]    JumpTarget  Address of function which shall be executed.
 *
 *  \context      ANY
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
Os_Hal_Entry_Interrupt MACRO JumpTarget
  mrs  r2, basepri
  mov  r3, #OS_CFG_HAL_GLOBAL_DISABLE_LEVEL
  msr  basepri, r3                               ; disable all interrupts
  mrs  r1, control
  push {r1-r2, lr}
  mov  r2, #0
  msr  control, r2

  sub  sp, sp, #0x20                             ; reserve the space for the frame copy
  mov  r1, #0x1000000                            ; prepare xPSR with only T bit set
  str  r1, [sp, #0x1C]
  mov  lr, #0xFFFFFFF9
  add  r1, pc, #0x8                              ; Dependend on the placement of this instruction
                                                 ; the result will be address of the "nop"
                                                 ; or the "bl" instruction
  str  r1, [sp, #0x18]                           ; replace the PC in the exceptions frame
  dsb
  bx   lr

  ; continue in thread mode here
  nop
  ; or here
  bl   OS_HAL_ASM_MACRO_PARAM_IN_BODY(JumpTarget); call the main ISR wrapper
  pop  {r1-r2, lr}                               ; restore the interrupt level
  mov  r0, sp                                    ; prepare the exception frame pointer for RFE
  msr  basepri, r2                               ; restore the interrupt level before interrupt
  svc  #2                                        ; use SvCall to unstack the original exception frame
  b    .
  ENDM


#endif /* defined(OS_HAL_ENTRY_INC) */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Entry.inc
 *********************************************************************************************************************/
