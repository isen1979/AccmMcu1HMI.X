/* 
 * File:   UART_Driver.h
 * Author: Administrator
 *
 * Created on 2015年1月19日, 下午 6:08
 */

#ifndef UART_DRIVER_H
#define	UART_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

//baud rate define
#if SYSOSC==60000000
#define BAUD_4800   780
#define BAUD_9600   390
#define BAUD_19200  194
#define BAUD_38400   97
#define BAUD_115200  32
#endif


#if SYSOSC==30000000
#define BAUD_4800  1561
#define BAUD_9600   780
#define BAUD_19200  390
#define BAUD_38400  194
#define BAUD_115200  65
#endif

#define NO_PARITY_9BIT   0x0006
#define ODD_PARITY_8BIT  0x0004
#define EVEN_PARITY_8BIT 0x0002
#define NO_PARITY_8BIT   0x0000
#define STOP_2BIT        0x0001
#define STOP_1BIT        0x0000


#define DE_ENABLE        1
#define DE_DISABLE       0
#define UART1_DE _RK15
#define UART2_DE _RK13
#define UART3_DE _RK14

void INIT_UART1(unsigned int baud_rate,unsigned int parity,unsigned int stopbit);    
//Example
//INIT_UART1(BAUD_9600,NO_PARITY_8BIT,STOP_1BIT,2); //9600,8,N,1 used rx interrupt

//************************************************************************
//Initial UART2 (RS232 / RS485 / RS422)
//unsigned int baud_rate    setting UART baud rate  range : BAUD_4800  BAUD_9600  BAUD_19200  BAUD_38400  BAUD_115200
//unsigned int parity       setting UART parity mode   range : NO_PARITY_9BIT / ODD_PARITY_8BIT / EVEN_PARITY_8BIT / NO_PARITY_8BIT
//unsigned int stopbit      setting UART stop bit mode  range : STOP_2BIT / STOP_1BIT
//unsigned char txrx_isr_en setting UART TX/RX Enable or Disable  range : 0(TX RX disable) / 1(TX enable  RX disable) / 2(TX disable  RX enable)  3(TX RX enable)
//************************************************************************
void INIT_UART2(unsigned int baud_rate,unsigned int parity,unsigned int stopbit,unsigned char txrx_isr_en);

//************************************************************************
//Initial UART3 (RS232 / RS485 / RS422)
//unsigned int baud_rate    setting UART baud rate  range : BAUD_4800  BAUD_9600  BAUD_19200  BAUD_38400  BAUD_115200
//unsigned int parity       setting UART parity mode   range : NO_PARITY_9BIT / ODD_PARITY_8BIT / EVEN_PARITY_8BIT / NO_PARITY_8BIT
//unsigned int stopbit      setting UART stop bit mode  range : STOP_2BIT / STOP_1BIT
//unsigned char txrx_isr_en setting UART TX/RX Enable or Disable  range : 0(TX RX disable) 1(TX enable  RX disable) 2(TX disable  RX enable)  3(TX RX enable)
//************************************************************************
void INIT_UART3(unsigned int baud_rate,unsigned int parity,unsigned int stopbit,unsigned char txrx_isr_en);

//************************************************************************
//void uart2_tx(unsigned char txdata); uart2 transmit one byte data  (not interrupt)
//unsigned char txdata  transmit data  range : 0~0xff
//************************************************************************
void uart2_tx(unsigned char txdata);

//************************************************************************
//unsigned char uart2_rx(void); uart2 receive one byte data (not interrupt)
//return receive data range : 0~0xff
//************************************************************************
unsigned char uart2_rx(void);

//************************************************************************
//void uart3_tx(unsigned char txdata); uart3 transmit one byte data
//unsigned char txdata  transmit data  range : 0~0xff
//************************************************************************
void uart3_tx(unsigned char txdata);

//************************************************************************
//unsigned char uart3_rx(void); uart3 receive one byte data (not interrupt)
//return receive data range : 0~0xff
//************************************************************************
unsigned char uart3_rx(void);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_DRIVER_H */

