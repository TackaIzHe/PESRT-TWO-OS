#include "../uint.h"
#include "../stdio.h"
#include "../idt/io.h"
#include "../idt/pic.h"

__attribute__((naked)) void keybord_interapt(void){
    uint8_t c = 0;
    __asm__ __volatile__("inb $0x60, %%al" : "=a" (c));

    uint16_t* vm = (uint16_t*)0xb8000;
    uint8_t *sumb = (uint8_t*)vm;
    sumb[2] = c;

    *(volatile uint32_t *)LAPIC_TIMER_EOI = 0;
    __asm__ __volatile__ ("iret");
    return;
}
