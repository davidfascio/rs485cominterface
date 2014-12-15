/*
 * File: DivisasScreenDotMatrix.h
 * Author: fascio
 * 
 * Created on November 10th, 2014 12:00:00
 */ 
 
//**********************************************************************
// Includes
//**********************************************************************

#include "ScreenDotMatrixDevice.h"
#include "ScreenDisplayProtocol.h"
#include "Timer.h"

//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{
	 int estado = LOW;    	
	//! SETUP
	bsp_setup();    
	Timer_Setup();	
	ScreenDisplayProtocol_Setup(0x11);	
	
	//! AFTER SETUP	
	ScreenDotMatrixDevice_Setup();	
	
	// Demo
	ScreenDotMatrix_SendText("GRUPO ELEKTRA",  DYNAMIC_LEFT);	
	
	//! LOOP
	while(TRUE){
	
		//!*************************************************************
		//! Render Process 
		//!*************************************************************
		ScreenDotMatrixDevice_Update();				
		
		//!*************************************************************
		//! Communication Protocol Process 
		//!*************************************************************
		//ScreenDisplayProtocol_WaitDataPacketCheck();
		ScreenDisplayProtocol_StateMachineUpdate();		
		ScreenDisplayProtocol_ProcessingDataPacketArrived();			
	}
}

