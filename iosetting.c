#include "..\h\Global_define.h"


//Input Port Setting
//input 0~7  = RD0~7 ( input 0~7 can be capture input 1~8 ) ( input 0~4 can be external interrupt input 0~4)
//input 8~15 = RH8~15
#define I0  _RD0
#define I1  _RD1
#define I2  _RD2
#define I3  _RD3
#define I4  _RD4
#define I5  _RD5
#define I6  _RD6
#define I7  _RD7
#define I8  _RH8
#define I9  _RH9
#define I10 _RH10
#define I11 _RH11
#define I12 _RH12
#define I13 _RH13
#define I14 _RH14
#define I15 _RH15

//Output 0~7 = RH0~7  
//Output 8~15 = RJ8~15

#define O0  _RH0 
#define O1  _RH1
#define O2  _RH2
#define O3  _RH3
#define O4  _RH4
#define O5  _RH5
#define O6  _RH6
#define O7  _RH7
#define O8  _RJ8
#define O9  _RJ9
#define O10 _RJ10
#define O11 _RJ11
#define O12 _RJ12
#define O13 _RJ13
#define O14 _RJ14
#define O15 _RJ15



#define ENABLE 1
#define DISABLE 0
#define USE_CAPTURE DISABLE
#define USE_EXT_INTERRUPT DISABLE
#if USE_CAPTURE 
	#define IC1_EN DISABLE //ENABLE 
	#define IC2_EN DISABLE //ENABLE
	#define IC3_EN DISABLE //ENABLE 
	#define IC4_EN DISABLE //ENABLE
	#define IC5_EN DISABLE //ENABLE
	#define IC6_EN DISABLE //ENABLE
	#define IC7_EN DISABLE //ENABLE
	#define IC8_EN DISABLE //ENABLE
#endif

#if USE_EXT_INTERRUPT
	#define INT0_EN DISABLE //ENABLE
	#define INT1_EN DISABLE //ENABLE
	#define INT2_EN DISABLE //ENABLE
	#define INT3_EN DISABLE //ENABLE 
	#define INT4_EN DISABLE //ENABLE
	#define INT_FULL_EDGE 1
    #define INT_RISE_EDGE 0
#endif

#define SPI_MASTER      1
#define SPI_SLAVE		0
#define SPI1_MODE	SPI_MASTER

void INIT_IOPORT(void)
{
	//PORTH all are digital
	ANSELD=0x0; //set PORTD 6,7 is digital
	//PORTJ all are digital

	TRISH = 0xff00; //RH0~7 is OUTPUT 0~7  RH8~15 is INPUT 8~15
	TRISD |=0x00ff; //RD0~7 is INTPUT 0~7
	TRISJ &=0x00ff; //RJ8~15 is OUTPUT 8~15
	
	PORTH = 0xff00;  //in8~15=1 / out0~7 =0
	PORTD = 0xff00; //in 0~7=1
	PORTJ = 0x00ff; //out8~15=0 


	#if IC1_EN 
	RPINR7bits.IC1R=RP64;  //capture1 =RD0 
	IFS0bits.IC1IF = 0; // Clear the IC1 interrupt status flag
	IEC0bits.IC1IE = 1; // Enable IC1 interrupts
	IPC0bits.IC1IP = 1; // Set module interrupt priority as 1 
	IC1CON1bits.ICSIDL = 0;  // Input capture will continue to operate in CPU idle mode
	IC1CON1bits.ICTSEL = 0b011; // T5 clock source for the IC1 module
	IC1CON1bits.ICI = 1;  // Interrupt on every capture event
	IC1CON1bits.ICBNE = 0; // Input capture is empty
	IC1CON1bits.ICM = 0b001;//Capture mode every rising & falling edge (Prescaler Capture mode)
	IC1CON2bits.IC32 = 0;  // Cascade module operation is disabled
	IC1CON2bits.ICTRIG = 0; // Input source used to synchronize the input capture timer of 
	 // another module (Synchronization mode) IC1CON2bits.TRIGSTAT = 0; // IC1TMR has not been triggered and is being held clear
	IC1CON2bits.SYNCSEL = 0; // No Sync or Trigger source for the IC1 module
	#endif

	#if IC2_EN 
	RPINR7bits.IC2R=RP65;  //capture2 =RD1	
	#endif

	#if IC3_EN 
	RPINR8bits.IC3R=RP66;  //capture3 =RD2
	
	#endif

	#if IC4_EN 
	RPINR8bits.IC4R=RP67;  //capture4 =RD3
	
	#endif

	#if IC5_EN 
	RPINR9bits.IC5R=RP68;  //capture5 =RD4

	#endif

	#if IC6_EN 
	RPINR9bits.IC6R=RP69;  //capture6 =RD5

	#endif

	#if IC7_EN 
	RPINR10bits.IC7R=RP70;  //capture7 =RD6

	#endif

	#if IC8_EN 
	RPINR10bits.IC8R=RP71;  //capture8 =RD7	
	#endif

	
	#if	INT0_EN
	IFS0bits.INT0IF = 0;    /*Reset INT0 interrupt flag */
	IEC0bits.INT0IE = 1;    /*Enable INT0 Interrupt Service Routine */
	INTCON2bits.INT0EP=INT_FULL_EDGE;  //INT_RISE_EDGE
	#endif
	
	#if	INT1_EN
	RPINR0bits.INT1R=RP65; //setting INT1=RD1	
	IFS1bits.INT1IF = 0;    /*Reset INT1 interrupt flag */
	IEC1bits.INT1IE = 1;    /*Enable INT1 Interrupt Service Routine */
	INTCON2bits.INT1EP=INT_FULL_EDGE;  //INT_RISE_EDGE
	#endif
	
	#if	INT2_EN
	RPINR1bits.INT2R=RP66; //setting INT2=RD2	
	IFS1bits.INT2IF = 0;    /*Reset INT0 interrupt flag */
    IEC1bits.INT2IE = 1;    /*Enable INT0 Interrupt Service Routine */
	INTCON2bits.INT2EP=INT_FULL_EDGE;  //INT_RISE_EDGE
	#endif

	#if	INT3_EN
	RPINR1bits.INT3R=RP67; //setting INT3=RD3	
	IFS3bits.INT3IF = 0;    /*Reset INT1 interrupt flag */
    IEC3bits.INT3IE = 1;    /*Enable INT1 Interrupt Service Routine */	
	INTCON2bits.INT3EP=INT_FULL_EDGE;  //INT_RISE_EDGE
	#endif

	#if	INT4_EN
	RPINR2bits.INT4R=RP68; //setting INT4=RD4	
	IFS3bits.INT4IF = 0;    /*Reset INT1 interrupt flag */
    IEC3bits.INT4IE = 1;    /*Enable INT1 Interrupt Service Routine */
	INTCON2bits.INT4EP=INT_FULL_EDGE;  //INT_RISE_EDGE
	#endif

}

unsigned int get_total_input_status(void)
{	
	//input 0~7  = RD0~7 
	//input 8~15 = RH8~15
	unsigned int port_value=0;
	port_value=~((PORTD&0x00ff)|(PORTH&0xff00));
	return port_value;	
} 

unsigned char get_single_input_status(unsigned char num)	
{	
	unsigned char i=0;
	switch(num)
	{
		case 0:
			i=I0;
		break;
		case 1:
			i=I1;
		break;
		case 2:
			i=I2;
		break;
		case 3:
			i=I3;
		break;
		case 4:
			i=I4;
		break;
		case 5:
			i=I5;
		break;
		case 6:
			i=I6;
		break;
		case 7:
			i=I7;
		break;
		case 8:
			i=I8;
		break;
		case 9:
			i=I9;
		break;
		case 10:
			i=I10;
		break;
		case 11:
			i=I11;
		break;
		case 12:
			i=I12;
		break;
		case 13:
			i=I13;
		break;
		case 14:
			i=I14;
		break;
		case 15:
			i=I15;
		break;
		default:
			i=1;		
		break;
	}
	return ((~i)&0x01);
}

void set_output_port(unsigned int value)
{
	//Output 0~7 = RH0~7  
	//Output 8~15 = RJ8~15	
	unsigned int temp=0;
	temp=PORTH&0xff00;
	PORTH=(value&0x00ff)|temp;
	temp=PORTJ&0x00ff;
	PORTJ=(value&0xff00)|temp;
}

void set_single_output_port(unsigned char num,unsigned char value)
{
	switch(num)
	{
		case 0:
			O0=value;		
		break;
		case 1:
			O1=value;		
		break;
		case 2:
			O2=value;		
		break;
		case 3:
			O3=value;		
		break;
		case 4:
			O4=value;		
		break;
		case 5:
			O5=value;		
		break;
		case 6:
			O6=value;		
		break;
		case 7:
			O7=value;		
		break;
		case 8:
			O8=value;		
		break;
		case 9:
			O9=value;		
		break;
		case 10:
			O10=value;		
		break;
		case 11:
			O11=value;		
		break;
		case 12:
			O12=value;		
		break;
		case 13:
			O13=value;		
		break;
		case 14:
			O14=value;		
		break;
		case 15:
			O15=value;		
		break;		
	}	
}



//Capture input ISR
#if IC1_EN 
unsigned int Capture1;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC1Interrupt(void)
{
	IFS0bits.IC1IF = 0; // Reset respective interrupt flag
	Capture1 = IC1BUF; // Read and save off first capture entry
}
#endif

#if IC2_EN 
unsigned int Capture2;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC2Interrupt(void)
{
	IFS0bits.IC2IF = 0; // Reset respective interrupt flag
	Capture2 = IC2BUF; // Read and save off first capture entry
}
#endif


#if IC3_EN 
unsigned int Capture3;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC3Interrupt(void)
{
	IFS2bits.IC3IF = 0; // Reset respective interrupt flag
	Capture3 = IC3BUF; // Read and save off first capture entry
}
#endif

#if IC4_EN 
unsigned int Capture4;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC4Interrupt(void)
{
	IFS2bits.IC4IF = 0; // Reset respective interrupt flag
	Capture4 = IC4BUF; // Read and save off first capture entry
}
#endif

#if IC5_EN 
unsigned int Capture5;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC5Interrupt(void)
{
	IFS2bits.IC5IF = 0; // Reset respective interrupt flag
	Capture5 = IC5BUF; // Read and save off first capture entry
}
#endif

#if IC6_EN 
unsigned int Capture6;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC6Interrupt(void)
{
	IFS2bits.IC6IF = 0; // Reset respective interrupt flag
	Capture6 = IC6BUF; // Read and save off first capture entry
}
#endif

#if IC7_EN 
unsigned int Capture7;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC7Interrupt(void)
{
	IFS1bits.IC7IF = 0; // Reset respective interrupt flag
	Capture7 = IC7BUF; // Read and save off first capture entry
}
#endif

#if IC8_EN 
unsigned int Capture8;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC8Interrupt(void)
{
	IFS1bits.IC8IF = 0; // Reset respective interrupt flag
	Capture8 = IC8BUF; // Read and save off first capture entry
}
#endif
//Capture input ISR END

