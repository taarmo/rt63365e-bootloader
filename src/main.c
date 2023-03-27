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
	//config_uart();
	uart_puts(buf);
	config_exceptions();
	//xxd(0x80000180,0x100,0x8);
	mips_gdb_stub_install();
	//__asm__ volatile ("li $a0, 0xfabada\n"
	//		  "li $a1, 0xfabada\n"
	//		  "li $a2, 0xfabada\n"
	//		  "li $a3, 0xfabada\n"
	//		  "li $k0, 0xfabada\n");

	__asm__ volatile ("break");
	//create_frame(WR_ENABLE,0x0,0x0);
	//create_frame(PAGE_PGRM,0x0,0x12345678);
	//write_frame(0x0,0x12345678);
	//__asm__ volatile ("j 0x80f00000"); //PROVOCAR EXCEPCION
	while (1){
		//value1=read_frame(0xbfc00044);
		//uart_printf("El valor es %x\n\r",value1);
		uart_debug_process();
		//reset();
	}
}
