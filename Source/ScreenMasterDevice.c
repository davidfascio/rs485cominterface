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
	ScreenMasterCommands_AddCommad(ScreenMasterDisplayDevice_LEDStatus);
	
	ScreenMasterCommands_AddCommad(ScreenMasterDotMatrixDevice_SendTextFunction);
	ScreenMasterCommands_AddCommad(ScreenMasterDotMatrixDevice_SendTextWithCustomDelayFunction);	
	ScreenMasterCommands_AddCommad(ScreenMasterDotMatrixDevice_GetTextWithCustomDelayFunction);	
	
	ScreenMasterCommands_AddCommad(ScreenMasterDisplayDevice_UpdateValue);
	ScreenMasterCommands_AddCommad(ScreenMasterDisplayDevice_GetValue);
	
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
															SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES);
															
        
	
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
	char dotMatrixParameters [20];	
	char * 	dotMatrixParametersIndex = dotMatrixParameters;
	int dotMatrixEffect;
	//char dotMatrixMessage[10];											  	
	char * dotMatrixMessageBegin;
	char * dotMatrixMessageEnd;
	int dotMatrixMessageLen;
	
	
	volatile int commandProcessed;
	int response;
	volatile char buffer[10];
	
	if (commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_SEND_TEXT)
	{			
		dotMatrixEffect = str2uint(data, 1, 10);	
		
		
		dotMatrixMessageBegin = strchr(data, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR) + 1;
		dotMatrixMessageEnd = strrchr(data, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);			
		
		
		if ((dotMatrixEffect < 0) || 
			(dotMatrixMessageBegin == NULL) || 
			(dotMatrixMessageBegin > dotMatrixMessageEnd)){			
	
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_PARAMETER_BAD_FORMAT_ERROR_CODE);					
			
			return;
		}
		
		memset(dotMatrixParametersIndex, 0, sizeof(dotMatrixParameters));
		
		memcpy(dotMatrixParametersIndex, (char *) &dotMatrixEffect, sizeof(dotMatrixEffect));
		
		dotMatrixParametersIndex += sizeof(dotMatrixEffect);
		dotMatrixMessageLen = dotMatrixMessageEnd - dotMatrixMessageBegin;
		memcpy(dotMatrixParametersIndex, dotMatrixMessageBegin, dotMatrixMessageLen);		
		
		dotMatrixParametersIndex += dotMatrixMessageLen;
		
		commandProcessed = ScreenDisplayProtocol_SendDataPackWaitForResponse(	slaveAddress, 
															commandId, 
															dotMatrixParameters, 
															dotMatrixParametersIndex - dotMatrixParameters, 
															SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_SEND_TEXT, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES);
															
        
	
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
													
void ScreenMasterDotMatrixDevice_SendTextWithCustomDelayFunction(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
																char slaveAddress, int commandId, char * data){

	char dotMatrixParameters [20];	
	char * 	dotMatrixParametersIndex = dotMatrixParameters;
	int dotMatrixEffect;
	int dotMatrixDelay;
	//char dotMatrixMessage[10];											  	
	char * dotMatrixMessageBegin;
	char * dotMatrixMessageEnd;
	int dotMatrixMessageLen;
	
	
	volatile int commandProcessed;
	int response;
	volatile char buffer[10];
	
	if (commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_SEND_TEXT_DELAY)
	{			
		dotMatrixEffect = str2uint(data, 1, 10);	
		
		
		dotMatrixMessageBegin = strchr(data, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR) + 1;
		dotMatrixMessageEnd = strchr(dotMatrixMessageBegin, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);			
		dotMatrixMessageLen = dotMatrixMessageEnd - dotMatrixMessageBegin;
		
		if ((dotMatrixEffect < 0) || 
			(dotMatrixMessageBegin == NULL) || 
			(dotMatrixMessageLen <= 0)){			
	
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_PARAMETER_BAD_FORMAT_ERROR_CODE);					
			
			return;
		}
		
		dotMatrixDelay = str2uint(dotMatrixMessageBegin, dotMatrixMessageLen, 10);
		
		dotMatrixMessageBegin = strchr(dotMatrixMessageEnd, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR) + 1;
		dotMatrixMessageEnd = strchr(dotMatrixMessageBegin, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);			
		dotMatrixMessageLen = dotMatrixMessageEnd - dotMatrixMessageBegin;
		
		if ((dotMatrixDelay < 0) || 
			(dotMatrixMessageBegin == NULL) || 
			(dotMatrixMessageLen <= 0)){			
	
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_PARAMETER_BAD_FORMAT_ERROR_CODE);					
			
			return;
		}
		
		memset(dotMatrixParametersIndex, 0, sizeof(dotMatrixParameters));
		
		memcpy(dotMatrixParametersIndex, (char *) &dotMatrixEffect, sizeof(dotMatrixEffect));
		
		dotMatrixParametersIndex += sizeof(dotMatrixEffect);
		memcpy(dotMatrixParametersIndex, (char * ) &dotMatrixDelay, sizeof(dotMatrixDelay));		
		
		dotMatrixParametersIndex += sizeof(dotMatrixDelay);
		memcpy(dotMatrixParametersIndex, dotMatrixMessageBegin, dotMatrixMessageLen);		
		
		dotMatrixParametersIndex += dotMatrixMessageLen;
		
		commandProcessed = ScreenDisplayProtocol_SendDataPackWaitForResponse(	slaveAddress, 
															commandId, 
															dotMatrixParameters, 
															dotMatrixParametersIndex - dotMatrixParameters, 
															SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_SEND_TEXT_DELAY, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES);
															
        
	
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

