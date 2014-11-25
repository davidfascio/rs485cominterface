/*
 * File: psp.h
 * Author: fascio
 * 
 * Created on November 20th, 2014, 09:34
 */ 
 
#ifndef __PSP_H__
#define __PSP_H__

//**********************************************************************
// Includes
//**********************************************************************
#ifdef __ATMEGA_1284P__
#include <mega1284p.h>
#endif /* #ifdef __ATMEGA_1284P__ */


//**********************************************************************
// Vartypes
//**********************************************************************
typedef char 	boolean;

//**********************************************************************
// Defines
//**********************************************************************
#define TRUE  														(1)
#define FALSE  														(0)

//**********************************************************************
// Util Prototype Functions
//**********************************************************************
int meminvrtncpy(char * BufferDestination, char * BufferSource, long SizeOfBuffers);


//**********************************************************************
// Util Functions
//**********************************************************************
int meminvrtncpy(char * BufferDestination, char * BufferSource, long SizeOfBuffers)
{
	char * BufferSourcePointer;
	if((BufferSource == NULL) || (BufferDestination == NULL) || (SizeOfBuffers <= 0))
	return -1;
	
	
	BufferSourcePointer = BufferSource + SizeOfBuffers - 1;
	
	while(BufferSourcePointer >= BufferSource)
	{
	    *BufferDestination = *BufferSourcePointer;
		
		BufferSourcePointer--;
		BufferDestination++;
	}
	return 1;
}

#endif /* __PSP_H__ */
