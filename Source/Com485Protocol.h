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
#define COM_485_PROTOCOL_RX_WINDOW_SIZE 								(20)
#endif

#ifndef RTCS_ERROR
#define RTCS_ERROR 														(-1)
#endif

#ifndef RTCS_NO_ERROR
#define RTCS_NO_ERROR 													(0)
#endif

#ifndef COM_485_PROTOCOL_PACKET_RECEIVED
#define COM_485_PROTOCOL_PACKET_RECEIVED 								(1)
#endif

#ifndef COM_485_PROTOCOL_PACKET_SENT
#define COM_485_PROTOCOL_PACKET_SENT 									(1)
#endif

#define COM_485_PROTOCOL_DO_NOT_SEND_DATA_PACKET						(0)
#define COM_485_PROTOCOL_DO_NOT_WAIT_DATA_PACKET						(0)

#define COM_485_PROTOCOL_MAX_TIME_OUT_LOOPS								(500)


#define COM_485_PROTOCOL_SEND_DATA_PACKET_WAIT_RESPONSE_DO_NOT_RETRY	(1)
#define COM_485_PROTOCOL_SEND_DATA_PACKET_WAIT_RESPONSE_DEFAULT_RETIES	(3)

// Error Code Defines
#define COM_485_PROTOCOL_DATA_PACKET_ARRIVED							(1)
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS		(-50)
#define COM_485_PROTOCOL_PACKET_RECEIVED_IS_LARGER_THAN_RECV_BUFFER		(-51)
#define COM_485_PROTOCOL_PACKET_RECEIVED_UNEXPECTED_ID_COMMAND_RECEIVED	(-52)
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_TIMEOUT_OCCURRED	(-53)
#define COM_485_PROTOCOL_PACKET_RECEIVED_DOES_NOT_HAVE_LAST_CHAR		(-54)

// Protocol Defines
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE					(2) 	// (2)
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE				(2) 	// (2)
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR_SIZE			(1)//sizeof(char) 	// (1)

#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD					(COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE + COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR_SIZE)

#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR					0XFF
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN				(TX_BUFFER_SIZE0 - COM_485_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD)


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
	boolean	DataPacketArrived;		
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

void COM485DEMO(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int dato);														
////////////////////////////////////////////////////////////////////////
//
// File name: Com485InterfaceProtocol.c
//
// #include "Com485InterfaceProtocol.h"
//

// LOCAL VARIABLES
boolean PacketLenReceived = FALSE;
boolean CommandIDReceived = FALSE;
boolean DataPacketReceived = FALSE;

int DataLenReceived = 0;
int DataLenExpected = 0;
int CommandIDValueReceived = 0;

int TotalDataArrived_t = 0;
unsigned char LastCharTemp;
unsigned char * LastChar;

char * packetArrived;

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
	
	Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
	Com485InterfaceProtocol_SetComHndlr(Com485InterfaceProtocolControl, comHndlr);
	
	//! Com485Interface_setup();
	bsp_usart_setup();
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
	
	//! recvrslt = Com485Interface_read();
	recvrslt = bsp_usart_read(DataReceiveBuffer, DataLen);
		
	if(recvrslt <= 0 )
		ErrorInCom485InterfaceProtocolCommunication(Com485InterfaceProtocolControl);
		
	return recvrslt;
}

int Com485InterfaceProtocol_SendData(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int Com485InterfaceHandler, char * DataToSend, int DataLen){
	
	int sendrslt;
	
	//! sendrslt = Com485Interface_write(DataToSend, DataLen);
	sendrslt = bsp_usart_write(DataToSend, DataLen);
		
	if(sendrslt != RTCS_NO_ERROR)
		ErrorInCom485InterfaceProtocolCommunication(Com485InterfaceProtocolControl);
		
	return sendrslt;
}

int Com485InterfaceProtocol_SendDataPackHdr(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int DataLen, int CommandID){
	
	int sendrslt;
	volatile int packetsize = 0;
	volatile char headerbuff[ COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE];
	
	
	if(DataLen > COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN)	
		return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
		
	packetsize = DataLen + COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR_SIZE;
	
	memcpy(headerbuff, (char *) & packetsize, COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE);
	memcpy((headerbuff + COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE), (char *) &CommandID, COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE);
	
	sendrslt = Com485InterfaceProtocol_SendData(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetComHndlr(Com485InterfaceProtocolControl), headerbuff, sizeof(headerbuff) );
	
	return sendrslt;	
}

