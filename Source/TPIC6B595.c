////////////////////////////////////////////////////////////////////////
//
// File name: TPIC6B595.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "TPIC6B595.h"

//**********************************************************************
// API Fucntions
//**********************************************************************

void TPIC6B595_Setup(void){
	
	// initialize SPI:
	bsp_pin_mode(TPIC6B595_STR_PIN, OUTPUT);
	bsp_spi_setup();
	bsp_io_write(TPIC6B595_STR_PIN, LOW);    
}

void TPIC6B595_HideData(){
	
	bsp_io_write(TPIC6B595_STR_PIN, LOW);    
}

void TPIC6B595_ShowData(){
	  
	bsp_io_write(TPIC6B595_STR_PIN, HIGH);          
	bsp_delay_100us();  
	bsp_io_write(TPIC6B595_STR_PIN, LOW);          
}

void TPIC6B595_SendBuffer(char * buffer, char bufferLen){
	
	char index;
	
	TPIC6B595_HideData();
	
	for(index = 0; index < bufferLen; index++){
	
		bsp_spi_send(buffer[index]);
	}
	
	TPIC6B595_ShowData();	 
}

void TPIC6B595_Clear(char bufferLen){
	
	char index;
	
	TPIC6B595_HideData();
	
	for(index = 0; index < bufferLen; index++){
	
		bsp_spi_send(0);
	}
	
	TPIC6B595_ShowData();	 
}

unsigned char TPIC6B595_WriteData(char data){
	
	return bsp_spi_send(data);
}

