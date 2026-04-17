#include "first_kernel/kernel.h"
#include "stdio.h"

int ash_main(void);

void main(void) {
    printf("1 HELLO WORLD !!! %s %d \n2 asdqw \n", "asdqw", 12341);
    printf("3 HELLO WORLD !!! %s %d \n4 asdqw \n", "asdqw", 12341);
    printf("5 HELLO WORLD !!! %s %d \n6 asdqw \n", "asdqw", 12341);
    printf("7 HELLO WORLD !!! %s %d \n8 asdqw \n", "asdqw", 12341);
    printf("9 HELLO WORLD !!! %s %d \n10 asdqw \n", "asdqw", 12341);
    printf("11 HELLO WORLD !!! %s %d \n12 asdqw \n", "asdqw", 12341);
    printf("13 HELLO WORLD !!! %s %d \n14 asdqw \n", "asdqw", 12341);
    printf("15 HELLO WORLD !!! %s %d \n16 asdqw \n", "asdqw", 12341);
    // set_terminal_tem(BLUE, RED);
    printf("17 HELLO WORLD !!! %s %d \n18 asdqw \n", "asdqw", 12341);
    printf("19 HELLO WORLD !!! %s %d \n20 asdqw \n", "asdqw", 12341);
    printf("21 HELLO WORLD !!! %s %d \n22 asdqw \n", "asdqw", 12341);
    printf("23 HELLO WORLD !!! %s %d \n24 asdqw \n", "asdqw", 12341);
    printf("25 HELLO WORLD !!! %s %d \n26 asdqw \n", "asdqw", 12341);
    printf("27 HELLO WORLD !!! %s %d \n28 asdqw \n", "asdqw", 12341);
    printf("29 HELLO WORLD !!! %s %d \n30 asdqw \n", "asdqw", 12341);
    printf("31 123\n32asdqwe123321");
    printf("31 123\n32asdqwe123321");
    clear_screen();
    set_cursor_pos(0, 0);
    
    ash_main();
    while(1)
    {
        __asm__ __volatile__ ("hlt");
    }

    return;
}