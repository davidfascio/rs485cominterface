/*
 * File: Com485Protocol.h
 * Author: fascio
 * 
 * Created on November 19th, 2014, 14:13
 */ 
 
#ifndef __COM_485_PROTOCOL_H__
#define __COM_485_PROTOCOL_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "CommonSystemLibraries.h"

//**********************************************************************
// Defines
//**********************************************************************

// High Level Defines
#ifndef COM_485_PROTOCOL_RX_WINDOW_SIZE   
#define COM_485_PROTOCOL_RX_WINDOW_SIZE 										(20)
#endif

#ifndef RTCS_ERROR
#define RTCS_ERROR 																					(-1)
#endif

#ifndef RTCS_NO_ERROR
#define RTCS_NO_ERROR 																				(0)
#endif

#ifndef COM_485_PROTOCOL_PACKET_RECEIVED
#define COM_485_PROTOCOL_PACKET_RECEIVED 										(1)
#endif

#ifndef COM_485_PROTOCOL_PACKET_SENT
#define COM_485_PROTOCOL_PACKET_SENT 											(1)
#endif

#define COM_485_PROTOCOL_DO_NOT_SEND_DATA_PACKET	(0)
#define COM_485_PROTOCOL_DO_NOT_WAIT_DATA_PACKET	(0)

#define COM_485_PROTOCOL_MAX_TIME_OUT_LOOPS		(500)


#define COM_485_PROTOCOL_SEND_DATA_PACKET_WAIT_RESPONSE_DO_NOT_RETRY				(1)
#define COM_485_PROTOCOL_SEND_DATA_PACKET_WAIT_RESPONSE_DEFAULT_RETIES			(3)

// Error Code Defines
#define COM_485_PROTOCOL_DATA_PACKET_ARRIVED										(1)
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS					(-50)
#define COM_485_PROTOCOL_PACKET_RECEIVED_IS_LARGER_THAN_RECV_BUFFER		(-51)
#define COM_485_PROTOCOL_PACKET_RECEIVED_UNEXPECTED_ID_COMMAND_RECEIVED	(-52)
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_TIMEOUT_OCCURRED				(-53)
#define COM_485_PROTOCOL_PACKET_RECEIVED_DOES_NOT_HAVE_LAST_CHAR		(-54)

// Protocol Defines
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE								sizeof(int) 	// (2)
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE							sizeof(int) 	// (2)
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR_SIZE						sizeof(char) 	// (1)

#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD								(COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE + COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR_SIZE)

#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR								0XFF
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN							(TX_BUFFER_SIZE - COM_485_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD)


//**********************************************************************
// Structures 
//**********************************************************************

typedef struct Com485InterfaceProtocolStruct
{
	int		comHndlr;
	char 	RecvBuffer [COM_485_PROTOCOL_RX_WINDOW_SIZE];
	char * 	RecvBufferPtr;
	int 	TotalDataArrived;	
	int		PacketLength;
	int		CommandIdInPacketReceived;
	char * 	DataInPacketReceived;
	int		DataInPacketReceivedLen;
	boolean		DataPacketArrived;		
	int		WaitDataPacketTimeOutLoopCntr;	
} COM_485_PROTOCOL_CONTROL_STRUCT, * COM_485_PROTOCOL_CONTROL_STRUCT_PTR_;

//**********************************************************************
// Setters and Getters Prototype Fucntions
//**********************************************************************

void Com485InterfaceProtocol_SetComHndlr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int comHndlr);
int Com485InterfaceProtocol_GetComHndlr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

char * Com485InterfaceProtocol_GetRecvBuffer(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);
int Com485InterfaceProtocol_GetRecvBufferSize(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

void Com485InterfaceProtocol_SetRecvBufferPtr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, char * RecvBufferPtr);
char * Com485InterfaceProtocol_GetRecvBufferPtr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

void Com485InterfaceProtocol_SetTotalDataArrived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int TotalDataArrived);
int  Com485InterfaceProtocol_GetTotalDataArrived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

