#include "../uint.h"
#include "io.h"

#define APIC_BASE   0xFEE00000
#define APIC_TIMER  0xFEE00320
#define APIC_TMICT  0xFEE00380
#define APIC_TDCR   0xFEE003E0
#define APIC_EOI    0xFEE000B0

#define TIMER_PERIODIC_FLAG (1 << 17)
#define TIMER_VECTOR 0x20

static inline void lapic_timer_init(void){
    *((uint32_t*)APIC_BASE + TIMER_VECTOR) |= 1<<8;   // SVR (0xFEE000F0) bit8 = Enable
    *(uint32_t*)APIC_TDCR   = 0x3;      // делитель = 16
    *(uint32_t*)APIC_TMICT  = 0x10000;  // ~1 кГц при 4 ГГц TSC
    *(uint32_t*)APIC_TIMER  = 0x20000 | 0x20 | (1 << 17);  // vec=0x20, periodic, unmasked
    return;
}
// /* разрешить pin 0, вектор 0x20, CPU 0 */
static inline void ioapic_init(void){
    // ioapic_write(0x10, 0x00000020);   /* low dword  */
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
    lapic_timer_init();
    ioapic_init();
}

    // ICW1
    // outb(0x20, 0x11);
    // outb(0xA0, 0x11);

    // // ICW2
    // outb(0x21, 0x20);  // Master PIC: IRQ 0x20-0x27
    // outb(0xA1, 0x28);  // Slave PIC: IRQ 0x28-0x2F

    // // ICW3
    // outb(0x21, 0x04);  // Master: Slave на IRQ2
    // outb(0xA1, 0x02);  // Slave: идентификатор 0x02

    // // ICW4
    // outb(0x21, 0x01);
    // outb(0xA1, 0x01);

    // // Маскируем все прерывания (позже размаскируем нужные)
    // outb(0x21, 0xFF);
    // outb(0xA1, 0xFF);