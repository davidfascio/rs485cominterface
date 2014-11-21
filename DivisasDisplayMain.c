/*
 * File: DivisasDisplayMain.h
 * Author: fascio
 * 
 * Created on November 10th, 2014 12:00:00
 */ 
 
//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDisplayDevice.h"
#include "ScreenDisplayProtocol.h"

//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{
	//! SETUP
	bsp_setup();    
	ScreenDisplayProtocol_Setup();	
	
	//! AFTER SETUP
	ScreenDisplayDevice_Setup();

	//! LOOP
	while(TRUE){
		
		ScreenDisplayProtocol_WaitDataPacketCheck();
		ScreenDisplayProtocol_ProcessingDataPacketArrived();	
        SEND_DEMO();
		bsp_delay_ms(1000);	
	}
}
