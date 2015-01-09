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
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_SendTextFunction);
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_SendTextWithCustomDelayFunction);
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_GetTextWithCustomDelayFunction);
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_LEDStatusFunction);
	
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

COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_GetTextWithCustomDelayFunction(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- 
	//! 	- 
	//!
	//! memcpy((char *) &command_parameter , data, sizeof(command_parameter));
	
	int command_parameter_effect;	
    int command_parameter_delay_ms;
	char * command_parameter_text;
	int command_parameter_text_len;
    
    char command_parammeters[50];
    char * command_parammeters_index;
    int command_parammeters_len;
    
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if(commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_GET_TEXT_DELAY){
		
		command_parameter_effect 	= ScreenDotMatrix_GetEffect();		
		command_parameter_delay_ms 	= ScreenDotMatrix_GetDelay_ms();
		command_parameter_text 		= ScreenDotMatrix_GetText();
		command_parameter_text_len 	= ScreenDotMatrix_GetTextLen();

		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_GET_TEXT_DELAY);
		
		if(command_parameter_text_len == 0){
			
			ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, SCREEN_DOT_MATRIX_DEVICE_EMPTY_BUFFER);
			return CommandResponseControl;
		}
			
		// Clear command_parameters buffer
		memset(command_parammeters, 0, sizeof(command_parammeters));
		
		// Filling command_parammeters
		command_parammeters_index = command_parammeters;
		memcpy(command_parammeters_index, (char * ) &command_parameter_effect, sizeof(command_parameter_effect));
		
		command_parammeters_index += sizeof(command_parameter_effect);
		memcpy(command_parammeters_index, (char * ) &command_parameter_delay_ms, sizeof(command_parameter_delay_ms));
		
		command_parammeters_index += sizeof(command_parameter_delay_ms);
		memcpy(command_parammeters_index, command_parameter_text, command_parameter_text_len);		
		
		command_parammeters_index += command_parameter_text_len;
		command_parammeters_len = command_parammeters_index - command_parammeters;
		
		ScreenDisplayCommands_SetCommandBufferResponse(&CommandResponseControl,command_parammeters, command_parammeters_len);				
		
	}
	
	return	CommandResponseControl;		
}
