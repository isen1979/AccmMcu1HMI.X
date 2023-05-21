/*
 * File:   SystemParameterInputProcess.c
 * Author: user
 *
 * Created on 2021年4月9日, 下午 4:15
 */
#include "..\h\SystemControl.h"

extern _SYSTEM_PARAMETER SystemParameter;

extern void COM3_Send_FAN1_Command(void);
extern void COM3_Send_FAN2_Command(void);
extern void COM3_Send_MTR4_Command(void);
extern void COM3_Send_PCD20_Command(void);
extern void COM3_Send_PCD22_Command(void);
extern void COM3_Send_PCD25_Command(void);
extern void COM3_Send_Heater_Command(void);

extern void SetSelectItemFontColor(char id);
extern void uC_HMI_RunReadByteSend(unsigned int addr, unsigned char count);
char SystemParameterId;

void GetSystemParameterId(unsigned int addr, unsigned char count, unsigned char id)
{    
    switch(addr)
    {
        case SYSTEM_PARAMETER_INPUT_ID_ADDR :
            if( count == 1 )
            {
                SystemParameterId = id;
                SetSelectItemFontColor(SystemParameterId);
            }
            else
                SystemParameterId = 0;
            break;
    }
}

long GetFloatTypeKeyBoardValue(unsigned char flag, unsigned char FloatCount, long Value)
{
    long FloatValue;
    long OffsetApproximation;
    
    if( Value >= 0 )
        OffsetApproximation = 5;
    else
        OffsetApproximation = -5;
    
    switch(flag)
    {
        case 0 ://This Parameter is Integer Value.
            switch(FloatCount)
            {
                case 0 :
                    FloatValue = Value / 10;
                    break;
                case 1 :
                    OffsetApproximation = OffsetApproximation * 10;
                    Value = Value + OffsetApproximation;//50
                    FloatValue = Value / 100;
                    break;
                case 2 :
                    OffsetApproximation = OffsetApproximation * 100;
                    Value = Value + OffsetApproximation;//500;
                    FloatValue = Value / 1000;
                    break;
                case 3 :
                    OffsetApproximation = OffsetApproximation * 1000;
                    Value = Value + OffsetApproximation;//5000;
                    FloatValue = Value / 10000;
                    break;
                case 4 :
                    OffsetApproximation = OffsetApproximation * 10000;
                    Value = Value + OffsetApproximation;//50000;
                    FloatValue = Value / 100000;
                    break;
                case 5 :
                    OffsetApproximation = OffsetApproximation * 100000;
                    Value = Value + OffsetApproximation;//500000;
                    FloatValue = Value / 1000000;
                    break;
            }
            break;
        case 1 ://This Parameter is One Digital under the Float Point.
            switch(FloatCount)
            {
                case 0 :
                    FloatValue = Value;
                    break;
                case 1 :
                    FloatValue = Value / 10;
                    break;
                case 2 :
                    OffsetApproximation = OffsetApproximation * 10;
                    Value = Value + OffsetApproximation;//50;
                    FloatValue = Value / 100;                    
                    break;
                case 3 :
                    OffsetApproximation = OffsetApproximation * 100;
                    Value = Value + OffsetApproximation;//500;
                    FloatValue = Value / 1000;
                    break;
                case 4 :
                    OffsetApproximation = OffsetApproximation * 1000;
                    Value = Value + OffsetApproximation;//5000;
                    FloatValue = Value / 10000;
                    break;
                case 5 :
                    OffsetApproximation = OffsetApproximation * 10000;
                    Value = Value + OffsetApproximation;//50000;
                    FloatValue = Value / 100000;
                    break;                    
            }            
            break;
        case 2 ://This Parameter is Two Digital under the Float Point.
            switch(FloatCount)
            {
                case 0 :
                    FloatValue = Value * 10;
                    break;
                case 1 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 10;
                    break;
                case 2 :
                    FloatValue = Value / 10;                    
                    break;
                case 3 :
                    OffsetApproximation = OffsetApproximation * 10;
                    Value = Value + OffsetApproximation;//50;
                    FloatValue = Value / 100;
                    break;
                case 4 :
                    OffsetApproximation = OffsetApproximation * 100;
                    Value = Value + OffsetApproximation;//500;
                    FloatValue = Value / 1000;
                    break;
                case 5 :
                    OffsetApproximation = OffsetApproximation * 1000;
                    Value = Value + OffsetApproximation;//5000;
                    FloatValue = Value / 10000;
                    break;                     
            }            
            break;
        case 3 ://This Parameter is Three Digital under the Float Point.
            switch(FloatCount)
            {
                case 0 :
                    FloatValue = Value * 100;
                    break;
                case 1 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 100;
                    break;
                case 2 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 10;
                    break;
                case 3 :
                    FloatValue = Value / 10;
                    break;
                case 4 :
                    OffsetApproximation = OffsetApproximation * 10;
                    Value = Value + OffsetApproximation;//50;
                    FloatValue = Value / 100;
                    break;
                case 5 :
                    OffsetApproximation = OffsetApproximation * 100;
                    Value = Value + OffsetApproximation;//500;
                    FloatValue = Value / 1000;
                    break;                      
            }            
            break;
        case 4 ://This Parameter is Four Digital under the Float Point.
            switch(FloatCount)
            {
                case 0 :
                    FloatValue = Value * 1000;
                    break;
                case 1 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 1000;
                    break;
                case 2 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 100;
                    break;
                case 3 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 10;
                    break;
                case 4 :
                    FloatValue = Value / 10;
                    break;
                case 5 :
                    OffsetApproximation = OffsetApproximation * 10;
                    Value = Value + OffsetApproximation;//50;
                    FloatValue = Value / 100;
                    break;                      
            }            
            break;
        case 5 ://This Parameter is Five Digital under the Float Point.
            switch(FloatCount)
            {
                case 0 :
                    FloatValue = Value * 10000;
                    break;
                case 1 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 10000;
                    break;
                case 2 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 1000;
                    break;
                case 3 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 100;
                    break;
                case 4 :
                    FloatValue = Value / 10;
                    FloatValue = FloatValue * 10;
                    break;
                case 5 :
                    FloatValue = Value / 10;
                    break;                      
            }
            break;                 
    }
    return FloatValue;
}

