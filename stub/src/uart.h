
#ifndef __UART_H__
#define __UART_H__

#include "types.h"
#include <stdarg.h>

void config_uart();
char uart_getb();
void uart_read(u8 *, int);

void uart_putb(u8);
void uart_puts(u8 *);
void uart_write(void *,size_t count);
int uart_printf(const char *fmt, ...);

#endif
