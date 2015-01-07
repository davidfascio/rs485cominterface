////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDisplay7Seg.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDisplay7Seg.h"
#include "Com485Interface.h"

//**********************************************************************
// Functions
//**********************************************************************

// Setters and Getters

void  ScreenDispla7Seg_SetData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, float data){

	screendisplay7seg->data  =  data;
}

float ScreenDispla7Seg_GetData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg){
	
	return screendisplay7seg->data;
}

void ScreenDispla7Seg_ClearStringData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg){

	memset(ScreenDispla7Seg_GetStringData(screendisplay7seg), 0, SCREEN_DISPLAY_7_SEG_MAX_STRING_DATA_BUFFER);
}	

void ScreenDispla7Seg_SetStringData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, char* data, int dataLen){
	
	if (dataLen > SCREEN_DISPLAY_7_SEG_MAX_STRING_DATA_BUFFER)
		return;
	
	ScreenDispla7Seg_ClearStringData(screendisplay7seg);
	memcpy(ScreenDispla7Seg_GetStringData(screendisplay7seg), data, dataLen );	
}

char * ScreenDispla7Seg_GetStringData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg){
	
	return screendisplay7seg->stringdata;
}

DISPLAY_7_SEG_PTR ScreenDispla7Seg_GetDisplay7Seg(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg){
	
	return &screendisplay7seg->display7seg;
}

//**********************************************************************
// API Functions
//**********************************************************************

void ScreenDispla7Seg_Setup(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, char * data, int dataLen, int * display7segbuffer, int display7segbuffersize){
	
	//ScreenDispla7Seg_SetData(screendisplay7seg, data);
	//!ScreenDispla7Seg_SetStringData(screendisplay7seg, data, strlen(data));	
	Display7Seg_Setup(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg), display7segbuffer, display7segbuffersize);
	
	//! Preinit
	ScreenDispla7Seg_UpdateStringData(screendisplay7seg, data, dataLen);
}

int ScreenDispla7Seg_UpdateData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, float data){	
	
	volatile int error_code;
	//! Special Messages HERE
	
	error_code = ScreenDispla7Seg_FloatParseToScreenDisplay(screendisplay7seg, data);
	
	if( error_code == SCREEN_DISPLAY_7_SEG_NO_ERROR_CODE){
			
		Display7Seg_SendBuffer(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg));	
		ScreenDispla7Seg_SetData(screendisplay7seg, data);	
	}
	
	return error_code;
}

int ScreenDispla7Seg_UpdateStringData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, char * data, int dataLen){	
	
	volatile int error_code;
	//! Special Messages HERE
	
	error_code = ScreenDispla7Seg_StringParseToScreenDisplay(screendisplay7seg, data, dataLen);
	
	if( error_code == SCREEN_DISPLAY_7_SEG_NO_ERROR_CODE){
			
		Display7Seg_SendBuffer(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg));	
		ScreenDispla7Seg_SetStringData(screendisplay7seg, data, dataLen);	
	}
	
	return error_code;
}

int ScreenDispla7Seg_FloatParseToScreenDisplay(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, float data){
	
	int bufferSize = (Display7Seg_GetBufferSize(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg)));
	int bufferIndex;
	
	int intlenght;
	int floatlenght = 0;
	int indexPosition;
		
	float auxdata = data;	
	float fauxdata = data;
	int   iauxdata = (int) data;
	
	int data7Seg;	
	
	intlenght = (auxdata < 1.0) ? 1 : 0;
	

	while(auxdata >= 1.0){
	auxdata /= 10.0;
			intlenght++;
	}
	
	if(intlenght >= bufferSize)
		return SCREEN_DISPLAY_7_SEG_MAX_NUMBER_ALLOWED_ERROR_CODE;	
	 
	indexPosition = bufferSize - intlenght;
	
	while( indexPosition > 0) 
	{
		floatlenght++;
		indexPosition--;

		fauxdata = data * (n_pow(10,floatlenght));		
	}
	
	iauxdata = (int) fauxdata; 	

	for(bufferIndex = 0; bufferIndex < bufferSize ; bufferIndex++)
	{
		data7Seg= (iauxdata % 10);
		iauxdata /=10;
		
		data7Seg = Display7Seg_IntParseTo7Seg(data7Seg);
		
		if(bufferIndex == (bufferSize - intlenght ))
			data7Seg |= DISPLAY_7_SEG_CHARACTER_DOT;
			
		Display7Seg_SetBufferByIndex(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg), bufferIndex, data7Seg);		
	}
	
	return 	SCREEN_DISPLAY_7_SEG_NO_ERROR_CODE; 
}


int n_pow(int number, int count) {
	int result = 1;
	
	while(count-- > 0)
		result *=number;  

	return result;
}

int ScreenDispla7Seg_StringParseToScreenDisplay(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, char * data, int dataLen){

	int bufferSize = (Display7Seg_GetBufferSize(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg)));
	int bufferIndex; 
    int index; 
    int data7Seg;
    char * dotPosition = strchr(data, '.');
    boolean containsDot = dotPosition != NULL ? TRUE : FALSE;
	
	//if(dataLen >= bufferSize)
		//return SCREEN_DISPLAY_7_SEG_MAX_NUMBER_ALLOWED_ERROR_CODE;	
	if( containsDot ? (dotPosition - data) > (bufferSize): dataLen > bufferSize )
		return SCREEN_DISPLAY_7_SEG_MAX_NUMBER_ALLOWED_ERROR_CODE;	
	
	for(index = 0; index < dataLen; index++){
		
		// Validation
		if (((*(data + index) < '0') ||
			(*(data + index) > '9')) && 
			(*(data + index) != '.'))
			return SCREEN_DISPLAY_7_SEG_BAD_FORMAT_ERROR_CODE;		
	}
	
	index = 0;
	bufferIndex = 0;	
	while(bufferIndex < bufferSize)
	{
		if (index < dataLen){
			
			data7Seg = *(data + index);				
			if(data7Seg == '.' && bufferIndex > 0){
				
				--bufferIndex;
				data7Seg =	Display7Seg_GetBufferByIndex(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg),
							bufferIndex);
							
				data7Seg |= DISPLAY_7_SEG_CHARACTER_DOT;
			} 
			else
			{
				data7Seg -= '0';
				data7Seg = Display7Seg_IntParseTo7Seg(data7Seg);				
			}
			
			
		}
		else if((index == dataLen) && !containsDot){
			--bufferIndex;
			data7Seg =	Display7Seg_GetBufferByIndex(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg),
						bufferIndex);
						
			data7Seg |= DISPLAY_7_SEG_CHARACTER_DOT;	
			containsDot = TRUE;		
		}
		else 
		{
			data7Seg = Display7Seg_IntParseTo7Seg(0);						
		}
		
		Display7Seg_SetBufferByIndex(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg),
							bufferIndex, data7Seg);							
		++bufferIndex;
		++index;
	}	
	
	//Display7Seg_ReverseBuffer(ScreenDispla7Seg_GetDisplay7Seg(screendisplay7seg));
	return 	SCREEN_DISPLAY_7_SEG_NO_ERROR_CODE; 
}
