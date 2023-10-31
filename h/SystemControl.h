/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   SystemControl.h
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SYSTEM_CONTROL_H
#define	SYSTEM_CONTROL_H

#define ANDROID_HMI 1//20220315 0.0.1//
#define RECORD_ITEM_NUM 12

#define KEYBOARD_VALUE_OUT_ADDR 0xD7
#define SYSTEM_PARAMETER_INPUT_ID_ADDR 0xE6
#define RECORD_POSITION_ADDR 272
#define UC_HMI_TIME_CODE_ADDR 290
#define UC_HMI_DATE_CODE_ADDR 291
#define START_READ_SD_INDEX_ADDR 299
#define GET_READ_SD_INDEX_ADDR 301
#define READ_RECORD_DATA_ADDR 303

#define PLAY_BACK_SHOW_CHART1_VIEW_FAR_CLOSE_BTN 437
#define PLAY_BACK_SHOW_CHART2_VIEW_FAR_CLOSE_BTN 438
#define PLAY_BACK_SHOW_CHART3_VIEW_FAR_CLOSE_BTN 439
#define PLAY_BACK_SHOW_CHART1_GO_BTN 440
#define PLAY_BACK_SHOW_CHART2_GO_BTN 441
#define PLAY_BACK_SHOW_CHART3_GO_BTN 442

#define PLAY_BACK_CHART1_PREV_DAY_ADDR 458
#define PLAY_BACK_CHART1_NEXT_DAY_ADDR 459
#define PLAY_BACK_CHART2_PREV_DAY_ADDR 460
#define PLAY_BACK_CHART2_NEXT_DAY_ADDR 461
#define PLAY_BACK_CHART3_PREV_DAY_ADDR 462
#define PLAY_BACK_CHART3_NEXT_DAY_ADDR 463
#define START_CHART1_PLAY_BACK_ADDR 472
#define START_CHART2_PLAY_BACK_ADDR 473
#define START_CHART3_PLAY_BACK_ADDR 474

#define MTR4_MANUAL_OPEN_BTN 608
#define MTR4_MANUAL_CLOSE_BTN 609
#define PCD20_OPEN_BTN 610
#define PCD20_CLOSE_BTN 611
#define FAN1_1MANUAL_OPEN_BTN 612
#define FAN1_1MANUAL_CLOSE_BTN 613
#define FAN2_MANUAL_OPEN_BTN 614
#define FAN2_MANUAL_CLOSE_BTN 615
#define PCD22_MANUAL_OPEN_BTN 616
#define PCD22_MANUAL_CLOSE_BTN 617
#define PCD25_MANUAL_OPEN_BTN 618
#define PCD25_MANUAL_CLOSE_BTN 619
//Philip 20220324 0.0.1 ===========================
#define PCD2_MANUAL_OPEN_BTN 640
#define PCD2_MANUAL_CLOSE_BTN 641
#define PCD6_MANUAL_OPEN_BTN 642
#define PCD6_MANUAL_CLOSE_BTN 643
#define V21_MANUAL_OPEN_BTN 644
#define V21_MANUAL_CLOSE_BTN 645
#define SYSTEM_AUTO_START_BTN 646
#define SYSTEM_AUTO_STOP_BTN 647
//Philip 20220324 0.0.1 ===========================
#define BUTTON_STATE1_ADDR 51
#define BUTTON_STATE2_ADDR 52
#define BUTTON_STATE3_ADDR 53

#define FLOAT_LOW_DIGITAL 100
#define FLOAT_MID_DIGITAL 10000
#define FLOAT_HIGH_DIGITAL 100000

#define PWM_SOURCE_FREQ_KHZ 7500//7500 pulse/msec
#define PWM_SOURCE_FREQ_HZ 7500000//7500000 pulse/sec
#define PWM_SOURCE_FREQ_10HZ 750000//7500000 pulse/0.1sec
#define PWM_MAX_PULSE_RATE 1875//1875 pulse/msec
#define MAX_PATTERN_NUMBER 5
#define LENGTH_OF_CMD_PACKAGE 12

#define EEPROM_PAGE_WRITE_SIZE 16//Philip 20180627 02 
#define ADC_MAX_NUM 4
#define REFERENCE_POSITION 0
#define UART1_SENDING_DELAY_TIME 10

#define UART1_BUFFER_SIZE 100
#define UART1_PACKET_SIZE 11

#define UART2_BUFFER_SIZE 100
#define UART2_PACKET_SIZE 12

#define UART3_BUFFER_SIZE 100
#define UART3_PACKET_SIZE 11

#define MAX_READ_TEXT_SIZE 46//46 = (100 - 8) / 2 ==> 8 = 0xAF, Size, ID, Addr, CRC16, 0xEF
#define MAX_WRITE_TEXT_SIZE 46//46 = (100 - 8) / 2 ==> 8 = 0xAF, Size, ID, Addr, CRC16, 0xEF

#define PWM_MAX_PULSE_WIDTH 7500
#define PWM_PULSE_WIDTH_OFFSET 1//Philip 20200313 02//200
#define KEYBOARD_MAX_ADC_VALUE 4095

