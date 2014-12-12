/*
 * File: ScreenMasterDevice.h
 * Author: fascio
 * 
 * Created on December 11th, 2014, 15:58
 */ 


#ifndef __SCREEN_MASTER_DEVICE_H__
#define __SCREEN_MASTER_DEVICE_H__

//**********************************************************************
// Includes
//**********************************************************************

//!#include "ScreenDotMatrix.h"
#include "ScreenDisplayCommands.h"
#include "ScreenDisplayDeviceCommandList.h"

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenMasterDevice_Setup(void);
int ScreenMasterDevice_LEDStatus(int status);

/* For Dot Matrix Commands */
int ScreenMatrixDevice_SendTextWithCustomDelay(char *text,  int effect, int delay_in_ms);
int ScreenMatrixDevice_SendText(char *text, int effect);

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


#endif /* __SCREEN_MASTER_DEVICE_H__ */
