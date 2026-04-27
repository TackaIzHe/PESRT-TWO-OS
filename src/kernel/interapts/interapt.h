#ifndef __INTERAPT_H__
#define __INTERAPT_H__

#include "../uint.h"

void keybord_interapt(uint8_t *key);
void timer_interapt(void);
void null_interapt(void);

void init_video_interapt(void);
void clear_screen_video_interapt(void);
void set_cursor_video_interapt(uint32_t x, uint32_t y);
void set_tem_terminal_interapt(uint16_t background, uint16_t text_color);
void print_char_interapt(uint8_t sumbole);

void reset_disk_interapt(void);
void read_disk_sectors_interapt(uint32_t lba, uint32_t cnt, void *buf);
#endif 