###############################################################################
# File Name  : Mcal_S32k_rules.mak                                            #
# Description: Autosar makefile Template                                      #
#              This makefile is a template to implement the common            #
#              features of each project.                                      #
#              It is included by the Global.Makefile.target.make.$(Version)   #
#              and is supported from version 3.24 .                           #
#                                                                             #
# This Template is based on AUTOSAR_BSW_MakefileInterface.doc version 0.4     #
#                                                                             #
#-----------------------------------------------------------------------------#
#               C O P Y R I G H T                                             #
#-----------------------------------------------------------------------------#
# Copyright (c) 2018 by Vector Informatik GmbH.  All rights reserved.         #
#                                                                             #
#-----------------------------------------------------------------------------#
#               A U T H O R   I D E N T I T Y                                 #
#-----------------------------------------------------------------------------#
# Initials     Name                      Company                              #
# --------     ---------------------     -------------------------------------#
# virgaj       Andrej Gazvoda			 Vector Informatik GmbH               #
# virrsu       Roland Suess				 Vector Informatik GmbH               #
# virmzi	   Marco Ziegler		     Vector Informatik GmbH	              #
# virgki	   Kishore Gunda		     Vector Informatik GmbH	              #
#-----------------------------------------------------------------------------#
#               R E V I S I O N   H I S T O R Y                               #
#-----------------------------------------------------------------------------#
# Date         Version  Sign    Description                                   #
# ----------   -------  ------  ----------------------------------------------#
# 2017-07-18   1.00.00  virgaj 	S32K14X_CSEC_MCAL4_0_RTM_P2_1_0_1			  #
#								S32K14X_MCAL4_0_RTM_1_0_1					  #
#								S32K14X_MCAL4_0_RTM_HF1_1_0_1				  #
#								S32K14X_MCAL4_0_RTM_P1_1_0_1_EEPonly		  #
# 2017-11-07   1.01.00	virgaj 	S32K14X_CSEC_MCAL4_2_RTM_1_0_0				  #
# 								S32K14X_MCAL4_2_RTM_1_0_0 					  #
#								Added ASR_VERSION specific Eep path			  #
#			   1.01.01	virgaj	- jumped over version to meet ALM tag version #	
# 2017-11-15   1.01.02  virgaj	Fixed error in path to CSEC src files		  #
# 2017-12-20   1.02.00  virrsu	Update with S32K14X_MCAL4_0_RTM_HF1_1_0_2	  #
#											S32K14X_CSEC_MCAL4_0_RTM_1_0_2	  #
# 2018-05-29   1.03.00  virmzi	Update with S32K14X_MCAL4_0_RTM__1_0_3	      #
#											S32K14X_MCAL4_0_RTM_HF1_1_0_3	  #
#											S32K14X_CSEC_MCAL4_0_RTM_1_0_3	  #
#								Abstraction: Used wildcard instead of	      #
#								full file names								  #
#								Added defaults for component switches		  #
# 2018-08-02   1.04.00  virgki	OCU module is included to MIP from            #
#                                this version                                 #
# 2018-08-28   1.05.00  virgki	I2C module is included to MIP from            #
#                                this version                                 #
###############################################################################


###############################################################
# REGISTRY
#

