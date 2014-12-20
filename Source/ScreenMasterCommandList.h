/*
 * File: ScreenDisplayDeviceCommandList.h
 * Author: fascio
 * 
 * Created on December 17th, 2014, 19:03
 */ 
 
#ifndef __SCREEN_MASTER_COMMAND_LIST_H__
#define __SCREEN_MASTER_COMMAND_LIST_H__

//****************************************************************************************
//* COMMAND ID LIST FOR SCREEN MASTER PROTOCOL DEVICE
//****************************************************************************************

#define SCREEN_MASTER_DEVICE_CLIENT_BASE									(7000)
#define SCREEN_MASTER_DEVICE_SERVER_BASE									(8000)
	
#define SCREEN_MASTER_DEVICE_SERVER_ERROR_CODE_COMMAND_ID					(SCREEN_MASTER_DEVICE_SERVER_BASE | 1)

#endif /* __SCREEN_MASTER_COMMAND_LIST_H__ */
