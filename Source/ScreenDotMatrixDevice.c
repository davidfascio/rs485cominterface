////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplayDevice.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDotMatrixDevice.h"

//**********************************************************************
// Variables
//**********************************************************************
//! DEFAULT PARAMMENTERS     	
volatile char ComAddress 					 		= SCREEN_DISPLAY_PROTOCOL_DEFAULT_SLAVE_ADDRESS;	
volatile char * DotMatrix_Message  					= SCREEN_DOT_MATRIX_ERROR_MESSAGE;
volatile SCREEN_DOT_MATRIX_EFFECT DotMatrix_Effect 	= SCREEN_DOT_MATRIX_ERROR_EFFECT;

TIMER_STRUCT ScreenDotMatrixUpdateValueTimeOut;
//**********************************************************************
// API Fucntions
//**********************************************************************
void ScreenDotMatrixDevice_Setup(void){
	
	//! LOAD CONFIGURATION
	//******************************************************************
	//*
	//* It needs to use setup function:
	//*
	//*		void DeviceConfig_Setup( char device_id, char device_size)
	//*
	//******************************************************************
	if(DeviceConfig_IsKeySet()){
		
		ComAddress = DeviceConfig_GetID();					// Slave Address
		//ScreenDisplay7SegBufferLen = DeviceConfig_GetSize();	// Buffer Size
	}
	
	//! AFTER SETUP
	ScreenDisplayProtocol_Setup(ComAddress);
	
	ScreenDotMatrix_Setup(DotMatrix_Message, strlen(DotMatrix_Message), DotMatrix_Effect);
	
	/* Install Commands*/		
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_SendTextFunction);
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_SendTextWithCustomDelayFunction);
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_GetTextWithCustomDelayFunction);
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_LEDStatusFunction);
	
	/* Install Configuration Commands */	
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_SetDeviceConfiguration); // Set Configuration
	ScreenDisplayCommands_AddCommad(ScreenDotMatrixDevice_GetDeviceConfiguration); // Get Configuration
	
	// Timer
	AddTimer(&ScreenDotMatrixUpdateValueTimeOut,SCREEN_DOT_MATRIX_DEVICE_DEFAULT_UPDATE_VALUE_TIMEOUT_MS);	
}


void ScreenDotMatrixDevice_Update(void){
	
	ScreenDotMatrix_Render();
	
	//! Communication Protocol Process 		
	//ScreenDisplayProtocol_WaitDataPacketCheck();
	ScreenDisplayProtocol_StateMachineUpdate();		
	ScreenDisplayProtocol_ProcessingDataPacketArrived();			
	
	if((Timer_GetOverflow(&ScreenDotMatrixUpdateValueTimeOut) == TRUE) &&
		(ScreenDotMatrix_GetErrorData() == FALSE)) {				
	
		ScreenDotMatrixDevice_Error();
		Timer_Reset(&ScreenDotMatrixUpdateValueTimeOut);
	}
}

