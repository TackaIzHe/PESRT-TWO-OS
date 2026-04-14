#include "../uint.h"
#include "../string.h"
#include "tss.h"

struct tss32 tss __attribute__((aligned(16))) = {0};

void init_tss(void) {
    memset((char *)&tss, 0, sizeof(tss));
    tss.esp0 = 0x20000;
    tss.ss0  = 0x10;
    tss.iomap = sizeof(tss);
    tss.iomap_pad = 0xFF;
}
