/*
 * File: DivisasScreenDotMatrix.h
 * Author: fascio
 * 
 * Created on November 10th, 2014 12:00:00
 */ 
 
//**********************************************************************
// Includes
//**********************************************************************
#include "CommonSystemLibraries.h"
#include "ScreenDotMatrix.h"

TIMER_STRUCT myTimer;

//**********************************************************************
// API Fucntions
//**********************************************************************

char * messages [] = {"EUR",					  
					  "EURO",
					  "USD",
					  "DOLAR",
					  "COMPRA", 
					  "VENTA"};

SCREEN_DOT_MATRIX_EFFECT	message_types[]	= {	STATIC_TEXT, 
												DYNAMIC_LEFT,
												STATIC_TEXT, 
												DYNAMIC_LEFT,
												DYNAMIC_LEFT,
												DYNAMIC_LEFT
												};
int message_len = 6;

void main(void)
{   	
	char texto []=  "TEXTO";
	int index = 0; 
	//! SETUP
	bsp_setup();    	
	Timer_Setup();
	
	
	
	ScreenDotMatrix_Setup();
	
	//! AFTER SETUP	
	AddTimer(&myTimer, 10000);		
	
	ScreenDotMatrix_SendText(texto,  DYNAMIC_LEFT);	
	//! LOOP
	while(TRUE){			
		
		ScreenDotMatrix_Render();		
		
		if(Timer_GetOverflow(&myTimer) == TRUE){		
			
			ScreenDotMatrix_SendText(messages[index], message_types[index]);	
			index = (index < (message_len - 1)) ? index + 1 : 0;
			Timer_Reset(&myTimer);
		}
	}
}
