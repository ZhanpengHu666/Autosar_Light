
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
  \file  File:  ARMStartup_CortexM.c
      Project:  Vector Basic Runtime System
       Module:  BrsHw for all platforms with ARM core Cortex-M
     Template:  This file is reviewed according to zBrs_Template@root[2.02.00]

  \brief Description:  This is a global, hardware-independent file for the ARM-BRS.
                       It contains the general startup-code for ARM-Core based Systems.
                       All the (hardware depending) rest needs to be defined in BrsHw.c

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
  Sascha Mauser                 vismaa        Vector Informatik GmbH
  Sherif Elsabbahy              vissey        Vector Informatik GmbH
  Muhammad Suliman              vismun        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  03.00.00  2016-05-04  vismin  Initial version for Cortex M based on ARMStartup.c
            2016-05-31  visbwa  Review
  03.00.01  2016-06-01  visbwa  Fixed compiler encapsulation within Startup Handler
  03.00.02  2016-06-15  vismin  Fixed support for IAR
  03.00.03  2016-06-22  vismin  Adapted complete file header structure for zBrs_Template@root[2.00.01]
  03.00.04  2016-06-29  vismin  Changed Assembler instruction MOV & ADD to MOVS & ADDS for Keil Compiler
  03.00.05  2016-07-01  vismin  Changed Assembler instruction MOV, ADD & B.W to MOVS, ADDS & BL for GNU Compiler
  03.00.06  2016-08-01  visbwa  Renamed _vector_table into _vector_table_core for TI compiler (same as other compilers)
  03.00.07  2016-10-07  vismaa  Added support for S32K142, S32K146, S32K148
  03.00.08  2017-04-05  visbwa  Changed compiler-encapsulation of Startup Handler to allow folding
  03.01.00  2017-06-16  vissey  Added support for ARM Compiler 6 (uses GNU Syntax for Assembler) threw BRS_COMP_ARM6,
                                changed BRS_COMP_ARM to BRS_COMP_ARM5
  03.02.00  2017-07-20  visbwa  Review, harmonized version with Cortex-M part,
                                added start symbol _start for better OsGen7 support
  03.02.01  2017-07-27  vissey  Finalized ARM6 support
  03.02.02  2017-10-17  visbwa  Encapsulated exception table within TI compiler (not used together with OS)
  03.02.03  2017-10-20  visbwa  Added IAR entry symbol _start for UseCase OsGen7
  03.02.04  2017-10-26  visbwa  Added support for Cortex-M4F (Cortex-M4 with FPU)
  03.02.05  2017-10-26  vismun  Fixed ARM5/KEIL compiler warnings, added ((unused)) for GNU within HardFault_Handler()
  03.02.06  2017-12-06  vismun  Compacted Startup_Handler routine for IAR compiler by calling __iar_data_init3()
  03.02.07  2017-12-22  visbwa  Simplified CORE encapsulation within CoreExceptionTable
  03.02.08  2018-02-13  visbwa  Changed include of ARMBrsHw.h to BrsHw.h (caused typedef issues)
  03.02.09  2018-04-27  visjhr  Fixed option bytes for S32K*
  03.02.10  2018-06-12  vismaa  Added support for Cortex-M0PLUS
  03.03.00  2018-06-27  vismaa  Changed naming COREINTERRUPTS to intvect_CoreExceptions for FBL support
  03.03.01  2018-07-05  visbwa  Fixed section name of CoreExceptions for TI compiler
  03.03.02  2018-07-05  visbwa  Fixed core encapsulation within TI compiler to solve compiler warning
  03.03.03  2018-08-06  vismaa  Finalized FBL support, renamed core exception table array, changed Startup_Handler
                                for ARM5 compiler (for correct entrypoint setting), ARM needs capital letters for
                                memory area .INTVECT_COREEXCEPTIONS
  03.04.00  2018-08-20  visbwa  Removed support for Keil compiler (use Arm5 instead!)
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

/*
 * Description: BrsTypes header is the abstraction for MSR/CBD to get access to types definitions
 */
#include "BrsTypes.h"


# if defined(BRS_COMP_GHS)  
/**********************************************************************************************************************
  Compiler abstraction
**********************************************************************************************************************/
#  if defined (BRS_COMP_GHS)
  #define Section_3(a,b,c)        .section a
  #define Section_4(a,b,c,d)      .section a
  #define Label(a)                a:
  #define EndlessLoopHandler(a)   a: B a

#  else
  #error "Compiler abstraction not defined for this compiler! "
#  endif /*BRS_COMP_x*/

/******************************************************************************
*              Stack & Heap Definitions                                       *
******************************************************************************/
/* Stack and Heap are defined in the linker script! */
#  if defined (BRS_COMP_GHS) 
  extern void __stack_top(void);
#  endif /*BRS_COMP_x*/

/******************************************************************************
*            Prototypes                                                       *
******************************************************************************/

/* CORE interrupts are only defined, if no OS is used. OS will handle them itself. */

/******************************************************************************
*                              Option Bytes                                   *
******************************************************************************/
#  if defined (BRS_OPTIONBYTES_ADR)
#   if defined (BRS_COMP_GHS) 
 __attribute__ ((section(".OPTIONBYTES")))
