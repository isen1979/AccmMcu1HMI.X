/*
 * File:   Machine_uC_HMI_Control.c
 * Author: user
 *
 * Created on 2020年4月21日, 上午 11:16
 */
#include "..\h\System_Control.h"
#include "uC_HMI_Control.h"

//extern void SaveEngineerMode(void);
extern void RegisterSendingPacket(unsigned char state, unsigned int addr, unsigned char *data, unsigned char size);
extern void uC_HMI_RunWriteSingleByteSend(unsigned int addr, unsigned char Value);
extern void uC_HMI_RunWriteMultiByteSend(unsigned int addr, unsigned char length, unsigned char *data);
extern void uC_HMI_RunWriteSingleLongWordSend(unsigned int addr, long Value);
extern void uC_HMI_RunWriteSingleWordSend(unsigned int addr, unsigned int Value);
extern void uC_HMI_RunReadLongWordSend(unsigned int addr, unsigned char count);
extern void uC_HMI_RunReadWordSend(unsigned int addr, unsigned char count);
extern void uC_HMI_RunWriteTextVariableSend(unsigned int addr, unsigned char Count);
extern void uC_HMI_RunWriteMultiWordSend(unsigned int addr, unsigned char length, unsigned char *data);
extern void Send_uCHMI_SystemParameter(void);
extern void uC_HMI_SetPage(unsigned int page);

extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
extern unsigned char MotorRunState;
extern _SYSTEM_PARAMETER SystemParameter, lastSystemParameter;
extern _SENDING_WORD SendingWord;
extern unsigned int TxTextBuffer[MAX_WRITE_TEXT_SIZE];

#define INDEX_FILENAME_LENGTH 11
#define RECORD_FILENAME_LENGTH 6
#define DATE_TIME_FILENAME_LENGTH 10
unsigned int IndexFileName[INDEX_FILENAME_LENGTH] = {0x0049, 0x006e, 0x0064, 0x0065, 0x0078, 0x0032, 0x0030, 0x002e, 0x0062, 0x0069, 0x006e};//Index20.bin//\u0049\u006e\u0064\u0065\u0078\u0032\u0030\u002e\u0062\u0069\u006e
unsigned int RecordFileName[RECORD_FILENAME_LENGTH] = {0x0032, 0x0030, 0x002e, 0x0062, 0x0069, 0x006e};//20.bin//\u0032\u0030\u002e\u0062\u0069\u006e
unsigned int DateTimeFileName[DATE_TIME_FILENAME_LENGTH] = {0x0054, 0x0069, 0x006d, 0x0065, 0x0032, 0x0030, 0x002e, 0x0062, 0x0069, 0x006e};//Time20.bin//\u0054\u0069\u006d\u0065\u0032\u0030\u002e\u0062\u0069\u006e
unsigned long uCHMI_DateCode;

void SendRecordFileName(void)
{
    unsigned char i;
    unsigned long DateVale10, DateVale1;
    
    DateVale10 = uCHMI_DateCode%100;
    DateVale10 = DateVale10 / 10;
    DateVale1 = uCHMI_DateCode%10;
    
    IndexFileName[5] = DateVale10 + 0x0030;
    IndexFileName[6] = DateVale1 + 0x0030;
    for(i=0;i<INDEX_FILENAME_LENGTH;i++)
        TxTextBuffer[i] = IndexFileName[i];
    
    uC_HMI_RunWriteTextVariableSend(150, INDEX_FILENAME_LENGTH);
    
    RecordFileName[0] = DateVale10 + 0x0030;
    RecordFileName[1] = DateVale1 + 0x0030;    
    for(i=0;i<RECORD_FILENAME_LENGTH;i++)
        TxTextBuffer[i] = RecordFileName[i];
    
    uC_HMI_RunWriteTextVariableSend(151, RECORD_FILENAME_LENGTH);
    
    DateTimeFileName[4] = DateVale10 + 0x0030;
    DateTimeFileName[5] = DateVale1 + 0x0030;        
    for(i=0;i<DATE_TIME_FILENAME_LENGTH;i++)
        TxTextBuffer[i] = DateTimeFileName[i];
    
    uC_HMI_RunWriteTextVariableSend(152, DATE_TIME_FILENAME_LENGTH);
}

void Get_uCHMI_DateCodeSend(void)
{
    uC_HMI_RunReadLongWordSend(UC_HMI_DATE_CODE_ADDR, 1);//Get Date Code
}

