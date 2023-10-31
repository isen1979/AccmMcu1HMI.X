/*
 * File:   InitialSystemTestParameter.c
 * Author: user
 *
 * Created on 2021年4月7日, 上午 9:58
 */
#include "SystemControl.h"

#define FAN1_1_ALARM_ADDR 15
#define FNA2_ALARM_ADDR 40
#define SCR_STATUS_ADDR 41
#define SCR_FAULT_ADDR 51
#define SCR_ALARM_ADDR 61
#define PCD_2_FAULT_ADDR 69
#define PCD_2_ALARM_ADDR 75
#define PCD_20_FAULT_ADDR 79
#define PCD_20_ALARM_ADDR 85
#define V21_FAULT_ADDR 89
#define V21_ALARM_ADDR 95
#define WHEEL_FAULT_ADDR 200

#define FAN1_DISPLAY_ADDR 180
#define FAN2_DISPLAY_ADDR 186
#define SCR_DISPLAY_ADDR 192
#define MTR4_DISPLAY_ADDR 660
#define PCD20_22_25_DISPLAY_ADDR 670
#define OTHER_DISPLAY_ADDR 254


extern unsigned int FirmwareVersion;
extern unsigned long FirmwareDate;
extern _SYSTEM_PARAMETER SystemParameter;
extern _SENDING_WORD SendingWord;
extern _SENDING_DATA SendingData;

extern void uC_HMI_RunWriteSingleByteSend(unsigned int addr, unsigned char Value);
extern void uC_HMI_RunWriteMultiByteSend(unsigned int addr, unsigned char length, unsigned char *data);
extern void uC_HMI_RunWriteMultiWordSend(unsigned int addr, unsigned char length, unsigned char *data);
extern void uC_HMI_RunWriteMultiLongWordSend(unsigned int addr, unsigned char length, unsigned char *data);

_RUNTIME_FAN1_1_ALARM FAN1_1_RunTimeFault;
_RUNTIME_FAN2_ALARM FAN2_RunTimeFault;
_RUNTIME_SCR_STATUS SCR_RunTimeStatus;
_RUNTIME_SCR_FAULT SCR_RunTimeFault;
_RUNTIME_SCR_ALARM SCR_RunTimeAlarm;
_RUNTIME_WHEEL_FAULT Wheel_RunTimeFault;
_RUNTIME_PCD2_FAULT PCD2_RunTimeFault;
_RUNTIME_PCD2_ALARM PCD2_RunTimeAlarm;
_RUNTIME_PCD20_FAULT PCD20_RunTimeFault;
_RUNTIME_PCD20_ALARM PCD20_RunTimeAlarm;
_RUNTIME_V21_FAULT V21_RunTimeFault;
_RUNTIME_V21_ALARM V21_RunTimeAlarm;

_FAN1_1_RUNTIME_DISPLAY lastFAN1_1_RunTimeDisplay, FAN1_1_RunTimeDisplay;
_FAN2_RUNTIME_DISPLAY lastFAN2_RunTimeDisplay, FAN2_RunTimeDisplay;
_HEATER_RUNTIME_DISPLAY HEATER_RunTimeDisplay, lastSCR_RunTimeDisplay;
_MTR4_RUNTIME_DISPLAY MTR4_RunTimeDisplay, lastMTR4_RunTimeDisplay;
_PCD20_RUNTIME_DISPLAY PCD20_RunTimeDisplay, lastPCD20_RunTimeDisplay;
_OTHER_RUNTIME_DISPLAY OtherRunTimeDisplay, lastOtherRunTimeDisplay;

void uC_HMI_Send_FAN1_1_Alarm(void)
{
    uC_HMI_RunWriteSingleByteSend(FAN1_1_ALARM_ADDR, FAN1_1_RunTimeFault.AlarmValue);//FAN1_1 Alarm addr = 15
}

void uC_HMI_Send_FAN2_Alarm(void)
{
    uC_HMI_RunWriteSingleByteSend(FNA2_ALARM_ADDR, FAN2_RunTimeFault.AlarmValue);
}

void uC_HMI_Send_SCR_AlarmFaultStatus(void)
{   
    uC_HMI_RunWriteSingleByteSend(SCR_STATUS_ADDR, SCR_RunTimeStatus.StatusValue);
    uC_HMI_RunWriteSingleByteSend(SCR_FAULT_ADDR, SCR_RunTimeFault.FaultValue);
    uC_HMI_RunWriteSingleByteSend(SCR_ALARM_ADDR, SCR_RunTimeAlarm.AlarmValue);
}

void uC_HMI_Send_Wheel_Fault(void)
{
    uC_HMI_RunWriteSingleByteSend(WHEEL_FAULT_ADDR, Wheel_RunTimeFault.FaultValue);
}
void uC_HMI_Send_PCD2_AlarmFault(void)
{
    uC_HMI_RunWriteSingleByteSend(PCD_2_FAULT_ADDR, PCD2_RunTimeFault.FaultValue);
    uC_HMI_RunWriteSingleByteSend(PCD_2_ALARM_ADDR, PCD2_RunTimeAlarm.AlarmValue);    
}
void uC_HMI_Send_PCD20_AlarmFault(void)
{
    uC_HMI_RunWriteSingleByteSend(PCD_20_FAULT_ADDR, PCD20_RunTimeFault.FaultValue);
    uC_HMI_RunWriteSingleByteSend(PCD_20_ALARM_ADDR, PCD20_RunTimeAlarm.AlarmValue);    
}

