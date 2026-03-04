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
 *  \brief      S32X specific primitives.
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
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined (OS_HAL_CORE_S32X_H)                                                                                        /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_CORE_S32X_H

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

/*! Processor X Number Register (CPUXNUM). */
# define OS_HAL_MSCM_CPUXNUM                             (*(volatile uint32*) (0x40198004UL))                           /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Partition 0 Core Process Configuration Register offset.  */
# define MC_ME_PRTN0_CORE_PCONF_OFFSET                  (0x0UL)
/*! Partition 0 Core Process Status Register offset.  */
# define MC_ME_PRTN0_CORE_STAT_OFFSET                   (0x8UL)
/*! Partition 0 Core Process Address Register offset.  */
# define MC_ME_PRTN0_CORE_ADDR_OFFSET                   (0xCUL)

/*! Bit mask to force Core0 reset on Peripheral Reset Register (RGM_PRST0[PERIPH_0_RST]).  */
# define MC_RGM_PRST0_0_CORE0_MASK                     0x1UL
/*! Bit mask to force Core1 reset on Peripheral Reset Register (RGM_PRST0[PERIPH_1_RST]).  */
# define MC_RGM_PRST0_0_CORE1_MASK                     0x2UL
/*! Bit mask to force Core2 reset on Peripheral Reset Register (RGM_PRST0[PERIPH_2_RST]).  */
# define MC_RGM_PRST0_0_CORE2_MASK                     0x4UL

/*! System SEMA42 lock value to get the spinlock. */
# define OS_HAL_SEMA42_LOCK_VALUE                        (OS_HAL_MSCM_CPUXNUM + 1)
/*! System SEMA42 unlock value to release the spinlock. */
# define OS_HAL_SEMA42_UNLOCK_VALUE                      0x0UL
/*! System SEMA42 first reset half word (RSTGT[TSTGDP]). */
# define OS_HAL_SEMA42_RSTGT_RSTGDP_FIRST_VALUE          0xE200UL
/*! System SEMA42 second reset half word (RSTGT[TSTGDP]). */
# define OS_HAL_SEMA42_RSTGT_RSTGDP_SECOND_VALUE         0x1D00UL

/*! System SEMA42 base address. */
# define OS_HAL_SEMA42_BASE                    (0x40298000UL)
/*! First System SEMA42 gate register (SEMA42_GATE). */
# define OS_HAL_SEMA42_GATE                    (*(volatile uint8*) (OS_HAL_SEMA42_BASE))                                /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! System SEMA42 reset gate register (SEMA42_RSTGT). */
# define OS_HAL_SEMA42_RSTGT                   (*(volatile uint16*) (OS_HAL_SEMA42_BASE + 0x42UL))                      /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Interrupt Router CPa Interrupt 0 Status Register (IRCPaISR0). */
# define OS_HAL_MSCM_IRCPSR(a)                 (*(volatile uint32*) (OS_HAL_INTC_MSCM_BASE + (0x200UL) + (0x20UL * a)))                    /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Interrupt Router CPa Interrupt 0 Generation Register (IRCPaIGR0). */
# define OS_HAL_MSCM_IRCPGR(a)                 (*(volatile uint32*) (OS_HAL_INTC_MSCM_BASE+ (0x204UL) + (0x20UL * a)))                    /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Mask used to acknowledge all triggered interrupt for given IRCPISR register.
 *  All sender cores can be acknowledged, because all the pending requests will be serviced by the same
 *  receiver interrupt routine. */
# define OS_HAL_MSCM_IRCPSR_ACKNOWLEDGE_MASK  (0x7FUL)
/*! Mask used to trigger a core-to-core interrupt in IRCPIGR register. */
# define OS_HAL_MSCM_IRCPGR_TRIGGER_MASK      (0x1UL)


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! XSignal interrupt configuration. */
struct Os_Hal_XSigInterruptConfigType_Tag
{
  Os_Hal_IntSourceType Source;                                   /*!< Interrupt Source. */
  uint32 TargetCoreId;                                           /*!< Target physical core id. */
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
  return (Os_CorePhysicalIdType)OS_HAL_MSCM_CPUXNUM;
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
  */
 OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
 OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
 Os_Hal_SpinInit,
 (
   P2VAR(volatile Os_Hal_SpinlockType, AUTOMATIC, OS_VAR_NOINIT) Spinlock
 ))
 {
   /* #10 Perform first part of gate reset. */
   OS_HAL_SEMA42_RSTGT = OS_HAL_SEMA42_RSTGT_RSTGDP_FIRST_VALUE;

   /* #20 Perform second part of gate reset. */
   OS_HAL_SEMA42_RSTGT = OS_HAL_SEMA42_RSTGT_RSTGDP_SECOND_VALUE;

   /* #30 Set given spinlock to 0. */
   *Spinlock = !OS_HAL_SPINLOCK_LOCKED;                                                                                  /* SBSW_OS_HAL_PWA_CALLER */
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

  /* #20 Wait until hardware spinlock is free and than lock it.  */
  do
  {
    OS_HAL_SEMA42_GATE = (uint8)OS_HAL_SEMA42_LOCK_VALUE;
  }
  while(OS_HAL_SEMA42_GATE != OS_HAL_SEMA42_LOCK_VALUE);

  /* #30 If the spinlock variable is already locked. */
  if(*Spinlock == OS_HAL_SPINLOCK_LOCKED)
  {
    /* #40 Set the result value to not succeeded. */
    result = !(OS_HAL_SPINLOCKSUCCEEDED);
  }
  /* #50 Otherwise (spinlock variable is unlocked). */
  else
  {
    /* #60 Lock the spinlock variable. */
    *Spinlock = OS_HAL_SPINLOCK_LOCKED;                                                                                /* SBSW_OS_HAL_PWA_CALLER */
    /* #70 Set the result value to succeeded. */
    result = OS_HAL_SPINLOCKSUCCEEDED;
  }

  /* #80 Release the hardware spinlock. */
  OS_HAL_SEMA42_GATE = OS_HAL_SEMA42_UNLOCK_VALUE;

  /* #90 Restore previous interrupt state. */
  Os_Hal_RestorePriorIntState(state);

  /* #100 Return the result value. */
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
  Os_Hal_INTC_EnableNotMappedSource(XSigConfig->Source);
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
  /* #10 Trigger interrupt in the IRCPGR specific register. */
  OS_HAL_MSCM_IRCPGR(XSigConfig->TargetCoreId) |= (uint32)OS_HAL_MSCM_IRCPGR_TRIGGER_MASK;
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
  /* #10 Acknowledge interrupt in the IRCPSR specific register. */
  OS_HAL_MSCM_IRCPSR(XSigConfig->TargetCoreId) = (uint32)OS_HAL_MSCM_IRCPSR_ACKNOWLEDGE_MASK;
}

