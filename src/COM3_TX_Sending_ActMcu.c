/*
 * File:   COM3_TX_ToKeyboard.c
 * Author: user
 *
 * Created on 2019年10月30日, 下午 6:29
 */
#include "..\h\Global_define.h"
#include "..\h\SystemControl.h"
#include "..\h\COM3_Command.h"
#include "UART_Driver.h"

#define COM3_NEXT_TX_DELAY_TIME 10
#define COM3_TX_RETRY_DELAY_TIME 20
#define MAX_COM3_RETRY_COUNT 3
#define COM3_MAX_RETRY_COUNT 3
#define COM3_NEXT_TX_PACKET_DELAY 30
#define COM3_MAX_SENDING_COMMAND_BUFFER_SIZE 50

extern unsigned int CRC_CREATE(unsigned char *data, unsigned char lenth);
extern unsigned char IsReadEEPROM_DataFinish(void);
extern unsigned char IsCOM3_TX_Busy(void);
extern void Get_ExtControllerFirmware(void);

extern _SYSTEM_RUNTIME_STATUS SystemRunTimeStatus;
extern _SYSTEM_PARAMETER SystemParameter;
extern _RUNTIME_STATUS RunTimeStatus;
extern _HMI_BUTTON_STATUS HMI_BtnStatus;
extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
extern unsigned char UART3TxBuffer[UART3_BUFFER_SIZE];
extern unsigned char UART3RxBuffer[UART3_BUFFER_SIZE];
extern unsigned int UART3TimeOutCount, UART3RxBufCount, U3SendDataCount, U3PacketLen;

enum COM3_SendControlStateEnum
{
    COM3_WaitStartSendControlStateEnum=0,

    COM3_SendStateEnum,
    COM3_WaitFinishSendStateEnum,
    COM3_WaitNextSendStateEnum,
      
    COM3_SendControlStateEnumEnd
};

_SENDING_DATA SendingData;
unsigned char COM3_SendControlState =COM3_WaitStartSendControlStateEnum;
unsigned char COM3_SendCommandBuffer[COM3_MAX_SENDING_COMMAND_BUFFER_SIZE];
unsigned char COM3_SendButtonCommandBuffer[COM3_MAX_SENDING_COMMAND_BUFFER_SIZE];
unsigned char COM3_SendIndex=0, COM3_SendCommandBufferWrite=0, COM3_SendCommandBufferSize=0;
unsigned char COM3_TxRetryCount=0;

void Register_COM3_Send_ButtonCommand(unsigned char cmd, unsigned char ButtonId)
{
    COM3_SendCommandBuffer[COM3_SendCommandBufferWrite] = cmd;
    COM3_SendButtonCommandBuffer[COM3_SendCommandBufferWrite] = ButtonId;
    COM3_SendCommandBufferSize++;
    COM3_SendCommandBufferWrite++;
    if( COM3_SendCommandBufferWrite >= COM3_MAX_SENDING_COMMAND_BUFFER_SIZE )
        COM3_SendCommandBufferWrite = 0;
}

void Register_COM3_Send_Command(unsigned char cmd)
{
    COM3_SendCommandBuffer[COM3_SendCommandBufferWrite] = cmd;
    COM3_SendCommandBufferSize++;
    COM3_SendCommandBufferWrite++;
    if( COM3_SendCommandBufferWrite >= COM3_MAX_SENDING_COMMAND_BUFFER_SIZE )
        COM3_SendCommandBufferWrite = 0;
}

void COM3_Send_All_Command(void)
{
    unsigned char i;
    
    for(i=COM3_TxSet_FAN1_Parameter1_Command_Enum;i<COM3_last_TxSet_Command_Enum;i++)
        Register_COM3_Send_Command(i);
   
    Register_COM3_Send_Command(COM3_Button_Status_Command_Enum);//Philip 20220530 0.0.1 
}

//Isen：20231020新增
void SendFunctionResetControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_System_Function_RESET_Enum);
}

//Isen：20231020新增
void SendAlarmLED_ONOFFControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_AlarmLED_STATE_SET_Enum);
}

//Isen：20231020新增
void SendFaultLED_ONOFFControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_FaultLED_STATE_SET_Enum);
}

void SendFaultResetControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_SetFaultResetEnum);
}

void SendMTR4MaualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_RotatorManualControlEnum);
}
void SendFAN1MaualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_Fan1_1ManualControlEnum);
}

