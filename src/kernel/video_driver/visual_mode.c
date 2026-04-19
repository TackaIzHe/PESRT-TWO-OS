#include "../uint.h"
#include "../idt/io.h"

// Установить пиксель в (x, y) цветом color
void put_pixel(int x, int y, uint8_t color) {
    if (x < 0 || x >= 320 || y < 0 || y >= 200) return; // Ограничения
    volatile uint8_t* vga = (volatile uint8_t*)0xA0000;
    vga[y * 320 + x] = color;
}

// Нарисовать горизонтальную линию
void draw_hline(int x1, int x2, int y, uint8_t color) {
    for (int x = x1; x <= x2; x++) {
        put_pixel(x, y, color);
    }
}

// Нарисовать вертикальную линию
void draw_vline(int x, int y1, int y2, uint8_t color) {
    for (int y = y1; y <= y2; y++) {
        put_pixel(x, y, color);
    }
}

// Нарисовать прямоугольник
void draw_rect(int x, int y, int w, int h, uint8_t color) {
    draw_hline(x, x + w - 1, y, color);
    draw_hline(x, x + w - 1, y + h - 1, color);
    draw_vline(x, y, y + h - 1, color);
    draw_vline(x + w - 1, y, y + h - 1, color);
}

void set_palette_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
    outb(0x3C8, index);
    outb(0x3C9, r & 0x3F); // Только 6 бит: 0–63
    outb(0x3C9, g & 0x3F);
    outb(0x3C9, b & 0x3F);
}
void init_palette_rainbow(void) {
    uint8_t r, g, b;

    // Цвета 0..63: Переход от Черного к Чистому Красному (R растет, G=0, B=0)
    for (int i = 0; i < 64; i++) {
        r = i * 4; // Масштабируем до 0-252 (VGA принимает 0-63)
        outb(0x3C8, i); // Индекс цвета
        outb(0x3C9, r / 4); // Red
        outb(0x3C9, 0);     // Green
        outb(0x3C9, 0);     // Blue
        outb(0x3C9, 0x00); 
    }

    // Цвета 64..127: Переход от Красного к Желтому (R=макс, G растет, B=0)
    for (int i = 64; i < 128; i++) {
        r = 252;
        g = (i - 64) * 4;
        outb(0x3C8, i);
        outb(0x3C9, r / 4);
        outb(0x3C9, g / 4);
        outb(0x3C9, 0);
        outb(0x3C9, 0x00); 
    }

    // Цвета 128..192: Переход от Желтого к Чистому Зеленому (R падает, G=макс, B=0)
    for (int i = 128; i < 192; i++) {
        r = 252 - (i - 128) * 4;
        g = 252;
        outb(0x3C8, i);
        outb(0x3C9, r / 4);
        outb(0x3C9, g / 4);
        outb(0x3C9, 0);
        outb(0x3C9, 0x00); 
    }

    // Цвета 192..255: Переход от Зеленого к Фиолетовому и Синему (R=0, G падает, B растет)
    for (int i = 192; i < 256; i++) {
        r = 0;
        g = 252 - (i - 192) * 4;
        b = (i - 192) * 4;
        outb(0x3C8, i);
        outb(0x3C9, r / 4);
        outb(0x3C9, g / 4);
        outb(0x3C9, b / 4);
        outb(0x3C9, 0x00); 
    }
}

// Пример: установим 16 цветов (как в стандартной палитре VGA)
// void init_palette(void) {
//     // Чёрный
//     set_palette_color(0, 0, 0, 0);
//     // Красный
//     set_palette_color(1, 4, 0, 0);
//     // Зелёный
//     set_palette_color(2, 0, 4, 0);
//     // Синий
//     set_palette_color(3, 0, 0, 4);
//     // Жёлтый
//     set_palette_color(4, 4, 4, 0);
//     // Пурпурный
//     set_palette_color(5, 4, 0, 4);
//     // Голубой
//     set_palette_color(6, 0, 4, 4);
//     // Белый
//     set_palette_color(7, 4, 4, 4);
//     // Серый
//     set_palette_color(8, 2, 2, 2);
//     // Ярко-красный
//     set_palette_color(9, 6, 0, 0);
//     // Ярко-зелёный
//     set_palette_color(10, 0, 6, 0);
//     // Ярко-синий
//     set_palette_color(11, 0, 0, 6);
//     // Ярко-жёлтый
//     set_palette_color(12, 6, 6, 0);
//     // Ярко-пурпурный
//     set_palette_color(13, 6, 0, 6);
//     // Ярко-голубой
//     set_palette_color(14, 0, 6, 6);
//     // Ярко-белый
//     set_palette_color(15, 6, 6, 6);
// }