void ScreenMasterDisplayDevice_LEDStatus(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
										char slaveAddress, int commandId, char * data){

	int parameter = 0;
	volatile int commandProcessed;
	int response;
	volatile char buffer[10];
	
	if (commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_LED_STATUS)
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
															SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_LED_STATUS, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES);
															
        
	
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

void ScreenMasterDisplayDevice_UpdateValue(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
											char slaveAddress, int commandId, char * data){

	char displayParameters [20];	
	char * 	displayParametersIndex = displayParameters;
	float  displayValue;
	//char dotMatrixMessage[10];											  	
	char * displayValueBegin;
	char * displayValueEnd;
	int displayValueLen;
	
	
	
	volatile int commandProcessed;
	int response;
	volatile char buffer[10];
	
	if (commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_FLOAT_VALUE_UPDATE)
	{			
		//dotMatrixMessageBegin = strchr(data, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR) + 1;
		displayValueBegin = data;
		displayValueEnd = strrchr(data, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
		displayValueLen = displayValueEnd - displayValueBegin;
		
		if ((displayValueBegin == NULL) || 
			(displayValueLen <= 0)){			
	
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_PARAMETER_BAD_FORMAT_ERROR_CODE);					
			
			return;
		}
		
		memset(displayParameters, 0, sizeof(displayParameters));		
		memcpy(displayParametersIndex, displayValueBegin, displayValueLen);		
		displayParametersIndex += displayValueLen;
		
		commandProcessed = ScreenDisplayProtocol_SendDataPackWaitForResponse(	slaveAddress, 
															commandId, 
															displayParameters, 
															displayParametersIndex - displayParameters, 
															SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_FLOAT_VALUE_UPDATE, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES);
															
        
	
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

//////////////////////
void ScreenMasterDotMatrixDevice_GetTextWithCustomDelayFunction(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
																char slaveAddress, int commandId, char * data){

	char dotMatrixParameters [20];	
	char * 	dotMatrixParametersIndex = dotMatrixParameters;
	int dotMatrixEffect;
	int dotMatrixDelay;
	//char dotMatrixMessage[10];											  	
	char * dotMatrixMessageBegin;
	char * dotMatrixMessageEnd;
	int dotMatrixMessageLen;
	
	
	volatile int commandProcessed;	
	
	volatile char buffer[50];
	char * bufferIndex;
	int bufferLen;
    
    char parameterBuffer[20];
	int parameterBufferLen = sizeof(parameterBuffer);
	
	if (commandId == SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_GET_TEXT_DELAY)
	{
		dotMatrixMessageBegin = data;
		dotMatrixMessageEnd = strchr(dotMatrixMessageBegin, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);			
		dotMatrixMessageLen = dotMatrixMessageEnd - dotMatrixMessageBegin;
		
		if ((dotMatrixMessageBegin == NULL) || 
			(dotMatrixMessageLen <= 0)){			
	
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_PARAMETER_BAD_FORMAT_ERROR_CODE);					
			
			return;
		}
		
		
		
		
		
		memset(dotMatrixParametersIndex, 0, sizeof(dotMatrixParameters));		
		
		memcpy(dotMatrixParametersIndex, dotMatrixMessageBegin, dotMatrixMessageLen);		
		
		dotMatrixParametersIndex += dotMatrixMessageLen;
		
		commandProcessed = ScreenDisplayProtocol_SendDataPackWaitForResponse(	slaveAddress, 
															commandId, 
															dotMatrixParameters, 
															dotMatrixParametersIndex - dotMatrixParameters, 
															SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_GET_TEXT_DELAY, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES);
															
        
	
		if (commandProcessed != COM_485_PROTOCOL_PACKET_RECEIVED){
			
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_SLAVE_ADDRESS_DID_NOT_RESPONSE_ERROR_CODE);			
			return;
		}
		
		
		ScreenMasterCommands_SetCommandIdResponse(MasterCommandResponseControl,ScreenDisplayProtocol_GetCommandIdInPacketReceived());
		
		// Buildding data packet parameters
		
		dotMatrixParametersIndex = ScreenDisplayProtocol_GetDataInPacketReceived();		
		memcpy((char *) & dotMatrixEffect, dotMatrixParametersIndex, sizeof(dotMatrixEffect));	
		
		dotMatrixParametersIndex += sizeof(dotMatrixEffect);
		memcpy((char *) & dotMatrixDelay, dotMatrixParametersIndex, sizeof(dotMatrixDelay));	
		
		dotMatrixParametersIndex += sizeof(dotMatrixDelay);
		dotMatrixMessageBegin = dotMatrixParametersIndex;
		dotMatrixMessageLen = ScreenDisplayProtocol_GetDataInPacketReceivedLen() - 
							 (dotMatrixMessageBegin - ScreenDisplayProtocol_GetDataInPacketReceived());
		
		bufferIndex = buffer;			
		uint2str(dotMatrixEffect, parameterBuffer, parameterBufferLen);								
		strappendchar(parameterBuffer, parameterBufferLen, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);			
		memcpy(bufferIndex, parameterBuffer, strlen(parameterBuffer));	
		
		
		bufferIndex += strlen(parameterBuffer);			
		uint2str(dotMatrixDelay, parameterBuffer, parameterBufferLen);								
		strappendchar(parameterBuffer, parameterBufferLen, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);		
		memcpy(bufferIndex, parameterBuffer, strlen(parameterBuffer));	
		
		bufferIndex += strlen(parameterBuffer);			
		memset(parameterBuffer, 0, parameterBufferLen);
		memcpy(parameterBuffer, dotMatrixMessageBegin, dotMatrixMessageLen);		
		strappendchar(parameterBuffer, parameterBufferLen, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
		memcpy(bufferIndex, parameterBuffer, strlen(parameterBuffer));	
		
		bufferIndex += strlen(parameterBuffer);					
		bufferLen = bufferIndex - buffer;	
		
		ScreenMasterCommands_SetCommandBufferResponse(MasterCommandResponseControl,buffer, bufferLen);								
		ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, SCREEN_MASTER_COMMADS_NO_ERROR_CODE);								
	}													  
}

