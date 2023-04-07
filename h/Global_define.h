#include <p33EP512MU814.h>
//#include <string.h>
//#include <stdio.h>



//IO FUNCTION SELECT
#define RPI17  0x11
#define RPI22  0x16 //QEI2 INDEX
#define RPI23  0x17 //QEI1 ONDEX
#define RPI44  0x2c
#define RPI49  0x31
#define RPI50  0x32
#define RPI51  0x33
#define RPI52  0x34
#define RP64   0x40
#define RP65   0x41
#define RP66   0x42
#define RP67   0x43
#define RP68   0x44
#define RP69   0x45
#define RP70   0x46
#define RP71   0x47
#define RPI72  0x48 
#define RPI73  0x49
#define RPI74  0x4a
#define RPI75  0x4b
#define RPI76  0x4c  //servo alm1
#define RPI77  0x4d  //servo alm1
#define RPI78  0x4e
#define RP79   0x4f
#define RP80   0x50 //PWM1L
#define RPI81  0x51	//PWM1H
#define RP82   0x52 //PWM2L
#define RPI83  0x53	//PWM2H
#define RP84   0x54
#define RP85   0x55
#define RPI86  0x56
#define RP87   0x57
#define RP96   0x60 //QEI2 compare output
#define RP97   0x61 //QEI1 compare output
#define RP98   0x62	//spi1 CLK
#define RP99   0x63	//spi1 DI
#define RP104  0x68	//spi1 DO
#define RP112  0x70 //QEI1 HOME
#define RP113  0x71 //QEI2 HOME
#define RPI124 0x7c //QEI1 A
#define RP125  0x7d //QEI2 A
#define RP126  0x7e //QEI1 B
#define RP127  0x7f //QEI2 B


//OUTPUT PIN SELECT SETTING
#define UART1TX  0x01
#define UART2TX  0X03
#define UART3TX  0X1b

#define SPIDO1   0X05  
#define SPICK1   0X06  



//BRGH=0 (Fcy/(16*BaudRate))-1
//BRGH=1 (Fcy/(4*BaudRate))-1
//if sysclock=60MIPS















//PANEL Control
#define PANEL_RST  _RA9 
#define PANEL_SD   _RA10

//BZ & FAN Control
#define BZ1_5V		_RB1   //BZ1
#define BZ2_24V		_RB0   //BZ2
#define FAN_CTRL    _RB2
#define FAN_DET     _RB3
#define BZON    1
#define BZOFF   0
#define FANON   1
#define FANOFF  0
//MACRO
#define MACRO_BZ1_INIT     _TRISB1=0; _ANSB1=0; BZ1_5V=0 
#define MACRO_BZ2_INIT	   _TRISB0=0; _ANSB0=0; BZ2_24V=0
#define MACRO_FAN_INIT     _TRISB2=0; _ANSB2=0; FAN_CTRL=0; _TRISB3=1; _ANSB3=0; FAN_DET=1  
#define MACRO_BZ1_ON       BZ1_5V=BZON       
#define MACRO_BZ1_OFF      BZ1_5V=BZOFF 
#define MACRO_BZ2_ON       BZ2_24V=BZON
#define MACRO_BZ2_OFF      BZ2_24V=BZOFF
#define MACRO_FAN_ON       FAN_CTRL=FANON         
#define MACRO_FAN_OFF      FAN_CTRL=FANOFF

//RTC
#define RTC_R1_SET_12H       0x00//                         0     0    0   0    0    0   0   0   
#define RTC_R1_SET_24H       0x40//                         0     1    0   0    0    0   0   0
#define RTC_R1_SET_INIT      0x80//                         1     0    0   0    0    0   0   0 
                                 //R2 RTC register2 INT1FE INT1ME INT1AE 32kE INT2FE INT2ME INT2AE TEST
#define RTC_R2_INIT          0x00//                           0      0     0     0      0      0     0 

struct RTC_DATA
{
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char week;
	unsigned char hour;
	unsigned char minute;
	unsigned char sec;
};
extern struct RTC_DATA SYS_TIME;

//I2C Slave ID
#define EEPROM_ID  0xA0
#define RTC_R1_ID 0x60
#define RTC_R2_ID 0x62
#define RTC_DATA_ID 0x64  //All data year momth day week hour min sec 
#define RTC_DATA2_ID  0x66  //hour min sec

//SPI SLAVE DEVICE DEFINE
#define EXTIO_W  0x40
#define EXTIO_R  0x41
//EXT IO reg adderss (bank=0)
#define EXTIO_DIRA   0x00
#define EXTIO_DIRB   0x01
#define EXTIO_IPOLA  0x02 //INPUT POL SELECT
#define EXTIO_IPOLB  0x03
#define EXTIO_IOCON  0x0A
#define EXTIO_GPPUA  0x0C   //INPUT PULL HIGH ENABLE/DISABLE
#define EXTIO_GPPUB  0x0D
#define EXTIO_GPIOA  0x12   //GPIO STATUS
#define EXTIO_GPIOB  0x13
#define EXTIO_OLATA  0x14   //OUTPUT LATCH
#define EXTIO_OLATB  0x15
#define EXTIO_I_CS   _RB13
#define EXTIO_O_CS   _RB14
#define SPI_CS_DIS     1
#define SPI_CS_EN     0





void INIT_I2C(void);
void i2c_wr(unsigned char id , unsigned int addr ,unsigned char *data,unsigned int nbyte,unsigned char addr_type);
//void i2c_rtc_set(unsigned char id ,unsigned char *data,unsigned int nbyte);
unsigned char msb_lsb_change(unsigned char data);
void INIT_EXT_RTC(void);
void INIT_INT_RTC(unsigned int year, unsigned int m_d,unsigned int w_h ,unsigned int m_s);
void UPDATE_SYS_TIME(void);
void INIT_SPI1(void);




void INIT_EXT_IO(void);
void EXTIO_SET_OUTPUT(unsigned int ioset);
unsigned int EXTIO_GET_INPUT(void);
unsigned int spi1_txrx16(unsigned int tx_data);
unsigned char spi1_txrx(unsigned char tx_data);

