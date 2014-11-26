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
#define SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT					   (5000)

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void ScreenDisplayProtocol_Setup(void);
void ScreenDisplayProtocol_WaitDataPacketCheck(void);
void ScreenDisplayProtocol_ProcessingDataPacketArrived(void);

#endif /* __SCREEN_DISPLAY_PROTOCOL_H__ */
