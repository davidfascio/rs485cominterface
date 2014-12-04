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
#include "ScreenDotMatrix.h"

TIMER_STRUCT myTimer;

//**********************************************************************
// API Fucntions
//**********************************************************************

void main(void)
{   
	int index = 24;
	//! SETUP
	bsp_setup();    
	//bsp_usart_setup();
	Timer_Setup();
	/*bsp_pin_mode(BSP_PIN_A1, OUTPUT);
	bsp_pin_mode(BSP_PIN_A2, OUTPUT);	
	bsp_pin_mode(BSP_PIN_A3, OUTPUT);*/
		
	ScreenDotMatrix_Setup();
	
	//! AFTER SETUP	
	AddTimer(&myTimer, 200);		
	
	//! LOOP
	while(TRUE){			
		
		ScreenDotMatrix_Render();
				
		if(Timer_GetOverflow(&myTimer) == TRUE){				
			
			ScreenDotMatrix_Clear();		
			ScreenDotMatrix_DrawText("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",index,0,FONT_7x6, FONT_7x6_WIDTH, FONT_7x6_HEIGHT);
			
			index --;

			if(index < -8*36)
				index = 24;
			Timer_Reset(&myTimer);
		}
		
	}
}

