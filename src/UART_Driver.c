#include "..\h\Global_define.h"
#include "..\h\UART_Driver.h"
#include "..\h\SYS_Driver.h"
#include "..\h\SystemControl.h"
#include "..\h\COM3_Command.h"
#define UARTRXTimeOutCNT 10

//Isen：20230922新增==================
#define UART1_RXDATA_SIZE 9
#define UART1_RXCRC_SIZE 2
//Isen：20230922新增==================

extern unsigned char CRC_CHECK(unsigned char *data, unsigned char lenth ,unsigned int crc_data);
extern void Android_HMI_Parsing(void);
extern void Android_HMI_SendingControl(void);
extern void U2CommandParsing(void);
extern void U3CommandParsing(void);
extern void Send_LoopBackResponse(void);//Isen：20230921新增
extern unsigned char COM1_RxData_Size, COM2_RxData_Size, COM3_RxData_Size;
extern unsigned char RoutineSendFlag;//Isen：20230921新增
extern unsigned char UART1TxBufCount;//Isen：20230922新增

unsigned char UART1RxBuffer[UART1_BUFFER_SIZE];
unsigned char UART1TxBuffer[UART1_BUFFER_SIZE];
unsigned char UART2TxBuffer[UART2_BUFFER_SIZE];
unsigned char UART2RxBuffer[UART2_BUFFER_SIZE];
unsigned char UART3TxBuffer[UART3_BUFFER_SIZE];
unsigned char UART3RxBuffer[UART3_BUFFER_SIZE];

unsigned char U3NewCommandReceivedFlag;
unsigned char U2NewCommandReceivedFlag;
unsigned char U1NewCommandReceivedFlag;

unsigned int UART1TimeOutCount, UART1RxBufCount, U1SendDataCount, U1PacketLen;
unsigned int UART2TimeOutCount, UART2RxBufCount, U2SendDataCount, U2PacketLen;
unsigned int UART3TimeOutCount, UART3RxBufCount, U3SendDataCount, U3PacketLen;

//Isen：20230922新增========================
extern _PARSING_WORD U1_ParsingWord;
extern _PARSING_DATA U1_ParsingData;
char UART1RxData[UART1_PACKET_SIZE];
unsigned int COM1_TxData_Size = 0;

//Isen：僅開機執行一次
void ClearUART1_Counter(void)
{
    U1NewCommandReceivedFlag = 0;
    U1SendDataCount = UART1_PACKET_SIZE;          
    U1PacketLen = 0;
    UART1RxBufCount = 0;
    UART1TimeOutCount = 0;   
    COM1_RxData_Size = 0;//Isen：20230922新增
}

void ClearUART2_Counter(void)
{
    U2NewCommandReceivedFlag = 0;    
    U2SendDataCount = UART2_PACKET_SIZE;    
    UART2RxBufCount = 0;
    U2PacketLen=0;
}

void ClearUART3_Counter(void)
{
    U3NewCommandReceivedFlag = 0;
    U3SendDataCount = UART3_PACKET_SIZE;  
    UART3RxBufCount = 0;
    U3PacketLen=0;    
}

void StartUART1WaitTimer(void)
{
    UART1TimeOutCount = 0;
}

void StartUART2WaitTimer(void)
{
    UART2TimeOutCount = 0;
}

void StartUART3WaitTimer(void)
{
    UART3TimeOutCount = 0;
}

void INIT_UART1(unsigned int baud_rate,unsigned int parity,unsigned int stopbit)
{
    // This is an EXAMPLE, so brutal typing goes into explaining all bit sets
    // The HPC16 board has a DB9 connector wired to UART1, so we will
    // be configuring this port only
    // configure U1MODE
    U1MODE=0; //8,n,1
    U1MODE=parity|stopbit;
    U1BRG = baud_rate;

    // Load all values in for U1STA SFR
    U1STA=0;
    IPC2bits.U1RXIP=3;
    IPC3bits.U1TXIP=3;
    IFS0bits.U1TXIF = 0;	// Clear the Transmit Interrupt Flag
    IEC0bits.U1TXIE = 0;//1;	// Enable Transmit Interrupts
    IFS0bits.U1RXIF = 0;	// Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1;//1;	// Enable Recieve Interrupts

    U1MODEbits.UARTEN = 1;	// And turn the peripheral on
    U1STAbits.UTXEN = 1; //tx enable
    //Set UART1 TX RX Pin
    RPOR4bits.RP79R = UART1TX;  // TX1 in RP79
    _TRISD15=0;  //tx output
    RPINR18bits.U1RXR = RPI78;  // RX1 in RPI78
    _TRISD14=1;  //rx input
    _TRISK15=0;
    UART1_DE=DE_ENABLE;
    
    ClearUART1_Counter(); //Isen：僅開機執行一次
}

