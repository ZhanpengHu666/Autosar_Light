
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
  \file  File:  ARMBrsHw_CortexM.c
      Project:  Vector Basic Runtime System
       Module:  BrsHw for all platforms with ARM core Cortex-M
     Template:  This file is reviewed according to zBrs_Template@root[2.02.00]

  \brief Description:  This is a global, hardware-independent file for the ARM-BRS.
                       This file includes all non-hardware dependent functions, e.g. the timer-configuration for the
                       Millisecond-Timebase. All the (hardware depending) rest needs to be defined in BrsHw.c

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
 ----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
  ----------------------------  ------------  -------------------------------------------------------------------------
  Michael Tiran                 vismin        Vector Informatik GmbH
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Jens Haerer                   visjhr        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
  Sherif Elsabbahy              vissey        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Hakan Capci                   vishci        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  03.00.00  2016-04-28  vismin  Initial Version for Cortex M based on ARMBrsHw.c (Ver. 02.00.19)
            2016-05-31  visbwa  Review
  03.00.01  2016-06-01  visbwa  Fixed encapsulation of BrsHwRestoreInterrupt() (also necessary for UseCase OS)
  03.00.02  2016-06-21  visbwa  Changed BrsHwEnableInterruptAtPowerOn() (enabling of Interrupts also necessary with OS)
                                fixed encapsulation within BrsHwTimeBaseInitPowerOn()
  03.00.03  2016-06-22  vismin  Adapted complete file header structure for zBrs_Template@root[2.00.01]
  03.00.04  2016-06-21  visbwa  Fixed BrsHwEnableInterruptAtPowerOn() ->
                                BrsHwConfigureInterruptsAtPowerOn() is now always called
  03.00.05  2016-07-01  vismin  Changed Assembler instruction MOV to MOVS for IAR Compiler
  03.00.06  2016-08-01  visbwa  Changed default of BRS_VECTOR_TABLE_SECTION to proper _vector_table_core,
                                added default BRS_VECTOR_TABLE_SECTION for VTOR within BrsHwVectorTableMovement()
  03.00.07  2016-10-18  visjhr  Added VTOR for CSRS3703
  03.00.08  2016-10-07  vismaa  Added support for S32K142, S32K146, S32K148
  03.00.09  2017-03-16  visbwa  Removed S32Kx sections from BrsHwVectorTableMovement(), always has ROM for VecTable
  03.00.10  2017-03-17  visbwa  Removed '_' from vector_table_core at BRS_VECTOR_TABLE_SECTION define
  03.01.00  2017-04-12  vissey  Adapted code structure to actual Brs_Template 2.01.00
            2017-05-30  visbwa  Review
  03.02.00  2017-06-14  vissey  Added support for ARM Compiler 6 (uses GNU Syntax for Assembler) threw BRS_COMP_ARM6,
                                changed BRS_COMP_ARM to BRS_COMP_ARM5
            2017-07-20  visbwa  Review, enhanced support for OsGen7
  03.02.01  2017-09-13  visivg  Added BRSHW_CORTEXM_PLATFORM_SPECIFIC_NVIC_INIT support within
                                BrsHwEnableInterruptAtPowerOn(), fixed _vector_table_core for TI compiler,
                                fixed configuration of NVIC_ISER0 according to vector_table_core[]
  03.02.02  2017-09-25  visivg  Fixed usage of BRS_VECTOR_TABLE_SECTION within BrsHwVectorTableMovement()
  03.02.03  2017-09-26  visbwa  Fixed interrupt restoring within BrsHwEnableInterruptAtPowerOn()
  03.02.04  2017-10-26  visbwa  Added support for Cortex-M4F (Cortex-M4 with FPU)
  03.02.05  2018-01-03  visbwa  Added support for ArmGeneric (Derivative=GENERIC),
                                review according to Brs_Template 2.02.00
  03.03.00  2018-02-13  visbwa  Introduced BrsHwEnableNVICInterrupt() and BrsHwDisableNVICInterrupt(), fixed default
                                interrupt enabling within BrsHwEnableInterruptAtPowerOn() (peripheral exceptions only),
                                rework of NVIC resiters definition (+ moved to ARMBrsHw.h),
                                removed include of ARMBrsHw.h (already done within BrsHw.h, caused typedef issues)
  03.03.01  2018-06-12  vismaa  Added support for Cortex-M0PLUS
  03.04.00  2018-08-06  vismaa  Added FBL support, renamed core exception table array
  03.05.00  2018-08-20  visbwa  Removed support for Keil compiler (use Arm5 instead!)
  03.05.01  2018-08-20  vishci  Removed implementation of S32V234
  03.05.02  2018-10-09  visbwa  BrsHwDisableInterruptAtPowerOn() modified (without masking out all exceptions and
                                interrupts via PRIMASK / FAULTMASK) (mandatory for OsGen7!)
  03.05.03  2018-10-19  visbwa  Fixed encapsulation and IAR implementation of interrupt disable mechanism