void uC_HMI_Send_V21_AlarmFault(void)
{
    uC_HMI_RunWriteSingleByteSend(V21_FAULT_ADDR, V21_RunTimeFault.FaultValue);
    uC_HMI_RunWriteSingleByteSend(V21_ALARM_ADDR, V21_RunTimeAlarm.AlarmValue);    
}

void uC_HMI_Send_FAN1_Display(void)
{
    unsigned char length;
    unsigned char data[10];

    length = 0;
    SendingWord.WordData = FAN1_1_RunTimeDisplay.RealPressure;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = FAN1_1_RunTimeDisplay.PID_Output;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = FAN1_1_RunTimeDisplay.RealFreq;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = FAN1_1_RunTimeDisplay.Current;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = FAN1_1_RunTimeDisplay.ErrorCode;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    
    uC_HMI_RunWriteMultiWordSend(FAN1_DISPLAY_ADDR, length, data);
}

void uC_HMI_Send_FAN2_Display(void)
{
    unsigned char length;
    unsigned char data[10];

    length = 0;
    SendingWord.WordData = FAN2_RunTimeDisplay.SV;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = FAN2_RunTimeDisplay.RealSpeed;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = FAN2_RunTimeDisplay.TE12;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = FAN2_RunTimeDisplay.Current;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    
    uC_HMI_RunWriteMultiWordSend(FAN2_DISPLAY_ADDR, length, data);
}

void uC_HMI_Send_SCR_Display(void)
{
    unsigned char length;
    unsigned char data[20];  
    
    length = 0;
    SendingWord.WordData = HEATER_RunTimeDisplay.RealOutputPercent;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = HEATER_RunTimeDisplay.OvenSP;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = HEATER_RunTimeDisplay.OvenSV;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = HEATER_RunTimeDisplay.AverageTemperature;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];       
    SendingWord.WordData = HEATER_RunTimeDisplay.TE11;//TE11A;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = HEATER_RunTimeDisplay.TE14;//TE11B;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    
    uC_HMI_RunWriteMultiWordSend(SCR_DISPLAY_ADDR, length, data);
}

void uC_HMI_Send_MTR4_Display(void)
{
    unsigned char length;
    unsigned char data[10];  
    
    length = 0;
    SendingWord.WordData = MTR4_RunTimeDisplay.RealFreq;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = MTR4_RunTimeDisplay.RPH;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = MTR4_RunTimeDisplay.TE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = MTR4_RunTimeDisplay.Current;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0]; 
    SendingWord.WordData = MTR4_RunTimeDisplay.ErrorCode;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];     
    
    uC_HMI_RunWriteMultiWordSend(MTR4_DISPLAY_ADDR, length, data);
}

void uC_HMI_Send_PCD20_Display(void)
{
    unsigned char length;
    unsigned char data[10];  
    
    length = 0;
    SendingWord.WordData = PCD20_RunTimeDisplay.TE3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];     
    SendingWord.WordData = PCD20_RunTimeDisplay.RealOpenSize;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = OtherRunTimeDisplay.PCD22_RealOpenSize;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];  
    SendingWord.WordData = OtherRunTimeDisplay.PCD25_RealOpenSize;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];      
    
    uC_HMI_RunWriteMultiWordSend(PCD20_22_25_DISPLAY_ADDR, length, data);
}