//External Interrupt ISR 
#if	INT0_EN
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{

        IFS0bits.INT0IF = 0;    //Clear the INT0 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif

#if	INT1_EN
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)
{
        LATA=(PORTA ^ 0x20);    //Toggle RA6
        IFS1bits.INT1IF = 0;    //Clear the INT1 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif

#if	INT2_EN
void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void)
{
        LATA=(PORTA ^ 0x40);    //Toggle RA7
        IFS1bits.INT2IF = 0;    //Clear the INT2 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif

#if	INT3_EN
void __attribute__((interrupt, no_auto_psv)) _INT3Interrupt(void)
{
        LATA=(PORTA ^ 0x04);    //Toggle RA2
        IFS3bits.INT3IF = 0;    //Clear the INT3 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif

#if	INT4_EN
void __attribute__((interrupt, no_auto_psv)) _INT4Interrupt(void)
{
        LATA=(PORTA ^ 0x08);    //Toggle RA3
        IFS3bits.INT4IF = 0;    //Clear the INT4 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif
//External Interrupt ISR END




//pwm setting
//#define F500K 0  //div 1
//#define F250K 1  //div 2
//#define F125K 2  //div 4
//#define F64K  3  //div 8

//delay 10ms
void delay_ms(unsigned int ms)
{
    unsigned int cnt1=0,cnt2=0;
    for(cnt2=0;cnt2<ms;cnt2++)
    {
        for(cnt1=0;cnt1<7600;cnt1++);//1 machine cycle 33nS  4cycle=132ns*7600=1mS
    }
}
void delay_ns(unsigned int ns)
{
    unsigned int cnt1=0;
    ns=ns/32;
    for(cnt1=0;cnt1<ns;cnt1++);//1 machine cycle 33nS  4cycle=132ns*7600=1mS
  //  for(cnt1=0;cnt1<ns;cnt1++);
}


unsigned char axis_x_status=0,axis_y_status=0;
unsigned int x_add_arry[11];
unsigned int x_dec_arry[11];
unsigned int y_add_arry[11];
unsigned int y_dec_arry[11];

//type pulse dir : 1 / a/b phase : 2  
#define PULSE_DIR  1
#define CW_CCW   0
#define AB_PHASE    2
void INIT_PWMX(unsigned char fail_en,unsigned char dead_time,unsigned char type)
{
    PTCON = 0x0000 ; //PWM disable
    PWMCON1=0;
 //   PTPER= 240;   //cnt=1 is 1/system clock*2 s  if 60MIPS    = 1/120M s
    //check alarm is happened ?
    if(1)//(SERVO_ALMX==SERVO_NO_ALM)
    {
     //   delay_ms(10);
        //setting servo on & servo clear
        _TRISJ11=0; //RJ11 is SERVO_ONX for output
        _TRISJ3=0;  //RJ3 is SERVO_CLRX for output
        SERVO_ONX=SERVO_ON;  //RJ11  set servo on
        SERVO_CLRX=SERVO_CLR_OFF; //RJ3 set servo clr off
        //------------------------------------
        #if PWM_FAIL_IN == PWM_CTRL
        if(fail_en==1)
        {
                RPINR12bits.FLT1R=SERVO_ALMX;// PWM1_Fail in RPI77
                FCLCON1 = 0x0001;     //FCLCON1 bit1~0 fail input    11 Disable
                                                   //01 enable PWM H,L=FLTDAT(unlock)
                                                  // 00 enablt PWM H,L=FLTDAT(lock)
                                                 //     bit2 pwm fail signal input    0 input H is fail    1 input L is pail
                PWMCON1bits.FLTIEN=1; //fail input interrupt enable
                PWMCON1bits.FLTSTAT=0; //clear fail interrupt flag
                IFS5bits.PWM1IF=0;     //clear pwm1 interrupt flag
        }
        else
        {
                FCLCON1 = 0x0003; //fail input disable
                PWMCON1bits.FLTIEN=0; //fail input interrupt disable
        }
        #endif
        #if PWM_FAIL_IN == GPIO_CTRL
        if(fail_en==1)
        {
                _TRISD13=1;  //set rd13 is input
                SERVO_ALMX=1;
        }
        #endif
        //dead time input
        if(dead_time>0 && type!=AB_PHASE)
        {
                RPINR38bits.DTCMP1R=0;//PWM1 DTCMP1R=GND
                DTR1 = dead_time;   //PWMH Dead Time Values
                ALTDTR1 = dead_time;  //PWML Dead Time Values
                PWMCON1bits.DTC=0b11; //Dead enable
                PWMCON1bits.DTCP=0;//  1: PWMH>PWML     0:PWMH<PWML
        }
        else
        {
                DTR1=ALTDTR1=0;
                PWMCON1bits.DTC=0b10; //Dead disable
        }
        // Set PWM Mode to Independent //
        //ifIOCON1 bit[9:8] can stop PWMH/PWML output,bit[7:6] setting
        if(type == AB_PHASE)
            IOCON1 = 0xcf00; //pwm ctrl PWML&PWMH   //pwmH/L=LOW
        else
            IOCON1 = 0xc300;//pwmH/L=LOW
        
        PWMCON1bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
        PWMCON1bits.MTBS = 0; //pwm clk = PTPER
        //SETTING TIMER TO COUNTER PWM PULSE

        //change to pwmx-action setting
        //RPINR5bits.T6CKR=RPI81;  //set T6CK pin as PWM1H
        RPINR5bits.T7CKR=RP80; //set T7CK pin as PWM1L

        _TRISE1=1;
        _TRISE0=1;
        _ANSE1=0;
        _ANSE0=0;
         //can set timer interrupt to dection pwm pulse
#if 0
        TMR6=0;//clear T6 counter pwm1h
        PR6=0; //Load the period value
        IPC11bits.T6IP = 0x01; // Set Timer6 Interrupt Priority Level
        IFS2bits.T6IF = 0; // Clear Timer6 Interrupt Flag
        IEC2bits.T6IE = 1; // Enable Timer6 interrupt
#endif
        TMR7=0;//clear T7 counter pwm1l
        PR7=0; //Load the period value
        IPC12bits.T7IP = 0x01; // Set Timer7 Interrupt Priority Level
        IFS3bits.T7IF = 0; // Clear Timer7 Interrupt Flag
        IEC3bits.T7IE = 1; // Enable Timer7 interrupt
 //       T6CON|=0x8006;//T6 enable external clock
//        T7CON|=0x8040;//0x8002;//T7 enable external clock
        //T7CONbits.TCS=0;
        //T7CONbits.TGATE=1;
        if(type == AB_PHASE)
            PWMCON1 |= 0x0001 ; //real time update Enable
        axis_x_status=(type<<4)&0x30;
    }
}

void INIT_PWMY(unsigned char fail_en,unsigned char dead_time,unsigned char type)
{	
   // PTCON = 0x0000 ; //PWM disable
    PWMCON2=0;
    //------------------------------------
    if(1)//(SERVO_ALMY==SERVO_NO_ALM)
    {
      //   delay_ms(10);
        //STPER = 240;
        //setting servo on & servo clear
        _TRISJ0=0; //RJ0 is SERVO_ONY for output
        _TRISJ2=0;  //RJ2 is SERVO_CLRY for output
        SERVO_ONY=0;  //RJ0
        SERVO_CLRY=0; //RJ2
	#if PWM_FAIL_IN == PWM_CTRL
	if(fail_en==1)
	{
		RPINR12bits.FLT2R=SERVO_ALMY;// PWM2_Fail in RPI76
		FCLCON2 = 0x0001;     //FCLCON2 bit1~0 fail input    11 Disable      
						   //01 enable PWM H,L=FLTDAT(unlock)   
		 				  // 00 enablt PWM H,L=FLTDAT(lock) 
						 //     bit2 pwm fail signal input    0 input H is fail    1 input L is pail
		PWMCON2bits.FLTIEN=1; //fail input interrupt enable
		PWMCON2bits.FLTSTAT=0; //clear fail interrupt flag
		IFS5bits.PWM2IF=0;     //clear pwm2 interrupt flag
	}
	else
	{
		FCLCON2 = 0x0003; //fail input disable	
		PWMCON2bits.FLTIEN=0; //fail input interrupt disable
	}
	#endif
	#if PWM_FAIL_IN == GPIO_CTRL
	if(fail_en==1)
	{	
		_TRISD12=1;  //set rd12 is input
		SERVO_ALMY=1;
	}	
	#endif
	//dead time input	
	if(dead_time>0 && type!=AB_PHASE)
	{
		RPINR39bits.DTCMP2R=0;//PWM2 DTCMP1R=GND
		DTR2 = dead_time;   //PWMH Dead Time Values
		ALTDTR2 = dead_time;  //PWML Dead Time Values
		PWMCON2bits.DTC=0b11; //Dead enable
		PWMCON2bits.DTCP=0;//  1: PWMH>PWML     0:PWMH<PWML
	}
	else
	{
		DTR2=ALTDTR2=0;
		PWMCON2bits.DTC=0b10; //Dead disable
	}
	// Set PWM Mode to Independent //
    //ifIOCON1 bit[9:8] can stop PWMH/PWML output,bit[7:6] setting
	if(type == AB_PHASE)
            IOCON2 = 0xcf00; //pwm ctrl PWML&PWMH   //pwmH/L=LOW
	else
            IOCON2 = 0xc300;//pwmH/L=LOW
	PWMCON2bits.MDCS =0; //pwm provide duty define by PDC2(PWMH)  SDC2(PWML)
	PWMCON2bits.MTBS =1; //pwm clk = STPER
 	//SETTING TIMER TO COUNTER PWM PULSE

        //RPINR6bits.T8CKR=RPI83; //set T8CK pin as PWM2H
	RPINR6bits.T9CKR=RP82; //set T9CK pin as PWM2L

        _TRISE2=1;
        _TRISE3=1;
        _ANSE3=0;
        _ANSE2=0;

	 //can set timer interrupt to dection pwm pulse  
#if 0
        TMR8=0;//clear T8 counter
        PR8=0; //Load the period value
	IPC12bits.T8IP = 0x01; // Set Timer8 Interrupt Priority Level
	IFS3bits.T8IF = 0; // Clear Timer8 Interrupt Flag
	IEC3bits.T8IE = 1; // Enable Timer8 interrupt
#endif
        TMR9=0;//clear T9 counter
	PR9=0; //Load the period value
	IPC13bits.T9IP = 0x01; // Set Timer9 Interrupt Priority Level
	IFS3bits.T9IF = 0; // Clear Timer9 Interrupt Flag
	IEC3bits.T9IE = 1; // Enable Timer9 interrupt
        if(type==AB_PHASE)
            PWMCON2 |= 0x0001 ; //real time update Enable
        axis_y_status=(type<<4)&0x30;
    }
}

void PWMX_frequency(unsigned int frequency);
void PWMY_frequency(unsigned int frequency);
void PWMX_DIS(unsigned char dis_value);  //set 0 led=off  pwm=L
void PWMX_EN(void);
void PWMY_EN(void);
void PWMY_DIS(unsigned char dis_value); //set 0 led=off  pwm=L
void PWMX_dir(unsigned char dir);// dir= 0 or 1
void PWMY_dir(unsigned char dir);// dir= 0 or 1
unsigned char velocity_x_lv=0,velocity_y_lv=0;
unsigned int init_velocity=0,full_celocity=0;
//x axis value
unsigned char accelerationx=0; //?�速�?%
unsigned char decelerationx=0; //減速�?%
unsigned long add_pulsex=0,dec_pulsex=0,nor_pulsex=0;
//y axis valus
unsigned char accelerationy=0; //?�速�?%
unsigned char decelerationy=0; //減速�?%
unsigned long add_pulsey=0,dec_pulsey=0,nor_pulsey=0;

//unsigned int output_pulse=0; //輸出?�波??
#if 0
const unsigned int pwmx_freq_table[12]={PWM_FREQ_2K,PWM_FREQ_2K,PWM_FREQ_2K,
                                       PWM_FREQ_4K,PWM_FREQ_4K,PWM_FREQ_8K,
                                       PWM_FREQ_15K,PWM_FREQ_30K,PWM_FREQ_60K,
                                       PWM_FREQ_125K,PWM_FREQ_250K,PWM_FREQ_500K
                                      };
#endif
#if 0
const unsigned int pwmx_freq_table[12]={PWM_FREQ_2K,PWM_FREQ_2K,PWM_FREQ_2K,
                                       PWM_FREQ_2K,PWM_FREQ_4K,PWM_FREQ_4K,
                                       PWM_FREQ_8K,PWM_FREQ_8K,PWM_FREQ_15K,
                                       PWM_FREQ_15K,PWM_FREQ_30K,PWM_FREQ_60K
                                      };
#endif
#if 1   //pulse dir used
const unsigned int pwmx_freq_table[12]={PWM_FREQ_2K,PWM_FREQ_8K,PWM_FREQ_15K,
                                       PWM_FREQ_30K,PWM_FREQ_60K,PWM_FREQ_125K,
                                       PWM_FREQ_250K,PWM_FREQ_300K,PWM_FREQ_350K,
                                       PWM_FREQ_400K,PWM_FREQ_450K,PWM_FREQ_500K
                                      };
#endif
#if 1     // ASIX Y frequency table
const unsigned int pwmy_freq_table[12]={PWM_FREQ_2K,PWM_FREQ_4K,PWM_FREQ_4K,
                                       PWM_FREQ_8K,PWM_FREQ_15K,PWM_FREQ_15K,
                                       PWM_FREQ_30K,PWM_FREQ_60K,PWM_FREQ_125K,
                                       PWM_FREQ_200K,PWM_FREQ_250K,PWM_FREQ_300K
                                      };
#endif


#if 0
const unsigned int pwmx_freq_table[12]={PWM_FREQ_2K,PWM_FREQ_4K,PWM_FREQ_2K,
                                       PWM_FREQ_4K,PWM_FREQ_2K,PWM_FREQ_4K,
                                       PWM_FREQ_4K,PWM_FREQ_4K,PWM_FREQ_8K,
                                       PWM_FREQ_8K,PWM_FREQ_15K,PWM_FREQ_15K
                                      };
#endif

void __attribute__((interrupt, no_auto_psv)) _T6Interrupt(void)
{
    //pwm1H counter
    IFS2bits.T6IF = 0; // Clear Timer6 Interrupt Flag
	//
}

void __attribute__((interrupt, no_auto_psv)) _T7Interrupt(void)
{
    //pwm1L counter
    IFS3bits.T7IF = 0; // Clear Timer7 Interrupt Flag
    IEC3bits.T7IE = 0; // Disable Timer7 interrupt
    //velocity_x_lv=PWMX_DEC_END;
    if(T7CONbits.TGATE==0 && (axis_x_status&0x30)==0x20)
    {
        T7CONbits.TCS=0;
        T7CONbits.TGATE=1;
        PR7=1;TMR7=0;
    }
    else
    {
        T7CONbits.TCS=1;
        T7CONbits.TGATE=0;

        switch(velocity_x_lv)
        {
            case PWMX_ADD_LV2:
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV2&0x0f]);
                velocity_x_lv=PWMX_ADD_LV3;
                TMR7=0;
                PR7= x_add_arry[PWMX_ADD_LV2&0x0f];
            break;
            case PWMX_ADD_LV3:
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV3&0x0f]);
                TMR7=0;
                PR7= x_add_arry[PWMX_ADD_LV3&0x0f];
                velocity_x_lv=PWMX_ADD_LV4;
            break;
            case PWMX_ADD_LV4:
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV4&0x0f]);
                TMR7=0;
                PR7= x_add_arry[PWMX_ADD_LV4&0x0f];
                velocity_x_lv=PWMX_ADD_LV5;  
            break;
            case PWMX_ADD_LV5:
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV5&0x0f]);
                TMR7=0;
                PR7= x_add_arry[PWMX_ADD_LV5&0x0f];
                velocity_x_lv=PWMX_ADD_LV6;
            break;
            case PWMX_ADD_LV6:
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV6&0x0f]);
                TMR7=0;
                PR7= x_add_arry[PWMX_ADD_LV6&0x0f];
                velocity_x_lv=PWMX_ADD_LV7;
            break;
            case PWMX_ADD_LV7:
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV7&0x0f]);
                TMR7=0;
                PR7= x_add_arry[PWMX_ADD_LV7&0x0f];
                velocity_x_lv=PWMX_ADD_LV8;
            break;
            case PWMX_ADD_LV8:
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV8&0x0f]);
                TMR7=0;
                PR7= x_add_arry[PWMX_ADD_LV8&0x0f];
                velocity_x_lv=PWMX_ADD_LV9;
            break;
            case PWMX_ADD_LV9:
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV9&0x0f]);
                TMR7=0;
                PR7= x_add_arry[PWMX_ADD_LV9&0x0f];
                velocity_x_lv=PWMX_ADD_LV10;
            break;
            case PWMX_ADD_LV10:
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV10&0x0f]);
                TMR7=0;
                PR7= x_add_arry[PWMX_ADD_LV10&0x0f];
                velocity_x_lv=PWMX_FULL_LV;
            break;
            case PWMX_FULL_LV:
                PWMX_frequency(pwmx_freq_table[PWMX_FULL_LV&0x0f]);
                TMR7=0;
                if(nor_pulsex>65535)
                {
                    PR7=65535;//set T7 counter pwm1l
                    nor_pulsex-=65535;
                }
                else
                {
                    PR7=nor_pulsex;
                    velocity_x_lv=PWMX_DEC_LV10;
                }
            break;
            case PWMX_DEC_LV10:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV10&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV10&0x0f];
                velocity_x_lv=PWMX_DEC_LV9;
            break;
            case PWMX_DEC_LV9:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV9&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV9&0x0f];
                velocity_x_lv=PWMX_DEC_LV8;
            break;
            case PWMX_DEC_LV8:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV8&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV8&0x0f];
                velocity_x_lv=PWMX_DEC_LV7;
            break;
            case PWMX_DEC_LV7:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV7&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV7&0x0f];
                velocity_x_lv=PWMX_DEC_LV6;
            break;
            case PWMX_DEC_LV6:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV6&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV6&0x0f];
                velocity_x_lv=PWMX_DEC_LV5;
            break;
            case PWMX_DEC_LV5:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV5&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV5&0x0f];
                velocity_x_lv=PWMX_DEC_LV4;
            break;
            case PWMX_DEC_LV4:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV4&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV4&0x0f];
                velocity_x_lv=PWMX_DEC_LV3;
            break;
            case PWMX_DEC_LV3:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV3&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV3&0x0f];
                velocity_x_lv=PWMX_DEC_LV2;
            break;
            case PWMX_DEC_LV2:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV2&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV2&0x0f];
                velocity_x_lv=PWMX_DEC_LV1;
            break;
            case PWMX_DEC_LV1:
                PWMX_frequency(pwmx_freq_table[PWMX_DEC_LV1&0x0f]);
                TMR7=0;
                PR7= x_dec_arry[PWMX_DEC_LV1&0x0f];
                velocity_x_lv=PWMX_DEC_END;
            break;
             case PWMX_DEC_END:
                if(axis_x_status==0x11)    //pluse dir ccw
                    PWMX_DIS(2); //disable pwm1
                else   //0x00 0x01 0x10 0x20 0x21
                    PWMX_DIS(0);
                T7CON&=0x0006;//T7 disable external clock       
                velocity_x_lv=PWMX_DEC_END2;
            break;
            default:
                while(1);//FAIL
            break;
        }
    }
    IFS3bits.T7IF = 0; // Clear Timer7 Interrupt Flag
    IEC3bits.T7IE = 1; // Enable Timer7 interrupt

}

