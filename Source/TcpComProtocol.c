////////////////////////////////////////////////////////////////////////
//
// File name: TcpComProtocol.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "TcpComProtocol.h"

//**********************************************************************
// Variables
//********************************************************************** 
TIMER_STRUCT TCPComTimer;

//**********************************************************************
// Setters and Getters Fucntions
//**********************************************************************

// Device configuration
void TCPComProtocol_SetComHndlr(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int ComHndlr){
			
	TCPComProtocolControl->ComHndlr = ComHndlr;
}

void TCPComProtocol_SetComAddress(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char ComAddress){
			
	TCPComProtocolControl->ComAddress = ComAddress;
}

void TCPComProtocol_SetComPrefix(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char * ComPrefix){			
	
	memcpy(TCPComProtocolControl->ComPrefix, ComPrefix,TCP_COM_PROTOCOL_PREFIX_SIZE);	
}

void TCPComProtocol_SetComUser(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char  ComUser){			
	
	TCPComProtocolControl->ComUser = ComUser;
}

void TCPComProtocol_SetComPassword(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char * ComPassword, char ComPasswordLen){			
	
	memset(TCPComProtocolControl->ComPassword, 0 , TCP_COM_PROTOCOL_PASSWORD_SIZE);
	memcpy(TCPComProtocolControl->ComPassword, ComPassword, ComPasswordLen);	
	TCPComProtocolControl->ComPasswordLen = ComPasswordLen;
}

void TCPComProtocol_SetTotalDataArrived(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int TotalDataArrived ){
	
	TCPComProtocolControl->TotalDataArrived = TotalDataArrived;
}

int TCPComProtocol_GetComHndlr(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl){
	
	return 	TCPComProtocolControl->ComHndlr;
}

int TCPComProtocol_GetDataPacketErrorCode(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl){
	
	return TCPComProtocolControl->DataPacketErrorCode;
}


void TCPComProtocol_SetDataPacketErrorCode(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int DataPacketErrorCode){
	
	TCPComProtocolControl->DataPacketErrorCode = DataPacketErrorCode;
}

boolean TCPComProtocol_GetDataPacketArrived(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl){
	
	return TCPComProtocolControl->DataPacketArrived;
}

void TCPComProtocol_SetDataPacketArrived(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, boolean DataPacketArrived){
	
	TCPComProtocolControl->DataPacketArrived = 	DataPacketArrived;
}

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void TCPComProtocol_Setup(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int comHndlr,
						  char ComAddress, char * ComPrefix , char ComUser, char * ComPassword, char ComPasswordLen){
	
	memset(TCPComProtocolControl, 0, sizeof(TCP_COM_PROTOCOL_STRUCT));	
	
	TCPComProtocol_SetComHndlr(TCPComProtocolControl, comHndlr);
	TCPComProtocol_SetComAddress(TCPComProtocolControl, ComAddress);
	TCPComProtocol_SetComPrefix(TCPComProtocolControl, ComPrefix);
	TCPComProtocol_SetComUser(TCPComProtocolControl, ComUser);
	TCPComProtocol_SetComPassword(TCPComProtocolControl, ComPassword, ComPasswordLen);	
		
	TCPComProtocol_RecvBufferReset(TCPComProtocolControl);	

	//! Configure Timer
	AddTimer(&TCPComTimer, TCP_COM_TIMER_DEFAULT_WAIT_VALUE_IN_MS);

	//!TCPComInterface_Setup();	
    bsp_usart1_setup(hacer_nada);	
}

void hacer_nada(void){
	
}

void TCPComProtocol_RecvBufferReset(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl){
	
	TCPComProtocol_SetTotalDataArrived(TCPComProtocolControl, 0);	
	
	memset(TCPComProtocolControl->RecvBuffer,0, TCP_COM_PROTOCOL_RX_WINDOW_SIZE);
	
	TCPComProtocolControl->RecvBufferPtr = TCPComProtocolControl->RecvBuffer;	
	
	TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_NO_ERROR_CODE;
}

