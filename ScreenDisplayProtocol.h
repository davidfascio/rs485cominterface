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
#define SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT					   (500)

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void ScreenDisplayProtocol_Setup(void);
void ScreenDisplayProtocol_Update(void);

void ScreenDisplayProtocol_WaitDataPacketCheck(void);
void ScreenDisplayProtocol_DataPacketArrivedCheck(void);

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
}

void ScreenDisplayProtocol_WaitDataPacketCheck(void){
	
	Com485InterfaceProtocol_WaitDataPacket(&ScreenDisplayProtocolControl, SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT);
}

void ScreenDisplayProtocol_ProcessingDataPacketArrived(void){
	
	int Handler;
	int TotalDataSize;
	int PacketSize;
	int CommandID;
	int DataPacketSize;
	char * cpPacketData;
	
	if(ComInterfaceProtocolsPacketArrived(&ScreenDisplayProtocolControl)) 
  {
    int_32 result = 0;
    int_32 resultInverted=0;
    
    uint_32 ulRelaysSatus = 0;
    uint_32 ulRelaysExpSatus = 0;

    
    Handler = Com485InterfaceProtocol_GetComHndlr(&ScreenDisplayProtocolControl);
        
    TotalDataSize = Com485InterfaceProtocol_GetTotalDataArrived(&ScreenDisplayProtocolControl);
        
    PacketSize = Com485InterfaceProtocol_GetPacketLength(&ScreenDisplayProtocolControl);
        
    CommandID = Com485InterfaceProtocol_GetCommandIdInPacketReceived(&ScreenDisplayProtocolControl);
        
    cpPacketData = Com485InterfaceProtocol_GetDataInPacketReceived(&ScreenDisplayProtocolControl);
    
    DataPacketSize = Com485InterfaceProtocol_GetDataInPacketReceivedLen(&ScreenDisplayProtocolControl);
        
    CommandID = ScreenDisplayCommands_ExecCommand(CommandID, cpPacketData, DataPacketSize);
    Com485InterfaceProtocol_SendDataPackWaitForResponse(&ScreenDisplayProtocolControl, CommandID , cpPacketData, PacketDataLen, ResponseCommandId, WaitTimeOutSec, Retries);
		
	Com485InterfaceProtocol_SetDataPacketArrived(&ScreenDisplayProtocolControl, FALSE);
  
	
}

#endif /* __SCREEN_DISPLAY_PROTOCOL_H__ */