**********************************************************************************************************************/

/**********************************************************************************************************************
*  EXAMPLE CODE ONLY
*  -------------------------------------------------------------------------------------------------------------------
*  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
*  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
*  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
*  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
*  according to the state of the art before their use.
*********************************************************************************************************************/

#if defined (BRS_CPU_CORE_CORTEX_M0) || defined (BRS_CPU_CORE_CORTEX_M0PLUS) || defined (BRS_CPU_CORE_CORTEX_M3) || \
    defined (BRS_CPU_CORE_CORTEX_M4) || defined (BRS_CPU_CORE_CORTEX_M4F)    || defined (BRS_CPU_CORE_CORTEX_M7)

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
/*
 * Description: The BrsHw header provides all the necessary interfaces to
 *              the microcontroller hardware features like ports, timers, LEDs, ...
 */
#include "BrsHw.h"


/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if (ARMBRSHW_CORTEXM_VERSION != 0x0305u)
  #error "Header and source file are inconsistent!"
#endif
#if (ARMBRSHW_CORTEXM_BUGFIX_VERSION != 0x03u)
  #error "Different versions of bugfix in Header and Source used!"
#endif

/**********************************************************************************************************************
  CONFIGURATION CHECK
**********************************************************************************************************************/
#if defined (BRS_COMP_GHS) 

#else
  #error "Unknown compiler specified!"
#endif

#if defined (BRS_VECTOR_TABLE_LOCATION_RAM)   || \
    defined (BRS_VECTOR_TABLE_LOCATION_FLASH)
#else
  #error "Unknown location for VectorTable specified. Please correct the setting of VECTOR_TABLE_LOCATION within Makefile.config!"
#endif

#if defined (BRS_PROGRAM_CODE_LOCATION_RAM)   || \
    defined (BRS_PROGRAM_CODE_LOCATION_FLASH)
#else
  #error "Unknown location for ProgramCode specified. Please correct the setting of PROGRAM_CODE_LOCATION within Makefile.config!"
#endif

#if defined (BRS_CPU_CORE_CORTEX_M0) || defined (BRS_CPU_CORE_CORTEX_M0PLUS)|| defined (BRS_CPU_CORE_CORTEX_M3) || \
    defined (BRS_CPU_CORE_CORTEX_M4) || defined (BRS_CPU_CORE_CORTEX_M4F)   || defined (BRS_CPU_CORE_CORTEX_M7)
#else
  #error "Unknown ARM Core specified. Please correct the setting of CPU_CORE within Makefile.Platform.config!"
#endif

/**********************************************************************************************************************
  DEFINITION + MACROS
**********************************************************************************************************************/

  #define BRSHWNOP10() __asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");__asm("NOP");

/**********************************************************************************************************************
  GLOBAL VARIABLES
**********************************************************************************************************************/

#if !defined (BRS_OS_USECASE_OSGEN7)
# if defined (BRS_VECTOR_TABLE_LOCATION_RAM)
  /* set up the section name of the intvect table of your OS here */
  /* for SingleCore OS, this could be: intvect_table              */
  /* for MultiCore OS, this could be: intvect_table_c0            */
  /* Dont forget the external define of this variable,            */
  /*  some lines below (for ARM5 compiler)                        */
  #error Please define os vector table location below! E. g.: osArmExcVecTab from \GenData\intvect.c */
  #define BRS_VECTOR_TABLE_SECTION osArmExcVecTab
# endif /*BRS_VECTOR_TABLE_LOCATION_RAM*/
#endif /*!BRS_OS_USECASE_OSGEN7*/

/**********************************************************************************************************************
  GLOBAL CONST VARIABLES
**********************************************************************************************************************/
#if !defined (BRS_OS_USECASE_OSGEN7)
extern const uint32 BRS_VECTOR_TABLE_SECTION; /* linker symbol of the vector table */
#endif

