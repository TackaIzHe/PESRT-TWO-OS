#ifndef __STDIO_H__
#define __STDIO_H__

#include "uint.h"
#include "tty.h"
#include "video_driver/vbe.h"

void scan(uint8_t *key);
void scanf(uint8_t *buff);
void init_video_mem(void);
void clear_screen(void);
void set_cursor_pos(uint32_t x, uint32_t y);
void set_terminal_tem(uint8_t background, uint8_t text_color);
void print_pixels_array(const uint16_t *buffer, uint32_t posX, uint32_t posY, uint32_t width, uint32_t height);

void get_vbe_info(vbe_info_t *info);
void get_vbe_mode_info(vbe_mode_info_t *mode_info);

void set_periodic_func(void(*func)(void*), void *arg);
void del_periodic_func(void);
void check_periodic_func(void(*func)(void*), uint8_t *res);
void get_tic(uint16_t *tic);

void get_tty(tty_atr *tty);
void set_keyboard_state(uint8_t keybord_state);
void set_last_dep_key(uint8_t last_dep_key);
void set_cyrsor_symboles(uint8_t *symboles);

/**
 * %d Вывод числа
 * %c Вывод символа
 * %s Вывод строки
 * \n Перенос на новую строку
 */
void printf(const uint8_t *str, ...);
void print(uint8_t sumbol);
void sprintf(uint8_t *dest, const uint8_t *str, ...);
void convert_int_to_string(uint32_t num, uint8_t *buff);

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

#define START_VIDEO_MEM (uint16_t *)0xb8000
#define ZERO_CHAR 48

#define KEYBOARD_STATE_DOWN 1
#define KEYBOARD_STATE_UP   0
/**
 * Количество одинаковых прерываний чтобы клавиша начала повторяться
 */
#define KEYBOARD_MAX_COUNT  250

#define ENTER        '\n'
#define BACKSPACE    '\b'


#endif