#ifndef __VISUAL_MODE_H__
#define __VISUAL_MODE_H__

#include "../uint.h"

void put_pixel(int x, int y, uint8_t color);
void draw_hline(int x1, int x2, int y, uint8_t color);
void draw_vline(int x, int y1, int y2, uint8_t color);
void draw_rect(int x, int y, int w, int h, uint8_t color);
// void init_palette(void);
void init_palette_rainbow(void);

#endif