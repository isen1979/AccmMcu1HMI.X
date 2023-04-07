/*
 * File:   uC_HMI_Control.c
 * Author: user
 *
 * Created on 2020年4月6日, 下午 3:38
 */
#include "..\h\System_Control.h"
#include "uC_HMI_Control.h"

extern void uC_HMI_RunWriteSingleLongWordSend(unsigned int addr, long Value);
extern void RegisterSendingPacket(unsigned char state, unsigned int addr, unsigned char *data, unsigned char size);

extern unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];
extern unsigned char UART1TxBuffer[UART1_BUFFER_SIZE];
extern _SENDING_DATA SendingData;

#define IO_PAGE_ID 0x3F09
#define IO_CURSOR_X_ADDR 0x3F21
#define IO_CURSOR_Y_ADDR 0x3F22
#define IO_CURSOR_W_ADDR 0x3F23
#define IO_CURSOR_H_ADDR 0x3F24
#define IO_CURSOR_C_ADDR 0x3F25
#define IO_CURSOR_P_ADDR 0x3F26
#define IO_DG_POS_XY 0x3F2E
#define IO_DG_POS_X 0x3F2E
#define IO_DG_POS_Y 0x3F2F
#define IO_DG_SELECT 0x3F31


void OpenDialog(unsigned int DialogNumber)
{
    unsigned char size, state, data[10];
    unsigned int addr;
    
    state = UC_HMI_WRITE_BYTE;
    addr = IO_DG_SELECT;
    data[0] = DialogNumber;
    size = 1;
    RegisterSendingPacket(state, addr, data, size);
}

void CloseDialog(void)
{
    unsigned char size, state, data[10];
    unsigned int addr;

    state = UC_HMI_WRITE_BYTE;
    addr = IO_DG_SELECT;
    data[0] = 0xFF;
    size = 1;   
    RegisterSendingPacket(state, addr, data, size);
}

void uC_HMI_SetPage(unsigned int page)
{
    uC_HMI_RunWriteSingleLongWordSend(IO_PAGE_ID, page);
}

void SetSelectItemFontColor(char id)
{
    switch(id)
    {
        case 1 :case 17 :case 25 :case 43 :case 44 :case 53 :case 55 :case 57 :case 70 :case 72 :case 76:case -3 :case -13 :case -23 :case -41 :
            uC_HMI_RunWriteSingleLongWordSend(581, -65536);
            break;
        case 2 :case 18 :case 26 :case 45 :case 54 :case 56 :case 58 :case 71 :case 73 :case 77:case -4 :case -14 :case -24 :case -42 :
            uC_HMI_RunWriteSingleLongWordSend(582, -65536);
            break;
        case 3 :case 19 :case 27 :case 46 :case 59 :case 74:case 78:case -5 :case -15 :case -25 :case -43 :
            uC_HMI_RunWriteSingleLongWordSend(583, -65536);
            break;
        case 4 :case 20 :case 28 :case 47 :case 60 :case 75:case 79:case -6 :case -16 :case -26 :case -44 :
            uC_HMI_RunWriteSingleLongWordSend(584, -65536);
            break;
        case 5 :case 21 :case 29 :case 48 :case 61 :case 80:case -7 :case -17 :case -27 :case -45 :
            uC_HMI_RunWriteSingleLongWordSend(585, -65536);
            break;
        case 6 :case 22 :case 30 :case 49 :case 62 :case 81:case -8 :case -18 :case -28 :case -46 :
            uC_HMI_RunWriteSingleLongWordSend(586, -65536);
            break;
        case 7 :case 23 :case 31 :case 50 :case 63 :case -9 :case -19 :case -29 :case -47 :
            uC_HMI_RunWriteSingleLongWordSend(587, -65536);
            break;
        case 8 :case 24 :case 32 :case 51 :case 64 :case -10 :case -20 :case -30 :case -48 :
            uC_HMI_RunWriteSingleLongWordSend(588, -65536);
            break;
        case 9 :case 33 :case 52 :case 65 :case -11 :case -21 :case -31 :case -49 :
            uC_HMI_RunWriteSingleLongWordSend(589, -65536);
            break;
        case 10 :case 34 :case 66 :case -12 :case -22 :case -32 :case -50 :
            uC_HMI_RunWriteSingleLongWordSend(590, -65536);
            break;
        case 11 :case 35 :case 67 :case -33 :
            uC_HMI_RunWriteSingleLongWordSend(591, -65536);
            break;
        case 12 :case 36 :case 68 :case -34 :
            uC_HMI_RunWriteSingleLongWordSend(592, -65536);
            break;
        case 13 :case 37 :case 69 :case -35 :
            uC_HMI_RunWriteSingleLongWordSend(593, -65536);
            break;
        case 14 :case 38 :case -36 :
            uC_HMI_RunWriteSingleLongWordSend(594, -65536);
            break;
        case 15 :case 39 :case -37 :
            uC_HMI_RunWriteSingleLongWordSend(595, -65536);
            break; 
        case 16 : case 40 :case -38 :
            uC_HMI_RunWriteSingleLongWordSend(596, -65536);
            break;
        case 41 :case -39 :
            uC_HMI_RunWriteSingleLongWordSend(597, -65536);
            break;
        case 42 :case -40 :
            uC_HMI_RunWriteSingleLongWordSend(598, -65536);
            break;
/*            
        case 42 :
            uC_HMI_RunWriteSingleLongWordSend(599, -65536);
            break;
        case 43 :
            uC_HMI_RunWriteSingleLongWordSend(600, -65536);
            break;
        case 44 :
            uC_HMI_RunWriteSingleLongWordSend(601, -65536);
            break;
        case 45 :
            uC_HMI_RunWriteSingleLongWordSend(602, -65536);
            break;
 */
    }
}


