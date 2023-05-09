/*
 * File:   Android_HMI_Parsing.c
 * Author: user
 *
 * Created on 2021年9月24日, 上午 9:31
 */
#include "SystemControl.h"
#include "COM3_Command.h"

extern unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];
extern _SYSTEM_PARAMETER SystemParameter;
extern _PARSING_WORD U1_SendingWord;
extern _PARSING_DATA U1_SendingWord2;
extern unsigned char RoutineSendFlag;

extern _HMI_BUTTON_STATUS HMI_BtnStatus;//Philip 20220325 0.0.1
extern _RUNTIME_STATUS RunTimeStatus;//Philip 20220510 0.0.1
extern _SYSTEM_RUNTIME_STATUS SystemRunTimeStatus;//Philip 20220510 0.0.1

extern void SaveRunTimeStatus(void);//Philip 20220510 0.0.1
extern unsigned char CRC_CHECK(unsigned char *data, unsigned char lenth ,unsigned int crc_data);
extern void SendFirmwareVersion(unsigned char flag);//flag == 0 : Firmware Version, flag == 1 : External Device Firmware Version
extern void SendFan1_1_GetSV_Response(void);
extern void SendFan1_1_GetPI_Response(void);
extern void SendFan1_1_GetD_LowLimit_Response(void);
extern void SendFan1_1_Get_TopLimit_Response(void);
extern void SendFan1_1_Get_ManualSet_Response(void);
extern void Send_GetFan2TempSetSpeedTopLimit_Response(void);
extern void Send_GetFan2SpeedSetResponse(void);
extern void Send_HeaterGetTempSetDbResponse(void);
extern void Send_Heater_Get_HH2LLSetResponse(void);
extern void Send_Heater_GetSP2LowLimitSetResponse(void);
extern void Send_Heater_GetPI_SetResponse(void);
extern void Send_Heater_GetManualSetResponse(void);
extern void Send_MTR4_GetTE5ConditionSetResponse(void);
extern void Send_MTR4_GetTE5SpeedSetResponse(void); 
extern void Send_MTR4_GetTopStopLowSetResponse(void);
extern void Send_GetPCD2_V21SetResponse(void);
extern void Send_GetPCD20_TempSizeSetResponse(void);
extern void Send_GetPCD20_PISetResponse(void);
extern void Send_GetPCD20_D_TimeSetResponse(void);
extern void Send_GetPCD20_DeadBandTopLowLimitPCD6SetResponse(void);
extern void Send_GetPCD22_SetResponse(void);
extern void Send_GetPCD25_PCD6TimeSetResponse(void);
extern void Send_GetPCD25_Limit_ManualSetResponse(void);

extern void Send_GetAlarm_A1_SetResponse(void);
extern void Send_GetAlarm_A1_A2SetResponse(void);
extern void Send_GetAlarm_A2_B_SetResponse(void);
extern void Send_GetHeaterTempAlarm_SetResponse(void);
extern void Send_GetHeaterPDTAlarm_SetResponse(void);
extern void Send_GetMTR4TempAlarm_SetResponse(void);
extern void Send_Get_MTR4TempPDTAlarm_SetResponse(void);
extern void Send_GetD_Alarm1_Set_SetResponse(void);
extern void Send_GetD_Alarm2_Set_SetResponse(void);
extern void Send_GetD_Alarm3__D1_SetResponse(void);
extern void Send_GetD1_Alarm2_Set_SetResponse(void);
extern void Send_GetD1_Alarm3_SetResponse(void);

