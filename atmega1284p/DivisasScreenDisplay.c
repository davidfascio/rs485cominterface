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
#include "Timer.h"

TIMER_STRUCT myTimer;
//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{
    int estado = LOW;      	
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
		
		ScreenDisplayProtocol_WaitDataPacketCheck();
		ScreenDisplayProtocol_ProcessingDataPacketArrived();		
		
		if(Timer_GetOverflow(&myTimer) == TRUE){
			estado = (estado == LOW )? HIGH : LOW;
			bsp_io_write(BSP_PIN_A1, estado);
			Timer_Reset(&myTimer);
		}
	}
}
