////////////////////////////////////////////////////////////////////////
//
// File name: Com485Interface.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "Com485Interface.h"

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void Com485Interface_Setup(void){
	
	//! Com485Interface_setup();
	bsp_pin_mode(COM_485_INTERFACE_ENALE_TRANSMITION, OUTPUT);
	bsp_io_write(COM_485_INTERFACE_ENALE_TRANSMITION, COM_485_INTERFACE_TX_OFF);
	
	bsp_usart_setup(Com485Interface_RestoreReception);	
}

int Com485Interface_Read(char * DataReceiveBuffer, int DataLen){

	//! recvrslt = Com485Interface_read();			
	return bsp_usart_read(DataReceiveBuffer, DataLen);	
}

int Com485Interface_Write(char * DataToSend, int DataLen){

	//! sendrslt = Com485Interface_write(DataToSend, DataLen);
	bsp_io_write(COM_485_INTERFACE_ENALE_TRANSMITION, COM_485_INTERFACE_TX_ON);
	return bsp_usart_write(DataToSend, DataLen);	
}

void Com485Interface_RestoreReception(void){
	
	boolean restoreReception = (boolean) bsp_usart_fstatus();
	
	if (restoreReception)
		bsp_io_write(COM_485_INTERFACE_ENALE_TRANSMITION, COM_485_INTERFACE_TX_OFF);	
}