#   endif
    const unsigned long int option_bytes[] = {
#   if defined (BRS_DERIVATIVE_ATSAMV71Q21) || defined (BRS_DERIVATIVE_ATSAMV70Q20)
#    if (defined (BRS_VECTOR_TABLE_LOCATION_RAM) && defined (BRS_PROGRAM_CODE_LOCATION_FLASH)) || \
       (defined (BRS_VECTOR_TABLE_LOCATION_FLASH) && defined (BRS_PROGRAM_CODE_LOCATION_RAM))
     #error "VECTOR_TABLE_LOCATION and PROGRAM_CODE_LOCATION has to be identical!"
#    else
      /* [0]: User and read protection option bytes, Flash memory address: 0x1FFF F800 */
#     if defined (BRS_VECTOR_TABLE_LOCATION_RAM) && defined (BRS_PROGRAM_CODE_LOCATION_RAM)
      0x986755AA, /* BOOT_SEL=0, nBOOT0=0, nBOOT1=0 -> Embedded SRAM */
#     endif /* defined (BRS_VECTOR_TABLE_LOCATION_RAM) && defined (BRS_PROGRAM_CODE_LOCATION_RAM) */
#     if defined (BRS_VECTOR_TABLE_LOCATION_FLASH) && defined (BRS_PROGRAM_CODE_LOCATION_FLASH)
      0x807F55AA, /* BOOT_SEL=0, nBOOT0=1 -> Main Flash */
#     endif /* defined (BRS_VECTOR_TABLE_LOCATION_FLASH) && defined (BRS_PROGRAM_CODE_LOCATION_FLASH) */
#    endif /* if (defined (..._RAM) && defined (,,,_FLASH)) || (defined (..._FLASH) && defined (,,,_RAM)) */
      /* [1]: User data option bytes, Flash memory address: 0x1FFF F804 */
      0x00FF00FF,
      /* [2]: Write protection option bytes (WRP1)/WRP0, Flash memory address: 0x1FFF F808 */
      0x00FF00FF,

#   elif defined (BRS_DERIVATIVE_S32K116) || defined (BRS_DERIVATIVE_S32K118) || defined (BRS_DERIVATIVE_S32K142) || defined (BRS_DERIVATIVE_S32K144) || defined (BRS_DERIVATIVE_S32K146) || defined (BRS_DERIVATIVE_S32K148)
      /* 0x40F: FDPROT, 0x40E: FEPROT, 0x40D: FOPT, 0x40C: FSEC */
      0xFFFFFFFE,

#   else
  #error "Optionbyte settings missing for your derivative!"
#   endif /*BRS_DERIVATIVE_S32K144*/
};
#  endif /*BRS_OPTIONBYTES_ADR*/

/******************************************************************************
*            Startup Handler (Reset Handler)                                  *
******************************************************************************/
#  if defined (BRS_COMP_GHS) 

#   if defined (BRS_COMP_GHS)
  #pragma asm
#   endif

  Section_3(.STARTUP,CODE,READONLY)
  EXPORT Startup_Handler
  EXPORT _start

Label(Startup_Handler)
Label(_start)

#   if defined(BRS_VECTOR_TABLE_LOCATION_RAM)
  ;/*----- SP initialization -----------------------------------------------------*/
  LDR  R0, =__stack_top
  MOV  SP, R0
#   endif /*BRS_VECTOR_TABLE_LOCATION_RAM*/

  ;/*----- Stack initialization ---------------------------------------------------*/
  ;/* Stack initialization has to be done in assembler instead by a for() loop,    */
  ;/* because otherwise the loop counter variable will be overwritten in the loop! */
  ;/*------------------------------------------------------------------------------*/
  LDR  R0, =__stack_start
  LDR  R1, =__stack_top
  MOVS R2, #0xFF

Label(stack_init_loop)

  CMP  R1, R0
  BLS  stack_init_loop_end
  STRB R2, [R0]
  ADDS R0, R0, #1
  B    stack_init_loop

Label(stack_init_loop_end)

  ;/*----- .bss initialization ---------------------------------------------------*/
  LDR  R0,=__bss_start
  LDR  R1,=__bss_end
  MOVS R2,#0

Label(bss_loop)

  CMP  R1, R0
  BLS  bss_loop_end
  STRB R2, [R0]
  ADDS R0, R0, #1
  B    bss_loop

Label(bss_loop_end)

#   if defined(BRS_COMP_GHS)
  ;/*----- .data initialization --------------------------------------------------*/
  LDR  R0,=RC_SDATA_SRC
  LDR  R1,=RC_SDATA_DEST
  LDR  R2,=RC_SDATA_SIZE

Label(datainit_loop)

  TST  R2, R2
  BEQ  datainit_loop_end
  LDRB R3, [R0]
  STRB R3, [R1]
  ADD  R0, R0, #1
  ADD  R1, R1, #1
  SUB  R2, R2, #1
  BNE  datainit_loop

Label(datainit_loop_end)
#   endif /*BRS_COMP_GHS*/

  ;/*----- Branch to main() -----------------------------------------------------*/
  IMPORT  main
  BL      main          ;/* Branch to main() */

  ;/*----- Capture the case of an unexpected return from main()! ----------------*/
EndlessLoopHandler(Loop)

#   if defined (BRS_COMP_GHS)
  #pragma endasm
#   endif
#  endif /*BRS_COMP_GHS||BRS_COMP_ARM5*/



/*******************************************************
*               Compiler specific things               *
*******************************************************/
# endif /*BRS_COMP_GNU||BRS_COMP_GHS||BRS_COMP_ARM5||BRS_COMP_ARM6||BRS_COMP_IAR*/

#endif /*BRS_CPU_CORE_CORTEX_Mx*/
