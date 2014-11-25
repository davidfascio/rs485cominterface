/*
 * File: ScreenDisplayProtocol.h
 * Author: fascio
 * 
 * Created on November 20th, 2014, 16:22
 */ 
 
#ifndef __SCREEN_DISPLAY_PROTOCOL_H__
#define __SCREEN_DISPLAY_PROTOCOL_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "Com485Protocol.h"
#include "ScreenDisplayCommands.h"

//**********************************************************************
// Defines
//**********************************************************************
#define SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT					   (5000)

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void ScreenDisplayProtocol_Setup(void);
//void ScreenDisplayProtocol_Update(void);

void ScreenDisplayProtocol_WaitDataPacketCheck(void);

void ScreenDisplayProtocol_ProcessingDataPacketArrived(void);

void SEND_DEMO(void);

////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplayProtocol.c
//
// #include "ScreenDisplayProtocol.h"
//

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
	
	//volatile COMMAND_RESPONSE_STRUCT CommandResponseControl;
	volatile int CommandIdResponse;
	volatile int CommandErrorCodeResponse;
	
	if(Com485InterfaceProtocol_GetDataPacketArrived(&ScreenDisplayProtocolControl)) 
	{
        
		Handler = Com485InterfaceProtocol_GetComHndlr(&ScreenDisplayProtocolControl);
			
		TotalDataSize = Com485InterfaceProtocol_GetTotalDataArrived(&ScreenDisplayProtocolControl);
			
		PacketSize = Com485InterfaceProtocol_GetPacketLength(&ScreenDisplayProtocolControl);
			
		CommandID = Com485InterfaceProtocol_GetCommandIdInPacketReceived(&ScreenDisplayProtocolControl);
			
		cpPacketData = Com485InterfaceProtocol_GetDataInPacketReceived(&ScreenDisplayProtocolControl);
		
		DataPacketSize = Com485InterfaceProtocol_GetDataInPacketReceivedLen(&ScreenDisplayProtocolControl);
		
		//COMMAND_RESPONSE_STRUCT CommandResponseControl;	
		//int commandErrorCodeResponse;
		//ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);

		if((CommandID == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_FLOAT_VALUE_UPDATE) && 
			DataPacketSize == sizeof(float)) {
			
			float fdato; 
			CommandIdResponse = SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_FLOAT_VALUE_UPDATE;
			
			memcpy((char*)&fdato, cpPacketData ,sizeof(float));

			CommandErrorCodeResponse = ScreenDisplayDevice_Update(fdato);
			
			if(CommandIdResponse != SCREEN_DISPLAY_COMMADS_NO_COMMAND_ID){			
				
				Com485InterfaceProtocol_SendDataPacket(&ScreenDisplayProtocolControl, 
																	CommandIdResponse , 
																	(char *) & CommandErrorCodeResponse, 
																	sizeof(CommandErrorCodeResponse));
			}
		
		}
		
		
		
		/*
		CommandResponseControl = ScreenDisplayCommands_ExecCommand(CommandID, cpPacketData, DataPacketSize);
		
		CommandIdResponse = ScreenDisplayCommands_GetCommandIdResponse(&CommandResponseControl);
		
		if(CommandIdResponse != SCREEN_DISPLAY_COMMADS_NO_COMMAND_ID){
			
			CommandErrorCodeResponse = ScreenDisplayCommands_GetCommandErrorCodeResponse(&CommandResponseControl);
			
			Com485InterfaceProtocol_SendDataPacket(&ScreenDisplayProtocolControl, 
																CommandIdResponse , 
																(char *) & CommandErrorCodeResponse, 
																sizeof(CommandErrorCodeResponse));
		}*/
		
				//Com485InterfaceProtocol_SendDataPacket(&ScreenDisplayProtocolControl, 
				//CommandID , /* CommandID*/
				//cpPacketData, /* DataInPacketReceived*/ 
				//DataPacketSize); /* DataInPacketReceivedLen*/ 
			
		Com485InterfaceProtocol_SetDataPacketArrived(&ScreenDisplayProtocolControl, FALSE);	
	}
}

void SEND_DEMO(void){
	
	volatile int CommandIdResponse = 2001;
	volatile float CommandErrorCodeResponse = 1.63;
	
	/*Com485InterfaceProtocol_SendDataPackWaitForResponse(&ScreenDisplayProtocolControl, 
																CommandIdResponse , 
																(char *) & CommandErrorCodeResponse, 
																sizeof(CommandErrorCodeResponse), 
																SCREEN_DISPLAY_COMMADS_NO_COMMAND_ID, 
																COM_485_PROTOCOL_DO_NOT_WAIT_DATA_PACKET, 
																COM_485_PROTOCOL_SEND_DATA_PACKET_WAIT_RESPONSE_DO_NOT_RETRY);*/
																
	
	Com485InterfaceProtocol_SendDataPacket(&ScreenDisplayProtocolControl,CommandIdResponse, (char *) & CommandErrorCodeResponse, sizeof(CommandErrorCodeResponse) );
	
	//COM485DEMO(&ScreenDisplayProtocolControl,  CommandErrorCodeResponse);
}
#endif /* __SCREEN_DISPLAY_PROTOCOL_H__ */
