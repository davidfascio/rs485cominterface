/*
 * File: DivisasScreenDisplay.h
 * Author: fascio
 * 
 * Created on November 10th, 2014 12:00:00
 */ 
 
//**********************************************************************
// Includes
//**********************************************************************
#include "System.h"
#include "Config.h"
#include "ScreenDisplayDevice.h"
#include "ScreenDisplayProtocol.h"

//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{   
	//! DEFAULT PARAMMENTERS     	
	volatile char ComAddress 			 = SCREEN_DISPLAY_PROTOCOL_DEFAULT_SLAVE_ADDRESS;	
	volatile char * Display7Seg_Message  = SCREEN_DISPLAY_7_SEG_ERROR_MESSAGE;
	volatile int  Display7Seg_BufferSize = SCREEN_DISPLAY_DEVICE_MAX_BUFFER_SIZE;
	
	//! SYSTEM SETUP	
	System_Setup();	
	
	//! SET CONFIGURATION
	FirmwareRelease_Setup(	BAZ_NUMDISPLAY_DEVICE, 
							CONFIG_DEFAULT_FIRMWARE_RELEASE_HIGH, 
							CONFIG_DEFAULT_FIRMWARE_RELEASE_LOW );
	
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
		Display7Seg_BufferSize = DeviceConfig_GetSize();	// Buffer Size
	}
							
	//! AFTER SETUP
	ScreenDisplayProtocol_Setup(ComAddress);	
	ScreenDisplayDevice_Setup(Display7Seg_Message, strlen(Display7Seg_Message), Display7Seg_BufferSize);		
	
	
	//! LOOP
	while(TRUE){
		
		//! System Loop Process
		System_Update();
		
		//! Device Render Process 
		ScreenDisplayDevice_Update();	
		
		//! Communication Protocol Process 		
		//ScreenDisplayProtocol_WaitDataPacketCheck();
		ScreenDisplayProtocol_StateMachineUpdate();
		ScreenDisplayProtocol_ProcessingDataPacketArrived();	
	}
}
