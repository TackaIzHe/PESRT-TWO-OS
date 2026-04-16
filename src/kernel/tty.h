#ifndef __TTY_H__
#define __TTY_H__

#include "uint.h"

struct tty_atr {
    uint8_t keyboard_state : 1;
    uint8_t last_dep_key; 
    uint8_t last_dep_count;
} typedef tty_atr;

#endif