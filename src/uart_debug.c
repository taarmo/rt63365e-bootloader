#include "regdef.h"
#include "uart.h"
#include "spi.h"
#include "utils.h"
#include "elf_loader.h"
#include "uart_debug.h"
#include "types.h"
#include "minlzma.h"

//extern u8 jump_zone[0x10000];
u8 input[972] __attribute__ ((aligned (32)));
u8 output[4287] __attribute__ ((aligned (32)));

void uart_debug_process() {
	u32 size_input = 972;
	u32 size_output = 4287;
	//u8 input[972];
	//u8 output[4287];

	//void *p;
	u32 value1,value2;
	struct request req;
	//struct reply rep;
	u32 addr;
	u32 val;
	u32 size;

	uart_read((u8*)&req, 16);
	//memcpy32(buf,&req,sizeof(struct request));
	//uart_write((u8 *)&req,4);
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
			mfc0(value1, C0_COUNT, 0);
			uart_write((u8 *)&value1, 4);
			uart_read((u8*)&req, 12);
			mfc0(value2, C0_COUNT, 0);
			value2 = value2-value1;
			uart_write((u8 *)&value2, 4);
			break;
		case TIMER_CMP:
			mtc0(val, C0_COMPARE, 0);
			val = 0x32;
			uart_write((u8 *)&val, 4);
			//val = read8((u32 *)req.args[0]);
			//__asm__ volatile("mfc0 %0,$9":"=r"(value1));
			break;
		case WRITE_MEM_FLASH:
			val = req.args[0];
			//write_frame(0x0,0x12345678,val);
			//xxd((u8 *)0xbfc00000,0x40,0x8);
			break;
		case WRITE_MEM_RAM:
			addr = req.args[0];
			size = req.args[1];
			uart_write((u8 *)&size, 4);
			//uart_read(jump_zone,size);
			uart_read(input, size);
			for(int i=0;i<4287;i++){
				output[i] = 0;
			}
			XzDecode(input, size_input, output, &size_output);
			xxd(output, 40, 0x8);
			//p = _main_elf(jump_zone);
			//void (*func)(void) = (void(*)(void))p;

			//u32 a = 0x80040000;
			//u32 b = 0x80050000;
			//while(a != b){
			//	cache(a,0x19);
			//	sync();
			//	cache(a,0x10);
			//	a+= 0x20;
			//}
			//func();
			//
			//
			break;
	}
	return;
}

