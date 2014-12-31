/*
 * File: ScreenMasterCommandList.h
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

//****************************************************************************************
//* COMMAND ID FOR SCREEN DISPLAY DEVICE
//****************************************************************************************
#define SCREEN_MASTER_DEVICE_CLIENT_COMMAND_ID_DISPLAY_FLOAT_VALUE_UPDATE	(SCREEN_MASTER_DEVICE_CLIENT_BASE | 2)
#define SCREEN_MASTER_DEVICE_SERVER_COMMAND_ID_DISPLAY_FLOAT_VALUE_UPDATE	(SCREEN_MASTER_DEVICE_SERVER_BASE | 2)

//****************************************************************************************
//* COMMAND ID FOR DOT MATRIX DEVICE
//****************************************************************************************
#define SCREEN_MASTER_DEVICE_CLIENT_COMMAND_ID_DOT_MATRIX_SEND_TEXT			(SCREEN_MASTER_DEVICE_CLIENT_BASE | 3)
#define SCREEN_MASTER_DEVICE_SERVER_COMMAND_ID_DOT_MATRIX_SEND_TEXT			(SCREEN_MASTER_DEVICE_SERVER_BASE | 3)

#define SCREEN_MASTER_DEVICE_CLIENT_COMMAND_ID_DOT_MATRIX_SEND_TEXT_DELAY	(SCREEN_MASTER_DEVICE_CLIENT_BASE | 4)
#define SCREEN_MASTER_DEVICE_SERVER_COMMAND_ID_DOT_MATRIX_SEND_TEXT_DELAY	(SCREEN_MASTER_DEVICE_SERVER_BASE | 4)

#endif /* __SCREEN_MASTER_COMMAND_LIST_H__ */
