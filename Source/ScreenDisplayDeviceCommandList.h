/*
 * File: ScreenDisplayDeviceCommandList.h
 * Author: fascio
 * 
 * Created on November 21th, 2014, 15:07
 */ 
 
#ifndef __SCREEN_DISPLAY_DEVICE_COMMAND_LIST_H__
#define __SCREEN_DISPLAY_DEVICE_COMMAND_LIST_H__

//****************************************************************************************
//* COMMAND ID LIST FOR SCREEN DISPLAY DEVICE 
//****************************************************************************************
#define SCREEN_DISPLAY_DEVICE_MASTER_BASE											(1000)
#define SCREEN_DISPLAY_DEVICE_SLAVE_BASE											(2000)

#define SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_LED_STATUS			 				(SCREEN_DISPLAY_DEVICE_MASTER_BASE 	+ 1)
#define SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_LED_STATUS			 				(SCREEN_DISPLAY_DEVICE_SLAVE_BASE 	+ 1)

#define SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_FLOAT_VALUE_UPDATE					(SCREEN_DISPLAY_DEVICE_MASTER_BASE 	+ 2)
#define SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_FLOAT_VALUE_UPDATE					(SCREEN_DISPLAY_DEVICE_SLAVE_BASE 	+ 2)

#define SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_GET_VALUE							(SCREEN_DISPLAY_DEVICE_MASTER_BASE 	+ 3)
#define SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_GET_VALUE							(SCREEN_DISPLAY_DEVICE_SLAVE_BASE 	+ 3)


//****************************************************************************************
//* COMMAND ID LIST FOR SCREEN DOT MATRIX DEVICE
//****************************************************************************************
#define SCREEN_DOT_MATRIX_DEVICE_MASTER_BASE										(3000)
#define SCREEN_DOT_MATRIX_DEVICE_SLAVE_BASE											(4000)

#define SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_LED_STATUS			 			(SCREEN_DOT_MATRIX_DEVICE_MASTER_BASE 	+ 1)
#define SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_LED_STATUS			 			(SCREEN_DOT_MATRIX_DEVICE_SLAVE_BASE 	+ 1)

#define SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_SEND_TEXT						(SCREEN_DOT_MATRIX_DEVICE_MASTER_BASE 	+ 2)
#define SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_SEND_TEXT							(SCREEN_DOT_MATRIX_DEVICE_SLAVE_BASE 	+ 2)

#define SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_SEND_TEXT_DELAY					(SCREEN_DOT_MATRIX_DEVICE_MASTER_BASE 	+ 3)
#define SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_SEND_TEXT_DELAY					(SCREEN_DOT_MATRIX_DEVICE_SLAVE_BASE 	+ 3)

#define SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_GET_TEXT_DELAY					(SCREEN_DOT_MATRIX_DEVICE_MASTER_BASE 	+ 4)
#define SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_GET_TEXT_DELAY					(SCREEN_DOT_MATRIX_DEVICE_SLAVE_BASE 	+ 4)

//****************************************************************************************
//* GENERIC PARAMMETERS COMMAND ID LIST 
//****************************************************************************************
#define DEVICE_CONFIG_MASTER_BASE													(5000)
#define DEVICE_CONFIG_SLAVE_BASE													(6000)

#define DEVICE_CONFIG_RESET_MASTER_COMMAND_ID										(DEVICE_CONFIG_MASTER_BASE 	+ 1)
#define DEVICE_CONFIG_RESET_SLAVE_COMMAND_ID										(DEVICE_CONFIG_SLAVE_BASE 	+ 1)

#define DEVICE_CONFIG_SET_ADDRESS_MASTER_COMMAND_ID									(DEVICE_CONFIG_MASTER_BASE 	+ 2)
#define DEVICE_CONFIG_SET_ADDRESS_SLAVE_COMMAND_ID									(DEVICE_CONFIG_SLAVE_BASE 	+ 2)

#define DEVICE_CONFIG_GET_ADDRESS_MASTER_COMMAND_ID									(DEVICE_CONFIG_MASTER_BASE 	+ 3)
#define DEVICE_CONFIG_GET_ADDRESS_SLAVE_COMMAND_ID									(DEVICE_CONFIG_SLAVE_BASE 	+ 3)

#define DEVICE_CONFIG_SET_SIZE_MASTER_COMMAND_ID									(DEVICE_CONFIG_MASTER_BASE 	+ 4)
#define DEVICE_CONFIG_SET_SIZE_SLAVE_COMMAND_ID										(DEVICE_CONFIG_SLAVE_BASE 	+ 4)

#define DEVICE_CONFIG_GET_SIZE_MASTER_COMMAND_ID									(DEVICE_CONFIG_MASTER_BASE 	+ 5)
#define DEVICE_CONFIG_GET_SIZE_SLAVE_COMMAND_ID										(DEVICE_CONFIG_SLAVE_BASE 	+ 5)

#endif /* __SCREEN_DISPLAY_DEVICE_COMMAND_LIST_H__ */
