
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
  \file  File:  BrsHw.c
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform NXP S32K1xx
     Template:  This file is reviewed according to zBrs_Template@root[2.02.02]

  \brief Description:  This is the hardware specific code file for Vector Basic Runtime System (BRS).
                       This file supports: see BrsHw_DerivativeList.h

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
  Nguyen Le                     vislnn        Vector Informatik GmbH
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Jens Haerer                   visjhr        Vector Informatik GmbH
  Michael Tiran                 vismin        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
  Stefan Schorer                vissns        Vector Informatik GmbH
  Cyrille  Wamba                viswca        Vector Informatik GmbH
  Sherif Elsabbahy              vissey        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Michael Tiran                 vismin        Vector Informatik GmbH
  Hakan Capci                   vishci        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2015-09-15  vislnn  Initial creation for S32K144
            2015-09-23  visbwa  Review
  01.00.01  2015-10-26  visjhr  Added support for running from flash, fixed BrsHwWatchdogInitPowerOn()
                                (based on Freescale example code)
  01.00.02  2015-11-19  visbwa  Added error-directive within BrsHwConfigureInterruptsAtPowerOn() (enable interrupts)
  01.00.03  2016-05-25  vismin  Added support for BRS_OSC_CLK == 16 MHz, fixed 8 MHz support
            2016-05-30  visbwa  Review, fixed PLL initialization, added BRS_TIMEBASE_CLOCK check
  01.00.04  2016-06-01  visbwa  Moved include of ARMBrsHw.h into BrsHw.h, fixed BrsHwSoftwareResetECU()
  01.01.00  2016-06-02  vismin  Added support for IAR Compiler
  01.01.01  2016-06-20  visbwa  Removed buggy disabling of all interrupts within BrsHwConfigureInterruptsAtPowerOn(),
                                reworked LEAD alive blinking function according to Brs_Template 2.00.01
  01.01.02  2016-06-21  visbwa  Encapsuled BrsHwConfigureInterruptsAtPowerOn() (not necessary with OS)
  01.01.03  2016-06-22  visbwa  Readded BrsHwSoftwareResetECU() (empty) for IAR compiler
  01.01.04  2016-06-29  visbwa  Removed encapsulation of BrsHwConfigureInterruptsAtPowerOn() ->
                                also needs to be called with UseCase OS
  01.02.00  2016-08-18  visbwa  Added BrsHwDummyInterrupts, added DrvLin support
  01.02.01  2016-10-07  vismaa  Added support for S32K142, S32K146, S32K148
  01.02.02. 2016-11-10  vissns  Corrected switching of the LED (it was inverted)
  01.02.03  2016-12-14  vismaa  Added SIO_ENABLE_SIO_UART1 support
  01.03.00  2017-01-30  visjhr  added support for S32V234 and HSR_1387 (ECU with S32V234 and Interface board)
  01.03.01  2017-03-14  vissey  Added LED support for HSR_1387 (S32K144), WCT1013 and WCT1014,
                                replaced derivatives with their groups from DerivativeList header
  01.04.00  2017-02-22  viswca  Introduced TCM support and BrsHw_Ports.h, added GPIOx_PDIR
  01.05.00  2017-04.28  visivg  Implemented BrsHw_Ports.h concept according to Brs_Template 2.01.00
            2017-05-15  visbwa  Review
  01.05.01  2017-07-21  visbwa  Added BRS_OS_USECASE_OSGEN7 to valid configurations within BrsHw.h check
  01.06.00  2017-07-21  vismin  Added access in usermode for memory protection usecase, BRSHW_USERMODE_ACCESS_GROUP_A
  01.07.00  2017-08-11  vismin  Added PllInit code and port initialization for I2c
  01.07.01  2017-10-20  visbwa  Enhanced encapsulation for UseCase OsGen7
  01.07.02  2018-01-31  vismaa  Added support for S32K116 and S32K118
  01.08.00  2018-04-27  visjhr  Added support for GNU Compiler,
                                fixed enabled peripheral interrupts in BrsHwConfigureInterruptsAtPowerOn()
                                (introduced BRSHW_CORTEXM_PLATFORM_SPECIFIC_NVIC_INIT in BrsHw.h)
  01.09.00  2018-06-20  vismaa  Added FBL support, added reset functionality
  01.09.01  2017-07-13  visbwa  Fixed encapsulation of BrsHwEnableIntRouting() and BrsHwConfigureInterruptsAtPowerOn()
  01.09.02  2018-08-03  visbwa  Increased vector table to proper 147 entries for interrupt table group A,
                                added 1st 32 interrupts into BrsHwConfigureInterruptsAtPowerOn() for Cortex-M4
  01.09.03  2018-08-17  vishci  Removed implementation of S32V234 and HSR_1387
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
/*
 * Description: The BrsHw header provides all the necessary interfaces to
 *              the microcontroller hardware features like ports, timers, LEDs, ...
 */
#include "BrsHw.h"

#if defined (VGEN_ENABLE_CAN_DRV)
# if defined (VGEN_ENABLE_IF_ASRIFCAN)
  /*Autosar component*/
  #include "Can.h"
# else
  /*CANbedded component*/
  #include "can_inc.h"
# endif
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
# if defined (VGEN_ENABLE_IF_ASRIFLIN)
  /*Autosar component*/
  #include "Lin.h"
# else
  /*CANbedded component*/
  #include "lin_api.h"
  #include "sio_par.h"
# endif
#endif


#if defined (BRSHW_PORT_GROUP_A) || defined (BRSHW_PORT_GROUP_B)
# if !defined (VGEN_ENABLE_DRVPORT)
  #include "BrsHw_Ports.h"
# endif
#endif

#if defined (VGEN_ENABLE_DRVDIO)
# if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #include "Dio.h"
#  if defined (VGEN_ENABLE_DRVPORT)
  #define BRSHW_PORT_LOGIC_HIGH STD_HIGH
  #define BRSHW_PORT_LOGIC_LOW STD_LOW
#  else
  #error "LED alive mechanism and MCAL does only work proper if DrvPort and DrvDio are used together!"
#  endif
# endif /*BRS_ENABLE_SUPPORT_LEDS||BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN||BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/
#else
# if defined (VGEN_ENABLE_DRVPORT)
#  if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
      defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
      defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #error "LED alive mechanism and MCAL does only work proper if DrvPort and DrvDio are used together!"
#  endif
# endif /*VGEN_ENABLE_DRVPORT*/
#endif /*VGEN_ENABLE_DRVDIO*/

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if (BRSHW_VERSION != 0x0109u)
  #error "Header and source file are inconsistent!"
#endif
#if (BRSHW_BUGFIX_VERSION != 0x03u)
  #error "Different versions of bugfix in Header and Source used!"
#endif

/**********************************************************************************************************************
  CONFIGURATION CHECK
**********************************************************************************************************************/
#if defined (BRS_COMP_GHS) 

#else
  #error "Unknown compiler specified!"
#endif

/**********************************************************************************************************************
  DEFINITION + MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONST VARIABLES
**********************************************************************************************************************/
/*
 * Description: These constants are used to propagate the Versions over
 *              module boundaries.The version numbers are BCD coded. E.g. a sub
 *              version of 23 is coded with 0x23, a bug fix version of 9 is
 *              coded 0x09.
 */
uint8 const kBrsHwMainVersion   = (uint8)(BRSHW_VERSION >> 8);
uint8 const kBrsHwSubVersion    = (uint8)(BRSHW_VERSION & 0xFF);
uint8 const kBrsHwBugfixVersion = (uint8)(BRSHW_BUGFIX_VERSION);