void INIT_UART2(unsigned int baud_rate,unsigned int parity,unsigned int stopbit,unsigned char txrx_isr_en)
{
    U2MODE=0; //8,n,1
    U2MODE=parity|stopbit;
    U2BRG = baud_rate;

    // Load all values in for U1STA SFR
    U2STA=0;
    IPC7bits.U2TXIP=3;
    IPC7bits.U2RXIP=3;
    IFS1bits.U2TXIF = 0;	// Clear the Transmit Interrupt Flag
    if((txrx_isr_en&0x01)==1)
        IEC1bits.U2TXIE = 1;	// Enable Transmit Interrupts
    else
        IEC1bits.U2TXIE = 0;//1;	// Disable Transmit Interrupts
    IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
    if((txrx_isr_en&0x02)==2)
        IEC1bits.U2RXIE = 1;//1;	// Enable Recieve Interrupts
    else
        IEC1bits.U2RXIE = 0;    // Disable Recieve Interrupts
    IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
    //Set UART2 TX RX Pin
    RPOR11bits.RP108R = UART2TX;  // TX2 in RP108
    _TRISF12=0;  //tx output
    RPINR19bits.U2RXR=RPI44;  // RX2 in RPI44
    _TRISB12=1;  //rx input
    _ANSB12=0;
    _TRISK13=0;
//    UART2_DE=DE_DISABLE;
    UART2_DE=DE_ENABLE;
    U2MODEbits.UARTEN = 1;	// And turn the peripheral on
    U2STAbits.UTXEN = 1; //tx enable
    
    ClearUART2_Counter();
}

void INIT_UART3(unsigned int baud_rate,unsigned int parity,unsigned int stopbit,unsigned char txrx_isr_en)
{
    U3MODE=0; //8,n,1
    U3MODE=parity|stopbit;
    U3BRG = baud_rate;
    // Load all values in for U1STA SFR
    U3STA=0;
    IPC20bits.U3TXIP=3;
    IPC20bits.U3RXIP=3;
    IFS5bits.U3TXIF = 0;	// Clear the Transmit Interrupt Flag
    if((txrx_isr_en&0x01)==1)
        IEC5bits.U3TXIE = 1;	// Enable Transmit Interrupts
    else
        IEC5bits.U3TXIE = 0;	// Disable Transmit Interrupts
    IFS5bits.U3RXIF = 0;	// Clear the Recieve Interrupt Flag
    if((txrx_isr_en&0x02)==2)
        IEC5bits.U3RXIE = 1;	// Enable Recieve Interrupts
    else
        IEC5bits.U3RXIE = 0;	// Disable Recieve Interrupts
    U3MODEbits.UARTEN = 1;	// And turn the peripheral on
    U3STAbits.UTXEN = 1; //tx enable
    //Set UART1 TX RX Pin
    RPOR12bits.RP109R = UART3TX;  // TX3 in RP109
    _TRISF13=0;  //tx output
    RPINR27bits.U3RXR=RPI17;  // RX3 in RPI17
    _TRISA1=1;  //rx input
    _TRISK14=0;
//    UART3_DE=DE_DISABLE;
    UART3_DE=DE_ENABLE;
    
    ClearUART3_Counter();
}

void uart1_tx(unsigned char txdata)
{
    U1TXREG = txdata;
}

void uart2_tx(unsigned char txdata)
{
    U2TXREG = txdata;
}

void uart3_tx(unsigned char txdata)
{
    U3TXREG = txdata;
}

