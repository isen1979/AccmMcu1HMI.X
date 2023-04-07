/*
 * File:   uC_HMI_Sending.c
 * Author: user
 *
 * Created on 2020年4月6日, 下午 3:41
 */
#include "..\h\System_Control.h"
#include "..\h\uC_HMI_Control.h"

#define UC_HMI_MAX_REPEAT_COUNT 3
#define UC_HMI_MAX_SENDING_DELAY 5//5msec
#define UC_HMI_MAX_ACK_WAIT_TIME 500//100//100msec


extern unsigned int uC_HMI_CRC_CREATE(unsigned char *data, unsigned char lenth);

extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
extern unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];
extern unsigned char UART1TxBuffer[UART1_BUFFER_SIZE];
extern unsigned int UART1TimeOutCount, UART1RxBufCount, U1SendDataCount, U1PacketLen;
extern _UC_HMI_SEND_BUF ucHMISuddenSendRegister;

_SENDING_WORD SendingWord;

void uC_HMI_Send_Packet(void)
{    
    unsigned char i, index;
    unsigned int crc_data;

    index = ucHMISuddenSendRegister.ReadIndex;
    UART1TxBuffer[0] = 0xAF;
    UART1TxBuffer[1] = ucHMISuddenSendRegister.PacketSize[index] + 3;
    UART1TxBuffer[2] = ucHMISuddenSendRegister.state[index];
    SendingWord.WordData = ucHMISuddenSendRegister.addr[index];
    UART1TxBuffer[3] = SendingWord.Byte[1];
    UART1TxBuffer[4] = SendingWord.Byte[0];
    if( ucHMISuddenSendRegister.PacketSize[index] > 0 )
    {
        for(i=0;i<ucHMISuddenSendRegister.PacketSize[index];i++)
            UART1TxBuffer[5+i] = ucHMISuddenSendRegister.data[index][i];
    }             
    crc_data = uC_HMI_CRC_CREATE(UART1TxBuffer, (ucHMISuddenSendRegister.PacketSize[index]+5));
    UART1TxBuffer[ucHMISuddenSendRegister.PacketSize[index]+5] = (crc_data & 0x00FF);
    UART1TxBuffer[ucHMISuddenSendRegister.PacketSize[index]+6] = (crc_data >> 8) & 0x00FF;        
    UART1TxBuffer[ucHMISuddenSendRegister.PacketSize[index]+7] = 0xEF;
    U1SendDataCount = 0;
    U1PacketLen = ucHMISuddenSendRegister.PacketSize[index]+8;
    ucHMISuddenSendRegister.RepeatCount++;
}

unsigned char IsAckReceived(void)
{
    unsigned char ret;
    
    if( ucHMISuddenSendRegister.state[ucHMISuddenSendRegister.ReadIndex] == 0 )
    {
        ucHMISuddenSendRegister.RepeatCount = 0;
        if( ucHMISuddenSendRegister.size > 0 )
            ucHMISuddenSendRegister.size--;
        
        ucHMISuddenSendRegister.ReadIndex++;
        if( ucHMISuddenSendRegister.ReadIndex >= UC_HMI_SEND_BUF_SIZE )
            ucHMISuddenSendRegister.ReadIndex = 0;

        ret = 1;
    }
    else
        ret = 0;
    
    return ret;
}


enum uC_HMI_SendingStateEnum
{
    WaitStartUC_HMI_SendingStateEnum=0,
    StartUC_HMI_SendingStateEnum,
    WaitFinishUC_HMI_SendingStateEnum,
    WaitAckTimeEnum,
    uC_HMI_SendingFaultEnum,
    
    uC_HMI_SendingStateEnumEnd
};

unsigned char uC_HMI_SendingState=WaitStartUC_HMI_SendingStateEnum;
void uC_HMI_SendingControl(void)
{
    switch(uC_HMI_SendingState)
    {
        case WaitStartUC_HMI_SendingStateEnum :
            if( DelayTimerCounter[UART1_SendingDelayEnum] > 0 )
                ;
            else if( ucHMISuddenSendRegister.size > 0 )
                uC_HMI_SendingState = StartUC_HMI_SendingStateEnum;
            break;
        case StartUC_HMI_SendingStateEnum :
            uC_HMI_Send_Packet();
            uC_HMI_SendingState = WaitFinishUC_HMI_SendingStateEnum;
            break;
        case WaitFinishUC_HMI_SendingStateEnum :
            if( U1SendDataCount >= U1PacketLen )
            {
                DelayTimerCounter[UART1_SendingDelayEnum] = UC_HMI_MAX_ACK_WAIT_TIME;
                uC_HMI_SendingState = WaitAckTimeEnum;
            }
            break;
        case WaitAckTimeEnum :
            if( DelayTimerCounter[UART1_SendingDelayEnum] == 0 )
            {
                if( ucHMISuddenSendRegister.RepeatCount >= UC_HMI_MAX_REPEAT_COUNT )
                    uC_HMI_SendingState = uC_HMI_SendingFaultEnum;
                else
                {
                    DelayTimerCounter[UART1_SendingDelayEnum] = UC_HMI_MAX_SENDING_DELAY;
                    uC_HMI_SendingState = WaitStartUC_HMI_SendingStateEnum;
                }
            }
            else if( IsAckReceived() == 1 )
            {
                DelayTimerCounter[UART1_SendingDelayEnum] = UC_HMI_MAX_SENDING_DELAY;
                uC_HMI_SendingState = WaitStartUC_HMI_SendingStateEnum;
            }
            break;
        case uC_HMI_SendingFaultEnum :
            //Show Sending Fault Signal
            ucHMISuddenSendRegister.RepeatCount = UC_HMI_MAX_REPEAT_COUNT;
            uC_HMI_SendingState = WaitStartUC_HMI_SendingStateEnum;
            break;
    }
}