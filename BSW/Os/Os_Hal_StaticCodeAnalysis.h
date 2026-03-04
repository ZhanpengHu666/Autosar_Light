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
 * \ingroup    Os_Hal
 * \addtogroup Os_Hal_Compiler
 * \{
 *
 * \file    Os_Hal_StaticCodeAnalysis.h
 * \brief   Compiler abstraction of the ANSI C compiler used for MISRA and ReviewHelper
 *
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined(OS_HAL_STATICCODEANALYSIS_H)
# define OS_HAL_STATICCODEANALYSIS_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/*! \brief      Declares a function with a compiler specific attribute.
 *  \details    The implementations prototype has to be created with OS_FUNC_ATTRIBUTE_DEFINITION.
 *  \param[in]  rettype       The return type of the function.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {OS_ALWAYS_INLINE; OS_PURE, ...}.
 *  \param[in]  functionName  The function name.
 *  \param[in]  arguments     The function arguments in brackets. E.g. (uint8 a, uint16 b) or (void).
 */
#define OS_FUNC_ATTRIBUTE_DECLARATION(rettype, memclass, attribute, functionName, arguments) \
  FUNC(rettype, memclass) functionName arguments                                                                        /* PRQA S 3410, 3453 */ /* MD_Os_Hal_3410_Decl, MD_Os_Hal_3453_Decl */


/*! \brief      Provides a function prototype for function definitions with a compiler specific attribute.
 *  \details    The declaration has to be created with OS_FUNC_ATTRIBUTE_DECLARE.
 *  \param[in]  rettype       The return type of the function.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {OS_ALWAYS_INLINE; OS_PURE, ...}.
 *  \param[in]  functionName  The function name.
 *  \param[in]  arguments     The function arguments in brackets. E.g. (uint8 a, uint16 b) or (void).
 */
#define OS_FUNC_ATTRIBUTE_DEFINITION(rettype, memclass, attribute, functionName, arguments) \
  FUNC(rettype, memclass) functionName arguments                                                                        /* PRQA S 3410, 3453 */ /* MD_Os_Hal_3410_Decl, MD_Os_Hal_3453_Decl */


/*! \brief      Provides a constant definition with a compiler specific attribute.
 *  \details    The attribute is only used for compiler without support of defining sections using pragma.
 *  \param[in]  constType     The type of the constant.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {alignment, ...}.
 *  \param[in]  constName     The constant name.
 */
#define OS_HAL_CONST_ATTRIBUTE_DEFINITION(constType, memclass, attribute, constName) \
  CONST(constType, memclass) constName                                                                                  /* PRQA S 3410, 3453 */ /* MD_Os_Hal_3410_Decl, MD_Os_Hal_3453_Decl */


/*! \brief      Provides a constant declaration with a compiler specific attribute.
 *  \details    The attribute is only used for compiler without support of defining sections using pragma.
 *  \param[in]  constType     The type of the constant.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {alignment, ...}.
 *  \param[in]  constName     The constant name.
 */
#define OS_HAL_CONST_ATTRIBUTE_DECLARATION(constType, memclass, attribute, constName) \
  extern CONST(constType, memclass) constName                                                                           /* PRQA S 3410, 3453 */ /* MD_Os_Hal_3410_Decl, MD_Os_Hal_3453_Decl */


/*! \brief    Abstraction for HAL specific compiler attribute to prevent from inlining a function. */
# define OS_HAL_NOINLINE

/*! \brief    Force the compiler to inline a function.
 *  \details  This attribute forces the compiler to inline the specified function,
 *            regardless of the optimization strategy of the compiler itself.
 *            On some compilers you may be able to disable even this kind of inlining, using debugging options.
 */
# define OS_ALWAYS_INLINE


/*! \brief    This attribute tells the compiler that a function never returns.
 *  \details  It can then optimize without regard to what would happen if the function ever did return.
 *            This makes slightly better code. More importantly, it helps avoid spurious warnings of uninitialized
 *            variables.
 */
# define OS_NORETURN


/*! \brief    This attribute forces inlining of all function calls in a function, including nested function calls.
 * \details   Whether the function itself is considered for inlining depends on its size and the current inlining
 *            parameters.
 */
# define OS_FLATTEN


/*! \brief    This attribute tells that a function has no side effects and will not access global data.
 *  \details  This can help the compiler to optimize code. Such functions do not examine any values except their
 *            arguments, and have no effects except the return value. This is just slightly more strict class than
 *            the OS_PURE attribute, since function is not allowed to read global memory.
 */
# define OS_NOSIDEEFFECTS


/*! \brief    This attribute tells that a function has no side effects, although it may read global data.
 *  \details  Such pure functions can be subject to common subexpression elimination and loop optimization.
 */
# define OS_PURE


/*! \brief    The specified function will not have prologue/epilogue sequences generated by the compiler.
 *  Internal comment removed.
 *
 *
 */
# define OS_NAKED


/*! \note     The attribute to define sections.
 *            This is only required if the compiler does not support section definition using pragmas
 */
# define OS_HAL_SECTION_ATTRIBUTE(x)


/*! \brief        Returns the current SP register value.
 *  \details      -
 *  \return       SP register value.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static uint32 Os_Hal_ReadStackPointer(void);
static uint32 Os_Hal_ReadStackPointer(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  return 0;
}

/*! \brief        Executes data memory barrier instruction "dmb".
 *  \details      -
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static void Os_Hal_DataMemoryBarrier(void);
static void Os_Hal_DataMemoryBarrier(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
}

/*! \brief        Executes data sync barrier instruction "dsb".
 *  \details      -
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static void Os_Hal_DataSyncBarrier(void);
static void Os_Hal_DataSyncBarrier(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
}

/*! \brief        Executes instruction sync barrier instruction "isb".
 *  \details      -
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static void Os_Hal_InstructionSyncBarrier(void);
static void Os_Hal_InstructionSyncBarrier(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
}

/*! \brief        Returns the link register value.
 *  \details      -
 *  \return       Link register value.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static uint32 Os_Hal_ReadLinkRegister(void);
static uint32 Os_Hal_ReadLinkRegister(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  return 0;
}

/*! \brief        Bypass given pointer and execute SVC instruction.
 *  \details      -
 *  \param[in]    TrapPacket  Value which shall be passed in parameter register. Parameter must not be NULL.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static void Os_Hal_SysCall(uint32 TrapPacket);
static void Os_Hal_SysCall(uint32 TrapPacket)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  OS_IGNORE_UNREF_PARAM(TrapPacket);           /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}

/*! \brief        Executes "no operation" instruction.
 *  \details      -
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static void Os_Hal_Nop(void);
static void Os_Hal_Nop(void)                   /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
}


static void Os_Hal_WriteBasepri(uint32 NewBasepri);
static void Os_Hal_WriteBasepri(uint32 NewBasepri)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  OS_IGNORE_UNREF_PARAM(NewBasepri);                /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}

static uint32 Os_Hal_ReadBasepri(void);
static uint32 Os_Hal_ReadBasepri(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  return 0;
}

static void Os_Hal_WriteControl(uint32 NewControl);
static void Os_Hal_WriteControl(uint32 NewControl)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  OS_IGNORE_UNREF_PARAM(NewControl);                /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}

static uint32 Os_Hal_ReadControl(void);
static uint32 Os_Hal_ReadControl(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  return 0;
}

static uint32 Os_Hal_ReadPsr(void);
static uint32 Os_Hal_ReadPsr(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  return 0;
}


static void Os_Hal_Trigger_Context_SvCall(uint32 NewSp);
static void Os_Hal_Trigger_Context_SvCall(uint32 NewSp)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  OS_IGNORE_UNREF_PARAM(NewSp);                          /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}


static void Os_Hal_Disable(void);
static void Os_Hal_Disable(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
}


static void Os_Hal_Enable(void);
static void Os_Hal_Enable(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
}

static uint32 Os_Hal_DisableAndReturnPriorState(void);
static uint32 Os_Hal_DisableAndReturnPriorState(void)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  return 0;
}

static void Os_Hal_RestorePriorIntState(uint32 IntState);
static void Os_Hal_RestorePriorIntState(uint32 IntState)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  OS_IGNORE_UNREF_PARAM(IntState);                        /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}


/* General function / macros */

/*! \brief        Takes a 32-bit integer argument and returns the count of leading zeros, which is a number from 0 to
 *                32.
 *  \details      -
 *  \param[in]    X  Integer which shall be inspected.
 *  \return       Count of leading zeros.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static uint32 Os_Hal_CLZ(uint32 val);
static uint32 Os_Hal_CLZ(uint32 val)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  OS_IGNORE_UNREF_PARAM(val);         /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  return 0;
}

/*! \brief        Uses a load exclusive synchronization instruction for the address, which attempts to mark the address
 *                for exclusive access by the current processor, and return the result.
 *  \details      -
 *  \param[in]    Addr  Address value to read from.
 *  \return       Value at Addr.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static uint32 Os_Hal_LoadExclusive(const volatile uint32* Addr);
static uint32 Os_Hal_LoadExclusive(const volatile uint32* Addr)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  return (uint32)(*Addr);
}

/*! \brief        Uses a store exclusive synchronization instruction, which attempts to store the value to the address.
 *                Returns 0 on success or 1 otherwise.
 *  \details      -
 *  \param[out]   Addr    Address to write to. Parameter must not be NULL.
 *  \param[in]    Value   Value which shall be written.
 *  \retval       0       Success.
 *  \retval       1       No success.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static uint32 Os_Hal_StoreExclusive(volatile uint32* Addr, uint32 Value);
static uint32 Os_Hal_StoreExclusive(volatile uint32* Addr, uint32 Value)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  OS_IGNORE_UNREF_PARAM(Addr);                                                                                          /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(Value);                                                                                         /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  (*Addr) = Value;                                                                                                      /* SBSW_OS_HAL_PWA_CALLER */
  return (uint32)(*Addr);
}


