/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**
 *  \addtogroup  Os_Hal_Interrupt
 *  \{
 *
 *  \file    Os_Hal_InterruptController_NVIC_S32x.h
 *  \brief   HAL interface to work with the S32x Interrupt Controller architecture.
 *  \details
 *  Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined(OS_HAL_INTERRUPTCONTROLLER_NVIC_S32VX_H)
# define OS_HAL_INTERRUPTCONTROLLER_NVIC_S32VX_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"

# include "Os_Hal_Derivative.h"
# include "Os_Hal_Compiler.h"
# include "Os_Hal_Interrupt_Types.h"
# include "Os_Error.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/*! Interrupt Router Shared Peripheral Routing Control Register (MSCM_IRSPRC). */
# define OS_HAL_MSCM_IRSPRC(x)       (*(volatile uint16*) (OS_HAL_MSCM_IRSPRC_BASE + ((x) * 2UL)))                      /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro to get the index inside MSCM_IRSPRC, given the physical core id parameter. */
# define OS_HAL_MSCM_IRSPRC_COREID2FIELD(x)       (x - 3)                                                               /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! System Exceptions Priority Level Registers (SHPR). */
# define OS_HAL_INTC_NVIC_SHPR(x)    (*(volatile uint8*) (OS_HAL_INTC_NVIC_BASE + 0xD14UL + (x)))                       /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! System Exceptions Priority Level Registers (SHPR). */
# define OS_HAL_INTC_NVIC_SHPR(x)    (*(volatile uint8*) (OS_HAL_INTC_NVIC_BASE + 0xD14UL + (x)))                       /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Interrupt Set-Enable Registers (ISER). */
# define OS_HAL_INTC_NVIC_ISER(x)    (*(volatile uint32*) (OS_HAL_INTC_NVIC_BASE + 0x100UL + ((x) * 4UL)))              /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Interrupt Clear-Enable Registers (ICER). */
# define OS_HAL_INTC_NVIC_ICER(x)    (*(volatile uint32*) (OS_HAL_INTC_NVIC_BASE + 0x180UL + ((x) * 4UL)))              /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Interrupt Set-Pending Registers (ISPR). */
# define OS_HAL_INTC_NVIC_ISPR(x)    (*(volatile uint32*) (OS_HAL_INTC_NVIC_BASE + 0x200UL + ((x) * 4UL)))              /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Interrupt Clear-Pending Registers (ICPR). */
# define OS_HAL_INTC_NVIC_ICPR(x)    (*(volatile uint32*) (OS_HAL_INTC_NVIC_BASE + 0x280UL + ((x) * 4UL)))              /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Interrupt Active Bit Registers (IABR). */
# define OS_HAL_INTC_NVIC_IABR(x)    (*(volatile uint32*) (OS_HAL_INTC_NVIC_BASE + 0x300UL + ((x) * 4UL)))              /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Interrupt Priority Registers (IPR). */
# define OS_HAL_INTC_NVIC_IPR(x)     (*(volatile uint8*) (OS_HAL_INTC_NVIC_BASE + 0x400UL + (x)))                       /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Interrupt Control State Register (ICSR). */
# define OS_HAL_INTC_NVIC_ICSR       (*(volatile uint32*) (0xE000ED04UL))                                               /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Vector Table Offset Register (VTOR). */
# define OS_HAL_INTC_SCB_VTOR        (*(volatile uint32*) (0xE000ED08UL))                                               /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Software Triggered Interrupt Register (STIR). */
# define OS_HAL_INTC_STIR            (*(volatile uint32*) (0xE000EF00UL))                                               /* PRQA S 3453 */ /* MD_MSR_19.7 */


/*! \brief    Logical interrupt level used for tasks.
 *  \details  The logically lowest interrupt level. */
# define OS_HAL_TASK_LEVEL                       (0x0U)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_INTC_InitializeVectorTable()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_InitializeVectorTable,
(
  Os_Hal_VectorTableType VectorTable
))
{
  /* #10 Set VTOR Register to given base address. */
  uint32 VectorTableStartAddress = (uint32)VectorTable;                                                                 /* PRQA S 0306 */ /* MD_Os_Hal_0306 */
  Os_Assert((Os_StdReturnType)((VectorTableStartAddress & 0x7FUL) == 0UL));
  OS_HAL_INTC_SCB_VTOR = VectorTableStartAddress;                                                                       /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_INTC_INITIALIZEVECTORTABLE_001 */

  /* #20 Disable interrupts. */
  Os_Hal_INTC_SetCurrentLevel(OS_CFG_HAL_GLOBAL_DISABLE_LEVEL);
}

/***********************************************************************************************************************
 *  Os_Hal_INTC_InitSource()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                            /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_InitSource,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  Os_CorePhysicalIdType CoreId = Os_Hal_CoreGetId();

  /* #10 Set IPR register at given source to given level. */
  OS_HAL_INTC_NVIC_IPR(IsrConfig->CoreInterruptSource) = (uint8)IsrConfig->Level;                                       /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_INTC_NVIC_IPR */

  /* #20 Set IRSPRC register to route the given source to given running core. */
  OS_HAL_MSCM_IRSPRC(IsrConfig->CoreInterruptSource) |= (uint16)(1UL << OS_HAL_MSCM_IRSPRC_COREID2FIELD(CoreId));                                       /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_INTC_NVIC_IPR */
}

