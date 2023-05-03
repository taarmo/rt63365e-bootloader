
#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define STR(x) #x

void show_regs();
void memcpy32(void *dst, void *src, size_t size);
u32 memcmp(const void *str1, const void *str2, size_t count);
void *memcpy(void *dest, const void *src, size_t len);
void *memset(void *s, int c,  unsigned int len);

void xxd(u8 *arr, u32 size, u32 col);
u32 crc32_compute(u8 const * p_data, u32 size, u32 const * p_crc);
 
inline void write32(u32 *addr,u32 val) {
	__asm__ volatile("sw\t%1,%0" : "+m"(*addr):"r"(val));
}

inline void write8(u32 *addr,u8 val) {
	__asm__ volatile("sb\t%1,%0" : "+m"(*addr):"r"(val));
}

inline u32 read32(u32 *addr) {
	u32 val;
	__asm__ volatile("lw\t%0,%1" : "=r"(val): "m"(*addr));
	return val;
}

inline u32 read8(u32 *addr) {
	u8 val;
	__asm__ volatile("lb\t%0,%1" : "=r"(val): "m"(*addr));
	return val;
}

	
#define jump(addr)								\
	__asm__ volatile("j\t " #addr);

#define mfc0(source, reg, val)							\
	if(val == 0){								\
		__asm__ volatile("mfc0\t%0, " STR(reg) : "=r"(source));		\
	}else{									\
		__asm__ volatile("mfc0\t%0, " STR(reg) "," #val : "=r"(source));	\
	}

#define mtc0(source,reg,val)							\
	if(val == 0){								\
		__asm__ volatile("mtc0\t%0, " STR(reg) :: "r"(source));		\
	}else{									\
		__asm__ volatile("mtc0\t%0, " STR(reg) "," #val :: "r"(source)); 	\
	}

#define cache(base,op)       							\
	__asm__ volatile("cache %1, (%0)":: "r"(base),"i"(op));

#define sync() 									\
	__asm__ volatile("sync 0x0":::);

#define hazardbarrier() 							\
	__asm__ volatile("ssnop\n"					   	\
			 "ssnop\n"					   	\
			 "ssnop\n"					   	\
			 "ehb\n":::);  

#endif
