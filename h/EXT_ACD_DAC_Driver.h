/* 
 * File:   EXT_ACD_DAC_Driver.h
 * Author: Administrator
 *
 * Created on 2014年12月15日, 下午 7:31
 */

#ifndef EXT_ACD_DAC_DRIVER_H
#define	EXT_ACD_DAC_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

//ad da io define
//ADC TLC3574
#define ADC_FS       _RA2
#define ADC_CS       _RA3
#define ADC_INT      _RA4
#define ADC_CSTART   _RA5
//DAC
#define DAC_CS       _RD9//_RB10//
#define DAC_GA       _RD8
#define DAC_GB       _RA15
#define DAC_RST      _RA14
#define DAC_BTC      _RK11
#define DAC_LDAC     _RK12
#define DAC_POWER    _RB15


//ADC command define
//bit 15~12
#define ADC_CH0              0x0000
#define ADC_CH1              0x1000
#define ADC_CH2              0x2000
#define ADC_CH3              0x3000
#define ADC_WRITE_CFR        0xA000 //bit11~0 below ADC
#define ADC_FIFO_READ        0xE000
#define ADC_HARDWARE_DEFAULT 0xAE00// 0xF000
//bit 11~0
#define  ADC_CFR             0x0800  //must setting 1
#define  ADC_DF_BOB          0x0000  //DATA formate is 0x0000=-10V  0x3fff=10V
#define  ADC_DF_BTC          0x0400  //DATA formate is 2's 0x2000=-10V  0x1fff=10V
#define  L_SAMP              0x0000  //44 clock sampling
#define  S_SAMP              0x0200  //12 clock sampling
#define  INT_OSC             0x0000  //Conversion clock is internal osc
#define  EXT_SCLK            0x0100  //Conversion clock is sclk
#define  SINGLE_MODE         0x0000  //single signal input
#define  DIFF_MODE           0x0080  //differential signal input
#define  OS_MODE             0x0000  //One_Shoot_Mode
#define  R_Mode              0x0020  //Repeat_Mode
#define  S_Mode              0x0040  //Sweep_Mode
#define  R_S_Mode            0x0060  //Repeat_Sweep_Mode
#define  CONVERT_EOC         0x0004
#define  CONVERT_INT         0x0000
#define  ADC_FIFO7           0x0000
#define  ADC_FIFO5           0x0001
#define  ADC_FIFO3           0x0002
#define  ADC_FIFO11          0x0003

//DAC command define   DAC 8734
//DACEWITE
#define DAC_W_CMD      0x00
#define DAC_W_MONITOR  0x01
#define DAC_W_DAC0     0x04
#define DAC_W_DAC1     0x05
#define DAC_W_DAC2     0x06
#define DAC_W_DAC3     0x07
//DAC 0FFSET ADJ REG
#define DAC_W_ADJZ0    0x08  //ADJ 1/8 LSB
#define DAC_W_ADJZ1    0x09
#define DAC_W_ADJZ2    0x0A
#define DAC_W_ADJZ3    0x0B
#define DAC_W_ADJG0    0x0C  //ADJ 1 LSB
#define DAC_W_ADJG1    0x0D
#define DAC_W_ADJG2    0x0E
#define DAC_W_ADJG3    0x0F

//DAC Command reg setting define   Default 0x03 0x03C
#define DAC_CMDH_AB_REG  0x00  // bit15 1:read dac value from latch reg
#define DAC_CMDH_AB_LAT  0x80  //       0:read dac value from dac reG
#define DAC_CMDH_LD_EN   0x40  // bit14 1:AUTO latch update enable
#define DAC_CMDH_LD_DIS  0x00  //       0:latch update disable update by LDAC pin
#define DAC_CMDH_RST_EN  0x20  // bit13 1:software reset
#define DAC_CMDH_RST_DIS 0x00  //       0:reset finish
#define DAC_CMDH_PDA_EN  0x10  // bit12 1:group A power down mode (DAC0 , DAC1)
#define DAC_CMDH_PDA_DIS 0x00  //       0:normal mode
#define DAC_CMDH_PDB_EN  0x08  // bit11 1:group B power down mode (DAC2 , DAC3)
#define DAC_CMDH_PDB_DIS 0x00  //       0:normal mode
//bit10 NOP
#define DAC_CMDH_IO1_H   0x02  // bit9  1:GPIO1 output H (open drain pull up 10K )
#define DAC_CMDH_IO1_L   0x00  //       0:output L
#define DAC_CMDH_IO0_H   0x01  // bit8  1:GPIO0 output H (open drain pull up 10K )
#define DAC_CMDH_IO0_L   0x00  //       0:output L

#define DAC_CMDL_R_EN    0x00  // bit7  0:SDO is SPI MODE
#define DAC_CMDL_R_DIS   0x80  //       1:SDO  no used
//bit6 nop
#define DAC_CMDL_GAIN3X4 0x20  // bit4  1:GAIN x4
#define DAC_CMDL_GAIN3X2 0x00  //       0:GAIN x2
#define DAC_CMDL_GAIN2X4 0x10  // bit4  1:GAIN x4
#define DAC_CMDL_GAIN2X2 0x00  //       0:GAIN x2
#define DAC_CMDL_GAIN1X4 0x08  // bit4  1:GAIN x4
#define DAC_CMDL_GAIN1X2 0x00  //       0:GAIN x2
#define DAC_CMDL_GAIN0X4 0x04  // bit4  1:GAIN x4
#define DAC_CMDL_GAIN0X2 0x00  //       0:GAIN x2


