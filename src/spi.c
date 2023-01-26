#include "types.h"
#include "utils.h"
#include "uart.h"
#include "spi.h"

u32 send_cmd(struct t_comm comm,u32 addr,u32 data){
	u32 val = 0;
	u32 reg;
	while((val = read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);

	write32((u32 *)0xbfbc0008,(data)>>24| (data & 0x00ff0000)>>8 |(data&0x0000ff00)<<8 | (data & 0xff)<<24); 

	write32((u32 *)0xbfbc0004, (addr&0x00ffffff) << 8 | comm.op & 0xff);

    reg = reg & ~SPI_CTL_TX_RX_CNT_MASK | comm.rx<<4 | comm.tx | SPI_ENABLE;

    write32((u32 *)0xbfbc0000,reg);

    if(comm.rx > 0){
		while((val = read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);
        reg = read32((u32 *)0xbfbc0008);
        reg &= (0xffffffff >> ((4 - comm.rx) << 3));
    }else
        reg = 0;
    
    return reg;
}

void spi_write(u8 op,u32 to,u8 data[256],u32 size){
	if(size <= 0 && size >=256)return;
	
    u32 n_bytes_data = size-1;
    u8 remainder = n_bytes_data % 4;
	
	u32 val = 0;
	while((val = read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);

    u32 reg_value = read32((u32 *)0xbfbc0028);
	write32((u32 *)0xbfbc0028,reg_value | (1 << 2));
    write32((u32 *)0xbfbc002c,0x28000000|(n_bytes_data<<3));

    u32 i = 0;
    while(i < ((n_bytes_data>>2)<<2)){
        write32((u32 *)0xbfbc0008+i, data[i+3] << 16 | data[i+2]<<8 | data[i+1] | data[i+4]<<24);
        i+=4;
	}

    if(remainder == 1){
        write32((u32 *)0xbfbc0008+i, data[i+1] );
	}else if(remainder == 2){
        write32((u32 *)0xbfbc0008+i, data[i+2]<<8 | data[i+1] );
	}else if(remainder == 3){
        write32((u32 *)0xbfbc0008+i, data[i+3] << 16 | data[i+2]<<8 | data[i+1] );
	}
    write32((u32 *)0xbfbc0004, (to&0x00ffffff)<<8 | data[0]);

    val = (val & ~SPI_CTL_TX_RX_CNT_MASK) | n_bytes_data | SPI_ENABLE | (op << 24);
    write32((u32 *)0xbfbc0000, val);
    //write32(0xbfbc0038,0x1);
}


