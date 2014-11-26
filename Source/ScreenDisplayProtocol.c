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
COM_485_PROTOCOL_CONTROL_STRUCT ScreenDisplayProtocolControl;

//**********************************************************************
// API Fucntions
//**********************************************************************

void ScreenDisplayProtocol_Setup(void){
	
	Com485InterfaceProtocol_Setup(&ScreenDisplayProtocolControl, BSP_USART_COM_HDLR);
	ScreenDisplayCommands_Setup();
}

void ScreenDisplayProtocol_WaitDataPacketCheck(void){
	
	Com485InterfaceProtocol_WaitDataPacket(&ScreenDisplayProtocolControl, SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT);
}

void ScreenDisplayProtocol_ProcessingDataPacketArrived(void){
	
	volatile int Handler;
	volatile int TotalDataSize;
	volatile int PacketSize;
	volatile int CommandID;
	volatile int DataPacketSize;
	volatile char * cpPacketData;
	
	volatile int CommandIdResponse;
	volatile int CommandErrorCodeResponse;
	
	COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	
	if(Com485InterfaceProtocol_GetDataPacketArrived(&ScreenDisplayProtocolControl)) 
	{
		Handler = Com485InterfaceProtocol_GetComHndlr(&ScreenDisplayProtocolControl);			
		TotalDataSize = Com485InterfaceProtocol_GetTotalDataArrived(&ScreenDisplayProtocolControl);			
		PacketSize = Com485InterfaceProtocol_GetPacketLength(&ScreenDisplayProtocolControl);			
		CommandID = Com485InterfaceProtocol_GetCommandIdInPacketReceived(&ScreenDisplayProtocolControl);			
		cpPacketData = Com485InterfaceProtocol_GetDataInPacketReceived(&ScreenDisplayProtocolControl);		
		DataPacketSize = Com485InterfaceProtocol_GetDataInPacketReceivedLen(&ScreenDisplayProtocolControl);		
		
		ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);		
				
		CommandResponseControl = ScreenDisplayCommands_ExecCommand(CommandID, cpPacketData, DataPacketSize);		
		CommandIdResponse = ScreenDisplayCommands_GetCommandIdResponse(&CommandResponseControl);
		
		if(CommandIdResponse != SCREEN_DISPLAY_COMMADS_NO_COMMAND_ID){
			
			CommandErrorCodeResponse = ScreenDisplayCommands_GetCommandErrorCodeResponse(&CommandResponseControl);			
			Com485InterfaceProtocol_SendDataPacket(&ScreenDisplayProtocolControl, 
																CommandIdResponse , 
																(char *) & CommandErrorCodeResponse, 
																sizeof(CommandErrorCodeResponse));
		}
		
		Com485InterfaceProtocol_SetDataPacketArrived(&ScreenDisplayProtocolControl, FALSE);	
	}
}

