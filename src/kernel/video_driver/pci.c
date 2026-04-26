#include "../uint.h"
#include "pci.h"
#include "../idt/io.h"
#include "../stdio.h"
#include "vendor.h"
#include "visual_mode.h"
#include "../string.h"

pci_bdf_t pci_devices[512] = {0};
video_card_bar card_bar[6] = {0};

// static inline void get_vendor_USB_str(uint16_t vendor_id, uint8_t *buffer);
// static inline void get_vendor_GPU_str(uint16_t vendor_id, uint8_t *buffer);
// static inline void get_vendor_NET_str(uint16_t vendor_id, uint8_t *buffer);
// static inline void get_class_PCI_str(uint16_t class_id, uint8_t *buffer);

uint32_t pci_make_address(uint8_t bus, uint8_t device, uint8_t function, uint8_t reg) {
    return (1U << 31) | ((uint32_t)bus << 16) | ((uint32_t)device << 11) | ((uint32_t)function << 8) | (reg & 0xFC);
}

// uint8_t pci_read_config_byte(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset) {
//     uint32_t address;
//     uint32_t value;

//     // Формируем адрес: [31] = 1 (включено), [23:16] = bus, [15:11] = device, [10:8] = function, [7:2] = offset
//     address = pci_make_address(bus, device, function, offset);
//     // Читаем 32-битное значение из порта 0xCFC
    
//     outl(PCI_CONFIG_ADDRESS_PORT, address);
//     value = inl(PCI_CONFIG_DATA_PORT);

//     // Смещение байта в зависимости от offset & 3
//     int shift = (offset & 3) * 8;
//     return (value >> shift) & 0xFF;
// }

// // Чтение 32-битного значения из PCI-конфигурации
static inline uint32_t pci_read_config_dword(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset) {
    uint32_t address;
    uint32_t value;

    // Формируем адрес: [31] = 1 (включено), [23:16] = bus, [15:11] = device, [10:8] = function, [7:2] = offset
    address = address = pci_make_address(bus, device, function, offset);

    outl(PCI_CONFIG_ADDRESS_PORT, address);
    value = inl(PCI_CONFIG_DATA_PORT);

    return value;
}

// void pci_write_config_dword(uint8_t bus, uint8_t device, uint8_t function, uint8_t reg, uint32_t value) {
//     uint32_t address = pci_make_address(bus, device, function, reg);
//     outl(address, PCI_CONFIG_ADDRESS_PORT);     // Записываем адрес
//     outl(value, PCI_CONFIG_DATA_PORT);         // Записываем данные
// }

// Чтение 16-битного Vendor ID
uint16_t pci_read_vendor_id(uint8_t bus, uint8_t device, uint8_t function) {
    return (uint16_t)(pci_read_config_dword(bus, device, function, PCI_VENDOR_ID_OFFSET) & 0xFFFF);
}

// // Чтение 16-битного Device ID
// uint16_t pci_read_device_id(uint8_t bus, uint8_t device, uint8_t function) {
//     return (uint16_t)(pci_read_config_dword(bus, device, function, PCI_DEVICE_ID_OFFSET) >> 16);
// }

// // Чтение 8-битного класса устройства
uint8_t pci_read_class_code(uint8_t bus, uint8_t device, uint8_t function) {
    uint32_t reg = pci_read_config_dword(bus, device, function, PCI_CLASS_CODE_OFFSET);
    return (reg >> 24) & 0xFF;
}

/**
 * Ищет PCI устроиства и заполняет структуру
 * pci_bdf_t pci_devices[512]
 */