void ScreenDotMatrixDevice_Error(void){		
	
	ScreenDotMatrix_SendTextWithCustomDelay(DotMatrix_Message, strlen(DotMatrix_Message), DotMatrix_Effect, SCREEN_DOT_MATRIX_DEFAULT_TIMER_VALUE_IN_MS);
	ScreenDotMatrix_SetErrorData(TRUE);	
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

int ScreenDotMatrixDevice_SendTextWithCustomDelay(char *text, int textLen, int effect, int delay_in_ms){
	
	SCREEN_DOT_MATRIX_EFFECT dotMatrixEffect = ParseIntToEffect(effect);
	
	ScreenDotMatrix_SetErrorData(FALSE);	
	Timer_Reset(&ScreenDotMatrixUpdateValueTimeOut);
	
	return ScreenDotMatrix_SendTextWithCustomDelay(text, textLen,  dotMatrixEffect, delay_in_ms);	
}

int ScreenDotMatrixDevice_SendText(char *text, int textLen, int effect){
	
	SCREEN_DOT_MATRIX_EFFECT dotMatrixEffect = ParseIntToEffect(effect);
	
	ScreenDotMatrix_SetErrorData(FALSE);	
	Timer_Reset(&ScreenDotMatrixUpdateValueTimeOut);
	
	return ScreenDotMatrix_SendText(text, textLen,  dotMatrixEffect);	
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
	int command_parameter_text_len;
    
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_SEND_TEXT) && 
		dataSize > sizeof(command_parameter_effect)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_SEND_TEXT);
		
		memcpy((char *) &command_parameter_effect , data, sizeof(command_parameter_effect));
		command_parameter_text = data + sizeof(command_parameter_effect);
		
		command_parameter_text_len = dataSize - (command_parameter_text - data);
		
		commandErrorCodeResponse = ScreenDotMatrixDevice_SendText(command_parameter_text, command_parameter_text_len, command_parameter_effect);
		
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
	int command_parameter_text_len;
    
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_SEND_TEXT_DELAY) && 
		dataSize > sizeof(command_parameter_effect)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_SEND_TEXT_DELAY);
		
		command_parameter_text = data ;
		memcpy((char *) &command_parameter_effect , command_parameter_text, sizeof(command_parameter_effect));
		
		command_parameter_text += sizeof(	command_parameter_effect);
		memcpy((char *) &command_parameter_delay_ms , command_parameter_text, sizeof(command_parameter_delay_ms));
		
		command_parameter_text +=  sizeof(command_parameter_effect);
		command_parameter_text_len = dataSize - (command_parameter_text - data);
		
		commandErrorCodeResponse = ScreenDotMatrixDevice_SendTextWithCustomDelay(command_parameter_text,command_parameter_text_len, command_parameter_effect, command_parameter_delay_ms);
		
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


////////////////////////// CONFIGURATION COMMANDS //////////////////////
		
COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_SetDeviceConfiguration(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- *data is char * type
	//! 	- dataSize is strlen(char *)
	//!
	//! 
	char command_parameter0;
	char command_parameter1;
	char * dataptr = data;
	
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == DEVICE_CONFIG_SET_CONFIG_MASTER_COMMAND_ID) &&
		dataSize == (2 * SIZE_OF_CHAR)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, DEVICE_CONFIG_SET_CONFIG_SLAVE_COMMAND_ID);
		
		memcpy((char *) &command_parameter0 , dataptr, SIZE_OF_CHAR);
		dataptr = dataptr + SIZE_OF_CHAR;
		
		memcpy((char *) &command_parameter1 , dataptr, SIZE_OF_CHAR);
		
		
		commandErrorCodeResponse = DeviceConfig_SetConfiguration(command_parameter0,command_parameter1);
		
		if (commandErrorCodeResponse == DEVICE_CONFIG_NO_ERROR_CODE)
		{
			
			ComAddress = command_parameter0;
			
			
			// Update Information
			ScreenDisplayProtocol_SetComAddress(ComAddress);	
			ScreenDotMatrix_Setup(DotMatrix_Message, strlen(DotMatrix_Message), DotMatrix_Effect);
		}
		
		ScreenDisplayCommands_SetCommandBufferResponse(&CommandResponseControl,(char *) &commandErrorCodeResponse,sizeof(commandErrorCodeResponse));				
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	
	return	CommandResponseControl;		
}

		
COMMAND_RESPONSE_STRUCT ScreenDotMatrixDevice_GetDeviceConfiguration(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- *data is char * type
	//! 	- dataSize is strlen(char *)
	//!
	//! 
	char command_parameter0;
	char command_parameter1;
	char command_response[10];
	
	char * dataptr = data;
	
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == DEVICE_CONFIG_GET_CONFIG_MASTER_COMMAND_ID) &&
		dataSize == ( SIZE_OF_CHAR)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, DEVICE_CONFIG_GET_CONFIG_SLAVE_COMMAND_ID);
		
		
		commandErrorCodeResponse = DeviceConfig_GetConfiguration(&command_parameter0,&command_parameter1);
		
		memset(command_response, 0 ,sizeof(command_response));
		memcpy(command_response, &command_parameter0, SIZE_OF_CHAR);
		memcpy(command_response + SIZE_OF_CHAR, &command_parameter1, SIZE_OF_CHAR);
		
		ScreenDisplayCommands_SetCommandBufferResponse(&CommandResponseControl,(char *) command_response,2* SIZE_OF_CHAR);				
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	
	return	CommandResponseControl;		
}

////////////////////////// CONFIGURATION COMMANDS //////////////////////
