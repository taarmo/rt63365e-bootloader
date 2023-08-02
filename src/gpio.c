#include "gpio.h"
#include "utils.h"
#include "uart.h"

void control_dcx(enum pin_state state) {
	write32(led1, state << 5);
}

void control_row_led(enum pin_state state) {
	write32(led2, state << 24);
}
  
void config_gpio(u8 pin) {
	write32(CTRL, 1 << ((pin & 0xf) << 1) | read32(CTRL));
	write32(DRAIN, 1 << (pin & 0x1f)  | read32(DRAIN));
}
   
void gpiooff(u8 pin) {
	write32(DATA, 1 << (pin & 0x1f) | read32(DATA));
}
  
void gpioon(u8 pin) {
	write32(DATA, ~(1 << (pin & 0x1f)) & read32(DATA));
}

void read_gpio() {
	uart_printf("CTRL %x\n\r", read32(CTRL));
	uart_printf("DATA: %x\n\r", read32(DATA));
	uart_printf("drain %x\n\r", read32(DRAIN));
}