#Defaults for component switches
#Can be overwritten in Makefile.project.part.defines
ifeq ($(MCAL_EXCLUDE_ADC),)
MCAL_EXCLUDE_ADC = 0
endif
ifeq ($(MCAL_EXCLUDE_CRY),)
MCAL_EXCLUDE_CRY = 0
endif
ifeq ($(MCAL_EXCLUDE_DIO),)
MCAL_EXCLUDE_DIO = 0
endif
ifeq ($(MCAL_EXCLUDE_EEP),)
MCAL_EXCLUDE_EEP = 0
endif
ifeq ($(MCAL_EXCLUDE_FLS),)
MCAL_EXCLUDE_FLS = 0
endif
ifeq ($(MCAL_EXCLUDE_GPT),)
MCAL_EXCLUDE_GPT = 0
endif
ifeq ($(MCAL_EXCLUDE_ICU),)
MCAL_EXCLUDE_ICU = 0
endif
ifeq ($(MCAL_EXCLUDE_MCEM),)
MCAL_EXCLUDE_MCEM = 0
endif
ifeq ($(MCAL_EXCLUDE_MCU),)
MCAL_EXCLUDE_MCU = 0
endif
ifeq ($(MCAL_EXCLUDE_MCL),)
MCAL_EXCLUDE_MCL = 0
endif
ifeq ($(MCAL_EXCLUDE_OCU),)
MCAL_EXCLUDE_OCU = 0
endif
ifeq ($(MCAL_EXCLUDE_PORT),)
MCAL_EXCLUDE_PORT = 0
endif
ifeq ($(MCAL_EXCLUDE_PWM),)
MCAL_EXCLUDE_PWM = 0
endif
ifeq ($(MCAL_EXCLUDE_SPI),)
MCAL_EXCLUDE_SPI = 0
endif
ifeq ($(MCAL_EXCLUDE_WDG),)
MCAL_EXCLUDE_WDG = 0
endif

MCAL_EXCLUDE_I2C = 1


#e.g.: LIBRARIES_TO_BUILD      +=    $(LIB_OUPUT_PATH)\vendorx_canlib1.$(LIB_FILE_SUFFIX)
LIBRARIES_TO_BUILD      +=

# e.g.: CC_FILES_TO_BUILD       += drv\can_drv.c
						   
#Path to Mcal source and include files
MCAL_PATH = ..\ThirdParty\Mcal_S32k\Supply\S32K14X_MCAL4_2_RTM_HF3_1_0_1
MCAL_MOD_V = T40D2M10I1R0

ASR_VERSION = 4.2.2

EEP_PATH =
CSEC_PATH = ..\ThirdParty\Mcal_S32k\Supply\S32K14X_CSEC_MCAL4_2_RTM_1_0_0

ifeq ($(ASR_VERSION),4.0.3)
MCAL_EXCLUDE_OCU = 1
endif
						   
ADC_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Adc_TS_$(MCAL_MOD_V)
DIO_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Dio_TS_$(MCAL_MOD_V)
FLS_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Fls_TS_$(MCAL_MOD_V)
GPT_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Gpt_TS_$(MCAL_MOD_V)
I2C_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\I2c_TS_$(MCAL_MOD_V)
ICU_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Icu_TS_$(MCAL_MOD_V)
MCEM_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Mcem_TS_$(MCAL_MOD_V)
MCU_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Mcu_TS_$(MCAL_MOD_V)
PORT_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Port_TS_$(MCAL_MOD_V)
PWM_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Pwm_TS_$(MCAL_MOD_V)
SPI_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Spi_TS_$(MCAL_MOD_V)
WDG_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Wdg_TS_$(MCAL_MOD_V)
BASE_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Base_TS_$(MCAL_MOD_V)
MCL_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Mcl_TS_$(MCAL_MOD_V)

ifneq ($(MCAL_EXCLUDE_OCU),1)
OCU_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Ocu_TS_$(MCAL_MOD_V)
endif

CSEC_BASE_PATH = $(CSEC_PATH)\eclipse\plugins\Csec_TS_$(MCAL_MOD_V)


ifeq ($(ASR_VERSION),4.0.3)
	ifeq ($(MCAL_MOD_V),TS_T40D2M10I1R0)
EEP_BASE_PATH = $(EEP_PATH)\eclipse\plugins\Eep_TS_$(MCAL_MOD_V)
	else
EEP_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Eep_TS_$(MCAL_MOD_V)
	endif
else
EEP_BASE_PATH = $(MCAL_PATH)\eclipse\plugins\Eep_TS_$(MCAL_MOD_V)
endif


CSEC_BASE_PATH = $(CSEC_PATH)\eclipse\plugins\Csec_TS_$(MCAL_MOD_V)