void SetReadSDIndex(void)
{
    uC_HMI_RunWriteSingleByteSend(START_READ_SD_INDEX_ADDR, 1);
}

void StartGetReadSDIndex(void)
{
    uC_HMI_RunReadWordSend(GET_READ_SD_INDEX_ADDR, 2);
}

void ReadSD_RecordData(void)
{
    uC_HMI_RunWriteSingleByteSend(READ_RECORD_DATA_ADDR, 1);
}


unsigned long uCHMI_DateCode, PlayBackDayCode;
void Get_uCHMI_DateCode(unsigned int addr, long Value)
{
    switch(addr)
    {
        case UC_HMI_DATE_CODE_ADDR :
            uCHMI_DateCode = Value;
            PlayBackDayCode = uCHMI_DateCode;
            SendRecordFileName();
            SetReadSDIndex();
            uC_HMI_SetPage(11);//Show the First Page
            Send_uCHMI_SystemParameter();
            StartGetReadSDIndex();            
            break;
    }
}

unsigned int IndexMonthCode, IndexRecordPosition;
void SetRecordPosition(unsigned int StartPosition)
{
    unsigned char i;
    unsigned char data[2*RECORD_ITEM_NUM];
    
    for(i=0;i<RECORD_ITEM_NUM;i++)
    {
        if( StartPosition == 0 )
        {
            SendingWord.WordData = (i * 1500) - 1;
            if( i == (RECORD_ITEM_NUM - 1) )
                SendingWord.WordData = 0;
        }
        else
        {
            SendingWord.WordData = StartPosition + (i * 1500);
            if( i == (RECORD_ITEM_NUM - 1) )
                SendingWord.WordData = StartPosition * 2;
        }
        
        data[2*i] = SendingWord.Byte[1];
        data[2*i+1] = SendingWord.Byte[0];
    }
    
    uC_HMI_RunWriteMultiWordSend(RECORD_POSITION_ADDR, (2*RECORD_ITEM_NUM), data);
}

void GetReadSDIndex(unsigned int addr, unsigned int *data, unsigned char Count)
{
    switch(addr)
    {
        case GET_READ_SD_INDEX_ADDR :
            if( Count == 2 )
            {
                IndexMonthCode = data[0];
                IndexRecordPosition = data[1];
                
                if( IndexRecordPosition >= 1440 )
                    SetRecordPosition(0);
                else if( IndexMonthCode >= 12112 )
                    SetRecordPosition(0);
                else if( (uCHMI_DateCode/100) == IndexMonthCode )
                {
                    ReadSD_RecordData();
                    SetRecordPosition(IndexRecordPosition);
                }
                else
                    SetRecordPosition(0);
            }
            break;
    }
}

void SendChartRecordFileName(unsigned long Date, unsigned char ChartNum)
{
    unsigned char i;
    unsigned long DateVale10, DateVale1;
    
    DateVale10 = Date%100;
    DateVale10 = DateVale10 / 10;
    DateVale1 = Date%10;
    
    IndexFileName[5] = DateVale10 + 0x0030;
    IndexFileName[6] = DateVale1 + 0x0030;
    for(i=0;i<INDEX_FILENAME_LENGTH;i++)
        TxTextBuffer[i] = IndexFileName[i];
    
    switch(ChartNum)
    {
        case 0 :
            uC_HMI_RunWriteTextVariableSend(253, INDEX_FILENAME_LENGTH);
            break;
        case 1 :
            uC_HMI_RunWriteTextVariableSend(256, INDEX_FILENAME_LENGTH);
            break;
        case 2 :
            uC_HMI_RunWriteTextVariableSend(259, INDEX_FILENAME_LENGTH);
            break;
    }
    
    
    RecordFileName[0] = DateVale10 + 0x0030;
    RecordFileName[1] = DateVale1 + 0x0030;    
    for(i=0;i<RECORD_FILENAME_LENGTH;i++)
        TxTextBuffer[i] = RecordFileName[i];

    switch(ChartNum)
    {
        case 0 :    
            uC_HMI_RunWriteTextVariableSend(254, RECORD_FILENAME_LENGTH);
            break;
        case 1 :
            uC_HMI_RunWriteTextVariableSend(257, RECORD_FILENAME_LENGTH);
            break;
        case 2 :
            uC_HMI_RunWriteTextVariableSend(260, RECORD_FILENAME_LENGTH);
            break;
    }
    
    DateTimeFileName[4] = DateVale10 + 0x0030;
    DateTimeFileName[5] = DateVale1 + 0x0030;        
    for(i=0;i<DATE_TIME_FILENAME_LENGTH;i++)
        TxTextBuffer[i] = DateTimeFileName[i];
    
    switch(ChartNum)
    {
        case 0 :
            uC_HMI_RunWriteTextVariableSend(255, DATE_TIME_FILENAME_LENGTH);
            break;
        case 1 :
            uC_HMI_RunWriteTextVariableSend(258, DATE_TIME_FILENAME_LENGTH);
            break;
        case 2 :
            uC_HMI_RunWriteTextVariableSend(261, DATE_TIME_FILENAME_LENGTH);
            break;            
    }
}