extern void Send_FAN1_uCHMI_SystemParameter(void);
extern void Send_FAN2_uCHMI_SystemParameter(void);
extern void Send_Heater_uCHMI_SystemParameter(void);
extern void Send_Wheel_uCHMI_SystemParameter(void);
extern void Send_PCD_6_20_uCHMI_SystemParameter(void);
extern void Send_PCD_2_V21_uCHMI_SystemParameter(void);
extern void Send_PCD22_25_uCHMI_SystemParameter(void);
void GetFAN1_1_SystemParameter(unsigned char FloatCount, long Value)
{
    switch(SystemParameterId)
    {
        case 5 :
        case 7 :
            Value = GetFloatTypeKeyBoardValue(4, FloatCount, Value);
            break;
        case 6 :
            Value = GetFloatTypeKeyBoardValue(2, FloatCount, Value);
            break;
        case 8 :
        case 10 :
        case 11 :            
            Value = GetFloatTypeKeyBoardValue(1, FloatCount, Value);
            break;
        case 1 :
        case 2 :
        case 3 :
        case 4 :
        case 9 :
        case 12 :
        case 13 :
        case 14 :
        case 15 :
        case 16 :
            Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
            break;
    }
    
    switch(SystemParameterId)
    {                
        case 1 :
            SystemParameter.FAN1_1.value.SuperHighPressureAlarmSet = Value;
            break;
        case 2 :
            SystemParameter.FAN1_1.value.HighPressureAlarmSet = Value;
            break;
        case 3 :
            SystemParameter.FAN1_1.value.LowPressureAlarmSet = Value;
            break;
        case 4 :
            SystemParameter.FAN1_1.value.SuperLowPressureAlarmSet = Value;
            break;
        case 5 :
            SystemParameter.FAN1_1.value.PID_P = Value;
            break;
        case 6 :
            SystemParameter.FAN1_1.value.PID_I = Value;
            break;
        case 7 :
            SystemParameter.FAN1_1.value.PID_D = Value;
            break;
        case 8 :
            SystemParameter.FAN1_1.value.DeadBand = Value;
            break;
        case 9 :
            SystemParameter.FAN1_1.value.FAN1_LowLimit = Value;
            break;
        case 10 :
            SystemParameter.FAN1_1.value.FAN1_High2 = Value;
            break;
        case 11 :
            SystemParameter.FAN1_1.value.FAN1_High1 = Value;
            break;
        case 12 :
            SystemParameter.FAN1_1.value.FAN1_1_2_DelayTime = Value;
            break;
        case 13 :
            SystemParameter.FAN1_1.value.ManualStartFrequency = Value;
            break;
        case 14 :
            SystemParameter.FAN1_1.value.ManualStopFrequency = Value;
            break;
        case 15 :
            SystemParameter.FAN1_1.value.FAN1_1ManualOpenSize = Value;
            break;
        case 16 :
            SystemParameter.FAN1_1.value.PT_1 = Value;
            break;            
    }
    switch(SystemParameterId)
    {                
        case 1 :
        case 2 :
        case 3 :
        case 4 :
        case 5 :
        case 6 :
        case 7 :
        case 8 :
        case 9 :
        case 10 :
        case 11 :
        case 12 :
        case 13 :
        case 14 :
        case 15 :
        case 16 :
            COM3_Send_FAN1_Command();
            Send_FAN1_uCHMI_SystemParameter();
            break;            
    }
    
}

