/*
 * File:   PWM_Setting.c
 * Author: user
 *
 * Created on 2017年8月11日, 下午 4:08
 */
#include "..\h\Global_define.h"
#include "..\h\IO_Driver.h"
#include "..\h\System_Control.h"

//PWM Setting
void InitialPWMPeriodX(void)
{
    PTPER = 10;
    PDC1 = 5;
    SDC1 = 5;
    SPHASE1 = 2;
    PHASE1 = 0;     
}

void InitialPWMPeriodY(void)
{
    STPER = 10;
    PDC2 = 5;
    SDC2 = 5;
    SPHASE2 = 0;
    PHASE2 = 0;     
}

void INIT_PWMX(void)
{//Use Primary Time Base, PTPER
    PTCON = 0x0000; //PWM disable
    PTCON2 = 0x0004;//PCLKDIV = 4 ==> PWM Source Frequency = 120MHz / 16 = 7.5MHz
    PWMCON1=0;
    FCLCON1 = 0x0003; //fail input disable
    PWMCON1bits.FLTIEN=0; //fail input interrupt disable
    DTR1=ALTDTR1=0;
    PWMCON1bits.DTC=0b10; //Dead disable
//    PWMCON1bits.ITB = 1;//PHASEx/SPHASEx registers provide time base period for this PWM generator
    PWMCON1bits.MDCS = 0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON1bits.MTBS = 0; //pwm clk = PTPER
    PWMCON1bits.IUE = 0;//PWMCON1 |= 0x0001 ;
    PTCONbits.EIPU = 0;//EIPU : Enable Immediate Period Update
    IOCON1 = 0xCF01;//Independent
//    IOCON1 = 0xC701;//Redundant
    
    InitialPWMPeriodX();   
    
    _TRISE0=0;//PWM1L     
    _TRISE1=0;//PWM1H
   
    PTCON |= 0x8000 ; //PWM Enable
}
void INIT_PWMY(void)
{//Use Secondary Time Base, STPER
    PTCON = 0x0000; //PWM disable
    STCON = 0x0000;
    STCON2 = 0x0004;//PCLKDIV = 4 ==> PWM Source Frequency = 120MHz / 16 = 7.5MHz
    PWMCON2=0;
    FCLCON2 = 0x0003; //fail input disable
    PWMCON2bits.FLTIEN=0; //fail input interrupt disable   
    DTR2=ALTDTR2=0;
    PWMCON2bits.DTC=0b10; //Dead disable         
//    PWMCON2bits.ITB = 1;//PHASEx/SPHASEx registers provide time base period for this PWM generator
    PWMCON2bits.MDCS =0;//pwm provide duty define by PDC2(PWMH) SDC2(PWML)
    PWMCON2bits.MTBS = 1; //pwm clk = STPER  
    PWMCON2bits.IUE = 0;//PWMCON2 |= 0x0001;
    STCONbits.EIPU = 0;//STCON |= 0x0400;//EIPU : Enable Immediate Period Update
    
    IOCON2 = 0xCF01;//Independent
//    IOCON2 = 0xC701;//Redundant    
    
    InitialPWMPeriodY();
            
    _TRISE2=0;//PWM2L
    _TRISE3=0;//PWM2H      
       
    PTCON |= 0x8000 ; //PWM Enable
}


void PWMX_EN(void)
{
//    PTCON &= (~0x8000); //PWM Disable           
//    IOCON1 |= 0x0300;
    PDC1 = 7;
    SDC1 = 7;
    IOCON1 &= (~0x0300);
//    PTCON |= 0x8000 ; //PWM Enable   
}

void PWMX_DIS(void)  //set 0 led=off  pwm=L
{
//    PTCON &= (~0x8000); //PWM Disable
//    IOCON1 &= (~0x0300);
    IOCON1 |= 0x0300;
    InitialPWMPeriodX();
//    PTCON |= 0x8000 ; //PWM Enable

//    InitialPWMPeriodX();
}


void PWMY_EN(void)
{
//    PTCON &= (~0x8000); //PWM Disable         
//    IOCON2 |= 0x0300;    
    PDC2 = 7;
    SDC2 = 7;
    IOCON2 &= (~0x0300);
//    PTCON |= 0x8000 ; //PWM Enable
}

void PWMY_DIS(void)  //set 0 led=off  pwm=L
{
//    PTCON &= (~0x8000); //PWM Disable
//    IOCON2 &= (~0x0300);
    IOCON2 |= 0x0300;
    InitialPWMPeriodY();
//    PTCON |= 0x8000 ; //PWM Enable
}


