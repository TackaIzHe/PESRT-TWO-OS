#include "../idt/io.h"
#include "../stdio.h"
#include "../idt/pic.h"

__attribute__((naked)) void timer_interapt(void)
{
    uint8_t color = 0x01;
    uint16_t* vm = (uint16_t*)0xb8000;
    uint8_t *sumb = (uint8_t*)vm;
    sumb[1] = sumb[1] + 1;  // Меняем цвет символа в верхнем левом углу

    *(volatile uint32_t *)LAPIC_TIMER_EOI = 0;
    __asm__ __volatile__ ("iret");
}