void PlayBackUpdateChartTimeDisplay(unsigned char ChartId)
{
    switch(ChartId)
    {
        case 1 ://Chart 1
            uC_HMI_RunWriteSingleByteSend(517, 1);//StartUpdateShowChartCount = 1
            uC_HMI_RunWriteSingleByteSend(518, 1);//ShowChartTimeUpdate = 1
//            uC_HMI_RunWriteSingleByteSend(519, 1);//ShowChartTimeReadSDTriger = 1
            break;
        case 2 ://Chart 2
            uC_HMI_RunWriteSingleByteSend(517, 2);//StartUpdateShowChartCount = 2
            uC_HMI_RunWriteSingleByteSend(518, 2);//ShowChartTimeUpdate = 2
//            uC_HMI_RunWriteSingleByteSend(519, 2);//ShowChartTimeReadSDTriger = 2
            break;
        case 3 ://Chart 3
            uC_HMI_RunWriteSingleByteSend(517, 3);//StartUpdateShowChartCount = 3
            uC_HMI_RunWriteSingleByteSend(518, 3);//ShowChartTimeUpdate = 3
//            uC_HMI_RunWriteSingleByteSend(519, 3);//ShowChartTimeReadSDTriger = 3
            break;
    }    
}

void StartChart1PlayBack(void)
{
    PlayBackDayCode = uCHMI_DateCode;
    SendChartRecordFileName(PlayBackDayCode, 0);
    uC_HMI_RunWriteSingleByteSend(466, 1);//ReadShowChart1RecordData = 1
    PlayBackUpdateChartTimeDisplay(1);
    uC_HMI_SetPage(41);//Show Chart 1 Playback-Page
}

void StartChart2PlayBack(void)
{
    PlayBackDayCode = uCHMI_DateCode;
    SendChartRecordFileName(PlayBackDayCode, 1);
    uC_HMI_RunWriteSingleByteSend(467, 1);//ReadShowChart2RecordData = 1
    PlayBackUpdateChartTimeDisplay(2);
    uC_HMI_SetPage(40);//Show Chart 2 Playback-Page
}

void StartChart3PlayBack(void)
{
    PlayBackDayCode = uCHMI_DateCode;
    SendChartRecordFileName(PlayBackDayCode, 2);
    uC_HMI_RunWriteSingleByteSend(468, 1);//ReadShowChart3RecordData = 1
    PlayBackUpdateChartTimeDisplay(3);
    uC_HMI_SetPage(42);//Show Chart 3 Playback-Page
}

void SetPlayBackDay(unsigned char ChartId, unsigned char IncDecFlag)
{
    if( IncDecFlag == 1 )
    {
        PlayBackDayCode++;
        if( (PlayBackDayCode%100) > 31 )
            PlayBackDayCode--;
    }
    else if( PlayBackDayCode > 1 )
        PlayBackDayCode--;
     
    switch(ChartId)
    {
        case 0 ://Chart 1
            SendChartRecordFileName(PlayBackDayCode, 0);
            uC_HMI_RunWriteSingleByteSend(466, 1);//ReadShowChart1RecordData = 1
            PlayBackUpdateChartTimeDisplay(1);
            break;
        case 1 ://Chart 2
            SendChartRecordFileName(PlayBackDayCode, 1);
            uC_HMI_RunWriteSingleByteSend(467, 1);//ReadShowChart2RecordData = 1
            PlayBackUpdateChartTimeDisplay(2);
            break;
        case 2 ://Chart 3
            SendChartRecordFileName(PlayBackDayCode, 2);
            uC_HMI_RunWriteSingleByteSend(468, 1);//ReadShowChart3RecordData = 1
            PlayBackUpdateChartTimeDisplay(3);
            break;
    }
}
