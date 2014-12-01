////////////////////////////////////////////////////////////////////////
//
// File name: SN54LS145N.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "SN54LS145N.h"

//**********************************************************************
// API Fucntions
//**********************************************************************

void SN54LS145N_Setup(void){	
	
	bsp_pin_mode(SN54LS145N_PIN_A, OUTPUT);
	bsp_pin_mode(SN54LS145N_PIN_B, OUTPUT);
	bsp_pin_mode(SN54LS145N_PIN_C, OUTPUT);
	bsp_pin_mode(SN54LS145N_PIN_D, OUTPUT);		
	
	SN54LS145N_ClearData();	
}

void SN54LS145N_ClearData(void){
	
	SN54LS145N_SendData(SN54LS145N_CLEAR_DATA);
}

void SN54LS145N_SendData(char data) {
	
	bsp_io_write(SN54LS145N_PIN_A, (data & 0x01) ? HIGH : LOW);
	bsp_io_write(SN54LS145N_PIN_B, (data & 0x02) ? HIGH : LOW);
	bsp_io_write(SN54LS145N_PIN_C, (data & 0x04) ? HIGH : LOW);
	bsp_io_write(SN54LS145N_PIN_D, (data & 0x08) ? HIGH : LOW);
}
