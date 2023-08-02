#include "regdef.h"
#include "uart.h"
#include "spi.h"
#include "utils.h"
#include "elf_loader.h"
#include "gpio.h"
#include "uart_debug.h"
#include "cache.h"
#include "types.h"
#include "flash.h"
#include "minlzma.h"
#include "lcd.h"
#include "malloc.h"
//#include "play_doom.h"

u8* outputBuffer;

void uart_debug_process() {
	u8* inputBuffer;
	void *p;

	struct request req;
	//struct reply rep;
	u32 input_addr, output_addr;
	u32 input_size, output_size = 0;
	u32 val;
	u32 time_init,time_end;

	while (1) {
		uart_read((u8*)&req, sizeof(struct request));
		switch(req.opcode){
			case WRITE32_UART:
				val = 0x32;
				write32((u32 *)req.args[0], req.args[1]);
				uart_write((u8 *)&val, 4);
				break;
			case WRITE8_UART:
				val = 0x8;
				write8((u32 *)req.args[0], req.args[1]);
				uart_write((u8 *)&val, 4);
				break;
			case READ32_UART:
				input_addr = read32((u32 *)req.args[0]);
				uart_write((u8 *)&input_addr, 4);
				break;
			case READ8_UART:
				input_addr = read8((u32 *)req.args[0]);
				uart_write((u8 *)&input_addr, 4);
				break;
			case TIMER_COUNT:
				mfc0(time_init, C0_COUNT, 0);
				uart_write((u8 *)&time_init, 4);
				uart_read((u8*)&req, 12);
				mfc0(time_end, C0_COUNT, 0);
				time_end = time_end-time_init;
				uart_write((u8 *)&time_end, 4);
				break;
			case JUMP:
				input_addr = req.args[0];
				val = 0x32;
				uart_write((u8 *)&val, 4);
				jump((void *)input_addr);
				break;
			case LOAD_ELF:
				input_addr = req.args[0];
				input_size = req.args[1];
				inputBuffer = (u8 *) input_addr;

				uart_read(inputBuffer, input_size);
				p = _main_elf(inputBuffer);
				uart_write((u8 *)&input_size, 4);
				void (*func)(void) = (void(*)(void))p;
				flush_icache_range(input_addr, input_size);
				func();
				break;
			case LOAD_KERNEL:
				input_addr = req.args[0];
				output_addr = req.args[1];
				input_size = req.args[2];
				output_size = req.args[3];
				//inputBuffer = (u8 *) 0x81a00000;
				//outputBuffer = (u8 *) 0x80002000;
				inputBuffer = (u8 *) input_addr;
				outputBuffer = (u8 *) output_addr;

				uart_read(inputBuffer, input_size);
				XzDecode(inputBuffer, input_size, outputBuffer, &output_size);
				flush_icache_range(output_addr, output_size);
				uart_write((u8 *)&output_size, 4);
				break;	
			case WRITE_MEM_RAM:
				input_addr = req.args[0];
				input_size = req.args[1];
				inputBuffer = (u8 *)input_addr;

				uart_read(inputBuffer, input_size);
				uart_write((u8 *)&input_size, 4);
				break;
			case WRITE_MEM_FLASH:
				input_addr = req.args[0];
				input_size = req.args[1];
				inputBuffer = (u8 *) input_addr;

				uart_read(inputBuffer, input_size);
				flash(input_addr, inputBuffer, input_size);
				uart_write((u8 *)&input_size, 4);
				break;
			case LCD:
				//adjust_clk_spi(0x1);
				//init_lcd();
				//setRotation(2);
				//fillScreen(color565(0x00, 0x00, 0x00));
				//delay_us(100000);
				//for (u16 i = 1; i < 240; i++) {
				//	drawPixel(i, i, color565(0x00, 0x4d, 0xFF));
				//}
				//val = 7;
				uart_write((u8 *)&val, 4);
				break;
			case DOOM:
				input_size = req.args[0];
				output_size = req.args[1];
				inputBuffer = (u8 *) malloc(input_size);

				uart_read(inputBuffer, input_size);
				outputBuffer = (u8 *) malloc(output_size);
				XzDecode(inputBuffer, input_size, outputBuffer, &output_size);
				flush_icache_range((u32) inputBuffer, output_size);
				uart_write((u8 *)&outputBuffer, 4);
				//play_doom();
				break;
			case MALLOC:
				input_size = req.args[0];
				val = (u32 ) malloc(input_size);
				uart_write((u8 *)&val, 4);
				break;
		}
	}
	return;
}

