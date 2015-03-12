////////////////////////////////////////////////////////////////////////
//
// File name: Com485Protocol.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "TcpComInterface.h"


//**********************************************************************
// API Fucntions
//**********************************************************************
void TCPComInterface_Setup(void){
	
	// Net Burner SBL2E Driver Implementation
	bsp_pin_mode(NETBURNER_SBL2E_TCP_RST, OUTPUT);
	bsp_io_write(NETBURNER_SBL2E_TCP_RST, NETBURNER_SBL2E_TCP_RST_OFF);
	
	bsp_usart1_setup(TCPComInterface_CallBackFromSendingProcess);
}

int TCPComInterface_Read(char * data, int data_lenght){

	return bsp_usart1_read(data, data_lenght);
}

int TCPComInterface_Write(char * data, int data_lenght){
	
	return bsp_usart1_write(data, data_lenght);
}

void TCPComInterface_CallBackFromSendingProcess(void){
	
	// By the moment do nothing XD	
}
