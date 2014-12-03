/*
 * File: Timer100ms.h
 * Author: fascio
 * 
 * Created on November 27th, 2014, 6:35
 */ 

#ifndef __TIMER_H__
#define __TIMER_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "CommonSystemLibraries.h"

//**********************************************************************
// Defines
//**********************************************************************

#define TIMER_MAX_SUPPORTED_NUMBER						  	(4)

#ifdef 	__TIMER_MIN_VALUE_SUPPORT_1_MS__
#define TIMER_MIN_VALUE_SUPPORT_IN_MS						(1)
#else
#define TIMER_MIN_VALUE_SUPPORT_IN_MS						(100)
#endif  /*TIMER_MIN_VALUE_SUPPORT_IN_MS*/

//Error defines
#define TIMER_MAX_SUPPORTED_NUMBER_OVERFLOW				 	(-1)
#define TIMER_MIN_VALUE_SUPPORT_IN_MS_IS_NOT_SUPPORT	 	(-2)

//**********************************************************************
// Structures 
//**********************************************************************
typedef struct timer_struct{
	int counter;
	int overflow_value;
	boolean overflow;		
} TIMER_STRUCT, * TIMER_STRUCT_PTR_;


//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

// Setters and Getters prototype functions
void Timer_SetCounter(TIMER_STRUCT_PTR_ timer_control, int counter);
int Timer_GetCounter(TIMER_STRUCT_PTR_ timer_control);

void Timer_SetOverflowValue(TIMER_STRUCT_PTR_ timer_control, int overflow_value);
int Timer_GetOverflowValue(TIMER_STRUCT_PTR_ timer_control);

void Timer_SetOverflow(TIMER_STRUCT_PTR_ timer_control, boolean overflow);
boolean Timer_GetOverflow(TIMER_STRUCT_PTR_ timer_control);

void Timer_Reset(TIMER_STRUCT_PTR_ timer_control);

// API Prototype
void Timer_Setup(void);
int AddTimer(TIMER_STRUCT_PTR_ timer_control, int overflow_value_in_ms);
int Timer_SetOverflowValue_MS(TIMER_STRUCT_PTR_ timer_control, int overflow_value_in_ms);
void Timer_Update(void);

#endif /* #ifndef __TIMER_H__ */
