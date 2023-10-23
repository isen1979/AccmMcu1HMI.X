/*
 * File:   COM3_RX_Parsing.c
 * Author: user
 *
 * Created on 2019年10月30日, 下午 6:58
 */
#include "..\h\SystemControl.h"
#include "..\h\COM3_Command.h"
/*
 20220322 :
 void COM3_GET_TE01_TE06_CMD(void), void COM3_GET_TE08_PDT1_FAN2_CMD(void), void COM3_GET_TE10_TE14_CMD(void),
 void COM3_GET_ROTATOR_PDT3_CMD(void), void COM3_GET_FAN1_1_PCD25_CMD(void), all of above functions are modified from high byte first to low byte first.
 Change function name from COM3_GET_TE10_TE14_CMD() to COM3_GET_TE10_PT1_CMD(void)
 Change function name from COM3_GET_ROTATOR_PDT3_CMD() to COM3_GET_ROTATOR_PDT5_CMD()
 Change variable assign from OtherRunTimeDisplay.PDT3 to OtherRunTimeDisplay.PDT5
 */
extern unsigned char CRC_CHECK(unsigned char *data, unsigned char lenth ,unsigned int crc_data);
extern void Set_Output_bit_Status(unsigned char bitnum);
extern void Clear_Output_bit_Status(unsigned char bitnum);
extern void CheckSendingAck(void);

extern _SYSTEM_RUNTIME_STATUS SystemRunTimeStatus;
extern _MTR4_RUNTIME_DISPLAY MTR4_RunTimeDisplay;
extern _OTHER_RUNTIME_DISPLAY OtherRunTimeDisplay;
extern _FAN2_RUNTIME_DISPLAY FAN2_RunTimeDisplay;
extern _FAN1_1_RUNTIME_DISPLAY FAN1_1_RunTimeDisplay;
extern _HEATER_RUNTIME_DISPLAY HEATER_RunTimeDisplay;
extern _PCD20_RUNTIME_DISPLAY PCD20_RunTimeDisplay, lastPCD20_RunTimeDisplay;
extern _SYSTEM_PARAMETER SystemParameter;
extern unsigned char UART3RxBuffer[UART3_BUFFER_SIZE];
extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
extern unsigned char KeyboardIndex;
extern unsigned char KeyboardResponseFlag, KeyboardFirmeareVersionResponseFlag, KeyboardScanResponseFlag;
extern void Send_uCHMI_AuxControllerFirmwareVersion(void);

_PARSING_DATA U3_ParsingData;
_PARSING_WORD U3_ParsingWord;
_IO_STATUS ioStatus;
_ALARM_STATUS alarmStatus;
unsigned char COM3_Rx_Size;
unsigned int ExtFirmwareVersion;
unsigned long ExtFirmwareDate;
unsigned int U3_CommnunicationFaultCount=0;

void COM3_GET_TE01_TE06_CMD(void)
{
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem1Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem2Enum];
    OtherRunTimeDisplay.TE1 = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem3Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem4Enum];
    PCD20_RunTimeDisplay.TE3 = U3_ParsingWord.WordData;
    
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem5Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem6Enum];
    MTR4_RunTimeDisplay.TE5 = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem7Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem8Enum];
    OtherRunTimeDisplay.TE6 = U3_ParsingWord.WordData; 
}

void COM3_GET_TE08_PDT1_FAN2_CMD(void)
{
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem1Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem2Enum];
    OtherRunTimeDisplay.TE8 = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem3Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem4Enum];
    OtherRunTimeDisplay.PDT1 = U3_ParsingWord.WordData;
    
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem5Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem6Enum];
    OtherRunTimeDisplay.PDT2 = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem7Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem8Enum];
    FAN2_RunTimeDisplay.RealSpeed = U3_ParsingWord.WordData;     
}

void COM3_GET_TE10_PT1_CMD(void)
{
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem1Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem2Enum];
    OtherRunTimeDisplay.TE10 = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem3Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem4Enum];
    HEATER_RunTimeDisplay.TE11 = U3_ParsingWord.WordData;
    
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem5Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem6Enum];
    FAN2_RunTimeDisplay.TE12 = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem7Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem8Enum];
    OtherRunTimeDisplay.PT1 = U3_ParsingWord.WordData;
}

void COM3_GET_ROTATOR_PDT5_CMD(void)
{
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem1Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem2Enum];
    MTR4_RunTimeDisplay.RealFreq = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem3Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem4Enum];
    OtherRunTimeDisplay.PDT5 = U3_ParsingWord.WordData;
    
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem5Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem6Enum];
    MTR4_RunTimeDisplay.Current = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem7Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem8Enum];
    MTR4_RunTimeDisplay.ErrorCode = U3_ParsingWord.WordData;     
}

void COM3_GET_FAN1_1_PCD25_CMD(void)
{
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem1Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem2Enum];
    FAN1_1_RunTimeDisplay.RealFreq = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem3Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem4Enum];
    PCD20_RunTimeDisplay.RealOpenSize = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem5Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem6Enum];
    OtherRunTimeDisplay.PCD22_RealOpenSize = U3_ParsingWord.WordData;
    
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem7Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem8Enum];
    OtherRunTimeDisplay.PCD25_RealOpenSize = U3_ParsingWord.WordData;
}

void COM3_GET_IO_STATUS_CMD(void)
{
    unsigned char i;
    
    for(i=0;i<IO_STATUS_SIZE;i++)
        ioStatus.ByteData[i] = UART3RxBuffer[COM3_PacketValueItem1Enum+i];
}

