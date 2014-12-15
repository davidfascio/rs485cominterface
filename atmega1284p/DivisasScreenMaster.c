/*
 * File: DivisasScreenMaster.h
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

float values [] = {	13.00,
					0.001,
					123.0,
					45.67,
					1.001,
					98.76};
					
int	message_types[]	= {	0, 
						1,
						0, 
						1,
						1,
						1
				                                };
                                                
typedef struct dotmatrixdatastruct{
int     dotMatrixEffect;
char     dotMatrixMessage[10];
} DOT_MATRIX_DATA_STRUCT, *DOT_MATRIX_DATA_STRUCT_PTR_;

TIMER_STRUCT myTimer;
DOT_MATRIX_DATA_STRUCT myDotMatrix;
float datafloat;
//**********************************************************************
// API Fucntions
//**********************************************************************

void main(void)
{   
    int index = 0;
    int status_pin = LOW;
    
    //! SETUP
    bsp_setup();        
    Timer_Setup();
    ScreenDisplayProtocol_Setup(0x01);
    
    
    //! AFTER SETUP    
    AddTimer(&myTimer, 5000);        
    
    bsp_pin_mode(BSP_PIN_A0, OUTPUT);
        
    bsp_io_write(BSP_PIN_A0, status_pin);
    
    //! LOOP
    while(TRUE){            
        
        
        
        //ScreenDisplayProtocol_StateMachineUpdate();
        //ScreenDisplayProtocol_ProcessingDataPacketArrived();
                
        if(Timer_GetOverflow(&myTimer) == TRUE){                
            
            status_pin = (status_pin == LOW) ? HIGH : LOW;
			bsp_io_write(BSP_PIN_A0, status_pin);
			
            myDotMatrix.dotMatrixEffect = message_types[index];
            memset(myDotMatrix.dotMatrixMessage, 0, 10);
            memcpy(myDotMatrix.dotMatrixMessage, messages[index], strlen(messages[index]));     
            
            datafloat = values[index];
            
            /*ScreenDisplayProtocol_SendDataPacket(0x11, 3002, (char *) &myDotMatrix, sizeof(DOT_MATRIX_DATA_STRUCT));*/
            
            
            
			
			
			
			/* dot Matrix -- Tipo de cambio */
            ScreenDisplayProtocol_SendDataPackWaitForResponse(0x11, 3002, (char *) &myDotMatrix, sizeof(DOT_MATRIX_DATA_STRUCT), 
														4002, 200, 2);
			
			/* Display -- Venta */
			ScreenDisplayProtocol_SendDataPackWaitForResponse(0x12, 1002, (char *) &datafloat, sizeof(datafloat), 
														2002, 200, 2);
            
            /* Display -- Compra */
            ScreenDisplayProtocol_SendDataPackWaitForResponse(0x13, 1002, (char *) &datafloat, sizeof(datafloat), 
														2002, 200, 2);

			/* Display -- Tasa */
			ScreenDisplayProtocol_SendDataPackWaitForResponse(0x14, 1002, (char *) &datafloat, sizeof(datafloat), 
														2002, 200, 2);    
            
            
														
            index = (index >= 5 ) ? 0 : index + 1;
            Timer_Reset(&myTimer);
        }
        
    }
}