void Com485InterfaceProtocol_SetPacketLength(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int PacketLength);
int  Com485InterfaceProtocol_GetPacketLength(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

void Com485InterfaceProtocol_SetCommandIdInPacketReceived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int CommandIdInPacketReceived);
int  Com485InterfaceProtocol_GetCommandIdInPacketReceived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

void  Com485InterfaceProtocol_SetDataInPacketReceived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, char * DataInPacketReceived);
char *  Com485InterfaceProtocol_GetDataInPacketReceived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

void Com485InterfaceProtocol_SetDataInPacketReceivedLen(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int DataInPacketReceivedLen);
int  Com485InterfaceProtocol_GetDataInPacketReceivedLen(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

void Com485InterfaceProtocol_SetDataPacketArrived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, boolean DataPacketArrived);
boolean  Com485InterfaceProtocol_GetDataPacketArrived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

void Com485InterfaceProtocol_SetWaitDataPacketTimeOutLoopCntr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int WaitDataPacketTimeOutLoopCntr);
boolean  Com485InterfaceProtocol_GetWaitDataPacketTimeOutLoopCntr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);


//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void Com485InterfaceProtocol_Setup(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int comHndlr);

void Com485InterfaceProtocol_RecvBufferReset(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);
void ErrorInCom485InterfaceProtocolCommunication(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

int Com485InterfaceProtocol_ReceiveData(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int Com485InterfaceHandler, char * DataReceiveBuffer, int DataLen);
int Com485InterfaceProtocol_SendData(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int Com485InterfaceHandler, char * DataToSend, int DataLen);

int Com485InterfaceProtocol_SendDataPackHdr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int DataLen, int CommandID);
int Com485InterfaceProtocol_SendDataPacket(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int CommandId, char * PacketData, int PacketDataLen);
int Com485InterfaceProtocol_WaitDataPacket(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int WaitTimeOutSeconds);
int Com485InterfaceProtocol_SendDataPackWaitForResponse(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries);
														
////////////////////////////////////////////////////////////////////////
//
// File name: Com485InterfaceProtocol.c
//
// #include "Com485InterfaceProtocol.h"
//


//**********************************************************************
// Setters and Getters Fucntions
//**********************************************************************

void Com485InterfaceProtocol_SetComHndlr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int comHndlr){
			
	Com485InterfaceProtocolControl->comHndlr = comHndlr;
}

int Com485InterfaceProtocol_GetComHndlr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return 	Com485InterfaceProtocolControl->comHndlr;
}

char * Com485InterfaceProtocol_GetRecvBuffer(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return 	Com485InterfaceProtocolControl->RecvBuffer;
}

int Com485InterfaceProtocol_GetRecvBufferSize(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return	sizeof(Com485InterfaceProtocolControl->RecvBuffer);
}

void Com485InterfaceProtocol_SetRecvBufferPtr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, char * RecvBufferPtr){
	
	Com485InterfaceProtocolControl->RecvBufferPtr = RecvBufferPtr;
}

char * Com485InterfaceProtocol_GetRecvBufferPtr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return Com485InterfaceProtocolControl->RecvBufferPtr;
}

void Com485InterfaceProtocol_SetTotalDataArrived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int TotalDataArrived){
	
	Com485InterfaceProtocolControl->TotalDataArrived = TotalDataArrived;
}

int  Com485InterfaceProtocol_GetTotalDataArrived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return	Com485InterfaceProtocolControl->TotalDataArrived;
}

void Com485InterfaceProtocol_SetPacketLength(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int PacketLength){
	
	Com485InterfaceProtocolControl->PacketLength = PacketLength;
}

int  Com485InterfaceProtocol_GetPacketLength(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return Com485InterfaceProtocolControl->PacketLength;
}

void Com485InterfaceProtocol_SetCommandIdInPacketReceived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int CommandIdInPacketReceived){
	
	Com485InterfaceProtocolControl->CommandIdInPacketReceived = CommandIdInPacketReceived;
}

int  Com485InterfaceProtocol_GetCommandIdInPacketReceived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return Com485InterfaceProtocolControl->CommandIdInPacketReceived;
}

