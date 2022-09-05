#ifndef __PROXY_H__
#define __PROXY_H__

#include "types.h"


struct request{
	u32 opcode;
	u32 args[2];
};

struct reply{
	u32 val;
};

void proxy_process();

enum type_opcode{
	WRITE32_UART=0x100,
	WRITE8_UART,
	READ32_UART,
	READ8_UART,
	TIMER_COUNT,
	TIMER_CMP,
	XXD
};

#endif
