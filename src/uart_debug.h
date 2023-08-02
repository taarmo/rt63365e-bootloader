#ifndef __PROXY_H__
#define __PROXY_H__

#include "types.h"


struct request{
	u32 opcode;
	u32 args[4];
};

struct reply {
	u32 val;
};

void uart_debug_process();

enum type_opcode{
	WRITE32_UART=0x100,
	WRITE8_UART,
	READ32_UART,
	READ8_UART,
	TIMER_COUNT,
	JUMP,
	LOAD_ELF,
	LOAD_KERNEL,
	WRITE_MEM_RAM,
	WRITE_MEM_FLASH,
	LCD,
	MALLOC,
	DOOM
};

#endif
