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
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE5;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE8;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE8;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];  
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE11;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE11;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE12;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE12;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
 
    uC_HMI_RunWriteMultiWordSend(ALARM_TYPE_D_SET_ADDR, length, data);    
}

void Send_AlarmTypeD1_uCHMI_SystemParameter(void)
{
    unsigned char length;
    unsigned char data[30];

    length = 0;
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE10;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE10;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighTE6;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowTE6;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighPDT1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowPDT1;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighPDT2;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowPDT2;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];  
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.HighPDT3;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = SystemParameter.Alarm.Value.AlarmTypeDSet.LowPDT3;
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



