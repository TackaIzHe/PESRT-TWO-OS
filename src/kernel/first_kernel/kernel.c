#include "kernel.h"
#include "../idt/idt.h"
#include "../idt/gdt.h"
#include "../idt/tss.h"
#include "../stdio.h"

char *videoMem = START_VIDEO_MEM;

void printf(char* mess, int color ){
    if(color == 0){
        color = 0x0f;
    }
    int i = 0;
    char *j = videoMem;
    *j = *(mess+3);
    while( *(mess+i) != 0 )
    {
        *j = mess[i];
        j += 1;
        *j = color;
        j += 1;
        i++;   
    }
}

void init() {
    // press_key = 48;
}
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
    init_idt();
    init_pic();
    while(1){}
    // enable_irq();
    __asm__ __volatile__ ("sti");
    

    main();
    return 0;
}
