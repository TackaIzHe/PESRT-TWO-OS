#ifndef __STDIO_H__
#define __STDIO_H__

#include "uint.h"

void scan_key(void);
void clear_screen(uint32_t x, uint32_t y);

#define TEXT_MOD_X   80
#define TEXT_MOD_Y   25

#define BLACK        0x00
#define BLUE         0x01
#define GREEN        0x02
#define BLUE_v2      0x03
#define RED          0x04
#define PURPLE       0x05
#define BROWN        0x06
#define GREY         0x07
#define DARK_GREY    0x08
#define LIGHT_PURPLE 0x09
#define LIME         0x0A
#define TURQUOISE    0x0B
#define LIGHT_RED    0x0C
#define PINK         0x0D
#define YELLOW       0x0E
#define WHITE        0x0F

#define START_VIDEO_MEM (char *)0xb8000
#define ZERO_CHAR 48

#endif