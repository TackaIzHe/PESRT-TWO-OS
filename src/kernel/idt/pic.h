#ifndef __PIC_H__
#define __PIC_H__

void init_pic(void);
void enable_irq(void);
/**
 * SVR (0xFEE000F0) bit8 = Enable
 * *((uint32_t*)APIC_TIMER_BASE + TIMER_VECTOR) |= 1<<8;
 */ 
#define LAPIC_TIMER_BASE   0xFEE00000

/**
 * vec=0x20, periodic, unmasked
 * *(uint32_t*)APIC_TIMER_VEC  = 0x20000 | 0x20 | (1 << 17);
 */
#define LAPIC_TIMER_VEC    0xFEE00320
/**
 * *(uint32_t*)APIC_TIMER_TMICT  = 0xFFFF;
 */
#define LAPIC_TIMER_TMICT  0xFEE00380
/**
 * делитель = 16
 * *(uint32_t*)APIC_TIMER_TDCR   = 0x3;
 */
#define LAPIC_TIMER_TDCR   0xFEE003E0
#define LAPIC_EOI    0xFEE000B0

#define TIMER_PERIODIC_FLAG (1 << 17)
#define TIMER_VECTOR 0x20

#define LAPIC_KEYBORD_BASE 0xFEC00000

#define KEYBORD_VECTOR 0x21

#endif