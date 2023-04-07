/*
 * File:   StorageDev.c
 * Author: user
 *
 * Created on 2018年5月17日, 下午 1:08
 */

#include "..\h\SystemControl.h"

#define EEPROM_MAX_READ_WRITE_REPEAT 5
//#define SYSTEM_PARAMETER_START_ADDR 0
#define SYSTEM_RUN_TIME_PARA_START_ADDR 352
//Philip 20180627 02 #define EEPROM_PAGE_WRITE_SIZE 16
#define EEPROM_ONE_PAGE_SIZE 256
#define EEPROM_4K_SIZE 512
#define EEPROM_U5_P0_W 0xA4//0xA4//0xA0//0xA8
#define EEPROM_U5_P1_W 0xA6//0xA6//0xA2//0xAA
#define EEPROM_U5_P0_R 0xA5//0xA5//0xA1//0xA9
#define EEPROM_U5_P1_R 0xA7//0xA7//0xA3//0xAB

#define EEPROM_U3_P0_W 0xA0//0xAC//0xA4//0xA8
#define EEPROM_U3_P1_W 0xA2//0xAE//0xA6//0xAA
#define EEPROM_U3_P0_R 0xA1//0xAD//0xA5//0xA9
#define EEPROM_U3_P1_R 0xA3//0xAF//0xA7//0xAB

#define EEPROM_U6_P0_W 0xA8//0xA4//0xA0//0xA8
#define EEPROM_U6_P1_W 0xAA//0xA6//0xA2//0xAA
#define EEPROM_U6_P0_R 0xA9//0xA5//0xA1//0xA9
#define EEPROM_U6_P1_R 0xAB//0xA7//0xA3//0xAB

#define EEPROM_U4_P0_W 0xA0//0xA4//0xA0//0xA8
#define EEPROM_U4_P1_W 0xA2//0xA6//0xA2//0xAA
#define EEPROM_U4_P0_R 0xA1//0xA5//0xA1//0xA9
#define EEPROM_U4_P1_R 0xA3//0xA7//0xA3//0xAB

#define READ_WRITE_PROCESS_SIZE 20

#define EEPROM_WRITE_WAIT_TIME 10//Timer Interrupt 1msec ==> Wait Time = 10msec
#define EEPROM_READ_WRITE_MAX_FAULT_COUNT 10//Philip 20180720 01

enum EEPROM_ID_ENUM
{
    EEPROM_U3=1,
    EEPROM_U4,    
    EEPROM_U5,
    EEPROM_U6
};

enum EEPROM_READ_WRITE_ADDRESS_SEGEMENT
{
    EEPROM_SYSTEM_PARAMETER=0,
    EEPROM_SYSTEM_RUN_TIME_PARAMETER,
    EEPROM_FEED_NOW_TURNS,
    EEPROM_ALARM_HISTORY,
    EEPROM_END
};

typedef struct __EEPROM_READ_WRITE_PROCESS
{
    unsigned char Process[READ_WRITE_PROCESS_SIZE];
    unsigned char *ReadWriteBuf[READ_WRITE_PROCESS_SIZE];
    unsigned int ReadWriteSize[READ_WRITE_PROCESS_SIZE];
    unsigned int ReadWriteAddr[READ_WRITE_PROCESS_SIZE];   
    unsigned char state[READ_WRITE_PROCESS_SIZE];
    unsigned char check_buf[EEPROM_PAGE_WRITE_SIZE];
    unsigned char bufw[EEPROM_PAGE_WRITE_SIZE];
    unsigned char *buf;
    unsigned int size;
    unsigned char id;
    unsigned int addr;    
    unsigned char ProcessIdx;
    unsigned char RegisterIdx;
    unsigned int WaitProcessSize;
} _EEPROM_READ_WRITE_PROCESS;

extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
extern void i2c_wr(unsigned char id , unsigned int addr ,unsigned char *data,unsigned int nbyte,unsigned char addr_type);
extern unsigned int CRC_CREATE(unsigned char *data, unsigned char lenth);

