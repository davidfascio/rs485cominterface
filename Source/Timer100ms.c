////////////////////////////////////////////////////////////////////////
//
// File name: Timer100ms.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "Timer100ms.h"

//**********************************************************************
// Variables
//**********************************************************************
TIMER_100MS_STRUCT_PTR_ Timer100ms_List[TIMER_100MS_MAX_SUPPORTED_NUMBER];
int Timer100ms_Number;

//**********************************************************************
// API Fucntions
//**********************************************************************

// Setters and Getters
void Timer100ms_SetCounter(TIMER_100MS_STRUCT_PTR_ timer_control, int counter){
	
	timer_control->counter = counter;
}

int Timer100ms_GetCounter(TIMER_100MS_STRUCT_PTR_ timer_control){
	
	return timer_control->counter;
}

void Timer100ms_SetOverflowValue(TIMER_100MS_STRUCT_PTR_ timer_control, int overflow_value){
	
	timer_control->overflow_value = overflow_value;
}

int Timer100ms_GetOverflowValue(TIMER_100MS_STRUCT_PTR_ timer_control){
	
	return timer_control->overflow_value;
}

void Timer100ms_SetOverflow(TIMER_100MS_STRUCT_PTR_ timer_control, boolean overflow){
	
	timer_control->overflow = overflow;
}

boolean Timer100ms_GetOverflow(TIMER_100MS_STRUCT_PTR_ timer_control){
	
	return timer_control->overflow;
}

void Timer100ms_Reset(TIMER_100MS_STRUCT_PTR_ timer_control){
	
	Timer100ms_SetCounter(timer_control, 0);
	Timer100ms_SetOverflow(timer_control, FALSE);	
}

//**********************************************************************
// API Functions
//**********************************************************************
void Timer100ms_Setup(void){
	
	
	// API Initialization
	memset(Timer100ms_List, 0, sizeof(Timer100ms_List));
	Timer100ms_Number = 0;
	
	//! bsp function
	bsp_timer100ms_setup(Timer100ms_Update);
}

int AddTimer100ms(TIMER_100MS_STRUCT_PTR_ timer_control, int overflow_value){
	
	if(Timer100ms_Number >= TIMER_100MS_MAX_SUPPORTED_NUMBER)
		return TIMER_100MS_MAX_SUPPORTED_NUMBER_OVERFLOW;	
			
	Timer100ms_Reset(timer_control);
	Timer100ms_SetOverflowValue(timer_control, overflow_value);	
	
	Timer100ms_List[Timer100ms_Number] = timer_control;	
	Timer100ms_Number++;	
		
	return Timer100ms_Number;			
}

void Timer100ms_Update(void){
	
	volatile int index = 0;		
	
	
	while(index < Timer100ms_Number) {
		
		// Increase counter number if there isnt overflow status
		if (Timer100ms_List[index]->overflow == FALSE){
			
			Timer100ms_List[index]->counter++;
		}
		
		
		// Turn overflow status on
		if (Timer100ms_List[index]->counter >= 
			Timer100ms_List[index]->overflow_value ){
			
			Timer100ms_List[index]->overflow = TRUE;
		}
		
		index++;
	}	
}

