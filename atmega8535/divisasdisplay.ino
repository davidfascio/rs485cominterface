
// inslude 
#include <SPI.h>
#include "ScreenDisplay7Seg.h"



// set pin 10 as the slave select for the digital pot:

SCREEN_DISPLAY_7_SEG screendisplay7segdemo;

#define DISPLAY_7_SEG_BUFFER_SIZE_DEMO  (4)
int display7segbufferdemo[DISPLAY_7_SEG_BUFFER_SIZE_DEMO];



float cadena[4] = {0.1, 1.123, 10.0 , 4.456};
int index;
void setup() {
	  
  ScreenDispla7Seg_Setup(&screendisplay7segdemo, 0.0,  display7segbufferdemo, DISPLAY_7_SEG_BUFFER_SIZE_DEMO);
  Serial.begin(9600);
}

void loop() { 
  float datademo;
 

  datademo =0.0;
   while(datademo < 1000.0){
	  ScreenDispla7Seg_UpdateData(&screendisplay7segdemo, datademo);
          datademo = datademo + 0.001;
	  delay(10);
  }
}
