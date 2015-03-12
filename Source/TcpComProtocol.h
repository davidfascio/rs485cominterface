/*
 * File: TcpComProtocol.h
 * Author: fascio
 * 
 * Created on December 15th, 2014, 15:09
 */ 

#ifndef __TCP_COM_PROTOCOL__
#define __TCP_COM_PROTOCOL__

//**********************************************************************
// Includes
//**********************************************************************

#include "CommonSystemLibraries.h"
#include "TcpComProtocolCommons.h"
#include "TcpComInterface.h"
#include "Timer.h"

//**********************************************************************
// Data types
//**********************************************************************

typedef struct TcpComProtocolStruct{
	
	// Device configuration
	int		ComHndlr;	
	char 	ComAddress;
	char 	ComPrefix[TCP_COM_PROTOCOL_PREFIX_SIZE];
	char 	ComUser;
	char	ComPassword[TCP_COM_PROTOCOL_MAXIMUM_PASSWORD_SIZE];
	char 	ComPasswordLen;
	
	// Received Buffer resource information
	char 	RecvBuffer [TCP_COM_PROTOCOL_RX_WINDOW_SIZE];
	char * 	RecvBufferPtr;
	int 	TotalDataArrived;		
	
	// Packet received fields
	char* 	STXCharacter;
	char*	Prefix;
	char* 	User;
	char* 	PasswordLen;
	char* 	Password;
	char*	SubModuleAddress;
	char*	CommandId;	
	char*	Parameters; 	
	char*	Checksum;
	char* 	ETXCharacter;
	
	// Packet received fields	
	char 	SlaveAddressInPacketReceived;
	int		CommandIdInPacketReceived;		
	int 	ChecksumInPacketReceived;
	
	// Control Fields	
	int 	DataPacketErrorCode;
	boolean	DataPacketArrived;			
	
}TCP_COM_PROTOCOL_STRUCT, * TCP_COM_PROTOCOL_STRUCT_PTR_;

//**********************************************************************
// Setters and Getters Fucntions
//**********************************************************************

// Device configuration
void TCPComProtocol_SetComHndlr(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int ComHndlr);
void TCPComProtocol_SetComAddress(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char ComAddress);
void TCPComProtocol_SetComPrefix(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char * ComPrefix);
void TCPComProtocol_SetComUser(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char  ComUser);
void TCPComProtocol_SetComPassword(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char * ComPassword, char ComPasswordLen);
void TCPComProtocol_SetTotalDataArrived(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int TotalDataArrived );
void TCPComProtocol_SetDataPacketArrived(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, boolean DataPacketArrived);
void TCPComProtocol_SetDataPacketErrorCode(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int DataPacketErrorCode);

int TCPComProtocol_GetComHndlr(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl);
int TCPComProtocol_GetDataPacketErrorCode(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl);
boolean TCPComProtocol_GetDataPacketArrived(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl);

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void TCPComProtocol_Setup(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int comHndlr,
						  char ComAddress, char * ComPrefix , char ComUser, char * ComPassword, char ComPasswordLen);
void TCPComProtocol_RecvBufferReset(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl);
void ErrorInTCPComProtocolCommunication(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl);

int TCPComProtocol_ReceiveData(int Com485InterfaceHandler, char * DataReceiveBuffer, int DataLen);
int TCPComProtocol_SendData(int Com485InterfaceHandler, char * DataToSend, int DataLen);

//int TCPComProtocol_SendHeaderPacket(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl,  char SlaveAddress, int CommandID);
int TCPComProtocol_SendDataPacket(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int CommandId, char * PacketData, int PacketDataLen);

int TCPComProtocol_WaitDataPacket(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int WaitTimeOutLoops);

/*int TCPComProtocol_SendDataPackWaitForResponse(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries);*/


#endif /* __TCP_COM_PROTOCOL__ */
