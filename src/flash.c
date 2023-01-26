#include "spi.h"
#include "flash.h"
#include "types.h"

struct t_comm stm_opcodes[] = {
	{NOP, 0, 0},
	{WRR, 1, 1},
	{PAGE_PGRM, 8, 0},
	{READ,4,4},
	{WR_DISABLE, 1, 0},
	{RDSR, 2, 0},
	{WR_ENABLE, 1, 0},
	{ERASE,2,0}
};

void page_pgrm(u32 addr, u8 buf[256],u32 size){
	spi_write(0x2,addr,buf,size);
}

void erase(u32 addr){
	send_cmd(stm_opcodes[ERASE],addr,0x0);
}

