#include "types.h"
#include "regdef.h"
#include "utils.h"
#include "uart.h"
#include "gpio.h"

extern inline void write32(u32 *addr,u32 val);
extern inline void write8(u32 *addr,u8 val);
extern inline u32 read32(u32 *addr);
extern inline u32 read8(u32 *addr);

void delay_us(u32 t) {
	u32 time_init, time_end;
	u32 aux;
	//u32 limit = t << 8; 1.1us
	u32 limit = t*250; 
	mfc0(time_init, C0_COUNT, 0);
	mfc0(time_end, C0_COUNT, 0);
	if (time_init > time_end) {
		mfc0(aux, C0_COUNT, 0);
		while(aux >= time_init) {
			mfc0(aux, C0_COUNT, 0);
		}
		mfc0(time_init, C0_COUNT, 0);
	}
	mfc0(time_end, C0_COUNT, 0);
	while ((time_end - time_init) < limit) {
		mfc0(time_end, C0_COUNT, 0);
	}
}

void flush_and_reboot() {
	jump(0x81f00000);
}

//debug_printf(fmt, ##__VA_ARGS__);

void * memcpy(void *dest, void *src, size_t len) {
        char *d = dest;
        const char *s = src;
        while (len--)
                *d++ = *s++;
        return dest;
}


u32 memcmp(const void *str1, const void *str2, size_t count) {
	const unsigned char *s1 = str1;
	const unsigned char *s2 = str2;

	while (count-- > 0) {
		if (*s1++ != *s2++) return s1[-1] < s2[-1] ? -1 : 1;
	}
	return 0;
}

void *memset(void *s, int c, u32 len) {
	unsigned char* p=s;
	while(len--) {
		*p++ = (unsigned char)c;
	}
	return s;
}

void xxd(u8 *arr, u32 size, u32 col) {
	uart_printf( "%x| ", (u32 *)arr);
	for(u8 i = 1; i < size; i++){
		uart_printf( "%02hhx ", *(arr+i-1) );
		if(!(i % col)){
			uart_puts((u8 *)"\n\r");
			uart_printf( "%x| ", (u32 *)(arr+i));
		}
	}
	uart_puts((u8 *)"\n\r");
}	

u32 crc32_compute(u8 const * p_data, u32 size, u32 const * p_crc) {
	u32 crc;

	crc = (p_crc == NULL) ? 0xFFFFFFFF : ~(*p_crc);
	for (u32 i = 0; i < size; i++) {
		crc = crc ^ p_data[i];
		for (u32 j = 8; j > 0; j--) {
			crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1));
		}
	}
	return ~crc;
}

static inline u32 read_reg(u32 reg) {
	u32 val;
	__asm__ volatile("sw\t $%1,%0" : "=m"(val) :"i"(reg));	
	return val;
}


void show_regs() {
	u32 inctl, status, epc, depc;
	mfc0(status, C0_STATUS, 0);
	mfc0(epc, C0_EPC, 0);
	mfc0(depc, C0_DEPC, 0);
	mfc0(inctl, C0_INTCTL, 1);
	uart_printf("zero: %08lx at: %08lx\n\r",
	       read_reg(0), read_reg(1));
	uart_printf("v0: %08lx v1: %08lx a0: %08lx a1: %08lx a2: %08lx a3: %08lx t0: %08lx t1: %08lx\n\r",
	       read_reg(2), read_reg(3), read_reg(4), read_reg(5),
	       read_reg(6), read_reg(7), read_reg(8), read_reg(9));
	uart_printf("t2: %08lx t3: %08lx t4: %08lx t5: %08lx t6: %08lx t7: %08lx s0: %08lx s1: %08lx\n\r",
	       read_reg(10), read_reg(11), read_reg(12), read_reg(13),
	       read_reg(14), read_reg(15), read_reg(16), read_reg(17));
	uart_printf("s2: %08lx s3: %08lx s4: %08lx s5: %08lx s6: %08lx s7: %08lx t8: %08lx t9: %08lx\n\r",
	       read_reg(18), read_reg(19), read_reg(20), read_reg(21),
	       read_reg(22), read_reg(23), read_reg(24), read_reg(25));
	uart_printf("k0: %08lx k1: %08lx gp: %08lx sp: %08lx fp: %08lx ra: %08lx\n\r",
	       read_reg(26), read_reg(27), read_reg(28), read_reg(29), read_reg(30), read_reg(31));
	uart_printf("inctl: %08lx status: %08lx epc: %08lx dpc: %08lx\n\r",
	       inctl, status, epc, depc);

}