_EEPROM_READ_WRITE_PROCESS WriteEEPROM, ReadEEPROM;

void I2C_EEPROM_WRITE(unsigned char id, unsigned char *buf, unsigned int size, unsigned int addr)
{   
    switch(id)
    {
        case EEPROM_U3:
            if(addr < 256)      
                i2c_wr(EEPROM_U3_P0_W, addr, buf, size, 1);  
            else
                i2c_wr(EEPROM_U3_P1_W, addr, buf, size, 1);
            break;            
        case EEPROM_U4 :
            if(addr < 256)      
                i2c_wr(EEPROM_U4_P0_W, addr, buf, size, 1);  
            else
                i2c_wr(EEPROM_U4_P1_W, addr, buf, size, 1);            
            break;
        case EEPROM_U5 :                
            if(addr < 256)      
                i2c_wr(EEPROM_U5_P0_W, addr, buf, size, 1);  
            else
                i2c_wr(EEPROM_U5_P1_W, addr, buf, size, 1);
            break;
        case EEPROM_U6 :
            if(addr < 256)      
                i2c_wr(EEPROM_U6_P0_W, addr, buf, size, 1);  
            else
                i2c_wr(EEPROM_U6_P1_W, addr, buf, size, 1);            
            break;
    }
}

void I2C_EEPROM_READ(unsigned char id, unsigned char *buf, unsigned int size, unsigned int StartAddr)
{
    unsigned int i;   
    for(i=0;i<size;i++)
    {
        switch(id)
        {
            case EEPROM_U3:
                if((StartAddr+i)>=256)
                    i2c_wr(EEPROM_U3_P1_R, StartAddr+i ,(unsigned char*)(&buf[i]),1,1); 
                else
                    i2c_wr(EEPROM_U3_P0_R, StartAddr+i ,(unsigned char*)(&buf[i]),1,1);                 
                break;                     
            case EEPROM_U4 :
                if((StartAddr+i)>=256)
                    i2c_wr(EEPROM_U4_P1_R, StartAddr+i ,(unsigned char*)(&buf[i]),1,1); 
                else
                    i2c_wr(EEPROM_U4_P0_R, StartAddr+i ,(unsigned char*)(&buf[i]),1,1);                               
                break;
            case EEPROM_U5 :    
                if((StartAddr+i)>=256)
                    i2c_wr(EEPROM_U5_P1_R, StartAddr+i ,(unsigned char*)(&buf[i]),1,1); 
                else
                    i2c_wr(EEPROM_U5_P0_R, StartAddr+i ,(unsigned char*)(&buf[i]),1,1);                   
                break;
            case EEPROM_U6 :
                if((StartAddr+i)>=256)
                    i2c_wr(EEPROM_U6_P1_R, StartAddr+i ,(unsigned char*)(&buf[i]),1,1); 
                else
                    i2c_wr(EEPROM_U6_P0_R, StartAddr+i ,(unsigned char*)(&buf[i]),1,1);                 
                break;                 
        }         
    }
}


