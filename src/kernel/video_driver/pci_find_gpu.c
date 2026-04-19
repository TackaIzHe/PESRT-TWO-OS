#include "../uint.h"
#include "pci.h"
#include "../idt/io.h"
#include "../stdio.h"
#include "vendor.h"
// Чтение 32-битного значения из PCI-конфигурации
static inline uint32_t pci_read_config_dword(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset) {
    uint32_t address;
    uint32_t value;

    // Формируем адрес: [31] = 1 (включено), [23:16] = bus, [15:11] = device, [10:8] = function, [7:2] = offset
    address = (1U << 31) | ((uint32_t)bus << 16) | ((uint32_t)device << 11) | ((uint32_t)function << 8) | (offset & 0xFC);

    outl(PCI_CONFIG_ADDRESS_PORT, address);
    value = inl(PCI_CONFIG_DATA_PORT);

    return value;
}

// Чтение 16-битного Vendor ID
uint16_t pci_read_vendor_id(uint8_t bus, uint8_t device, uint8_t function) {
    return (uint16_t)(pci_read_config_dword(bus, device, function, PCI_VENDOR_ID_OFFSET) & 0xFFFF);
}

// Чтение 16-битного Device ID
uint16_t pci_read_device_id(uint8_t bus, uint8_t device, uint8_t function) {
    return (uint16_t)(pci_read_config_dword(bus, device, function, PCI_DEVICE_ID_OFFSET) >> 16);
}

// Чтение 8-битного класса устройства
uint8_t pci_read_class_code(uint8_t bus, uint8_t device, uint8_t function) {
    uint32_t reg = pci_read_config_dword(bus, device, function, PCI_CLASS_CODE_OFFSET);
    return (reg >> 24) & 0xFF;
}

// Поиск видеокарты
// Возвращает найденный BDF, или {0,0,0} если не найдено
pci_bdf_t pci_find_display_device(void) {
    pci_bdf_t result = {0, 0, 0};

    // printf("Сканирование PCI-шины...\n");

    for (uint8_t bus = 0; bus < 255; bus++) {
        for (uint8_t device = 0; device < 32; device++) {
            for (uint8_t function = 0; function < 8; function++) {
                uint16_t vendor_id = pci_read_vendor_id(bus, device, function);

                // Если Vendor ID == 0xFFFF — устройство не существует
                if (vendor_id == 0xFFFF) {
                    // Если функция 0 вернула 0xFFFF — это устройство отсутствует, пропускаем все функции
                    if (function == 0) {
                        // Проверим, что это не "специальное" устройство (редко, но бывает)
                        uint32_t first_word = pci_read_config_dword(bus, device, 0, PCI_VENDOR_ID_OFFSET);
                        if ((first_word & 0xFFFF) == 0xFFFF) {
                            break; // Пропускаем всё устройство
                        }
                    }
                    continue;
                }

                uint8_t class_code = pci_read_class_code(bus, device, function);

                // Отладка: показать все найденные устройства
                printf("PCI: %d:%d.%d | Vendor: 0x%d | Class: 0x%d \n",
                       (uint32_t)bus, (uint32_t)device, (uint32_t)function, (uint32_t)vendor_id, (uint32_t)class_code);

                // while (vendor_id != 17 && vendor_id != 0){}       
                // Проверяем: является ли устройство видеокартой?
                // if (class_code == PCI_CLASS_DISPLAY) {
                //     result.bus = bus;
                //     result.device = device;
                //     result.function = function;
                //     // printf("Card exist: %d:%d.%d\n", bus, device, function);
                //     return result;
                // }
            }
        }
    }

    // printf("CARD not found.\n");
    return result;
}

// Проверка: является ли устройство VGA-совместимым (дополнительно)
int pci_is_vga_compatible(uint8_t bus, uint8_t device, uint8_t function) {
    uint8_t class_code = pci_read_class_code(bus, device, function);
    uint8_t subclass = (pci_read_config_dword(bus, device, function, PCI_CLASS_CODE_OFFSET) >> 8) & 0xFF;
    return (class_code == PCI_CLASS_DISPLAY && subclass == PCI_SUBCLASS_VGA);
}