void INIT_PWM(void)
{
    PTCON = 0x0000; //Primary PWM disable
    PTCON2 = 0x0004;//PCLKDIV = 4 ==> PWM Source Frequency = 120MHz / 16 = 7.5MHz
    STCON = 0x0000;//Secondary PWM disable
    STCON2 = 0x0004;//PCLKDIV = 4 ==> PWM Source Frequency = 120MHz / 16 = 7.5MHz
    PWMCON1=0;
    PWMCON2=0;
    PWMCON3=0;
    PWMCON4=0;   
    PWMCON5=0;
    PWMCON6=0;
    PWMCON7=0;
     
    
//    PTPER= 100;   //cnt=1 is 1/system clock*2 s  if 60MIPS    = 1/120M s  
//    STPER = 200;
    FCLCON1 = 0x0003; //fail input disable
    FCLCON2 = 0x0003; //fail input disable
    FCLCON3 = 0x0003; //fail input disable
    FCLCON4 = 0x0003; //fail input disable
    FCLCON5 = 0x0003; //fail input disable
    FCLCON6 = 0x0003; //fail input disable    
    
    PWMCON1bits.FLTIEN=0; //fail input interrupt disable
    PWMCON2bits.FLTIEN=0; //fail input interrupt disable   
    PWMCON3bits.FLTIEN=0; //fail input interrupt disable
    PWMCON4bits.FLTIEN=0; //fail input interrupt disable   
    PWMCON5bits.FLTIEN=0; //fail input interrupt disable
    PWMCON6bits.FLTIEN=0; //fail input interrupt disable   
    
    DTR1=ALTDTR1=0;
    PWMCON1bits.DTC=0b10; //Dead disable
    DTR2=ALTDTR2=0;
    PWMCON2bits.DTC=0b10; //Dead disable    
    DTR3=ALTDTR3=0;
    PWMCON3bits.DTC=0b10; //Dead disable    
    DTR4=ALTDTR4=0;
    PWMCON4bits.DTC=0b10; //Dead disable    
    DTR5=ALTDTR5=0;
    PWMCON5bits.DTC=0b10; //Dead disable        
    DTR6=ALTDTR6=0;
    PWMCON6bits.DTC=0b10; //Dead disable           
    
// Set PWM Mode to Independent //
    //ifIOCON1 bit[9:8] can stop PWMH/PWML output,bit[7:6] setting        
    //IOCON1 = 0xcf00; //pwm ctrl PWML&PWMH   //pwmH/L=LOW          
/*    
    IOCON1 = 0xC3A8;
    IOCON2 = 0xCFC9;//0xC3A8;
    IOCON3 = 0xC3A8;
    IOCON4 = 0xC3A8;
    IOCON5 = 0xC3A8;
    IOCON6 = 0xC3A8;
    IOCON7 = 0xC3A8;
*/    
    IOCON1 = 0;
    IOCON2 = 0x8C09;
    IOCON3 = 0x8C09;
    IOCON4 = 0x8C09;
    IOCON5 = 0x8C09;
    IOCON6 = 0x8C09;
    IOCON7 = 0x8C09;    
    
/*Bit15 : PENH = 1 ==> PWMxH, = 0 ==> GPIO                                            //1 //1000 ==> 8
  Bit14 : PENL                                                                        //0
  Bit13 : POLH = 0 ==> PWMHxH Active High, = 1 ==> Active Low                         //0
  Bit12 : POLL = 0 ==> PWMHxL Active High, = 1 ==> Active Low                         //0
  Bit11 : PMOD = 11 ==> True Independent                                              //1 //1100 ==> C
  Bit10 : PMOD = 11 ==> True Independent                                              //1
  Bit9  : OVRENH : 1 ==> Controlled by OVRDAT[1](PWMxH Override Enable)               //0
  Bit8  : OVRENL : 1 ==> Controlled by OVRDAT[0](PWMxL Override Enable)               //0
  Bit7  : OVRDAT : PWMxH Override Data                                                //0 //0000 ==> 0
  Bit6  : OVRDAT : PWMxL Override Data                                                //0
  Bit5  : FLTDAT : PWMxH Fault Override Data                                          //0
  Bit4  : FLTDAT : PWMxL Fault Override Data                                          //0
  Bit3  : CLDAT : PWMxH  Current Limit Override Data                                  //0 //0001 ==> 1
  Bit2  : CLDAT : PWMxL  Current Limit Override Data                                  //0
  Bit1  : SWAP : = 0 ==> Not Swap, 1 ==> Swap, PWMxH(PWMxL) ouput to PWMxL(PWMxH) Pin //0
  Bit0  : OSYNC : 1 ==> Override Sync with PWM Time Base                              //1
 */
/*    
    PWMCON1bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON1bits.MTBS = 0; //pwm clk = PTPER
    PWMCON2bits.MDCS =0;//pwm provide duty define by PDC2(PWMH) SDC2(PWML)
    PWMCON2bits.MTBS = 0; //pwm clk = PTPER    
    PWMCON3bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON3bits.MTBS = 1; //pwm clk = STPER
    PWMCON4bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON4bits.MTBS = 0; //pwm clk = PTPER    
    PWMCON5bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON5bits.MTBS = 1; //pwm clk = STPER
    PWMCON6bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON6bits.MTBS = 0; //pwm clk = PTPER   
*/ 
    PWMCON1bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON1bits.MTBS = 0; //pwm clk = PTPER
    PWMCON2bits.MDCS =0;//pwm provide duty define by PDC2(PWMH) SDC2(PWML)
    PWMCON2bits.MTBS = 0; //pwm clk = PTPER    
    PWMCON3bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON3bits.MTBS = 0; //pwm clk = STPER
    PWMCON4bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON4bits.MTBS = 0; //pwm clk = PTPER    
    PWMCON5bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON5bits.MTBS = 0; //pwm clk = STPER
    PWMCON6bits.MDCS =0;//pwm provide duty define by PDC1(PWMH) SDC1(PWML)
    PWMCON6bits.MTBS = 0; //pwm clk = PTPER         
    
    //SETTING TIMER TO COUNTER PWM PULSE
        
    //change to pwmx-action setting
    //RPINR5bits.T6CKR=RPI81;  //set T6CK pin as PWM1H
    //RPINR5bits.T7CKR=RP80; //set T7CK pin as PWM1L
/*
    _TRISE1=1;//PWM1H
    _TRISE0=1;//PWM1L
    
    _TRISE3=1;//PWM2H
    _TRISE5=1;//PWM3H
    _TRISE7=1;//PWM4H
    _TRISC2=1;//PWM5H
    _TRISC4=1;//PWM6H
*/
    
    _TRISE1=1;//PWM1H
    _TRISE0=1;//PWM1L
    
    _TRISE3=0;//PWM2H
    _TRISE5=0;//PWM3H
    _TRISE7=0;//PWM4H
    _TRISC2=0;//PWM5H
//    _TRISC4=1;//PWM6H

    PTPER = PWM_MAX_PULSE_WIDTH;
    PDC2 = 0;
    PDC3 = 0;
    PDC4 = 0;
    PDC5 = 0;    
    
    //_ANSE1=0;//PWM1H
    //_ANSE0=0;//PWM1L
    //can set timer interrupt to dection pwm pulse
    //TMR7=0;//clear T7 counter pwm1l
    //PR7=0; //Load the period value
    //IPC12bits.T7IP = 0x01; // Set Timer7 Interrupt Priority Level
    //IFS3bits.T7IF = 0; // Clear Timer7 Interrupt Flag    
    //IEC3bits.T7IE = 1; // Enable Timer7 interrupt
    //       T6CON|=0x8006;//T6 enable external clock
    //        T7CON|=0x8040;//0x8002;//T7 enable external clock
    //T7CONbits.TCS=0;
    //T7CONbits.TGATE=1;
    
    PWMCON1 |= 0x0001 ; //real time update Enable
    PWMCON2 |= 0x0001 ; //real time update Enable    
    PWMCON3 |= 0x0001 ; //real time update Enable
    PWMCON4 |= 0x0001 ; //real time update Enable    
    PWMCON5 |= 0x0001 ; //real time update Enable
    PWMCON6 |= 0x0001 ; //real time update Enable        
    
//    IOCON1&=0xfcff;
    PTCON |= 0x8000 ; //PWM Enable
}

