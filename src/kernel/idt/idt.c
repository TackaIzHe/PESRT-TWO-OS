#include "idt.h"
#include "../interapts/interapt.h"
#include "../string.h"

static IDTEntry idt[IDT_LENGHT];
static IDTptr idtr;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].offset_low = base & 0xFFFF;
    idt[num].offset_high = (base >> 16) & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].type_attr = flags;
    return;
}

void init_idt(void) {

    memset((char*)&idt, 0, sizeof(IDTEntry) * IDT_LENGHT);
    
    for (int i = 0; i < IDT_LENGHT; i++)
        idt_set_gate(i, (uint32_t)null_interapt, 0x08, 0x8E);
    
    idt_set_gate(0x20, (uint32_t)timer_interapt,
    0x08, 0x8E);
    
    idt_set_gate(0x21, (uint32_t)keybord_interapt,
    0x08, 0x8E | 0x60);  // 0x60 - DPL=3 (разрешить из кольца 3)

    idt_set_gate(0x80, (uint32_t)init_video_interapt,
    0x08, 0x8E | 0x60);  // 0x6

    idt_set_gate(0x81, (uint32_t)clear_screen_video_interapt,
    0x08, 0x8E | 0x60);  // 0x6

    idt_set_gate(0x82, (uint32_t)set_cursor_video_interapt,
    0x08, 0x8E | 0x60);  // 0x6

    idt_set_gate(0x83, (uint32_t)set_tem_terminal_interapt,
    0x08, 0x8E | 0x60);  // 0x6

    idt_set_gate(0x84, (uint32_t)print_char_interapt,
    0x08, 0x8E | 0x60);  // 0x6

    // Загружаем IDT
    idtr.limit = sizeof(IDTEntry) * IDT_LENGHT - 1;
    idtr.base = (uint32_t)&idt;

    __asm__ __volatile__ ("lidt %0" : : "m" (idtr));
}