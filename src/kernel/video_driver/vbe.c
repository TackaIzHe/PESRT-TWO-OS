#include "../uint.h"
#include "../string.h"
#include "vbe.h"
#include "../stdio.h"
#include "../idt/tss.h"
#include "../first_kernel/kernel.h"

vbe_info_t vbe_info = {0};
vbe_mode_info_t vbe_mode_info = {0};

#define SEG_ADDR(s)	((uint32_t)(s) << 4)

#define MODE_LFB	(1 << 14)

vbe_info_t *vbe_get_info(void)
{
	vbe_info_t *info;
	vm86_regs_t regs;

	info = (vbe_info_t*)low_mem_buffer;

    
	memcpy((uint8_t*)info->sig, "VBE2", 4);

	memset((uint8_t*)&regs, 0, sizeof regs);
	regs.es = (uint32_t)info >> 4;
	regs.eax = 0x4f00;
	int86(0x10, &regs);

	if((regs.eax & 0xffff) != 0x4f) {
		return 0;
	}

	return info;
}

vbe_mode_info_t *vbe_get_mode_info(int mode)
{
	vbe_mode_info_t *mi;
	vm86_regs_t regs;

	mi = (vbe_mode_info_t*)(low_mem_buffer + 512);

	memset((uint8_t*)&regs, 0, sizeof regs);
	regs.es = (uint32_t)mi >> 4;
	regs.eax = 0x4f01;
	regs.ecx = mode;
	int86(0x10, &regs);

	if((regs.eax & 0xffff) != 0x4f) {
		return 0;
	}

	return mi;
}

int vbe_set_mode(int mode)
{
	vm86_regs_t regs;

	memset((uint8_t*)&regs, 0, sizeof regs);
	regs.eax = 0x4f02;
	regs.ebx = mode;
	int86(0x10, &regs);

	if(regs.eax == 0x100) {
		return -1;
	}
	return 0;
}

void print_mode_info(vbe_mode_info_t *mi)
{
	static unsigned int maskbits[] = {0, 1, 3, 7, 0xf, 0x1f, 0x3f, 0x7f, 0xff};

	printf("resolution: %dx%d\n", mi->xres, mi->yres);
	printf("color depth: %d\n", mi->bpp);
	printf("mode attributes: %x\n", mi->mode_attr);
	printf("bytes per scanline: %d\n", mi->scanline_bytes);
	printf("number of planes: %d\n", (int)mi->num_planes);
	printf("number of banks: %d\n", (int)mi->num_banks);
	printf("mem model: %d\n", (int)mi->mem_model);
	printf("red bits: %d (mask: %x)\n", (int)mi->rmask_size, maskbits[mi->rmask_size] << mi->rpos);
	printf("green bits: %d (mask: %x)\n", (int)mi->gmask_size, maskbits[mi->gmask_size] << mi->gpos);
	printf("blue bits: %d (mask: %x)\n", (int)mi->bmask_size, maskbits[mi->bmask_size] << mi->bpos);
	printf("framebuffer address: %x\n", (unsigned int)mi->fb_addr);
}

int vbe_get_edid(vbe_edid_t *edid)
{
	vm86_regs_t regs;

	memset((uint8_t*)&regs, 0, sizeof regs);
	regs.es = (uint32_t)low_mem_buffer >> 4;
	regs.eax = 0x4f15;
	regs.ebx = 1;
	int86(0x10, &regs);

	if((regs.eax & 0xffff) != 0x4f) {
		return -1;
	}
	memcpy((uint8_t*)edid, low_mem_buffer, sizeof *edid);
	return 0;
}

int edid_preferred_resolution(vbe_edid_t *edid, int *xres, int *yres)
{
	if(memcmp((uint8_t*)edid->magic, VBE_EDID_MAGIC, 8) != 0) {
		return -1;
	}

	*xres = (int)edid->timing[0].hactive_lsb | ((int)(edid->timing[0].hact_hblank_msb & 0xf0) << 4);
	*yres = (int)edid->timing[0].vactive_lsb | ((int)(edid->timing[0].vact_vblank_msb & 0xf0) << 4);
	return 0;
}

void print_edid(vbe_edid_t *edid)
{
	char vendor[4];
	int xres, yres;

	if(memcmp((uint8_t*)edid->magic, VBE_EDID_MAGIC, 8) != 0) {
		printf("invalid EDID magic\n");
		return;
	}

	vendor[0] = (edid->vendor >> 10) & 0x1f;
	vendor[1] = (edid->vendor >> 5) & 0x1f;
	vendor[2] = edid->vendor & 0x1f;
	vendor[3] = 0;
	printf("Manufacturer: %s\n", vendor);

	edid_preferred_resolution(edid, &xres, &yres);
	printf("Preferred resolution: %dx%d\n", xres, yres);
}