void pci_find_device(void) {
    uint32_t counter = 0;
    // memset((uint8_t*)&pci_devices, 0, 12*512);
    // // printf("Сканирование PCI-шины...\n");

    // for (uint8_t bus = 0; bus < 255; bus++) {
    //     for (uint8_t device = 0; device < 32; device++) {
    //         for (uint8_t function = 0; function < 8; function++) {
    //             uint16_t vendor_id = pci_read_vendor_id(bus, device, function);

    //             // Если Vendor ID == 0xFFFF — устройство не существует
    //             if (vendor_id == 0xFFFF) {
    //                 // Если функция 0 вернула 0xFFFF — это устройство отсутствует, пропускаем все функции
    //                 if (function == 0) {
    //                     // Проверим, что это не "специальное" устройство (редко, но бывает)
    //                     uint32_t first_word = pci_read_config_dword(bus, device, 0, PCI_VENDOR_ID_OFFSET);
    //                     if ((first_word & 0xFFFF) == 0xFFFF) {
    //                         break; // Пропускаем всё устройство
    //                     }
    //                 }
    //                 continue;
    //             }

    //             uint8_t class_code = pci_read_class_code(bus, device, function);

    //             pci_devices[counter].bus = bus;
    //             pci_devices[counter].device = device;
    //             pci_devices[counter].function = function;
    //             pci_devices[counter].vendor = vendor_id;
    //             pci_devices[counter].class = class_code;
    //             pci_devices[counter].base_class = (class_code >> 16) & 0xFF;   // биты 23:16
    //             pci_devices[counter].sub_class = (class_code >>  8) & 0xFF;   // биты 15:8
    //             pci_devices[counter].prog_if = (class_code >>  0) & 0xFF;   // биты 7:0
    //             pci_devices[counter].flag = 1;
    //             counter++;
    //         }
    //     }
    // }
}

// Проверка: является ли устройство VGA-совместимым (дополнительно)
// int pci_is_vga_compatible(uint8_t bus, uint8_t device, uint8_t function) {
//     uint8_t class_code = pci_read_class_code(bus, device, function);
//     uint8_t subclass = (pci_read_config_dword(bus, device, function, PCI_CLASS_CODE_OFFSET) >> 8) & 0xFF;
//     return (class_code == PCI_CLASS_DISPLAY && subclass == PCI_SUBCLASS_DISPLAY_VGA);
// }

// void print_PCI_devices(void) {
//     uint32_t i = 0;
//     while (pci_devices[i].flag == 1) {
//         uint8_t class_str[50] = {0};
//         uint8_t vendor_str[50] = {0};
//         get_class_PCI_str(pci_devices[i].class, class_str);
//         get_vendor_GPU_str(pci_devices[i].vendor, vendor_str);
//         printf("#%d %d:%d.%d Vendor: %s; Class: %s; \n", 
//             i, pci_devices[i].bus, 
//             pci_devices[i].device, 
//             pci_devices[i].function, 
//             vendor_str, class_str);
//         i++;
//     }
// }

// uint32_t get_GPU_index(void) {
//     uint32_t i = 0;
//     while (pci_devices[i].flag == 1) {
//         if (pci_devices[i].class == PCI_CLASS_DISPLAY && pci_devices[i].sub_class == PCI_SUBCLASS_DISPLAY_VGA) {
//             break;
//         }
//         i++;
//     }
//     return i;
// }

// uint32_t check_GPU_BAR(void) {
//     uint32_t index = get_GPU_index();
//     uint8_t counter = 0;
//     uint32_t bar0 = pci_read_config_dword(pci_devices[index].bus, pci_devices[index].device, pci_devices[index].function, 0x10);


//     for (int i = 0; i < 6; i++) {
//     uint32_t bar = pci_read_config_dword(pci_devices[index].bus, pci_devices[index].device, pci_devices[index].function, 0x10+(i*4));
//     if (bar != 0 && (bar & 0x1) == 0) { // MMIO
//             uint32_t base = bar & ~0xF;
//             if (base != 0 && base != 0xFFFFFFFF) {
//                 card_bar[counter].bar_id = i;
//                 card_bar[counter].bar_addr = base;
//                 counter++;
//             }
//         }
//     }   

//     if (bar0 != 0 && (bar0 & 0x1) == 0) {
//         return bar0;
//     } else {
//         return 0;
//     }
// }

// uint8_t check_GPU_revision_id(void) {
//     uint32_t i = get_GPU_index();

