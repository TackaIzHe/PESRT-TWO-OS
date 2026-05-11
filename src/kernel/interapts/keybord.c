#include "../idt/io.h"
#include "../idt/pic.h"
#include "../tty.h"
#include "../string.h"

tty_atr tty = {0};

__attribute__((naked)) void keybord_interapt(uint8_t *key) {
    __asm__ __volatile__ ("pusha");
    uint8_t k;
    __asm__ __volatile__ ("inb $0x60, %%al" : "=a" (k));
    *key = k;
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void get_tty_atr_interapt(tty_atr *atr) {
    __asm__ __volatile__ ("pusha");

    memcpy((uint8_t*)atr, (uint8_t*)&tty, sizeof(tty));

    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void set_tty_keyboard_state_interapt(uint8_t keyboard_state) {
    __asm__ __volatile__ ("pusha");

    tty.keyboard_state = keyboard_state;

    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void set_tty_last_dep_key_interapt(uint8_t last_dep_key) {
    __asm__ __volatile__ ("pusha");

    tty.last_dep_key = last_dep_key;

    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void set_tty_cursor_symboles_interapt(uint8_t *symboles) {
    __asm__ __volatile__ ("pusha");

    memcpy((uint8_t*)tty.cursor_chars, symboles, 4);

    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}