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
 *  \brief        HAL interface to work with the Real-time Timer (RTT) module as a free running timer.
 *  \details
 *  RTT module features:
 *  - 32-bit Free-running Counter on prescaled slow clock or RTC calibrated 1Hz clock
 *  - 16-bit Configurable Prescaler- Can be used as FRT or PIT.
 *  - Interrupt on Alarm or Counter Increment.
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
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined(OS_HAL_TIMER_FRT_RTT_H)                                                                                    /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_TIMER_FRT_RTT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os HAL dependencies */
# include "Os_Hal_Interrupt.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/
/*! Real-time Timer Prescaler Value (RTT_MR.RTPRES). */
# define OS_HAL_TIMER_RTT_MR_RTPRES_MASK       (0xFFFFUL << 0)
/*! Alarm Interrupt Enable (RTT_MR.ALMIEN). */
# define OS_HAL_TIMER_RTT_MR_ALMIEN            (1UL << 16)
/*! Real-time Timer Increment Interrupt Enable (RTT_MR.RTTINCIEN). */
# define OS_HAL_TIMER_RTT_MR_RTTINCIEN         (1UL << 17)
/*! Real-time Timer Restart (RTT_MR.RTTRST). */
# define OS_HAL_TIMER_RTT_MR_RTTRST            (1UL << 18)
/*! Real-time Timer Disable (RTT_MR.RTTDIS). */
# define OS_HAL_TIMER_RTT_MR_RTTDIS            (1UL << 20)
/*! Real-time Clock 1Hz Clock Selection (RTT_MR.RTC1HZ). */
# define OS_HAL_TIMER_RTT_MR_RTC1HZ            (1UL << 24)

/*! Real-time Alarm Status (RTT_SR.ALMS).
 *  \details Cleared on read. */
# define OS_HAL_TIMER_RTT_SR_ALMS              (1UL << 0)
/*! Prescaler Roll-over Status (RTT_SR.RTTINC).
 *  \details Cleared on read. */
# define OS_HAL_TIMER_RTT_SR_RTTINC            (1UL << 1)

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
/*! RTT module Layout. */
typedef struct
{
  uint32 ModeRegister;            /*!< Offset: 0x00 Mode Register (RTT_MR). */
  uint32 AlarmRegister;           /*!< Offset: 0x04 Alarm Register (RTT_AR). */
  uint32 ValueRegister;           /*!< Offset: 0x08 Value Register (RTT_VR). */
  uint32 StatusRegister;          /*!< Offset: 0x0C Status Register (RTT_SR). */
} Os_Hal_TimerRttModuleType;


/*! High resolution timer configuration information for RTT timer module. */
struct Os_Hal_TimerFrtConfigType_Tag
{
  volatile Os_Hal_TimerRttModuleType * const Rtt;   /*!< Rtt module base address. */
  uint32 InterruptSource;                           /*!< Interrupt source. */
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
 *  Os_Hal_TimerFrtInit()
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
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_TimerFrtInit,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
# if defined (OS_CFG_COMPILER_LINARO)
/* This suppresses the warning regarding that "forceRead" is unsed after having been set. This warning can be ignored,
 * since this reading into "forceRead" is intended for the corresponding register.
 */
#  pragma GCC diagnostic ignored "-Wunused-but-set-variable"                                                            /* PRQA S 3116 */ /* MD_MSR_1.1 */
# endif

  volatile Os_Hal_TimerRttModuleType * const rtt = TimerConfig->Rtt;
  volatile uint32 forceRead;                                                                                            /* PRQA S 3203 */ /* MD_Os_Hal_3203 */

  /* #10 Disable the timer. */
  rtt->ModeRegister |= OS_HAL_TIMER_RTT_MR_RTTDIS;                                                                      /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

  /* #20 Set the timer prescaler with a minimal value. */
  rtt->ModeRegister &= ~OS_HAL_TIMER_RTT_MR_RTPRES_MASK;                                                                /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */
  rtt->ModeRegister |= 1UL;                                                                                             /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

  /* #30 Do not use 1Hz RTC as clock source. */
  rtt->ModeRegister &= ~OS_HAL_TIMER_RTT_MR_RTC1HZ;                                                                     /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

  /* #40 Configure RTT to not generate an interrupt on prescaler overflow. */
  rtt->ModeRegister &= ~OS_HAL_TIMER_RTT_MR_RTTINCIEN;                                                                  /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