extern void WriteFan1_1_Parameters(void);
extern void WriteFan2_Parameter(void);
extern void Write_Heater_Parameters(void);
extern void WriteMTR4_Parameter(void);
extern void WritePCD_2_6_V21_Parameter(void);
extern void WritePCD_20_Parameter(void);
extern void WritePCD_22_25_Parameter(void);
extern void Write_Alarm1_Parameter(void);
extern void Write_Alarm2_Parameter(void);
extern void Write_Alarm3_Parameter(void);
extern void Write_Alarm4_Parameter(void);
//Philip 20220325 0.0.1 ==============================================================================================
extern void SendMTR4MaualControlCommand(void);
extern void SendFAN1MaualControlCommand(void);
extern void SendFAN2MaualControlCommand(void);
extern void SendPCD20MaualControlCommand(void);
extern void SendPCD22MaualControlCommand(void);
extern void SendPCD25MaualControlCommand(void);
extern void SendSystemAutoStartStopControlCommand(void);
extern void SendV21MaualControlCommand(void);
extern void SendPCD2MaualControlCommand(void);
extern void SendPCD6MaualControlCommand(void);
//Philip 20220325 0.0.1 ==============================================================================================
extern void SendSystemResetControlCommand(void);//Philip 20220414 0.0.1

extern void Send_LoopBackResponse(void);
extern void SaveSystemParameter(unsigned int addr);
//Philip 20220530 0.0.1 ====================================================
extern void SendSystemAutoGasInControlCommand(void);
extern void SendSystemGasInOutControlCommand(void);
extern void SendSystemManualControlCommand(void);
extern void SendFAN1_1_PID_OnControlCommand(void);
extern void SendFAN1_1_PID_AutoControlCommand(void);
extern void Send_PCD_20_PID_AutoControlCommand(void);
extern void SendHeater_PID_AutoControlCommand(void);
//Philip 20220530 0.0.1 ====================================================

unsigned char COM1_Rx_Size;

void WriteParameterParsing(void)
{
    switch(UART1RxBuffer[1])
    {
        case 1 :case 2 :case 3 :case 4 :case 5 :case 6 :case 7 :case 8 :case 9 :case 10 :
        case 11 :case 12 :case 13 :case 14 :case 15 :case 16 :
            WriteFan1_1_Parameters();
            break;
        case 17 :case 18 :case 19 :case 20 :case 21 :case 22 :case 23 :case 24 :
            WriteFan2_Parameter();
            break;
        case 25 :case 26 :case 27 :case 28 :case 29 :case 30 :case 31 :case 32 :case 33 :case 34 :
        case 35 :case 36 :case 37 :case 38 :case 39 :case 40 :case 41 :case 42 :case 129 :
            Write_Heater_Parameters();
            break;
        case 43 :case 44 :case 45 :case 46 :case 47 :case 48 :case 49 :case 50 :case 51 :
            WriteMTR4_Parameter();
            break;
        case 52 :case 53 :case 54 :case 55 :case 56 :case 57 :
            WritePCD_2_6_V21_Parameter();
            break;
        case 58 :case 59 :case 60 :case 61 :case 62 :case 63 :case 64 :case 65 :case 66 :case 67 :
        case 68 :case 69 :case 70 :
            WritePCD_20_Parameter();
            break;
        case 71 :case 72 :case 73 :case 74 :case 75 :case 76 :case 77 :case 78 :case 79 :case 80 :
            WritePCD_22_25_Parameter();
            break;
        case 81 :case 82 :case 83 :case 84 :case 85 :case 86 :case 87 :case 88 :case 89 :case 90 :
            Write_Alarm1_Parameter();
            break;
        case 91 :case 92 :case 93 :case 94 :case 95 :case 96 :case 97 :case 98 :case 99 :case 100 :
            Write_Alarm2_Parameter();
            break;
        case 101 :case 102 :case 103 :case 104 :case 105 :case 106 :case 107 :case 108 :case 109 :case 110 :
        case 111 :case 112 :case 113 :case 114 :case 115 :case 116 :case 117 :case 118 :
            Write_Alarm3_Parameter();
            break;
        case 119 :case 120 :case 121 :case 122 :case 123 :case 124 :case 125 :case 126 :case 127 :case 128 :
            Write_Alarm4_Parameter();
            break;
    }
    SaveSystemParameter(SYSTEM_PARAMETER_START_ADDR);
}

