
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
  \file  File:  BrsTcc.c
      Project:  Vector Basic Runtime System for MICROSAR4
       Module:  BrsTcc

  \brief Description:  Implementation of static Test Control Center code.

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
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Andreas Hahn                  vishan        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2015-10-06  visbwa  Initial creation of new static BrsTcc part
  01.00.01  2015-10-27  visbwa  Introduced include of BrsTccCfg.h (Generator issue ESCAN00086103)
  01.00.02  2015-11-30  visbwa  Changed include-structure within BrsTcc.h 
                                (to get OS_MS2TICKS_SystemTimer within BrsAsrMain)
  01.01.00  2016-07-11  visbwa  Added TCM support
  01.01.01  2016-08-16  visbwa  Moved include of BrsTccCfg.h into BrsTcc.h to fix include-structure errors
  01.01.02  2016-11-29  vishan  Added TCM header
  01.01.03  2016-12-22  visbwa  Encapsuled ci within BrsTcc_RxIndication() and brsTccLastTransmissionResult (TGF only),
                                removed include of ComStack_Types.h within BrsTcc.h (only available in SIPs with CFG5)
  01.01.04  2017-01-03  vishan  Added BrsTcc_Delay() and BrsTcc_MeasureCyclesPerDelayLoopInMSec()
  01.01.05  2017-01-11  vishan  ORed encapsulation BRSASR_ENABLE_TGFSUPPORT with BRS_ENABLE_HLPTEST_SUPPORT
  01.01.06  2017-12-06  visbwa  Reworked sample/example code disclaimer
  01.01.07  2018-01-05  visbwa  Enhanced VTT support (include of BrsHw.h in BrsTcc.h)
  01.01.08  2018-07-12  visbwa  Reworked encapsulation of BrsTcc1msTask (not needed for HLP testsuite any more)
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
#include "BrsTcc.h"
#if defined (BRS_ENABLE_TCM_SUPPORT)
#include "TcmDriver.h"
#endif

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if (  (BRSTCC_MAJOR_VERSION != (0x01u)) \
    || (BRSTCC_MINOR_VERSION != (0x01u)) \
    || (BRSTCC_PATCH_VERSION != (0x08u)) )
# error "Vendor specific version numbers of BrsTcc.c and BrsTcc.h are inconsistent"
#endif

#if defined (BRSASR_ENABLE_TGFSUPPORT) || defined (BRS_ENABLE_TCM_SUPPORT) || defined (BRS_ENABLE_HLPTEST_SUPPORT)
/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/
#define BRSTCC_NACK  0x7F /* Negative response identifier */  
#define BRSTCC_PACK  0x40 /* Positive response bit */

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/
#if defined (BRSASR_ENABLE_TGFSUPPORT) || defined (BRS_ENABLE_HLPTEST_SUPPORT)
  #define START_SEC_VAR_NOINIT_8BIT
  #include "MemMap.h"

  static uint8 brsTccLastTransmissionResult;

  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif

/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
#define START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"

uint8  brsTccBuffer[8];

#define STOP_SEC_VAR
#include "MemMap.h"

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
#define START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
  BrsTcc_Init
**********************************************************************************************************************/
void BrsTcc_Init(void)
{
# if defined (BRSASR_ENABLE_TGFSUPPORT) || defined (BRS_ENABLE_HLPTEST_SUPPORT)
  brsTccLastTransmissionResult = E_OK;
# endif
  brsTccBuffer[0] = 0;
  brsTccBuffer[1] = 0;
  brsTccBuffer[2] = 0;
  brsTccBuffer[3] = 0;
  brsTccBuffer[4] = 0;
  brsTccBuffer[5] = 0;
  brsTccBuffer[6] = 0;
  brsTccBuffer[7] = 0;
}

/**********************************************************************************************************************
  BrsTccSendResponse
**********************************************************************************************************************/
void BrsTccSendResponse(void)
{
  PduInfoType pduInfo;
  pduInfo.SduDataPtr = &brsTccBuffer[0];
  pduInfo.SduLength = 8;
# if defined (BRSASR_ENABLE_TGFSUPPORT) || defined (BRS_ENABLE_HLPTEST_SUPPORT)
  brsTccLastTransmissionResult = BRS_TRANSMIT_FUNCTION(BRS_TRANSMIT_HANDLE, &pduInfo);
# else
  BRS_TRANSMIT_FUNCTION(BRS_TRANSMIT_HANDLE, &pduInfo);
# endif
}

# if defined (BRSASR_ENABLE_TGFSUPPORT)
/**********************************************************************************************************************
  BrsTcc1msTask
**********************************************************************************************************************/
TASK(BrsTcc1msTask) 
{
  EventMaskType ev;
  (void)SetRelAlarm(Alarm_BrsTcc1msTask, OS_MS2TICKS_SystemTimer(1), OS_MS2TICKS_SystemTimer(1));
  for(;;)
  {
    (void)WaitEvent(Event_BrsTcc1msTask);
    (void)GetEvent(BrsTcc1msTask, &ev);
    (void)ClearEvent(ev & (Event_BrsTcc1msTask));

    if ((ev & Event_BrsTcc1msTask) != (EventMaskType)0)
    {
      if (E_OK != brsTccLastTransmissionResult)
      {
        PduInfoType pduInfo;
        pduInfo.SduDataPtr = &brsTccBuffer[0];
        pduInfo.SduLength = 8;
        brsTccLastTransmissionResult = BRS_TRANSMIT_FUNCTION(BRS_TRANSMIT_HANDLE, &pduInfo);
      }
    }
  }
}
# endif /*BRSASR_ENABLE_TGFSUPPORT*/

