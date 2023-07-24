#include "types.h"


enum OP_FLASH {
	NOP = 0x0,
	WRR =	0x01,
	PAGE_PGRM = 0x2,
	READ = 0x3,
	WR_DISABLE = 0x4,
	RDSR = 0x5,
	WR_ENABLE = 0x6,
	ERASE = 0x7,
	CSLR = 0x8
};

void cslr();
void write_enable();
void write_status_register(u8, u8);
u16 read_statusreg();
void page_pgrm(u32, u8 *, u32);
void erase(u32 addr);
void flash(u32 addr, u8 *buf, u32 size);
