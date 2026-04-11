#include "../idt/io.h"
#include "../idt/pic.h"

__attribute__((naked)) void null_interapt(void)
{
    *(volatile uint32_t *)LAPIC_TIMER_EOI = 0;
    __asm__ __volatile__ ("iret");
}