void __attribute__((interrupt, no_auto_psv)) _T8Interrupt(void)
{
    //pwm2H counter
    IFS3bits.T8IF = 0; // Clear Timer8 Interrupt Flag
  
}


void __attribute__((interrupt, no_auto_psv)) _T9Interrupt(void)
{
    //pwm2L counter
    IFS3bits.T9IF = 0; // Clear Timer9 Interrupt Flag
    IEC3bits.T9IE = 0; // Disable Timer9 interrupt
 
    if(T9CONbits.TGATE==0 && (axis_y_status&0x30)==0x20)
    {
        T9CONbits.TCS=0;
        T9CONbits.TGATE=1;
        PR9=1;TMR9=0;
    }
    else
    {
        T9CONbits.TCS=1;
        T9CONbits.TGATE=0;

        switch(velocity_y_lv)
        {
            case PWMY_ADD_LV2:
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV2&0x0f]);
                velocity_y_lv=PWMY_ADD_LV3;
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV2&0x0f];
                velocity_y_lv=PWMY_ADD_LV3;
            break;
            case PWMY_ADD_LV3:
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV3&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV3&0x0f];
                velocity_y_lv=PWMY_ADD_LV4;
            break;
            case PWMY_ADD_LV4:
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV4&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV4&0x0f];
                velocity_y_lv=PWMY_ADD_LV5;
            break;
            case PWMY_ADD_LV5:
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV5&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV5&0x0f];
                velocity_y_lv=PWMY_ADD_LV6;
            break;
            case PWMY_ADD_LV6:
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV6&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV6&0x0f];
                velocity_y_lv=PWMY_ADD_LV7;
            break;
            case PWMY_ADD_LV7:
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV7&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV7&0x0f];
                velocity_y_lv=PWMY_ADD_LV8;
            break;
            case PWMY_ADD_LV8:
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV8&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV8&0x0f];
                velocity_y_lv=PWMY_ADD_LV9;
            break;
            case PWMY_ADD_LV9:
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV9&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV9&0x0f];
                velocity_y_lv=PWMY_ADD_LV10;
            break;
            case PWMY_ADD_LV10:
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV10&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV10&0x0f];
                velocity_y_lv=PWMY_FULL_LV;
            break;
            case PWMY_FULL_LV:
                PWMY_frequency(pwmy_freq_table[PWMY_FULL_LV&0x0f]);
                TMR9=0;
                if(nor_pulsey>65535)
                {
                    PR9=65535;//set T7 counter pwm1l
                    nor_pulsey-=65535;
                }
                else
                {
                    PR9=nor_pulsey;
                    velocity_y_lv=PWMY_DEC_LV10;
                }
            break;
            case PWMY_DEC_LV10:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV10&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV10&0x0f];
                velocity_y_lv=PWMY_DEC_LV9;
            break;
            case PWMY_DEC_LV9:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV9&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV9&0x0f];
                velocity_y_lv=PWMY_DEC_LV8;
            break;
            case PWMY_DEC_LV8:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV8&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV8&0x0f];
                velocity_y_lv=PWMY_DEC_LV7;
            break;
            case PWMY_DEC_LV7:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV7&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV7&0x0f];
                velocity_y_lv=PWMY_DEC_LV6;
            break;
            case PWMY_DEC_LV6:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV6&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV6&0x0f];
                velocity_y_lv=PWMY_DEC_LV5;
            break;
            case PWMY_DEC_LV5:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV5&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV5&0x0f];
                velocity_y_lv=PWMY_DEC_LV4;
            break;
            case PWMY_DEC_LV4:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV4&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV4&0x0f];
                velocity_y_lv=PWMY_DEC_LV3;
            break;
            case PWMY_DEC_LV3:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV3&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV3&0x0f];
                velocity_y_lv=PWMY_DEC_LV2;
            break;
            case PWMY_DEC_LV2:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV2&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV2&0x0f];
                velocity_y_lv=PWMY_DEC_LV1;
            break;
            case PWMY_DEC_LV1:
                PWMY_frequency(pwmy_freq_table[PWMY_DEC_LV1&0x0f]);
                TMR9=0;
                PR9=y_dec_arry[PWMY_DEC_LV1&0x0f];
                velocity_y_lv=PWMY_DEC_END;
            break;
             case PWMY_DEC_END:
                 T9CON&=0x0006;
                 if(axis_y_status==0x11)    //pluse dir ccw
                    PWMY_DIS(2); //disable pwm1
                else   //0x00 0x01 0x10 0x20 0x21
                    PWMY_DIS(0);
                velocity_y_lv=PWMY_DEC_END2;
            break;
            default:
                while(1);//FAIL
            break;
        }
    }
    IFS3bits.T9IF = 0; // Clear Timer9 Interrupt Flag
    IEC3bits.T9IE = 1; // Enable Timer9 interrupt

}
void __attribute__((interrupt, no_auto_psv)) _PWM1Interrupt(void)
{
	IFS5bits.PWM1IF=0;
	if(PWMCON1bits.FLTSTAT==1)
		PWMCON1bits.FLTSTAT=0;
}

void __attribute__((interrupt, no_auto_psv)) _PWM2Interrupt(void)
{
	IFS5bits.PWM2IF=0;
	if(PWMCON2bits.FLTSTAT==1)
		PWMCON2bits.FLTSTAT=0;
}

void PWM_CLKDIV(unsigned char clkdiv) //?�?�PWM?�頻
{
     //   PTCON &=0x0400; //disable pwm
	STCON2 = clkdiv;
        PTCON2 = clkdiv;
       // STCON=0x0400;
        PTCON |=0x8000; //enable pwm
}

void PWMX_frequency(unsigned int frequency)
{
    unsigned int freq1=0,freq2=0;
    
    PTPER =0;  //244=500K
    SDC1=PDC1=0;  //pwmh duty cycle
    SPHASE1=0;//(frequency/4);   //pwml phase  -180D
    freq1=(frequency/2);
    freq2=(frequency/4)*3;
    SPHASE1=freq2;//(frequency/4);   //pwml phase  -180D
    SDC1=freq1;  //pwml duty cycle ab phase used
    PDC1=freq1;  //pwmh duty cycle pulse dir used
    PTPER =frequency;  //244=500K 
}

