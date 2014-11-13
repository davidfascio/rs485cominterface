#include "TPIC6B595.h"

const int slaveSelectPin = 8;

void TPIC6B595_Setup(void){
	// set the slaveSelectPin as an output:
	pinMode (slaveSelectPin, OUTPUT);
	// initialize SPI:
	SPI.begin();  
    digitalWrite(slaveSelectPin,LOW);
}

void TPIC6B595_SendData(int data) {
  // take the SS pin low to select the chip:

//  delay(10);
  //  send in the address and value via SPI:
  
  SPI.transfer(data);

  //delay(10);
  // take the SS pin high to de-select the chip:
//  digitalWrite(slaveSelectPin,HIGH); 
  //delay(10);
  
//  digitalWrite(slaveSelectPin,LOW); 	
}

void TPIC6B595_HideData(){
  
    digitalWrite(slaveSelectPin,LOW);
}

void TPIC6B595_ShowData(){
      digitalWrite(slaveSelectPin,HIGH); 
      delay(1);  
      digitalWrite(slaveSelectPin,LOW); 
}