//     uint8_t rev_id = pci_read_config_byte(pci_devices[i].bus, pci_devices[i].device, pci_devices[i].function, 0x08);
//     return rev_id;
// }

// uint32_t get_GPU_memory(void) {
//     uint32_t i = get_GPU_index();

//     uint32_t bar0_raw = pci_read_config_dword(pci_devices[i].bus, pci_devices[i].device, pci_devices[i].function, 0x10);
//     uint32_t bar0_phys = bar0_raw & 0xFFFFFFF0; // Убираем флаги (бит 0 = 0 → MMIO)


//     pci_write_config_dword(pci_devices[i].bus, pci_devices[i].device, pci_devices[i].function, 0x10, 0xFFFFFFFF); // Запишите 0xFF...
//     uint32_t size_mask = pci_read_config_dword(pci_devices[i].bus, pci_devices[i].device, pci_devices[i].function, 0x10); // Прочитайте, что вернулось
//     pci_write_config_dword(pci_devices[i].bus, pci_devices[i].device, pci_devices[i].function, 0x10, bar0_raw);     // Восстановите оригинал

//     uint32_t size = ~(size_mask & 0xFFFFFFF0) + 1; // Размер в байтах
//     return size / (1024 * 1024);
// }

// uint8_t check_GPU_class(void) {
//     uint32_t i = get_GPU_index();

//     uint8_t class_code = pci_read_config_byte(pci_devices[i].bus, pci_devices[i].device, pci_devices[i].function, 0x0B); // Base Class
//     uint8_t subclass = pci_read_config_byte(pci_devices[i].bus, pci_devices[i].device, pci_devices[i].function, 0x0C);  // Subclass

//     if (class_code == PCI_CLASS_DISPLAY && subclass == PCI_SUBCLASS_DISPLAY_VGA) {
//         return 1;
//     } else if (class_code == PCI_CLASS_DISPLAY && subclass == PCI_SUBCLASS_DISPLAY_XGA) {
//         return 0;
//     }
// }

// void set_vga_mode_13h(void) {
//     // ВАЖНО: Порядок инициализации критически важен.
//     // Мы будем использовать стандартный режим "Mode 13h" с адресацией 0xA0000.
//     // Этот код настраивает карту так, чтобы запись в 0xA0000:xxxx работала линейно.

//     // 1. Блокируем CRTC (чтобы можно было менять настройки)
//     outb(0x3D4, 0x11);
//     outb(0x3D5, inb(0x3D5) | 0x80);

//     // 2. Настройка Sequencer (Memory Mode)
//     // Устанавливаем режим "256-Color" (Write Mode 0), отключаем Chain-4.
//     // Значение 0x06: Binary(0110) - Write Mode 0 (биты [1:0]=01), Disable Chain-4 (бит 0 = 0).
//     outb(0x3C4, 0x04);
//     outb(0x3C5, 0x06);

//     // Сброс Sequencer и настройка таймингов
//     outb(0x3C4, 0x00); outb(0x3C5, 0x03); // Reset
//     outb(0x3C4, 0x01); outb(0x3C5, 0x01); // Clocking Mode

//     // 3. Настройка Graphics Controller
//     // Устанавливаем режим "Read/Write" для доступа к видеопамяти.
//     outb(0x3CE, 0x06); outb(0x3CF, 0x04); // Set/Reset -> 4 (для корректной работы)
//     outb(0x3CE, 7);     outb(0x3CF, 0x00); // Graphics Mode -> Write Mode 0

//     // 4. Настройка CRTC (Тайминги) - Стандартные значения для Mode 13h
//     // Горизонтальные параметры
//     outb(0x3D4, 0x00); outb(0x3D5, 0x5F); // Horizontal Total
//     outb(0x3D4, 0x01); outb(0x3D5, 0x4F); // Horizontal Displayed
//     outb(0x3D4, 0x02); outb(0x3D5, 0x50); // H Blank Start
//     outb(0x3D4, 0x03); outb(0x3D5, 0x82); // H Blank End
//     outb(0x3D4, 0x04); outb(0x3D5, 0x55); // Sync Start
//     outb(0x3D4, 0x07); outb(0x3D5, 0x41); // Vertical Total

