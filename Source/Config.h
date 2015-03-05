/*
 * File: Config.h
 * Author: fascio
 * 
 * Created on March 3rd, 2015, 16:38
 */ 

#ifndef __CONFIG_H__
#define __CONFIG_H__

//**********************************************************************
// Includes
//********************************************************************** 
#include "CommonSystemLibraries.h"

//**********************************************************************
// Defines
//********************************************************************** 

//////////////////////////////////////////////////////////////////////////////
// FIRMWARE RELEASE
//
// [DEVICE TYPE | HIGH RELEASE  | LOW RELEASE]

#define CONFIG_FIRMWARE_RELEASE_SIZE									(3)
	
#define BAZ_NUMDISPLAY_DEVICE											(0x01)
#define BAZ_DOTMATRIX_DEVICE											(0x02)
#define BAZ_FOREXCTRL_DEVICE											(0x03)

// NO DEFINED
#define CONFIG_DEFAULT_FIRMWARE_DEVICE_TYPE								(0x00)	

#define CONFIG_DEFAULT_FIRMWARE_RELEASE_HIGH							(0x01)
#define CONFIG_DEFAULT_FIRMWARE_RELEASE_LOW								(0x03)

//////////////////////////////////////////////////////////////////////////////

// KEY DEFINES
#define CONFIG_KEY_SIZE													(3)
#define CONFIG_DEFAULT_KEY_1											(0XFA)
#define CONFIG_DEFAULT_KEY_2											(0x5C)
#define CONFIG_DEFAULT_KEY_3											(0X10)

// EEPROM
#define CONFIG_DEFAULT_BACKUP_INFORMATION_SIZE							(1024) // bytes

// NETWORK 
#define CONFIG_DEFAULT_NETWORK_OCT_SIZE									(4) // bytes


////****************************************************************************************
////* GENERIC PARAMMETERS COMMAND ID LIST 
////****************************************************************************************
//#define DEVICE_CONFIG_MASTER_BASE										(5000)
//#define DEVICE_CONFIG_SLAVE_BASE										(6000)

//#define DEVICE_CONFIG_RESET_MASTER_COMMAND_ID							(DEVICE_CONFIG_MASTER_BASE 	+ 1)
//#define DEVICE_CONFIG_RESET_SLAVE_COMMAND_ID							(DEVICE_CONFIG_SLAVE_BASE 	+ 1)

//#define DEVICE_CONFIG_SET_ADDRESS_MASTER_COMMAND_ID						(DEVICE_CONFIG_MASTER_BASE 	+ 2)
//#define DEVICE_CONFIG_SET_ADDRESS_SLAVE_COMMAND_ID						(DEVICE_CONFIG_SLAVE_BASE 	+ 2)

//#define DEVICE_CONFIG_GET_ADDRESS_MASTER_COMMAND_ID						(DEVICE_CONFIG_MASTER_BASE 	+ 3)
//#define DEVICE_CONFIG_GET_ADDRESS_SLAVE_COMMAND_ID						(DEVICE_CONFIG_SLAVE_BASE 	+ 3)

//#define DEVICE_CONFIG_SET_SIZE_MASTER_COMMAND_ID						(DEVICE_CONFIG_MASTER_BASE 	+ 4)
//#define DEVICE_CONFIG_SET_SIZE_SLAVE_COMMAND_ID							(DEVICE_CONFIG_SLAVE_BASE 	+ 4)


// ERROR CODES
#define DEVICE_CONFIG_SET_ID_MINIMUM_VALUE								(1)
#define DEVICE_CONFIG_SET_ID_MAXIMUM_VALUE								(247)

#define DEVICE_CONFIG_SET_SIZE_MINIMUM_VALUE							(1)

#define DEVICE_CONFIG_NO_ERROR_CODE										(0)
#define DEVICE_CONFIG_SET_ID_ERROR_CODE									(-1)
#define DEVICE_CONFIG_SET_SIZE_ERROR_CODE								(-2)


//**********************************************************************
// Structs
//**********************************************************************

typedef struct firmwarereleasestruct{
	
	char device_type;
	char realise_high;
	char realise_low;
	
} FIRMWARE_REALISE_STRUCT, *FIRMWARE_REALISE_STRUCT_PTR_;

typedef struct deviceconfigstruct{	
	
	char key[CONFIG_KEY_SIZE];	
	char device_id;
	char device_size;		
	
} DEVICE_CONFIG_STRUCT, * DEVICE_CONFIG_STRUCT_PTR_;

typedef struct backupconfigstruct{	
	
	char 	backup_information[CONFIG_DEFAULT_BACKUP_INFORMATION_SIZE];
	int 	backup_information_size;
	int 	backup_time;
	boolean backup_alert;	
	
} BACKUP_CONFIGURATION_STRUCT, * BACKUP_CONFIGURATION_STRUCT_PTR_;

typedef struct networkconfigstruct{
	
	char network_ip_address[CONFIG_DEFAULT_NETWORK_OCT_SIZE];
	char network_subnet_address[CONFIG_DEFAULT_NETWORK_OCT_SIZE];
	char network_gateway_address[CONFIG_DEFAULT_NETWORK_OCT_SIZE];
	char network_dns_address[CONFIG_DEFAULT_NETWORK_OCT_SIZE];
	
} NETWORK_CONFIGURATION_STRUCT, * NETWORK_CONFIGURATION_STRUCT_PTR_;

//**********************************************************************
// Prototype functions
//**********************************************************************

void FirmwareRelease_Setup(	char device_type, char realise_high, char realise_low);

int DeviceConfig_SetConfiguration( char device_id, char device_size);
void DeviceConfig_GetKey(char * key);
char DeviceConfig_GetID(void);
int DeviceConfig_SetID(char device_id);
char DeviceConfig_GetSize(void);
int DeviceConfig_SetSize(char device_size);
boolean DeviceConfig_IsKeySet(void);
void DeviceConfig_EraseKey(void);
void DeviceConfig_WriteKey(void);

#endif /* __CONFIG_H__ */
