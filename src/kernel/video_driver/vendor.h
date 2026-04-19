#ifndef __VENDOR_H__
#define __VENDOR_H__

/* GPU Vendor ID Definitions */
#define GPU_VENDOR_AMD      0x1002   /* AMD Radeon, Instinct */
#define GPU_VENDOR_NVIDIA   0x10DE   /* NVIDIA GeForce, RTX, Tesla */
#define GPU_VENDOR_INTEL    0x8086   /* Intel Iris Xe, Arc */
#define GPU_VENDOR_APPLE    0x106B   /* Apple Silicon (M1/M2/M3) */
#define GPU_VENDOR_MATROX   0x1014   /* Matrox professional GPUs */
#define GPU_VENDOR_S3       0x10E0   /* S3 Graphics (legacy) */
#define GPU_VENDOR_CIRRUS   0x1013   /* Cirrus Logic (legacy) */
#define GPU_VENDOR_ATI      0x100A   /* ATI (pre-AMD acquisition, legacy) */

/* Virtual GPU Vendor IDs (for VM environments) */
#define GPU_VENDOR_VIRTUALBOX 0x1234 /* Oracle VirtualBox */
#define GPU_VENDOR_VMWARE     0x15AD /* VMware SVGA */
#define GPU_VENDOR_MICROSOFT  0x1414 /* Microsoft Hyper-V Basic Display */

/* Legacy / Rare / Special Cases */
#define GPU_VENDOR_PLX        0x10B5 /* PLX Technology (PCIe bridges, rarely GPU) */
#define GPU_VENDOR_IBM        0x1014   /* IBM POWER GPUs (legacy) */

/* === Основные производители USB-контроллеров === */

#define USB_VENDOR_INTEL          0x8086   /* Intel */
#define USB_VENDOR_AMD            0x1022   /* AMD */
#define USB_VENDOR_AS MEDIA       0x1b21   /* Asmedia */
#define USB_VENDOR_RENESAS        0x11c1   /* Renesas (наследник NEC) */
#define USB_VENDOR_MICROCHIP      0x0424   /* Microchip (ex-SMSC) */
#define USB_VENDOR_QUALCOMM       0x05c6   /* Qualcomm */
#define USB_VENDOR_TEXAS          0x17cc   /* Texas Instruments */
#define USB_VENDOR_FRESCO         0x10ce   /* Fresco Logic */
#define USB_VENDOR_MICROSOFT      0x045e   /* Microsoft (Hyper-V, Surface) */
#define USB_VENDOR_CYPRESS        0x1c1c   /* Cypress (now Infineon) */
#define USB_VENDOR_PERICOM        0x12d8   /* Pericom (Diodes Inc.) */
#define USB_VENDOR_LINUX          0x1b6b   /* Linux Foundation (USB Gadget) */

/* === Дополнительные производители === */

#define USB_VENDOR_ASUSTEK        0x1043   /* ASUS */
#define USB_VENDOR_ACER           0x057c   /* Acer */
#define USB_VENDOR_CHICONY        0x04f2   /* Chicony */
#define USB_VENDOR_SANDISK        0x0781   /* SanDisk / Lexar (встроенные контроллеры) */
#define USB_VENDOR_NEC            0x1033   /* NEC (устаревший, но встречается) */

// ======================
// Wi-Fi Adapters
// ======================
#define USB_VENDOR_ATHEROS      0x07b8  // Qualcomm Atheros (AR9271, AR7010)
#define USB_VENDOR_REALTEK      0x0bda  // RTL8188EU, RTL8192EU, RTL8811AU, RTL8812AU
#define USB_VENDOR_RALINK       0x148f  // Ralink/MTK (RT2870, RT3070, RT3572)
#define USB_VENDOR_BUFFALO      0x0489  // Buffalo (often Realtek-based)
#define USB_VENDOR_DLINK        0x07d1  // D-Link (DWA-121, DWA-131)
#define USB_VENDOR_NETGEAR      0x0846  // Netgear (A6100, A6200)
#define USB_VENDOR_LINKSYS      0x13b1  // Linksys (USB300M, USB200M)
#define USB_VENDOR_ASUS         0x0b05  // ASUS USB Wi-Fi adapters
#define USB_VENDOR_TENDA        0x0fd9  // Tenda (U3, etc.)
#define USB_VENDOR_IMC          0x13d3  // IMC Networks (Lenovo/ASUS OEM)
#define USB_VENDOR_SONY         0x056c  // Sony integrated Wi-Fi modules
#define USB_VENDOR_SISVEL       0x14b5  // Sisvel (OEM for Realtek)

// ======================
// USB Ethernet Adapters
// ======================
#define USB_VENDOR_ASIX         0x0b95  // AX88772, AX88179 (high-quality)
#define USB_VENDOR_PROLIFIC     0x067b  // PL2501, PL2502 (common in cheap adapters)
#define USB_VENDOR_APPLE        0x05ac  // Apple USB Ethernet Adapter
#define USB_VENDOR_SAMSUNG      0x04e8  // Samsung USB Ethernet (DeX)
#define USB_VENDOR_FOXCONN      0x0489  // Foxconn (often same as Buffalo, OEM for many)
#define USB_VENDOR_GENESYS      0x05e3  // Genesys Logic (USB hubs with Ethernet)
#define USB_VENDOR_NECS         0x0409  // NEC (legacy USB Ethernet)
#define USB_VENDOR_BELKIN       0x050d  // Belkin (F5D7050, etc.)
#define USB_VENDOR_IODATA       0x04bb  // I-O DATA (Japan market)
#define USB_VENDOR_SITECOM      0x0df6  // Sitecom USB Ethernet