//     // Вертикальные параметры
//     outb(0x3D4, 0x12); outb(0x3D5, 28);   // Overflow Register (старшие биты)
//     outb(0x3D4, 0x14); outb(0x3D5, 8);    // V Blank Start
//     outb(0x3D4, 0x15); outb(0x3D5, 9);    // V Blank End
//     outb(0x3D4, 0x16); outb(0x3D5, 16);   // V Sync Start

//     // Разблокируем CRTC
//     outb(0x3D4, 0x11);
//     outb(0x3D5, inb(0x3D5) & ~0x80);

//     // ====== Инициализация палитры ======
//     init_palette_rainbow();
// }

#define H_TOTAL   2200
#define H_SYNC_START 1920
#define H_SYNC_END   2000
#define H_DISPLAY   1920

#define V_TOTAL   1125
#define V_SYNC_START 1080
#define V_SYNC_END   1084
#define V_DISPLAY   1080

/////////////
    /**
     * дублирует экран горизонтально
     */
    // outb(0x3D4, 0x11);  // CRTC Index: Horizontal Total
    // outw(0x3D5, 1920*4+15);  // Horizontal Total: 80 * 4 + 15 = 335 → 0x4F (для 320x200)
/////////////

// Настройка CRTC (CRT Controller)
// void set_vga_mode_1920x1080(void) {
//     // 1. Отключить обновление
//     // outb(0x3C4, 0x01); outb(0x3C5, 0x01); // SEQ: Disable clock
//     // outb(0x3C4, 0x00); outb(0x3C5, 0x01); // SEQ: Reset

//      // ====== 3. Настройка Sequencer (включаем режим 13h) ======
//     outb(0x3C4, 0x00);  // Sequencer Index: Reset
//     outb(0x3C5, 0x03);  // Reset sequencer and enable clocking
//     outb(0x3C4, 0x01);  // Sequencer Index: Clocking Mode
//     outb(0x3C5, 0x01);  // Enable all 4 planes, 8-bit mode
//     outb(0x3C4, 0x02);  // Sequencer Index: Map Mask
//     outb(0x3C5, 0x0F);  // Enable all 4 planes
//     outb(0x3C4, 0x03);  // Sequencer Index: Character Map Select
//     outb(0x3C5, 0x00);  // Use plane 0-3 for pixel data (not text)
//     outb(0x3C4, 0x04);  // Sequencer Index: Memory Mode
//     outb(0x3C5, 0x03);  // Enable chain-4 mode (required for 256-color mode)

//     // // ====== 6. Настройка палитры — устанавливаем красный цвет ======
//     // outb(0x3C8, 0x00);  // Palette Index: 0
//     // outb(0x3C9, 0x00);  // Red: 4 (0-63 range, 4 ≈ 16%)
//     // init_palette();

//     // outb(0x3C8, 0x04);  // Palette Index: 1
//     // outb(0x3C9, 0x00);  // Red: 0
//     // outb(0x3C9, 0x00);  // Green: 0
//     // outb(0x3C9, 0x00);  // Blue: 0 (чёрный)

//     // outb(0x3C0, 0x00);  // Сброс атрибутов
//     // outb(0x3C1, 0x00);  // Все пиксели — невидимы (не текст!)
//     // 2. Настроить CRTC
//     // outb(0x3D4, 0x00); outb(0x3D5, (H_TOTAL - 5) & 0xFF);      // CRTC_H_TOTAL
//     // outb(0x3D4, 0x01); outb(0x3D5, (H_DISPLAY - 1) & 0xFF);    // CRTC_H_DISP
//     // outb(0x3D4, 0x02); outb(0x3D5, (H_SYNC_START - 1) & 0xFF); // CRTC_H_SYNC_START
//     // outb(0x3D4, 0x04); outb(0x3D5, (H_SYNC_END - 1) & 0xFF);   // CRTC_H_SYNC_END
    
