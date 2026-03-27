#ifndef __IDT_H__
#define __IDT_H__

#include "../uint.h"

#define IDT_LENGHT 256
#define INTERRUPT 0x80

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void init_idt(void);


void init_pic();
void enable_irq();
enum {
    INT_I = 0,
    INT_O
};

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed)) IDTEntry;

extern IDTEntry idt[IDT_LENGHT];
#endif