void ErrorInTCPComProtocolCommunication(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl){
	
	TCPComProtocol_RecvBufferReset(TCPComProtocolControl);
}

int TCPComProtocol_ReceiveData(int Com485InterfaceHandler, char * DataReceiveBuffer, int DataLen){

	//!return TCPComInterface_Read(DataReceiveBuffer, DataLen);
	return bsp_usart1_read(DataReceiveBuffer, DataLen);
}

int TCPComProtocol_SendData(int Com485InterfaceHandler, char * DataToSend, int DataLen){
	
	//!return TCPComInterface_Write(DataToSend, DataLen);
	return bsp_usart1_write(DataToSend, DataLen);
}



int TCPComProtocol_SendDataPacket(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, 
									int CommandId, char * PacketData, int PacketDataLen){
										
	int sendrslt;
	volatile unsigned int checksum;
	
	volatile char headerbuff[TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + 1];		
	volatile char tailbuff[TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_TAIL_SIZE + 1];	
		
	if( PacketDataLen < 0 || PacketDataLen > TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_MAX_DATA_LEN)	
		return TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
		
	// Clear buffer
	memset(headerbuff, 0, TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE + 1);
	
	// Buildding Header
	sprintf(headerbuff,"%c%s%c%04d%c", 		 TCP_COM_PROTOCOL_DEFAULT_STX_CHAR,	 
											 TCPComProtocolControl->ComPrefix,											 
											 TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR, 
											 CommandId,
											 TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);					
	
	
	sendrslt = TCPComProtocol_SendData(TCPComProtocol_GetComHndlr(TCPComProtocolControl), headerbuff, TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE);
	checksum = strchecksum(headerbuff, TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_HEADER_SIZE);
	if(sendrslt == RTCS_NO_ERROR){
		
		// Sendding Body
		
		sendrslt = TCPComProtocol_SendData(TCPComProtocol_GetComHndlr(TCPComProtocolControl), PacketData, PacketDataLen);
		checksum += strchecksum(PacketData, PacketDataLen);
		if(sendrslt == RTCS_NO_ERROR){
			
			// Clear buffer
			memset(tailbuff, 0, TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_TAIL_SIZE + 1);
			
			sprintf(tailbuff,"%04X%c", checksum, TCP_COM_PROTOCOL_DEFAULT_ETX_CHAR);		
			
			sendrslt = TCPComProtocol_SendData(TCPComProtocol_GetComHndlr(TCPComProtocolControl), tailbuff, TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_TAIL_SIZE);
		}		
	}
	
	return sendrslt;
										
}


