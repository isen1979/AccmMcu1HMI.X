/*
 * File:   Android_HMI_WriteParameters.c
 * Author: user
 *
 * Created on 2021年9月29日, 上午 9:18
 */

#include "SystemControl.h"
#include "COM3_Command.h"

extern void Register_COM3_Send_Command(unsigned char cmd);//Philip 20220407 0.0.1

extern unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];
extern _SYSTEM_PARAMETER SystemParameter;
extern _PARSING_WORD U1_SendingWord;
extern _PARSING_DATA U1_SendingWord2;

void WriteFan1_1_Parameters(void)
{
    switch(UART1RxBuffer[1])
    {
        case 1 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.SuperHighPressureAlarmSet = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter1_Command_Enum);
            break;
        case 2 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.HighPressureAlarmSet = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter1_Command_Enum);
            break;
        case 3 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.LowPressureAlarmSet = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter1_Command_Enum);
            break;
        case 4 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.SuperLowPressureAlarmSet = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter1_Command_Enum);
            break;
        case 5 :
            U1_SendingWord2.data[0] = UART1RxBuffer[2];
            U1_SendingWord2.data[1] = UART1RxBuffer[3];
            U1_SendingWord2.data[2] = UART1RxBuffer[4];
            U1_SendingWord2.data[3] = UART1RxBuffer[5];
            SystemParameter.FAN1_1.value.PID_P = U1_SendingWord2.value;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter4_Command_Enum);
            break;
        case 6 :            
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.PID_I = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter2_Command_Enum);           
            break;
        case 7 :          
            U1_SendingWord2.data[0] = UART1RxBuffer[2];
            U1_SendingWord2.data[1] = UART1RxBuffer[3];
            U1_SendingWord2.data[2] = UART1RxBuffer[4];
            U1_SendingWord2.data[3] = UART1RxBuffer[5];
            SystemParameter.FAN1_1.value.PID_D = U1_SendingWord2.value;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter4_Command_Enum);            
            break;       
        case 8 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.DeadBand = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 9 :         
            SystemParameter.FAN1_1.value.FAN1_LowLimit = UART1RxBuffer[2];
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter3_Command_Enum);        
            break;   
        case 10 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.FAN1_High2 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 11 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.FAN1_High1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;       
        case 12 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.FAN1_1_2_DelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 13 :            
            SystemParameter.FAN1_1.value.ManualStartFrequency = UART1RxBuffer[2];
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter3_Command_Enum);           
            break;   
        case 14 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.ManualStopFrequency = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter5_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 15 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.FAN1_1ManualOpenSize = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;   
        case 16 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN1_1.value.PT_1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;            
    }    
}

void WriteFan2_Parameter(void)
{
    switch(UART1RxBuffer[1])
    {
        case 17 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN_2.value.FAN_2_Target_Temp1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 18 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN_2.value.FAN_2_Target_Temp2 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 19 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN_2.value.FAN_2_Target_Temp3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 20 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN_2.value.FAN_2_Top = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 21 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN_2.value.FAN_2_Low = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 22 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN_2.value.FAN_2_TargetTemp1_Hz = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 23 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN_2.value.FAN_2_TargetTemp2_Hz = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;       
        case 24 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.FAN_2.value.FAN_2_TargetTemp3_Hz = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;         
    }     
}

