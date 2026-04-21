#ifndef __STRING_H__
#define __STRING_H__

#include "uint.h"

void memset(uint8_t* dest, uint8_t data, uint32_t size);
uint32_t strlen(const uint8_t* str);
int strcmp(const uint8_t* str1, const uint8_t* str2);
void strcpy(uint8_t *dest, const uint8_t *source);
void memcpy(uint8_t *dest, uint8_t *source, uint32_t size);
uint32_t memcmp(uint8_t *mem1, uint8_t *mem2, uint32_t size);

/**
 * buffer - двумерный масив
 * str_len - размер строки в масиве строк
 * str - строка для разбиения
 * buffer_len - количество строк (MAX)
 * split_sumbol - символ разбиения
 */
void strsplit(uint8_t *buffer, uint32_t str_len, const uint8_t *str, uint32_t buffer_len, uint8_t split_sumbol);

#endif