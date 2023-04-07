#include "..\h\Global_define.h"
#include "..\h\UART_Driver.h"
//#include "..\h\LCD_driver.h"
#include "..\h\HMI_Control.h"
#include "..\h\SystemControl.h"

unsigned char DEC2BCD(unsigned char dec)
{
    return ( (dec/10*16) + (dec%10) );
}

unsigned char BCD2DEC(unsigned char bcd)
{
    return ( (bcd/16*10) + (bcd%16) );
}






