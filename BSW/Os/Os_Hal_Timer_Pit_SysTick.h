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
 *  \addtogroup  Os_Hal_Timer
 *  \{
 *
 *  \file
 *  \brief        Primitives to work with Cortex M SysTick timer hardware.
 *  \details
 *  The ARMv7-M architecture provides a system timer (SysTick):
 *  - 24-bit
 *  - Decrementing
 *  - Wrap-on-zero
 *
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
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined(OS_HAL_TIMER_PIT_SYSTICK_H)                                                                                /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_TIMER_PIT_SYSTICK_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
# include "Std_Types.h"
# include "Os_Common.h"
# include "Os_Hal_Timer_Types.h"

# include "Os_Hal_Interrupt.h"


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/
/*! SysTick base address. */
# define OS_HAL_TIMER_SYSTICK_BASE                       (0xE000E010UL)

/*! SysTick Control and Status Register (SYST_CSR). */
# define OS_HAL_TIMER_SYSTICK_SYST_CSR                   (*(volatile uint32*)(OS_HAL_TIMER_SYSTICK_BASE + 0x0UL))
/*! SYST_CSR.ENABLE bit. */
# define OS_HAL_TIMER_SYSTICK_SYST_CSR_ENABLE            (1UL << 0)
/*! SYST_CSR.TICKINT bit. */
# define OS_HAL_TIMER_SYSTICK_SYST_CSR_TICKINT           (1UL << 1)
/*! SYST_CSR.CLKSOURCE bit. */
# define OS_HAL_TIMER_SYSTICK_SYST_CSR_CLKSOURCE         (1UL << 2)
/*! SYST_CSR.COUNTFLAG bit. */
# define OS_HAL_TIMER_SYSTICK_SYST_CSR_COUNTFLAG         (1UL << 16)

/*! SysTick Reload Value Register (SYST_RVR). */
# define OS_HAL_TIMER_SYSTICK_SYST_RVR                   (*(volatile uint32*)(OS_HAL_TIMER_SYSTICK_BASE + 0x4UL))

/*! SysTick Current Value Register (SYST_CVR). */
# define OS_HAL_TIMER_SYSTICK_SYST_CVR                   (*(volatile uint32*)(OS_HAL_TIMER_SYSTICK_BASE + 0x8UL))

/*! SysTick Calibration Value Register (SYST_CALIB). */
# define OS_HAL_TIMER_SYSTICK_SYST_CALIB                 (*(volatile uint32*)(OS_HAL_TIMER_SYSTICK_BASE + 0xCUL))

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
/*! Programmable interval timer configuration information for Systick timer module. */
struct Os_Hal_TimerPitConfigType_Tag
{
  uint32 ReloadValue;      /*!< Reload value. */
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
 *  Os_Hal_TimerPitInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_TimerPitInit,
(
  P2CONST(Os_Hal_TimerPitConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
  /* #10 Disable the timer. */
  OS_HAL_TIMER_SYSTICK_SYST_CSR = 0UL;                                                                                   /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_TIMER_SYSTICK_SYST_CSR */

  /* #20 Set SYST_RVR to configured reload value. */
  OS_HAL_TIMER_SYSTICK_SYST_RVR = TimerConfig->ReloadValue;                                                              /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_TIMER_SYSTICK_SYST_RVR */

  /* #30 Set current counter value (SYST_CVR) to 0. */
  OS_HAL_TIMER_SYSTICK_SYST_CVR = 0UL;                                                                                   /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_TIMER_SYSTICK_SYST_CVR */

  /* #40 Configure timer to generate interrupts and use CPU as clock source. */
  /* #50 Enable the timer. */
  OS_HAL_TIMER_SYSTICK_SYST_CSR = OS_HAL_TIMER_SYSTICK_SYST_CSR_ENABLE |                                                 /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_TIMER_SYSTICK_SYST_CSR */
                                  OS_HAL_TIMER_SYSTICK_SYST_CSR_TICKINT |
                                  OS_HAL_TIMER_SYSTICK_SYST_CSR_CLKSOURCE;
}


/***********************************************************************************************************************
 *  Os_Hal_TimerPitAckAndReload()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_TimerPitAckAndReload,
(
  P2CONST(Os_Hal_TimerPitConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
# if defined (OS_CFG_COMPILER_LINARO)
/* This suppresses the warning regarding that "forceRead" is unsed after having been set. This warning can be ignored,
 * since this reading into "forceRead" is intended for the corresponding register.
 */
#  pragma GCC diagnostic ignored "-Wunused-but-set-variable"                                                            /* PRQA S 3116 */ /* MD_MSR_1.1 */
# endif

  volatile uint32 forceRead;                                                                                            /* PRQA S 3203 */ /* MD_Os_Hal_3203 */

  /* #10 Read SYST_CSR to clear COUNTFLAG. */
  forceRead = OS_HAL_TIMER_SYSTICK_SYST_CSR;                                                                            /* PRQA S 0303 */ /* MD_Os_Hal_0303 */

  OS_IGNORE_UNREF_PARAM(TimerConfig);                                                                                   /* PRQA S 3112 */ /* MD_Os_Hal_3112 */

# if defined (OS_CFG_COMPILER_LINARO)
#  pragma GCC diagnostic warning "-Wunused-but-set-variable"                                                            /* PRQA S 3116 */ /* MD_MSR_1.1 */
# endif
}


/***********************************************************************************************************************
 *  Os_Hal_TimerPitIsPending()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE,                                         /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_TimerPitIsPending,
(
  P2CONST(Os_Hal_TimerPitConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
  uint32 isPending;

  /* #10 Return value of SYST_CSR.COUNTFLAG. */
  isPending = OS_HAL_TIMER_SYSTICK_SYST_CSR & OS_HAL_TIMER_SYSTICK_SYST_CSR_COUNTFLAG;                                  /* PRQA S 0303 */ /* MD_Os_Hal_0303 */

  OS_IGNORE_UNREF_PARAM(TimerConfig);                                                                                   /* PRQA S 3112 */ /* MD_Os_Hal_3112 */

  return isPending;
}


# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* OS_HAL_TIMER_PIT_SYSTICK_H */

/*!
 * \}
 */
/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_HwTimer_Pit_SysTick.h
 *********************************************************************************************************************/
