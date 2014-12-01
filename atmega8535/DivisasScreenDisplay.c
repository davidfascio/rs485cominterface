/*
 * File: DivisasScreenDisplay.h
 * Author: fascio
 * 
 * Created on November 10th, 2014 12:00:00
 */ 
 
//**********************************************************************
// Includes
//**********************************************************************
//#include "ScreenDisplayDevice.h"
//#include "ScreenDisplayProtocol.h"
#include "CommonSystemLibraries.h"
#include "TPIC6B595.h"
#include "SN54LS145N.h"
#include "Timer.h"

TIMER_STRUCT myTimer;
//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{   char row = 0;   	
	//! SETUP
	bsp_setup();    
	Timer_Setup();
	bsp_pin_mode(BSP_PIN_A1, OUTPUT);
	
	TPIC6B595_Setup();
	SN54LS145N_Setup();
	
	//! AFTER SETUP	
	AddTimer(&myTimer, 1000);
	
	//! LOOP
	while(TRUE){	
		
		TPIC6B595_HideData();
		TPIC6B595_SendData(0xFF);
		TPIC6B595_ShowData();
		
		SN54LS145N_SendData(row++);
		if(row >= 7)
			row = 0;
		
		if(Timer_GetOverflow(&myTimer) == TRUE){
			
			bsp_io_toggle(BSP_PIN_A1);			
			Timer_Reset(&myTimer);
		}
	}
}
