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

// =========================
// PCI CLASS CODES (8-bit)
// =========================

#define PCI_CLASS_PRE_2_0           0x00
#define PCI_CLASS_MASS_STORAGE      0x01
#define PCI_CLASS_NETWORK           0x02
#define PCI_CLASS_DISPLAY           0x03
#define PCI_CLASS_MULTIMEDIA        0x04
#define PCI_CLASS_MEMORY            0x05
#define PCI_CLASS_BRIDGE            0x06
#define PCI_CLASS_COMMUNICATION     0x07
#define PCI_CLASS_SYSTEM_PERIPHERAL 0x08
#define PCI_CLASS_INPUT             0x09
#define PCI_CLASS_DOCKING           0x0A
#define PCI_CLASS_PROCESSOR         0x0B
#define PCI_CLASS_SERIAL_BUS        0x0C
#define PCI_CLASS_WIRELESS          0x0D
#define PCI_CLASS_INTELLIGENT       0x0E
#define PCI_CLASS_SATELLITE         0x0F
#define PCI_CLASS_ENCRYPTION        0x10
#define PCI_CLASS_SIGNAL_PROCESSING 0x11
#define PCI_CLASS_ASIC              0x12

#define PCI_CLASS_PRE_2_0_STR           "Pre-2.0"
#define PCI_CLASS_MASS_STORAGE_STR      "Mass Storage Controller"
#define PCI_CLASS_NETWORK_STR           "Network Controller"
#define PCI_CLASS_DISPLAY_STR           "Display Controller"
#define PCI_CLASS_MULTIMEDIA_STR        "Multimedia Controller"
#define PCI_CLASS_MEMORY_STR            "Memory Controller"
#define PCI_CLASS_BRIDGE_STR            "Bridge Device"
#define PCI_CLASS_COMMUNICATION_STR     "Communication Controller"
#define PCI_CLASS_SYSTEM_PERIPHERAL_STR "System Peripheral"
#define PCI_CLASS_INPUT_STR             "Input Device"
#define PCI_CLASS_DOCKING_STR           "Docking Station"
#define PCI_CLASS_PROCESSOR_STR         "Processor"
#define PCI_CLASS_SERIAL_BUS_STR        "Serial Bus Controller"
#define PCI_CLASS_WIRELESS_STR          "Wireless Controller"
#define PCI_CLASS_INTELLIGENT_STR       "Intelligent Controller"
#define PCI_CLASS_SATELLITE_STR         "Satellite Controller"
#define PCI_CLASS_ENCRYPTION_STR        "Encryption Controller"
#define PCI_CLASS_SIGNAL_PROCESSING_STR "Signal Processing Controller"
#define PCI_CLASS_ASIC_STR              "ASIC"


// Reserved classes (0x13 to 0xFF) — not defined here

// =========================
// PCI SUBCLASS CODES (8-bit)
// =========================

// Mass Storage Controller (0x01)
#define PCI_SUBCLASS_MASS_STORAGE_SCSI        0x00
#define PCI_SUBCLASS_MASS_STORAGE_IDE         0x01
#define PCI_SUBCLASS_MASS_STORAGE_FLOPPY      0x02
#define PCI_SUBCLASS_MASS_STORAGE_IPI         0x03
#define PCI_SUBCLASS_MASS_STORAGE_RAID        0x04
#define PCI_SUBCLASS_MASS_STORAGE_ATA         0x05
#define PCI_SUBCLASS_MASS_STORAGE_SATA        0x06
#define PCI_SUBCLASS_MASS_STORAGE_SAS         0x07
#define PCI_SUBCLASS_MASS_STORAGE_OTHER       0x80

// Network Controller (0x02)
#define PCI_SUBCLASS_NETWORK_ETHERNET         0x00
#define PCI_SUBCLASS_NETWORK_TOKEN_RING       0x01
#define PCI_SUBCLASS_NETWORK_FDDI             0x02
#define PCI_SUBCLASS_NETWORK_ATM              0x03
#define PCI_SUBCLASS_NETWORK_ISDN             0x04
#define PCI_SUBCLASS_NETWORK_WORLDFIP         0x05
#define PCI_SUBCLASS_NETWORK_PICMG            0x06
#define PCI_SUBCLASS_NETWORK_INFINIBAND       0x07
#define PCI_SUBCLASS_NETWORK_OTHER            0x80

// Display Controller (0x03)
#define PCI_SUBCLASS_DISPLAY_VGA              0x00
#define PCI_SUBCLASS_DISPLAY_XGA              0x01
#define PCI_SUBCLASS_DISPLAY_3D               0x02
#define PCI_SUBCLASS_DISPLAY_OTHER            0x80

