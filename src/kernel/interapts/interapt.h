#ifndef __INTERAPT_H__
#define __INTERAPT_H__

void keybord_interapt(uint8_t *key);
void timer_interapt(void);
void null_interapt(void);
void init_video_interapt(void);
void clear_screen_video_interapt(void);
void set_cursor_video_interapt(uint32_t x, uint32_t y);
void set_tem_terminal_interapt(uint8_t background, uint8_t text_color);
void print_char_interapt(uint8_t sumbole);

#endif 