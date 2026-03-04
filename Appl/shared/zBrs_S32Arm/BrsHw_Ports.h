
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
  \file  File:  BrsHw_Ports.h
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform Freescale S32K1xx

  \brief Description:  This header file contains the information for the evalboard specific port settings,
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
  Cyrille  Wamba                viswca        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Michael Tiran                 vismin        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2017-02-24  viswca  Initial creation for TCM support and alive LED handling
  01.00.01  2017-04-28  visivg  Added Pin configuration for alive LED support, CAN and LIN
            2017-05-15  visbwa  Review
  01.00.02  2017-08-11  vismin  Added Pin configurations for I2c
  01.00.03  2017-08-31  visbwa  Added missing BRSHW_PORT_CONF_I2C
  01.00.04  2018-01-30  vismaa  Added PORT_GROUP_C, used generic PORT definition types for PORT_GROUP_A + PORT_GROUP_C
  01.01.00  2018-06-14  vismaa  Added FBL support (custom and watchdog toggle pin),
                                added error directives for not implemented bus channels
  01.01.01  2018-08-03  vismaa  Added Can0 Pins for BRSHW_PORT_GROUP_C
  01.01.02  2018-08-20  visbwa  Removed implementation of HSR_1387
  01.01.03  2018-08-20  vishci  Renamed BRSHW_PORT_GROUP_C into BRSHW_PORT_GROUP_B
  01.01.04  2018-11-05  vishci  Disabled Open Drain for BRSHW_PORT_CONF_CAN
**********************************************************************************************************************/

#ifndef _BRSHW_PORTS_H_
#define _BRSHW_PORTS_H_


/*******************************************************************************
  Generic PORT definition types
********************************************************************************/
typedef enum
{
  BRSHW_PORT_PORTGROUP_A=0x40049000,
  BRSHW_PORT_PORTGROUP_B=0x4004A000,
  BRSHW_PORT_PORTGROUP_C=0x4004B000,
  BRSHW_PORT_PORTGROUP_D=0x4004C000,
  BRSHW_PORT_PORTGROUP_E=0x4004D000
}brsHw_Port_PortGroupType;

typedef enum
{
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_PORTNUMBER_16,
  BRSHW_PORT_PORTNUMBER_17,
  BRSHW_PORT_PORTNUMBER_18,
  BRSHW_PORT_PORTNUMBER_19,
  BRSHW_PORT_PORTNUMBER_20,
  BRSHW_PORT_PORTNUMBER_21,
  BRSHW_PORT_PORTNUMBER_22,
  BRSHW_PORT_PORTNUMBER_23,
  BRSHW_PORT_PORTNUMBER_24,
  BRSHW_PORT_PORTNUMBER_25,
  BRSHW_PORT_PORTNUMBER_26,
  BRSHW_PORT_PORTNUMBER_27,
  BRSHW_PORT_PORTNUMBER_28,
  BRSHW_PORT_PORTNUMBER_29,
  BRSHW_PORT_PORTNUMBER_30,
  BRSHW_PORT_PORTNUMBER_31
}brsHw_Port_PortNumberType;

typedef enum
{
  BRSHW_PORT_ALT_0,
  BRSHW_PORT_ALT_1,
  BRSHW_PORT_ALT_2,
  BRSHW_PORT_ALT_3,
  BRSHW_PORT_ALT_4,
  BRSHW_PORT_ALT_5
}brsHw_Port_AlternativeType;

typedef struct
{
  brsHw_Port_PortGroupType   portGroup;
  brsHw_Port_PortNumberType  portNumber;
  brsHw_Port_AlternativeType portAlternative;
}brsHw_Port_PortType;

typedef enum
{
  PORT_OPEN_DRAIN_DISABLED,
  PORT_OPEN_DRAIN_ENABLED
}brsHw_Port_OpenDrainOutput;

typedef enum
{
  PORT_PULL_DISABLED,
  PORT_PULL_ENABLED
}brsHw_Port_PullEnableOption;

typedef enum
{
  PORT_PULL_UP,
  PORT_PULL_DOWN
}brsHw_Port_PullSelectOption;

typedef struct
{
  brsHw_Port_OpenDrainOutput  PortOpenDrain;
  brsHw_Port_PullEnableOption PortPullEnable;
  brsHw_Port_PullSelectOption PortPullSelect;
}brsHw_Port_ConfType;

#define BRSHW_PORT_LOGIC_HIGH (uint8)1
#define BRSHW_PORT_LOGIC_LOW  (uint8)0

