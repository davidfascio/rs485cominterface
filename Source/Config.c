////////////////////////////////////////////////////////////////////////
//
// File name: Display7Seg.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "Config.h"

//**********************************************************************
// Variables
//********************************************************************** 

eeprom FIRMWARE_REALISE_STRUCT firmware_control;

eeprom DEVICE_CONFIG_STRUCT	device_config_control;

char default_key[CONFIG_KEY_SIZE] = {CONFIG_DEFAULT_KEY_1, CONFIG_DEFAULT_KEY_2, CONFIG_DEFAULT_KEY_3};

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void FirmwareRelease_Setup(	char device_type, char realise_high, char realise_low){
		
	firmware_control.device_type = device_type;
	firmware_control.realise_high = realise_high;
	firmware_control.realise_low = realise_low;
}

//********************************
// Device Configuration
//********************************
int DeviceConfig_SetConfiguration( char device_id, char device_size){
	
	int error_code;
	
	error_code = DeviceConfig_SetID(device_id);	
	
	if(error_code == DEVICE_CONFIG_NO_ERROR_CODE){		
		
		error_code = DeviceConfig_SetSize(device_size);	
		
		if(error_code == DEVICE_CONFIG_NO_ERROR_CODE){		
			
			DeviceConfig_WriteKey();
		}
	}
		
	return error_code;	
}

void DeviceConfig_GetKey(char * key){
    
    char index;

	for ( index = 0; index < CONFIG_KEY_SIZE; index++)
		key[index] = device_config_control.key[index];
}

char DeviceConfig_GetID(void){
	
	return device_config_control.device_id;	
}

int DeviceConfig_SetID(char device_id){

	// Validation
	if ( device_id < DEVICE_CONFIG_SET_ID_MINIMUM_VALUE || 
		 device_id > DEVICE_CONFIG_SET_ID_MAXIMUM_VALUE )
		 
		return DEVICE_CONFIG_SET_ID_ERROR_CODE;
	
	device_config_control.device_id = device_id;
	
	return DEVICE_CONFIG_NO_ERROR_CODE;
}

char DeviceConfig_GetSize(void){

	return device_config_control.device_size;
}

int DeviceConfig_SetSize(char device_size){

	// Validation
	if ( device_size < DEVICE_CONFIG_SET_SIZE_MINIMUM_VALUE )
		 
		return DEVICE_CONFIG_SET_SIZE_ERROR_CODE;
	
	device_config_control.device_size = device_size;
	
	return DEVICE_CONFIG_NO_ERROR_CODE;
}

boolean DeviceConfig_IsKeySet(void){
	
	char key[CONFIG_KEY_SIZE];	
	DeviceConfig_GetKey(key);
		
	if (memcmp(default_key, key,CONFIG_KEY_SIZE))
		return FALSE;	
		
	return TRUE;
}

void DeviceConfig_WriteKey(void){
	
	char index;

	for ( index = 0; index < CONFIG_KEY_SIZE; index++)
				device_config_control.key[index] = default_key[index];
}

void DeviceConfig_EraseKey(void){
	
	char index;

	for ( index = 0; index < CONFIG_KEY_SIZE; index++)
				device_config_control.key[index] = 0;
}
