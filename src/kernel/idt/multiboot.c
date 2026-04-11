#define MULTIBOOT_MAGIC 0x1BADB002
#define MULTIBOOT_FLAGS 0x00010003   /* align + mem-info */
#define MULTIBOOT_CHECKSUM -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

#include "../uint.h"

__attribute__((section(".multiboot"), aligned(4)))
static const struct {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
} mbhdr = {
    MULTIBOOT_MAGIC,
    MULTIBOOT_FLAGS,
    MULTIBOOT_CHECKSUM
};