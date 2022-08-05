#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
 
/*#define read32(addr)       \
	*((u32 *) addr) 

#define write32(addr, val)     \
	*((u32 *) addr) = (u32)val;	*/


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

#define memcpy32(src,dst,fin)					  \
	__asm__ volatile("move $k0,%0\n"			  \
			 "move $k1,%1\n"			  \
			 "a:lw $t0,0x0($k0)\n" 		  \
			 "sw $t0,0x0($k1)\n"		  \
			 "addiu $k0,$k0,0x4\n"		  \
			 "addiu $k1,$k1,0x4\n"		  \
			 "bne $k0,%2,a\n" ::"r"(src),"r"(dst),"r"(fin) );

#define clear()				\
	__asm__ volatile("add $v0,$0,$0");

#define cache(base,op)       \
	__asm__ volatile("cache %1, (%0)":: "r"(base),"i"(op));

#define sync() \
	__asm__ volatile("sync":::);

#define hazardbarrier() \
	__asm__ volatile("ssnop\n"					   \
			 "ssnop\n"					   \
			 "ssnop\n"					   \
			 "ehb\n":::);  

#define nopslide()			\
	__asm__ volatile(		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n"      		\
		"nop\n");      		

/*#define read32(addr)      					       \
({ register u32 __res;                             \
        __asm__ __volatile__(                      \
			"lw %0,%1" : "=r"(__res):"i"(addr));   \
    __res;                                         \
});




#define readc0(source, sel)      \
({ register int __res;                             \
    if (sel == 0)                                  \
        __asm__ __volatile__(                      \
            "mfc0\t%0, " #source "\n\t"            \
            : "=r" (__res));                       \
    else                                           \
        __asm__ __volatile__(                      \
            ".set\tmips32\n\t"                     \
            "mfc0\t%0, " #source ", " #sel "\n\t"  \
            ".set\tmips0\n\t"                      \
            : "=r" (__res));                       \
    __res;                                         \
});

#define writec0(register, sel, value)   \
do {                                    				  \
    if (sel == 0)                           			  \
        __asm__ __volatile__(                    		  \
            "mtc0\t%z0, " #register "\n\t"          	  \
            : : "Jr" ((unsigned int)(value)));      	  \
    else                                				  \
        __asm__ __volatile__(                   		  \
            ".set\tmips32\n\t"              			  \
            "mtc0\t%z0, " #register ", " #sel "\n\t"      \
            ".set\tmips0"                   			  \
            : : "Jr" ((unsigned int)(value)));      	  \
} while (0) */


#endif
