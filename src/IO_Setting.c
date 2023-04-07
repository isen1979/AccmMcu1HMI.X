#include "..\h\Global_define.h"
#include "..\h\Ext_ACD_DAC_Driver.h"
#define SPI_MASTER      1
#define SPI_SLAVE	0
#define SPI1_MODE	SPI_MASTER





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
    //PORTB |= 0x8400;

    //RB8 set ctrl rx enable
    _ANSB8=0;
    _TRISB8=0;
    //_RB8=1;  //1 adc & sac used   0 extio used
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
    _RB8=0;
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
    _RB8=0;
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
    _RB8=0;
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
    RCFGCAL=0x9700;  // enable RTC & disable RTC write
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