void uC_HMI_Send_Other_Display(void)
{
    unsigned char length;
    unsigned char data[20];  
    
    length = 0;
    SendingWord.WordData = OtherRunTimeDisplay.TE1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];     
    SendingWord.WordData = OtherRunTimeDisplay.TE6;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = OtherRunTimeDisplay.TE8;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];     
    SendingWord.WordData = OtherRunTimeDisplay.TE10;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0]; 
    SendingWord.WordData = OtherRunTimeDisplay.PDT1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = OtherRunTimeDisplay.PDT2;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];      
    SendingWord.WordData = OtherRunTimeDisplay.PDT5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    
    uC_HMI_RunWriteMultiWordSend(OTHER_DISPLAY_ADDR, length, data);
}
/*
void Fill_RunTimeDisplayData(void)
{
    FAN1_1_RunTimeDisplay.PID_Output = 30;
    FAN1_1_RunTimeDisplay.RealFreq = 24;
    FAN1_1_RunTimeDisplay.RealPressure = 250;
    FAN1_1_RunTimeDisplay.Current = 3000;
    FAN1_1_RunTimeDisplay.ErrorCode = 0x1234;    
    
    FAN2_RunTimeDisplay.RealSpeed = 46;
    FAN2_RunTimeDisplay.SV = 43;
    FAN2_RunTimeDisplay.TE12 = 0;
    FAN2_RunTimeDisplay.Current = 4000;
    
    SCR_RunTimeDisplay.OvenSP = 1235;
    SCR_RunTimeDisplay.OvenSV = 1230;
    SCR_RunTimeDisplay.RealOutputPercent = 65;
    SCR_RunTimeDisplay.AverageTemperature = 1017;
    SCR_RunTimeDisplay.TE11 = 0;
    SCR_RunTimeDisplay.TE14 = 0;  
    
    MTR4_RunTimeDisplay.RealFreq = 47;
    MTR4_RunTimeDisplay.RPH = 126;
    MTR4_RunTimeDisplay.TE5 = 0;
    MTR4_RunTimeDisplay.Current = 6000;
    MTR4_RunTimeDisplay.ErrorCode = 0x2345;    
    
    PCD20_RunTimeDisplay.RealOpenSize = 23;
    PCD20_RunTimeDisplay.TE3 = 0;
    OtherRunTimeDisplay.PCD22_RealOpenSize = 25;
    OtherRunTimeDisplay.PCD25_RealOpenSize =65;    

    OtherRunTimeDisplay.TE1 = 0;
    OtherRunTimeDisplay.TE6 = 0;
    OtherRunTimeDisplay.TE8 = 0;
    OtherRunTimeDisplay.TE10 = 0;
    OtherRunTimeDisplay.PDT1 = -700;
    OtherRunTimeDisplay.PDT2 = -700;
    OtherRunTimeDisplay.PDT3 = -700;
}

void Fill_Fault_Alarm_Status_Data(void)
{
    FAN1_1_RunTimeFault.bitmap.PressureSensorTurnOnFault = 1;
    FAN1_1_RunTimeFault.bitmap.PressureSensorTurnOffFault = 1;
    FAN1_1_RunTimeFault.bitmap.PressureSensorRunningFault = 1;
    FAN1_1_RunTimeFault.bitmap.InverterFault = 1;
    FAN1_1_RunTimeFault.bitmap.MotorOverTempFault = 1;
    FAN1_1_RunTimeFault.bitmap.InverterContactFault = 1;
    FAN1_1_RunTimeFault.bitmap.Dummy = 0;
    
    FAN2_RunTimeFault.bitmap.PressureSensorTurnOnFault = 1;
    FAN2_RunTimeFault.bitmap.PressureSensorTurnOffFault = 0;
    FAN2_RunTimeFault.bitmap.PressureSensorRunningFault = 1;
    FAN2_RunTimeFault.bitmap.InverterTurnOnFault = 0;
    FAN2_RunTimeFault.bitmap.InverterRunningFault = 1;
    FAN2_RunTimeFault.bitmap.InverterTurnOffFault = 0;
    FAN2_RunTimeFault.bitmap.Dummy = 0; 
    
    SCR_RunTimeStatus.bitmap.FinishCleanOven = 1;
    SCR_RunTimeStatus.bitmap.DropOutTemperatureReady = 0;
    SCR_RunTimeStatus.bitmap.OvenControllerEn = 1;
    SCR_RunTimeStatus.bitmap.OvenTemperatureReady = 0;
    SCR_RunTimeStatus.bitmap.SCR_Heater_TurnOn = 1;
    SCR_RunTimeStatus.bitmap.Dummy = 0;
    
    SCR_RunTimeFault.bitmap.SCR_HeatingSystemFault = 1;
    SCR_RunTimeFault.bitmap.HighTemperatureContorlFault = 0;
    SCR_RunTimeFault.bitmap.SuperHighTemperatureFault = 1;
    SCR_RunTimeFault.bitmap.SuperLowTemperatureFault = 0;
    SCR_RunTimeFault.bitmap.TwoTemperatureSensorFault = 1;
    SCR_RunTimeFault.bitmap.Dummy = 0;
    
    SCR_RunTimeAlarm.bitmap.HighTemperatureAlarm = 1;
    SCR_RunTimeAlarm.bitmap.LowTemperatureAlarm = 0;
    SCR_RunTimeAlarm.bitmap.TemperatureSensor1Alarm = 1;
    SCR_RunTimeAlarm.bitmap.TemperatureSensor2Alarm = 0;
    SCR_RunTimeAlarm.bitmap.Dummy = 0;
    
    Wheel_RunTimeFault.bitmap.InverterFault = 1;
    Wheel_RunTimeFault.bitmap.InverterRunningFault = 0;
    Wheel_RunTimeFault.bitmap.RunningFault = 1;
    Wheel_RunTimeFault.bitmap.StopFault = 1;
    Wheel_RunTimeFault.bitmap.WheelRotateFault = 0;    
    Wheel_RunTimeFault.bitmap.Dummy = 0;
    
    PCD2_RunTimeFault.bitmap.CloseFault = 1;
    PCD2_RunTimeFault.bitmap.LimitFault = 0;
    PCD2_RunTimeFault.bitmap.OpenFault = 1;    
    PCD2_RunTimeFault.bitmap.Dummy = 0;
    
    PCD2_RunTimeAlarm.bitmap.CloseAlarm = 1;
    PCD2_RunTimeAlarm.bitmap.OpenAlarm = 0;    
    PCD2_RunTimeAlarm.bitmap.Dummy = 0;
    
    PCD20_RunTimeFault.bitmap.LimitFault = 1;
    PCD20_RunTimeFault.bitmap.OpenFault = 0;
    PCD20_RunTimeFault.bitmap.CloseFault = 1;
    PCD20_RunTimeFault.bitmap.Dummy = 0;
    
    PCD20_RunTimeAlarm.bitmap.OpenAlarm = 1;
    PCD20_RunTimeAlarm.bitmap.CloseAlarm = 0;
    PCD20_RunTimeAlarm.bitmap.Dummy = 0;
    
    V21_RunTimeFault.bitmap.LimitFault = 1;
    V21_RunTimeFault.bitmap.CloseFault = 0;
    V21_RunTimeFault.bitmap.OpenFault = 1;
    V21_RunTimeFault.bitmap.Dummy = 0;
    
    V21_RunTimeAlarm.bitmap.OpenAlarm = 1;
    V21_RunTimeAlarm.bitmap.CloseAlarm = 0;
    V21_RunTimeAlarm.bitmap.Dummy = 0;
}

void Fill_FAN1_SystemParameter(void)
{
    SystemParameter.FAN1_1.value.SuperHighPressureAlarmSet = 1000;
    SystemParameter.FAN1_1.value. HighPressureAlarmSet = 800;
    SystemParameter.FAN1_1.value.LowPressureAlarmSet = 300;
    SystemParameter.FAN1_1.value.SuperLowPressureAlarmSet = 100;
    SystemParameter.FAN1_1.value.PT_1 = 100;
    SystemParameter.FAN1_1.value.FAN1_1ManualOpenSize = 50;
    
    SystemParameter.FAN1_1.value.PID_P = 120;
    SystemParameter.FAN1_1.value.PID_I = 567;//mSec
    SystemParameter.FAN1_1.value.PID_D = 678;//mSec
    SystemParameter.FAN1_1.value.FAN1_1_2_DelayTime = 1234;//mSec
    
    SystemParameter.FAN1_1.value.DeadBand = 23;//0-100%    
    SystemParameter.FAN1_1.value.FAN1_LowLimit = 15;//0-100%
    SystemParameter.FAN1_1.value.FAN1_High1 = 75;//0-100%
    SystemParameter.FAN1_1.value.FAN1_High2 = 95;//0-100%
    SystemParameter.FAN1_1.value.ManualStartFrequency = 15;//0-100%
    SystemParameter.FAN1_1.value.ManualStopFrequency = 5;    
}

void Fill_FAN2_SystemParameter(void)
{
    SystemParameter.FAN_2.value.FAN_2_Target_Temp1 = 123;
    SystemParameter.FAN_2.value.FAN_2_Target_Temp2 = 234;
    SystemParameter.FAN_2.value.FAN_2_Target_Temp3 = 345;
    SystemParameter.FAN_2.value.FAN_2_TargetTemp1_Hz = 200;
    SystemParameter.FAN_2.value.FAN_2_TargetTemp2_Hz = 400;    
    SystemParameter.FAN_2.value.FAN_2_TargetTemp3_Hz = 600;
//    SystemParameter.FAN_2.value.FAN_2 = 55;//Inverter Frequency(0-60Hz)//10Bytes
    SystemParameter.FAN_2.value.FAN_2_Top = 600;//Inverter MAx Frequency(0-60.0Hz)//11Bytes
    SystemParameter.FAN_2.value.FAN_2_Low = 100;//Inverter Low Frequency(0-60.0Hz)//12Bytes    
}   

void Fill_HEATER_SET_SystemParameter(void)
{
    SystemParameter.HeaterSet.value.OP_Temp = 4000;
    SystemParameter.HeaterSet.value.StandBy_Temp = 4001;
    SystemParameter.HeaterSet.value.KeepWarmTemp = 4002;
    SystemParameter.HeaterSet.value.SuperHighTemp = 4003;
    SystemParameter.HeaterSet.value.HighTemp = 4004;
    SystemParameter.HeaterSet.value.LowTemp = 4005;
    SystemParameter.HeaterSet.value.SuperLowTemp = 4006;
    SystemParameter.HeaterSet.value.PID_P = 1423;
    SystemParameter.HeaterSet.value.PID_I = 589;
    SystemParameter.HeaterSet.value.PID_D = 698;
    SystemParameter.HeaterSet.value.DeadBand = 255;
    SystemParameter.HeaterSet.value.MoreThanSP_StopTemp = 4007; 
    SystemParameter.HeaterSet.value.LessThanSP_StartTemp = 4008;
    SystemParameter.HeaterSet.value.ReFireTemp = 4009;//0 - 400.0
    SystemParameter.HeaterSet.value.FireCount = 999;//0 - 999
    SystemParameter.HeaterSet.value.TopLimit = 1000;//0 - 100.0%
    SystemParameter.HeaterSet.value.LowLimit = 200;//0 - 100.0%
    SystemParameter.HeaterSet.value.ManualOpenSize = 300;//0 - 100.0% 
}

void Fill_Wheel_SystemParameter(void)
{
    SystemParameter.Wheel.value.T5_CheckTemp1 = 111;
    SystemParameter.Wheel.value.T5_CheckTemp2 = 222;
    SystemParameter.Wheel.value.T5_CheckTemp3 = 333;
    SystemParameter.Wheel.value.T5_CheckTemp1Frequency = 560;
    SystemParameter.Wheel.value.T5_CheckTemp2Frequency = 670;
    SystemParameter.Wheel.value.T5_CheckTemp3Frequency = 790;
    SystemParameter.Wheel.value.StopTemp = 444;
    SystemParameter.Wheel.value.TopLimitFrequency = 600;
    SystemParameter.Wheel.value.LowLimitFrequency = 120;
}

void Fill_PDC_6_20_22_25_SystemParameter(void)
{
    SystemParameter.PDC_20.value.OP_Temp = 356;
    SystemParameter.PDC_20.value.StandByTemp = 125;
    SystemParameter.PDC_20.value.CoolingTemp = 100;
    SystemParameter.PDC_20.value.PID_P = 102;;
    SystemParameter.PDC_20.value.PID_I = 687;//mSec
    SystemParameter.PDC_20.value.PID_D = 765;//mSec
    SystemParameter.PDC_20.value.DeadBand = 10;
    SystemParameter.PDC_20.value.TopLimit = 95;//0 - 100%
    SystemParameter.PDC_20.value.LowLimit = 20;//0 - 100%
    SystemParameter.PDC_20.value.ManualOpenSize = 100;//0 - 100.0%

    SystemParameter.PDC_20.value.FaultDelayTime = 999;//Sec
    SystemParameter.PDC_20.value.AlarmDelayTime = 998;//Sec
    SystemParameter.PDC_20.value.OnOFFDelayTime = 997;//Sec
    
//    SystemParameter.PDC_20.value.T3_CheckTemp1 = 123;
//    SystemParameter.PDC_20.value.T3_CheckTemp2 = 256;
//    SystemParameter.PDC_20.value.T3_CheckTemp3 = 347;
    
    SystemParameter.PCD_6.value.FaultDelayTime = 12;
    SystemParameter.PCD_6.value.AlarmDelayTime = 15;

//    SystemParameter.PDC_20.value.OpenSizeTopLimit = 98;//0 - 100%
//    SystemParameter.PDC_20.value.OpenSizeLowLimit = 3;//0 - 100%
//    SystemParameter.PDC_20.value.T3_CheckTemp1_OpenSize = 25;//0 - 100%
//    SystemParameter.PDC_20.value.T3_CheckTemp2_OpenSize = 78;//0 - 100%
//    SystemParameter.PDC_20.value.T3_CheckTemp3_OpenSize = 94;//0 - 100%  
    
    SystemParameter.PDC_22.value.ReleaseTemp = 4000;//0 - 400.0 deg//2Bytes
    SystemParameter.PDC_22.value.FaultDelayTime = 10;//0 - 999 Sec
    SystemParameter.PDC_22.value.AlarmDelayTime = 11;//0 - 999 Sec
    SystemParameter.PDC_22.value.OnOFFDelayTime = 12;//0 - 999 Sec

    SystemParameter.PDC_25.value.FaultDelayTime = 13;//0 - 999 Sec
    SystemParameter.PDC_25.value.AlarmDelayTime = 14;//0 - 999 Sec
    SystemParameter.PDC_25.value.OnOFFDelayTime = 15;//0 - 999 Sec

    SystemParameter.PDC_25.value.TopLimit = 500;//0 - 100.0%
    SystemParameter.PDC_25.value.LowLimit = 80;//0 - 100.0%
    SystemParameter.PDC_25.value.ManualOpenSize = 90;//0 - 100.0%
}

void Fill_PDC_2_SystemParameter(void)
{
    SystemParameter.PDC2.FaultDelayTime = 1001;
    SystemParameter.PDC2.AlarmDelayTime = 1002;    
}

void Fill_V21_SystemParameter(void)
{
    SystemParameter.V21.FaultDelayTime = 1003;
    SystemParameter.V21.AlarmDelayTime = 1004;    
}

void Fill_AlarmTypeASystemParameter(void)
{
    SystemParameter.AlarmTypeASet.A1_TE8 = 1;
    SystemParameter.AlarmTypeASet.A1_TE5 = 2;
    SystemParameter.AlarmTypeASet.A1_TE5GTwhenTE3 = 3;
    SystemParameter.AlarmTypeASet.A1_TE3Offset = 4;
    SystemParameter.AlarmTypeASet.A1_TE5GTwhenFAN2Stop = 5;
    
    SystemParameter.AlarmTypeASet.A2_TE8 = 6;
    SystemParameter.AlarmTypeASet.A2_TE5 = 7;
    SystemParameter.AlarmTypeASet.A2_TE5GTwhenTE3 = 8;
    SystemParameter.AlarmTypeASet.A2_TE3Offset = 9;
    SystemParameter.AlarmTypeASet.A2_TE5LTwhenFAN2Stop = 10;
}

void Fill_AlarmTypeBSystemParameter(void)
{
    SystemParameter.AlarmTypeBSet.TE5 = 11;
    SystemParameter.AlarmTypeBSet.TE5GTwhenFAN2Stop = 12;
}

void Fill_BurnSystemAlarmSystemParameter(void)
{
    SystemParameter.BurnSystemAlarmSet.SuperHighTE11 = 13;
    SystemParameter.BurnSystemAlarmSet.SuperLowTE11 = 14;
    SystemParameter.BurnSystemAlarmSet.SuperHighTE12 = 15;
    SystemParameter.BurnSystemAlarmSet.SuperLowTE12 = 16;
    SystemParameter.BurnSystemAlarmSet.SuperHighPDT2 = 17;
    SystemParameter.BurnSystemAlarmSet.SuperLowPDT2 = 18;  
    SystemParameter.BurnSystemAlarmSet.SuperHighPDT3 = 19;
    SystemParameter.BurnSystemAlarmSet.SuperLowPDT3 = 20;       
}

void Fill_WheelAlarmSystemParameter(void)
{
    SystemParameter.WheelAlarmSet.SuperHighTE3 = 17;
    SystemParameter.WheelAlarmSet.SuperLowTE3 = 18;
    SystemParameter.WheelAlarmSet.SuperHighTE8 = 19;
    SystemParameter.WheelAlarmSet.SuperLowTE8 = 20;
    SystemParameter.WheelAlarmSet.SuperHighTE5 = 21;
    SystemParameter.WheelAlarmSet.SuperLowTE5 = 22;
    SystemParameter.WheelAlarmSet.SuperHighPDT1 = 23;
    SystemParameter.WheelAlarmSet.SuperLowPDT1 = 24;    
}

void Fill_AlarmTypeDSystemParameter(void)
{  
    SystemParameter.AlarmTypeDSet.SuperHighTE3 = 23;
    SystemParameter.AlarmTypeDSet.SuperLowTE3 = 24;
    SystemParameter.AlarmTypeDSet.SuperHighTE5 = 25;
    SystemParameter.AlarmTypeDSet.SuperLowTE5 = 26;
    SystemParameter.AlarmTypeDSet.SuperHighTE8 = 27;
    SystemParameter.AlarmTypeDSet.SuperLowTE8 = 28;
    SystemParameter.AlarmTypeDSet.SuperHighTE11 = 29;
    SystemParameter.AlarmTypeDSet.SuperLowTE11 = 30;    
    SystemParameter.AlarmTypeDSet.SuperHighTE12 = 31;
    SystemParameter.AlarmTypeDSet.SuperLowTE12 = 32;
       
    SystemParameter.AlarmTypeDSet.SuperHighTE14 = 33;
    SystemParameter.AlarmTypeDSet.SuperLowTE14 = 34;    
    SystemParameter.AlarmTypeDSet.SuperHighTE1 = 35;
    SystemParameter.AlarmTypeDSet.SuperLowTE1 = 36;
    
    SystemParameter.AlarmTypeDSet.SuperHighPDT1 = 37;
    SystemParameter.AlarmTypeDSet.SuperLowPDT1 = 38;    
    SystemParameter.AlarmTypeDSet.SuperHighPDT2 = 39;
    SystemParameter.AlarmTypeDSet.SuperLowPDT2 = 40;

    SystemParameter.AlarmTypeDSet.SuperHighPDT3 = 41;
    SystemParameter.AlarmTypeDSet.SuperLowPDT3 = 42; 
}

void Fill_AlarmSetSystemParameter(void)
{
    Fill_AlarmTypeASystemParameter();
    Fill_AlarmTypeBSystemParameter();
    Fill_BurnSystemAlarmSystemParameter();
    Fill_WheelAlarmSystemParameter();
    Fill_AlarmTypeDSystemParameter();
}

void Fill_SystemParameterData(void)
{
    Fill_FAN1_SystemParameter();
    Fill_FAN2_SystemParameter();
    Fill_HEATER_SET_SystemParameter();
    Fill_Wheel_SystemParameter();
    Fill_PDC_6_20_22_25_SystemParameter();
    Fill_PDC_2_SystemParameter();
    Fill_V21_SystemParameter();
    Fill_AlarmSetSystemParameter();
}

void Fill_TestParameter(void)
{
//   Fill_Fault_Alarm_Status_Data();
//   Fill_SystemParameterData();
   Fill_RunTimeDisplayData();
}
*///Philip 20220315 0.0.1
#define FAN1_SYSTEM_PARAMETER_START_ADDR 100
#define FAN1_LONG_WORD_SYSTEM_PARAMETER_START_ADDR 114
#define FAN2_SYSTEM_PARAMETER_START_ADDR 118
#define SCR_SYSTEM_PARAMETER_START_ADDR 126
#define WHEEL_SYSTEM_PARAMETER_START_ADDR 145
#define PCD20_SYSTEM_PARAMETER_START_ADDR 154
#define PCD20_LONG_WORD_SYSTEM_PARAMETER_START_ADDR 171
#define V21_SYSTEM_PARAMETER_START_ADDR 176
#define PCD22_25_SYSTEM_PARAMETER_START_ADDR 650
#define SHOW_FIRMWARE_VERSION_ADDR 247
#define SHOW_AUX_FIRMWARE_VERSION_ADDR 690

