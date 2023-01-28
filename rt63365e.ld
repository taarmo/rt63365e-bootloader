
MEMORY
{
	RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 32M 
	FLASH (rx) : ORIGIN = 0xbfc00000, LENGTH = 8M 
}

__stack_size = 0x1200;

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

	.rodata : {
		__rodata_start = .;
		__cte1 = .;
		LONG(0x25222719)
		__cte2 = .;
		LONG(0x202e2424)
 	   	*(.rodata)
 	   	*(.rodata.*)
		__rodata_end = .;
 	 } > FLASH		/* read-only data */	

	.text : {
		_stext = .;
		*(.text.init_main)
		*(.text.main)
		*(.text)
		_etext = .;
	} > RAM AT>FLASH

	.data : { 
		_sdata = .;
		*(.data.*) 
		_gp = ALIGN(16);
		*(.data) 
		_edata = .;
	} > RAM	AT>FLASH	/* initialized data */

	.bss : ALIGN(16) { 
		__bss_start = .;
		*(.bss) 
		*(.bss.*) 
		__bss_end = .;
	} > RAM			/* cleared-to-zero data */

	.stack : ALIGN(16){
		__stack_end = .;
		. = . + __stack_size;
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
_irq_size = _eirq - _sirq;
_rodata_size = __rodata_end - __rodata_start;
_text_size = _etext - _stext;
_data_size = _edata - _sdata;

_init_text_flash = _init_size + _irq_size + _rodata_size + 4;
_fin_text_flash = _init_text_flash + _text_size + 16;

_init_data_flash = _init_size + _irq_size + _rodata_size + _text_size + 4;
_fin_data_flash = _init_data_flash + _data_size;



