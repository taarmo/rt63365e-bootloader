#include "uart.h"


void __main_stub(){
	while(1){
		uart_puts((u8 *)"Lo conseguiste");
	}
}
