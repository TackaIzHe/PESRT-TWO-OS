#include "uint.h"


void memset(uint8_t* dest, uint8_t data, uint32_t size) {
    for (uint32_t i = 0; i < size; i++)
        dest[i] = data;
    return;
}

uint32_t strlen(const uint8_t* str) {
    uint32_t i = 0;
    while (*str != '\0')
    {
        str++;
        i++;
    }

    return i;
}

void strcpy(uint8_t *dest, const uint8_t *source) {
    uint32_t i = 0;
    while (source[i] != '\0') {
        dest[i] = source[i];
        i++;
    }
}

int strcmp(const uint8_t* str1, const uint8_t* str2) {
    int res = -1;
    if (strlen(str1) != strlen(str2))
        goto _exit;
    
    while((*str1 != '\0') && (*str2 != '\0'))
    {
        if (*str1 != *str2)
            goto _exit;
        
        str1++;
        str2++;
    }
    res = 0;
_exit:
    return res;
}