void SendFAN2MaualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_Fan2ManualControlEnum);
}
void SendPCD20MaualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_PCD20ManualControlEnum);
}
void SendPCD22MaualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_PCD22ManualControlEnum);
}
void SendPCD25MaualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_PCD25ManualControlEnum);
}

void SendPCD2MaualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_PCD2ManualControlEnum);
}
void SendPCD6MaualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_PCD6ManualControlEnum);
}
void SendV21MaualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_V21ManualControlEnum);
}
void SendSystemAutoStartStopControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_SystemAutoStartStopControlEnum);
}

void SendSystemAutoGasInControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_AUTO_GAS_IN_SET_Enum);
}
void SendSystemGasInOutControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_GAS_IN_OUT_SET_Enum);
}

void SendSystemManualModeControl(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_MANUAL_MODE_SET_Enum);
}

void SendFAN1_1_PID_OnControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_FAN1_1_PID_ON_SET_Enum);
}

void SendFAN1_1_PID_AutoControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_FAN1_1_PID_AUTO_STATE_SET_Enum);
}

void SendHeater_PID_AutoControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_HEATER_PID_AUTO_STATE_SET_Enum);
}

void Send_PCD_20_PID_AutoControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_PCD_20_PID_AUTO_STATE_SET_Enum);
}

void SendSystemManualControlCommand(void)
{
    Register_COM3_Send_ButtonCommand(COM3_Button_Command_Enum, Android_HMI_MANUAL_MODE_SET_Enum);
}

void COM3_Send_FAN1_Command(void)
{
    Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter1_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter2_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter3_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter4_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_FAN1_Parameter5_Command_Enum);
}

void COM3_Send_FAN2_Command(void)
{
    Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter1_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_FAN2_Parameter2_Command_Enum);
}

void COM3_Send_MTR4_Command(void)
{
    Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter1_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter2_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_MTR4_Parameter3_Command_Enum);
}

void COM3_Send_PCD20_Command(void)
{
    Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter1_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter2_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter3_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_PCD20_Parameter4_Command_Enum);
}

void COM3_Send_PCD22_Command(void)
{
    Register_COM3_Send_Command(COM3_TxSet_PCD22_Parameter_Command_Enum);
}

void COM3_Send_PCD25_Command(void)
{
    Register_COM3_Send_Command(COM3_TxSet_PCD25_Parameter1_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_PCD25_Parameter2_Command_Enum);
}

void COM3_Send_Heater_Command(void)
{
    Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter1_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter2_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter3_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter4_Command_Enum);
    Register_COM3_Send_Command(COM3_TxSet_Heater_Parameter5_Command_Enum);
}            

void CheckSendingAck(void)
{
    if( UART3RxBuffer[COM3_PacketCommandItemEnum] == COM3_SendCommandBuffer[COM3_SendIndex] )
    {
        Get_ExtControllerFirmware();
        if( COM3_SendCommandBufferSize > 0 )
        {
            COM3_TxRetryCount = 0;
            COM3_SendCommandBufferSize--;
            COM3_SendCommandBuffer[COM3_SendIndex] = COM3_TxNOP_Command_Enum;
            COM3_SendIndex++;
            if( COM3_SendIndex >= COM3_MAX_SENDING_COMMAND_BUFFER_SIZE )
                COM3_SendIndex = 0;
        }
    }
}

void COM3_TxRotatorManual_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_RotatorManualControlEnum;
    if( HMI_BtnStatus.MTR4ManualOpenBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.MTR4ManualOpenBtn = 0;
    }
    else if( HMI_BtnStatus.MTR4ManualCloseBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.MTR4ManualCloseBtn = 0;
    }
}

void COM3_TxFAN1_Manual_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_Fan1_1ManualControlEnum;
    if( HMI_BtnStatus.FAN1ManualOpenBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.FAN1ManualOpenBtn = 0;
    }
    else if( HMI_BtnStatus.FAN1ManualCloseBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.FAN1ManualCloseBtn = 0;
    }
}

void COM3_TxFAN2_Manual_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_Fan2ManualControlEnum;
    if( HMI_BtnStatus.FAN2ManualOpenBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.FAN2ManualOpenBtn = 0;
    }
    else if( HMI_BtnStatus.FAN2ManualCloseBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.FAN2ManualCloseBtn = 0;
    }
}