/**********************************************************************************************************************
  LOCAL VARIABLES AND LOCAL HW REGISTERS
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONTROLLER CONFIGURATION REGISTERS
**********************************************************************************************************************/
#if defined (BRSHW_CLOCK_GROUP_A)
  /* Watchdog Register */
  #define WDOG_BASE_ADDR 0x40052000

  #define WDOG_CS        BRSHW_IOS(uint32, WDOG_BASE_ADDR + 0x00)
  #define WDOG_CNT       BRSHW_IOS(uint32, WDOG_BASE_ADDR + 0x04)
  #define WDOG_TOVAL     BRSHW_IOS(uint32, WDOG_BASE_ADDR + 0x08)

  #define WDOG_UNLOCK_KEY     (0xD928C520UL)
  #define WDOG_CLK_FROM_BUS   (0x0UL)
  #define WDOG_CLK_FROM_LPO   (0x1UL)
  #define WDOG_CLK_FROM_SOSC  (0x2UL)
  #define WDOG_CLK_FROM_SIRC  (0x3UL)

  /* System Clock Generator register */
  #define SCG_BASE_ADDR 0x40064000

  #define SCG_RCCR       BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x14)  /* Run Clock Control Register */
  #define SCG_VCCR       BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x18)  /* VLPR Clock Control Register */
  #define SCG_HCCR       BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x1C)  /* HSRUN Clock Control Register */

  #define SCG_SOSCCSR    BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x100) /* System OSC Control Status Register */
  #define SCG_SOSCDIV    BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x104) /* System OSC Divide Register */
  #define SCG_SOSCCFG    BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x108) /* System OSC Configuration Register */

  #define SCG_SPLLCSR    BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x600) /* System PLL Control Status Register */
  #define SCG_SPLLDIV    BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x604) /* System PLL Devide Register */
  #define SCG_SPLLCFG    BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x608) /* System PLL Configuration Register */

  /* PCC register ( Peripheral Clock Control Register ) */
  #define PCC_BASE_ADDR 0x40065000

  #define PCC_FLASH      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x80)

  #define PCC_FLEXCAN0   BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x90)
  #define PCC_FLEXCAN1   BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x94)
  #define PCC_FLEXCAN2   BRSHW_IOS(uint32, PCC_BASE_ADDR + 0xAC)

  #define PCC_LPUART0    BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x1A8)
  #define PCC_LPUART1    BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x1AC)
  #define PCC_LPUART2    BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x1B0)

  #define PCC_PORTA      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x124)
  #define PCC_PORTB      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x128)
  #define PCC_PORTC      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x12C)
  #define PCC_PORTD      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x130)
  #define PCC_PORTE      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x134)

  #define PCC_LPI2C      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x198)

  /* CAN modules */
  #define CAN0_MCR       BRSHW_IOS(uint32,0x40024000)
  #define CAN0_CTRL1     BRSHW_IOS(uint32,0x40024004)
  #define CAN0_CTRL2     BRSHW_IOS(uint32,0x40024034)

  #define CAN1_MCR       BRSHW_IOS(uint32,0x4002B000)
  #define CAN1_CTRL1     BRSHW_IOS(uint32,0x4002B004)
  #define CAN1_CTRL2     BRSHW_IOS(uint32,0x4002B034)
#endif /*BRSHW_CLOCK_GROUP_A*/

#if defined (BRSHW_CLOCK_GROUP_B)
  /* Watchdog Register */
  #define WDOG_BASE_ADDR 0x40052000

  #define WDOG_CS        BRSHW_IOS(uint32,WDOG_BASE_ADDR + 0x00)
  #define WDOG_CNT       BRSHW_IOS(uint32,WDOG_BASE_ADDR + 0x04)
  #define WDOG_TOVAL     BRSHW_IOS(uint32,WDOG_BASE_ADDR + 0x08)

  #define WDOG_UNLOCK_KEY     (0xD928C520UL)
  #define WDOG_CLK_FROM_BUS   (0x0UL)
  #define WDOG_CLK_FROM_LPO   (0x1UL)
  #define WDOG_CLK_FROM_SOSC  (0x2UL)
  #define WDOG_CLK_FROM_SIRC  (0x3UL)

  /* System Clock Generator register */
  #define SCG_BASE_ADDR 0x40064000

  #define SCG_RCCR       BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x14)  /* Run Clock Control Register */
  #define SCG_VCCR       BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x18)  /* VLPR Clock Control Register */

  #define SCG_SOSCCSR    BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x100) /* System OSC Control Status Register */
  #define SCG_SOSCDIV    BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x104) /* System OSC Divide Register */
  #define SCG_SOSCCFG    BRSHW_IOS(uint32,SCG_BASE_ADDR + 0x108) /* System OSC Configuration Register */

  /* PCC register ( Peripheral Clock Control Register ) */
  #define PCC_BASE_ADDR 0x40065000

  #define PCC_FLASH      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x80)

  #define PCC_FLEXCAN0   BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x90)

  #define PCC_LPUART0    BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x1A8)
  #define PCC_LPUART1    BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x1AC)

  #define PCC_PORTA      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x124)
  #define PCC_PORTB      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x128)
  #define PCC_PORTC      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x12C)
  #define PCC_PORTD      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x130)
  #define PCC_PORTE      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x134)

  #define PCC_LPI2C      BRSHW_IOS(uint32, PCC_BASE_ADDR + 0x198)

  /* CAN modules */
  #define CAN0_MCR       BRSHW_IOS(uint32,0x40024000)
  #define CAN0_CTRL1     BRSHW_IOS(uint32,0x40024004)
  #define CAN0_CTRL2     BRSHW_IOS(uint32,0x40024034)

#endif /*BRSHW_CLOCK_GROUP_B*/

#if defined (BRSHW_PORT_GROUP_A) || defined (BRSHW_PORT_GROUP_B)
  /* Pin Control Register n ( PORTx_PCRn) */
  #define PORTA_PCR(n)   BRSHW_IOS(uint32, 0x40049000 + 4*n)
  #define PORTB_PCR(n)   BRSHW_IOS(uint32, 0x4004A000 + 4*n)
  #define PORTC_PCR(n)   BRSHW_IOS(uint32, 0x4004B000 + 4*n)
  #define PORTD_PCR(n)   BRSHW_IOS(uint32, 0x4004C000 + 4*n)
  #define PORTE_PCR(n)   BRSHW_IOS(uint32, 0x4004D000 + 4*n)

  /* Port Data Input/Output Register */
  #define GPIOA_PDOR     BRSHW_IOS(uint32, 0x400FF000)
  #define GPIOB_PDOR     BRSHW_IOS(uint32, 0x400FF040)
  #define GPIOC_PDOR     BRSHW_IOS(uint32, 0x400FF080)
  #define GPIOD_PDOR     BRSHW_IOS(uint32, 0x400FF0C0)
  #define GPIOE_PDOR     BRSHW_IOS(uint32, 0x400FF100)

  #define GPIOA_PSOR     BRSHW_IOS(uint32, 0x400FF004)
  #define GPIOB_PSOR     BRSHW_IOS(uint32, 0x400FF044)
  #define GPIOC_PSOR     BRSHW_IOS(uint32, 0x400FF084)
  #define GPIOD_PSOR     BRSHW_IOS(uint32, 0x400FF0C4)
  #define GPIOE_PSOR     BRSHW_IOS(uint32, 0x400FF104)

  #define GPIOA_PCOR     BRSHW_IOS(uint32, 0x400FF008)
  #define GPIOB_PCOR     BRSHW_IOS(uint32, 0x400FF048)
  #define GPIOC_PCOR     BRSHW_IOS(uint32, 0x400FF088)
  #define GPIOD_PCOR     BRSHW_IOS(uint32, 0x400FF0C8)
  #define GPIOE_PCOR     BRSHW_IOS(uint32, 0x400FF108)

  #define GPIOA_PTOR     BRSHW_IOS(uint32, 0x400FF00C)
  #define GPIOB_PTOR     BRSHW_IOS(uint32, 0x400FF04C)
  #define GPIOC_PTOR     BRSHW_IOS(uint32, 0x400FF08C)
  #define GPIOD_PTOR     BRSHW_IOS(uint32, 0x400FF0CC)
  #define GPIOE_PTOR     BRSHW_IOS(uint32, 0x400FF10C)

  #define GPIOA_PDIR     BRSHW_IOS(uint32, 0x400FF010)
  #define GPIOB_PDIR     BRSHW_IOS(uint32, 0x400FF050)
  #define GPIOC_PDIR     BRSHW_IOS(uint32, 0x400FF090)
  #define GPIOD_PDIR     BRSHW_IOS(uint32, 0x400FF0D0)
  #define GPIOE_PDIR     BRSHW_IOS(uint32, 0x400FF110)

  #define GPIOA_PDDR     BRSHW_IOS(uint32, 0x400FF014)
  #define GPIOB_PDDR     BRSHW_IOS(uint32, 0x400FF054)
  #define GPIOC_PDDR     BRSHW_IOS(uint32, 0x400FF094)
  #define GPIOD_PDDR     BRSHW_IOS(uint32, 0x400FF0D4)
  #define GPIOE_PDDR     BRSHW_IOS(uint32, 0x400FF114)
