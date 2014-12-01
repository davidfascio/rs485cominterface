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

//**********************************************************************
// Defines
//********************************************************************** 

//**********************************************************************
// Structs
//**********************************************************************
typedef struct dotmatrixstruct{
	char *dotMatrix_Buffer;		
	char  dotMatrix_Width;	
	char  dotMatrix_Height;	
} DOT_MATRIX_STRUCT, * DOT_MATRIX_STRUCT_PTR_;

//**********************************************************************
// Prototype functions
//********************************************************************** 

// Setters and Getters
void DotMatrix_SetMatrixBuffer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char *dotMatrix_Buffer);
char * DotMatrix_GetMatrixBuffer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl);

void DotMatrix_SetWidth(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char dotMatrix_Width);
char DotMatrix_GetWidth(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl);

void DotMatrix_SetHeight(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char dotMatrix_Height);
char DotMatrix_GetHeight(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl);

// Specific Setters and Getters
void DotMatrix_SetElementBufferByCoordinate(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char Pox, char Poy, char data);
char DotMatrix_GetElementBufferByCoordinate(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char Pox, char Poy);

void DotMatrix_SetWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char rowIndex, char * widthBuffer);
char * DotMatrix_GetWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char rowIndex);

// API Functions
void DotMatrix_Setup(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char width, char height);

void DotMatrix_SendWidthBuffer(char * widthBuffer, char width);
void DotMatrix_SendWidthBufferByRowIndex(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl, char rowIndex);
void DotMatrix_SendMatrixBuffer(DOT_MATRIX_STRUCT_PTR_ dotMatrixControl);

#endif /* __DOT_MATRIX_H__ */
