#include "kernel.h"
#include "../idt/idt.h"
#include "../idt/gdt.h"
#include "../idt/tss.h"
#include "../idt/pic.h"
#include "../uint.h"
#include "../stdio.h"

extern tty_atr tty;

/**
 * Нужно настроить link.ld 
 * Нужно что то сделать с idt и маской pic
 */
int start_kernel(void){
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
    main();
    return 0;
}