//     // outb(0x3D4, 0x06); outb(0x3D5, (V_TOTAL - 2) & 0xFF);      // CRTC_V_TOTAL
//     // outb(0x3D4, 0x07); outb(0x3D5, (V_DISPLAY - 1) & 0xFF);    // CRTC_V_DISP
//     // outb(0x3D4, 0x09); outb(0x3D5, (V_SYNC_START - 1) & 0xFF); // CRTC_V_SYNC_START
//     // outb(0x3D4, 0x0A); outb(0x3D5, (V_SYNC_END - 1) & 0xFF);   // CRTC_V_SYNC_END
    
//     // outb(0x3D4, 0x12);  // CRTC Index: Horizontal Display End
//     // outw(0x3D5, 1920/4);  // Horizontal Display End: 320/4 = 80 → 0x4F
//     // 3. Настроить пиксельную частоту (если нужно)
//     //   — Для QEMU/Bochs: 148.5 MHz (для 1080p@60Hz)

//     // 4. Включить обновление
//     // outb(0x3C4, 0x01); outb(0x3C5, 0x00); // SEQ: Enable clock
// }


// static inline void get_vendor_GPU_str(uint16_t vendor_id, uint8_t *buffer) {
//     switch (vendor_id) {
//         case GPU_VENDOR_AMD:            return strcpy(buffer, GPU_VENDOR_AMD_STR);
//         case GPU_VENDOR_NVIDIA:         return strcpy(buffer, GPU_VENDOR_NVIDIA_STR);
//         case GPU_VENDOR_INTEL:          return strcpy(buffer, GPU_VENDOR_INTEL_STR);
//         case GPU_VENDOR_APPLE:          return strcpy(buffer, GPU_VENDOR_APPLE_STR);
//         case GPU_VENDOR_MATROX:         return strcpy(buffer, GPU_VENDOR_MATROX_STR);
//         case GPU_VENDOR_S3:             return strcpy(buffer, GPU_VENDOR_S3_STR);
//         case GPU_VENDOR_CIRRUS:         return strcpy(buffer, GPU_VENDOR_CIRRUS_STR);
//         case GPU_VENDOR_ATI:            return strcpy(buffer, GPU_VENDOR_ATI_STR);
//         case GPU_VENDOR_VIRTUALBOX:     return strcpy(buffer, GPU_VENDOR_VIRTUALBOX_STR);
//         case GPU_VENDOR_VMWARE:         return strcpy(buffer, GPU_VENDOR_VMWARE_STR);
//         case GPU_VENDOR_MICROSOFT:      return strcpy(buffer, GPU_VENDOR_MICROSOFT_STR);
//         case GPU_VENDOR_PLX:            return strcpy(buffer, GPU_VENDOR_PLX_STR);
//         // case GPU_VENDOR_IBM:            return strcpy(buffer, GPU_VENDOR_IBM_STR);
//         default:                        return strcpy(buffer, "Unknown vendor");
//     }
// }

// static inline void get_vendor_USB_str(uint16_t vendor_id, uint8_t *buffer) {
//     switch (vendor_id) {
//         case USB_VENDOR_INTEL:          return strcpy(buffer, USB_VENDOR_INTEL_STR);
//         case USB_VENDOR_AMD:            return strcpy(buffer, USB_VENDOR_AMD_STR);
//         case USB_VENDOR_RENESAS:        return strcpy(buffer, USB_VENDOR_RENESAS_STR);
//         case USB_VENDOR_MICROCHIP:      return strcpy(buffer, USB_VENDOR_MICROCHIP_STR);
//         case USB_VENDOR_QUALCOMM:       return strcpy(buffer, USB_VENDOR_QUALCOMM_STR);
//         case USB_VENDOR_TEXAS:          return strcpy(buffer, USB_VENDOR_TEXAS_STR);
//         case USB_VENDOR_FRESCO:         return strcpy(buffer, USB_VENDOR_FRESCO_STR);
//         case USB_VENDOR_MICROSOFT:      return strcpy(buffer, USB_VENDOR_MICROSOFT_STR);
//         case USB_VENDOR_CYPRESS:        return strcpy(buffer, USB_VENDOR_CYPRESS_STR);
//         case USB_VENDOR_PERICOM:        return strcpy(buffer, USB_VENDOR_PERICOM_STR);
//         case USB_VENDOR_LINUX:          return strcpy(buffer, USB_VENDOR_LINUX_STR);

