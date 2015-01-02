/*
 * File: DivisasScreenMaster.h
 * Author: fascio
 * 
 * Created on November 10th, 2014 12:00:00
 */ 
 
//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenMasterProtocol.h"
#include "ScreenMasterDevice.h"
#include "Timer.h"
                                                                                                                                                
TIMER_STRUCT myTimer;                                                                                                                                                                                                                                                      
TCP_COM_PROTOCOL_STRUCT TCPComProtocolControl;
char masterPassword[] = "123456789";
char MasterAddress = 0x01;

//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{
    int estado = LOW;      	

	//! SETUP
	bsp_setup();    
	Timer_Setup();	
	
	ScreenMasterProtocol_Setup(MasterAddress);
	ScreenMasterDevice_Setup(MasterAddress);	
	
	//! AFTER SETUP                                	
	bsp_pin_mode(BSP_PIN_A0, OUTPUT);
	bsp_io_write(BSP_PIN_A0, HIGH);
	AddTimer(&myTimer, 1000);	                                      	
	
	//! LOOP
	while(TRUE){
		
		//!*************************************************************
		//! Communication Protocol Process 
		//!*************************************************************		
		ScreenMasterProtocol_WaitDataPacketCheck();                                          		
		ScreenMasterProtocol_ProcessingDataPacketArrived();
		
		if(Timer_GetOverflow(&myTimer) == TRUE){			
					
			estado = (estado == LOW )? HIGH : LOW;
			bsp_io_write(BSP_PIN_A0, estado);
			Timer_Reset(&myTimer);
		}				
	}
}