// Multimedia Controller (0x04)
#define PCI_SUBCLASS_MULTIMEDIA_VIDEO         0x00
#define PCI_SUBCLASS_MULTIMEDIA_AUDIO         0x01
#define PCI_SUBCLASS_MULTIMEDIA_TELEPHONY     0x02
#define PCI_SUBCLASS_MULTIMEDIA_AUDIO_VIDEO   0x03
#define PCI_SUBCLASS_MULTIMEDIA_OTHER         0x80

// Memory Controller (0x05)
#define PCI_SUBCLASS_MEMORY_RAM               0x00
#define PCI_SUBCLASS_MEMORY_FLASH             0x01
#define PCI_SUBCLASS_MEMORY_OTHER             0x80

// Bridge Device (0x06)
#define PCI_SUBCLASS_BRIDGE_HOST_TO_PCI       0x00
#define PCI_SUBCLASS_BRIDGE_PCI_TO_PCI        0x01
#define PCI_SUBCLASS_BRIDGE_PCI_TO_CARDBUS    0x02
#define PCI_SUBCLASS_BRIDGE_PCI_TO_PMC        0x03
#define PCI_SUBCLASS_BRIDGE_PCI_TO_ISA        0x04
#define PCI_SUBCLASS_BRIDGE_PCI_TO_EISA       0x05
#define PCI_SUBCLASS_BRIDGE_PCI_TO_MCA        0x06
#define PCI_SUBCLASS_BRIDGE_PCI_TO_AGP        0x07
#define PCI_SUBCLASS_BRIDGE_PCI_TO_PCIX       0x08
#define PCI_SUBCLASS_BRIDGE_PCI_TO_PCIE       0x09
#define PCI_SUBCLASS_BRIDGE_OTHER             0x80

// Communication Controller (0x07)
#define PCI_SUBCLASS_COMMUNICATION_SERIAL     0x00
#define PCI_SUBCLASS_COMMUNICATION_PARALLEL   0x01
#define PCI_SUBCLASS_COMMUNICATION_MULTIPORT  0x02
#define PCI_SUBCLASS_COMMUNICATION_MODEM      0x03
#define PCI_SUBCLASS_COMMUNICATION_GSP        0x04
#define PCI_SUBCLASS_COMMUNICATION_ISDN       0x05
#define PCI_SUBCLASS_COMMUNICATION_NFC        0x06
#define PCI_SUBCLASS_COMMUNICATION_OTHER      0x80

// System Peripheral (0x08)
#define PCI_SUBCLASS_SYSTEM_PIC               0x00
#define PCI_SUBCLASS_SYSTEM_DMA               0x01
#define PCI_SUBCLASS_SYSTEM_TIMER             0x02
#define PCI_SUBCLASS_SYSTEM_RTC               0x03
#define PCI_SUBCLASS_SYSTEM_HOTPLUG           0x04
#define PCI_SUBCLASS_SYSTEM_SD_HOST           0x05
#define PCI_SUBCLASS_SYSTEM_IOMMU             0x06
#define PCI_SUBCLASS_SYSTEM_OTHER             0x80

// Input Device Controller (0x09)
#define PCI_SUBCLASS_INPUT_KEYBOARD           0x00
#define PCI_SUBCLASS_INPUT_DIGITIZER          0x01
#define PCI_SUBCLASS_INPUT_MOUSE              0x02
#define PCI_SUBCLASS_INPUT_SCANNER            0x03
#define PCI_SUBCLASS_INPUT_GAMEPORT           0x04
#define PCI_SUBCLASS_INPUT_OTHER              0x80

// Docking Station (0x0A)
#define PCI_SUBCLASS_DOCKING_GENERIC          0x00
#define PCI_SUBCLASS_DOCKING_OTHER            0x80

// Processor (0x0B)
#define PCI_SUBCLASS_PROCESSOR_386            0x00
#define PCI_SUBCLASS_PROCESSOR_486            0x01
#define PCI_SUBCLASS_PROCESSOR_PENTIUM        0x02
#define PCI_SUBCLASS_PROCESSOR_ALPHA          0x10
#define PCI_SUBCLASS_PROCESSOR_POWERPC        0x20
#define PCI_SUBCLASS_PROCESSOR_MIPS           0x30
#define PCI_SUBCLASS_PROCESSOR_CO_PROCESSOR   0x40

// Serial Bus Controller (0x0C)
#define PCI_SUBCLASS_SERIAL_BUS_FIREWIRE      0x00
#define PCI_SUBCLASS_SERIAL_BUS_ACCESS_BUS    0x01
#define PCI_SUBCLASS_SERIAL_BUS_USB           0x03
#define PCI_SUBCLASS_SERIAL_BUS_FIBER_CHANNEL 0x04
#define PCI_SUBCLASS_SERIAL_BUS_SMBUS         0x05
#define PCI_SUBCLASS_SERIAL_BUS_INFINIBAND    0x06
#define PCI_SUBCLASS_SERIAL_BUS_IPMI          0x07
#define PCI_SUBCLASS_SERIAL_BUS_SERCOS        0x08
#define PCI_SUBCLASS_SERIAL_BUS_CANBUS        0x09
#define PCI_SUBCLASS_SERIAL_BUS_OTHER         0x80

