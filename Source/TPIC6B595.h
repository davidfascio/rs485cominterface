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

//**********************************************************************
// Defines
//**********************************************************************
#define TPIC6B595_STR_PIN  (BSP_PIN_A0)

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void TPIC6B595_Setup(void);

void TPIC6B595_HideData();
void TPIC6B595_ShowData();

void TPIC6B595_SendBuffer(char * buffer, char bufferLen);
void TPIC6B595_Clear(char bufferLen);

void TPIC6B595_WriteData(char data);

#endif /* __TPIC6B595_H__ */
