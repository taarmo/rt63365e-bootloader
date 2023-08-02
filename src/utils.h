
#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define STR(x) #x

void show_regs();
void memcpy32(void *dst, void *src, size_t size);
u32 memcmp(const void *str1, const void *str2, size_t count);
void *memcpy(void *dest, void *src, size_t len);
void *memset(void *s, int c,  unsigned int len);
void delay_us(u32 t);

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

inline void jump(void *addr) {
	((void(*)()) addr)();
}

#define mfc0(source, reg, val)								\
	if(val == 0){									\
		__asm__ volatile("mfc0\t%0, " STR(reg) : "=r"(source));			\
	}else{										\
		__asm__ volatile("mfc0\t%0, " STR(reg) "," #val : "=r"(source));	\
	}

#define mtc0(source, reg, val)								\
	if(val == 0){									\
		__asm__ volatile("mtc0\t%0, " STR(reg) :: "r"(source));			\
	}else{										\
		__asm__ volatile("mtc0\t%0, " STR(reg) "," #val :: "r"(source)); 	\
	}

#define cache(op,addr)						\
	__asm__ __volatile__(						\
	"	.set	push					\n"	\
	"	.set	noreorder				\n"	\
	"	.set	mips3\n\t				\n"	\
	"	cache	%0, %1					\n"	\
	"	.set	pop					\n"	\
	:								\
	: "i" (op), "R" (*(unsigned char *)(addr)))


#define hazardbarrier() 								\
	__asm__ volatile("ssnop\n"					   		\
			 "ssnop\n"					   		\
			 "ssnop\n"					   		\
			 "ehb\n":::);  

#define instruction_hazard()								\
do {											\
	unsigned long tmp;								\
											\
	__asm__ __volatile__(								\
	"	.set	mips64r2				\n"			\
	"	dla	%0, 1f					\n"			\
	"	jr.hb	%0					\n"			\
	"	.set	mips0					\n"			\
	"1:							\n"			\
	: "=r" (tmp));									\
} while (0)

#endif