#endif /*BRSHW_PORT_GROUP_A, BRSHW_PORT_GROUP_B*/

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_A)
  #define NVIC_ICER0     BRSHW_IOS(uint32, 0xE000E180)
  #define NVIC_ICER1     BRSHW_IOS(uint32, 0xE000E184)
  #define NVIC_ICER2     BRSHW_IOS(uint32, 0xE000E188)
  #define NVIC_ICER3     BRSHW_IOS(uint32, 0xE000E18C)
  #define NVIC_ICER4     BRSHW_IOS(uint32, 0xE000E190)
  #define NVIC_ICER5     BRSHW_IOS(uint32, 0xE000E194)
  #define NVIC_ICER6     BRSHW_IOS(uint32, 0xE000E198)
  #define NVIC_ICER7     BRSHW_IOS(uint32, 0xE000E19C)
#endif /*BRSHW_INTERRUPT_TABLE_GROUP_A*/

#if defined (BRSASR_ENABLE_SAFECTXSUPPORT)
# if defined (BRSHW_USERMODE_ACCESS_GROUP_A)
   /***************************************************************/
  /* Platform / Off-platform peripheral access control registers */
  /***************************************************************/
  #define PBRIDGE_BASE 0x40000000

  /* PBRIDGE PACR0 AIPS*/
  #define PACR_REGISTER_AIPS_ADDR       BRSHW_IOS(uint32, PBRIDGE_BASE + 0x20)
  #define PACR_REGISTER_AIPS_VALUE      0x0FFFFFFF
  /* PBRIDGE OPACR23 LPIT */
  #define OPACR_REGISTER_LPIT_ADDR      BRSHW_IOS(uint32, PBRIDGE_BASE + 0x48)
  #define OPACR_REGISTER_LPIT_VALUE     0xFFFFFFF0

  /* *******************CAN****************** */
  /* PBRIDGE OPACR4 - FlexCan0 */
  #define OPACR_REGISTER_CAN0_ADDR      BRSHW_IOS(uint32, PBRIDGE_BASE + 0x40)
  #define OPACR_REGISTER_CAN0_VALUE     0xFFFF0FFF
  /* PBRIDGE OPACR5 - FlexCan1 */
  #define OPACR_REGISTER_CAN1_ADDR      BRSHW_IOS(uint32, PBRIDGE_BASE + 0x40)
  #define OPACR_REGISTER_CAN1_VALUE     0xFFFFF0FF
  /* PBRIDGE OPACR11 - FlexCan2 */
  #define OPACR_REGISTER_CAN2_ADDR      BRSHW_IOS(uint32, PBRIDGE_BASE + 0x44)
  #define OPACR_REGISTER_CAN2_VALUE     0xFFF0FFFF

  /* ******************Ethernet**************** */
  /* PBRIDGE OPACR89 - ENET */
  #define OPACR_REGISTER_ENET_ADDR      BRSHW_IOS(uint32, PBRIDGE_BASE + 0x6C)
  #define OPACR_REGISTER_ENET_VALUE     0xF0FFFFFF

  /* *******************SPI****************** */
  /* PBRIDGE OPACR12 - SPI0 */
  #define OPACR_REGISTER_SPI0_ADDR      BRSHW_IOS(uint32, PBRIDGE_BASE + 0x44)
  #define OPACR_REGISTER_SPI0_VALUE     0xFFFF0FFF
  /* PBRIDGE OPACR13 - SPI1 */
  #define OPACR_REGISTER_SPI1_ADDR      BRSHW_IOS(uint32, PBRIDGE_BASE + 0x44)
  #define OPACR_REGISTER_SPI1_VALUE     0xFFFFF0FF
  /* PBRIDGE OPACR14 - SPI2 */
  #define OPACR_REGISTER_SPI2_ADDR      BRSHW_IOS(uint32, PBRIDGE_BASE + 0x44)
  #define OPACR_REGISTER_SPI2_VALUE     0xFFFFFF0F

  /* *******************WDG****************** */
  /* PBRIDGE PACR50 - WDOG (internal SW Wdg)*/
  #define OPACR_REGISTER_WDOG_ADDR      BRSHW_IOS(uint32, PBRIDGE_BASE + 0x58)
  #define OPACR_REGISTER_WDOG_VALUE     0xFF0FFFFF

  /* *******************FLASH****************** */
  /* PBRIDGE0 OPACR0 - Flash */
  #define OPACR_REGISTER_FLASH_ADDR    BRSHW_IOS(uint32, PBRIDGE_BASE + 0x40)
  #define OPACR_REGISTER_FLASH_VALUE   0x0FFFFFFF
# endif /*BRSHW_USERMODE_ACCESS_GROUP_A*/
#endif /*BRSASR_ENABLE_SAFECTXSUPPORT*/

/*System Control Space*/
#define SCS_BASE    0xE000E000
#define SCS_AIRCR   BRSHW_IOS(uint32, SCS_BASE + 0x0D0Cu) /*Application Interrupt And Reset Control Register*/
#define VECTKEY     0x05FA0000u

/**********************************************************************************************************************
  LOCAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL CONST VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  PROTOTYPES OF LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  FUNCTION DEFINITIONS
**********************************************************************************************************************/

/*****************************************************************************/
/**
 * @brief      This function has to be used to initialize the Watchdog.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain or EcuM at power on initialization
 */
/*****************************************************************************/
void BrsHwWatchdogInitPowerOn(void)
{
#if !defined (VGEN_ENABLE_DRVWD)

# if defined (BRSHW_CLOCK_GROUP_A) || defined (BRSHW_CLOCK_GROUP_B)
  /*inital write of wdog config register; clock select from lpo, update enable, watchdog enable*/
  WDOG_CNT = (uint32)WDOG_UNLOCK_KEY;
  //WDOG_CS =  (uint32) ((1 << 13)|(WDOG_CLK_FROM_LPO << 8)|(0 << 7) | (1 << 5));
  WDOG_CS &= 0xFF7F;
  WDOG_TOVAL= 0xFFFF;
  while((WDOG_CS&0x0800)){}
  while(!(WDOG_CS&0x0400)){}
  /*write of the wdog unlock key to cnt register, must be done in order to allow any modifications*/
  //WDOG_TOVAL = (uint32)0xFFFF;
# endif /*BRSHW_CLOCK_GROUP_A||BRSHW_CLOCK_GROUP_B*/
#endif /*!VGEN_ENABLE_DRVWD*/
}