void PWMY_frequency(unsigned int frequency)
{	
    unsigned int freq1=0,freq2=0;
    STPER =0;  //244=500K
    SDC2=PDC2=0;  //pwmh duty cycle
    SPHASE2=0;//(frequency/4);   //pwml phase  -180
    freq1=(frequency/2);
    freq2=(frequency/4)*3;
    SPHASE2=freq2;
    SDC2=freq1;  //pwml duty cycle ab phase used
    PDC2=freq1;  //pwmh duty cycle   pulse dir used
    STPER =frequency;  //244=500K
}

void INIT_PWMXY(unsigned char fail_en,unsigned char dead_time,unsigned char type)
{   // fail disable  dead time disable
    INIT_PWMY(fail_en,dead_time,type&0x0f);  //default pwm frequency is 500K bps
    if((type&0x0f)==AB_PHASE) //y axis
    {
        STCON|=0x0400;
        STCON2=2;//div 4
    }
    type=(type&0xf0)>>4;
    INIT_PWMX(fail_en,dead_time,type);  //default pwm frequency is 500K bps
    if((type&0x0f)==AB_PHASE)//x axis
    {
        PTCON2=2;
        PTCON|=0x0400;
    }
    PTCON |=0x8000;
    //PWM_CLKDIV(PWMCLK_DIV);

   
}

