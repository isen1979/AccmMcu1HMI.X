#include "..\h\Global_define.h"
#include "..\h\IO_Driver.h"
void INIT_IOPORT(void)
{
	
    ANSELD=0x0; //PortD are Digital Ports.
    //PORTH all are digital   
	//PORTJ all are digital
//Input Port :
/*
 * RD0 - RD7 ==> IN0 - IN7
 * RH8 - RH15 ==> IN8 - IN15
 */	
    
/*
 * RH0 - RH7 ==> DO0- DO7
 * RJ8 - RJ15 ==> DO8 - DO15
 */    
    TRISA = 0x39C3;//RA1(UART3RX),2-5(NC),6(S1_QEI2_INDEX),7(S1_QEI1_PA),8(X),9-10(NC),11-13,14-15((NC) are input ports.
    ANSELA = 0;//All ports are digital ports.//RA6 and RA7 is not analog input.// &= ~0x0C0;    

//Axis Y Motor Moving Signal Output : SPI_M1_CS ==> Moving Singal Output(RB14)
//    TRISB = 0xFFFF;//RB0-1(NC),2-5,6-7(X),8-13(NC),14(SPI_M3_CS),15(NC) are input ports.//|= 0x004D;
    TRISB = 0x18ED;//RB0-1(NC),2-5,6-7(X),8-13(NC),14(Y Axis Moving Signal),15(NC) are input ports.//|= 0x004D;    
//    TRISB &= ~0x0F3F;//RB0 - RB11 are output ports, except RG6, RG7.
    ANSELB = 0;//All ports are digital ports.//RB0-RB5 and RB8 - RB11 are digital// &= ~0x0F3F
    
    TRISC = 0xFFE1;//RC0(X),1-4,5-11(X),12(NC),13-14(OSC),15(NC) are input ports.//&= 0xFFF5;
    ANSELC = 0;//All of ports are output ports.&= 0xFFF5;      
    
    TRISD = 0xFCFF; //RD0(S3_Get_Position_R),1(S3_Start_Run),2(S3_Motor_Rotate_X2_R),3(S3_Motor_Rotate_Z2_R),4(workin_YA_S3),5(workin_XZ_S3),
                    //6(workout_67_S3),7(workout_89_S3),8-11(NC),12(S3_SERVO_ALM2),13(S3_SERVO_ALM1),14(S3_UART1_RX),15(S3_UART1_TX) are input ports.//INTPUT 0~7, RD12,RD13 == Servo Alarm2, Servo Alarm1(Input)//0x30ff;
//    TRISD &= ~0x0F00;//RD8 - RD11 are output ports
    ANSELD = 0;//All of ports are digital ports.//&= ~0x3FFF;
    
    TRISE = 0xFF00;//,4-7(NC),8-9,10-15(X) are input ports.    
    ANSELE = 0;//     
    
    TRISF = 0xFFFF;//RF0-1(NC),2(SPI_Ethernet_CLK),3(SPI_Ethernet_DI),6-7(X),8(PI_Ethernet_DO),9-11(X),12(NC),13(S3_UART3_TX),14-15(X) are input ports.// &= ~0x0003;
    TRISF = 0;//4(S3_I2C_DA) and 5(S3_I2C_CLK) are output ports.

    TRISG = 0xFFFF;//RG0(S1_QEI1_HOME),1(S1_QEI2_HOME),2-3(NC),4-5(X),6-9(NC),10-11(X),12(S1_QEI1_INDEX),13(S1_QEI2_PA),14(S1_QEI1_PB),15(S1_QEI2_PB) are input ports.//&= ~0x03C0;
    ANSELG = 0;//All of ports are digital ports.//&= ~0x03C3;    
    
    TRISH = 0xFF00;//RH0-7 is output ports, RH8-15 is input ports;
    
    TRISJ = 0x00F0;//RJ4(S2_LIMIT_Y2),5(S2_LIMIT_Y1),6(S2_LIMIT_X2),7(S2_LIMIT_X1),8-15 are output ports. 

}
void enable_ext_interrupt(unsigned char int_num,unsigned char trigger_edge)
{
    switch(int_num)
    {
        case EXT_INT0:
            IFS0bits.INT0IF = 0;    /*Reset INT0 interrupt flag */
            IEC0bits.INT0IE = 1;    /*Enable INT0 Interrupt Service Routine */
            INTCON2bits.INT0EP=trigger_edge;  //INT_RISE_EDGE
        break;
        case EXT_INT1:
            RPINR0bits.INT1R=RP65; //setting INT1=RD1
            IFS1bits.INT1IF = 0;    /*Reset INT1 interrupt flag */
            IEC1bits.INT1IE = 1;    /*Enable INT1 Interrupt Service Routine */
            INTCON2bits.INT1EP=trigger_edge;  //INT_RISE_EDGE
        break;
        case EXT_INT2:
            RPINR1bits.INT2R=RP66; //setting INT2=RD2
            IFS1bits.INT2IF = 0;    /*Reset INT0 interrupt flag */
            IEC1bits.INT2IE = 1;    /*Enable INT0 Interrupt Service Routine */
            INTCON2bits.INT2EP=trigger_edge;  //INT_RISE_EDGE
        break;
        case EXT_INT3:
            RPINR1bits.INT3R=RP67; //setting INT3=RD3
            IFS3bits.INT3IF = 0;    /*Reset INT1 interrupt flag */
            IEC3bits.INT3IE = 1;    /*Enable INT1 Interrupt Service Routine */
            INTCON2bits.INT3EP=trigger_edge;  //INT_RISE_EDGE
        break;
        case EXT_INT4:
            RPINR2bits.INT4R=RP68; //setting INT4=RD4
            IFS3bits.INT4IF = 0;    /*Reset INT1 interrupt flag */
            IEC3bits.INT4IE = 1;    /*Enable INT1 Interrupt Service Routine */
            INTCON2bits.INT4EP=trigger_edge;  //INT_RISE_EDGE
        break;
    }
}
void enable_capture_timebace(unsigned char cap_timer_num)
{
       switch(cap_timer_num)
       {
          // case INPUT_CAPTURE1_8:
          //     IC1CON1 = IC2CON1 = IC3CON1 = IC4CON1 = IC5CON1 = IC6CON1 = IC7CON1 = IC8CON1 = 0x1001;
          //     IC1CON2 = IC2CON2 = IC3CON2 = IC4CON2 = IC5CON2 = IC6CON2 = IC7CON2 = IC8CON2 = 0;
          // break;
           case INPUT_CAPTURE1:
               IC1CON1bits.ICSIDL = 0;  // Input capture will continue to operate in CPU idle mode
               IC1CON1bits.ICTSEL =0b100;//timer 1 is source      0b111; // system clock source for the IC1 module
               IC1CON1bits.ICI = 0;  // Interrupt on every capture event
               IC1CON1bits.ICBNE = 0; // Input capture is empty
               IC1CON1bits.ICM = 0b001;//Capture mode every rising & falling edge (Prescaler Capture mode)
               IC1CON2bits.IC32 = 0;  // Cascade module operation is disabled
               IC1CON2bits.ICTRIG = 0; // Input source used to synchronize the input capture timer of
               // another module (Synchronization mode) IC1CON2bits.TRIGSTAT = 0; // IC1TMR has not been triggered and is being held clear
               IC1CON2bits.SYNCSEL = 0; // No Sync or Trigger source for the IC1 module
           break;
           case INPUT_CAPTURE2:
               IC2CON1 = 0x1001;
               IC2CON2 = 0;
           break;
           case INPUT_CAPTURE3:
               IC3CON1=0x1001;
               IC3CON2 = 0;
           break;
           case INPUT_CAPTURE4:
               IC4CON1=0x1001;
               IC4CON2 = 0;
           break;
           case INPUT_CAPTURE5:
               IC5CON1 = 0x1001;
               IC5CON2 = 0;
           break;
           case INPUT_CAPTURE6:
               IC6CON1 = 0x1001;
               IC6CON2 = 0;
           break;
           case INPUT_CAPTURE7:
               IC7CON1 = 0x1001;
               IC7CON2 = 0;
           break;
           case INPUT_CAPTURE8:
               IC8CON1 = 0x1001;
               IC8CON2 = 0;
           break;
       }
}
void enable_capture_io(unsigned char capture_num)
{
    unsigned char capture_nct=0,capture_loop=0;
    if(capture_num==INPUT_CAPTURE1_8)
        capture_loop=8;
    for(capture_nct=0;capture_nct<capture_loop;capture_nct++)
    {
        switch(capture_num)
        {
            case INPUT_CAPTURE1:
                RPINR7bits.IC1R=RP64;  //capture1 =RD0
                IFS0bits.IC1IF = 0; // Clear the IC1 interrupt status flag
                IEC0bits.IC1IE = 1; // Enable IC1 interrupts
                IPC0bits.IC1IP = 1; // Set module interrupt priority as 1
                enable_capture_timebace(INPUT_CAPTURE1);
            break;

            case INPUT_CAPTURE2:
                RPINR7bits.IC2R=RP65;  //capture2 =RD1
                IFS0bits.IC2IF = 0; // Clear the IC2 interrupt status flag
                IEC0bits.IC2IE = 1; // Enable IC2 interrupts
                IPC1bits.IC2IP = 1; // Set module interrupt priority as 1
                enable_capture_timebace(INPUT_CAPTURE2);
            break;

            case INPUT_CAPTURE3:
                RPINR8bits.IC3R=RP66;  //capture3 =RD2
                IFS2bits.IC3IF = 0; // Clear the IC3 interrupt status flag
                IEC2bits.IC3IE = 1; // Enable IC3 interrupts
                IPC9bits.IC3IP = 1; // Set module interrupt priority as 1
                enable_capture_timebace(INPUT_CAPTURE3);

            break;

            case INPUT_CAPTURE4:
                RPINR8bits.IC4R=RP67;  //capture4 =RD3
                IFS2bits.IC4IF = 0; // Clear the IC3 interrupt status flag
                IEC2bits.IC4IE = 1; // Enable IC3 interrupts
                IPC9bits.IC4IP = 1; // Set module interrupt priority as 1
                enable_capture_timebace(INPUT_CAPTURE4);
            break;

            case INPUT_CAPTURE5:
                RPINR9bits.IC5R=RP68;  //capture5 =RD4
                IFS2bits.IC5IF = 0; // Clear the IC3 interrupt status flag
                IEC2bits.IC5IE = 1; // Enable IC3 interrupts
                IPC9bits.IC5IP = 1; // Set module interrupt priority as 1
                enable_capture_timebace(INPUT_CAPTURE5);
            break;

            case INPUT_CAPTURE6:
                RPINR9bits.IC6R=RP69;  //capture6 =RD5
                IFS2bits.IC6IF = 0; // Clear the IC3 interrupt status flag
                IEC2bits.IC6IE = 1; // Enable IC3 interrupts
                IPC10bits.IC6IP = 1; // Set module interrupt priority as 1
                enable_capture_timebace(INPUT_CAPTURE6);
            break;

            case INPUT_CAPTURE7:
                RPINR10bits.IC7R=RP70;  //capture7 =RD6
                IFS1bits.IC7IF = 0; // Clear the IC3 interrupt status flag
                IEC1bits.IC7IE = 1; // Enable IC3 interrupts
                IPC5bits.IC7IP = 1; // Set module interrupt priority as 1
                enable_capture_timebace(INPUT_CAPTURE7);
          break;

            case INPUT_CAPTURE8:
                RPINR10bits.IC8R=RP71;  //capture8 =RD7
                IFS1bits.IC8IF = 0; // Clear the IC3 interrupt status flag
                IEC1bits.IC8IE = 1; // Enable IC3 interrupts
                IPC5bits.IC8IP = 1; // Set module interrupt priority as 1
                enable_capture_timebace(INPUT_CAPTURE8);
            break;
        }
    }
}
unsigned int get_total_input_status(void)
{
	//input 0~7  = RD0~7
	//input 8~15 = RH8~15
	unsigned int port_value=0;
	port_value=~((PORTD&0x00ff)|(PORTH&0xff00));
	return port_value;
}