/*****************************************************************************/
/**
 * @brief      This function has to be used to initialize the PLL.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain or EcuM at power on initialization
 */
/*****************************************************************************/
void BrsHwPllInitPowerOn(void)
{
#if !defined (VGEN_ENABLE_DRVMCU)

# if defined (BRSHW_PLL_GROUP_A)
  /* BRS_DERIVATIVE_S32K144 */
  /* Clock Source : */
  /*          + FIRC     */
  /*          + SIRC     */
  /*          + SOSC     */
  /* ---               */
  /* FIRC/SOSC --> PLL --> SCG (CORE/Platform/Bus) */
#  if (BRS_TIMEBASE_CLOCK != 80)
  #error "Only 80MHz for Timebase clock are actually supported. Please choose correct value within Makefile.config."
#  endif

  /* Configure and enable System OSC */
  SCG_SOSCCSR = (uint32)0x00;   /* disable system OSC */
  SCG_SOSCCFG = (uint32)0x34;   /* configure system OSC range : 8 Mhz to 32 Mhz (RANGE=b11); OSC selected (EREFS=1) */
  SCG_SOSCDIV = (uint32)0x101;  /* SOSCDIV1 = 1; SOSCDIV2 = 1 */
  SCG_SOSCCSR = (uint32)0x01;   /* enable System OSC */

  while (!(SCG_SOSCCSR & 0x01000000UL)){}; /* wait until System OSC is valid */

  /* Configure and enable PLL */
  /* PLLCLK = 80MHz */
  SCG_SPLLCSR = (uint32)0x00;   /* disable PLL */
  while (SCG_SPLLCSR & 0x00800000UL){}; /* wait until PLL Lock is released */

#  if (BRS_OSC_CLK == 8)
  SCG_SPLLCFG = (uint32)0x00040000;  /* PLLCLK = 8MHz(OSC) x 20(MULT=b00100) / 1(PREDIV=0) / 2(fix) = 80MHz */
#  elif (BRS_OSC_CLK == 16)
  SCG_SPLLCFG = (uint32)0x00040100;  /* PLLCLK = 16MHz(OSC) x 20(MULT=b00100) / 2(PREDIV=1) / 2(fix) = 80MHz */
#  else
   #error "The selected clock frequency of main oscillator is not supported (supported: 8 and 16 MHz)."
#  endif
  SCG_SPLLDIV = (uint32)0x101;  /* SPLLDIV1 = 1; SPLLDIV2 = 1 */
  SCG_SPLLCSR = (uint32)0x01;   /* enable PLL */

  while (!(SCG_SPLLCSR & 0x01000000UL)){}; /* wait until PLL clock is valid */

  /* RUN MODE :                      */
  /* System Clock Source (SCS) = PLL */
  /* CORE_CLK  = PLLCLK / 1 = 80MHz  */
  /* SYS_CLK   = PLLCLK / 1 = 80MHz  */
  /* BUS_CLK   = PLLCLK / 2 = 40MHz  */
  /* FLASH_CLK = PLLCLK / 4 = 20MHz  */
  SCG_RCCR = (uint32)((6 << 24)|(0 << 16)|(0 << 12)|(1 << 4)|(3 << 0));

  /* Enable clock to Peripherals */
#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
  PCC_FLEXCAN0 |= (1 << 30); /* clock gate for CAN0 */
#   endif
#   if defined (kCanPhysToLogChannelIndex_1)
  PCC_FLEXCAN1 |= (1 << 30); /* clock gate for CAN1 */
#   endif
#   if defined (kCanPhysToLogChannelIndex_2)
  PCC_FLEXCAN2 |= (1 << 30); /* clock gate for CAN2 */
#   endif
#  endif

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (SIO_ENABLE_SIO_UART0) || defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  PCC_LPUART0 = 0x81000000;
  PCC_LPUART0 |= (1 << 30); /* clock gate for LIN0 */
#   endif
#   if defined (SIO_ENABLE_SIO_UART1) || defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  PCC_LPUART1 = 0x81000000;
  PCC_LPUART1 |= (1 << 30); /* clock gate for LIN1 */
#   endif
#   if defined (SIO_ENABLE_SIO_UART2) || defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  PCC_LPUART2 = 0x81000000;
  PCC_LPUART2 |= (1 << 30); /* clock gate for LIN2 */
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/

  PCC_PORTA |= (1 << 30); /* clock gate for PORTA */
  PCC_PORTB |= (1 << 30); /* clock gate for PORTB */
  PCC_PORTC |= (1 << 30); /* clock gate for PORTC */
  PCC_PORTD |= (1 << 30); /* clock gate for PORTD */
  PCC_PORTE |= (1 << 30); /* clock gate for PORTE */

#  if defined (VGEN_ENABLE_DRVI2C)
  PCC_LPI2C = 0x86000000;
  PCC_LPI2C |= (1 << 30); /* clock gate for PPC_LPI2C */
#  endif /*VGEN_ENABLE_DRVI2C*/

# endif /*BRSHW_PLL_GROUP_A*/

# if defined (BRSHW_PLL_GROUP_B)
  /* BRS_DERIVATIVE_S32K11X */
  /* Clock Source :         */
  /*          + FIRC        */
  /*          + SIRC        */
  /*          + SOSC        */
  /*FIRC/SOSC --> SCG (CORE/Platform/Bus) */
#  if (BRS_OSC_CLK != BRS_TIMEBASE_CLOCK)
  #error "It is only possible to set BRS_TIMEBASE_CLOCK equal to MAIN_OSC_CLK becaus no PLL is available for this derivative!"
#  endif

  /* Configure and enable System OSC */
  SCG_SOSCCSR = (uint32)0x00;   /* disable system OSC */
  SCG_SOSCCFG = (uint32)0x34;   /* configure system OSC range : 8 Mhz to 32 Mhz (RANGE=b11); OSC selected (EREFS=1) */ /*vismaa: check clock ! */
  SCG_SOSCDIV = (uint32)0x101;  /* SOSCDIV1 = 1; SOSCDIV2 = 1 */
  SCG_SOSCCSR = (uint32)0x01;   /* enable System OSC */

  while (!(SCG_SOSCCSR & 0x01000000UL)){}; /* wait until System OSC is valid */

  /* RUN MODE :                      */
  /* System Clock Source (SCS) = System Oscillator  */
  /* CORE_CLK  = MAIN_OSC_CLK / 1 = MAIN_OSC_CLK    */
  /* SYS_CLK   = MAIN_OSC_CLK / 1 = MAIN_OSC_CLK    */
  /* BUS_CLK   = MAIN_OSC_CLK / 1 = MAIN_OSC_CLK    */
  /* FLASH_CLK = MAIN_OSC_CLK / 2 = X               */
  SCG_RCCR = (uint32)((1 << 24)|(0 << 16)|(0 << 12)|(0 << 4)|(1 << 0)); /* select System OSC, core clock divider = 1, bus clock divider = 1, flash clock divider =2 */

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
  PCC_FLEXCAN0 |= (1 << 30); /* clock gate for CAN0 */
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (SIO_ENABLE_SIO_UART0) || defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  PCC_LPUART0 = 0x81000000; /* selected SOSCDIV2_CLK */
  PCC_LPUART0 |= (1 << 30); /* clock gate for LIN0 */
#   endif
#   if defined (SIO_ENABLE_SIO_UART1) || defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  PCC_LPUART1 = 0x81000000; /* selected SOSCDIV2_CLK */
  PCC_LPUART1 |= (1 << 30); /* clock gate for LIN1 */
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/

  PCC_PORTA |= (1 << 30); /* clock gate for PORTA */
  PCC_PORTB |= (1 << 30); /* clock gate for PORTB */
  PCC_PORTC |= (1 << 30); /* clock gate for PORTC */
  PCC_PORTD |= (1 << 30); /* clock gate for PORTD */
  PCC_PORTE |= (1 << 30); /* clock gate for PORTE */
  
#  if defined (VGEN_ENABLE_DRVI2C)
  PCC_LPI2C = 0x86000000;
  PCC_LPI2C |= (1 << 30); /* clock gate for PPC_LPI2C */
#  endif /*VGEN_ENABLE_DRVI2C*/
# endif /*BRSHW_PLL_GROUP_B*/
#endif /*VGEN_ENABLE_DRVMCU*/
}

