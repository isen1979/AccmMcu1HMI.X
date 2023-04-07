/*
 * File:   RunTimeDisplayControl.c
 * Author: user
 *
 * Created on 2021年4月15日, 下午 3:51
 */

#include "System_Control.h"

extern void uC_HMI_Send_FAN1_Display(void);
extern void uC_HMI_Send_FAN2_Display(void);
extern void uC_HMI_Send_SCR_Display(void);
extern void uC_HMI_Send_PCD20_Display(void);
extern void uC_HMI_Send_MTR4_Display(void);
extern void uC_HMI_Send_Other_Display(void);

extern _FAN1_1_RUNTIME_DISPLAY lastFAN1_1_RunTimeDisplay, FAN1_1_RunTimeDisplay;
extern _FAN2_RUNTIME_DISPLAY lastFAN2_RunTimeDisplay, FAN2_RunTimeDisplay;
extern _SCR_RUNTIME_DISPLAY SCR_RunTimeDisplay, lastSCR_RunTimeDisplay;
extern _MTR4_RUNTIME_DISPLAY MTR4_RunTimeDisplay, lastMTR4_RunTimeDisplay;
extern _PCD20_RUNTIME_DISPLAY PCD20_RunTimeDisplay, lastPCD20_RunTimeDisplay;
extern _OTHER_RUNTIME_DISPLAY OtherRunTimeDisplay, lastOtherRunTimeDisplay;

void ShowFAN1_RunTimeDisplayControl(void)
{
    if( (lastFAN1_1_RunTimeDisplay.RealPressure != FAN1_1_RunTimeDisplay.RealPressure) || (lastFAN1_1_RunTimeDisplay.PID_Output != FAN1_1_RunTimeDisplay.PID_Output) ||
        (lastFAN1_1_RunTimeDisplay.RealFreq != FAN1_1_RunTimeDisplay.RealFreq) || (lastFAN1_1_RunTimeDisplay.Current != FAN1_1_RunTimeDisplay.Current) ||
        (lastFAN1_1_RunTimeDisplay.ErrorCode!= FAN1_1_RunTimeDisplay.ErrorCode) )
    {
        lastFAN1_1_RunTimeDisplay.RealPressure = FAN1_1_RunTimeDisplay.RealPressure;
        lastFAN1_1_RunTimeDisplay.PID_Output = FAN1_1_RunTimeDisplay.PID_Output;
        lastFAN1_1_RunTimeDisplay.RealFreq = FAN1_1_RunTimeDisplay.RealFreq;
        lastFAN1_1_RunTimeDisplay.Current = FAN1_1_RunTimeDisplay.Current;
        lastFAN1_1_RunTimeDisplay.ErrorCode = FAN1_1_RunTimeDisplay.ErrorCode;
        uC_HMI_Send_FAN1_Display();
    }
}

void ShowFAN2_RunTimeDisplayControl(void)
{
    if( (lastFAN2_RunTimeDisplay.SV != FAN2_RunTimeDisplay.SV) || (lastFAN2_RunTimeDisplay.RealSpeed != FAN2_RunTimeDisplay.RealSpeed) || 
        (lastFAN2_RunTimeDisplay.TE12 != FAN2_RunTimeDisplay.TE12) || (lastFAN2_RunTimeDisplay.Current != FAN2_RunTimeDisplay.Current) )
    {
        lastFAN2_RunTimeDisplay.SV = FAN2_RunTimeDisplay.SV;
        lastFAN2_RunTimeDisplay.RealSpeed = FAN2_RunTimeDisplay.RealSpeed;
        lastFAN2_RunTimeDisplay.TE12 = FAN2_RunTimeDisplay.TE12;
        lastFAN2_RunTimeDisplay.Current = FAN2_RunTimeDisplay.Current;
        uC_HMI_Send_FAN2_Display();
    }
}

void SCR_RunTimeDisplayContorl(void)
{
    if( (lastSCR_RunTimeDisplay.TE11 != SCR_RunTimeDisplay.TE11) || (lastSCR_RunTimeDisplay.TE14 != SCR_RunTimeDisplay.TE14) ||
        (lastSCR_RunTimeDisplay.OvenSP != SCR_RunTimeDisplay.OvenSP) || (lastSCR_RunTimeDisplay.OvenSV != SCR_RunTimeDisplay.OvenSV) ||
        (lastSCR_RunTimeDisplay.RealOutputPercent != SCR_RunTimeDisplay.RealOutputPercent) )
    {
        lastSCR_RunTimeDisplay.TE11 = SCR_RunTimeDisplay.TE11;
        lastSCR_RunTimeDisplay.TE14 = SCR_RunTimeDisplay.TE14;
        lastSCR_RunTimeDisplay.OvenSP = SCR_RunTimeDisplay.OvenSP;
        lastSCR_RunTimeDisplay.OvenSV = SCR_RunTimeDisplay.OvenSV;
        lastSCR_RunTimeDisplay.RealOutputPercent = SCR_RunTimeDisplay.RealOutputPercent;
        uC_HMI_Send_SCR_Display();
    }
}

