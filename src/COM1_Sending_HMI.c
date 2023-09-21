/*
 * File:   Android_HMI_Sending.c
 * Author: user
 *
 * Created on 2021年9月24日, 上午 9:32
 */
#include "SystemControl.h"
#include "COM3_Command.h"

extern unsigned int CRC_CREATE(unsigned char *data, unsigned char lenth);

extern unsigned char UART1TxBuffer[UART1_BUFFER_SIZE];
extern unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];
extern unsigned int UART1TimeOutCount, UART1RxBufCount, U1SendDataCount, U1PacketLen;
extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
extern unsigned int FirmwareVersion;
extern unsigned long FirmwareDate;
extern unsigned int ExtFirmwareVersion;
extern unsigned long ExtFirmwareDate;

extern _IO_STATUS ioStatus;
extern _ALARM_STATUS alarmStatus;

_PARSING_WORD U1_SendingWord;
_PARSING_DATA U1_SendingWord2;
unsigned char RoutineSendFlag = 1;

void SendFirmwareVersion(unsigned char flag)//flag == 0 : Firmware Version, flag == 1 : External Device Firmware Version
{
    switch(flag)
    {
        case 0 :
            UART1TxBuffer[0] = Android_HMI_GetFirmwareVersionCommandEnum;
            U1_SendingWord.WordData = FirmwareVersion;
            U1_SendingWord2.value = FirmwareDate;
            break;
        case 1 :
            UART1TxBuffer[0] = Android_HMI_GetExtFirmwareVersionCommandEnum;
            U1_SendingWord.WordData = ExtFirmwareVersion;
            U1_SendingWord2.value = ExtFirmwareDate;            
            break;
    }    
    UART1TxBuffer[1] = U1_SendingWord2.data[0];
    UART1TxBuffer[2] = U1_SendingWord2.data[1];
    UART1TxBuffer[3] = U1_SendingWord2.data[2];
    UART1TxBuffer[4] = U1_SendingWord2.data[3];
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    UART1TxBuffer[7] = 0;
    UART1TxBuffer[8] = 0;
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE;
}

void Send_LoopBackResponse(void)
{
    unsigned char i;
    
    for(i=0;i<12;i++)
        UART1TxBuffer[i] = UART1RxBuffer[i];
}
extern _FAN1_1_RUNTIME_DISPLAY FAN1_1_RunTimeDisplay;
extern _FAN2_RUNTIME_DISPLAY FAN2_RunTimeDisplay;
extern _MTR4_RUNTIME_DISPLAY MTR4_RunTimeDisplay;
extern _HEATER_RUNTIME_DISPLAY HEATER_RunTimeDisplay;
extern _OTHER_RUNTIME_DISPLAY OtherRunTimeDisplay;
extern _PCD20_RUNTIME_DISPLAY PCD20_RunTimeDisplay;
extern _RUNTIME_STATUS RunTimeStatus;//Philip 20220124 0.0.1

void Get_TE1_3_5_6_SendPacket(void)
{    
    UART1TxBuffer[0] = Android_HMI_RunTimeTE1_3_5_6_CommandEnum;
    U1_SendingWord.WordData = OtherRunTimeDisplay.TE1;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = PCD20_RunTimeDisplay.TE3;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = MTR4_RunTimeDisplay.TE5;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = OtherRunTimeDisplay.TE6;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}

void Get_TE8_10_11_12_SendPacket(void)
{  
    UART1TxBuffer[0] = Android_HMI_RunTimeTE8_10_11_12_CommandEnum;
    U1_SendingWord.WordData = OtherRunTimeDisplay.TE8;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = OtherRunTimeDisplay.TE10;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = HEATER_RunTimeDisplay.TE11;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = FAN2_RunTimeDisplay.TE12;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}

void Get_PDT1_2_3_SendPacket(void)
{
    UART1TxBuffer[0] = Android_HMI_RunTimePDT1_2_3_CommandEnum;
    U1_SendingWord.WordData = OtherRunTimeDisplay.PDT1;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = OtherRunTimeDisplay.PDT2;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = OtherRunTimeDisplay.PDT5;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = OtherRunTimeDisplay.PT1;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}

//Philip 20220124 0.0.1 ====================================================================
void Get_FAN1_RunTime_SendPacket(void)
{
    UART1TxBuffer[0] = Android_HMI_FAN1_RunTime_CommandEnum;
    U1_SendingWord.WordData = FAN1_1_RunTimeDisplay.PID_Output;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = FAN1_1_RunTimeDisplay.RealFreq;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = FAN1_1_RunTimeDisplay.ErrorCode;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = FAN1_1_RunTimeDisplay.Current;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}

void Get_FAN2_RunTime_SendPacket(void)
{
    UART1TxBuffer[0] = Android_HMI_FAN2_RunTime_CommandEnum;
    U1_SendingWord.WordData = FAN2_RunTimeDisplay.Current;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = FAN2_RunTimeDisplay.SV;//Maybe delete later
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = FAN2_RunTimeDisplay.RealSpeed;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = FAN2_RunTimeDisplay.ErrorCode;
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}

