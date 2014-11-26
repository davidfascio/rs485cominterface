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
int Com485InterfaceProtocol_WaitDataPacket(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int WaitTimeOutLoops);
int Com485InterfaceProtocol_SendDataPackWaitForResponse(COM_485_PROTOCOL_CONTROL_STRUCT_PTR_ Com485InterfaceProtocolControl, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries);



#endif /* __COM_485_PROTOCOL_H__ */