/*
void PWM_EN(void)
{
    PTCON &= (~0x8000); //PWM Disable
 //   IOCON1&=0xfcff;
    IOCON2&=0xfcff;
    IOCON3&=0xfcff;
    IOCON4&=0xfcff;
    IOCON5&=0xfcff;
    IOCON6&=0xfcff;
      //  PWMX_dir(0); //pulse dir use this function
    PTCON |= 0x8000 ; //PWM Enable
 //   PDC1 = 50;
    PDC2 = 50;
    PDC3 = 50;
    PDC4 = 50;
    PDC5 = 50;
    PDC6 = 50;

//    SDC1 = 20;
    SDC2 = 20;
    SDC3 = 20;    
    SDC4 = 20;
    SDC5 = 20;
    SDC6 = 20;    
   
}

void PWM_DIS(void)  //set 0 led=off  pwm=L
{
    PTCON &= (~0x8000); //PWM Disable
    IOCON1bits.OVRDAT=0;   
//    IOCON1|=0x0300;//bits.OVRENH=1; //PWM1H disable
    IOCON2|=0x0300;//bits.OVRENH=1; //PWM1H disable    
    IOCON3|=0x0300;//bits.OVRENH=1; //PWM1H disable    
    IOCON4|=0x0300;//bits.OVRENH=1; //PWM1H disable    
    IOCON5|=0x0300;//bits.OVRENH=1; //PWM1H disable        
    IOCON6|=0x0300;//bits.OVRENH=1; //PWM1H disable        
	//IOCON1bits.OVRENL=1; //PWM1L disable
    PTCON |= 0x8000 ; //PWM Enable
}
*/
