#include "types.h"
#include "utils.h"
#include "vsprintf.h"
#include <stdarg.h>

//__attribute__ ((section(".init.uart")))
void config_uart() {
	write8((u32 *)0xbfbf0003, 1);
	write8((u32 *)0xbfbf0007, 0);
	write8((u32 *)0xbfbf000b, 0xf);
	write8((u32 *)0xbfbf000f, 3);
	write8((u32 *)0xbfbf0013, 0);
	write8((u32 *)0xbfbf0027, 0);
	write32((u32 *)0xbfbf002c, 0xea00fde8);
}

void uart_putb(u8 ch) {
	while(!((read8((u32 *)0xbfbf0017)) & 0x20));
	write8((u32 *)0xbfbf0003, ch);
}

void uart_puts(u8 *s) {
	while (*s) {
		uart_putb((*(s++)));
	}
}

void uart_write(void *buf, size_t count) {
	u8 *p = buf;

	while (count--)
		uart_putb(*p++);
}

int uart_printf(const char *fmt, ...) {
	char buffer[512];
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	uart_write(buffer, min(i, (int)(sizeof(buffer) - 1)));

	return i;
}

char uart_getb(){
	while(!((read8((u32 *)0xbfbf0017)) & 0x1));
	return read8((u32 *)0xbfbf0003);
}

void uart_read(u8 *buf,int size){
	u8 *p = buf;
	while(size--){
		*p++ = uart_getb();
	}	
	//*p = '\x00';
}

