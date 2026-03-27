#include "../idt/io.h"
#include "../stdio.h"

void timer_interapt(void)
{
    uint8_t color = 0x01;
    uint16_t* vm = (uint16_t*)0xb8000;
    vm[0] = (color << 8) | 'A';  // Меняем цвет символа в верхнем левом углу
    // color = (color + 1) % 16;     // Циклически меняем цвет
    outb(0x20, 0x20);
    outb(0xA0, 0x11);
    return;
}