void  Com485InterfaceProtocol_SetDataInPacketReceived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, char * DataInPacketReceived){	
	
	Com485InterfaceProtocolControl->DataInPacketReceived = DataInPacketReceived;
}

char *  Com485InterfaceProtocol_GetDataInPacketReceived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){	
	
	return	Com485InterfaceProtocolControl->DataInPacketReceived;
}

void Com485InterfaceProtocol_SetDataInPacketReceivedLen(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int DataInPacketReceivedLen){

	Com485InterfaceProtocolControl->DataInPacketReceivedLen = DataInPacketReceivedLen;
}

int  Com485InterfaceProtocol_GetDataInPacketReceivedLen(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return	Com485InterfaceProtocolControl->DataInPacketReceivedLen;
}

void Com485InterfaceProtocol_SetDataPacketArrived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, boolean DataPacketArrived){
	
	Com485InterfaceProtocolControl->DataPacketArrived = DataPacketArrived;
}

boolean  Com485InterfaceProtocol_GetDataPacketArrived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return Com485InterfaceProtocolControl->DataPacketArrived;
}

void Com485InterfaceProtocol_SetWaitDataPacketTimeOutLoopCntr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int WaitDataPacketTimeOutLoopCntr){

	Com485InterfaceProtocolControl->WaitDataPacketTimeOutLoopCntr = WaitDataPacketTimeOutLoopCntr;
}

boolean  Com485InterfaceProtocol_GetWaitDataPacketTimeOutLoopCntr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	return Com485InterfaceProtocolControl->WaitDataPacketTimeOutLoopCntr;
}

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void Com485InterfaceProtocol_Setup(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int comHndlr){
	
	memset(Com485InterfaceProtocolControl, 0, sizeof(COM_485_PROTOCOL_CONTROL_STRUCT));
	Com485InterfaceProtocol_SetComHndlr(Com485InterfaceProtocolControl, comHndlr);
}

void Com485InterfaceProtocol_RecvBufferReset(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	Com485InterfaceProtocol_SetTotalDataArrived(Com485InterfaceProtocolControl, 0);
	
	/*
	 *  Initialization DataInPaketReceived  ??????
	 */ 
	Com485InterfaceProtocol_SetRecvBufferPtr(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetRecvBuffer(Com485InterfaceProtocolControl));
	Com485InterfaceProtocol_SetDataInPacketReceived(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetRecvBuffer(Com485InterfaceProtocolControl));
	
	Com485InterfaceProtocol_SetPacketLength(Com485InterfaceProtocolControl, 0);
	Com485InterfaceProtocol_SetDataInPacketReceivedLen(Com485InterfaceProtocolControl, 0);	
}

void ErrorInCom485InterfaceProtocolCommunication(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl){
	
	Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
}

// Verbose Function
//void Com485InterfaceProtocol_DataPacketArrived(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl);

int Com485InterfaceProtocol_ReceiveData(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int Com485InterfaceHandler, char * DataReceiveBuffer, int DataLen){
	
	int recvrslt;
	
	recvrslt = bsp_usart_read(DataReceiveBuffer, DataLen);
		
	if(recvrslt <= 0 )
		ErrorInCom485InterfaceProtocolCommunication(Com485InterfaceProtocolControl);
		
	return recvrslt;
}

int Com485InterfaceProtocol_SendData(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int Com485InterfaceHandler, char * DataToSend, int DataLen){
	
	int sendrslt;
	
	sendrslt = bsp_usart_write(DataToSend, DataLen);
		
	if(sendrslt != RTCS_NO_ERROR)
		ErrorInCom485InterfaceProtocolCommunication(Com485InterfaceProtocolControl);
		
	return sendrslt;
}

int Com485InterfaceProtocol_SendDataPackHdr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int DataLen, int CommandID){
	
	int sendrslt;
	int packetsize = DataLen + COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR_SIZE;
	char headerbuff[ COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE];
	
	if(DataLen > COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN)	
		return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
	
	memcpy(headerbuff, (char *) &packetsize, COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE);
	memcpy(headerbuff + COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE, (char *) &CommandID, COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE);
	
	sendrslt = Com485InterfaceProtocol_SendData(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetComHndlr(Com485InterfaceProtocolControl), headerbuff, sizeof(headerbuff) );
	
	return sendrslt;	
}

