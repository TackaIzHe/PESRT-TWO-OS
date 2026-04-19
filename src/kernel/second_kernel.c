#include "first_kernel/kernel.h"
#include "video_driver/pci.h"
#include "stdio.h"

int ash_main(void);

void main(void) {
    // printf("1 HELLO WORLD !!! %s %d \n2 asdqw \n", "asdqw", 12341);
    // printf("3 HELLO WORLD !!! %s %d \n4 asdqw \n", "asdqw", 12341);
    // printf("5 HELLO WORLD !!! %s %d \n6 asdqw \n", "asdqw", 12341);
    // printf("7 HELLO WORLD !!! %s %d \n8 asdqw \n", "asdqw", 12341);
    // printf("9 HELLO WORLD !!! %s %d \n10 asdqw \n", "asdqw", 12341);
    // printf("11 HELLO WORLD !!! %s %d \n12 asdqw \n", "asdqw", 12341);
    // printf("13 HELLO WORLD !!! %s %d \n14 asdqw \n", "asdqw", 12341);
    // printf("15 HELLO WORLD !!! %s %d \n16 asdqw \n", "asdqw", 12341);
    // // set_terminal_tem(BLUE, RED);
    // printf("17 HELLO WORLD !!! %s %d \n18 asdqw \n", "asdqw", 12341);
    // printf("19 HELLO WORLD !!! %s %d \n20 asdqw \n", "asdqw", 12341);
    // printf("21 HELLO WORLD !!! %s %d \n22 asdqw \n", "asdqw", 12341);
    // printf("23 HELLO WORLD !!! %s %d \n24 asdqw \n", "asdqw", 12341);
    // printf("25 HELLO WORLD !!! %s %d \n26 asdqw \n", "asdqw", 12341);
    // printf("27 HELLO WORLD !!! %s %d \n28 asdqw \n", "asdqw", 12341);
    // printf("29 HELLO WORLD !!! %s %d \n30 asdqw \n", "asdqw", 12341);
    // printf("31 123\n32asdqwe123321");
    // printf("31 123\n32asdqwe123321");
    // clear_screen();
    // set_cursor_pos(0, 0);
    // ash_main();

    pci_bdf_t vga = pci_find_display_device();

    if (vga.bus != 0 || vga.device != 0 || vga.function != 0) {
        uint16_t vendor = pci_read_vendor_id(vga.bus, vga.device, vga.function);
        uint16_t device = pci_read_device_id(vga.bus, vga.device, vga.function);

        printf("card exist:\n");
        printf("  BDF: %02X:%02X.%X\n", vga.bus, vga.device, vga.function);
        printf("  Vendor ID: 0x%04X\n", vendor);
        printf("  Device ID: 0x%04X\n", device);

        // Проверка на известные производители
        if (vendor == 0x8086) printf("  vendor: Intel\n");
        else if (vendor == 0x1002) printf("  vendor: AMD\n");
        else if (vendor == 0x10DE) printf("  vendor: NVIDIA\n");
        else printf("  not found vendor\n");

    }

    printf("card not found.\n");


    while(1)
    {
        __asm__ __volatile__ ("hlt");
    }

    return;
}