/*
 * File:   COM2_RX_Parsing.c
 * Author: user
 *
 * Created on 2019年10月30日, 下午 6:57
 */
#include "..\h\SystemControl.h"

extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
extern unsigned int UART2TimeOutCount, UART2RxBufCount, U2SendDataCount, U2PacketLen;
extern unsigned char UART2TxBuffer[UART2_BUFFER_SIZE], UART2RxBuffer[UART2_BUFFER_SIZE];
extern _PARSING_DATA U2_SendingWord2;

extern void LoopBackResponse(void);
extern unsigned char CRC_CHECK(unsigned char *data, unsigned char lenth ,unsigned int crc_data);
extern void uC_HMI_RunWriteSingleLongWordSend(unsigned int addr, long Value);

_PARSING_WORD ParsingWord;
unsigned char COM2_RxData_Size;

void U2CommandParsing(void)
{    
    unsigned int crc_data;
    crc_data = UART2RxBuffer[COM2_RxData_Size-2];
    crc_data = (crc_data << 8) | UART2RxBuffer[COM2_RxData_Size-1];
    if( CRC_CHECK(UART2RxBuffer, COM2_RxData_Size-2, crc_data) == 1 )
    {
        switch(UART2RxBuffer[0])
        {
            default :
                LoopBackResponse();
                break;
        } 
    }
}