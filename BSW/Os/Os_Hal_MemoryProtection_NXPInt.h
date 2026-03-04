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
 *  \addtogroup Os_Hal_MemoryProtection
 *  \{
 *
 *  \file
 *  \brief
 *  \details
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined (OS_HAL_MEMORYPROTECTION_NXPINT_H)                                                                         /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_MEMORYPROTECTION_NXPINT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Region descriptors start offset */
# define OS_HAL_SMPU_RGD_DESCRIPTOR_OFFSET         (0x400UL)
/*! Region alternate access configuration resgister offset */
# define OS_HAL_SMPU_RGDAAC_DESCRIPTOR_OFFSET      (0x800UL)
/*! Length of a region descriptor in Byte */
# define OS_HAL_SMPU_RGD_DESCRIPTOR_LENGTH         (0x10UL)
/*! Offset of Region Descriptor Word 0 (SMPU_RGDn_WORD0) */
# define OS_HAL_SMPU_RGD_DESCRIPTOR_WORD_0_OFFSET  (0x00UL)
/*! Offset of Region Descriptor Word 1 (SMPU_RGDn_WORD1) */
# define OS_HAL_SMPU_RGD_DESCRIPTOR_WORD_1_OFFSET  (0x04UL)
/*! Offset of Region Descriptor Word 2 (SMPU_RGDn_WORD2) */
# define OS_HAL_SMPU_RGD_DESCRIPTOR_WORD_2_OFFSET  (0x08UL)
/*! Offset of Region Descriptor Word 3 (SMPU_RGDn_WORD3) */
# define OS_HAL_SMPU_RGD_DESCRIPTOR_WORD_3_OFFSET  (0x0CUL)

/*! CESR provides error status plus configuration information.
 *  A global SMPU enable/disable bit is also included in this register.
 */
# define OS_HAL_SMPU_CESR_OFFSET                   (0x0UL)

/*! Basic bit mask for bus master access evaluation */
# define OS_HAL_SMPU_RGD_WORD_2_MSK                (0x0UL)

/*! Bit mask for region valid flag */
# define OS_HAL_SMPU_RGD_VALID                     (0x1UL)
/*! Bit mask for region invalid flag */
# define OS_HAL_SMPU_RGD_INVALID                   (0x0UL)

/*! Number of Bits used for Access Right definition */
# define OS_HAL_SMPU_ACCESSRIGHTWIDTH              (0x6UL)

/*! Bit mask for user mode none */
# define OS_HAL_SMPU_UNONE_MSK                     (0x0UL)
/*! Bit mask for user mode execute access */
# define OS_HAL_SMPU_UX_MSK                        (0x1UL)
/*! Bit mask for user mode write access */
# define OS_HAL_SMPU_UW_MSK                        (0x2UL)
/*! Bit mask for user mode read access */
# define OS_HAL_SMPU_UR_MSK                        (0x4UL)
/*! Bit mask for supervisor mode read, write and execute access */
# define OS_HAL_SMPU_SRWX_MSK                      (0x0UL)
/*! Bit mask for supervisor mode read and execute access */
# define OS_HAL_SMPU_SRX_MSK                       (0x8UL)
/*! Bit mask for supervisor mode read and write access */
# define OS_HAL_SMPU_SRW_MSK                       (0x10UL)
/*! Bit mask for supervisor mode same as user mode access */
# define OS_HAL_SMPU_SU_MSK                        (0x18UL)
/*! Bit mask for PID enable */
# define OS_HAL_SMPU_PID_ENABLE                    (0x20UL)
/*! \brief   Attributes and size for the maximum stack. */
# define OS_HAL_MP_STACK_MAXSIZE_AND_ATTRIBUTES    (0xFFFFffffUL)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/*! MPU specific define for stack region configuration. */
# define OS_HAL_MPU_GETSTACKREGIONINFO(stackConfig)   (stackConfig.StackRegionEnd)                                      /* PRQA S 3410, 3453 */ /* MD_Os_Hal_3410_Decl, MD_MSR_19.7 */

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! System MPU Region description */
struct Os_Hal_MpRegionType_Tag
{
  /*! Base Address of the corresponding SMPU Unit */
  uint32 MpuBaseAddress;
  /*! Memory Region Identifier */
  uint32 RegionIndex;
  /*! Region Word 0 defines the byte start address of the memory region (16 byte aligned)*/
  uint32 Word0;
  /*! Region Word 1 defines the byte end address of the memory region (16 byte aligned)*/
  uint32 Word1;
  /*! Region Word 2 defines the access control rights of the memory region */
  uint32 Word2;
  /*! Region Word 3 defines the PID and PIDMSK configuration and the region valid flag. */
  uint32 Word3;
};

#endif /* OS_MEMORYPROTECTION_NXPINT_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_MemoryProtection_NXPInt.h
 **********************************************************************************************************************/