void WriteSystemParameterToI2C_EEPROM(unsigned char *buf, unsigned char *LastData, unsigned int StartAddr, unsigned int size, unsigned char flag)
{
    unsigned int crc_data, Nowaddr, WriteSize, ChangeCount;
    unsigned char i, eepromwriteOK, WriteCount, id;
    unsigned char bufw[EEPROM_PAGE_WRITE_SIZE], bufr[EEPROM_PAGE_WRITE_SIZE];
    WriteCount = 0;
    ChangeCount = 0;
//    StartAddr = 0;
    if(flag==0)
        id = EEPROM_U4;//EEPROM_U3;
    else if(flag==1)
        id = EEPROM_U5;//EEPROM_U5;
    else if(flag==2)
        id = EEPROM_U3;
    else if(flag==3)
        id = EEPROM_U6;
    
    Nowaddr = StartAddr;
    for(WriteSize=0;WriteSize<size;)
    {           
        for(i=0;i<(EEPROM_PAGE_WRITE_SIZE-2);i++)
        {
            if((size - WriteSize)>0)
            {
                bufw[i] = buf[WriteSize];
                if(buf[WriteSize] != LastData[WriteSize])
                {
                    LastData[WriteSize] = buf[WriteSize];
                    ChangeCount++;
                }
                
                WriteSize++;
            }
            else
                bufw[i] = 0;           
        }
        crc_data = CRC_CREATE(bufw, (EEPROM_PAGE_WRITE_SIZE-2));
        bufw[EEPROM_PAGE_WRITE_SIZE-2] = (crc_data>>8) & 0x00ff;
        bufw[EEPROM_PAGE_WRITE_SIZE-1] = (crc_data & 0x00ff);        
        if(ChangeCount>0)
        {
            ChangeCount = 0;
            eepromwriteOK = 0;
            WriteCount = 0;
        }
        else
            eepromwriteOK = 1;
        while(eepromwriteOK==0)
        {                    
            I2C_EEPROM_WRITE(id, bufw, EEPROM_PAGE_WRITE_SIZE, Nowaddr);
            I2C_EEPROM_READ(id, bufr, EEPROM_PAGE_WRITE_SIZE, Nowaddr);
            eepromwriteOK = 1;
            WriteCount++;
            for(i=0;i<EEPROM_PAGE_WRITE_SIZE;i++)
            {
                if(bufw[i] != bufr[i])
                {
                    eepromwriteOK = 0;
                    break;
                }  
            }
            if(WriteCount > EEPROM_MAX_READ_WRITE_REPEAT)
            {
                //Pose Error Anouncement
                break;
            }
        }
        Nowaddr = Nowaddr + EEPROM_PAGE_WRITE_SIZE;
    }
}


enum EEPROM_READ_WRITE_STATE
{
    EEPROM_READ_WRITE_STATE_wait=0,
    EEPROM_READ_WRITE_STATE_read_prepare,
    EEPROM_READ_WRITE_STATE_read,
    EEPROM_READ_WRITE_STATE_wait_read_complete,
    EEPROM_READ_WRITE_STATE_prepare_next_read,
    EEPROM_READ_WRITE_STATE_write_prepare,
    EEPROM_READ_WRITE_STATE_write,
    EEPROM_READ_WRITE_STATE_wait_write_complete,
    EEPROM_READ_WRITE_STATE_write_check,
    EEPROM_READ_WRITE_STATE_prepare_next_write,
    
    
    EEPROM_READ_WRITE_STATE_pending,    
    
    EEPROM_READ_WRITE_STATE_read_error,//Philip 20180720 01
    EEPROM_READ_WRITE_STATE_write_error,//Philip 20180720 01
        
    EEPROM_READ_WRITE_STATE_enumEnd
};

unsigned char EEPROM_WriteState=EEPROM_READ_WRITE_STATE_wait, EEPROM_ReadState=EEPROM_READ_WRITE_STATE_wait;

void RegisterWriteEEPROM(unsigned int addr, unsigned char *buf, unsigned int size)
{
    if(WriteEEPROM.WaitProcessSize < READ_WRITE_PROCESS_SIZE)
    {
        WriteEEPROM.ReadWriteBuf[WriteEEPROM.RegisterIdx] = buf;
        WriteEEPROM.ReadWriteSize[WriteEEPROM.RegisterIdx] = size;
        WriteEEPROM.ReadWriteAddr[WriteEEPROM.RegisterIdx] = addr;
        WriteEEPROM.WaitProcessSize++;
        WriteEEPROM.RegisterIdx++;
        if(WriteEEPROM.RegisterIdx >= READ_WRITE_PROCESS_SIZE)
            WriteEEPROM.RegisterIdx=0;
    }
    else
        ;//EEPROM Write Error
}