#if defined (BRSHW_PORT_GROUP_A)
/*******************************************************************************
  PIN configuration for TCM support
********************************************************************************/
#if defined (BRS_ENABLE_TCM_SUPPORT)
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_OUT = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_IN = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_OUT = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_17,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_IN = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_1};

const brsHw_Port_ConfType BRSHW_PORT_CONF_TCM_CLK = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_DISABLED,
  PORT_PULL_DOWN};

const brsHw_Port_ConfType BRSHW_PORT_CONF_TCM_SDA = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_DISABLED,
  PORT_PULL_DOWN};

#  if defined (BRS_ENABLE_TCM_EXT_IRQ)
  #define BRSHW_PORT_TCM_INTA_IN INTC_PSR(134)
  #define BRSHW_PORT_TCM_INTB_IN INTC_PSR(135)
#  endif /*BRS_ENABLE_TCM_EXT_IRQ*/
#endif /*BRS_ENABLE_TCM_SUPPORT*/

/*******************************************************************************
  PIN configuration for alive LED support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_LEDS)
# if !defined (VGEN_ENABLE_DRVPORT)
#  if defined (BRS_EVA_BOARD_VEN001229)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_0};

#  elif defined (BRS_EVA_BOARD_VEN001231) || \
        defined (BRS_EVA_BOARD_HSR_706)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_16,
  BRSHW_PORT_ALT_1};

#  else
  #error "Your chosen EvaBoard ist not yet supported for LED support. Feel free to add your EvaBoard on top, or disable BRS LED support."
#  endif

const brsHw_Port_ConfType BRSHW_PORT_CONF_LED = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_DOWN};

# else
  #error "Configure the valid PortPin for the LED within your DrvPort config and uncomment this error. Or disable BRS_ENABLE_SUPPORT_LEDS."
# endif /*!VGEN_ENABLE_DRVPORT*/
#endif /*BRS_ENABLE_SUPPORT_LEDS*/

/*******************************************************************************
  PIN configuration for toggle WD pin support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CONST
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif

  #error "Please configure here the needed WD-toggle pin and uncomment this error, or disable BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN"*/

const brsHw_Port_PortType BRSHW_PORT_TOGGLE_WD = {
  BRSHW_PORT_PORTGROUP_x,
  BRSHW_PORT_PORTNUMBER_x,
  BRSHW_PORT_ALT_x};

const brsHw_Port_ConfType BRSHW_PORT_CONF_TOGGLE_WD = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_DOWN};

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CONST
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif
#endif /*BRS_ENABLE_SUPPORT_WD_PIN*/

/*******************************************************************************
  PIN configuration for toggle CUSTOM pin support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)

  #error "Please configure here the needed custom toggle pin and uncomment this error, or disable BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN"*/

const brsHw_Port_PortType BRSHW_PORT_TOGGLE_CUSTOM = {
  BRSHW_PORT_PORTGROUP_x,
  BRSHW_PORT_PORTNUMBER_x,
  BRSHW_PORT_ALT_x};

const brsHw_Port_ConfType BRSHW_PORT_CONF_TOGGLE_CUSTOM = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_DOWN};
#endif /*BRS_ENABLE_SUPPORT_CUSTOM_PIN*/

/*******************************************************************************
  ------------------------------------------------------------
  COMMUNICATION DRIVER SPECIFIC PORT SETTINGS
  ------------------------------------------------------------
********************************************************************************/
/*******************************************************************************
  GENERAL COMMUNICATION DRIVER SPECIFIC SETTINGS
********************************************************************************/
#if defined (VGEN_ENABLE_CAN_DRV)
const brsHw_Port_ConfType BRSHW_PORT_CONF_CAN = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_DISABLED,
  PORT_PULL_DOWN};
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
const brsHw_Port_ConfType BRSHW_PORT_CONF_LIN_RX = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_UP};
const brsHw_Port_ConfType BRSHW_PORT_CONF_LIN_TX = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_DISABLED,
  PORT_PULL_DOWN};
#endif /*VGEN_ENABLE_LIN_DRV*/

#if defined (VGEN_ENABLE_DRVI2C)
const brsHw_Port_ConfType BRSHW_PORT_CONF_I2C = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_DOWN};
#endif

/*******************************************************************************
  CAN driver
********************************************************************************/
#if defined (VGEN_ENABLE_CAN_DRV)
# if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_5};
# endif /*kCanPhysToLogChannelIndex_0*/

# if defined (kCanPhysToLogChannelIndex_1)
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_3};
# endif /*kCanPhysToLogChannelIndex_1*/

