#include "proxy.h"
#include "uart.h"
#include "spi.h"
#include "utils.h"
#include "exceptions.h"

u8 *buf = "Bienvenido\n\r";
u32 *p = 0xbfc000a4;
u32 *q = 0xbfc000a8;


__attribute__ ((section(".text.main")))
void _main() {
u32 value1 = 0;
u32 value2;
  write32((u32 *)0xbfb40000, ((read32((u32 *)0xbfb40000)) | 0x40400));
  config_uart();
 uart_puts(buf);
 config_exceptions();
 //__asm__ volatile ("j 0x80f00000"); //PROVOCAR EXCEPCION
  while (1){
 	 value1 = build_frame(0x3,0x44); //50
	 //a0  --> 1a
	 //a8  --> 9a
	 //b0  --> 8
	 //b8  --> 9
 	 uart_printf("El valor es %x\n\r",value1);
	//uart_printf("El valor es %u\n\r",val);
	//spi_write(0,0x1);
	//proxy_process();
	  //reset();
  }
}
