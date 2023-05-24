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
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
/*
 20220322:
COM3_RX_CommandEnum : modified name, from COM3_RX_TE10_TE14_Command_Enum to COM3_RX_TE10_PT1_TypeEnum, from COM3_ROTATOR_PDT3_Command_Enum to COM3_ROTATOR_PDT5_TypeEnum
 */
#ifndef COM3_COMMAND_H
#define	COM3_COMMAND_H

#define COM3_TEMP_BUFFER_SIZE 50
#define SERVO_MOTOR_STEP_MOVE_MAX_RUNNING_TIME 2147483647

enum COM3_TX_CommandEnum
{
    COM3_NOP_Command_Enum=0,
	GetKeyValueResponseEnum,
	GetFirmWareVersionEnum,
    ExtKeyScanResponseEnum,
        
    COM3_TX_CommandEnumEnd
};

enum COM3_TxCommand_Enum
{
    COM3_TxNOP_Command_Enum=0,
    COM3_TxSet_FAN1_Parameter1_Command_Enum,
    COM3_TxSet_FAN1_Parameter2_Command_Enum,
    COM3_TxSet_FAN1_Parameter3_Command_Enum,
    COM3_TxSet_FAN1_Parameter4_Command_Enum,
    COM3_TxSet_FAN1_Parameter5_Command_Enum,//5
    COM3_TxSet_FAN2_Parameter1_Command_Enum,
    COM3_TxSet_FAN2_Parameter2_Command_Enum,
    COM3_TxSet_MTR4_Parameter1_Command_Enum,
    COM3_TxSet_MTR4_Parameter2_Command_Enum,
    COM3_TxSet_MTR4_Parameter3_Command_Enum,//10

//Philip 20220330 0.0.1 ==================================================
    COM3_RxSet_PCD2_PCD6_Parameter_Command_Enum,
    COM3_RxSet_V21_Parameter_Command_Enum,
//Philip 20220330 0.0.1 ==================================================

    COM3_TxSet_PCD20_Parameter1_Command_Enum,
    COM3_TxSet_PCD20_Parameter2_Command_Enum,
    COM3_TxSet_PCD20_Parameter3_Command_Enum,//15
    COM3_TxSet_PCD20_Parameter4_Command_Enum,
    COM3_TxSet_PCD22_Parameter_Command_Enum,
    COM3_TxSet_PCD25_Parameter1_Command_Enum,
    COM3_TxSet_PCD25_Parameter2_Command_Enum,
    
    COM3_TxSet_Heater_Parameter1_Command_Enum,//20
    COM3_TxSet_Heater_Parameter2_Command_Enum,
    COM3_TxSet_Heater_Parameter3_Command_Enum,
    COM3_TxSet_Heater_Parameter4_Command_Enum,
    COM3_TxSet_Heater_Parameter5_Command_Enum,

//Philip 20220330 0.0.1 ==================================================
    COM3_RxSetAlarm_Parameter1_CommandEnum,//25
    COM3_RxSetAlarm_Parameter2_CommandEnum,
    COM3_RxSetAlarm_Parameter3_CommandEnum,
    COM3_RxSetAlarm_Parameter4_CommandEnum,
    COM3_RxSetAlarm_Parameter5_CommandEnum,
    COM3_RxSetAlarm_Parameter6_CommandEnum,//30
    COM3_RxSetAlarm_Parameter7_CommandEnum,
    COM3_RxSetAlarm_Parameter8_CommandEnum,
    COM3_RxSetAlarm_Parameter9_CommandEnum,
    COM3_RxSetAlarm_Parameter10_CommandEnum,
    COM3_RxSetAlarm_Parameter11_CommandEnum,//35
    COM3_RxSetAlarm_Parameter12_CommandEnum,
//Philip 20220330 0.0.1 ==================================================
    
    COM3_TxRequestFirmwareVersionCommand_Enum,
    
    COM3_last_TxSet_Command_Enum,//Last Command for Aux Controller

//Philip 20220530 0.0.1 ========================================
    COM3_Button_Status_Command_Enum,
    COM3_Button_Command_Enum,//40
//Philip 20220530 0.0.1 ========================================    
   
    
    COM3_TxCommand_EnumEnd
};