/**********************************************************************************************************************
  BrsTccSendNegResponse
**********************************************************************************************************************/
void BrsTccSendNegResponse(uint8 errorCode)
{
  brsTccBuffer[3] = errorCode;
  brsTccBuffer[2] = brsTccBuffer[1];
  brsTccBuffer[1] = brsTccBuffer[0];
  brsTccBuffer[0] = BRSTCC_NACK;
  
  brsTccBuffer[4] = 0;
  brsTccBuffer[5] = 0;
  brsTccBuffer[6] = 0;
  brsTccBuffer[7] = 0;
  
  BrsTccSendResponse();
}

/**********************************************************************************************************************
  BrsTccSendPosResponse
**********************************************************************************************************************/
void BrsTccSendPosResponse(void)
{
  brsTccBuffer[1] |= BRSTCC_PACK;
  BrsTccSendResponse();
}

/**********************************************************************************************************************
  BrsTcc_RxIndication
**********************************************************************************************************************/
void BrsTcc_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, BRSTCC_DATA) PduInfoPtr)
{
  uint8 si;
# if defined (BRSASR_ENABLE_TGFSUPPORT) || defined (BRS_ENABLE_HLPTEST_SUPPORT)
  uint8 ci;
  ci = PduInfoPtr->SduDataPtr[0];
# endif
  si = PduInfoPtr->SduDataPtr[1];

  switch (si)
  {
    case BRSTCC_FCT_RDBI:
    {
      brsTccBuffer[2] = brsTccBuffer[4];
      brsTccBuffer[3] = brsTccBuffer[5];
      break;
    }
  }
# if defined (BRSASR_ENABLE_TGFSUPPORT) || defined (BRS_ENABLE_HLPTEST_SUPPORT)
  TgfAppl_TccCmdIn(ci, si, PduInfoPtr);
# else
  BrsTccSendResponse();
# endif
}

/**********************************************************************************************************************
  BrsTcc_TxConfirmation
**********************************************************************************************************************/
void BrsTcc_TxConfirmation(PduIdType TxPduId)
{

}

/**********************************************************************************************************************
  BrsTcc_TriggerTransmit
**********************************************************************************************************************/
Std_ReturnType BrsTcc_TriggerTransmit(PduIdType TxPduId, CONSTP2VAR(PduInfoType, AUTOMATIC, BRSTCC_DATA) PduInfoPtr)
{
  uint8 i = 8;
  while (i--) 
  {
    PduInfoPtr->SduDataPtr[i] = brsTccBuffer[i];
  }
  PduInfoPtr->SduLength = 8;
  return E_OK;
}

# if defined (BRSHW_CYCLES_PER_DELAY_LOOP)
/**********************************************************************************************************************
  BrsTcc_Delay
**********************************************************************************************************************/
void BrsTcc_Delay(int usec)
{
  volatile uint32 i    = 0;
  volatile uint32 imax = 0;

#  if (BRSHW_CYCLES_PER_DELAY_LOOP == 0)
  /* Measure the BRSHW_CYCLES_PER_DELAY_LOOP value in msec by half cycle lenght.
  One half cycle time of signal toogle in msec: _|<-->|____|----|_ (e.g. 6 ms)
  "* usec / usec" is a dummy instruction against unwanted compiler optimisation */
  imax = BRSTCC_DELAY_CYCLES(usec) * usec / usec;
#  else
  /* correct value of BRSHW_CYCLES_PER_DELAY_LOOP should result in 1 ms per half cycle */
  imax = BRSTCC_DELAY_CYCLES(usec) / BRSHW_CYCLES_PER_DELAY_LOOP;
#  endif /* BRSHW_CYCLES_PER_DELAY_LOOP == 0 */
  for(i = 0;i < imax;i++); /* dummy delay loop */
}

/**********************************************************************************************************************
  BrsTcc_MeasureCyclesPerDelayLoopInMSec
**********************************************************************************************************************/
void BrsTcc_MeasureCyclesPerDelayLoopInMSec()
{
  int level = 0;
  int usec = 1000;
  while(1)
  {
    if (level == 0)
    {
      level = 1;
    }
    else
    {
      level = 0;
    }
#  if defined (BRS_ENABLE_TCM_SUPPORT)
    BrsHw_WriteDio_TCM_CLK_OUT(level);
#  endif
#  if defined (BRS_ENABLE_SUPPORT_LEDS)
    BrsHwSetLed(0, level); /* please set a valid LedNumber, if you want an LED signal */
#  endif
    BrsTcc_Delay(usec);
  }
}
# endif /*BRSHW_CYCLES_PER_DELAY_LOOP*/

#define STOP_SEC_CODE
#include "MemMap.h"

#endif /*BRSASR_ENABLE_TGFSUPPORT || BRS_ENABLE_TCM_SUPPORT || BRS_ENABLE_HLPTEST_SUPPORT*/
