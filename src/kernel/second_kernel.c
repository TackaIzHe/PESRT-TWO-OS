#include "first_kernel/kernel.h"
#include "stdio.h"

void main(void)
{

    // uint8_t c;
    clear_screen(80, 25);
    while(1)
    {
        scan_key();
        __asm__ __volatile__ ("hlt");
    }

    return;
}