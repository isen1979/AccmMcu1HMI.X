#include "..\h\Global_define.h"
#include "..\h\SYS_Driver.h"
#include "..\h\SystemControl.h"

// System OSC
#define SYS_CLK_60MHZ  65
#define SYS_CLK_30MHZ  33

//extern unsigned char ServoBoardResponseBufCount1, ServoBoardResponseBufCount2, ServoBoardResponseFlag;
//extern unsigned char ServoBoardResponseTimeOutCount1, ServoBoardResponseTimeOutFlag1;


extern void UARTRXTimeOutCheck(void);
extern void DelayTimer(void);
extern void ServoMotorPulseCalculate(void);

void INIT_OSC(void)
{
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    //FCY = FOSC / (2 * DOZE)   DOZE=1  //machine cycle
    //FOSC = (Fin * M) / (N1 * N2)      //system clock
    PLLFBD=SYS_CLK_60MHZ;//60MHz ; // M=65    //(7.37MHz*PLLFBD)/(N1*N2) = 7.37*65/4 = 119.7625 MHz
    CLKDIVbits.PLLPOST=0; // N2=2*(CLKDIVbits.PLLPOST+1) =2
    CLKDIVbits.PLLPRE=0; // N1=2^CLKDIVbits.PLLPRE       =2
    CLKDIVbits.DOZE=0;
    //OSCTUN = 0;
    // Initiate Clock Switch to FRC oscillator with PLL (NOSC=0b001)
    __builtin_write_OSCCONH(0x01);//0x03?
    __builtin_write_OSCCONL(0x01);  ///0x01 20140529
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC!= 0b001);
    // Wait for PLL to lock
    while (OSCCONbits.LOCK!= 1);
    __builtin_write_OSCCONL(0x02);
    RCONbits.SWDTEN=0; // Disable Watch Dog Timer
}


//delay 10ms
void delay_ms(unsigned int ms)
{
    unsigned int cnt1=0,cnt2=0;
    for(cnt2=0;cnt2<ms;cnt2++)
    {
        for(cnt1=0;cnt1<7600;cnt1++);//1 machine cycle 33nS  
    }
}
void delay_ns(unsigned int ns)
{
    unsigned int cnt1=0;
    ns=ns/32;
    for(cnt1=0;cnt1<ns;cnt1++);//1 machine cycle 33nS  
  //  for(cnt1=0;cnt1<ns;cnt1++);
}


void INIT_TIMER1(unsigned char isr_period)  //Timer1 interrupt
{
 //   _TRISE1=0;
 //   _TRISE0=0;
//    _ANSE1=0;
//    _ANSE0=0;
    T1CON=0;//disable timer 1
    TMR1=0;//clear T1 counter
    switch(isr_period)
    {
        case INIT_TIMER_INTERRUPT_PERIOD_1MS:        
            T1CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR1=234; //Load the period value  234&4.27us=1ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_5MS:        
            T1CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR1=1172; //Load the period value  1172&4.27us=5ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_10MS:        
            T1CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR1=2343; //Load the period value  2343&4.27us=10ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_50MS:        
            T1CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR1=11719; //Load the period value  11719&4.27us=50ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_100MS:        
            T1CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR1=23438; //Load the period value  23438&4.27us=100ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_200MS:        
            T1CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR1=46875; //Load the period value  46875&4.27us=200ms
        break;
    }
    IPC0bits.T1IP = 0x03; // Set Timer1 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer` Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt

    //Initial All of flags processing in the timer1.

}

void enable_timer1(void)
{
    TMR1=0;
    T1CON |=0x8000;
}
void disable_timer1(void)
{
    TMR1=0;
    T1CON&=~(0x8000);
}


extern unsigned char OneMiliSecFlag;
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    //system timer 1ms
    IFS0bits.T1IF = 0; // Clear Timer8 Interrupt Flag  
    
    OneMiliSecFlag = 1;
    DelayTimer(); 
    UARTRXTimeOutCheck();
}

void INIT_TIMER3(unsigned char isr_period)  //Timer2 interrupt
{
 //   _TRISE1=0;
 //   _TRISE0=0;
//    _ANSE1=0;
//    _ANSE0=0;
    T3CON=0;//disable timer3
    TMR3=0;//clear T3 counter
    switch(isr_period)
    {
        case INIT_TIMER_INTERRUPT_PERIOD_1MS:        
            T3CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR3=234; //Load the period value  234&4.27us=1ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_5MS:        
            T3CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR3=1172; //Load the period value  1172&4.27us=5ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_10MS:        
            T3CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR3=2343; //Load the period value  2343&4.27us=10ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_50MS:        
            T3CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR3=11719; //Load the period value  11719&4.27us=50ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_100MS:        
            T3CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR3=23438; //Load the period value  23438&4.27us=100ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_200MS:        
            T3CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR3=46875; //Load the period value  46875&4.27us=200ms
        break;
        case EXT_INPUT_COUNTER_MODE :
            T3CON = 0x0002;//External Clock from T3CK Pin
            PR3 = 65535;
            RPINR3 |= (RP80 << 8);//PWML or RE0
            break;
    }
    IPC2bits.T3IP = 0x02; // Set Timer2 Interrupt Priority Level
    IFS0bits.T3IF = 0; // Clear Timer2 Interrupt Flag
    IEC0bits.T3IE = 1; // Enable Timer2 interrupt
}

void enable_timer3(void)
{
    TMR3=0;
    T3CON |=0x8000;
}
void disable_timer3(void)
{
    TMR3=0;
    T3CON&=~(0x8000);
}


