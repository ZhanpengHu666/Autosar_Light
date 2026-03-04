/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain wi:wth Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 *  \addtogroup Os_Hal_Core
 *  \{
 *
 *  \file
 *  \brief      Jacinto (TDAx) specific primitives.
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
 *
 *
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined (OS_HAL_CORE_JACINTO_H)                                                                                        /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_CORE_JACINTO_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Common.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/*! System spinlock configuration register (SPINLOCK_SYSCONFIG) SOFTRESET bit. */
# define OS_HAL_SPINLOCK_SYSCONFIG_RESET_BIT        (0x1UL)
/*! System spinlock status register (SPINLOCK_SYSTATUS) RESETDONE mask. */
# define OS_HAL_SPINLOCK_SYSTATUS_RESET_MASK        (0x1UL)
/*! System spinlock lock register (SPINLOCK_LOCK) mask to get spinlock. */
# define OS_HAL_SPINLOCK_LOCK_MASK                  (0x0UL)
/*! System spinlock lock register (SPINLOCK_LOCK) value to release spinlock. */
# define OS_HAL_SPINLOCK_UNLOCK_VALUE               (0x0UL)


/*! System spinlock base address. */
# define OS_HAL_SPINLOCK_BASE                       (0x4A0F6000UL)
/*! System spinlock configuration register (SPINLOCK_SYSCONFIG). */
# define OS_HAL_SPINLOCK_SYSCONFIG                  (*(volatile uint32*) (OS_HAL_SPINLOCK_BASE + 0x10UL))               /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! System spinlock status register (SPINLOCK_SYSTATUS). */
# define OS_HAL_SPINLOCK_SYSTATUS                   (*(volatile uint32*) (OS_HAL_SPINLOCK_BASE + 0x14UL))               /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! System spinlock lock register (SPINLOCK_LOCK_REG). */
# define OS_HAL_SPINLOCK_LOCK_REG                   (*(volatile uint32*) (OS_HAL_SPINLOCK_BASE + 0x800UL))              /* PRQA S 3453 */ /* MD_MSR_19.7 */


/*! Image Processor Unit Inter Processor Communication Register (CORTEXM4_CTRL_REG). */
# define OS_HAL_IPU1_WUGEN_CORTEXM4_CTRL_REG        (*(volatile uint32*) (0x55081000UL))                                /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Image Processor Unit Inter Peripheral Identification Register (CORTEXM4_RW_PID1). */
# define OS_HAL_IPU_RW_TABLE                        (*(volatile uint32*) (0xE00FE000UL))                                /* PRQA S 3453 */ /* MD_MSR_19.7 */


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! XSignal interrupt configuration. */
struct Os_Hal_XSigInterruptConfigType_Tag
{
  uint32 Source;                      /*!< The interrupt source of the xsignal. */
  uint32 InterruptFlag;               /*!< The flag to trigger an interrupt. */
};

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_19.1 */


/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_CoreGetId()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */

OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_CorePhysicalIdType, OS_CODE, OS_ALWAYS_INLINE,                          /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_CoreGetId,
(
  void
))
{
  /* #10 Return physical core ID. */
  return (Os_CorePhysicalIdType)OS_HAL_IPU_RW_TABLE;
}

 /***********************************************************************************************************************
  *  Os_Hal_SpinInit()
  **********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
 OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
 OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
 Os_Hal_SpinInit,
 (
   P2VAR(volatile Os_Hal_SpinlockType, AUTOMATIC, OS_VAR_NOINIT) Spinlock
 ))
 {
   /* #10 Perform hardware spinlock software reset. */
   OS_HAL_SPINLOCK_SYSCONFIG |= (1UL << OS_HAL_SPINLOCK_SYSCONFIG_RESET_BIT);

   /* #20 wait until reset procedure is finished. */
   while ((OS_HAL_SPINLOCK_SYSTATUS & OS_HAL_SPINLOCK_SYSTATUS_RESET_MASK) == 0)
   {
      /* loops until RESETDONE bit becomes 1. */
   }

   /* #30 Release the hardware spinlock. */
   OS_HAL_SPINLOCK_LOCK_REG = OS_HAL_SPINLOCK_UNLOCK_VALUE;

   /* #40 Set given spinlock to 0. */
   *Spinlock = 0;                                                                                                        /* SBSW_OS_HAL_PWA_CALLER */
 }