void COM3_TxPCD20_Manual_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_PCD20ManualControlEnum;
    if( HMI_BtnStatus.PCD20ManualOpenBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.PCD20ManualOpenBtn = 0;
    }
    else if( HMI_BtnStatus.PCD20ManualCloseBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.PCD20ManualCloseBtn = 0;
    }
}

void COM3_TxPCD22_Manual_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_PCD22ManualControlEnum;
    if( HMI_BtnStatus.PCD22ManualOpenBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.PCD22ManualOpenBtn = 0;
    }
    else if( HMI_BtnStatus.PCD22ManualCloseBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.PCD22ManualCloseBtn = 0;
    }
}

void COM3_TxPCD25_Manual_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_PCD25ManualControlEnum;
    if( HMI_BtnStatus.PCD25ManualOpenBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.PCD25ManualOpenBtn = 0;
    }
    else if( HMI_BtnStatus.PCD25ManualCloseBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.PCD25ManualCloseBtn = 0;
    }
}

void COM3_TxPCD2_Manual_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_PCD2ManualControlEnum;
    if( HMI_BtnStatus.PCD2ManualOpenBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.PCD2ManualOpenBtn = 0;
    }
    else if( HMI_BtnStatus.PCD2ManualCloseBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.PCD2ManualCloseBtn = 0;
    }
}

void COM3_TxPCD6_Manual_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_PCD6ManualControlEnum;
    if( HMI_BtnStatus.PCD6ManualOpenBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.PCD6ManualOpenBtn = 0;
    }
    else if( HMI_BtnStatus.PCD6ManualCloseBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.PCD6ManualCloseBtn = 0;
    }
}

void COM3_TxV21_Manual_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_V21ManualControlEnum;
    if( HMI_BtnStatus.V21ManualOpenBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.V21ManualOpenBtn = 0;
    }
    else if( HMI_BtnStatus.V21ManualCloseBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.V21ManualCloseBtn = 0;
    }
}

void COM3_SystemAutoStartStop_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_SystemAutoStartStopControlEnum;
    if( HMI_BtnStatus.SystemAutoStartBtn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.SystemAutoStartBtn = 0;
    }
    else if( HMI_BtnStatus.SystemAutoStopBtn == 1 )
    {
        UART3TxBuffer[2] = 0x01;
        HMI_BtnStatus.SystemAutoStopBtn = 0;
    }    
}

void COM3_AutoGasInControl(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_AUTO_GAS_IN_SET_Enum;
    UART3TxBuffer[2] = SystemRunTimeStatus.ByteData[0];
}

void COM3_GasInOutControl(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_GAS_IN_OUT_SET_Enum;
    UART3TxBuffer[2] = SystemRunTimeStatus.ByteData[0];
}

void COM3_SystemManualControl(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_MANUAL_MODE_SET_Enum;
    UART3TxBuffer[2] = SystemRunTimeStatus.ByteData[0];    
}

void COM3_FAN1_1_PID_OnControl(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_FAN1_1_PID_ON_SET_Enum;
    UART3TxBuffer[2] = SystemRunTimeStatus.ByteData[0];    
}

void COM3_FAN1_1_PID_AutoControl(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_FAN1_1_PID_AUTO_STATE_SET_Enum;
    UART3TxBuffer[2] = SystemRunTimeStatus.ByteData[0];    
}

void COM3_Heater_PID_AutoControl(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_HEATER_PID_AUTO_STATE_SET_Enum;
    UART3TxBuffer[2] = SystemRunTimeStatus.ByteData[0];    
}

void COM3_PCD_20_PID_AutoControl(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_PCD_20_PID_AUTO_STATE_SET_Enum;
    UART3TxBuffer[2] = SystemRunTimeStatus.ByteData[0];    
}

