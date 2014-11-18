#include "TPIC6B595.h"

BSP_PORT slaveSelectPin = BSP_PIN_A0;

void TPIC6B595_Setup(void){
	
	// initialize SPI:
	bsp_pin_mode(TPIC6B595_STR_PIN, OUTPUT);
	bsp_spi_setup();
	bsp_io_write(TPIC6B595_STR_PIN, LOW);    
}

void TPIC6B595_SendData(int data) {
	  
	bsp_spi_send(data);  
}

void TPIC6B595_HideData(){
	
	bsp_io_write(TPIC6B595_STR_PIN, LOW);    
}

void TPIC6B595_ShowData(){
	  
	bsp_io_write(TPIC6B595_STR_PIN, HIGH);          
	delay(1);  
	bsp_io_write(TPIC6B595_STR_PIN, LOW);          
}
