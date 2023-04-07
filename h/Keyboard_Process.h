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

#define MACHINE_RUN_FWD_BTN 0x0001
#define MACHINE_RUN_REV_BTN 0x0002
#define MACHINE_RUN_STOP_BTN 0x0004
//#define TENSION_MINUS_BTN 0x0008
//#define TENSION_FINE_MINUS_BTN 0x0010
//#define TENSION_MINUS_BTN 0x0008
//#define TENSION_PLUS_BTN 0x0010
#define SENDER_RUN_FWD_JOG_BTN 0x0008
#define SENDER_RUN_REV_JOG_BTN 0x0010
#define TENSION_MINUS_BTN 0x0020
#define TENSION_PLUS_BTN 0x0040
#define ATTACH_CLOTHES_BTN 0x0080
#define CLOTHES_CENTERIZE_BTN 0x0100
//#define CLOTHES_FWD_REV_FEED_SEL_BTN 0x0200
//#define FEED_CLOTHES_SYNC_IND_SEL_BTN 0x0400
//#define TOP_BOTTOM_FEED_SEL_BTN 0x0800
//#define BOTTOM_FWD_REV_FEED_SEL_BTN 0x1000
//#define BOTTOM_FWD_FEED_JOG_BTN 0x2000
//#define BOTTOM_REV_FEED_JOG_BTN 0x4000
//#define BOTTOM_FEED_SYNC_IND_SEL_BTN 0x8000

enum KeyboardScanEnum
{
    WaitKeyboardPressEnum=0,
    WaitTensionFwdMinusReleaseEnum,//WaitTensionFineMinusReleaseEnum,
    WaitTensionFwdPlusReleaseEnum,//WaitTensionFinePlusReleaseEnum,
    WaitSenderFwdReleaseEnum,//WaitTensionMinusReleaseEnum,
    WaitSenderRevReleaseEnum,//WaitTensionPlusReleaseEnum,
    WaitTensionFwdLongMinusReleaseEnum,//WaitTensionLongMinusReleaseEnum,
    WaitTensionFwdLongPlusReleaseEnum,//WaitTensionLongPlusReleaseEnum,
    WaitTensionRevLongMinusReleaseEnum,
    WaitTensionRevLongPlusReleaseEnum,
    WaitFWD_BtnReleaseEnum,
    WaitREV_BtnReleaseEnum,
    WaitStopBtnReleaseEnum,
    WaitAttachClothesBtnReleaseEnum,//WaitClearEncoderBtnReleaseEnum,
    WaitLeadClothesBtnReleaseEnum,//WaitClothesCenterizedBtnReleaseEnum,
    WaitAll_KeyReleaseEnum,
        
    KeyboardScanEnumEnd
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

#endif	/* XC_HEADER_TEMPLATE_H */

