#ifndef __VBE_H__
#define __VBE_H__

#include "../uint.h"

void call_interrupt(uint16_t ax, uint16_t bx, uint16_t di, uint16_t es);
void init_graphics_vbe(void);
// VBE Info Block (возвращается при вызове INT 10h, AX=4F00h)
typedef struct {
    char signature[4];           // "VESA"
    uint16_t version;            // версия VBE (например, 0x0300 = VBE 3.0)
    uint32_t oem_string_ptr;     // указатель на строку производителя (в сегменте)
    uint8_t capabilities[4];     // возможности (бит 14 = LFB поддерживается)
    uint32_t video_mode_ptr;     // указатель на список режимов
    uint16_t total_memory;       // количество 64KB блоков
    uint16_t oem_software_rev;
    uint32_t oem_vendor_name_ptr;
    uint32_t oem_product_name_ptr;
    uint32_t oem_product_rev_ptr;
    uint8_t reserved[222];
    uint8_t oem_data[256];
} __attribute__((packed)) vbe_info_block_t;

// VBE Mode Info Block (возвращается при INT 10h, AX=4F01h, CX=режим)
typedef struct {
    uint16_t attributes;
    uint8_t win_a, win_b;
    uint16_t granularity;
    uint16_t winsize;
    uint16_t segment_a, segment_b;
    uint32_t real_mode_ptr;
    uint16_t pitch;              // количество байт на строку (строковый шаг)
    uint16_t width, height;
    uint8_t w_char, h_char;
    uint8_t planes, bits_per_pixel, banks;
    uint8_t memory_model, bank_size, image_pages;
    uint8_t reserved;
    uint8_t red_mask, red_position;
    uint8_t green_mask, green_position;
    uint8_t blue_mask, blue_position;
    uint8_t reserved_mask, reserved_position;
    uint8_t direct_color_attributes;
    uint32_t framebuffer;        // ✅ ЛИНЕЙНЫЙ АДРЕС ВИДЕОПАМЯТИ (LFB)
    uint32_t offscreen_mem_off;
    uint16_t offscreen_mem_size;
    uint8_t reserved2[206];
} __attribute__((packed)) vbe_mode_info_block_t;

typedef struct {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Регистры общего назначения
    uint16_t ds, es, fs, gs;                          // Сегментные регистры
    uint16_t ip, cs, flags, sp, ss;                   // IP, CS, EFLAGS, SP, SS (в VM86)
} __attribute__((packed)) vm86_regs_t;


extern vbe_info_block_t vbe_info;
extern vbe_mode_info_block_t mode_info;

#endif