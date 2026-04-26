#include "first_kernel/kernel.h"
#include "video_driver/pci.h"
#include "stdio.h"
#include "string.h"

int ash_main(void);

void main(void) {
    uint16_t har[10] = {0};
    pci_find_device();
    ash_main();
    while(1)
    {
        __asm__ __volatile__ ("hlt");
    }

    return;
}