//20231020，Isen：Sys-OP操作功能統一集中在此處
void COM3_SystemFaultReset_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_SetFaultResetEnum;
}
//20231020，Isen：新增
void COM3_FunctionReset_Control(void)
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_System_Function_RESET_Enum;
    if( HMI_BtnStatus.FunctionResetBtn == 1 ) //Isen：20230703僅需Pulse一次的按鈕功能。
    {
        UART3TxBuffer[2] = 0x02;
        HMI_BtnStatus.FunctionResetBtn = 0;
    } 
}
//20231020，Isen：新增
void COM3_AlarmLED_ONOFFControl(void)//Isen：20231020，於COM1_Parsing處理並記憶RunTime狀態後，由此處發送給MCU2
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum;
    UART3TxBuffer[1] = Android_HMI_AlarmLED_STATE_SET_Enum; 
    if( SystemRunTimeStatus.Value.AlarmLEDOn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
    }
    else
    {
        UART3TxBuffer[2] = 0x01;
    }
}
//20231020，Isen：新增
void COM3_FaultLED_ONOFFControl(void)//Isen：20231020，於COM1_Parsing處理並記憶RunTime狀態後，由此處發送給MCU2
{
    UART3TxBuffer[0] = COM3_Button_Command_Enum; 
    UART3TxBuffer[1] = Android_HMI_FaultLED_STATE_SET_Enum; 
    if( SystemRunTimeStatus.Value.FaultLEDOn == 1 )
    {
        UART3TxBuffer[2] = 0x02;
    }
    else
    {
        UART3TxBuffer[2] = 0x01;
    }
}

void COM3_Send_ButtonStatus(void)
{
    UART3TxBuffer[0] = COM3_Button_Status_Command_Enum;
    UART3TxBuffer[1] = SystemRunTimeStatus.ByteData[0];
}

void COM3_TxSet_FAN1_Parameter(void)
{
    unsigned char i, id;
    
    id = COM3_SendCommandBuffer[COM3_SendIndex] - COM3_TxSet_FAN1_Parameter1_Command_Enum;
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    switch(id)
    {
        case 0 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.FAN1_1.Byte[i];
            break;
        case 1 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.FAN1_1.Byte[i+8];            
            break;
        case 2 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.FAN1_1.Byte[i+16];                  
            break;
        case 3 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.FAN1_1.Byte[i+24];                  
            break;
        case 4 :
            UART3TxBuffer[1] = SystemParameter.FAN1_1.Byte[32];
            UART3TxBuffer[2] = SystemParameter.FAN1_1.Byte[33];
            for(i=2;i<8;i++)
                UART3TxBuffer[i+1] = 0;         
            break;
    }
}

void COM3_TxSet_FAN2_Parameter(void)
{
    unsigned char i, id;
    
    id = COM3_SendCommandBuffer[COM3_SendIndex] - COM3_TxSet_FAN2_Parameter1_Command_Enum;
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    switch(id)
    {
        case 0 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.FAN_2.Byte[i];
            break;
        case 1 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.FAN_2.Byte[i+8];            
            break;         
    }
    
}

void COM3_TxSet_MTR4_Parameter(void)
{
    unsigned char i, id;
    
    id = COM3_SendCommandBuffer[COM3_SendIndex] - COM3_TxSet_MTR4_Parameter1_Command_Enum;
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    switch(id)
    {
        case 0 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.Wheel.Byte[i];
            break;
        case 1 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.Wheel.Byte[i+8];
            break;
        case 2 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.Wheel.Byte[i+16];
            break;                
    }
}

void COM3_TxSet_PCD20_Parameter(void)
{
    unsigned char i, id;
    
    id = COM3_SendCommandBuffer[COM3_SendIndex] - COM3_TxSet_PCD20_Parameter1_Command_Enum;
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    switch(id)
    {
        case 0 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.PCD_20.Byte[i];
            break;
        case 1 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.PCD_20.Byte[i+8];
            break;
        case 2 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.PCD_20.Byte[i+16];
            break;  
        case 3 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.PCD_20.Byte[i+24];            
            break;
    }
}

void COM3_TxSet_PCD22_Parameter(void)
{
    unsigned char i;
    
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    for(i=0;i<8;i++)
        UART3TxBuffer[i+1] = SystemParameter.PCD_22.Byte[i];
}

void COM3_TxSet_PCD25_Parameter(void)
{
    unsigned char i, id;
    
    id = COM3_SendCommandBuffer[COM3_SendIndex] - COM3_TxSet_PCD25_Parameter1_Command_Enum;
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    switch(id)
    {
        case 0 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.PCD_25.Byte[i];
            break;
        case 1 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.PCD_25.Byte[i+8];
            break;
    }
}

