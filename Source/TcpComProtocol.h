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

//!#include "Com485Interface.h"
#include "CommonSystemLibraries.h"
#include "Utils.h"
#include "Timer.h"

//**********************************************************************
// Defines
//**********************************************************************

// High Level Defines
#ifndef TCP_COM_PROTOCOL_RX_WINDOW_SIZE   
#define TCP_COM_PROTOCOL_RX_WINDOW_SIZE 								(50)
#endif

#ifndef RTCS_ERROR
#define RTCS_ERROR 														(-1)
#endif

#ifndef RTCS_NO_ERROR
#define RTCS_NO_ERROR 													(0)
#endif

#ifndef TCP_COM_PROTOCOL_PACKET_RECEIVED
#define TCP_COM_PROTOCOL_PACKET_RECEIVED 								(1)
#endif

#ifndef TCP_COM_PROTOCOL_PACKET_SENT
#define TCP_COM_PROTOCOL_PACKET_SENT 									(1)
#endif

#define TCP_COM_PROTOCOL_DO_NOT_SEND_DATA_PACKET						(0)
#define TCP_COM_PROTOCOL_DO_NOT_WAIT_DATA_PACKET						(0)

#define TCP_COM_PROTOCOL_MAX_TIME_OUT_LOOPS								(500)


#define TCP_COM_PROTOCOL_SEND_DATA_PACKET_WAIT_RESPONSE_DO_NOT_RETRY	(1)
#define TCP_COM_PROTOCOL_SEND_DATA_PACKET_WAIT_RESPONSE_DEFAULT_RETIES	(3)

// Error Code Defines
#define TCP_COM_PROTOCOL_DATA_PACKET_ARRIVED							(1)
#define TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS		(-50)
#define TCP_COM_PROTOCOL_PACKET_RECEIVED_IS_LARGER_THAN_RECV_BUFFER		(-51)
#define TCP_COM_PROTOCOL_PACKET_RECEIVED_UNEXPECTED_ID_COMMAND_RECEIVED	(-52)
#define TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_TIMEOUT_OCCURRED	(-53)
#define TCP_COM_PROTOCOL_PACKET_RECEIVED_DOES_NOT_HAVE_LAST_CHAR		(-54)
#define TCP_COM_PROTOCOL_DATA_PACKET_RECEIVED_PROCESSING				(-55)
#define TCP_COM_PROTOCOL_DATA_PACKET_ARRIVED_PROCESSING					(-56)

//**********************************************************************
// Structures 
//**********************************************************************

//! Protocol description in Packet Received:
//!												 	
//! +---+----------------------------------------+-----------------------+----------+---+
//! |STX|				HEADER 		             |      	DATA       	 | CHECKSUM	|ETX|
//! +---+-----+----+----+--------------+----+----+----+------------------+----------+---+
//! | < | BAZ | $u | $l | $cccccc(ccc) | $h | $n |  $p$p$p$p$p$p$p$p$p$p | 	$kkkk	| > |
//! +---+-----+----+----+--------------+----+----+----+------------------+----------+---+
//!  
//!  Ascii Format
//!  < 	: Start of Transmition Character				-	
//!  BAZ: Prefix of protocol (BANCO AZTECA)				-	
//!  $u : Associated user to this device				- 	'$' Character + {'0' Ascii Value: Administrador}
//!  $l : Password Lenght {6,7,8,9}						-	'$' Character + From '6'to '9' Ascii Value
//!	 $cccccc(ccc) : Password							-	'$' Character + String of Password Lenght 
//!  $h : Sub-Module Address							-   '$' Character + From '001' to '247' {'000' for Broadcast and '248' Per to per Communication}
//!  $n : CommandId, Function or Operation to excecute  -   '$' Character + Upper '1000' Descriptor
//!  $p$p$p$p$p$p$p: Parameters							-	'$' Character + Parammeters in String Form
//!  $kkkk : Checksum in Hexadecimal format				-   '$' Character + Checksum from '<' Character position to last character in data packet. In Hexadecimal Format
//!  >	: Last Character in Transmition 				-
//!
//! Protocol description in Packet Send:
//!						
//! +---+----------+--------------+----------+---+
//! |STX|  HEADER  |  	 DATA     | CHECKSUM |ETX|
//! +---+-----+----+----+---------+----------+---+
//! | < | BAZ | $n | $p$p$p$p$p$p |  $kkkk   | > |
//! +---+-----+----+----+---------+----------+---+
//!  
//!  Ascii Format
//!  < 	: Start of Transmition Character				-	
//!  BAZ: Prefix of protocol (BANCO AZTECA)				-	
//!  $n : CommandId, Function or Operation to excecute  -   '$' Character + Upper '1000' Descriptor
//!  $ppppppppppppp: Parameters							-	'$' Character + Parammeters in String Form
//!  $kkkk : Checksum in Hexadecimal format				-   '$' Character + Checksum from '<' Character position to last character in data packet. In Hexadecimal Format
//!  >	: Last Character in Transmition 				-

