/*
 * File:   Android_HMI_AlarmPacket_Generator.c
 * Author: user
 *
 * Created on 2021年9月27日, 上午 11:33
 */
#include "SystemControl.h"

extern unsigned int CRC_CREATE(unsigned char *data, unsigned char lenth);

extern _SYSTEM_PARAMETER SystemParameter;
extern _PARSING_WORD U1_SendingWord;
extern _PARSING_DATA U1_SendingWord2;
extern unsigned char UART1TxBuffer[UART1_BUFFER_SIZE];
extern unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];
extern unsigned int UART1TimeOutCount, UART1RxBufCount, U1SendDataCount, U1PacketLen;

void Send_GetAlarm_A1_SetResponse(void)
{
    UART1TxBuffer[0] = Android_HMI_Alarm_A1_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE8;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5GTwhenTE3;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE3Offset;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetAlarm_A1_A2SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_Alarm_A1_A2_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5GTwhenFAN2Stop;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE8;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5GTwhenTE3;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetAlarm_A2_B_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_Alarm_A2_B_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE3Offset;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5LTwhenFAN2Stop;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeBSet.TE5;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeBSet.TE5GTwhenFAN2Stop;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetHeaterTempAlarm_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_HeaterTempAlarm_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighTE11;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowTE11;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighTE12;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowTE12;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetHeaterPDTAlarm_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_HeaterPDTAlarm_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighPDT2;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowPDT2;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighPDT3;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowPDT3;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetMTR4TempAlarm_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_MTR4TempAlarm_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE3;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE3;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE8;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE8;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_Get_MTR4TempPDTAlarm_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_MTR4TempPDTAlarm_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE5;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE5;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighPDT1;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowPDT1;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetD_Alarm1_Set_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_D_Alarm1_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE3;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE3;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE5;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE5;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];     
}

void Send_GetD_Alarm2_Set_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_D_Alarm2_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE8;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE8;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE11;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE11;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];        
}

void Send_GetD_Alarm3__D1_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_D_Alarm3__D1_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE12;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE12;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE10;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE10;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetD1_Alarm2_Set_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_D1_Alarm2_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE6;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE6;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighPDT1;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowPDT1;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}

void Send_GetD1_Alarm3_SetResponse()
{
    UART1TxBuffer[0] = Android_HMI_D1_Alarm3_Set_CommandEnum;

    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighPDT2;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowPDT2;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighPDT3;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowPDT3;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];      
}