int TCPComProtocol_WaitDataPacket(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, int WaitTimeOutLoops){
	
	
	volatile int SocketClientrecvRslt = 0;
	
	volatile boolean STXCharacterReceived = FALSE;
	volatile boolean ETXCharacterReceived = FALSE;
	volatile boolean DataPacketReceived = FALSE;
		
	volatile char * RecvBufferIndexPtr;

	//******************************************************************
	//* 					Temporary Data	
	//******************************************************************
	volatile char tempChecksum[TCP_COM_PROTOCOL_CHECKSUM_SIZE];
	volatile char * checksumIndex;
	volatile unsigned int checksumValue = 0;
	
	volatile char tempUserBuffer[TCP_COM_PROTOCOL_USER_SIZE];
	
	volatile char tempPasswordLen[TCP_COM_PROTOCOL_PASSWORD_SIZE];
	
	volatile char tempSubAddress[TCP_COM_PROTOCOL_SUBADDRESS_SIZE];
	
	volatile char tempCommandId[TCP_COM_PROTOCOL_COMMAND_ID_SIZE];
	
	volatile char tempDataPacketLen[TCP_COM_PROTOCOL_DATA_PACKET_SIZE];
	
	volatile int tempdato;
	
	//******************************************************************
	//* 					Temporary Data	
	//******************************************************************
	
	if(TCPComProtocolControl->DataPacketArrived == TRUE)
		return 1;
	
	if(Timer_SetOverflowValue_MS(&TCPComTimer, WaitTimeOutLoops) < 0)
		return TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_BAD_PARAMETERS;
	
	// Initialization Process	
   	TCPComProtocol_RecvBufferReset(TCPComProtocolControl);   	   	
	
	while(Timer_GetOverflow(&TCPComTimer) == FALSE)
	{	
   		// Reading Process
   		
   		if ((TCPComProtocolControl->RecvBufferPtr - TCPComProtocolControl->RecvBuffer) >= 
			(TCP_COM_PROTOCOL_RX_WINDOW_SIZE - TCP_COM_PROTOCOL_DEFAULT_DATA_LEN_EXPECTED)){
				
				TCPComProtocol_RecvBufferReset(TCPComProtocolControl);				
		}
			
   		SocketClientrecvRslt = TCPComProtocol_ReceiveData(	TCPComProtocolControl->ComHndlr, 
															TCPComProtocolControl->RecvBufferPtr, 
															TCP_COM_PROTOCOL_DEFAULT_DATA_LEN_EXPECTED);   		
   		
   		if (SocketClientrecvRslt < 0) {
			
			ErrorInTCPComProtocolCommunication(TCPComProtocolControl);
			return SocketClientrecvRslt;
		}
		
		if(SocketClientrecvRslt > 0)
		{			
			TCPComProtocolControl->RecvBufferPtr 	+= SocketClientrecvRslt;
			TCPComProtocolControl->TotalDataArrived += SocketClientrecvRslt;				
			Timer_Reset(&TCPComTimer);
									
			// Processing Start of Packet
			if (STXCharacterReceived == FALSE) {				
				
				//**************************************************************************************************
				//* STX CHARACTER
				//**************************************************************************************************
				RecvBufferIndexPtr = strchr(TCPComProtocolControl->RecvBuffer,  TCP_COM_PROTOCOL_DEFAULT_STX_CHAR);
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->STXCharacter = RecvBufferIndexPtr;
					
					STXCharacterReceived = TRUE;					
				}
			}
			
			// Processing End of Packet
			if ((ETXCharacterReceived == FALSE) && (STXCharacterReceived == TRUE)) {				
				
				//**************************************************************************************************
				//* ETX CHARACTER
				//**************************************************************************************************
				RecvBufferIndexPtr = strchr(TCPComProtocolControl->RecvBuffer, TCP_COM_PROTOCOL_DEFAULT_ETX_CHAR);
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->ETXCharacter = RecvBufferIndexPtr;
					
					/* VALIDATION */			
						
					if(TCPComProtocolControl->ETXCharacter - TCPComProtocolControl->STXCharacter <= 0){						
						break;
					}
					
					
					ETXCharacterReceived = TRUE;					
				}				
			}
			
			if ((ETXCharacterReceived == TRUE) && (STXCharacterReceived == TRUE)){
				
				//**************************************************************************************************
				//* CHECKSUM
				//**************************************************************************************************				
				RecvBufferIndexPtr = strrchr(TCPComProtocolControl->RecvBuffer, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->Checksum = RecvBufferIndexPtr + 1;
					
					/* VALIDATION */
					if((TCPComProtocolControl->ETXCharacter - TCPComProtocolControl->Checksum) != 
						TCP_COM_PROTOCOL_CHECKSUM_SIZE){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_CHECKSUM_BAD_SIZE_ERROR_CODE;
						break;
					}
					
					memcpy(tempChecksum, TCPComProtocolControl->Checksum, TCP_COM_PROTOCOL_CHECKSUM_SIZE);					
					
					
					
					TCPComProtocolControl->ChecksumInPacketReceived = str2uint(tempChecksum, TCP_COM_PROTOCOL_CHECKSUM_SIZE, 16);						
										
					for (checksumIndex = TCPComProtocolControl->STXCharacter; checksumIndex < TCPComProtocolControl->Checksum; checksumIndex ++)
						checksumValue += *checksumIndex;
					
					
					
					
					if (checksumValue != TCPComProtocolControl->ChecksumInPacketReceived) {						
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_CHECKSUM_NO_MATCH_ERROR_CODE;
						break;					
					}
						
					
				} else {
					
					
					TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_CHECKSUM_NO_FOUND_ERROR_CODE;
					break;					
				}
				
				//**************************************************************************************************
				//* PREFIX
				//**************************************************************************************************				
				RecvBufferIndexPtr = TCPComProtocolControl->STXCharacter;
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->Prefix = RecvBufferIndexPtr + 1;
					
					/* VALIDATION */		
					if(memcmp(TCPComProtocolControl->ComPrefix, TCPComProtocolControl->Prefix, TCP_COM_PROTOCOL_PREFIX_SIZE)){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PREFIX_NO_MATCH_ERROR_CODE;
						break;
					}
					
					
				} else {
					
					TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PREFIX_NO_FOUND_ERROR_CODE;
					break;	
				}
					
				//**************************************************************************************************
				//* USER
				//**************************************************************************************************							
				RecvBufferIndexPtr = strchr(TCPComProtocolControl->Prefix, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->User = RecvBufferIndexPtr + 1;
					
					/* VALIDATION */					
					if( TCPComProtocolControl->User == TCPComProtocolControl->Checksum ){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_USER_CHECKSUM_POSITION_ERROR_CODE;
						break;
					}
						
					memcpy(tempUserBuffer, TCPComProtocolControl->User, TCP_COM_PROTOCOL_USER_SIZE);
					
					
					
					if (str2uint(tempUserBuffer, TCP_COM_PROTOCOL_USER_SIZE, 10)  != 	TCPComProtocolControl->ComUser){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_USER_NO_MATCH_ERROR_CODE;
						break;
					}
					
					
					
				} else {
					
					TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_USER_NO_FOUND_ERROR_CODE;
					break;
				}
				
				//**************************************************************************************************
				//* PASSWORD LENGHT
				//**************************************************************************************************				
				RecvBufferIndexPtr = strchr(TCPComProtocolControl->User, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->PasswordLen = RecvBufferIndexPtr + 1;
					
					/* VALIDATION */	
					
					if( TCPComProtocolControl->PasswordLen == TCPComProtocolControl->Checksum ){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PASSWORD_LEN_CHECKSUM_POSITION_ERROR_CODE;
						break;	
					}
					
					
					memcpy(tempPasswordLen, TCPComProtocolControl->PasswordLen, TCP_COM_PROTOCOL_PASSWORD_SIZE);
										
					/*if(	TCPComProtocolControl->ComPasswordLen < TCP_COM_PROTOCOL_MINIMUM_PASSWORD_SIZE || 
						TCPComProtocolControl->ComPasswordLen > TCP_COM_PROTOCOL_MAXIMUM_PASSWORD_SIZE )*/
					//tempdato = (int) atoi(tempPasswordLen);
					
					
					if (str2uint(tempPasswordLen, TCP_COM_PROTOCOL_PASSWORD_SIZE, 10)!= TCPComProtocolControl->ComPasswordLen){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PASSWORD_LEN_NO_MATCH_ERROR_CODE;
						break;
					}
					
					
					
				} else {
					
					TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PASSWORD_LEN_NO_FOUND_ERROR_CODE;
					break;
				}
					
				//**************************************************************************************************
				//* PASSWORD 
				//**************************************************************************************************
				RecvBufferIndexPtr = strchr(TCPComProtocolControl->PasswordLen, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->Password = RecvBufferIndexPtr + 1;
					
					/* VALIDATION */		
					
					if( TCPComProtocolControl->Password == TCPComProtocolControl->Checksum ){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PASSWORD_CHECKSUM_POSITION_ERROR_CODE;
						break;	
					}
					
					
						
					if(memcmp(TCPComProtocolControl->ComPassword, TCPComProtocolControl->Password, TCPComProtocolControl->ComPasswordLen)){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PASSWORD_NO_MATCH_ERROR_CODE;
						break;			
					}
					
					
					
				} else {
					
					TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PASSWORD_NO_FOUND_ERROR_CODE;
					break;
				}
					
				//**************************************************************************************************
				//* SUBMODULE ADDRESS 
				//**************************************************************************************************				
				RecvBufferIndexPtr = strchr(TCPComProtocolControl->Password, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->SubModuleAddress = RecvBufferIndexPtr + 1;
					
					/* VALIDATION */			
					
					if( TCPComProtocolControl->SubModuleAddress == TCPComProtocolControl->Checksum ){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_SUBADDRESS_CHECKSUM_POSITION_ERROR_CODE;
						break;			
					}
						
					memcpy(tempSubAddress, TCPComProtocolControl->SubModuleAddress, TCP_COM_PROTOCOL_SUBADDRESS_SIZE);
					
					if (str2uint(tempSubAddress, TCP_COM_PROTOCOL_SUBADDRESS_SIZE, 10) < 0){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_SUBADDRESS_FORMAT_ERROR_CODE;
						break;
					}
						
					TCPComProtocolControl->SlaveAddressInPacketReceived = str2uint(tempSubAddress, TCP_COM_PROTOCOL_SUBADDRESS_SIZE, 10);					
										
					
					
				} else {
					
					TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_SUBADDRESS_NO_FOUND_ERROR_CODE;
					break;
				}
				
				//**************************************************************************************************
				//* COMMAND ID
				//**************************************************************************************************				
				RecvBufferIndexPtr = strchr(TCPComProtocolControl->SubModuleAddress, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->CommandId = RecvBufferIndexPtr + 1;
					
					/* VALIDATION */	
					if( TCPComProtocolControl->CommandId == TCPComProtocolControl->Checksum ){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_COMMAND_ID_CHECKSUM_POSITION_ERROR_CODE;
						break;			
					}
					
					memcpy(tempCommandId, TCPComProtocolControl->CommandId, TCP_COM_PROTOCOL_COMMAND_ID_SIZE);					
					
					if (str2uint(tempCommandId, TCP_COM_PROTOCOL_COMMAND_ID_SIZE, 10) < 0){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_COMMAND_ID_FORMAT_ERROR_CODE;
						break;
					}
					
					TCPComProtocolControl->CommandIdInPacketReceived = str2uint(tempCommandId, TCP_COM_PROTOCOL_COMMAND_ID_SIZE, 10);						
					
				} else {
					
					TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_COMMAND_ID_NO_FOUND_ERROR_CODE;
					break;
				}
				
				//**************************************************************************************************
				//* PARAMETERS
				//**************************************************************************************************
				RecvBufferIndexPtr = strchr(TCPComProtocolControl->CommandId, TCP_COM_PROTOCOL_DEFAULT_BREAK_CHAR);
				
				if (RecvBufferIndexPtr != NULL){
					
					TCPComProtocolControl->Parameters = RecvBufferIndexPtr + 1;
					
					/* VALIDATION */	
					if( TCPComProtocolControl->Parameters == TCPComProtocolControl->Checksum ){
						
						TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PARAMETERS_CHECKSUM_POSITION_ERROR_CODE;
						break;					
					}
					
					
					
				} else {
					
					TCPComProtocolControl->DataPacketErrorCode = TCP_COM_PROTOCOL_PARAMETERS_NO_FOUND_ERROR_CODE;
					break;
				}
						
				DataPacketReceived = TRUE;
				
				break;
			}
			
			// Processing rest of the information 						
		}
	}
			
	if(DataPacketReceived == TRUE)
	{	
		TCPComProtocolControl->DataPacketArrived = TRUE;				
		return TCP_COM_PROTOCOL_PACKET_RECEIVED;
	}

	//TCPComProtocol_RecvBufferReset(TCPComProtocolControl);
	return TCP_COM_PROTOCOL_CONFIG_DATA_PACKET_RECEIVED_TIMEOUT_OCCURRED;
	
}

/*int TCPComProtocol_SendDataPackWaitForResponse(TCP_COM_PROTOCOL_STRUCT_PTR_ TCPComProtocolControl, char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries);*/