//         case USB_VENDOR_ASUSTEK:        return strcpy(buffer, USB_VENDOR_ASUSTEK_STR);
//         case USB_VENDOR_ACER:           return strcpy(buffer, USB_VENDOR_ACER_STR);
//         case USB_VENDOR_CHICONY:        return strcpy(buffer, USB_VENDOR_CHICONY_STR);
//         case USB_VENDOR_SANDISK:        return strcpy(buffer, USB_VENDOR_SANDISK_STR);
//         case USB_VENDOR_NEC:            return strcpy(buffer, USB_VENDOR_NEC_STR);

//         case USB_VENDOR_ATHEROS:        return strcpy(buffer, USB_VENDOR_ATHEROS_STR);
//         case USB_VENDOR_REALTEK:        return strcpy(buffer, USB_VENDOR_REALTEK_STR);
//         case USB_VENDOR_RALINK:         return strcpy(buffer, USB_VENDOR_RALINK_STR);
//         case USB_VENDOR_BUFFALO:        return strcpy(buffer, USB_VENDOR_BUFFALO_STR);
//         case USB_VENDOR_DLINK:          return strcpy(buffer, USB_VENDOR_DLINK_STR);
//         case USB_VENDOR_NETGEAR:        return strcpy(buffer, USB_VENDOR_NETGEAR_STR);
//         case USB_VENDOR_LINKSYS:        return strcpy(buffer, USB_VENDOR_LINKSYS_STR);
//         case USB_VENDOR_ASUS:           return strcpy(buffer, USB_VENDOR_ASUS_STR);
//         case USB_VENDOR_TENDA:          return strcpy(buffer, USB_VENDOR_TENDA_STR);
//         case USB_VENDOR_IMC:            return strcpy(buffer, USB_VENDOR_IMC_STR);
//         case USB_VENDOR_SONY:           return strcpy(buffer, USB_VENDOR_SONY_STR);
//         default:                        return strcpy(buffer, "Unknown vendor");
//     }
// }

// static inline void get_vendor_NET_str(uint16_t vendor_id, uint8_t *buffer) {
//     switch (vendor_id) {
//         case USB_VENDOR_ATHEROS:        return strcpy(buffer, USB_VENDOR_ATHEROS_STR);
//         case USB_VENDOR_REALTEK:        return strcpy(buffer, USB_VENDOR_REALTEK_STR);
//         case USB_VENDOR_RALINK:         return strcpy(buffer, USB_VENDOR_RALINK_STR);
//         case USB_VENDOR_BUFFALO:        return strcpy(buffer, USB_VENDOR_BUFFALO_STR);
//         case USB_VENDOR_DLINK:          return strcpy(buffer, USB_VENDOR_DLINK_STR);
//         case USB_VENDOR_NETGEAR:        return strcpy(buffer, USB_VENDOR_NETGEAR_STR);
//         case USB_VENDOR_LINKSYS:        return strcpy(buffer, USB_VENDOR_LINKSYS_STR);
//         case USB_VENDOR_ASUS:           return strcpy(buffer, USB_VENDOR_ASUS_STR);
//         case USB_VENDOR_TENDA:          return strcpy(buffer, USB_VENDOR_TENDA_STR);
//         case USB_VENDOR_IMC:            return strcpy(buffer, USB_VENDOR_IMC_STR);
//         case USB_VENDOR_SONY:           return strcpy(buffer, USB_VENDOR_SONY_STR);
//         case USB_VENDOR_SISVEL:         return strcpy(buffer, USB_VENDOR_SISVEL_STR);
//         case USB_VENDOR_ASIX:           return strcpy(buffer, USB_VENDOR_ASIX_STR);
//         case USB_VENDOR_PROLIFIC:       return strcpy(buffer, USB_VENDOR_PROLIFIC_STR);
//         case USB_VENDOR_APPLE:          return strcpy(buffer, USB_VENDOR_APPLE_STR);
//         case USB_VENDOR_SAMSUNG:        return strcpy(buffer, USB_VENDOR_SAMSUNG_STR);
//         // case USB_VENDOR_FOXCONN: return strcpy(buffer, USB_VENDOR_FOXCONN_STR);
//         case USB_VENDOR_GENESYS:        return strcpy(buffer, USB_VENDOR_GENESYS_STR);
//         case USB_VENDOR_NECS:           return strcpy(buffer, USB_VENDOR_NECS_STR);
//         case USB_VENDOR_BELKIN:         return strcpy(buffer, USB_VENDOR_BELKIN_STR);
//         case USB_VENDOR_IODATA:         return strcpy(buffer, USB_VENDOR_IODATA_STR);
//         case USB_VENDOR_SITECOM:        return strcpy(buffer, USB_VENDOR_SITECOM_STR);
//         default:                        return strcpy(buffer, "Unknown vendor");
//     }
// }

