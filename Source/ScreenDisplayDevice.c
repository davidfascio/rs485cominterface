////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplayDevice.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDisplayDevice.h"

//**********************************************************************
// Variables
//**********************************************************************
volatile SCREEN_DISPLAY_7_SEG ScreenDisplay7SegControl;
volatile int ScreenDisplay7SegBuffer[SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE];
volatile int ScreenDisplay7SegBufferLen = SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE;

//! DEFAULT PARAMMENTERS     	
volatile char ComAddress 			 = SCREEN_DISPLAY_PROTOCOL_DEFAULT_SLAVE_ADDRESS;	
volatile char * Display7Seg_Message  = SCREEN_DISPLAY_7_SEG_ERROR_MESSAGE;
//volatile int  Display7Seg_BufferSize = SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE;

//int ScreenDisplay7SegUpdateLed = LOW;
TIMER_STRUCT ScreenDisplay7SegTimer;
TIMER_STRUCT ScreenDisplay7SegUpdateValueTimeOut;

//**********************************************************************
// Setters and Getters Prototype Functions
//**********************************************************************
void ScreenDisplayDevice_SetDisplay7SegBufferLen(int bufferLen){
	
	if (bufferLen > SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE)
		return;
		
	ScreenDisplay7SegBufferLen = bufferLen;
}

int ScreenDisplayDevice_GetDisplay7SegBufferLen(void){
	
	return ScreenDisplay7SegBufferLen;
}

//**********************************************************************
// API Fucntions
//**********************************************************************
void ScreenDisplayDevice_Setup(void){
//void ScreenDisplayDevice_Setup(char * data, int dataLen, int display7segbuffersize){
	

	
	//! LOAD CONFIGURATION
	//******************************************************************
	//*
	//* It needs to use setup function:
	//*
	//*		void DeviceConfig_Setup( char device_id, char device_size)
	//*
	//******************************************************************
	if(DeviceConfig_IsKeySet()){
		
		ComAddress = DeviceConfig_GetID();					// Slave Address
		ScreenDisplay7SegBufferLen = DeviceConfig_GetSize();	// Buffer Size
	}
							
	//! AFTER SETUP
	ScreenDisplayProtocol_Setup(ComAddress);		    
    
	ScreenDisplayDevice7Seg_Setup();
	
	/* Install Commands*/	
	ScreenDisplayCommands_AddCommad(ScreenDisplayDevice_UpdateStringValue);
	ScreenDisplayCommands_AddCommad(ScreenDisplayDevice_GetStringValue);
	ScreenDisplayCommands_AddCommad(ScreenDisplayDevice_LEDStatus);
	
	/* Install Configuration Commands*/	
	ScreenDisplayCommands_AddCommad(ScreenDisplayDevice_SetDeviceConfiguration);	
	ScreenDisplayCommands_AddCommad(ScreenDisplayDevice_GetDeviceConfiguration);
	
	// Timers
	AddTimer(&ScreenDisplay7SegTimer,SCREEN_DISPLAY_DEVICE_DEFAULT_TIMER_REFRESH_MS_VALUE);	
	AddTimer(&ScreenDisplay7SegUpdateValueTimeOut,SCREEN_DISPLAY_DEVICE_DEFAULT_UPDATE_VALUE_TIMEOUT_MS);
	
}

void ScreenDisplayDevice7Seg_Setup(void) {
	
	ScreenDispla7Seg_Setup(&ScreenDisplay7SegControl, Display7Seg_Message, strlen(Display7Seg_Message),  
							ScreenDisplay7SegBuffer, ScreenDisplay7SegBufferLen);
}

void ScreenDisplayDevice_Clear(void){
	
	ScreenDispla7Seg_Clear(&ScreenDisplay7SegControl);
}
void ScreenDisplayDevice_Update(void){
	
	//! Communication Protocol Process 		
	//ScreenDisplayProtocol_WaitDataPacketCheck();
	ScreenDisplayProtocol_StateMachineUpdate();
	ScreenDisplayProtocol_ProcessingDataPacketArrived();	
	
	if(Timer_GetOverflow(&ScreenDisplay7SegTimer) == TRUE) {
		
		//ScreenDisplay7SegUpdateLed = (ScreenDisplay7SegUpdateLed == LOW )? HIGH : LOW;
		//bsp_io_write(SCREEN_DISPLAY_DEVICE_LED_UPDATE_INDICATOR, ScreenDisplay7SegUpdateLed);
		ScreenDispla7Seg_Update(&ScreenDisplay7SegControl);
		Timer_Reset(&ScreenDisplay7SegTimer);
	}
	
	if(Timer_GetOverflow(&ScreenDisplay7SegUpdateValueTimeOut) == TRUE) {	
			
	
		ScreenDisplayDevice_Error();
		Timer_Reset(&ScreenDisplay7SegUpdateValueTimeOut);
	}
}
/*int ScreenDisplayDevice_Update(float data){
	return ScreenDispla7Seg_UpdateData(&ScreenDisplay7SegControl, data);
}*/

