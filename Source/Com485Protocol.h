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
#include "Timer.h"

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
#define COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE						(2) 	// (2 Bytes)
#define COM_485_PROTOCOL_DATA_PACKET_SLAVE_ADDRESS_FIELD_SIZE			(1)		// (1 Byte)
#define COM_485_PROTOCOL_DATA_PACKET_COMMAND_ID_FIELD_SIZE				(2) 	// (2 Bytes)
#define COM_485_PROTOCOL_DATA_PACKET_EOT_FIELD_SIZE						(1)		// (1 Byte)

#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE					(COM_485_PROTOCOL_DATA_PACKET_LEN_FIELD_SIZE + COM_485_PROTOCOL_DATA_PACKET_SLAVE_ADDRESS_FIELD_SIZE + COM_485_PROTOCOL_DATA_PACKET_COMMAND_ID_FIELD_SIZE)
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD					(COM_485_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + COM_485_PROTOCOL_DATA_PACKET_EOT_FIELD_SIZE)

#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_FINISH_CHAR					0XFF
#define COM_485_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN				(TX_BUFFER_SIZE0 - COM_485_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD)

#define COM_485_TIMER_DEFAULT_WAIT_VALUE_IN_MS							(1000)
//**********************************************************************
// Structures 
//**********************************************************************

//! Protocol description in Packet Received:
//!																		   |------------- PACKET LENGTH ----------|
//! |----------------------------------------------------------------------|-----------------|--------------------|
//! |					 			HEADER 					 			   |      DATA       | END OF TRANSMITION |
//! |------------------------|-----------------------|---------------------|-----------------|--------------------|
//! | PacketLength (2 Bytes) | SlaveAddress (1 Byte) | CommandId (2 bytes) | Data ( n Bytes) | EOT-0xFF (1 Byte ) |
//! |------------------------|-----------------------|---------------------|-----------------|--------------------|
//!
//!  PacketLength: Number of Bytes from Data[0] ... Data[n-1] to EOT character
//!  SlaveAddress: Address of device which must to excecute the commandId function
//!  CommandId:    Function or Operation to excecute
//!  Data:		   Arguments associated to CommandId
//!  EOT:		   End of Transmition, Last Character in Transmition and always is (0xFF) char value
	
typedef struct Com485ProtocolStruct
{
	// Device configuration
	int		ComHndlr;	
	char 	ComAddress;
	
	// Received Buffer resource information
	char 	RecvBuffer [COM_485_PROTOCOL_RX_WINDOW_SIZE];
	char * 	RecvBufferPtr;
	int 	TotalDataArrived;		
	
	// Packet received fields
	int		PacketLength;	
	char 	SlaveAddressInPacketReceived;
	int		CommandIdInPacketReceived;
	char * 	DataInPacketReceived;
	int		DataInPacketReceivedLen;
	
	// Control Fields
	boolean	DataPacketArrived;		
	int		WaitDataPacketTimeOutLoopCntr;	
		
} COM_485_PROTOCOL_STRUCT, * COM_485_PROTOCOL_STRUCT_PTR_;

//**********************************************************************
// Setters and Getters Prototype Fucntions
//**********************************************************************

// Device configuration
void Com485Protocol_SetComHndlr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int comHndlr);
int Com485Protocol_GetComHndlr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

void Com485Protocol_SetComAddress(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char ComAddress);
char Com485Protocol_GetComAddress(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

// Received Buffer resource information
char * Com485Protocol_GetRecvBuffer(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);
int Com485Protocol_GetRecvBufferSize(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

void Com485Protocol_SetRecvBufferPtr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char * RecvBufferPtr);
char * Com485Protocol_GetRecvBufferPtr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

void Com485Protocol_SetTotalDataArrived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int TotalDataArrived);
int  Com485Protocol_GetTotalDataArrived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

// Packet received fields
void Com485Protocol_SetPacketLength(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int PacketLength);
int  Com485Protocol_GetPacketLength(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

void Com485Protocol_SetSlaveAddressInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char SlaveAddressInPacketReceived);
char  Com485Protocol_GetSlaveAddressInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

void Com485Protocol_SetCommandIdInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int CommandIdInPacketReceived);
int  Com485Protocol_GetCommandIdInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

void  Com485Protocol_SetDataInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char * DataInPacketReceived);
char *  Com485Protocol_GetDataInPacketReceived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

void Com485Protocol_SetDataInPacketReceivedLen(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int DataInPacketReceivedLen);
int  Com485Protocol_GetDataInPacketReceivedLen(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

// Control Fields
void Com485Protocol_SetDataPacketArrived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, boolean DataPacketArrived);
boolean  Com485Protocol_GetDataPacketArrived(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

void Com485Protocol_SetWaitDataPacketTimeOutLoopCntr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int WaitDataPacketTimeOutLoopCntr);
boolean  Com485Protocol_GetWaitDataPacketTimeOutLoopCntr(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);


//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void Com485Protocol_Setup(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int comHndlr, char ComAddress);

void Com485Protocol_RecvBufferReset(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);
void ErrorInCom485ProtocolCommunication(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl);

int Com485Protocol_ReceiveData(int Com485InterfaceHandler, char * DataReceiveBuffer, int DataLen);
int Com485Protocol_SendData(int Com485InterfaceHandler, char * DataToSend, int DataLen);

int Com485Protocol_SendHeaderPacket(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int DataLen, char SlaveAddress, int CommandID);
int Com485Protocol_SendDataPacket(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen);

int Com485Protocol_WaitDataPacket(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, int WaitTimeOutLoops);
int Com485Protocol_SendDataPackWaitForResponse(COM_485_PROTOCOL_STRUCT_PTR_ Com485ProtocolControl, char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries);



#endif /* __COM_485_PROTOCOL_H__ */
