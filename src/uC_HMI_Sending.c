/*
 * File:   uC_HMI_Sending.c
 * Author: user
 *
 * Created on 2020年4月6日, 下午 3:41
 */
#include "..\h\SystemControl.h"
#include "..\h\uC_HMI_Control.h"

#define UC_HMI_MAX_REPEAT_COUNT 3
#define UC_HMI_MAX_SENDING_DELAY 5//5msec
#define UC_HMI_MAX_ACK_WAIT_TIME 500//100//100msec

extern unsigned int uC_HMI_CRC_CREATE(unsigned char *data, unsigned char lenth);
extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
extern _UC_HMI_SEND_BUF ucHMISuddenSendRegister;

_SENDING_WORD SendingWord;

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
