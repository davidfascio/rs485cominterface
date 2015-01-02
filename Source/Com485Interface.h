/*
 * File: Com485Interface.h
 * Author: fascio
 * 
 * Created on December 12th, 2014, 16:02
 */ 
 
#ifndef __COM_485_INTERFACE_H__
#define __COM_485_INTERFACE_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "CommonSystemLibraries.h"

//**********************************************************************
// Defines
//**********************************************************************
#define COM_485_INTERFACE_ENALE_TRANSMITION						BSP_PIN_A3//BSP_PIN_D2
#define COM_485_INTERFACE_TX_ON									HIGH
#define COM_485_INTERFACE_TX_OFF								LOW

void Com485Interface_Setup(void);
int Com485Interface_Read(char * DataReceiveBuffer, int DataLen);
int Com485Interface_Write(char * DataToSend, int DataLen);

void Com485Interface_RestoreReception(void);


#endif /* __COM_485_INTERFACE_H__ */
