////////////////////////////////////////////////////////////////////////
//
// File name: ScreenDotMatrix.c
//

//**********************************************************************
// Includes
//**********************************************************************
#include "ScreenDotMatrix.h"

//**********************************************************************
// Extern Variables
//********************************************************************** 
extern char * FONT_7x6_PTR_;

//**********************************************************************
// Variables
//**********************************************************************
DOT_MATRIX_STRUCT dotMatrixControl;
char SCREEN_DOT_MATRIX_BUFFER [SCREEN_DOT_MATRIX_WIDTH * SCREEN_DOT_MATRIX_HEIGHT];

char ScreenDotMatrixBuffer[SCREEN_DOT_MATRIX_DEFAULT_BUFFER_SIZE];
SCREEN_DOT_MATRIX_EFFECT ScreenDotMatrixEffect ;
int ScreenDotMatrixEffectIndex;
TIMER_STRUCT ScreenDotMatrixTimer;

int estado = LOW;    
//**********************************************************************
// API Fucntions
//**********************************************************************
char * ScreenDotMatrix_GetText(void){
	
	return ScreenDotMatrixBuffer;
}

int ScreenDotMatrix_GetTextLen(void){
	
	return strlen(ScreenDotMatrixBuffer);
}

int ScreenDotMatrix_GetEffect(void){
	
	return (int) ScreenDotMatrixEffect;
}

int ScreenDotMatrix_GetDelay_ms(void){

	return Timer_GetOverflowValue(&ScreenDotMatrixTimer);
}

void ScreenDotMatrix_Setup(void){
	
	ScreenDotMatrix_Clear();
	DotMatrix_Setup(&dotMatrixControl, SCREEN_DOT_MATRIX_BUFFER, 
					SCREEN_DOT_MATRIX_WIDTH, SCREEN_DOT_MATRIX_HEIGHT);
					
	memset(ScreenDotMatrixBuffer, 0, sizeof(ScreenDotMatrixBuffer));
	ScreenDotMatrixEffect = STATIC_TEXT;
	ScreenDotMatrixEffectIndex = 0;
	AddTimer(&ScreenDotMatrixTimer, SCREEN_DOT_MATRIX_DEFAULT_TIMER_VALUE_IN_MS);	
	
	bsp_pin_mode(BSP_PIN_A1, OUTPUT);		
	bsp_io_write(BSP_PIN_A1, estado);		
}

void ScreenDotMatrix_Render(void){
	
	DotMatrix_Update(&dotMatrixControl);
	
	if(ScreenDotMatrixEffect == STATIC_TEXT)
		return;
		
	if(Timer_GetOverflow(&ScreenDotMatrixTimer) == TRUE){				
			
		ScreenDotMatrix_Clear();		
		ScreenDotMatrix_DrawText(ScreenDotMatrixBuffer,ScreenDotMatrixEffectIndex,0,FONT_7x6, FONT_7x6_WIDTH, FONT_7x6_HEIGHT);

		if (ScreenDotMatrixEffect == DYNAMIC_LEFT){
			
			if(ScreenDotMatrixEffectIndex <  SCREEN_DOT_MATRIX_MINIMUM_POS_LIMIT_ON_X(strlen(ScreenDotMatrixBuffer)))
				ScreenDotMatrixEffectIndex = SCREEN_DOT_MATRIX_MAXIMUM_POS_LIMIT_ON_X() ;
			else
				--ScreenDotMatrixEffectIndex;
			
		} else {
			if(ScreenDotMatrixEffectIndex >  SCREEN_DOT_MATRIX_MAXIMUM_POS_LIMIT_ON_X() )
				ScreenDotMatrixEffectIndex = SCREEN_DOT_MATRIX_MINIMUM_POS_LIMIT_ON_X(strlen(ScreenDotMatrixBuffer));
			else
				++ScreenDotMatrixEffectIndex; 								
		}	
		
		estado = (estado == LOW )? HIGH : LOW;
		bsp_io_write(BSP_PIN_A1, estado);		
		
		
		Timer_Reset(&ScreenDotMatrixTimer);
	}
}

void ScreenDotMatrix_Clear(void){
	
	memset(SCREEN_DOT_MATRIX_BUFFER, 0x00, sizeof(SCREEN_DOT_MATRIX_BUFFER));
}

