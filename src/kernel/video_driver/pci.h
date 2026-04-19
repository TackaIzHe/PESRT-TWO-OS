#ifndef __PCI_H__
#define __PCI_H__

#include "../uint.h"
// Порты PCI конфигурации
#define PCI_CONFIG_ADDRESS_PORT 0xCF8
#define PCI_CONFIG_DATA_PORT    0xCFC

// Смещения в PCI-конфигурационном пространстве
#define PCI_VENDOR_ID_OFFSET    0x00
#define PCI_DEVICE_ID_OFFSET    0x02
#define PCI_CLASS_CODE_OFFSET   0x09
#define PCI_BASE_ADDRESS_0      0x10

// Классы устройств
#define PCI_CLASS_DISPLAY       0x03
#define PCI_SUBCLASS_VGA        0x00
#define PCI_SUBCLASS_3D         0x01

// Тип для хранения BDF (Bus, Device, Function)
typedef struct {
    uint8_t bus;
    uint8_t device;
    uint8_t function;
} pci_bdf_t;

int pci_is_vga_compatible(uint8_t bus, uint8_t device, uint8_t function);
pci_bdf_t pci_find_display_device(void);
uint8_t pci_read_class_code(uint8_t bus, uint8_t device, uint8_t function);
uint16_t pci_read_device_id(uint8_t bus, uint8_t device, uint8_t function);
uint16_t pci_read_vendor_id(uint8_t bus, uint8_t device, uint8_t function);

#endif