void GetFAN2_SystemParameter(unsigned char FloatCount, long Value)
{
    Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
    switch(SystemParameterId)
    {
        case 17 :
            SystemParameter.FAN_2.value.FAN_2_Target_Temp1 = Value;
            break;
        case 18 :
            SystemParameter.FAN_2.value.FAN_2_Target_Temp2 = Value;
            break;
        case 19 :
            SystemParameter.FAN_2.value.FAN_2_Target_Temp3 = Value;
            break;
        case 20 :
            SystemParameter.FAN_2.value.FAN_2_Top = Value;
            break;
        case 21 :
            SystemParameter.FAN_2.value.FAN_2_Low = Value;
            break;               
        case 22 :
            SystemParameter.FAN_2.value.FAN_2_TargetTemp1_Hz = Value;
            break;
        case 23 :
            SystemParameter.FAN_2.value.FAN_2_TargetTemp2_Hz = Value;
            break;
        case 24 :
            SystemParameter.FAN_2.value.FAN_2_TargetTemp3_Hz = Value;
            break;            
    }
    
    switch(SystemParameterId)
    {
        case 17 :
        case 18 :
        case 19 :
        case 20 :            
        case 21 :
        case 22 :
        case 23 :
        case 24 :
            COM3_Send_FAN2_Command();
            Send_FAN2_uCHMI_SystemParameter();
            break;            
    }
}

void GetSCR_SystemParameter(unsigned char FloatCount, long Value)
{
    switch(SystemParameterId)
    {
        case 32 :
        case 38 :
        case 39 :
            Value = GetFloatTypeKeyBoardValue(1, FloatCount, Value);
            break;
        case 24 :
        case 25 :
        case 26 :
        case 27 :
        case 28 :
        case 29 :
        case 30 :
        case 31 :
        case 33 :
        case 34 :
        case 35 :
        case 36 :
        case 37 :
        case 40 :
        case 41 :         
        case 42 :
        case 43 :
            Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
            break;
    }
    
    switch(SystemParameterId)
    {
        case 25 :
            SystemParameter.HeaterSet.value.OP_Temp = Value;
            break;
        case 26 :
            SystemParameter.HeaterSet.value.StandBy_Temp = Value;
            break;
        case 27 :
            SystemParameter.HeaterSet.value.KeepWarmTemp = Value;
            break;
        case 28 :
            SystemParameter.HeaterSet.value.SuperHighTemp = Value;
            break;
        case 29 :
            SystemParameter.HeaterSet.value.HighTemp = Value;
            break;
        case 30 :
            SystemParameter.HeaterSet.value.LowTemp = Value;
            break;
        case 31 :
            SystemParameter.HeaterSet.value.SuperLowTemp = Value;
            break;
        case 32 :
            SystemParameter.HeaterSet.value.PID_P = Value;
            break; 
        case 33 :
            SystemParameter.HeaterSet.value.PID_I = Value;
            break;
        case 34 :
            SystemParameter.HeaterSet.value.PID_D = Value;
            break;
        case 35 :
            SystemParameter.HeaterSet.value.DeadBand = Value;
            break;
        case 36 :
            SystemParameter.HeaterSet.value.MoreThanSP_StopTemp = Value;
            break;
        case 37 :
            SystemParameter.HeaterSet.value.LessThanSP_StartTemp = Value;
            break;
        case 38 :
            SystemParameter.HeaterSet.value.TopLimit = Value;
            break;
        case 39 :
            SystemParameter.HeaterSet.value.LowLimit = Value;
            break;
        case 40 :
            SystemParameter.HeaterSet.value.FireCount = Value;
            break;
        case 41 :
            SystemParameter.HeaterSet.value.ReFireTemp = Value;
            break;
        case 42 :
            SystemParameter.HeaterSet.value.ManualOpenSize = Value;
            break;            
        case 43 :
            SystemParameter.HeaterSet.value.CleanOvenTime = Value;
            break;
    }
    
    switch(SystemParameterId)
    {
        case 24 :
        case 25 :
        case 26 :
        case 27 :
        case 28 :
        case 29 :
        case 30 :
        case 31 :
        case 32 :
        case 33 :
        case 34 :
        case 35 :
        case 36 :
        case 37 :
        case 38 :
        case 39 :
        case 40 :
        case 41 :         
        case 42 :
        case 43 :
            COM3_Send_Heater_Command();
            Send_Heater_uCHMI_SystemParameter();            
            break;
    }
}