void Write_Heater_Parameters(void)
{
    switch(UART1RxBuffer[1])
    {
        case 25 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.OP_Temp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 26 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.StandBy_Temp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 27 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.KeepWarmTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 28 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.SuperHighTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 29 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.HighTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 30 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.LowTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 31 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.SuperLowTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;       
        case 32 :
            U1_SendingWord2.data[0] = UART1RxBuffer[2];
            U1_SendingWord2.data[1] = UART1RxBuffer[3];
            U1_SendingWord2.data[2] = UART1RxBuffer[4];
            U1_SendingWord2.data[3] = UART1RxBuffer[5];
            SystemParameter.HeaterSet.value.PID_P = U1_SendingWord2.value;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 33 :
            U1_SendingWord2.data[0] = UART1RxBuffer[2];
            U1_SendingWord2.data[1] = UART1RxBuffer[3];
            U1_SendingWord2.data[2] = UART1RxBuffer[4];
            U1_SendingWord2.data[3] = UART1RxBuffer[5];
            SystemParameter.HeaterSet.value.PID_I = U1_SendingWord2.value;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter4_Command_Enum);//Philip 20220408 0.0.1
            break;   
        case 34 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.PID_D = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter4_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 35 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.DeadBand = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter4_Command_Enum);//Philip 20220408 0.0.1
            break;       
        case 36 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.MoreThanSP_StopTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 37 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.LessThanSP_StartTemp = U1_SendingWord.WordData;  
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;   
        case 38 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.TopLimit = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter5_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 39 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.LowLimit = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter5_Command_Enum);//Philip 20220408 0.0.1
            break;   
        case 40 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.FireCount = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter4_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 41 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.ReFireTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;   
        case 42 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.ManualOpenSize = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter5_Command_Enum);//Philip 20220408 0.0.1
            break;  
        case 129 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.HeaterSet.value.CleanOvenTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter5_Command_Enum);//Philip 20220408 0.0.1
            break;            
    }    
}

void WriteMTR4_Parameter(void)
{
    switch(UART1RxBuffer[1])
    {
        case 43 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Wheel.value.T5_CheckTemp1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 44 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Wheel.value.T5_CheckTemp2 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 45 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Wheel.value.T5_CheckTemp3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 46 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Wheel.value.TopLimitFrequency = U1_SendingWord.WordData;            
            break;
        case 47 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Wheel.value.StopTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 48 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Wheel.value.T5_CheckTemp1Frequency = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 49 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Wheel.value.T5_CheckTemp2Frequency = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;       
        case 50 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Wheel.value.T5_CheckTemp3Frequency = U1_SendingWord.WordData;  
            Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 51 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Wheel.value.LowLimitFrequency = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;
    }     
}

void WritePCD_2_6_V21_Parameter(void)
{
    switch(UART1RxBuffer[1])
    {
        case 52 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD2.Value.FaultDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSet_PCD2_PCD6_Parameter_Command_Enum);//Philip 20220407 0.0.1
            break;
        case 53 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD2.Value.AlarmDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSet_PCD2_PCD6_Parameter_Command_Enum);//Philip 20220407 0.0.1
            break;
        case 54 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_6.value.FaultDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSet_PCD2_PCD6_Parameter_Command_Enum);//Philip 20220407 0.0.1
            break;
        case 55 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_6.value.AlarmDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSet_PCD2_PCD6_Parameter_Command_Enum);//Philip 20220407 0.0.1
            break;
        case 56 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.V21.Value.FaultDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSet_V21_Parameter_Command_Enum);//Philip 20220407 0.0.1
            break;
        case 57 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.V21.Value.AlarmDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSet_V21_Parameter_Command_Enum);//Philip 20220407 0.0.1
            break;
    }
}


void WritePCD_20_Parameter(void)
{
    switch(UART1RxBuffer[1])
    {
        case 58 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.OP_Temp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 59 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.StandByTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 60 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.CoolingTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 61 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.FaultDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 62 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.AlarmDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;  
        case 63 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.OnOFFDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;            
        case 64 :
            U1_SendingWord2.data[0] = UART1RxBuffer[2];
            U1_SendingWord2.data[1] = UART1RxBuffer[3];
            U1_SendingWord2.data[2] = UART1RxBuffer[4];
            U1_SendingWord2.data[3] = UART1RxBuffer[5];
            SystemParameter.PCD_20.value.PID_P = U1_SendingWord2.value;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 65 :
            U1_SendingWord2.data[0] = UART1RxBuffer[2];
            U1_SendingWord2.data[1] = UART1RxBuffer[3];
            U1_SendingWord2.data[2] = UART1RxBuffer[4];
            U1_SendingWord2.data[3] = UART1RxBuffer[5];
            SystemParameter.PCD_20.value.PID_I = U1_SendingWord2.value;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter4_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 66 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.PID_D = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter4_Command_Enum);//Philip 20220408 0.0.1
            break;       
        case 67 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.DeadBand = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 68 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.TopLimit = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 69 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.LowLimit = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;       
        case 70 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_20.value.ManualOpenSize = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter3_Command_Enum);//Philip 20220408 0.0.1
            break;    
    }   
}

