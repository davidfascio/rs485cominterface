/*
 * File: ScreenMasterCommands.h
 * Author: fascio
 * 
 * Created on December 19th, 2014, 15:50
 */ 
 
#ifndef __SCREEN_MASTER_COMMANDS_H__
#define __SCREEN_MASTER_COMMANDS_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "CommonSystemLibraries.h"

//**********************************************************************
// Defines
//**********************************************************************
#define SCREEN_MASTER_COMMADS_MAX_SUPPORTED_COMMANDS					(8)
#define SCREEN_MASTER_COMMADS_MAX_SUPPORTED_COMMANDS_OVERFLOW			(-1)

// Command Id
#define SCREEN_MASTER_COMMADS_NO_COMMAND_ID						 		(0)

// BUFFER PROPERTIES
#define SCREEN_MASTER_COMMANDS_MAX_BUFFER_RESPONSE_LEN					(20)


// Error Code List
#define SCREEN_MASTER_COMMANDS_ERROR_CODE_BASE							(900)

#define SCREEN_MASTER_COMMADS_NO_ERROR_CODE								(SCREEN_MASTER_COMMANDS_ERROR_CODE_BASE + 0)
#define SCREEN_MASTER_COMMANDS_COMMAND_ID_NOT_FOUND_ERROR_CODE			(SCREEN_MASTER_COMMANDS_ERROR_CODE_BASE + 1)			
#define SCREEN_MASTER_COMMANDS_SLAVE_ADDRESS_DID_NOT_RESPONSE_ERROR_CODE (SCREEN_MASTER_COMMANDS_ERROR_CODE_BASE + 2)			
#define SCREEN_MASTER_COMMANDS_PARAMETER_BAD_FORMAT_ERROR_CODE			(SCREEN_MASTER_COMMANDS_ERROR_CODE_BASE + 3)			
#define SCREEN_MASTER_COMMANDS_TIMEOUT_EXPIRED_ERROR_CODE				(SCREEN_MASTER_COMMANDS_ERROR_CODE_BASE + 4)			

//**********************************************************************
// Vartypes
//**********************************************************************

typedef struct master_command_result_struct{
	int commandIdResponse;	
	char commandBufferResponse[SCREEN_MASTER_COMMANDS_MAX_BUFFER_RESPONSE_LEN];
	int commandBufferResponseLen;
	int commandErrorCodeResponse;
} MASTER_COMMAND_RESPONSE_STRUCT, * MASTER_COMMAND_RESPONSE_STRUCT_PTR_;

typedef void  (* SCREEN_MASTER_COMMANDS_FUNCTION )(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl,
													char slaveAddress, int commandId, char * data);

//**********************************************************************
// Setters and Getters Prototype Functions
//**********************************************************************
void ScreenMasterCommands_SetCommandIdResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, int commandIdResponse);
int ScreenMasterCommands_GetCommandIdResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl);

void ScreenMasterCommands_SetCommandBufferResponseLen(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, int commandBufferResponseLen);
int ScreenMasterCommands_GetCommandBufferResponseLen(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl);

void ScreenMasterCommands_SetCommandBufferResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, char * commandBufferResponse, int commandBufferResponseLen);
char * ScreenMasterCommands_GetCommandBufferResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl);

void ScreenMasterCommands_SetCommandErrorCodeResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, int commandErrorCodeResponse);
int ScreenMasterCommands_GetCommandErrorCodeResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl);

void ScreenMasterCommands_MasterCommandResponseSetup(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl);

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenMasterCommands_Setup(void);
int	 ScreenMasterCommands_AddCommad(SCREEN_MASTER_COMMANDS_FUNCTION CommadFunction);
void ScreenMasterCommands_ExecCommand(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl,
									  char slaveAddress, int commandId, char * data);

#endif /* __SCREEN_MASTER_COMMANDS_H__ */