  /* #50 Reset the timer (value = 0, alarm = 0xFFFFffff). */
  rtt->ModeRegister |= OS_HAL_TIMER_RTT_MR_RTTRST;                                                                      /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

  /* #60 Clear status register. */
  forceRead = rtt->StatusRegister;

  /* #70 Configure RTT to generate an interrupt on reaching alarm value. */
  rtt->ModeRegister |= OS_HAL_TIMER_RTT_MR_ALMIEN;                                                                      /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

  /* #80 Enable interrupt source. */
  Os_Hal_INTC_EnableNotMappedSource(TimerConfig->InterruptSource);

  /* #90 Enable the timer. */
  rtt->ModeRegister &= ~OS_HAL_TIMER_RTT_MR_RTTDIS;                                                                     /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

# if defined (OS_CFG_COMPILER_LINARO)
#  pragma GCC diagnostic warning "-Wunused-but-set-variable"                                                            /* PRQA S 3116 */ /* MD_MSR_1.1 */
# endif
}


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtGetCounterValue()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
OS_LOCAL_INLINE Os_Hal_TimerFrtTickType, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_TimerFrtGetCounterValue,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
  uint32 firstValue;
  uint32 secondValue;

  do
  {
    /* #10 Read counter value twice. */
    /* Citation from HW-Manual: Note: As CRTV can be updated asynchronously,
       it must be read twice at the same value. */
    firstValue = TimerConfig->Rtt->ValueRegister;
    secondValue = TimerConfig->Rtt->ValueRegister;
  /* #20 If values are not identical, repeat. */
  }while(firstValue != secondValue);

  /* #30 Return consistent counter value. */
  return firstValue;
}


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtSetCompareValue()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_TimerFrtSetCompareValue,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig,
  Os_Hal_TimerFrtTickType ExpirationTime
))
{
  /* #10 Disable alarm interrupt generation. */
  /* Citation from HW-Manual: Note: The alarm interrupt must be disabled
     (ALMIEN must be cleared in RTT_MR) when writing a new ALMV value. */
  TimerConfig->Rtt->ModeRegister &= ~OS_HAL_TIMER_RTT_MR_ALMIEN;                                                        /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

  /* #20 Set new alarm value. */
  TimerConfig->Rtt->AlarmRegister = ExpirationTime;                                                                     /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

  /* #30 Re-enable alarm interrupt generation. */
  TimerConfig->Rtt->ModeRegister |= OS_HAL_TIMER_RTT_MR_ALMIEN;                                                         /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */
}


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtAcknowledge()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_TimerFrtAcknowledge,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
# if defined (OS_CFG_COMPILER_LINARO)
/* This suppresses the warning regarding that "forceRead" is unsed after having been set. This warning can be ignored,
 * since this reading into "forceRead" is intended for the corresponding register.
 */
#  pragma GCC diagnostic ignored "-Wunused-but-set-variable"                                                            /* PRQA S 3116 */ /* MD_MSR_1.1 */
# endif

  volatile uint32 forceRead;                                                                                            /* PRQA S 3203 */ /* MD_Os_Hal_3203 */

  /* #10 Disable alarm interrupt generation. */
  TimerConfig->Rtt->ModeRegister &= ~OS_HAL_TIMER_RTT_MR_ALMIEN;                                                        /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

  /* #20 Clear status register. */
  forceRead = TimerConfig->Rtt->StatusRegister;

  /* #30 Re-enable alarm interrupt generation. */
  TimerConfig->Rtt->ModeRegister |= OS_HAL_TIMER_RTT_MR_ALMIEN;                                                         /* SBSW_OS_HAL_PWA_FRTCONFIG_RTT */

# if defined (OS_CFG_COMPILER_LINARO)
#  pragma GCC diagnostic warning "-Wunused-but-set-variable"                                                            /* PRQA S 3116 */ /* MD_MSR_1.1 */
# endif
}


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtTriggerIrq()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_TimerFrtTriggerIrq,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
  /* #10 Trigger interrupt source of the given timer. */
  Os_Hal_INTC_TriggerSoftwareInterrupt(TimerConfig->InterruptSource);
}

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* OS_HAL_TIMER_FRT_RTT_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Timer_Frt_Rtt.h
 **********************************************************************************************************************/
