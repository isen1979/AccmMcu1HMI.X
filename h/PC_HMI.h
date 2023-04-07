/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PC_HMI_H
#define	PC_HMI_H

enum PC_HMI_CommandEnum
{
    PC_HMI_NoCommand=0,
    PC_HMI_GET_DAC_Setting_Command,//1
    PC_HMI_GET_DAC_PW_Command,
    PC_HMI_GET_MachineStatus_Command,
    PC_HMI_GET_MachineRunTimeStatus_Command,
    PC_HMI_GetFirmwareVersionCommand,    
    PC_HMI_SetSystemParameterCommand,
    PC_HMI_SetEncoderParameterCommand,
    PC_HMI_SetSystemLengthParameterCommand,
    PC_HMI_SetDetectorParamterCommand,
           
    PC_HMI_CommandEnumEnd
};


enum PC_HMI_PacketEnum
{
    PC_HMI_PacketCmd=0,
    PC_HMI_PacketItem1stEnum,
    PC_HMI_PacketItem2ndEnum,
    PC_HMI_PacketItem3rdEnum,
    PC_HMI_PacketItem4thEnum,
    PC_HMI_PacketItem5thEnum,
    PC_HMI_PacketItem6thEnum,
    PC_HMI_PacketItem7thEnum,
    PC_HMI_PacketItem8thEnum,
        
    PC_HMI_crcHB,
    PC_HMI_crcLB,
    
    PC_HMI_PacketEnumEnd
};

enum PC_HMI_Send_CommandResponseEnum
{
    PC_HMI_NoNeedCommandResponseEnum=0,
    PC_HMI_GetFirmwareCommandResponseEnum,
    PC_HMI_SendLookBackCommandResponseEnum,
    
    PC_HMI_GetSendCommandResponseEnumEnd
};

enum PC_HMI_Send_ControllerStatusEnum
{
    PC_HMI_Send_InputOutputStatusEnum=0,
    
    PC_HMI_Send_ControllerStatusEnumEnd
};

enum PC_HMI_SendResponseEnum
{
    PC_HMI_InitialSendResponseEnum=0,
    PC_HMI_SendControllerResponeEnum,
    PC_HMI_WaitResponseSendOutEnum,
    PC_HMI_WaitNextResponseEnum,
    
    PC_HMI_SendResponseEnumEnd
};

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* PC_HMI_H */

