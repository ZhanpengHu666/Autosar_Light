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
 *  \addtogroup  Os_Hal_Core
 *  \{
 *
 *  \file        Os_Hal_Core.c
 *  \brief       Core related primitives which don't have to be inlined.
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

                                                                                                                        /* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */


#define OS_HAL_CORE_SOURCE

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Derivative.h"
#include "Os_Hal_Core.h"
#include "Os_Hal_Interrupt.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
#include "Os_Hal_Os.h"
#include "Os_Hal_Cfg.h"

/***********************************************************************************************************************
 *  VERSION CHECK
 **********************************************************************************************************************/

/* Check the version of OS header file */
#if (  (OS_HAL_SW_MAJOR_VERSION != (2u)) \
    || (OS_HAL_SW_MINOR_VERSION != (20u)) \
    || (OS_HAL_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of Os_Hal_Core.c and Os_Hal_Os.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (OS_CFG_HAL_MAJOR_VERSION != (2u)) \
    || (OS_CFG_HAL_MINOR_VERSION != (16u)) )
# error "Version numbers of Os_Hal_Core.c and Os_Hal_Cfg.h are inconsistent!"
#endif

/***********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define OS_START_SEC_CODE
#include "Os_MemMap_OsCode.h"                                                                                           /* PRQA S 5087 */ /* MD_MSR_19.1 */


/***********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_CoreInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, OS_CODE) Os_Hal_CoreInit
(
  P2CONST(Os_Hal_CoreAsrConfigType, AUTOMATIC, OS_CONST) Config
)
{
  /* #10 Initialize exception handling. */
  Os_Hal_Core_InitExceptions(Config);                                                                                   /* SBSW_OS_HAL_FC_CALLER */

  /* #20 Initialize interrupt handling. */
  Os_Hal_INTC_InitializeVectorTable(Config->VectorTable);                                                               /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreInitHardware()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, OS_CODE) Os_Hal_CoreInitHardware(P2CONST(Os_Hal_SystemConfigType, AUTOMATIC, OS_CONST) Config)
{
  /* #10 Nop. */
  OS_IGNORE_UNREF_PARAM(Config);                                                                                        /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreFreeze()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(void, OS_CODE, OS_NORETURN, Os_Hal_CoreFreeze,                                             /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
(
  void
))                                                                                                                      /* COV_OS_HALARMCMCOREFREEZE */
{
  /* #10 Loop forever. */
  while( (1 == 1) )                                                                                                     /* COV_OS_HALARMCMCOREFREEZE */
  {
    Os_Hal_Nop();
  }
}


#define OS_STOP_SEC_CODE
#include "Os_MemMap_OsCode.h"                                                                                           /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* START_COVERAGE_JUSTIFICATION

\ID COV_OS_HALARMCMCOREFREEZE
  \ACCEPT XX
  \REASON This function is called from Os_ErrKernelPanic() right after the panic hook has returned. As the panic hook
          is the last possible exit point for the tests, Os_Hal_CoreFreeze cannot be covered in tests. Because of the
          simplicity of the code, the performed code inspection results in sufficient quality.

\ID COV_OS_HALARMCMSTATICCODEANALYSIS
  \ACCEPT TX
  \REASON The code after this condition is always covered as it just needs to be masked out during static code analysis.
          See also [COV_OS_STATICCODEANALYSIS].

Justifications for core:

\ID COV_OS_HALPLATFORMCLZAVAILABILITY
  \ACCEPT TX
  \REASON The condition is hardware dependent always true. The unnecessary code parts should be
          removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
          always just test the code for the respective platform. No risk as the remaining code shall be optimized
          away. (Other platforms may set ACCEPT XF with a similar justification)

\ID COV_OS_HALPLATFORMTHREADPOINTERUSERREADABILITY_TX_XF
  \ACCEPT TX
  \REASON The condition is hardware dependent always true. The unnecessary code parts should be
          removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
          always just test the code for the respective platform. No risk as the remaining code shall be optimized
          away. (Other platforms may set ACCEPT XF with a similar justification)

\ID COV_OS_HALPLATFORMCOREIDUSERREADABILITY_TX_XF
   \ACCEPT TX
   \REASON The condition is hardware dependent always true. The unnecessary code parts should be
           removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
           always just test the code for the respective platform. No risk as the remaining code shall be optimized
           away. (Other platforms may set ACCEPT XF with a similar justification)

\ID COV_OS_HALPLATFORMPRIVILEGEMODEUSERREADABILITY
  \ACCEPT TX
  \REASON The condition is hardware dependent always true. The unnecessary code parts should be
          removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
          always just test the code for the respective platform. No risk as the remaining code shall be optimized
          away.

\ID COV_OS_HALPLATFORMTHREADPOINTERUSERREADABILITY_XX
  \ACCEPT XX
  \REASON Due to the hardware ability to read the current privileges directly, this function is never called. The
          unnecessary code parts should be removed by compiler optimization. As the tests run on each platform, the OS
          is to be released for, we always just test the code for the respective platform. No risk as the remaining code
          shall be optimized away.

\ID COV_OS_HALPLATFORMCLEARPENDINGAVAILABILITY
   \ACCEPT TX
   \REASON The condition is hardware dependent always true. The unnecessary code parts should be
           removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
           always just test the code for the respective platform. No risk as the remaining code shall be optimized
           away. (Other platforms may set ACCEPT XF with a similar justification)

\ID COV_OS_HALPLATFORMBITLIBCLZ
  \ACCEPT XX
  \REASON This code is meant as library code for the software implementation of Os_Bit_CountLeadingZeros(). As this
          processor provides a hardware solution, this code is unused. However, the function is extremely simple,
          code inspected and unit tested. It is typically optimized away by the linker. Therefore, the risk of
          keeping this code is expected to be low.

\ID COV_OS_HALPLATFORMUNHANDLEDSYSCALL
  \ACCEPT TF
  \REASON This function is only reacheable on some platforms. However, unit test and code inspection have not found
          any risk in keeping this code. The function is fully tested on those platforms which have potentially
          unhandled system calls.

\ID COV_OS_HALPLATFORMAPPISPRIVILEGED
  \ACCEPT XX
  \REASON Platform is able to read privileges from hardware. Thus, this function is never used for determination of
          current privileges.

\ID COV_OS_HALPLATFORMCOREINTERRUPTSUNSUPPORTED
  \ACCEPT XF
  \REASON The loop invariant is never true, because on this platform all interrupts are system wide. They are initialized
          in Os_SystemInterruptHandlingInit.

\ID COV_OS_HALPLATFORMEXCEPTIONCONTEXTUNSUPPORTED
   \ACCEPT XF
   \ACCEPT XX
   \REASON The feature "exception context" is not supported on this platform.

\ID COV_OS_HALPLATFORMEXCEPTIONCONTEXTAVAILABILITY
   \ACCEPT TX
   \REASON The feature "exception context" is not available on this platform.

\ID COV_OS_HALPLATFORM_NEED_NO_TRAP_IOC_MULTIQUEUE
  \ACCEPT XF
  \ACCEPT XX
  \REASON This path can never be reached on this platform. As IsTrapRequired is always false for multi-queue IOCs
          and the thread pointer is readable in user mode on this platform, no trap is necessary. However, the code is
          unit tested as well as tested on other platforms. Aditionally it is similar to the code used for the call of
          other OS API functios. So there is no risk in keeping this code.

\ID COV_OS_HALPLATFORMGLOBAL2LEVELSUPPORTED
   \ACCEPT XF
   \ACCEPT XX
   \REASON Global to level switch is not supported on this platform.

END_COVERAGE_JUSTIFICATION */

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_OS_HAL_PWA_CALLER
 \DESCRIPTION    A write access is performed on a pointer, which is coming directly from the caller.
 \COUNTERMEASURE \N No measure is required, because the caller has to check the validity.

\ID SBSW_OS_HAL_FC_CALLER
 \DESCRIPTION    A function is called with one or more pointer parameters, which are coming directly from the caller.
 \COUNTERMEASURE \N No measure is required, because the caller has to check the validity.

\ID SBSW_OS_HAL_FC_LOCAL_VAR
 \DESCRIPTION    A function is called with one or more pointer parameters, which are pointing to local variables.
 \COUNTERMEASURE \N No measure is required, because local variables are always valid.

\ID SBSW_OS_HAL_FC_MPUCONFIG
 \DESCRIPTION    A function is called with a pointer parameter.
 \COUNTERMEASURE \N No measure required, because this pointer will not be used for write operation by the callee.

\ID SBSW_OS_HAL_FC_STACKCONFIG
 \DESCRIPTION    A function is called with a pointer parameter. The pointer references a mandatory structure inside the
                 CONST section. The array access is allways valid because Os_Hal_CoreGetId allways returns 0.
 \COUNTERMEASURE \N No measure required, because this pointer will not be used for write operation by the callee.

\ID SBSW_OS_HAL_INTC_INITIALIZEVECTORTABLE_001
 \DESCRIPTION    A write access is performed on the Vector Table Offset Register (VTOR). The validity of
                 OS_HAL_INTC_SCB_VTOR is checked by review. Additionally the Safety manual should state that
                 the functionality of each configured ISR has to be checked for its correctness.
 \COUNTERMEASURE \S [CM_OS_HAL_ISRCONFIG_S]

\ID SBSW_OS_HAL_INTC_NVIC_IPR
 \DESCRIPTION    A write access is performed on the Interrupt Priority Registers (IPR). The validity of
                 OS_HAL_INTC_NVIC_IPR() is checked by review. Additionally, the Safety manual should state that
                 the functionality of each configured ISR has to be checked for its correctness.
 \COUNTERMEASURE \S [CM_OS_HAL_ISRCONFIG_S]

\ID SBSW_OS_HAL_INTC_NVIC_ISER
 \DESCRIPTION    A write access is performed on the Interrupt Set-Enable Registers (ISER). The validity of
                 OS_HAL_INTC_NVIC_ISER() is checked by review. Additionally, the Safety manual should state that
                 the functionality of each configured ISR has to be checked for its correctness.
 \COUNTERMEASURE \S [CM_OS_HAL_ISRCONFIG_S]

\ID SBSW_OS_HAL_INTC_NVIC_ICER
 \DESCRIPTION    A write access is performed on the Interrupt Clear-Enable Registers (ICER). The validity of
                 OS_HAL_INTC_NVIC_ICER() is checked by review. Additionally, the Safety manual should state that
                 the functionality of each configured ISR has to be checked for its correctness.
 \COUNTERMEASURE \S [CM_OS_HAL_ISRCONFIG_S]

\ID SBSW_OS_HAL_INTC_NVIC_ICPR
 \DESCRIPTION    A write access is performed on the Interrupt Clear-Pending Registers (ICPR). The validity of
                 OS_HAL_INTC_NVIC_ICPR() is checked by review. Additionally, the Safety manual should state that
                 the functionality of each configured ISR has to be checked for its correctness.
 \COUNTERMEASURE \S [CM_OS_HAL_ISRCONFIG_S]

\ID SBSW_OS_HAL_INTC_NVIC_ISPR
 \DESCRIPTION    A write access is performed on the Interrupt Set-Pending Registers (ISPR). The validity of
                 OS_HAL_INTC_NVIC_ISPR() is checked by review. Additionally, the Safety manual should state that
                 the functionality of each configured ISR has to be checked for its correctness.
 \COUNTERMEASURE \S [CM_OS_HAL_ISRCONFIG_S]

 \ID SBSW_OS_HAL_INTC_NVIC_STEER
 \DESCRIPTION    A write access is performed on the Steer Module Registers (IRQSTEER). The validity of
                 OS_HAL_INTC_STEER_BASE and register write implementation in the static code is checked by review.
                 Additionally, the Safety manual should state that the functionality of each configured ISR has to be
                 checked for its correctness.
 \COUNTERMEASURE \S [CM_OS_HAL_ISRCONFIG_S]

\ID SBSW_OS_HAL_CORE_INITEXCEPTIONS_001
 \DESCRIPTION    A write access is performed on the System Handler Configuration Registers. The validity of the
                 base address OS_HAL_SCS_SH_BASE_ADDRESS is checked by review.
 \COUNTERMEASURE \N No measure is required, because the validity of the pointer is checked by review.

\ID SBSW_OS_HAL_MP_MPU_CTRL
 \DESCRIPTION    A write access is performed on the MPU Control Register (MPU_CTRL). The validity of the
                 address OS_HAL_MP_MPU_CTRL is checked by review.
 \COUNTERMEASURE \N No measure is required, because the validity of the pointer is checked by review.

\ID SBSW_OS_HAL_MP_MPU_RNR
 \DESCRIPTION    A write access is performed on the MPU Region Number Register (MPU_RNR). The validity of the
                 address OS_HAL_MP_MPU_RNR is checked by review.
 \COUNTERMEASURE \N No measure is required, because the validity of the pointer is checked by review.

\ID SBSW_OS_HAL_MP_MPU_RASR
 \DESCRIPTION    A write access is performed on the MPU Region Attribute and Size Register (MPU_RASR).
                 The validity of the address OS_HAL_MP_MPU_RASR is checked by review.
 \COUNTERMEASURE \N No measure is required, because the validity of the pointer is checked by review.

\ID SBSW_OS_HAL_MP_MPU_RBAR
 \DESCRIPTION    A write access is performed on the MPU Region Base Address Register (MPU_RBAR). The validity of the
                 address OS_HAL_MP_MPU_RBAR is checked by review.
 \COUNTERMEASURE \N No measure is required, because the validity of the pointer is checked by review.

\ID SBSW_OS_HAL_CORESETTHREAD_001
 \DESCRIPTION    A write access is performed to a Core2Thread pointer type. The Core2Thread object is derived
                 with an index from the Core2Thread array.
 \COUNTERMEASURE \S Safety manual should state that the generated OsCfg_Hal_Core2Thread object of type
                 Os_Hal_Core2ThreadConfigType in _Os_Hal_Core_Lcfg.c_ has to be checked for its correctness.
                 The array Core2Thread in the object OsCfg_Hal_Core2Thread contains all physical cores.
                 For each existing physical hardware core identifier there shall be one corresponding entry inside
                 the array which is indexed by the physical hardware core identifier provided directly by the
                 hardware registers. SMI-30843

\ID SBSW_OS_HAL_TIMER_SYSTICK_SYST_CSR
 \DESCRIPTION    A write access is performed on the SysTick Control and Status Register (SYST_CSR). The validity of the
                 address OS_HAL_TIMER_SYSTICK_SYST_CSR is checked by review.
 \COUNTERMEASURE \N No measure is required, because the validity of the pointer is checked by review.

\ID SBSW_OS_HAL_TIMER_SYSTICK_SYST_RVR
 \DESCRIPTION    A write access is performed on the SysTick Reload Value Register (SYST_RVR). The validity of the
                 address OS_HAL_TIMER_SYSTICK_SYST_RVR is checked by review.
 \COUNTERMEASURE \N No measure is required, because the validity of the pointer is checked by review.

\ID SBSW_OS_HAL_TIMER_SYSTICK_SYST_CVR
 \DESCRIPTION    A write access is performed on the SysTick Current Value Register (SYST_CVR). The validity of the
                 address OS_HAL_TIMER_SYSTICK_SYST_CVR is checked by review.
 \COUNTERMEASURE \N No measure is required, because the validity of the pointer is checked by review.

\ID SBSW_OS_HAL_CONTEXTSUSPEND
 \DESCRIPTION    A write access is performed on a pointer, which is coming directly from the caller. All passed pointer
                 reference members of the Os_Hal_ContextType. The pointer to this data type comes directly from the
                 caller.
 \COUNTERMEASURE \N No measure is required, because the caller has to check the validity.

\ID SBSW_OS_HAL_PWA_FRTCONFIG_RTT
 \DESCRIPTION    A write access is performed on a pointer, which is in the generated timer configuration for STM of
                 type Os_Hal_TimerFrtConfigType. The pointer TimerConfig is coming directly from the caller.
 \COUNTERMEASURE \S Safety manual should state that the generated FRT configuration of type _Os_Hal_TimerFrtConfigType_
                 in _Os_Hal_Timer_Lcfg.c_ has to be checked for its correctness.
                 More in details:
                 * RTT configuration base address of type _Os_Hal_TimerRttModuleType*_ has to match the hardware manual
                   specification.
                 * InterruptSource has to match the configuration.
                 SMI-30842

\ID SBSW_OS_HAL_FC_POINTER2LOCAL
 \DESCRIPTION    Pass a reference to a local variable.
 \COUNTERMEASURE \N No measure required, as the passed pointer refers to a local variable and the called function
                    allows that the existence of the local variable ends on return.

\ID SBSW_OS_HAL_SMPU_ADDR
 \DESCRIPTION    Write address is performed on a pointer to an SMPU registers. (from Os_Hal_MemoryProtection_NXP.h;
                 Base addresses are defined within the derivative headers)
 \COUNTERMEASURE \N No measure is required, because the SMPU addresses and offsets are reviewed.

\CM CM_OS_HAL_ISRCONFIG_S
                 Safety manual should state that the functionality of each configured ISR has to be checked for its
                 correctness. This includes the correct call of the ISR handler as well as enabling, disabling,
                 reading the enable state, reading the pending state and clearing of the pending information of
                 the corresponding ISR sources. SMI-491

SBSW_JUSTIFICATION_END */

/*!
 * \}
 */
/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core.c
 **********************************************************************************************************************/
