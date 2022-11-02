
#ifndef __SPI_H__
#define __SPI_H__

#include "types.h"

#define SPI_CTL_BUSY 0x00010000
#define SPI_ENABLE 0x00000100
#define SPI_CTL_TX_RX_CNT_MASK 0x000000ff

enum OP_FLASH{
	NOP = 0x0,
	WR_STATUS =	0x01,
	PAGE_PGRM = 0x2,
	READ = 0x3
};

u32 send_frame(enum OP_FLASH,u32 data);
u32 spi_read();
void spi_write(u32 off,u32 val);

#endif