/**********************************************************************************************************************
  LOCAL VARIABLES AND LOCAL HW REGISTERS
**********************************************************************************************************************/
/*
 * Description: This counter is used to count the number of nested calls to
 *              disable and restore the state of the global INT enable bit.
 *              Please note: This variable is used only in this file.
 * Values     : 0 if no BrsHwDisableInterrupt is called and INT is allowed by the
 *              BRS. Value > 0 if INT is locked by the BRS interrupt control API.
 */
static uint8 bBrsHwIntDiCounter;

/* Needed for BASEPRI analyzation within BrsHwDisableInterruptAtPowerOn() */
uint8 brsDisIntPrioTmp;
uint8 brsDisIntITmp;

/**********************************************************************************************************************
  CONTROLLER CONFIGURATION REGISTERS
**********************************************************************************************************************/
/* lowest 4 bit -> INTLINESNUM -> No. of last implemented NVIC_IPR-Register (4 int prios / 32bit-Register) */
#define BRSHW_MCORE_NVIC_ICTR BRSHW_IOS(uint32, (0xE000E004UL))
#define BRSHW_MCORE_NVIC_IPR(X) BRSHW_IOS(uint8, (0xE000E400UL+(X)))


/* Vector Table Offset Register */
#define VTOR         BRSHW_IOS(uint32, (0xE000ED08UL))

/**********************************************************************************************************************
  LOCAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL CONST VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  PROTOTYPES OF LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  FUNCTION DEFINITIONS
**********************************************************************************************************************/
#if defined (BRS_OS_USECASE_OS)
#endif /*BRS_OS_USECASE_OS*/

/* BrsHwTimeBaseInitPowerOn() and BrsHwTimeBaseInterrupt() removed by Organi, because of ALM attributes of project */

