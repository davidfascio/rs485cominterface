/*
 * File: Utils.h
 * Author: fascio
 * 
 * Created on December 15th, 2014, 15:09
 */ 

#ifndef __UTILS_H__
#define __UTILS_H__

//**********************************************************************
// Includes
//**********************************************************************
//#include "CommonSystemLibraries.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//**********************************************************************
// API Prototype Fucntions
//**********************************************************************
int str2uint(char * data, int dataLen, int base);
int char2int(char data);
char * strsearch(char * data,  char pattern);
unsigned int strchecksum(char * data, int dataLen);
void uint2str(int data,char * buffer,int bufferLen);
void strappendchar(char * buffer, int bufferLen, char data);

#endif /* __UTILS_H__ */
