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
 *              File: Os_Link_Core0_Stacks.ld
 *   Generation Time: 2021-04-17 17:11:59
 *           Project: S32K144_Start - Version 1.0
 *          Delivery: CBD1800257_D01
 *      Tool Version: DaVinci Configurator  5.18.37 SP1
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  STACK SECTIONS
 *********************************************************************************************************************/

#if defined ( OS_LINK_KERNEL_STACKS )
_OS_CORE0_STACKS_START = .;
__OS_CORE0_STACKS_START = .;

/* Stack: OsCore0_Error (1024 Byte) */
.OS_STACK_OSCORE0_ERROR_VAR_NOINIT ALIGN(32) :> .
_OS_STACK_OSCORE0_ERROR_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_ERROR_VAR_NOINIT);
_OS_STACK_OSCORE0_ERROR_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_ERROR_VAR_NOINIT) - 1;

/* Stack: OsCore0_Init (2048 Byte) */
.OS_STACK_OSCORE0_INIT_VAR_NOINIT ALIGN(32) :> .
_OS_STACK_OSCORE0_INIT_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_INIT_VAR_NOINIT);
_OS_STACK_OSCORE0_INIT_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_INIT_VAR_NOINIT) - 1;

/* Stack: OsCore0_Isr_Core (1024 Byte) */
.OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT ALIGN(32) :> .
_OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT);
_OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT) - 1;

/* Stack: OsCore0_Kernel (2048 Byte) */
.OS_STACK_OSCORE0_KERNEL_VAR_NOINIT ALIGN(32) :> .
_OS_STACK_OSCORE0_KERNEL_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_KERNEL_VAR_NOINIT);
_OS_STACK_OSCORE0_KERNEL_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_KERNEL_VAR_NOINIT) - 1;

/* Stack: OsCore0_Task_Prio100 (1024 Byte) */
.OS_STACK_OSCORE0_TASK_PRIO100_VAR_NOINIT ALIGN(32) :> .
_OS_STACK_OSCORE0_TASK_PRIO100_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_TASK_PRIO100_VAR_NOINIT);
_OS_STACK_OSCORE0_TASK_PRIO100_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_TASK_PRIO100_VAR_NOINIT) - 1;

/* Stack: OsCore0_Task_Prio4294967295 (1024 Byte) */
.OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT ALIGN(32) :> .
_OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT);
_OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT) - 1;

/* Stack: OsTask_APP (1024 Byte) */
.OS_STACK_OSTASK_APP_VAR_NOINIT ALIGN(32) :> .
_OS_STACK_OSTASK_APP_VAR_NOINIT_START = ADDR(.OS_STACK_OSTASK_APP_VAR_NOINIT);
_OS_STACK_OSTASK_APP_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSTASK_APP_VAR_NOINIT) - 1;

/* Stack: OsTask_BSW_SCHM (1024 Byte) */
.OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT ALIGN(32) :> .
_OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_START = ADDR(.OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT);
_OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT) - 1;



_OS_CORE0_STACKS_END = .-1;
__OS_CORE0_STACKS_END = .-1;
#endif

#ifdef OS_LINK_KERNEL_STACKS
# undef OS_LINK_KERNEL_STACKS
#endif


