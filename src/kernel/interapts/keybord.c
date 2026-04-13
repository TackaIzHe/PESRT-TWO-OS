#include "../idt/io.h"
#include "../idt/pic.h"

uint8_t press_key = 0;

__attribute__((naked)) void keybord_interapt(void) {
    __asm__ __volatile__("inb $0x60, %%al" : "=a" (press_key));
    uint16_t* vm = (uint16_t*)0xb8000;
    uint8_t *sumb = (uint8_t*)vm;
    sumb[1] = sumb[1] + 1;  // Меняем цвет символа в верхнем левом углу
    *(volatile uint32_t *)LAPIC_TIMER_EOI = 0;
    __asm__ __volatile__ ("iret");
}
