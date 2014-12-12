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
#include "ScreenDisplayProtocol.h"
//#include "ScreenDotMatrix.h"
#include "Timer.h"

//#include "ScreenDotMatrix.h"

char * messages [] = {"EUR",					  
					  "EURO",
					  "USD",
					  "DOLAR",
					  "COMPRA", 
					  "VENTA"};

int	message_types[]	= {	0, 
						1,
						0, 
						1,
						1,
						1
												};
												
typedef struct dotmatrixdatastruct{
int 	dotMatrixEffect;
char 	dotMatrixMessage[10];
} DOT_MATRIX_DATA_STRUCT, *DOT_MATRIX_DATA_STRUCT_PTR_;

TIMER_STRUCT myTimer;
DOT_MATRIX_DATA_STRUCT myDotMatrix;
//**********************************************************************
// API Fucntions
//**********************************************************************

void main(void)
{   
	int index = 0;
	
	//! SETUP
	bsp_setup();    	
	Timer_Setup();
	ScreenDisplayProtocol_Setup();
	
	//! AFTER SETUP	
	AddTimer(&myTimer, 1000);		
	
	//! LOOP
	while(TRUE){			
		
		
				
		if(Timer_GetOverflow(&myTimer) == TRUE){				
			
			myDotMatrix.dotMatrixEffect = message_types[index];
			memset(myDotMatrix.dotMatrixMessage, 0, 10);
			memcpy(myDotMatrix.dotMatrixMessage, messages[index], strlen(messages[index]));			
			
			ScreenDisplayProtocol_SendDataPacket(0x11, 3002, (char *) &myDotMatrix, sizeof(DOT_MATRIX_DATA_STRUCT));
			
			index = (index >= 5 ) ? 0 : index + 1;
			Timer_Reset(&myTimer);
		}
		
	}
}