#if 0
void pwm_action(unsigned long send_pulse , unsigned char motor_dir )
{
   
 //   init_velocity=PWM_FREQ_2K;
 //   full_celocity=PWM_FREQ_500K;
    acceleration=20; //?�速�?%
    deceleration=20; //減速�?%
    add_pulse=(send_pulse/100)*acceleration;   //計�??�速pulse
    dec_pulse=(send_pulse/100)*deceleration;   //計�?減速pulse
    nor_pulse= send_pulse-add_pulse-dec_pulse; //計�??�速pulse
    velocity_x_lv = PWMX_ADD_LV2;
    //set add lv1
    if(add_pulse<=65535)
    {
        if(motor_dir==MOTOR_DIR_CCW)
        {   PWMX_DIS(2);
            TMR7=0;
            PR7=(add_pulse/LV_PCNT_TOTAL)*LV_PCNT1;
            T6CON&=0x0006;//T6 disable external clock
            T7CON|=0x8006;//T7 enable external clock
            PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV1&0x0f],MOTOR_DIR_CCW);
            PWMX_dir(2);
        }
        else
        {
            PWMX_DIS(0);
            TMR7=0;
            PR7=(add_pulse/LV_PCNT_TOTAL)*LV_PCNT1;
            T7CON|=0x8006;//T7 enable external clock
            T6CON&=0x0006;//T6 disable external clock
            PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV1&0x0f],MOTOR_DIR_CW);
            PWMX_dir(0);
        }
    }
    //PWMX_EN();

    //TMR8=0;//clear T8 counter pwm2h
    //TMR9=0;//clear T9 counter pwm2l
    while(1)
    {
        if(velocity_x_lv==PWMX_DEC_END2)
        {
            velocity_x_lv=0;
            T7CON&=0x0006;//T7 disable external clock
            if(motor_dir != MOTOR_DIR_CCW)
                PWMX_DIS(0); //disable pwmH
            else
                PWMX_DIS(2); //disable pwmH
            T7CONbits.TCS=1;
            T7CONbits.TGATE=0;
            TMR7=0;
            PR7=0;
            break;
        }
    }

}
#endif
void PWMX_ccw(unsigned char dir);// dir= 0 or 1
void PWMY_ccw(unsigned char dir);// dir= 0 or 1
unsigned char pwmx_action(unsigned long send_pulse , unsigned char motor_dir )
{

    if(velocity_x_lv==0) //start
    {
        accelerationx=30; //X AXIS ?�速�?%
        decelerationx=30; //X AXIS減速�?%
        add_pulsex=(send_pulse/100)*accelerationx;   //計�??�速pulse
        dec_pulsex=(send_pulse/100)*decelerationx;   //計�?減速pulse
        x_add_arry[1]=(add_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_1;
        x_add_arry[2]=(add_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_2;
        x_add_arry[3]=(add_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_3;
        x_add_arry[4]=(add_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_4;
        x_add_arry[5]=(add_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_5;
        x_add_arry[6]=(add_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_6;
        x_add_arry[7]=(add_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_7;
        x_add_arry[8]=(add_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_8;
        x_add_arry[9]=(add_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_9;
        x_add_arry[0]=x_add_arry[9]+x_add_arry[8]+x_add_arry[7]+x_add_arry[6]+x_add_arry[5];
        x_add_arry[10]=add_pulsex-x_add_arry[4]-x_add_arry[3]-x_add_arry[2]-x_add_arry[1]-x_add_arry[0];
        x_dec_arry[1]=(dec_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_1;
        x_dec_arry[2]=(dec_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_2;
        x_dec_arry[3]=(dec_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_3;
        x_dec_arry[4]=(dec_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_4;
        x_dec_arry[5]=(dec_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_5;
        x_dec_arry[6]=(dec_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_6;
        x_dec_arry[7]=(dec_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_7;
        x_dec_arry[8]=(dec_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_8;
        x_dec_arry[9]=(dec_pulsex/LV_PCNTX_TOTAL)*LV_PCNTX_9;
        x_dec_arry[0]=x_dec_arry[9]+x_dec_arry[8]+x_dec_arry[7]+x_dec_arry[6]+x_dec_arry[5];
        x_dec_arry[10]=dec_pulsex-x_dec_arry[4]-x_dec_arry[3]-x_dec_arry[2]-x_dec_arry[1]-x_dec_arry[0];
        nor_pulsex= send_pulse-add_pulsex-dec_pulsex; //計�??�速pulse
        velocity_x_lv = PWMX_ADD_LV2;
        //set add lv1
        if(add_pulsex<=65535)
        {
            if(motor_dir==MOTOR_DIR_CCW)
            {
                if(axis_x_status==0x10)  //pulse dir used
                    PWMX_DIS(2);
                
                delay_ns(pwmx_freq_table[PWMX_ADD_LV1&0x0f]);
                TMR7=0;
                //nor_pulsex+=2;
                PR7= x_add_arry[PWMX_ADD_LV1&0x0f];
                if(axis_x_status==0x20 || axis_x_status==0x00)
                {
                    
                    if(axis_x_status==0x20)
                    {
                        IOCON1bits.SWAP=0;
                        RPINR5bits.T7CKR=RP80; //set T7CK pin as PWM1L
                    }
                    else
                     //   IOCON1bits.SWAP=1;
                        RPINR5bits.T7CKR=RPI81; //set T7CK pin as PWM1H
                    }
                axis_x_status |= 1;
                IFS3bits.T7IF = 0; // Clear Timer7 Interrupt Flag
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV1&0x0f]);
                T7CON|=0x8006;//T7 enable external clock
                if(axis_x_status==0x21)
                    PWMX_EN();
                else if(axis_x_status==0x01)
                   PWMX_ccw(1);
                else if(axis_x_status==0x11)
                   PWMX_dir(2);
            }
            else
            {
                if(axis_x_status==0x10)  //pulse dir used
                    PWMX_DIS(0);
                
                delay_ns(pwmx_freq_table[PWMX_ADD_LV1&0x0f]);
                TMR7=0;
                PR7=x_add_arry[PWMX_ADD_LV1&0x0f];
                if(axis_x_status==0x20 || axis_x_status==0x00)
                {
                    if(axis_x_status==0x20)
                    {
                        IOCON1bits.SWAP=1;
                        RPINR5bits.T7CKR=RPI81; //set T7CK pin as PWM1H
                    }
                    else
                    {
                      //  IOCON1bits.SWAP=0;
                        RPINR5bits.T7CKR=RP80; //set T7CK pin as PWM1L
                    }
                }
                axis_x_status |= 0;
                IFS3bits.T7IF = 0; // Clear Timer7 Interrupt Flag
                PWMX_frequency(pwmx_freq_table[PWMX_ADD_LV1&0x0f]);
                T7CON|=0x8006;//T7 enable external clock
                if(axis_x_status==0x20)
                    PWMX_EN();
                else if(axis_x_status==0x00)
                    PWMX_ccw(0);
                else if(axis_x_status==0x10)
                    PWMX_dir(0);
            }
            return 1;//busy
        }
        else
        {
            velocity_x_lv=0;
            return 2; //init fail pulse to much
        }
    }
    else if(velocity_x_lv==PWMX_DEC_END2)//finish
    {
        velocity_x_lv=0;
        axis_x_status &=0xf0;
        T7CONbits.TCS=1;
        T7CONbits.TGATE=0;
        TMR7=0;
        PR7=0;
        return 0; //finish
    }
    else
        return 1; //busy
}

unsigned char pwmy_action(unsigned long send_pulse , unsigned char motor_dir )
{

    if(velocity_y_lv==0) //start
    {
        accelerationy=20; //?�速�?%
        decelerationy=20; //減速�?%
        add_pulsey=(send_pulse/100)*accelerationy;   //計�??�速pulse
        dec_pulsey=(send_pulse/100)*decelerationy;   //計�?減速pulse
        nor_pulsey= send_pulse-add_pulsey-dec_pulsey; //計�??�速pulse
        y_add_arry[1]=(add_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_1;
        y_add_arry[2]=(add_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_2;
        y_add_arry[3]=(add_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_3;
        y_add_arry[4]=(add_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_4;
        y_add_arry[5]=(add_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_5;
        y_add_arry[6]=(add_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_6;
        y_add_arry[7]=(add_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_7;
        y_add_arry[8]=(add_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_8;
        y_add_arry[9]=(add_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_9;
        y_add_arry[0]=y_add_arry[9]+y_add_arry[8]+y_add_arry[7]+y_add_arry[6]+y_add_arry[5];
        y_add_arry[10]=add_pulsey-y_add_arry[4]-y_add_arry[3]-y_add_arry[2]-y_add_arry[1]-y_add_arry[0];
        y_dec_arry[1]=(dec_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_1;
        y_dec_arry[2]=(dec_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_2;
        y_dec_arry[3]=(dec_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_3;
        y_dec_arry[4]=(dec_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_4;
        y_dec_arry[5]=(dec_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_5;
        y_dec_arry[6]=(dec_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_6;
        y_dec_arry[7]=(dec_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_7;
        y_dec_arry[8]=(dec_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_8;
        y_dec_arry[9]=(dec_pulsey/LV_PCNTY_TOTAL)*LV_PCNTY_9;
        y_dec_arry[0]=y_dec_arry[9]+y_dec_arry[8]+y_dec_arry[7]+y_dec_arry[6]+y_dec_arry[5];
        y_dec_arry[10]=dec_pulsey-y_dec_arry[4]-y_dec_arry[3]-y_dec_arry[2]-y_dec_arry[1]-y_dec_arry[0];
        velocity_y_lv = PWMY_ADD_LV2;
        //set add lv1
        if(add_pulsey<=65535)
        {
            if(motor_dir==MOTOR_DIR_CCW)
            {
                if(axis_y_status==0x10)  //pulse dir used
                    PWMY_DIS(2);
                delay_ns(pwmy_freq_table[PWMY_ADD_LV1&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV1&0x0f];
                if(axis_y_status==0x20 || axis_y_status==0x00)
                {
                    if(axis_y_status==0x20)
                    {
                        IOCON2bits.SWAP=0;
                        RPINR6bits.T9CKR=RP82; //RPI83 //set T9CK pin as PWM2L                   
                    }
                    else
                        RPINR6bits.T9CKR=RPI83; //RPI83 //set T9CK pin as PWM2H

                }
                axis_y_status |= 1;
                //T8CON&=0x0006;//T8 disable external clock
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV1&0x0f]);
                T9CON|=0x8006;//T9 enable external clock
                IFS3bits.T9IF = 0; // Clear Timer9 Interrupt Flag
                IEC3bits.T9IE = 1; // Enable Timer9 interrupt
                if(axis_y_status==0x21)
                    PWMY_EN();
                else if(axis_y_status==0x01)
                    PWMY_ccw(1);
                else if(axis_y_status==0x11)
                    PWMY_dir(2);
            }
            else
            {
                if(axis_y_status==0x10)
                    PWMY_DIS(0);
                
                delay_ns(pwmy_freq_table[PWMY_ADD_LV1&0x0f]);
                TMR9=0;
                PR9=y_add_arry[PWMY_ADD_LV1&0x0f];
                if(axis_y_status==0x20 || axis_y_status==0x00)
                {
                    if(axis_y_status==0x20)
                    {
                        RPINR6bits.T9CKR=RPI83; //set T9CK pin as PWM2H
                        IOCON2bits.SWAP=1;
                    }
                    else
                        RPINR6bits.T9CKR=RP82; //set T9CK pin as PWM2L
                }

                axis_y_status |= 0;
                PWMY_frequency(pwmy_freq_table[PWMY_ADD_LV1&0x0f]);
                 T9CON|=0x8006;//T9 enable external clock
                //T8CON&=0x0006;//T8 disable external clock
                IFS3bits.T9IF = 0; // Clear Timer9 Interrupt Flag
                IEC3bits.T9IE = 1; // Enable Timer9 interrupt
                if(axis_y_status==0x20)
                    PWMY_EN();
                else if(axis_y_status==0x0)
                    PWMY_ccw(0);
                else if(axis_y_status==0x10)
                    PWMY_dir(0);
            }
            return 1;//busy
        }
        else
        {
            velocity_y_lv=0;
            return 2; //init fail pulse to much
        }
    }
    else if(velocity_y_lv==PWMY_DEC_END2)//finish
    {
        axis_y_status &=0xf0;
        T9CON&=0x0006;//T7 disable external clock
        T9CONbits.TCS=1;
        T9CONbits.TGATE=0;
        /*
        if(motor_dir != MOTOR_DIR_CCW)
            PWMY_DIS(0); //disable pwmH
        else
            PWMY_DIS(2); //disable pwmH
         */
        TMR9=0;
        PR9=0;
        IFS3bits.T9IF = 0; // Clear Timer9 Interrupt Flag
        IEC3bits.T9IE = 0; // Enable Timer9 interrupt
        velocity_y_lv=0;//PWMY_FINISH;

        return 0; //finish
    }
    else
        return 1; //busy
}

//A/B Phase
void PWMX_EN(void)
{
        IOCON1&=0xfcff;
      //  PWMX_dir(0); //pulse dir use this function
}

void PWMX_DIS(unsigned char dis_value)  //set 0 led=off  pwm=L
{
	IOCON1bits.OVRDAT=dis_value;
        IOCON1|=0x0300;//bits.OVRENH=1; //PWM1H disable
	//IOCON1bits.OVRENL=1; //PWM1L disable
}

void PWMY_EN(void)
{
    IOCON2&=0xfcff;
   // PWMY_dir(0); //pulse dir use this function
    //IOCON2bits.OVRENH=0; //PWM2H enable
	//IOCON2bits.OVRENL=0; //PWM2L enable
}

void PWMY_DIS(unsigned char dis_value) //set 0 led=off  pwm=L
{
	IOCON2bits.OVRDAT=dis_value;
       	IOCON2|=0x0300; //PWM2H PWM2L disable
}

//pulse dir
void PWMX_dir(unsigned char dir)// dir= 0 or 1
{
    IOCON1bits.OVRENH=1; //PWM1H enable
    IOCON1bits.OVRENL=0; //PWM1L disable
    IOCON1bits.OVRDAT=dir;
}
void PWMY_dir(unsigned char dir)// dir= 0 or 1
{
    IOCON2bits.OVRENH=1; //PWM2H enable
    IOCON2bits.OVRENL=0; //PWM2L disable
    IOCON2bits.OVRDAT=dir;
}
//cw/ccw 
void PWMX_ccw(unsigned char dir)// dir= 0 or 1
{
	if(dir==1)
	{
		IOCON1bits.OVRENH=0; //PWM1H enable
		IOCON1bits.OVRENL=1; //PWM1L disable	
	}
	else
	{
		IOCON1bits.OVRENH=1; //PWM1H disable
		IOCON1bits.OVRENL=0; //PWM1L enable	
	}
	IOCON1bits.OVRDAT=0;
}

void PWMY_ccw(unsigned char dir)// dir= 0 or 1
{
	if(dir==1)
	{
		IOCON2bits.OVRENH=0; //PWM2H enable
		IOCON2bits.OVRENL=1; //PWM2L disable	
	}
	else
	{
		IOCON2bits.OVRENH=1; //PWM2H disable
		IOCON2bits.OVRENL=0; //PWM2L enable	
	}
	IOCON2bits.OVRDAT=0;
}

//Example
//INIT_UART1(BAUD_9600,NO_PARITY_8BIT,STOP_1BIT);

//uart 1~3
//--------------------
//
void INIT_UART1(unsigned int baud_rate,unsigned int parity,unsigned int stopbit) 
{
	// This is an EXAMPLE, so brutal typing goes into explaining all bit sets

	// The HPC16 board has a DB9 connector wired to UART1, so we will
	// be configuring this port only

	// configure U1MODE
	U1MODE=0; //8,n,1
	U1MODE=parity|stopbit;
/*
	U1MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//U2MODEbits.notimplemented;	// Bit14
	U1MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U1MODEbits.IREN = 0;	// Bit12 No IR translation
	U1MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	//U2MODEbits.notimplemented;	// Bit10
	U1MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U1MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U1MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U1MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')

	U1MODEbits.BRGH = 0;	// Bit3 16 clocks per bit period
	U1MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U1MODEbits.STSEL = 0;	// Bit0 One Stop Bit
*/	
	// Load a value into Baud Rate Generator.  Example is for 9600.
	// See section 19.3.1 of datasheet.
	//  U1BRG = (Fcy/(16*BaudRate))-1
	//  U1BRG = (60M/(16*9600))-1
   
	U1BRG = baud_rate;	

	// Load all values in for U1STA SFR
	U1STA=0;
/*	
	U1STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U1STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
	U1STAbits.UTXISEL0 = 0;	//Bit13 Other half of Bit15
    //U1STAbits.URXEN = 0;	//Bit12
	U1STAbits.UTXBRK = 0;	//Bit11 Disabled
	U1STAbits.UTXEN = 0;	//Bit10 TX pins controlled by periph
	U1STAbits.UTXBF = 0;	//Bit9 Read Only// 1:Transmit buffer is full
	U1STAbits.TRMT = 0;		//Bit8 Read Only// 1:Transmit Shift Register is empty   
	U1STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U1STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	U1STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	U1STAbits.PERR = 0;		//Bit3 *Read Only Bit*
	U1STAbits.FERR = 0;		//Bit2 *Read Only Bit*
	U1STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	U1STAbits.URXDA = 0;	//Bit0 *Read Only Bit*
*/
//	IPC7 = 0x4400;	// Mid Range Interrupt Priority level, no urgent reason
	IPC2bits.U1RXIP=3;
	IPC3bits.U1TXIP=3;
	IFS0bits.U1TXIF = 0;	// Clear the Transmit Interrupt Flag
	IEC0bits.U1TXIE = 0;//1;	// Enable Transmit Interrupts
	IFS0bits.U1RXIF = 0;	// Clear the Recieve Interrupt Flag
	IEC0bits.U1RXIE = 1;//1;	// Enable Recieve Interrupts

	U1MODEbits.UARTEN = 1;	// And turn the peripheral on
	U1STAbits.UTXEN = 1; //tx enable
	//Set UART1 TX RX Pin
	RPOR4bits.RP79R = UART1TX;  // TX1 in RP79	
	_TRISD15=0;  //tx output	
	RPINR18bits.U1RXR=RPI78;  // RX1 in RPI78
	_TRISD14=1;  //rx input
	_TRISK15=0;
	UART1_DE=DE_DISABLE;
}
void INIT_UART2(unsigned int baud_rate,unsigned int parity,unsigned int stopbit) 
{
	U2MODE=0; //8,n,1
	U2MODE=parity|stopbit;
	U2BRG = baud_rate;	

	// Load all values in for U1STA SFR
	U2STA=0;
	IPC7bits.U2TXIP=3;
	IPC7bits.U2RXIP=3;
	IFS1bits.U2TXIF = 0;	// Clear the Transmit Interrupt Flag
	IEC1bits.U2TXIE = 0;//1;	// Enable Transmit Interrupts
	IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
	IEC1bits.U2RXIE = 1;//1;	// Enable Recieve Interrupts
	IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
	//Set UART2 TX RX Pin
	RPOR11bits.RP108R = UART2TX;  // TX2 in RP108	
	_TRISF12=0;  //tx output	
	RPINR19bits.U2RXR=RPI44;  // RX2 in RPI44
	_TRISB12=1;  //rx input
	_ANSB12=0;
	_TRISK13=0;
	UART2_DE=DE_DISABLE;
	U2MODEbits.UARTEN = 1;	// And turn the peripheral on
	U2STAbits.UTXEN = 1; //tx enable
	
}
void INIT_UART3(unsigned int baud_rate,unsigned int parity,unsigned int stopbit) 
{
	U3MODE=0; //8,n,1
	U3MODE=parity|stopbit;
	U3BRG = baud_rate;	
	// Load all values in for U1STA SFR
	U3STA=0;
	IPC20bits.U3TXIP=3;
	IPC20bits.U3RXIP=3;
	IFS5bits.U3TXIF = 0;	// Clear the Transmit Interrupt Flag
	IEC5bits.U3TXIE = 0;//1;	// Enable Transmit Interrupts
	IFS5bits.U3RXIF = 0;	// Clear the Recieve Interrupt Flag
	IEC5bits.U3RXIE = 1;//1;	// Enable Recieve Interrupts
	U3MODEbits.UARTEN = 1;	// And turn the peripheral on
	U3STAbits.UTXEN = 1; //tx enable
	//Set UART1 TX RX Pin
	RPOR12bits.RP109R = UART3TX;  // TX3 in RP109	
	_TRISF13=0;  //tx output	
	RPINR27bits.U3RXR=RPI17;  // RX3 in RPI17
	_TRISA1=1;  //rx input
	_TRISK14=0;
	UART3_DE=DE_DISABLE;
}

void uart1_tx(unsigned char txdata)
{	
	UART1_DE=DE_ENABLE;	
	U1TXREG = txdata;
	while(!U1STAbits.TRMT);  //wait tx finish
	UART1_DE=DE_DISABLE;
}
void __attribute__( ( interrupt , no_auto_psv ) ) _U1TXInterrupt( void )
{   
	IEC0bits.U1TXIE=0;
	IFS0bits.U1TXIF = 0;
	IEC0bits.U1TXIE=1;
}  
void __attribute__( ( interrupt , no_auto_psv ) ) _U1RXInterrupt( void )
{   
	IEC0bits.U1RXIE=0;
	//U1RXREG;
	IFS0bits.U1RXIF = 0;
	IEC0bits.U1RXIE=1;
	U1STAbits.OERR = 0;
} 
void uart2_tx(unsigned char txdata)
{
	UART2_DE=DE_ENABLE;	
	U2TXREG = txdata;
	while(!U2STAbits.TRMT);  //wait tx finish
	UART2_DE=DE_DISABLE;
}
void __attribute__( ( interrupt , no_auto_psv ) ) _U2TXInterrupt( void )
{   
	IEC1bits.U2TXIE=0;
	IFS1bits.U2TXIF = 0;
	IEC1bits.U2TXIE=1;
} 
unsigned int rx2buf=0;
unsigned int rx2flag=0;
void __attribute__( ( interrupt , no_auto_psv ) ) _U2RXInterrupt( void )
{   
	IEC1bits.U2RXIE=0;
	rx2buf=U2RXREG;
	IFS1bits.U2RXIF = 0;
	IEC1bits.U2RXIE=1;
	U2STAbits.OERR = 0;
	rx2flag=1;
} 
void uart3_tx(unsigned char txdata)
{
	UART3_DE=DE_ENABLE;
	U3TXREG = txdata;
	while(!U3STAbits.TRMT);  //wait tx finish
	UART3_DE=DE_DISABLE;
}
void __attribute__( ( interrupt , no_auto_psv ) ) _U3TXInterrupt( void )
{   
	IEC5bits.U3TXIE=0;
	IFS5bits.U3TXIF = 0;
	IEC5bits.U3TXIE=1;
} 
void __attribute__( ( interrupt , no_auto_psv ) ) _U3RXInterrupt( void )
{   
	IEC5bits.U3RXIE=0;
	rx2buf=U3RXREG;  //rx date buffet 
	IFS5bits.U3RXIF = 0;
	IEC5bits.U3RXIE=1;
	U3STAbits.OERR = 0;
	rx2flag=1;
} 

//SPI

void INIT_SPI1(void)
{
    //EXTER IO input cs init
    _TRISB13=0;
    _ANSB13=0;  //RB13 is digital Output
    EXTIO_I_CS=SPI_CS_DIS;

    //EXTER IO output cs init
    _TRISB14=0;
    _ANSB14=0;  //RB14 is digital Output
    EXTIO_O_CS=SPI_CS_DIS;

     //ADC CS Pin init
    _TRISA3=0;
    ADC_CS=SPI_CS_DIS;

    //DAC CS Pin init
    _TRISD9=0;
    DAC_CS=SPI_CS_DIS;

    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 0; // Disable the interrupt
/*
    SPI1STATbits.SPIEN = 0;		//SPI1 disable
    SPI1STATbits.SPISIDL =0;	//1: into idle mode stop spi   0:dont stop spi
    SPI1STATbits.SPIBEC = 0;  	//unknow
    SPI1STATbits.SRMPT = 0;		//Shift Register (SPIxSR) Empty   1:buffer empty   0: buffer is not empty
    SPI1STATbits.SPIROV = 0;	//Receive Overflow Flag   1:overflow happend     0:no overflow
    SPI1STATbits.SRXMPT = 0;	//Receive FIFO Empty   1:RX FIFO empty   0:RX FIFO not empty
    SPI1STATbits.SISEL = 0;		//interrupt mode
    SPI1STATbits.SPITBF = 0;	//SPI1 Transmit Buffer Full 1:full   0:empty
    SPI1STATbits.SPIRBF = 0;	//SPI1 Receive Buffer Full 1:full   0:empty
*/
    SPI1STAT=0;
    SPI1CON1bits.DISSCK = 0;	//Internal serial clock is enabled		 1:pin is I/O
    SPI1CON1bits.DISSDO = 0;	// SDO1 pin is controlled by the module  1:pin is I/O
    SPI1CON1bits.MODE16 = 0;	// 1: 16 bits   0: 8 bits

    SPI1CON1bits.CKE = 1; 		// Serial output data changes on transition from
                                                            // Idle clock state to active clock state
    SPI1CON1bits.CKP = 0; 		// Idle state for clock is a low-level;
    
    //SPI1 clock speed settig 60MHz / SPRE / PPRE = 60M/64=937.5Kbps
    SPI1CON1bits.SPRE = 7;		//Secondary prescale   7~0 ->  1:1~8
    SPI1CON1bits.PPRE = 0;		//Primary Prescale    0(64:1)  1(16:1)   2(4:1)  3(1:1)
    SPI1CON2=0;					//spi1 framed disable                                                        // active state is a high-level
#if SPI1_MODE == SPI_MASTER
    SPI1CON1bits.MSTEN = 1;		//1:master mode   0:slave mode
    SPI1CON1bits.SMP = 0;		//Data Input Sample Phase(master only)   1: sample at data end  0: sample at middle
    //spi IO setting
    _TRISF8=0;
    _TRISF2=0;
    _TRISF3=1;
    RPOR8bits.RP98R= SPICK1;	//SCK1  SPI1 clock output setting at master mode
    RPOR11bits.RP104R= SPIDO1;//SPI1 DO Pin setting
    RPINR20bits.SDI1R=RP99;//SPI1 DI Pin setting
#endif
#if SPI1_MODE == SPI_SLAVE
    SPI1CON1bits.MSTEN = 0;		//1:master mode   0:slave mode
    SPI1CON1bits.SSEN = 0;		//0:slave mode dont used CS pin   1: slave used CS pin
    //spi IO setting
    RPINR20bits.SCK1R=RP98;//SPI1 clock input Pin setting at slave mode
    //RPINR21bits.SS1R=?;//SPI1 chip select pin setting
    RPOR11bits.RP104R= SPIDO1;//SPI1 DO Pin setting
    RPINR20bits.SDI1R=RP99;//SPI1 DI Pin setting
#endif
	 
    SPI1STATbits.SPIEN = 1; // Enable SPI module
    // Interrupt Controller Settings
//	IFS0bits.SPI1IF = 0;  // Clear the Interrupt flag
//	IEC0bits.SPI1IE = 1; // Enable the interrupt

}


unsigned char spi1_txrx(unsigned char tx_data)
{
    unsigned char temp=0;
 //   temp = SPI1BUF;			// dummy read of the SPI1BUF register to clear the SPIRBF flag
    asm("nop");asm("nop"); //cs low to high must be 50nS
    SPI1BUF = tx_data;		// write the data out to the SPI peripheral
    while (!SPI1STATbits.SPIRBF);	// wait for the data to be sent out
   // asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");
    temp = SPI1BUF;			// dummy read of the SPI1BUF register to clear the SPIRBF flag
    asm("nop");asm("nop"); //cs low to high must be 50nS
    return temp;
}
unsigned char spitemp=0;

unsigned int spi1_txrx16(unsigned int tx_data)
{
    unsigned int temp=0;
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); //cs low to high must be 50nS
    SPI1BUF = tx_data;		// write the data out to the SPI peripheral
    while (!SPI1STATbits.SPIRBF);	// wait for the data to be sent out
    temp = SPI1BUF;			// dummy read of the SPI1BUF register to clear the SPIRBF flag
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); //cs low to high must be 50nS
    return temp;
}


void INIT_EXT_IO(void)
{
    //check spi init
    if(SPI1STATbits.SPIEN==0) //spi1 was uninitial
        INIT_SPI1();
    else                      //spi1 was ininial
    {
        if(SPI1CON1bits.CKE==0)//check edge setting
        {   
            SPI1STATbits.SPIEN = 0; //SPI disable
            SPI1CON1bits.CKE = 1;
            SPI1CON1bits.PPRE = 0; //sclk=937Kbps
            SPI1CON1bits.MODE16 = 0;//8bit mode
            SPI1STATbits.SPIEN = 1; //SPI enable
        }
    }
    //INIT OUTUT
    EXTIO_O_CS=0;
    spi1_txrx(EXTIO_W);
    spi1_txrx(EXTIO_IOCON);
    spi1_txrx(0x08); //ADDRESS ADD MODE
    spi1_txrx(0x08); //ADDRESS ADD MODE
    EXTIO_O_CS=1;
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); //cs low to high must be 50nS
    EXTIO_O_CS=0;
    spi1_txrx(EXTIO_W);
    spi1_txrx(EXTIO_DIRA);
    spi1_txrx(0); //setting dir A OUTPUT
    spi1_txrx(0); //setting dir B OUTPUT
    EXTIO_O_CS=1;
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); //cs low to high must be 50nS
    EXTIO_O_CS=0;
    spi1_txrx(EXTIO_W);
    spi1_txrx(EXTIO_GPIOA);
    spi1_txrx(0x00); //setting gpio A =0
    spi1_txrx(0x00); //setting gpio B =0
    EXTIO_O_CS=1;   
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    
    //INIT INPUT
    EXTIO_I_CS=0;
    spi1_txrx(EXTIO_W);
    spi1_txrx(EXTIO_IOCON);
    spi1_txrx(0x08);  //ADDRESS ADD MODE
    spi1_txrx(0x08); //ADDRESS ADD MODE
    EXTIO_I_CS=1;
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
   
    EXTIO_I_CS=0;
    spi1_txrx(EXTIO_W);
    spi1_txrx(EXTIO_IPOLA);
    spi1_txrx(0xff);  //ADDRESS ADD MODE
    spi1_txrx(0xff); //ADDRESS ADD MODE
    EXTIO_I_CS=1;
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    
}
void EXTIO_SET_OUTPUT(unsigned int ioset)
{
    unsigned char temp=0;
    if(SPI1CON1bits.CKE==0) //check edge setting
    {
       SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 1;
        SPI1CON1bits.PPRE = 0; //sclk=937kbps
        SPI1CON1bits.MODE16 = 0; //8 bit mode
        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
        SPI1STATbits.SPIEN = 1; //SPI enable
    }
    EXTIO_O_CS=0;
    spi1_txrx(EXTIO_W);
    spi1_txrx(EXTIO_GPIOA);
    temp=ioset&0x00ff;
    spi1_txrx(temp); //setting gpio A =0
    temp=(ioset&0xff00)>>8;
    spi1_txrx(temp); //setting gpio B =0
    EXTIO_O_CS=1;
}
unsigned int EXTIO_GET_OUTPUT(void)
{
    unsigned char temp=0,temp1=0;
    unsigned int output_val=0;
    if(SPI1CON1bits.CKE==0)//check edge setting
    {
        SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 1;
        SPI1CON1bits.PPRE = 0;//sclk=937kbps
        SPI1CON1bits.MODE16 = 0; //8 bit mode
        SPI1STATbits.SPIEN = 1; //SPI enable
        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    }
    EXTIO_O_CS=0;
    spi1_txrx(EXTIO_R);
    spi1_txrx(EXTIO_GPIOA);
    temp=spi1_txrx(0); //setting gpio A =0
    temp1=spi1_txrx(0); //setting gpio B =0
    EXTIO_O_CS=1;
    output_val=(temp1<<8)|temp;
    return output_val;
}
unsigned int EXTIO_GET_INPUT(void)
{
    unsigned char temp=0,temp1=0;
    unsigned int input_val=0;
    if(SPI1CON1bits.CKE==0)//check edge setting
    {
        SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 1;
        SPI1CON1bits.PPRE = 0; //sclk=937kbps
        SPI1CON1bits.MODE16 = 0; //8 bit mode
        SPI1STATbits.SPIEN = 1; //SPI enable
        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    }
    EXTIO_I_CS=0;
    spi1_txrx(EXTIO_R);
    spi1_txrx(EXTIO_GPIOA);
    temp=spi1_txrx(0); //setting gpio A =0
    temp1=spi1_txrx(0); //setting gpio B =0
    EXTIO_I_CS=1;
    input_val=(temp1<<8)|temp;
    return input_val;
}
void INIT_ADC(void)
{
    _TRISA2=0;
    _TRISA4=1;
    _TRISA5=0;
    ADC_FS=1;
    ADC_INT=1;
    ADC_CSTART=1;
    
    if(SPI1STATbits.SPIEN==0) //spi1 was uninitial
    {
        INIT_SPI1();
        SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 0;
        //SPI1CON1bits.SPRE = 0;		//Secondary prescale   7~0 ->  1:1~8
        SPI1CON1bits.PPRE = 2;//1;//sclk=15Mbps
        SPI1CON1bits.MODE16 = 1; //16 bit mode
        SPI1STATbits.SPIEN = 1; //SPI enable
    }
    else                      //spi1 was ininial
    {
        if(SPI1CON1bits.CKE==1)//check edge setting
        {
            SPI1STATbits.SPIEN = 0; //SPI disable
            SPI1CON1bits.CKE = 0;
            SPI1CON1bits.PPRE = 2;//sclk=15Mbps
            SPI1CON1bits.MODE16 = 1; //16 bit mode
            SPI1STATbits.SPIEN = 1; //SPI enable
        }
    }
    //init tlc3574
    ADC_CS=SPI_CS_EN;
    spi1_txrx16(ADC_HARDWARE_DEFAULT);
    ADC_CS=SPI_CS_DIS;
     asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}

/*
 ADC read value demo code
        q=ADC_GET_VAL(ADC_CH0); //start adc
        for(j=0;j<1000;j++);
        while(1)
	{
            UPDATE_SYS_TIME();

            q=ADC_GET_VAL(ADC_CH1);
            adc_test_val0=(q*0.0012207)-8192*0.0012207;
            for(j=0;j<1000;j++);

            q=ADC_GET_VAL(ADC_CH2);
            adc_test_val1=(q*0.0012207)-8192*0.0012207;
            for(j=0;j<1000;j++);

            q=ADC_GET_VAL(ADC_CH3);
            adc_test_val2=(q*0.0012207)-8192*0.0012207;
            for(j=0;j<1000;j++);

            q=ADC_GET_VAL(ADC_CH0);
            adc_test_val3=(q*0.0012207)-8192*0.0012207;
            for(j=0;j<1000;j++);
            adc_last=adc_test_val0;
    }
 */

unsigned int ADC_GET_VAL(unsigned int ch)
{
    unsigned int val=0;

    if(SPI1CON1bits.CKE==1)//check edge setting
    {
        SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 0;
        SPI1CON1bits.PPRE = 2;//sclk=15Mbps
        SPI1CON1bits.MODE16 = 1; //16 bit mode
        SPI1STATbits.SPIEN = 1; //SPI enable
    }
    ADC_CS=SPI_CS_EN;
    val=spi1_txrx16(ch);
    spi1_txrx16(0);//wait sample 48 sclk
    spi1_txrx16(0);
    while(ADC_INT==1); //wait adc convert finish
    ADC_CS=SPI_CS_DIS;
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
 //   ADC_CS=SPI_CS_EN;
  //  val=spi1_txrx16(ch);//get adc values
//    ADC_CS=SPI_CS_DIS;
    val=val>>2;
    return val;
}


unsigned int DAC_REG_RW(unsigned char reg , unsigned int wdata)
{
    unsigned int rdata=0;
    asm("nop");asm("nop");asm("nop");
    DAC_CS=SPI_CS_EN;
    asm("nop");asm("nop");asm("nop");
    if((reg&0x80)==0x80)
        spi1_txrx(reg); //read mode
    else
        spi1_txrx(reg&0x7f); //write mode

    spi1_txrx(((wdata&0xff00)>>8));//send wdata high byte
    spi1_txrx(wdata&0x00ff); //send wdata low byte
    asm("nop");asm("nop");asm("nop");
    DAC_CS=SPI_CS_DIS;

    if((reg&0x80)==0x80)
    {
        asm("nop");asm("nop");asm("nop");
        DAC_CS=SPI_CS_EN;
        asm("nop");asm("nop");asm("nop");
        spi1_txrx(reg);
        rdata = spi1_txrx(0);
        rdata=rdata<<8;
        rdata |= spi1_txrx(0); //ALL dac gain is x2
        asm("nop");asm("nop");asm("nop");
        DAC_CS=SPI_CS_DIS;
        asm("nop");asm("nop");asm("nop");
    }
    return rdata;
 //    asm("nop");asm("nop");
//    DAC_LDAC= DAC_DATA_UPDATE_EN;
//    asm("nop");asm("nop");
//    DAC_LDAC= DAC_DATA_UPDATE_DIS;
}

void INIT_DAC(unsigned char data_pol,unsigned int dac_gain_sel)
{
    if(SPI1STATbits.SPIEN==0) //spi1 was uninitial
    {
        INIT_SPI1();
        SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 0;
        SPI1CON1bits.SPRE =2;  //0~7=div8~1
        SPI1CON1bits.PPRE = 3;//1;//sclk=4Mbps
        SPI1CON1bits.MODE16 = 0; //8 bit mode
        SPI1STATbits.SPIEN = 1; //SPI enable
    }
    else                      //spi1 was ininial
    {
        if(SPI1CON1bits.CKE==1 || SPI1CON1bits.MODE16 ==1)//check edge setting
        {
            SPI1STATbits.SPIEN = 0; //SPI disable
            SPI1CON1bits.CKE = 0;
            SPI1CON1bits.PPRE = 1;//sclk=4Mbps
            SPI1CON1bits.MODE16 = 0; //8 bit mode
            SPI1STATbits.SPIEN = 1; //SPI enable
        }
    }

    _TRISD8=0;  //DAC_GA
    _TRISA15=0; //DAC_GB
    _TRISA14=0; //DAC_RST
    _TRISK11=0; //DAC_BTC NO USE
    _TRISK12=0; //DAC_LDAC
    _TRISB15=0; //DAC_POWER
    _ANSB15=0;
    DAC_RST=DAC_RST_DIS;
    DAC_POWER=DAC_POW_ON;
    DAC_LDAC= DAC_DATA_UPDATE_EN;

     switch(data_pol)
    {
        case GAUN_GBUN :
            DAC_GA = UNIPOLAR_MODE; //0~+Vref x gain
            DAC_GB = UNIPOLAR_MODE; //0~+Vref x gain
        break;
            case GAB_GBUN :
            DAC_GA = BIPOLAR_MODE;  //-vref x gain/2 ~ +Vref x gain/2
            DAC_GB = UNIPOLAR_MODE; //0~+Vref x gain
        break;

        case GAUN_GBB :
            DAC_GA = UNIPOLAR_MODE; //0~+Vref x gain
            DAC_GB = BIPOLAR_MODE;  //-vref x gain/2 ~ +Vref x gain/2
        break;

        case GAB_GBB :
            DAC_GA = BIPOLAR_MODE; //-vref x gain/2 ~ +Vref x gain/2
            DAC_GB = BIPOLAR_MODE; //-vref x gain/2 ~ +Vref x gain/2
        break;
        default:
            DAC_GA = UNIPOLAR_MODE; //0~+Vref x gain
            DAC_GB = UNIPOLAR_MODE; //0~+Vref x gain
        break;
    }
    //reset dac
    DAC_RST=DAC_RST_EN;
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    DAC_RST=DAC_RST_DIS;
   
    DAC_BTC=0;//dac8734 is no used this pin
   

    //INIT dac
   DAC_REG_RW(DAC_W_CMD,dac_gain_sel);
   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}



//SPI2 SD Card

//I2C
void INIT_I2C(void) //I2C 2
{    //60000/(I2C2BRG+8.6)=I2C CLK  X KHz  12M/2/(BRG+8.6)  //8.6=110NS*60m+2  
	I2C2BRG=300;     //300;//194KHz    // 72;//738K    //419;//144KHz     //i2c clk frequency
//	ODCFbits.ODCF4=1;  //setting i2c2 DA is open drin
//	ODCFbits.ODCF5=1;  //setting i2c2 CLK is open drin
	I2C2CON=0xD220;//I2C1_ON & I2C1_IDLE_CON & I2C1_CLK_REL & I2C1_IPMI_DIS & I2C1_7BIT_ADD &
			//	I2C1_SLW_DIS & I2C1_SM_DIS & I2C1_GCALL_DIS & I2C1_STR_DIS & I2C1_NACK &
	//00xD220		//	I2C1_ACK_DIS & I2C1_RCV_DIS & I2C1_STOP_DIS & I2C1_RESTART_DIS & I2C1_START_DIS ;//0xFFF0;//I2c disable	
	I2C2STAT=0; //I2c status clear
/*
	I2C2STATbits.ACKSTAT=0;// 0:ACK  1:NACK
	I2C2STATbits.TRSTAT=0; // MASTER STATUS 0:EMPTY 1:BUSY(8bit+ack)
 	I2C2STATbits.BCL=0;    // 1:Bus Collision
	I2C2STATbits.IWCOL=0;  // 1:Write Collision 
	I2C2STATbits.I2COV=0;  // 1:Receive Overflow
	I2C2STATbits.TBF=0;    // 0: RX BUF NULL   1:RX BUF FULL
	I2C2STATbits.RBF=0;	   // 0: TX FINISH     1: TX BUSY
*/

//	I2C2CONbits.I2CEN=1;
//	I2C2CONbits.ACKEN=1;
}


#define TWOBYTE  2
#define ONEBYTE  1
#define ZEROBYTE  0
char i2c_send_byte(unsigned char data)
{
	while( I2C2STATbits.TBF ); //wait i2c buffer empty
	I2C2TRN = data;
	if(I2C2STATbits.IWCOL)        /* If write collision occurs,return -1 */
		return -1;
    else
    {
        while(I2C2STATbits.TRSTAT);  // wait until write cycle is complete 
        while(I2C2CONbits.SEN || I2C2CONbits.RSEN || I2C2CONbits.PEN || I2C2CONbits.RCEN ||
        I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT);  //wait i2c idel            // ensure module is idle
     	if ( I2C2STATbits.ACKSTAT ) // test for ACK condition received
    	 	return ( -2 );
	    else 
			return ( 0 );               // if WCOL bit is not set return non-negative #
    }
}
unsigned char msb_lsb_change(unsigned char data)
{
    unsigned char temp=0;
    temp= ((data&0xf0)>>4) | ((data&0x0f)<<4);
    temp= ((temp&0xcc)>>2) | ((temp&0x33)<<2);
    temp= ((temp&0xaa)>>1) | ((temp&0x55)<<1);
    return temp;
}

//under at24c16 no page read mode
//at24c01,02    1K/2K bit    8 bytes page write
//at24c04,08,16 4K/8K/16K   16 bytes page write
//at24c32,64    32K/64K     32 bytes page write
//at24c128,256  128K/256K   64 bytes page write
//at24c512      512K       128 bytes page write
//at24cm01      1M bit     256 bytes page write



//i2c_wr(0xa0, 0x0 ,(unsigned char*)&eeprom_data,8,1);  //exp write
//i2c_wr(0xa1, 0x0 ,(unsigned char*)&eeprom_data,1,1);  //exp read
void i2c_wr(unsigned char id , unsigned int addr ,unsigned char *data,unsigned int nbyte,unsigned char addr_type)
{   
	while(I2C2CONbits.SEN || I2C2CONbits.RSEN || I2C2CONbits.PEN || I2C2CONbits.RCEN ||
          I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT);  //wait i2c idel
	I2C2CONbits.SEN=1; //I2C 2 send start signal	
	while( I2C2CONbits.SEN );	

	i2c_send_byte(id&0xfe);  // id    bit0(first must be set 0) : 0=write 1=read ; bit1~3  device address

	if(addr_type==TWOBYTE)
		i2c_send_byte((addr&0xff00)>>8);  // addr High byte 
	if(addr_type==TWOBYTE || addr_type==ONEBYTE)
		i2c_send_byte(addr&0x00ff);  // addr Low byte
	
	if((id&0x01)==1) //read mode
	{
		I2C2CONbits.RSEN=1; //send read start
		while( I2C2CONbits.RSEN );
		i2c_send_byte(id);  // id read cmd  	
		while(nbyte>0)
		{
			I2C2CONbits.RCEN=1;	// Receive Enable 
			while(I2C2CONbits.RCEN);
			I2C2STATbits.I2COV = 0;
    		while( I2C2STATbits.RBF==0 ); //wait i2c RX buffer full	
			*data++=I2C2RCV;
			nbyte--;
		}
	}
	else 
	{
		while(nbyte>0)
		{				
			i2c_send_byte(*data++);  // data   write n byte data
			nbyte--;	
		}
	}
	while( I2C2STATbits.TBF );
	I2C2CONbits.PEN=1;	//I2C 2 send stop signal
	while ( I2C2CONbits.PEN ); //wait stop finish 	
}

//set time example
//for(i=0;i<7;i++)
//	time_data[i]=msb_lsb_change(time_data[i]);
//i2c_wr(0x64 ,0,(unsigned char *)&time_data,7,0);

//read time example
//i2c_wr(0x65 ,0,(unsigned char *)&time_data,7,0);
//for(i=0;i<7;i++)
//	time_data[i]=msb_lsb_change(time_data[i]);
//  time_data[4]=time_data[4]&0xbf; //clear hour am/pm flag
void INIT_EXT_RTC(void)
{	
	unsigned char reg[1];
	i2c_wr(0x6f , 0 ,(unsigned char *)&reg,1,0); //check sram !=0 
	if(reg[0]==0)
	{
		reg[0]=0xc0;
		i2c_wr(0x60 ,0,(unsigned char *)&reg,1,0);
		i2c_wr(0x6e ,0,(unsigned char *)&reg,1,0);
	
	}
}
//INIT internal rtc
void INIT_INT_RTC(unsigned int year, unsigned int m_d,unsigned int w_h ,unsigned int m_s)
{
    RCFGCAL=0;      //disable RTC
    NVMKEY=0x55;    //unlock rtc byte 1
    NVMKEY=0xaa;    //unlock rtc byte 2
    RCFGCAL=0x2300; // RTCWREN=1 rtc write enable  addr=3 start form yera
    RTCVAL=year;
    RTCVAL=m_d;
    RTCVAL=w_h;
    RTCVAL=m_s;
    RCFGCAL=0x8300;  // enable RTC & disable RTC write
}
struct RTC_DATA SYS_TIME;
void UPDATE_SYS_TIME(void)
{
    unsigned int temp=0;
 
    RCFGCAL|=0x0300;
    SYS_TIME.year=RTCVAL;
    temp=RTCVAL;
    SYS_TIME.month=(temp&0xff00)>>8;
    SYS_TIME.day=(temp&0x00ff);
    temp=RTCVAL;
    SYS_TIME.week=(temp&0xff00)>>8;
    SYS_TIME.hour=(temp&0x00ff);
    temp=RTCVAL;
    SYS_TIME.minute=(temp&0xff00)>>8;
    SYS_TIME.sec=(temp&0x00ff);
  
}

// System OSC
void INIT_OSC(void)
{
	// Configure PLL prescaler, PLL postscaler, PLL divisor
	//FCY = FOSC / (2 * DOZE)   DOZE=1  //machine cycle
    //FOSC = (Fin * M) / (N1 * N2)      //system clock 
	PLLFBD=65;//60MHz ; // M=65    //(7.37MHz*PLLFBD)/(N1*N2) = 7.37*65/4 = 119.7625 MHz           
	CLKDIVbits.PLLPOST=0; // N2=2
	CLKDIVbits.PLLPRE=0; // N1=2
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


void INIT_LIMITX(void)
{
    //INIT LIMITX1  LIMITX2
    _TRISJ7=1;  //LIMITX1 IS INPUT
    _TRISJ6=1;  //LIMITX2 IS INPUT
}  //READ LIMITX1=LIMIT_H OR LIMIT_L
void INIT_LIMITY(void)
{
    //INIT LIMITX1  LIMITX2
    _TRISJ5=1;  //LIMITY1 IS INPUT
    _TRISJ4=1;  //LIMITY2 IS INPUT
}

//QEI X Encode input  initial
//reg1 set QEI2CON , reg2 set QEI2IOC , reg3 set QEI2STAT
//QEI1CON//control QEI operation 
//QEI1IOC// control QEI IO mode(polarity level)
//QEI1STAT// interrupt enable & interrupt flag

// Used EXT up/dpwn mode must set QEI_CNT_DIR_P  pulse x1 mode
// Used QUAD mode must set QEI_CNT_DIR_P  pulse X4 mode
// INIT_QEIX( QEI_DIS | QEI_SIDL_DIS | QEI_COUNT_INIT_M0 | QEI_IMV0 | QEI_TIMER_DIV1
//            | QEI_CNT_DIR_P | QEI_GATE_DIS | QEI_CNT_UD_TIMER/*QEI_CNT_QUAD_TIMER*/
//            ,QEI_OUT_MODE1,0);//reg3=0 all interrupt disable

// INIT_QEIX( QEI_DIS | QEI_SIDL_DIS | QEI_COUNT_INIT_M0 | QEI_IMV0 | QEI_TIMER_DIV1
//          | QEI_CNT_DIR_P | QEI_GATE_DIS | QEI_CNT_QUAD_TIMER
//          ,QEI_OUT_MODE1,0);//reg3=0 all interrupt disable

void INIT_QEIX(unsigned int reg1,unsigned int reg2,unsigned int reg3) //QEI1
{
    QEI1CON = 0;  //QEI1 disable
    RPINR14bits.QEA1R = QEIX_A_SEL;	    //select QEI1 pulse A Pin
    RPINR14bits.QEB1R = QEIX_B_SEL;	    //select QEI1 pulse B Pin
    RPINR15bits.INDX1R = QEIX_INDEX_SEL;//select QEI1 pulse Index Pin
    RPINR15bits.HOME1R = QEIX_HOME_SEL;	//select QEI1 pulse Home Pin
    _TRISA6=1;
    _TRISG15=1;
    _TRISG13=1;
    _TRISG1=1;
    _ANSA6=0;  //rpi22 is digital input
    #if QEI_OUT_CTRL==QEI_CTRL
    RPOR7bits.RP97R = QEIOUTX;
    #endif
    #if QEI_OUT_CTRL==GPIO_CTRL
    _TRISF1=0;
    QEIOUTX=QEIOUT_L;
    #endif

    QEI1CON = reg1 & 0x7FFF; //control QEI operation
    QEI1IOC = reg2; // control QEI IO mode(polarity level)
    QEI1STAT = reg3;// interrupt enable & interrupt flag
    //counter
    POS1CNTH = 0; //counter high byte
    POS1CNTL = 0; //counter low byte
    POS1HLD = 0; //counter high byte latch
    VEL1CNT = 0;
    INT1TMRL = 0;
    INT1TMRH = 0;
    INT1HLDL = 0;
    INT1HLDH = 0;
    INDX1CNTL = 0;
    INDX1CNTH = 0;
    INDX1HLD = 0;
    QEI1GECL = 0;
    QEI1ICL = 0;
    QEI1GECH = 0;
    QEI1ICH = 0;
    QEI1LECL = 0;
    QEI1LECH = 0;
    IFS3bits.QEI1IF=0; //interrupt flag
    if((reg3&0x1555)!=0)
    {
        IEC3bits.QEI1IE=1; //interrupt enable
        IPC14bits.QEI1IP=1;//interrupt source enable
    }
    else
    {
        IEC3bits.QEI1IE=0; //interrupt disable
        IPC14bits.QEI1IP=0;//interrupt source disable
    }
    QEI1CON |= QEI_EN;
}





//QEI Y Encode input  initial
//reg1 set QEI2CON , reg2 set QEI2IOC , reg3 set QEI2STAT
//QEI2CON//control QEI operation 
//QEI2IOC// control QEI IO mode(polarity level)
//QEI2STAT// interrupt enable & interrupt flag

void INIT_QEIY(unsigned int reg1,unsigned int reg2,unsigned int reg3) //QEI2
{
    QEI2CON = 0;  //QEI1 disable
    RPINR16bits.QEA2R = QEIY_A_SEL;	    //select QEI1 pulse A Pin
    RPINR16bits.QEB2R = QEIY_B_SEL;	    //select QEI1 pulse B Pin
    RPINR17bits.INDX2R = QEIY_INDEX_SEL;//select QEI1 pulse Index Pin
    RPINR17bits.HOME2R = QEIY_HOME_SEL;	//select QEI1 pulse Home Pin
    _TRISA7=1;
    _TRISG14=1;
    _TRISG12=1;
    _TRISG0=1;
    _ANSA7=0;  //rpi23 is digital input
    #if QEI_OUT_CTRL==QEI_CTRL
    RPOR7bits.RP96R = QEIOUTY;
    #endif
    #if QEI_OUT_CTRL==GPIO_CTRL
    _TRISF0=0;
    OEIOUTY=QEIOUT_L;
    #endif

    QEI2CON = reg1 & 0x7FFF;  //control QEI operation
    QEI2IOC = reg2;           // control QEI IO mode(polarity level)
    QEI2STAT = reg3;         // interrupt enable & interrupt flag

    //counter
    POS2CNTH = 0; //counter high byte
    POS2CNTL = 0; //counter low byte
    POS2HLD = 0; //counter high byte latch
    VEL2CNT = 0;
    INT2TMRL = 0;
    INT2TMRH = 0;
    INT2HLDL = 0;
    INT2HLDH = 0;
    INDX2CNTL = 0;
    INDX2CNTH = 0;
    INDX2HLD = 0;
    QEI2GECL = 0;
    QEI2ICL = 0;
    QEI2GECH = 0;
    QEI2ICH = 0;
    QEI2LECL = 0;
    QEI2LECH = 0;
    IFS4bits.QEI2IF=0; //interrupt flag
    if((reg3&0x1555)!=0)  //every interrupt enable
    {
        IEC4bits.QEI2IE=1; //interrupt enable
        IPC18bits.QEI2IP=1;//interrupt source enable
    }
    else
    {
        IEC4bits.QEI2IE=0; //interrupt disable
        IPC18bits.QEI2IP=0; //interrupt source disable
    }
    QEI2CON |= QEI_EN;
}


void __attribute__((interrupt, no_auto_psv)) _QEI1Interrupt(void)   
{
	IFS3bits.QEI1IF=0;
        if(QEI1STATbits.IDXIRQ==1)
        {
            QEI1STATbits.IDXIRQ=0;	//index interrupt status
        
        }
        if(QEI1STATbits.HOMIRQ==1)
        {
            QEI1STATbits.HOMIRQ = 0;//home interrupt status

        }
        if(QEI1STATbits.VELOVIRQ==1)
        {
            QEI1STATbits.VELOVIRQ = 0;//Velocity Counter interrupt status

        }
        if(QEI1STATbits.PCIIRQ==1)
        {
            QEI1STATbits.PCIIRQ = 0;//Position Counter (Homing) status

        }
        if(QEI1STATbits.POSOVIRQ==1)
        {
            QEI1STATbits.POSOVIRQ = 0;//counter overflow status

        }
        if(QEI1STATbits.PCLEQIRQ==1)
        {
            QEI1STATbits.PCLEQIRQ = 0;//Position Counter Less Than or Equal Compare status
        
        }
        if(QEI1STATbits.PCHEQIRQ==1)
        {
            QEI1STATbits.PCHEQIRQ = 0;	// Position Counter Greater Than or Equal Compare status

        }
}


void __attribute__((interrupt, no_auto_psv)) _QEI2Interrupt(void)   
{
	IFS4bits.QEI2IF=0;
        if(QEI2STATbits.IDXIRQ==1)
        {
            QEI2STATbits.IDXIRQ=0;	//index interrupt status

        }
        if(QEI2STATbits.HOMIRQ==1)
        {
            QEI2STATbits.HOMIRQ = 0;//home interrupt status

        }
        if(QEI2STATbits.VELOVIRQ==1)
        {
            QEI2STATbits.VELOVIRQ = 0;//Velocity Counter interrupt status

        }
        if(QEI2STATbits.PCIIRQ==1)
        {
            QEI2STATbits.PCIIRQ = 0;//Position Counter (Homing) Initialization Process Complete status

        }
        if(QEI2STATbits.POSOVIRQ==1)
        {
            QEI2STATbits.POSOVIRQ = 0;//counter overflow status

        }
        if(QEI2STATbits.PCLEQIRQ==1)
        {
            QEI2STATbits.PCLEQIRQ = 0;//Position Counter Less Than or Equal Compare tatus

        }
        if(QEI2STATbits.PCHEQIRQ==1)
        {
            QEI2STATbits.PCHEQIRQ = 0;	// Position Counter Greater Than or Equal Compare status

        }
}

unsigned long GET_ENCX(void)
{
    unsigned long cntx=0;
    cntx = POS1CNTH;
    cntx = (cntx<<16) | POS1CNTL; //counter low byte
    POS1HLD = 0;
    POS1CNTH = 0;
    POS1CNTL = 0;        
    return cntx;
}

unsigned long GET_ENCY(void)
{
    unsigned long cnty=0;
    cnty = POS2CNTH;
    cnty = (cnty<<16) | POS2CNTL; //counter low byte
    POS2HLD = 0;
    POS2CNTH = 0;
    POS2CNTL = 0;
    return cnty;
}

unsigned long GET_INDEX_X(void)
{
    unsigned long indx_cnt=0;
    indx_cnt=INDX1CNTH;
    indx_cnt=(indx_cnt<<16) | INDX1CNTL;
    return indx_cnt;
}
unsigned long GET_INDEX_Y(void)
{
    unsigned long indy_cnt=0;
    indy_cnt=INDX2CNTH;
    indy_cnt=(indy_cnt<<16) | INDX2CNTL;
    return indy_cnt;
}


void INIT_SYSTEM_TIMER(void)  //Timer1 interrupt cycle about 10ms
{
    _TRISE1=0;
    _TRISE0=0;
    _ANSE1=0;
    _ANSE0=0;
    T1CON=0;
    TMR1=0;//clear T8 counter
    PR1=2343; //Load the period value  2343&4.27us=10ms
    IPC0bits.T1IP = 0x03; // Set Timer8 Interrupt Priority Level
    IFS0bits.T1IF = 0; // Clear Timer8 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer8 interrupt
    T1CON=0x8030; // 256/60M= 4.27us
}

unsigned char system_time_flag=0;
unsigned char system_time_flag2=0;
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    //system timer 10ms
    IFS0bits.T1IF = 0; // Clear Timer8 Interrupt Flag
    TMR1=0;
    PR1=2343;
    system_time_flag=1;
    system_time_flag2=1;
}