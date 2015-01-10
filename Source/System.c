////////////////////////////////////////////////////////////////////////
//
// File name: System.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "System.h"

//**********************************************************************
// API Variables
//**********************************************************************
int system_status;
TIMER_STRUCT SystemTimer;

//**********************************************************************
// API Fucntions
//**********************************************************************
void System_Setup(void){
	
	// Setup Low Level Layers
	bsp_setup();    
	Timer_Setup();
	
	// Led Indicator XD
    system_status = LOW;
	bsp_pin_mode(SYSTEM_LED_INDICATOR_STATUS, OUTPUT);
	bsp_io_write(SYSTEM_LED_INDICATOR_STATUS, system_status);
	AddTimer(&SystemTimer, SYSTEM_LED_INDICATOR_STATUS_DELAY_IN_MS);	    
}

void System_Update(void){
	
	if(Timer_GetOverflow(&SystemTimer) == TRUE){
		
		system_status = (system_status == LOW )? HIGH : LOW;
		bsp_io_write(SYSTEM_LED_INDICATOR_STATUS, system_status);	
		Timer_Reset(&SystemTimer);
	}	
}