int Com485InterfaceProtocol_SendDataPacket(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int CommandId, char * PacketData, int PacketDataLen){

	int sendrslt;
	volatile char lastchar = COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR;
	
	if( PacketDataLen == 0 || PacketDataLen > COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN)	
		return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
	
	sendrslt = Com485InterfaceProtocol_SendDataPackHdr(Com485InterfaceProtocolControl, PacketDataLen, CommandId);
	
	if(sendrslt == RTCS_NO_ERROR){
		
		sendrslt = Com485InterfaceProtocol_SendData(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetComHndlr(Com485InterfaceProtocolControl), PacketData, PacketDataLen);
		
		if(sendrslt == RTCS_NO_ERROR){
			
			sendrslt = Com485InterfaceProtocol_SendData(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetComHndlr(Com485InterfaceProtocolControl), (char *) &lastchar, COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR_SIZE);
		}		
	}	
	
	return sendrslt;
}

int Com485InterfaceProtocol_WaitDataPacket(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int WaitTimeOutLoops){
	
	volatile int SocketClientReceiveBufferLen = 0;
	volatile int SocketClientrecvRslt = 0;
	
	volatile boolean PacketLenReceived = FALSE;
	volatile boolean CommandIDReceived = FALSE;
	volatile boolean DataPacketReceived = FALSE;
	
	volatile int DataLenReceived = 0;
	volatile int DataLenExpected = COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
	volatile int CommandIDValueReceived = 0;
	//int TotalDataReceived = 0;
	
	if(Com485InterfaceProtocolControl->DataPacketArrived == TRUE)
		return 1;
	
	if(WaitTimeOutLoops==0)
		return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
	
	Com485InterfaceProtocolControl->WaitDataPacketTimeOutLoopCntr = 0;
   	Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
   	SocketClientReceiveBufferLen = DataLenExpected;
	
	while((Com485InterfaceProtocolControl->WaitDataPacketTimeOutLoopCntr <= WaitTimeOutLoops))
	{
   		SocketClientReceiveBufferLen = (int)Com485InterfaceProtocolControl->RecvBufferPtr - (int)Com485InterfaceProtocolControl->RecvBuffer;
   		SocketClientReceiveBufferLen = DataLenExpected - SocketClientReceiveBufferLen;
   		if(SocketClientReceiveBufferLen<=0)
   		{
   			Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
   			DataLenExpected = COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
   			SocketClientReceiveBufferLen = DataLenExpected;
   		}
   		
   		SocketClientrecvRslt = Com485InterfaceProtocol_ReceiveData(Com485InterfaceProtocolControl, Com485InterfaceProtocolControl->comHndlr, Com485InterfaceProtocolControl->RecvBufferPtr, SocketClientReceiveBufferLen);
   		if (SocketClientrecvRslt < 0)
		{
			//!UART_DBG_EnvCad("\nrecv() error");
			ErrorInCom485InterfaceProtocolCommunication(Com485InterfaceProtocolControl);
			return SocketClientrecvRslt;
		}
		if(SocketClientrecvRslt>0)
		{
			//byteBuffToHexStr(Com485InterfaceProtocolControl->RecvBufferPtr, SocketClientrecvRslt, NULL);
			//UART_DBG_EnvCad("\r\n");
			Com485InterfaceProtocolControl->RecvBufferPtr+= SocketClientrecvRslt;
			Com485InterfaceProtocolControl->TotalDataArrived+=SocketClientrecvRslt;
			Com485InterfaceProtocolControl->WaitDataPacketTimeOutLoopCntr = 0;
			//printf("Tot Data Recv:%d\r\n", Com485InterfaceProtocolControl->TotalDataArrived);
        //!                ImprimeConFormatoStdDebug("\r\nTot Data Recv:",'l', &Com485InterfaceProtocolControl->TotalDataArrived,"\r\n",NULL);
			if((PacketLenReceived==FALSE)&&(Com485InterfaceProtocolControl->TotalDataArrived>=COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE))
			{
				//memcpy((char*)&DataLenReceived,Com485InterfaceProtocolControl->RecvBuffer,COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE);
                //!                meminvrtncpy((char*)&DataLenReceived,Com485InterfaceProtocolControl->RecvBuffer,COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE);
                memcpy((char*)&DataLenReceived,Com485InterfaceProtocolControl->RecvBuffer,COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE);
				//DataLenReceived>>=16;

				DataLenExpected = (DataLenReceived + COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE+COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE);
				//printf("Data len Recv: %d. Exp:%d.\r\n",DataLenReceived, DataLenExpected);
                                //!ImprimeConFormatoStdDebug("\r\nData len Recv:",'l',&DataLenReceived,"\r\n",NULL);
                                //!ImprimeConFormatoStdDebug("Expected:",'l',&DataLenExpected,"\r\n",NULL);
				if(DataLenExpected>=COM_485_PROTOCOL_RX_WINDOW_SIZE)
				{
					Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
					//!UART_DBG_EnvCad("\nDATA_PACKET_RECEIVED_IS_LARGER_THAN_RECV_BUFFER");
					DataLenExpected = COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
					continue;
				}
				PacketLenReceived = TRUE;	
			}
			
			if((CommandIDReceived==FALSE)&&(Com485InterfaceProtocolControl->TotalDataArrived>=(COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE+COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE)))
			{
				char * CommandIdInPacket = Com485InterfaceProtocolControl->RecvBuffer + COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
				//memcpy((char*)&CommandIDValueReceived, CommandIdInPacket ,COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE);
                //!                meminvrtncpy((char*)&CommandIDValueReceived, CommandIdInPacket ,COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE);
                memcpy((char*)&CommandIDValueReceived, CommandIdInPacket ,COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE);
				//CommandIDValueReceived>>=16;
                                /*
				if(CommandIDValueReceived<0)
				{
					Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
					UART_DBG_EnvCad("\nDATA_PACKET_RECEIVED_UNEXPECTED_ID_COMMAND_RECEIVED");
					DataLenExpected = COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
					continue;
				}*/
				CommandIDReceived = TRUE;
			}
			
			if((PacketLenReceived == TRUE)&&(CommandIDReceived==TRUE)&&(Com485InterfaceProtocolControl->TotalDataArrived >= DataLenExpected))
			{
					unsigned char * LastChar = (unsigned char *)(Com485InterfaceProtocolControl->RecvBuffer+(DataLenExpected - 1));//SocketClientCommunicationControl.RecvBufferPtr - 1;
					if(*LastChar == COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR)
					{
						DataPacketReceived = TRUE;
						//!UART_DBG_EnvCad("\nDATA_PACKET_RECEIVED_COMPLETE_PACKET_HAS_BEEN_RECEIVED");
						break;
					}	
					else
					{
						Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
						//!UART_DBG_EnvCad("\nDATA_PACKET_RECEIVED_DOES_NOT_HAVE_LAST_CHAR");
						DataLenExpected = COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE;
						continue;
					}
			}
		}
		Com485InterfaceProtocolControl->WaitDataPacketTimeOutLoopCntr++;
	}
	
	if(DataPacketReceived == TRUE)
	{
		Com485InterfaceProtocolControl->PacketLength = DataLenExpected;
		Com485InterfaceProtocolControl->CommandIdInPacketReceived = CommandIDValueReceived;
		Com485InterfaceProtocolControl->DataInPacketReceived = Com485InterfaceProtocolControl->RecvBuffer + COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + COM_485_PROTOCOL_CONFIG_DATA_PACKET_COMMAND_ID_SIZE;
		Com485InterfaceProtocolControl->DataInPacketReceivedLen = DataLenExpected - COM_485_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD;
		//!ComInterfaceProtocolsDataPacketArrived(Com485InterfaceProtocolControl);
		Com485InterfaceProtocolControl->DataPacketArrived = TRUE;
		
		
		Com485InterfaceProtocol_SendDataPacket(Com485InterfaceProtocolControl, 
				Com485InterfaceProtocolControl->CommandIdInPacketReceived , /* CommandID*/
				Com485InterfaceProtocolControl->DataInPacketReceived, /* DataInPacketReceived*/ 
				Com485InterfaceProtocolControl->DataInPacketReceivedLen); /* DataInPacketReceivedLen*/ 
				
		return COM_485_PROTOCOL_PACKET_RECEIVED;
	}
	
	Com485InterfaceProtocol_RecvBufferReset(Com485InterfaceProtocolControl);
	return COM_485_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_TIMEOUT_OCCURRED;
	
}

int Com485InterfaceProtocol_SendDataPackWaitForResponse(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int CommandId, char * PacketData, int PacketDataLen, 
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

void COM485DEMO(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int dato){	

	Com485InterfaceProtocol_SendData(Com485InterfaceProtocolControl, Com485InterfaceProtocol_GetComHndlr(Com485InterfaceProtocolControl), (char *) &dato, sizeof(dato) );
}

#endif /* __COM_485_PROTOCOL_H__ */