#if defined (BRSHW_PORT_GROUP_A) || defined (BRSHW_PORT_GROUP_B)
# if !defined (VGEN_ENABLE_DRVPORT)
/*******************************************************************************
  Port Pin initialization helper functions for usage of BrsHw_Ports.h
********************************************************************************/

/*****************************************************************************/
/**
 * @brief      This function sets port alternative mode registers.
 * @pre        Port pin configuartions available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwInitPortInput() and
 *             BrsHwInitPortOutput() locally.
 */
/*****************************************************************************/
void BrsHwInitPortAlternative(brsHw_Port_PortType p)
{
/* Pin 10-8 Pin Mux Control
    000 Pin disabled (Alternative 0) (analog).
    001 Alternative 1 (GPIO).
    010 Alternative 2 (chip-specific).
    011 Alternative 3 (chip-specific).
    100 Alternative 4 (chip-specific).
    101 Alternative 5 (chip-specific).
    It can be extended up to 7. Configure also in BrsHw_Ports.h*/

  switch(p.portGroup)
  {
    case (BRSHW_PORT_PORTGROUP_A):
      PORTA_PCR(p.portNumber) &= (0xFFFFF8FF);
      PORTA_PCR(p.portNumber) |= (p.portAlternative << 8);
      break;

    case (BRSHW_PORT_PORTGROUP_B):
      PORTB_PCR(p.portNumber) &= (0xFFFFF8FF);
      PORTB_PCR(p.portNumber) |= (p.portAlternative << 8);
      break;

    case (BRSHW_PORT_PORTGROUP_C):
      PORTC_PCR(p.portNumber) &= (0xFFFFF8FF);
      PORTC_PCR(p.portNumber) |= (p.portAlternative << 8);
      break;

    case (BRSHW_PORT_PORTGROUP_D):
      PORTD_PCR(p.portNumber) &= (0xFFFFF8FF);
      PORTD_PCR(p.portNumber) |= (p.portAlternative << 8);
      break;

    case (BRSHW_PORT_PORTGROUP_E):
      PORTE_PCR(p.portNumber) &= (0xFFFFF8FF);
      PORTE_PCR(p.portNumber) |= (p.portAlternative << 8);
      break;
  }
}

/*****************************************************************************/
/**
 * @brief      This function configures the port pin configuration registers
 *             (pull-up, open drain)
 * @pre        Port pin configuartions available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized,
 *             n - brsHw_Port_ConfType, for port pin configuration
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() locally.
 */
/*****************************************************************************/
void BrsHwInitPortConfig(brsHw_Port_PortType p, brsHw_Port_ConfType n)
{
  if(n.PortOpenDrain == PORT_OPEN_DRAIN_ENABLED)
  {
    switch(p.portGroup)
    {
      case (BRSHW_PORT_PORTGROUP_A):
        PORTA_PCR(p.portNumber) |= (1 << 5);
        break;

      case (BRSHW_PORT_PORTGROUP_B):
        PORTB_PCR(p.portNumber) |= (1 << 5);
        break;

      case (BRSHW_PORT_PORTGROUP_C):
        PORTC_PCR(p.portNumber)|= (1 << 5);
        break;

      case (BRSHW_PORT_PORTGROUP_D):
        PORTD_PCR(p.portNumber)|= (1 << 5);
        break;

      case (BRSHW_PORT_PORTGROUP_E):
        PORTE_PCR(p.portNumber)|= (1 << 5);
        break;
    }
  }
  else
  {
    switch(p.portGroup)
    {
      case (BRSHW_PORT_PORTGROUP_A):
        PORTA_PCR(p.portNumber) &= ~(1 << 5);
        break;

      case (BRSHW_PORT_PORTGROUP_B):
        PORTB_PCR(p.portNumber) &= ~(1 << 5);
        break;

      case (BRSHW_PORT_PORTGROUP_C):
        PORTC_PCR(p.portNumber) &= ~(1 << 5);
        break;

      case (BRSHW_PORT_PORTGROUP_D):
        PORTD_PCR(p.portNumber) &= ~(1 << 5);
        break;

      case (BRSHW_PORT_PORTGROUP_E):
        PORTE_PCR(p.portNumber) &= ~(1 << 5);
        break;
    }
  }

  if(n.PortPullSelect == PORT_PULL_UP)
  {
    switch(p.portGroup)
    {
      case (BRSHW_PORT_PORTGROUP_A):
        PORTA_PCR(p.portNumber) |= (1 << 0);
        break;

      case (BRSHW_PORT_PORTGROUP_B):
        PORTB_PCR(p.portNumber) |= (1 << 0);
        break;

      case (BRSHW_PORT_PORTGROUP_C):
        PORTC_PCR(p.portNumber)|= (1 << 0);
        break;

      case (BRSHW_PORT_PORTGROUP_D):
        PORTD_PCR(p.portNumber)|= (1 << 0);
        break;

      case (BRSHW_PORT_PORTGROUP_E):
        PORTE_PCR(p.portNumber)|= (1 << 0);
        break;
    }
  }
  else
  {
    switch(p.portGroup)
    {
      case (BRSHW_PORT_PORTGROUP_A):
        PORTA_PCR(p.portNumber) &= ~(1 << 0);
        break;

      case (BRSHW_PORT_PORTGROUP_B):
        PORTB_PCR(p.portNumber) &= ~(1 << 0);
        break;

      case (BRSHW_PORT_PORTGROUP_C):
        PORTC_PCR(p.portNumber) &= ~(1 << 0);
        break;

      case (BRSHW_PORT_PORTGROUP_D):
        PORTD_PCR(p.portNumber) &= ~(1 << 0);
        break;

      case (BRSHW_PORT_PORTGROUP_E):
        PORTE_PCR(p.portNumber) &= ~(1 << 0);
        break;
    }
  }

  if(n.PortPullEnable == PORT_PULL_ENABLED)
  {
    switch(p.portGroup)
    {
      case (BRSHW_PORT_PORTGROUP_A):
        PORTA_PCR(p.portNumber) |= (1 << 1);
        break;

      case (BRSHW_PORT_PORTGROUP_B):
        PORTB_PCR(p.portNumber) |= (1 << 1);
        break;

      case (BRSHW_PORT_PORTGROUP_C):
        PORTC_PCR(p.portNumber)|= (1 << 1);
        break;

      case (BRSHW_PORT_PORTGROUP_D):
        PORTD_PCR(p.portNumber)|= (1 << 1);
        break;

      case (BRSHW_PORT_PORTGROUP_E):
        PORTE_PCR(p.portNumber)|= (1 << 1);
        break;
    }
  }
  else
  {
    switch(p.portGroup)
    {
      case (BRSHW_PORT_PORTGROUP_A):
        PORTA_PCR(p.portNumber) &= ~(1 << 1);
        break;

      case (BRSHW_PORT_PORTGROUP_B):
        PORTB_PCR(p.portNumber) &= ~(1 << 1);
        break;

      case (BRSHW_PORT_PORTGROUP_C):
        PORTC_PCR(p.portNumber) &= ~(1 << 1);
        break;

      case (BRSHW_PORT_PORTGROUP_D):
        PORTD_PCR(p.portNumber) &= ~(1 << 1);
        break;

      case (BRSHW_PORT_PORTGROUP_E):
        PORTE_PCR(p.portNumber) &= ~(1 << 1);
        break;
    }
  }
}

