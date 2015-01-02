#include "Utils.h"

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
