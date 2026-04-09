#include "../uint.h"
#include "../stdio.h"
#include "../idt/io.h"

void keybord_interapt(void){
    __asm__ __volatile__("inb $0x64, %%al" : "=a" (keybord_state));
    
    outb(0x20, 0x20);
    // outb(0xA0, 0x11);
    // keybord_state = 1;
    return;
}



// Читаем статус клавиатуры (порт 0x64)
// "wait_for_keyboard:\n"
// "testb $0x00, %%al\n"  // Проверяем бит 0 (Output Buffer Full)
// "jz wait_for_keyboard\n" // Если не готов, ждем дальше
// "inb $0x60, %%al\n"    // Читаем скан-код (теперь безопасно)
// "movb %%al, %0\n"      // Сохраняем в scancode
// "outb %%al, $0xE9\n"   // Отправляем в Bochs debug порт
// "movb $0x20, %%al\n"   // Готовим EOI
// "outb %%al, $0x20\n"   // Отправляем EOI в PIC1
// : "=r" (scancode)      // Выход
// :                      // Вход
// : "al"                 // Клоубераем AL
