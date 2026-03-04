
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
  \file  File:  BrsAsrInit.c
      Project:  Vector Basic Runtime System for MICROSAR4
       Module:  BrsAsrInit

  \brief Description:  Vector Basic Runtime System for AUTOSAR 4 projects 
                       - Module source for initialization routines

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
-----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
-----------------------------------------------------------------------------------------------------------------------
  Benjamin Walter               visbwa        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
 ----------------------------------------------------------------------------------------------------------------------
  01.00.00  2013-12-20  visbwa  Initial creation
  01.00.01  2014-03-27  visbwa  Added call of NvM_ReadAll() within BrsAsrInit_NvMReadAll()
  01.00.02  2014-08-19  visbwa  Added support of CanTransceiver TJA1145
  01.00.03  2014-10-10  visbwa  Added support of Ipv4, Ipv6
  01.00.04  2014-10-16  visbwa  Added support for MultiCore SafeWatchdog Stack
  01.01.00  2015-06-17  visbwa  Removed BrsAsrInit_InitMemory() (not necessary for >=R12)
  01.01.01  2015-09-10  visbwa  Added includes of SchM_Module headers (MainFunctions declared there since ASR4.1.2)
  01.01.02  2016-03-23  visbwa  Added include of WdgM_PBCfg.h to get config pointer
  01.01.03  2017-02-27  visbwa  Added support for SmallSectorFee
  01.01.04  2017-12-06  visbwa  Reworked sample/example code disclaimer
  01.01.05  2018-01-05  visbwa  Enhanced support for DrvFls of platform Aurix/AurixPlus
  01.01.06  2018-01-05  visbwa  Added template implementation of NvM_Call_PreInit() for Infineon Fee usage
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

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "BrsAsrInit.h"

#if defined (VGEN_ENABLE_MEMSERVICE_ASRNVM)
#include "NvM.h"
#include "NvM_PrivateCfg.h"
# if defined (VGEN_ENABLE_DRVFLS)
#include "Fls.h"
#  if defined (BRS_PLATFORM_AURIX) || defined (BRS_PLATFORM_AURIXPLUS)
  #include "SchM_Fls_17_Pmu.h"
#  else
  #include "SchM_Fls.h"
#  endif
# endif
# if defined (VGEN_ENABLE_IF_ASRIFFEE)
#include "Fee.h"
# endif
# if defined (VGEN_ENABLE_IF_ASRIFFEE_SMALLSECTOR)
#include "Fee_30_SmallSector.h"
# endif
# if defined (VGEN_ENABLE_IF_ASRIFEA)
#include "Ea.h"
# endif
# if defined (VGEN_ENABLE_DRVEEP_30_AT25128)
#include "Eep_30_At25128.h"
#  if defined (VGEN_ENABLE_DRVSPI)
#include "Spi.h"
#include "SchM_Spi.h"
#  endif
#  if defined (VGEN_ENABLE_DRVI2C)
#include "I2c.h"
#  endif
# endif /*VGEN_ENABLE_DRVEEP_30_AT25128*/
# if defined (VGEN_ENABLE_DRVEEP)
#include "Eep.h"
#include "SchM_Eep.h"
# endif
# if defined (VGEN_ENABLE_DRVWD)
#include "Wdg.h"
#include "SchM_Wdg.h"
# endif
#endif /*VGEN_ENABLE_MEMSERVICE_ASRNVM*/

#if defined (BRSASR_ENABLE_SAFEWDGSUPPORT)
#include "Wdg.h"
#include "WdgM.h"
#include "WdgM_PBCfg.h"
#endif

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/

