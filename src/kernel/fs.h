#ifndef __FS_H__
#define __FS_H__

#include "uint.h"

void reset_disk(void);
void read_disk_sectors(uint32_t lba, uint32_t cnt, void *buf);

#endif