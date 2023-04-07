/*
 * File:   uC_HMI_Utility.c
 * Author: user
 *
 * Created on 2020年4月17日, 下午 5:13
 */
#include "..\h\uC_HMI_Control.h"
#include "SystemControl.h"

extern _SENDING_WORD SendingWord;
extern _SENDING_DATA SendingData;
extern _SYSTEM_PARAMETER SystemParameter;

_UC_HMI_SEND_BUF ucHMISuddenSendRegister;

void Initial_uCHMI_SuddenSendBuffer(void)
{
    unsigned char i;
    
    for(i=0;i<UC_HMI_SEND_BUF_SIZE;i++)
    {
        ucHMISuddenSendRegister.state[i] = 0;
        ucHMISuddenSendRegister.ReadIndex = 0;
        ucHMISuddenSendRegister.WriteIndex = 0;
        ucHMISuddenSendRegister.size = 0;
    }
}

void RegisterSendingPacket(unsigned char state, unsigned int addr, unsigned char *data, unsigned char size)
{
    unsigned char j;
            
    ucHMISuddenSendRegister.state[ucHMISuddenSendRegister.WriteIndex] = state;
    ucHMISuddenSendRegister.addr[ucHMISuddenSendRegister.WriteIndex] = addr;
    ucHMISuddenSendRegister.PacketSize[ucHMISuddenSendRegister.WriteIndex] = size;
    
    if( size > 0 )
    {
        for(j=0;j<size;j++)
            ucHMISuddenSendRegister.data[ucHMISuddenSendRegister.WriteIndex][j] = data[j];
    }
    
    ucHMISuddenSendRegister.size++;
    if( ucHMISuddenSendRegister.size < UC_HMI_SEND_BUF_SIZE )
    {
        ucHMISuddenSendRegister.WriteIndex++;
        if( ucHMISuddenSendRegister.WriteIndex >= UC_HMI_SEND_BUF_SIZE )
            ucHMISuddenSendRegister.WriteIndex = 0;    
    }
    else
        ucHMISuddenSendRegister.size--;
}

void uC_HMI_RunReadByteSend(unsigned int addr, unsigned char count)
{
    unsigned char size, state, data[10];
    
    state = UC_HMI_READ_BYTE;
    data[0] = count;
    size = 1;
    
    RegisterSendingPacket(state, addr, data, size);
}

void uC_HMI_RunReadWordSend(unsigned int addr, unsigned char count)
{
    unsigned char size, state, data[10];
    
    state = UC_HMI_READ_WORD;
    data[0] = count;
    size = 1;
    
    RegisterSendingPacket(state, addr, data, size);
}

void uC_HMI_RunReadLongWordSend(unsigned int addr, unsigned char count)
{
    unsigned char size, state, data[10];
    
    state = UC_HMI_READ_LONG_WORD;
    data[0] = count;
    size = 1;
    
    RegisterSendingPacket(state, addr, data, size);
}

void uC_HMI_RunReadTextVariableSend(unsigned char addr)
{
    unsigned char state, data[10], size;
    
    state = UC_HMI_READ_TEXT;
    data[0] = 0;
    size = 0;
    RegisterSendingPacket(state, addr, data, size);    
}

void uC_HMI_RunWriteSingleByteSend(unsigned int addr, unsigned char Value)
{
    unsigned char state, data[10], size;
    if( Value > 127 )
        Value = 127;
    
    state = UC_HMI_WRITE_BYTE;
    data[0] = Value;
    size = 1;
    
    RegisterSendingPacket(state, addr, data, size);   
}

void uC_HMI_RunWriteMultiByteSend(unsigned int addr, unsigned char length, unsigned char *data)
{
    unsigned char state, size;
    
    state = UC_HMI_WRITE_BYTE;
    size = length;
    
    RegisterSendingPacket(state, addr, data, size);    
}

void uC_HMI_RunWriteSingleWordSend(unsigned int addr, unsigned int Value)
{   
    unsigned char state, data[10], size;
    if( Value > 32767 )
        Value = 32767;
    
    state = UC_HMI_WRITE_WORD;
    SendingWord.WordData = Value;
    data[0] = SendingWord.Byte[1];
    data[1] = SendingWord.Byte[0];
    size = 2;
    
    RegisterSendingPacket(state, addr, data, size);
}

