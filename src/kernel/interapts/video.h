#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "../uint.h"
#include "../stdio.h"

struct video_atr {
    uint32_t cursor_pos_x;
    uint32_t cursor_pos_y;
    // uint16_t *vm_array[TEXT_MOD_Y];
    uint16_t background_terminal_tem;
    uint16_t terminal_tem;
} typedef video_atr;

void p_char(uint8_t symbole, uint32_t posX, uint32_t posY);
uint16_t get_pixel(uint32_t posX, uint32_t posY);
void set_pixel(uint16_t color, uint32_t posX, uint32_t posY);
// struct video_atr {
//     uint32_t cursor_pos_x;
//     uint32_t cursor_pos_y;
//     uint16_t *vm_array[TEXT_MOD_Y];
//     uint16_t terminal_tem;
// } typedef video_atr;

#endif