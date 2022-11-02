
MEMORY
{
	RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 32M 
	FLASH (rx) : ORIGIN = 0xbfc00000, LENGTH = 8M 
}

__stack_size = 0x2000;
__data_size = 0x200;

ENTRY(__start)

SECTIONS
{
	.init : {
		_inits_sym = .;
		*(.init)
		*(.init.*)
		_inite_sym = .;
		_sirq = .;
		*(.text.irq)
		_eirq = .;
	} > FLASH

	.text : {
		_stext = .;
		*(.text.init_main)
		*(.text.main)
		*(.text)
		_etext = .;
	} >RAM AT>FLASH

	.rodata : { *(.rodata) } > FLASH	/* read-only data */	

	.data : { 
		__global_pointer = .;
		*(.data) 
		__cte1 = .;
		LONG(0x25222719)
		__cte2 = .;
		LONG(0x202e2424)
		. = . + __data_size;
		_edata = .;
	} > FLASH					/* initialized data */

	.bss : { 
		__bss_start = .;
		*(.bss) 
		__bss_end = .;
	} > RAM					/* cleared-to-zero data */

	.stack : {
		. = ALIGN(16);
		__stack_end = .;
		. = . + __stack_size;
		. = ALIGN(16);
		*(.stack)
		__stack_addr = .;
	} > RAM


	/*
	 * Debug info
	 */

	/* stabs debug sections */
	.stab 0:		{ *(.stab) } .stabstr 0:		{ *(.stabstr) }

	/* DWARF debug sections */
	.debug 0:		{ *(.debug) }
	.debug_srcinfo 0:	{ *(.debug_srcinfo) }
	.debug_aranges 0:	{ *(.debug_aranges) }
	.debug_pubnames 0:	{ *(.debug_pubnames) }
	.debug_sfnames 0:	{ *(.debug_sfnames) }
	.line 0:		{ *(.line) }
	/*.note.gnu.build-id*/
	/DISCARD/ :
	{
		*(.note*)
		*(.reginfo) 
		*(.MIPS.abiflags)
	}
}

_init_size = _inite_sym - _inits_sym;
_text_size = _etext - _stext;

_init_text_flash = _inits_sym + _init_size;
_fin_text_flash = _init_text_flash + _text_size + 16;


