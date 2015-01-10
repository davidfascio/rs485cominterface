/*
 * File: System.h
 * Author: fascio
 * 
 * Created on January 9th, 2015, 11:53
 */ 

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "bsp.h"
#include "psp.h"
#include "Timer.h"

#define SYSTEM_LED_INDICATOR_STATUS							(BSP_PIN_C0) // Temporally
#define SYSTEM_LED_INDICATOR_STATUS_DELAY_IN_MS				(500)
//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
void System_Setup(void);
void System_Update(void);

#endif /* __SYSTEM_H__ */