void ScreenMasterDisplayDevice_GetValue(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
											char slaveAddress, int commandId, char * data){

	char displayParameters [20];	
	char * 	displayParametersIndex = displayParameters;
	float  displayValue;
	//char dotMatrixMessage[10];											  	
	char * displayValueBegin;
	char * displayValueEnd;
	int displayValueLen;
	
	
	
	volatile int commandProcessed;
	int response; 
    
	volatile char buffer[10];
	char * bufferIndex;
	int bufferLen;
	
	if (commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_GET_VALUE)
	{			
		//dotMatrixMessageBegin = strchr(data, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR) + 1;
		displayValueBegin = data;
		displayValueEnd = strrchr(data, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
		displayValueLen = displayValueEnd - displayValueBegin;
		
		if ((displayValueBegin == NULL) || 
			(displayValueLen <= 0)){			
	
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_PARAMETER_BAD_FORMAT_ERROR_CODE);					
			
			return;
		}
		
		memset(displayParameters, 0, sizeof(displayParameters));		
		memcpy(displayParametersIndex, displayValueBegin, displayValueLen);		
		displayParametersIndex += displayValueLen;
		
		commandProcessed = ScreenDisplayProtocol_SendDataPackWaitForResponse(	slaveAddress, 
															commandId, 
															displayParameters, 
															displayParametersIndex - displayParameters, 
															SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_GET_VALUE, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT, 
															SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES);
															
        
	
		if (commandProcessed != COM_485_PROTOCOL_PACKET_RECEIVED){
			
			ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, 
															SCREEN_MASTER_COMMANDS_SLAVE_ADDRESS_DID_NOT_RESPONSE_ERROR_CODE);			
			return;
		}
		
		
		ScreenMasterCommands_SetCommandIdResponse(MasterCommandResponseControl,ScreenDisplayProtocol_GetCommandIdInPacketReceived());
		
		
		displayValueBegin = ScreenDisplayProtocol_GetDataInPacketReceived();
		displayValueLen   = ScreenDisplayProtocol_GetDataInPacketReceivedLen() - 
							(displayValueBegin - ScreenDisplayProtocol_GetDataInPacketReceived());
							 
		
		// Buildding data packet parameters
		bufferIndex = buffer;			
		memset(buffer, 0, sizeof(buffer));
		memcpy(bufferIndex, displayValueBegin, displayValueLen);		
		strappendchar(bufferIndex, sizeof(buffer), TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
		
		bufferIndex	+= strlen(bufferIndex);
		bufferLen = bufferIndex - buffer;					
		
		ScreenMasterCommands_SetCommandBufferResponse(MasterCommandResponseControl,buffer, bufferLen);		
		ScreenMasterCommands_SetCommandErrorCodeResponse(MasterCommandResponseControl, SCREEN_MASTER_COMMADS_NO_ERROR_CODE);								
	}								
}