int Com485InterfaceProtocol_SendDataPacket(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int CommandId, char * PacketData, int PacketDataLen){

	int sendrslt;
	char lastchar = COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR;
	
	if( PacketDataLen == 0 || PacketDataLen > COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN)	
		return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
	
	sendrslt = Com485InterfaceProtocol_SendDataPackHdr(Com485InterfaceProtocolControl, PacketDataLen, CommandId);
	
	if(sendrslt == RTCS_NO_ERROR){
		
		sendrslt = Com485InterfaceProtocol_SendData(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetComHndlr(Com485InterfaceProtocolControl), PacketData, PacketDataLen);
		
		if(sendrslt == RTCS_NO_ERROR){
			
			sendrslt = Com485InterfaceProtocol_SendData(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetComHndlr(Com485InterfaceProtocolControl), (char *) &lastchar, sizeof(lastchar));
		}		
	}	
	
	return sendrslt;
}

int Com485InterfaceProtocol_WaitDataPacket(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int WaitTimeOutLoops){

	int receiveBufferLen = 0;
	int recvRslt = 0;
	
	boolean PacketLenReceived = FALSE;
	boolean CommandIDReceived = FALSE;
	boolean DataPacketReceived = FALSE;
	
	int DataLenReceived = 0;
	int DataLenExpected = COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
	int CommandIDValueReceived = 0;
	
	char * CommandIdInPacket;
	char * LastChar;
	
	
	if(Com485InterfaceProtocol_GetDataPacketArrived(Com485InterfaceProtocolControl) == TRUE)
		return COM_485_PROTOCOL_DATA_PACKET_ARRIVED;
	
	if(WaitTimeOutLoops==0)
		return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
		
	Com485InterfaceProtocol_SetWaitDataPacketTimeOutLoopCntr(Com485InterfaceProtocolControl, 0);
	Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
	receiveBufferLen = DataLenExpected;
	
	while(Com485InterfaceProtocol_GetWaitDataPacketTimeOutLoopCntr(Com485InterfaceProtocolControl) <= WaitTimeOutLoops ){
	
		receiveBufferLen = 	Com485InterfaceProtocol_GetRecvBufferPtr(Com485InterfaceProtocolControl)- 
							Com485InterfaceProtocol_GetRecvBuffer(Com485InterfaceProtocolControl);
		
		receiveBufferLen = DataLenExpected - receiveBufferLen;
		
		if(receiveBufferLen <= 0)
		{
			Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
			DataLenExpected = COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
			receiveBufferLen = DataLenExpected;
		}
		
		recvRslt = Com485InterfaceProtocol_ReceiveData( Com485InterfaceProtocolControl,
														Com485InterfaceProtocol_GetComHndlr(Com485InterfaceProtocolControl),
														Com485InterfaceProtocol_GetRecvBufferPtr(Com485InterfaceProtocolControl),
													    Com485InterfaceProtocol_GetRecvBufferSize(Com485InterfaceProtocolControl));
		
		if(recvRslt <= 0)
			return recvRslt;
		
		Com485InterfaceProtocol_SetRecvBufferPtr(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetRecvBufferPtr(Com485InterfaceProtocolControl) + recvRslt );
		Com485InterfaceProtocol_SetTotalDataArrived(Com485InterfaceProtocolControl, recvRslt);
		Com485InterfaceProtocol_SetWaitDataPacketTimeOutLoopCntr(Com485InterfaceProtocolControl, 0);
		
		
		if( (PacketLenReceived == FALSE) && Com485InterfaceProtocol_GetTotalDataArrived(Com485InterfaceProtocolControl) >= COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE ) {
			
			memcpy((char *) &DataLenReceived, Com485InterfaceProtocol_GetRecvBuffer(Com485InterfaceProtocolControl), COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE);
			
			DataLenExpected = DataLenReceived + COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE;
			
			if(DataLenExpected >= COM_485_PROTOCOL_RX_WINDOW_SIZE){
				
				Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
				DataLenExpected = COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
				continue;
			}
			
			PacketLenReceived = TRUE;			
		}
		
		if( (CommandIDReceived==FALSE) && 
			(Com485InterfaceProtocol_GetTotalDataArrived(Com485InterfaceProtocolControl) >= 
			(COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE))) {
				
			CommandIdInPacket = Com485InterfaceProtocol_GetRecvBuffer(Com485InterfaceProtocolControl) + COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
			
			memcpy((char*)&CommandIDValueReceived, CommandIdInPacket ,COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE);
				
			CommandIDReceived = TRUE;
		}
		
		if( (PacketLenReceived == TRUE) && 
		    (CommandIDReceived == TRUE) &&
		    (Com485InterfaceProtocol_GetTotalDataArrived(Com485InterfaceProtocolControl) >= DataLenExpected)) {
				
			LastChar = ( char *) (Com485InterfaceProtocol_GetRecvBuffer(Com485InterfaceProtocolControl) + (DataLenExpected - 1));//SocketClientCOMControl.RecvBufferPtr - 1;
			
			if(*LastChar == COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR)
			{
				DataPacketReceived = TRUE;						
				break;
			}	
			else
			{
				Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);						
				DataLenExpected = COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
				continue;
			}
		}
		
		Com485InterfaceProtocol_SetWaitDataPacketTimeOutLoopCntr(	Com485InterfaceProtocolControl, 
																	Com485InterfaceProtocol_GetWaitDataPacketTimeOutLoopCntr(Com485InterfaceProtocolControl) + 1);						
	}	
	
	if(DataPacketReceived == TRUE)
	{
		Com485InterfaceProtocol_SetPacketLength(Com485InterfaceProtocolControl, DataLenExpected);		
		Com485InterfaceProtocol_SetCommandIdInPacketReceived(Com485InterfaceProtocolControl, CommandIDValueReceived);		
		
		Com485InterfaceProtocol_SetDataInPacketReceived(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetRecvBuffer(Com485InterfaceProtocolControl) + 
														COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + 
														COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE);
																												
		Com485InterfaceProtocol_SetDataInPacketReceivedLen(Com485InterfaceProtocolControl, DataLenExpected - COM_485_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD);
		Com485InterfaceProtocol_SetDataPacketArrived(Com485InterfaceProtocolControl, TRUE);	
		
		return COM_485_PROTOCOL_PACKET_RECEIVED;
	}
	
	Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
	
	return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_TIMEOUT_OCCURRED;
}

