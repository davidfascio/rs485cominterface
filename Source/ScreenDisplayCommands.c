////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplayCommands.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDisplayCommands.h"

//**********************************************************************
// Variables
//**********************************************************************
SCREEN_DISPLAY_COMMANDS_FUNCTION ScreenDisplayComands_CommandFunction[SCREEN_DISPLAY_COMMADS_MAX_SUPPORTED_COMMANDS];
int ScreenDisplayComands_NumberOfCommandFunctions;

//**********************************************************************
// Setters and Getters Prototype Functions
//**********************************************************************
void ScreenDisplayCommands_SetCommandIdResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl, int commandIdResponse){
	
	CommandIdResponseControl->commandIdResponse = commandIdResponse;
}

int ScreenDisplayCommands_GetCommandIdResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl){
	
	return CommandIdResponseControl->commandIdResponse;
}

void ScreenDisplayCommands_SetCommandBufferResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl, char * commandBufferResponse, int commandBufferResponseLen){	
	
	if (commandBufferResponse == NULL)
		return;
	
	if(commandBufferResponseLen > SCREEN_DISPLAY_COMMANDS_MAX_BUFFER_RESPONSE_LEN)	
		return;
	
	memset(CommandIdResponseControl->commandBufferResponse, 0, SCREEN_DISPLAY_COMMANDS_MAX_BUFFER_RESPONSE_LEN);
	memcpy(CommandIdResponseControl->commandBufferResponse, commandBufferResponse, commandBufferResponseLen);
	CommandIdResponseControl->commandBufferResponseLen = commandBufferResponseLen;
}

char * ScreenDisplayCommands_GetCommandBufferResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl){

	return CommandIdResponseControl->commandBufferResponse;
}

int ScreenDisplayCommands_GetCommandBufferResponseLen(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl){

	return CommandIdResponseControl->commandBufferResponseLen;
}

void ScreenDisplayCommands_SetCommandErrorCodeResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl, int commandErrorCodeResponse){
	
	CommandIdResponseControl->commandErrorCodeResponse = commandErrorCodeResponse;
}

int ScreenDisplayCommands_GetCommandErrorCodeResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl){

	return CommandIdResponseControl->commandErrorCodeResponse;
}

void ScreenDisplayCommands_CommandResponseSetup(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl){
	
	memset(CommandIdResponseControl, 0, sizeof(COMMAND_RESPONSE_STRUCT));	
}

//**********************************************************************
// API Fucntions
//**********************************************************************

void ScreenDisplayCommands_Setup(void){
	
	memset(ScreenDisplayComands_CommandFunction, 0, sizeof(ScreenDisplayComands_CommandFunction));
	ScreenDisplayComands_NumberOfCommandFunctions = 0;	
}

int ScreenDisplayCommands_AddCommad(SCREEN_DISPLAY_COMMANDS_FUNCTION CommadFunction){
	
	if(ScreenDisplayComands_NumberOfCommandFunctions >= SCREEN_DISPLAY_COMMADS_MAX_SUPPORTED_COMMANDS)
		return SCREEN_DISPLAY_COMMADS_MAX_SUPPORTED_COMMANDS_OVERFLOW;
	
	ScreenDisplayComands_CommandFunction[ScreenDisplayComands_NumberOfCommandFunctions] = CommadFunction;	
	ScreenDisplayComands_NumberOfCommandFunctions++;
		
	return ScreenDisplayComands_NumberOfCommandFunctions;	
}

COMMAND_RESPONSE_STRUCT  ScreenDisplayCommands_ExecCommand(int commandId, char * data, int dataSize){
		
	volatile int index = 0;
	
	volatile COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);
	
	while(ScreenDisplayCommands_GetCommandIdResponse(&CommandResponseControl) == SCREEN_DISPLAY_COMMADS_NO_COMMAND_ID &&
			index < ScreenDisplayComands_NumberOfCommandFunctions) {
		
		CommandResponseControl = ScreenDisplayComands_CommandFunction[index](commandId, data, dataSize);
		index++;
	}
	
	return CommandResponseControl;
}
