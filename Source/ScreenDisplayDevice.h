/*
 * File: ScreenDisplayDevice.h
 * Author: fascio
 * 
 * Created on November 21th, 2014, 12:50
 */ 
 
#ifndef __SCREEN_DISPLAY_DEVICE_H__
#define __SCREEN_DISPLAY_DEVICE_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "Timer.h"
#include "ScreenDisplay7Seg.h"
#include "ScreenDisplayCommands.h"
#include "ScreenDisplayDeviceCommandList.h"
#include "Config.h"
#include "ScreenDisplayProtocol.h"

//**********************************************************************
// Defines
//**********************************************************************
#define SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE						  (4)
#define SCREEN_DISPLAY_DEVICE_DEFAULT_TIMER_REFRESH_MS_VALUE	   (1000)
#define SCREEN_DISPLAY_DEVICE_DEFAULT_UPDATE_VALUE_TIMEOUT_MS	  (60000) // Minute *Configurable 

#define SCREEN_DISPLAY_DEVICE_LED_UPDATE_INDICATOR 			(BSP_NO_PIN) //(BSP_PIN_A1)

#define SCREEN_DISPLAY_DEVICE_EMPTY_BUFFER							(-1)
//**********************************************************************
// Setters and Getters Prototype Functions
//**********************************************************************
void ScreenDisplayDevice_SetDisplay7SegBufferLen(int bufferLen);
int ScreenDisplayDevice_GetDisplay7SegBufferLen(void);

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
char * ScreenDisplayDevice_GetStringData(void);
int ScreenDisplayDevice_GetStringDataLen(void);

void ScreenDisplayDevice_Setup(void);
void ScreenDisplayDevice7Seg_Setup(void);
void ScreenDisplayDevice_Clear(void);
//void ScreenDisplayDevice_Setup(char * data, int dataLen, int display7segbuffersize);
void ScreenDisplayDevice_Update(void);
void ScreenDisplayDevice_Error(void);

int ScreenDisplayDevice_UpdateStringData(char * data, int dataLen);

//**********************************************************************
// Command List Fucntions
//
// Acoording to this pattern:
//
// COMMAND_RESPONSE_STRUCT (* SCREEN_DISPLAY_COMMANDS_FUNCTION )(int commandId, char * data, int dataSize)
//
// More Information see ScreenDisplayCommands.h library
//**********************************************************************
COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_LEDStatus(int commandId, char * data, int dataSize);
//COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_UpdateValue(int commandId, char * data, int dataSize);
COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_UpdateStringValue(int commandId, char * data, int dataSize);
COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_GetStringValue(int commandId, char * data, int dataSize);

int LEDStatus(int status);


////////////////////////// CONFIGURATION COMMANDS //////////////////////

COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_SetDeviceConfiguration(int commandId, char * data, int dataSize);
COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_GetDeviceConfiguration(int commandId, char * data, int dataSize);


#endif /* __SCREEN_DISPLAY_DEVICE_H__  */