unsigned char IsCOM1_TX_Busy(void)
{
    if(!U1STAbits.TRMT)
        return 1;
    else
        return 0;
}

unsigned char IsCOM2_TX_Busy(void)
{
    if(!U2STAbits.TRMT)
        return 1;
    else
        return 0;
}

unsigned char IsCOM3_TX_Busy(void)
{
    if(!U3STAbits.TRMT)
        return 1;
    else
        return 0;
}

unsigned char uart2_rx(void)
{
    unsigned char uart2_rxdata = 0;
    UART2_DE = DE_DISABLE;
    while(!U2STAbits.URXDA == 0);  //wait tx finish
    uart2_rxdata = U2RXREG ;
    return uart2_rxdata;
}

unsigned char uart3_rx(void)
{
    unsigned char uart3_rxdata = 0;
    UART3_DE = DE_DISABLE;
    while(!U3STAbits.URXDA == 0);  //wait rx finish
    uart3_rxdata = U3RXREG ;
    return uart3_rxdata;
}

void __attribute__( ( interrupt , no_auto_psv ) ) _U1TXInterrupt( void )
{
    IEC0bits.U1TXIE=0;
    IFS0bits.U1TXIF = 0;
    IEC0bits.U1TXIE=1;
}

void __attribute__( ( interrupt , no_auto_psv ) ) _U1RXInterrupt( void )
{   
    IEC0bits.U1RXIE=0;
    IFS0bits.U1RXIF = 0;

    unsigned int index;
    index = UART1RxBufCount++;
    UART1RxBuffer[index] = U1RXREG;   
    StartUART1WaitTimer();
   
    IEC0bits.U1RXIE=1;
    U1STAbits.OERR = 0;
} 

void __attribute__( ( interrupt , no_auto_psv ) ) _U2RXInterrupt( void )
{	
    IEC1bits.U2RXIE=0;
    IFS1bits.U2RXIF = 0;
    
    UART2RxBuffer[UART2RxBufCount++] = U2RXREG;   
    StartUART2WaitTimer();    

	IEC1bits.U2RXIE=1;
	U2STAbits.OERR = 0;
}

void __attribute__( ( interrupt , no_auto_psv ) ) _U3RXInterrupt( void )
{	
    IEC5bits.U3RXIE=0;
    IFS5bits.U3RXIF = 0;

    UART3RxBuffer[UART3RxBufCount++] = U3RXREG; 
    StartUART3WaitTimer();
    
	IEC5bits.U3RXIE=1;
	U3STAbits.OERR = 0;
}

void UARTRXTimeOutCheck(void)//Isen：原設計會因系統中斷後自動執行，繼續沿用
{
    UART1TimeOutCount++;
    UART2TimeOutCount++;
    UART3TimeOutCount++;

    if( UART1TimeOutCount > UARTRXTimeOutCNT )
    {
        UART1TimeOutCount = UARTRXTimeOutCNT;
        if( UART1RxBufCount > 0 )
        {     
            if( UART1RxBufCount > UART1_PACKET_SIZE )
            {
                COM1_RxData_Size = UART1RxBufCount;
                U1NewCommandReceivedFlag = 1;          
            }
            UART1RxBufCount = 0;
        }
    }     
    
    if( UART2TimeOutCount > UARTRXTimeOutCNT )
    {
        UART2TimeOutCount = UARTRXTimeOutCNT;        
        if( UART2RxBufCount >= UART2_PACKET_SIZE )
        {
            COM2_RxData_Size = UART2RxBufCount;
            U2NewCommandReceivedFlag = 1;
        }
        else if( UART2RxBufCount > 0 )
            UART2RxBufCount = 0;
    }    
    
    if( UART3TimeOutCount > UARTRXTimeOutCNT )
    {
        UART3TimeOutCount = UARTRXTimeOutCNT;
        if( UART3RxBufCount > 0 )
        {
            if( UART3RxBufCount > 4 )
            {
                COM3_RxData_Size = UART3RxBufCount;
                U3NewCommandReceivedFlag = 1;
            }
            UART3RxBufCount = 0;            
        }
    }
}