/***********************************************************************************************************************
 *  Os_Hal_CoreStart()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* COV_OS_HALPLATFORMMULTICOREUNSUPPORTED */ /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_CoreStart,
(
  P2CONST(Os_Hal_CoreConfigType, AUTOMATIC, OS_CONST) Core
))                                                                                                                      /* COV_OS_HALPLATFORMMULTICOREUNSUPPORTED */
{

  volatile uint32 ResetMask;
  volatile uint32 CoreStatusRegisterAddress;

  /* #10 Set the core boot address and enable the clock. */
  if(Core->CoreId == 4)                                                                                         /* COV_OS_INVSTATE */
  {
    *(volatile uint32*)(OS_HAL_MC_ME_PRTN0_CORE0_BASE + MC_ME_PRTN0_CORE_ADDR_OFFSET) =                                 /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
                                                                                (Core->CoreStartAddress) | 1;
    *(volatile uint32*)(OS_HAL_MC_ME_PRTN0_CORE0_BASE + MC_ME_PRTN0_CORE_PCONF_OFFSET) |= 1;                            /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
    ResetMask = MC_RGM_PRST0_0_CORE0_MASK;
    CoreStatusRegisterAddress = OS_HAL_MC_ME_PRTN0_CORE0_BASE + MC_ME_PRTN0_CORE_STAT_OFFSET;
  }else if(Core->CoreId == 5)
  {
    *(volatile uint32*)(OS_HAL_MC_ME_PRTN0_CORE1_BASE + MC_ME_PRTN0_CORE_ADDR_OFFSET) =                                 /* PRQA S 0303 */ /* MD_Os_Hal_0303, MD_Os_Hal_0428 */
                                                                                (Core->CoreStartAddress) | 1;
    *(volatile uint32*)(OS_HAL_MC_ME_PRTN0_CORE1_BASE + MC_ME_PRTN0_CORE_PCONF_OFFSET) |= 1;                            /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
    ResetMask = MC_RGM_PRST0_0_CORE1_MASK;
    CoreStatusRegisterAddress = OS_HAL_MC_ME_PRTN0_CORE1_BASE + MC_ME_PRTN0_CORE_STAT_OFFSET;
  }else if (Core->CoreId == 6)
  {
    *(volatile uint32*)(OS_HAL_MC_ME_PRTN0_CORE2_BASE + MC_ME_PRTN0_CORE_ADDR_OFFSET) =                                 /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
                                                                                (Core->CoreStartAddress) | 1;
    *(volatile uint32*)(OS_HAL_MC_ME_PRTN0_CORE2_BASE + MC_ME_PRTN0_CORE_PCONF_OFFSET) |= 1;                            /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
    ResetMask = MC_RGM_PRST0_0_CORE2_MASK;
    CoreStatusRegisterAddress = OS_HAL_MC_ME_PRTN0_CORE2_BASE + MC_ME_PRTN0_CORE_STAT_OFFSET;
  } else
  {
    /* Case may not occur. */
    Os_Hal_CoreFreeze();
  }

  /* #20 Wait Until clock is enabled. */
  while (((*(volatile uint32*)(CoreStatusRegisterAddress)) & 0x00000001UL)                                              /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
         != 1)
  {

  }

  /* #30 Release the core reset.*/
  *(volatile uint32*)(OS_HAL_RGM_PRST_BASE) &= ~ResetMask;                                                               /* PRQA S 0303 */ /* MD_Os_Hal_0303 */

  /* #40 Wait until reset has been deasserted. */
  while (((*(volatile uint32*)(OS_HAL_RGM_PSTAT_BASE)) & ResetMask)                                                     /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
         == 1)
  {

  }
}

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* OS_HAL_CORE_S32VX_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core_S32x.h
 **********************************************************************************************************************/

