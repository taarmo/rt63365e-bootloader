#include "uart_debug.h"
#include "timer.h"
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
	init_irq();
	config_timer();
	//xxd(0x80000180,0x100,0x8);
	//mips_gdb_stub_install();
	//create_frame(WR_ENABLE,0x0,0x0);
	//create_frame(PAGE_PGRM,0x0,0x12345678);
	//write_frame(0x0,0x12345678);
	while (1) {
		//value1=read_frame(0xbfc00044);
		//uart_printf("El valor es %x\n\r",value1);
		//uart_printf("ra: %x", regs_init->reg32);
		//uart_puts("YEP\n\r");
		uart_debug_process();
		//reset();
	}
}
