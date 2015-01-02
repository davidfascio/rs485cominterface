////////////////////////////////////////////////////////////////////////
//
// File name: ScreenMasterDevice.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenMasterDevice.h"

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenMasterDevice_Setup(char ComAddress){
	
	ScreenDisplayProtocol_Setup(ComAddress);
	
	/* Install Commands*/	
	ScreenMasterCommands_AddCommad(ScreenMasterDotMatrixDevice_LEDStatusFunction);
	/*ScreenMasterCommands_AddCommad(ScreenMasterDotMatrixDevice_SendTextFunction);
	ScreenMasterCommands_AddCommad(ScreenMasterDotMatrixDevice_SendTextWithCustomDelayFunction);
	ScreenMasterCommands_AddCommad(ScreenMasterDisplayDevice_LEDStatus);
	ScreenMasterCommands_AddCommad(ScreenMasterDisplayDevice_UpdateValue);	*/
}


//**********************************************************************
// Command List Fucntions
//
// Acoording to this pattern:
//
// void  (* SCREEN_MASTER_COMMANDS_FUNCTION )(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, char slaveAddress, int commandId, char * data);
//
// More Information see ScreenDisplayCommands.h library
//**********************************************************************

void ScreenMasterDotMatrixDevice_LEDStatusFunction(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
													char slaveAddress, int commandId, char * data){
	int parameter = 0;
	volatile int commandProcessed;
	int response;
	volatile char buffer[10];
	
	if (commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_LED_STATUS)
	{			
		parameter = str2uint(data, 1, 10);	
		
		if (parameter < 0){			
	
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_PARAMETER_BAD_FORMAT_ERROR_CODE);					
			
			return;
		}
		
		
		commandProcessed = ScreenDisplayProtocol_SendDataPackWaitForResponse(	slaveAddress, 
															commandId, 
															(char *) &parameter, 
															sizeof(parameter), 
															SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_LED_STATUS, 
															COM_485_TIMER_DEFAULT_WAIT_VALUE_IN_MS, 
															COM_485_PROTOCOL_SEND_DATA_PACKET_WAIT_RESPONSE_DEFAULT_RETIES);
															
        
	
		if (commandProcessed != COM_485_PROTOCOL_PACKET_RECEIVED){
			
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_SLAVE_ADDRESS_DID_NOT_RESPONSE_ERROR_CODE);			
			return;
		}
		
		
		ScreenMasterCommands_SetCommandIdResponse(MasterCommandResponseControl,ScreenDisplayProtocol_GetCommandIdInPacketReceived());
		
		// Buildding data packet parameters
		memcpy((char *) & response, ScreenDisplayProtocol_GetDataInPacketReceived(), sizeof(int));				
		uint2str(response, buffer, sizeof(buffer));								
		strappendchar(buffer, sizeof(buffer), TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);		
		ScreenMasterCommands_SetCommandBufferResponse(MasterCommandResponseControl,buffer, strlen(buffer));				
				
		ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, SCREEN_MASTER_COMMADS_NO_ERROR_CODE);								
	}
}
													
void ScreenMasterDotMatrixDevice_SendTextFunction(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
												  char slaveAddress, int commandId, char * data){
													  
}
													
void ScreenMasterDotMatrixDevice_SendTextWithCustomDelayFunction(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
																char slaveAddress, int commandId, char * data){

}

void ScreenMasterDisplayDevice_LEDStatus(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
										char slaveAddress, int commandId, char * data){

}

void ScreenMasterDisplayDevice_UpdateValue(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
											char slaveAddress, int commandId, char * data){

}