/*****************************************************************************/
/**
 * @brief      This function configures a port pin as input pin.
 * @pre        Port pin configuartions available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             BrsHwEvaBoardInitPowerOn() locally.
 */
/*****************************************************************************/
void BrsHwInitPortInput(brsHw_Port_PortType p)
{
  /* Enable input buffer */
  switch(p.portGroup)
  {
    case (BRSHW_PORT_PORTGROUP_A):
      GPIOA_PDDR &= ~(1 << p.portNumber);
      break;

    case (BRSHW_PORT_PORTGROUP_B):
      GPIOB_PDDR &= ~(1 << p.portNumber);
      break;

    case (BRSHW_PORT_PORTGROUP_C):
      GPIOC_PDDR &= ~(1 << p.portNumber);
      break;

    case (BRSHW_PORT_PORTGROUP_D):
      GPIOD_PDDR &= ~(1 << p.portNumber);
      break;

    case (BRSHW_PORT_PORTGROUP_E):
      GPIOE_PDDR &= ~(1 << p.portNumber);
      break;
  }

  BrsHwInitPortAlternative(p);
}

/*****************************************************************************/
/**
 * @brief      This function configures a port pin as output pin.
 * @pre        Port pin configuartions available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 *             n - brsHw_Port_ConfType, for port pin configuration
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             BrsHwEvaBoardInitPowerOn() locally.
 */
/*****************************************************************************/
void BrsHwInitPortOutput(brsHw_Port_PortType p, brsHw_Port_ConfType n)
{
  switch(p.portGroup)
  {
    case (BRSHW_PORT_PORTGROUP_A):
      GPIOA_PDDR |= (1 << p.portNumber);
      break;

    case (BRSHW_PORT_PORTGROUP_B):
      GPIOB_PDDR |= (1 << p.portNumber);
      break;

    case (BRSHW_PORT_PORTGROUP_C):
      GPIOC_PDDR |= (1 << p.portNumber);
      break;

    case (BRSHW_PORT_PORTGROUP_D):
      GPIOD_PDDR |= (1 << p.portNumber);
      break;

    case (BRSHW_PORT_PORTGROUP_E):
      GPIOE_PDDR |= (1 << p.portNumber);
      break;
  }

  BrsHwInitPortAlternative(p);
  BrsHwInitPortConfig(p,n);
}


/*****************************************************************************/
/**
 * @brief      This function sets the output level of a port pin.
 * @pre        Port pin configuartions available within BrsHw_Ports.h,
 *             no DrvPort used for port pin initialization and
 *             transferred port pin has to be initialized as output pin with
 *             GPIO functionality.
 * @param[in]  p     - brsHw_Port_PortType, to be set,
 *             Level - level, port pin has to be set to
 *                     (BRSHW_PORT_LOGIC_LOW or BRSHW_PORT_LOGIC_HIGH).
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn(),
 *             BrsHwEvaBoardInitPowerOn(), BrsHw_WriteDio_TCM_SDA_OUT() and
 *             BrsHw_WriteDio_TCM_CLK_OUT() locally.
 */
/*****************************************************************************/
void BrsHwPort_SetLevel(brsHw_Port_PortType p, uint8 Level)
{
  switch(p.portGroup)
  {
    case (BRSHW_PORT_PORTGROUP_A):
      if (Level != BRSHW_PORT_LOGIC_LOW)
      {
        GPIOA_PDOR |= (1 << p.portNumber); /* set port-pin-level to high */
      }
      else
      {
        GPIOA_PDOR &= ~(1 << p.portNumber); /* set port-pin-level to low */
      }
      break;

    case (BRSHW_PORT_PORTGROUP_B):
      if (Level != BRSHW_PORT_LOGIC_LOW)
      {
        GPIOB_PDOR |= (1 << p.portNumber); /* set port-pin-level to high */
      }
      else
      {
        GPIOB_PDOR &= ~(1 << p.portNumber); /* set port-pin-level to low */
      }
      break;

    case (BRSHW_PORT_PORTGROUP_C):
      if (Level != BRSHW_PORT_LOGIC_LOW)
      {
        GPIOC_PDOR |= (1 << p.portNumber); /* set port-pin-level to high */
      }
      else
      {
        GPIOC_PDOR &= ~(1 << p.portNumber); /* set port-pin-level to low */
      }
      break;

    case (BRSHW_PORT_PORTGROUP_D):
      if (Level != BRSHW_PORT_LOGIC_LOW)
      {
        GPIOD_PDOR |= (1 << p.portNumber); /* set port-pin-level to high */
      }
      else
      {
        GPIOD_PDOR &= ~(1 << p.portNumber); /* set port-pin-level to low */
      }
      break;

    case (BRSHW_PORT_PORTGROUP_E):
      if (Level != BRSHW_PORT_LOGIC_LOW)
      {
        GPIOE_PDOR |= (1 << p.portNumber); /* set port-pin-level to high */
      }
      else
      {
        GPIOE_PDOR &= ~(1 << p.portNumber); /* set port-pin-level to low */
      }
      break;
  }
}

/*****************************************************************************/
/**
 * @brief      This function reads the input level of a port pin.
 * @pre        Port pin configuartions available within BrsHw_Ports.h,
 *             no DrvPort used for port pin initialization and
 *             transferred port pin has to be initialized as input pin with
 *             GPIO functionality.
 * @param[in]  p - brsHw_Port_PortType, to be read.
 * @param[out] -
 * @return     Level, read from port pin
 *             (BRSHW_PORT_LOGIC_LOW or BRSHW_PORT_LOGIC_HIGH).
 * @context    Function is called from BrsHw_WriteDio_TCM_SDA_OUT() and
 *             BrsHw_WriteDio_TCM_CLK_OUT() locally.
 */
/*****************************************************************************/
uint8 BrsHwPort_GetLevel(brsHw_Port_PortType p)
{
  uint32 temp;

  switch(p.portGroup)
  {
    case (BRSHW_PORT_PORTGROUP_A):
      temp = GPIOA_PDIR;
      temp &= (1 << p.portNumber);

      if(temp != 0x00000000)
      {
        return BRSHW_PORT_LOGIC_HIGH;
      }
      else
      {
        return BRSHW_PORT_LOGIC_LOW;
      }

    case (BRSHW_PORT_PORTGROUP_B):
      temp = GPIOB_PDIR;
      temp &= (1 << p.portNumber);

      if(temp != 0x00000000)
      {
        return BRSHW_PORT_LOGIC_HIGH;
      }
      else
      {
        return BRSHW_PORT_LOGIC_LOW;
      }

    case (BRSHW_PORT_PORTGROUP_C):
      temp = GPIOC_PDIR;
      temp &= (1 << p.portNumber);

      if(temp != 0x00000000)
      {
        return BRSHW_PORT_LOGIC_HIGH;
      }
      else
      {
        return BRSHW_PORT_LOGIC_LOW;
      }

    case (BRSHW_PORT_PORTGROUP_D):
      temp = GPIOD_PDIR;
      temp &= (1 << p.portNumber);

      if(temp != 0x00000000)
      {
        return BRSHW_PORT_LOGIC_HIGH;
      }
      else
      {
        return BRSHW_PORT_LOGIC_LOW;
      }

    case (BRSHW_PORT_PORTGROUP_E):
      temp = GPIOE_PDIR;
      temp &= (1 << p.portNumber);

      if(temp != 0x00000000)
      {
        return BRSHW_PORT_LOGIC_HIGH;
      }
      else
      {
        return BRSHW_PORT_LOGIC_LOW;
      }
  }

  /* this line should never be achieved. This is to prevent compiler warnings */
  return BRSHW_PORT_LOGIC_LOW;
}

