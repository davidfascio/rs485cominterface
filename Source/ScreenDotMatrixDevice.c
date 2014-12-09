////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplayDevice.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDotMatrixDevice.h"

//**********************************************************************
// API Fucntions
//**********************************************************************
void ScreenDotMatrixDevice_Setup(void){
	
	ScreenDotMatrix_Setup();
	
	/* Install Commands*/	
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_LEDStatusFunction);
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_SendTextFunction);
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_SendTextWithCustomDelayFunction);
	
}


void ScreenDotMatrixDevice_Update(void){
	
	ScreenDotMatrix_Render();
}


// DEMO
int ScreenDotMatrixDevice_LEDStatus(int status){
		
	bsp_pin_mode(BSP_PIN_A2, OUTPUT);	
	
	if( status == LOW || status == HIGH ){
		bsp_io_write(BSP_PIN_A2, status);  		 	
	}
		
	return status;
}

SCREEN_DOT_MATRIX_EFFECT ParseIntToEffect(int effect){
	
	switch(effect){
		
		case 0:
			return STATIC_TEXT;
				
		case 1:
			return DYNAMIC_LEFT;
					
		case 2:
			return DYNAMIC_RIGHT;
					
		default:
			return NO_EFFECT;		
	}
}

int ScreenDotMatrixDevice_SendTextWithCustomDelay(char *text,  int effect, int delay_in_ms){
	
	SCREEN_DOT_MATRIX_EFFECT dotMatrixEffect = ParseIntToEffect(effect);
	return ScreenDotMatrix_SendTextWithCustomDelay(text,  dotMatrixEffect, delay_in_ms);	
}

int ScreenDotMatrixDevice_SendText(char *text, int effect){
	
	SCREEN_DOT_MATRIX_EFFECT dotMatrixEffect = ParseIntToEffect(effect);
	return ScreenDotMatrix_SendText(text,  dotMatrixEffect);	
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

COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_LEDStatusFunction(int commandId, char * data, int dataSize){
    
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
	
	if((commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_LED_STATUS) && 
		dataSize == sizeof(command_parameter)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_LED_STATUS);
		
		memcpy((char *) &command_parameter , data, sizeof(command_parameter));
		
		commandErrorCodeResponse = ScreenDotMatrixDevice_LEDStatus(command_parameter);
		
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}

COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_SendTextFunction(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDotMatrixDevice_SendTextFunction Command	
	//!
	//! Notice:
	//! 	- 
	//! 	- 
	//!
	//! memcpy((char *) &command_parameter , data, sizeof(command_parameter));
	
	int command_parameter_effect = 0;
	char * command_parameter_text;
    
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_SEND_TEXT) && 
		dataSize > sizeof(command_parameter_effect)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_SEND_TEXT);
		
		memcpy((char *) &command_parameter_effect , data, sizeof(command_parameter_effect));
		command_parameter_text = data + sizeof(command_parameter_effect);
		
		commandErrorCodeResponse = ScreenDotMatrixDevice_SendText(command_parameter_text, command_parameter_effect);
		
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}



COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_SendTextWithCustomDelayFunction(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- 
	//! 	- 
	//!
	//! memcpy((char *) &command_parameter , data, sizeof(command_parameter));
	
	int command_parameter_effect = 0;
    int command_parameter_delay_ms = SCREEN_DOT_MATRIX_DEFAULT_TIMER_VALUE_IN_MS;
	char * command_parameter_text;
    
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_SEND_TEXT_DELAY) && 
		dataSize > sizeof(command_parameter_effect)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_SEND_TEXT_DELAY);
		command_parameter_text = data ;
		memcpy((char *) &command_parameter_effect , command_parameter_text, sizeof(command_parameter_effect));
		
		command_parameter_text += sizeof(command_parameter_effect);
		memcpy((char *) &command_parameter_delay_ms , command_parameter_text, sizeof(command_parameter_delay_ms));
		
		command_parameter_text +=  sizeof(command_parameter_effect);
		
		commandErrorCodeResponse = ScreenDotMatrixDevice_SendTextWithCustomDelay(command_parameter_text, command_parameter_effect, command_parameter_delay_ms);
		
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}