void COM3_TxSet_Heater_Parameter(void)
{
    unsigned char i, id;
    
    id = COM3_SendCommandBuffer[COM3_SendIndex] - COM3_TxSet_Heater_Parameter1_Command_Enum;
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    switch(id)
    {
        case 0 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.HeaterSet.Byte[i];
            break;
        case 1 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.HeaterSet.Byte[i+8];
            break;
        case 2 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.HeaterSet.Byte[i+16];
            break;
        case 3 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.HeaterSet.Byte[i+24];
            break;
        case 4 :
            for(i=0;i<8;i++)
                UART3TxBuffer[i+1] = SystemParameter.HeaterSet.Byte[i+32];
            break;            
    }
}

void COM3_TxSet_PCD2_PCD6_Parameter(void)
{
    unsigned char i;
    
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    for(i=0;i<4;i++)
    {
        UART3TxBuffer[i+1] = SystemParameter.PCD2.ByteData[i];
        UART3TxBuffer[i+5] = SystemParameter.PCD_6.ByteData[i];
    }
}

void COM3_TxSet_V21_Parameter(void)
{
    unsigned char i;
    
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    for(i=0;i<4;i++)
        UART3TxBuffer[i+1] = SystemParameter.V21.ByteData[i];
}

void COM3_TxSet_Alarm_Parameter(void)
{
    unsigned char i, offset;
    
    offset = (COM3_SendCommandBuffer[COM3_SendIndex] - COM3_RxSetAlarm_Parameter1_CommandEnum) * 8;
    UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex];
    for(i=0;i<8;i++)
        UART3TxBuffer[i+1] = SystemParameter.Alarm.ByteData[i+offset];
    
    /*
     * 這段程式碼是設定某種警報參數的功能。首先，它從一個命令緩衝區(COM3_SendCommandBuffer)中讀取一個命令，
     * 然後基於該命令計算一個偏移量(offset)。然後它將該命令放入UART3TxBuffer的第一個位置，接著透過一個迴圈來填充UART3TxBuffer中的剩餘部分。
     * 每一個元素都是從系統參數(SystemParameter.Alarm.ByteData)中相應的偏移量位置獲取的。
     * 解析每行代碼：
     * unsigned char i, offset; 定義兩個無符號字符變量i和offset。
     * offset = (COM3_SendCommandBuffer[COM3_SendIndex] - COM3_RxSetAlarm_Parameter1_CommandEnum) * 8; 從COM3_SendCommandBuffer中讀取一個命令，並計算出一個偏移量。
     * UART3TxBuffer[0] = COM3_SendCommandBuffer[COM3_SendIndex]; 將讀取的命令放入UART3TxBuffer的第一個位置。
     * for(i=0;i<8;i++) 這是一個for迴圈，用於逐個填充UART3TxBuffer中的元素。
        * UART3TxBuffer[i+1] = SystemParameter.Alarm.ByteData[i+offset]; 在每次迴圈中，將UART3TxBuffer的下一個元素設置為SystemParameter.Alarm.ByteData的對應偏移量位置的值。
        * 這段程式碼的主要目的是將特定的警報參數放入UART3TxBuffer中，以便在某種通信協議中使用。
        */
}

void COM3_TxRequestFirmwareVersionCommand(void)
{
    unsigned char i;
    
    UART3TxBuffer[0] = COM3_TxRequestFirmwareVersionCommand_Enum;
    for(i=0;i<8;i++)
        UART3TxBuffer[i+1] = 0;
}

