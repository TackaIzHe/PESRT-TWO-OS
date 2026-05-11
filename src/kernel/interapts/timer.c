#include "../idt/io.h"
#include "../stdio.h"
#include "../idt/pic.h"
#include "../string.h"
#include "video.h"

extern tty_atr tty;
extern video_atr video;
uint8_t cur_sumbol = 0;

struct periodic_func_arg{
    void(*periodic_func)(void*);
    void *arg;
} typedef periodic_func_arg;

static periodic_func_arg periodic_func[50] = {0};
static uint32_t periodic_func_count = 0;

static inline void print_cursor(void);
uint16_t counter = 0;

__attribute__((naked)) void timer_interapt(void) {
    tty.tick_timer_count++;
    if (counter == 10) {

        for (uint8_t i = 0; i < periodic_func_count; i++) {
            periodic_func[i].periodic_func(periodic_func[i].arg);
        }
        counter = 0;
    }
    counter++;

    print_cursor();
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void set_timer_periodic_func_interapt(void(*func)(void*), void *arg) {
    __asm__ __volatile__ ("pusha");

    periodic_func[periodic_func_count].periodic_func = func;
    periodic_func[periodic_func_count].arg = arg;
    periodic_func_count++;

    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void del_timer_periodic_func_interapt(void) {
    __asm__ __volatile__ ("pusha");

    if (periodic_func_count > 0)
        periodic_func_count--;

    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void get_cur_tic_interapt(uint16_t *tic) {
    __asm__ __volatile__ ("pusha");

    *tic = tty.tick_timer_count;

    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void check_func_periodic_interapt(void(*func)(void*), uint8_t *res) {
    __asm__ __volatile__ ("pusha");
    for (uint32_t i = 0; i < periodic_func_count; i++) {
        if ((void*)(periodic_func + i)->periodic_func == (void*)func) {
            *res = 1;
            goto _exit;
        }
    }
    *res = 0;
_exit:
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

static inline void print_cursor(void) {
    if (tty.tick_timer_count == 18) {
        p_char(tty.cursor_chars[cur_sumbol], video.cursor_pos_x, video.cursor_pos_y);
        tty.tick_timer_count = 0;
        cur_sumbol++;
        if (cur_sumbol > 3)
            cur_sumbol = 0;
    }
}