#include "../idt/io.h"
#include "../idt/pic.h"

static uint8_t key_state = 0;

__attribute__((naked)) void keybord_interapt(uint8_t *key) {
    __asm__ __volatile__ ("pusha");
    uint8_t k;
    __asm__ __volatile__ ("inb $0x60, %%al" : "=a" (k));
    *key = k;
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}
