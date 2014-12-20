////////////////////////////////////////////////////////////////////////
//
// File name: ScreenMasterCommands.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenMasterCommands.h"

//**********************************************************************
// Variables
//**********************************************************************
SCREEN_MASTER_COMMANDS_FUNCTION ScreenMasterCommands_CommandFunction[SCREEN_MASTER_COMMADS_MAX_SUPPORTED_COMMANDS];
int ScreenMasterCommands_NumberOfCommandFunctions;

//**********************************************************************
// Setters and Getters Prototype Functions
//**********************************************************************
void ScreenMasterCommands_SetCommandIdResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, int commandIdResponse){
	
	MasterCommandResponseControl->commandIdResponse = commandIdResponse;
}

int ScreenMasterCommands_GetCommandIdResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl){
	
	return MasterCommandResponseControl->commandIdResponse;
}

void ScreenMasterCommands_SetCommandBufferResponseLen(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, int commandBufferResponseLen){
	
	MasterCommandResponseControl->commandBufferResponseLen = commandBufferResponseLen;
}

int ScreenMasterCommands_GetCommandBufferResponseLen(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl){

	return	MasterCommandResponseControl->commandBufferResponseLen;
}

void ScreenMasterCommands_SetCommandBufferResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, char * commandBufferResponse, int commandBufferResponseLen){

	if ( commandBufferResponseLen > sizeof(MasterCommandResponseControl->commandBufferResponse))
		return;
		
	memset(MasterCommandResponseControl->commandBufferResponse, 0, sizeof(MasterCommandResponseControl->commandBufferResponse));
	memcpy(MasterCommandResponseControl->commandBufferResponse, commandBufferResponse, commandBufferResponseLen);
	
	ScreenMasterCommands_SetCommandBufferResponseLen(MasterCommandResponseControl, commandBufferResponseLen);
}

char * ScreenMasterCommands_GetCommandBufferResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl){
	
	return MasterCommandResponseControl->commandBufferResponse;
}

void ScreenMasterCommands_SetCommandErrorCodeResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, int commandErrorCodeResponse){
	
	MasterCommandResponseControl->commandErrorCodeResponse = commandErrorCodeResponse;
}

int ScreenMasterCommands_GetCommandErrorCodeResponse(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl){

	return MasterCommandResponseControl->commandErrorCodeResponse;
}

void ScreenMasterCommands_MasterCommandResponseSetup(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl){
	
	memset(MasterCommandResponseControl, 0, sizeof(MASTER_COMMAND_RESPONSE_STRUCT));
	ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, SCREEN_MASTER_COMMANDS_COMMAND_ID_NOT_FOUND_ERROR_CODE);
}

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenMasterCommands_Setup(void){
	
	memset(ScreenMasterCommands_CommandFunction, 0, sizeof(ScreenMasterCommands_CommandFunction));
	ScreenMasterCommands_NumberOfCommandFunctions = 0;	
}

int	ScreenMasterCommands_AddCommad(SCREEN_MASTER_COMMANDS_FUNCTION CommadFunction){
	
	if(ScreenMasterCommands_NumberOfCommandFunctions >= SCREEN_MASTER_COMMADS_MAX_SUPPORTED_COMMANDS)
		return SCREEN_MASTER_COMMADS_MAX_SUPPORTED_COMMANDS_OVERFLOW;
	
	ScreenMasterCommands_CommandFunction[ScreenMasterCommands_NumberOfCommandFunctions] = CommadFunction;	
	ScreenMasterCommands_NumberOfCommandFunctions++;
		
	return ScreenMasterCommands_NumberOfCommandFunctions;	
}

void  ScreenMasterCommands_ExecCommand(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
									   char slaveAddress, int commandId, char * data){
	
	volatile int index = 0;
	
	ScreenMasterCommands_MasterCommandResponseSetup(MasterCommandResponseControl);
	
	while(ScreenMasterCommands_GetCommandIdResponse(MasterCommandResponseControl) == SCREEN_MASTER_COMMADS_NO_COMMAND_ID &&
			index < ScreenMasterCommands_NumberOfCommandFunctions) {
		
		ScreenMasterCommands_CommandFunction[index](MasterCommandResponseControl, slaveAddress, commandId, data);
		index++;
	}	
}

