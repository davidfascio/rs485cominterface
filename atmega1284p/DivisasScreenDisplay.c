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
#include "ScreenDisplayDevice.h"
#include "ScreenDisplayProtocol.h"

//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{        	
	//! SETUP	
	System_Setup();
	ScreenDisplayProtocol_Setup(0x12);		
	
	//! AFTER SETUP
	ScreenDisplayDevice_Setup("0.0", strlen("0.0"));	
	
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
