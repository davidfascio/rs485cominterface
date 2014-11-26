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
#include "ScreenDisplay7Seg.h"
#include "ScreenDisplayCommands.h"
#include "ScreenDisplayDeviceCommandList.h"

//**********************************************************************
// Defines
//**********************************************************************
#define SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE						 (4)

//**********************************************************************
// Setters and Getters Prototype Functions
//**********************************************************************
void ScreenDisplayDevice_SetDisplay7SegBufferLen(int bufferLen);
int ScreenDisplayDevice_GetDisplay7SegBufferLen(void);

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenDisplayDevice_Setup(void);
int ScreenDisplayDevice_Update(float data);

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
COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_UpdateValue(int commandId, char * data, int dataSize);

int LEDStatus(int status);

#endif /* __SCREEN_DISPLAY_DEVICE_H__  */