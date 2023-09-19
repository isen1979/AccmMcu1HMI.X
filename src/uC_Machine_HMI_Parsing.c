/*
 * File:   Machine_uC_HMI_Parsing.c
 * Author: user
 *
 * Created on 2020年4月21日, 上午 11:05
 */
#include "..\h\SystemControl.h"
#include "uC_HMI_Control.h"

#define NUMBER_KEYBOARD_ENTER 0
#define NUMBER_KEYBOARD_CANCEL 100

//extern void SaveRunTimeStatus(void);
extern void OpenDialog(unsigned char DialogNumber);
extern void CloseDialog(void);
extern void uC_HMI_RunWriteMultiByteSend(unsigned int addr, unsigned char length, unsigned char *data);
extern void uC_HMI_RunWriteSingleByteSend(unsigned int addr, unsigned char Value);
extern void uC_HMI_RunReadLongWordSend(unsigned int addr, unsigned char count);
extern void uC_HMI_RunReadByteSend(unsigned int addr, unsigned char count);
extern void uC_HMI_RunReadTextVariableSend(unsigned char addr);
extern unsigned char uC_HMI_CRC_Check_OK(unsigned char *data, unsigned char length);
extern void uC_HMI_Check_Ack(unsigned char state);
extern void GetReadSDIndex(unsigned int addr, unsigned int *data, unsigned char Count);
extern void Get_uCHMI_DateCode(unsigned int addr, long Value);
extern void StartChart1PlayBack(void);
extern void StartChart2PlayBack(void);
extern void StartChart3PlayBack(void);
extern void SetPlayBackDay(unsigned char ChartId, unsigned char IncDecFlag);//Dec : IncDecFlag = 0, Inc : IncDecFlag = 1
extern void PlayBackUpdateChartTimeDisplay(unsigned char ChartId);
extern void GetSystemParameterId(unsigned int addr, unsigned char count, unsigned char id);
extern void GetKeyBoardValue(unsigned int addr, unsigned char count, long Value);
extern void SendMTR4MaualControlCommand(void);
extern void SendFAN1MaualControlCommand(void);
extern void SendFAN2MaualControlCommand(void);
extern void SendPCD20MaualControlCommand(void);
extern void SendPCD22MaualControlCommand(void);
extern void SendPCD25MaualControlCommand(void);
//Philip 20220325 0.0.1 ==============================================================================================
extern void SendSystemAutoStartStopControlCommand(void);
extern void SendV21MaualControlCommand(void);
extern void SendPCD6MaualControlCommand(void);
extern void SendPCD2MaualControlCommand(void);
//Philip 20220325 0.0.1 ==============================================================================================
extern _SYSTEM_PARAMETER SystemParameter, lastSystemParameter;
extern unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];

_PARSING_WORD U1_ParsingWord;
_PARSING_DATA ParsingData;
_HMI_BUTTON_STATUS HMI_BtnStatus;

void GetReadByteData(void)
{
    unsigned int addr;
    unsigned char Value, Count;//, i;
    
    U1_ParsingWord.Byte[1] = UART1RxBuffer[3];
    U1_ParsingWord.Byte[0] = UART1RxBuffer[4];
    addr = U1_ParsingWord.WordData;
    Count = UART1RxBuffer[5];
    Value = UART1RxBuffer[6];
    GetSystemParameterId(addr, Count, Value);
    
}

void GetReadWordData(void)
{
    unsigned int addr, data[20];
    unsigned char Count, i;
    
    U1_ParsingWord.Byte[1] = UART1RxBuffer[3];
    U1_ParsingWord.Byte[0] = UART1RxBuffer[4];
    addr = U1_ParsingWord.WordData;
    Count = UART1RxBuffer[5];
    
    for(i=0;i<Count;i++)
    {
        U1_ParsingWord.Byte[1] = UART1RxBuffer[6+2*i];
        U1_ParsingWord.Byte[0] = UART1RxBuffer[7+2*i];
        data[i] = U1_ParsingWord.WordData;
    }
    
    GetReadSDIndex(addr, data, Count);
}

