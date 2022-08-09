#include "types.h"
#include "uart.h"

void xxd(u8 *arr,u32 size,u32 col){
	uart_printf( "%x| ", (u32 *)arr);
	for(u8 i = 1; i < size; i++){
		uart_printf( "%02hhx ", *(arr+i-1) );
		if(!(i % col)){
			uart_puts("\n\r");
			uart_printf( "%x| ", (u32 *)(arr+i));
		}
	}
}	