#  if defined (BRS_ENABLE_TCM_SUPPORT)
/*******************************************************************************
  TCM Write Functions
********************************************************************************/
void BrsHw_WriteDio_TCM_SDA_OUT(uint8 Level)
{
  BrsHwPort_SetLevel(BRSHW_PORT_TCM_SDA_OUT, Level);
}

void BrsHw_WriteDio_TCM_CLK_OUT(uint8 Level)
{
  BrsHwPort_SetLevel(BRSHW_PORT_TCM_CLK_OUT, Level);
}

/*******************************************************************************
  TCM Read Functions
********************************************************************************/
uint8 BrsHw_ReadDio_TCM_SDA_IN(void)
{
  return BrsHwPort_GetLevel(BRSHW_PORT_TCM_SDA_IN);
}

uint8 BrsHw_ReadDio_TCM_CLK_IN(void)
{
  return BrsHwPort_GetLevel(BRSHW_PORT_TCM_CLK_IN);
}
#  endif /*BRS_ENABLE_TCM_SUPPORT*/
# endif /*!VGEN_ENABLE_DRVPORT*/
#endif /*BRSHW_PORT_GROUP_A, BRSHW_PORT_GROUP_B*/

/*****************************************************************************/
/**
 * @brief      This function has to be used to initialize the used ports.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain or EcuM at power on initialization
 */
/*****************************************************************************/
void BrsHwPortInitPowerOn(void)
{
#if defined (VGEN_ENABLE_DRVPORT)
# if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #error "Configure the valid toggle pins within your DrvPort config. Or disable the depending BRS mechanism."*/
# endif

#else
# if defined (BRS_ENABLE_SUPPORT_LEDS)
  BrsHwInitPortOutput(BRSHW_PORT_LED, BRSHW_PORT_CONF_LED);

  /* Set LED on EVB demo board to show the system is alive */
  BrsHwTogglePin(BRSHW_TOGGLEPIN_LED);
# endif /*BRS_ENABLE_SUPPORT_LEDS*/

# if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_WD, BRSHW_PORT_CONF_TOGGLE_WD);
# endif

# if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_CUSTOM, BRSHW_PORT_CONF_TOGGLE_CUSTOM);
# endif

# if defined (BRS_ENABLE_TCM_SUPPORT)
  BrsHwInitPortOutput(BRSHW_PORT_TCM_CLK_OUT, BRSHW_PORT_CONF_TCM_CLK);
  BrsHwInitPortOutput(BRSHW_PORT_TCM_SDA_OUT, BRSHW_PORT_CONF_TCM_SDA);
  BrsHwInitPortInput(BRSHW_PORT_TCM_SDA_IN);
  BrsHwInitPortInput(BRSHW_PORT_TCM_CLK_IN);
# endif /*BRS_ENABLE_TCM_SUPPORT*/

# if defined (BRSHW_PORT_GROUP_A) || defined (BRSHW_PORT_GROUP_B)
/*******************************************************************************
  CAN driver
********************************************************************************/
#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
  BrsHwInitPortInput(BRSHW_PORT_CAN0_RX);
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TX, BRSHW_PORT_CONF_CAN);
#   endif

#   if defined (kCanPhysToLogChannelIndex_1)
  BrsHwInitPortInput(BRSHW_PORT_CAN1_RX);
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TX, BRSHW_PORT_CONF_CAN);
#   endif

#   if defined (kCanPhysToLogChannelIndex_2)
  BrsHwInitPortInput(BRSHW_PORT_CAN2_RX);
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TX, BRSHW_PORT_CONF_CAN);
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (SIO_ENABLE_SIO_UART0) || defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  BrsHwInitPortInput(BRSHW_PORT_LIN0_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN0_RX, BRSHW_PORT_CONF_LIN_RX);
  BrsHwInitPortOutput(BRSHW_PORT_LIN0_TX, BRSHW_PORT_CONF_LIN_TX);
#   endif

#   if defined (SIO_ENABLE_SIO_UART1) || defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  BrsHwInitPortInput(BRSHW_PORT_LIN1_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN1_RX, BRSHW_PORT_CONF_LIN_RX);
  BrsHwInitPortOutput(BRSHW_PORT_LIN1_TX, BRSHW_PORT_CONF_LIN_TX);
#   endif

#   if defined (SIO_ENABLE_SIO_UART2) || defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  BrsHwInitPortInput(BRSHW_PORT_LIN2_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_RX, BRSHW_PORT_CONF_LIN_RX);
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_TX, BRSHW_PORT_CONF_LIN_TX);
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/

/*******************************************************************************
  I2C driver
********************************************************************************/
#  if defined (VGEN_ENABLE_DRVI2C)
  BrsHwInitPortInput(BRSHW_PORT_I2C_SDA);
  BrsHwInitPortOutput(BRSHW_PORT_I2C_SCL, BRSHW_PORT_CONF_I2C);
  BrsHwInitPortOutput(BRSHW_PORT_I2C_SDA, BRSHW_PORT_CONF_I2C);
#  endif /*VGEN_ENABLE_DRVI2C*/
# endif /*BRSHW_PORT_GROUP_A, BRSHW_PORT_GROUP_B*/

#endif /*!VGEN_ENABLE_DRVPORT*/
}

#if !defined (BRS_OS_USECASE_OSGEN7) 
/*****************************************************************************/
/**
 * @brief      This function has to be used to initialize the used interrupts.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwEnableInterruptAtPowerOn or EcuM-DriverInitThree
 */
/*****************************************************************************/
void BrsHwConfigureInterruptsAtPowerOn(void)
{
# if defined (BRS_CPU_CORE_CORTEX_M0PLUS)
  /* Cortex-M0 only supports 32 Peripheral-Interrupts */
  NVIC_ISER_ADDR(0) = 0xFFFFFFBF;  /* Enable 1nd 32 interrupts - but NOT int #6 -> RTC ALARM */

# else
  NVIC_ISER_ADDR(0) = 0xFFFFFFFF;  /* Enable 1st 32 interrupts */
  NVIC_ISER_ADDR(1) = 0xFFFFBFFF;  /* Enable 2nd 32 interrupts - but NOT int #46 -> RTC ALARM */
  NVIC_ISER_ADDR(2) = 0xFFFFFFFF;  /* Enable 3rd 32 interrupts */
  NVIC_ISER_ADDR(3) = 0xFFFFFFFF;  /* Enable 4th 32 interrupts */
  NVIC_ISER_ADDR(4) = 0xFFFFFFFF;  /* Enable 5th 32 interrupts */
  NVIC_ISER_ADDR(5) = 0xFFFFFFFF;  /* Enable 6th 32 interrupts */
  NVIC_ISER_ADDR(6) = 0xFFFFFFFF;  /* Enable 7th 32 interrupts */
  NVIC_ISER_ADDR(7) = 0xFFFFFFFF;  /* Enable 8th 32 interrupts */
# endif

#if defined (BRS_VECTOR_TABLE_LOCATION_RAM)
  BrsHwVectorTableMovement();
#endif
}
#endif /*!BRS_OS_USECASE_OSGEN7 && !BRS_ENABLE_FBL_SUPPORT*/

