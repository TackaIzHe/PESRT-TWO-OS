#include "../uint.h"
#include "io.h"

// Инициализация PIC
void init_pic() {
    // ICW1
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    // ICW2
    outb(0x21, 0x20);  // Master PIC: IRQ 0x20-0x27
    outb(0xA1, 0x28);  // Slave PIC: IRQ 0x28-0x2F

    // ICW3
    outb(0x21, 0x04);  // Master: Slave на IRQ2
    outb(0xA1, 0x02);  // Slave: идентификатор 0x02

    // ICW4
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Маскируем все прерывания (позже размаскируем нужные)
    outb(0x21, 0xFC);
    outb(0xA1, 0xFF);

    // Настраиваем PIT на частоту ~18.2 Hz (стандарт для PC)
    outb(0x43, 0x36);  // Command byte: channel 0, mode 3 (square wave)
    outb(0x40, 0xff);  // Low byte (0x0000 = 65536 Hz → 18.2 Hz)
    outb(0x40, 0x00);  // High byte
}

// Разрешаем IRQ0 (таймер) и IRQ1 (клавиатура)
void enable_irq() {
    outb(0x21, 0xFC);  // 0xFC = 11111100 (разрешаем IRQ0 и IRQ1)
}