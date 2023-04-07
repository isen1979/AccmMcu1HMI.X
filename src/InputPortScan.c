/*
 * File:   InputPortScan.c
 * Author: user
 *
 * Created on 2018年12月6日, 上午 11:31
 */

#include "..\h\Global_define.h"
#include "..\h\Data_API.h"
#include "..\h\System_Control.h"
#include "..\h\IO_Driver.h"
#include "..\h\Datien_IO_Define.h"

#define PORT_BITS_NUM 8
#define DECIDE_COUNT 10

extern _SYSTEM_PARAMETER SystemParameter;
extern unsigned char MotorRunState;
extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];

unsigned char PortCounterH[PORT_BITS_NUM], PortCounterJ[PORT_BITS_NUM], PortCounterD[PORT_BITS_NUM];
//RD0 - RD7 : D_IN0 - D_IN7
//RH8 - RH15 : D_IN8 - D_IN15
unsigned int lastPortValueH;
unsigned long lastInputPortValue=0xFFFFFFFF, InputPortValue=0;
unsigned long lastOtherInputPortValue=0xFFFFFFFF, OtherInputPortValue=0;
void ScanPortH(void)
{
    unsigned char i;
    unsigned int Pattern, PortValue, lastPortValue, PortValueFinal;
    
    PortValue = ~PORTH;    
    lastPortValue = lastPortValueH;    

    for(i=0;i<PORT_BITS_NUM;i++)
    {
        Pattern = 0x0100 << i;
        if( (lastPortValue & Pattern)  != (PortValue & Pattern) )
        {
            PortCounterH[i] = 0;
        }
        else
        {
            if( PortCounterH[i] < DECIDE_COUNT )
                PortCounterH[i]++;
            else
            {
                PortCounterH[i] = DECIDE_COUNT;         
                PortValueFinal &= ~Pattern;
                PortValueFinal |= (PortValue & Pattern);
            }            
        }
    }
    lastPortValueH = PortValue;
    InputPortValue &= 0xFFFF00FF;//Clear High Byte
    InputPortValue |= PortValueFinal;
}

void ScanPortJ(void)
{/*
    unsigned char i;
    unsigned int Pattern, PortValue, lastPortValue, PortValueFinal;
    unsigned int *pPort;    
    
    PortValue = PORTJ;    
    lastPortValue = lastPortValueJ;   

 
    for(i=0;i<PORT_BITS_NUM;i++)
    {
        Pattern = 0x0001 << i;
        if( (lastPortValue & Pattern)  != (PortValue & Pattern) )
        {
            PortCounterJ[i] = 0;
        }
        else
        {
            if( PortCounterJ[i] < DECIDE_COUNT )
                PortCounterJ[i]++;
            else
            {
                PortCounterJ[i] = DECIDE_COUNT;         
                PortValueFinal &= ~Pattern;
                PortValueFinal |= (PortValue & Pattern);                
            }
        }
    }
    lastPortValueJ = PortValue;  
  * */
}

unsigned int lastPortValueD;
void ScanPortD(void)
{
    unsigned char i;
    unsigned int Pattern, PortValue, lastPortValue, PortValueFinal;  
    
    PortValue = ~PORTD;    
    lastPortValue = lastPortValueD;    

    for(i=0;i<PORT_BITS_NUM;i++)
    {
        Pattern = 0x0001 << i;
        if( (lastPortValue & Pattern)  != (PortValue & Pattern) )
        {
            PortCounterD[i] = 0;
        }
        else
        {
            if( PortCounterD[i] < DECIDE_COUNT )
                PortCounterD[i]++;
            else
            {
                PortCounterD[i] = DECIDE_COUNT;         
                PortValueFinal &= ~Pattern;
                PortValueFinal |= (PortValue & Pattern);
            }
        }
    }
    lastPortValueD = PortValue;
    InputPortValue &= 0xFFFFFF00;//Clear Low Byte
    InputPortValue |= PortValueFinal;    
}

extern unsigned int EXTIO_GET_INPUT(void);
unsigned int lastExternalInput;
#define EXT_INPUT_BIT_NUM 16
unsigned char ExternalPortCounter[EXT_INPUT_BIT_NUM];
void ExternalInputScan(void)
{
    unsigned char i;
    unsigned int Pattern, PortValue, lastPortValue;
    unsigned long PortValueFinal;
    
    PortValue = EXTIO_GET_INPUT();

    lastPortValue = lastExternalInput;

    for(i=0;i<EXT_INPUT_BIT_NUM;i++)
    {
        Pattern = 0x00000001 << i;
        if( (lastPortValue & Pattern)  != (PortValue & Pattern) )
        {
            ExternalPortCounter[i] = 0;
        }
        else
        {
            if( ExternalPortCounter[i] < DECIDE_COUNT )
                ExternalPortCounter[i]++;
            else
            {
                ExternalPortCounter[i] = DECIDE_COUNT;         
                PortValueFinal &= ~Pattern;
                PortValueFinal |= (PortValue & Pattern);
            }
        }
    }
    lastExternalInput = PortValue;
    InputPortValue &= 0x0000FFFF;
    InputPortValue |= (PortValueFinal << 16);
    InputPortValue &= 0x7FFFFFFF;
    OtherInputPortValue = 0;
    OtherInputPortValue |= (PortValueFinal >> 15);
}

void ScanInputPort(void)
{
    ScanPortH();
    ScanPortD();
    ExternalInputScan();
}

