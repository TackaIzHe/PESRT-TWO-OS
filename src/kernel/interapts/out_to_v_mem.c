// void irq0_handler() {
//     // Обновляем позицию курсора (например, мигаем)
//     static bool cursor_visible = true;
//     cursor_visible = !cursor_visible;

//     if (cursor_visible) {
//         set_cursor(current_row, current_col);
//     } else {
//         set_cursor(255, 255);  // Скрываем курсор (за границами экрана)
//     }

//     // Отправляем EOI (End of Interrupt) в PIC
//     outb(0x20, 0x20);
// }