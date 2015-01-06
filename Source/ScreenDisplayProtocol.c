////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplayProtocol.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDisplayProtocol.h"

//**********************************************************************
// Variables
//**********************************************************************
COM_485_PROTOCOL_STRUCT ScreenDisplayProtocolControl;

//**********************************************************************
// API Fucntions
//**********************************************************************

void ScreenDisplayProtocol_Setup(char ComAddress ){
	
	Com485Protocol_Setup(&ScreenDisplayProtocolControl, BSP_USART_COM_HDLR, ComAddress, SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT);
	ScreenDisplayCommands_Setup();
}

void ScreenDisplayProtocol_WaitDataPacketCheck(void){
	
	Com485Protocol_WaitDataPacket(&ScreenDisplayProtocolControl, SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT);
}

void ScreenDisplayProtocol_ProcessingDataPacketArrived(void){
	
	volatile int 	Handler;
	volatile char 	ComAddress;
	
	volatile int 	TotalDataSize;
	
	volatile int 	PacketSize;
	volatile char 	SlaveAddress;	
	volatile int 	CommandID;
	volatile int 	DataPacketSize;
	volatile char * cpPacketData;
	
	volatile int 	CommandIdResponse;
	volatile int 	CommandErrorCodeResponse;
	
	volatile COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	volatile int commandErrorCodeResponse;
	
	
	if(Com485Protocol_GetDataPacketArrived(&ScreenDisplayProtocolControl)) 
	{
		ComAddress 		= Com485Protocol_GetComAddress(&ScreenDisplayProtocolControl);	
		SlaveAddress 	= Com485Protocol_GetSlaveAddressInPacketReceived(&ScreenDisplayProtocolControl);	
		
		// Verifying Slave Address with Device Address
		if (ComAddress == SlaveAddress ||
			SlaveAddress == SCREEN_DISPLAY_PROTOCOL_DEFAULT_BROADCAST_ADDRESS){
		
			Handler 		= Com485Protocol_GetComHndlr(&ScreenDisplayProtocolControl);			
			TotalDataSize 	= Com485Protocol_GetTotalDataArrived(&ScreenDisplayProtocolControl);			
			PacketSize 		= Com485Protocol_GetPacketLength(&ScreenDisplayProtocolControl);			
			CommandID 		= Com485Protocol_GetCommandIdInPacketReceived(&ScreenDisplayProtocolControl);			
			cpPacketData 	= Com485Protocol_GetDataInPacketReceived(&ScreenDisplayProtocolControl);		
			DataPacketSize 	= Com485Protocol_GetDataInPacketReceivedLen(&ScreenDisplayProtocolControl);		
			
			ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);		
			
			CommandResponseControl = ScreenDisplayCommands_ExecCommand(CommandID, cpPacketData, DataPacketSize);		
			CommandIdResponse = ScreenDisplayCommands_GetCommandIdResponse(&CommandResponseControl);
			
				
			// Answering to Master Request
			if (CommandIdResponse != SCREEN_DISPLAY_COMMADS_NO_COMMAND_ID &&
				SlaveAddress!= SCREEN_DISPLAY_PROTOCOL_DEFAULT_BROADCAST_ADDRESS) {
				
				CommandErrorCodeResponse = ScreenDisplayCommands_GetCommandErrorCodeResponse(&CommandResponseControl);			
				
				ScreenDisplayProtocol_SendDataPacket(	SCREEN_DISPLAY_PROTOCOL_DEFAULT_MASTER_ADDRESS,
														CommandIdResponse, 
														(char *) & CommandErrorCodeResponse, 
														sizeof(CommandErrorCodeResponse));
			}
		}
		
		// Command was processing
		Com485Protocol_SetDataPacketArrived(&ScreenDisplayProtocolControl, FALSE);	
	}
}

int ScreenDisplayProtocol_StateMachineUpdate(void){
	
	return Com485ProtocolStateMachine_Update(&ScreenDisplayProtocolControl);
}

int ScreenDisplayProtocol_SendDataPackWaitForResponse(char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries){
	int protocol_status;
	
	protocol_status = Com485Protocol_SendDataPackWaitForResponse(&ScreenDisplayProtocolControl, SlaveAddress, CommandId,  PacketData, PacketDataLen, 
														ResponseCommandId, WaitTimeOutSec, Retries);
	
	if (protocol_status == COM_485_PROTOCOL_PACKET_RECEIVED)													
		ScreenDisplayProtocol_ProcessingDataPacketArrived();
	else
		Com485Protocol_SetDataPacketArrived(&ScreenDisplayProtocolControl, FALSE);	
		
	return protocol_status;														
}

int ScreenDisplayProtocol_SendDataPacket(char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen){
	
	return Com485Protocol_SendDataPacket(&ScreenDisplayProtocolControl, SlaveAddress, CommandId,  PacketData, PacketDataLen);
}

int ScreenDisplayProtocol_GetCommandIdInPacketReceived(void){
	
	return Com485Protocol_GetCommandIdInPacketReceived(&ScreenDisplayProtocolControl);			
}

char * ScreenDisplayProtocol_GetDataInPacketReceived(void){
	
	return Com485Protocol_GetDataInPacketReceived(&ScreenDisplayProtocolControl);		
}

int ScreenDisplayProtocol_GetDataInPacketReceivedLen(void){

	return Com485Protocol_GetDataInPacketReceivedLen(&ScreenDisplayProtocolControl);		
}