void GetReadLongWordData(void)
{    
    unsigned int addr;
    unsigned char Count, i;
    unsigned long Value;
    unsigned long data[10];
    
    U1_ParsingWord.Byte[1] = UART1RxBuffer[3];
    U1_ParsingWord.Byte[0] = UART1RxBuffer[4];
    addr = U1_ParsingWord.WordData;
    Count = UART1RxBuffer[5];
    
    if( Count == 1 )
    {
        ParsingData.data[3] = UART1RxBuffer[6];
        ParsingData.data[2] = UART1RxBuffer[7];    
        ParsingData.data[1] = UART1RxBuffer[8];
        ParsingData.data[0] = UART1RxBuffer[9];
        Value = ParsingData.value;
        
        GetKeyBoardValue(addr, Count, Value);
        Get_uCHMI_DateCode(addr, Value);
    }
    else if( Count > 1 )
    {
        for(i=0;i<Count;i++)
        {
            ParsingData.data[3] = UART1RxBuffer[6+4*i];
            ParsingData.data[2] = UART1RxBuffer[7+4*i];    
            ParsingData.data[1] = UART1RxBuffer[8+4*i];
            ParsingData.data[0] = UART1RxBuffer[9+4*i];            
            data[i] = ParsingData.value;
        }
    }
}

extern void uC_HMI_RunDeleteTextVariableSend(unsigned int addr);
unsigned int RxTextBuffer[MAX_READ_TEXT_SIZE];
void GetReadTextData(void)
{
    unsigned int addr;
    unsigned char i, Count;
    unsigned int Value;
    
    U1_ParsingWord.Byte[1] = UART1RxBuffer[3];
    U1_ParsingWord.Byte[0] = UART1RxBuffer[4];
    addr = U1_ParsingWord.WordData;
    Count = (UART1RxBuffer[1] - 3)/2;
   
    for(i=0;i<Count;i++)
    {
        U1_ParsingWord.Byte[1] = UART1RxBuffer[(2*i+5)];
        U1_ParsingWord.Byte[0] = UART1RxBuffer[(2*i+6)];
        Value = U1_ParsingWord.WordData;
        RxTextBuffer[i] = Value;
    }
    RxTextBuffer[i] = 0;
}

