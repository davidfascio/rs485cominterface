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
#include "Fonts.h"

//**********************************************************************
// Defines
//**********************************************************************

#define SCREEN_DOT_MATRIX_WIDTH 									(3)
#define SCREEN_DOT_MATRIX_HEIGHT 									(7)

#define SCREEN_DOT_MATRIX_DEFAULT_TIMER_VALUE_IN_MS					(50)
#define SCREEN_DOT_MATRIX_DEFAULT_BUFFER_SIZE						(100)
#define SCREEN_DOT_MATRIX_DEFAULT_OFFSET_ON_X						(0)//(3)

#define SCREEN_DOT_MATRIX_NO_ERROR									(0)
#define SCREEN_DOT_MATRIX_BAD_EFFECT								(-1)
#define SCREEN_DOT_MATRIX_NO_ENOUGH_BUFFER_RESOURCES				(-2)

#define SCREEN_DOT_MATRIX_MAXIMUM_POS_LIMIT_ON_X(x)					(SCREEN_DOT_MATRIX_WIDTH  * 8)
#define SCREEN_DOT_MATRIX_MINIMUM_POS_LIMIT_ON_X(x)					((FONT_7x6_WIDTH - 1) * (int) (x -1) * (-1)) //+ SCREEN_DOT_MATRIX_DEFAULT_OFFSET_ON_X

typedef enum screendotmatrixeffect{	
	STATIC_TEXT,
	DYNAMIC_LEFT,
	DYNAMIC_RIGHT,
	NO_EFFECT
} SCREEN_DOT_MATRIX_EFFECT;

char * ScreenDotMatrix_GetText(void);
int ScreenDotMatrix_GetTextLen(void);
int ScreenDotMatrix_GetEffect(void);
int ScreenDotMatrix_GetDelay_ms(void);

void ScreenDotMatrix_Setup(void);
void ScreenDotMatrix_Render(void);
void ScreenDotMatrix_Clear(void);

void ScreenDotMatrix_Draw( 	char flash * img, int width_pixels, int height_pixels, int x_pixels, int y_pixels);
char * ScreenDotMatrix_GetByteAddressByPosition(int x_pixels, int y_pixels);

void ScreenDotMatrix_DrawText(char * text, int x_pixel, int y_pixel, char flash * font, int font_width, int font_height);

int ScreenDotMatrix_SendTextWithCustomDelay(char *text, int textLen, SCREEN_DOT_MATRIX_EFFECT effect, int delay_in_ms);
int ScreenDotMatrix_SendText(char *text, int textLen, SCREEN_DOT_MATRIX_EFFECT effect);


#endif /* __SCREEN_DOT_MATRIX_H__ */
