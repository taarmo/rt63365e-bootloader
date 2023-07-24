#include "regdef.h"
#include "uart.h"
#include "spi.h"
#include "utils.h"
#include "elf_loader.h"
#include "uart_debug.h"
#include "types.h"
#include "flash.h"
#include "minlzma.h"

u8 input[0x800000] __attribute__ ((aligned (32)));

void uart_debug_process() {
	struct request req;
	//struct reply rep;
	u32 addr;
	u32 val;
	u32 size;
	u32 time_init,time_end;

	uart_read((u8*)&req, 16);

	switch(req.opcode){
		case WRITE32_UART:
			write32((u32 *)req.args[0], req.args[1]);
			val = 0x32;
			uart_write((u8 *)&val, 4);
			break;
		case WRITE8_UART:
			write8((u32 *)req.args[0], req.args[1]);
			val = 0x8;
			uart_write((u8 *)&val, 4);
			break;
		case READ32_UART:
			addr = read32((u32 *)req.args[0]);
			uart_write((u8 *)&addr, 4);
			break;
		case READ8_UART:
			addr = read8((u32 *)req.args[0]);
			uart_write((u8 *)&addr, 4);
			break;
		case TIMER_COUNT:
			mfc0(time_init, C0_COUNT, 0);
			uart_write((u8 *)&time_init, 4);
			uart_read((u8*)&req, 12);
			mfc0(time_end, C0_COUNT, 0);
			time_end = time_end-time_init;
			uart_write((u8 *)&time_end, 4);
			break;
		case TIMER_CMP:
			mtc0(val, C0_COMPARE, 0);
			val = 0x32;
			uart_write((u8 *)&val, 4);
			//val = read8((u32 *)req.args[0]);
			//__asm__ volatile("mfc0 %0,$9":"=r"(time_init));
			break;
		case WRITE_MEM_RAM:
			addr = req.args[0];
			size = req.args[1];
			uart_read(input, size);
			flash(addr, input, size);
			while (1)
				xxd(input, size, 8);
			uart_write((u8 *)&size, 4);
			//uart_write((u8 *)&size, 4);
			//uart_read(jump_zone,size);
			//XzDecode(input, size_input, output, &size_output);
			//p = _main_elf(jump_zone);
			//void (*func)(void) = (void(*)(void))p;

			//func();
			break;
		case WRITE_MEM_FLASH:
			val = 0x1;
			uart_write((u8 *)&val, 4);
			//write_frame(0x0,0x12345678,val);
			//xxd((u8 *)0xbfc00000,0x40,0x8);
			break;
	}
	return;
}

