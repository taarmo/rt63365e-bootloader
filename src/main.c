#include "uart_debug.h"
#include "timer.h"
#include "uart.h"
#include "spi.h"
#include "flash.h"
#include "exceptions.h"
#include "utils.h"
#include "lcd.h"
#include "timer.h"
#include "gpio.h"
#include "malloc.h"
#include "heapblock.h"
#include "regdef.h"
#include "gdb_stub.h"

u8 *buf = (u8 *)"Bienvenido\n\r";

__attribute__ ((section(".text.main")))
void _main() {
	uart_puts(buf);
	config_exceptions();
	heapblock_init();
	init_irq();
	//mips_gdb_stub_install();
	//config_timer();
	//config_high_precision_timer();
	//write32((u32 *) 0xbfb00038, read32((u32 *)0xbfb00038) | 0x80000000);
	uart_debug_process();
}
