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

////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplayDevice.c
//
// #include "ScreenDisplayDevice.h"
//

//**********************************************************************
// Variables
//**********************************************************************

SCREEN_DISPLAY_7_SEG ScreenDisplay7SegControl;
int ScreenDisplay7SegBuffer[SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE];
int ScreenDisplay7SegBufferLen = SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE;

//**********************************************************************
// Setters and Getters Prototype Functions
//**********************************************************************
void ScreenDisplayDevice_SetDisplay7SegBufferLen(int bufferLen){
	
	if (bufferLen > SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE)
		return;
		
	ScreenDisplay7SegBufferLen = bufferLen;
}

int ScreenDisplayDevice_GetDisplay7SegBufferLen(void){
	
	return ScreenDisplay7SegBufferLen;
}

//**********************************************************************
// API Fucntions
//**********************************************************************
void ScreenDisplayDevice_Setup(void){
	
	ScreenDispla7Seg_Setup(&ScreenDisplay7SegControl, 1.63,  ScreenDisplay7SegBuffer, ScreenDisplay7SegBufferLen);
	
	/* Install Commands*/
	//ScreenDisplayCommands_AddCommad(ScreenDisplayDevice_LEDStatus);
	ScreenDisplayCommands_AddCommad(ScreenDisplayDevice_UpdateValue);
	
}

int ScreenDisplayDevice_Update(float data){
	return ScreenDispla7Seg_UpdateData(&ScreenDisplay7SegControl, data);
}

//**********************************************************************
// Command List Fucntions
//
// Acoording to this pattern:
//
// COMMAND_RESPONSE_STRUCT (* SCREEN_DISPLAY_COMMANDS_FUNCTION )(int commandId, char * data, int dataSize)
//
// More Information see ScreenDisplayCommands.h library
//**********************************************************************

COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_LEDStatus(int commandId, char * data, int dataSize){
	
	COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);
	
	if((commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_LED_STATUS) && 
		dataSize == sizeof(int)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_LED_STATUS);
				
		commandErrorCodeResponse = LEDStatus((int) *data);
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}


// DEMO
int LEDStatus(int status){
		
	bsp_pin_mode(BSP_PIN_A1, OUTPUT);	
	
	if( status == LOW || status == HIGH ){
		bsp_io_write(BSP_PIN_A1, status);  		 	
	}
		
	return status;
}


COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_UpdateValue(int commandId, char * data, int dataSize){
	
	COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);
	
	if((commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_FLOAT_VALUE_UPDATE) && 
		dataSize == sizeof(float)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_FLOAT_VALUE_UPDATE);
		
		commandErrorCodeResponse = ScreenDisplayDevice_Update((float) *data);
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}

#endif /* __SCREEN_DISPLAY_DEVICE_H__  */
