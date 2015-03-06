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
	//! MUST BE
	//bsp_io_write(SN54LS145N_PIN_A, (data & 0x01) ? HIGH : LOW);
	//bsp_io_write(SN54LS145N_PIN_B, (data & 0x02) ? HIGH : LOW);
	//bsp_io_write(SN54LS145N_PIN_C, (data & 0x04) ? HIGH : LOW);
	//bsp_io_write(SN54LS145N_PIN_D, (data & 0x08) ? HIGH : LOW);
	
	switch(data){
		case 0:
			bsp_io_write(SN54LS145N_PIN_A, LOW);
			bsp_io_write(SN54LS145N_PIN_B, LOW);
			bsp_io_write(SN54LS145N_PIN_C, LOW);
			bsp_io_write(SN54LS145N_PIN_D, LOW);
			
			break;
			
		case 1:
			bsp_io_write(SN54LS145N_PIN_A, HIGH);
			bsp_io_write(SN54LS145N_PIN_B, LOW);
			bsp_io_write(SN54LS145N_PIN_C, LOW);
			bsp_io_write(SN54LS145N_PIN_D, LOW);
			
			break;
			
		case 2:
			bsp_io_write(SN54LS145N_PIN_A, LOW);
			bsp_io_write(SN54LS145N_PIN_B, HIGH);
			bsp_io_write(SN54LS145N_PIN_C, LOW);
			bsp_io_write(SN54LS145N_PIN_D, LOW);
			break;
		
		/*case 0:
		case 1:
		case 2:
				PORTD = data;
				break;*/
		case 3:
			bsp_io_write(SN54LS145N_PIN_A, HIGH);
			bsp_io_write(SN54LS145N_PIN_B, HIGH);
			bsp_io_write(SN54LS145N_PIN_C, LOW);
			bsp_io_write(SN54LS145N_PIN_D, LOW);
			break;
			
		case 4:
			bsp_io_write(SN54LS145N_PIN_A, LOW);
			bsp_io_write(SN54LS145N_PIN_B, LOW);
			bsp_io_write(SN54LS145N_PIN_C, HIGH);
			bsp_io_write(SN54LS145N_PIN_D, LOW);
			break;
			
		case 5:
			bsp_io_write(SN54LS145N_PIN_A, HIGH);
			bsp_io_write(SN54LS145N_PIN_B, LOW);
			bsp_io_write(SN54LS145N_PIN_C, HIGH);
			bsp_io_write(SN54LS145N_PIN_D, LOW);
			break;
			
		case 6:
			bsp_io_write(SN54LS145N_PIN_A, LOW);
			bsp_io_write(SN54LS145N_PIN_B, HIGH);
			bsp_io_write(SN54LS145N_PIN_C, HIGH);
			bsp_io_write(SN54LS145N_PIN_D, LOW);
			break;
		/*case 3:
		case 4:
		case 5:
			PORTD = data + 1;
			break;*/		
		/*case 6:	
			PORTD = 0x03;
			break;*/
		default:
			bsp_io_write(SN54LS145N_PIN_A, HIGH);
			bsp_io_write(SN54LS145N_PIN_B, HIGH);
			bsp_io_write(SN54LS145N_PIN_C, HIGH);
			bsp_io_write(SN54LS145N_PIN_D, HIGH);
			//PORTD = 0xFF;
			break;		
	}
}


