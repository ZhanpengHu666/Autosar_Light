/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 * \ingroup      Os_Hal
 * \defgroup     Os_Hal_Derivative HAL Derivative
 *
 * \{
 * \file         Os_Hal_DerivativeInt.h
 * \brief        Selects a derivative specific header and includes it.
 * \details
 *  This modules decides which HAL specific sub components are needed to implement HAL functionality on a specific
 *  derivative.
 *
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/


#if !defined(OS_HAL_DERIVATIVEINT_H)
# define OS_HAL_DERIVATIVEINT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */

/* Os module declarations */
# include "Os_Cfg.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
# if defined(OS_CFG_DERIVATIVEGROUP_ATSAMV7X)                                                                           /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
#  include "Os_Hal_Derivative_ATSAMV7xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_S32K14X)                                                                          /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_S32K14xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_S32K148)                                                                          /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_S32K148Int.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_GENERIC_CORTEXM)                                                                  /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_Generic_CortexMInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_GENERIC_CORTEXM_MP)                                                               /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_Generic_CortexM_MpInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TDA2X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TDA2xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_CYT2BX)                                                                           /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_CYT2BxInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_IMX8X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_IMX8xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_S32X)
#  include <Os_Hal_Derivative_S32xInt.h>
# else
#  error "The selected derivative is not supported!"
# endif /* OS_CFG_DERIVATIVE_<> */

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/


#endif /* OS_HAL_DERIVATIVEINT_H */

/*!
 * \}
 */
/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_DerivativeInt.h
 **********************************************************************************************************************/