void GetWheel_SystemParameter(unsigned char FloatCount, long Value)
{
    switch(SystemParameterId)
    {
        case 44 :
        case 45 :
        case 46 :          
        case 48 :
            Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
            break;
        case 47 :
        case 49 :
        case 50 :
        case 51 :
        case 52 :
            Value = GetFloatTypeKeyBoardValue(1, FloatCount, Value);
            break;
    }

    switch(SystemParameterId)
    {
        case 44 :
            SystemParameter.Wheel.value.T5_CheckTemp1 = Value;
            break;
        case 45 :
            SystemParameter.Wheel.value.T5_CheckTemp2 = Value;
            break;
        case 46 :
            SystemParameter.Wheel.value.T5_CheckTemp3 = Value;
            break;
        case 47 :
            SystemParameter.Wheel.value.TopLimitFrequency = Value;
            break;            
        case 48 :
            SystemParameter.Wheel.value.StopTemp = Value;
            break;            
        case 49 :
            SystemParameter.Wheel.value.T5_CheckTemp1Frequency = Value;
            break;
        case 50 :
            SystemParameter.Wheel.value.T5_CheckTemp2Frequency = Value;
            break;
        case 51 :
            SystemParameter.Wheel.value.T5_CheckTemp3Frequency = Value;
            break;
        case 52 :
            SystemParameter.Wheel.value.LowLimitFrequency = Value;
            break;
    }
    
    switch(SystemParameterId)
    {
        case 44 :
        case 45 :
        case 46 :
        case 47 :          
        case 48 :           
        case 49 :
        case 50 :
        case 51 :
        case 52 :
            COM3_Send_MTR4_Command();
            Send_Wheel_uCHMI_SystemParameter();            
            break;
    }
}
        

