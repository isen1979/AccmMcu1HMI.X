#include "..\h\Global_define.h"
#include "..\h\Item.h"
#include "..\h\LCD_driver.h"
#include "..\h\IO_Driver.h"
#include "..\h\Ext_ACD_DAC_Driver.h"
#include "..\h\System_Driver.h"
#include "..\h\UART_Driver.h"
#include "..\h\Data_API.h"
//#include "..\h\SystemControl.h"
#include "..\h\Encoder_Driver.h"

_FGS( GWRP_OFF & GSS_OFF & GSSK_OFF );
//_FOSCSEL(FNOSC_FRC & IESO_OFF);
_FOSCSEL(/*FNOSC_FRC*/FNOSC_FRCPLL & IESO_OFF);//20140715 test
// Enable Clock Switching and Configure Primary Oscillator in XT mode
_FOSC( IOL1WAY_ON & FCKSM_CSDCMD & OSCIOFNC_ON & POSCMD_NONE);
_FWDT( WDTPOST_PS32768 & WDTPRE_PR128 & PLLKEN_ON & WINDIS_OFF & FWDTEN_OFF );
_FAS( AWRP_OFF & APL_OFF & APLK_OFF );
_FPOR(FPWRT_PWR2 & BOREN_ON & ALTI2C1_OFF & ALTI2C2_OFF );
_FICD( RSTPRI_PF & ICS_PGD1 & JTAGEN_OFF );



unsigned int FirmwareVersion=1;//2;
unsigned long FirmwareDate=20220531;//20220124;//20210820;

extern void INIT_PWM(void);
extern void INIT_PWMX(void);
extern void INIT_PWMY(void);
extern void SystemControl(void);
extern void INIT_TIMER5(unsigned char isr_period);  //Timer5 interrupt
extern void enable_timer5(void);
extern void INIT_TIMER7(unsigned char isr_period);  //Timer5 interrupt
extern void enable_timer7(void);
extern void INIT_TIMER9(unsigned char isr_period);  //Timer5 interrupt
extern void enable_timer9(void);
extern void uC_HMI_SetPage(unsigned int page);

int main(void)
{
    INIT_OSC();
    INIT_IOPORT();
    INIT_I2C();
    INIT_SPI1();

   // INIT_IOPORT();

    INIT_TIMER1(INIT_TIMER_INTERRUPT_PERIOD_1MS);    
    enable_timer1();

    //INIT_TIMER2(INIT_TIMER_INTERRUPT_PERIOD_200MS);
    INIT_TIMER3(EXT_INPUT_COUNTER_MODE);//X-A Phase 
    enable_timer3();//X-A Phase    
    INIT_TIMER5(EXT_INPUT_COUNTER_MODE);//X-B Phase 
    enable_timer5();//X-B Phase 
    
    INIT_TIMER7(EXT_INPUT_COUNTER_MODE);//Y-A Phase 
    enable_timer7();//Y-A Phase 
    
    INIT_TIMER9(EXT_INPUT_COUNTER_MODE);//Y-B Phase  
    enable_timer9();//Y-B Phase     

    INIT_PWMX();
    INIT_PWMY();


//    INIT_TIMER4(INIT_TIMER_INTERRUPT_PERIOD_200MS);
//    enable_timer4();    
//Philip 20190912 01 baud rate changes to 9600 =======================================================================
    INIT_UART1(BAUD_9600,NO_PARITY_8BIT,STOP_1BIT);
    INIT_UART2(BAUD_9600,NO_PARITY_8BIT,STOP_1BIT,2);//2: RX Interrupt Enable//BAUD_115200
    INIT_UART3(BAUD_9600,NO_PARITY_8BIT,STOP_1BIT,2);//2: RX Interrupt Enable//BAUD_115200
//Philip 20190912 01 baud rate changes to 9600 =======================================================================    
/*
     INIT_QEIX( QEI_DIS | QEI_SIDL_DIS | QEI_COUNT_INIT_M0 | QEI_IMV2 | QEI_TIMER_DIV1
               | QEI_CNT_DIR_P | QEI_GATE_DIS | QEI_CNT_QUAD_TIMER,QEI_OUT_MODE1,0);//reg3=0 all interrupt disable
*/    
    INIT_QEIY( QEI_DIS | QEI_SIDL_DIS | QEI_COUNT_INIT_M0 | QEI_IMV2 | QEI_TIMER_DIV1
               | QEI_CNT_DIR_P | QEI_GATE_DIS | QEI_CNT_QUAD_TIMER,QEI_OUT_MODE1,0);//reg3=0 all interrupt disable    

//    INIT_ADC();  
//    INIT_PWM();
//    uC_HMI_SetPage(10);//First Page    
    while(1)
    {
        SystemControl();
    }

}
