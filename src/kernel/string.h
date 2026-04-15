#ifndef __STRING_H__
#define __STRING_H__

#include "uint.h"

void memset(uint8_t* dest, uint8_t data, uint32_t size);
uint32_t strlen(const uint8_t* str);
int strcmp(const uint8_t* str1, const uint8_t* str2);
void strcpy(uint8_t *dest, const uint8_t *source);

#endif