////////////////////////////////////////////////////////////////////////
//
// File name: DotMatrix.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "DotMatrix.h"


//**********************************************************************
// Functions
//********************************************************************** 

// Setters and Getters
void DotMatrix_SetMatrixBuffer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char *dotMatrix_Buffer){
	
	dotMatrixControl->dotMatrix_Buffer = dotMatrix_Buffer;
}

char * DotMatrix_GetMatrixBuffer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl){
	
	return dotMatrixControl->dotMatrix_Buffer;
}

void DotMatrix_SetWidth(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int dotMatrix_Width){
	
	dotMatrixControl->dotMatrix_Width = dotMatrix_Width;	
}

int DotMatrix_GetWidth(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl){
	
	return dotMatrixControl->dotMatrix_Width;	
}

void DotMatrix_SetHeight(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int dotMatrix_Height){
	
	dotMatrixControl->dotMatrix_Height = dotMatrix_Height;	
}

int DotMatrix_GetHeight(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl){
	
	return dotMatrixControl->dotMatrix_Height;		
}

void DotMatrix_SetRenderRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int dotMatrix_RenderRowIndex){
	
	dotMatrixControl->dotMatrix_RenderRowIndex = dotMatrix_RenderRowIndex;	
}

int DotMatrix_GetRenderRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl){
	
	return dotMatrixControl->dotMatrix_RenderRowIndex;		
}

void DotMatrix_SetRenderRowTimer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, TIMER_STRUCT dotMatrix_RenderRowTimer){
	
	dotMatrixControl->dotMatrix_RenderRowTimer = dotMatrix_RenderRowTimer;	
}

TIMER_STRUCT_PTR_ DotMatrix_GetRenderRowTimer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl){
	
	return &dotMatrixControl->dotMatrix_RenderRowTimer;		
}

// Specific Setters and Getters
/*void DotMatrix_SetElementBvoid DotMatrix_SetElementBufferByCoordinate(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int Pox, int Poy, int data){
	
}

char DotMatrix_GetElementBufferByCoordinate(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int Pox, int Poy){
	
}

void DotMatrix_SetWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int rowIndex, char * widthBuffer){
	
}*/

char * DotMatrix_GetWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int rowIndex){
	
	int width;	
	char * widthBuffer;
	width = DotMatrix_GetWidth(dotMatrixControl);
	widthBuffer = DotMatrix_GetMatrixBuffer(dotMatrixControl);
	return (widthBuffer + (rowIndex * width));
}
char message[20];
// API Functions
void DotMatrix_Setup(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char * dotMatrix_Buffer, int width, int height){
	
	TIMER_STRUCT_PTR_ timer;

	//memset(dotMatrix_Buffer, 0x00, width * height);
		
	dotMatrixControl->dotMatrix_Buffer 			= dotMatrix_Buffer;	
	dotMatrixControl->dotMatrix_Width 			=  width;
	dotMatrixControl->dotMatrix_Height 			=  height;
	dotMatrixControl->dotMatrix_RenderRowIndex 	= 0;
		
	// Driver
	TPIC6B595_Setup();
	SN54LS145N_Setup();	
						
	//Setting Timer
	timer = DotMatrix_GetRenderRowTimer(dotMatrixControl);
	AddTimer(timer, DOT_MATRIX_RENDER_ROW_TIME_DEFAULT_VALUE_IN_MS);
}


void DotMatrix_SendWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int rowIndex){
	
	volatile char * widthBuffer;
	volatile int width;
	
	width = DotMatrix_GetWidth(dotMatrixControl);
	widthBuffer = DotMatrix_GetWidthBufferByRowIndex(dotMatrixControl, rowIndex);
		
	SN54LS145N_SendData(rowIndex);	
	TPIC6B595_SendBuffer(widthBuffer, width);	
}

void DotMatrix_Update(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl){
	
	TIMER_STRUCT_PTR_ timer;
	
	timer = DotMatrix_GetRenderRowTimer(dotMatrixControl);
	
	/*if(!Timer_GetOverflow(timer))
		return;*/
		
		
	if(	dotMatrixControl->dotMatrix_RenderRowIndex >= 
		dotMatrixControl->dotMatrix_Height) {
			
		dotMatrixControl->dotMatrix_RenderRowIndex = 0;			
	}		
		
	TPIC6B595_Clear(dotMatrixControl->dotMatrix_Width);
	//SN54LS145N_ClearData();
		
	SN54LS145N_SendData((dotMatrixControl->dotMatrix_Height -1) - 
						 dotMatrixControl->dotMatrix_RenderRowIndex);		
						 
	TPIC6B595_SendBuffer(dotMatrixControl->dotMatrix_Buffer + 
						(dotMatrixControl->dotMatrix_RenderRowIndex * 
						dotMatrixControl->dotMatrix_Width), 
						dotMatrixControl->dotMatrix_Width);
		
	dotMatrixControl->dotMatrix_RenderRowIndex++;	
	
	Timer_Reset(timer);	
}
