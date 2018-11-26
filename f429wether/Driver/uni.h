#ifndef __UNI_H
#define __UNI_H

#include <stdio.h>
#include "stm32f4xx.h"                  // Device header

#define MAX_UNI_INDEX	6776

typedef unsigned short	uint16;
typedef unsigned char	  uchar;
void UniToStr(const uint16_t *uni,char *str);
int SwitchToGbk(const unsigned char* pszBufIn, int nBufInLen, unsigned char* pszBufOut);
#endif
