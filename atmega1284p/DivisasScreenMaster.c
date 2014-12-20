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

//#include "TcpComProtocol.h"
#include "ScreenMasterProtocol.h"
#include "Timer.h"


TIMER_STRUCT myTimer;

TCP_COM_PROTOCOL_STRUCT TCPComProtocolControl;

char masterPassword[] = "123456789";
//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{
    int estado = LOW;      	
	//! SETUP
	bsp_setup();    
	Timer_Setup();	
	
	ScreenMasterProtocol_Setup(0x01);
	/*TCPComProtocol_Setup(&TCPComProtocolControl, BSP_USART_COM_HDLR,
						  0x01, TCP_COM_PROTOCOL_DEFAULT_PREFIX, 0, masterPassword, 9);						  */
	
	//! AFTER SETUP
	
	bsp_pin_mode(BSP_PIN_A0, OUTPUT);
	bsp_io_write(BSP_PIN_A0, HIGH);
	AddTimer(&myTimer, 2000);	
	
	
	//! LOOP
	while(TRUE){
		
		//!*************************************************************
		//! Communication Protocol Process 
		//!*************************************************************
		//ScreenDisplayProtocol_WaitDataPacketCheck();
		//TCPComProtocol_WaitDataPacket(&TCPComProtocolControl, 100);
		ScreenMasterProtocol_WaitDataPacketCheck();
		//TCPComProtocolControl.DataPacketArrived = FALSE;		
		ScreenMasterProtocol_ProcessingDataPacketArrived();
		
		if(Timer_GetOverflow(&myTimer) == TRUE){
			
			//TCPComProtocol_SendDataPacket(&TCPComProtocolControl, 2, "0$HOLA MUNDO!$", strlen("0$HOLA MUNDO!$"));	
					
			estado = (estado == LOW )? HIGH : LOW;
			bsp_io_write(BSP_PIN_A0, estado);
			Timer_Reset(&myTimer);
		}				
	}
}
