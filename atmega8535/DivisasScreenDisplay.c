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
/*#include "TPIC6B595.h"
#include "SN54LS145N.h"
#include "Timer.h"*/
#include "DotMatrix.h"

TIMER_STRUCT myTimer;
DOT_MATRIX_STRUCT dotMatrixControl;

#define DEMO_WIDTH 					(3)
#define DEMO_HEIGHT 				(7)

char DEMO_DOT_MATRIX_BUFFER[DEMO_WIDTH * DEMO_HEIGHT];
//**********************************************************************
// API Fucntions
//**********************************************************************

int n_pow(int number, int count) {
	int result = 1;
	
	while(count-- > 0)
		result *=number;  

	return result;
}
void main(void)
{   
	int index;
	//! SETUP
	bsp_setup();    
	bsp_usart_setup();
	Timer_Setup();
	bsp_pin_mode(BSP_PIN_A1, OUTPUT);
	bsp_pin_mode(BSP_PIN_A2, OUTPUT);	
	bsp_pin_mode(BSP_PIN_A3, OUTPUT);
	
	DotMatrix_Setup(&dotMatrixControl, 
					DEMO_DOT_MATRIX_BUFFER, 
					DEMO_WIDTH, 
					DEMO_HEIGHT);
	
	//! AFTER SETUP	
	//AddTimer(&myTimer, 1000);	
	for(index = 0; index < DEMO_HEIGHT; index++)
		memset(DEMO_DOT_MATRIX_BUFFER + (DEMO_WIDTH * index), n_pow(2,index), DEMO_WIDTH );
	//! LOOP
	while(TRUE){			
		
		DotMatrix_Update(&dotMatrixControl);
		
		/*if(Timer_GetOverflow(&myTimer) == TRUE){				
			
			bsp_io_toggle(BSP_PIN_A2);			
			Timer_Reset(&myTimer);
		}*/
	}
}