void Set_Output_bit_Status(unsigned char bitnum)
{
    switch(bitnum)
    {
        case 0 :
            D_OUT0 = 1;
            break;
        case 1 :
            D_OUT1 = 1;
            break;
        case 2 :
            D_OUT2 = 1;
            break;
        case 3 :
            D_OUT3 = 1;
            break;
        case 4 :
            D_OUT4 = 1;
            break;
        case 5 :
            D_OUT5 = 1;
            break;     
        case 6 :
            D_OUT6 = 1;
            break;
        case 7 :
            D_OUT7 = 1;
            break;
        case 8 :
            D_OUT8 = 1;
            break;
        case 9 :
            D_OUT9 = 1;
            break;
        case 10 :
            D_OUT10 = 1;
            break;
        case 11 :
            D_OUT11 = 1;
            break;     
        case 12 :
            D_OUT12 = 1;
            break;
        case 13 :
            D_OUT13 = 1;
            break;    
        case 14 :
            D_OUT14 = 1;
            break;
        case 15 :
            D_OUT15 = 1;
            break;                
    }
    asm("nop");asm("nop");    
}

void Clear_Output_bit_Status(unsigned char bitnum)
{
    switch(bitnum)
    {
        case 0 :
            D_OUT0 = 0;
            break;
        case 1 :
            D_OUT1 = 0;
            break;
        case 2 :
            D_OUT2 = 0;
            break;
        case 3 :
            D_OUT3 = 0;
            break;
        case 4 :
            D_OUT4 = 0;
            break;
        case 5 :
            D_OUT5 = 0;
            break;     
        case 6 :
            D_OUT6 = 0;
            break;
        case 7 :
            D_OUT7 = 0;
            break;
        case 8 :
            D_OUT8 = 0;
            break;
        case 9 :
            D_OUT9 = 0;
            break;
        case 10 :
            D_OUT10 = 0;
            break;
        case 11 :
            D_OUT11 = 0;
            break;     
        case 12 :
            D_OUT12 = 0;
            break;
        case 13 :
            D_OUT13 = 0;
            break;    
        case 14 :
            D_OUT14 = 0;
            break;
        case 15 :
            D_OUT15 = 0;
            break;                
    }
    asm("nop");asm("nop");    
}