#define ALARM_TYPE_A_SET_ADDR 547
#define ALARM_TYPE_B_SET_ADDR 630
#define BURN_SYSTEM_ALARM_SET_ADDR 632
#define WHEEL_ALARM_SET_ADDR 560
#define ALARM_TYPE_D_SET_ADDR 568
#define ALARM_TYPE_D1_SET_ADDR 620

void Send_uCHMI_ControllerFirmwareVersion(void)
{
    unsigned char length;
    unsigned char data[20];

    length = 0;
    SendingData.value = FirmwareDate;
    data[length++] = SendingData.data[3];
    data[length++] = SendingData.data[2];    
    data[length++] = SendingData.data[1];
    data[length++] = SendingData.data[0];
    SendingData.value = FirmwareVersion;
    data[length++] = SendingData.data[3];
    data[length++] = SendingData.data[2];    
    data[length++] = SendingData.data[1];
    data[length++] = SendingData.data[0];
    
    uC_HMI_RunWriteMultiLongWordSend(SHOW_FIRMWARE_VERSION_ADDR, length, data);
}

extern unsigned int ExtFirmwareVersion;
extern unsigned long ExtFirmwareDate;
void Send_uCHMI_AuxControllerFirmwareVersion(void)
{
    unsigned char length;
    unsigned char data[20];

    length = 0;
    SendingData.value = ExtFirmwareDate;
    data[length++] = SendingData.data[3];
    data[length++] = SendingData.data[2];    
    data[length++] = SendingData.data[1];
    data[length++] = SendingData.data[0];
    SendingData.value = ExtFirmwareVersion;
    data[length++] = SendingData.data[3];
    data[length++] = SendingData.data[2];    
    data[length++] = SendingData.data[1];
    data[length++] = SendingData.data[0];
    
    uC_HMI_RunWriteMultiLongWordSend(SHOW_AUX_FIRMWARE_VERSION_ADDR, length, data);
}

