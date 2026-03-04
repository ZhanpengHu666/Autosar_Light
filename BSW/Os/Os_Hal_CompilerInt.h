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
 *  \ingroup    Os_Hal
 *  \addtogroup Os_Hal_Compiler  HAL Compiler
 *  \brief      Abstraction of compiler specific keywords to allow the compiler to generate more efficient code.
 *  \details
 *  The kernel should be able to give the compiler meta information to generate more efficient code.
 *  It also needs to tell the linker where to put data and code to implement Memory Protection.
 *  In multi core systems there may be the need for data/code duplication.
 *  The keywords to provide this information are not part of ANSI-C and are highly compiler dependent.
 *
 *  AUTOSAR already defines concepts to abstract compiler specifics:
 *  - [AUTOSAR Compiler Abstraction](http://www.autosar.org/fileadmin/files/releases/4-2/software-architecture/implementation-integration/standard/AUTOSAR_SWS_CompilerAbstraction.pdf)
 *  - [AUTOSAR Memory Mapping](http://www.autosar.org/fileadmin/files/releases/3-2/software-architecture/implementation-integration/standard/AUTOSAR_SWS_MemoryMapping.pdf)
 *
 *  They are used in MICROSAR OS. This module defines additional compiler abstraction keywords for MICROSAR OS.
 *  They are relevant to provide OS functionality or improve efficiency.
 *
 *  \{
 *
 *  \file
 *  \brief      Additional services defined here are available to the user.
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined (OS_HAL_COMPILERINT_H)                                                                                     /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_COMPILERINT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* Os kernel module dependencies */
# include "Os_Cfg.h"
# include "Os_CommonInt.h"

# include "Os_Hal_Derivative.h"

# if defined(OS_STATIC_CODE_ANALYSIS)                                                                                   /* COV_OS_STATICCODEANALYSIS */
#  include "Os_Hal_StaticCodeAnalysis.h"
# else
#  if defined (OS_CFG_COMPILER_GREENHILLS)
#   include "Os_Hal_Compiler_GreenhillsInt.h"
#  elif defined (OS_CFG_COMPILER_IAR)
#   include "Os_Hal_Compiler_IarInt.h"
#  elif defined (OS_CFG_COMPILER_TEXASINSTRUMENTS)
#   include "Os_Hal_Compiler_TiInt.h"
#  elif defined (OS_CFG_COMPILER_ARM)
#   include "Os_Hal_Compiler_ArmInt.h"
#  elif defined (OS_CFG_COMPILER_LINARO)
#   include "Os_Hal_Compiler_GccInt.h"
# else
#   error "Undefined or unsupported compiler"
#  endif
# endif


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/*! \brief      Tells the compiler that the conditional statement is likely to be true.
 *  \details    The compiler, in turn, can then perform block reordering, and other optimization to
 *              improve the performance of conditional branches.
 *  \param[in]  CONDITION   The condition which is likely to be true
 */
# define OS_LIKELY(CONDITION)       (CONDITION)                                                                         /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! \brief      Tells the compiler that the conditional statement is likely to be false.
 *  \details    The compiler, in turn, can then perform block reordering, and other optimization to
 *              improve the performance of conditional branches.
 *  \param[in]  CONDITION   The condition which is likely to be false
 */
# define OS_UNLIKELY(CONDITION)     (CONDITION)                                                                         /* PRQA S 3453 */ /* MD_MSR_19.7 */


# if !defined (OS_ALWAYS_INLINE)
#  error "OS_ALWAYS_INLINE is undefined!"
# endif


# if !defined (OS_NORETURN)
#  error "OS_NORETURN is undefined!"
# endif


# if !defined (OS_FLATTEN)
#  error "OS_FLATTEN undefined"
# endif


# if !defined (OS_NOSIDEEFFECTS)
#  error "OS_NOSIDEEFFECTS undefined"
# endif


# if !defined (OS_PURE)
#  error "OS_PURE undefined"
# endif


# if !defined (OS_NAKED)
#  error "OS_NAKED undefined"
# endif


# if !defined (OS_LIKELY)
#  error "OS_LIKELY(Condition) undefined"
# endif


# if !defined (OS_UNLIKELY)
#  error "OS_UNLIKELY(Condition) undefined"
# endif


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#endif /* OS_HAL_COMPILERINT_H */

/* module specific MISRA deviations:
 MD_Os_Hal_0303:
      Reason:     This statement converts an integral address to a pointer or vice versa. This is unavoidable for
                  memory access of that address or put a pointer to a core register.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0305:
      Reason:     This statement converts a function pointer to an integral address or vice versa. This is unavoidable to
                  use the function pointer address.
      Risk:       The risk for incompatibility is low here as the code is used on a specific hardware platform only with
                  known sizes of pointer types and integral types.
      Prevention: The code is tested with all compilers it shall be compiled with.
 MD_Os_Hal_0306:
      Reason:     This statement converts an integral address to a pointer or vice versa. This is unavoidable for
                  memory access of that address or put a pointer to a core register.
      Risk:       The risk for incompatibility is low here as the code is used on a specific hardware platform only with
                  known sizes of pointer types and integral types.
      Prevention: The code is tested with all compilers it shall be compiled with.
 MD_Os_Hal_0489_StackPointer:
      Reason:     The increment or decrement operation on pointer is explicitly required here.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0489_GenData:
      Reason:     The increment or decrement operation on pointer is not avoidable due to the usage of macro defined
                  in core code: "OS_STACK_GETHIGHADDRESS".
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0685:
      Reason:     This is a constant expression. The MISRA tool seems to be unable to detect this. However, the compiler
                  produces correct code and we test with all compilers which shall be supported.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0883:
      Reason:     The protection against repeated inclusion is complete and correct. The MISRA tool is unable to
                  detect this.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_3112:
      Reason:     This statement is used to avoid warnings caused by unused parameters. Parameters are defined by
                  standardized API requirements, and not needed in case a feature is disabled by configuration.
                  It is either impossible due to API standardization or necessary code duplication (severe maintenance
                  increase) to provide feature dependent APIs with different signatures.
      Risk:       Unavoidable compiler warning or error because of either unused statements or unused parameter.
      Prevention: None.
 MD_Os_Hal_3410_Decl:
      Reason:     Macro is used for declaration, which does not allow enclosing parameters in brackets.
      Risk:       None, type errors will be detected by the compiler.
      Prevention: None.
 MD_Os_Hal_3219:
      Reason:     This function is inlined and therefore it has to be implemented here. The function is not used
                  by all implementation files which include this header file.
      Risk:       This function may not be used by any implementation file.
      Prevention: The reviewer has to ensure the each static inline function is used at leased once.
 MD_Os_Hal_3450_Gen:
      Reason:     Function prototype is ommitted to avoid code overhead in generated files.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_3447_Loc:
      Reason:     This function should be visible in general but within this file.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_3453_Decl:
      Reason:     Macro is used for declaration, which is not possible within a function.
      Risk:       None, type errors will be detected by the compiler.
      Prevention: None.
 MD_Os_Hal_3673:
      Reason:     The parameter may be modified in other HAL implementations, thus it is necessary to keep it
                  as "pointer to non-const".
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_3673_NotUsed:
      Reason:     This input parameter is not used in this HAL implementation, thus it is not modified. However, since
                  it may be used or modified in other platforms, it is unavoidable to keep it as "pointer to non-const".
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_3203:
      Reason:     The variable is prepared for use in assembler, can't be seen by MISRA.
      Risk:       None.
      Prevention: None.
 */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_CompilerInt.h
 **********************************************************************************************************************/