# if defined (kCanPhysToLogChannelIndex_2)
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_17,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_16,
  BRSHW_PORT_ALT_3};
# endif /*kCanPhysToLogChannelIndex_2*/

# if defined (kCanPhysToLogChannelIndex_3) || defined (kCanPhysToLogChannelIndex_4)
  #error "Port config for these CAN channels not yet implemented!"
# endif
#endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
#if defined (VGEN_ENABLE_LIN_DRV)
# if defined (SIO_ENABLE_SIO_UART0) || defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
const brsHw_Port_PortType BRSHW_PORT_LIN0_TX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_LIN0_RX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_2};
# endif

# if defined (SIO_ENABLE_SIO_UART1) || defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
const brsHw_Port_PortType BRSHW_PORT_LIN1_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_LIN1_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_2};
# endif

# if defined (SIO_ENABLE_SIO_UART2) || defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
const brsHw_Port_PortType BRSHW_PORT_LIN2_TX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_LIN2_RX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_17,
  BRSHW_PORT_ALT_3};
# endif

# if defined (SIO_ENABLE_SIO_UART3) || defined (LIN_ENABLE_HARDWARE_INTERFACE_3) || \
     defined (SIO_ENABLE_SIO_UART4) || defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  #error "Port config for these LIN channels not yet implemented!"
# endif
#endif /*VGEN_ENABLE_LIN_DRV*/

/*******************************************************************************
  I2C Port
********************************************************************************/
#if defined (VGEN_ENABLE_DRVI2C)
const brsHw_Port_PortType BRSHW_PORT_I2C_SDA = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_I2C_SCL = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_3};
#endif /*VGEN_ENABLE_DRVI2C*/

#endif /*BRSHW_PORT_GROUP_A*/

#if defined (BRSHW_PORT_GROUP_B)
/*******************************************************************************
  PIN configuration for TCM support
********************************************************************************/
#if defined (BRS_ENABLE_TCM_SUPPORT)
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_OUT = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_IN = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_OUT = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_17,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_IN = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_1};

const brsHw_Port_ConfType BRSHW_PORT_CONF_TCM_CLK = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_DISABLED,
  PORT_PULL_DOWN};

const brsHw_Port_ConfType BRSHW_PORT_CONF_TCM_SDA = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_DISABLED,
  PORT_PULL_DOWN};

#  if defined (BRS_ENABLE_TCM_EXT_IRQ)
  #define BRSHW_PORT_TCM_INTA_IN INTC_PSR(134)
  #define BRSHW_PORT_TCM_INTB_IN INTC_PSR(135)
#  endif /*BRS_ENABLE_TCM_EXT_IRQ*/
#endif /*BRS_ENABLE_TCM_SUPPORT*/

/*******************************************************************************
  PIN configuration for alive LED support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_LEDS)
# if !defined (VGEN_ENABLE_DRVPORT)
#  if defined (BRS_EVA_BOARD_VEN001231)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_16,
  BRSHW_PORT_ALT_1};

#  elif defined (BRS_EVA_BOARD_CUSTOMER_HARDWARE)
 #error "Please configure here the led pin for your Hardware!"
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_0};
#  else
  #error "Your chosen EvaBoard ist not yet supported for LED support. Feel free to add your EvaBoard on top, or disable BRS LED support."
#  endif

const brsHw_Port_ConfType BRSHW_PORT_CONF_LED = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_DOWN};

# else
  #error "Configure the valid PortPin for the LED within your DrvPort config and uncomment this error. Or disable BRS_ENABLE_SUPPORT_LEDS."
# endif /*!VGEN_ENABLE_DRVPORT*/
#endif /*BRS_ENABLE_SUPPORT_LEDS*/

/*******************************************************************************
  PIN configuration for toggle WD pin support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CONST
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif

  #error "Please configure here the needed WD-toggle pin and uncomment this error, or disable BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN"*/

const brsHw_Port_PortType BRSHW_PORT_TOGGLE_WD = {
  BRSHW_PORT_PORTGROUP_x,
  BRSHW_PORT_PORTNUMBER_x,
  BRSHW_PORT_ALT_x};

const brsHw_Port_ConfType BRSHW_PORT_CONF_TOGGLE_WD = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_DOWN};

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CONST
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif
#endif /*BRS_ENABLE_SUPPORT_WD_PIN*/

/*******************************************************************************
  PIN configuration for toggle CUSTOM pin support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #error "Please configure here the needed custom toggle pin and uncomment this error, or disable BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN"*/