void Send_FAN1_uCHMI_LongWordSystemParamter(void)
{
    unsigned char length;
    unsigned char data[20];
    
    length = 0;
    SendingData.value = SystemParameter.FAN1_1.value.PID_P;
    data[length++] = SendingData.data[3];
    data[length++] = SendingData.data[2];    
    data[length++] = SendingData.data[1];
    data[length++] = SendingData.data[0];
    SendingData.value = SystemParameter.FAN1_1.value.PID_D;//Sec
    data[length++] = SendingData.data[3];
    data[length++] = SendingData.data[2];    
    data[length++] = SendingData.data[1];
    data[length++] = SendingData.data[0];
    
    uC_HMI_RunWriteMultiLongWordSend(FAN1_LONG_WORD_SYSTEM_PARAMETER_START_ADDR, length, data);
}

void Send_FAN1_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[36];
    
    length = 0;
    SendingWord.WordData = SystemParameter.FAN1_1.value.SuperHighPressureAlarmSet;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.FAN1_1. value.HighPressureAlarmSet;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.FAN1_1.value.LowPressureAlarmSet;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.FAN1_1.value.SuperLowPressureAlarmSet;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];   
    SendingWord.WordData = SystemParameter.FAN1_1.value.DeadBand;//0-100%
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_LowLimit;//0-100%
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_High2;//0-100%
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_High1;//0-100%
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_1_2_DelayTime;//mSec
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.FAN1_1.value.ManualStartFrequency;//0-100%
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.FAN1_1.value.ManualStopFrequency;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];   
    SendingWord.WordData = SystemParameter.FAN1_1.value.PT_1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.FAN1_1.value.FAN1_1ManualOpenSize;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.FAN1_1.value.PID_I;//Sec
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    
    uC_HMI_RunWriteMultiWordSend(FAN1_SYSTEM_PARAMETER_START_ADDR, length, data);
    Send_FAN1_uCHMI_LongWordSystemParamter();
}

