
MEMORY
{
	RAM (rwx) : ORIGIN = 0x80000300, LENGTH = 32M 
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
		. = ALIGN(16);
		_inite_sym = .;
	} > FLASH

	.rodata : {
		__rodata_start = .;
 	   	*(.rodata)
 	   	*(.rodata.*)
		. = ALIGN(16);
		__rodata_end = .;
 	 } > FLASH		/* read-only data */	

	.text : {
		_stext = .;
		*(.text.init_main)
		*(.text.main)
		*(.text.*)
		. = ALIGN(16);
		_etext = .;
	} > RAM AT>FLASH

	.data : { 
		_sdata = .;
		*(.data.*) 
		_gp = ALIGN(16);
		*(.data) 
		_edata = .;
	} > RAM	AT>FLASH	/* initialized data */

	.bss : { 
		__bss_start = .;
		*(.bss) 
		*(.bss.*) 
		*(.sbss)
		*(.sbss*)
		. = ALIGN(16);
		__bss_end = .;
	} > RAM			/* cleared-to-zero data */

	.stack : {
		__stack_end = .;
		. = . + __stack_size;
		*(.stack)
		. = ALIGN(16);
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

/*_init_size = _inite_sym - _inits_sym;*/
_init_size = SIZEOF(.init);
/*_rodata_size = __rodata_end - __rodata_start;*/
_rodata_size = SIZEOF(.rodata);
/*_text_size = _etext - _stext;*/
_text_size = SIZEOF(.text);
/*_data_size = _edata - _sdata;*/
_data_size = SIZEOF(.data);
/*_data_size = __bass_end - __bss_start */ 
_bss_size = SIZEOF(.bss);

_init_text_flash = _init_size + _rodata_size;
_fin_text_flash = _init_text_flash + _text_size;
_init_data_flash = _init_size + _rodata_size + _text_size;
_fin_data_flash = _init_data_flash + _data_size;

