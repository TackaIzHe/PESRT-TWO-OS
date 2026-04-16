#include "../idt/io.h"
#include "../stdio.h"
#include "../idt/pic.h"

uint8_t terminal_tem = ((BLACK << 4) | WHITE);
uint32_t cursor_pos_x = 0;
uint32_t cursor_pos_y = 0;
uint16_t *vm_array[TEXT_MOD_Y];

static inline void scroll_page(void) {
    for (uint32_t i = 0; i < TEXT_MOD_Y - 1; i++)
        for (uint32_t j = 0; j < TEXT_MOD_X; j++) {
            vm_array[i][j] = vm_array[i + 1][j];
        }
    for (uint32_t i = 0; i < TEXT_MOD_X; i++)
        vm_array[TEXT_MOD_Y - 1][i] = (terminal_tem << 8) | 0;
}

__attribute__((naked)) void init_video_interapt(void) {
    for (uint32_t i = 0; i < TEXT_MOD_Y; i++)
        vm_array[i] = (START_VIDEO_MEM + (TEXT_MOD_X * i));

    cursor_pos_x = 0;
    cursor_pos_y = 0;
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void clear_screen_video_interapt(void) {
    for (uint32_t i = 0; i < TEXT_MOD_Y; i++)
        for (uint32_t j = 0; j < TEXT_MOD_X; j++)
            vm_array[i][j] = (terminal_tem << 8) | 0;

    cursor_pos_x = 0;
    cursor_pos_y = 0;

    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void set_cursor_video_interapt(uint32_t x, uint32_t y) {
    __asm__ __volatile__ ("pusha");
    cursor_pos_x = x;
    cursor_pos_y = y;
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void set_tem_terminal_interapt(uint8_t background, uint8_t text_color) {
    __asm__ __volatile__ ("pusha");
    terminal_tem = ((background << 4) | text_color);
    for (uint32_t i = cursor_pos_y; i < TEXT_MOD_Y; i++)
        for (uint32_t j = 0; j < TEXT_MOD_X; j++)
            vm_array[i][j] = (terminal_tem << 8) | ((vm_array[i][j] < 8) > 8);
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void print_char_interapt(uint8_t sumbole) {
    __asm__ __volatile__ ("pusha");
    if (sumbole == '\0')
        goto _exit;

    if (sumbole == BACKSPACE){
        if (cursor_pos_y == 0) {
            if (cursor_pos_x > 0) {
                cursor_pos_x--;
            }
        }
        else if (cursor_pos_y > 0) {
            if (cursor_pos_x == 0) {
                cursor_pos_x = TEXT_MOD_X - 1;
                cursor_pos_y--;
            }
            else {
                cursor_pos_x--;
            }
        }
        vm_array[cursor_pos_y][cursor_pos_x] = (terminal_tem << 8) | 0;
        goto _exit;
    }

    if (sumbole == ENTER) {
        cursor_pos_y++;
        cursor_pos_x = 0;
    }
    if (cursor_pos_x >= TEXT_MOD_X) {
        cursor_pos_y++;
        cursor_pos_x = 0;
    }
    if (cursor_pos_y >= TEXT_MOD_Y) {
        cursor_pos_y = TEXT_MOD_Y - 1;
        scroll_page();
    }
    if (sumbole != ENTER) {
        vm_array[cursor_pos_y][cursor_pos_x] = (terminal_tem << 8) | sumbole;
        cursor_pos_x++;
    }
_exit:
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}