/***********************************************************************************************************************
 *  Os_Hal_INTC_EnableMappedSource()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_EnableMappedSource,
(
  Os_Hal_IntSourceType SystemInterruptSource,
  Os_Hal_IntSourceType CoreInterruptSource
))                                                                                                                      /* COV_OS_HALPLATFORMINTERRUPTMAPPINGSUPPORTED */
{
  /* #10 No action for NVIC_S32x necessary. */
  OS_IGNORE_UNREF_PARAM(SystemInterruptSource);                                                                         /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(CoreInterruptSource);                                                                           /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}

/***********************************************************************************************************************
 *  Os_Hal_INTC_EnableNotMappedSource()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_EnableNotMappedSource,
(
  Os_Hal_IntSourceType CoreInterruptSource
))
{
  /* #10 Set enable bit in ISER register for given source. */
  OS_HAL_INTC_NVIC_ISER(CoreInterruptSource >> 5) = (1UL << (CoreInterruptSource & 31UL));                              /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_INTC_NVIC_ISER */
}


/***********************************************************************************************************************
 *  Os_Hal_INTC_DisableSource()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_DisableSource,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Set disable bit in ICER register for the given source. */
    OS_HAL_INTC_NVIC_ICER(IsrConfig->CoreInterruptSource >> 5) =
        (1UL << (IsrConfig->CoreInterruptSource & 31UL));
}



/***********************************************************************************************************************
 *  Os_Hal_INTC_SetCurrentLevel()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                            /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_SetCurrentLevel,
(
  Os_Hal_IntLevelType Level
))
{
  /* #10 Set BASEPRI to given level. */
  Os_Hal_WriteBasepri(Level);
}


/***********************************************************************************************************************
 *  Os_Hal_INTC_GetCurrentLevel()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_Hal_IntLevelType, OS_CODE, OS_ALWAYS_INLINE,                             /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_GetCurrentLevel,
(
  void
))
{
  /* #10 Return BASEPRI. */
  return Os_Hal_ReadBasepri();
}


/***********************************************************************************************************************
 *  Os_Hal_INTC_EndOfInterrupt()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_EndOfInterrupt,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Set clear bit in ICPR register for the core interrupt source. */
  OS_HAL_INTC_NVIC_ICPR(IsrConfig->CoreInterruptSource >> 5) =
      (1UL << (IsrConfig->CoreInterruptSource & 31UL));                                                                 /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_INTC_NVIC_ICPR */
}


/***********************************************************************************************************************
 *  Os_Hal_INTC_TriggerSoftwareInterrupt()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_TriggerSoftwareInterrupt,
(
  Os_Hal_IntSourceType Source
))                                                                                                                      /* COV_OS_HALPLATFORMFRTUNSUPPORTED_XX */
{
  /* #10 Set pending bit in ISPR register for given source. */
  OS_HAL_INTC_NVIC_ISPR(Source >> 5) = (1UL << (Source & 31UL));                                                        /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_INTC_NVIC_ISPR */
}



/***********************************************************************************************************************
 *  Os_Hal_INTC_ResetSoftwareInterrupt()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                            /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_ResetSoftwareInterrupt,
(
  Os_Hal_IntSourceType Source
))
{
  /* #10 No action for NVIC necessary. */
  OS_IGNORE_UNREF_PARAM(Source);                                                                                        /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}


/***********************************************************************************************************************
 *  Os_Hal_INTC_IsInterruptSourceEnabled()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint8, OS_CODE, OS_ALWAYS_INLINE,                                          /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_IsInterruptSourceEnabled,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Return enable bit on NVIC ICER register for the core interrupt source. */
  return ((OS_HAL_INTC_NVIC_ICER(IsrConfig->CoreInterruptSource >> 5) &
      (1UL << (IsrConfig->CoreInterruptSource & 31UL))) != 0);

}


/***********************************************************************************************************************
 *  Os_Hal_INTC_IsInterruptPending()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint8, OS_CODE, OS_ALWAYS_INLINE,                                          /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_INTC_IsInterruptPending,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Return clear-pending bit in ICPR for the core interrupt source. */
  return (uint8)((OS_HAL_INTC_NVIC_ICPR(IsrConfig->CoreInterruptSource >> 5) &
        (1UL << (IsrConfig->CoreInterruptSource & 31UL))) != 0);                                                        /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
}


/***********************************************************************************************************************
 *  Os_Hal_INTC_IntLevelIsGt()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_INTC_IntLevelIsGt,
(
  CONST(Os_Hal_IntLevelType, OS_CONST) LevelX,
  CONST(Os_Hal_IntLevelType, OS_CONST) LevelY
))
{
  /* #10 Return !0 if LevelX is smaller than LevelY. */
  return (Os_StdReturnType)((LevelX - 1) < (LevelY - 1));
}

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* OS_HAL_INTERRUPTCONTROLLER_MSCM_H */

/*!
 * \}
 */
/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_InterruptController_NVIC_S32Vx.h
 *********************************************************************************************************************/