void Send_Button_Command(unsigned char id)
{
    switch(id)
    {
        case Android_HMI_RotatorManualControlEnum :
            COM3_TxRotatorManual_Control();
            break;
        case Android_HMI_Fan1_1ManualControlEnum :
            COM3_TxFAN1_Manual_Control();
            break;
        case Android_HMI_Fan2ManualControlEnum :
            COM3_TxFAN2_Manual_Control();
            break;
        case Android_HMI_PCD20ManualControlEnum :
            COM3_TxPCD20_Manual_Control();
            break;
        case Android_HMI_PCD22ManualControlEnum :
            COM3_TxPCD22_Manual_Control();
            break;
        case Android_HMI_PCD25ManualControlEnum :
            COM3_TxPCD25_Manual_Control();
            break;
        case Android_HMI_PCD2ManualControlEnum :
            COM3_TxPCD2_Manual_Control();
            break;
        case Android_HMI_PCD6ManualControlEnum :
            COM3_TxPCD6_Manual_Control();
            break;
        case Android_HMI_V21ManualControlEnum :
            COM3_TxV21_Manual_Control();
            break;
        case Android_HMI_SystemAutoStartStopControlEnum :
            COM3_SystemAutoStartStop_Control();
            break;       
        case Android_HMI_SetFaultResetEnum :
            COM3_SystemFaultReset_Control();
            break;
        case Android_HMI_AUTO_GAS_IN_SET_Enum :
            COM3_AutoGasInControl();
            break;
        case Android_HMI_GAS_IN_OUT_SET_Enum :
            COM3_GasInOutControl();
            break;
        case Android_HMI_MANUAL_MODE_SET_Enum :
            COM3_SystemManualControl();
            break;            
        case Android_HMI_FAN1_1_PID_ON_SET_Enum :
            COM3_FAN1_1_PID_OnControl();
            break;
        case Android_HMI_FAN1_1_PID_AUTO_STATE_SET_Enum :
            COM3_FAN1_1_PID_AutoControl();
            break;
        case Android_HMI_HEATER_PID_AUTO_STATE_SET_Enum :
            COM3_Heater_PID_AutoControl();
            break;
        case Android_HMI_PCD_20_PID_AUTO_STATE_SET_Enum :
            COM3_PCD_20_PID_AutoControl();
            break; 
        case Android_HMI_System_Function_RESET_Enum ://Isen：20231020新增
            COM3_FunctionReset_Control();
            break; 
        case Android_HMI_FaultLED_STATE_SET_Enum ://Isen：20231020新增
            COM3_FaultLED_ONOFFControl();
            break; 
        case Android_HMI_AlarmLED_STATE_SET_Enum ://Isen：20231020新增
            COM3_AlarmLED_ONOFFControl();
            break;
    }
}

void COM3_CreateCRC(void)
{
    unsigned int crc_data;
    
    crc_data = CRC_CREATE(UART3TxBuffer, (UART3_PACKET_SIZE - 2));
    UART3TxBuffer[UART3_PACKET_SIZE - 2] = (crc_data >> 8) & 0x00FF;
    UART3TxBuffer[UART3_PACKET_SIZE - 1] = (crc_data & 0x00FF);    
    
    U3SendDataCount = 0;
    U3PacketLen = UART3_PACKET_SIZE;        
}

