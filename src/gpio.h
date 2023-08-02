#include "types.h"

#define GPIO_BASE ((u32 *)0xbfbf0200)
#define CTRL ((u32 *)GPIO_BASE+0x0)
#define DATA ((u32 *)GPIO_BASE+0x4)
#define DRAIN ((u32 *)GPIO_BASE+0x14)

#define led1 ((u32 *)0xbfb00080)
#define led2 ((u32 *)0xbfb00834)

enum pin_state {
	OFF = 0,
	ON = 1
};

void gpiooff(u8);
void gpioon(u8);
void config_gpio(u8);
void control_dcx(enum pin_state);
void control_row_led(enum pin_state state);
void read_gpio();