/*****************************************************************************/
/**
 * @brief      restart ECU (issue a software reset or jump to startup code)
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from e.g. ECU state handling
 */
/*****************************************************************************/
void BrsHwSoftwareResetECU(void)
{
  BrsHwDisableInterrupt();

  SCS_AIRCR = (uint32)(VECTKEY | 0x04u);    /*request a reset via the bit SYSRESETREQ*/ 

  while (1)
  {
    /* if no reset is triggered */
  }
}

#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
/*****************************************************************************/
/**
 * @brief      This API is used to toggle a PortPin.
 *             Per default, the following parameters are available:
 *               BRSHW_TOGGLEPIN_LED
 *               BRSHW_TOGGLEPIN_WD
 *               BRSHW_TOGGLEPIN_CUSTOM
 *             Depending pins have to be configured within BrsHw_Ports.h.
 * @pre        -
 * @param[in]  Pin has to configure the depending pin to be toggled
 * @param[out] -
 * @return     -
 * @context    Function is called from all modules to set or clear a PortPin
 */
/*****************************************************************************/
void BrsHwTogglePin(brsHw_TogglePin Pin)
{
#if defined (VGEN_ENABLE_DRVDIO)
  #error "Configure the valid DioChannel for the toggle pins within your DrvDio config and set it as value for BrsHw_Dio_ToggleX_Channel. Or disable the depending BRS mechanism."*/
# if defined (BRS_ENABLE_SUPPORT_LEDS)
  Dio_ChannelType BrsHw_Dio_ToggleLED_Channel = DioConf_DioChannel_DioChannel_LED;
# endif
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  Dio_ChannelType BrsHw_Dio_ToggleWD_Channel = DioConf_DioChannel_DioChannel_WD;
# endif
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  Dio_ChannelType BrsHw_Dio_ToggleCUSTOM_Channel = DioConf_DioChannel_DioChannel_CUSTOM;
# endif
#endif /*VGEN_ENABLE_DRVDIO*/

#if defined (BRS_ENABLE_SUPPORT_LEDS)
  static uint8 BrsHw_ToggleSwitch_LED = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  static uint8 BrsHw_ToggleSwitch_WD = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  static uint8 BrsHw_ToggleSwitch_CUSTOM = BRSHW_PORT_LOGIC_HIGH;
#endif

  switch (Pin)
  {
#if defined (BRS_ENABLE_SUPPORT_LEDS)
    case BRSHW_TOGGLEPIN_LED:
# if defined (VGEN_ENABLE_DRVDIO)
      Dio_WriteChannel(BrsHw_Dio_ToggleLED_Channel, BrsHw_ToggleSwitch_LED & 0x01);
# else
      BrsHwPort_SetLevel(BRSHW_PORT_LED, BrsHw_ToggleSwitch_LED & 0x01);
# endif
      BrsHw_ToggleSwitch_LED++;
      break;
#endif /*BRS_ENABLE_SUPPORT_LEDS*/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
    case BRSHW_TOGGLEPIN_WD:
# if defined (VGEN_ENABLE_DRVDIO)
      Dio_WriteChannel(BrsHw_Dio_ToggleWD_Channel, BrsHw_ToggleSwitch_WD & 0x01);
# else
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_WD, BrsHw_ToggleSwitch_WD & 0x01);
# endif
      BrsHw_ToggleSwitch_WD++;
      break;
#endif /*BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN*/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
    case BRSHW_TOGGLEPIN_CUSTOM:
# if defined (VGEN_ENABLE_DRVDIO)
      Dio_WriteChannel(BrsHw_Dio_ToggleCUSTOM_Channel, BrsHw_ToggleSwitch_CUSTOM & 0x01);
# else
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_CUSTOM, BrsHw_ToggleSwitch_CUSTOM & 0x01);
# endif
      BrsHw_ToggleSwitch_CUSTOM++;
      break;
#endif /*BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/
    default:
      break;
  }
}
#endif /*BRS_ENABLE_SUPPORT_LEDS||BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN||BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/

# if defined (BRSASR_ENABLE_SAFECTXSUPPORT)
/*****************************************************************************/
/**
 * @brief      This API is used to enable hardware access in untrusted mode
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsAsrInitBsw
 */
/*****************************************************************************/
void BrsHw_EnableHwAccess(void)
{
#if defined (BRSHW_USERMODE_ACCESS_GROUP_A)
  OPACR_REGISTER_LPIT_ADDR &= OPACR_REGISTER_LPIT_VALUE; /* set OPACR-Register to enable read/write access to LPIT in usermode */
  PACR_REGISTER_AIPS_ADDR  &= PACR_REGISTER_AIPS_VALUE;  /* set PACR-Register to enable read/write access to AIPS in usermode */

# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
  OPACR_REGISTER_CAN0_ADDR &= OPACR_REGISTER_CAN0_VALUE; /* set OPACR-Register to enable read/write access to FlexCAN0 in usermode */
#  endif
#  if defined (kCanPhysToLogChannelIndex_1)
  OPACR_REGISTER_CAN1_ADDR &= OPACR_REGISTER_CAN1_VALUE; /* set OPACR-Register to enable read/write access to FlexCAN1 in usermode */
#  endif
#  if defined (kCanPhysToLogChannelIndex_2)
  OPACR_REGISTER_CAN2_ADDR &= OPACR_REGISTER_CAN2_VALUE; /* set OPACR-Register to enable read/write access to FlexCAN2 in usermode */
#  endif
# endif /*VGEN_ENABLE_CAN_DRV*/

# if defined (VGEN_ENABLE_DRVETH__BASEASR)
  OPACR_REGISTER_ENET_ADDR &= OPACR_REGISTER_ENET_VALUE; /* set OPACR-Register to enable read/write access to ENET in usermode */
# endif

# if defined (VGEN_ENABLE_DRVSPI)
  OPACR_REGISTER_SPI0_ADDR &= OPACR_REGISTER_SPI0_VALUE; /* set OPACR-Register to enable read/write access to SPI in usermode */
#  if !defined (BRS_DERIVATIVE_S32K116)
  OPACR_REGISTER_SPI1_ADDR &= OPACR_REGISTER_SPI1_VALUE; /* set OPACR-Register to enable read/write access to SPI in usermode */
#  if defined (BRS_DERIVATIVE_S32K144) || defined (BRS_DERIVATIVE_S32K146) || defined (BRS_DERIVATIVE_S32K148)
  OPACR_REGISTER_SPI2_ADDR &= OPACR_REGISTER_SPI2_VALUE; /* set OPACR-Register to enable read/write access to SPI in usermode */
#  endif
#  endif
# endif /*VGEN_ENABLE_DRVSPI*/

# if defined (VGEN_ENABLE_DRVWD)
  OPACR_REGISTER_WDOG_ADDR &= OPACR_REGISTER_WDOG_VALUE; /* set OPACR-Register to enable read/write access to WDOG in usermode */
# endif

# if defined (VGEN_ENABLE_DRVFLS)
  OPACR_REGISTER_FLASH_ADDR &= OPACR_REGISTER_FLASH_VALUE; /* set OPACR-Register to enable read/write access to Fls in usermode */
# endif /*VGEN_ENABLE_DRVFLS*/

#else
  #error "Your derivative group is currently not supported for UserMode access. Only USERMODE_ACCESS_GROUP_A is implemented."
#endif /*BRSHW_USERMODE_ACCESS_GROUP_x*/
}
# else
  /* BrsHw_EnableHwAccess() removed by Organi, because of ALM attributes of project */
# endif /*BRSASR_ENABLE_SAFECTXSUPPORT*/

/**********************************************************************************************************************
  Interrupt handler function protoytpes
**********************************************************************************************************************/