void PCD20_RunTimeDisplayControl(void)
{
    if( (lastPCD20_RunTimeDisplay.TE3 != PCD20_RunTimeDisplay.TE3) || (lastPCD20_RunTimeDisplay.RealOpenSize != PCD20_RunTimeDisplay.RealOpenSize) ||
        (lastOtherRunTimeDisplay.PCD22_RealOpenSize != OtherRunTimeDisplay.PCD22_RealOpenSize) || 
        (lastOtherRunTimeDisplay.PCD25_RealOpenSize != OtherRunTimeDisplay.PCD25_RealOpenSize) )
    {
        lastPCD20_RunTimeDisplay.TE3 = PCD20_RunTimeDisplay.TE3;
        lastPCD20_RunTimeDisplay.RealOpenSize = PCD20_RunTimeDisplay.RealOpenSize;
        lastOtherRunTimeDisplay.PCD22_RealOpenSize = OtherRunTimeDisplay.PCD22_RealOpenSize;
        lastOtherRunTimeDisplay.PCD25_RealOpenSize = OtherRunTimeDisplay.PCD25_RealOpenSize;
        uC_HMI_Send_PCD20_Display();
    }
}

void ShowMTR4RunTimeDisplayControl(void)
{
    if( (lastMTR4_RunTimeDisplay.RealFreq != MTR4_RunTimeDisplay.RealFreq) || (lastMTR4_RunTimeDisplay.RPH != MTR4_RunTimeDisplay.RPH) || 
        (lastMTR4_RunTimeDisplay.TE5 != MTR4_RunTimeDisplay.TE5) || (lastMTR4_RunTimeDisplay.Current != MTR4_RunTimeDisplay.Current) ||
        (lastMTR4_RunTimeDisplay.ErrorCode != MTR4_RunTimeDisplay.ErrorCode) )
    {
        lastMTR4_RunTimeDisplay.RealFreq = MTR4_RunTimeDisplay.RealFreq;
        lastMTR4_RunTimeDisplay.RPH = MTR4_RunTimeDisplay.RPH;
        lastMTR4_RunTimeDisplay.TE5 = MTR4_RunTimeDisplay.TE5;
        lastMTR4_RunTimeDisplay.Current = MTR4_RunTimeDisplay.Current;
        lastMTR4_RunTimeDisplay.ErrorCode = MTR4_RunTimeDisplay.ErrorCode;
        uC_HMI_Send_MTR4_Display();
    }
}

void ShowRunTimeOtherDisplayControl(void)
{
    if( (lastOtherRunTimeDisplay.TE1 != OtherRunTimeDisplay.TE1) || (lastOtherRunTimeDisplay.TE6 != OtherRunTimeDisplay.TE6) ||
        (lastOtherRunTimeDisplay.TE8 != OtherRunTimeDisplay.TE8) || (lastOtherRunTimeDisplay.TE10 != OtherRunTimeDisplay.TE10) ||
        (lastOtherRunTimeDisplay.PDT1 != OtherRunTimeDisplay.PDT1) || (lastOtherRunTimeDisplay.PDT2 != OtherRunTimeDisplay.PDT2) ||
        (lastOtherRunTimeDisplay.PDT5 != OtherRunTimeDisplay.PDT5) )
    {
        lastOtherRunTimeDisplay.TE1 = OtherRunTimeDisplay.TE1;
        lastOtherRunTimeDisplay.TE6 = OtherRunTimeDisplay.TE6;
        lastOtherRunTimeDisplay.TE8 = OtherRunTimeDisplay.TE8;
        lastOtherRunTimeDisplay.TE10 = OtherRunTimeDisplay.TE10;
        lastOtherRunTimeDisplay.PDT1 = OtherRunTimeDisplay.PDT1;
        lastOtherRunTimeDisplay.PDT2 = OtherRunTimeDisplay.PDT2;
        lastOtherRunTimeDisplay.PDT5 = OtherRunTimeDisplay.PDT5;        
        uC_HMI_Send_Other_Display();    
    }
}

void ShowRunTimeDisplay(void)
{
    ShowFAN1_RunTimeDisplayControl();
    ShowFAN2_RunTimeDisplayControl();    
    SCR_RunTimeDisplayContorl();
    PCD20_RunTimeDisplayControl();
    ShowMTR4RunTimeDisplayControl();
    ShowRunTimeOtherDisplayControl();
}