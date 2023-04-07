#include "..\h\Global_define.h"

#define ISR_DISABLE  0
#define ISR_ENABLE   1

// capture input interrupt function define
#define CAPTURE1_ISR ISR_DISABLE
#define CAPTURE2_ISR ISR_DISABLE
#define CAPTURE3_ISR ISR_DISABLE
#define CAPTURE4_ISR ISR_DISABLE
#define CAPTURE5_ISR ISR_DISABLE
#define CAPTURE6_ISR ISR_DISABLE
#define CAPTURE7_ISR ISR_DISABLE
#define CAPTURE8_ISR ISR_DISABLE

// External input interrupt function define
#define EXTERNAL_INPUT0_ISR ISR_DISABLE
#define EXTERNAL_INPUT1_ISR ISR_DISABLE
#define EXTERNAL_INPUT2_ISR ISR_DISABLE
#define EXTERNAL_INPUT3_ISR ISR_DISABLE
#define EXTERNAL_INPUT4_ISR ISR_DISABLE

// UART / RS232 / RS422 / RS485 interrupt function define
#define UART2_TX_ISR ISR_DISABLE
#define UART2_RX_ISR ISR_DISABLE
#define UART3_TX_ISR ISR_DISABLE
#define UART3_RX_ISR ISR_DISABLE

//Encoder Interrupt function define
#define ENCODERX_ISR ISR_DISABLE
#define ENCODERY_ISR ISR_DISABLE

//Capture input ISR
#if CAPTURE1_ISR==ISR_ENABLE
unsigned int Capture1;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC1Interrupt(void)
{
	IFS0bits.IC1IF = 0; // Reset respective interrupt flag
	Capture1 = IC1BUF; // Read and save off first capture entry
}
#endif

#if CAPTURE2_ISR==ISR_ENABLE
unsigned int Capture2;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC2Interrupt(void)
{
	IFS0bits.IC2IF = 0; // Reset respective interrupt flag
	Capture2 = IC2BUF; // Read and save off first capture entry
}
#endif


#if CAPTURE3_ISR==ISR_ENABLE
unsigned int Capture3;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC3Interrupt(void)
{
	IFS2bits.IC3IF = 0; // Reset respective interrupt flag
	Capture3 = IC3BUF; // Read and save off first capture entry
}
#endif

#if CAPTURE4_ISR==ISR_ENABLE
unsigned int Capture4;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC4Interrupt(void)
{
	IFS2bits.IC4IF = 0; // Reset respective interrupt flag
	Capture4 = IC4BUF; // Read and save off first capture entry
}
#endif

#if CAPTURE5_ISR==ISR_ENABLE
unsigned int Capture5;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC5Interrupt(void)
{
	IFS2bits.IC5IF = 0; // Reset respective interrupt flag
	Capture5 = IC5BUF; // Read and save off first capture entry
}
#endif

#if CAPTURE6_ISR==ISR_ENABLE
unsigned int Capture6;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC6Interrupt(void)
{
	IFS2bits.IC6IF = 0; // Reset respective interrupt flag
	Capture6 = IC6BUF; // Read and save off first capture entry
}
#endif

#if CAPTURE7_ISR==ISR_ENABLE
unsigned int Capture7;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC7Interrupt(void)
{
	IFS1bits.IC7IF = 0; // Reset respective interrupt flag
	Capture7 = IC7BUF; // Read and save off first capture entry
}
#endif

#if CAPTURE8_ISR==ISR_ENABLE
unsigned int Capture8;
void __attribute__ ((__interrupt__, no_auto_psv)) _IC8Interrupt(void)
{
	IFS1bits.IC8IF = 0; // Reset respective interrupt flag
	Capture8 = IC8BUF; // Read and save off first capture entry
}
#endif
//Capture input ISR END

//External Interrupt ISR
#if EXTERNAL_INPUT0_ISR==ISR_ENABLE
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{

        IFS0bits.INT0IF = 0;    //Clear the INT0 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif

#if EXTERNAL_INPUT1_ISR==ISR_ENABLE

void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)
{
        LATA=(PORTA ^ 0x20);    //Toggle RA6
        IFS1bits.INT1IF = 0;    //Clear the INT1 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif

#if EXTERNAL_INPUT2_ISR==ISR_ENABLE
void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void)
{
        LATA=(PORTA ^ 0x40);    //Toggle RA7
        IFS1bits.INT2IF = 0;    //Clear the INT2 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif

#if EXTERNAL_INPUT3_ISR==ISR_ENABLE
void __attribute__((interrupt, no_auto_psv)) _INT3Interrupt(void)
{
        LATA=(PORTA ^ 0x04);    //Toggle RA2
        IFS3bits.INT3IF = 0;    //Clear the INT3 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif

#if EXTERNAL_INPUT4_ISR==ISR_ENABLE
void __attribute__((interrupt, no_auto_psv)) _INT4Interrupt(void)
{
        LATA=(PORTA ^ 0x08);    //Toggle RA3
        IFS3bits.INT4IF = 0;    //Clear the INT4 interrupt flag or else
                                //the CPU will keep vectoring back to the ISR
}
#endif
//External Interrupt ISR END


// UART2 UART3 interrupt ISR START
#if UART2_TX_ISR==ISR_ENABLE
void __attribute__( ( interrupt , no_auto_psv ) ) _U2TXInterrupt( void )
{
	IEC1bits.U2TXIE=0;
	IFS1bits.U2TXIF = 0;
	IEC1bits.U2TXIE=1;
}
#endif

#if UART2_RX_ISR==ISR_ENABLE
void __attribute__( ( interrupt , no_auto_psv ) ) _U2RXInterrupt( void )
{
	IEC1bits.U2RXIE=0;
	//U2RXREG;
	IFS1bits.U2RXIF = 0;
	IEC1bits.U2RXIE=1;
	U2STAbits.OERR = 0;
}
#endif

#if UART3_TX_ISR==ISR_ENABLE
void __attribute__( ( interrupt , no_auto_psv ) ) _U3TXInterrupt( void )
{
	IEC5bits.U3TXIE=0;
	IFS5bits.U3TXIF = 0;
	IEC5bits.U3TXIE=1;
}
#endif

#if UART3_RX_ISR==ISR_ENABLE
void __attribute__( ( interrupt , no_auto_psv ) ) _U3RXInterrupt( void )
{
	IEC5bits.U3RXIE=0;
	//U3RXREG;  //rx date buffet
	IFS5bits.U3RXIF = 0;
	IEC5bits.U3RXIE=1;
	U3STAbits.OERR = 0;

}
#endif
// COM2 COM3 interrupt ISR END


//ENCODER interrupt ISR START
#if ENCODERX_ISR==ISR_ENABLE
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
#endif

#if ENCODERY_ISR==ISR_ENABLE
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
#endif
//ENCODER interrupt ISR END