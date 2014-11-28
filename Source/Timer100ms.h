/*
 * File: Timer100ms.h
 * Author: fascio
 * 
 * Created on November 27th, 2014, 6:35
 */ 

#ifndef __TIMER_100MS_H__
#define __TIMER_100MS_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "CommonSystemLibraries.h"

//**********************************************************************
// Defines
//**********************************************************************
#define TIMER_100MS_MAX_SUPPORTED_NUMBER						  	(4)
#define TIMER_100MS_MAX_SUPPORTED_NUMBER_OVERFLOW				 	(-1)

//**********************************************************************
// Structures 
//**********************************************************************
typedef struct timer100ms_struct{
	int counter;
	int overflow_value;
	boolean overflow;
	/*int (*timerFunctionToCall)(void);*/		
} TIMER_100MS_STRUCT, * TIMER_100MS_STRUCT_PTR_;


//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

// Setters and Getters prototype functions
void Timer100ms_SetCounter(TIMER_100MS_STRUCT_PTR_ timer_control, int counter);
int Timer100ms_GetCounter(TIMER_100MS_STRUCT_PTR_ timer_control);

void Timer100ms_SetOverflowValue(TIMER_100MS_STRUCT_PTR_ timer_control, int overflow_value);
int Timer100ms_GetOverflowValue(TIMER_100MS_STRUCT_PTR_ timer_control);

void Timer100ms_SetOverflow(TIMER_100MS_STRUCT_PTR_ timer_control, boolean overflow);
boolean Timer100ms_GetOverflow(TIMER_100MS_STRUCT_PTR_ timer_control);

void Timer100ms_Reset(TIMER_100MS_STRUCT_PTR_ timer_control);

// API Prototype
void Timer100ms_Setup(void);
int AddTimer100ms(TIMER_100MS_STRUCT_PTR_ timer_control, int overflow_value);
void Timer100ms_Update(void);

#endif /* #ifndef __TIMER_100MS_H__ */
