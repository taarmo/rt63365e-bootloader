
#ifndef __SPI_H__
#define __SPI_H__

#include "types.h"


#define SPI_CTL_BUSY 0x00010000
#define SPI_ENABLE 0x00000100
#define SPI_CTL_TX_RX_CNT_MASK 0x000000ff


struct t_comm {
	u32 op;
	u8 tx;
	u8 rx;
};

u32 spi_write_comm(struct t_comm , u32, u32);
void spi_write(u8, u32, u8 *, u32);
void spiWrite8(u8);
void spiWrite16(u16);
void spi_write_data(u8 *, u32 , u32 );
void writeCommand(u8);
void writedata(u8); 
void adjust_clk_spi(u8 divisor);


/***************************************************************************************
** Function name:           spiWait
** Descriptions:            12 cycle delay
***************************************************************************************/
inline void spiWait12(void) {
  __asm__ volatile
  (
    "	nop         \n"	// 1
    "	nop         \n"	// 2
    "	nop         \n"	// 3
    "	nop         \n"	// 4
    "	nop         \n"	// 5
    "	nop         \n"	// 6
    "	nop         \n"	// 7
    "	nop         \n"	// 8
    "	nop         \n"	// 9
    "	nop         \n"	// 10
    "	nop         \n"	// 11
    "	nop         \n"	// 12
  );
}

/***************************************************************************************
** Function name:           spiWait
** Descriptions:            14 cycle delay
***************************************************************************************/
inline void spiWait14(void) {
  __asm__ volatile
  (
    "	nop         \n"	// 1
    "	nop         \n"	// 2
    "	nop         \n"	// 3
    "	nop         \n"	// 4
    "	nop         \n"	// 5
    "	nop         \n"	// 6
    "	nop         \n"	// 7
    "	nop         \n"	// 8
    "	nop         \n"	// 9
    "	nop         \n"	// 10
    "	nop         \n"	// 11
    "	nop         \n"	// 12
    "	nop         \n"	// 13
    "	nop         \n"	// 14
  );
}

/***************************************************************************************
** Function name:           spiWait
** Descriptions:            15 cycle delay
***************************************************************************************/
inline void spiWait15(void) {
__asm__ volatile
  (
    "	nop 	       \n"	// 1
    "	nop 	       \n"	// 2
    "	nop            \n"	// 3
    "	nop	       \n"	// 4
    "	nop            \n"	// 5
    "	nop	       \n"	// 6
    "	nop	       \n"	// 7
    "	nop	       \n"	// 8
    "	nop	       \n"	// 9
    "	nop	       \n"	// 10
    "	nop	       \n"	// 11
    "	nop	       \n"	// 12
    "	nop	       \n"	// 13
    "	nop	       \n"	// 14
    "	nop	       \n"	// 15
  );
}

inline void spiWait17(void) {
  __asm__ volatile
  (
    "	nop         \n"	// 1
    "	nop         \n"	// 2
    "	nop         \n"	// 3
    "	nop         \n"	// 4
    "	nop         \n"	// 5
    "	nop         \n"	// 6
    "	nop         \n"	// 7
    "	nop         \n"	// 8
    "	nop         \n"	// 9
    "	nop         \n"	// 10
    "	nop         \n"	// 11
    "	nop         \n"	// 12
    "	nop         \n"	// 13
    "	nop         \n"	// 14
    "	nop         \n"	// 15
    "	nop         \n"	// 16
    "	nop         \n"	// 17
  );
}


#endif
