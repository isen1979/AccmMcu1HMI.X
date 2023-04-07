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
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#define SINGLE_ARM_POSITION_ACK_CHECK_TIME_OUT 1000//1Sec
#define SINGLE_ARM_POSITION_MOTOR_RUN_CHECK_DELAY 1000//1Sec
#define SINGLE_ARM_POSITION_MOTOR_RUN_TIME_OUT 30000//30Sec
#define RUN_STACK_MAX_TIME_OUT 90000//90sec


#define SERVO_MOTOR_MAX_RPM 3000
#define START_AXIS_CARD_RUNNING_SIGNA_L_ID 15 

enum MachineArmControlStateEnum
{
    WaitMachineArmStartRunningEnum=0,
    
    MachineRunArmGoHomeEnum,
    MachineArmRunTestRunningEnum,
    MachineArmRunSingleArmPositionEnum,
    MachineArmRunTwoArmOneStartTheOtherDelayStartEnum,
    MachineArmThreeArmTrackingPositionEnum,
    MachineArmRunStackEnum,
    MachineArmRunSingleArmPositionSearchEnum,
    
    MachineArmControlStateEnumEnd
};
  
enum MachineArmGoHomeStateEnum
{    
    WaitMachineArmRunGoHomeEnum=0,
    
    MachineArmStartToGoHomeEnum,
    MachineArmDelayToCheckArriveHomeEnum,
    WaitMachineArmArriveHomeEnum,    
    
    MachineArmGoHomeStateEnumEnd
};

enum RunTestRunningStateEnum
{
    WaitRunTestRunningStateEnum=0,
    
    WaitStartRunJogContorlStateEnum,
    ServoMotorRunJogEnum,    
    ServoMotorStopRunJogEnum,
    WaitStartRunStepMoveControlStateEnum,
    ServoMotorStartStepMoveEnum,
    ServoMotorDoStepMoveRunningEnum,
    
    RunStepMoveControlStateEnumEnd
};

enum ThreeArmTrackingAxisEnum
{
    ThreeArmTrackingAxisYEnum=0,
    ThreeArmTrackingAxisXEnum,
    ThreeArmTrackingAxisZEnum,
    ThreeArmTrackingAxisX2Enum,
    ThreeArmTrackingAxisZ2Enum,
    ThreeArmTrackingAxisAEnum,
    ThreeArmTrackingAxisCEnum,
    
    ThreeArmTrackingAxisEnumEnd
};

enum GoHomeOrderEnum
{
    GoHomeOrderNANEnum=0,
    GoHomeOrderAxisY_Enum,
    GoHomeOrderAxisA_Enum,
    GoHomeOrderAxisX_Enum,
    GoHomeOrderAxisZ_Enum,
    GoHomeOrderAxisX2_Enum,
    GoHomeOrderAxisZ2_Enum,

    GoHomeOrderAxis_7_Enum,
    GoHomeOrderAxis_8_Enum,
    GoHomeOrderAxis_9_Enum,
    GoHomeOrderAxis_10_Enum,  
    
    GoHomeOrderEnumEnd
};

typedef struct __SERVO_ALARM_STATUS_BITMAP
{
    unsigned char ServoMotorGoHomeState : 1;
    unsigned char MachineArmNowState : 5;    
    unsigned char Dummy1 : 2;
    unsigned char Dummy2 : 8;
    
} _SERVO_ALARM_STATUS_BITMAP;

typedef union __SERVO_ALARM_STATUS
{
    _SERVO_ALARM_STATUS_BITMAP bitmap;
    unsigned char Byte[2];
} _SERVO_ALARM_STATUS;

typedef struct __SINGLE_ARM_POSITION_OPTION
{
    unsigned char axis : 4;
    unsigned char option : 2;
    unsigned char type : 2;
} _SINGLE_ARM_POSITION_OPTION;

typedef struct __SINGLE_ARM_POSITION_DATA
{    
    unsigned char MainRunningSpeedRatio;
    unsigned char FinalSpeedRatio;
    long TargetPosition;
    long ChangeSpeedPosition;     
    
    _SINGLE_ARM_POSITION_OPTION PositionOption;
} _SINGLE_ARM_POSITION_DATA;

typedef union __SINGLE_ARM_POSITION
{
    _SINGLE_ARM_POSITION_DATA SingleArmPositionData;
    unsigned char DataByte[11];
} _SINGLE_ARM_POSITION;


typedef struct __TWO_ARM_DELAY_TRACK_POSITION_DATA
{    
    unsigned char TrackingOrReferenceArm : 6;
    unsigned char Type : 2;
    unsigned char TrackingArm : 6;
    unsigned char TypeBackup : 2;    
    unsigned char ReferenceArmSpeedRatio;
    unsigned char TrackingArmSpeedRatio;
    long ReferenceArmTargetPosition;
    long ReferenceArmOffset;
    long TrackingArmTargetPosition;
} _TWO_ARM_DELAY_TRACK_POSITION_DATA;//16Bytes

typedef union __TWO_ARM_DELAY_TRACK_POSITION
{
    _TWO_ARM_DELAY_TRACK_POSITION_DATA data;
    unsigned char ByteData[16];
} _TWO_ARM_DELAY_TRACK_POSITION;

typedef struct __THREE_ARM_TRACKING_POSITION_DATA
{
    unsigned char axis;
    unsigned char SpeedRatio;
    unsigned char Type;
    unsigned char Dummy;
    long TargetPosition;
    
    long TargetDistanceY;//TargetPositionY;
    long TargetDistanceA;//TargetPositionA;
    long TargetDistanceX;//TargetPositionX;
    long TargetDistanceZ;//TargetPositionZ;
    long TargetDistanceX2;//TargetPositionX2;
    long TargetDistanceZ2;//TargetPositionZ2;
    long TargetDistance_7;//TargetPosition_7;
    long TargetDistance_8;//TargetPosition_8;
    long TargetDistance_9;//TargetPosition_9;
    long TargetDistance_10;//TargetPosition_10;        
} _THREE_ARM_TRACKING_POSITION_DATA;

typedef union __THREE_ARM_TRACKING_POSITION
{
    _THREE_ARM_TRACKING_POSITION_DATA data;
    unsigned char ByteData[48];
} _THREE_ARM_TRACKING_POSITION;

typedef struct __SINGLE_ARM_SEARCH_DATA
{
//    unsigned char StopCheckPortH : 4;
//    unsigned char type : 1;
//    unsigned char axis : 3;
//    unsigned char StopCheckPortL;//2
    unsigned char Type : 4;
    unsigned char Axis : 4;//1
    unsigned char StopCheckPort : 4;
    unsigned char SlowCheckPort : 4;//2    
    unsigned char SpeedRatio;//3
    unsigned char LowSpeedRatio;//4
    
    long DecPosition;//8
    
//    unsigned int SlowCheckPort;//10
    
} _SINGLE_ARM_SEARCH_DATA;//1+1+1+1+4+2=10

typedef union __SINGLE_ARM_SEARCH
{
    unsigned char ByteData[8];//[10];
    _SINGLE_ARM_SEARCH_DATA data;
} _SINGLE_ARM_SEARCH;
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

#endif	/* XC_HEADER_TEMPLATE_H */

