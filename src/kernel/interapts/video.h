#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "../uint.h"
#include "../stdio.h"

struct video_atr {
    uint32_t cursor_pos_x;
    uint32_t cursor_pos_y;
    uint16_t *vm_array[TEXT_MOD_Y];
    uint8_t terminal_tem;
} typedef video_atr;

#endif