void Send_FAN2_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[36];
    
    length = 0;    
    SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Target_Temp1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Target_Temp2;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];  
    SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Target_Temp3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0]; 
    SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_TargetTemp1_Hz;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0]; 
    SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_TargetTemp2_Hz;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0]; 
    SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_TargetTemp3_Hz;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Top;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];     
    SendingWord.WordData = SystemParameter.FAN_2.value.FAN_2_Low;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0]; 

    uC_HMI_RunWriteMultiWordSend(FAN2_SYSTEM_PARAMETER_START_ADDR, length, data);    
}

void Send_Heater_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[50];
    
    length = 0;    
    SendingWord.WordData = SystemParameter.HeaterSet.value.OP_Temp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.HeaterSet.value.StandBy_Temp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.HeaterSet.value.KeepWarmTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.HeaterSet.value.SuperHighTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];       
    SendingWord.WordData = SystemParameter.HeaterSet.value.HighTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.HeaterSet.value.LowTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.HeaterSet.value.SuperLowTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.HeaterSet.value.FireCount;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.HeaterSet.value.ReFireTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.HeaterSet.value.ManualOpenSize;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];   
    SendingWord.WordData = SystemParameter.HeaterSet.value.PID_P;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.HeaterSet.value.PID_I;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.HeaterSet.value.PID_D;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];  
    SendingWord.WordData = SystemParameter.HeaterSet.value.LessThanSP_StartTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.HeaterSet.value.MoreThanSP_StopTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.HeaterSet.value.TopLimit;//%
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.HeaterSet.value.LowLimit;//%
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.HeaterSet.value.DeadBand;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.HeaterSet.value.CleanOvenTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];      
    
    uC_HMI_RunWriteMultiWordSend(SCR_SYSTEM_PARAMETER_START_ADDR, length, data);    
}

