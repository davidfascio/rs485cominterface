/*
 * File: ScreenMaster.h
 * Author: fascio
 * 
 * Created on March 11th, 2015, 16:15
 */ 


#ifndef __SCREEN_MASTER_H__
#define __SCREEN_MASTER_H__

// **********************************************************************
// Includes
//**********************************************************************

#include "CommonSystemLibraries.h"
#include "Timer.h"

#include "ScreenDisplayProtocol.h"
#include "ScreenDisplayDeviceCommandList.h"

//**********************************************************************
// Defines
//**********************************************************************

// Size defines
#define SCREEN_MASTER_MAX_FOREX_MESSAGE_SIZE					(50)
#define SCREEN_MASTER_MAX_NUM_MESSAGE_SIZE						(10)
#define SCREEN_MASTER_MAX_MASTER_MESSAGE_SIZE					(20)

// Configuration defines
#define SCREEN_MASTER_DEFAULT_REFRESH_RATE_IN_MS				(10000) // Customizable

#define SCREEN_MASTER_DEFAULT_FOREX_ADDRESS						(0x11) // Customizable
#define SCREEN_MASTER_DEFAULT_BUY_ADDRESS						(0x12) // Customizable
#define SCREEN_MASTER_DEFAULT_SELL_ADDRESS						(0x13) // Customizable
#define SCREEN_MASTER_DEFAULT_INVESTMENT_RATE_ADDRESS			(0x14) // Customizable





//**********************************************************************
// Vartypes
//**********************************************************************

typedef struct dot_matrix_message_struct{	

	char message[SCREEN_MASTER_MAX_FOREX_MESSAGE_SIZE];
	int  messageLen;		
	int  messageEffect;
	int  messageEffectRate;

} DOT_MATRIX_MESSAGE_STRUCT, * DOT_MATRIX_MESSAGE_STRUCT_PTR_;


typedef struct num_display_message_struct{	

	char message[SCREEN_MASTER_MAX_NUM_MESSAGE_SIZE];
	int  messageLen;			

} NUM_DISPLAY_MESSAGE_STRUCT, * NUM_DISPLAY_MESSAGE_STRUCT_PTR_;


typedef struct foreign_struct{	
		
	DOT_MATRIX_MESSAGE_STRUCT 	forexMessage;
	NUM_DISPLAY_MESSAGE_STRUCT 	sellMessage;
	NUM_DISPLAY_MESSAGE_STRUCT	buyMessage;		
	
} SCREEN_FOREIGN_STRUCT, * SCREEN_FOREIGN_STRUCT_PTR_;


typedef struct screen_master_struct{	

	int uuid;
	SCREEN_FOREIGN_STRUCT foreignMessages[SCREEN_MASTER_MAX_MASTER_MESSAGE_SIZE];
	NUM_DISPLAY_MESSAGE_STRUCT investmentRateMessage;	
	unsigned long int refreshRate;
	
} SCREEN_FOREIGN_MASTER_STRUCT, * SCREEN_FOREIGN_MASTER_STRUCT_PTR_;


// SCREEN_FOREIGN_STRUCT Setters
void Foreign_SetForexMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl, char * message, int messageLen, int messageEffect, int messageEffectRate);
void Foreign_SetSellMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl, char * message, int messageLen);
void Foreign_SetBuyMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl, char * message, int messageLen);

// SCREEN_FOREIGN_STRUCT Getters
DOT_MATRIX_MESSAGE_STRUCT_PTR_  Foreign_GetForexMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl);
NUM_DISPLAY_MESSAGE_STRUCT_PTR_ Foreign_GetSellMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl);
NUM_DISPLAY_MESSAGE_STRUCT_PTR_ Foreign_GetBuyMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl);


// SCREEN_FOREIGN_MASTER_STRUCT Setters
void ForeignMaster_SetUUID(int uuid);

void ForeignMaster_AddForeignMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl);
void ForeignMaster_Clear();

void ForeignMaster_SetInvestmentRateMessage(char * message, int messageLen);

void ForeignMaster_SetRefreshRate_ms(unsigned long int refreshRate);

// SCREEN_FOREIGN_MASTER_STRUCT Getters
int ForeignMaster_GetUUID();

SCREEN_FOREIGN_STRUCT_PTR_ ForeignMaster_GetForeignMessageByIndex( int index);

NUM_DISPLAY_MESSAGE_STRUCT_PTR_ ForeignMaster_GetInvestmentRateMessage();

unsigned long int ForeignMaster_GetRefreshRate_ms();

//**********************************************************************
// SCREEN_FOREIGN_MASTER_STRUCT API
//**********************************************************************

void  ForeignMaster_Setup(void);
void  ForeignMaster_Update(void);
void  ForeignMaster_Refresh(void);

int ForeignMaster_SendDotMatrixMessage( DOT_MATRIX_MESSAGE_STRUCT_PTR_ dotMatrixMessageControl, char dotMatrixMessageAddress);
int ForeignMaster_SendNumDisplayMessage( NUM_DISPLAY_MESSAGE_STRUCT_PTR_ numDisplayMessageControl, char numDisplayMessageAddress);

void test (void);
 
#endif /* __SCREEN_MASTER_H__ */
