/*
 * File: TcpComInterface.h
 * Author: fascio
 * 
 * Created on March 11th, 2015, 10:21 
 */ 
 
#ifndef __TCP_COM_INTERFACE__
#define __TCP_COM_INTERFACE__

//**********************************************************************
// Includes
//**********************************************************************

#include "CommonSystemLibraries.h"

//**********************************************************************
// Defines
//**********************************************************************
#define NETBURNER_SBL2E_TCP_RST									BSP_PIN_D4
#define NETBURNER_SBL2E_TCP_RST_ON								(LOW)
#define NETBURNER_SBL2E_TCP_RST_OFF								(HIGH)


void TCPComInterface_Setup(void);
int TCPComInterface_Read(char * data, int data_lenght);
int TCPComInterface_Write(char * data, int data_lenght);

void TCPComInterface_CallBackFromSendingProcess(void);



#endif /* __TCP_COM_INTERFACE__ */
