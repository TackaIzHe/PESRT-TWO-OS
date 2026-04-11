#ifndef __TSS_H__
#define __TSS_H__

#include "../uint.h"

extern struct tss32 tss;

void init_tss(void);

struct tss32 {
    uint16_t link;        // 0x00  селектор предыдущего TSS (для task switch)
    uint16_t res0;        // 0x02  reserved
    uint32_t esp0;        // 0x04  stack ring 0
    uint16_t ss0;         // 0x08
    uint16_t res1;        // 0x0A
    uint32_t esp1;        // 0x0C  stack ring 1
    uint16_t ss1;         // 0x10
    uint16_t res2;        // 0x12
    uint32_t esp2;        // 0x14  stack ring 2
    uint16_t ss2;         // 0x18
    uint16_t res3;        // 0x1A
    uint32_t cr3;         // 0x1C  PDBR при task switch
    uint32_t eip;         // 0x20  EIP при task switch
    uint32_t eflags;      // 0x24
    uint32_t eax;         // 0x28  GP regs
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;         // 0x38
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint16_t es;          // 0x48  segment selectors
    uint16_t res4;
    uint16_t cs;
    uint16_t res5;
    uint16_t ss;
    uint16_t res6;
    uint16_t ds;
    uint16_t res7;
    uint16_t fs;
    uint16_t res8;
    uint16_t gs;
    uint16_t res9;
    uint16_t ldt;         // 0x60  LDT selector
    uint16_t res10;
    uint16_t trap;        // 0x64  T-bit (debug trap)
    uint16_t iomap;       // 0x66  смещение I/O bitmap
    uint8_t  iomap_pad;
    /* можно дописать 8192 байта bitmap'а, но для ядра хватает 0xFFFF = нет bitmap */
} __attribute__((packed));

#endif