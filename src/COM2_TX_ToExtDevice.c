/*
 * File:   COM2_TX_ToHMI.c
 * Author: user
 *
 * Created on 2019年10月30日, 下午 6:56
 */
#include "..\h\SystemControl.h"
#include "..\h\HMI_Control.h"
#include "COM3_Command.h"

extern _SYSTEM_PARAMETER SystemParameter;
extern unsigned int UART2TimeOutCount, UART2RxBufCount, U2SendDataCount, U2PacketLen;
extern unsigned char UART2TxBuffer[UART2_BUFFER_SIZE], UART2RxBuffer[UART2_BUFFER_SIZE];
extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];

extern unsigned int CRC_CREATE(unsigned char *data, unsigned char lenth);

_PARSING_WORD U2_SendingWord;
_PARSING_DATA U2_SendingWord2;

void LoopBackResponseProcess(void)
{
    unsigned int i;
    
    for(i=0;i<UART2_PACKET_SIZE;i++)
        UART2TxBuffer[i] = UART2RxBuffer[i];    
    
    U2SendDataCount = 0;
    U2PacketLen = UART2_PACKET_SIZE;      
}

#define COM2_SEND_DELAY_TIME 50//50msec
#define COM2_MAX_RETRY_COUNT 3
enum COM2_SendControlStateEnum
{
    COM2_WaitStartSendStateEnum=0,
    COM2_SendStateEnum,
    COM2_WaitFinishSendStateEnum,
    COM2_Send_DelayStateEnum,
    
    COM2_SendControlStateEnumEnd
};
enum COM2_Build_Packet_Enum
{
    COM2_Build_NopPacket_Enum=0,
    COM2_Build_LoopBackPacket_Enum,
    COM2_Build_Packet_EnumEnd
};

unsigned char COM2_ReTryCounter;
unsigned char COM2_Send_Index;
void LoopBackResponse(void)
{
    COM2_Send_Index = COM2_Build_LoopBackPacket_Enum;    
}

void COM2_Build_Send_Packet(void)
{
    switch(COM2_Send_Index)
    {
        case COM2_Build_NopPacket_Enum :
            break;
        case COM2_Build_LoopBackPacket_Enum :
            COM2_ReTryCounter = COM2_MAX_RETRY_COUNT;
            LoopBackResponseProcess();
            break;
        default :
            U2PacketLen = UART2_PACKET_SIZE;
            U2SendDataCount = U2PacketLen;
            COM2_Send_Index = COM2_Build_NopPacket_Enum;
            break;
    }
}

unsigned char COM2_SendControlState=COM2_WaitStartSendStateEnum;
void COM2_SendControl_Process(void)
{    
    switch(COM2_SendControlState)
    {
        case COM2_WaitStartSendStateEnum : 
            if( COM2_Send_Index > COM2_Build_NopPacket_Enum )
                COM2_SendControlState = COM2_SendStateEnum;
            break;
        case COM2_SendStateEnum :
            COM2_Build_Send_Packet();
            COM2_SendControlState = COM2_WaitFinishSendStateEnum;
            break;
        case COM2_WaitFinishSendStateEnum :
            if( (U2SendDataCount >= U2PacketLen) && (U2PacketLen > 0) )
            {
                DelayTimerCounter[COM2_TX_TIMER_ENUM] = COM2_SEND_DELAY_TIME;
                COM2_SendControlState = COM2_Send_DelayStateEnum;
            }            
            break;
        case COM2_Send_DelayStateEnum :
            if( DelayTimerCounter[COM2_TX_TIMER_ENUM] == 0 )
            {
                if( COM2_ReTryCounter >= COM2_MAX_RETRY_COUNT )
                    COM2_SendControlState = COM2_WaitStartSendStateEnum;
                else
                {//Re-try
                    U2PacketLen = UART2_PACKET_SIZE;
                    U2SendDataCount = 0;
                }
            }
            break;
    }
}


void COM2_SendControl(void)
{
    COM2_SendControl_Process();
}