/* ================================================
 * GPU Vendor ID String Definitions
 * ================================================ */
#define GPU_VENDOR_AMD_STR        "AMD Radeon / Instinct"
#define GPU_VENDOR_NVIDIA_STR     "NVIDIA GeForce / RTX / Tesla"
#define GPU_VENDOR_INTEL_STR      "Intel Iris Xe / Arc"
#define GPU_VENDOR_APPLE_STR      "Apple Silicon (M1/M2/M3)"
#define GPU_VENDOR_MATROX_STR     "Matrox Professional GPUs"
#define GPU_VENDOR_S3_STR         "S3 Graphics (Legacy)"
#define GPU_VENDOR_CIRRUS_STR     "Cirrus Logic (Legacy)"
#define GPU_VENDOR_ATI_STR        "ATI (Pre-AMD Acquisition, Legacy)"
#define GPU_VENDOR_VIRTUALBOX_STR "Oracle VirtualBox"
#define GPU_VENDOR_VMWARE_STR     "VMware SVGA"
#define GPU_VENDOR_MICROSOFT_STR  "Microsoft Hyper-V Basic Display"
#define GPU_VENDOR_PLX_STR        "PLX Technology (PCIe Bridge)"
#define GPU_VENDOR_IBM_STR        "IBM POWER GPUs (Legacy)"

/* ================================================
 * USB Controller Vendor String Definitions
 * ================================================ */
#define USB_VENDOR_INTEL_STR      "Intel"
#define USB_VENDOR_AMD_STR        "AMD"
#define USB_VENDOR_AS_MEDIA_STR   "Asmedia"
#define USB_VENDOR_RENESAS_STR    "Renesas (ex-NEC)"
#define USB_VENDOR_MICROCHIP_STR  "Microchip (ex-SMSC)"
#define USB_VENDOR_QUALCOMM_STR   "Qualcomm"
#define USB_VENDOR_TEXAS_STR      "Texas Instruments"
#define USB_VENDOR_FRESCO_STR     "Fresco Logic"
#define USB_VENDOR_MICROSOFT_STR  "Microsoft (Hyper-V, Surface)"
#define USB_VENDOR_CYPRESS_STR    "Cypress (now Infineon)"
#define USB_VENDOR_PERICOM_STR    "Pericom (Diodes Inc.)"
#define USB_VENDOR_LINUX_STR      "Linux Foundation (USB Gadget)"

/* ================================================
 * Additional USB Vendor String Definitions
 * ================================================ */
#define USB_VENDOR_ASUSTEK_STR    "ASUS"
#define USB_VENDOR_ACER_STR       "Acer"
#define USB_VENDOR_CHICONY_STR    "Chicony"
#define USB_VENDOR_SANDISK_STR    "SanDisk / Lexar"
#define USB_VENDOR_NEC_STR        "NEC (Legacy)"

/* ================================================
 * Wi-Fi Adapter Vendor String Definitions
 * ================================================ */
#define USB_VENDOR_ATHEROS_STR    "Qualcomm Atheros"
#define USB_VENDOR_REALTEK_STR    "Realtek Semiconductor"
#define USB_VENDOR_RALINK_STR     "Ralink / MediaTek"
#define USB_VENDOR_BUFFALO_STR    "Buffalo"
#define USB_VENDOR_DLINK_STR      "D-Link"
#define USB_VENDOR_NETGEAR_STR    "Netgear"
#define USB_VENDOR_LINKSYS_STR    "Linksys"
#define USB_VENDOR_ASUS_STR       "ASUS"
#define USB_VENDOR_TENDA_STR      "Tenda"
#define USB_VENDOR_IMC_STR        "IMC Networks (OEM)"
#define USB_VENDOR_SONY_STR       "Sony"
#define USB_VENDOR_SISVEL_STR     "Sisvel (OEM)"

/* ================================================
 * USB Ethernet Adapter Vendor String Definitions
 * ================================================ */
#define USB_VENDOR_ASIX_STR       "ASIX Electronics"
#define USB_VENDOR_PROLIFIC_STR   "Prolific Technology"
#define USB_VENDOR_APPLE_STR      "Apple"
#define USB_VENDOR_SAMSUNG_STR    "Samsung"
#define USB_VENDOR_FOXCONN_STR    "Foxconn (Hon Hai)"
#define USB_VENDOR_GENESYS_STR    "Genesys Logic"
#define USB_VENDOR_NECS_STR       "NEC (Legacy USB Ethernet)"
#define USB_VENDOR_BELKIN_STR     "Belkin"
#define USB_VENDOR_IODATA_STR     "I-O DATA"
#define USB_VENDOR_SITECOM_STR    "Sitecom"


#endif