void Send_Wheel_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[30];
    
    length = 0;    
    SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp2;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp1Frequency;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];       
    SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp2Frequency;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Wheel.value.T5_CheckTemp3Frequency;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Wheel.value.StopTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Wheel.value.TopLimitFrequency;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Wheel.value.LowLimitFrequency;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];       
    
    uC_HMI_RunWriteMultiWordSend(WHEEL_SYSTEM_PARAMETER_START_ADDR, length, data);        
}

void Send_PCD_20_uCHMI_LongWordSystemParameter(void)
{
    unsigned char length;
    unsigned char data[30];
    
    length = 0;        
    SendingData.value = SystemParameter.PCD_20.value.PID_P;
    data[length++] = SendingData.data[3];
    data[length++] = SendingData.data[2];    
    data[length++] = SendingData.data[1];
    data[length++] = SendingData.data[0];
    SendingData.value = SystemParameter.PCD_20.value.PID_I;
    data[length++] = SendingData.data[3];
    data[length++] = SendingData.data[2];    
    data[length++] = SendingData.data[1];
    data[length++] = SendingData.data[0];  
    SendingData.value = SystemParameter.PCD_20.value.PID_D;
    data[length++] = SendingData.data[3];
    data[length++] = SendingData.data[2];    
    data[length++] = SendingData.data[1];
    data[length++] = SendingData.data[0];
    
    uC_HMI_RunWriteMultiLongWordSend(PCD20_LONG_WORD_SYSTEM_PARAMETER_START_ADDR, length, data);    
}

void Send_PCD_6_20_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[46];
    
    length = 0;    
    SendingWord.WordData = SystemParameter.PCD_20.value.OP_Temp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.PCD_20.value.StandByTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];   
    SendingWord.WordData = SystemParameter.PCD_20.value.CoolingTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];  
        
    SendingWord.WordData = SystemParameter.PCD_20.value.DeadBand;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.PCD_20.value.TopLimit;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];   
    SendingWord.WordData = SystemParameter.PCD_20.value.LowLimit;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    
    SendingWord.WordData = SystemParameter.PCD_20.value.FaultDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.PCD_20.value.AlarmDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    
    SendingWord.WordData = SystemParameter.PCD_20.value.ManualOpenSize;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.PCD_20.value.OnOFFDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    
    SendingWord.WordData = SystemParameter.PCD_6.value.FaultDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.PCD_6.value.AlarmDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    

    uC_HMI_RunWriteMultiWordSend(PCD20_SYSTEM_PARAMETER_START_ADDR, length, data);
    Send_PCD_20_uCHMI_LongWordSystemParameter();
}

