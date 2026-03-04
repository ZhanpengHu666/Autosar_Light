/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  CanNm_Cbk.h
 *        \brief  TODO
 *
 *      \details  TODO
 *
 *  \attention    Please note:
 *                The demo and example programs only show special aspects of the software. With regard to the fact
 *                that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
 *                expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  TODO                          virvll        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  YYYY-MM-DD  virvll TODO          TODO
 *********************************************************************************************************************/
#ifndef APPL_INCLUDE_CANNM_CBK_H_
#define APPL_INCLUDE_CANNM_CBK_H_

#include "Compiler.h"

#define CANNM_CODE

#define CanNmConf_CanNmRxPdu_CAN_5f8bc0cc_Rx 0U
#define CanNmConf_CanNmTxPdu_msg_nm_MyECU_oCAN_9090bd79_Tx 3

CanIf_SimpleRxIndicationFctType CanNm_RxIndication (void)
{
  return 0;
}

FUNC( void, CANNM_CODE ) CanNm_TxConfirmation (void)
{
}

#endif /* APPL_INCLUDE_CANNM_CBK_H_ */