#if defined (BRS_VECTOR_TABLE_LOCATION_RAM)
# if !defined (BRS_DERIVATIVE_IMX6X) && !defined (BRS_DERIVATIVE_GENERIC)
void BrsHwVectorTableMovement(void)
{
/**************************************************/
/**               Cortex-M-Series                **/
/** Note: VTOR neednt be supported by every MCU **/
/**************************************************/
  /* Configure the location of the InterruptVectorTable */
  /* -> VTOR has to point to the reset value of main stack pointer (first word of exception table) */
  /* Possible values for already evaluated platforms:   */
  /*   Sta1095 (Cortex_M3): VTOR =  0x10000000          */
  /*   Vybrid (Cortex_M4) : VTOR =  0x3F040000          */
# if defined (BRS_CPU_CORE_CORTEX_M0) || defined (BRS_CPU_CORE_CORTEX_M0PLUS)
#  if defined (BRS_DERIVATIVE_STM32F04x)
  /* Derivative has no vector table relocation support */
  /* -> mapped to RAM via linker cmd file, mapped to start adr 0x0 via .OPTIONBYTES in ARMStartup.c */
#  else /*BRS_DERIVATIVE_STM32F04x*/
  #error "Specify the address for BrsHwVectorTableMovement here manually" */
  VTOR &= ~0xFFFFFF00;      /* TBLOFF [31:7] - low bits are always zero */
  VTOR  =  0x________;  /* try BRS_VECTOR_TABLE_SECTION or fill in full new address */
#  endif /*BRS_DERIVATIVE_STM32F04x*/
# elif defined (BRS_CPU_CORE_CORTEX_M3) || defined (BRS_CPU_CORE_CORTEX_M4) || defined (BRS_CPU_CORE_CORTEX_M4F) || defined (BRS_CPU_CORE_CORTEX_M7)
#   if defined (BRS_DERIVATIVE_ATSAMV71Q21) || defined (BRS_DERIVATIVE_ATSAMV70Q20)
   VTOR  =  0x00000000;      /* starts always on pointer read from 0x00000004... */
#   elif defined (BRS_DERIVATIVE_CSRS3703)
   /* @@@visjhr VTOR  =  0x17E00000; */     /* RAM start address -> M3 core SPRAM start */
   VTOR  =  0x00000000;      /* RAM start address -> DRAM start */
#   elif defined (BRS_DERIVATIVE_STM32L4x6)
   VTOR &= ~0xFFFFFF00;      /* TBLOFF [31:7] - low bits are always zero */
#    if defined (BRS_VECTOR_TABLE_LOCATION_RAM)
    #error "For booting from SRAM1 the User Option Byte nBOOT1 has to be set to 0!" */
    VTOR  =  0x20000000;      /* Write address of the vector table to VTOR -> start of SRAM1 */
#    else /*BRS_VECTOR_TABLE_LOCATION_FLASH*/
    VTOR  =  0x08000000;      /* Write address of the vector table to VTOR -> start of Main Flash */
#    endif /*BRS_VECTOR_TABLE_LOCATION_RAM*/

#   else
    /* Try BRS_VECTOR_TABLE_SECTION first and use manual setup if this does not work. */
    VTOR = (uint32) &BRS_VECTOR_TABLE_SECTION; /* Write address of the vector table to VTOR */
    /*VTOR &= ~0xFFFFFF00;*/  /* TBLOFF [31:7] - low bits are always zero */
    /*VTOR  =  0x________;*/  /* Write address of the vector table to VTOR */
#   endif /*BRS_DERIVATIVE_ATSAMV71Q21 || BRS_DERIVATIVE_ATSAMV70Q20*/
# endif /*BRS_CPU_CORE_CORTEX_Mx*/
}
# endif /*!BRS_DERIVATIVE_IMX6X&&!BRS_DERIVATIVE_GENERIC*/
#endif /*BRS_VECTOR_TABLE_LOCATION_RAM*/

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
void BrsHwDisableInterruptAtPowerOn(void)
{
  uint8 brsIdx;

  bBrsHwIntDiCounter = 0;

  brsDisIntITmp = 0; /* prevent compiler warning */

  /* get pointer to brsDisIntITmp */
  __as1(LDR  R4, =brsDisIntITmp)
  /* analyze amount of supported bits in priority registers and BASEPRI
   * (BASEPRI bits not supported are "Read All Zero, Ignore Writes") */
   /* BASEPRI = 255 */
  __as1(MOV  R2, #255)
  __as1(MSR  basepri, R2)
  /* brsDisIntITmp = BASEPRI */
  __as1(MRS  R2, basepri)
  __as1(STR  R2, [R4])

  brsDisIntPrioTmp = 0xFF;
  for (brsIdx = 0; brsIdx < 8; brsIdx++)
  {
    if ((((uint32)((uint32)1UL << brsIdx)) & brsDisIntITmp) != 0)
    {
      brsDisIntPrioTmp = (boolean)(((uint32)((uint32)1UL << brsIdx)) & 0xFF);
      break;
    }
  }
  if (brsDisIntPrioTmp == 0xFF)
  {
    /* BASEPRI not writable! */
    while (1);
  }

  /* get pointer to brsDisIntPrioTmp */
  __as1(LDR  R4, =brsDisIntPrioTmp)
  __as1(LDR  R2, [R4])
  /* BASEPRI = brsDisIntPrioTmp */
  __as1(MSR  basepri, R2)

  /* evaluate amount of available NVIC_IPR regs within this Cortex-M* core */
  brsDisIntITmp = ((BRSHW_MCORE_NVIC_ICTR & 0x0000000F)+1) << 5;

  /* set all interrupt priorities to BASEPRI priority -> disable all interrupts
   * (if an interrupts shall be enabled -> set its NVIC_IPR reg to 0) */
  for (brsIdx = 0; brsIdx < brsDisIntITmp; brsIdx++)
  {
    BRSHW_MCORE_NVIC_IPR(brsIdx) = brsDisIntPrioTmp;
  }

}


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
void BrsHwEnableInterruptAtPowerOn(void)
{
# if !defined (BRSHW_CORTEXM_PLATFORM_SPECIFIC_NVIC_INIT)
  #error "The following sequence is enabling all peripheral interrupts. If this causes problems, try to only enable the interrupts, used by your actual controller and your actual configuration" */
#  if defined (BRS_CPU_CORE_CORTEX_M0) || defined (BRS_CPU_CORE_CORTEX_M0PLUS)
  NVIC_ISER_ADDR(0) = 0xFFFFFFFF;  /* Cortex-M0 only supports 32 Peripheral-Interrupts */
#  elif defined (BRS_CPU_CORE_CORTEX_M3) || defined (BRS_CPU_CORE_CORTEX_M4) || defined (BRS_CPU_CORE_CORTEX_M4F) || defined (BRS_CPU_CORE_CORTEX_M7)
  NVIC_ISER_ADDR(0) = 0xFFFFFFFF;  /* Enable 1st 32 interrupts */
  NVIC_ISER_ADDR(1) = 0xFFFFFFFF;  /* Enable 2nd 32 interrupts */
  NVIC_ISER_ADDR(2) = 0xFFFFFFFF;  /* Enable 3rd 32 interrupts */
  NVIC_ISER_ADDR(3) = 0xFFFFFFFF;  /* Enable 4th 32 interrupts */
  NVIC_ISER_ADDR(4) = 0xFFFFFFFF;  /* Enable 5th 32 interrupts */
  NVIC_ISER_ADDR(5) = 0xFFFFFFFF;  /* Enable 6th 32 interrupts */
  NVIC_ISER_ADDR(6) = 0xFFFFFFFF;  /* Enable 7th 32 interrupts */
  NVIC_ISER_ADDR(7) = 0xFFFFFFFF;  /* Enable 8th 32 interrupts */
#  endif /*BRS_CPU_CORE_CORTEX_X*/
# endif /*!BRSHW_CORTEXM_PLATFORM_SPECIFIC_NVIC_INIT*/

  /* Call platform specific interrupt enabling function in here */
  BrsHwConfigureInterruptsAtPowerOn();



#if defined (BRS_COMP_GHS) 
# if defined (BRS_CPU_CORE_CORTEX_M0) || defined (BRS_CPU_CORE_CORTEX_M0PLUS)
    /* Global enable IRQs */
    __asm("MOVS R0, #0      ");
    __asm("MSR primask,   R0");
# endif
# if defined (BRS_CPU_CORE_CORTEX_M3) || defined (BRS_CPU_CORE_CORTEX_M4) || defined (BRS_CPU_CORE_CORTEX_M4F) || defined (BRS_CPU_CORE_CORTEX_M7)
    /* Global enable IRQs */
    __asm("MOV R0, #0       ");
    __asm("MSR primask,   R0");
    __asm("MSR faultmask, R0");
# endif
#endif /*BRS_COMP_GHS||BRS_COMP_IAR||BRS_COMP_GNU||BRS_COMP_ARM6*/
}
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
void BrsHwDisableInterrupt(void)
{
  /* No check for "overrun" of nested INT lock counter is performed, due to more
  *  than 255 nested calls to BrsHwDisableInterrupt are very unlikely. */
  if (bBrsHwIntDiCounter == 0)
  {


#if defined (BRS_COMP_GHS) 
# if defined (BRS_CPU_CORE_CORTEX_M0) || defined (BRS_CPU_CORE_CORTEX_M0PLUS)
    /* Global disable IRQs, EXCEPT HardFault and NMI! */
    __asm("MOVS R0, #1      ");
    __asm("MSR primask,   R0");
# endif
# if defined (BRS_CPU_CORE_CORTEX_M3) || defined (BRS_CPU_CORE_CORTEX_M4) || defined (BRS_CPU_CORE_CORTEX_M4F) || defined (BRS_CPU_CORE_CORTEX_M7)
    /* Global disable IRQs, EXCEPT HardFault and NMI! */
    __asm("MOV R0, #1       ");
    __asm("MSR primask,   R0");
    __asm("MSR faultmask, R0");
# endif
#endif /*BRS_COMP_GHS||BRS_COMP_IAR||BRS_COMP_GNU||BRS_COMP_ARM6*/
  }

  bBrsHwIntDiCounter++;
}

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
void BrsHwRestoreInterrupt(void)
{
  /* Check for illegal call of BrsHwRestoreInterrupt. If this function is called
   *  too often, the INT lock works incorrect. */
  if (bBrsHwIntDiCounter == 0)
  {
    /* Check is only performed, if no OS and no FBL are used */
  }

  bBrsHwIntDiCounter--;
  if (bBrsHwIntDiCounter == 0)
  {


#if defined (BRS_COMP_GHS) 
# if defined (BRS_CPU_CORE_CORTEX_M0) || defined (BRS_CPU_CORE_CORTEX_M0PLUS)
    /* Global enable IRQs */
    __asm("MOVS R0, #0      ");
    __asm("MSR primask,   R0");
# endif
# if defined (BRS_CPU_CORE_CORTEX_M3) || defined (BRS_CPU_CORE_CORTEX_M4) || defined (BRS_CPU_CORE_CORTEX_M4F) || defined (BRS_CPU_CORE_CORTEX_M7)
    /* Global enable IRQs */
    __asm("MOV R0, #0       ");
    __asm("MSR primask,   R0");
    __asm("MSR faultmask, R0");
# endif
#endif /*BRS_COMP_GHS||BRS_COMP_IAR||BRS_COMP_GNU||BRS_COMP_ARM6*/
  }
}

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
void BrsHwTime100NOP(void)
{
  BrsHwDisableInterrupt();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();

  BrsHwRestoreInterrupt();
}

#endif /*BRS_CPU_CORE_CORTEX_Mx*/