/***********************************************************************************************************************
 *  Os_Hal_SpinTryLock()
 **********************************************************************************************************************/
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
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219, 3673 */ /* MD_Os_Hal_3219, MD_Os_Hal_3673_NotUsed */
OS_LOCAL_INLINE Os_Hal_SpinlockResultType, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_SpinTryLock,
(
  P2VAR(volatile Os_Hal_SpinlockType, AUTOMATIC, OS_VAR_NOINIT) Spinlock
))
{
  Os_Hal_SpinlockResultType result;
  uint32 state;

  /* #10 Disable global interrupt handling and store prior state. */
  state = Os_Hal_DisableAndReturnPriorState();

  /* #20 Wait until hardware spinlock is free and than take it.  */
  while(OS_HAL_SPINLOCK_LOCK_REG != OS_HAL_SPINLOCK_LOCK_MASK)
  {
    /* loops until occupy the spinlock. */
  }
  /* #30 If the spinlock variable is available. */
  if(*Spinlock == 0)
  {
     /* #40 Lock the spinlock variable */
     *Spinlock = 1;

     /* #50 Set the result value to succeeded. */
     result = OS_HAL_SPINLOCKSUCCEEDED;
  }
  else
  {
    /* #60 Otherwise set the result value to not succeeded. */
    result = !OS_HAL_SPINLOCKSUCCEEDED;
  }

  /* #70 Release the hardware spinlock. */
  OS_HAL_SPINLOCK_LOCK_REG = OS_HAL_SPINLOCK_UNLOCK_VALUE;

  /* #80 Restore previous interrupt state. */
  Os_Hal_RestorePriorIntState(state);

  /* #90 Return the result value. */
  return result;
}


/***********************************************************************************************************************
 *  Os_Hal_XSigInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_XSigInit,
(
  P2CONST(Os_Hal_XSigInterruptConfigType, AUTOMATIC, OS_CONST) XSigConfig
))
{
  /* #10 Enable the corresponding interrupt source. */
  Os_Hal_INTC_EnableSourceNotMapped(XSigConfig->Source);
}


/***********************************************************************************************************************
 *  Os_Hal_XSigTrigger()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_XSigTrigger,
(
  P2CONST(Os_Hal_XSigInterruptConfigType, AUTOMATIC, OS_CONST) XSigConfig
))
{
  /* #10 Trigger interrupt in the IPU specific register. */
  OS_HAL_IPU1_WUGEN_CORTEXM4_CTRL_REG |= (uint32)(1UL << XSigConfig->InterruptFlag);
}


/***********************************************************************************************************************
 *  Os_Hal_XSigAcknowledge()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_XSigAcknowledge,
(
  P2CONST(Os_Hal_XSigInterruptConfigType, AUTOMATIC, OS_CONST) XSigConfig
))
{
  /* #10 Reset interrupt trigger bit in the IPU specific register. */
  OS_HAL_IPU1_WUGEN_CORTEXM4_CTRL_REG &= (uint32)~(1UL << XSigConfig->InterruptFlag);
}

/***********************************************************************************************************************
 *  Os_Hal_CoreStart()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* COV_OS_HALPLATFORMMULTICOREUNSUPPORTED */ /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_CoreStart,
(
  P2CONST(Os_Hal_CoreConfigType, AUTOMATIC, OS_CONST) Core
))                                                                                                                      /* COV_OS_HALPLATFORMMULTICOREUNSUPPORTED */
{
  /* #10 Stub implementation: Currently not needed. */
  OS_IGNORE_UNREF_PARAM(Core);                                                                                          /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* OS_HAL_CORE_JACINTO_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core_Jacinto.h
 **********************************************************************************************************************/