//#define U2_RS422_SIZE 10
//#define U3_RS422_SIZE 11
enum SystemDelayTimerEnum
{
    SystemDelayTimerEnum=0,
    DAC_TimeOut_CounterEnum,
    UART3_SendTimerEnum,
    UART1_SendingDelayEnum,
    DummyTimer5,
    UART_ResponseDelayEnum,
    EEPROM_Delay_Timer_Count,
    ParameterLoadTimeEnum,
    DummyTimer9,//COM3_RX_TIMER_ENUM,
    COM3_TX_TIMER_ENUM,
    
    DummyTimer11,    
    COM2_TX_TIMER_ENUM,
    DummyTimer13,
    
    SystemDelayTimerEnumEnd
};


enum SystemInitialEnum
{
    SystemLoadSystemParameterEnum=0,
    waitSystemLoadSystemParameterEnum,
    waitSystemLoadRunTimeStatusEnum,
    SystemFinishLoadSystemParamterEnum,
    SystemStartRunningEnum,
    
    SystemLoadSystemParameterFaultEnum,
    
    SystemInitialEnumEnd
};

enum UART2PacketEnum
{
    UART2PacketCmd=0,
    UART2PacketNumberLB,
    UART2PacketNumberHB,
    UART2Packet1stParameter,
    
    UART2crcHB=9,
    UART2crcLB,
    
    UART2PacketEnumEnd
};

enum Android_HMI_CommandEnum
{
    Android_HMI_GetFirmwareVersionCommandEnum=0,//0
    Android_HMI_GetExtFirmwareVersionCommandEnum,//1
    Android_HMI_Fan1_1_GetSV_CommandEnum,//2
    Android_HMI_Fan1_1_GetPI_CommandEnum,
    Android_HMI_Fan1_1_GetD_LowLimit_CommandEnum,//4
    Android_HMI_Fan1_1_GetTopLimit_CommandEnum,//5
    Android_HMI_Fan1_1_GetManualSet_CommandEnum,//6
    Android_HMI_Fan2_GetTempSetSpeedTopLimit_CommandEnum,
    Android_HMI_Fan2_GetSpeedSet_CommandEnum,//8
    Android_HMI_Heater_TempSetDb_CommandEnum,
    Android_HMI_Heater_TempHH2LLSet_CommandEnum,//10
    Android_HMI_HeaterSP2LowLimitSet_CommandEnum,
    Android_HMI_HeaterPI_Set_CommandEnum,//12
    Android_HMI_HeaterD2_ManualSet_CommandEnum,//13
    Android_HMI_MTR4_TE5ConditionSet_CommandEnum,//14
    Android_HMI_MTR4_TE5SpeedSet_CommandEnum,
    Android_HMI_MTR4_TopStopTempLowSet_CommandEnum,//16
    Android_HMI_PCD2_V21Set_CommandEnum,
    Android_HMI_PCD20_Temp_SizeSet_CommandEnum,//18
    Android_HMI_PCD20_PISet_CommandEnum,
    Android_HMI_PCD20_D_TimeSet_CommandEnum,//20
    Android_HMI_PCD20_DeadTopLowLimit_PCD6TimeSet_CommandEnum,
    Android_HMI_PCD22_Set_CommandEnum,//22
    Android_HMI_PCD25_PCD6_TimeSet_CommandEnum,
    Android_HMI_PCD25_Limit_ManualSet_CommandEnum,//24
    
    Android_HMI_Alarm_A1_Set_CommandEnum,//25
    Android_HMI_Alarm_A1_A2_Set_CommandEnum,//26
    Android_HMI_Alarm_A2_B_Set_CommandEnum,
    Android_HMI_HeaterTempAlarm_Set_CommandEnum,//28
    Android_HMI_HeaterPDTAlarm_Set_CommandEnum,
    Android_HMI_MTR4TempAlarm_Set_CommandEnum,//30
    Android_HMI_MTR4TempPDTAlarm_Set_CommandEnum,
    Android_HMI_D_Alarm1_Set_CommandEnum,//32
    Android_HMI_D_Alarm2_Set_CommandEnum,
    Android_HMI_D_Alarm3__D1_Set_CommandEnum,//34
    Android_HMI_D1_Alarm2_Set_CommandEnum,//35
    Android_HMI_D1_Alarm3_Set_CommandEnum,//36
    
     Android_HMI_Button_CommandEnum,//37 //Philip 20220325 0.0.1
     Android_HMI_Dummy38_CommandEnum,//38
     Android_HMI_Dummy39_CommandEnum,
     Android_HMI_Dummy40_CommandEnum,//40
     Android_HMI_Dummy41_CommandEnum,
     Android_HMI_Dummy42_CommandEnum,//42
     Android_HMI_Dummy43_CommandEnum,
     Android_HMI_Dummy44_CommandEnum,//44
     Android_HMI_Dummy45_CommandEnum,
     Android_HMI_Dummy46_CommandEnum,//46
     Android_HMI_Dummy47_CommandEnum,
     Android_HMI_Dummy48_CommandEnum,//48    
     Android_HMI_Dummy49_CommandEnum,
     Android_HMI_WriteParameter_CommandEnum,//50
     
