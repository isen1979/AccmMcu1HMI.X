

#ifndef ENCODER_DRIVER_H
#define	ENCODER_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

 //function io control select
#define GPIO_CTRL    1
#define QEI_CTRL     2

#define QEI_INP_CTRL   QEI_CTRL
#define QEI_HOME_CTRL  QEI_CTRL

#if QEI_OUT_CTRL==QEI_CTRL
	#define QEIOUTX	  0x2F//RP97 //RF1 INPX
	#define QEIOUTY   0x30//RP96 //RF0  INPY
#endif
#if QEI_INP_CTRL==GPIO_CTRL
	#define QEIOUTX	   _RF1
	#define QEIOUTY	   _RF0
	#define QEIOUT_L      1
	#define QEIOUT_H      0
#endif
#define QEIX_A_SEL	RP126
#define QEIX_B_SEL	RPI23//RPI124
#define QEIX_INDEX_SEL	RPI22
#define QEIX_HOME_SEL	RP113

#define QEIY_A_SEL	RP125//RP127//RP125//RP127
#define QEIY_B_SEL	RP127//RP125//RP127//RP125
#define QEIY_INDEX_SEL	RPI124
#define QEIY_HOME_SEL	RP112

//reg1 QEIxCON
#define QEI_EN              0x8000 //bit15
#define QEI_DIS             0x0000
#define QEI_SIDL_DIS        0x0000 //bit13     //in idle continue counter
#define QEI_SIDL_EN         0x2000             //in idle uncontinue counter
#define QEI_COUNT_INIT_M0   0x0000 //bit12~10  //0: every index pulse dont clear QEI counter
#define QEI_COUNT_INIT_M1   0x0400             //1: every index pulse clear QEI counter
#define QEI_COUNT_INIT_M2   0x0800             //2: Next index input event initializes the position counter with contents of QEIxIC register
#define QEI_COUNT_INIT_M3   0x0C00             //3: First index event after home event initializes position counter with contents of QEIxIC register
#define QEI_COUNT_INIT_M4   0x1000             //4: Second index event after home event initializes position counter with contents of QEIxIC register
#define QEI_COUNT_INIT_M5   0x1400             //5: Resets the position counter when the position counter equals QEIxGEC register
#define QEI_COUNT_INIT_M6   0x1800             //6: Modulo Count mode for position counter
#define QEI_IMV0            0x0000 //bit9~8    //0: Index input event does not affect position counter
#define QEI_IMV1            0x0100             //1: Index match occurs when QEB = 0 and QEA = 1
#define QEI_IMV2            0x0200             //2: Index match occurs when QEB = 1 and QEA = 0
#define QEI_IMV3            0x0300             //3: Index match occurs when QEB = 1 and QEA = 1
//if QEI used timer to counter pluse
#define QEI_TIMER_DIV1      0x0000 //bit6~4    //0: 1:1 prescale value internal clock divider select
#define QEI_TIMER_DIV2      0x0010             //1: 1:2
#define QEI_TIMER_DIV4      0x0020             //2: 1:4
#define QEI_TIMER_DIV8      0x0030             //3: 1:8
#define QEI_TIMER_DIV16     0x0040             //4: 1:16
#define QEI_TIMER_DIV32     0x0050             //5: 1:32
#define QEI_TIMER_DIV64     0x0060             //6: 1:64
#define QEI_TIMER_DIV256    0x0070             //7: 1:256
//Position and Index Counter/Timer Direction Select bit  //方向上下數選擇
#define QEI_CNT_DIR_P       0x0000 //bit3      //0: Counter direction is positive unless 正轉
#define QEI_CNT_DIR_N       0x0008             //1: Counter direction is negative unless 反轉
//External Count Gate Enable
#define QEI_GATE_EN         0x0004 //bit2      //1: External gate signal controls position counter operation
#define QEI_GATE_DIS        0x0000             //0: External gate signal does not affect position counter/timer operation
//Counter Control Mode Selection
#define QEI_CNT_INT_TIMER   0X0003             //3: Internal Timer mode
#define QEI_CNT_GATE_TIMER   0x0002             //2: External clock count with external Gate mode
#define QEI_CNT_UD_TIMER   0x0001             //1: External clock count with external Up/Down mode
#define QEI_CNT_QUAD_TIMER   0x0000             //0: Quadrature Encoder mode