//! TCP_COM_PROTOCOL
#define TCP_COM_PROTOCOL_DEFAULT_STX_CHAR								'<'
#define TCP_COM_PROTOCOL_DEFAULT_ETX_CHAR								'>'
#define TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR								'$'
#define TCP_COM_PROTOCOL_DEFAULT_PREFIX									"BAZ"

#define TCP_COM_PROTOCOL_STX_CHAR_SIZE									(1)
#define TCP_COM_PROTOCOL_ETX_CHAR_SIZE									(1)
#define TCP_COM_PROTOCOL_BREAK_CHAR_SIZE								(1)

#define TCP_COM_PROTOCOL_PREFIX_SIZE									(3)
#define TCP_COM_PROTOCOL_USER_SIZE										(1)

#define TCP_COM_PROTOCOL_PASSWORD_SIZE									(1)
#define TCP_COM_PROTOCOL_MINIMUM_PASSWORD_SIZE							(6)
#define TCP_COM_PROTOCOL_MAXIMUM_PASSWORD_SIZE							(9)

#define TCP_COM_PROTOCOL_SUBADDRESS_SIZE								(3)
#define TCP_COM_PROTOCOL_COMMAND_ID_SIZE								(4)

#define TCP_COM_PROTOCOL_DATA_PACKET_SIZE								(2)

#define TCP_COM_PROTOCOL_CHECKSUM_SIZE									(4)
#define TCP_COM_PROTOCOL_MAX_CHECKSUM_VALUE								(0x10000)


#define TCP_COM_TIMER_DEFAULT_WAIT_VALUE_IN_MS							(100)
#define TCP_COM_PROTOCOL_DEFAULT_DATA_LEN_EXPECTED						(1)

#define TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE 				(TCP_COM_PROTOCOL_STX_CHAR_SIZE + \
																		TCP_COM_PROTOCOL_PREFIX_SIZE + \
																		TCP_COM_PROTOCOL_BREAK_CHAR_SIZE +	\																		
																		TCP_COM_PROTOCOL_COMMAND_ID_SIZE + \
																		TCP_COM_PROTOCOL_BREAK_CHAR_SIZE )
																		
#define TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_TAIL_SIZE 					(TCP_COM_PROTOCOL_CHECKSUM_SIZE + \
																		TCP_COM_PROTOCOL_ETX_CHAR_SIZE)
																		
#define TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD				   (TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + \
																		TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_TAIL_SIZE )
																		
#define TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN				(BSP_TX_BUFFER_SIZE - TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_OVERHEAD)

//**********************************************************************
//* ERROR CODE
//**********************************************************************
#define TCP_COM_PROTOCOL_NO_ERROR_CODE									(0)
#define TCP_COM_PROTOCOL_CHECKSUM_BASE_ERROR_CODE						(100)
#define TCP_COM_PROTOCOL_PREFIX_BASE_ERROR_CODE							(200)
#define TCP_COM_PROTOCOL_USER_BASE_ERROR_CODE							(300)
#define TCP_COM_PROTOCOL_PASSWORD_LEN_BASE_ERROR_CODE					(400)
#define TCP_COM_PROTOCOL_PASSWORD_BASE_ERROR_CODE						(500)
#define TCP_COM_PROTOCOL_SUBADDRESS_BASE_ERROR_CODE						(600)
#define TCP_COM_PROTOCOL_COMMAND_ID_BASE_ERROR_CODE						(700)
#define TCP_COM_PROTOCOL_PARAMETERS_BASE_ERROR_CODE						(800)


//Checksum Error Codes
#define TCP_COM_PROTOCOL_CHECKSUM_NO_FOUND_ERROR_CODE					(TCP_COM_PROTOCOL_CHECKSUM_BASE_ERROR_CODE |1)
#define TCP_COM_PROTOCOL_CHECKSUM_NO_MATCH_ERROR_CODE					(TCP_COM_PROTOCOL_CHECKSUM_BASE_ERROR_CODE |2)
#define TCP_COM_PROTOCOL_CHECKSUM_BAD_SIZE_ERROR_CODE					(TCP_COM_PROTOCOL_CHECKSUM_BASE_ERROR_CODE |3)

