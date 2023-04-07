#include "..\h\Global_define.h"
#include "..\h\Encoder_Driver.h"


void INIT_QEIX(unsigned int reg1,unsigned int reg2,unsigned int reg3) //QEI1
{
    QEI1CON = 0;  //QEI1 disable
    RPINR14bits.QEA1R = QEIX_A_SEL;//RG15//select QEI1 pulse A Pin
    RPINR14bits.QEB1R = QEIX_B_SEL;	//RG13//select QEI1 pulse B Pin
//    RPINR15bits.INDX1R = QEIX_INDEX_SEL;//RA6 : RPI22//select QEI1 pulse Index Pin
//    RPINR15bits.HOME1R = QEIX_HOME_SEL;//RG1 : RP113//select QEI1 pulse Home Pin
//    _TRISA6=1;
//Philip 20181211 01         _TRISG15=1;//QEIX_A
//Philip 20181211 01         _TRISG13=1;//QEIX_B
    _TRISG14=1;//QEIX_B   
//    _TRISG12=1;  
    _TRISA7 = 1;//QEIX_A
//    _TRISG1=1;//QEI_X_HOME
//    _ANSA6=0;//QEI_X_INDEX  //rpi22 is digital input
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
    
    POS1CNTL = 0; //counter low byte
    POS1CNTH = 0; //counter high byte
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
//    RPINR17bits.INDX2R = QEIY_INDEX_SEL;//select QEI1 pulse Index Pin
//    RPINR17bits.HOME2R = QEIY_HOME_SEL;	//select QEI1 pulse Home Pin
//    _TRISA7=1;
//Philip 20181211 01     _TRISG14=1;
//Philip 20181211 01     _TRISG12=1;
    _TRISG13=1;//QEIX_A//Philip 20181211 01
    _TRISG15=1;//QEIX_B//Philip 20181211 01 
     
    
//    _TRISG0=1;
//    _ANSA7=0;  //rpi23 is digital input
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
    QEI2GECH = 0;
    QEI2ICL = 0;  //20141120 modify
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
unsigned long GET_ENCX(void)
{
    unsigned long cntx=0;
    cntx = POS1CNTH;
    cntx = (cntx<<16) | POS1CNTL; //counter low byte
//    POS1HLD = 0;
//    POS1CNTH = 0;
//    POS1CNTL = 0;
    return cntx;
}

unsigned long GET_ENCY(void)
{
    unsigned long cnty=0;
    cnty = POS2CNTH;
    cnty = (cnty<<16) | POS2CNTL; //counter low byte
//    POS2HLD = 0;
//    POS2CNTH = 0;
//    POS2CNTL = 0;
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

unsigned char get_limit_x1(void)
{
    if(LIMITX1==LIMIT_CLOSE)
        return 1;
    else
        return 0;
}
unsigned char get_limit_x2(void)
{
    if(LIMITX2==LIMIT_CLOSE)
        return 1;
    else
        return 0;
}

unsigned char get_limit_y1(void)
{
    if(LIMITY1==LIMIT_CLOSE)
        return 1;
    else
        return 0;
}
unsigned char get_limit_y2(void)
{
    if(LIMITY2==LIMIT_CLOSE)
        return 1;
    else
        return 0;
}

long GetEncoderY_Value(void)
{
    long value;
    unsigned long EncoderValueH, EncoderValueL;

    EncoderValueH = POS2CNTH;
    EncoderValueL = POS2CNTL;
    value = (long)((EncoderValueH<<16) | EncoderValueL); //counter low byte    
    
    return value;
}

void ClearEncoderY_Value(void)
{
    POS2CNTH = 0;
    POS2CNTL = 0;
}