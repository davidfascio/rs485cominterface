/*
 * File: ScreenDotMatrix.h
 * Author: fascio
 * 
 * Created on December 2nd, 2014, 09:18
 */ 

#ifndef __SCREEN_DOT_MATRIX_H__
#define __SCREEN_DOT_MATRIX_H__

//**********************************************************************
// BSP Includes
//**********************************************************************
#include "DotMatrix.h"
//#include "Fonts.h"

//**********************************************************************
// Defines
//**********************************************************************
#define SCREEN_DOT_MATRIX_WIDTH 									(3)
#define SCREEN_DOT_MATRIX_HEIGHT 									(7)


void ScreenDotMatrix_Setup(void);
void ScreenDotMatrix_Render(void);
void ScreenDotMatrix_Clear(void);

void ScreenDotMatrix_Draw( 	char * img, int width_pixels, int height_pixels, int x_pixels, int y_pixels);
char * ScreenDotMatrix_GetByteAddressByPosition(int x_pixels, int y_pixels);

#endif /* __SCREEN_DOT_MATRIX_H__ */
