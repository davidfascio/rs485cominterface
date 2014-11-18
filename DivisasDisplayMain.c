/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.4 Standard
Automatic Program Generator
© Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 13/11/2014
Author  : 
Company : 
Comments: 


Chip type           : ATmega8535
Program type        : Application
Clock frequency     : 8.000000 MHz
Memory model        : Small
External RAM size   : 0
Data Stack size     : 128
*****************************************************/



// SPI functions

#include "ScreenDisplay7Seg.h"


// set pin 10 as the slave select for the digital pot:

SCREEN_DISPLAY_7_SEG screendisplay7segdemo;

#define DISPLAY_7_SEG_BUFFER_SIZE_DEMO  (4)

int display7segbufferdemo[DISPLAY_7_SEG_BUFFER_SIZE_DEMO];
float cadena[4] = {0.1, 1.123, 10.0 , 4.456};
int index;

void main(void)
{
	float datademo;	
	
	bsp_setup();
	bsp_pin_mode(BSP_PIN_A0,OUTPUT);
	ScreenDispla7Seg_Setup(&screendisplay7segdemo, 0.0,  display7segbufferdemo, DISPLAY_7_SEG_BUFFER_SIZE_DEMO);
	
	datademo =0.0;
	
	while(datademo < 1000.0){
		ScreenDispla7Seg_UpdateData(&screendisplay7segdemo, datademo);
        datademo = datademo + 0.001;              
		bsp_delay_ms(1000);
	}
}