unsigned char RegisterReadEEPROM(unsigned int addr, unsigned char *buf, unsigned int size)
{
    unsigned char ret;
    if(ReadEEPROM.WaitProcessSize < READ_WRITE_PROCESS_SIZE)
    {
        ReadEEPROM.ReadWriteBuf[ReadEEPROM.RegisterIdx] = buf;//Philip 20180530 01
        ReadEEPROM.ReadWriteSize[ReadEEPROM.RegisterIdx] = size;//Philip 20180530 01
        ReadEEPROM.ReadWriteAddr[ReadEEPROM.RegisterIdx] = addr;//Philip 20180530 01
        ReadEEPROM.state[ReadEEPROM.RegisterIdx] = EEPROM_READ_WRITE_STATE_pending;
        ReadEEPROM.WaitProcessSize++;
        ret = ReadEEPROM.RegisterIdx;
        ReadEEPROM.RegisterIdx++;
        if(ReadEEPROM.RegisterIdx >= READ_WRITE_PROCESS_SIZE)
            ReadEEPROM.RegisterIdx=0;   
    }
    else
        ret = 0xFF;//EEPROM Read Error  
    
    return ret;
}

void Built_EEPROM_WriteBuf(void)
{
    unsigned char i;
    unsigned int crc_data;    
    for(i=0;i<(EEPROM_PAGE_WRITE_SIZE - 2);i++)
        WriteEEPROM.bufw[i] =  WriteEEPROM.buf[i];            
            
    crc_data = CRC_CREATE(WriteEEPROM.bufw, (EEPROM_PAGE_WRITE_SIZE-2));            
    WriteEEPROM.bufw[EEPROM_PAGE_WRITE_SIZE-2] = (crc_data>>8) & 0x00ff;            
    WriteEEPROM.bufw[EEPROM_PAGE_WRITE_SIZE-1] = (crc_data & 0x00ff);         
}
unsigned char WriteFaultTimes;//Philip 20180720 01
unsigned char ReadFaultTimes;//Philip 20180720 01
void RunWriteProcess(void)
{    
    unsigned char i, FailCnt;

    switch(EEPROM_WriteState)
    {
        case EEPROM_READ_WRITE_STATE_write_prepare:
            WriteEEPROM.addr = WriteEEPROM.ReadWriteAddr[WriteEEPROM.ProcessIdx]%EEPROM_4K_SIZE;
            WriteEEPROM.id =EEPROM_U3 + (WriteEEPROM.ReadWriteAddr[WriteEEPROM.ProcessIdx]/EEPROM_4K_SIZE);
            WriteEEPROM.buf = WriteEEPROM.ReadWriteBuf[WriteEEPROM.ProcessIdx]; 
            WriteEEPROM.size = WriteEEPROM.ReadWriteSize[WriteEEPROM.ProcessIdx];    
            Built_EEPROM_WriteBuf();
            WriteFaultTimes = 0;//Philip 20180720 01
            EEPROM_WriteState = EEPROM_READ_WRITE_STATE_write;
            break;            
        case EEPROM_READ_WRITE_STATE_write :
            I2C_EEPROM_WRITE(WriteEEPROM.id, WriteEEPROM.bufw, EEPROM_PAGE_WRITE_SIZE, WriteEEPROM.addr);
            DelayTimerCounter[EEPROM_Delay_Timer_Count] = EEPROM_WRITE_WAIT_TIME;
            EEPROM_WriteState = EEPROM_READ_WRITE_STATE_wait_write_complete;
            break;
        case EEPROM_READ_WRITE_STATE_wait_write_complete:
            if( DelayTimerCounter[EEPROM_Delay_Timer_Count] == 0 )
            {
                I2C_EEPROM_READ(WriteEEPROM.id, WriteEEPROM.check_buf, EEPROM_PAGE_WRITE_SIZE, WriteEEPROM.addr);
                EEPROM_WriteState = EEPROM_READ_WRITE_STATE_write_check;
            }
            break;
        case EEPROM_READ_WRITE_STATE_write_check :
            FailCnt = 0;
            for(i=0;i<(EEPROM_PAGE_WRITE_SIZE - 2);i++)
            {
                if( WriteEEPROM.check_buf[i] != WriteEEPROM.bufw[i] )
                    FailCnt++;
            }
            
            if(FailCnt > 0)
            {
                WriteFaultTimes++;//Philip 20180720 01
                if(WriteFaultTimes > EEPROM_READ_WRITE_MAX_FAULT_COUNT)//Philip 20180720 01
                    EEPROM_WriteState = EEPROM_READ_WRITE_STATE_write_error;//Philip 20180720 01
                EEPROM_WriteState = EEPROM_READ_WRITE_STATE_write;
            }
            else if(WriteEEPROM.size > (EEPROM_PAGE_WRITE_SIZE -2))
            {
                WriteEEPROM.size =  WriteEEPROM.size - (EEPROM_PAGE_WRITE_SIZE - 2);
                EEPROM_WriteState = EEPROM_READ_WRITE_STATE_prepare_next_write;
            }
            else
            {
                WriteEEPROM.size =  0;
                WriteEEPROM.ProcessIdx++;
                if(WriteEEPROM.ProcessIdx >= READ_WRITE_PROCESS_SIZE)
                    WriteEEPROM.ProcessIdx = 0;                
                EEPROM_WriteState = EEPROM_READ_WRITE_STATE_wait;                
            }           
            break;
        case EEPROM_READ_WRITE_STATE_prepare_next_write :
            WriteEEPROM.buf = WriteEEPROM.buf + (EEPROM_PAGE_WRITE_SIZE - 2);
            WriteEEPROM.addr = WriteEEPROM.addr + EEPROM_PAGE_WRITE_SIZE;                    
            Built_EEPROM_WriteBuf();
            
            if(WriteEEPROM.addr >= EEPROM_4K_SIZE)
            {
                WriteEEPROM.addr = WriteEEPROM.addr - EEPROM_4K_SIZE;
                WriteEEPROM.id++;
            }
            EEPROM_WriteState = EEPROM_READ_WRITE_STATE_write;
            break;
        case EEPROM_READ_WRITE_STATE_write_error ://Philip 20180720 01
            break;//Philip 20180720 01
    }
}

