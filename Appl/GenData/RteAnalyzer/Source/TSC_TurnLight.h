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
 *          File:  TSC_TurnLight.h
 *        Config:  S32K144_Start.dpa
 *   ECU-Project:  MyECU
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1800257
 *
 *   Description:  Header of wrapper software component for Bte-based Rte test cases
 *********************************************************************************************************************/


/** Sender receiver - explicit read services */
Std_ReturnType TSC_TurnLight_Rte_Read_CountSignal_Left_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_CountSignal_Right_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_CrashIntensity_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_EmergencyBrakeLight_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_HazardSw_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_IGN_Status_u8_signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampCtrlCmd_FL_u8_signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampCtrlCmd_FR_u8_signa(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampCtrlCmd_RL_u8_signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampCtrlCmd_RR_u8_signal(uint64 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampFb_FL_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampFb_FR_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampFb_RL_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampFb_RR_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_TurnLampSw_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_VehicleSpeed_u16_signal(uint16 *data);
Std_ReturnType TSC_TurnLight_Rte_Read_VehicleSpeed_Valid_u8_Signal(uint8 *data);

/** Sender receiver - explicit write services */
Std_ReturnType TSC_TurnLight_Rte_Write_TurnLampSwMode_u8_signa(uint8 data);

/** Client server interfaces */
Std_ReturnType TSC_TurnLight_Rte_Call_TurnLightService_TurnLightControl_Operation(const TurnLightService *TurnLightCtrlPara);




