
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  ARMBrsHw.h
      Project:  Vector Basic Runtime System
       Module:  BrsHw for all platforms with ARM core

  \brief Description:  This is a global, hardware-independent header file for the ARM-BRS.
                       This file includes all non-hardware dependent functions, e.g. the timer-configuration for the
                       Millisecond-Timebase. All the (hardware depending) rest needs to be defined in BrsHw.c

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

#ifndef _ARMBRSHW_H_
#define _ARMBRSHW_H_

/**********************************************************************************************************************
  MODULE VERSION
**********************************************************************************************************************/
/*
 * Description: This is the BrsHw main and bug fix version. The version numbers are BCD coded. 
 *              E.g. a main version of 1.23 is coded with 0x0123, a bug fix version of 9 is coded 0x09.
 */
#define ARMBRSHW_CORTEXM_VERSION        0x0305u
#define ARMBRSHW_CORTEXM_BUGFIX_VERSION 0x03u

#define ARMBRSHW_CORTEXA_VERSION        0x0303u
#define ARMBRSHW_CORTEXA_BUGFIX_VERSION 0x00u

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  Compiler abstraction
**********************************************************************************************************************/
#if defined (BRS_COMP_GHS)
  #define ___asm(c)       __asm_(c)
  #define __asm_(c)       asm(" " #c);
  #define __as1(c, d)     __as1_(c, d)
  #define __as1_(c, d)    asm(" " #c " , " #d);
  #define BRS_ISR_KEYWORD __interrupt

#else
  #error: "Compiler not yet supported"
#endif

/**********************************************************************************************************************
  BrsHW configuration
**********************************************************************************************************************/
#if defined (BRS_OS_USECASE_OS)
/* nothing to be done here yet */

#elif defined (BRS_OS_USECASE_OSGEN7)
/* nothing to be done here yet */

#else
  #error "Configured OS_USECASE is not supported (Organi filtered because of ALM attributes or wrong set within Makefile.config)"
#endif

/**********************************************************************************************************************
  Global variables
**********************************************************************************************************************/

/**********************************************************************************************************************
  Global const variables
**********************************************************************************************************************/

/**********************************************************************************************************************
  Global function prototypes
**********************************************************************************************************************/

#if defined (BRS_CPU_CORE_CORTEX_M0) || defined (BRS_CPU_CORE_CORTEX_M0PLUS) || defined (BRS_CPU_CORE_CORTEX_M3) || \
    defined (BRS_CPU_CORE_CORTEX_M4) || defined (BRS_CPU_CORE_CORTEX_M4F)    || defined (BRS_CPU_CORE_CORTEX_M7)

#endif /*Cortex-M Series*/

#if !defined (BRS_OS_USECASE_OSGEN7)
#if defined (BRS_VECTOR_TABLE_LOCATION_RAM)
# if !defined (BRS_DERIVATIVE_IMX6X) || defined (BRS_CPU_CORE_CORTEX_A9)
/*****************************************************************************/
/**
 * @brief      Function to tell the MCU the new Vector-Table-Location (in RAM)
 * @pre        No interrupt occurrence before (this) function call
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    At beginning of BrsHwConfigureInterruptsAtPowerOn(), if needed!
 */
/*****************************************************************************/
  void BrsHwVectorTableMovement(void);
# endif /*!BRS_DERIVATIVE_IMX6X||BRS_CPU_CORE_CORTEX_A9*/
#endif /*BRS_VECTOR_TABLE_LOCATION_RAM*/
#endif /*!BRS_OS_USECASE_OSGEN7*/

/*****************************************************************************/
/**
 * @brief      Disable the global system interrupt and initialize the INT
 *             lock handler variables.
 * @pre        Must be the first function call in main@BrsMain
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain at power on initialization
 */
/*****************************************************************************/
void BrsHwDisableInterruptAtPowerOn(void);

#if !defined (BRS_OS_USECASE_OSGEN7)
/*****************************************************************************/
/**
 * @brief      Enable the global system interrupt the first time
 * @pre        Must be called after all initializations are done
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain at power on initialization
 */
/*****************************************************************************/
void BrsHwEnableInterruptAtPowerOn(void);
#endif /*!BRS_OS_USECASE_OSGEN7*/

/*****************************************************************************/
/**
 * @brief      Disables the global interrupt of the micro. This is done in a
 *             "save way" to allow also nested calls of BrsHwDisableInterrupt
 *             and BrsHwRestoreInterrupt. The first call of BrsHwDisableInterrupt
 *             stores the current state of the global INT flag and the last
 *             call to BrsHwRestoreInterrupt restores the state.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from all modules to disable the global interrupt
 */
/*****************************************************************************/
void BrsHwDisableInterrupt(void);

/*****************************************************************************/
/**
 * @brief      Restores the state of the global interrupt of the micro. This
 *             is done in a "save way" to allow also nested calls of
 *             BrsHwDisableInterrupt and BrsHwRestoreInterrupt. The first call
 *             of BrsHwDisableInterrupt stores the current state of the global
 *             INT flag and the last call to BrsHwRestoreInterrupt restores the
 *             state.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from all modules to enable the global interrupt
 */
/*****************************************************************************/
void BrsHwRestoreInterrupt(void);

/*****************************************************************************/
/**
 * @brief      This API is used for the BRS time measurement support to get a
 *             default time value for all measurements with this platform to
 *             be able to compare time measurements on different dates based
 *             on this time result.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from TimeMeasurement
 */
/*****************************************************************************/
void BrsHwTime100NOP(void);

#endif /*_ARMBRSHW_H_*/
