/*
 * File:   Machine_uC_HMI_Parsing.c
 * Author: user
 *
 * Created on 2020年4月21日, 上午 11:05
 */
#include "..\h\SystemControl.h"
#include "uC_HMI_Control.h"

#define NUMBER_KEYBOARD_ENTER 0
#define NUMBER_KEYBOARD_CANCEL 100

_PARSING_DATA ParsingData;
_HMI_BUTTON_STATUS HMI_BtnStatus;

unsigned int RxTextBuffer[MAX_READ_TEXT_SIZE];
