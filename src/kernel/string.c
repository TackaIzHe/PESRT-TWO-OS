#include "uint.h"
#include "stdio.h"


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
    if (source[i] == '\0')
        dest[i] = '\0';
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

void strsplit(uint8_t *buffer, uint32_t str_len, const uint8_t *str, uint32_t buffer_len, uint8_t split_sumbole) {
    uint32_t len = strlen(str);
    uint8_t buffer_str[1024]; 
    uint32_t counter = 0;
    uint32_t start_str = 0;
    strcpy(buffer_str, str);
    for (uint32_t i = 0; i < len; i++) {
        if (counter >= buffer_len)
            goto _exit;

        if (buffer_str[i] == split_sumbole || buffer_str[i] == '\n') {
            buffer_str[i] = '\0';
            strcpy(buffer + ((str_len)*counter), buffer_str + start_str);
            counter++;
            start_str = i + 1;
        }
    }
_exit:
}