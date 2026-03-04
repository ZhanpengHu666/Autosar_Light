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
 *  \ingroup    Os_Hal
 *  \defgroup   Os_Hal_MemoryProtection  HAL Memory Protection
 *  \brief      Internal functions and data types related to memory protection.
 *  \details
 *  \{
 *
 *  \file
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined (OS_HAL_MEMORYPROTECTION_PMSAV7MINT_H)                                                                     /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_MEMORYPROTECTION_PMSAV7MINT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/*! MPU specific define for stack region configuration. */
# define OS_HAL_MPU_GETSTACKREGIONINFO(stackConfig)   (stackConfig.StackRegionSize)                                     /* PRQA S 3410, 3453 */ /* MD_Os_Hal_3410_Decl, MD_MSR_19.7 */

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/
# define OS_HAL_MP_MPU_BASE    (0xE000ED90UL)

/*! MPU Type Register (MPU_TYPE). */
# define OS_HAL_MP_MPU_TYPE    (*(volatile uint32*) (OS_HAL_MP_MPU_BASE +  0x0UL))

/*! MPU Control Register (MPU_CTRL). */
# define OS_HAL_MP_MPU_CTRL    (*(volatile uint32*) (OS_HAL_MP_MPU_BASE +  0x4UL))

/*! MPU Region Number Register (MPU_RNR). */
# define OS_HAL_MP_MPU_RNR     (*(volatile uint32*) (OS_HAL_MP_MPU_BASE +  0x8UL))

/*! MPU Region Base Address Register (MPU_RBAR). */
# define OS_HAL_MP_MPU_RBAR    (*(volatile uint32*) (OS_HAL_MP_MPU_BASE +  0xCUL))

/*! MPU Region Attribute and Size Register (MPU_RASR). */
# define OS_HAL_MP_MPU_RASR    (*(volatile uint32*) (OS_HAL_MP_MPU_BASE + 0x10UL))

/*! MPU Control Register, MPU active. */
# define OS_HAL_MP_MPU_CTRL_ENABLE     (1UL << 0)
/*! MPU Control Register, MPU active in HardFault and NMIs. */
# define OS_HAL_MP_MPU_CTRL_HFNMIENA   (1UL << 1)
/*! MPU Control Register, Enable background region. */
# define OS_HAL_MP_MPU_CTRL_PRIVDEFENA (1UL << 2)

/*! Region Attribute and Size Register (MPU_RASR): Value to use for a disabled region. */
# define OS_HAL_MP_REGION_DISABLED_VALUE           (0UL)
/*! Region Attribute and Size Register (MPU_RASR): MPU_RASR.ENABLE bit. */
# define OS_HAL_MP_REGION_SIZE_ENABLE              (1UL     << 0)
/*! Region Attribute and Size Register (MPU_RASR): MPU_RASR.SIZE field. */
# define OS_HAL_MP_REGION_SIZE_POWER_OF_TWO(x)     (((x) - 1) << 1)                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Region Attribute and Size Register (MPU_RASR): MPU_RASR.S bit. */
# define OS_HAL_MP_ACCESS_SHAREABLE                (1UL << 18)
/*! Region Attribute and Size Register (MPU_RASR): MPU_RASR.XN bit, allowed value. */
# define OS_HAL_MP_ACCESS_EXECUTE_ALLOWED          (0UL << 28)
/*! Region Attribute and Size Register (MPU_RASR): MPU_RASR.XN bit, forbidden value. */
# define OS_HAL_MP_ACCESS_EXECUTE_FORBIDDEN        (1UL << 28)

/*! \brief  Region Attribute and Size Register (MPU_RASR): MPU_RASR.AP value.
 *  \details Supervisor: --- User: ---. */
# define OS_HAL_MP_ACCESS_S_NONE_U_NONE              (0UL << 24)
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.AP value.
 *  \details Supervisor: RW- User: ---. */
# define OS_HAL_MP_ACCESS_S_RW_U_NONE                (1UL << 24)
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.AP value.
 *  \details Supervisor: RW- User: R--. */
# define OS_HAL_MP_ACCESS_S_RW_U_R                   (2UL << 24)
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.AP value.
 *  \details Supervisor: RW- User: RW-. */
# define OS_HAL_MP_ACCESS_S_RW_U_RW                  (3UL << 24)
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.AP value.
 *  \details Supervisor: R-- User: ---. */
# define OS_HAL_MP_ACCESS_S_R_U_NONE                 (5UL << 24)
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.AP value.
 *  \details Supervisor: R-- User: R--. */
# define OS_HAL_MP_ACCESS_S_R_U_R                    (6UL << 24)

/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.C,B and TEX value
 *  \details Strongly ordered. */
# define OS_HAL_MP_ACCESS_TYPE_STRONGLY_ORDERED               ((0UL << 19) | (0UL << 16))
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.C,B and TEX value
 *  \details Outer and inner Non-cacheable. */
#define OS_HAL_MP_ACCESS_TYPE_NON_CACHEABLE                     ((1UL << 19) | (0UL << 16))
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.C,B and TEX value
 *  \details Outer and Inner Write-Back, Cacheable. */
# define OS_HAL_MP_ACCESS_TYPE_CACHEABLE_WRITEBACK_ALLOCATE   ((1UL << 19) | (3UL << 16))
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.C,B and TEX value
 *  \details Shared device, Non-cacheable. */
# define OS_HAL_MP_ACCESS_TYPE_SHARED_DEVICE                         ((0UL << 19) | (1UL << 16))
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.C,B and TEX value
 *  \details Non-Shared device, Non-cacheable. */
# define OS_HAL_MP_ACCESS_TYPE_NON_SHARED_DEVICE              ((2UL << 19) | (0UL << 16))
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.C,B and TEX value
 *  \details Outer and inner write-through, no write allocate. */
# define OS_HAL_MP_ACCESS_TYPE_CACHEABLE_WRITETHROUGH_NO_ALLOCATE   ((0UL << 19) | (2UL << 16))
/*! \brief   Region Attribute and Size Register (MPU_RASR): MPU_RASR.C,B and TEX value
 *  \details Outer and inner write-back, no write allocate. */
# define OS_HAL_MP_ACCESS_TYPE_CACHEABLE_WRITEBACK_NO_ALLOCATE            ((0UL << 19) | (3UL << 16))
/*! \brief   Attributes and size for the maximum stack. */
# define OS_HAL_MP_STACK_MAXSIZE_AND_ATTRIBUTES  ((OS_HAL_MP_ACCESS_S_RW_U_RW)                         | \
                                                  (OS_HAL_MP_REGION_SIZE_ENABLE)                       | \
                                                  (OS_HAL_MP_ACCESS_EXECUTE_ALLOWED)                   | \
                                                  (OS_HAL_MP_ACCESS_TYPE_CACHEABLE_WRITEBACK_ALLOCATE) | \
                                                  (OS_HAL_REGION_MAXSIZE)                                 )

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! Description of a single region in the ARM PMSAv7m implementation. */
struct Os_Hal_MpRegionType_Tag
{
  uint32 RegionNumber;           /*!< Region number (MPU_RNR). */
  uint32 RegionBaseAddress;      /*!< Region base address (MPU_RBAR). */
  uint32 RegionAttributeAndSize; /*!< Region attribute, size and enable value (MPU_RASR). */
};

#endif /* OS_HAL_MEMORYPROTECTION_PMSAV7MINT_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_MemoryProtection_PMSAv7mInt.h
 **********************************************************************************************************************/
