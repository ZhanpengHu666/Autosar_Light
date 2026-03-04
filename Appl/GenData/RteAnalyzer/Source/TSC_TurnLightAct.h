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
 *          File:  TSC_TurnLightAct.h
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
Std_ReturnType TSC_TurnLightAct_Rte_Read_TurnLamp_FL_Out_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLightAct_Rte_Read_TurnLamp_RL_Out_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLightAct_Rte_Read_TurnLapm_FR_Out_u8_Signal(uint8 *data);
Std_ReturnType TSC_TurnLightAct_Rte_Read_TurnLapme_RR_Out_u8_Signal(uint8 *data);

/** Sender receiver - explicit write services */
Std_ReturnType TSC_TurnLightAct_Rte_Write_Com_CAN_LA_St_DirectionLampL_u8_signal(uint8 data);
Std_ReturnType TSC_TurnLightAct_Rte_Write_Com_CAN_LA_St_DirectionLampR_u8_signal(uint8 data);
Std_ReturnType TSC_TurnLightAct_Rte_Write_CountSignal_Left_u8_Signal(uint8 data);
Std_ReturnType TSC_TurnLightAct_Rte_Write_CountSignal_Right_u8_Signal(uint8 data);
Std_ReturnType TSC_TurnLightAct_Rte_Write_TurnLampCtrlCmd_FL_u8_signal(uint8 data);
Std_ReturnType TSC_TurnLightAct_Rte_Write_TurnLampCtrlCmd_FR_u8_signa(uint8 data);
Std_ReturnType TSC_TurnLightAct_Rte_Write_TurnLampCtrlCmd_RL_u8_signal(uint8 data);
Std_ReturnType TSC_TurnLightAct_Rte_Write_TurnLampCtrlCmd_RR_u8_signal(uint64 data);

/** Client server interfaces */
Std_ReturnType TSC_TurnLightAct_Rte_Call_IoHwAb_TurnLightCtrlCmd_FL_Operation(uint8 CtrlCmd);
Std_ReturnType TSC_TurnLightAct_Rte_Call_IoHwAb_TurnLightCtrlCmd_FR_Operation(uint8 CtrlCmd);
Std_ReturnType TSC_TurnLightAct_Rte_Call_IoHwAb_TurnLightCtrlCmd_RL_Operation(uint8 CtrlCmd);
Std_ReturnType TSC_TurnLightAct_Rte_Call_IoHwAb_TurnLightCtrlCmd_RR_Operation(uint8 CtrlCmd);




