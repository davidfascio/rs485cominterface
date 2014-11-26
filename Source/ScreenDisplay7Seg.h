/*
 * File: ScreenDisplay7Seg.h
 * Author: fascio
 * 
 * Created on November 12th, 2014, 16:21
 */ 
 
#ifndef __SCREEN_DISPLAY_7_SEG_H__
#define __SCREEN_DISPLAY_7_SEG_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "Display7Seg.h"

#define SCREEN_DISPLAY_7_SEG_NO_ERROR_CODE			  				(0)
#define SCREEN_DISPLAY_7_SEG_MAX_NUMBER_ALLOWED_ERROR_CODE			(-1)

//**********************************************************************
// Structures
//**********************************************************************
typedef struct screendisplay7segstruct{
	float data;
	DISPLAY_7_SEG display7seg;
}SCREEN_DISPLAY_7_SEG, * SCREEN_DISPLAY_7_SEG_PTR;


//**********************************************************************
// Prototype functions
//**********************************************************************

void  ScreenDispla7Seg_SetData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, float data);
float ScreenDispla7Seg_GetData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg);	
	
DISPLAY_7_SEG_PTR ScreenDispla7Seg_GetDisplay7Seg(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg);

void ScreenDispla7Seg_Setup(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, float data, int * display7segbuffer, int display7segbuffersize);
int ScreenDispla7Seg_UpdateData(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, float data);
int ScreenDispla7Seg_FloatParseToScreenDisplay(SCREEN_DISPLAY_7_SEG_PTR screendisplay7seg, float data);

int n_pow(int number, int count);

#endif /* __SCREEN_DISPLAY_7_SEG_H__ */
