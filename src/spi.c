#include "utils.h"
#include "uart.h"
#include "spi.h"

u32 build_frame(enum OP_FLASH op,u32 data){
		volatile u32 val = 0;
		while((val = read32((u32 *)0xbfbc0000))&0x10000);
		if(op == DEFAULT){
			write32(0xbfbc0000, (0xfffff000) | 0x00000101);  									//enable and size frame
			write32(0xbfbc0004, (0xffffff00) | (data & 0xff));
		}else{
			//write32(0xbfbc0004, (data&0xff0000)<<7 | (data & 0xff00)<<7 | (data&0xff)<<7 | op&0xff );
			write32(0xbfbc0004, (data&0xff00)<<16 | (data & 0xff)<<8 | op&0xff );
			write32(0xbfbc0000, 0x00000100 | val&0x00ffffff | (data & 0xff0000)<<8 | 1<<4 | 4 );      //enable and size frame
			while((val = read32((u32 *)0xbfbc0000))&0x10000);
			val = read32(0xbfbc0008);
		}	
		return val;
}

u32 spi_read(){
	u32 val = 0;
	//while(val = read32((u32 *)0xbfbc0000)&0x10000 != 0);
	val = read32((u32 *)0xbfbc0008);
	return val;
}

void spi_write(u32 off,u32 val){
	return write32((u32 *)0xbfbc0000 + off,val);
}