void ScreenDotMatrix_Draw(	 char flash * img, int width_pixels, int height_pixels, 
							int x_pixels, int y_pixels){

	int w_bytes = width_pixels / 8;
	char * address;
	char img_data;	
	int x_offset = x_pixels % 8;
	int w_offset = width_pixels % 8;
	
	char low_data, high_data;
	char low_mask, high_mask;	
	int h_index, w_index, k;	
	
	for (h_index = y_pixels, k = 0; h_index < height_pixels; h_index ++, k++){
		
		if( h_index >= SCREEN_DOT_MATRIX_HEIGHT || h_index < 0 )
			continue;		
		
		for (w_index = 0; w_index < (w_offset ? w_bytes + 1: w_bytes); w_index++){		
			
			if((x_pixels + w_index * 8 ) >= (SCREEN_DOT_MATRIX_WIDTH * 8) ||
			   (x_pixels + w_index * 8 ) < 0 )
				continue;
			
			address = ScreenDotMatrix_GetByteAddressByPosition((x_pixels + w_index * 8 ), h_index);
			
			img_data = img [w_bytes * k + w_index] ;
			
			if(x_offset){
				low_data = img_data >> (x_offset);
				low_mask = 0xFF >> (x_offset);
				high_data = img_data << (8-x_offset);
				high_mask = 0xFF << (8-x_offset);
				*address = ( *address & high_mask) | (low_data & low_mask);
								
				if((x_pixels + w_index * 8  + 8) < (SCREEN_DOT_MATRIX_WIDTH * 8) )
					*(address + 1) |= (*(address + 1) & low_mask) | (high_data & high_mask);		
			} else {
				
				*address = img_data;
			}
		}		
	}		
}

char * ScreenDotMatrix_GetByteAddressByPosition(int x_pixels, int y_pixels){
	
	int x_bytes = x_pixels/8;		
	return SCREEN_DOT_MATRIX_BUFFER + x_bytes + y_pixels * SCREEN_DOT_MATRIX_WIDTH;
}


void ScreenDotMatrix_DrawText(char * text, int x_pixel, int y_pixel, char flash * font, int font_width, 
							  int font_height){
	int index = 0;
	char current_char;
	int current_x_pixel = x_pixel;
								  
	while(text[index] != '\0'){
		
		current_char = text[index] - FONTS_MINIMUM_ASCII_CHARACTER_TO_SHOW;
		
		if(current_char < 0 || current_char > (FONTS_MAXIMUM_ASCII_CHARACTER_TO_SHOW - FONTS_MINIMUM_ASCII_CHARACTER_TO_SHOW) ){
			++index;
			continue;
		}
		
		if(current_x_pixel >= SCREEN_DOT_MATRIX_WIDTH * 8)
			break;
		
		if(current_x_pixel + (font_width -1) >= 0 ){ // font_width 
			
			ScreenDotMatrix_Draw(font + (
			((font_width % 8) ? font_width / 8 + 1 : font_width / 8 )* font_height * current_char), 
			font_width, font_height, current_x_pixel, y_pixel);
		}
		
		current_x_pixel += (font_width -1); // font_width 
		++index;	
	}
 }


int ScreenDotMatrix_SendTextWithCustomDelay(char *text, int textLen, SCREEN_DOT_MATRIX_EFFECT effect, int delay_in_ms){
	
	switch(effect){
		
		case STATIC_TEXT:
		case DYNAMIC_LEFT:
		case DYNAMIC_RIGHT:
			
			if(textLen >= sizeof(ScreenDotMatrixBuffer))
				return SCREEN_DOT_MATRIX_NO_ENOUGH_BUFFER_RESOURCES;

			ScreenDotMatrixEffect = effect;	
			ScreenDotMatrix_Clear();		

			memset(ScreenDotMatrixBuffer, 0, sizeof(ScreenDotMatrixBuffer));			
			memcpy( ScreenDotMatrixBuffer, text , textLen);	
			
			break;
		default:
			return SCREEN_DOT_MATRIX_BAD_EFFECT;
	}
	
	
	if (effect == STATIC_TEXT) { 				
		ScreenDotMatrix_DrawText(ScreenDotMatrixBuffer,SCREEN_DOT_MATRIX_DEFAULT_OFFSET_ON_X,0,FONT_7x6, FONT_7x6_WIDTH, FONT_7x6_HEIGHT);
	}
	else {		
		ScreenDotMatrixEffectIndex = (ScreenDotMatrixEffect == DYNAMIC_LEFT) ? SCREEN_DOT_MATRIX_MAXIMUM_POS_LIMIT_ON_X() : SCREEN_DOT_MATRIX_MINIMUM_POS_LIMIT_ON_X(strlen(ScreenDotMatrixBuffer));     
	}
	
	
	
	Timer_SetOverflowValue_MS(&ScreenDotMatrixTimer, delay_in_ms);		
	
	return SCREEN_DOT_MATRIX_NO_ERROR;	
}

int ScreenDotMatrix_SendText(char *text, int textLen, SCREEN_DOT_MATRIX_EFFECT effect){		
	
	return ScreenDotMatrix_SendTextWithCustomDelay(text, textLen, effect, SCREEN_DOT_MATRIX_DEFAULT_TIMER_VALUE_IN_MS);	
}