     Android_HMI_RunTimeTE1_3_5_6_CommandEnum,//51
     Android_HMI_RunTimeTE8_10_11_12_CommandEnum,//52
     Android_HMI_RunTimePDT1_2_3_CommandEnum,
     Android_HMI_FAN1_RunTime_CommandEnum,//54
     Android_HMI_FAN2_RunTime_CommandEnum,//55
     Android_HMI_MTR4_RunTime_CommandEnum,//56
     Android_HMI_Heater_RunTime_CommandEnum,
     Android_HMI_PCD_RunTime_CommandEnum,//58
     Android_HMI_UsingCount_RunTime_CommandEnum,
     Android_HMI_Alarm_RunTime_CommandEnum,//60//Philip 20220406 0.0.1
     Android_HMI_SystemStatus_RunTime_CommandEnum,//61//Philip 20220510 0.0.1
     Android_HMI_Alarm1_RunTime_CommandEnum,//62//Philip 20220526 0.0.1
    
    Android_HMI_CommandEnumEnd
};

typedef struct __RUNTIME_SHOW_STATUS_BITMAP
{
//Byte[0] =======================================================================
    unsigned char PDS1_1 : 1;//Pressure Switch at the Process Side
    unsigned char PDS_2 : 1;//Pressure Switch at the Drop-out Side
    unsigned char PDS_2_StartFault : 1;
    unsigned char PDS_2_RunningFault : 1;
    unsigned char PDS_2_StopFault : 1;
    unsigned char FAN_2_InverterFault : 1;
    unsigned char FAN_2_InverterStartFault : 1;
    unsigned char FAN_2_InverterStopFault : 1;
//Byte[1] =======================================================================
    unsigned char FAN_2_InverterRunningFault : 1;
    unsigned char SCR_En : 1;
    unsigned char SCR_StartHeating : 1;
    unsigned char SCR_FinishCleanOven : 1;
    unsigned char SCR_OvenOP_TempReady : 1;
    unsigned char SCR_DropOutOP_TempReady : 1;
    unsigned char SCR_HeatingFault : 1;
    unsigned char TwoTempSensorFault : 1;
//Byte[2] =======================================================================     
    unsigned char SCR_TempTooHigh : 1;
    unsigned char SCR_TempSuperHigh : 1;
    unsigned char SCR_TempSuperLow : 1;
    unsigned char TempSensor1Alarm : 1;
    unsigned char TempSensor2Alarm : 1;
    unsigned char SCR_HighTempAlarm : 1;
    unsigned char SCR_LowTempAlarm : 1;
    unsigned char PCD_2_OpenFault : 1;
//Byte[3] =======================================================================     
    unsigned char PCD_2_CloseFault : 1;
    unsigned char PCD_2_LimitFault : 1;
    unsigned char PCD_2_OpenAlarm : 1;
    unsigned char PCD_2_CloseAlarm : 1;
    unsigned char PCD_20_OpenFault : 1;
    unsigned char PCD_20_CloseFault : 1;
    unsigned char PCD_20_LimitFault : 1;
    unsigned char PCD_20_OpenAlarm : 1;
 //Byte[4] =======================================================================  
    unsigned char PCD_20_CloseAlarm : 1;
    unsigned char V21_OpenFault : 1;
    unsigned char V21_CloseFault : 1;
    unsigned char V21_LimitFault : 1;
    unsigned char V21_OpenAlarm : 1;
    unsigned char V21_CloseAlarm : 1;    
    unsigned char Dummy4 : 2;        
 //Byte[5] =======================================================================      
    
    
    unsigned int PT_1;//Byte[4], Pressure Sensor at the Process Side
    unsigned int PDT_1;//Byte[6], Pressure Sensor at the Wheel Input Side
    unsigned int PDT_2;//Byte[8], Pressure Sensor at the Wheel Output Side
    
    unsigned char FAN1_1;//Byte[10], Inverter Frequency(0 - 60Hz) 
    unsigned char FAN_2;//Byte[11], Inverter Frequency(0 - 60Hz)
    unsigned char FAN1_PID_Output;//0-100//Byte[12]
    unsigned char FAN2_ShowFrequency;//0-100//Byte[13]
//Temperature    
    unsigned int TE_1;//Byte[14], Temperature at the Input End of the Process Side
    unsigned int TE_3;//Byte[16], Temperature at the Input End of the Drop-out Side
    unsigned int TE_5;//Byte[18], Temperature at the output End of the Drop-out Side
    unsigned int TE_6;//Byte[20], Temperature in the Chimney
    unsigned int TE_8;//Byte[22], Temperature at the output End of the Drop-out Side
    unsigned int TE_10;//Byte[24], Temperature at the input End of the Recycle Side
    unsigned int TE_11A;//Byte[26], Temperature A In the Oxidation Oven
    unsigned int TE_11B;//Byte[28], Temperature B In the Oxidation Oven
    unsigned int TE_12;//Byte[30], Temperature In the  Output End of the Oxidation Oven
    
} _RUNTIME_SHOW_STATUS_BITMAP;

typedef union __RUNTIME_SHOW_STATUS
{
    unsigned char data[32];
    _RUNTIME_SHOW_STATUS_BITMAP bitmap;
    
} _RUNTIME_SHOW_STATUS;

