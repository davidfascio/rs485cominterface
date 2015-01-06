/*
 * File: SN54LS145N.h
 * Author: fascio
 * 
 * Created on November 28th, 2014, 15:22
 */ 

#ifndef __SN54LS145N_H__
#define __SN54LS145N_H__

//**********************************************************************
// Includes
//**********************************************************************
#include "CommonSystemLibraries.h"

//**********************************************************************
// Defines
//**********************************************************************

#define SN54LS145N_PIN_A  									(BSP_PIN_A4)/*(BSP_PIN_a4)*/
#define SN54LS145N_PIN_B  									(BSP_PIN_A5)/*(BSP_PIN_D4)*/
#define SN54LS145N_PIN_C  									(BSP_PIN_A6)/*(BSP_PIN_D5)*/
#define SN54LS145N_PIN_D  									(BSP_PIN_A7)/*(BSP_PIN_D6)*/

#define SN54LS145N_CLEAR_DATA									  (0x0F)


//**********************************************************************
// API Prototype Fucntions
//**********************************************************************

void SN54LS145N_Setup(void);
void SN54LS145N_ClearData(void);
void SN54LS145N_SendData(char data);


#endif /* __SN54LS145N_H__ */