void Get_EEPROM_Data(unsigned char size)//Philip 20180720 1603
{
    unsigned char i;
    //Philip 20180720 1603 for(i=0;i<(EEPROM_PAGE_WRITE_SIZE-2);i++)
    for(i=0;i<size;i++)//Philip 20180720 1603
        ReadEEPROM.buf[i] =  ReadEEPROM.bufw[i];
}

void RunReadProcess(void)
{

    unsigned int crc_data, buf_crc;  
    
    switch(EEPROM_ReadState)
    {
        case EEPROM_READ_WRITE_STATE_read_prepare:
            ReadEEPROM.addr = ReadEEPROM.ReadWriteAddr[ReadEEPROM.ProcessIdx]%EEPROM_4K_SIZE;
            ReadEEPROM.id =EEPROM_U3 + (ReadEEPROM.ReadWriteAddr[ReadEEPROM.ProcessIdx]/EEPROM_4K_SIZE);
            ReadEEPROM.buf = ReadEEPROM.ReadWriteBuf[ReadEEPROM.ProcessIdx]; 
            ReadEEPROM.size = ReadEEPROM.ReadWriteSize[ReadEEPROM.ProcessIdx]; 
            ReadFaultTimes = 0;//Philip 20180720 01
            EEPROM_ReadState = EEPROM_READ_WRITE_STATE_read;
            break;
        case EEPROM_READ_WRITE_STATE_read :
            I2C_EEPROM_READ(ReadEEPROM.id, ReadEEPROM.bufw, EEPROM_PAGE_WRITE_SIZE, ReadEEPROM.addr);
            EEPROM_ReadState = EEPROM_READ_WRITE_STATE_wait_read_complete;
            break;
        case EEPROM_READ_WRITE_STATE_wait_read_complete :
            crc_data = CRC_CREATE(ReadEEPROM.bufw, (EEPROM_PAGE_WRITE_SIZE-2)); 
            buf_crc = ReadEEPROM.bufw[EEPROM_PAGE_WRITE_SIZE-2];
            buf_crc = (buf_crc << 8) | ReadEEPROM.bufw[EEPROM_PAGE_WRITE_SIZE-1];
            if(buf_crc != crc_data)
            {
                ReadFaultTimes++;//Philip 20180720 01
                if(ReadFaultTimes > EEPROM_READ_WRITE_MAX_FAULT_COUNT)//Philip 20180720 01
                    EEPROM_ReadState = EEPROM_READ_WRITE_STATE_read_error;//Philip 20180720 01
                EEPROM_ReadState = EEPROM_READ_WRITE_STATE_read;
            }
            else if(ReadEEPROM.size > (EEPROM_PAGE_WRITE_SIZE -2))
            {
                Get_EEPROM_Data(EEPROM_PAGE_WRITE_SIZE -2);//Philip 20180720 1603
                ReadEEPROM.size =  ReadEEPROM.size - (EEPROM_PAGE_WRITE_SIZE - 2);
                EEPROM_ReadState = EEPROM_READ_WRITE_STATE_prepare_next_read;
            }
            else
            {
                Get_EEPROM_Data(ReadEEPROM.size);//Philip 20180720 1603
                ReadEEPROM.size =  0;
                ReadEEPROM.state[ReadEEPROM.ProcessIdx] = EEPROM_READ_WRITE_STATE_wait;
                
                ReadEEPROM.ProcessIdx++;
                if(ReadEEPROM.ProcessIdx >= READ_WRITE_PROCESS_SIZE)
                    ReadEEPROM.ProcessIdx = 0;                 
                
                EEPROM_ReadState = EEPROM_READ_WRITE_STATE_wait;                
            }                  
            break;
        case EEPROM_READ_WRITE_STATE_prepare_next_read :
            ReadEEPROM.buf = ReadEEPROM.buf + (EEPROM_PAGE_WRITE_SIZE - 2);
            ReadEEPROM.addr = ReadEEPROM.addr + EEPROM_PAGE_WRITE_SIZE;
            
            if(ReadEEPROM.addr >= EEPROM_4K_SIZE)
            {
                ReadEEPROM.addr = ReadEEPROM.addr - EEPROM_4K_SIZE;
                ReadEEPROM.id++;
            }
            EEPROM_ReadState = EEPROM_READ_WRITE_STATE_read;            
            break;
        case EEPROM_READ_WRITE_STATE_read_error ://Philip 20180720 01
            break;//Philip 20180720 01
    }    
}