void Send_PCD_2_V21_uCHMI_SystemParameter(void)
{
    //V21_SYSTEM_PARAMETER_START_ADDR
    unsigned char length;
    unsigned char data[20];
    
    length = 0;    
    SendingWord.WordData = SystemParameter.V21.Value.FaultDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.V21.Value.AlarmDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.PCD2.Value.FaultDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.PCD2.Value.AlarmDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0]; 
    
    uC_HMI_RunWriteMultiWordSend(V21_SYSTEM_PARAMETER_START_ADDR, length, data);    
}

void Send_PCD22_25_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[46];
    
    length = 0;    
    SendingWord.WordData = SystemParameter.PCD_22.value.FaultDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.PCD_22.value.AlarmDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.PCD_22.value.ReleaseTemp;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
        
    SendingWord.WordData = SystemParameter.PCD_22.value.OnOFFDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.PCD_25.value.FaultDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.PCD_25.value.AlarmDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    
    SendingWord.WordData = SystemParameter.PCD_25.value.OnOFFDelayTime;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.PCD_25.value.TopLimit;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    
    SendingWord.WordData = SystemParameter.PCD_25.value.LowLimit;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.PCD_25.value.ManualOpenSize;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];

    uC_HMI_RunWriteMultiWordSend(PCD22_25_SYSTEM_PARAMETER_START_ADDR, length, data);
}

void Send_AlarmTypeA_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[30];
 
    length = 0;
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE8;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5GTwhenTE3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE3Offset;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5GTwhenFAN2Stop;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE8;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5GTwhenTE3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE3Offset;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];       
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5LTwhenFAN2Stop;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0]; 
    
    uC_HMI_RunWriteMultiWordSend(ALARM_TYPE_A_SET_ADDR, length, data);    
}

void Send_AlarmTypeB_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[20];

    length = 0;
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeBSet.TE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeBSet.TE5GTwhenFAN2Stop;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];     
    
    uC_HMI_RunWriteMultiWordSend(ALARM_TYPE_B_SET_ADDR, length, data);    
}

void Send_BurnSystemAlarm_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[30];

    length = 0;
    SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighTE11;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowTE11;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighTE12;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowTE12;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0]; 
    SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighPDT2;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowPDT2;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighPDT3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowPDT3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];     
    
    uC_HMI_RunWriteMultiWordSend(BURN_SYSTEM_ALARM_SET_ADDR, length, data);    
}

void Send_WheelAlarm_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[30];

    length = 0;
    SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE8;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighPDT1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];     
    SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE8;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowPDT1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];     
    
    uC_HMI_RunWriteMultiWordSend(WHEEL_ALARM_SET_ADDR, length, data);    
}

void Send_AlarmTypeD_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[30];

    length = 0;
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE8;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE8;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];  
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE11;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE11;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE12;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE12;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
/*
    SendingWord.WordData = SystemParameter.AlarmTypeDSet.SuperHighTE1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.AlarmTypeDSet.SuperLowTE1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
*/    
    uC_HMI_RunWriteMultiWordSend(ALARM_TYPE_D_SET_ADDR, length, data);    
}

void Send_AlarmTypeD1_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[30];

    length = 0;
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE10;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE10;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE06;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE06;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighPDT1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowPDT1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighPDT2;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowPDT2;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];  
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighPDT3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowPDT3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
  
    uC_HMI_RunWriteMultiWordSend(ALARM_TYPE_D1_SET_ADDR, length, data);    
}


void Send_uCHMI_AlarmSetSystemParameter(void)
{
    Send_AlarmTypeA_uCHMI_SystemParameter();
    Send_AlarmTypeB_uCHMI_SystemParameter();
    Send_BurnSystemAlarm_uCHMI_SystemParameter();
    Send_WheelAlarm_uCHMI_SystemParameter();
    Send_AlarmTypeD_uCHMI_SystemParameter();
    Send_AlarmTypeD1_uCHMI_SystemParameter();
}

void Send_uCHMI_Alarm(void)
{
    uC_HMI_Send_FAN1_1_Alarm();
    uC_HMI_Send_FAN2_Alarm();
    uC_HMI_Send_SCR_AlarmFaultStatus();
    uC_HMI_Send_Wheel_Fault();
    uC_HMI_Send_PCD2_AlarmFault();
    uC_HMI_Send_PCD20_AlarmFault();
    uC_HMI_Send_V21_AlarmFault();    
}

void Send_uC_HMI_Display(void)
{
    uC_HMI_Send_FAN1_Display();
    uC_HMI_Send_FAN2_Display();
    uC_HMI_Send_SCR_Display();
    uC_HMI_Send_MTR4_Display();
    uC_HMI_Send_PCD20_Display();
    uC_HMI_Send_Other_Display();
}

void uC_HMI_Send_SystemParameter(void)
{
    Send_FAN1_uCHMI_SystemParameter();
    Send_FAN2_uCHMI_SystemParameter();
    Send_Heater_uCHMI_SystemParameter();
    Send_Wheel_uCHMI_SystemParameter();
    Send_PCD_6_20_uCHMI_SystemParameter();     
    Send_PCD_2_V21_uCHMI_SystemParameter();
    Send_PCD22_25_uCHMI_SystemParameter();
    Send_uCHMI_Alarm();
    Send_uC_HMI_Display();
    Send_uCHMI_AlarmSetSystemParameter();
}



