#ifndef __KERNEL_H__
#define __KERNEL_H__

/*-------------------------------------------------------------------------------------*/

/**
 * ASM Function
 */
// extern long getTackt();
// extern char keyboard_interrupt_handler();
// extern void keybord_init();
/*-------------------------------------------------------------------------------------*/

void main(void);

#define START_VIDEO_MEM (char *)0xb8000
#define ZERO_CHAR 48

#endif 