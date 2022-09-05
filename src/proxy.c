#include "uart.h"
#include "utils.h"
#include "proxy.h"


void proxy_process(){
	u32 value1,value2;
	struct request req;
	//struct reply rep;
	u32 val;

	uart_read((u8*)&req,12);
	//memcpy32(buf,&req,sizeof(struct request));
	//uart_write((u8 *)&req,4);
	switch(req.opcode){
		case WRITE32_UART:
			write32((u32 *)req.args[0],req.args[1]);
			val = 0x32;
			uart_write((u8 *)&val,4);
			break;
		case WRITE8_UART:
			write8((u32 *)req.args[0],req.args[1]);
			val = 0x8;
			uart_write((u8 *)&val,4);
			break;
		case READ32_UART:
			val = read32((u32 *)req.args[0]);
			uart_write((u8 *)&val,4);
			break;
		case READ8_UART:
			val = read8((u32 *)req.args[0]);
			uart_write((u8 *)&val,4);
			break;
		case TIMER_COUNT:
			mfc0(value1,$9,0);
			uart_write((u8 *)&value1,4);
			uart_read((u8*)&req,12);
			mfc0(value2,$9,0);
			value2 = value2-value1;
			uart_write((u8 *)&value2,4);
			break;
		case TIMER_CMP:
			mtc0(val,$11,0);
			val = 0x32;
			uart_write((u8 *)&val,4);
			//val = read8((u32 *)req.args[0]);
			//__asm__ volatile("mfc0 %0,$9":"=r"(value1));
			
			break;
	}
	return;
}