void uC_HMI_RunWriteMultiWordSend(unsigned int addr, unsigned char length, unsigned char *data)
{
    unsigned char state, size;
    
    state = UC_HMI_WRITE_WORD;
    size = length;
    
    RegisterSendingPacket(state, addr, data, size);    
}

void uC_HMI_RunWriteSingleLongWordSend(unsigned int addr, long Value)
{
    unsigned char state, data[10], size;
        
    state = UC_HMI_WRITE_LONG_WORD;
    SendingData.value = Value;
    data[0] = SendingData.data[3];
    data[1] = SendingData.data[2];
    data[2] = SendingData.data[1];
    data[3] = SendingData.data[0];
    size = 4;
    
    RegisterSendingPacket(state, addr, data, size);
}

void uC_HMI_RunWriteMultiLongWordSend(unsigned int addr, unsigned char length, unsigned char *data)
{
    unsigned char state, size;
    
    state = UC_HMI_WRITE_LONG_WORD;
    size = length;
    
    RegisterSendingPacket(state, addr, data, size);    
}


extern unsigned int RxTextBuffer[MAX_READ_TEXT_SIZE];
extern unsigned int TxTextBuffer[MAX_WRITE_TEXT_SIZE];
unsigned char WriteTextVariableBuffer[MAX_WRITE_TEXT_SIZE+MAX_WRITE_TEXT_SIZE];
void uC_HMI_RunWriteTextVariableSend(unsigned int addr, unsigned char Count)
{
    unsigned char state, i, size;
    
    state = UC_HMI_WRITE_TEXT;
    
    for(i=0;i<Count;i++)
    {
        SendingWord.WordData = TxTextBuffer[i];
        WriteTextVariableBuffer[(2*i)] = SendingWord.Byte[1];
        WriteTextVariableBuffer[(2*i+1)] = SendingWord.Byte[0];
    } 
    size = Count * 2;
    
    RegisterSendingPacket(state, addr, WriteTextVariableBuffer, size);
}

void uC_HMI_RunDeleteTextVariableSend(unsigned int addr)
{
    unsigned char state, data[10], size;
        
    state = UC_HMI_DELETE_TEXT;
    data[0] = 0;
    size = 0;    
    RegisterSendingPacket(state, addr, data, size);
}

void Set_uCHMI_RtcDate(unsigned int Year, unsigned int Month, unsigned int Day)
{
    unsigned char length;
     unsigned char data[20];
    
    length = 0;
    SendingWord.WordData = Year;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = Month;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = Day;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    
    uC_HMI_RunWriteMultiWordSend(16150, length, data);    
}

void Set_uCHMI_RtcTime(unsigned int Hour, unsigned int Min, unsigned int Sec)
{
    unsigned char length;
     unsigned char data[20];
    
    length = 0;
    SendingWord.WordData = Hour;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = Min;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];
    SendingWord.WordData = Sec;
    data[length++] = SendingWord.Byte[1];
    data[length++] = SendingWord.Byte[0];    
    
    uC_HMI_RunWriteMultiWordSend(16153, length, data);    
}


void uC_HMI_Check_Ack(unsigned char state)
{
    unsigned char index;
    index = ucHMISuddenSendRegister.ReadIndex;
    if( ucHMISuddenSendRegister.state[index] == state )
        ucHMISuddenSendRegister.state[index] = 0;
}

unsigned int uC_HMI_CRC_CREATE(unsigned char *data, unsigned char lenth)
{
    unsigned char i;
    unsigned char e, p;
    unsigned short f, crc;
    crc = 0xffff;
    
    for (i = 1; i < lenth; i++) 
    {
        e = crc ^ data[i];
        p = e ^ (e >> 4);
        p = p ^ (p >> 2);
        p = p ^ (p >> 1);
        p = p & 1;
        f = e | (p << 8);
        crc = (crc >> 8) ^ (f << 6) ^ (f << 7) ^ (f >> 8);
    }
    
    return crc;    
}

unsigned char uC_HMI_CRC_Check_OK(unsigned char *data, unsigned char length)
{
    unsigned char ret;
    unsigned int crc_check_data, crc_packet_data;
    
    crc_check_data = uC_HMI_CRC_CREATE(data, length);
    crc_packet_data = 0;
    crc_packet_data = (data[length] | (data[length+1] << 8));
    
    if( crc_packet_data == crc_check_data )
        ret = 1;
    else
        ret = 0;
    
    return ret;
    
}




