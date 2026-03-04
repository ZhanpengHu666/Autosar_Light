
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
  \file  File:  BrsHw_DerivativeList.h
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform NXP S32K1xx

  \brief Description:  This header file contains the information for the specific groups of the different derivatives,
                       supported by this Brs implementation.

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
  Sherif Elsabbahy              vissey        Vector Informatik GmbH
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Michael Tiran                 vismin        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
  Hakan Capci                   vishci        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2017-03-15  vissey  First Version
  01.00.01  2017-03-20  visbwa  Added error for unfinished S32V
  01.00.02  2017-07-27  vismin  Added BRSHW_USERMODE_ACCESS_GROUP_A
  01.00.03  2018-01-29  vismaa  Added S32K116 and S32K118
  01.00.04  2018-08-03  vismaa  Added error directive for S32K1xx S32k11RAMinit.ini hint
  01.01.05  2018-08-17  vishci  Removed implementation of S32V234, reworked groups of S32K11x
**********************************************************************************************************************/

#ifndef _BRSHW_DERIVATIVELIST_H_
#define _BRSHW_DERIVATIVELIST_H_

/****************************************************
  SUPPORTED DERIVATIVES
*****************************************************/
#if defined (BRS_DERIVATIVE_S32K116) || defined (BRS_DERIVATIVE_S32K118)
  #error: +++ ATTENTION +++ \
  S32K11x needs to initalize RAM. Brs was testet with S32K118 and IC5000. Therefore you need to use the "S32k11RAMinit.ini" file. \
  This has to be added in winIDEA "Emulation Options" --> "Initalization" with the following values:  Initialization = Ini sequence, load from file S32k11RAMinit.ini, \
  Address offset = Specify 0 HEX */
# if defined (BRS_DERIVATIVE_S32K116)
  #error: Adjust the "S32k11RAMinit.ini" file for you needs (RAM size). Only tested with S32K118 so far. */
# endif
  #define BRSHW_CPU_MAX_FREQUENCY 48
  #define BRSHW_INTERRUPT_TABLE_GROUP_B
  #define BRSHW_PLL_GROUP_B
  #define BRSHW_CLOCK_GROUP_B
  #define BRSHW_TIMER_GROUP_A
  #define BRSHW_PORT_GROUP_B
  #define BRSHW_USERMODE_ACCESS_GROUP_A

#elif defined (BRS_DERIVATIVE_S32K142) || defined (BRS_DERIVATIVE_S32K144) || \
      defined (BRS_DERIVATIVE_S32K146) || defined (BRS_DERIVATIVE_S32K148) || \
      defined (BRS_DERIVATIVE_WCT1013) || defined (BRS_DERIVATIVE_WCT1014)
  #define BRSHW_CPU_MAX_FREQUENCY 112
  #define BRSHW_INTERRUPT_TABLE_GROUP_A
  #define BRSHW_PLL_GROUP_A
  #define BRSHW_CLOCK_GROUP_A
  #define BRSHW_TIMER_GROUP_A
  #define BRSHW_PORT_GROUP_A
  #define BRSHW_USERMODE_ACCESS_GROUP_A

#else
  #error "Configured derivative (Makefile.config) not yet supported"
#endif /*BRS_DERIVATIVE_x*/

#endif /*_BRSHW_DERIVATIVELIST_H_*/