void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)
{
    IFS0bits.T3IF = 0; // Clear Timer8 Interrupt Flag
}

void INIT_TIMER5(unsigned char isr_period)  //Timer5 interrupt
{
    T5CON=0;//disable timer4
    TMR5=0;//clear T4 counter
    
    switch(isr_period)
    {
        case INIT_TIMER_INTERRUPT_PERIOD_1MS:        
            T5CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR5=234; //Load the period value  234&4.27us=1ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_5MS:        
            T5CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR5=1172; //Load the period value  1172&4.27us=5ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_10MS:        
            T5CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR5=2343; //Load the period value  2343&4.27us=10ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_50MS:        
            T5CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR5=11719; //Load the period value  11719&4.27us=50ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_100MS:        
            T5CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR5=23438; //Load the period value  23438&4.27us=100ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_200MS:        
            T5CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR5=46838; //Load the period value  46875&4.27us=200ms
        break;
        case EXT_INPUT_COUNTER_MODE :
            T5CON = 0x0002;//External Clock from T5CK Pin
            PR5 = 65535;            
            //RPINR4 |= RPI81;
            RPINR4 |= (RPI81 << 8);//PWMH1 or RE1
            break;
    }
    IPC7bits.T5IP = 0x02; // Set Timer4 Interrupt Priority Level
    IFS1bits.T5IF = 0; // Clear Timer4 Interrupt Flag
    IEC1bits.T5IE = 1; // Enable Timer4 interrupt
}

void enable_timer5(void)
{
    TMR5=0;
    T5CON |=0x8000;
}
void disable_timer5(void)
{
    TMR5=0;
    T5CON&=~(0x8000);
}


void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void)
{
    IFS1bits.T5IF = 0; // Clear Timer4 Interrupt Flag
}

//API
void clear_memory(unsigned char *buf,unsigned char lenth)
{
    unsigned char lenth_1=0;
    for(lenth_1=0;lenth_1<lenth;lenth_1++)
    *buf++=0;
}

void INIT_TIMER7(unsigned char isr_period)  //Timer2 interrupt
{
 //   _TRISE1=0;
 //   _TRISE0=0;
//    _ANSE1=0;
//    _ANSE0=0;
    T7CON=0;//disable timer2
    TMR7=0;//clear T2 counter
    switch(isr_period)
    {
        case INIT_TIMER_INTERRUPT_PERIOD_1MS:        
            T7CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR7=234; //Load the period value  234&4.27us=1ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_5MS:        
            T7CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR7=1172; //Load the period value  1172&4.27us=5ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_10MS:        
            T7CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR7=2343; //Load the period value  2343&4.27us=10ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_50MS:        
            T7CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR7=11719; //Load the period value  11719&4.27us=50ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_100MS:        
            T7CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR7=23438; //Load the period value  23438&4.27us=100ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_200MS:        
            T7CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR7=46875; //Load the period value  46875&4.27us=200ms
        break;
        case EXT_INPUT_COUNTER_MODE :
            T7CON = 0x0002;//External Clock from T2CK Pin
            PR7 = 65535;
            RPINR5 |= (RP82 << 8);//PWML or RE2
            break;
    }
    IPC12bits.T7IP = 0x02; // Set Timer2 Interrupt Priority Level
    IFS3bits.T7IF = 0; // Clear Timer2 Interrupt Flag
    IEC3bits.T7IE = 1; // Enable Timer2 interrupt
}

void enable_timer7(void)
{
    TMR7=0;
    T7CON |=0x8000;
}
void disable_timer7(void)
{
    TMR7=0;
    T7CON&=~(0x8000);
}


void __attribute__((interrupt, no_auto_psv)) _T7Interrupt(void)
{
    IFS3bits.T7IF = 0; // Clear Timer8 Interrupt Flag
}

void INIT_TIMER9(unsigned char isr_period)  //Timer4 interrupt
{
    T9CON=0;//disable timer4
    TMR9=0;//clear T4 counter
    
    switch(isr_period)
    {
        case INIT_TIMER_INTERRUPT_PERIOD_1MS:        
            T9CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR9=234; //Load the period value  234&4.27us=1ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_5MS:        
            T9CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR9=1172; //Load the period value  1172&4.27us=5ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_10MS:        
            T9CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR9=2343; //Load the period value  2343&4.27us=10ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_50MS:        
            T9CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR9=11719; //Load the period value  11719&4.27us=50ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_100MS:        
            T9CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR9=23438; //Load the period value  23438&4.27us=100ms
        break;
        case INIT_TIMER_INTERRUPT_PERIOD_200MS:        
            T9CON=0x0030; // 256/60M= 4.27us    clock=60MHZ/256=234KHz
            PR9=46838; //Load the period value  46875&4.27us=200ms
        break;
        case EXT_INPUT_COUNTER_MODE :
            T9CON = 0x0002;//External Clock from T4CK Pin
            PR9 = 65535;
            RPINR6 |= (RPI83 << 8);//PWML or RE3
            break;
    }
    IPC13bits.T9IP = 0x02; // Set Timer4 Interrupt Priority Level
    IFS3bits.T9IF = 0; // Clear Timer4 Interrupt Flag
    IEC3bits.T9IE = 1; // Enable Timer4 interrupt
}

void enable_timer9(void)
{
    TMR9=0;
    T9CON |=0x8000;
}
void disable_timer9(void)
{
    TMR9=0;
    T9CON&=~(0x8000);
}


void __attribute__((interrupt, no_auto_psv)) _T9Interrupt(void)
{
    IFS3bits.T9IF = 0; // Clear Timer4 Interrupt Flag
}