void GetPCD6_20_SystemParameter(unsigned char FloatCount, long Value)
{
    switch(SystemParameterId)
    {
        case 63 :
        case 64 :
            Value = GetFloatTypeKeyBoardValue(5, FloatCount, Value);
            break;
        case 65 :
            Value = GetFloatTypeKeyBoardValue(4, FloatCount, Value);
            break;
        case 66 :
            Value = GetFloatTypeKeyBoardValue(2, FloatCount, Value);
            break;
        case 55 :
        case 56 :
        case 57 :
        case 58 :
        case 59 :
        case 60 :
        case 61 :
        case 62 :
        case 67 :
        case 68 :
        case 69 :
            Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
            break;
    }
    
    switch(SystemParameterId)
    {
        case 55 :
            SystemParameter.PCD_6.value.FaultDelayTime = Value;
            break;
        case 56 :
            SystemParameter.PCD_6.value.AlarmDelayTime = Value;
            break;
        case 57 :
            SystemParameter.PCD_20.value.OP_Temp = Value;
            break;
        case 58 :
            SystemParameter.PCD_20.value.StandByTemp = Value;
            break;
        case 59 :
            SystemParameter.PCD_20.value.CoolingTemp = Value;
            break;
        case 60 :
            SystemParameter.PCD_20.value.FaultDelayTime = Value;
            break;
        case 61 :
            SystemParameter.PCD_20.value.AlarmDelayTime = Value;
            break;
        case 62 :
            SystemParameter.PCD_20.value.OnOFFDelayTime = Value;
            break;  
        case 63 :
            SystemParameter.PCD_20.value.PID_P = Value;
            break;
        case 64 :
            SystemParameter.PCD_20.value.PID_I = Value;
            break;
        case 65 :
            SystemParameter.PCD_20.value.PID_D = Value;
            break;
        case 66 :
            SystemParameter.PCD_20.value.DeadBand = Value;
            break;
        case 67 :
            SystemParameter.PCD_20.value.TopLimit = Value;
            break;            
        case 68 :
            SystemParameter.PCD_20.value.LowLimit = Value;
            break;
        case 69 :
            SystemParameter.PCD_20.value.ManualOpenSize = Value;
            break;
    }
    
    switch(SystemParameterId)
    {
        case 55 :
        case 56 :
        case 57 :
        case 58 :
        case 59 :
        case 60 :
        case 61 :
        case 62 :
        case 63 :        
        case 64 :
        case 65 :
        case 66 :
        case 67 :
        case 68 :
        case 69 :
            COM3_Send_PCD20_Command();
            Send_PCD_6_20_uCHMI_SystemParameter();            
            break;
    }
}


void GetPCD2_V21_SystemParameter(unsigned char FloatCount, long Value)
{
    Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
    switch(SystemParameterId)
    {
        case 53 :
            SystemParameter.PCD2.Value.FaultDelayTime = Value;
            break;
        case 54 :
            SystemParameter.PCD2.Value.AlarmDelayTime = Value;
            break;        
        case 70 :
            SystemParameter.V21.Value.FaultDelayTime = Value;
            break;
        case 71 :
            SystemParameter.V21.Value.AlarmDelayTime = Value;
            break;
    }
    
    switch(SystemParameterId)
    {
        case 53 :
        case 54 :
        case 70 :      
        case 71 :
            Send_PCD_2_V21_uCHMI_SystemParameter();
            break;
    }
}

void GetPCD22_25SystemParameter(unsigned char FloatCount, long Value)
{
    switch(SystemParameterId)
    {
        case 72 :
        case 73 :
        case 74 :
        case 75 :
        case 76 :
        case 77 :
        case 78 :        
        case 79 :
        case 80 :
        case 81 :
            Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
            break;
    }
    
    switch(SystemParameterId)
    {
        case 72 :
            SystemParameter.PCD_22.value.FaultDelayTime = Value;
            break;
        case 73 :
            SystemParameter.PCD_22.value.AlarmDelayTime = Value;
            break;
        case 74 :
            SystemParameter.PCD_22.value.ReleaseTemp = Value;
            break;
        case 75 :
            SystemParameter.PCD_22.value.OnOFFDelayTime = Value;
            break;
        case 76 :
            SystemParameter.PCD_25.value.FaultDelayTime = Value;
            break;
        case 77 :
            SystemParameter.PCD_25.value.AlarmDelayTime = Value;
            break;  
        case 78 :
            SystemParameter.PCD_25.value.OnOFFDelayTime = Value;
            break;
        case 79 :
            SystemParameter.PCD_25.value.TopLimit = Value;
            break;
        case 80 :
            SystemParameter.PCD_25.value.LowLimit = Value;
            break;
        case 81 :
            SystemParameter.PCD_25.value.ManualOpenSize = Value;
            break;
    }
    
    switch(SystemParameterId)
    {
        case 72 :
        case 73 :
        case 74 :
        case 75 :
        case 76 :
        case 77 :
        case 78 :        
        case 79 :
        case 80 :
        case 81 :
            COM3_Send_PCD22_Command();
            COM3_Send_PCD25_Command();
            Send_PCD22_25_uCHMI_SystemParameter();
            break;
    }    
}

