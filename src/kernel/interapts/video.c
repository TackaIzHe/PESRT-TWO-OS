#include "../idt/io.h"
#include "../stdio.h"
#include "../idt/pic.h"
#include "../video_driver/vbe.h"
#include "../video_driver/symboles.h"
#include "video.h"

video_atr video = {0};
static inline void backspace_func(void);
static inline void scroll_page(void);
// uint16_t get_pixel(uint32_t posX, uint32_t posY);
// void set_pixel(uint16_t color, uint32_t posX, uint32_t posY);
void p_char(uint8_t symbole, uint32_t posX, uint32_t posY);

void p_char(uint8_t symbole, uint32_t posX, uint32_t posY) {
    uint32_t u = 0;
    const uint16_t *symb = get_symbole_buffer_en(symbole);
    uint16_t *pos = ((uint16_t*)vbe_mode_info.fb_addr+(((posY * vbe_mode_info.xres * SYMBOLE_HEIGHT) + (posX * SYMBOLE_WIDTH))));
    for (uint32_t i = 0; i < SYMBOLE_HEIGHT; i++) {
        for (uint32_t j = 0; j < SYMBOLE_WIDTH; j++) {
            if ((symb[u] >> (SYMBOLE_WIDTH - j)) & 1) {
                *(pos + (i * vbe_mode_info.xres + j)) = \
                video.terminal_tem;
            }
            else {
                *(pos + (i * vbe_mode_info.xres + j)) = \
                video.background_terminal_tem;
            }
        }
        u++;
    }
}

uint16_t get_pixel(uint32_t posX, uint32_t posY) {
    return *((uint16_t*)vbe_mode_info.fb_addr+(posY * vbe_mode_info.xres + posX));
}

void set_pixel(uint16_t color, uint32_t posX, uint32_t posY) {
    *((uint16_t*)vbe_mode_info.fb_addr+(posY * vbe_mode_info.xres + posX)) = color;
}

