#include "utils.h"
#include "uart.h"

u8 *buf = "Bienvenido\n\r";
char *arr = "La direccion es 0x%x su contenido es 0x%x\n\r";
u32 *a = (u32 *)0xbfc00000;
u8 p[10];

void _main() {
  write32((u32 *)0xbfb40000, ((read32((u32 *)0xbfb40000)) | 0x40400));
  config_uart();
  
  uart_puts(buf);
  uart_printf(arr,a,*a);
  while (1){
	  uart_read(p,10);
	  uart_puts(p);
  }
}
