#include "types.h"
#include "uart.h"

void write32(u32 *addr,u32 val) {
	__asm__ volatile("sw\t%1,%0" : "+m"(*addr):"r"(val));
}

void write8(u32 *addr,u8 val) {
	__asm__ volatile("sb\t%1,%0" : "+m"(*addr):"r"(val));
}

u32 read32(u32 *addr) {
	u32 val;
	__asm__ volatile("lw\t%0,%1" : "=r"(val): "m"(*addr));
	return val;
}

u32 read8(u32 *addr) {
	u8 val;
	__asm__ volatile("lb\t%0,%1" : "=r"(val): "m"(*addr));
	return val;
}

u32 memcmp(const void *str1, const void *str2, size_t count) {
  const unsigned char *s1 = str1;
  const unsigned char *s2 = str2;

  while (count-- > 0)
    {
      if (*s1++ != *s2++)
	  return s1[-1] < s2[-1] ? -1 : 1;
    }
  return 0;
}

void *memset(void *s, int c,  unsigned int len) {
    unsigned char* p=s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

void xxd(u8 *arr,u32 size,u32 col) {
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
    for (u32 i = 0; i < size; i++)
    {
        crc = crc ^ p_data[i];
        for (u32 j = 8; j > 0; j--)
        {
            crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1));
        }
    }
    return ~crc;
}

void jump_to_addr(u32 *addr) {
	((void(*)()) addr)();
}

void reset() {
	jump_to_addr((u32*)0xbfc00000);
}


