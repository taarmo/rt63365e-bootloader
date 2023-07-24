
#ifndef __SPI_H__
#define __SPI_H__

#include "types.h"


#define SPI_CTL_BUSY 0x00010000
#define SPI_ENABLE 0x00000100
#define SPI_CTL_TX_RX_CNT_MASK 0x000000ff


struct t_comm{
	u32 op;
	u8 tx;
	u8 rx;
};

u32 send_cmd(struct t_comm , u32, u32);
void spi_write(u8, u32, u8 *, u32);

#endif
