////////////////////////////////////////////////////////////////////////
//
// File name: ScreenMasterProtocol.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenMasterProtocol.h"

//**********************************************************************
// Variables
//**********************************************************************
TCP_COM_PROTOCOL_STRUCT ScreenMasterProtocolControl;

//**********************************************************************
// API Fucntions
//**********************************************************************

void ScreenMasterProtocol_Setup(char ComAddress ){	
	
	TCPComProtocol_Setup(&ScreenMasterProtocolControl, BSP_USART_COM_HDLR,
						  ComAddress, TCP_COM_PROTOCOL_DEFAULT_PREFIX, TCP_COM_PROTOCOL_ADMINISTRATOR, TCP_COM_PROTOCOL_DEFAULT_PASSWORD, TCP_COM_PROTOCOL_DEFAULT_PASSWORD_LEN);	
	
	ScreenMasterCommands_Setup();
}

void ScreenMasterProtocol_WaitDataPacketCheck(void){
	
	TCPComProtocol_WaitDataPacket(&ScreenMasterProtocolControl, SCREEN_MASTER_PROTOCOL_WAIT_TIME_OUT);
}

void ScreenMasterProtocol_ProcessingDataPacketArrived(void){
	
	
	
	volatile char buffer[10];
	
	volatile int 	CommandId;
	volatile char 	SlaveAddress;
	volatile char * Parameters;
	
	volatile MASTER_COMMAND_RESPONSE_STRUCT MasterCommandResponseControl;
	
	
	
	if(TCPComProtocol_GetDataPacketArrived(&ScreenMasterProtocolControl)) 
	{
		CommandId = ScreenMasterProtocolControl.CommandIdInPacketReceived;
		SlaveAddress = ScreenMasterProtocolControl.SlaveAddressInPacketReceived;
		Parameters = ScreenMasterProtocolControl.Parameters;
		
		
		ScreenMasterCommands_ExecCommand(&MasterCommandResponseControl, SlaveAddress, CommandId, Parameters);		
		
		if( MasterCommandResponseControl.commandIdResponse != SCREEN_MASTER_COMMADS_NO_COMMAND_ID && 
			MasterCommandResponseControl.commandErrorCodeResponse == SCREEN_MASTER_COMMADS_NO_ERROR_CODE ){
		
			ScreenMasterProtocol_SendDataPacket( MasterCommandResponseControl.commandIdResponse,
												 MasterCommandResponseControl.commandBufferResponse, 
												 MasterCommandResponseControl.commandBufferResponseLen);
		} else {
			
			TCPComProtocol_SetDataPacketErrorCode(&ScreenMasterProtocolControl, MasterCommandResponseControl.commandErrorCodeResponse);
		}		
		
		
		// Command was processing
		TCPComProtocol_SetDataPacketArrived(&ScreenMasterProtocolControl, FALSE);	
	}
	
	if(TCPComProtocol_GetDataPacketErrorCode(&ScreenMasterProtocolControl)){
		
		ScreenMasterProtocol_FormatBuilder(TCPComProtocol_GetDataPacketErrorCode(&ScreenMasterProtocolControl), buffer, sizeof(buffer));
		ScreenMasterProtocol_SendDataPacket( SCREEN_MASTER_DEVICE_SERVER_ERROR_CODE_COMMAND_ID, buffer, strlen(buffer));
	}
}



int ScreenMasterProtocol_SendDataPacket( int CommandId, char * PacketData, int PacketDataLen){
	
	return TCPComProtocol_SendDataPacket(&ScreenMasterProtocolControl, CommandId,  PacketData, PacketDataLen);
}


void ScreenMasterProtocol_FormatBuilder(int data, char * buffer, int bufferLen){
	
	uint2str(data,buffer,bufferLen);
	
	if( strlen(buffer) < bufferLen)	
		*(buffer + strlen(buffer)) = TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR;
}