/*! \brief        Returns a 32-bit value from given coprocessor Coproc.
 *  \details      -
 *  \param[in]    Coproc    Coprocessor to read from.
 *  \param[in]    Opcode1   Coprocessor specific opcode.
 *  \param[in]    CRn       Coprocessor register that contains the first operand.
 *  \param[in]    CRm       Additional source or destination coprocessor register.
 *  \param[in]    Opcode2   Coprocessor specific opcode.
 *  \return       Value read from coprocessor.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static uint32 Os_Hal_ReadFromCoprocessor(uint32 x0, uint32 x1, uint32 x2, uint32 x3, uint32 x4);
static uint32 Os_Hal_ReadFromCoprocessor(uint32 x0, uint32 x1, uint32 x2, uint32 x3, uint32 x4)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  OS_IGNORE_UNREF_PARAM(x0);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(x1);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(x2);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(x3);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(x4);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  return 0x1234UL;
}


/*! \brief        Pass a 32-bit value to given coprocessor Coproc.
 *  \details      -
 *  \param[in]    Value     Value which shall be passed.
 *  \param[in]    Coproc    Coprocessor to pass given value to.
 *  \param[in]    Opcode1   Coprocessor specific opcode.
 *  \param[in]    CRn       Destination coprocessor register.
 *  \param[in]    CRm       Additional destination coprocessor register.
 *  \param[in]    Opcode2   Coprocessor specific opcode.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          -
 */
static void Os_Hal_WriteToCoprocessor(uint32 x0, uint32 x1, uint32 x2, uint32 x3, uint32 x4, uint32 x5);
static void Os_Hal_WriteToCoprocessor(uint32 x0, uint32 x1, uint32 x2, uint32 x3, uint32 x4, uint32 x5)  /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
{
  OS_IGNORE_UNREF_PARAM(x0);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(x1);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(x2);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(x3);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(x4);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
  OS_IGNORE_UNREF_PARAM(x5);  /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
} /* PRQA S 6060 */ /* MD_Os_STPAR */



/*! \brief      Abstraction for declaring a CAT1 ISR. */
# define DeclareCat1Isr(core, level, name)  void name(void)  /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! \brief      Abstraction for defining a CAT1 ISR. */
# define DefineCat1Isr(core, level, name)   void name(void)  /* PRQA S 3453 */ /* MD_MSR_19.7 */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* OS_HAL_STATICCODEANALYSIS_H */

/*!
 * \}
 */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_StaticCodeAnalysis.h
 *********************************************************************************************************************/

