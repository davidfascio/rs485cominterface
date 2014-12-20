#ifndef __UTILS_H__
#define __UTILS_H__

#include "CommonSystemLibraries.h"

int str2uint(char * data, int dataLen, int base);
int char2int(char data);
char * strsearch(char * data,  char pattern);
unsigned int strchecksum(char * data, int dataLen);
void uint2str(int data,char * buffer,int bufferLen);

#endif /* __UTILS_H__ */
