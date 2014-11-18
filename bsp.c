#include "bsp.h"

//**********************************************************************
// BSP IO Functions
//**********************************************************************
void bsp_pin_mode(BSP_PORT bsp_pin, int dir_pin){
	
}

void bsp_io_write(BSP_PORT bsp_pin, int state_pin){
	
}

//**********************************************************************
// BSP SPI Functions
//**********************************************************************

void bsp_spi_setup(void){
	
	// SPI initialization
// SPI Type: Master
// SPI Clock Rate: 31.250 kHz
// SPI Clock Phase: Cycle Half
// SPI Clock Polarity: Low
// SPI Data Order: MSB First
SPCR=0x53;
SPSR=0x00;
	
}

void bsp_spi_send(int data){
	
	spi(data);
}

