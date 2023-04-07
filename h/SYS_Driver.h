/* 
 * File:   SYS_Driver.h
 * Author: Administrator
 *
 * Created on 2014年12月16日, 下午 1:15
 */

#ifndef SYS_DRIVER_H
#define	SYS_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

//system clock define   UART I2C SPI used
#define SYSOSC  60000000 //60MHz

#define INIT_TIMER_INTERRUPT_PERIOD_1MS    0
#define INIT_TIMER_INTERRUPT_PERIOD_5MS    1
#define INIT_TIMER_INTERRUPT_PERIOD_10MS   2
#define INIT_TIMER_INTERRUPT_PERIOD_50MS   3
#define INIT_TIMER_INTERRUPT_PERIOD_100MS  4
#define INIT_TIMER_INTERRUPT_PERIOD_200MS  5
#define EXT_INPUT_COUNTER_MODE 0xFF


//************************************************************************
//void INIT_OSC(void);
//Initial System clock=60MHz
//************************************************************************
void INIT_OSC(void);

//************************************************************************
//void delay_ms(unsigned int ms);
//stop program until delay time counter finish
//unsigned int ms   setting delay time  unit ms  range 0~65536  0~65.536 S
//************************************************************************
void delay_ms(unsigned int ms);

//************************************************************************
//void delay_ns(unsigned int ns);
//stop program until delay time counter finish
//unsigned int ns   setting delay time  unit ns  range 0~65536  0~65.536 mS
//************************************************************************
void delay_ns(unsigned int ns);

//************************************************************************
//void INIT_TIMER1(unsigned char isr_period);
//Initial timer1 interrupt period
//unsigned char isr_period     setting interrupt period
//example : isr_period = INIT_TIMER_INTERRUPT_PERIOD_100MS  //setting 100ms happend interrupt once
//************************************************************************
void INIT_TIMER1(unsigned char isr_period);  //Timer1 interrupt cycle

//************************************************************************
//void enable_timer1(void);
//Enable timer1 counter and clear counter
//************************************************************************
void enable_timer1(void);

//************************************************************************
//void enable_timer1(void);
//Disable timer1 counter and clear counter
//************************************************************************
void disable_timer1(void);

//************************************************************************
//void clear_memory(unsigned char *buf,unsigned char lenth);
//Clear data memory
//unsigned char *buf      memory start address
//unsigned char lenth     clear memory lenth   range : 0~255 bytes
//************************************************************************
void clear_memory(unsigned char *buf,unsigned char lenth);




void INIT_TIMER2(unsigned char isr_period);
void enable_timer2(void);
void INIT_TIMER3(unsigned char isr_period);
void enable_timer3(void);
//Philip 20190222 02 =========================================
void INIT_TIMER4(unsigned char isr_period);
void enable_timer4(void);
//Philip 20190222 02 =========================================
#ifdef	__cplusplus
}
#endif

#endif	/* SYS_DRIVER_H */

