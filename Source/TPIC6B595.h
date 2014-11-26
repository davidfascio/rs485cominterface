/*
 * File: TPIC6B595.h
 * Author: fascio
 * 
 * Created on November 12th, 2014, 12:25
 */ 

#ifndef __TPIC6B595_H__
#define __TPIC6B595_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "CommonSystemLibraries.h"

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

//**********************************************************************
// Defines
//**********************************************************************

#define TPIC6B595_STR_PIN  (BSP_PIN_A0)

// Pinout 7 Segments Defines
#define DISPLAY_7_SEG_A			(0x02)
#define DISPLAY_7_SEG_B			(0x01)
#define DISPLAY_7_SEG_C			(0x20)
#define DISPLAY_7_SEG_D			(0x10)
#define DISPLAY_7_SEG_E			(0x04)
#define DISPLAY_7_SEG_F			(0x40)
#define DISPLAY_7_SEG_G			(0x08)
#define DISPLAY_7_SEG_DP		(0x80)

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void TPIC6B595_Setup(void);
void TPIC6B595_SendData(int data);

void TPIC6B595_HideData();
void TPIC6B595_ShowData();

#endif /* __TPIC6B595_H__ */
