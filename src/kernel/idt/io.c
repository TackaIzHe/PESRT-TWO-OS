#include "../uint.h"

// Функция для вывода в порт
void outb(uint16_t port, uint8_t value) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(value), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t val;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}
//найти ошибку в данной функции
void outl(uint16_t port, uint32_t value) {
    __asm__ __volatile__ ("outl %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

uint32_t inl(uint16_t port) {
    uint32_t val;
    __asm__ __volatile__ ("inl %1, %0" : "=a"(val) : "Nd"(port) : "memory");
    return val;
}