//reg2 QEIxIOC
//Position Counter Input Capture Enable bit15
#define QEI_HOME_TRIG_EN    0x8000             //1: HOMEx input event (positive edge) triggers a position capture event
#define QEI_HOME_TRIG_DIS   0x0000             //0: HOMEx input event (positive edge) does not trigger a position capture event
//FLTREN:QEA/QEB/INDX/HOMEx Digital Filter Enable bit14
#define QEI_DFT_EN          0x4000             //1: Input Pin Digital filter is enabled
#define QEI_DFT_DIS         0x0000             //0: Input Pin Digital filter is disabled (bypassed)
//QEA/QEB/INDX/HOMEx Digital Input Filter Clock Divide Select bit13~11
#define QEI_DFT_DIV256      0x3800             //7: 1:256 clock divide
#define QEI_DFT_DIV64       0x3000             //6: 1:64 clock divide
#define QEI_DFT_DIV32       0x2800             //5: 1:32 clock divide
#define QEI_DFT_DIV16       0x2000             //4: 1:16 clock divide
#define QEI_DFT_DIV8        0x1800             //3: 1:8 clock divide
#define QEI_DFT_DIV4        0x1000             //2: 1:4 clock divide
#define QEI_DFT_DIV2        0x0800             //1: 1:2 clock divide
#define QEI_DFT_DIV1        0x0000             //0: 1:1 clock divide
//QEI Module Output Function Mode Select bits10~9
#define QEI_OUT_MODE3       0x0600             //3: The CNTCMPx pin goes high when POSxCNT ≤QEIxLEC or POSxCNT ≥QEIxGEC
#define QEI_OUT_MODE2       0x0400             //2: The CNTCMPx pin goes high when POSxCNT ≤QEIxLEC
#define QEI_OUT_MODE1       0x0200             //1: The CNTCMPx pin goes high when POSxCNT≥QEIxGEC
#define QEI_OUT_MODE0       0x0000             //0: Output is disabled
//Swap QEA and QEB Inputs bit8
#define QEI_AB_SWAP_EN      0x0100             //1: QEAx and QEBx are swapped prior to quadrature decoder logic
#define QEI_AB_SWAP_DIS     0x0000             //0: QEAx and QEBx are not swapped
//HOMEx Input Polarity Select bit7
#define QEI_HOME_INV_EN     0x0080             //1: Input is inverted
#define QEI_HOME_INV_DIS    0x0000             //0: Input is not inverted
//INDXx Input Polarity Select bit6
#define QEI_INDEX_INV_EN    0x0040             //1: Input is inverted
#define QEI_INDEX_INV_DIS   0x0000             //0: Input is not inverted
//QEBx Input Polarity Select bit5
#define QEI_B_INV_EN        0x0020             //1: Input is inverted
#define QEI_B_INV_DIS       0x0000             //0: Input is not inverted
//QEAx Input Polarity Select bit4
#define QEI_A_INV_EN        0x0010             //1: Input is inverted
#define QEI_A_INV_DIS       0x0000             //0: Input is not inverted
//Status of HOMEx Input Pin after Polarity Control bit3 (Read-Only)
//Status of INDXx Input Pin after Polarity Control bit2 (Read-Only)
//Status of QEBx Input Pin after Polarity Control and SWPAB Pin Swapping bit1 (read-only)
//Status of QEAx Input Pin after Polarity Control and SWPAB Pin Swapping bit0 (read-only)

//reg3 QEIxSTAT
//Position Counter Greater Than or Equal Compare Status bit13
//1= POSxCNT ≥QEIxGEC  0= POSxCNT < QEIxGEC
//Position Counter Greater Than or Equal Compare Interrupt Enable bit12
#define QEI_GREAT_INT_EN     0x1000            //1: Interrupt is enabled
#define QEI_GREAT_INT_DIS    0x0000            //0: Interrupt is disabled
//Position Counter Less Than or Equal Compare Status bit11
//1= POSxCNT ≤QEIxLEC  0= POSxCNT > QEIxLEC
//Position Counter Less Than or Equal Compare Interrupt Enable bit10
#define QEI_LESS_INT_EN      0x0400            //1: Interrupt is enabled
#define QEI_LESS_INT_DIS     0x0000            //0: Interrupt is disabled
//Position Counter Overflow Status bit9
//1= Overflow has occurred  0= No overflow has occurred
//Position Counter Overflow Interrupt Enable bit8
#define QEI_OVERFLOW_INT_EN  0x0100            //1: Interrupt is enabled
#define QEI_OVERFLOW_INT_DIS 0x0000            //0: Interrupt is disabled
//Position Counter (Homing) Initialization Process Complete Status bit7
//1= POSxCNT was reinitialized  0= POSxCNT was not reinitialized
//Position Counter (Homing) Initialization Process Complete Interrupt Enable bit6
#define QEI_INIT_INT_EN      0x0040            //1: Interrupt is enabled
#define QEI_INIT_INT_DIS     0x0000            //0: Interrupt is disabled
//Velocity Counter Overflow Status bit5
//1= Overflow has occurred  0= No overflow has occurred
//Velocity Counter Overflow Interrupt Enable bit4
#define QEI_VEL_INT_EN       0x0010           //1: Interrupt is enabled
#define QEI_VEL_INT_DIS      0x0000           //0: Interrupt is disabled
//Status Flag for Home Event Status bit3
//1= Home event has occurred  0= No Home event has occurred