void ScreenDisplayDevice_Error(void){		
	
	ScreenDisplayDevice_UpdateStringData(Display7Seg_Message, strlen(Display7Seg_Message));
	ScreenDispla7Seg_SetErrorData(&ScreenDisplay7SegControl, TRUE);	
}

int ScreenDisplayDevice_UpdateStringData(char * data, int dataLen){
	return ScreenDispla7Seg_UpdateStringData(&ScreenDisplay7SegControl, data, dataLen);
}

char * ScreenDisplayDevice_GetStringData(void){

	return ScreenDispla7Seg_GetStringData(&ScreenDisplay7SegControl);
}

int ScreenDisplayDevice_GetStringDataLen(void){
	
	return ScreenDispla7Seg_GetStringDataLen(&ScreenDisplay7SegControl);
}

// DEMO
int LEDStatus(int status){
		
	bsp_pin_mode(BSP_PIN_A2, OUTPUT);	
	
	if( status == LOW || status == HIGH ){
		bsp_io_write(BSP_PIN_A2, status);  		 	
	}
		
	return status;
}


//**********************************************************************
// Command List Fucntions
//
// Acoording to this pattern:
//
// COMMAND_RESPONSE_STRUCT (* SCREEN_DISPLAY_COMMANDS_FUNCTION )(int commandId, char * data, int dataSize)
//
// More Information see ScreenDisplayCommands.h library
//**********************************************************************

COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_LEDStatus(int commandId, char * data, int dataSize){
    
    //! Upper Cast Implementation for ScreenDisplayDevice_LEDStatus Command	
	//!
	//! Notice:
	//! 	- *data is integer type
	//! 	- dataSize is sizeof(int)
	//!
	//! memcpy((char *) &command_parameter , data, sizeof(command_parameter));
	
	int command_parameter = 0;
	
	COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);              	
	
	if((commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_LED_STATUS) && 
		dataSize == sizeof(command_parameter)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_LED_STATUS);
		
		memcpy((char *) &command_parameter , data, sizeof(command_parameter));
		
		commandErrorCodeResponse = LEDStatus(command_parameter);
		
		ScreenDisplayCommands_SetCommandBufferResponse(&CommandResponseControl,(char *) &commandErrorCodeResponse,sizeof(commandErrorCodeResponse));				
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}
/*
COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_UpdateValue(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- *data is float type
	//! 	- dataSize is sizeof(float)
	//!
	//! memcpy((char *) &command_parameter , data, sizeof(command_parameter));
	
	float command_parameter = 0;
    
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_FLOAT_VALUE_UPDATE) && 
		dataSize == sizeof(command_parameter)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_FLOAT_VALUE_UPDATE);
		
		memcpy((char *) &command_parameter , data, sizeof(command_parameter));
		
		commandErrorCodeResponse = ScreenDisplayDevice_Update(command_parameter);
		
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}*/

COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_UpdateStringValue(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- *data is char * type
	//! 	- dataSize is strlen(char *)
	//!
	//! 
	
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_FLOAT_VALUE_UPDATE)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_FLOAT_VALUE_UPDATE);
		
		//memcpy((char *) &command_parameter , data, sizeof(command_parameter));
		
		commandErrorCodeResponse = ScreenDisplayDevice_UpdateStringData(data, dataSize);
		
		if(commandErrorCodeResponse == SCREEN_DISPLAY_7_SEG_NO_ERROR_CODE)
			Timer_Reset(&ScreenDisplay7SegUpdateValueTimeOut);
		
		ScreenDisplayCommands_SetCommandBufferResponse(&CommandResponseControl,(char *) &commandErrorCodeResponse,sizeof(commandErrorCodeResponse));				
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	return	CommandResponseControl;		
}

COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_GetStringValue(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- *data is char * type
	//! 	- dataSize is strlen(char *)
	//!
	//! 
	
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	
	int commandErrorCodeResponse;
	char * commandBufferResponse;
	int commandBufferResponseLen;
	
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_GET_VALUE)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_GET_VALUE);
		
		commandBufferResponse = ScreenDisplayDevice_GetStringData();
		commandBufferResponseLen = ScreenDisplayDevice_GetStringDataLen();
		
		ScreenDisplayCommands_SetCommandBufferResponse(&CommandResponseControl,commandBufferResponse,commandBufferResponseLen);				
		
		if(commandBufferResponseLen == 0)
			ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, SCREEN_DISPLAY_DEVICE_EMPTY_BUFFER);
	}
	return	CommandResponseControl;		
}



////////////////////////// CONFIGURATION COMMANDS //////////////////////
		
COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_SetDeviceConfiguration(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- *data is char * type
	//! 	- dataSize is strlen(char *)
	//!
	//! 
	char command_parameter0;
	char command_parameter1;
	char * dataptr = data;
	
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == DEVICE_CONFIG_SET_CONFIG_MASTER_COMMAND_ID) &&
		dataSize == (2 * SIZE_OF_CHAR)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, DEVICE_CONFIG_SET_CONFIG_SLAVE_COMMAND_ID);
		
		memcpy((char *) &command_parameter0 , dataptr, SIZE_OF_CHAR);
		dataptr = dataptr + SIZE_OF_CHAR;
		
		memcpy((char *) &command_parameter1 , dataptr, SIZE_OF_CHAR);
		
		
		commandErrorCodeResponse = DeviceConfig_SetConfiguration(command_parameter0,command_parameter1);
		
		if (commandErrorCodeResponse == DEVICE_CONFIG_NO_ERROR_CODE)
		{
			ScreenDisplayDevice_Clear();
			ComAddress = command_parameter0;
			ScreenDisplay7SegBufferLen = command_parameter1;
			
			// Update Information
			ScreenDisplayProtocol_SetComAddress(ComAddress);			
			ScreenDisplayDevice7Seg_Setup(); 
		}
		
		ScreenDisplayCommands_SetCommandBufferResponse(&CommandResponseControl,(char *) &commandErrorCodeResponse,sizeof(commandErrorCodeResponse));				
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	
	return	CommandResponseControl;		
}

		
COMMAND_RESPONSE_STRUCT ScreenDisplayDevice_GetDeviceConfiguration(int commandId, char * data, int dataSize){
	
	//! Upper Cast Implementation for ScreenDisplayDevice_UpdateValue Command	
	//!
	//! Notice:
	//! 	- *data is char * type
	//! 	- dataSize is strlen(char *)
	//!
	//! 
	char command_parameter0;
	char command_parameter1;
	char command_response[10];
	
	char * dataptr = data;
	
    COMMAND_RESPONSE_STRUCT CommandResponseControl;	
	int commandErrorCodeResponse;
	ScreenDisplayCommands_CommandResponseSetup(&CommandResponseControl);	
	
	if((commandId == DEVICE_CONFIG_GET_CONFIG_MASTER_COMMAND_ID) &&
		dataSize == ( SIZE_OF_CHAR)) {
		
		ScreenDisplayCommands_SetCommandIdResponse(&CommandResponseControl, DEVICE_CONFIG_GET_CONFIG_SLAVE_COMMAND_ID);
		
		
		commandErrorCodeResponse = DeviceConfig_GetConfiguration(&command_parameter0,&command_parameter1);
		
		memset(command_response, 0 ,sizeof(command_response));
		memcpy(command_response, &command_parameter0, SIZE_OF_CHAR);
		memcpy(command_response + SIZE_OF_CHAR, &command_parameter1, SIZE_OF_CHAR);
		
		ScreenDisplayCommands_SetCommandBufferResponse(&CommandResponseControl,(char *) command_response,2* SIZE_OF_CHAR);				
		ScreenDisplayCommands_SetCommandErrorCodeResponse(&CommandResponseControl, commandErrorCodeResponse);
	}
	
	return	CommandResponseControl;		
}

////////////////////////// CONFIGURATION COMMANDS //////////////////////
