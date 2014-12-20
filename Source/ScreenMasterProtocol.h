/*
 * File: ScreenMasterProtocol.h
 * Author: fascio
 * 
 * Created on December 17th, 2014, 17:39
 */ 
 
#ifndef __SCREEN_MASTER_PROTOCOL_H__
#define __SCREEN_MASTER_PROTOCOL_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "TCPComProtocol.h"
#include "ScreenMasterCommandList.h"
#include "ScreenMasterCommands.h"

//**********************************************************************
// Defines
//**********************************************************************
#define SCREEN_MASTER_PROTOCOL_DEFAULT_SLAVE_ADDRESS			   	(0x11)
#define SCREEN_MASTER_PROTOCOL_DEFAULT_MASTER_ADDRESS			   	(0x01)
#define SCREEN_MASTER_PROTOCOL_DEFAULT_BROADCAST_ADDRESS		   	(0x00)

#define SCREEN_MASTER_PROTOCOL_WAIT_TIME_OUT					   (100)

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void ScreenMasterProtocol_Setup(char ComAddress );
void ScreenMasterProtocol_WaitDataPacketCheck(void);
void ScreenMasterProtocol_ProcessingDataPacketArrived(void);


/*int ScreenDisplayProtocol_SendDataPackWaitForResponse(char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries);*/
int ScreenMasterProtocol_SendDataPacket(int CommandId, char * PacketData, int PacketDataLen);

void ScreenMasterProtocol_FormatBuilder(int data, char * buffer, int bufferLen);
#endif /* __SCREEN_MASTER_PROTOCOL_H__ */
