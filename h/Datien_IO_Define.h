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
#ifndef DATIEN_IO_DEFINE_H
#define	DATIEN_IO_DEFINE_H
//Input Action Define
#define INPUT_ACTION 0
#define INPUT_NO_ACTION 1

//Output Action Define
#define OUTPUT_ACTION 1
#define OUTPUT_NO_ACTION 0
#define OUTPUT_ACTION_A 1
#define OUTPUT_ACTION_B 0
#define OUTPUT_NO_ACTION_A 0
#define OUTPUT_NO_ACTION_B 1


typedef struct __DatienINPUT_PORTH
{
   
    unsigned  dummy1_8 : 8;
    
    unsigned IN8  : 1;
    unsigned IN9 : 1;
    unsigned IN10 : 1;
    unsigned IN11 : 1;
    unsigned IN12 : 1;
    unsigned IN13 : 1;
    unsigned IN14 : 1;
    unsigned IN15 : 1;
} _DatienINPUT_PORTH;

typedef struct __DatienINPUT_PORTD
{
//TM14    
    unsigned IN0 : 1;//Philip 20181211 01  //BLOWER_MOTOR_ACTION_SELECTION_L : 1;//D_IN32//X33
    unsigned IN1 : 1;//D_IN33//X34
    unsigned IN2 : 1;//D_IN34//X35
    unsigned IN3 : 1;//D_IN35//X37
    unsigned IN4 : 1;//D_IN36//X38
    unsigned IN5 : 1;//D_IN37//X39
    unsigned IN6 : 1;//D_IN38//X40
    unsigned IN7 : 1;
  
    unsigned char Dummy8_15; 
} _DatienINPUT_PORTD;


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

#endif	/* DATIEN_IO_DEFINE_H */

