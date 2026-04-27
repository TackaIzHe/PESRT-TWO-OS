#include "uint.h"

void reset_disk(void) {
    __asm__ __volatile__ ("int $0x90");
}

void read_disk_sectors(uint32_t lba, uint32_t cnt, void *buf) {
    __asm__ __volatile__ ("int $0x91");
}