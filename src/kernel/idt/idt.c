#include "idt.h"
#include "../interapts/interapt.h"
#include "../string.h"

IDTEntry idt[IDT_LENGHT];

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].offset_low = base & 0xFFFF;
    idt[num].offset_high = (base >> 16) & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].type_attr = flags;
    return;
}

void init_idt(void) {
    while (1){}
    memset((char*)&idt, 0, sizeof(IDTEntry) * IDT_LENGHT);
    
    for (int i = 0; i < IDT_LENGHT; i++)
    idt_set_gate(i, (uint32_t)null_interapt, 0x08, 0x8E);
    
    idt_set_gate(0x20, (uint32_t)timer_interapt,
    0x08, 0x8E);  // 0x60 - DPL=3 (разрешить из кольца 3)
    
    idt_set_gate(0x21, (uint32_t)keybord_interapt,
    0x08, 0x8E | 0x60);  // 0x60 - DPL=3 (разрешить из кольца 3)
    
    // // Загружаем IDT
    // struct {
    //     uint16_t limit;
    //     uint32_t base;
    // } __attribute__((packed)) idtr = {
    //     .limit = sizeof(IDTEntry) * IDT_LENGHT - 1,
    //     .base = (uint32_t)&idt
    // };
    
    // __asm__ __volatile__ ("lidt %0" : : "m" (idtr));
}