////////////////////////////////////////////////////////////////////////
//
// File name: Display7Seg.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "Display7Seg.h"
 
//**********************************************************************
// Variables
//********************************************************************** 
//Map of Characters
int Display7SegCharacters[DISPLAY_7_SEG_MAX_CHARACTER_INDEX] = {DISPLAY_7_SEG_CHARACTER_0, 
																DISPLAY_7_SEG_CHARACTER_1, 
																DISPLAY_7_SEG_CHARACTER_2, 
																DISPLAY_7_SEG_CHARACTER_3,
																DISPLAY_7_SEG_CHARACTER_4,
																DISPLAY_7_SEG_CHARACTER_5,
																DISPLAY_7_SEG_CHARACTER_6,
																DISPLAY_7_SEG_CHARACTER_7,
																DISPLAY_7_SEG_CHARACTER_8,
																DISPLAY_7_SEG_CHARACTER_9
															   };



//**********************************************************************
// Functions
//**********************************************************************

// Setters and Getters
void Display7Seg_SetBuffer(DISPLAY_7_SEG_PTR display7seg, int * display7segbuffer){
	
	display7seg->display7segbuffer = display7segbuffer;	
}

int * Display7Seg_GetBuffer(DISPLAY_7_SEG_PTR display7seg){
	
	return display7seg->display7segbuffer;	
}

void Display7Seg_SetBufferSize(DISPLAY_7_SEG_PTR display7seg, int display7segbuffersize ){
	
	display7seg->display7segbuffersize = display7segbuffersize;
}
void Display7Seg_SetBufferByIndex(DISPLAY_7_SEG_PTR display7seg, int index, int data){
	
	display7seg->display7segbuffer[index] = data;
}

int Display7Seg_GetBufferByIndex(DISPLAY_7_SEG_PTR display7seg, int index){
	
	if(index >= Display7Seg_GetBufferSize(display7seg))
	 return DISPLAY_7_SEG_OUT_OF_MAX_BUFFER_SIZE_ERROR_CODE;
	
	return	display7seg->display7segbuffer[index];
}

int Display7Seg_GetBufferSize(DISPLAY_7_SEG_PTR display7seg){
	return display7seg->display7segbuffersize;
}


void Display7Seg_SetFeedbackError(DISPLAY_7_SEG_PTR display7seg, boolean display7segfeedbackerror){

	display7seg->display7segfeedbackerror = display7segfeedbackerror;
}

boolean Display7Seg_GetFeedbackError(DISPLAY_7_SEG_PTR display7seg){

	return display7seg->display7segfeedbackerror;	
}

// API Functions

void Display7Seg_Setup(DISPLAY_7_SEG_PTR display7seg, int * display7segbuffer, int display7segbuffersize){
		
	Display7Seg_SetBuffer(display7seg, display7segbuffer);
	Display7Seg_SetBufferSize(display7seg, display7segbuffersize);
	
	// Driver
	TPIC6B595_Setup();
}

unsigned char Display7Seg_SendDataInterface(int data) {
  
  //Driver
  return TPIC6B595_WriteData(data);	
}

int  Display7Seg_IntParseTo7Seg( int integerData){
	
	if (integerData < 0 || integerData >= DISPLAY_7_SEG_MAX_CHARACTER_INDEX)	
		return DISPLAY_7_SEG_OUT_OF_RANGE_ERROR_CODE;
	
	return Display7SegCharacters[integerData];
}

int Display7Seg_Symbols(SYMBOLS_ENUM symbol){
	
	switch(symbol){
				
		case DOT:
			return DISPLAY_7_SEG_CHARACTER_DOT;
			
		case HYPHEN:
			return DISPLAY_7_SEG_CHARACTER_HYPHEN;
			
		default:
			return DISPLAY_7_SEG_CHARACTER_NO_SYMBOL;
	}	
}

int  Display7Seg_ReverseBuffer(DISPLAY_7_SEG_PTR display7seg){	
	
	int * buffer;
	int bufferSize;
	int index;
	int reverseIndex;
	int dataIndex;
	
	bufferSize = Display7Seg_GetBufferSize(display7seg);
	buffer = (int *) malloc( bufferSize * sizeof(int));
	
	if (buffer == NULL)
		return DISPLAY_7_SEG_OUT_OF_MEMORY_ERROR_CODE; 
	
	reverseIndex = bufferSize - 1;
	
	for	(index = 0; index < bufferSize ; index++ ){
		
		dataIndex = Display7Seg_GetBufferByIndex(display7seg, index);
		*(buffer + reverseIndex) = dataIndex;
		--reverseIndex;
	}
	
	memcpy(Display7Seg_GetBuffer(display7seg), buffer, bufferSize);
	free(buffer);
	
	return 	DISPLAY_7_SEG_NO_ERROR_CODE;
}

void  Display7Seg_SendBuffer(DISPLAY_7_SEG_PTR display7seg){
	
	int index = 0;
	int bufferSize = Display7Seg_GetBufferSize(display7seg);
	int reverseIndex = bufferSize - 1;
	unsigned char checksum;
	unsigned char checksumResponse;
	
	checksum = bufferchecksum(Display7Seg_GetBuffer(display7seg),Display7Seg_GetBufferSize(display7seg));
	
	TPIC6B595_HideData();
	
    Display7Seg_SendDataInterface(checksum);
	for	(index = 0; index < Display7Seg_GetBufferSize(display7seg) ; index++ ){
		
		checksumResponse = Display7Seg_SendDataInterface(Display7Seg_GetBufferByIndex(display7seg, reverseIndex));
		--reverseIndex;
	}

    TPIC6B595_ShowData();             
    
    if(checksum != checksumResponse){
		Display7Seg_SetFeedbackError(display7seg, TRUE);
	}
	else{
		Display7Seg_SetFeedbackError(display7seg, FALSE);
	}    
}

void  Display7Seg_Clear(DISPLAY_7_SEG_PTR display7seg){
	
	int index = 0;
	int bufferSize = Display7Seg_GetBufferSize(display7seg);
	int reverseIndex = bufferSize - 1;
	unsigned char checksum;
	unsigned char checksumResponse;
	
	checksum = bufferchecksum(Display7Seg_GetBuffer(display7seg),Display7Seg_GetBufferSize(display7seg));
	
	TPIC6B595_HideData();
	
    Display7Seg_SendDataInterface(checksum);
	for	(index = 0; index < Display7Seg_GetBufferSize(display7seg) ; index++ ){
		
		checksumResponse = Display7Seg_SendDataInterface(0);
		--reverseIndex;
	}

    TPIC6B595_ShowData();             
    
    if(checksum != checksumResponse){
		Display7Seg_SetFeedbackError(display7seg, TRUE);
	}
	else{
		Display7Seg_SetFeedbackError(display7seg, FALSE);
	}    
}
