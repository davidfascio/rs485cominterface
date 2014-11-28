////////////////////////////////////////////////////////////////////////
//
// File name: Com485Protocol.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "Com485Protocol.h"

//**********************************************************************
// Variables
//********************************************************************** 
TIMER_STRUCT Com485Timer;

//**********************************************************************
// Setters and Getters Fucntions
//**********************************************************************

// Device configuration
void Com485Protocol_SetComHndlr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int ComHndlr){
			
	Com485ProtocolControl->ComHndlr = ComHndlr;
}

int Com485Protocol_GetComHndlr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return 	Com485ProtocolControl->ComHndlr;
}

void Com485Protocol_SetComAddress(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char ComAddress){
	
	Com485ProtocolControl->ComAddress = ComAddress;
}

char Com485Protocol_GetComAddress(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return Com485ProtocolControl->ComAddress;	
}

// Received Buffer resource information
char * Com485Protocol_GetRecvBuffer(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return 	Com485ProtocolControl->RecvBuffer;
}

int Com485Protocol_GetRecvBufferSize(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return	sizeof(Com485ProtocolControl->RecvBuffer);
}

void Com485Protocol_SetRecvBufferPtr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char * RecvBufferPtr){
	
	Com485ProtocolControl->RecvBufferPtr = RecvBufferPtr;
}

char * Com485Protocol_GetRecvBufferPtr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return Com485ProtocolControl->RecvBufferPtr;
}

void Com485Protocol_SetTotalDataArrived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int TotalDataArrived){
	
	Com485ProtocolControl->TotalDataArrived = TotalDataArrived;
}

int  Com485Protocol_GetTotalDataArrived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return	Com485ProtocolControl->TotalDataArrived;
}

// Packet received fields
void Com485Protocol_SetPacketLength(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int PacketLength){
	
	Com485ProtocolControl->PacketLength = PacketLength;
}

int  Com485Protocol_GetPacketLength(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return Com485ProtocolControl->PacketLength;
}
void Com485Protocol_SetSlaveAddressInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char SlaveAddressInPacketReceived){
	
	Com485ProtocolControl->SlaveAddressInPacketReceived = SlaveAddressInPacketReceived;
}

char  Com485Protocol_GetSlaveAddressInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return Com485ProtocolControl->SlaveAddressInPacketReceived;	
}

void Com485Protocol_SetCommandIdInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int CommandIdInPacketReceived){
	
	Com485ProtocolControl->CommandIdInPacketReceived = CommandIdInPacketReceived;
}

int  Com485Protocol_GetCommandIdInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return Com485ProtocolControl->CommandIdInPacketReceived;
}

void  Com485Protocol_SetDataInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char * DataInPacketReceived){	
	
	Com485ProtocolControl->DataInPacketReceived = DataInPacketReceived;
}

char *  Com485Protocol_GetDataInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){	
	
	return	Com485ProtocolControl->DataInPacketReceived;
}

void Com485Protocol_SetDataInPacketReceivedLen(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int DataInPacketReceivedLen){

	Com485ProtocolControl->DataInPacketReceivedLen = DataInPacketReceivedLen;
}

int  Com485Protocol_GetDataInPacketReceivedLen(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return	Com485ProtocolControl->DataInPacketReceivedLen;
}

// Control Fields
void Com485Protocol_SetDataPacketArrived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, boolean DataPacketArrived){
	
	Com485ProtocolControl->DataPacketArrived = DataPacketArrived;
}

boolean  Com485Protocol_GetDataPacketArrived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return Com485ProtocolControl->DataPacketArrived;
}

void Com485Protocol_SetWaitDataPacketTimeOutLoopCntr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int WaitDataPacketTimeOutLoopCntr){

	Com485ProtocolControl->WaitDataPacketTimeOutLoopCntr = WaitDataPacketTimeOutLoopCntr;
}

