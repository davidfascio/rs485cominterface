////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplayDevice.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDisplayDevice.h"

//**********************************************************************
// Variables
//**********************************************************************
volatile SCREEN_DISPLAY_7_SEG ScreenDisplay7SegControl;
volatile int ScreenDisplay7SegBuffer[SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE];
volatile int ScreenDisplay7SegBufferLen = SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE;

int ScreenDisplay7SegUpdateLed = LOW;
TIMER_STRUCT ScreenDisplay7SegTimer;

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
void ScreenDisplayDevice_Setup(char * data, int dataLen){
	
	ScreenDispla7Seg_Setup(&ScreenDisplay7SegControl, data, dataLen,  ScreenDisplay7SegBuffer, ScreenDisplay7SegBufferLen);
	
	/* Install Commands*/	
	ScreenDisplayCommands_AddCommad(ScreenDisplayDevice_UpdateStringValue);
	ScreenDisplayCommands_AddCommad(ScreenDisplayDevice_LEDStatus);
	
	// Timer
	AddTimer(&ScreenDisplay7SegTimer,SCREEN_DISPLAY_DEVICE_DEFAULT_TIMER_REFRESH_MS_VALUE);
	
	bsp_pin_mode(SCREEN_DISPLAY_DEVICE_LED_UPDATE_INDICATOR, OUTPUT);
	
}

void ScreenDisplayDevice_Update(void){
	
	if(Timer_GetOverflow(&ScreenDisplay7SegTimer) == TRUE) {
		
		ScreenDisplay7SegUpdateLed = (ScreenDisplay7SegUpdateLed == LOW )? HIGH : LOW;
		bsp_io_write(SCREEN_DISPLAY_DEVICE_LED_UPDATE_INDICATOR, ScreenDisplay7SegUpdateLed);
		ScreenDispla7Seg_Update(&ScreenDisplay7SegControl);
		Timer_Reset(&ScreenDisplay7SegTimer);
	}
}
/*int ScreenDisplayDevice_Update(float data){
	return ScreenDispla7Seg_UpdateData(&ScreenDisplay7SegControl, data);
}*/

int ScreenDisplayDevice_UpdateStringData(char * data, int dataLen){
	return ScreenDispla7Seg_UpdateStringData(&ScreenDisplay7SegControl, data, dataLen);
}

// DEMO
int LEDStatus(int status){
		
	bsp_pin_mode(BSP_PIN_A2, OUTPUT);	
	
	if( status == LOW || status == HIGH ){
		bsp_io_write(BSP_PIN_A2, status);  		 	
	}
		
	return status;
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
    
    //! Upper Cast Implementation for ScreenDisplayDevice_LEDStatus Command	
	//!
	//! Notice:
	//! 	- *data is integer type
	//! 	- dataSize is sizeof(int)
	//!
	//! memcpy((char *) &command_parameter , data, sizeof(command_parameter));
	
	int command_parameter = 0;
	
	COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);              	
	
	if((commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_LED_STATUS) && 
		dataSize == sizeof(command_parameter)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_LED_STATUS);
		
		memcpy((char *) &command_parameter , data, sizeof(command_parameter));
		
		commandErrorCodeResponse = LEDStatus(command_parameter);
		
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}
/*
COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_UpdateValue(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- *data is float type
	//! 	- dataSize is sizeof(float)
	//!
	//! memcpy((char *) &command_parameter , data, sizeof(command_parameter));
	
	float command_parameter = 0;
    
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_FLOAT_VALUE_UPDATE) && 
		dataSize == sizeof(command_parameter)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_FLOAT_VALUE_UPDATE);
		
		memcpy((char *) &command_parameter , data, sizeof(command_parameter));
		
		commandErrorCodeResponse = ScreenDisplayDevice_Update(command_parameter);
		
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}*/

COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_UpdateStringValue(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- *data is char * type
	//! 	- dataSize is strlen(char *)
	//!
	//! 
	
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_FLOAT_VALUE_UPDATE)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_FLOAT_VALUE_UPDATE);
		
		//memcpy((char *) &command_parameter , data, sizeof(command_parameter));
		
		commandErrorCodeResponse = ScreenDisplayDevice_UpdateStringData(data, dataSize);
		
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}
