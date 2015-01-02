/*
 * File: ScreenDisplayCommands.h
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

typedef COMMAND_RESPONSE_STRUCT  (* SCREEN_DISPLAY_COMMANDS_FUNCTION )(int commandId, char * data, int dataSize);

//**********************************************************************
// Setters and Getters Prototype Functions
//**********************************************************************
void ScreenDisplayCommands_SetCommandIdResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl, int commandIdResponse);
int ScreenDisplayCommands_GetCommandIdResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl);

void ScreenDisplayCommands_SetCommandErrorCodeResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl, int commandErrorCodeResponse);
int ScreenDisplayCommands_GetCommandErrorCodeResponse(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl);

void ScreenDisplayCommands_CommandResponseSetup(COMMAND_RESPONSE_STRUCT_PTR_ CommandIdResponseControl);

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenDisplayCommands_Setup(void);
int	ScreenDisplayCommands_AddCommad(SCREEN_DISPLAY_COMMANDS_FUNCTION CommadFunction);
COMMAND_RESPONSE_STRUCT  ScreenDisplayCommands_ExecCommand(int commandId, char * data, int dataSize);

#endif /* __SCREEN_DISPLAY_COMMANDS_H__ */