void COM3_GET_ALARM_STATUS_CMD(void)
{
    unsigned char i;    
    switch(UART3RxBuffer[COM3_PacketCommandItemEnum])
    {
        case COM3_RX_ALARM_STATUS_TypeEnum :
            for(i=0;i<8;i++)
                alarmStatus.ByteData[i] = UART3RxBuffer[COM3_PacketValueItem1Enum+i];
            break;
        case COM3_RX_ALARM1_STATUS_TypeEnum :
            for(i=0;i<8;i++)
                alarmStatus.ByteData[i+8] = UART3RxBuffer[COM3_PacketValueItem1Enum+i];
            break;
    }
}

void COM3_GET_FAN1_FAN2_Current_CMD(void)
{
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem1Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem2Enum];
    FAN1_1_RunTimeDisplay.Current = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem3Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem4Enum];
    FAN1_1_RunTimeDisplay.ErrorCode = U3_ParsingWord.WordData;

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem5Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem6Enum];
    FAN2_RunTimeDisplay.Current = U3_ParsingWord.WordData;
    
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem7Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem8Enum];
    FAN2_RunTimeDisplay.ErrorCode = U3_ParsingWord.WordData;
}

void COM3_GET_SystemRunStatus(void)
{
    SystemRunTimeStatus.Value.SystemAutoStopStatus = UART3RxBuffer[COM3_PacketValueItem1Enum];
    SystemRunTimeStatus.Value.SystemAutoStartStatus = UART3RxBuffer[COM3_PacketValueItem2Enum];
    FAN2_RunTimeDisplay.SV = UART3RxBuffer[COM3_PacketValueItem3Enum];//Philip 20220531 0.0.1
/*
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem3Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem4Enum];

    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem5Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem6Enum];
  
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem7Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem8Enum];
    FAN2_RunTimeDisplay.ErrorCode = U3_ParsingWord.WordData;
*/
}

void GetRunTimeHeaterFAN1_1_Status(void)
{
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem1Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem2Enum];
    HEATER_RunTimeDisplay.RealOutputPercent = U3_ParsingWord.WordData;
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem3Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem4Enum];
    HEATER_RunTimeDisplay.OvenSP = U3_ParsingWord.WordData;//SP
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem5Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem6Enum];
    HEATER_RunTimeDisplay.OvenSV = U3_ParsingWord.WordData;//SV   
    U3_ParsingWord.Byte[0] = UART3RxBuffer[COM3_PacketValueItem7Enum];
    U3_ParsingWord.Byte[1] = UART3RxBuffer[COM3_PacketValueItem8Enum];
    FAN1_1_RunTimeDisplay.PID_Output = U3_ParsingWord.WordData;  
}

void Get_ExtControllerFirmware(void)
{
    switch(UART3RxBuffer[COM3_PacketCommandItemEnum])
    {
        case COM3_TxRequestFirmwareVersionCommand_Enum :
            U3_ParsingData.data[0] = UART3RxBuffer[1];
            U3_ParsingData.data[1] = UART3RxBuffer[2];
            U3_ParsingData.data[2] = UART3RxBuffer[3];
            U3_ParsingData.data[3] = UART3RxBuffer[4];
            ExtFirmwareVersion = U3_ParsingData.value;
            U3_ParsingData.data[0] = UART3RxBuffer[5];
            U3_ParsingData.data[1] = UART3RxBuffer[6];
            U3_ParsingData.data[2] = UART3RxBuffer[7];
            U3_ParsingData.data[3] = UART3RxBuffer[8];
            ExtFirmwareDate = U3_ParsingData.value;
            Send_uCHMI_AuxControllerFirmwareVersion();
            break;
    }
}

void U3CommandParsing(void)
{
    unsigned int crc_data;
    crc_data = UART3RxBuffer[COM3_Rx_Size - 2];
    crc_data = (crc_data << 8) | UART3RxBuffer[COM3_Rx_Size - 1];
    if( CRC_CHECK(UART3RxBuffer, (COM3_Rx_Size-2), crc_data) == 1 )
    {
        switch(UART3RxBuffer[COM3_PacketCommandItemEnum])
        {        
            case COM3_RX_TE10_PT1_TypeEnum :
                COM3_GET_TE10_PT1_CMD();
                break;
            case COM3_ROTATOR_PDT5_TypeEnum :
                COM3_GET_ROTATOR_PDT5_CMD();
                break;
            case  COM3_RX_TE01_TE06_TypeEnum :
                COM3_GET_TE01_TE06_CMD();
                break;
            case COM3_RX_TE08_PDT1_FAN2_TypeEnum :
                COM3_GET_TE08_PDT1_FAN2_CMD();               
                break;
            case COM3_RX_FAN1_1_PCD25_TypeEnum :
                COM3_GET_FAN1_1_PCD25_CMD();
                break; 
            case COM3_RX_IO_STATUS_TypeEnum :
                COM3_GET_IO_STATUS_CMD();
                break;
            case COM3_RX_ALARM_STATUS_TypeEnum :
            case COM3_RX_ALARM1_STATUS_TypeEnum ://Philip 20220526 0.0.1
                COM3_GET_ALARM_STATUS_CMD();
                break;
            case COM3_RX_FAN1_FAN2_Current_TypeEnum :
                COM3_GET_FAN1_FAN2_Current_CMD();
                break;              
            case COM3_RX_SystemRunStatusEnum :
                COM3_GET_SystemRunStatus();
                break;             
            case COM3_RX_RunTimeHeaterFAN1_StatusEnum ://Philip 20220519 0.0.1
                GetRunTimeHeaterFAN1_1_Status();//Philip 20220519 0.0.1
                break;                
            default :
                CheckSendingAck();
                break;
        }        
    }
}