// static inline void get_class_PCI_str(uint16_t class_id, uint8_t *buffer) {
//     switch (class_id) {
//         case PCI_CLASS_PRE_2_0:           return strcpy(buffer, PCI_CLASS_PRE_2_0_STR);
//         case PCI_CLASS_MASS_STORAGE:      return strcpy(buffer, PCI_CLASS_MASS_STORAGE_STR);
//         case PCI_CLASS_NETWORK:           return strcpy(buffer, PCI_CLASS_NETWORK_STR);
//         case PCI_CLASS_DISPLAY:           return strcpy(buffer, PCI_CLASS_DISPLAY_STR);
//         case PCI_CLASS_MULTIMEDIA:        return strcpy(buffer, PCI_CLASS_MULTIMEDIA_STR);
//         case PCI_CLASS_MEMORY:            return strcpy(buffer, PCI_CLASS_MEMORY_STR);
//         case PCI_CLASS_BRIDGE:            return strcpy(buffer, PCI_CLASS_BRIDGE_STR);
//         case PCI_CLASS_COMMUNICATION:     return strcpy(buffer, PCI_CLASS_COMMUNICATION_STR);
//         case PCI_CLASS_SYSTEM_PERIPHERAL: return strcpy(buffer, PCI_CLASS_SYSTEM_PERIPHERAL_STR);
//         case PCI_CLASS_INPUT:             return strcpy(buffer, PCI_CLASS_INPUT_STR);
//         case PCI_CLASS_DOCKING:           return strcpy(buffer, PCI_CLASS_DOCKING_STR);
//         case PCI_CLASS_PROCESSOR:         return strcpy(buffer, PCI_CLASS_PROCESSOR_STR);
//         case PCI_CLASS_SERIAL_BUS:        return strcpy(buffer, PCI_CLASS_SERIAL_BUS_STR);
//         case PCI_CLASS_WIRELESS:          return strcpy(buffer, PCI_CLASS_WIRELESS_STR);
//         case PCI_CLASS_INTELLIGENT:       return strcpy(buffer, PCI_CLASS_INTELLIGENT_STR);
//         case PCI_CLASS_SATELLITE:         return strcpy(buffer, PCI_CLASS_SATELLITE_STR);
//         case PCI_CLASS_ENCRYPTION:        return strcpy(buffer, PCI_CLASS_ENCRYPTION_STR);
//         case PCI_CLASS_SIGNAL_PROCESSING: return strcpy(buffer, PCI_CLASS_SIGNAL_PROCESSING_STR);
//         case PCI_CLASS_ASIC:              return strcpy(buffer, PCI_CLASS_ASIC_STR);
//         default:                          return strcpy(buffer, "Unknown class");
//     }

// }