//DAC READ
#define DAC_R_CMD  0x80
#define DAC_R_MONITOR  0x81
#define DAC_R_DAC0     0x84
#define DAC_R_DAC1     0x85
#define DAC_R_DAC2     0x86
#define DAC_R_DAC3     0x87
//DAC 0FFSET ADJ REG
#define DAC_R_ADJZ0    0x88  //ADJ 1/8 LSB
#define DAC_R_ADJZ1    0x89
#define DAC_R_ADJZ2    0x8A
#define DAC_R_ADJZ3    0x8B
#define DAC_R_ADJG0    0x8C  //ADJ 1 LSB
#define DAC_R_ADJG1    0x8D
#define DAC_R_ADJG2    0x8E
#define DAC_R_ADJG3    0x8F


//DAC CTRL setting define
#define UNIPOLAR_MODE       1  // 0~VREF x GAIN
#define BIPOLAR_MODE        0  // -VREF x GAIN /2  ~ VREF x GAIN /2
#define GAUN_GBUN           0  // group A & B is UNIPOLAR_MODE
#define GAB_GBUN            1  // group A is BIPOLAR_MODE , B is UNIPOLAR_MODE
#define GAUN_GBB            2  // group A is UNIPOLAR_MODE & B is BIPOLAR_MODE
#define GAB_GBB             3  // group A & B is BIPOLAR_MODE

#define DAC0_GAIN2          0x0000
#define DAC1_GAIN2          0x0000
#define DAC2_GAIN2          0x0000
#define DAC3_GAIN2          0x0000

#define DAC0_GAIN4          0x0004
#define DAC1_GAIN4          0x0008
#define DAC2_GAIN4          0x0010
#define DAC3_GAIN4          0x0020

#define DAC_DATA_UPDATE_EN  0
#define DAC_DATA_UPDATE_DIS 1
#define DAC_RST_EN          0  //RESET DAC chip
#define DAC_RST_DIS         1
#define DAC_POW_ON   1
#define DAC_POW_OFF  0

#define DAC_CH0 0
#define DAC_CH1 1
#define DAC_CH2 2
#define DAC_CH3 3
//************************************************************************
//void INIT_ADC(void);
//Initial External ADC board
//************************************************************************
void INIT_ADC(void);

//************************************************************************
//unsigned int ADC_GET_VAL(unsigned int ch);
//get adc channel 0~3 data
//unsigned int adc_ch      adc_ch=ADC_CH0 get adc channel 0 data
//                         adc_ch=ADC_CH1 get adc channel 1 data
//                         adc_ch=ADC_CH2 get adc channel 2 data
//                         adc_ch=ADC_CH3 get adc channel 3 data
//************************************************************************
unsigned int ADC_GET_VAL(unsigned int adc_ch);

//************************************************************************
//void INIT_DAC(unsigned char data_pol,unsigned int dac_gain_sel);
//Initial External DAC board
// DAC0 & DAC1 are group A  , DAC2 & DAC3 are group B
//unsigned char data_pol setting DAC output range
// set 0 groupA,B output range = 0~5 X gain
// set 1 groupA output range =-5 x gain/2 ~ +5 x gain/2  groupB output range = 0~5 X gain
// set 2 groupA output range =0~5 X gain                 groupB output range = -5 x gain/2 ~ +5 x gain/2
// set 3 groupA,B output range =  -5 x gain/2 ~ +5 x gain/2
//unsigned int dac_gain_sel set DAC output gain valus
// Example dac_gain_sel =DAC0_GAIN4 | DAC1_GAIN2 | DAC2_GAIN2 | DAC3_GAIN4
//   set DAC0 gain = 4 , DAC1 gain = 2 , DAC2 gain = 2 , DAC3 gain = 4
//************************************************************************
void INIT_DAC(unsigned char data_pol,unsigned int dac_gain_sel);

//************************************************************************
//void SET_DAC_OUTPUT(unsigned char dac_ch_num,unsigned int dac_data);
//unsigned char dac_ch_num  setting DAC channel select range : 0~3
//unsigned int dac_data setting DAC channel data value ; if init dac = 0~5 X gain         -> rang : 0~0xffff(0~65535)
//                                                       if init dac = -5 X gain~5 X gain -> rang : 0x8000~0x7fff(-32768~32767)
//************************************************************************
void SET_DAC_OUTPUT(unsigned char dac_ch_num,unsigned int dac_data);

//************************************************************************
//unsigned int GET_DAC_OUTPUT_DATA(unsigned char dac_ch_num);
//get now dac setting value
//unsigned char read_dac_ch_num   setting get dac channel number range : 0~3
//************************************************************************
unsigned int GET_DAC_OUTPUT_DATA(unsigned char read_dac_ch_num);

//************************************************************************
//unsigned int DAC_REG_RW(unsigned char reg , unsigned int wdata);
//DAC detail setting used
//unsigned char reg    setting DAC register address
//unsigned int wdata   setting DAC value 
//************************************************************************
unsigned int DAC_REG_RW(unsigned char reg , unsigned int wdata);


#ifdef	__cplusplus
}
#endif

#endif	/* EXT_ACD_DAC_DRIVER_H */

