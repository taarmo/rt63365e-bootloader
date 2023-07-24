#include "spi.h"
#include "flash.h"
#include "uart.h"
#include "utils.h"
#include "types.h"

struct t_comm stm_opcodes[] = {
	{NOP, 0, 0},
	{WRR, 2, 0},
	{PAGE_PGRM, 8, 0},
	{READ,4,4},
	{WR_DISABLE, 1, 0},
	{RDSR, 1, 2},
	{WR_ENABLE, 1, 0},
	{0x20,4,0},   //erase
	{0x30,1,0}    //cslr
};
void cslr() {
	send_cmd(stm_opcodes[CSLR], 0, 0);
}

void write_enable() {
	send_cmd(stm_opcodes[WR_ENABLE], 0x0, 0x0);
}

void write_status_register(u8 status, u8 data) {
	send_cmd(stm_opcodes[WRR], status, data);
}

u16 read_statusreg() {
	return send_cmd(stm_opcodes[RDSR], 0x0, 0x0);
}

void page_pgrm(u32 addr, u8 *buf, u32 size) {
	write_enable();
	spi_write(stm_opcodes[PAGE_PGRM].op, addr, buf, size);
	while (read_statusreg() & 0x1);
	//write32((u32 *)0xbfbc0038,0x1);
}

void erase(u32 addr) {
	write_enable();
	send_cmd(stm_opcodes[ERASE], addr, 0x0);
	while (read_statusreg() & 0x1);
	//write32((u32 *)0xbfbc0038,0x1);
}

void flash(u32 addr, u8 *buf, u32 size) {
	if ((addr + size) > 0x7f0000) return;

	u32 last_page = size%0x1000;
	u32 pages = size/0x1000;
	u32 p = 0x0;
	for(u32 i = 0; i < pages + (last_page > 0); i+=1) {
		erase(addr+(i*0x1000));	
	}
	u32 limit = pages*0x1000;

	while (p < limit && pages) {
		page_pgrm(addr+p, buf, 256);
		p+=256;
		buf+=256;
	}
	page_pgrm(addr+p, buf+p, last_page);

}
