#include "utils.h"
#include "uart.h"
#include "spi.h"

struct op{
	enum OP_FLASH comm;
	u8 tx;
	u8 rx;
}stm_opcodes[] = {
	{NOP, 0, 0},
	{WR_STATUS, 2, 0},
	{PAGE_PGRM, 8, 0},
	{READ,4,4}
};


u32 send_frame(enum OP_FLASH op,u32 data){
		u32 reg = 0;
		u32 val = 0;
		while((val = read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);
		reg = (data&0xff00)<<16 | (data & 0xff)<<8 | stm_opcodes[op].comm & 0xff;
		write32(0xbfbc0004, reg);
		//write32(0xbfbc0004, stm_opcodes[op].comm);
		reg = (data & 0xff0000)<<8 | val & 0xff0000 | reg & ~SPI_CTL_TX_RX_CNT_MASK | stm_opcodes[op].rx<<4 | stm_opcodes[op].tx | SPI_ENABLE;
		write32(0xbfbc0000, reg);
		while((reg = read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);
		reg = read32(0xbfbc0008);
		return reg;
}

