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
#include "ScreenDisplayProtocol.h"


//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{
	//! SETUP
	System_Setup();	
	ScreenDisplayProtocol_Setup(0x11);	
	
	//! AFTER SETUP	
	ScreenDotMatrixDevice_Setup();	
	
	// Demo
	ScreenDotMatrix_SendText("LA JOYA", strlen("LA JOYA"),  DYNAMIC_LEFT);	
	
	//! LOOP
	while(TRUE){
		
		//! System Loop Process
		System_Update();
		
		//! Render Process 		
		ScreenDotMatrixDevice_Update();				
		
		//! Communication Protocol Process 		
		//ScreenDisplayProtocol_WaitDataPacketCheck();
		ScreenDisplayProtocol_StateMachineUpdate();		
		ScreenDisplayProtocol_ProcessingDataPacketArrived();			
	}
}

