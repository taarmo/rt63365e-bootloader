
ENTRY(__start)

__base_addr = 0x80040000;
/*__base_addr = 0x5000;*/

SECTIONS
{
	. = __base_addr;

	__code_start = .;

	.init :
	{
		*(.init)
		. = ALIGN(4);
	}

	.got :
	{
		__got_start = .;
		*(.got.*)
		*(.got)
		. = ALIGN(4);
		__got_end = . ;
	}

	.text : {
		_stext = .;
		*(.text)
		*(.text*)
		_etext = .;
	} 

	.rodata :
	{
		*(.rodata)
		*all.rodata*(*)
		*(.roda)
		*(.rodata.*)
		*(.gnu.linkonce.r*)
		. = ALIGN(4);
	}
	
	.data :
	{
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d*)
		. = ALIGN(4);
	}
	
	.bss :
	{
		__bss_start = . ;
		*(.dynbss)
		*(.gnu.linkonce.b*)
		*(.bss*)
		*(.sbss*)
		*(COMMON)
		. = ALIGN(32);
		__bss_end = . ;
	}
	/DISCARD/ :
	{
		*(.note.*)
		*(.MIPS.*)
		*(.reginfo)
	}
}

__stack_end = (__bss_end);
__stack_addr = (__bss_end + 0x100);

__end = __stack_addr ;
__loader_size = __end - __code_start;

PROVIDE (__stack_end = __stack_end);
PROVIDE (__stack_addr = __stack_addr);
PROVIDE (__got_start = __got_start);
PROVIDE (__got_end = __got_end);
PROVIDE (__bss_start = __bss_start);
PROVIDE (__bss_end = __bss_end);


