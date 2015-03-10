////////////////////////////////////////////////////////////////////////
//
// File name: Timer.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "Timer.h"

//**********************************************************************
// Variables
//**********************************************************************
TIMER_STRUCT_PTR_ Timer_List[TIMER_MAX_SUPPORTED_NUMBER];
int Timer_Number;
boolean Timer_Interrupt_Event;

//**********************************************************************
// API Fucntions
//**********************************************************************

// Setters and Getters
void Timer_SetCounter(TIMER_STRUCT_PTR_ timer_control, unsigned long int counter){
	
	timer_control->counter = counter;
}

unsigned long int Timer_GetCounter(TIMER_STRUCT_PTR_ timer_control){
	
	return timer_control->counter;
}

void Timer_SetOverflowValue(TIMER_STRUCT_PTR_ timer_control, unsigned long int overflow_value){
	
	timer_control->overflow_value = overflow_value;
}

unsigned long int Timer_GetOverflowValue(TIMER_STRUCT_PTR_ timer_control){
	
	return timer_control->overflow_value;
}

void Timer_SetOverflow(TIMER_STRUCT_PTR_ timer_control, boolean overflow){
	
	timer_control->overflow = overflow;
}

boolean Timer_GetOverflow(TIMER_STRUCT_PTR_ timer_control){
	
	return timer_control->overflow;
}

void Timer_Reset(TIMER_STRUCT_PTR_ timer_control){
	
	Timer_SetCounter(timer_control, 0);
	Timer_SetOverflow(timer_control, FALSE);	
}

//**********************************************************************
// API Functions
//**********************************************************************
void Timer_Setup(void){
	
	
	// API Initialization
	memset(Timer_List, 0, sizeof(Timer_List));
	Timer_Number = 0;
	Timer_Interrupt_Event = FALSE;
	//! bsp function
	bsp_timer_setup(Timer_Event);
}

int AddTimer(TIMER_STRUCT_PTR_ timer_control, unsigned long int overflow_value_in_ms){
	
	unsigned long int overflow_value = TIMER_MIN_VALUE_SUPPORT_IN_MS;
	
	if(Timer_Number >= TIMER_MAX_SUPPORTED_NUMBER)
		return TIMER_MAX_SUPPORTED_NUMBER_OVERFLOW;	
	
	if(overflow_value_in_ms < overflow_value)
		return TIMER_MIN_VALUE_SUPPORT_IN_MS_IS_NOT_SUPPORT;
	
	overflow_value = overflow_value_in_ms / overflow_value;
			
	Timer_Reset(timer_control);
	Timer_SetOverflowValue(timer_control, overflow_value);	
	
	Timer_List[Timer_Number] = timer_control;	
	Timer_Number++;	
		
	return Timer_Number;			
}

unsigned long int Timer_SetOverflowValue_MS(TIMER_STRUCT_PTR_ timer_control, unsigned long int overflow_value_in_ms){
	
	unsigned long int overflow_value = TIMER_MIN_VALUE_SUPPORT_IN_MS;
	
	if(overflow_value_in_ms < overflow_value)
		return TIMER_MIN_VALUE_SUPPORT_IN_MS_IS_NOT_SUPPORT;
	
	overflow_value = overflow_value_in_ms / overflow_value;
			
	Timer_Reset(timer_control);
	Timer_SetOverflowValue(timer_control, overflow_value);	
	
	return overflow_value;
}

void Timer_Update(void){
	
	volatile int index = 0;		
	
	if(Timer_Interrupt_Event == TRUE){
		while(index < Timer_Number) {
			
			// Increase counter number if there isnt overflow status
			if (Timer_List[index]->overflow == FALSE){
				
				Timer_List[index]->counter++;
			}			
			
			// Turn overflow status on
			if (Timer_List[index]->counter >= 
				Timer_List[index]->overflow_value ){
				
				Timer_List[index]->overflow = TRUE;
			}
			
			index++;
		}
		Timer_Interrupt_Event = FALSE;
	}	
}

void Timer_Event(void){
	
	Timer_Interrupt_Event = TRUE;
	Timer_Update();
}
