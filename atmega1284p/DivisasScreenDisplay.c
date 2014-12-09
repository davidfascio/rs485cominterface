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

#ifdef __DIVISAS_SCREEN_DISPLAY_DEBUG__
TIMER_STRUCT myTimer;
#endif /* __DIVISAS_SCREEN_DISPLAY_DEBUG__ */

//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{
    int estado = LOW;      	
	//! SETUP
	bsp_setup();    
	Timer_Setup();	
	ScreenDisplayProtocol_Setup();		
	
	//! AFTER SETUP
	ScreenDisplayDevice_Setup();
	
	
	#ifdef __DIVISAS_SCREEN_DISPLAY_DEBUG__
	bsp_pin_mode(BSP_PIN_A1, OUTPUT);
	AddTimer(&myTimer, 1000);
	#endif /* __DIVISAS_SCREEN_DISPLAY_DEBUG__ */
	
	
	
	//! LOOP
	while(TRUE){
		
		//!*************************************************************
		//! Communication Protocol Process 
		//!*************************************************************
		//ScreenDisplayProtocol_WaitDataPacketCheck();
		ScreenDisplayProtocol_StateMachineUpdate();
		ScreenDisplayProtocol_ProcessingDataPacketArrived();		
		
		#ifdef __DIVISAS_SCREEN_DISPLAY_DEBUG__
		
		if(Timer_GetOverflow(&myTimer) == TRUE){
			estado = (estado == LOW )? HIGH : LOW;
			bsp_io_write(BSP_PIN_A1, estado);
			Timer_Reset(&myTimer);
		}
		
		#endif /* __DIVISAS_SCREEN_DISPLAY_DEBUG__ */
	}
}
