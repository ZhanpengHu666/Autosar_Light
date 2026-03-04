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
 * \addtogroup  Os_Hal_Derivative
 * \{
 *
 * \file
 * \brief  This file contains derivative specific information.
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 *********************************************************************************************************************/

#if !defined (OS_HAL_DERIVATIVE_S32XINT_H) /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_DERIVATIVE_S32XINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  S32x
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Core
 *********************************************************************************************************************/
/*! Defines whether ARMv7 CortexM Architecture is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_ARCH_V7M     (STD_ON)

/*! Defines whether V7M Exceptions Handling is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_EXCEPTIONS_V7M     (STD_ON)


/**********************************************************************************************************************
 *  Interrupt Controller
 *********************************************************************************************************************/

/*! Defines whether NVIC_S32 interrupt controller is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_INTC_NVIC_S32     (STD_ON)

/*! NVIC, base address. */
# define OS_HAL_INTC_NVIC_BASE              (0xE000E000UL)

/*! MSCM, base address. */
# define OS_HAL_INTC_MSCM_BASE              (0x40198000UL)

/*! MSCM_IRSPRC address. */
# define OS_HAL_MSCM_IRSPRC_ASM          0x40198880
# define OS_HAL_MSCM_IRSPRC_BASE        (0x40198880UL)

/*! Number of available IRQ. */
# define OS_HAL_INTC_NUMBER_OF_IRQS     (240UL)

/**********************************************************************************************************************
 *  Timer
 *********************************************************************************************************************/
/*! Defines whether FRT_UNSUPPORTED Timer Unit is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_TIMER_FRT_UNSUPPORTED     (STD_ON)

/*! Defines whether PIT_SYSTICK Timer Unit is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_TIMER_PIT_SYSTICK     (STD_ON)


/**********************************************************************************************************************
 *  Memory Protection
 *********************************************************************************************************************/
/*! Defines whether PMSAV7M Memory Protection Architecture is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_MEMORY_PROTECTION_PMSAV7M         (STD_ON)
# define OS_HAL_MPU_BASE_ADDRESS_ASM              0xE000ED98
# define OS_HAL_MPU_BASE_ADDRESS                  (0xE000ED98UL)

/**********************************************************************************************************************
 *  Physical Core Modules
 *********************************************************************************************************************/
/*! RGM_PRST_BASE address */
# define OS_HAL_RGM_PRST_BASE                     (0x40078040UL)
/*! RGM_PSTAT_BASE address */
# define OS_HAL_RGM_PSTAT_BASE                    (0x40078140UL)

/*! MC_ME_PRTN0_CORE0_BASE address */
# define OS_HAL_MC_ME_PRTN0_CORE0_BASE            (0x40088140UL)
/*! MC_ME_PRTN0_CORE1_BASE address */
# define OS_HAL_MC_ME_PRTN0_CORE1_BASE            (0x40088160UL)
/*! MC_ME_PRTN0_CORE2_BASE address */
# define OS_HAL_MC_ME_PRTN0_CORE2_BASE            (0x40088180UL)


#endif /* OS_HAL_DERIVATIVE_S32XINT_H */

/*!
 * \}
 */
/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Derivative_S32xInt.h
 *********************************************************************************************************************/
