#include "../idt/io.h"
#include "../idt/pic.h"

uint8_t press_key = 0;

__attribute__((naked)) void keybord_interapt(void) {
    __asm__ __volatile__("inb $0x60, %%al" : "=a" (press_key));
    *(volatile uint32_t *)LAPIC_TIMER_EOI = 0;
    __asm__ __volatile__ ("iret");
}