//Philip 20220530 0.0.1 ===========================================================================
enum Android_HMI_Button_Command_Enum
{
    Android_HMI_NOP_Command_Enum=0,
    Android_HMI_RotatorManualControlEnum,
    Android_HMI_Fan1_1ManualControlEnum,
    Android_HMI_Fan2ManualControlEnum,
    Android_HMI_PCD20ManualControlEnum,
    Android_HMI_PCD22ManualControlEnum,//5
    Android_HMI_PCD25ManualControlEnum,    
    Android_HMI_PCD2ManualControlEnum,
    Android_HMI_PCD6ManualControlEnum,
    Android_HMI_V21ManualControlEnum,
    Android_HMI_SystemAutoStartStopControlEnum,//10
    Android_HMI_SetFaultResetEnum,
    Android_HMI_AUTO_GAS_IN_SET_Enum,
    Android_HMI_GAS_IN_OUT_SET_Enum,
    Android_HMI_MANUAL_MODE_SET_Enum,
    Android_HMI_FAN1_1_PID_ON_SET_Enum,//15
    Android_HMI_FAN1_1_PID_AUTO_STATE_SET_Enum,
    Android_HMI_HEATER_PID_AUTO_STATE_SET_Enum,
    Android_HMI_PCD_20_PID_AUTO_STATE_SET_Enum,
    
    Android_HMI_Button_Command_EnumEnd//19
};
//Philip 20220530 0.0.1 ===========================================================================


enum COM3_RX_CommandEnum
{    
    COM3_RX_TE10_PT1_TypeEnum=COM3_TxCommand_EnumEnd,
    COM3_ROTATOR_PDT5_TypeEnum,
    
    COM3_RX_TE01_TE06_TypeEnum,
    COM3_RX_TE08_PDT1_FAN2_TypeEnum,
    COM3_RX_FAN1_1_PCD25_TypeEnum,
//Philip 20220330 0.0.1 ========================================================================    
    COM3_RX_IO_STATUS_TypeEnum,
    COM3_RX_ALARM_STATUS_TypeEnum,
//Philip 20220330 0.0.1 ========================================================================
    
    COM3_RX_FAN1_FAN2_Current_TypeEnum,//Philip 20220406 0.0.1
    COM3_RX_SystemRunStatusEnum,//Philip 20220517 0.0.1
    COM3_RX_RunTimeHeaterFAN1_StatusEnum,//Philip 20220518 0.0.1
    
    COM3_RX_ALARM1_STATUS_TypeEnum,//Philip 20220526 0.0.1
    
    COM3_RX_CommandEnumEnd
};

enum COM3_PacketEnum
{
    COM3_PacketCommandItemEnum=0,
    COM3_PacketValueItem1Enum,
	COM3_PacketValueItem2Enum,
	COM3_PacketValueItem3Enum,
	COM3_PacketValueItem4Enum,
	COM3_PacketValueItem5Enum,
    COM3_PacketValueItem6Enum,
    COM3_PacketValueItem7Enum,
    COM3_PacketValueItem8Enum,
    COM3_PacketValueItem9Enum,

    COM3_crcHB,
    COM3_crcLB,
    
    COM3_PacketEnumEnd
};

//Philip 20220330 0.0.1 ========================================================================
typedef struct __IO_STATUS_VALUE
{
    unsigned int DIN0 : 1;//RD0
    unsigned int DIN1 : 1;//RD1
    unsigned int DIN2 : 1;//RD2 
    unsigned int PCD2_OpenSensor : 1;//DIN3//RD3
    unsigned int PCD2_CloseSensor : 1;//DIN4//RD4
    unsigned int DIN5 : 1;//RD5
    unsigned int DIN6 : 1;//RD6
    unsigned int DIN7 : 1;//RD7
    unsigned int DIN8 : 1;//RH8
    unsigned int DIN9 : 1;//RH9
    unsigned int DIN10 : 1;//RH10
    unsigned int DIN11 : 1;//RH11
    unsigned int DIN12 : 1;//RH12
    unsigned int PCD6_OpenSensor : 1;//DIN13//RH13
    unsigned int PCD6_CloseSensor : 1;//DIN14//RH14
    unsigned int DIN15 : 1;//RH15
//Philip 20220414 0.0.1 ==============================================    
    unsigned int DOUT0 : 1;//RH0
    unsigned int DOUT1 : 1;//RH1
    unsigned int DOUT2 : 1;//RH2
    unsigned int DOUT3 : 1;//RH3
    unsigned int DOUT4 : 1;//RH4
    unsigned int DOUT5 : 1;//RH5
    unsigned int V21_OUT : 1;//DOUT6//RH6
    unsigned int PCD2_Close : 1;//DOUT7//RH7
    unsigned int PCD2_Open : 1;//DOUT8//RJ8
    unsigned int DOUT9 : 1;//RJ9
    unsigned int PCD6_Close : 1;//DOUT10//RJ10
    unsigned int PCD6_Open : 1;//DOUT11//RJ11
    unsigned int DOUT12 : 1;//RJ12
    unsigned int DOUT13 : 1;//DIN13//RJ13
    unsigned int DOUT14 : 1;//DIN14//RJ14
    unsigned int DOUT15 : 1;//RJ15
//Philip 20220414 0.0.1 ==============================================
} _IO_STATUS_VALUE;
#define IO_STATUS_SIZE 4
typedef union __IO_STATUS
{
    _IO_STATUS_VALUE Value;
    unsigned int WordData[2];//Philip 20220414 0.0.1
    unsigned char ByteData[IO_STATUS_SIZE];//Philip 20220414 0.0.1
} _IO_STATUS;