typedef struct __FAN1_1_SETTING_VALUE
{
    int SuperHighPressureAlarmSet;//2Bytes
    int HighPressureAlarmSet;//4Bytes
    int LowPressureAlarmSet;//6Bytes
    int SuperLowPressureAlarmSet;//8Bytes
    int PT_1;//10Bytes
    unsigned int PID_I;//Sec//12Bytes
    unsigned int FAN1_High1;//0-100%//14Bytes
    unsigned int FAN1_High2;//0-100%//16Bytes
    unsigned int FAN1_1_2_DelayTime;//Sec//18Bytes
    unsigned int DeadBand;//0-100%//20Bytes
    unsigned int FAN1_1ManualOpenSize;//0 -100%//22Bytes
    unsigned char FAN1_LowLimit;//0-100%//23Bytes
    unsigned char ManualStartFrequency;//0-100%//24Bytes    
    
    long PID_P;//28Bytes
    unsigned long PID_D;//Sec//32Bytes

    unsigned char ManualStopFrequency;//0-100%//33Bytes
    unsigned char Dummy;//34Bytes
    
} _FAN1_1_SETTING_VALUE;

typedef union __FAN1_1_SETTING
{
    _FAN1_1_SETTING_VALUE value;
    unsigned char Byte[34];
} _FAN1_1_SETTING;


typedef struct __FAN2_SETTING_VALUE
{
    unsigned int FAN_2_Target_Temp1;//2Bytes
    unsigned int FAN_2_Target_Temp2;//4Bytes
    unsigned int FAN_2_Target_Temp3;//6Bytes        
    unsigned int FAN_2_Top;//Inverter MAx Frequency(0-60.0Hz)//8Bytes
    unsigned int FAN_2_Low;//Inverter Low Frequency(0-60.0Hz)//10Bytes
    unsigned int FAN_2_TargetTemp1_Hz;//Inverter Frequency(0-60.0Hz)//12Bytes    
    unsigned int FAN_2_TargetTemp2_Hz;//Inverter Frequency(0-60.0Hz)//14Bytes
    unsigned int FAN_2_TargetTemp3_Hz;//Inverter Frequency(0-60.0Hz)//16Bytes
    
//    unsigned char FAN_2;//Inverter Frequency(0-60Hz)//10Bytes
} _FAN2_SETTING_VALUE;//14Bytes

typedef union __FAN2_SETTING
{
    _FAN2_SETTING_VALUE value;
    unsigned char Byte[16];
} _FAN2_SETTING;

typedef struct __HEATER_SETTING_VALUE
{
    unsigned int OP_Temp;//0 - 400.0 deg//2Bytes
    unsigned int StandBy_Temp;//0 - 400.0 deg//4Bytes
    unsigned int KeepWarmTemp;//0 - 400.0 deg//6Bytes
    unsigned int SuperHighTemp;//0 - 400.0 deg//8Bytes
    unsigned int HighTemp;//0 - 400.0 deg//10Bytes
    unsigned int LowTemp;//0 - 400.0 deg//12Bytes
    unsigned int SuperLowTemp;//0 - 400.0 deg//14Bytes
    unsigned int MoreThanSP_StopTemp;//0 - 400.0 deg//16Bytes
    unsigned int LessThanSP_StartTemp;//0 - 400.0 deg//18Bytes
    unsigned int ReFireTemp;//0 - 400.0 deg//20Bytes
    long PID_P;//24Bytes
    unsigned int PID_I;//Unit : 10mSec//0 - 10.00Sec//26Bytes
    unsigned int PID_D;//Unit : 10mSec//0 - 10.00Sec//28Bytes
    unsigned int DeadBand;//30Bytes
    unsigned int FireCount;//0 - 999//32Bytes
    unsigned int TopLimit;//0 - 100.0%//34Bytes
    unsigned int LowLimit;//0 - 100.0%//36Bytes
    unsigned int ManualOpenSize;//0 - 100.0%//38Bytes
    unsigned int CleanOvenTime;//40Bytes
} _HEATER_SETTING_VALUE;

typedef union __HEATER_SETTING
{
    _HEATER_SETTING_VALUE value;
    unsigned char Byte[40];
    
} _HEATER_SETTING;

typedef struct __WHEEL_SETTING_VALUE
{
    unsigned int T5_CheckTemp1;//2Bytes
    unsigned int T5_CheckTemp2;//4Bytes
    unsigned int T5_CheckTemp3;//6Bytes
    unsigned int StopTemp;//8Bytes
    unsigned int T5_CheckTemp1Frequency;//0 - 60.0//10Bytes
    unsigned int T5_CheckTemp2Frequency;//0 - 60.0//12Bytes
    unsigned int T5_CheckTemp3Frequency;//0 - 60.0//14Bytes
    unsigned int TopLimitFrequency;//0 - 60.0//16Bytes
    unsigned int LowLimitFrequency;//0 - 60.0//18Bytes
    unsigned int Dummy1;//20Bytes
    unsigned long Dummy2;//24Bytes
} _WHEEL_SETTING_VALUE;

