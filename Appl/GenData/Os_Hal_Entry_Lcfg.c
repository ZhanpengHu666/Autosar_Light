/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: Harman International (China) Holdings Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: FS32K148UAT0VLQR
 *    License Scope : The usage is restricted to CBD1800257_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Hal_Entry_Lcfg.c
 *   Generation Time: 2021-06-22 16:26:33
 *           Project: S32K144_Start - Version 1.0
 *          Delivery: CBD1800257_D01
 *      Tool Version: DaVinci Configurator  5.18.37 SP1
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_HAL_ENTRY_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Entry_Cfg.h"
#include "Os_Hal_Entry_Lcfg.h"
#include "Os_Hal_Entry.h"

/* Os kernel module dependencies */
#include "Os_Isr_Lcfg.h"
#include "Os.h"

/* Os hal dependencies */
#include "Os_Hal_Cfg.h"
#include "Os_Hal_Core_Lcfg.h"
#include "Os_Hal_Interrupt_Cfg.h"
#include "Os_Hal_Trap.h"


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EXCEPTION VECTOR TABLE CORE 0
 *********************************************************************************************************************/




/**********************************************************************************************************************
 *  INTERRUPT VECTOR TABLE CORE 0
 *********************************************************************************************************************/

#define OS_START_SEC_INTVEC_CORE0_CODE
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Extern declarations of the ISR wrappers. */
extern void Os_Isr_Core0_Interrupt_15(void); /* PRQA S 3447 */ /* MD_Os_Hal_3447_Loc */
extern void Os_Isr_Core0_Interrupt_94(void); /* PRQA S 3447 */ /* MD_Os_Hal_3447_Loc */
extern void Os_Isr_Core0_Interrupt_97(void); /* PRQA S 3447 */ /* MD_Os_Hal_3447_Loc */
extern void Os_Isr_Core0_Interrupt_98(void); /* PRQA S 3447 */ /* MD_Os_Hal_3447_Loc */

#define OS_STOP_SEC_INTVEC_CORE0_CODE
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define OS_START_SEC_INTVEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

OS_HAL_CONST_ATTRIBUTE_DEFINITION
(
  Os_Hal_VectorTableEntryType,
  OS_CONST,
  OS_HAL_SECTION_ATTRIBUTE("OsCore0_VectorTable_Section"),
  OsCfg_Hal_Core_OsCore0_VectorTable[240]
) =
{
  /* Reset stack value: Init stack OsCore0 */
  (Os_Hal_VectorTableEntryType)((uint32)(OS_STACK_GETHIGHADDRESS(OsCfg_Stack_OsCore0_Init_Dyn)+1)), /* PRQA S 0305, 0306, 0489 */ /* MD_Os_Hal_0305, MD_Os_Hal_0306, MD_Os_Hal_0489_GenData */
  /* Reset: Core entry symbol OsCore0 */
  (Os_Hal_VectorTableEntryType)((uint32)&(Reset_Handler)), /* PRQA S 0305, 0306 */ /* MD_Os_Hal_0305, MD_Os_Hal_0306 */
  /* User configured exceptions and interrupts: */
  Os_Hal_UnhandledEXC, /* Exception: 2 */
  Os_Hal_UnhandledEXC, /* Exception: 3 */
  Os_Hal_UnhandledEXC, /* Exception: 4 */
  Os_Hal_UnhandledEXC, /* Exception: 5 */
  Os_Hal_UnhandledEXC, /* Exception: 6 */
  Os_Hal_UnhandledEXC, /* Exception: 7 */
  Os_Hal_UnhandledEXC, /* Exception: 8 */
  Os_Hal_UnhandledEXC, /* Exception: 9 */
  Os_Hal_UnhandledEXC, /* Exception: 10 */
  Os_Hal_SysCallHandler, /* OS internal SVCall (Number 11) exception handler */
  Os_Hal_UnhandledEXC, /* Exception: 12 */
  Os_Hal_UnhandledEXC, /* Exception: 13 */
  Os_Hal_UnhandledEXC, /* Exception: 14 */
  Os_Isr_Core0_Interrupt_15, /* External interrupt: 15 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 16 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 17 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 18 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 19 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 20 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 21 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 22 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 23 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 24 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 25 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 26 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 27 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 28 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 29 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 30 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 31 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 32 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 33 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 34 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 35 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 36 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 37 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 38 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 39 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 40 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 41 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 42 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 43 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 44 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 45 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 46 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 47 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 48 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 49 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 50 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 51 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 52 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 53 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 54 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 55 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 56 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 57 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 58 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 59 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 60 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 61 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 62 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 63 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 64 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 65 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 66 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 67 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 68 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 69 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 70 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 71 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 72 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 73 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 74 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 75 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 76 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 77 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 78 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 79 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 80 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 81 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 82 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 83 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 84 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 85 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 86 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 87 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 88 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 89 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 90 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 91 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 92 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 93 */
  Os_Isr_Core0_Interrupt_94, /* External interrupt: 94 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 95 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 96 */
  Os_Isr_Core0_Interrupt_97, /* External interrupt: 97 */
  Os_Isr_Core0_Interrupt_98, /* External interrupt: 98 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 99 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 100 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 101 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 102 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 103 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 104 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 105 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 106 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 107 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 108 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 109 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 110 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 111 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 112 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 113 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 114 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 115 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 116 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 117 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 118 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 119 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 120 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 121 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 122 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 123 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 124 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 125 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 126 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 127 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 128 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 129 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 130 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 131 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 132 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 133 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 134 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 135 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 136 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 137 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 138 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 139 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 140 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 141 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 142 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 143 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 144 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 145 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 146 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 147 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 148 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 149 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 150 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 151 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 152 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 153 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 154 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 155 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 156 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 157 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 158 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 159 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 160 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 161 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 162 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 163 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 164 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 165 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 166 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 167 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 168 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 169 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 170 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 171 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 172 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 173 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 174 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 175 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 176 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 177 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 178 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 179 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 180 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 181 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 182 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 183 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 184 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 185 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 186 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 187 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 188 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 189 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 190 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 191 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 192 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 193 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 194 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 195 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 196 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 197 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 198 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 199 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 200 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 201 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 202 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 203 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 204 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 205 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 206 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 207 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 208 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 209 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 210 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 211 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 212 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 213 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 214 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 215 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 216 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 217 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 218 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 219 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 220 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 221 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 222 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 223 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 224 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 225 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 226 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 227 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 228 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 229 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 230 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 231 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 232 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 233 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 234 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 235 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 236 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 237 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 238 */
  Os_Hal_UnhandledIRQ, /* External interrupt: 239 */
};

#define OS_STOP_SEC_INTVEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */




/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Entry_Lcfg.c
 *********************************************************************************************************************/