void Get_MTR4_RunTime_SendPacket(void)
{
    UART1TxBuffer[0] = Android_HMI_MTR4_RunTime_CommandEnum;
    U1_SendingWord.WordData = MTR4_RunTimeDisplay.ErrorCode;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = MTR4_RunTimeDisplay.Current;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = MTR4_RunTimeDisplay.RealFreq;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
//Philip 20220414 0.0.1 ========================================================    
//    U1_SendingWord.WordData = MTR4_RunTimeDisplay.RPH;//Maybe delete later
    UART1TxBuffer[7] = ioStatus.ByteData[2];//U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = ioStatus.ByteData[3];//U1_SendingWord.Byte[1];
//Philip 20220414 0.0.1 ========================================================    
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}

void Get_Input_Heater_RunTime_SendPacket(void)//Philip 20220406 0.0.1
{
    UART1TxBuffer[0] = Android_HMI_Heater_RunTime_CommandEnum;
    U1_SendingWord.WordData = HEATER_RunTimeDisplay.RealOutputPercent;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = HEATER_RunTimeDisplay.OvenSP;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = HEATER_RunTimeDisplay.OvenSV;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
//Philip 20220406 0.0.1 =============================================
    U1_SendingWord.WordData = 0;//Gas
    UART1TxBuffer[7] = U1_SendingWord.Byte[0];
    UART1TxBuffer[8] = U1_SendingWord.Byte[1];
//Philip 20220406 0.0.1 =============================================    
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}

void Get_PCD_RunTime_SendPacket(void)
{   
    UART1TxBuffer[0] = Android_HMI_PCD_RunTime_CommandEnum;
    U1_SendingWord.WordData = PCD20_RunTimeDisplay.RealOpenSize;
    UART1TxBuffer[1] = U1_SendingWord.Byte[0];
    UART1TxBuffer[2] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = OtherRunTimeDisplay.PCD22_RealOpenSize;
    UART1TxBuffer[3] = U1_SendingWord.Byte[0];
    UART1TxBuffer[4] = U1_SendingWord.Byte[1];
    U1_SendingWord.WordData = OtherRunTimeDisplay.PCD25_RealOpenSize;
    UART1TxBuffer[5] = U1_SendingWord.Byte[0];
    UART1TxBuffer[6] = U1_SendingWord.Byte[1];
//Philip 20220406 0.0.1 =============================================
    UART1TxBuffer[7] = ioStatus.ByteData[0];
    UART1TxBuffer[8] = ioStatus.ByteData[1];
//Philip 20220406 0.0.1 ============================================= 
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}

void Get_UsingRecord_RunTime_SendPacket(void)
{   
    UART1TxBuffer[0] = Android_HMI_UsingCount_RunTime_CommandEnum;
    U1_SendingWord2.value = RunTimeStatus.UsingCount;
    UART1TxBuffer[1] = U1_SendingWord2.data[0];
    UART1TxBuffer[2] = U1_SendingWord2.data[1];
    UART1TxBuffer[3] = U1_SendingWord2.data[2];
    UART1TxBuffer[4] = U1_SendingWord2.data[3];
    U1_SendingWord2.value = RunTimeStatus.UsingHours;
    UART1TxBuffer[5] = U1_SendingWord2.data[0];
    UART1TxBuffer[6] = U1_SendingWord2.data[1];
    UART1TxBuffer[7] = U1_SendingWord2.data[2];
    UART1TxBuffer[8] = U1_SendingWord2.data[3];
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}
//Philip 20220124 0.0.1 ====================================================================

//Philip 20220406 0.0.1 =====================================================================
void Get_AlarmStatus_RunTime_SendPacket(unsigned char flag) 
//flag == 0 : Android_HMI_Alarm_RunTime_CommandEnum,
//flag == 1 : Android_HMI_Alarm1_RunTime_CommandEnum
{   
    unsigned char i;
//Philip 20220526 0.0.1 =====================================================================    
    switch(flag)
    {
        case 0 :
            UART1TxBuffer[0] = Android_HMI_Alarm_RunTime_CommandEnum;
            for(i=0;i<8;i++)
                UART1TxBuffer[i+1] = alarmStatus.ByteData[i];
            break;
        case 1 :
            UART1TxBuffer[0] = Android_HMI_Alarm1_RunTime_CommandEnum;
            for(i=0;i<8;i++)
                UART1TxBuffer[i+1] = alarmStatus.ByteData[i+8];
            break;
    }    
//Philip 20220526 0.0.1 =====================================================================    
    
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}
//Philip 20220406 0.0.1 =====================================================================

