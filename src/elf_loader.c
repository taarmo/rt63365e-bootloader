#include "types.h"
#include "uart.h"
#include "utils.h"
#include "elf.h"


void *loadelf(const u8 *elf) {
	if(memcmp("\x7F" "ELF\x01\x02\x01",elf,7)) {
		uart_puts((u8 *)"ERROR\n");
		return (void *)0x0;
	}
	
	Elf32_Ehdr *ehdr = (Elf32_Ehdr*)elf;
	if(ehdr->e_phoff == 0) {
		uart_puts((u8 *)"ERROR\n");
		return (void *)0x0;
	}
	int count = ehdr->e_phnum;
	Elf32_Phdr *phdr = (Elf32_Phdr*)(elf + ehdr->e_phoff);
	while(count--)
	{
		if(phdr->p_type == PT_LOAD) {
			const void *src = elf + phdr->p_offset;
			memcpy(phdr->p_paddr, (void *)src, phdr->p_filesz);
		}
		phdr++;
	}
	return ehdr->e_entry;
}

void *_main_elf(void *base)
{
	u8 *elf;
	void *entry;
	
	elf = (u8*) base;
	
	entry = loadelf(elf);
	return entry;

}