//Home Input Event Interrupt Enable bit2
#define QEI_HOME_INT_EN      0x0004           //1: Interrupt is enabled
#define QEI_HOME_INT_DIS     0x0000           //0: Interrupt is disabled

//Status Flag for Index Event Status bit1
//1= Index event has occurred  0= No Index event has occurred
//Index Input Event Interrupt Enable bit0
#define QEI_INDEX_INT_EN     0x0001             //1: Interrupt is enabled
#define QEI_INDEX_INT_DIS    0x0000             //0: Interrupt is disabled


//************************************************************************
//void INIT_QEIX(unsigned int reg1,unsigned int reg2,unsigned int reg3);//reg1 set QEI1CON,reg2 set QEI1IOC,reg3 set QEI1STAT
//MCU Encoder X initial
//Example:   INIT_QEIX( QEI_DIS | QEI_SIDL_DIS | QEI_COUNT_INIT_M0 | QEI_IMV2 | QEI_TIMER_DIV1
//                      | QEI_CNT_DIR_P | QEI_GATE_DIS | QEI_CNT_QUAD_TIMER,QEI_OUT_MODE1,0);//reg3=0 all interrupt disable
//           setting Encoder X is AB phase input
//************************************************************************
void INIT_QEIX(unsigned int reg1,unsigned int reg2,unsigned int reg3);//reg1 set QEI1CON,reg2 set QEI1IOC,reg3 set QEI1STAT

//************************************************************************
//void INIT_QEIY(unsigned int reg1,unsigned int reg2,unsigned int reg3);//reg1 set QEI1CON,reg2 set QEI1IOC,reg3 set QEI1STAT
//MCU Encoder Y initial
//Example:   INIT_QEIY( QEI_DIS | QEI_SIDL_DIS | QEI_COUNT_INIT_M0 | QEI_IMV2 | QEI_TIMER_DIV1
//                      | QEI_CNT_DIR_P | QEI_GATE_DIS | QEI_CNT_QUAD_TIMER,QEI_OUT_MODE1,0);//reg3=0 all interrupt disable
//           setting Encoder Y is AB phase input
//************************************************************************
void INIT_QEIY(unsigned int reg1,unsigned int reg2,unsigned int reg3);//reg1 set QEI2CON,reg2 set QEI2IOC,reg3 set QEI2STAT

//************************************************************************
//unsigned long GET_ENCX(void);
//get Encoder X pulse counter values
//return pulse counter values range : 0~0xffffffff
// After get Encoder X pulse counter values counter buffer will clear
//************************************************************************
unsigned long GET_ENCX(void);

//************************************************************************
//unsigned long GET_ENCY(void);
//get Encoder Y pulse counter values
//return pulse counter values range : 0~0xffffffff
// After get Encoder Y pulse counter values counter buffer will clear
//************************************************************************
unsigned long GET_ENCY(void);

//************************************************************************
//unsigned long GET_INDEX_X(void);
//get Encoder X INDEX counter values
//return INDEX counter values range : 0~0xffffffff
// After get Encoder X INDEX counter values counter buffer will clear
//************************************************************************
unsigned long GET_INDEX_X(void);

//************************************************************************
//unsigned long GET_INDEX_Y(void);
//get Encoder Y INDEX counter values
//return INDEX counter values range : 0~0xffffffff
// After get Encoder Y INDEX counter values counter buffer will clear
//************************************************************************
unsigned long GET_INDEX_Y(void);

//************************************************************************
//void INIT_LIMITX(void);
//iNITIAL LIMIT X1 X2
//************************************************************************
void INIT_LIMITX(void);

//************************************************************************
//void INIT_LIMITY(void);
//iNITIAL LIMIT Y1 Y2
//************************************************************************
void INIT_LIMITY(void);

//************************************************************************
//unsigned char get_limit_x1(void);
//Get limit x1 status
//return limit x1 status range : 0/1 (limit open / limit close)
//************************************************************************
unsigned char get_limit_x1(void);

//************************************************************************
//unsigned char get_limit_x2(void);
//Get limit x2 status
//return limit x2 status range : 0/1 (limit open / limit close)
//************************************************************************
unsigned char get_limit_x2(void);

//************************************************************************
//unsigned char get_limit_y1(void);
//Get limit y1 status
//return limit y1 status range : 0/1 (limit open / limit close)
//************************************************************************
unsigned char get_limit_y1(void);

//************************************************************************
//unsigned char get_limit_y2(void);
//Get limit y2 status
//return limit y2 status range : 0/1 (limit open / limit close)
//************************************************************************
unsigned char get_limit_y2(void);

//Limit 
#define LIMITX1  	   _RJ7
#define LIMITX2		   _RJ6

#define LIMITY1		   _RJ5
#define LIMITY2            _RJ4
//LIMIT POLE DEFINE
#define LIMIT_CLOSE       0   //LINIT INPUT
#define LIMIT_OPEN      1   //LINIT  NO INPUT

void INIT_LIMITX(void);
void INIT_LIMITY(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ENCODER_DRIVER_H */

