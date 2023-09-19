/*
 * File:   test.c
 * Author: user
 *
 * Created on 2017年9月11日, 下午 6:02
 */

#include "..\h\Global_define.h"
#include "..\h\Data_API.h"
#include "..\h\SystemControl.h"
//#include "..\h\LCD_driver.h"
#include "..\h\IO_Driver.h"
#include "..\h\Datien_IO_Define.h"

#define LOAD_RUN_TIME_PARAMTER_TIME 1000

extern void Initial_EEPROM_Read_Write_Process(void);
extern void RunEEPROM_ReadWriteProcess(void);//Philip 20180517 02
extern unsigned char RegisterReadEEPROM(unsigned int addr, unsigned char *buf, unsigned int size);
extern void RegisterWriteEEPROM(unsigned int addr, unsigned char *buf, unsigned int size);
extern void LoadRunTimeParameter(void);
extern void CommandParsingProcess(void);
extern void SEND_U1_RS422CMD_Process(void);
extern void SEND_U2_RS422_CMD_Process(void);
extern void SEND_U3_RS422_CMD_Process(void);
extern void BottomFeederFeedingTypeClutchSet(void);
extern void TopFeederFeedingTypeClutchSet(void);
extern void RewinderClutchTypeSet(void);
extern long GetEncoderY_Value(void);
extern void COM2_SendControl(void);
extern void Fill_TestParameter(void);
extern void Send_uCHMI_ControllerFirmwareVersion(void);
extern void COM3_Send_All_Command(void);


_SYSTEM_PARAMETER SystemParameter, lastSystemParameter, *pSystemParameter;
_RUNTIME_STATUS RunTimeStatus, lastRunTimeStatus, *pRunTimeStatus;

unsigned long DelayTimerCounter[SystemDelayTimerEnumEnd];
unsigned char SystemInitialState=SystemLoadSystemParameterEnum;

void DelayTimer(void)
{
    unsigned char i;
    for(i=0;i<SystemDelayTimerEnumEnd;i++)
    {
        if(DelayTimerCounter[i] > 0)
            DelayTimerCounter[i]--;
    }
}

void LoadSystemParameter(unsigned int addr)
{
    unsigned char SystemParameterHandler;
    unsigned int size;
    size = sizeof(_SYSTEM_PARAMETER);
    
    pSystemParameter = &SystemParameter;
    SystemParameterHandler = RegisterReadEEPROM(addr, (unsigned char *)pSystemParameter, SYSTEM_PARAMETER_SIZE);
    pSystemParameter = &lastSystemParameter;
    SystemParameterHandler = RegisterReadEEPROM(addr, (unsigned char *)pSystemParameter, SYSTEM_PARAMETER_SIZE);
}

void SaveSystemParameter(unsigned int addr)
{
    unsigned int size;
    size = sizeof(_SYSTEM_PARAMETER);
    
    pSystemParameter = &SystemParameter;
    SystemParameter.WriteEEPROM_Count++;
    RegisterWriteEEPROM(addr, (unsigned char *)pSystemParameter, SYSTEM_PARAMETER_SIZE);     
}

void LoadRunTimeStatus(void)
{
    unsigned char SystemParameterHandler;
    pRunTimeStatus = &RunTimeStatus;
    SystemParameterHandler = RegisterReadEEPROM(SystemParameter.RunTimeStatusAddr, (unsigned char *)pRunTimeStatus, RUNTIME_STATUS_SIZE);
    pRunTimeStatus = &lastRunTimeStatus;
    SystemParameterHandler = RegisterReadEEPROM(SystemParameter.RunTimeStatusAddr, (unsigned char *)pRunTimeStatus, RUNTIME_STATUS_SIZE); 
}

#define MAX_EEPROM_ADDR 2032
#define MAX_RUN_TIME_STATUS_SAVE_TIME 950000
void SaveRunTimeStatus(void)//SystemParameter
{       
    pRunTimeStatus = &RunTimeStatus;
    RunTimeStatus.WriteEEPROM_Count++;    
    if( RunTimeStatus.WriteEEPROM_Count >= MAX_RUN_TIME_STATUS_SAVE_TIME )
    {        
        if( SystemParameter.RunTimeStatusAddr < MAX_EEPROM_ADDR )
        {
            RunTimeStatus.WriteEEPROM_Count = 0;
            SystemParameter.RunTimeStatusAddr = SystemParameter.RunTimeStatusAddr + 16;
            RegisterWriteEEPROM(SystemParameter.RunTimeStatusAddr, (unsigned char *)pRunTimeStatus, RUNTIME_STATUS_SIZE);
            SaveSystemParameter(SYSTEM_PARAMETER_START_ADDR);
        }
        else
            ;//Show EEPROM Fault
    }
    else
        RegisterWriteEEPROM(SystemParameter.RunTimeStatusAddr, (unsigned char *)pRunTimeStatus, RUNTIME_STATUS_SIZE);
}