extern void Set_uCHMI_RtcDate(unsigned int Year, unsigned int Month, unsigned int Day);
extern void Set_uCHMI_RtcTime(unsigned int Hour, unsigned int Min, unsigned int Sec);
void SetSystemDateTime(unsigned char FloatCount, long Value)
{
    unsigned int Year, Month, Day;
    unsigned int Hour, Min, Sec;
    
    if( (FloatCount == 0) && (Value > 0) )
    {
        Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
        switch(SystemParameterId)
        {
            case -1 :
                Year = Value / 10000;
                Month = (Value/100)%100;
                Day = Value % 100;
                Set_uCHMI_RtcDate(Year, Month, Day);
                break;
            case -2 :
                Hour = Value / 10000;
                Min = (Value/100)%100;
                Sec = Value % 100;
                Set_uCHMI_RtcTime(Hour, Min, Sec);                
                break;
        }
    }    
}

extern void Send_AlarmTypeA_uCHMI_SystemParameter(void);
extern void Send_AlarmTypeB_uCHMI_SystemParameter(void);
extern void Send_BurnSystemAlarm_uCHMI_SystemParameter(void);
extern void Send_WheelAlarm_uCHMI_SystemParameter(void);
extern void Send_AlarmTypeD_uCHMI_SystemParameter(void);
extern void Send_AlarmTypeD1_uCHMI_SystemParameter(void);

void GetAlarmTypeASystemParameter(unsigned char FloatCount, long Value)
{
    Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
    switch(SystemParameterId)
    {
        case -3 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE8 = Value;
            break;
        case -4 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5 = Value;
            break;
        case -5 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5GTwhenTE3 = Value;
            break;
        case -6 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE3Offset = Value;
            break;
        case -7 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A1_TE5GTwhenFAN2Stop = Value;
            break;        
        case -8 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE8 = Value;
            break;
        case -9 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5 = Value;
            break;
        case -10 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5GTwhenTE3 = Value;
            break;
        case -11 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE3Offset = Value;
            break;
        case -12 :
            SystemParameter.Alarm.Value.AlarmTypeASet.A2_TE5LTwhenFAN2Stop = Value;
            break;
    }
    
    switch(SystemParameterId)
    {
        case -3 :
        case -4 :
        case -5 :
        case -6 :
        case -7 :        
        case -8 :
        case -9 :
        case -10 :
        case -11 :
        case -12 :
            Send_AlarmTypeA_uCHMI_SystemParameter();
            break;
    }
}

void GetAlarmTypeBSystemParameter(unsigned char FloatCount, long Value)
{
    Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
    switch(SystemParameterId)
    {
        case -13 :
            SystemParameter.Alarm.Value.AlarmTypeBSet.TE5 = Value;
            break;
        case -14 :
            SystemParameter.Alarm.Value.AlarmTypeBSet.TE5GTwhenFAN2Stop = Value;
            break;
    }
    
    switch(SystemParameterId)
    {
        case -13 :
        case -14 :
            Send_AlarmTypeB_uCHMI_SystemParameter();
            break;
    }    
}

void GetBurnSystemAlarmSystemParameter(unsigned char FloatCount, long Value)
{
    Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
    switch(SystemParameterId)
    {
        case -15 :
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighTE11 = Value;
            break;
        case -16 :
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowTE11 = Value;
            break;
        case -17 :
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighTE12 = Value;
            break;
        case -18 :
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowTE12 = Value;
            break;
        case -19 :
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighPDT2 = Value;
            break;
        case -20 :
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowPDT2 = Value;
            break;
        case -21 :
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperHighPDT3 = Value;
            break;
        case -22 :
            SystemParameter.Alarm.Value.BurnSystemAlarmSet.SuperLowPDT3 = Value;
            break;            
    }
    
    switch(SystemParameterId)
    {
        case -15 :
        case -16 :
        case -17 :
        case -18 :
        case -19 :
        case -20 :
        case -21 :
        case -22 :
            Send_BurnSystemAlarm_uCHMI_SystemParameter();
            break;
    }
}

