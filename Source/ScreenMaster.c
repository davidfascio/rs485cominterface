////////////////////////////////////////////////////////////////////////
//
// File name: ScreenMaster.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenMaster.h"

//**********************************************************************
// LOCAL VARIABLES
//**********************************************************************
SCREEN_FOREIGN_MASTER_STRUCT ForeignMasterMessagesControl;

int ForeignMasterMessagesControl_ForeignRefreshCounter = 0;
int ForeignMasterMessagesControl_ForeignCounter = 0;

TIMER_STRUCT ForeignMasterMessagesControl_Timer;

char ForeignMasterMessagesControl_ForexAddress 			= SCREEN_MASTER_DEFAULT_FOREX_ADDRESS;
char ForeignMasterMessagesControl_SellAddress 			= SCREEN_MASTER_DEFAULT_SELL_ADDRESS;
char ForeignMasterMessagesControl_BuyAddress 			= SCREEN_MASTER_DEFAULT_BUY_ADDRESS;
char ForeignMasterMessagesControl_InvestmentRateAddress = SCREEN_MASTER_DEFAULT_INVESTMENT_RATE_ADDRESS;

//**********************************************************************
// SCREEN_FOREIGN_STRUCT Setters
//**********************************************************************
void Foreign_SetForexMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl, char * message, int messageLen, int messageEffect, int messageEffectRate){
	
	// NULL Validation
	if(message == NULL)
		return;
		
	// Size Validation 
	if(messageLen >= SCREEN_MASTER_MAX_FOREX_MESSAGE_SIZE)
		return;
		
	// Copy the contents of message inside foreignControl memory location
	memset(foreignControl->forexMessage.message, 0, SCREEN_MASTER_MAX_FOREX_MESSAGE_SIZE);
	memcpy(foreignControl->forexMessage.message, message, messageLen); //XD
	
	foreignControl->forexMessage.messageLen = messageLen;
	
	foreignControl->forexMessage.messageEffect = messageEffect;
	
	foreignControl->forexMessage.messageEffectRate = messageEffectRate;
}

void Foreign_SetSellMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl, char * message, int messageLen){
	
	// NULL Validation
	if(message == NULL)
		return;
		
	// Size Validation 
	if(messageLen >= SCREEN_MASTER_MAX_NUM_MESSAGE_SIZE)
		return;
		
	// Copy the contents of message inside foreignControl memory location
	memset(foreignControl->sellMessage.message, 0, SCREEN_MASTER_MAX_NUM_MESSAGE_SIZE);
	memcpy(foreignControl->sellMessage.message, message, messageLen); //XD
	
	foreignControl->sellMessage.messageLen = messageLen;
}

void Foreign_SetBuyMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl, char * message, int messageLen){

	// NULL Validation
	if(message == NULL)
		return;
		
	// Size Validation 
	if(messageLen >= SCREEN_MASTER_MAX_NUM_MESSAGE_SIZE)
		return;
		
	// Copy the contents of message inside foreignControl memory location
	memset(foreignControl->buyMessage.message, 0, SCREEN_MASTER_MAX_NUM_MESSAGE_SIZE);
	memcpy(foreignControl->buyMessage.message, message, messageLen); //XD
	
	foreignControl->buyMessage.messageLen = messageLen;
}

//**********************************************************************
// SCREEN_FOREIGN_STRUCT Getters
//**********************************************************************
DOT_MATRIX_MESSAGE_STRUCT_PTR_  Foreign_GetForexMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl){
	
	return 	&foreignControl->forexMessage;
}

NUM_DISPLAY_MESSAGE_STRUCT_PTR_ Foreign_GetSellMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl){

	return &foreignControl->sellMessage;
}

NUM_DISPLAY_MESSAGE_STRUCT_PTR_ Foreign_GetBuyMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl){
	
	return &foreignControl->buyMessage;
}


//**********************************************************************
// SCREEN_FOREIGN_MASTER_STRUCT Setters
//**********************************************************************
void ForeignMaster_SetUUID(int uuid){
	
	
	ForeignMasterMessagesControl.uuid = uuid;
}

void ForeignMaster_AddForeignMessage(SCREEN_FOREIGN_STRUCT_PTR_ foreignControl){

	if(foreignControl == NULL)
		return;
	
	if(ForeignMasterMessagesControl_ForeignCounter >= SCREEN_MASTER_MAX_MASTER_MESSAGE_SIZE)
		return;
		
	memcpy(	&ForeignMasterMessagesControl.foreignMessages[ForeignMasterMessagesControl_ForeignCounter],
			foreignControl, 
			sizeof(SCREEN_FOREIGN_STRUCT));
	
	ForeignMasterMessagesControl_ForeignCounter++;		
}