typedef union __WHEEL_SETTING
{
    _WHEEL_SETTING_VALUE value;
    unsigned char Byte[24];
} _WHEEL_SETTING;

typedef struct __PCD20_SETTING_VALUE
{
    unsigned int OP_Temp;//0 - 280.0//2Bytes
    unsigned int StandByTemp;//0 - 280.0//4Bytes
    unsigned int DeadBand;//0 - 255//6Bytes
    unsigned int FaultDelayTime;//0 - 999 Sec//8Bytes
    unsigned int AlarmDelayTime;//0 - 999 Sec//10Bytes
    unsigned int OnOFFDelayTime;//0 - 999 Sec//12Bytes
    unsigned int TopLimit;//0 - 100.0%//14Bytes
    unsigned int LowLimit;//0 - 100.0%//16Bytes
    unsigned int ManualOpenSize;//0 - 100.0%//18Bytes    
    unsigned int CoolingTemp;//0 - 280.0 deg//20Bytes      

    long PID_P;//24Bytes
    unsigned long PID_I;//Unit : 10mSec//28Bytes
    unsigned long PID_D;//Unit : 10mSec//32Bytes
} _PCD20_SETTING_VALUE;

typedef union __PCD20_SETTING
{
    _PCD20_SETTING_VALUE value;
    unsigned char Byte[32];
} _PCD20_SETTING;

typedef struct __PCD6_SETTING_VALUE
{
    unsigned int FaultDelayTime;//0 - 999 Sec//4Bytes
    unsigned int AlarmDelayTime;//0 - 999 Sec//6Bytes
} _PCD6_SETTING_VALUE;

typedef union __PCD6_SETTING
{
    _PCD6_SETTING_VALUE value;
    unsigned char ByteData[4];
} _PCD6_SETTING;


typedef struct __PCD22_SETTING_VALUE
{
    unsigned int FaultDelayTime;//0 - 999 Sec//4Bytes
    unsigned int AlarmDelayTime;//0 - 999 Sec//6Bytes
    unsigned int ReleaseTemp;//0 - 400.0 deg//2Bytes
    unsigned int OnOFFDelayTime;//0 - 999 Sec//8Bytes  
} _PCD22_SETTING_VALUE;

typedef union __PCD22_SETTING
{
    _PCD22_SETTING_VALUE value;
    unsigned char Byte[8];
} _PCD22_SETTING;

typedef struct __PCD25_SETTING_VALUE
{
    unsigned int FaultDelayTime;//0 - 999 Sec//2Bytes
    unsigned int AlarmDelayTime;//0 - 999 Sec//4Bytes
    unsigned int OnOFFDelayTime;//0 - 999 Sec//5Bytes
    unsigned int TopLimit;//0 - 100.0%//8Bytes
    unsigned int LowLimit;//0 - 100.0%//10Bytes
    unsigned int ManualOpenSize;//0 - 100.0%//12Bytes
    unsigned long Dummy1;//16Bytes  
} _PCD25_SETTING_VALUE;

typedef union __PCD25_SETTING
{
    _PCD25_SETTING_VALUE value;
    unsigned char Byte[16];
} _PCD25_SETTING;

typedef struct __PCD2_SETTING_VALUE
{
    unsigned int FaultDelayTime;
    unsigned int AlarmDelayTime;
} _PCD2_SETTING_VALUE;

typedef union __PCD2_SETTING
{
    _PCD2_SETTING_VALUE Value;
    unsigned char ByteData[4];
} _PCD2_SETTING;

typedef struct __V21_SETTING_VALUE
{
    unsigned int FaultDelayTime;
    unsigned int AlarmDelayTime;
} _V21_SETTING_VALUE;

typedef union __V21_SETTING
{
    _V21_SETTING_VALUE Value;
    unsigned char ByteData[4];
} _V21_SETTING;

//Philip 20220527 0.0.1 =========================Temp and PDT change from unsigned int to int===============
typedef struct __ALARM_TYPE_A_SET
{    
    int A1_TE8;
    int A1_TE5;
    int A1_TE5GTwhenTE3;
    int A1_TE3Offset;
    int A1_TE5GTwhenFAN2Stop;     
    int A2_TE8;
    int A2_TE5;
    int A2_TE5GTwhenTE3;
    int A2_TE3Offset;
    int A2_TE5LTwhenFAN2Stop;      
} _ALARM_TYPE_A_SET;

typedef struct __ALARM_TYPE_B_SET
{
    int TE5;
    int TE5GTwhenFAN2Stop;      
} _ALARM_TYPE_B_SET;

typedef struct __BURN_SYSTEM_ALARM_SET
{
    int SuperHighTE11;
    int SuperLowTE11;
    int SuperHighTE12;
    int SuperLowTE12;
    int SuperHighPDT2;
    int SuperLowPDT2;
    int SuperHighPDT3;
    int SuperLowPDT3;
} _BURN_SYSTEM_ALARM_SET;

typedef struct __WHEEL_ALARM_SET
{
    int SuperHighTE3;
    int SuperLowTE3;
    int SuperHighTE8;
    int SuperHighPDT1;
    int SuperLowTE8;
    int SuperHighTE5;
    int SuperLowTE5;
    int SuperLowPDT1;
} _WHEEL_ALARM_SET;

