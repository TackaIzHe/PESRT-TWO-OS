#ifndef __IO_H__
#define __IO_H_

#include "../uint.h"

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
#define io_wait() outb(0x80, 0)
#endif