void MachineUcHMI_EventProcess(unsigned int addr)
{
    switch(addr)
    {
        case KEYBOARD_VALUE_OUT_ADDR :
            uC_HMI_RunReadLongWordSend(addr, 1);
            break;
        case SYSTEM_PARAMETER_INPUT_ID_ADDR :
            uC_HMI_RunReadByteSend(addr, 1);
            break;
        case START_CHART1_PLAY_BACK_ADDR :
            StartChart1PlayBack();
            break;
        case START_CHART2_PLAY_BACK_ADDR :
             StartChart2PlayBack();
            break;
        case START_CHART3_PLAY_BACK_ADDR :
             StartChart3PlayBack();
            break;
        case PLAY_BACK_CHART1_PREV_DAY_ADDR :
            SetPlayBackDay(0, 0);
            break;
        case PLAY_BACK_CHART1_NEXT_DAY_ADDR :
            SetPlayBackDay(0, 1);
            break;
        case PLAY_BACK_CHART2_PREV_DAY_ADDR :
            SetPlayBackDay(1, 0);
            break;
        case PLAY_BACK_CHART2_NEXT_DAY_ADDR :
            SetPlayBackDay(1, 1);
            break;
        case PLAY_BACK_CHART3_PREV_DAY_ADDR :
            SetPlayBackDay(2, 0);
            break;
        case PLAY_BACK_CHART3_NEXT_DAY_ADDR :
            SetPlayBackDay(2, 1);
            break;
        case PLAY_BACK_SHOW_CHART1_VIEW_FAR_CLOSE_BTN :
        case PLAY_BACK_SHOW_CHART1_GO_BTN :
            PlayBackUpdateChartTimeDisplay(1);
            break;
        case PLAY_BACK_SHOW_CHART2_VIEW_FAR_CLOSE_BTN :
        case PLAY_BACK_SHOW_CHART2_GO_BTN :
            PlayBackUpdateChartTimeDisplay(2);
            break;
        case PLAY_BACK_SHOW_CHART3_VIEW_FAR_CLOSE_BTN :
        case PLAY_BACK_SHOW_CHART3_GO_BTN :
            PlayBackUpdateChartTimeDisplay(3);
            break;
        case MTR4_MANUAL_OPEN_BTN :
            HMI_BtnStatus.MTR4ManualOpenBtn = 1;
            SendMTR4MaualControlCommand();
            break;
        case MTR4_MANUAL_CLOSE_BTN :
            HMI_BtnStatus.MTR4ManualCloseBtn = 1;
            SendMTR4MaualControlCommand();
            break;
        case PCD20_OPEN_BTN :
            HMI_BtnStatus.PCD20ManualOpenBtn = 1;
            SendPCD20MaualControlCommand();
            break;
        case PCD20_CLOSE_BTN :
            HMI_BtnStatus.PCD20ManualCloseBtn = 1;
            SendPCD20MaualControlCommand();
            break;
        case FAN1_1MANUAL_OPEN_BTN :
            HMI_BtnStatus.FAN1ManualOpenBtn = 1;
            SendFAN1MaualControlCommand();
            break;
        case FAN1_1MANUAL_CLOSE_BTN :
            HMI_BtnStatus.FAN1ManualCloseBtn = 1;
            SendFAN1MaualControlCommand();
            break;
        case FAN2_MANUAL_OPEN_BTN :
            HMI_BtnStatus.FAN2ManualOpenBtn = 1;
            SendFAN2MaualControlCommand();
            break;
        case FAN2_MANUAL_CLOSE_BTN :
            HMI_BtnStatus.FAN2ManualCloseBtn = 1;
            SendFAN2MaualControlCommand();
            break;
        case PCD22_MANUAL_OPEN_BTN :
            HMI_BtnStatus.PCD22ManualOpenBtn = 1;
            SendPCD22MaualControlCommand();
            break;
        case PCD22_MANUAL_CLOSE_BTN :
            HMI_BtnStatus.PCD22ManualCloseBtn = 1;
            SendPCD22MaualControlCommand();
            break;
        case PCD25_MANUAL_OPEN_BTN :
            HMI_BtnStatus.PCD25ManualOpenBtn = 1;
            SendPCD25MaualControlCommand();
            break;
        case PCD25_MANUAL_CLOSE_BTN :
            HMI_BtnStatus.PCD25ManualCloseBtn = 1;
            SendPCD25MaualControlCommand();
            break;  
//Philip 20220325 0.0.1 ===============================================================================
        case PCD2_MANUAL_OPEN_BTN :
            HMI_BtnStatus.PCD2ManualOpenBtn = 1;
            SendPCD2MaualControlCommand();
            break;  
        case PCD2_MANUAL_CLOSE_BTN :
            HMI_BtnStatus.PCD2ManualCloseBtn = 1;
            SendPCD2MaualControlCommand();
            break;    
        case PCD6_MANUAL_OPEN_BTN :
            HMI_BtnStatus.PCD6ManualOpenBtn = 1;
            SendPCD6MaualControlCommand();
            break;  
        case PCD6_MANUAL_CLOSE_BTN :
            HMI_BtnStatus.PCD6ManualCloseBtn = 1;
            SendPCD6MaualControlCommand();
            break;            
        case V21_MANUAL_OPEN_BTN :
            HMI_BtnStatus.V21ManualOpenBtn = 1;
            SendV21MaualControlCommand();
            break;  
        case V21_MANUAL_CLOSE_BTN :
            HMI_BtnStatus.V21ManualCloseBtn = 1;
            SendV21MaualControlCommand();
            break;      
        case SYSTEM_AUTO_START_BTN :
            HMI_BtnStatus.SystemAutoStartBtn = 1;
            SendSystemAutoStartStopControlCommand();
            break;  
        case SYSTEM_AUTO_STOP_BTN :
            HMI_BtnStatus.SystemAutoStopBtn = 1;
            SendSystemAutoStartStopControlCommand();
            break;
//Philip 20220325 0.0.1 ===============================================================================            
    }
}

