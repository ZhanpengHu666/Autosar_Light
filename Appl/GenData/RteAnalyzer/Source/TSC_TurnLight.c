/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  TSC_TurnLight.c
 *        Config:  S32K144_Start.dpa
 *   ECU-Project:  MyECU
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Implementation of wrapper software component for Bte-based Rte test cases
 *********************************************************************************************************************/
#include "Rte_TurnLight.h"
#include "TSC_TurnLight.h"








Std_ReturnType TSC_TurnLight_Rte_Read_CountSignal_Left_u8_Signal(uint8 *data)
{
  return Rte_Read_CountSignal_Left_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_CountSignal_Right_u8_Signal(uint8 *data)
{
  return Rte_Read_CountSignal_Right_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_CrashIntensity_u8_Signal(uint8 *data)
{
  return Rte_Read_CrashIntensity_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_EmergencyBrakeLight_u8_Signal(uint8 *data)
{
  return Rte_Read_EmergencyBrakeLight_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_HazardSw_u8_Signal(uint8 *data)
{
  return Rte_Read_HazardSw_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_IGN_Status_u8_signal(uint8 *data)
{
  return Rte_Read_IGN_Status_u8_signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampCtrlCmd_FL_u8_signal(uint8 *data)
{
  return Rte_Read_TurnLampCtrlCmd_FL_u8_signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampCtrlCmd_FR_u8_signa(uint8 *data)
{
  return Rte_Read_TurnLampCtrlCmd_FR_u8_signa(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampCtrlCmd_RL_u8_signal(uint8 *data)
{
  return Rte_Read_TurnLampCtrlCmd_RL_u8_signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampCtrlCmd_RR_u8_signal(uint64 *data)
{
  return Rte_Read_TurnLampCtrlCmd_RR_u8_signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampFb_FL_u8_Signal(uint8 *data)
{
  return Rte_Read_TurnLampFb_FL_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampFb_FR_u8_Signal(uint8 *data)
{
  return Rte_Read_TurnLampFb_FR_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampFb_RL_u8_Signal(uint8 *data)
{
  return Rte_Read_TurnLampFb_RL_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampFb_RR_u8_Signal(uint8 *data)
{
  return Rte_Read_TurnLampFb_RR_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampSw_u8_Signal(uint8 *data)
{
  return Rte_Read_TurnLampSw_u8_Signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_VehicleSpeed_u16_signal(uint16 *data)
{
  return Rte_Read_VehicleSpeed_u16_signal(data);
}

Std_ReturnType TSC_TurnLight_Rte_Read_VehicleSpeed_Valid_u8_Signal(uint8 *data)
{
  return Rte_Read_VehicleSpeed_Valid_u8_Signal(data);
}




Std_ReturnType TSC_TurnLight_Rte_Write_TurnLampSwMode_u8_signa(uint8 data)
{
  return Rte_Write_TurnLampSwMode_u8_signa(data);
}





     /* Client Server Interfaces: */
Std_ReturnType TSC_TurnLight_Rte_Call_TurnLightService_TurnLightControl_Operation(const TurnLightService *TurnLightCtrlPara)
{
  return Rte_Call_TurnLightService_TurnLightControl_Operation(TurnLightCtrlPara);
}


     /* Service calls */


     /* Mode Interfaces */




     /* Trigger Interfaces */

     /* Inter-Runnable variables */







     /* TurnLight */
      /* TurnLight */



