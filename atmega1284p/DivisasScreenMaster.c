/*
 * File: DivisasScreenMaster.h
 * Author: fascio
 * 
 * Created on November 10th, 2014 12:00:00
 */ 
 
//**********************************************************************
// Includes
//**********************************************************************
#include "System.h"
#include "ScreenMasterProtocol.h"
#include "ScreenMasterDevice.h"

                                                                                                                                                
TIMER_STRUCT myTimer;                                                                                                                                                                                                                                                      
TCP_COM_PROTOCOL_STRUCT TCPComProtocolControl;
char masterPassword[] = "123456789";
char MasterAddress = 0x01;

//**********************************************************************
// API Fucntions
//**********************************************************************
void main(void)
{
	//! SETUP
	System_Setup();		
	ScreenMasterProtocol_Setup(MasterAddress);
		
	//! AFTER SETUP                                	
	ScreenMasterDevice_Setup(MasterAddress);		                                	
	
	
	//! LOOP
	while(TRUE){
		
		//! System Loop Process
		System_Update();
		
		ScreenMasterDevice_Update();
		
		//! Communication Protocol Process 		
		ScreenMasterProtocol_WaitDataPacketCheck();                                          		
		ScreenMasterProtocol_ProcessingDataPacketArrived();		
		
	}
}
