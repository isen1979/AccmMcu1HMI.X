/* 
 * File:   IO_Driver.h
 * Author: Administrator
 *
 * Created on 2014年12月15日, 上午 9:39
 */

#ifndef IO_DRIVER_H
#define	IO_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

//Input Port Setting
#define D_IN0  _RD0
#define D_IN1  _RD1
#define D_IN2  _RD2
#define D_IN3  _RD3
#define D_IN4  _RD4
#define D_IN5  _RD5
#define D_IN6  _RD6
#define D_IN7  _RD7

#define D_IN8  _RH8
#define D_IN9  _RH9
#define D_IN10 _RH10
#define D_IN11 _RH11
#define D_IN12 _RH12
#define D_IN13 _RH13
#define D_IN14 _RH14
#define D_IN15 _RH15     

#define X1  _RH0
#define X2  _RH1
#define X3  _RH2
#define X4  _RH3
#define X5  _RH4
#define X6  _RH5
#define X7  _RH6
#define X8  _RH7
#define X9  _RH8
#define X10 _RH9
#define X11 _RH10
#define X12 _RH11
#define X13 _RH12
#define X14 _RH13
#define X15 _RH14
#define X16 _RH15       
#define X17 _RJ0
#define X18 _RJ1
#define X19 _RJ2
#define X20 _RJ3
#define X21 _RJ4
#define X22 _RJ5
#define X23 _RJ6
#define X24 _RJ7
#define X25 _RJ8
#define X26 _RJ9
#define X27 _RJ10
#define X28 _RJ11
#define X29 _RJ12
#define X30 _RJ13
#define X31 _RJ14
#define X32 _RJ15     
#define X33 _RD0
#define X34 _RD1
#define X35 _RD2
#define X36 _RD3
#define X37 _RD4
#define X38 _RD5
#define X39 _RG2//_RD6
#define X40 _RG3//_RD7

    
//Output Port    
#define D_OUT0  _RH0
#define D_OUT1  _RH1
#define D_OUT2  _RH2
#define D_OUT3  _RH3
#define D_OUT4  _RH4
#define D_OUT5  _RH5
#define D_OUT6  _RH6
#define D_OUT7  _RH7
   
#define D_OUT8  _RJ8
#define D_OUT9  _RJ9
#define D_OUT10 _RJ10
#define D_OUT11 _RJ11
#define D_OUT12 _RJ12
#define D_OUT13 _RJ13
#define D_OUT14 _RJ14
#define D_OUT15 _RJ15

#define Y1 _LATA4//_RA4  
#define Y2 _LATA5//_RA5      
#define Y3 _LATA6//_RA6      
#define Y4 _LATA7//_RA7              
#define Y5 _LATC1//_RC1
#define Y6 _LATC3//_RC3   
#define Y7 _LATG6//_RG6     
#define Y8 _LATG7//_RG7   
#define Y9 _LATG8//_RG8     
#define Y10 _LATG9//_RG9     
#define Y11 _LATE8//_RE8
#define Y12 _LATE9//_RE9      
#define Y13 _LATK0//_RK0  
#define Y14 _LATK1//_RK1      
#define Y15 _LATB5//_RB5      
#define Y16 _LATB4//_RB4              
#define Y17 _LATB0//_RB0
#define Y18 _LATB1//_RB1   
#define Y19 _LATB2//_RB2     
#define Y20 _LATB3//_RB3  
#define Y21 _LATB8//_RB8     
#define Y22 _LATB9//_RB9     
#define Y23 _LATB10//_RB10
#define Y24 _LATB11//_RB11     
#define Y25 _LATG0//_RG0   
#define Y26 _LATG1//_RG1   
#define Y27 _LATD6//_RD6//_RG2     
#define Y28 _LATD7//_RD7//_RE3
#define Y29 _LATD12//_RD12     
#define Y30 _LATD13//_RD13  
#define Y31 _LATF0//_RF0   
#define Y32 _LATF1//_RF1     
    
    
    

#define INT0_EN DISABLE //ENABLE
#define INT1_EN DISABLE //ENABLE
#define INT2_EN DISABLE //ENABLE
#define INT3_EN DISABLE //ENABLE
#define INT4_EN DISABLE //ENABLE

//trigger edge
#define INT_FALL_EDGE 1
#define INT_RISE_EDGE 0

//external interrupt selsct
#define EXT_INT0        0   //setting input 0 to external interrupt input 0
#define EXT_INT1        1   //setting input 1 to external interrupt input 1
#define EXT_INT2        2   //setting input 2 to external interrupt input 2
#define EXT_INT3        3   //setting input 3 to external interrupt input 3
#define EXT_INT4        4   //setting input 4 to external interrupt input 4


#define INPUT_CAPTURE1  1   //setting input 0 to capture input 1
#define INPUT_CAPTURE2  2   //setting input 1 to capture input 2
#define INPUT_CAPTURE3  3   //setting input 2 to capture input 3
#define INPUT_CAPTURE4  4   //setting input 3 to capture input 4
#define INPUT_CAPTURE5  5   //setting input 4 to capture input 5
#define INPUT_CAPTURE6  6   //setting input 5 to capture input 6
#define INPUT_CAPTURE7  7   //setting input 6 to capture input 7
#define INPUT_CAPTURE8  8   //setting input 7 to capture input 8
#define INPUT_CAPTURE1_8  0   //setting input 0~7 to capture input 1~8
#define CAPTURE_TIMER_T1 

//************************************************************************
//void set_single_output_port(unsigned char num,unsigned char value); 
//setting one output port
//unsigned char num : output number select    range : 0~15                (Output0~15)
//unsigned char value :output status setting  range : OUTPUT_H / OUTPUT_L (ON/OFF)
//************************************************************************
//void set_single_output_port(unsigned char num,unsigned char value);

//************************************************************************
//void set_output_port(unsigned int value);
//setting all output port
//unsigned int value : output status setting    range : 0~0xffff  1=OUTPUT_H  0=OUTPUT_L
//************************************************************************
//void set_output_port(unsigned int value);

//************************************************************************
//unsigned char get_single_input_status(unsigned char num);
//read one input pout status
//unsigned char num : input number select
//return input status range : 0(no input) / 1(input)
//************************************************************************
//unsigned char get_single_input_status(unsigned char num);

//************************************************************************
//unsigned int get_total_input_status(void);
//read all input port status
//return all input port status  range : 0~0xffff
//************************************************************************
//unsigned int get_total_input_status(void);


//************************************************************************
//void INIT_IOPORT(void);
// 16 input & 16 output port initial
//************************************************************************
void INIT_IOPORT(void);


#ifdef	__cplusplus
}
#endif

#endif	/* IO_DRIVER_H */

