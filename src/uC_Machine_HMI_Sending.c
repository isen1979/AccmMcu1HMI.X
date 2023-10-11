/*
 * File:   Machine_uC_HMI_Sending.c
 * Author: user
 *
 * Created on 2020年4月20日, 上午 11:32
 */
#include "uC_HMI_Control.h"
#include "SystemControl.h"
#include "COM3_Command.h"

extern void RegisterSendingPacket(unsigned char state, unsigned int addr, unsigned char *data, unsigned char size);
extern void uC_HMI_RunWriteSingleLongWordSend(unsigned int addr, long Value);
extern void uC_HMI_RunWriteMultiByteSend(unsigned int addr, unsigned char length, unsigned char *data);
extern void uC_HMI_RunWriteSingleByteSend(unsigned int addr, unsigned char Value);
extern void uC_HMI_RunWriteSingleWordSend(unsigned int addr, unsigned int Value);
extern void uC_HMI_RunWriteTextVariableSend(unsigned int addr, unsigned char Count);

extern _UC_HMI_SEND_BUF ucHMISuddenSendRegister;
extern _SYSTEM_PARAMETER SystemParameter;
extern _SENDING_DATA SendingData;
extern _SENDING_WORD SendingWord;
extern unsigned int RxTextBuffer[MAX_READ_TEXT_SIZE];

unsigned int TxTextBuffer[MAX_WRITE_TEXT_SIZE];
/*
void ShowInputPassword(void)
{
    unsigned char i;
    
    i=0;
    while(RxTextBuffer[i] > 0)
    {
        TxTextBuffer[i] = RxTextBuffer[i];
        i++;
    }
    uC_HMI_RunWriteTextVariableSend(16, i);
}

void SendSpeedRatioWordData(void)
{    
    unsigned char *p;    
    unsigned char data[10];
    unsigned char state, size;
    unsigned int addr;
    
    state = UC_HMI_WRITE_WORD;
    addr = REWINDER_TENSION_RATIO_ADDR;
    p = (unsigned char *)&(SystemParameter.RewinderTensionRatio);    
    data[0] = p[1];//Low Byte Data
    data[1] = p[0];//High Byte Data
    p = (unsigned char *)&(SystemParameter.TopFeederTensionRatio);  
    data[2] = p[1];//Low Byte Data
    data[3] = p[0];//High Byte Data
    p = (unsigned char *)&(SystemParameter.BottomFeederTensionRatio); 
    data[4] = p[1];//Low Byte Data
    data[5] = p[0];//High Byte Data    
    size = 6;
    
    RegisterSendingPacket(state, addr, data, size);
}

void SendSystemParameterLongWord(void)
{
    unsigned char data[15];
    unsigned char state, size;
    unsigned int addr;
    
    state = UC_HMI_WRITE_LONG_WORD;   
    addr = STOP_RUNNING_LENGTH_ADDR;//Address    
    SendingData.value = SystemParameter.StopRunningLength;    
    data[0] = SendingData.data[3];
    data[1] = SendingData.data[2];
    data[2] = SendingData.data[1];
    data[3] = SendingData.data[0];    
    SendingData.value = SystemParameter.EncoderOneTurnPulseCount;
    data[4] = SendingData.data[3];
    data[5] = SendingData.data[2];
    data[6] = SendingData.data[1];
    data[7] = SendingData.data[0];
    SendingData.value = SystemParameter.DetectWheelPerimeter;
    data[8] = SendingData.data[3];
    data[9] = SendingData.data[2];
    data[10] = SendingData.data[1];
    data[11] = SendingData.data[0];      
    size = 12;
    
    RegisterSendingPacket(state, addr, data, size);
}

void ShowSystemParameterWriteDataCounter(void)
{
    unsigned char data[10];
    unsigned char state, size;
    unsigned int addr;

    state = UC_HMI_WRITE_LONG_WORD;
    addr = 0;//SYSTEM_PARAMETER_DATA_WRITE_COUT_ADDR;//Address    
    SendingData.value = SystemParameter.WriteEEPROM_Count;
    data[0] = SendingData.data[3];
    data[1] = SendingData.data[2];
    data[2] = SendingData.data[1];
    data[3] = SendingData.data[0];
    size = 4;
    
    RegisterSendingPacket(state, addr, data, size);      
}  

#define UC_HMI_ROUTINE_SEND_DELAY 500
enum RoutineSendStateEnum
{
    WaitStartRoutineSendStateEnum=0,
    RoutineSendPulseWidthStateEnum,
    WaitRoutineSendCrossEdgeStateEnum,
    RoutineSendCrossEdgeStateEnum,
    WaitRoutineSendClothesLengthStateEnum,
    RoutineSendClothesLengthStateEnum,
    WaitRoutineSendPulseWidthStateEnum,
    RoutineSendStateEnumEnd
};
unsigned int RoutineSendTimeDelay;
unsigned char RoutineSendState=WaitStartRoutineSendStateEnum;
void uC_HMI_RoutineSend(void)
{
    switch(RoutineSendState)
    {
        case WaitStartRoutineSendStateEnum :
            if( ucHMISuddenSendRegister.size == 0 )
                RoutineSendState = RoutineSendPulseWidthStateEnum;
            break;
        case RoutineSendPulseWidthStateEnum :
            //SendPulseWidthWordData();
            RoutineSendTimeDelay = UC_HMI_ROUTINE_SEND_DELAY;
            RoutineSendState = WaitRoutineSendCrossEdgeStateEnum;
            break;
        case WaitRoutineSendCrossEdgeStateEnum:
            if( RoutineSendTimeDelay > 0 )
                RoutineSendTimeDelay--;
            else
                RoutineSendState = RoutineSendCrossEdgeStateEnum;
            break;            
        case RoutineSendCrossEdgeStateEnum :
            //ShowCrossEdgeAlignStatus();
            RoutineSendTimeDelay = UC_HMI_ROUTINE_SEND_DELAY;
            RoutineSendState = WaitRoutineSendClothesLengthStateEnum;
            break;
        case WaitRoutineSendClothesLengthStateEnum :
            if( RoutineSendTimeDelay > 0 )
                RoutineSendTimeDelay--;
            else
                RoutineSendState = RoutineSendClothesLengthStateEnum;            
            break;
        case RoutineSendClothesLengthStateEnum :
            RoutineSendTimeDelay = UC_HMI_ROUTINE_SEND_DELAY;            
            RoutineSendState = WaitRoutineSendPulseWidthStateEnum;
            break;
        case WaitRoutineSendPulseWidthStateEnum :
            if( RoutineSendTimeDelay > 0 )
                RoutineSendTimeDelay--;
            else
                RoutineSendState = RoutineSendPulseWidthStateEnum;               
            break;            
    }
}
*/
