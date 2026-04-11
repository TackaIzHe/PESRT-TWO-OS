#ifndef __GDT_H__
#define __GDT_H__

#include "../uint.h"
#include "../string.h"

#define GDT_ENTRIES 8            /* null,kcode,kdata,ucode,udata,tss */

void gdt_install(void);
void reload_segments(void);
void tss_flush(void);

typedef struct __attribute__((packed)) {
    uint16_t limit_15_0;
    uint16_t base_15_0;
    uint8_t  base_23_16;
    uint8_t  access;          /* 1001 0000b – 0x90, 0x9A, 0x92 … */
    uint8_t  flags_limit_19_16;/* G D L AVL */
    uint8_t  base_31_24;
} gdt_entry_t;

typedef struct __attribute__((packed)) {
    uint16_t size;
    uint32_t base;            /* линейный адрес таблицы */
} gdt_ptr_t;

#endif