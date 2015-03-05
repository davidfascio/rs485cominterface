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
//#include "ScreenDisplayDevice.h" //temp

//**********************************************************************
// Defines
//**********************************************************************
//#define SCREEN_DISPLAY_PROTOCOL_DEFAULT_SLAVE_ADDRESS			   	(0x11)
#define SCREEN_DISPLAY_PROTOCOL_DEFAULT_MASTER_ADDRESS			   	(1)
#define SCREEN_DISPLAY_PROTOCOL_DEFAULT_BROADCAST_ADDRESS		   	(0)
#define SCREEN_DISPLAY_PROTOCOL_DEFAULT_PEER_TO_PEER_ADDRESS	   	(248)
#define SCREEN_DISPLAY_PROTOCOL_DEFAULT_SLAVE_ADDRESS			   	SCREEN_DISPLAY_PROTOCOL_DEFAULT_PEER_TO_PEER_ADDRESS

#ifdef  __MASTER_DEVICE__
	#define SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT					   (250)
#else 
	#define SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT					   (150)
#endif /* __MASTER_DEVICE__ */

#define SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES			(3)
//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void ScreenDisplayProtocol_Setup(char ComAddress );
void ScreenDisplayProtocol_WaitDataPacketCheck(void);
void ScreenDisplayProtocol_ProcessingDataPacketArrived(void);
int ScreenDisplayProtocol_StateMachineUpdate(void);

int ScreenDisplayProtocol_SendDataPackWaitForResponse(char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen, 
														int ResponseCommandId, int WaitTimeOutSec, int Retries);
int ScreenDisplayProtocol_SendDataPacket(char SlaveAddress, int CommandId, char * PacketData, int PacketDataLen);

int ScreenDisplayProtocol_GetCommandIdInPacketReceived(void);
char * ScreenDisplayProtocol_GetDataInPacketReceived(void);
int ScreenDisplayProtocol_GetDataInPacketReceivedLen(void);

#endif /* __SCREEN_DISPLAY_PROTOCOL_H__ */