ifneq ($(MCAL_EXCLUDE_ADC),1)
CC_FILES_TO_BUILD  += $(ADC_BASE_PATH)\src\Adc*.c
CC_INCLUDE_PATH    += $(ADC_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_CRY),1)
CC_FILES_TO_BUILD += $(CSEC_BASE_PATH)\src\Csec*.c
CC_INCLUDE_PATH   += $(CSEC_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_DIO),1)
CC_FILES_TO_BUILD  += $(DIO_BASE_PATH)\src\Dio*.c
CC_INCLUDE_PATH    += $(DIO_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_EEP),1)
CC_FILES_TO_BUILD += $(EEP_BASE_PATH)\src\Eep*c
CC_INCLUDE_PATH   += $(EEP_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_FLS),1)
CC_FILES_TO_BUILD  += $(FLS_BASE_PATH)\src\Fls*.c
CC_INCLUDE_PATH    += $(FLS_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_GPT),1)
CC_FILES_TO_BUILD  += $(GPT_BASE_PATH)\src\Gpt*.c
CC_INCLUDE_PATH    += $(GPT_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_I2C),1)
CC_FILES_TO_BUILD  += $(I2C_BASE_PATH)\src\I2c*.c \
                      $(I2C_BASE_PATH)\src\CDD_I2c.c
CC_INCLUDE_PATH    += $(I2C_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_ICU),1)
CC_FILES_TO_BUILD  += $(ICU_BASE_PATH)\src\Icu*.c
CC_INCLUDE_PATH    += $(ICU_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_MCEM),1)
CC_FILES_TO_BUILD  += $(MCEM_BASE_PATH)\src\CDD_Mcem.c \
					  $(MCEM_BASE_PATH)\src\Mcem*.c
CC_INCLUDE_PATH    += $(MCEM_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_MCL),1)
CC_FILES_TO_BUILD  += $(MCL_BASE_PATH)\src\CDD_Mcl.c \
					  $(MCL_BASE_PATH)\src\*_Common.c \
					  $(MCL_BASE_PATH)\src\Mcl*.c
CC_INCLUDE_PATH    += $(MCL_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_MCU),1)
CC_FILES_TO_BUILD  += $(MCU_BASE_PATH)\src\Mcu*.c
CC_INCLUDE_PATH    += $(MCU_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_OCU),1)
CC_FILES_TO_BUILD  += $(OCU_BASE_PATH)\src\Ocu*.c
CC_INCLUDE_PATH    += $(OCU_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_PORT),1)
CC_FILES_TO_BUILD  += $(PORT_BASE_PATH)\src\Port*.c
CC_INCLUDE_PATH    += $(PORT_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_PWM),1)
CC_FILES_TO_BUILD  += $(PWM_BASE_PATH)\src\Pwm*.c
CC_INCLUDE_PATH    += $(PWM_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_SPI),1)
CC_FILES_TO_BUILD  += $(SPI_BASE_PATH)\src\Spi*.c
CC_INCLUDE_PATH    += $(SPI_BASE_PATH)\include
endif

ifneq ($(MCAL_EXCLUDE_WDG),1)
CC_FILES_TO_BUILD  += $(WDG_BASE_PATH)\src\Wdg*.c
CC_INCLUDE_PATH    += $(WDG_BASE_PATH)\include
endif

CC_INCLUDE_PATH    += $(BASE_BASE_PATH)\include

#Removed files of Infineon-stack-internal VersionCheck
#$(ADC_BASE_PATH)\src\Adc_Ver.c $(DIO_BASE_PATH)\src\Dio_Ver.c $(GPT_BASE_PATH)\src\Gpt_Ver.c $(ICU_BASE_PATH)\src\Icu_17_GtmCcu6_Ver.c $(MCU_BASE_PATH)\src\Mcu_Ver.c $(PWM_BASE_PATH)\src\Pwm_17_Gtm_Ver.c $(SPI_BASE_PATH)\src\Spi_Ver.c $(FEE_BASE_PATH)\src\Fee_Ver.c $(FLS_BASE_PATH)\src\Fls_17_Pmu_Ver.c

CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=

#LIBRARIES_LINK_ONLY     += (not yet supported)
#OBJECTS_LINK_ONLY       += (not yet supported)

#-------------------------------------------------------------------------------------------------
#only define new dirs, OBJ, LIB, LOG were created automaticly
#-------------------------------------------------------------------------------------------------
DIRECTORIES_TO_CREATE   +=

#DEPEND_GCC_OPTS         += (not yet supported)

