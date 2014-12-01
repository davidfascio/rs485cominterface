/*
 * File: Display7Seg.h
 * Author: fascio
 * 
 * Created on November 12th, 2014, 12:25
 */ 

#ifndef __DISPLAY_7_SEG_H__
#define __DISPLAY_7_SEG_H__

//**********************************************************************
// Includes
//********************************************************************** 
#include "TPIC6B595.h"

//**********************************************************************
// Defines
//********************************************************************** 
////////////////////////////////////////////////////////////////////////
// 
//   Display 7 segments connection diagram
//  
//							/- A -/
//						   C     B
//      			      /- D -/
//     				     F     E
//    				    /- G -/
//            					*DP
//	Where:
//			Binary data 0x01 - Segment B
//						0x02 - A
//						0x04 - E
//						0x08 - G
//						0x10 - D
//						0x20 - C
//						0x40 - F 
//						0x80 - DP
////////////////////////////////////////////////////////////////////////

// Pinout 7 Segments Defines
#define DISPLAY_7_SEG_A			(0x02)
#define DISPLAY_7_SEG_B			(0x01)
#define DISPLAY_7_SEG_C			(0x20)
#define DISPLAY_7_SEG_D			(0x10)
#define DISPLAY_7_SEG_E			(0x04)
#define DISPLAY_7_SEG_F			(0x40)
#define DISPLAY_7_SEG_G			(0x08)
#define DISPLAY_7_SEG_DP		(0x80)

// Characters Defines
#define DISPLAY_7_SEG_CHARACTER_0 (DISPLAY_7_SEG_A | DISPLAY_7_SEG_B | DISPLAY_7_SEG_C | DISPLAY_7_SEG_E | DISPLAY_7_SEG_F | DISPLAY_7_SEG_G)
#define DISPLAY_7_SEG_CHARACTER_1 (DISPLAY_7_SEG_B | DISPLAY_7_SEG_E)
#define DISPLAY_7_SEG_CHARACTER_2 (DISPLAY_7_SEG_A | DISPLAY_7_SEG_B | DISPLAY_7_SEG_D | DISPLAY_7_SEG_F | DISPLAY_7_SEG_G)
#define DISPLAY_7_SEG_CHARACTER_3 (DISPLAY_7_SEG_A | DISPLAY_7_SEG_B | DISPLAY_7_SEG_D | DISPLAY_7_SEG_E | DISPLAY_7_SEG_G)
#define DISPLAY_7_SEG_CHARACTER_4 (DISPLAY_7_SEG_B | DISPLAY_7_SEG_C | DISPLAY_7_SEG_D | DISPLAY_7_SEG_E)
#define DISPLAY_7_SEG_CHARACTER_5 (DISPLAY_7_SEG_A | DISPLAY_7_SEG_C | DISPLAY_7_SEG_D | DISPLAY_7_SEG_E | DISPLAY_7_SEG_G)
#define DISPLAY_7_SEG_CHARACTER_6 (DISPLAY_7_SEG_A | DISPLAY_7_SEG_C | DISPLAY_7_SEG_D | DISPLAY_7_SEG_E | DISPLAY_7_SEG_F | DISPLAY_7_SEG_G)
#define DISPLAY_7_SEG_CHARACTER_7 (DISPLAY_7_SEG_A | DISPLAY_7_SEG_B | DISPLAY_7_SEG_E)
#define DISPLAY_7_SEG_CHARACTER_8 (DISPLAY_7_SEG_A | DISPLAY_7_SEG_B | DISPLAY_7_SEG_C | DISPLAY_7_SEG_D | DISPLAY_7_SEG_E | DISPLAY_7_SEG_F | DISPLAY_7_SEG_G)
#define DISPLAY_7_SEG_CHARACTER_9 (DISPLAY_7_SEG_A | DISPLAY_7_SEG_B | DISPLAY_7_SEG_C | DISPLAY_7_SEG_D | DISPLAY_7_SEG_E | DISPLAY_7_SEG_G)

// Special Characters Defines

#define DISPLAY_7_SEG_CHARACTER_DOT  (DISPLAY_7_SEG_DP)

// Error Code Defines
#define DISPLAY_7_SEG_OUT_OF_RANGE_ERROR_CODE						(-1)
#define DISPLAY_7_SEG_OUT_OF_MAX_BUFFER_SIZE_ERROR_CODE				(-2)

// API Defines
#define DISPLAY_7_SEG_MAX_CHARACTER_INDEX 							(10)

//**********************************************************************
// Structs
//********************************************************************** 
typedef struct display7segstruct{	
	int *  display7segbuffer;
	int display7segbuffersize;	
} DISPLAY_7_SEG, * DISPLAY_7_SEG_PTR;

//**********************************************************************
// Prototype functions
//********************************************************************** 

// Setters and Getters
void Display7Seg_SetBuffer(DISPLAY_7_SEG_PTR display7seg, int * display7segbuffer);
void Display7Seg_SetBufferSize(DISPLAY_7_SEG_PTR display7seg, int display7segbuffersize );
void Display7Seg_SetBufferByIndex(DISPLAY_7_SEG_PTR display7seg, int index, int data);

int Display7Seg_GetBufferSize(DISPLAY_7_SEG_PTR display7seg);
int Display7Seg_GetBufferByIndex(DISPLAY_7_SEG_PTR display7seg, int index);

// API Functions
void Display7Seg_Setup(DISPLAY_7_SEG_PTR display7seg, int * display7segbuffer, int display7segbuffersize);
void Display7Seg_SendDataInterface(int data);
void  Display7Seg_SendBuffer(DISPLAY_7_SEG_PTR display7seg);
int  Display7Seg_IntParseTo7Seg(int integerData);

#endif /* __DISPLAY_7_SEG_H__ */
