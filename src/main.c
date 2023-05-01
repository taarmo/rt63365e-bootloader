#include "uart_debug.h"
#include "uart.h"
#include "spi.h"
#include "utils.h"
#include "exceptions.h"
#include "regdef.h"
#include "../lib/gdbstub/src/gdb_stub.h"

u8 *buf = (u8 *)"Bienvenido\n\r";
u8 jump_zone[0x10000];

__attribute__ ((section(".text.main")))
void _main() {
	uart_puts(buf);
	config_exceptions();
	mips_gdb_stub_install();

	__asm__ volatile ("break");
	__asm__ volatile ("nop\n"
			  "nop\n"
			  "nop\n"
			  "nop\n"
			  "nop\n"
			  "nop\n");
	//create_frame(WR_ENABLE,0x0,0x0);
	//create_frame(PAGE_PGRM,0x0,0x12345678);
	//write_frame(0x0,0x12345678);
	while (1){
		uart_debug_process();
	}
}
