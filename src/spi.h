
#ifndef __SPI_H__
#define __SPI_H__

#include "types.h"

enum OP_FLASH{
	DEFAULT = 0x0,
	PROGRAM = 0x2,
	READ = 0x3
};

u32 build_frame(enum OP_FLASH,u32 data);
u32 spi_read();
void spi_write(u32 off,u32 val);

#endif