typedef struct __ALARM_STATUS_VALUE
{
//Philip 20220526 0.0.1 =========================================================    
    unsigned int PCD_2_OpenFault : 1;
    unsigned int PCD_2_OpenAlarm : 1;
    unsigned int PCD_2_CloseFault : 1;
    unsigned int PCD_2_CloseAlarm : 1;
    unsigned int PCD_2_LimitFault : 1;
    
    unsigned int PCD_6_OpenFault : 1;
    unsigned int PCD_6_OpenAlarm : 1;
    unsigned int PCD_6_CloseFault : 1;
    unsigned int PCD_6_CloseAlarm : 1;
    unsigned int PCD_6_LimitFault : 1;  
    
    unsigned int PCD_20_OpenFault : 1;
    unsigned int PCD_20_OpenAlarm : 1;
    unsigned int PCD_20_CloseFault : 1;
    unsigned int PCD_20_CloseAlarm : 1;
     unsigned int PCD_20_LimitFault : 1;
     
    unsigned int PCD_22_OpenFault : 1;//2Bytes
    unsigned int PCD_22_OpenAlarm : 1;
    unsigned int PCD_22_CloseFault : 1;
    unsigned int PCD_22_CloseAlarm : 1;
    unsigned int PCD_22_LimitFault : 1;
    
    unsigned int PCD_25_OpenFault : 1;
    unsigned int PCD_25_OpenAlarm : 1;
    unsigned int PCD_25_CloseFault : 1;
    unsigned int PCD_25_CloseAlarm : 1;
    unsigned int PCD_25_LimitFault : 1;
    
    unsigned int V21_OpenFault : 1;
    unsigned int V21_OpenAlarm : 1;
    unsigned int V21_CloseFault : 1;
    unsigned int V21_CloseAlarm : 1;
    unsigned int V21_LimitFault : 1;//14th bit
    
    unsigned int FAN1_1_StartFault : 1;
    unsigned int FAN1_1_RuningFault : 1;//4Bytes
    unsigned int FAN1_1_StopFault : 1;
    unsigned int FAN1_1_ContactFault : 1;
    unsigned int FAN1_1_Fault : 1;
    unsigned int FAN1_1_MotorHtempFault : 1;
    
    unsigned int FAN2_StartFault : 1;
    unsigned int FAN2_RuningFault : 1;
    unsigned int FAN2_StopFault : 1;
    unsigned int FAN2_InverterFault : 1;   
    unsigned int FAN2_InverterRuningFault : 1;
    unsigned int FAN2_InverterStopFault : 1;
    unsigned int FAN2_InverterStartFault : 1;
    
    unsigned int MTR4_InverterFault : 1;
    unsigned int MTR4_InverterRuningFault : 1;
    unsigned int MTR4_StopFault : 1;
    unsigned int MTR4_RuningFault : 1;
    unsigned int MTR4_NotRotateFault : 1;//6Bytes
    
    unsigned int HeaterLowFireFault : 1;
    unsigned int GasLowPressureF : 1;
    unsigned int GasHighPressureF : 1;
    unsigned int GasValveNotOpenF : 1;
    unsigned int MoreThanFireCountLimitF : 1;
    unsigned int TE11_SensorFault : 1;
    unsigned int HighTempControllerF : 1;
    unsigned int HeaterHHTempFault : 1;
    unsigned int HeaterLLTempFault : 1;
    unsigned int OvenOutLowPressureF : 1;
    
    unsigned int HeaterHTempAlarm : 1;
    unsigned int HeaterLTempAlarm : 1;
    unsigned int HeaterReFireFaultAlarm : 1;
    unsigned int HeaterFlameFaultAlarm : 1;
    unsigned int GasLowPressureAlarm : 1;
    unsigned int Dummy1 : 1;//8Bytes
    
    unsigned int TE8_A1_Alarm : 1;
    unsigned int TE5_A1_Alarm : 1;
    unsigned int TE5_TE3_A1_Alarm : 1;
    unsigned int TE5_FAN2_A1_Alarm : 1;
    unsigned int TE8_A2_Alarm : 1;
    unsigned int TE5_A2_Alarm : 1;
    unsigned int TE5_TE3_A2_Alarm : 1;
    unsigned int TE5_FAN2_A2_Alarm : 1;
    
    unsigned int TE5_B_Alarm : 1;
    unsigned int TE5_FAN2_B_Alarm : 1;
    unsigned int TE11_HTempHeaterAlarm : 1;
    unsigned int TE11_LTempHeaterAlarm : 1;
    unsigned int TE12_HTempHeaterAlarm : 1;
    unsigned int TE12_LTempHeaterAlarm : 1;
    unsigned int PDT_2_H_HeaterAlarm : 1;
    unsigned int PDT_2_L_HeaterAlarm : 1;//10Bytes
    unsigned int PDT_3_H_HeaterAlarm : 1;
    unsigned int PDT_3_L_HeaterAlarm : 1;
    unsigned int TE3_H_MTR4Alarm : 1;
    unsigned int TE3_L_MTR4Alarm : 1;
    unsigned int TE8_H_MTR4Alarm : 1;
    unsigned int TE8_L_MTR4Alarm : 1;
    unsigned int TE5_H_MTR4Alarm : 1;
    unsigned int TE5_L_MTR4Alarm : 1;
    unsigned int PDT1_H_MTR4Alarm : 1;
    unsigned int PDT1_L_MTR4Alarm : 1;
    unsigned int TE3_H_D_Alarm : 1;
    unsigned int TE3_L_D_Alarm : 1;
    unsigned int TE5_H_D_Alarm : 1;
    unsigned int TE5_L_D_Alarm : 1;
    unsigned int TE8_H_D_Alarm : 1;
    unsigned int TE8_L_D_Alarm : 1;//12Bytes
    unsigned int TE11_H_D_Alarm : 1;
    unsigned int TE11_L_D_Alarm : 1;
    unsigned int TE12_H_D_Alarm : 1;
    unsigned int TE12_L_D_Alarm : 1;
    unsigned int TE14_H_D_Alarm : 1;
    unsigned int TE14_L_D_Alarm : 1;
    unsigned int TE1_H_D_Alarm : 1;
    unsigned int TE1_L_D_Alarm : 1;
    unsigned int PDT1_H_D_Alarm : 1;
    unsigned int PDT1_L_D_Alarm : 1;
    unsigned int PDT2_H_D_Alarm : 1;
    unsigned int PDT2_L_D_Alarm : 1;
    unsigned int PDT3_H_D_Alarm : 1;
    unsigned int PDT3_L_D_Alarm : 1;
    unsigned int Dummy2 : 1;
    unsigned int Dummy3 : 1;//14Bytes
    unsigned int Dummy4 : 1;
    unsigned int Dummy5 : 1;
    unsigned int Dummy6 : 1;
    unsigned int Dummy7 : 1;
    unsigned int Dummy8 : 1;
    unsigned int Dummy9 : 1;
    unsigned int Dummy10 : 1;
    unsigned int Dummy11 : 1;
    unsigned int Dummy12 : 1;
    unsigned int Dummy13 : 1;
    unsigned int Dummy14 : 1;
    unsigned int Dummy15 : 1;
    unsigned int Dummy16 : 1;
    unsigned int Dummy17 : 1;
    unsigned int Dummy18 : 1;
    unsigned int Dummy19 : 1;//16Bytes
//Philip 20220526 0.0.1 =========================================================
} _ALARM_STATUS_VALUE;

