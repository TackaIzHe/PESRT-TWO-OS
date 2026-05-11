#ifndef __INTERAPT_H__
#define __INTERAPT_H__

#include "../uint.h"
#include "../video_driver/vbe.h"
#include "../tty.h"

void keybord_interapt(uint8_t *key);
void timer_interapt(void);
void null_interapt(void);

void init_video_interapt(void);
void clear_screen_video_interapt(void);
void set_cursor_video_interapt(uint32_t x, uint32_t y);
void set_tem_terminal_interapt(uint16_t background, uint16_t text_color);
void print_char_interapt(uint8_t sumbole);
void p_buffer_interapt(const uint16_t *buffer, uint32_t posX, uint32_t posY, uint32_t width, uint32_t height);

void set_timer_periodic_func_interapt(void(*func)(void*), void *arg);
void del_timer_periodic_func_interapt(void);
void check_func_periodic_interapt(void(*func)(void*), uint8_t *res);
void get_cur_tic_interapt(uint16_t *tic);

void get_tty_atr_interapt(tty_atr *atr);
void set_tty_keyboard_state_interapt(uint8_t keyboard_state);
void set_tty_last_dep_key_interapt(uint8_t last_dep_key);
void set_tty_cursor_symboles_interapt(uint8_t *symboles);

void get_vbe_info_interapt(vbe_info_t *info);
void get_vbe_mode_info_interapt(vbe_mode_info_t *mode_info);

void reset_disk_interapt(void);
void read_disk_sectors_interapt(uint32_t lba, uint32_t cnt, void *buf);
#endif 