void InitialSystemParameter(void)
{/*
    SystemParameter.RewinderTensionRatio = 500;//5.00
    SystemParameter.TopFeederTensionRatio = 500;//5.00
    SystemParameter.BottomFeederTensionRatio = 500;//5.00
    SystemParameter.flag.flagbitmap.BottomFeederFeedDir = 1;
    SystemParameter.flag.flagbitmap.BottomFeederSyncIndSelect = 1;
    SystemParameter.flag.flagbitmap.TopBottomFeederSelect = 1;
    SystemParameter.flag.flagbitmap.TopFeederFeedDir = 1;
    SystemParameter.flag.flagbitmap.TopFeederSyncIndSelect = 1;
    SystemParameter.flag.flagbitmap.SpreadClothes_1st_Enable = 1;
    SystemParameter.flag.flagbitmap.SpreadClothes_2nd_Enable = 1;
    SystemParameter.flag.flagbitmap.SpreadClothes_3rd_Enable = 1;
    
    SaveSystemParameter();*/
}

#define FORMAT_EEPROM_UNIT_SIZE 56
unsigned char FormatEEPROMdata[FORMAT_EEPROM_UNIT_SIZE];
void FormatEEPROM(void)
{
    RegisterWriteEEPROM(0, (unsigned char *)FormatEEPROMdata, FORMAT_EEPROM_UNIT_SIZE);
    RegisterWriteEEPROM(64, (unsigned char *)FormatEEPROMdata, FORMAT_EEPROM_UNIT_SIZE);
    RegisterWriteEEPROM(128, (unsigned char *)FormatEEPROMdata, FORMAT_EEPROM_UNIT_SIZE);
    RegisterWriteEEPROM(192, (unsigned char *)FormatEEPROMdata, FORMAT_EEPROM_UNIT_SIZE);
    RegisterWriteEEPROM(256, (unsigned char *)FormatEEPROMdata, FORMAT_EEPROM_UNIT_SIZE);
    RegisterWriteEEPROM(320, (unsigned char *)FormatEEPROMdata, FORMAT_EEPROM_UNIT_SIZE);
    RegisterWriteEEPROM(384, (unsigned char *)FormatEEPROMdata, FORMAT_EEPROM_UNIT_SIZE);
    RegisterWriteEEPROM(448, (unsigned char *)FormatEEPROMdata, FORMAT_EEPROM_UNIT_SIZE);
}

void Initial_OutputPorts(void)
{
    Y1 = 0;asm("nop");asm("nop");
    Y2 = 0;asm("nop");asm("nop");
    Y3 = 0;asm("nop");asm("nop");
    Y4 = 0;asm("nop");asm("nop");
    Y5 = 0;asm("nop");asm("nop");
    Y6 = 0;asm("nop");asm("nop");
    Y7 = 0;asm("nop");asm("nop");
    Y8 = 0;asm("nop");asm("nop");
    Y9 = 0;asm("nop");asm("nop");
    Y10 = 0;asm("nop");asm("nop");
    Y11 = 0;asm("nop");asm("nop");
    Y12 = 0;asm("nop");asm("nop");
    Y13 = 0;asm("nop");asm("nop");
    Y14 = 0;asm("nop");asm("nop");
    Y15 = 0;asm("nop");asm("nop");
    Y16 = 0;asm("nop");asm("nop");
    Y17 = 0;asm("nop");asm("nop");
    Y18 = 0;asm("nop");asm("nop");
    Y19 = 0;asm("nop");asm("nop");
    Y20 = 0;asm("nop");asm("nop");
    Y21 = 0;asm("nop");asm("nop");
    Y22 = 0;asm("nop");asm("nop");
    Y23 = 0;asm("nop");asm("nop");
    Y24 = 0;asm("nop");asm("nop");
    Y25 = 0;asm("nop");asm("nop");
    Y26 = 0;asm("nop");asm("nop");
    Y27 = 0;asm("nop");asm("nop");
    Y28 = 0;asm("nop");asm("nop");
    Y29 = 0;asm("nop");asm("nop");
    Y30 = 0;asm("nop");asm("nop");    
    Y31 = 0;asm("nop");asm("nop");   
    Y32 = 0;asm("nop");asm("nop");       
}