void ForeignMaster_Clear(){
	
	memset(&ForeignMasterMessagesControl, 0, sizeof(SCREEN_FOREIGN_MASTER_STRUCT));
}

void ForeignMaster_SetInvestmentRateMessage( char * message, int messageLen){
	
	// NULL Validation
	if(message == NULL)
		return;
		
	// Size Validation 
	if(messageLen >= SCREEN_MASTER_MAX_NUM_MESSAGE_SIZE)
		return;
		
	// Copy the contents of message inside foreignControl memory location
	memset(ForeignMasterMessagesControl.investmentRateMessage.message, 0, SCREEN_MASTER_MAX_NUM_MESSAGE_SIZE);
	memcpy(ForeignMasterMessagesControl.investmentRateMessage.message, message, messageLen); //XD	
	
	ForeignMasterMessagesControl.investmentRateMessage.messageLen = messageLen;
}

void ForeignMaster_SetRefreshRate_ms(unsigned long int refreshRate){

	ForeignMasterMessagesControl.refreshRate = refreshRate;
}

//**********************************************************************
// SCREEN_FOREIGN_MASTER_STRUCT Getters
//**********************************************************************
int ForeignMaster_GetUUID(){
	
	return ForeignMasterMessagesControl.uuid;
}

SCREEN_FOREIGN_STRUCT_PTR_ ForeignMaster_GetForeignMessageByIndex(int index){
	
	return & ForeignMasterMessagesControl.foreignMessages[index];
}

NUM_DISPLAY_MESSAGE_STRUCT_PTR_ ForeignMaster_GetInvestmentRateMessage(){

	return & ForeignMasterMessagesControl.investmentRateMessage;
}

unsigned long int ForeignMaster_GetRefreshRate_ms(){

	return ForeignMasterMessagesControl.refreshRate;
}

//**********************************************************************
// SCREEN_FOREIGN_MASTER_STRUCT API
//**********************************************************************

void  ForeignMaster_Setup(void){

	ForeignMaster_Clear();
	
	/**********************************************/
	
	// Another configuration process over HERE
	
	/**********************************************/
	
	// DEFAULT VALUES ¬¬¡
	ForeignMaster_SetRefreshRate_ms(SCREEN_MASTER_DEFAULT_REFRESH_RATE_IN_MS);
	
	AddTimer(&ForeignMasterMessagesControl_Timer, ForeignMaster_GetRefreshRate_ms());
	
	test();
}

void  ForeignMaster_Update(void){
	
	if(Timer_GetOverflow(&ForeignMasterMessagesControl_Timer) == FALSE)
		return;
	
	
	Timer_Reset(&ForeignMasterMessagesControl_Timer);
	
	if(ForeignMasterMessagesControl_ForeignCounter == 0)	
		return;
	
	ForeignMaster_Refresh();
	
}



void ForeignMaster_Refresh(void){
	
	SCREEN_FOREIGN_STRUCT_PTR_  foreignControl;
	
	if(	ForeignMasterMessagesControl_ForeignRefreshCounter >= 
		ForeignMasterMessagesControl_ForeignCounter)
	
		ForeignMasterMessagesControl_ForeignRefreshCounter = 0;
		
	
	foreignControl = ForeignMaster_GetForeignMessageByIndex(ForeignMasterMessagesControl_ForeignRefreshCounter);	
	
	
	ForeignMaster_SendDotMatrixMessage(Foreign_GetForexMessage(foreignControl), 	ForeignMasterMessagesControl_ForexAddress);
	ForeignMaster_SendNumDisplayMessage(Foreign_GetBuyMessage(foreignControl), 		ForeignMasterMessagesControl_BuyAddress);
	ForeignMaster_SendNumDisplayMessage(Foreign_GetSellMessage(foreignControl), 	ForeignMasterMessagesControl_SellAddress);
	ForeignMaster_SendNumDisplayMessage(ForeignMaster_GetInvestmentRateMessage(), 	ForeignMasterMessagesControl_InvestmentRateAddress);
	
	ForeignMasterMessagesControl_ForeignRefreshCounter++;	
}



