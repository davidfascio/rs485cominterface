/*
 * File: ScreenDotMatrixDevice.h
 * Author: fascio
 * 
 * Created on December 2nd, 2014, 09:18
 */ 

#ifndef __SCREEN_DOT_MATRIX_DEVICE_H__
#define __SCREEN_DOT_MATRIX_DEVICE_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDotMatrix.h"
#include "ScreenDisplayCommands.h"
#include "ScreenDisplayDeviceCommandList.h"

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenDotMatrixDevice_Setup(void);
void ScreenDotMatrixDevice_Update(void);

int ScreenDotMatrixDevice_LEDStatus(int status);
SCREEN_DOT_MATRIX_EFFECT ParseIntToEffect(int effect);

int ScreenDotMatrixDevice_SendTextWithCustomDelay(char *text,  int effect, int delay_in_ms);
int ScreenDotMatrixDevice_SendText(char *text, int effect);

//**********************************************************************
// Command List Fucntions
//
// Acoording to this pattern:
//
// COMMAND_RESPONSE_STRUCT (* SCREEN_DISPLAY_COMMANDS_FUNCTION )(int commandId, char * data, int dataSize)
//
// More Information see ScreenDisplayCommands.h library
//**********************************************************************
COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_LEDStatusFunction(int commandId, char * data, int dataSize);
COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_SendTextFunction(int commandId, char * data, int dataSize);
COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_SendTextWithCustomDelayFunction(int commandId, char * data, int dataSize);


#endif /* __SCREEN_DOT_MATRIX_DEVICE_H__ */
