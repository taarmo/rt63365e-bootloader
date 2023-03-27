
#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

void memcpy32(void *dst, void *src, size_t size);
u32 memcmp(const void *str1, const void *str2, size_t count);

void xxd(u8 *arr,int size,int col);
u32 crc32_compute(u8 const * p_data, u32 size, u32 const * p_crc);
void jump_to_addr(u32 *addr);
void reset();
 
void inline write32(u32 *addr,u32 val){
	__asm__ volatile("sw\t%1,%0" : "+m"(*addr):"r"(val));
}

void inline write8(u32 *addr,u8 val){
	__asm__ volatile("sb\t%1,%0" : "+m"(*addr):"r"(val));
}

u32 inline read32(u32 *addr){
	u32 val;
	__asm__ volatile("lw\t%0,%1" : "=r"(val): "m"(*addr));
	return val;
}

u32 inline read8(u32 *addr){
	u8 val;
	__asm__ volatile("lb\t%0,%1" : "=r"(val): "m"(*addr));
	return val;
}

#define mfc0(source,reg,val)										 \
	if(val == 0){													 \
		__asm__ volatile("mfc0\t%0, " #reg : "=r"(source));			 \
	}else{															 \
		__asm__ volatile("mfc0\t%0, " #reg "," #val : "=r"(source)); \
	}

#define mtc0(source,reg,val)										 \
	if(val == 0){													 \
		__asm__ volatile("mtc0\t%0, " #reg :: "r"(source));			 \
	}else{															 \
		__asm__ volatile("mtc0\t%0, " #reg "," #val :: "r"(source)); \
	}

#define cache(base,op)       \
	__asm__ volatile("cache %1, (%0)":: "r"(base),"i"(op));

#define sync() \
	__asm__ volatile("sync 0x0":::);

#define hazardbarrier() \
	__asm__ volatile("ssnop\n"					   \
			 "ssnop\n"					   \
			 "ssnop\n"					   \
			 "ehb\n":::);  

#endif