typedef struct __ALARM_TYPE_D_SET
{
    int SuperHighTE3;
    int SuperLowTE3;
    int SuperHighTE5;
    int SuperLowTE5;
    int SuperHighTE8;
    int SuperLowTE8;
    int SuperHighTE11;
    int SuperLowTE11;
    int SuperHighTE12;
    int SuperLowTE12;
//D1
    int SuperHighTE10;
    int SuperLowTE10;
    int SuperHighTE06;
    int SuperLowTE06;
    int SuperHighPDT1;
    int SuperLowPDT1;    
    int SuperHighPDT2;
    int SuperLowPDT2;
    int SuperHighPDT3;
    int SuperLowPDT3;
} _ALARM_TYPE_D_SET;
//Philip 20220527 0.0.1 =========================Temp and PDT change from unsigned int to int===============
typedef struct __ALARM_SET_PARAMETER_VALUE
{
    _ALARM_TYPE_A_SET AlarmTypeASet;//20Bytes==>202Bytes
    _ALARM_TYPE_B_SET AlarmTypeBSet;//4Bytes==>206Bytes
    _BURN_SYSTEM_ALARM_SET BurnSystemAlarmSet;//16Bytes==>222Bytes
    _WHEEL_ALARM_SET WheelAlarmSet;//16Bytes==>238Bytes
    _ALARM_TYPE_D_SET AlarmTypeDSet;//40Bytes==>278Bytes
} _ALARM_SET_PARAMETER_VALUE;

typedef union __ALARM_SET_PARAMETER
{
    _ALARM_SET_PARAMETER_VALUE Value;
    unsigned char ByteData[96];
} _ALARM_SET_PARAMETER;

typedef struct __SYSTEM_PARAMETER
{    
    _FAN1_1_SETTING FAN1_1;//34Bytes
    _FAN2_SETTING FAN_2;//16Bytes==>50Bytes
    _HEATER_SETTING HeaterSet;//40Bytes==>90Bytes
    _WHEEL_SETTING Wheel;//24Bytes==>114Bytes
    _PCD20_SETTING PCD_20;//32Bytes==>146Bytes
    _PCD6_SETTING PCD_6;//4Bytes==>150Bytes
    _PCD22_SETTING PCD_22;//8Bytes==>158Bytes
    _PCD25_SETTING PCD_25;//16Bytes==>174Bytes
    _PCD2_SETTING PCD2;//4Bytes==>178Bytes
    _V21_SETTING V21;//4Bytes==>182Bytes

    _ALARM_SET_PARAMETER Alarm;//96Bytes==>278Bytes

    unsigned int RunTimeStatusAddr;//2Bytes==>280Bytes
    unsigned long WriteEEPROM_Count;//4Bytes==>284Bytes
    unsigned long Dummy1;//4Bytes==>288Bytes
    unsigned long Dummy2;//4Bytes==>292Bytes
    unsigned int Dummy3;//2Bytes==>294Bytes
} _SYSTEM_PARAMETER;

#define SYSTEM_PARAMETER_START_ADDR 0
#define SYSTEM_PARAMETER_SIZE 294//286//112
//#define KNIFE_INFORM_START_ADDR 128
//#define KNIFE_INFORM_SIZE 364
#define RUNTIME_STATUS_START_ADDR 336//294 / 14 = 21, 21 * 16 = 336//544

typedef struct __RUNTIME_STATUS
{
//Philip 20220124 0.0.1 ===============================================================    
    unsigned long UsingCount;
    unsigned long UsingHours;
    unsigned long WriteEEPROM_Count;
    unsigned int AutoGasIn : 1;
    unsigned int FAN1_1_PID_ON : 1;//0 : for PID OFF, 1 : for PID ON
    unsigned int FAN1_1_PID_Auto : 1;//0 : for Manual, 1 : for Auto
    unsigned int PCD20_PID_Auto : 1;//0 : for Manual, 1 : for Auto
    unsigned int Heater_PID_Auto : 1;//0 : for Manual, 1 : for Auto
    
    unsigned int FaultLEDOn : 1;//0 : for OFF, 1 : for ON //Isen：20230703新增
    unsigned int AlarmLEDOn : 1;//0 : for OFF, 1 : for ON //Isen：20230703新增   
    
    unsigned int DummyBit : 9;
//Philip 20220124 0.0.1 ===============================================================    
} _RUNTIME_STATUS;//1+1+4+4+4=14Bytes = 1 Pages, Next Address = Now Address + 16
//#define RUNTIME_STATUS_START_ADDR 128
#define RUNTIME_STATUS_SIZE 14

typedef struct __RUNTIME_FAN1_1_ALARM_BITMAP
{
    unsigned char PressureSensorTurnOnFault : 1;
    unsigned char PressureSensorRunningFault : 1;
    unsigned char PressureSensorTurnOffFault : 1;
    unsigned char InverterContactFault : 1;
    unsigned char InverterFault : 1;
    unsigned char MotorOverTempFault : 1;
    unsigned char Dummy : 2;
    
} __RUNTIME_FAN1_1_ALARM_BITMAP;

