#include "..\h\Global_define.h"
#include "..\h\EXT_ACD_DAC_Driver.h"
#include "..\h\SystemControl.h"

#define ADC_TIME_OUT_COUNT 2
extern unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];

void INIT_ADC(void)
{
    unsigned adc_delay=0;
    _TRISA2=0;
    _TRISA4=1;
    _TRISA5=0;
    ADC_FS=1;
    ADC_INT=1;
    ADC_CSTART=1;
    _TRISB15=0; //DAC_POWER
    _ANSB15=0;
    DAC_POWER=DAC_POW_ON;
    if(SPI1STATbits.SPIEN==0) //spi1 was uninitial
    {
        INIT_SPI1();
        SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 0;
        //SPI1CON1bits.SPRE = 0;		//Secondary prescale   7~0 ->  1:1~8
        SPI1CON1bits.PPRE = 1;//1 sclk 7.5m ;//2 sclk=15Mbps
        SPI1CON1bits.MODE16 = 1; //16 bit mode
        SPI1STATbits.SPIEN = 1; //SPI enable
    }
    else                      //spi1 was ininial
    {
        if(SPI1CON1bits.CKE==1)//check edge setting
        {
            SPI1STATbits.SPIEN = 0; //SPI disable
            SPI1CON1bits.CKE = 0;
            SPI1CON1bits.PPRE = 1;//sclk=15Mbps
            SPI1CON1bits.MODE16 = 1; //16 bit mode
            SPI1STATbits.SPIEN = 1; //SPI enable
        }
    }
    //init tlc3574
    ADC_CS=SPI_CS_EN;
    spi1_txrx16(ADC_WRITE_CFR);
    ADC_CS=SPI_CS_DIS;
    
    //delay_ns(100);  delay 100ns
    for(adc_delay=0;adc_delay<3;adc_delay++);//1 machine cycle 33nS

    ADC_CS=SPI_CS_EN;
    spi1_txrx16(ADC_HARDWARE_DEFAULT);
    ADC_CS=SPI_CS_DIS;
     asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}

unsigned int ADC_GET_VAL(unsigned int acd_ch)
{
    unsigned int val=0;
    //_RB8=1;
    if(SPI1CON1bits.CKE==1)//check edge setting
    {
        SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 0;
        SPI1CON1bits.PPRE = 1;//2;//sclk=15Mbps
        SPI1CON1bits.MODE16 = 1; //16 bit mode
        SPI1STATbits.SPIEN = 1; //SPI enable
    }
    acd_ch = acd_ch << 12;
    ADC_CS=SPI_CS_EN;
    val=spi1_txrx16(acd_ch);
    //spi1_txrx16(0);//wait sample 48 sclk
    //spi1_txrx16(0);
    DelayTimerCounter[DAC_TimeOut_CounterEnum] = ADC_TIME_OUT_COUNT;
    while(ADC_INT==1)
    {
        if( DelayTimerCounter[DAC_TimeOut_CounterEnum] == 0 )
            break;
    } //wait adc convert finish
    ADC_CS=SPI_CS_DIS;
    asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
    ADC_CS=SPI_CS_EN;
    val=spi1_txrx16(acd_ch);//get adc values
   // spi1_txrx16(0);//wait sample 48 sclk
   // spi1_txrx16(0);
    DelayTimerCounter[DAC_TimeOut_CounterEnum] = ADC_TIME_OUT_COUNT;
    while(ADC_INT==1)
    {
        if( DelayTimerCounter[DAC_TimeOut_CounterEnum] == 0 )
            break;        
     
    }//wait adc convert finish
    ADC_CS=SPI_CS_DIS;
    val=(val&0xfffc)>>2;
    //val=val&0x3fff;
    return val;
}

unsigned int UNSYNC_ADC_GET_VAL(unsigned int acd_ch)
{
    unsigned int val=0;
    //_RB8=1;
    if(SPI1CON1bits.CKE==1)//check edge setting
    {
        SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 0;
        SPI1CON1bits.PPRE = 1;//2;//sclk=15Mbps
        SPI1CON1bits.MODE16 = 1; //16 bit mode
        SPI1STATbits.SPIEN = 1; //SPI enable
    }    
    ADC_CS=SPI_CS_EN;
    val=spi1_txrx16(acd_ch);//get adc values
    ADC_CS=SPI_CS_DIS;
    val=(val&0xfffc)>>2;
    //val=val&0x3fff;
    return val;
}


