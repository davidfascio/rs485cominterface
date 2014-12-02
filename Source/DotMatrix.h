/*
 * File: DotMatrix.h
 * Author: fascio
 * 
 * Created on November 28th, 2014, 18:36
 */ 

#ifndef __DOT_MATRIX_H__
#define __DOT_MATRIX_H__

//**********************************************************************
// Includes
//********************************************************************** 
#include "TPIC6B595.h"
#include "SN54LS145N.h"
#include "Timer.h"


//**********************************************************************
// Defines
//********************************************************************** 
#define DOT_MATRIX_RENDER_ROW_TIME_DEFAULT_VALUE_IN_MS				(1)			


//**********************************************************************
// Structs
//**********************************************************************
typedef struct dotmatrixstruct{
	char *dotMatrix_Buffer;		
	int  dotMatrix_Width;	
	int  dotMatrix_Height;	
	int  dotMatrix_RenderRowIndex;
	TIMER_STRUCT dotMatrix_RenderRowTimer;
} DOT_MATRIX_STRUCT, * DOT_MATRIX_STRUCT_PTR_;

//**********************************************************************
// Prototype functions
//********************************************************************** 

// Setters and Getters
void DotMatrix_SetMatrixBuffer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char *dotMatrix_Buffer);
char * DotMatrix_GetMatrixBuffer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl);

void DotMatrix_SetWidth(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int dotMatrix_Width);
int DotMatrix_GetWidth(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl);

void DotMatrix_SetHeight(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int dotMatrix_Height);
int DotMatrix_GetHeight(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl);

// Specific Setters and Getters
/*void DotMatrix_SetElementBufferByCoordinate(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int Pox, int Poy, int data);
int DotMatrix_GetElementBufferByCoordinate(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int Pox, int Poy);

void DotMatrix_SetWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char rowIndex, char * widthBuffer);*/
char * DotMatrix_GetWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int rowIndex);

// API Functions
void DotMatrix_Setup(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char * dotMatrix_Buffer, int width, int height);
void DotMatrix_SendWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, int rowIndex);
void DotMatrix_Update(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl);

#endif /* __DOT_MATRIX_H__ */
