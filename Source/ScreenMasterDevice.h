/*
 * File: ScreenMasterDevice.h
 * Author: fascio
 * 
 * Created on December 11th, 2014, 15:58
 */ 


#ifndef __SCREEN_MASTER_DEVICE_H__
#define __SCREEN_MASTER_DEVICE_H__

//**********************************************************************
// Includes
//**********************************************************************

#include "ScreenDisplayProtocol.h"
#include "TcpComProtocolCommons.h"
#include "ScreenMasterCommands.h"
#include "ScreenMasterCommandList.h"
#include "ScreenMaster.h"


//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void ScreenMasterDevice_Setup(char ComAddress);
void ScreenMasterDevice_Update(void);

//**********************************************************************
// Command List Fucntions
//
// Acoording to this pattern:
//
// void  (* SCREEN_MASTER_COMMANDS_FUNCTION )(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, char slaveAddress, int commandId, char * data);
//
// More Information see ScreenDisplayCommands.h library
//**********************************************************************

void ScreenMasterDotMatrixDevice_LEDStatusFunction(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
													char slaveAddress, int commandId, char * data);
													
void ScreenMasterDotMatrixDevice_SendTextFunction(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
												  char slaveAddress, int commandId, char * data);
													
void ScreenMasterDotMatrixDevice_SendTextWithCustomDelayFunction(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
																char slaveAddress, int commandId, char * data);

void ScreenMasterDisplayDevice_LEDStatus(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
										char slaveAddress, int commandId, char * data);

void ScreenMasterDisplayDevice_UpdateValue(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
											char slaveAddress, int commandId, char * data);
											
void ScreenMasterDotMatrixDevice_GetTextWithCustomDelayFunction(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
																char slaveAddress, int commandId, char * data);
																
void ScreenMasterDisplayDevice_GetValue(MASTER_COMMAND_RESPONSE_STRUCT_PTR_ MasterCommandResponseControl, 
											char slaveAddress, int commandId, char * data);																

#endif /* __SCREEN_MASTER_DEVICE_H__ */