// Wireless Controller (0x0D)
#define PCI_SUBCLASS_WIRELESS_IRDA            0x00
#define PCI_SUBCLASS_WIRELESS_CONSUMER_IR     0x01
#define PCI_SUBCLASS_WIRELESS_RF              0x02
#define PCI_SUBCLASS_WIRELESS_BLUETOOTH       0x03
#define PCI_SUBCLASS_WIRELESS_BROADBAND       0x04
#define PCI_SUBCLASS_WIRELESS_802_11          0x05
#define PCI_SUBCLASS_WIRELESS_OTHER           0x80

// Intelligent Controller (0x0E)
#define PCI_SUBCLASS_INTELLIGENT_I2O          0x00

// Satellite Communication (0x0F)
#define PCI_SUBCLASS_SATELLITE_TV             0x00
#define PCI_SUBCLASS_SATELLITE_AUDIO          0x01
#define PCI_SUBCLASS_SATELLITE_VOICE          0x02
#define PCI_SUBCLASS_SATELLITE_DATA           0x03

// Encryption/Decryption (0x10)
#define PCI_SUBCLASS_ENCRYPTION_NETWORK       0x00
#define PCI_SUBCLASS_ENCRYPTION_ENTERTAINMENT 0x01
#define PCI_SUBCLASS_ENCRYPTION_OTHER         0x02

// Signal Processing (0x11)
#define PCI_SUBCLASS_SIGNAL_PROCESSING_DPIO   0x00
#define PCI_SUBCLASS_SIGNAL_PROCESSING_DSP    0x01

// ASIC (0x12) — no subclasses defined

// =========================
// PCI PROGIF (Programming Interface) CODES (8-bit)
// =========================

// For Display Controller (Class 0x03)
#define PCI_PROGIF_DISPLAY_VGA_COMPATIBLE     0x00
#define PCI_PROGIF_DISPLAY_XGA                0x01
#define PCI_PROGIF_DISPLAY_3D_CONTROLLER      0x02

// For Mass Storage (Class 0x01)
#define PCI_PROGIF_MASS_STORAGE_IDE_PRIMARY   0x01
#define PCI_PROGIF_MASS_STORAGE_IDE_SECONDARY 0x05
#define PCI_PROGIF_MASS_STORAGE_SATA          0x01
#define PCI_PROGIF_MASS_STORAGE_AHCI          0x01

// For Network (Class 0x02)
#define PCI_PROGIF_NETWORK_ETHERNET           0x00

// For Serial Bus (Class 0x0C)
#define PCI_PROGIF_SERIAL_BUS_USB_OHCI        0x10
#define PCI_PROGIF_SERIAL_BUS_USB_EHCI        0x20
#define PCI_PROGIF_SERIAL_BUS_USB_XHCI        0x30

// For Bridge (Class 0x06)
#define PCI_PROGIF_BRIDGE_HOST_TO_PCI         0x00

// For System Peripheral (Class 0x08)
#define PCI_PROGIF_SYSTEM_PIC_I8259           0x00
#define PCI_PROGIF_SYSTEM_DMA_I8237           0x00
#define PCI_PROGIF_SYSTEM_TIMER_I8253         0x00

// Generic "Other" or undefined
#define PCI_PROGIF_OTHER                      0x80


// Тип для хранения BDF (Bus, Device, Function)
typedef struct {
    uint8_t  bus;
    uint8_t  device;
    uint8_t  function;
    uint16_t vendor;
    uint16_t class;
    uint8_t  base_class;
    uint8_t  sub_class;
    uint8_t  prog_if;
    uint8_t  flag;
} pci_bdf_t;

typedef struct {
    uint8_t bar_id;
    uint32_t bar_addr;
} video_card_bar;

extern pci_bdf_t pci_devices[512];
extern video_card_bar card_bar[6];

uint32_t check_GPU_BAR(void);
uint8_t check_GPU_class(void);
uint8_t check_GPU_revision_id(void);
uint32_t get_GPU_memory(void);
void set_vga_mode_13h(void);
void set_vga_mode_1920x1080(void);

void pci_find_device(void);
void print_PCI_devices(void);
uint32_t get_GPU_index(void);
int pci_is_vga_compatible(uint8_t bus, uint8_t device, uint8_t function);
uint8_t pci_read_class_code(uint8_t bus, uint8_t device, uint8_t function);
uint16_t pci_read_device_id(uint8_t bus, uint8_t device, uint8_t function);
uint16_t pci_read_vendor_id(uint8_t bus, uint8_t device, uint8_t function);

#endif