#include "m32c0.h"
#include "utils.h"


void flush_icache_range_gdb(unsigned long start_addr, unsigned long size) {		
	unsigned long lsize = 32;
	unsigned long addr = start_addr & ~(lsize - 1);
	unsigned long aend = (start_addr + size - 1) & ~(lsize - 1);


	while (1) {							
		cache(Hit_Writeback_Inv_D, addr);
		__asm__ volatile ("sync");
		cache(Hit_Invalidate_I, addr);				
		if (addr == aend)					
			break;						
		addr += lsize;						
	}								

	instruction_hazard();
}

void flush_dcache_range_gdb(unsigned long start_addr, unsigned long size) {
	unsigned long lsize = 32;
	unsigned long addr = start_addr & ~(lsize - 1);
	unsigned long aend = (start_addr + size - 1) & ~(lsize - 1);

	while (1) {							
		cache(Hit_Invalidate_D, addr);				
		if (addr == aend)					
			break;						
		addr += lsize;						
	}								

	instruction_hazard();
}

void flush_cache_gdb(unsigned long start_addr, unsigned long size) {
	unsigned long lsize = 32;
	unsigned long addr = start_addr & ~(lsize - 1);
	unsigned long aend = (start_addr + size - 1) & ~(lsize - 1);

	while (1) {
		cache(Hit_Writeback_Inv_D, addr);
		cache(Hit_Invalidate_I, addr);
		if (addr == aend)
			break;
		addr += lsize;
	}
}



