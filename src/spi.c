#include "types.h"
#include "utils.h"
#include "spi.h"
#include "flash.h"
#include "gpio.h"

void adjust_clk_spi(u8 divisor) {
	write32((u32 *)0xbfbc0028, ((read32((u32 *) 0xbfbc0028)) & 0xf000ffff) | (divisor << 16));
}

u32 spi_write_comm(struct t_comm comm,u32 addr,u32 data) {
	u32 reg = 0;
	while ((reg = read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);

	write32((u32 *)0xbfbc0008, (data)>>24 | (data & 0x00ff0000)>>8 |(data&0x0000ff00)<<8 | (data & 0xff)<<24); 

	write32((u32 *)0xbfbc0004, (addr&0x00ffffff) << 8 | (comm.op & 0xff));

	reg = (reg & ~SPI_CTL_TX_RX_CNT_MASK) | (comm.rx<<4) | comm.tx | SPI_ENABLE;

    	write32((u32 *)0xbfbc0000, reg);

	if (comm.rx > 0){
		while ((reg = read32((u32 *)0xbfbc0000)) & SPI_CTL_BUSY);
        	reg = read32((u32 *)0xbfbc0008);
        	reg &= (0xffffffff >> ((4 - comm.rx) << 3));
	} else
        	reg = 0;

    	return reg;
}

void spi_write(u8 op, u32 to, u8 *data, u32 size) {
	if (!size || size > 33) return;
	
	u32 n_bytes_data = size-1;
	u8 remainder = n_bytes_data % 4;

	u32 state = 0;
	u32 val = 0;
	while ((state = read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);

	u32 reg_value = read32((u32 *)0xbfbc0028);
	write32((u32 *)0xbfbc0028, reg_value | (1 << 2));
	write32((u32 *)0xbfbc002c, 0x28000000 | (n_bytes_data << 3));

	u32 i = 0;
	u32 * addr = (u32 *)0xbfbc0008;
	while (i < ((n_bytes_data>>2)<<2)) {
		write32(addr, data[i+3] << 16 | data[i+2]<<8 | data[i+1] | data[i+4]<<24);
		addr++;
		i+=4;
	}

	if (remainder == 1) {
		write32((u32 *)addr, data[i+1]);
	} else if(remainder == 2) {
		write32((u32 *)addr, data[i+2]<<8 | data[i+1]);
	} else if(remainder == 3) {
		write32((u32 *)addr, data[i+3] << 16 | data[i+2] << 8 | data[i+1]);
	}
	write32((u32 *)0xbfbc0004, (to&0x00ffffff)<<8 | data[0]);

	val = (state & ~SPI_CTL_TX_RX_CNT_MASK) | n_bytes_data | SPI_ENABLE | (op << 24);
	write32((u32 *)0xbfbc0000, val);
	while ((read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);
	write32((u32 *)0xbfbc002c, 0x0);
	write32((u32 *)0xbfbc0028, reg_value );
	
}

void spiWrite8(u8 op) {
	
	u32 reg = read32((u32 *)0xbfbc0000);
	u32 val;
	while ((val = read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);

	write32((u32 *)0xbfbc0004, op);

	reg = (reg & ~SPI_CTL_TX_RX_CNT_MASK) | 1 | SPI_ENABLE;

	write32((u32 *)0xbfbc0000,reg);
}

void spiWrite16(u16 data) {
	u32 reg = 0;
	u32 val = 0;
	while ((val = read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);

	write32((u32 *)0xbfbc0004, (data & 0xff) << 24 | ((data & 0xff00) >> 8));
 
	reg = (val & ~SPI_CTL_TX_RX_CNT_MASK) | 2 | SPI_ENABLE;

    	write32((u32 *)0xbfbc0000, reg);
}



void spi_write_data(u8 * data, u32 rx, u32 size) {

	u32 reg = 0;
	u32 d = 0;
	u32 f = 0;
	while ((read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);

	if (size >= 1 && size <= 4) {
		d = data[0];
		if (size == 2) {
			f = data[1];
		} else if (size == 3) {
			d |= (data[2] << 24);
			f = data[1];	
		} else if (size == 4) {
			d |= ((data[2] << 24) | (data[3] << 16));
			f = data[1];	
		}

		write32((u32 *)0xbfbc0004, d);
		reg = (reg & ~SPI_CTL_TX_RX_CNT_MASK) | rx<<4 | size | SPI_ENABLE | (f << 24);
		write32((u32 *)0xbfbc0000, reg);

	} else if (size >= 5) {
		u32 n_bytes_data = size - 5;
		u8 remainder = size % 4;

		u32 val = 0;
		while ((read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);

		u32 reg_value = read32((u32 *)0xbfbc0028);
		write32((u32 *)0xbfbc0028, reg_value | (1 << 2));
		write32((u32 *)0xbfbc002c, 0x28000000 | (n_bytes_data << 3));

		u32 i = 4;
		u32 * addr = (u32 *)0xbfbc0008;
		while (i < ((size>>2)<<2)) {
			write32(addr, data[i+3] << 16 | data[i+2]<<8 | data[i+1] | data[i+4]<<24);
			addr++;
			i+=4;
		}

		if (remainder == 1) {
			write32((u32 *)addr, data[i+1]);
		} else if(remainder == 2) {
			write32((u32 *)addr, data[i+2]<<8 | data[i+1]);
		} else if(remainder == 3) {
			write32((u32 *)addr, data[i+3] << 16 | data[i+2] << 8 | data[i+1]);
		}
		write32((u32 *)0xbfbc0004, (data[1] << 24 | data[2] << 16 | data[3] << 8 ) | data[4]);

		val = (val & ~SPI_CTL_TX_RX_CNT_MASK) | n_bytes_data | SPI_ENABLE | (data[0] << 24);
		write32((u32 *)0xbfbc0000, val);
		while ((read32((u32 *)0xbfbc0000))& SPI_CTL_BUSY);
		write32((u32 *)0xbfbc002c, 0x0);
		write32((u32 *)0xbfbc0028, reg_value );

	}

    //if(rx > 0):
    //    rem = rx % 4
    //    while reg := p.read32(0xbfbc0000) & SPI_CTL_BUSY:
    //        pass
    //    while i < rx:
    //        reg = p.read32(0xbfbc0008 + i) 
    //        i+=4
    //        rx-=4
    //    reg &= (0xffffffff >> ((rem) << 3));
    //else:
    //    reg = 0
    //return reg  
}

void writeCommand(u8 c) {
	control_dcx(ON);
	spiWrite8(c);
	//delay_us(1);
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();

	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
}

void writedata(u8 c) {
	control_dcx(OFF);
	spiWrite8(c);
	//delay_us(1);
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();

	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
	spiWait17();
}

extern inline void spiWait12(void);
extern inline void spiWait14(void);
extern inline void spiWait15(void);
extern inline void spiWait17(void);
