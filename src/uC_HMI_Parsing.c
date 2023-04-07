/*
 * File:   uC_HMI_Parsing.c
 * Author: user
 *
 * Created on 2020年4月8日, 下午 6:01
 */
#include "..\h\SystemControl.h"
#include "uC_HMI_Control.h"

#define UC_HMI_READ_BYTE_ACK UC_HMI_READ_BYTE
#define UC_HMI_READ_WORD_ACK UC_HMI_READ_WORD
#define UC_HMI_READ_LONG_WORD_ACK UC_HMI_READ_LONG_WORD
#define UC_HMI_WRITE_BYTE_ACK UC_HMI_WRITE_BYTE
#define UC_HMI_WRITE_WORD_ACK UC_HMI_WRITE_WORD
#define UC_HMI_WRITE_LONG_WORD_ACK UC_HMI_WRITE_LONG_WORD
#define UC_HMI_READ_TEXT_ACK UC_HMI_READ_TEXT
#define UC_HMI_WRITE_TEXT_ACK UC_HMI_WRITE_TEXT
#define UC_HMI_DELETE_TEXT_ACK UC_HMI_DELETE_TEXT

#define VARIBLE_CHANGE_EVENT 0xEB
#define START_UP_CMD 0xE0



extern void MachineUcHMI_EventProcess(unsigned int addr);
extern void GetReadByteData(void);
extern void GetReadWordData(void);
extern void GetReadLongWordData(void);
extern void GetReadTextData(void);
extern void uC_HMI_Check_Ack(unsigned char state);
extern unsigned char uC_HMI_CRC_Check_OK(unsigned char *data, unsigned char length);
extern void uC_HMI_SetPage(unsigned int page);

extern _PARSING_WORD U1_ParsingWord;
extern unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];
extern unsigned char SystemInitialState;
extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
unsigned char StartupFinsihFlag=0;
void uC_HMI_ParsingProcess(void)
{
    unsigned int addr;
       
    switch(UART1RxBuffer[2])
    {
        case START_UP_CMD :
            if( UART1RxBuffer[1] == 1 )
            {
                StartupFinsihFlag = 1;
                uC_HMI_SetPage(11);//Show the First Page
            }
/*            
            if( (UART1RxBuffer[1] == 1) && (SystemInitialState == SystemFinishLoadSystemParamterEnum) )
                DelayTimerCounter[ParameterLoadTimeEnum] = 0;
 */
            break;
        case VARIBLE_CHANGE_EVENT :
            U1_ParsingWord.Byte[0] = UART1RxBuffer[4];
            U1_ParsingWord.Byte[1] = UART1RxBuffer[3];
            addr = U1_ParsingWord.WordData;
            MachineUcHMI_EventProcess(addr);
            break;
        case UC_HMI_READ_BYTE :
            GetReadByteData();
            uC_HMI_Check_Ack(UC_HMI_READ_BYTE_ACK);
            break;
        case UC_HMI_READ_WORD :
            GetReadWordData();
            uC_HMI_Check_Ack(UC_HMI_READ_WORD_ACK);            
        case UC_HMI_READ_LONG_WORD :
            GetReadLongWordData();
            uC_HMI_Check_Ack(UC_HMI_READ_LONG_WORD_ACK);
            break;
        case UC_HMI_READ_TEXT :
            GetReadTextData();
            uC_HMI_Check_Ack(UC_HMI_READ_TEXT_ACK);
            break;
        case UC_HMI_WRITE_BYTE_ACK :
            uC_HMI_Check_Ack(UC_HMI_WRITE_BYTE_ACK);
            break;
        case UC_HMI_WRITE_WORD_ACK :
            uC_HMI_Check_Ack(UC_HMI_WRITE_WORD_ACK);
            break;
        case UC_HMI_WRITE_LONG_WORD_ACK :
            uC_HMI_Check_Ack(UC_HMI_WRITE_LONG_WORD_ACK);
            break;
        case UC_HMI_WRITE_TEXT_ACK :
            uC_HMI_Check_Ack(UC_HMI_WRITE_TEXT_ACK);
            break;
        case UC_HMI_DELETE_TEXT_ACK :
            uC_HMI_Check_Ack(UC_HMI_DELETE_TEXT_ACK);
            break;
    }
}

void uC_HMI_Parsing(void)
{
    unsigned char length;
    
    length = UART1RxBuffer[1]+2;
    if( uC_HMI_CRC_Check_OK(UART1RxBuffer, length) == 1 )
    {
        if( (UART1RxBuffer[0] == 0xAF) && (UART1RxBuffer[length+2] == 0xEF) )
            uC_HMI_ParsingProcess();
    }
}