boolean  Com485Protocol_GetWaitDataPacketTimeOutLoopCntr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	return Com485ProtocolControl->WaitDataPacketTimeOutLoopCntr;
}

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void Com485Protocol_Setup(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int comHndlr,char ComAddress){
	
	memset(Com485ProtocolControl, 0, sizeof(COM_485_PROTOCOL_STRUCT));
	
	Com485Protocol_SetComHndlr(Com485ProtocolControl, comHndlr);
	Com485Protocol_SetComAddress(Com485ProtocolControl, ComAddress);
	Com485Protocol_RecvBufferReset(Com485ProtocolControl);	
	//! Configure Timer
	AddTimer(&Com485Timer, COM_485_TIMER_DEFAULT_WAIT_VALUE_IN_MS);
	//! Com485Interface_setup();
	bsp_usart_setup();
}

void Com485Protocol_RecvBufferReset(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	Com485Protocol_SetTotalDataArrived(Com485ProtocolControl, 0);	
	
	Com485Protocol_SetRecvBufferPtr(Com485ProtocolControl, Com485Protocol_GetRecvBuffer(Com485ProtocolControl));
	Com485Protocol_SetDataInPacketReceived(Com485ProtocolControl, Com485Protocol_GetRecvBuffer(Com485ProtocolControl));
	
	Com485Protocol_SetPacketLength(Com485ProtocolControl, 0);
	Com485Protocol_SetDataInPacketReceivedLen(Com485ProtocolControl, 0);	
}

void ErrorInCom485ProtocolCommunication(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl){
	
	Com485Protocol_RecvBufferReset(Com485ProtocolControl);
}

int Com485Protocol_ReceiveData(int Com485InterfaceHandler, char * DataReceiveBuffer, int DataLen){

	//! recvrslt = Com485Interface_read();	
	return bsp_usart_read(DataReceiveBuffer, DataLen);
}

int Com485Protocol_SendData(int Com485InterfaceHandler, char * DataToSend, int DataLen){

	//! sendrslt = Com485Interface_write(DataToSend, DataLen);
	return bsp_usart_write(DataToSend, DataLen);	
}

int Com485Protocol_SendHeaderPacket(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int DataLen, char SlaveAddress, int CommandID){
	
	int sendrslt = 0;
	volatile int packetsize = 0;
	volatile char headerbuff[COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE];
	char * headerbuffptr = headerbuff;
	
	if(DataLen > COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN)	
		return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
		
	packetsize = DataLen + COM_485_PROTOCOL_DATA_PACKET_EOT_FIELD_SIZE;
	
	// Set DataPacketLen Field in headerbuffer
	memcpy(headerbuffptr, (char *) & packetsize, COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE);
	
	// Set SlaveAddress Field in headerbuffer
	headerbuffptr += COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE;
	memcpy(headerbuffptr, (char *) &SlaveAddress, COM_485_PROTOCOL_DATA_PACKET_SLAVE_ADDRESS_FIELD_SIZE);
	
	// Set CommandID Field in headerbuffer
	headerbuffptr += COM_485_PROTOCOL_DATA_PACKET_SLAVE_ADDRESS_FIELD_SIZE;
	memcpy(headerbuffptr, (char *) &CommandID, COM_485_PROTOCOL_DATA_PACKET_COMMAND_ID_FIELD_SIZE);
	
	sendrslt = Com485Protocol_SendData(Com485Protocol_GetComHndlr(Com485ProtocolControl), headerbuff, sizeof(headerbuff) );
	
	if (sendrslt != RTCS_NO_ERROR)
		ErrorInCom485ProtocolCommunication(Com485ProtocolControl);
	
	return sendrslt;	
}

int Com485Protocol_SendDataPacket(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen){

	int sendrslt;
	volatile char lastchar = COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR;
	
	if( PacketDataLen == 0 || PacketDataLen > COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN)	
		return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
	
	sendrslt = Com485Protocol_SendHeaderPacket(Com485ProtocolControl, PacketDataLen, SlaveAddress,CommandId);
	
	if(sendrslt == RTCS_NO_ERROR){
		
		sendrslt = Com485Protocol_SendData(Com485Protocol_GetComHndlr(Com485ProtocolControl), PacketData, PacketDataLen);
		
		if(sendrslt == RTCS_NO_ERROR){
			
			sendrslt = Com485Protocol_SendData(Com485Protocol_GetComHndlr(Com485ProtocolControl), (char *) &lastchar, COM_485_PROTOCOL_DATA_PACKET_EOT_FIELD_SIZE);
		}		
	}	
	
	return sendrslt;
}

