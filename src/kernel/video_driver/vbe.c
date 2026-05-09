#include "../uint.h"
#include "../string.h"
#include "vbe.h"
#include "../stdio.h"
#include "../idt/tss.h"
#include "../first_kernel/kernel.h"

vbe_info_t vbe_info = {0};
vbe_mode_info_t vbe_mode_info = {0};