typedef union __ALARM_STATUS
{
    _ALARM_STATUS_VALUE Value;
    unsigned char ByteData[16];
} _ALARM_STATUS;
//Philip 20220330 0.0.1 ========================================================================
//Philip 20220510 0.0.1 ========================================================================
typedef struct __SYSTEM_RUNTIME_STATUS_VALUE
{
    unsigned char AutoGasIn : 1;
    unsigned char GasIn : 1;
    unsigned char GasOut : 1;
    unsigned char FAN1_1_PID_ON : 1;
    unsigned char FAN1_1_PID_Auto : 1;
    unsigned char PCD20_PID_Auto : 1;
    unsigned char Heater_PID_Auto : 1;     
    unsigned char SystemManualMode : 1;//1st Byte
    unsigned char SystemAutoStartStatus;//2nd Byte
    unsigned char SystemAutoStopStatus;//3rd Byte
    unsigned char Dummy4;//4th Byte
    unsigned char Dummy5;
    unsigned char Dummy6;
    unsigned char Dummy7;
    unsigned char Dummy8;
} _SYSTEM_RUNTIME_STATUS_VALUE;

typedef union __SYSTEM_RUNTIME_STATUS
{
    _SYSTEM_RUNTIME_STATUS_VALUE Value;
    unsigned char ByteData[8];
} _SYSTEM_RUNTIME_STATUS;
//Philip 20220510 0.0.1 ========================================================================

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

#endif	/* COM3_COMMAND_H */

