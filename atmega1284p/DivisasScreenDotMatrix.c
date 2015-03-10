/*
 * File: DivisasScreenDotMatrix.h
 * Author: fascio
 * 
 * Created on November 10th, 2014 12:00:00
 */ 
 
//**********************************************************************
// Includes
//**********************************************************************
#include "System.h"
#include "ScreenDotMatrixDevice.h"
#include "Config.h"


//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{
	//! SYSTEM SETUP
	System_Setup();	
	
	//! SET CONFIGURATION
	FirmwareRelease_Setup(	BAZ_DOTMATRIX_DEVICE, 
							CONFIG_DEFAULT_FIRMWARE_RELEASE_HIGH, 
							CONFIG_DEFAULT_FIRMWARE_RELEASE_LOW );	
	
	//! LOAD CONFIGURATION
	ScreenDotMatrixDevice_Setup();		
		
	//! LOOP
	while(TRUE){
		
		//! System Loop Process
		System_Update();
		
		//! Device Render Process 		
		ScreenDotMatrixDevice_Update();						
	}
}

