#ifndef __UINT_H__
#define __UINT_H__

#define uint8_t  unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int
typedef struct { 
    uint32_t value : 24;
} __attribute__((packed)) uint24_t;

#endif