#if defined (VGEN_ENABLE_MEMSERVICE_ASRNVM)
void BrsAsrInit_NvMReadAll(void)
{
  NvM_ReadAll();
  {
    NvM_RequestResultType Int_NvMultiBlockStatus;
    do
    {
      NvM_MainFunction();
# if defined (VGEN_ENABLE_DRVFLS)
#  if defined (BRS_PLATFORM_AURIX) || defined (BRS_PLATFORM_AURIXPLUS)
      Fls_17_Pmu_MainFunction();
#  else
      Fls_MainFunction();
#  endif
# endif
# if defined (VGEN_ENABLE_IF_ASRIFFEE)
      Fee_MainFunction();
# endif
# if defined (VGEN_ENABLE_IF_ASRIFFEE_SMALLSECTOR)
      Fee_30_SmallSector_MainFunction();
# endif
# if defined (VGEN_ENABLE_IF_ASRIFEA)
      Ea_MainFunction();
# endif
# if defined (VGEN_ENABLE_DRVEEP_30_AT25128)
      Eep_30_At25128_MainFunction();
#  if defined (VGEN_ENABLE_DRVSPI)
      Spi_MainFunction_Driving();
      Spi_MainFunction_Handling();
#  endif
#  if defined (VGEN_ENABLE_DRVI2C)
      I2c_MainFunction();
#  endif
# endif /* VGEN_ENABLE_DRVEEP_30_AT25128 */
# if defined (VGEN_ENABLE_DRVEEP)
      Eep_MainFunction();
# endif

      NvM_GetErrorStatus(NvMConf___MultiBlockRequest, &Int_NvMultiBlockStatus);

# if defined (VGEN_ENABLE_DRVWD)
      Wdg_SetTriggerCondition(100u);
# endif
    }
    while (Int_NvMultiBlockStatus == NVM_REQ_PENDING);
  }
} /*BrsAsrInit_NvMReadAll*/

# if defined (BRS_PLATFORM_AURIX) || defined (BRS_PLATFORM_AURIXPLUS)
#  if defined (VGEN_ENABLE_DRVFLS)
void NvM_Call_PreInit(void)
{
  uint16 i;
  NvM_RequestResultType Int_NvMultiBlockStatus;

  NvM_DcmBlockMngmt_t.NvDataIndex_t = 0;
  NvM_DcmBlockMngmt_t.NvRamAttributes_u8 = 0;
  NvM_DcmBlockMngmt_t.NvRamErrorStatus_u8 = 0;

  for (i=1; i<NVM_TOTAL_NUM_OF_NVRAM_BLOCKS; i++)
  {
    NvM_InvalidateNvBlock(i);
    Fls_17_Pmu_ControlTimeoutDet(0);
    do
    {
      NvM_MainFunction();
      Fee_MainFunction();
      Fls_17_Pmu_MainFunction();

      NvM_GetErrorStatus(i, &Int_NvMultiBlockStatus);

    }while (Int_NvMultiBlockStatus == NVM_REQ_PENDING);
    Fls_17_Pmu_ControlTimeoutDet(1);
  }
}
#  endif /*VGEN_ENABLE_DRVFLS*/
# endif /*BRS_PLATFORM_AURIX||BRS_PLATFORM_AURIXPLUS*/
#endif /*VGEN_ENABLE_MEMSERVICE_ASRNVM*/

#if defined (BRSASR_ENABLE_SAFEWDGSUPPORT)
/***********************************************************************************************************************
 *  BrsAsrInitSafeWdg
 **********************************************************************************************************************/
/*! \brief      Initialisation of SafeWatchdogStack
 *  \param[in]  -
 *  \param[out] -
 *  \return     -
 *  \context    Function is called from Task WdgStack_ASILD_Task (of BrsAsrMain.c)
 **********************************************************************************************************************/
void BrsAsrInit_SafeWdg(void)
{
  #error "TODO: Initialize Watchdog driver here" */
  Wdg_Init(&wdg_config);

  WdgM_Init(&WdgMConfigSet);
}

# if defined (BRSASR_ENABLE_SAFEWDG_MULTICORESUPPORT)
void BrsAsrInit_SafeWdg_Core1(void)
{
  #error "TODO: Initialize Watchdog driver with pointer to ConfigStruct of Core1 here" */
  Wdg_Init(&wdg_config_core1); 

  WdgM_Init(&WdgMConfigSet1);
}

void BrsAsrInit_SafeWdg_Core2(void)
{
  #error "TODO: Initialize Watchdog driver with pointer to ConfigStruct of Core2 here" */
  Wdg_Init(&wdg_config_core2); 

  WdgM_Init(&WdgMConfigSet2);
}
# endif /*BRSASR_ENABLE_SAFEWDG_MULTICORESUPPORT*/

#endif /*BRSASR_ENABLE_SAFEWDGSUPPORT*/
