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

void DotMatrix_SetWidth(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char dotMatrix_Width){
	
	dotMatrixControl->dotMatrix_Width;	
}

char DotMatrix_GetWidth(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl){
	
	return dotMatrixControl->dotMatrix_Width;	
}

void DotMatrix_SetHeight(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char dotMatrix_Height){
	
	dotMatrixControl->dotMatrix_Height = dotMatrix_Height;	
}

char DotMatrix_GetHeight(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl){
	
	return dotMatrixControl->dotMatrix_Height;		
}

// Specific Setters and Getters
void DotMatrix_SetElementBufferByCoordinate(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char Pox, char Poy, char data){
	
}

char DotMatrix_GetElementBufferByCoordinate(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char Pox, char Poy){
	
}

void DotMatrix_SetWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char rowIndex, char * widthBuffer){
	
}

char * DotMatrix_GetWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char rowIndex){
	
}

// API Functions
void DotMatrix_Setup(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char width, char height){
	
}

void DotMatrix_SendWidthBuffer(char * widthBuffer, char width){
	
}

void DotMatrix_SendWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char rowIndex){
	
}

void DotMatrix_SendMatrixBuffer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl){
	
}

#endif /* __DOT_MATRIX_H__ */