int Com485InterfaceProtocol_SendDataPackWaitForResponse(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries){
															
	//int_32 SocketClientrecvRslt = 0;
	int SendRslt = 0;
	int RetiresCounter = 0;
	//unsigned char LastChar = COM_PROTOCOLL_CONFIG_DATA_PACKET_FINISH_CHAR;
	
	
	if(CommandId!=0)
	{				
		if((PacketDataLen == 0)||(PacketDataLen > COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN))	
			return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;		
	}
	
	for(RetiresCounter = 0; RetiresCounter < Retries; RetiresCounter++)
	{
		SendRslt = 1;
		if(CommandId != 0)
		{
			SendRslt =  Com485InterfaceProtocol_SendDataPacket(Com485InterfaceProtocolControl, CommandId, PacketData, PacketDataLen);
		}
		
		if(SendRslt == RTCS_NO_ERROR)
		{
			if(ResponseCommandId != 0)
			{
				if(WaitTimeOutSec == 0)
					return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
				
				SendRslt = Com485InterfaceProtocol_WaitDataPacket(Com485InterfaceProtocolControl, WaitTimeOutSec);
				
				if(SendRslt == COM_485_PROTOCOL_PACKET_RECEIVED)
				{
					if(Com485InterfaceProtocol_GetCommandIdInPacketReceived(Com485InterfaceProtocolControl) == ResponseCommandId)
						return SendRslt;
				}
			}
			else 
				return COM_485_PROTOCOL_PACKET_SENT;
		}
	}
	
	return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_TIMEOUT_OCCURRED;															
}


#endif /* __COM_485_PROTOCOL_H__ */