//Philip 20220325 0.0.1 =========================================================================
void Android_ButtonProcess(void)
{
    switch(UART1RxBuffer[1])
    {
        case 1 ://PCD2 Open
            HMI_BtnStatus.PCD2ManualOpenBtn = 1;
            SendPCD2MaualControlCommand();
            break;
        case 2 ://PCD2 Close
            HMI_BtnStatus.PCD2ManualCloseBtn = 1;
            SendPCD2MaualControlCommand();
            break;
        case 3 ://PCD6 Open
            HMI_BtnStatus.PCD6ManualOpenBtn = 1;
            SendPCD6MaualControlCommand();
            break;
        case 4 ://PCD6 Close
            HMI_BtnStatus.PCD6ManualCloseBtn = 1;
            SendPCD6MaualControlCommand();
            break;
        case 5 ://PCD20 Open
            HMI_BtnStatus.PCD20ManualOpenBtn = 1;
            SendPCD20MaualControlCommand();
            break;
        case 6 ://PCD20 Close
            HMI_BtnStatus.PCD20ManualCloseBtn = 1;
            SendPCD20MaualControlCommand();
            break;
        case 7 ://PCD22 Open
            HMI_BtnStatus.PCD22ManualOpenBtn = 1;
            SendPCD22MaualControlCommand();
            break;
        case 8 ://PCD22 Close
            HMI_BtnStatus.PCD22ManualCloseBtn = 1;
            SendPCD22MaualControlCommand();
            break;
        case 9 ://PCD25 Open
            HMI_BtnStatus.PCD25ManualOpenBtn = 1;
            SendPCD25MaualControlCommand();
            break;
        case 10 ://PCD25 Close
            HMI_BtnStatus.PCD25ManualCloseBtn = 1;
            SendPCD25MaualControlCommand();
            break;
        case 11 ://V21 Open
            HMI_BtnStatus.V21ManualOpenBtn = 1;
            SendV21MaualControlCommand();
            break;
        case 12 ://V21 Close
            HMI_BtnStatus.V21ManualCloseBtn = 1;
            SendV21MaualControlCommand();
            break;  
        case 13 ://System Auto Start
            HMI_BtnStatus.SystemAutoStartBtn = 1;
            SendSystemAutoStartStopControlCommand();
            break;    
        case 14 ://System Auto Stop
            HMI_BtnStatus.SystemAutoStopBtn = 1;
            SendSystemAutoStartStopControlCommand();
            break;
        case 15 ://FAN1
            HMI_BtnStatus.FAN1ManualOpenBtn = 1;
            SendFAN1MaualControlCommand();
            break;
        case 16 ://FAN1
            HMI_BtnStatus.FAN1ManualCloseBtn = 1;
            SendFAN1MaualControlCommand();
            break;
        case 17 :
            HMI_BtnStatus.FAN2ManualOpenBtn = 1;
            SendFAN2MaualControlCommand();
            break;
        case 18 :
            HMI_BtnStatus.FAN2ManualCloseBtn = 1;
            SendFAN2MaualControlCommand();
            break; 
        case 19 :
            HMI_BtnStatus.MTR4ManualOpenBtn = 1;
            SendMTR4MaualControlCommand();
            break;
        case 20 :
            HMI_BtnStatus.MTR4ManualCloseBtn = 1;
            SendMTR4MaualControlCommand();
            break;  
//Philip 20220407 0.0.1 ====================================================================            
        case 21 ://SystemReset
            SendSystemResetControlCommand();//Philip 20220414 0.0.1
            break;
//Philip 20220407 0.0.1 ====================================================================

//Philip 20220510 0.0.1 ==================================================================== 
        case 22 ://Gas In Type Select
            RunTimeStatus.AutoGasIn = ~RunTimeStatus.AutoGasIn;
            SystemRunTimeStatus.Value.AutoGasIn = RunTimeStatus.AutoGasIn;//Philip 20220527 0.0.1
            SystemRunTimeStatus.Value.GasIn = 0;
            SystemRunTimeStatus.Value.GasOut = 0;
            SendSystemAutoGasInControlCommand();//Philip 20220530 0.0.1
            SaveRunTimeStatus();
            break;
        case 23 ://Gas In Button
            SystemRunTimeStatus.Value.GasIn = 1;
            SystemRunTimeStatus.Value.GasOut = 0;
            SendSystemGasInOutControlCommand();//Philip 20220530 0.0.1
            break;
        case 24 ://Gas Out Button
            SystemRunTimeStatus.Value.GasIn = 0;
            SystemRunTimeStatus.Value.GasOut = 1;
            SendSystemGasInOutControlCommand();//Philip 20220530 0.0.1
            break; 
//Philip 20220510 0.0.1 ====================================================================
            
//Philip 20220525 0.0.1 ====================================================================
        case 25 ://FAN1_1_PID_ON
            RunTimeStatus.FAN1_1_PID_ON = ~RunTimeStatus.FAN1_1_PID_ON;//Philip 20220526 0.0.1
            SystemRunTimeStatus.Value.FAN1_1_PID_ON = RunTimeStatus.FAN1_1_PID_ON;
            SaveRunTimeStatus();
            SendFAN1_1_PID_OnControlCommand();//Philip 20220530 0.0.1
            break;
        case 26 ://FAN1_1_PID_Auto
            if( RunTimeStatus.FAN1_1_PID_ON == 1 )
            {
                RunTimeStatus.FAN1_1_PID_Auto = 1;
                SystemRunTimeStatus.Value.FAN1_1_PID_Auto = RunTimeStatus.FAN1_1_PID_Auto;
                SaveRunTimeStatus();
                SendFAN1_1_PID_AutoControlCommand();//Philip 20220530 0.0.1
            }
            break;
        case 27 ://FAN1_1_PID_Manual
            if( RunTimeStatus.FAN1_1_PID_ON == 1 )
            {
                RunTimeStatus.FAN1_1_PID_Auto = 0;
                SystemRunTimeStatus.Value.FAN1_1_PID_Auto = RunTimeStatus.FAN1_1_PID_Auto;
                SaveRunTimeStatus();
                SendFAN1_1_PID_AutoControlCommand();//Philip 20220530 0.0.1
            }
            break;
        case 28 ://PCD20_PID_Manual
            RunTimeStatus.PCD20_PID_Auto = 0;
            SystemRunTimeStatus.Value.PCD20_PID_Auto = RunTimeStatus.PCD20_PID_Auto;
            SaveRunTimeStatus();
            Send_PCD_20_PID_AutoControlCommand();//Philip 20220530 0.0.1
            break;
        case 29 ://PCD20_PID_Auto
            RunTimeStatus.PCD20_PID_Auto = 1;
            SystemRunTimeStatus.Value.PCD20_PID_Auto = RunTimeStatus.PCD20_PID_Auto;
            SaveRunTimeStatus();
            Send_PCD_20_PID_AutoControlCommand();//Philip 20220530 0.0.1
            break;
        case 30 ://Heater_PID_Manual
            RunTimeStatus.Heater_PID_Auto = 0;
            SystemRunTimeStatus.Value.Heater_PID_Auto = RunTimeStatus.Heater_PID_Auto;
            SaveRunTimeStatus();
            SendHeater_PID_AutoControlCommand();//Philip 20220530 0.0.1
            break;
        case 31 ://Heater_PID_Auto
            RunTimeStatus.Heater_PID_Auto = 1;
            SystemRunTimeStatus.Value.Heater_PID_Auto = RunTimeStatus.Heater_PID_Auto;
            SaveRunTimeStatus();
            SendHeater_PID_AutoControlCommand();//Philip 20220530 0.0.1
            break;               
//Philip 20220525 0.0.1 ====================================================================
//Philip 20220526 0.0.1 ====================================================================
        case 32 ://SystemManualMode
            SystemRunTimeStatus.Value.SystemManualMode = 1;
            SaveRunTimeStatus();
            SendSystemManualControlCommand();//Philip 20220530 0.0.1
            break;
        case 33 ://Stop SystemManualMode
            SystemRunTimeStatus.Value.SystemManualMode = 0;
            SaveRunTimeStatus();
            SendSystemManualControlCommand();//Philip 20220530 0.0.1
            break;
//Philip 20220526 0.0.1 ====================================================================            
    }
}
//Philip 20220325 0.0.1 =========================================================================

