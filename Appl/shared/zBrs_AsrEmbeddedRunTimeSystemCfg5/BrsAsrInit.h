
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
  \file  File:  BrsAsrInit.h
      Project:  Vector Basic Runtime System for MICROSAR4
       Module:  BrsAsrInit

  \brief Description:  Vector Basic Runtime System for AUTOSAR 4 projects
                       - Module header for initialization routines

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

#ifndef _BRSASRINIT_H_
#define _BRSASRINIT_H_

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
/*
 * Description: The BrsCfg header provides all the necessary configuration switches of the BrsAsr4.
 *              It is either a template file or generated out of Configurator 5.
 */
#include "BrsCfg.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#if defined (VGEN_ENABLE_MEMSERVICE_ASRNVM)
void BrsAsrInit_NvMReadAll(void);
# if defined (BRS_PLATFORM_AURIX) || defined (BRS_PLATFORM_AURIXPLUS)
#  if defined (VGEN_ENABLE_DRVFLS)
void NvM_Call_PreInit(void)
#  endif
# endif
#endif /*VGEN_ENABLE_MEMSERVICE_ASRNVM*/

#if defined (BRSASR_ENABLE_SAFEWDGSUPPORT)
void BrsAsrInit_SafeWdg(void);
# if defined (BRSASR_ENABLE_SAFEWDG_MULTICORESUPPORT)
void BrsAsrInit_SafeWdg_Core1(void);
void BrsAsrInit_SafeWdg_Core2(void);
# endif
#endif /*BRSASR_ENABLE_SAFEWDGSUPPORT*/

#endif /*_BRSASRINIT_H_*/