__attribute__((naked)) void init_video_interapt(void) {
    video.cursor_pos_x = 0;
    video.cursor_pos_y = 0;
    video.terminal_tem = 0xFFFF;
    video.background_terminal_tem = 0x0000;

    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void clear_screen_video_interapt(void) {
    for (uint32_t i = 0; i < vbe_mode_info.yres / SYMBOLE_HEIGHT; i++)
        for (uint32_t j = 0; j < vbe_mode_info.xres / SYMBOLE_WIDTH; j++)
            p_char(' ', j, i);

    video.cursor_pos_x = 0;
    video.cursor_pos_y = 0;

    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void set_cursor_video_interapt(uint32_t x, uint32_t y) {
    __asm__ __volatile__ ("pusha");
    video.cursor_pos_x = x;
    video.cursor_pos_y = y;
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void set_tem_terminal_interapt(uint16_t background, uint16_t text_color) {
    __asm__ __volatile__ ("pusha");
    video.terminal_tem = text_color;
    video.background_terminal_tem = background;
    for (uint32_t i = video.cursor_pos_y; i < vbe_mode_info.yres / SYMBOLE_HEIGHT; i++)
        for (uint32_t j = 0; j < vbe_mode_info.xres / SYMBOLE_WIDTH; j++)
            p_char(' ', j, i);
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void print_char_interapt(uint8_t sumbole) {
    __asm__ __volatile__ ("pusha");
    if (sumbole == '\0')
        goto _exit;

    if (sumbole == BACKSPACE) {
        backspace_func();
        goto _exit;
    }

    if (sumbole == ENTER) {
        video.cursor_pos_y++;
        video.cursor_pos_x = 0;
    }
    if (video.cursor_pos_x >= vbe_mode_info.xres/ SYMBOLE_WIDTH) {
        video.cursor_pos_y++;
        video.cursor_pos_x = 0;
    }
    if (video.cursor_pos_y >= vbe_mode_info.yres/ SYMBOLE_HEIGHT) {
        video.cursor_pos_y = vbe_mode_info.yres/ SYMBOLE_HEIGHT -1;
        scroll_page();
    }
    if (sumbole != ENTER) {
        p_char(sumbole, video.cursor_pos_x, video.cursor_pos_y);
        video.cursor_pos_x++;
    }
_exit:
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

static inline void scroll_page(void) {
    for (uint32_t k = 0; k < SYMBOLE_HEIGHT; k++) {
        for (uint32_t i = 1; i < vbe_mode_info.yres; i++) {
            for (uint32_t j = 0; j < vbe_mode_info.xres; j++) {
                uint16_t prev_pixel = get_pixel(j, i);
                set_pixel(prev_pixel, j, i -1);
            }
        }
    }
}

static inline void backspace_func(void) {
    p_char(' ', video.cursor_pos_x, video.cursor_pos_y);
    if (video.cursor_pos_x > 0) {
        if (video.cursor_pos_y == 0) {
            video.cursor_pos_x--;
        }
    }
    if (video.cursor_pos_y > 0) {
        if (video.cursor_pos_x == 0) {
            video.cursor_pos_x = vbe_mode_info.xres / SYMBOLE_WIDTH;
            video.cursor_pos_y--;
        }
        else {
            video.cursor_pos_x--;
        }
    }
    p_char(' ', video.cursor_pos_x, video.cursor_pos_y);
}

// __attribute__((naked)) void init_video_interapt(void) {
//     video.cursor_pos_x = 0;
//     video.cursor_pos_y = 0;
//     video.terminal_tem = ((BLACK << 4) | WHITE);
//     for (uint32_t i = 0; i < TEXT_MOD_Y; i++)
//         video.vm_array[i] = (START_VIDEO_MEM + (TEXT_MOD_X * i));

//     *(volatile uint32_t *)LAPIC_EOI = 0;
//     __asm__ __volatile__ ("iret");
// }

// __attribute__((naked)) void clear_screen_video_interapt(void) {
//     for (uint32_t i = 0; i < TEXT_MOD_Y; i++)
//         for (uint32_t j = 0; j < TEXT_MOD_X; j++)
//             video.vm_array[i][j] = (video.terminal_tem << 8) | 0;

//     video.cursor_pos_x = 0;
//     video.cursor_pos_y = 0;

//     *(volatile uint32_t *)LAPIC_EOI = 0;
//     __asm__ __volatile__ ("iret");
// }

// __attribute__((naked)) void set_cursor_video_interapt(uint32_t x, uint32_t y) {
//     __asm__ __volatile__ ("pusha");
//     video.cursor_pos_x = x;
//     video.cursor_pos_y = y;
//     __asm__ __volatile__ ("popa");
//     *(volatile uint32_t *)LAPIC_EOI = 0;
//     __asm__ __volatile__ ("iret");
// }

// __attribute__((naked)) void set_tem_terminal_interapt(uint8_t background, uint8_t text_color) {
//     __asm__ __volatile__ ("pusha");
//     video.terminal_tem = ((background << 4) | text_color);
//     for (uint32_t i = video.cursor_pos_y; i < TEXT_MOD_Y; i++)
//         for (uint32_t j = 0; j < TEXT_MOD_X; j++)
//             video.vm_array[i][j] = (video.terminal_tem << 8) | ((video.vm_array[i][j] < 8) > 8);
//     __asm__ __volatile__ ("popa");
//     *(volatile uint32_t *)LAPIC_EOI = 0;
//     __asm__ __volatile__ ("iret");
// }

// __attribute__((naked)) void print_char_interapt(uint8_t sumbole) {
//     __asm__ __volatile__ ("pusha");
//     if (sumbole == '\0')
//         goto _exit;

//     if (sumbole == BACKSPACE) {
//         backspace_func();
//         goto _exit;
//     }

//     if (sumbole == ENTER) {
//         video.cursor_pos_y++;
//         video.cursor_pos_x = 0;
//     }
//     if (video.cursor_pos_x >= TEXT_MOD_X) {
//         video.cursor_pos_y++;
//         video.cursor_pos_x = 0;
//     }
//     if (video.cursor_pos_y >= TEXT_MOD_Y) {
//         video.cursor_pos_y = TEXT_MOD_Y - 1;
//         scroll_page();
//     }
//     if (sumbole != ENTER) {
//         video.vm_array[video.cursor_pos_y][video.cursor_pos_x] = (video.terminal_tem << 8) | sumbole;
//         video.cursor_pos_x++;
//     }
// _exit:
//     __asm__ __volatile__ ("popa");
//     *(volatile uint32_t *)LAPIC_EOI = 0;
//     __asm__ __volatile__ ("iret");
// }

// static inline void scroll_page(void) {
//     for (uint32_t i = 0; i < TEXT_MOD_Y - 1; i++)
//         for (uint32_t j = 0; j < TEXT_MOD_X; j++) {
//             video.vm_array[i][j] = video.vm_array[i + 1][j];
//         }
//     for (uint32_t i = 0; i < TEXT_MOD_X; i++)
//         video.vm_array[TEXT_MOD_Y - 1][i] = (video.terminal_tem << 8) | 0;
// }

// static inline void backspace_func(void) {
//     video.vm_array[video.cursor_pos_y][video.cursor_pos_x] = (video.terminal_tem << 8) | 0;
//     if (video.cursor_pos_x > 0) {
//         if (video.cursor_pos_y == 0) {
//             video.cursor_pos_x--;
//         }
//     }
//     if (video.cursor_pos_y > 0) {
//         if (video.cursor_pos_x == 0) {
//             video.cursor_pos_x = TEXT_MOD_X - 1;
//             video.cursor_pos_y--;
//         }
//         else {
//             video.cursor_pos_x--;
//         }
//     }
//     video.vm_array[video.cursor_pos_y][video.cursor_pos_x] = (video.terminal_tem << 8) | 0;
// }