typedef union __RUNTIME_FAN1_1_ALARM
{
    __RUNTIME_FAN1_1_ALARM_BITMAP bitmap;
    unsigned char AlarmValue;
    
} _RUNTIME_FAN1_1_ALARM;

typedef struct __RUNTIME_FAN2_ALARM_BITMAP
{
    unsigned char PressureSensorTurnOnFault : 1;
    unsigned char PressureSensorRunningFault : 1;
    unsigned char PressureSensorTurnOffFault : 1;
    unsigned char InverterTurnOnFault : 1;
    unsigned char InverterRunningFault : 1;
    unsigned char InverterTurnOffFault : 1;
    unsigned char Dummy : 2;
    
} __RUNTIME_FAN2_ALARM_BITMAP;

typedef union __RUNTIME_FAN2_ALARM
{
    __RUNTIME_FAN2_ALARM_BITMAP bitmap;
    unsigned char AlarmValue;
    
} _RUNTIME_FAN2_ALARM;

typedef struct __RUNTIME_SCR_STATUS_BITMAP
{
    unsigned char OvenControllerEn : 1;
    unsigned char SCR_Heater_TurnOn : 1;
    unsigned char FinishCleanOven : 1;
    unsigned char OvenTemperatureReady : 1;
    unsigned char DropOutTemperatureReady : 1;
    unsigned char Dummy : 3;
    
} _RUNTIME_SCR_STATUS_BITMAP;

typedef union __RUNTIME_SCR_STATUS
{
    _RUNTIME_SCR_STATUS_BITMAP bitmap;
    unsigned char StatusValue;
    
} _RUNTIME_SCR_STATUS;

typedef struct __RUNTIME_SCR_FAULT_BITMAP
{
    unsigned char SCR_HeatingSystemFault : 1;
    unsigned char TwoTemperatureSensorFault : 1;
    unsigned char HighTemperatureContorlFault : 1;
    unsigned char SuperHighTemperatureFault : 1;
    unsigned char SuperLowTemperatureFault : 1;
    unsigned char Dummy : 3;
    
} _RUNTIME_SCR_FAULT_BITMAP;

typedef union __RUNTIME_SCR_FAULT
{
    _RUNTIME_SCR_FAULT_BITMAP bitmap;
    unsigned char FaultValue;
    
} _RUNTIME_SCR_FAULT;

typedef struct __RUNTIME_SCR_ALARM_BITMAP
{
    unsigned char TemperatureSensor1Alarm : 1;
    unsigned char TemperatureSensor2Alarm : 1;
    unsigned char HighTemperatureAlarm : 1;
    unsigned char LowTemperatureAlarm : 1;
    unsigned char Dummy : 4;
    
} _RUNTIME_SCR_ALARM_BITMAP;

typedef union __RUNTIME_SCR_ALARM
{
    _RUNTIME_SCR_ALARM_BITMAP bitmap;
    unsigned char AlarmValue;
    
} _RUNTIME_SCR_ALARM;

typedef struct __RUNTIME_WHEEL_FAULT_BITMAP
{
    unsigned char InverterFault : 1;
    unsigned char InverterRunningFault : 1;
    unsigned char StopFault : 1;
    unsigned char RunningFault : 1;
    unsigned char WheelRotateFault : 1;
    unsigned char Dummy : 3;
} _RUNTIME_WHEEL_FAULT_BITMAP;

typedef union __RUNTIME_WHEEL_FAULT
{
    _RUNTIME_WHEEL_FAULT_BITMAP bitmap;
    unsigned char FaultValue;
    
} _RUNTIME_WHEEL_FAULT;

typedef struct __RUNTIME_PCD2_FAULT_BITMAP
{
    unsigned char OpenFault : 1;
    unsigned char CloseFault : 1;
    unsigned char LimitFault : 1;
    unsigned char Dummy : 5;
    
} _RUNTIME_PCD2_FAULT_BITMAP;

typedef union __RUNTIME_PCD2_FAULT
{
    _RUNTIME_PCD2_FAULT_BITMAP bitmap;
    unsigned char FaultValue;
    
} _RUNTIME_PCD2_FAULT;

typedef struct __RUNTIME_PCD2_ALARM_BITMAP
{
    unsigned char OpenAlarm : 1;
    unsigned char CloseAlarm : 1;
    unsigned char Dummy : 6;
} _RUNTIME_PCD2_ALARM_BITMAP;

typedef union __RUNTIME_PCD2_ALARM
{
    _RUNTIME_PCD2_ALARM_BITMAP bitmap;
    unsigned char AlarmValue;
    
} _RUNTIME_PCD2_ALARM;

typedef struct __RUNTIME_PCD20_FAULT_BITMAP
{
    unsigned char OpenFault : 1;
    unsigned char CloseFault : 1;
    unsigned char LimitFault : 1;
    unsigned char Dummy : 5;
    
} _RUNTIME_PCD20_FAULT_BITMAP;

typedef union __RUNTIME_PCD20_FAULT
{
    _RUNTIME_PCD20_FAULT_BITMAP bitmap;
    unsigned char FaultValue;
    
} _RUNTIME_PCD20_FAULT;