int ForeignMaster_SendDotMatrixMessage( DOT_MATRIX_MESSAGE_STRUCT_PTR_ dotMatrixMessageControl, char dotMatrixMessageAddress){

	char dotMatrixParameters [100];	
	char * 	dotMatrixParametersIndex = dotMatrixParameters;
		
	memset(dotMatrixParametersIndex, 0, sizeof(dotMatrixParameters));		
	memcpy(dotMatrixParametersIndex, (char *) &dotMatrixMessageControl->messageEffect, sizeof(dotMatrixMessageControl->messageEffect));		
	dotMatrixParametersIndex += sizeof(dotMatrixMessageControl->messageEffect);
	
	memcpy(dotMatrixParametersIndex, (char * ) &dotMatrixMessageControl->messageEffectRate, sizeof(dotMatrixMessageControl->messageEffectRate));				
	dotMatrixParametersIndex += sizeof(dotMatrixMessageControl->messageEffectRate);
	
	memcpy(dotMatrixParametersIndex, dotMatrixMessageControl->message, dotMatrixMessageControl->messageLen);				
	dotMatrixParametersIndex += dotMatrixMessageControl->messageLen;
		
	return ScreenDisplayProtocol_SendDataPackWaitForResponse( 	dotMatrixMessageAddress, 
																SCREEN_DOT_MATRIX_DEVICE_MASTER_COMMAND_ID_SEND_TEXT_DELAY, 
																dotMatrixParameters, 
																dotMatrixParametersIndex - dotMatrixParameters, 
																SCREEN_DOT_MATRIX_DEVICE_SLAVE_COMMAND_ID_SEND_TEXT_DELAY, 
																SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT, 
																SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES);																
}

int ForeignMaster_SendNumDisplayMessage( NUM_DISPLAY_MESSAGE_STRUCT_PTR_ numDisplayMessageControl, char numDisplayMessageAddress){

	char numDisplayParameters [20];	
	char * 	numDisplayParametersIndex = numDisplayParameters;
		
	memset(numDisplayParametersIndex, 0, sizeof(numDisplayParameters));		
	
	memcpy(numDisplayParametersIndex, numDisplayMessageControl->message, numDisplayMessageControl->messageLen);				
	numDisplayParametersIndex += numDisplayMessageControl->messageLen;

	return ScreenDisplayProtocol_SendDataPackWaitForResponse(	numDisplayMessageAddress, 
																SCREEN_DISPLAY_DEVICE_MASTER_COMMAND_ID_FLOAT_VALUE_UPDATE, 
																numDisplayParameters, 
																numDisplayParametersIndex - numDisplayParameters, 
																SCREEN_DISPLAY_DEVICE_SLAVE_COMMAND_ID_FLOAT_VALUE_UPDATE, 
																SCREEN_DISPLAY_PROTOCOL_WAIT_TIME_OUT, 
																SCREEN_DISPLAY_PROTOCOL_WAIT_RESPONSE_DEFAULT_RETIES);
}





void test (void){
	
	SCREEN_FOREIGN_STRUCT bla;
	
	Foreign_SetForexMessage(&bla, "Euro", strlen("Euro"), 1, 100);
	Foreign_SetBuyMessage(&bla, "17.50", strlen("17.50"));
	Foreign_SetSellMessage(&bla, "17.00", strlen("17.00"));			
	ForeignMaster_AddForeignMessage(&bla);
	
	Foreign_SetForexMessage(&bla, "DOLARES", strlen("DOLARES"), 1, 100);
	Foreign_SetBuyMessage(&bla, "14.50", strlen("14.50"));
	Foreign_SetSellMessage(&bla, "14.00", strlen("14.00"));	
	ForeignMaster_AddForeignMessage(&bla);
	
	
	Foreign_SetForexMessage(&bla, "Plata Libertad", strlen("Plata Libertad"), 1, 100);
	Foreign_SetBuyMessage(&bla, "54.50", strlen("54.50"));
	Foreign_SetSellMessage(&bla, "54.00", strlen("54.00"));	
	ForeignMaster_AddForeignMessage(&bla);
	
	Foreign_SetForexMessage(&bla, "DOLAR CAD", strlen("DOLAR CAD"), 2, 100);
	Foreign_SetBuyMessage(&bla, "14.50", strlen("14.50"));
	Foreign_SetSellMessage(&bla, "14.00", strlen("14.00"));	
	ForeignMaster_AddForeignMessage(&bla);
	
	
	Foreign_SetForexMessage(&bla, "CENTENARIO", strlen("CENTENARIO"), 2, 100);
	Foreign_SetBuyMessage(&bla, "7000.50", strlen("7000.50"));
	Foreign_SetSellMessage(&bla, "7000.00", strlen("7000.00"));	
	ForeignMaster_AddForeignMessage(&bla);
	
	ForeignMaster_SetInvestmentRateMessage("4.5", strlen("4.5"));
}
