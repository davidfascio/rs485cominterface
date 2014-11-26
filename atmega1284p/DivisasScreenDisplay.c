/*
 * File: DivisasScreenDisplay.h
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
	bsp_pin_mode(BSP_PIN_A1, OUTPUT);
	ScreenDisplayProtocol_Setup();	
	
	//! AFTER SETUP
	ScreenDisplayDevice_Setup();

	//! LOOP
	while(TRUE){
		
		ScreenDisplayProtocol_WaitDataPacketCheck();
		ScreenDisplayProtocol_ProcessingDataPacketArrived();		
		bsp_io_toggle(BSP_PIN_A1);
	}
}
