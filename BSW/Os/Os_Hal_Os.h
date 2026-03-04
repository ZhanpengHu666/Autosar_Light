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
 *  \addtogroup Os_Hal_Os
 *  \{
 *
 *  \file
 *  \brief      HAL interfaces which are visible to the user.
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Benjamin Seifert              virbse        Vector Informatik GmbH
 *  Bilal Parvez                  visbpz        Vector Informatik GmbH
 *  Ivan Begert                   virbiv        Vector Informatik GmbH
 *  Michael Kock                  vismkk        Vector Informatik GmbH
 *  Martin Schultheiss            virsmn        Vector Informatik GmbH
 *  David Feuerstein              visdfe        Vector Informatik GmbH
 *  Senol Cendere                 visces        Vector Informatik GmbH
 *  Hendrik Stoffers              visshk        Vector Informatik GmbH
 *  Rainer Kuennemeyer            visrk         Vector Informatik GmbH
 *  Da He                         visdhe        Vector Informatik GmbH
 *  Stefano Simoncelli            virsso        Vector Informatik GmbH
 *  Andreas Jehl                  virjas        Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  02.00.00  2017-04-06  virbse  WORKITEM15149 Initial version for ARM Cortex-M
 *  02.01.00  2017-05-04  vismkk  -             Internal improvements.
 *            2017-05-22  virbse  STORY-993     Internal improvements.
 *                        virsmn  STORY-1029    Memory protection support for S32K and MWCT101x devices
 *                                ESCAN00095068 Compiler error: Multiple defined MPU functions
 *  02.01.01  2017-05-31  visrk   -             Internal improvements.
 *  02.02.00  2017-06-01  visdfe  ESCAN00094046 Wrong validation of the maximum available MPU regions
 *  02.03.00  2017-06-29  visces  STORYC-1302   Support for cat. 0 ISRs
 *  02.04.00  2017-07-13  visshk  -             Internal improvements
 *  02.05.00  2017-08-15  virsmn  ESCAN00094867 Compiler warning: warning #1514-D:
 *                                              incorrect GHS #pragma: small data area is not supported in this configuration
 *                        visrk   -             Internal improvements
 *                        visdhe  STORY-1752    Support for ARM compiler with Cortex-M platform
 *                        virbiv  ESCAN00096081 Compiler Warning  #32-D: expression must have arithmetic type in
 *                                              Os_Hal_Context_Lcfg.c
 *                        virsmn  ESCAN00095677 CortexM CoreMPU wrongly reprogrammed
 *                        virsso  STORYC-1891   Support for TI compiler as BETA
 *  02.06.00  2017-09-05  virsso  ESCAN00096420 Compiler error: "OS_HAL_MP_STACK_MAXSIZE_AND_ATTRIBUTES" not defined
 *  02.07.00  2017-10-10  visces  ESCAN00095552 Free Running Timers configured as non High Resolution Counters do not
 *                                              work properly.
 *  02.08.00  2017-10-18  virsso  ESCAN00096902 Compiler warning: OS_HAL_COMPILER_TINT_H is used as a header guard,
 *                                              followed by #define of a different macro [-Wheader-guard]
 *                                ESCAN00096476 "OS_CODE" memory section is not properly linked
 *                        virbse  FEAT-2816     Support shared stack for non-preemptive Basic tasks
 *                                FEAT-2815     Support shared stack for tasks with same internal resource
 *                        virsso  ESCAN00097137 The pre-config of MPU region for non-trusted application contains the
 *                                              wrong accessing rights
 *  02.09.00  2017-11-03  virsmn  ESCAN00096854 Usage of High Resolution Timer and Master Protection Mechanism of INTC
 *                                              could lead to protection violation.
 *                        visdhe  STORYC-2762   Support OS SC1/SC2 with GCC Compiler Production QM
 *                        virbiv  ESCAN00097206 Stack corruption during context switch if FPU is used
 *  02.10.00  2017-11-22  visshk  STORYC-1751   Performance improvements for some IOC configurations
 *                        visbpz  STORY-2769    OS Interrupt API optimization by replacement of a call sequence for
 *                                              modification of the global interrupt flag.
 *                        virsso  STORYC-3110   Support for TDA2Eco derivative.
 *                        virsso  ESCAN00094835 Spinlock API may cause a fatal exception with IAR compiler
 *  02.11.00  2017-01-10  virsso  STORYC-3218   Support for user configurable FPU cotext saving
 *                        virjas  ESCAN00098049 Undefined behavior of OS after context switch
 *                        virsso  ESCAN00097806 Spinlock API may cause a fatal exception with GCC Linaro compiler
 *  02.12.00  2017-01-29  virjas  -             Internal improvements
 *                        virsmn  STORYC-3282   Support for user Msr settings.
 *  02.12.02  2018-03-05  virsso  ESCAN00098567 Stack corruption in trap handler if hardware fpu is used
 *  02.13.00  2018-03-09  virsmn  STORYC-3042   Support for OS internal exception detection.
 *                        virsso  ESCAN00098061 FPU registers not correctly saved/restored during context switch
 *                        virsso  ESCAN00096334 BETA version - the BSW module has a feature with BETA state
 *                                              (Support for TI compiler)
 *                        virsso  ESCAN00098749 Os platform specific functions are wrongly mapped in case of TI compiler
 *  02.14.00  2018-03-23  visbpz  STORYC-4068   Performance improvment by avoiding traps
 *  02.15.00  2018-04-23  virsmn  STORYC-4799   Added coverage justifications for S32K derivatives.
 *            2018-05-03  virsmn  STORYC-3965   Added support for derivatives without interrupt level support.
 *  02.16.00  2018-05-14  virsmn  STORYC-3320   Added support for interrupt mapping feature.
 *            2018-05-15  virsso  ESCAN00099062 Wrong interrupt level restored after non trusted function call
 *                                              because of IAR compiler optimization.
 *  02.17.00  2018-06-11  virsso  ESCAN00099374 Not all the MPU regions can be used on S32K148.
 *            2018-06-14  visbpz  STORY-5018    Unhandled Exception not available for SC >= SC3
 *            2018-06-27  virsso  STORYC-5587   Support for Traveo2(CYT2Bx) peripheral interrupt handling.
 *                                ESCAN00099836 Compiler reports error because of typo in include file name.
 *            2018-06-29  virsmn  STORYC-5594   Added support for aggregated stack configuration view.
 *  02.18.00  2018-07-20  visbpz  STORYC-5671   Added support for IMX8x peripheral interrupt handling.
 *  02.19.00  2018-08-03  virsso  STORYC-6091   Added support for S32x peripheral interrupt handling and multicore.
 *            2018-08-08  virsmn  STORYC-4094   Achieve 100 percent variant coverage.
 *            2018-08-16  virsso  ESCAN00100283 Store immediate overlapping exception return might vector to incorrect 
 *                                              interrupt
 *            2018-08-16  visbpz  ESCAN00100164 BETA version - the BSW module has a feature with BETA state 
 *                                              (IMX8x support)
 *  02.20.00  2018-09-14  visbpz  -             Internal Improvements.
 **********************************************************************************************************************/

#if !defined (OS_HAL_OS_H)                                                                                              /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_OS_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_OsInt.h"

/* Os kernel module dependencies */
# include "Os_Lcfg.h"

/* Os hal dependencies */


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/
/* ----- Component version information ----- */
# define OS_HAL_SW_MAJOR_VERSION                     (2u)
# define OS_HAL_SW_MINOR_VERSION                     (20u)
# define OS_HAL_SW_PATCH_VERSION                     (0u)

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#endif /* OS_HAL_OS_H */


/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Os.h
 **********************************************************************************************************************/
