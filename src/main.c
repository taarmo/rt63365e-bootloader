#include "uart_debug.h"
#include "timer.h"
#include "uart.h"
#include "spi.h"
#include "flash.h"
#include "utils.h"
#include "exceptions.h"
#include "regdef.h"
#include "../lib/gdbstub/src/gdb_stub.h"

u8 *buf = (u8 *)"Bienvenido\n\r";
u8 arr[] = {0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf,0x10};

__attribute__ ((section(".text.main")))
void _main() {
	uart_puts(buf);
	config_exceptions();
	init_irq();
	//config_timer();
	//mips_gdb_stub_install();
	erase(0x3000);	
	while (1) {
		//value1=read_frame(0xbfc00044);
		//uart_printf("El valor es %x\n\r",value1);
		//uart_printf("ra: %x", regs_init->reg32);
		uart_debug_process();
	}
}