//Philip 20220510 0.0.1 =====================================================================
_SYSTEM_RUNTIME_STATUS SystemRunTimeStatus;
void Get_SystemStatus_RunTime_SendPacket(void)
{   
    unsigned char i;
    
    UART1TxBuffer[0] = Android_HMI_SystemStatus_RunTime_CommandEnum;
    SystemRunTimeStatus.Value.AutoGasIn = RunTimeStatus.AutoGasIn;
//Philip 20220525 0.0.1 ====================================================================    
    SystemRunTimeStatus.Value.FAN1_1_PID_ON = RunTimeStatus.FAN1_1_PID_ON;
    SystemRunTimeStatus.Value.FAN1_1_PID_Auto = RunTimeStatus.FAN1_1_PID_Auto;
    SystemRunTimeStatus.Value.PCD20_PID_Auto = RunTimeStatus.PCD20_PID_Auto;
    SystemRunTimeStatus.Value.Heater_PID_Auto = RunTimeStatus.Heater_PID_Auto;
//Philip 20220525 0.0.1 ====================================================================    
    for(i=0;i<8;i++)
        UART1TxBuffer[i+1] = SystemRunTimeStatus.ByteData[i];
    
    U1_SendingWord.WordData = CRC_CREATE(UART1TxBuffer, 9);
    UART1TxBuffer[9] = U1_SendingWord.Byte[1];
    UART1TxBuffer[10] = U1_SendingWord.Byte[0];    
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE; 
}
//Philip 20220510 0.0.1 =====================================================================

unsigned char RoutineSendIndex=0;
void RoutineSendingProcess(void)
{
    switch(RoutineSendIndex)
    {
        case 0 :
            Get_TE1_3_5_6_SendPacket();
            RoutineSendIndex = 1;
            break;
        case 1 :
            Get_TE8_10_11_12_SendPacket();
            RoutineSendIndex = 2;
            break;
        case 2 :
            Get_PDT1_2_3_SendPacket();          
            RoutineSendIndex = 3;
            break;
        case 3 :
            Get_FAN1_RunTime_SendPacket();
            RoutineSendIndex = 4;
            break;
        case 4 :
            Get_FAN2_RunTime_SendPacket();
            RoutineSendIndex = 5;
            break;
        case 5 :
            Get_MTR4_RunTime_SendPacket();
            RoutineSendIndex = 6;
            break;
        case 6 :
            Get_Input_Heater_RunTime_SendPacket();
            RoutineSendIndex = 7;
            break;
        case 7 :
            Get_PCD_RunTime_SendPacket();
            RoutineSendIndex = 8;
            break;
        case 8 :
            Get_UsingRecord_RunTime_SendPacket();
            RoutineSendIndex = 9;
            break;          
        case 9 :            
            Get_AlarmStatus_RunTime_SendPacket(0);
            RoutineSendIndex = 10;
            break;   
        case 10 :
            Get_SystemStatus_RunTime_SendPacket();
            RoutineSendIndex = 11;
            break;       
        case 11 :            
            Get_AlarmStatus_RunTime_SendPacket(1);
            RoutineSendIndex = 0;
            break;            
        default :
            Get_TE1_3_5_6_SendPacket();
            RoutineSendIndex = 1;
            break;          
    }    
}

void ResponseSendingProcess(void)
{
    U1SendDataCount = 0;
    U1PacketLen = UART1_PACKET_SIZE;
}

enum Android_HMI_SendStateEnum
{
    Wait_Android_HMI_StartSendStateEnum=0,
    Android_HMI_StartSendStateEnum,
    Wait_Android_HMI_FinishSendStateEnum,
    
    Android_HMI_SendStateEnumEnd
};

unsigned char Android_HMI_SendState = Wait_Android_HMI_StartSendStateEnum;
void Android_HMI_SendingControl(void)
{
    switch(Android_HMI_SendState)
    {
        case Wait_Android_HMI_StartSendStateEnum :
            if( DelayTimerCounter[UART1_SendingDelayEnum] == 0 )
                Android_HMI_SendState = Android_HMI_StartSendStateEnum;
            break;
        case Android_HMI_StartSendStateEnum :
            if( RoutineSendFlag == 1 ) 
                RoutineSendingProcess(); //Isen：傳送11組Unit錶頭數值至UART1_TX_Buffer
            else
            {
//                ResponseSendingProcess(); //Isen：若RoutineSendFlag不為1，則執行這段函式，但因為只有2行，故將其搬移至此，讓Code保持直觀好閱讀
                U1SendDataCount = 0; //Isen：若RoutineSendFlag不為1，則清空 U1SendDataCount
                U1PacketLen = UART1_PACKET_SIZE; //Isen：若RoutineSendFlag不為1，則賦值給 U1PacketLen 準備傳送至TX
                RoutineSendFlag = 1;
            }
            Android_HMI_SendState = Wait_Android_HMI_FinishSendStateEnum;
            break;
        case Wait_Android_HMI_FinishSendStateEnum :
            if( ( U1SendDataCount >= U1PacketLen) && (U1PacketLen > 0) )
            {
                DelayTimerCounter[UART1_SendingDelayEnum] = 200; //Isen：這裡定義UART1_Sending的間隔時間，若以5ms的速度來計算，則為每100ms傳送一筆
                Android_HMI_SendState = Wait_Android_HMI_StartSendStateEnum;
            }
            break;
    }
}
