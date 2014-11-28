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
#include "Timer100ms.h"

TIMER_STRUCT myTimer;
//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{      	
	//! SETUP
	bsp_setup();    
	Timer_Setup();
	bsp_pin_mode(BSP_PIN_A1, OUTPUT);
	ScreenDisplayProtocol_Setup();	
	
	//! AFTER SETUP
	ScreenDisplayDevice_Setup();
	AddTimer(&myTimer, 1000);
	//! LOOP
	while(TRUE){
		
		//ScreenDisplayProtocol_WaitDataPacketCheck();
		//ScreenDisplayProtocol_ProcessingDataPacketArrived();		
		
		if(Timer_GetOverflow(&myTimer) == TRUE){
			bsp_io_toggle(BSP_PIN_A1);
			Timer_Reset(&myTimer);
		}
	}
}
