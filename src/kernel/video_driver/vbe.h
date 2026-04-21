#ifndef __VBE_H__
#define __VBE_H__

#include "../uint.h"
#include "../int86.h"

#define VBE_EDID_MAGIC	"\0\xff\xff\xff\xff\xff\xff\0"

// VBE Info Block (возвращается при вызове INT 10h, AX=4F00h)
typedef struct {
    uint8_t sig[4];
	uint16_t version;
	uint32_t oem_str_ptr;
	uint8_t caps[4];			/* capabilities */
	uint32_t vid_mode_ptr;		/* vbefarptr to video mode list */
	uint16_t total_mem;			/* num of 64k mem blocks */
	uint16_t oem_sw_rev;		/* VBE implementation software revision */
	uint32_t oem_vendor_name_ptr;
	uint32_t oem_product_name_ptr;
	uint32_t oem_product_rev_ptr;
	uint8_t reserved[222];
	uint8_t oem_data[256];
} __attribute__((packed)) vbe_info_t;

// VBE Mode Info Block (возвращается при INT 10h, AX=4F01h, CX=режим)
typedef struct {
    uint16_t mode_attr;              // 0x00
    uint8_t  wina_attr;              // 0x02
    uint8_t  winb_attr;              // 0x03
    uint16_t win_gran;               // 0x04
    uint16_t win_size;               // 0x06
    uint16_t wina_seg;               // 0x08
    uint16_t winb_seg;               // 0x0A
    uint32_t win_func;               // 0x0C
    uint16_t scanline_bytes;         // 0x10 — bytes per scanline (VBE 1.2+)
    uint16_t xres;                   // 0x12
    uint16_t yres;                   // 0x14
    uint8_t  xcharsz;                // 0x16
    uint8_t  ycharsz;                // 0x17
    uint8_t  num_planes;             // 0x18
    uint8_t  bpp;                    // 0x19
    uint8_t  num_banks;              // 0x1A
    uint8_t  mem_model;              // 0x1B
    uint8_t  bank_size;              // 0x1C — bank size in KB
    uint8_t  num_img_pages;          // 0x1D
    uint8_t  reserved1;              // 0x1E — must be 0

    // Direct color fields (only valid if mem_model == 4)
    uint8_t  rmask_size;             // 0x1F — red mask size in bits
    uint8_t  rpos;                   // 0x20 — red bit position
    uint8_t  gmask_size;             // 0x21 — green mask size
    uint8_t  gpos;                   // 0x22 — green bit position
    uint8_t  bmask_size;             // 0x23 — blue mask size
    uint8_t  bpos;                   // 0x24 — blue bit position
    uint8_t  xmask_size;             // 0x25 — reserved/alpha mask size
    uint8_t  xpos;                   // 0x26 — reserved/alpha bit position
    uint8_t  cmode_info;             // 0x27 — direct color mode attributes

    // VBE 2.0+ fields
    uint32_t fb_addr;                // 0x28 — physical address of linear framebuffer
    uint16_t lin_bytes_per_scanline; // 0x2C — bytes per scanline in linear mode (VBE 3.0+)
    uint32_t reserved2;              // 0x2E — must be 0
    uint16_t reserved3;              // 0x32 — must be 0

    // Reserved padding to 512 bytes
    uint8_t  reserved4[512 - 0x34];  // 0x34 = 52 bytes used so far → 512 - 52 = 460 bytes
} __attribute__((packed)) vbe_mode_info_t;

typedef struct {
    uint8_t redgreen_xy_lsb;
	uint8_t bluewhite_xy_lsb;
	uint8_t redx_msb, redy_msb;
	uint8_t greenx_msb, greeny_msb;
	uint8_t bluex_msb, bluey_msb;
	uint8_t whitex_msb, whitey_msb;
} __attribute__((packed)) vbe_edid_chroma_t;

typedef struct {
    uint16_t dotclock;
	uint8_t hactive_lsb, hblank_lsb, hact_hblank_msb;
	uint8_t vactive_lsb, vblank_lsb, vact_vblank_msb;
	uint8_t hporch_lsb, hsync_lsb;
	uint8_t vporch_vsync_lsb;
	uint8_t hvporch_hvsync_msb;
	uint8_t hsize_lsb, vsize_lsb;	/* mm */
	uint8_t hsize_vsize_msb;
	uint8_t hborder, vborder;
	uint8_t features;
} __attribute__((packed)) vbe_edid_timing_t;

typedef struct {
    uint8_t magic[8];
	uint16_t vendor;
	uint16_t product;
	uint32_t serial;
	uint8_t week, year;
	uint8_t ver_major, ver_minor;

	uint8_t vidinp;
	uint8_t hsize, vsize;
	uint8_t gamma;
	uint8_t features;

	vbe_edid_chroma_t chroma;

	uint16_t modes_std;
	uint8_t modes_ext;
	uint16_t timing_std;

	vbe_edid_timing_t timing[4];
	uint8_t num_ext, csum;
} __attribute__((packed)) vbe_edid_t;

extern vbe_info_t vbe_info;
extern vbe_mode_info_t mode_info;

vbe_info_t *vbe_get_info(void);
vbe_mode_info_t *vbe_get_mode_info(int mode);
int vbe_set_mode(int mode);
void print_mode_info(vbe_mode_info_t *modei);
int vbe_get_edid(vbe_edid_t *edid);
int edid_preferred_resolution(vbe_edid_t *edid, int *xres, int *yres);
void print_edid(vbe_edid_t *edid);

#endif