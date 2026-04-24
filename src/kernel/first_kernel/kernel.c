#include "kernel.h"
#include "../idt/idt.h"
#include "../idt/gdt.h"
#include "../idt/tss.h"
#include "../idt/pic.h"
#include "../uint.h"
#include "../stdio.h"
#include "../video_driver/pci.h"
#include "../video_driver/vbe.h"
#include "../video_driver/symboles.h"
extern tty_atr tty;

/**
 * Нужно настроить link.ld 
 * Нужно что то сделать с idt и маской pic
 */
int start_kernel(void){
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
    __asm__ __volatile__ ("sti");
    init_video_mem();
    clear_screen();

    
    tty.cursor_chars[0] = '\\';
    tty.cursor_chars[1] =  '-';
    tty.cursor_chars[2] =  '/';
    tty.cursor_chars[3] =  '|';
    uint32_t u = 0;
    const uint16_t *symb = sumbole_вопрос;
    for (uint32_t i = 0; i < SYMBOLE_HEIGHT; i++) {
        for (uint32_t j = 0; j < SYMBOLE_WIDTH; j++) {
            uint16_t cur = symb[u];
            if ((cur >> (SYMBOLE_WIDTH - j)) & 1) {
                *((uint16_t*)vbe_mode_info.fb_addr+(i * vbe_mode_info.xres + j)) = 0xFFFF;
            }
        }
        u++;
    }
    // *((uint32_t*)vbe_mode_info.fb_addr+18) = 0xFFFFFF00;
    // printf("%d\n", !!(symb[0] >> 0));
    while(1){}

    main();
    return 0;
}