# e.g.:  GENERATED_SOURCE_FILES += $(GENDATA_DIR)\drv_par.c
ifneq ($(MCAL_EXCLUDE_ADC),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Adc*.c
endif

ifneq ($(MCAL_EXCLUDE_CRY),1)
GENERATED_SOURCE_FILES += $(GENDATA_DIR)\src\Csec*.c
endif

ifneq ($(MCAL_EXCLUDE_DIO),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Dio*.c
endif

ifneq ($(MCAL_EXCLUDE_EEP),1)
GENERATED_SOURCE_FILES += $(GENDATA_DIR)\src\Eep*.c
endif

ifneq ($(MCAL_EXCLUDE_FLS),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Fls*.c 
endif

ifneq ($(MCAL_EXCLUDE_GPT),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Gpt*.c
	ifneq ($(ASR_VERSION),4.2.2)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Gpt*.c
	endif
endif

ifneq ($(MCAL_EXCLUDE_I2C),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\CDD_I2c*.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\CDD_Mcem*.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\CDD_Mcl*.c
endif

ifneq ($(MCAL_EXCLUDE_ICU),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Icu*.c
endif

ifneq ($(MCAL_EXCLUDE_MCEM),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\CDD_Mcem*.c
endif

ifneq ($(MCAL_EXCLUDE_MCL),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\CDD_Mcl*.c
endif

ifneq ($(MCAL_EXCLUDE_MCU),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Mcu*.c
endif

ifneq ($(MCAL_EXCLUDE_OCU),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Ocu*.c
endif

ifneq ($(MCAL_EXCLUDE_PORT),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Port*.c
endif

ifneq ($(MCAL_EXCLUDE_PWM),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Pwm_PBcfg.c
	ifneq ($(ASR_VERSION),4.2.2)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Pwm_Cfg.c
	endif
endif

ifneq ($(MCAL_EXCLUDE_SPI),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Spi_PBcfg.c
	ifneq ($(ASR_VERSION),4.2.2)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Spi_Lcfg.c $(GENDATA_DIR)\src\Spi_Cfg.c
	endif
endif

ifneq ($(MCAL_EXCLUDE_WDG),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\src\Wdg*.c
endif

ADDITIONAL_INCLUDES     += $(GENDATA_DIR)\include


#e.g.: COMMON_SOURCE_FILES     += $(GENDATA_DIR)\v_par.c
COMMON_SOURCE_FILES     +=

#-------------------------------------------------------------------------------------------------
# <project>.dep & <projekt>.lnk & <project>.bin and.....
# all in err\ & obj\ & lst\ & lib\ & log\ will be deleted by clean-rule automaticly
# so in this clean-rule it is only necessary to define additional files which
# were not delete automaticly.
# e.g.: $(<PATH>)\can_test.c
#-------------------------------------------------------------------------------------------------
MAKE_CLEAN_RULES        +=
#MAKE_GENERATE_RULES     +=
#MAKE_COMPILER_RULES     +=
#MAKE_DEBUG_RULES        +=
#MAKE_CONFIG_RULES       +=
#MAKE_ADD_RULES          +=


###############################################################
# REQUIRED   (defined in BaseMake (global.Makefile.target.make...))
#
# SSC_ROOT		(required)
# PROJECT_ROOT	(required)
#
# LIB_OUTPUT_PATH	(optional)
# OBJ_OUTPUT_PATH	(optional)
#
# OBJ_FILE_SUFFIX
# LIB_FILE_SUFFIX
#
###############################################################


###############################################################
# PROVIDE   this Section can be used to define own additional rules
#
# In vendorx_can_cfg.mak:
# Please configure the project file:
#CAN_CONFIG_FILE = $(PROJECT_ROOT)\source\network\can\my_can_config.cfg

#In vendorx_can_config :
#generate_can_config:
#$(SSC_ROOT)\core\com\can\tools\canconfiggen.exe -o $(CAN_CONFIG_FILE)


###############################################################
# SPECIFIC
#
# There are no rules defined for the Specific part of the
# Rules-Makefile. Each author is free to create temporary
# variables or to use other resources of GNU-MAKE
#
###############################################################


