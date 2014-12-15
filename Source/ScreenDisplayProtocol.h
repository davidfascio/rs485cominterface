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
#include "ScreenDisplayDevice.h" //temp

//**********************************************************************
// Defines
//**********************************************************************
#define SCREEN_DISPLAY_PROTOCOL_DEFAULT_SLAVE_ADDRESS			   	(0x11)
#define SCREEN_DISPLAY_PROTOCOL_DEFAULT_MASTER_ADDRESS			   	(0x01)
#define SCREEN_DISPLAY_PROTOCOL_DEFAULT_BROADCAST_ADDRESS		   	(0x00)

#define SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT					   (100)

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
#endif /* __SCREEN_DISPLAY_PROTOCOL_H__ */
