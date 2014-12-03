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

//**********************************************************************
// API Fucntions
//**********************************************************************

void ScreenDotMatrix_Setup(void){
	
	ScreenDotMatrix_Clear();
	DotMatrix_Setup(&dotMatrixControl, SCREEN_DOT_MATRIX_BUFFER, 
					SCREEN_DOT_MATRIX_WIDTH, SCREEN_DOT_MATRIX_HEIGHT);
}

void ScreenDotMatrix_Render(void){
	
	DotMatrix_Update(&dotMatrixControl);
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
