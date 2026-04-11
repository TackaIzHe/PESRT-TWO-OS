#include "gdt.h"
#include "tss.h"

static gdt_entry_t gdt[GDT_ENTRIES];
static gdt_ptr_t   gdt_ptr; 

static void gdt_set_gate(uint32_t n,
                         uint32_t base, uint32_t limit,
                         uint8_t access, uint8_t gran)
{
    gdt[n].base_15_0   = base & 0xFFFF;
    gdt[n].base_23_16  = (base >> 16) & 0xFF;
    gdt[n].base_31_24  = (base >> 24) & 0xFF;
    gdt[n].limit_15_0  = limit & 0xFFFF;
    gdt[n].flags_limit_19_16 = (limit >> 16) & 0x0F;
    gdt[n].flags_limit_19_16 |= gran & 0xF0;
    gdt[n].access      = access;
}

void gdt_install(void)
{
    /* 1. очистить */
    memset((char*)&gdt, 0, sizeof(gdt));

    /* 2. селекторы 0x00..0x28  (индекс<<3) */
    gdt_set_gate(0, 0, 0, 0, 0);                    // 0x00 null
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);   // 0x08 kcode
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);   // 0x10 kdata
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);   // 0x18 ucode
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   // 0x20 udata
    /* 5-й слот – TSS, заполним ниже */

    /* 3. указатель */
    gdt_ptr.size = sizeof(gdt) - 1;
    gdt_ptr.base = (uint32_t)gdt;

    /* 4. загрузить */
    asm volatile("lgdt (%0)" :: "m"(gdt_ptr));
    
    /* 5. перезагрузить сегменты  (far jmp ниже) */
}

void reload_segments(void)
{
    asm volatile(
        "ljmp $0x08, $1f\n"   /* far jump на селектор 0x08 (kcode) */
        "1:\n"
        "mov  $0x10, %%ax\n"  /* kdata */
        "mov  %%ax, %%ds\n"
        "mov  %%ax, %%es\n"
        "mov  %%ax, %%fs\n"
        "mov  %%ax, %%gs\n"
        "mov  %%ax, %%ss\n"
        ::: "ax");
}

void tss_flush(void)
{
    uint32_t base  = (uint32_t)&tss;
    uint32_t limit = sizeof(tss) - 1;

    /* 5-я запись GDT = 0x28 */
    gdt_set_gate(5, base, limit, 0x89, 0x40);  /* type=0x9 (32-bit TSS) */

    /* перезагрузить GDTR (limit изменился) */
    gdt_ptr.size = sizeof(gdt) - 1;
    // asm volatile("lgdt %0" :: "m"(gdt_ptr));
    // asm volatile("lgdt (%0)" :: "r"(&gdt_ptr));

    /* загрузить Task Register */
    asm volatile("lgdt (%0)" :: "r"(&gdt_ptr));
    asm volatile("ltr %%ax" :: "a"(0x28));
}