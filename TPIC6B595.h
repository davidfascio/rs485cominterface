/***********************************************************************
 * TPIC6B595.h -- Power Logic 8-BIT Shift Register Library
 * 
 * November 12th, 2014 12:25 pm
 ***********************************************************************/ 

#ifndef __TPIC6B595_H__
#define __TPIC6B595_H__


#include "bsp.h"
/***********************************************************************
 
   Display 7 segments connection diagram
  
  						     /- A -/
							C     B
      					   /- D -/
     					  F     E
    					 /- G -/
            						*DP
	Where:
	Binary data 0x01 - Segment B
				0x02 - A
				0x04 - E
				0x08 - G
				0x10 - D
				0x20 - C
				0x40 - F 
				0x80 - DP
 
************************************************************************/


// Pinout 7 Segments Defines
#define DISPLAY_7_SEG_A			(0x02)
#define DISPLAY_7_SEG_B			(0x01)
#define DISPLAY_7_SEG_C			(0x20)
#define DISPLAY_7_SEG_D			(0x10)
#define DISPLAY_7_SEG_E			(0x04)
#define DISPLAY_7_SEG_F			(0x40)
#define DISPLAY_7_SEG_G			(0x08)
#define DISPLAY_7_SEG_DP		(0x80)


void TPIC6B595_Setup(void);
void TPIC6B595_SendData(int data);

void TPIC6B595_HideData();
void TPIC6B595_ShowData();


#define TPIC6B595_STR_PIN  (BSP_PIN_A0)

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
	bsp_delay_ms(1);  
	bsp_io_write(TPIC6B595_STR_PIN, LOW);          
}

#endif /* __TPIC6B595_H__ */
