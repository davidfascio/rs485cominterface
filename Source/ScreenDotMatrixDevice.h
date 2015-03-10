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
#include "Config.h"
#include "ScreenDisplayProtocol.h"


#define SCREEN_DOT_MATRIX_DEVICE_EMPTY_BUFFER								(-1)
#define SCREEN_DOT_MATRIX_DEVICE_DEFAULT_UPDATE_VALUE_TIMEOUT_MS			(60000) // Minute
//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenDotMatrixDevice_Setup(void);
void ScreenDotMatrixDevice_Update(void);
void ScreenDotMatrixDevice_Error(void);

int ScreenDotMatrixDevice_LEDStatus(int status);
SCREEN_DOT_MATRIX_EFFECT ParseIntToEffect(int effect);

int ScreenDotMatrixDevice_SendTextWithCustomDelay(char *text, int textLen, int effect, int delay_in_ms);
int ScreenDotMatrixDevice_SendText(char *text, int textLen, int effect);

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
COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_GetTextWithCustomDelayFunction(int commandId, char * data, int dataSize);

COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_SetDeviceConfiguration(int commandId, char * data, int dataSize);
COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_GetDeviceConfiguration(int commandId, char * data, int dataSize);

#endif /* __SCREEN_DOT_MATRIX_DEVICE_H__ */
