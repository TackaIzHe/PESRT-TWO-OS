#include "../uint.h"
#include "pic.h"
#include "io.h"

// Инит таймера
static inline void lapic_timer_init(void) {
    *((uint32_t*)LAPIC_TIMER_BASE + TIMER_VECTOR) |= 1<<8;
    *(uint32_t*)LAPIC_TIMER_TDCR   = 0xA;      
    *(uint32_t*)LAPIC_TIMER_TMICT  = 0xFFFF;
    *(uint32_t*)LAPIC_TIMER_VEC  = 0x20000 | 0x20 | (1 << 17);  
    return;
}
// Инит клавиатуры
static inline void lapic_keybord_init(void) {
    *(uint32_t*)LAPIC_KEYBORD_BASE = 0x12;
    *((uint32_t*)LAPIC_KEYBORD_BASE + 4) = KEYBORD_VECTOR | 0x00010000;

    *(uint32_t*)LAPIC_KEYBORD_BASE = 0x13;
    *((uint32_t*)LAPIC_KEYBORD_BASE + 4) = 0;
}
// /* разрешить pin 0, вектор 0x20, CPU 0 */
static inline void lapic_init(void) {
    lapic_timer_init();
    lapic_keybord_init();
}
// Инициализация PIC
void init_pic(void) {
    /* Полный выключатель 8259 */
    outb(0x21, 0xFF);   // mask master
    outb(0xA1, 0xFF);   // mask slave
    outb(0x20, 0x11);   // ICW1 (init)
    outb(0xA0, 0x11);
    outb(0x21, 0x20);   // ICW2
    outb(0xA1, 0x28);
    outb(0x21, 0x04);   // ICW3
    outb(0xA1, 0x02);
    outb(0x21, 0x01);   // ICW4
    outb(0xA1, 0x01);
}

// Разрешаем IRQ0 (таймер) и IRQ1 (клавиатура)
void enable_irq(void) {
    lapic_init();
}
