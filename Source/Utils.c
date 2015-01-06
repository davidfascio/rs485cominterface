////////////////////////////////////////////////////////////////////////
//
// File name: Utils.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "Utils.h"

//**********************************************************************
// API Fucntions
//**********************************************************************
int str2uint(char * data, int dataLen, int base){
	
	volatile int index;
	volatile int integer;
	volatile int result = 0;
	
	for (index = 0 ; index < dataLen; index ++ )	{
		integer = char2int(* (data + index));
		
		if ( integer < 0)
			return integer;
			
		if (integer >= base)
			return - integer;
			
		result = base * result + integer;
	}
		
	return result;
}

int char2int(char data){
	
	if (data >= '0' && data <= '9')
		return data - '0';
	
	if (data >= 'A' && data <= 'F')
		return data - 'A' + 10;
	
	return -1; // ERROR
}

char * strsearch(char * data,  char pattern){
	int index;
	for (index = 0; index < strlen(data); index++){
		
		if (*(data + index)	 == pattern)
			return data + index;
	}
	
	return NULL;
}

unsigned int strchecksum(char * data, int dataLen){
	
	int index;
	int checksum = 0;
	
	for(index = 0; index < dataLen ; index++ )
		checksum = checksum + *(data +  index);
	
	return checksum;
}

void uint2str(int data,char * buffer,int bufferLen){
	
	memset(buffer, 0, bufferLen);
	sprintf(buffer, "%d",data);
}

void strappendchar(char * buffer, int bufferLen, char data){
	
	if( strlen(buffer) < (bufferLen - 1))	
		*(buffer + strlen(buffer)) = data;		
}

float str2float(char * data, int dataLen){
	
	char buffer[10];
	float value = 0.0;
	float base = 1.0;
    
    int index;
    int dotIndex = -1;
    
	if (dataLen > 10)
	 return -1;
	 
	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, data, dataLen);
	
	for ( index = 0; index < dataLen; index++){
		
		if ((*(buffer + index) >= '0' )&& 
		   (*(buffer + index) <= '9' ) ){
			   
			   value = (float) (*(buffer + index)- '0') + 10.0 * value;
		   }
		   
		if(*(buffer + index) == '.')
			dotIndex = index;
	}
	
	if (dotIndex >= 0){
		for ( index = dotIndex + 1; index < dataLen; index++)
			base =  base * 10.0;
			
		value = value / base;
	}	
		
	return value;	
}
