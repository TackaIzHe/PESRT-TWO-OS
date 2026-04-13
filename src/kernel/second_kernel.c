#include "first_kernel/kernel.h"
#include "stdio.h"

void main(void)
{

    // uint8_t c;
    // scan_key();

    while(1)
    {
        // __asm__ __volatile__ ("int $0x21");
        __asm__ __volatile__ ("hlt");
    }

    return;
}