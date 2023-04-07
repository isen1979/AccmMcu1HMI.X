/*
 * File:   Android_HMI_GetParameterResponsePacketGenerator.c
 * Author: user
 *
 * Created on 2021年9月28日, 上午 11:25
 */
#include "SystemControl.h"

extern _SYSTEM_PARAMETER SystemParameter;
extern _PARSING_WORD U1_SendingWord;
extern _PARSING_DATA U1_SendingWord2;
extern unsigned char UART1TxBuffer[UART1_BUFFER_SIZE];
extern unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];
extern unsigned int UART1TimeOutCount, UART1RxBufCount, U1SendDataCount, U1PacketLen;


extern unsigned int CRC_CREATE(unsigned char *data, unsigned char lenth);


//U1_SendingWord2.value = ExtFirmwareDate;
void SendFan1_1_GetSV_Response(void)
{
    UART1TxBuffer[0] = Android_HMI_Fan1_1_GetSV_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.SuperHighPressureAlarmSet;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.HighPressureAlarmSet;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.LowPressureAlarmSet;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.SuperLowPressureAlarmSet;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void SendFan1_1_GetPI_Response(void)
{
    UART1TxBuffer[0] = Android_HMI_Fan1_1_GetPI_CommandEnum;

    U1_SendingWord2.value = SystemParameter.FAN1_1.value.PID_P;
    UART1TxBuffer[1] = U1_SendingWord2.data[0];
    UART1TxBuffer[2] = U1_SendingWord2.data[1];
    UART1TxBuffer[3] = U1_SendingWord2.data[2];
    UART1TxBuffer[4] = U1_SendingWord2.data[3];
    U1_SendingWord2.value = SystemParameter.FAN1_1.value.PID_D;//Philip 20220408 0.0.1
    UART1TxBuffer[5] = U1_SendingWord2.data[0];
    UART1TxBuffer[6] = U1_SendingWord2.data[1];
    UART1TxBuffer[7] = U1_SendingWord2.data[2];
    UART1TxBuffer[8] = U1_SendingWord2.data[3];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void SendFan1_1_GetD_LowLimit_Response(void)
{
    UART1TxBuffer[0] = Android_HMI_Fan1_1_GetD_LowLimit_CommandEnum;

    U1_SendingWord2.value = SystemParameter.FAN1_1.value.PID_I;//Philip 20220408 0.0.1
    UART1TxBuffer[1] = U1_SendingWord2.data[0];
    UART1TxBuffer[2] = U1_SendingWord2.data[1];
    UART1TxBuffer[3] = U1_SendingWord2.data[2];
    UART1TxBuffer[4] = U1_SendingWord2.data[3];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.DeadBand;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_LowLimit;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void SendFan1_1_Get_TopLimit_Response(void)
{
    UART1TxBuffer[0] = Android_HMI_Fan1_1_GetTopLimit_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_High2;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_High1;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_1_2_DelayTime;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.PT_1;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void SendFan1_1_Get_ManualSet_Response(void)
{
    UART1TxBuffer[0] = Android_HMI_Fan1_1_GetManualSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.ManualStartFrequency;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.ManualStopFrequency;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_1ManualOpenSize;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = 0;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_GetFan2TempSetSpeedTopLimit_Response(void)
{
    UART1TxBuffer[0] = Android_HMI_Fan2_GetTempSetSpeedTopLimit_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Target_Temp1;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Target_Temp2;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Target_Temp3;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Top;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_GetFan2SpeedSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_Fan2_GetSpeedSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Low;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_TargetTemp1_Hz;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_TargetTemp2_Hz;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_TargetTemp3_Hz;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_HeaterGetTempSetDbResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_Heater_TempSetDb_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.OP_Temp;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.StandBy_Temp;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.KeepWarmTemp;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.DeadBand;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_Heater_Get_HH2LLSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_Heater_TempHH2LLSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.SuperHighTemp;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.HighTemp;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.LowTemp;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.SuperLowTemp;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_Heater_GetSP2LowLimitSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_HeaterSP2LowLimitSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.MoreThanSP_StopTemp;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.LessThanSP_StartTemp;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.TopLimit;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.LowLimit;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_Heater_GetPI_SetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_HeaterPI_Set_CommandEnum;

    U1_SendingWord2.value = SystemParameter.HeaterSet.value.PID_P;
    UART1TxBuffer[1] = U1_SendingWord2.data[0];
    UART1TxBuffer[2] = U1_SendingWord2.data[1];
    UART1TxBuffer[3] = U1_SendingWord2.data[2];
    UART1TxBuffer[4] = U1_SendingWord2.data[3];
    U1_SendingWord2.value = SystemParameter.HeaterSet.value.PID_I;
    UART1TxBuffer[5] = U1_SendingWord2.data[0];
    UART1TxBuffer[6] = U1_SendingWord2.data[1];
    UART1TxBuffer[7] = U1_SendingWord2.data[2];
    UART1TxBuffer[8] = U1_SendingWord2.data[3];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_Heater_GetManualSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_HeaterD2_ManualSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.PID_D;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.FireCount;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.ReFireTemp;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.ManualOpenSize;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_MTR4_GetTE5ConditionSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_MTR4_TE5ConditionSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp1;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp2;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp3;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.HeaterSet.value.CleanOvenTime;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_MTR4_GetTE5SpeedSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_MTR4_TE5SpeedSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp1Frequency;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp2Frequency;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp3Frequency;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = 0;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}

void Send_MTR4_GetTopStopLowSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_MTR4_TopStopTempLowSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Wheel.value.TopLimitFrequency;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Wheel.value.StopTemp;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Wheel.value.LowLimitFrequency;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = 0;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];
}                

void Send_GetPCD2_V21SetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_PCD2_V21Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.PCD2.Value.FaultDelayTime;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD2.Value.AlarmDelayTime;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.V21.Value.FaultDelayTime;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.V21.Value.AlarmDelayTime;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
}

void Send_GetPCD20_TempSizeSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_PCD20_Temp_SizeSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.PCD_20.value.OP_Temp;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_20.value.StandByTemp;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_20.value.CoolingTemp;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_20.value.ManualOpenSize;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetPCD20_PISetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_PCD20_PISet_CommandEnum;

    U1_SendingWord2.value = SystemParameter.PCD_20.value.PID_P;
    UART1TxBuffer[1] = U1_SendingWord2.data[0];
    UART1TxBuffer[2] = U1_SendingWord2.data[1];
    UART1TxBuffer[3] = U1_SendingWord2.data[2];
    UART1TxBuffer[4] = U1_SendingWord2.data[3];
    U1_SendingWord2.value = SystemParameter.PCD_20.value.PID_I;
    UART1TxBuffer[5] = U1_SendingWord2.data[0];
    UART1TxBuffer[6] = U1_SendingWord2.data[1];
    UART1TxBuffer[7] = U1_SendingWord2.data[2];
    UART1TxBuffer[8] = U1_SendingWord2.data[3];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetPCD20_D_TimeSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_PCD20_D_TimeSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.PCD_20.value.PID_D;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_20.value.FaultDelayTime;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_20.value.AlarmDelayTime;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_20.value.OnOFFDelayTime;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetPCD20_DeadBandTopLowLimitPCD6SetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_PCD20_DeadBandTopLowLimit_PCD6TimeSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.PCD_20.value.DeadBand;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_20.value.TopLimit;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_20.value.LowLimit;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_6.value.FaultDelayTime;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetPCD22_SetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_PCD22_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.PCD_22.value.FaultDelayTime;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_22.value.AlarmDelayTime;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_22.value.ReleaseTemp;//Philip 20220517 0.0.1//SystemParameter.PCD_22.value.OnOFFDelayTime;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_22.value.OnOFFDelayTime;//Philip 20220517 0.0.1//SystemParameter.PCD_22.value.ReleaseTemp;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetPCD25_PCD6TimeSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_PCD25_PCD6_TimeSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.PCD_25.value.FaultDelayTime;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_25.value.AlarmDelayTime;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_25.value.OnOFFDelayTime;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_6.value.AlarmDelayTime;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetPCD25_Limit_ManualSetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_PCD25_Limit_ManualSet_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.PCD_25.value.TopLimit;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_25.value.LowLimit;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.PCD_25.value.ManualOpenSize;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = 0;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}