void GetWheelAlarmSystemParameter(unsigned char FloatCount, long Value)
{
    Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
    switch(SystemParameterId)
    {
        case -23 :
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE3 = Value;
            break;
        case -24 :
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE3 = Value;
            break;
        case -25 :
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE8 = Value;
            break;
        case -26 :
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighPDT1 = Value;
            break;
        case -27 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE3 = Value;
            break;
        case -28 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE3 = Value;
            break;
        case -29 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE5 = Value;
            break;
        case -30 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE5 = Value;
            break;
        case -31 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE8 = Value;
            break;
        case -32 :
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE8 = Value;
            break;
        case -33 :
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperHighTE5 = Value;
            break;
        case -34 :
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowTE5 = Value;
            break;
        case -35 :
            SystemParameter.Alarm.Value.WheelAlarmSet.SuperLowPDT1 = Value;
            break;
        case -36 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE8 = Value;
            break;
        case -37 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE11 = Value;
            break;
        case -38 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE11 = Value;
            break;
        case -39 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE12 = Value;
            break;
        case -40 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE12 = Value;
            break;            
    }
    
    switch(SystemParameterId)
    {
        case -23 :
        case -24 :
        case -25 :
        case -26 :
        case -32 :
        case -33 :
        case -34 :
        case -35 :
            Send_WheelAlarm_uCHMI_SystemParameter();
            break;
        case -27 :
        case -28 :
        case -29 :
        case -30 :
        case -31 :            
        case -36 :
        case -37 :
        case -38 :
        case -39 :
        case -40 :
            Send_AlarmTypeD_uCHMI_SystemParameter();
            break;
    }
}

void GetAlarmTypeD1SystemParameter(unsigned char FloatCount, long Value)
{
    Value = GetFloatTypeKeyBoardValue(0, FloatCount, Value);
    switch(SystemParameterId)
    {   
        case -41 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE14 = Value;
            break;
        case -42 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE14 = Value;
            break;
        case -43 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighTE1 = Value;
            break;
        case -44 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowTE1 = Value;
            break;
        case -45 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighPDT1 = Value;
            break;
        case -46 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowPDT1 = Value;
            break;
        case -47 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighPDT2 = Value;
            break;
        case -48 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowPDT2 = Value;
            break;
        case -49 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperHighPDT3 = Value;
            break;
        case -50 :
            SystemParameter.Alarm.Value.AlarmTypeDSet.SuperLowPDT3 = Value;
            break;          
    }
    
    switch(SystemParameterId)
    {
        case -41 :
        case -42 :
        case -43 :
        case -44 :
        case -45 :
        case -46 :
        case -47 :
        case -48 :
        case -49 :
        case -50 :
            Send_AlarmTypeD1_uCHMI_SystemParameter();
            break;             
    }
}
extern void SaveSystemParameter(unsigned int addr);//Philip 20220315 0.0.1 
void GetKeyBoardValue(unsigned int addr, unsigned char count, long Value)
{
    long FloatCount;
    unsigned char FloatCnt;
    
    switch(addr)
    {
        case KEYBOARD_VALUE_OUT_ADDR :
            if( count == 1 )
            {
                FloatCount = Value%10;
                if( FloatCount < 0 )
                    FloatCnt = (unsigned char)(0 - FloatCount);
                else
                    FloatCnt = (unsigned char)FloatCount;
//Philip 20220315 0.0.1 ======================================================================                
                switch(SystemParameterId)
                {
                    case -1 :case -2 :
                        SetSystemDateTime(FloatCnt, Value);
                        break;
                    default :
                        GetFAN1_1_SystemParameter(FloatCnt, Value);
                        GetFAN2_SystemParameter(FloatCnt, Value);
                        GetSCR_SystemParameter(FloatCnt, Value);
                        GetWheel_SystemParameter(FloatCnt, Value);
                        GetPCD6_20_SystemParameter(FloatCnt, Value);
                        GetPCD2_V21_SystemParameter(FloatCnt, Value);
                        GetPCD22_25SystemParameter(FloatCnt, Value);
                        GetAlarmTypeASystemParameter(FloatCnt, Value);
                        GetAlarmTypeBSystemParameter(FloatCnt, Value);
                        GetBurnSystemAlarmSystemParameter(FloatCnt, Value);
                        GetWheelAlarmSystemParameter(FloatCnt, Value);
                        GetAlarmTypeD1SystemParameter(FloatCnt, Value);
                        SaveSystemParameter(SYSTEM_PARAMETER_START_ADDR);
                        break;
                }
//Philip 20220315 0.0.1 ======================================================================                
            }
            break;
    }
}

 
    
    