int Com485Protocol_WaitDataPacket(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int WaitTimeOutLoops){
	
	volatile int SocketClientReceiveBufferLen = 0;
	volatile int SocketClientrecvRslt = 0;
	
	volatile boolean PacketLenReceived = FALSE;
	volatile boolean SlaveAddressReceived =  FALSE;
	volatile boolean CommandIDReceived = FALSE;
	volatile boolean DataPacketReceived = FALSE;
	
		
	volatile int DataLenReceived = 0;
	volatile char SlaveAddressValueReceived = 0;
	volatile int CommandIDValueReceived = 0;
	
	volatile int DataLenExpected = COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE;
	
	char * RecvBufferIndexPtr;
	
	if(Com485ProtocolControl->DataPacketArrived == TRUE)
		return 1;
	
	//if(WaitTimeOutLoops == 0)
	if(Timer_SetOverflowValue_MS(&Com485Timer, WaitTimeOutLoops) < 0)
		return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
	
	// Initialization Process
	Com485ProtocolControl->WaitDataPacketTimeOutLoopCntr = 0;
   	Com485Protocol_RecvBufferReset(Com485ProtocolControl);
   	SocketClientReceiveBufferLen = DataLenExpected;
	
	
	//while(Com485ProtocolControl->WaitDataPacketTimeOutLoopCntr <= WaitTimeOutLoops)
	while(Timer_GetOverflow(&Com485Timer) == FALSE)
	{
   		SocketClientReceiveBufferLen = (int)Com485ProtocolControl->RecvBufferPtr - (int)Com485ProtocolControl->RecvBuffer;
   		SocketClientReceiveBufferLen = DataLenExpected - SocketClientReceiveBufferLen;
   		
   		// Validation
   		if(SocketClientReceiveBufferLen <= 0)
   		{
   			Com485Protocol_RecvBufferReset(Com485ProtocolControl);
   			DataLenExpected = COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE;
   			SocketClientReceiveBufferLen = DataLenExpected;
   		}
   		
   		
   		// Reading Process
   		SocketClientrecvRslt = Com485Protocol_ReceiveData(Com485ProtocolControl->ComHndlr, Com485ProtocolControl->RecvBufferPtr, SocketClientReceiveBufferLen);
   		
   		
   		if (SocketClientrecvRslt < 0) {
			
			ErrorInCom485ProtocolCommunication(Com485ProtocolControl);
			return SocketClientrecvRslt;
		}
		
		if(SocketClientrecvRslt > 0)
		{			
			Com485ProtocolControl->RecvBufferPtr += SocketClientrecvRslt;
			Com485ProtocolControl->TotalDataArrived += SocketClientrecvRslt;
			//Com485ProtocolControl->WaitDataPacketTimeOutLoopCntr = 0;		
			
			// Processing DataPacketLen Field
			if ((PacketLenReceived == FALSE) && 
				(Com485ProtocolControl->TotalDataArrived >= COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE)) {
				
				RecvBufferIndexPtr = Com485ProtocolControl->RecvBuffer;
				memcpy( (char*) &DataLenReceived, RecvBufferIndexPtr, COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE);
				
				DataLenExpected = DataLenReceived + COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
				
				if(DataLenExpected >= COM_485_PROTOCOL_RX_WINDOW_SIZE)
				{
					Com485Protocol_RecvBufferReset(Com485ProtocolControl);					
					DataLenExpected = COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE;
					continue;
				}
				
				PacketLenReceived = TRUE;	
			}
			
			// Processing SlaveAddress Field
			if ((SlaveAddressReceived == FALSE) && 
				(Com485ProtocolControl->TotalDataArrived >= 
				(COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE + COM_485_PROTOCOL_DATA_PACKET_SLAVE_ADDRESS_FIELD_SIZE))) {
				
				RecvBufferIndexPtr += COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE;	
				memcpy( (char*) &SlaveAddressValueReceived, RecvBufferIndexPtr, COM_485_PROTOCOL_DATA_PACKET_SLAVE_ADDRESS_FIELD_SIZE);				
								
				SlaveAddressReceived = TRUE;	
			}	
			
			// Processing CommandID Field
			if ((CommandIDReceived == FALSE) && 
				(Com485ProtocolControl->TotalDataArrived >= COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE )) {
				
				RecvBufferIndexPtr += COM_485_PROTOCOL_DATA_PACKET_SLAVE_ADDRESS_FIELD_SIZE;					                
                memcpy((char*)&CommandIDValueReceived, RecvBufferIndexPtr ,COM_485_PROTOCOL_DATA_PACKET_COMMAND_ID_FIELD_SIZE);
				
				CommandIDReceived = TRUE;
			}
			
			// Processing EOT Field
			if ((PacketLenReceived == TRUE) && 
				(SlaveAddressReceived == TRUE) && 
				(CommandIDReceived==TRUE) &&
				(Com485ProtocolControl->TotalDataArrived >= DataLenExpected)) {
					
				 unsigned char * LastChar = (unsigned char *)(Com485ProtocolControl->RecvBuffer+(DataLenExpected - 1));
				if(*LastChar == COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR)
				{
					DataPacketReceived = TRUE;					
					break;
				}	
				else
				{
					Com485Protocol_RecvBufferReset(Com485ProtocolControl);					
					DataLenExpected = COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE;
					continue;
				}
			}
		}
		
		Com485ProtocolControl->WaitDataPacketTimeOutLoopCntr++;
	}
	
	if(DataPacketReceived == TRUE)
	{
		Com485ProtocolControl->PacketLength = DataLenExpected;
		Com485ProtocolControl->SlaveAddressInPacketReceived = SlaveAddressValueReceived;
		Com485ProtocolControl->CommandIdInPacketReceived = CommandIDValueReceived;
		Com485ProtocolControl->DataInPacketReceived = Com485ProtocolControl->RecvBuffer + COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
		Com485ProtocolControl->DataInPacketReceivedLen = DataLenExpected - COM_485_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD;
		//!ComInterfaceProtocolsDataPacketArrived(Com485ProtocolControl);
		Com485ProtocolControl->DataPacketArrived = TRUE;
		
		
		//Com485Protocol_SendDataPacket(Com485ProtocolControl, 
				//Com485ProtocolControl->CommandIdInPacketReceived , /* CommandID*/
				//Com485ProtocolControl->DataInPacketReceived, /* DataInPacketReceived*/ 
				//Com485ProtocolControl->DataInPacketReceivedLen); /* DataInPacketReceivedLen*/ 
				
		return COM_485_PROTOCOL_PACKET_RECEIVED;
	}
	
	Com485Protocol_RecvBufferReset(Com485ProtocolControl);
	return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_TIMEOUT_OCCURRED;
	
}

int Com485Protocol_SendDataPackWaitForResponse(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl,char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries){
															
	int SendRslt = 0;
	int RetiresCounter = 0;
		
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
			SendRslt =  Com485Protocol_SendDataPacket(Com485ProtocolControl, SlaveAddress, CommandId, PacketData, PacketDataLen);
		}
		
		if(SendRslt == RTCS_NO_ERROR)
		{
			if(ResponseCommandId != 0)
			{
				if(WaitTimeOutSec == 0)
					return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
				
				SendRslt = Com485Protocol_WaitDataPacket(Com485ProtocolControl, WaitTimeOutSec);
				
				if(SendRslt == COM_485_PROTOCOL_PACKET_RECEIVED)
				{
					if(Com485Protocol_GetCommandIdInPacketReceived(Com485ProtocolControl) == ResponseCommandId)
						return SendRslt;
				}
			}
			else 
				return COM_485_PROTOCOL_PACKET_SENT;
		}
	}
	
	return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_TIMEOUT_OCCURRED;															
}