void InverseOutPutBit(unsigned char id)
{
    switch(id)
    {
        case 0 :
            _LATH0 = ~_LATH0;  
            break;
        case 1 :
            _LATH1 = ~_LATH1;
            break;
        case 2 :
            _LATH2 = ~_LATH2;    
            break;
        case 3 :
            _LATH3 = ~_LATH3;
            break;
        case 4 :
            _LATH4 = ~_LATH4;    
            break;
        case 5 :
            _LATH5 = ~_LATH5;
            break;
        case 6 :
            _LATH6 = ~_LATH6;    
            break;
        case 7 :
            _LATH7 = ~_LATH7;
            break;
        case 8 :
            _LATJ8 = ~_LATJ8;
            break;
        case 9 :
            _LATJ9 = ~_LATJ9;
            break;
        case 10 :
            _LATJ10 = ~_LATJ10;
            break;
        case 11 :
            _LATJ11 = ~_LATJ11;    
            break;
        case 12 :
            _LATJ12 = ~_LATJ12;
            break;
        case 13 :
            _LATJ13 = ~_LATJ13;    
            break;
        case 14 :
            _LATJ14 = ~_LATJ14;    
            break;
        case 15 :
            _LATJ15 = ~_LATJ15;
            break;              
    }
}


void InverseOutput(void)
{
    _LATH0 = ~_LATH0;
    _LATH1 = ~_LATH1;
    _LATH2 = ~_LATH2;
    _LATH3 = ~_LATH3;
    _LATH4 = ~_LATH4;
    _LATH5 = ~_LATH5;
    _LATH6 = ~_LATH6;
    _LATH7 = ~_LATH7;
    
    _LATJ8 = ~_LATJ8;
    _LATJ9 = ~_LATJ9;
    _LATJ10 = ~_LATJ10;
    _LATJ11 = ~_LATJ11;
    _LATJ12 = ~_LATJ12;
    _LATJ13 = ~_LATJ13;
    _LATJ14 = ~_LATJ14;
    _LATJ15 = ~_LATJ15;
}