void Initial_OutputPortsHigh(void)
{
    Y1 = 1;asm("nop");asm("nop");
    Y2 = 1;asm("nop");asm("nop");
    Y3 = 1;asm("nop");asm("nop");
    Y4 = 1;asm("nop");asm("nop");
    Y5 = 1;asm("nop");asm("nop");
    Y6 = 1;asm("nop");asm("nop");
    Y7 = 1;asm("nop");asm("nop");
    Y8 = 1;asm("nop");asm("nop");
    Y9 = 1;asm("nop");asm("nop");
    Y10 = 1;asm("nop");asm("nop");
    Y11 = 1;asm("nop");asm("nop");
    Y12 = 1;asm("nop");asm("nop");
    Y13 = 1;asm("nop");asm("nop");
    Y14 = 1;asm("nop");asm("nop");
    Y15 = 1;asm("nop");asm("nop");
    Y16 = 1;asm("nop");asm("nop");
    Y17 = 1;asm("nop");asm("nop");
    Y18 = 1;asm("nop");asm("nop");
    Y19 = 1;asm("nop");asm("nop");
    Y20 = 1;asm("nop");asm("nop");
    Y21 = 1;asm("nop");asm("nop");
    Y22 = 1;asm("nop");asm("nop");
    Y23 = 1;asm("nop");asm("nop");
    Y24 = 1;asm("nop");asm("nop");
    Y25 = 1;asm("nop");asm("nop");
    Y26 = 1;asm("nop");asm("nop");
    Y27 = 1;asm("nop");asm("nop");
    Y28 = 1;asm("nop");asm("nop");
    Y29 = 1;asm("nop");asm("nop");
    Y30 = 1;asm("nop");asm("nop");
    Y31 = 1;asm("nop");asm("nop");
    Y32 = 1;asm("nop");asm("nop");
}

//extern void ClearClothesLengthLongKeyReleaseCheck(void);


#define DYNAMIC_STORE_TIME 10000//10Sec
unsigned int DynamicStoreTimer=0;
void DynamicStoreRunTimeData(void)
{
    DynamicStoreTimer++;
    if( DynamicStoreTimer >= DYNAMIC_STORE_TIME )
    {
        DynamicStoreTimer = 0;
        //SaveRunTimeStatus();
    }
}

extern void ShowRunTimeDisplay(void);
extern void StartCOM3SendCommand(void);
extern unsigned char IsReadEEPROM_DataFinish(void);
extern void ScanInputPort(void);
extern void COM3_SendControl(void);
extern void Get_uCHMI_DateCodeSend(void);

unsigned char OneMiliSecFlag;
unsigned char StartupFinsihFlag = 0;

void SystemControl(void)
{ 
    switch(SystemInitialState)
    {
        case SystemLoadSystemParameterEnum :           
#ifndef ANDROID_HMI            
            Send_uCHMI_ControllerFirmwareVersion();
#endif            
            LoadSystemParameter(SYSTEM_PARAMETER_START_ADDR);
            DelayTimerCounter[ParameterLoadTimeEnum] = 1000;//Philip 20220510 0.0.1
//Philip 20220510 0.0.1            LoadRunTimeStatus();
//            Fill_TestParameter();            
            SystemInitialState = waitSystemLoadSystemParameterEnum;
            break;
        case waitSystemLoadSystemParameterEnum :
//Philip 20220510 0.0.1 ===================================================================            
            if( IsReadEEPROM_DataFinish() == 1 )
            {
                LoadRunTimeStatus();
                DelayTimerCounter[ParameterLoadTimeEnum] = 1000;
                SystemInitialState = waitSystemLoadRunTimeStatusEnum;
            }
            else if( DelayTimerCounter[ParameterLoadTimeEnum] == 0 )
                ;//Show Fault
            break;
//Philip 20220510 0.0.1 ===================================================================            
        case waitSystemLoadRunTimeStatusEnum :
            if( IsReadEEPROM_DataFinish() == 1 )
            {                
                COM3_Send_All_Command();
                DelayTimerCounter[ParameterLoadTimeEnum] = 2000;
//Philip 20220315 0.0.1 ==========================================================                
#ifdef ANDROID_HMI
                SystemInitialState = SystemStartRunningEnum;
#else                
                SystemInitialState = SystemFinishLoadSystemParamterEnum;
#endif
//Philip 20220315 0.0.1 ==========================================================                
            }
//Philip 20220510 0.0.1 ===================================================================
            else if( DelayTimerCounter[ParameterLoadTimeEnum] == 0 )
                ;//Show Fault
//Philip 20220510 0.0.1 ===================================================================            
            break;
        case SystemFinishLoadSystemParamterEnum :
            if( (StartupFinsihFlag == 1) || (DelayTimerCounter[ParameterLoadTimeEnum] == 0) )
            {
                OneMiliSecFlag = 0;
                Get_uCHMI_DateCodeSend();
//                INIT_EXT_IO();
                SystemInitialState = SystemStartRunningEnum;
            }
            break;
        case SystemStartRunningEnum :
            COM2_SendControl();
            COM3_SendControl();
            if( OneMiliSecFlag == 1 )
            {
                ScanInputPort();
                ShowRunTimeDisplay();
                OneMiliSecFlag = 0;
            }
            break;
    }
    
    CommandParsingProcess();        
    SEND_U3_RS422_CMD_Process();    
    SEND_U2_RS422_CMD_Process();
    SEND_U1_RS422CMD_Process();
    RunEEPROM_ReadWriteProcess();
}