typedef struct __RUNTIME_PCD20_ALARM_BITMAP
{
    unsigned char OpenAlarm : 1;
    unsigned char CloseAlarm : 1;
    unsigned char Dummy : 6;
} _RUNTIME_PCD20_ALARM_BITMAP;

typedef union __RUNTIME_PCD20_ALARM
{
    _RUNTIME_PCD20_ALARM_BITMAP bitmap;
    unsigned char AlarmValue;
    
} _RUNTIME_PCD20_ALARM;

typedef struct __RUNTIME_V21_FAULT_BITMAP
{
    unsigned char OpenFault : 1;
    unsigned char CloseFault : 1;
    unsigned char LimitFault : 1;
    unsigned char Dummy : 5;
    
} _RUNTIME_V21_FAULT_BITMAP;

typedef union __RUNTIME_V21_FAULT
{
    _RUNTIME_V21_FAULT_BITMAP bitmap;
    unsigned char FaultValue;
    
} _RUNTIME_V21_FAULT;

typedef struct __RUNTIME_V21_ALARM_BITMAP
{
    unsigned char OpenAlarm : 1;
    unsigned char CloseAlarm : 1;
    unsigned char Dummy : 6;
} _RUNTIME_V21_ALARM_BITMAP;

typedef union __RUNTIME_V21_ALARM
{
    _RUNTIME_V21_ALARM_BITMAP bitmap;
    unsigned char AlarmValue;
    
} _RUNTIME_V21_ALARM;

typedef struct __FAN1_1_RUNTIME_DISPLAY
{
    unsigned int RealPressure;
    unsigned int PID_Output;
    unsigned int RealFreq;
    unsigned int Current;
    unsigned int ErrorCode;
} _FAN1_1_RUNTIME_DISPLAY;

typedef struct __FAN2_RUNTIME_DISPLAY
{
    unsigned int SV;
    unsigned int RealSpeed;
    int TE12;
    unsigned int Current;
    unsigned int ErrorCode;
} _FAN2_RUNTIME_DISPLAY;

typedef struct __HEATER_RUNTIME_DISPLAY
{
    unsigned int RealOutputPercent;
    unsigned int OvenSP;
    unsigned int OvenSV;
    int AverageTemperature;
    int TE11;//A;
    int TE14;//1B;
} _HEATER_RUNTIME_DISPLAY;

typedef struct __MTR4_RUNTIME_DISPLAY
{
    unsigned int RealFreq;
    unsigned int RPH;
    unsigned int TE5;
    unsigned int Current;
    unsigned int ErrorCode;
} _MTR4_RUNTIME_DISPLAY;

typedef struct __PCD20_RUNTIME_DISPLAY
{
    int TE3;
    unsigned int RealOpenSize;//%
} _PCD20_RUNTIME_DISPLAY;

typedef struct __OTHER_RUNTIME_DISPLAY
{
    int TE1;
    int TE6;
    int TE8;
    int TE10;
    int PDT1;
    int PDT2;
    int PDT5;//PDT3;
    int PT1;
    unsigned int PCD22_RealOpenSize;
    unsigned int PCD25_RealOpenSize;
} _OTHER_RUNTIME_DISPLAY;


typedef struct __HMI_BUTTON_STATUS
{
    //Isen：1st Byte
    unsigned char MTR4ManualOpenBtn : 1;
    unsigned char MTR4ManualCloseBtn : 1;
    unsigned char PCD20ManualOpenBtn : 1;
    unsigned char PCD20ManualCloseBtn : 1;
    unsigned char FAN1ManualOpenBtn : 1;
    unsigned char FAN1ManualCloseBtn : 1;
    unsigned char FAN2ManualOpenBtn : 1;
    unsigned char FAN2ManualCloseBtn : 1;
    
    //Isen：2st Byte    
    unsigned char PCD2ManualOpenBtn : 1;
    unsigned char PCD2ManualCloseBtn : 1;
    unsigned char PCD6ManualOpenBtn : 1;
    unsigned char PCD6ManualCloseBtn : 1; 
    unsigned char PCD22ManualOpenBtn : 1;
    unsigned char PCD22ManualCloseBtn : 1;
    unsigned char PCD25ManualOpenBtn : 1;
    unsigned char PCD25ManualCloseBtn : 1;
    
    //Isen：3st Byte 
    unsigned char V21ManualOpenBtn : 1;
    unsigned char V21ManualCloseBtn : 1;     
    unsigned char SystemAutoStartBtn : 1;
    unsigned char SystemAutoStopBtn : 1;
    unsigned char FaultResetBtn : 1;
    unsigned char FunctionResetBtn : 1;
    unsigned char Dummy3Bit : 2;

} _HMI_BUTTON_STATUS;

typedef union __SENDING_DATA
{
    long value;
    unsigned char data[4];
} _SENDING_DATA;

typedef union __PARSING_DATA
{
    long value;
    unsigned char data[4];
} _PARSING_DATA;

typedef union __PARSING_WORD
{
    int WordData;
    unsigned char Byte[2];
} _PARSING_WORD;

typedef union __SENDING_WORD
{
    int WordData;
    unsigned char Byte[2];
} _SENDING_WORD;

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* SYSTEM_CONTROL_H */