void RunEEPROM_ReadWriteProcess(void)
{
    if(WriteEEPROM.WaitProcessSize > 0)
    {
        if(EEPROM_WriteState == EEPROM_READ_WRITE_STATE_wait)
        {
            WriteEEPROM.WaitProcessSize--;
            EEPROM_WriteState = EEPROM_READ_WRITE_STATE_write_prepare;
        }
    }
    else if(ReadEEPROM.WaitProcessSize > 0) 
    {        
        if(EEPROM_ReadState == EEPROM_READ_WRITE_STATE_wait)
        {
            ReadEEPROM.WaitProcessSize--;
            EEPROM_ReadState = EEPROM_READ_WRITE_STATE_read_prepare;
        }
    }
    
    if(EEPROM_WriteState != EEPROM_READ_WRITE_STATE_wait)
        RunWriteProcess();
    else if(EEPROM_ReadState != EEPROM_READ_WRITE_STATE_wait)
        RunReadProcess();        
}

unsigned char IsReadEEPROM_DataFinish(void)
{
    unsigned char ret;
    if( (EEPROM_ReadState == EEPROM_READ_WRITE_STATE_wait) && (ReadEEPROM.WaitProcessSize == 0) )
        ret = 1;
    else
        ret = 0;
        
    return ret;
}

void Initial_EEPROM_Read_Write_Process(void)
{
    WriteEEPROM.RegisterIdx = 0;
    WriteEEPROM.ProcessIdx = 0;
    ReadEEPROM.RegisterIdx = 0;
    ReadEEPROM.ProcessIdx = 0;
    EEPROM_WriteState = EEPROM_READ_WRITE_STATE_wait;
    EEPROM_ReadState = EEPROM_READ_WRITE_STATE_wait;
}