void WritePCD_22_25_Parameter(void)
{
    switch(UART1RxBuffer[1])
    {
        case 71 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_22.value.FaultDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD22_Parameter_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 72 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_22.value.AlarmDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD22_Parameter_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 73 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_22.value.ReleaseTemp = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD22_Parameter_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 74 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_22.value.OnOFFDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD22_Parameter_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 75 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_25.value.FaultDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD25_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 76 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_25.value.AlarmDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD25_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 77 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_25.value.OnOFFDelayTime = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD25_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break;       
        case 78 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_25.value.TopLimit = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD25_Parameter1_Command_Enum);//Philip 20220408 0.0.1
            break; 
        case 79 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_25.value.LowLimit = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD25_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
        case 80 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.PCD_25.value.ManualOpenSize = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_TxSet_PCD25_Parameter2_Command_Enum);//Philip 20220408 0.0.1
            break;
    }
}

void Write_Alarm1_Parameter(void)
{
    switch(UART1RxBuffer[1])
    {
        case 81 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE8 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter1_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 82 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter1_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 83 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5GTwhenTE3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter1_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 84 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE3Offset = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter1_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 85 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5GTwhenFAN2Stop = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter2_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 86 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE8 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter2_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 87 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter2_CommandEnum);//Philip 20220408 0.0.1
            break;       
        case 88 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5GTwhenTE3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter2_CommandEnum);//Philip 20220408 0.0.1
            break; 
        case 89 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE3Offset = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter3_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 90 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5LTwhenFAN2Stop = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter3_CommandEnum);//Philip 20220408 0.0.1
            break;
    }
}

void Write_Alarm2_Parameter(void)
{
    switch(UART1RxBuffer[1])
    {
        case 91 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeBSet.TE5 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter3_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 92 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeBSet.TE5GTwhenFAN2Stop = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter3_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 93 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighTE11 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter4_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 94 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowTE11 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter4_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 95 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighTE12 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter4_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 96 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowTE12 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter4_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 97 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighPDT2 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter5_CommandEnum);//Philip 20220408 0.0.1
            break;       
        case 98 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowPDT2 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter5_CommandEnum);//Philip 20220408 0.0.1
            break; 
        case 99 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighPDT3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter5_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 100 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowPDT3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter5_CommandEnum);//Philip 20220408 0.0.1
            break;
    }
}

void Write_Alarm3_Parameter(void)
{
    switch(UART1RxBuffer[1])
    {
        case 101 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter6_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 102 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter6_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 103 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE8 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter6_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 104 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE8 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter7_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 105 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE5 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter7_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 106 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE5 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter7_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 107 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighPDT1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter6_CommandEnum);//Philip 20220408 0.0.1
            break;       
        case 108 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowPDT1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter7_CommandEnum);//Philip 20220408 0.0.1
            break; 
        case 109 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter8_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 110 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter8_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 111 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE5 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter8_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 112 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE5 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter8_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 113 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE8 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter9_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 114 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE8 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter9_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 115 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE11 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter9_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 116:
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE11 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter9_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 117 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE12 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter10_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 118 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE12 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter10_CommandEnum);//Philip 20220408 0.0.1
            break;
    }
}

void Write_Alarm4_Parameter(void)
{
    switch(UART1RxBuffer[1])
    {
        case 119 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE14 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter10_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 120 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE14 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter10_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 121 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter11_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 122 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter11_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 123 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighPDT1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter11_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 124 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowPDT1 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter11_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 125 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighPDT2 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter12_CommandEnum);//Philip 20220408 0.0.1
            break;       
        case 126 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowPDT2 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter12_CommandEnum);//Philip 20220408 0.0.1
            break; 
        case 127 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighPDT3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter12_CommandEnum);//Philip 20220408 0.0.1
            break;
        case 128 :
            U1_SendingWord.Byte[0] = UART1RxBuffer[2];
            U1_SendingWord.Byte[1] = UART1RxBuffer[3];
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowPDT3 = U1_SendingWord.WordData;
            Register_COM3_Send_Command(COM3_RxSetAlarm_Parameter12_CommandEnum);//Philip 20220408 0.0.1
            break;
    }
}
