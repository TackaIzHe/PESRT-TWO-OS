#include "first_kernel/kernel.h"
#include "stdio.h"

void main(void)
{
    // uint8_t c;
    uint8_t asd[100];
    clear_screen(80, 25);
    init_cursor_pos();
    set_terminal_tem(BLACK, GREEN);
    convert_int_to_string(25012396, asd);
    uint32_t arg[3] = {'a', 250412, "asdqwedasd"};
    printf("qwe %c %d %s", arg);
    while(1)
    {
        scan_key();
        __asm__ __volatile__ ("hlt");
    }

    return;
}