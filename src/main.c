#include "uart_debug.h"
#include "uart.h"
#include "spi.h"
#include "utils.h"
#include "exceptions.h"

u8 *buf = (u8 *)"Bienvenido\n\r";
u8 jump_zone[0x10000];

__attribute__ ((section(".text.main")))
void _main() {
	write32((u32 *)0xbfb40000, ((read32((u32 *)0xbfb40000)) | 0x40400));
	config_uart();
	uart_puts(buf);
	config_exceptions();

	//create_frame(WR_ENABLE,0x0,0x0);
	//create_frame(PAGE_PGRM,0x0,0x12345678);
	//write_frame(0x0,0x12345678);
	//__asm__ volatile ("j 0x80f00000"); //PROVOCAR EXCEPCION
	while (1){
		//value1=read_frame(0xbfc00044);
		//uart_printf("El valor es %x\n\r",value1);
		proxy_uart_process();
		//reset();
	}
}
