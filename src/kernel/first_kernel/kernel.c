#include "kernel.h"
#include "../idt/idt.h"
#include "../idt/gdt.h"
#include "../idt/tss.h"
#include "../idt/pic.h"
#include "../uint.h"
#include "../stdio.h"
#include "../video_driver/pci.h"
#include "../video_driver/vbe.h"
#include "../fs.h"
extern tty_atr tty;
extern vbe_info_t vbe_info;
extern vbe_mode_info_t vbe_mode_info;

void init_main_kernel(void) {
    uint32_t last_sector = 74;
    read_disk_sectors(1, 80, (void*)(0x200000));
    memcpy((uint8_t*)(0x2000), (uint8_t*)(0x200000), last_sector*512);
    /**
     * Здесь неровное число так как система вылетае если указано больше байт чем есть програма
     */
    memcpy((uint8_t*)(0x2000+(last_sector*512)), (uint8_t*)(0x200000+(last_sector*512)), 1*38);
}

int start_kernel(void) {
    memcpy((uint8_t*)&vbe_mode_info, (uint8_t*)0x1000, sizeof(vbe_mode_info));
    memcpy((uint8_t*)&vbe_info, (uint8_t*)0x1100, sizeof(vbe_info));
    __asm__ __volatile__ ("cli");
    gdt_install();     /* строим таблицу */
    reload_segments(); /* сегменты теперь 32-битные */
    
    init_tss();        /* заполняем TSS */
    tss_flush();       /* добавляем TSS-дескриптор и ltr */
    init_pic();
    init_idt();
    enable_irq();
    tty.cursor_chars[0] = '\\';
    tty.cursor_chars[1] =  '-';
    tty.cursor_chars[2] =  '/';
    tty.cursor_chars[3] =  '|';
    __asm__ __volatile__ ("sti");
    reset_disk();
    init_main_kernel();
    init_video_mem();
    clear_screen();
    pci_find_device();

    main();
    return 0;
}
