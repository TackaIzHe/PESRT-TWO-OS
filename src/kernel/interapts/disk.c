#include "../uint.h"
#include "../idt/pic.h"
#include "../idt/io.h"

static inline void ata_wait(void) {
    while (inb(0x1F7) & 0x80);   // BSY
    while (!(inb(0x1F7) & 0x08)); // DRQ
}

__attribute__((naked)) void reset_disk_interapt(void) {
    __asm__ __volatile__ ("pusha");
    int i = 0;
    outb(0x1F6, 0xA0);          /* select master */
    outb(0x1F7, 0x08);          /* SRST=1 (Device Control Register) */
    for (i; i < 1000000; i++);
        outb(0x1F7, 0x00);          /* снять reset */
    while (inb(0x1F7) & 0x80);  /* ждём BSY=0 */
    while (!(inb(0x1F7) & 0x40)); /* ждём RDY=1 */
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}

__attribute__((naked)) void read_disk_sectors_interapt(uint32_t lba, uint32_t cnt, void *buf) {
    __asm__ __volatile__ ("pusha");
    uint8_t *p = (uint8_t *)buf;

    while (cnt--) {
        /* LBA28: 28 бит адреса (макс. 268 435 455) */
        uint8_t head = 0xE0 | ((lba >> 24) & 0x0F);

        outb(0x1F6, head);
        outb(0x1F1, 0);              /* features */
        outb(0x1F2, 1);              /* sector count */
        outb(0x1F3, lba & 0xFF);
        outb(0x1F4, (lba >> 8)  & 0xFF);
        outb(0x1F5, (lba >> 16) & 0xFF);
        outb(0x1F7, 0x20);           /* READ SECTORS */

        ata_wait();
        insw(0x1F0, p, 256);         /* 256 × 2 = 512 B */
        p += 512;
        ++lba;
    }
    __asm__ __volatile__ ("popa");
    *(volatile uint32_t *)LAPIC_EOI = 0;
    __asm__ __volatile__ ("iret");
}