//Isen：20230913-1，新增讀取UART1暫存區的功能函式
//Isen：讀取UART1的數據並立即回傳
char readUART1Data(void) {   
    if (UART1RxBufCount > 0) { // 檢查是否有可用的數據
        char receivedData = UART1RxBuffer[0]; // 讀取緩衝區的第一個字節
        int i;
        for(i = 0; i < UART1RxBufCount; i++) {
            UART1RxBuffer[i] = UART1RxBuffer[i + 1]; // 移動緩衝區的數據
        }
        UART1RxBufCount--; // 減少緩衝區的數據計數器
        return receivedData; // 返回接收到的數據
    }
    return 0; // 如果沒有可用的數據，返回0
}

//Isen：利用系統中斷<->掃描運行，來仿製For-Next功能的典型設計
void UART1_RXtoTX(void){
    int i;
    for(i = 0; i < UART1RxBufCount; i++) {
        UART1RxBuffer[i] = UART1RxBuffer[i + 1]; // Shift移動Rx緩衝區的數據
    }
}

//Isen：20230922新增，設計這段只會執行一次函式 (當Count = 11時)，用於處理CRC檢查以及RX->TX
void ParsingUART1_RXBufferData(void){
    
}

//Isen：20230913-1，發送數據到UART1
void sendUART1Data(char receivedData) {
    while (U1STAbits.UTXBF); // 等待傳輸緩衝區有空間
    U1TXREG = receivedData; // 將數據放入傳輸暫存器，開始傳輸
    IFS0bits.U1RXIF = 0; // 清除接收中斷標誌
}

//Isen：20230913-1，檢查是否接收到有效數據
void echoUART1Data(void) {
    char receivedData = readUART1Data(); // 讀取RX數據
    if (receivedData != 0) { // 檢查不為0的數據才送出TX
        sendUART1Data(receivedData); 
    }
}

//Isen：20230913-1，發送數據到UART1
void SendingUART1_TxBuffData(void) {
    // 如果接收到11個byte
    if (UART1RxBufCount == UART1_PACKET_SIZE) {
        // 將接收到的資料複製到Tx
        int i;
        for (i = 0; i < UART1_PACKET_SIZE; i++) {
            while (U1STAbits.UTXBF); // 等待Tx緩衝區有空間
            U1TXREG = UART1RxBuffer[i];
        }
        // 重置計數器
        UART1RxBufCount = 0;
    }
}

void CommandParsingProcess(void)
{        
    if(U1NewCommandReceivedFlag == 1)   
    { 
//        readUART1Data();//Isen：20230913-1通訊測試用  
//        ParsingUART1_RXBufferData();
//        Android_HMI_Parsing();
        U1NewCommandReceivedFlag = 0;
    }
    
    if(U2NewCommandReceivedFlag == 1)
    {       
        U2CommandParsing();
        U2NewCommandReceivedFlag = 0;
    }
    
    if(U3NewCommandReceivedFlag == 1)
    {
        U3CommandParsing();
        U3NewCommandReceivedFlag = 0;
    }    
//    echoUART1Data();//Isen：20230913-1通訊測試用
    SendingUART1_TxBuffData();//Isen：20230922-2通訊測試用
//    Android_HMI_SendingControl();
    
}

void SEND_U1_RS422_CMD_Process(void)
{
    if(IsCOM1_TX_Busy() == 1)
        ;
    else if( U1SendDataCount < U1PacketLen )
        uart1_tx(UART1TxBuffer[U1SendDataCount++]);    
}

void SEND_U2_RS422_CMD_Process(void)
{   
    if(IsCOM2_TX_Busy()==1)//(!U3STAbits.TRMT))
        ;
    else if( U2SendDataCount < U2PacketLen )
        uart2_tx(UART2TxBuffer[U2SendDataCount++]);
}

void SEND_U3_RS422_CMD_Process(void)
{
    if(IsCOM3_TX_Busy()==1)//(!U3STAbits.TRMT))
        ;
    else if( U3SendDataCount < U3PacketLen )
    {        
        uart3_tx(UART3TxBuffer[U3SendDataCount++]);
    }
}