//Prefix Error Codes
#define TCP_COM_PROTOCOL_PREFIX_NO_FOUND_ERROR_CODE						(TCP_COM_PROTOCOL_PREFIX_BASE_ERROR_CODE |1)
#define TCP_COM_PROTOCOL_PREFIX_NO_MATCH_ERROR_CODE						(TCP_COM_PROTOCOL_PREFIX_BASE_ERROR_CODE |2)

//User Error Codes
#define TCP_COM_PROTOCOL_USER_NO_FOUND_ERROR_CODE						(TCP_COM_PROTOCOL_USER_BASE_ERROR_CODE |1)
#define TCP_COM_PROTOCOL_USER_NO_MATCH_ERROR_CODE						(TCP_COM_PROTOCOL_USER_BASE_ERROR_CODE |2)
#define TCP_COM_PROTOCOL_USER_CHECKSUM_POSITION_ERROR_CODE				(TCP_COM_PROTOCOL_USER_BASE_ERROR_CODE |3)

//Password Len Error Codes
#define TCP_COM_PROTOCOL_PASSWORD_LEN_NO_FOUND_ERROR_CODE				(TCP_COM_PROTOCOL_PASSWORD_LEN_BASE_ERROR_CODE |1)
#define TCP_COM_PROTOCOL_PASSWORD_LEN_NO_MATCH_ERROR_CODE				(TCP_COM_PROTOCOL_PASSWORD_LEN_BASE_ERROR_CODE |2)
#define TCP_COM_PROTOCOL_PASSWORD_LEN_CHECKSUM_POSITION_ERROR_CODE		(TCP_COM_PROTOCOL_PASSWORD_LEN_BASE_ERROR_CODE |3)

//Password Error Codes
#define TCP_COM_PROTOCOL_PASSWORD_NO_FOUND_ERROR_CODE					(TCP_COM_PROTOCOL_PASSWORD_BASE_ERROR_CODE |1)
#define TCP_COM_PROTOCOL_PASSWORD_NO_MATCH_ERROR_CODE					(TCP_COM_PROTOCOL_PASSWORD_BASE_ERROR_CODE |2)
#define TCP_COM_PROTOCOL_PASSWORD_CHECKSUM_POSITION_ERROR_CODE			(TCP_COM_PROTOCOL_PASSWORD_BASE_ERROR_CODE |3)

//Sub Address Error Codes
#define TCP_COM_PROTOCOL_SUBADDRESS_NO_FOUND_ERROR_CODE					(TCP_COM_PROTOCOL_SUBADDRESS_BASE_ERROR_CODE |1)
#define TCP_COM_PROTOCOL_SUBADDRESS_CHECKSUM_POSITION_ERROR_CODE		(TCP_COM_PROTOCOL_SUBADDRESS_BASE_ERROR_CODE |3)
#define TCP_COM_PROTOCOL_SUBADDRESS_FORMAT_ERROR_CODE					(TCP_COM_PROTOCOL_SUBADDRESS_BASE_ERROR_CODE |4)

//Command Id Error Codes
#define TCP_COM_PROTOCOL_COMMAND_ID_NO_FOUND_ERROR_CODE					(TCP_COM_PROTOCOL_COMMAND_ID_BASE_ERROR_CODE |1)
#define TCP_COM_PROTOCOL_COMMAND_ID_CHECKSUM_POSITION_ERROR_CODE		(TCP_COM_PROTOCOL_COMMAND_ID_BASE_ERROR_CODE |3)
#define TCP_COM_PROTOCOL_COMMAND_ID_FORMAT_ERROR_CODE					(TCP_COM_PROTOCOL_COMMAND_ID_BASE_ERROR_CODE |4)

//Parameters Error Codes
#define TCP_COM_PROTOCOL_PARAMETERS_NO_FOUND_ERROR_CODE					(TCP_COM_PROTOCOL_PARAMETERS_BASE_ERROR_CODE |1)
#define TCP_COM_PROTOCOL_PARAMETERS_CHECKSUM_POSITION_ERROR_CODE		(TCP_COM_PROTOCOL_PARAMETERS_BASE_ERROR_CODE |3)


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

int TCPComProtocol_GetComHndlr(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl);

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void TCPComProtocol_Setup(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int comHndlr,
						  char ComAddress, char * ComPrefix , char ComUser, char * ComPassword, char ComPasswordLen);
void hacer_nada(void);
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