unsigned int DAC_REG_RW(unsigned char reg , unsigned int wdata)
{
    unsigned int rdata=0;
    //_RB8=1;
    asm("nop");asm("nop");asm("nop");
    DAC_CS=SPI_CS_EN;
    asm("nop");asm("nop");asm("nop");
    if((reg&0x80)==0x80)
    {
        spi1_txrx(reg); //read mode
        spi1_txrx(0);
        spi1_txrx(0);
    }
    else
    {
        spi1_txrx(reg&0x7f); //write mode
        spi1_txrx(((wdata&0xff00)>>8));//send wdata high byte
        spi1_txrx(wdata&0x00ff); //send wdata low byte
    }
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");    
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop"); 
    DAC_CS=SPI_CS_DIS;
    //PORTB |= 0x8400;

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
        asm("nop");asm("nop");asm("nop");
        asm("nop");asm("nop");asm("nop");
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");   
        asm("nop");asm("nop");asm("nop");   
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");       
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");   
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");   
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop");    
        asm("nop");asm("nop");asm("nop"); 
        DAC_CS=SPI_CS_DIS;
        //PORTB |= 0x8400;
        asm("nop");asm("nop");asm("nop");
    }
    return rdata;
 //    asm("nop");asm("nop");
//    DAC_LDAC= DAC_DATA_UPDATE_EN;
//    asm("nop");asm("nop");
//    DAC_LDAC= DAC_DATA_UPDATE_DIS;
}
unsigned int GET_DAC_OUTPUT_DATA(unsigned char read_dac_ch_num)
{
    unsigned int dac_read_data=0;
    //_RB8=1;
    asm("nop");asm("nop");asm("nop");
    DAC_CS=SPI_CS_EN;
    asm("nop");asm("nop");asm("nop");
    switch(read_dac_ch_num)
    {
        case 0:
            spi1_txrx(DAC_R_DAC0); //write mode
        break;
        case 1:
            spi1_txrx(DAC_R_DAC1); //write mode
        break;
        case 2:
            spi1_txrx(DAC_R_DAC2); //write mode
        break;
        case 3:
            spi1_txrx(DAC_R_DAC3); //write mode
        break;
    }
    spi1_txrx(0);//send wdata high byte
    spi1_txrx(0); //send wdata low byte
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");    
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop"); 
    DAC_CS=SPI_CS_DIS;
    //PORTB |= 0x8400;

    //send dummy data
    asm("nop");asm("nop");asm("nop");
    DAC_CS=SPI_CS_EN;
    asm("nop");asm("nop");asm("nop");
    spi1_txrx(0);
    dac_read_data = spi1_txrx(0);
    dac_read_data=dac_read_data<<8;
    dac_read_data |= spi1_txrx(0); //ALL dac gain is x2
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");    
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop"); 
    DAC_CS=SPI_CS_DIS;
    //PORTB |= 0x8400;
    asm("nop");asm("nop");asm("nop");
    return dac_read_data;
}
void SET_DAC_OUTPUT(unsigned char dac_ch_num,unsigned int dac_data)
{
    //_RB8=1;
    asm("nop");asm("nop");asm("nop");
    DAC_CS=SPI_CS_EN;
    asm("nop");asm("nop");asm("nop");
    switch(dac_ch_num)
    {
        case 0:
            spi1_txrx(DAC_W_DAC0); //write mode
        break;
        case 1:
            spi1_txrx(DAC_W_DAC1); //write mode
        break;
        case 2:
            spi1_txrx(DAC_W_DAC2); //write mode
        break;
        case 3:
            spi1_txrx(DAC_W_DAC3); //write mode
        break;
    }
    spi1_txrx(((dac_data&0xff00)>>8));//send wdata high byte
    spi1_txrx(dac_data&0x00ff); //send wdata low byte
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");    
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");       
    DAC_CS=SPI_CS_DIS;
    //PORTB |= 0x8400;

    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop");
    asm("nop");asm("nop");asm("nop"); 
}

void INIT_DAC(unsigned char data_pol,unsigned int dac_gain_sel)
{
    if(SPI1STATbits.SPIEN==0) //spi1 was uninitial
    {
        INIT_SPI1();
        SPI1STATbits.SPIEN = 0; //SPI disable
        SPI1CON1bits.CKE = 0;
        SPI1CON1bits.SPRE =2;  //0~7=div8~1
        SPI1CON1bits.PPRE = 2;//3;//1;//sclk=4Mbps
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
   DAC_REG_RW(DAC_W_CMD,(0x0300 | dac_gain_sel) );
   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
}

unsigned int LastDAC_Value=0xFFFF;
void Inverter_Control_By_DAC(unsigned int Speed)
{
    unsigned long LongDAC_Value, temp1;
    unsigned int DAC_Value;
    temp1 = Speed;
    LongDAC_Value = 65535 * temp1 / 480;
    LongDAC_Value = LongDAC_Value + 5;
    LongDAC_Value = LongDAC_Value / 10;
    DAC_Value = LongDAC_Value;
    if(LastDAC_Value != DAC_Value)
    {
        LastDAC_Value = DAC_Value; 
    }
}