void COM3_SendingCommandControl(void)
{
    if( COM3_SendCommandBufferSize > 0 )
    {
        COM3_SendControlState = COM3_WaitFinishSendStateEnum;
        COM3_TxRetryCount++;
        if( COM3_TxRetryCount > COM3_MAX_RETRY_COUNT )
        {
            //Show Fault
            COM3_TxRetryCount = 0;
            COM3_SendCommandBufferSize--;
            COM3_SendCommandBuffer[COM3_SendIndex] = COM3_TxNOP_Command_Enum;
            COM3_SendIndex++;
            if( COM3_SendIndex >= COM3_MAX_SENDING_COMMAND_BUFFER_SIZE )
                COM3_SendIndex = 0;            
        }

        switch(COM3_SendCommandBuffer[COM3_SendIndex])
        {
            case COM3_TxSet_FAN1_Parameter1_Command_Enum :
            case COM3_TxSet_FAN1_Parameter2_Command_Enum :
            case COM3_TxSet_FAN1_Parameter3_Command_Enum :
            case COM3_TxSet_FAN1_Parameter4_Command_Enum :
            case COM3_TxSet_FAN1_Parameter5_Command_Enum :
                COM3_TxSet_FAN1_Parameter();
                COM3_CreateCRC();                
                break;
            case COM3_TxSet_FAN2_Parameter1_Command_Enum :
            case COM3_TxSet_FAN2_Parameter2_Command_Enum :
                COM3_TxSet_FAN2_Parameter();
                COM3_CreateCRC();
                break;
            case COM3_TxSet_MTR4_Parameter1_Command_Enum :
            case COM3_TxSet_MTR4_Parameter2_Command_Enum :
            case COM3_TxSet_MTR4_Parameter3_Command_Enum :
                COM3_TxSet_MTR4_Parameter();
                COM3_CreateCRC();
                break;
            case COM3_TxSet_PCD20_Parameter1_Command_Enum :
            case COM3_TxSet_PCD20_Parameter2_Command_Enum :                
            case COM3_TxSet_PCD20_Parameter3_Command_Enum :
            case COM3_TxSet_PCD20_Parameter4_Command_Enum :
                COM3_TxSet_PCD20_Parameter();
                COM3_CreateCRC();
                break;
            case COM3_TxSet_PCD22_Parameter_Command_Enum :
                COM3_TxSet_PCD22_Parameter();
                COM3_CreateCRC();
                break;
            case COM3_TxSet_PCD25_Parameter1_Command_Enum :
            case COM3_TxSet_PCD25_Parameter2_Command_Enum :
                COM3_TxSet_PCD25_Parameter();
                COM3_CreateCRC();
                break;
            case COM3_RxSet_PCD2_PCD6_Parameter_Command_Enum :
                COM3_TxSet_PCD2_PCD6_Parameter();
                COM3_CreateCRC();
                break;
            case COM3_RxSet_V21_Parameter_Command_Enum :
                COM3_TxSet_V21_Parameter();
                COM3_CreateCRC();
                break;
            case COM3_RxSetAlarm_Parameter1_CommandEnum :
            case COM3_RxSetAlarm_Parameter2_CommandEnum :
            case COM3_RxSetAlarm_Parameter3_CommandEnum :
            case COM3_RxSetAlarm_Parameter4_CommandEnum :
            case COM3_RxSetAlarm_Parameter5_CommandEnum :
            case COM3_RxSetAlarm_Parameter6_CommandEnum :
            case COM3_RxSetAlarm_Parameter7_CommandEnum :
            case COM3_RxSetAlarm_Parameter8_CommandEnum :
            case COM3_RxSetAlarm_Parameter9_CommandEnum :
            case COM3_RxSetAlarm_Parameter10_CommandEnum :
            case COM3_RxSetAlarm_Parameter11_CommandEnum :
            case COM3_RxSetAlarm_Parameter12_CommandEnum :                
                COM3_TxSet_Alarm_Parameter();
                COM3_CreateCRC();
                break;                          
            case COM3_TxSet_Heater_Parameter1_Command_Enum :
            case COM3_TxSet_Heater_Parameter2_Command_Enum :
            case COM3_TxSet_Heater_Parameter3_Command_Enum :
            case COM3_TxSet_Heater_Parameter4_Command_Enum :
            case COM3_TxSet_Heater_Parameter5_Command_Enum :
                COM3_TxSet_Heater_Parameter();
                COM3_CreateCRC();
                break;
            case COM3_TxRequestFirmwareVersionCommand_Enum :
                COM3_TxRequestFirmwareVersionCommand();
                COM3_CreateCRC();
                break;
            case COM3_Button_Status_Command_Enum :
                COM3_Send_ButtonStatus();
                COM3_CreateCRC();
                break;
            case COM3_Button_Command_Enum :
                Send_Button_Command(COM3_SendButtonCommandBuffer[COM3_SendIndex]);
                COM3_CreateCRC();
                break;              
            default :
                if( COM3_SendCommandBufferSize > 0 )
                {
                    COM3_SendCommandBufferSize--;
                    COM3_SendCommandBuffer[COM3_SendIndex] = COM3_TxNOP_Command_Enum;
                    COM3_SendIndex++;
                    if( COM3_SendIndex >= COM3_MAX_SENDING_COMMAND_BUFFER_SIZE )
                        COM3_SendIndex = 0;                  
                }
                COM3_SendControlState = COM3_WaitStartSendControlStateEnum;
                break;
        }        
    }
    else
        COM3_SendControlState = COM3_WaitStartSendControlStateEnum;
}

void COM3_SendControl(void)
{
    switch(COM3_SendControlState)
    {
        case COM3_WaitStartSendControlStateEnum :
            if( COM3_SendCommandBufferSize > 0 )
            {
                COM3_TxRetryCount = 0;
                COM3_SendControlState = COM3_SendStateEnum;
            }
            break;
        case COM3_SendStateEnum :
            COM3_SendingCommandControl();            
            break;
        case COM3_WaitFinishSendStateEnum :
            if( (U3SendDataCount >= U3PacketLen) && (U3PacketLen > 0) )
            {
                COM3_SendControlState = COM3_WaitNextSendStateEnum;
                DelayTimerCounter[UART3_SendTimerEnum] = COM3_NEXT_TX_PACKET_DELAY;
            }
            break;
        case COM3_WaitNextSendStateEnum :
            if( DelayTimerCounter[UART3_SendTimerEnum] == 0 )
                COM3_SendControlState = COM3_SendStateEnum;  
            break;
    }
}