void Android_HMI_Parsing(void)
{
    unsigned int crc_data;
    U1_SendingWord.Byte[0] = UART1RxBuffer[COM1_Rx_Size - 1];
    U1_SendingWord.Byte[1] = UART1RxBuffer[COM1_Rx_Size - 2];
    crc_data = U1_SendingWord.WordData;
    
    if( CRC_CHECK(UART1RxBuffer, (COM1_Rx_Size - 2), crc_data) == 1 )
    {
        switch(UART1RxBuffer[0])
        {
            case Android_HMI_GetFirmwareVersionCommandEnum ://00
                RoutineSendFlag = 0;
                SendFirmwareVersion(0);
                break;
            case Android_HMI_GetExtFirmwareVersionCommandEnum ://01
                RoutineSendFlag = 0;
                SendFirmwareVersion(1);                
                break;
            case Android_HMI_Fan1_1_GetSV_CommandEnum ://02
                RoutineSendFlag = 0;
                SendFan1_1_GetSV_Response();
                break;
            case Android_HMI_Fan1_1_GetPI_CommandEnum :
                RoutineSendFlag = 0;
                SendFan1_1_GetPI_Response();
                break;
            case Android_HMI_Fan1_1_GetD_LowLimit_CommandEnum ://04
                RoutineSendFlag = 0;
                SendFan1_1_GetD_LowLimit_Response();
                break;
            case Android_HMI_Fan1_1_GetTopLimit_CommandEnum :
                RoutineSendFlag = 0;
                SendFan1_1_Get_TopLimit_Response();
                break;
            case Android_HMI_Fan1_1_GetManualSet_CommandEnum ://06
                RoutineSendFlag = 0;
                SendFan1_1_Get_ManualSet_Response();
                break;
            case Android_HMI_Fan2_GetTempSetSpeedTopLimit_CommandEnum :
                RoutineSendFlag = 0;
                Send_GetFan2TempSetSpeedTopLimit_Response();
                break;
            case Android_HMI_Fan2_GetSpeedSet_CommandEnum ://08
                RoutineSendFlag = 0;
                Send_GetFan2SpeedSetResponse();
                break;
            case Android_HMI_Heater_TempSetDb_CommandEnum :
                RoutineSendFlag = 0;
                Send_HeaterGetTempSetDbResponse();
                break;
            case Android_HMI_Heater_TempHH2LLSet_CommandEnum ://10
                RoutineSendFlag = 0;
                Send_Heater_Get_HH2LLSetResponse();
                break;
            case Android_HMI_HeaterSP2LowLimitSet_CommandEnum :
                RoutineSendFlag = 0;
                Send_Heater_GetSP2LowLimitSetResponse();
                break;
            case Android_HMI_HeaterPI_Set_CommandEnum ://12
                RoutineSendFlag = 0;
                Send_Heater_GetPI_SetResponse();
                break;   
            case Android_HMI_HeaterD2_ManualSet_CommandEnum ://13
                RoutineSendFlag = 0;
                Send_Heater_GetManualSetResponse();
                break;
            case Android_HMI_MTR4_TE5ConditionSet_CommandEnum ://14
                RoutineSendFlag = 0;
                Send_MTR4_GetTE5ConditionSetResponse();
                break;
            case Android_HMI_MTR4_TE5SpeedSet_CommandEnum :
                RoutineSendFlag = 0;
                Send_MTR4_GetTE5SpeedSetResponse();
                break;
            case Android_HMI_MTR4_TopStopTempLowSet_CommandEnum ://16
                RoutineSendFlag = 0;
                Send_MTR4_GetTopStopLowSetResponse();
                break;    
            case Android_HMI_PCD2_V21Set_CommandEnum :
                RoutineSendFlag = 0;
                Send_GetPCD2_V21SetResponse();
                break;
            case Android_HMI_PCD20_Temp_SizeSet_CommandEnum ://18
                RoutineSendFlag = 0;
                Send_GetPCD20_TempSizeSetResponse();
                break;
            case Android_HMI_PCD20_PISet_CommandEnum ://19
                RoutineSendFlag = 0;
                Send_GetPCD20_PISetResponse();
                break;
            case Android_HMI_PCD20_D_TimeSet_CommandEnum ://20
                RoutineSendFlag = 0;
                Send_GetPCD20_D_TimeSetResponse();
                break;
            case Android_HMI_PCD20_DeadBandTopLowLimit_PCD6TimeSet_CommandEnum :
                RoutineSendFlag = 0;
                Send_GetPCD20_DeadBandTopLowLimitPCD6SetResponse();
                break;
            case Android_HMI_PCD22_Set_CommandEnum ://22
                RoutineSendFlag = 0;
                Send_GetPCD22_SetResponse();
                break;
            case Android_HMI_PCD25_PCD6_TimeSet_CommandEnum :
                RoutineSendFlag = 0;
                Send_GetPCD25_PCD6TimeSetResponse();
                break;  
            case Android_HMI_PCD25_Limit_ManualSet_CommandEnum ://24
                RoutineSendFlag = 0;
                Send_GetPCD25_Limit_ManualSetResponse();
                break;              
                
            case Android_HMI_Alarm_A1_Set_CommandEnum :
                RoutineSendFlag = 0;
                Send_GetAlarm_A1_SetResponse();                
                break;
            case Android_HMI_Alarm_A1_A2_Set_CommandEnum ://26
                RoutineSendFlag = 0;
                Send_GetAlarm_A1_A2SetResponse();                
                break;
            case Android_HMI_Alarm_A2_B_Set_CommandEnum :
                RoutineSendFlag = 0;
                Send_GetAlarm_A2_B_SetResponse();                
                break;
            case Android_HMI_HeaterTempAlarm_Set_CommandEnum ://28
                RoutineSendFlag = 0;
                Send_GetHeaterTempAlarm_SetResponse();                
                break;
            case Android_HMI_HeaterPDTAlarm_Set_CommandEnum :
                RoutineSendFlag = 0;
                Send_GetHeaterPDTAlarm_SetResponse();                
                break;          
            case Android_HMI_MTR4TempAlarm_Set_CommandEnum ://30
                RoutineSendFlag = 0;
                Send_GetMTR4TempAlarm_SetResponse();                
                break;
            case Android_HMI_MTR4TempPDTAlarm_Set_CommandEnum :
                RoutineSendFlag = 0;
                Send_Get_MTR4TempPDTAlarm_SetResponse();                
                break;
            case Android_HMI_D_Alarm1_Set_CommandEnum ://32
                RoutineSendFlag = 0;
                Send_GetD_Alarm1_Set_SetResponse();                
                break;
            case Android_HMI_D_Alarm2_Set_CommandEnum :
                RoutineSendFlag = 0;
                Send_GetD_Alarm2_Set_SetResponse();                
                break;
            case Android_HMI_D_Alarm3__D1_Set_CommandEnum ://34
                RoutineSendFlag = 0;
                Send_GetD_Alarm3__D1_SetResponse();                
                break;
            case Android_HMI_D1_Alarm2_Set_CommandEnum :
                RoutineSendFlag = 0;
                Send_GetD1_Alarm2_Set_SetResponse();                
                break;
            case Android_HMI_D1_Alarm3_Set_CommandEnum ://36
                RoutineSendFlag = 0;
                Send_GetD1_Alarm3_SetResponse();                
                break;
                //Philip 20220325 0.0.1 =========================================================================                
            case Android_HMI_Button_CommandEnum ://37
                Android_ButtonProcess();
                Send_LoopBackResponse();
                break;
                //Philip 20220325 0.0.1 ========================================================================= 
                
            case Android_HMI_WriteParameter_CommandEnum ://50
                RoutineSendFlag = 0;
                WriteParameterParsing();
                Send_LoopBackResponse();
                break;
               
        }
    }
}
