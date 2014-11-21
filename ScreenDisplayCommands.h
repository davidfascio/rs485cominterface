/*
 * File: ScreenDisplayProtocol.h
 * Author: fascio
 * 
 * Created on November 20th, 2014, 16:22
 */ 
 
#ifndef __SCREEN_DISPLAY_COMMANDS_H__
#define __SCREEN_DISPLAY_COMMANDS_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "CommonSystemLibraries.h"

//**********************************************************************
// Defines
//**********************************************************************
#define SCREEN_DISPLAY_COMMADS_MAX_SUPPORTED_COMMANDS				(8)

// Error code
#define SCREEN_DISPLAY_COMMADS_MAX_SUPPORTED_COMMANDS_OVERFLOW		(-1)

// Command Id
#define SCREEN_DISPLAY_COMMADS_NO_COMMAND_ID						 (0)

//**********************************************************************
// Vartypes
//**********************************************************************

typedef struct command_result_struct{
	int commandIdResponse;
	int commandErrorCodeResponse;
} COMMAND_RESPONSE_STRUCT, * COMMAND_RESPONSE_STRUCT_PTR_;

typedef (COMMAND_RESPONSE_STRUCT )  (* SCREEN_DISPLAY_COMMANDS_FUNCTION )(int commandId, char * data, int dataSize);

//**********************************************************************
// Setters and Getters Prototype Functions
//**********************************************************************
void ScreenDisplayCommands_SetCommandIdResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl, int commandIdResponse);
int ScreenDisplayCommands_GetCommandIdResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl);

void ScreenDisplayCommands_SetCommandErrorCodeResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl, int commandErrorCodeResponse);
int ScreenDisplayCommands_GetCommandErrorCodeResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl);

void ScreenDisplayCommands_Setup(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl);

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenDisplayCommands_Setup(void);
int	ScreenDisplayCommands_AddCommad(SCREEN_DISPLAY_COMMANDS_FUNCTION CommadFunction);
COMMAND_RESPONSE_STRUCT  ScreenDisplayCommands_ExecCommand(int commandId, char * data, int dataSize);

////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplayCommands.c
//
// #include "ScreenDisplayCommands.h"
//

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

void ScreenDisplayCommands_SetCommandErrorCodeResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl, int commandErrorCodeResponse){
	
	CommandIdResponseControl->commandErrorCodeResponse = commandErrorCodeResponse;
}

int ScreenDisplayCommands_GetCommandErrorCodeResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl){

	return CommandIdResponseControl->commandErrorCodeResponse;
}

void ScreenDisplayCommands_Setup(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl){
	
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
		
	int index;
	COMMAND_RESPONSE_STRUCT CommandResponseControl;
	
	ScreenDisplayCommands_Setup(&CommandResponseControl);
	
	while(ScreenDisplayCommands_GetCommandIdResponse(&CommandResponseControl) == SCREEN_DISPLAY_COMMADS_NO_COMMAND_ID &&
			index < ScreenDisplayComands_NumberOfCommandFunctions) {
		
		CommadResponseControl = ScreenDisplayComands_CommandFunction[index](commandId, data, dataSize);
	}
	
	return CommandResponseControl;
}

#endif /* __SCREEN_DISPLAY_COMMANDS_H__ */