const brsHw_Port_PortType BRSHW_PORT_TOGGLE_CUSTOM = {
  BRSHW_PORT_PORTGROUP_x,
  BRSHW_PORT_PORTNUMBER_x,
  BRSHW_PORT_ALT_x};

const brsHw_Port_ConfType BRSHW_PORT_CONF_TOGGLE_CUSTOM = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_DOWN};
#endif /*BRS_ENABLE_SUPPORT_CUSTOM_PIN*/

/*******************************************************************************
  ------------------------------------------------------------
  COMMUNICATION DRIVER SPECIFIC PORT SETTINGS
  ------------------------------------------------------------
********************************************************************************/
/*******************************************************************************
  GENERAL COMMUNICATION DRIVER SPECIFIC SETTINGS
********************************************************************************/
#if defined (VGEN_ENABLE_CAN_DRV)
const brsHw_Port_ConfType BRSHW_PORT_CONF_CAN = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_DISABLED,
  PORT_PULL_DOWN};
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
const brsHw_Port_ConfType BRSHW_PORT_CONF_LIN_RX = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_UP};
const brsHw_Port_ConfType BRSHW_PORT_CONF_LIN_TX = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_DISABLED,
  PORT_PULL_DOWN};
#endif /*VGEN_ENABLE_LIN_DRV*/

#if defined (VGEN_ENABLE_DRVI2C)
const brsHw_Port_ConfType BRSHW_PORT_CONF_I2C = {
  PORT_OPEN_DRAIN_DISABLED,
  PORT_PULL_ENABLED,
  PORT_PULL_DOWN};
#endif

/*******************************************************************************
  CAN driver
********************************************************************************/
#if defined (VGEN_ENABLE_CAN_DRV)
# if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_5};
# endif /*kCanPhysToLogChannelIndex_0*/

# if defined (kCanPhysToLogChannelIndex_1) || defined (kCanPhysToLogChannelIndex_2) || \
     defined (kCanPhysToLogChannelIndex_3) || defined (kCanPhysToLogChannelIndex_4)
  #error "Port config for these CAN channels not yet implemented!"
# endif
#endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
#if defined (VGEN_ENABLE_LIN_DRV)
# if defined (SIO_ENABLE_SIO_UART0) || defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
const brsHw_Port_PortType BRSHW_PORT_LIN0_TX = {
  BRSHW_PORT_PORTGROUP_X,
  BRSHW_PORT_PORTNUMBER_X,
  BRSHW_PORT_ALT_X};
const brsHw_Port_PortType BRSHW_PORT_LIN0_RX = {
  BRSHW_PORT_PORTGROUP_X,
  BRSHW_PORT_PORTNUMBER_X,
  BRSHW_PORT_ALT_X};
# endif

# if defined (SIO_ENABLE_SIO_UART1) || defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
const brsHw_Port_PortType BRSHW_PORT_LIN1_TX = {
  BRSHW_PORT_PORTGROUP_X,
  BRSHW_PORT_PORTNUMBER_X,
  BRSHW_PORT_ALT_X};
const brsHw_Port_PortType BRSHW_PORT_LIN1_RX = {
  BRSHW_PORT_PORTGROUP_X,
  BRSHW_PORT_PORTNUMBER_X,
  BRSHW_PORT_ALT_X};
# endif

# if defined (SIO_ENABLE_SIO_UART2) || defined (LIN_ENABLE_HARDWARE_INTERFACE_2) || \
     defined (SIO_ENABLE_SIO_UART3) || defined (LIN_ENABLE_HARDWARE_INTERFACE_3) || \
     defined (SIO_ENABLE_SIO_UART4) || defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  #error "Port config for these LIN channels not yet implemented!"
# endif

#endif /*VGEN_ENABLE_LIN_DRV*/

/*******************************************************************************
  I2C Port
********************************************************************************/
#if defined (VGEN_ENABLE_DRVI2C)
# error "I2C pin is not configured!"
const brsHw_Port_PortType BRSHW_PORT_I2C_SDA = {
  BRSHW_PORT_PORTGROUP_X,
  BRSHW_PORT_PORTNUMBER_X,
  BRSHW_PORT_ALT_X};
const brsHw_Port_PortType BRSHW_PORT_I2C_SCL = {
  BRSHW_PORT_PORTGROUP_X,
  BRSHW_PORT_PORTNUMBER_X,
  BRSHW_PORT_ALT_X};
#endif /*VGEN_ENABLE_DRVI2C*/

#endif /*BRSHW_PORT_GROUP_B*/

#endif /*_BRSHW_PORTS_H_*/
