#include "../idt/io.h"
#include "../stdio.h"
#include "../idt/pic.h"
#include "video.h"

extern tty_atr tty;
extern video_atr video;
uint8_t cur_sumbol = 0;

static inline void print_cursor(void);

__attribute__((naked)) void timer_interapt(void) {
    tty.tick_timer_count++;

    print_cursor();
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

static inline void print_cursor(void) {
    if (tty.tick_timer_count == 18) {
        video.vm_array[video.cursor_pos_y][video.cursor_pos_x] = (video.terminal_tem << 8) | tty.cursor_chars[cur_sumbol];
        tty.tick_timer_count = 0;
        cur_sumbol++;
        if (cur_sumbol > 3)
            cur_sumbol = 0;
    }
}