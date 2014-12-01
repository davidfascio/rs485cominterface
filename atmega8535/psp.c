////////////////////////////////////////////////////////////////////////
//
// File name: psp.c
//

//**********************************************************************
// Includes
//**********************************************************************
 #include "psp.h"

//**********************************************************************
// Util Functions
//**********************************************************************
int meminvrtncpy(char * BufferDestination, char * BufferSource, long SizeOfBuffers)
{
	char * BufferSourcePointer;
	//if((BufferSource == NULL) || (BufferDestination == NULL) || (SizeOfBuffers <= 0))
	//return -1;	
	
	BufferSourcePointer = BufferSource + SizeOfBuffers - 1;
	
	while(BufferSourcePointer >= BufferSource)
	{
	    *BufferDestination = *BufferSourcePointer;
		
		BufferSourcePointer--;
		BufferDestination++;
	}
	return 1;
}
