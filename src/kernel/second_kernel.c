#include "first_kernel/kernel.h"
#include "video_driver/pci.h"
#include "stdio.h"
#include "string.h"
#include "fs.h"

int ash_main(void);

void main(void) {
    ash_main();
    while(1)
    {
        __asm__ __volatile__ ("hlt");
    }

    return;
}