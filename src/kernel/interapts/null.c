#include "../idt/io.h"

void null_interapt(void)
{
    outb(0x20, 0x20);
    // outb(0xA0, 0x20);
    return;
}